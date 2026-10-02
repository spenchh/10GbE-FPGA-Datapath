# 10GbE FPGA Lab Bill of Materials

Researched: 2026-09-30. Budget: USD 1,000. No purchases made.

This is a procurement plan, not a tested hardware configuration. Listed prices
are public-page snapshots, not delivered quotes. Check stock, shipping, tax,
return conditions and the compatibility gates below before ordering.

## Recommendation

Keep the existing laptop for development. Use a refurbished Linux desktop with
a PCIe SFP+ network card for traffic generation and capture, connected directly
to a Kria KR260. Borrow the desktop from a university lab if possible.

The locally identified laptop is an HP Victus 15-fb3xxx. HP documents the series'
USB-C connection as USB 3.2 Gen 1, 5 Gb/s, including Ryzen AI variants. It is not
a USB4/Thunderbolt port. Do not buy a Thunderbolt/USB4 10G adapter for this machine.
DisplayPort and USB Power Delivery support do not imply Thunderbolt support.
See [HP specifications][hp-ports].

The reported 16 GB RAM is sufficient to start small simulations, but full Vivado
build memory use is design-dependent. Start with the existing machine, monitor
memory, and use university compute if necessary. Approximately 465 GB free storage
was reported; install only needed device families and manage waveform/build files.
Neither a GPU upgrade nor a new development laptop is part of this BOM.

## Connections

```text
Development laptop -- USB debug/UART --> KR260
Development laptop -- 1G Ethernet ----> Linux test PC onboard Ethernet
                                       |
                                  PCIe X520-DA2
                                       |
                                10G SFP+ DAC
                                       |
                                KR260 SFP+ port
```

The 10G link is full duplex: the PC transmits market-data packets and receives
the FPGA's simulated order responses on the same cable. The laptop-to-PC link
is for SSH, configuration and results, not the high-rate packet stream.
Wi-Fi can remain the laptop's Internet connection. No 10G switch is required.
The kit's included RJ45 cable can serve the laptop-to-PC connection; USB UART
can handle initial board management. Additional shared-LAN cabling is optional.

## Purchase List

Quantities are one each. CSV companion: [BOM.csv](BOM.csv).

| Item | Exact candidate or specification | USD allowance | Price basis / purpose |
| --- | --- | ---: | --- |
| FPGA starter kit | AMD **SK-KR260-G** complete kit | 431.02 | [DigiKey listing][kr260-dk]; programmable logic, Arm control processor, one 10G SFP+ port |
| Traffic-generator PC | Refurbished **Dell OptiPlex 7060 SFF**, i5-8500, 16 GB RAM, 256 GB SSD, PSU/power cord included | 299.00 | [Listing example][pc-listing]; native Linux replay/capture host, not an FPGA |
| 10G PCIe NIC | Refurbished **Intel X520-DA2**, low-profile bracket | 29.00 | [Stallard listing][nic-listing]; confirm exact OEM revision and return policy |
| Direct-attach cable | **10Gtek CAB-10GSFP-P1M-24**, passive SFP+ to SFP+, 1 m, Intel-compatible option | 20.90 | [Vendor listing][dac]; pair compatibility still requires verification |
| USB card reader | USB-A microSD/SD reader | 12.00 | Planning estimate; skip if already available |
| Linux installer media | USB flash drive, 16 GB or larger | 10.00 | Planning estimate; can reuse an existing drive after backing it up |
| Bench accessories | Nonconductive board support and ESD handling supplies | 20.00 | Planning estimate; keep fans unobstructed |
| Spare boot card, optional | Reputable 32 GB microSDHC | 10.00 | Planning estimate; the kit already includes a card |
| **Parts subtotal** | Includes optional spare card | **831.92** | Excludes tax and shipping |
| Tax/shipping/price reserve | Budget allowance, not a quoted charge | 100.00 | Recalculate using actual checkout totals |
| **Planned total** | | **931.92** | **68.08 remains** below the budget |

