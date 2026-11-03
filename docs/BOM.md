# VCU118 Market-Data Datapath Bill of Materials

Updated: 2026-11-03. Target board: AMD VCU118, kit EK-U1-VCU118-G.

This is an equipment and software requirements list. The initial network setup is
10GbE, with a separate 100GbE extension below. Board access, the exact cable/NIC
combination, and the Ethernet implementation still need confirmation.

## Hardware

| Item | Quantity | Specification / purpose |
| --- | ---: | --- |
| VCU118 evaluation board | 1 | AMD EK-U1-VCU118-G, Virtex UltraScale+ XCVU9P platform. Record board revision and exact device marking. |
| Board power and cooling | 1 set | Correct VCU118 kit supply and cooling assembly. The quick-start guide shows a 180 W supply. Verify the actual kit contents and board-specific connector. |
| Development computer | 1 | Existing laptop for RTL, Python tests and small simulations. Use a lab build machine if VU9P implementation exceeds local resources. |
| Linux traffic-generator PC | 1 | Native Linux desktop/server with an appropriate PCIe slot, NIC bracket clearance and airflow. The earlier Dell OptiPlex 7060 SFF is a 10G candidate, not a verified 100G replay host. |
| 10G SFP+ NIC | 1 | Intel X520-DA2 or another supported 10GbE NIC. Confirm exact OEM version, driver and cable acceptance. |
| 10G breakout cable | 1 | Short QSFP+ to 4x10G SFP+ DAC. QSFP end connects to a VCU118 cage; one SFP+ leg connects to the host NIC. Verify the selected FPGA lane and both endpoint requirements. |
| USB data cables | 2 | Micro-USB cables for the VCU118's separate USB JTAG and USB UART connections. Inventory the kit before obtaining duplicates. |
| Management Ethernet connection | 1 | Existing LAN/direct link for laptop-to-test-PC SSH and result transfer. The VCU118 RJ45 port is a separate 1G interface. |
| Bench support and ESD supplies | 1 set | Nonconductive support with cooling unobstructed. |
| Linux installer media | As needed | Reuse suitable USB media. |
| Initial PC setup peripherals | As needed | Monitor, keyboard, mouse and display cable. |
| QSFP loopback module | Optional | Useful for local bring-up if supplied with the kit. It does not replace the cable to the host. |

