# 10GbE FPGA Market Data Datapath

A SystemVerilog project targeting the AMD VCU118. The goal is to receive synthetic market data over Ethernet and UDP, track quote state, evaluate integer-scaled rules, and generate simulated order intents after hardware risk checks. The first milestone is to capture and read back a known Ethernet frame.

## Current status

The **RX frame capture prototype works in directed RTL simulation**. The tests drive a MAC-style receive stream directly and check the internal readback data. The VCU118 Ethernet link, Vivado memory mapping, and end-to-end throughput are still to be verified. **10GbE line rate is a design target.**

| Block | Status |
| --- | --- |
| [Ethernet frame capture](rtl/packet_capture.sv) | Captures one frame at a time on a 64-bit receive interface. Stores data and byte masks, reads back the frame, then rearms for another capture. |
| [Market data decoder](rtl/market_data_decoder.sv) | Standalone decoder for a synthetic 31-byte quote payload. Checks message type, nonzero sizes, and `bid <= ask`. The decoder takes an already extracted payload. |
| [Synchronous FIFO](rtl/sync_fifo.sv) | Standalone parameterized FIFO with directed cocotb coverage. It is available for later stages that need buffering. |
| [TX traffic generator](rtl/traffic_gen.sv) | Placeholder. An external sender is the planned source for the first board capture. |

## Ethernet architecture

The board plan uses one QSFP1 lane on the VCU118. AMD's Ethernet Subsystem IP supplies the MAC and 10GBASE-R PCS, with a dedicated GTY transceiver for the serial link. The custom RTL connects at the 64-bit AXI4-Stream interfaces.

```text
RX   Link partner → QSFP1 → GTY → AMD Ethernet PCS/MAC
       → 64-bit AXI4-Stream → frame capture → capture memory → readback

TX   Planned test-frame generator → 64-bit AXI4-Stream
       → AMD Ethernet MAC/PCS → GTY → QSFP1 → link partner
```

The planned application path adds Ethernet/IPv4/UDP parsing and frame validation before quote processing. Accepted payloads go to the decoder, then to sequence tracking, bounded per-symbol quote state, and an integer-scaled decision rule. A risk and queue reservation check gates the simulated order intent. The wire format is synthetic. ITCH/OUCH compatibility and host-side replay are later extensions.

## How capture works

1. **Capture.** On each valid RX transfer, store the 64 data bits and the 8-bit `tkeep` mask together. The default array has 256 entries of 72 bits and is intended for simple dual-port block RAM.
2. **Inspect.** A final transfer marked good by the MAC starts readback. The RTL scans one byte lane per clock, copies bytes marked valid by the saved mask, and zeros the unused lanes in the internal 64-bit `DOUT` word.
3. **Rearm.** The final lane of the final stored word completes inspection. The FSM returns to capture and clears the addresses and entry count on that clock edge. The RX interface has no backpressure, so transfers that arrive during inspection are skipped.

The current readback is internal to the RTL. A readout interface and explicit handling for bad frames, buffer overflow, and frames that overlap rearm are the next pieces of capture logic.

## Verification

Directed Icarus Verilog simulations checked complete words, partial final words, and successive captures after one reset. Tests exercised receive traffic both during inspection and on its final clock edge. With `tkeep = 8'h07`, readback kept the three valid bytes and zeroed the other five lanes. These checks used a standalone simulation harness. The checked-in Makefile runs the decoder and FIFO suites.

Run the Icarus Verilog compile check from the repository root.

```sh
iverilog -g2012 -Wall -tnull -s packet_capture rtl/packet_capture.sv
```

The existing test targets use GNU Make, Python, cocotb, and Verilator.

```sh
make test          # Decoder and FIFO
make test-decoder  # Decoder only
make test-fifo     # FIFO only
```

## Next milestones

1. **Finish the capture interface.** Expose a completed readback word and its valid-byte count. Qualify frame completion with `tvalid` and add directed cases for bad frames, a full buffer, and a frame that starts during inspection.
2. **Bring up RX on the VCU118.** Configure the AMD Ethernet IP and QSFP1 lane, constrain the clocks and pins, check the memory mapping and timing in Vivado, and compare a known frame from an external sender against ILA readback.
3. **Add TX test traffic.** Build a known-frame generator and verify TX-to-RX loopback before testing the external link in both directions.
4. **Connect the market data path.** Parse Ethernet/IPv4/UDP, feed validated payloads to the decoder, and add quote state and risk checks. Measure throughput and latency once the integrated datapath is running on hardware.

## Repository layout

```text
rtl/          Capture, market data decoder, FIFO, and TX generator placeholder
sim/          Decoder cocotb test and Makefile
sim/fifo/     FIFO test and Makefile
tools/        Python generator for the synthetic quote payload
constraints/ FIFO clock constraint
```

## References

- [AMD PG210 — 10G/25G High Speed Ethernet Subsystem](https://docs.amd.com/r/en-US/pg210-25g-ethernet)
- [AMD UG1224 — VCU118 Evaluation Board User Guide](https://docs.amd.com/v/u/en-US/ug1224-vcu118-eval-bd)