The PC listing is a price example, not an endorsement of that marketplace seller.
Inspect condition, seller history, warranty, accessories and actual chassis photos.
Do not pay for an unwanted Windows upgrade; this test host will run Linux.
Borrowing an equivalent PC reduces the planned total to **632.92** using the same
reserve. A cheaper local refurbished PC is useful only if its slot, cooling and
complete configuration are suitable.

AMD lists a **349.00 MSRP** and a **26-week lead time** on its [product page][kr260].
DigiKey's US page returned **431.02** and **192 in stock**, with a
non-cancelable/non-returnable notice, during this check. The BOM uses the higher
actual listing rather than assuming MSRP is available. Stock and prices can change;
confirm before purchase. No stock has been reserved.

## Already Included or Borrowed

[AMD's box inventory][box] lists the K26 SOM/carrier, fan/heatsink, power supply
and adapters, RJ45 Ethernet cable, USB-A-to-micro-B cable, and microSD with adapter.
Do not buy another PSU, fan, boot card or debug cable by default. The microSD-to-SD
adapter is not a USB reader. Use the board's integrated USB debug connection;
an external JTAG programming pod is not an initial requirement.

Borrow a monitor with the correct cable/adapter, USB keyboard and mouse for initial
Linux installation and recovery. A laptop's HDMI port is normally an output, not
a monitor input. Run the PC headlessly over SSH afterward. If these cannot be
borrowed, include their real cost before ordering: they are not priced in the total.
Also borrow a screwdriver for the NIC installation. Confirm the PC power cord and
all board kit accessories are actually included, especially with secondhand units.

## Compatibility Gates Before Purchase

1. **PC chassis and slot:** choose the SFF, not the similarly named Micro. Dell
   specifies a PCIe 3.0 x16 slot for the [7060 SFF][pc-slots]. Reserve that slot
   for the NIC, use integrated graphics, verify clearance and the low-profile
   bracket. The X520 needs adequate chassis airflow. This is a candidate pairing,
   not a claim that this exact refurbished machine has been tested.
2. **NIC and cable:** confirm the actual card's OEM identity, Linux driver support,
   EEPROM/firmware condition and DAC acceptance with the seller. Intel documents
   required cable standards and identifier in its [X520 compatibility note][intel].
   Buy a returnable short passive DAC matching those requirements. Intel-compatible
   coding alone does not prove the entire FPGA link will work.
3. **FPGA physical interface:** before a non-returnable board order, audit KR260
   schematic revision, SFP+ transceiver routing, reference clock, power/control
   signals and constraints against the selected 10G MAC/PCS design. Generate and
   build a minimal link design. This board-specific port remains unverified.
4. **License path:** establish a usable Vivado/device license and Ethernet MAC
   implementation, as described below. A tool license is not automatically a MAC
   license. Do not rely on an expiring evaluation core for the final demonstration.
5. **Delivered total:** substitute the actual PC/NIC/cable and tax/shipping quotes.
   If the total exceeds 1,000, borrow the PC or defer purchase. Do not silently
   drop needed accessories or assume additional funds.

AMD's tested peripheral list names the **10Gtek AXS85-192-M3 10GBASE-SR** module
for its 10GigE Vision application. It does not verify our proposed DAC and RTL.
See [supported peripherals][peripherals]. If using optics instead of a DAC, buy
one board-side SR module, an Intel-validated host-side SR module, and a duplex
LC-to-LC OM3 multimode cable. Rebudget this alternative; do not buy both paths.
Intel warns of restrictions on third-party optics. Do not treat the board-side
module as automatically approved for the Intel card.

Avoid an RJ45 10GBASE-T SFP+ module as the default board connection: check module
power explicitly against the KR260's **3.3 V, 600 mA** SFP+ allowance in
[AMD's power budget][power]. A passive DAC needs no separate optical modules.

## Software and IP Bill of Materials

The baseline assumes no paid software purchases. These are requirements to set
up and validate, not a statement that everything is installed or passing today.

| Tool or dependency | Role | Cost / decision |
| --- | --- | --- |
| SystemVerilog and editor | RTL, assertions and interfaces | No language license fee; use existing editor |
| Python, venv, pytest | Packet codec, reference models, scenario generation and scoreboards | Open-source tooling; pin dependencies |
| cocotb | Drive RTL and check cycle-by-cycle results from Python | Open source; select a released version |
| Verilator and C++ compiler | Fast portable RTL simulation and lint | Open source; pin a supported cocotb/Verilator pair |
| cocotbext-axi / cocotbext-eth | Bus and Ethernet verification models when relevant | Open source; audit licenses and versions |
| GTKWave or Surfer | Inspect simulation waveforms | Open source |
| Vivado, Tcl, XDC, hardware manager/ILA | Synthesis, constraints, implementation, timing and board debug | Version/device entitlement must be confirmed |
| Four-state simulator lane | Reset/X behavior and vendor primitive models | Vivado xsim or institution-provided simulator; separate from portable Verilator tests |
| GCC/Clang, CMake/Make, C++ | Native Linux packet replay, mock venue and capture utilities | Open source |
| Linux, SSH, Git | Test host, reproducible scripts and version control | No paid OS required for the test PC |
| Wireshark/tshark, tcpdump/libpcap, ethtool | Packet inspection, capture and NIC configuration | Open source; disable/record offloads where test correctness requires it |
| DPDK or another supported packet-I/O backend, later | Higher-rate replay if ordinary sockets cannot supply the required load | Optional integration work; verify NIC/driver support and measured rate |
| Vitis / board Linux image, later | Arm-side configuration and telemetry | Add only when integrating the SoC control plane; match hardware/tool versions |
| UVM, optional | Additional SystemVerilog verification methodology | Not required for this baseline; use a verified simulator and university license if necessary |
| Market-data fixtures | Synthetic packets and fault scenarios first | No live exchange subscription required; review rights before adding historical data |

The [cocotb simulator support page][cocotb] currently lists Verilator 5.036+.
Because the stable URL returned development-version documentation, confirm the
requirements for the exact released cocotb version chosen; do not install an
arbitrary distribution package and assume compatibility.

### Vivado and Ethernet License Decision

- **Older supported route:** AMD's [Vivado 2025.1 device table][vivado-devices]
  includes Kria in Standard Edition. The [licensing FAQ][licenses] says Standard
  2025.2 and earlier does not require a FLEX license. Validate the chosen board
  files, IP configuration and host OS against a pinned release before adopting it.
- **2026.1 and newer:** the licensing model changed to tiers. AMD says Kria kits
  receive a CORE voucher starting with 2026.1. Confirm the entitlement in the
  actual kit, subscription duration and project-long access; do not assume an
  older-stock box includes a new voucher or every feature is in free BASIC.
- **Ethernet IP:** [PG210][ethernet-license] distinguishes no-purchase BASE-R
  PCS/PMA from separately licensed MAC configurations. The 931.92 plan assumes
  a suitable open-source MAC or confirmed institution-provided rights. A commercial
  MAC license is **not included** in that number and could invalidate the budget.
- **Open-source candidate:** [verilog-ethernet][open-mac] supplies MIT-licensed
  10G MAC components, but is deprecated. An audited, pinned version is a candidate,
  not a turnkey KR260 solution. Its successor has separate licensing to review.
  Reuse the MAC/PHY infrastructure without replacing the intended custom
  IPv4/UDP parser, decoder, feed handling and risk RTL with an entire copied stack.

## What This Lab Can and Cannot Establish

This keeps the original architecture: Ethernet -> IPv4 -> UDP -> market data ->
sequence/state handling -> decision -> risk checks -> simulated order transmission.
Python and C++ remain test and control components, not a replacement for FPGA RTL.

The KR260 has one SFP+ port. Two logical A/B feeds can share it, with aggregate
ingress limited to 10 Gb/s. This supports duplicate/gap/reordering experiments,
but **not two independent physical 10G inputs or independent-link failover**.
A dual-port NIC in the PC does not change the FPGA's port count. Borrow a suitable
multi-port FPGA platform later if physical redundancy becomes a research requirement.

Buying a 10G NIC does not prove minimum-frame line-rate replay. Benchmark offered
packets/s, capture loss, driver settings and CPU limits before drawing conclusions
about the FPGA. Large-packet TCP throughput is not a tiny-packet UDP test. Native
Linux on the test PC avoids making Windows/WSL raw-NIC access an unverified premise.
Ordinary NICs may regenerate FCS and apply offloads: use simulation or suitable lab
equipment for malformed-FCS testing that the NIC cannot generate.

Internal counters and ILA can establish precisely defined fabric-cycle timing.
They cannot by themselves establish calibrated wire-to-wire latency. Borrow a
hardware traffic generator, timestamp-capable measurement setup or appropriate
lab instruments for that claim; no such equipment is included in the budget.
Record clock domains, timing reference points and measurement uncertainty.

## Purchase Timing

1. **Now, 0 dollars:** define the 31-byte synthetic protocol behavior; implement
   the registered decoder; run a self-checking cocotb test and lint. Learn on the
   existing laptop. Do not wait for a board to start.
2. **Before ordering the FPGA:** resolve the license path and board clock/pin/IP
   audit, and ask the advisor about loaner boards, PCs and measurement equipment.
3. **Board bring-up:** purchase the kit and reader as needed; prove programming,
   reset and basic debug before adding the full trading pipeline.
4. **Physical network testing:** obtain the PC/NIC/cable near the link bring-up
   milestone so their return windows do not expire during months of RTL learning.
5. **Later, evidence-driven upgrades:** additional capture storage, compatible
   RAM or lab equipment only when measured needs justify them. No 10G switch,
   external JTAG pod, oscilloscope purchase, second FPGA, live trading account,
   motors or sensors are required to start this design.

## Sources

[hp-ports]: https://support.hp.com/gb-en/document/ish_11678529-11678592-16
[kr260]: https://www.amd.com/en/products/system-on-modules/kria/k26/kr260-robotics-starter-kit.html
[kr260-dk]: https://www.digikey.com/en/products/detail/amd/SK-KR260-G/16521660
[box]: https://docs.amd.com/r/en-US/ug1092-kr260-starter-kit/What-s-in-the-Box
[pc-listing]: https://www.target.com/p/-/A-1004161493
[pc-slots]: https://www.dell.com/support/manuals/en-us/optiplex-7060-sff/opti_7060_sff_setup_specs_manual/system-board-connectors?guid=guid-a828ebb5-0563-42e5-826a-ed9ee262d30b&lang=en-us
[nic-listing]: https://www.stikc.com/products/intel-x520-da2-dual-port-10gb-sfp-cna-low-profile
[dac]: https://www.sfpcables.com/SFP-Cable-CAB-10GSFP-P1M-24?source=10gtekProductPage
[intel]: https://www.intel.com/content/www/us/en/support/articles/000005528/ethernet-products/500-series-network-adapters-up-to-10gbe.html
[peripherals]: https://docs.amd.com/r/en-US/ug1092-kr260-starter-kit/Supported-Peripherals
[power]: https://docs.amd.com/r/en-US/ug1092-kr260-starter-kit/Powering-the-Starter-Kit-and-Power-Budgets
[vivado-devices]: https://docs.amd.com/r/2025.1-English/ug973-vivado-release-notes-install-license/Supported-Devices
[licenses]: https://www.amd.com/en/products/software/adaptive-socs-and-fpgas/licensing-faq.html
[ethernet-license]: https://docs.amd.com/r/5.0-English/pg210-25g-ethernet/Ordering-Information
[open-mac]: https://github.com/alexforencich/verilog-ethernet
[cocotb]: https://docs.cocotb.org/en/stable/simulator_support.html