[AMD's product page][vcu-kit] identifies the kit. [UG1224][vcu-guide] documents the
board's FPGA, GTY connections, clocks and interfaces. The [quick-start guide][vcu-quick]
shows the power and debug accessories. Inventory borrowed or secondhand equipment.

The former KR260 boot-card/card-reader and single-SFP+ assumptions no longer apply.
The VCU118 system-controller SoC is separate from the XCVU9P datapath FPGA. Its microSD
interface does not make a card or board Linux image necessary for the initial RTL/JTAG demo.

## 10GbE Connections

1. Connect the development computer to VCU118 USB JTAG for programming and USB UART for the chosen debug/control design.
2. Connect the development computer to the Linux test PC through the existing LAN or a direct management Ethernet link.
3. Install the 10G SFP+ NIC in the test PC.
4. Connect one SFP+ breakout leg to the NIC and the QSFP+ end to the selected VCU118 cage.
5. Configure the corresponding GTY lane, reference clock and MAC/PCS for 10GbE. Leave unused breakout legs disconnected.
6. Power and cool the board using its correct kit hardware.

Design Gateway documents a [VCU118 10G breakout connection][vcu-10g]. This supports the
connection approach, but does not verify our selected cable, NIC or custom RTL.

The link is full duplex, so one selected 10G lane can carry market data to the FPGA
and simulated responses back to the host. A breakout cable exposes separate lanes.
It does not convert an active 100G Ethernet interface into 10G.

The laptop-to-PC connection carries SSH/control/results, not the high-rate packet stream.
A 10G switch and a PCIe connection between the VCU118 and host are not required for this
direct Ethernet setup. The on-board USB JTAG interface avoids a separate programming pod.

## Compatibility and Bring-Up

- **Board identity:** record revision, device marking and matching board files/schematic. Select the exact installed part in Vivado.
- **GTY lane and reference clock:** audit the selected QSFP cage, lane, clock source, reset and module-control pins against UG1224 and the chosen MAC/PCS example. A QSFP cage alone does not establish every operating mode.
- **Breakout cable:** match the labeled leg to the FPGA lane selected by constraints. Confirm NIC-end coding/cable acceptance and any module power requirements. See [Intel X520 guidance][intel].
- **Test host:** verify slot width, bracket and airflow. The original OptiPlex 7060 SFF candidate reserves its x16 slot for the NIC. Check the actual machine before adopting it.
- **Build computer:** use the selected Vivado release's memory guidance and measured build usage for VU9P work. Use university compute if needed.
- **Programming and link tests:** run board self-test, verify JTAG programming and clock/reset behavior, then build a minimal MAC/PCS link before integrating the market-data pipeline.

## Software and IP Requirements

| Tool or dependency | Role | Setup requirement |
| --- | --- | --- |
| SystemVerilog and editor | RTL, assertions and interfaces | Use existing editor |
| Python, venv, pytest | Packet codec, reference models, scenario generation and scoreboards | Open-source tooling; pin dependencies |
| cocotb | Drive RTL and check cycle-by-cycle results from Python | Open source; select a released version |
| Verilator and C++ compiler | Fast portable RTL simulation and lint | Open source; pin a supported cocotb/Verilator pair |
| cocotbext-axi / cocotbext-eth | Bus and Ethernet verification models when relevant | Open source; audit licenses and versions |
| GTKWave or Surfer | Inspect simulation waveforms | Open source |
| Vivado, Tcl, XDC, hardware manager/ILA | Synthesis, constraints, implementation, timing and board debug | Version/device entitlement must be confirmed |
| Four-state simulator lane | Reset/X behavior and vendor primitive models | Vivado xsim or institution-provided simulator; separate from portable Verilator tests |
| GCC/Clang, CMake/Make, C++ | Native Linux packet replay, mock venue and capture utilities | Open source |
| Linux, SSH, Git | Test host, reproducible scripts and version control | Use a supported Linux distribution |
| Wireshark/tshark, tcpdump/libpcap, ethtool | Packet inspection, capture and NIC configuration | Open source; disable/record offloads where test correctness requires it |
| DPDK or another supported packet-I/O backend, later | Higher-rate replay if ordinary sockets cannot supply the required load | Optional integration work; verify NIC/driver support and measured rate |
| VCU118 controller utilities and custom UART host tools | Board clock setup, configuration and telemetry | Use VCU118 documentation. A KR260 Linux image is not applicable to the VU9P datapath. |
| UVM, optional | Additional SystemVerilog verification methodology | Not required for this baseline; use a verified simulator and university license if necessary |
| Market-data fixtures | Synthetic packets and fault scenarios first | Use synthetic fixtures first; review rights before adding historical data |

The [cocotb simulator support page][cocotb] currently lists Verilator 5.036+.
Because the stable URL returned development-version documentation, confirm the
requirements for the exact released cocotb version chosen; do not install an
arbitrary distribution package and assume compatibility.

### Vivado and Ethernet Entitlements

- Confirm a Vivado release and entitlement that can synthesize, implement and generate bitstreams for the exact XCVU9P device.
- The historical VCU118 quick-start guide describes a node-locked, device-locked Design Edition voucher. A borrowed or used board does not establish an unused or transferable voucher. Verify the actual lab/kit license and permitted tool version.
- AMD describes changed licensing tiers starting in 2026.1 on its [Vivado page][vivado]. Check current entitlement rather than assuming the historical voucher covers a newer release.
- A device/tool entitlement does not establish Ethernet MAC/IP rights. Validate the chosen 10G MAC/PCS, and separately validate any 100G implementation. [PG210][ethernet-license] covers the 10G/25G subsystem.
- The earlier [verilog-ethernet][open-mac] candidate needs version/license review and a VCU118-specific port. Reuse infrastructure while retaining the intended custom parser, decoder and research logic.

## Optional 100GbE Extension

The VCU118 has two QSFP cages with four GTY lanes each. Moving from the initial
single-lane 10G design to 100GbE requires a separate core and system configuration.

| Requirement | Candidate / verification |
| --- | --- |
| 100G FPGA MAC/PCS | VU9P-compatible implementation with confirmed entitlement, reference clocks, lane mapping, FEC, reset sequencing and user-stream interface. |
| 100GbE QSFP28 host NIC | NVIDIA/Mellanox ConnectX-4 MCX455A-ECAT is one documented candidate. Verify exact SKU, Ethernet mode, firmware, driver and cooling. The baseline X520 is 10G only. |
| 100G cable or optics | Compatible QSFP28-to-QSFP28 DAC, or matched optical modules and fiber. The baseline 4x10G breakout connection is not the 100G cable. |
| Suitable replay host | Validate PCIe bandwidth, memory bandwidth, CPU and actual packet rate. The MCX455A-ECAT is documented with PCIe Gen3 x16. Do not assume the baseline PC can generate/capture the target workload. |
| Wider streaming datapath | Derive width, clock and byte-valid/message-boundary handling from the selected 100G core. Do not assume the initial 32-bit simulation interface is the final MAC interface. |

See the [NVIDIA manufacturer manual][cx4] for the MCX455A-ECAT. ConnectX-4 Lx is not
an interchangeable 100G candidate. Treat host/NIC/cable/core selection as one integration task.

## Measurement and Research Scope

The application architecture remains Ethernet -> IPv4 -> UDP -> market-data decoding ->
sequence/state handling -> decision -> risk checks -> simulated order transmission.
Python and C++ provide test/control functions. This BOM update does not implement or
verify the pipeline.

Use the VCU118's additional lanes/cage only after instantiating and validating the
corresponding logic and external connections. One working lane does not establish
multi-link redundancy or 100G operation.

Benchmark offered packet rate, capture loss, driver settings and CPU limits. A NIC's
rated link speed does not prove minimum-frame line-rate replay. Use simulation or
appropriate lab equipment for malformed-FCS testing that the NIC cannot generate.

Internal timestamps/counters and ILA establish defined fabric-cycle timing. Calibrated
wire-to-wire results require an appropriate external measurement setup, defined reference
points and recorded uncertainty.

## Next Steps

1. Confirm access to the VCU118 and inventory power, cooling, USB cables, loopback accessories and tool entitlement.
2. Agree on the initial link rate, MAC/PCS implementation and user-stream interface.
3. Continue decoder and streaming-front-end verification on the existing development computer.
4. Prove board programming and a minimal Ethernet link.
5. Integrate the parser/decoder and add per-stage timing instrumentation.
6. Validate the optional 100G equipment and configuration when that extension is selected.

## Sources

[vcu-kit]: https://www.amd.com/en/products/adaptive-socs-and-fpgas/evaluation-boards/vcu118.html
[vcu-guide]: https://docs.amd.com/api/khub/documents/Uoc4S9pQd1uve6kiGiG2kA/content
[vcu-quick]: https://docs.amd.com/api/khub/documents/HoK4yan7ctgxSGOLW0OVng/content
[vcu-10g]: https://dgway.com/products/IP/TOE10G-IP/dg_toeudp10gip_fpgasetup_xilinx/dg_toeudp10gip_fpgasetup_xilinx.htm
[intel]: https://www.intel.com/content/www/us/en/support/articles/000005528/ethernet-products/500-series-network-adapters-up-to-10gbe.html
[vivado]: https://www.amd.com/en/products/software/adaptive-socs-and-fpgas/vivado.html
[ethernet-license]: https://docs.amd.com/r/5.0-English/pg210-25g-ethernet/Ordering-Information
[open-mac]: https://github.com/alexforencich/verilog-ethernet
[cocotb]: https://docs.cocotb.org/en/stable/simulator_support.html
[cx4]: https://networking-docs.nvidia.com/connectx4vpihw/introduction
