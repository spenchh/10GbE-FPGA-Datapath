# 10GbE Line-Rate Packet Processing Datapath

An FPGA networking project using market-data processing as its workload.
The intended system receives UDP quote updates, maintains bounded symbol state,
evaluates an integer-scaled rule, enforces hardware risk limits, and returns
simulated order intents. The long-term target is a measured 10GbE implementation.


## Planned Data Path

```text
10GbE Ethernet / IPv4 / UDP
  -> tentative packet parsing
  -> complete-frame integrity validation
  -> sequence health and bounded quote state
  -> integer-scaled decision logic
  -> atomic risk and output-queue reservation
  -> simulated order intent / venue feedback
```

Python/cocotb reference models and tests, C++ replay/control software, and
Tcl/XDC build and timing checks support the RTL. The first packet format is
synthetic; Nasdaq ITCH/OUCH compatibility is a possible later extension.


## Repository Layout

```text
rtl/       FPGA RTL
tools/     Python packet generator and future host-side utilities
sim/       Planned RTL simulation and verification
docs/      Project checkpoint and design documents
```
