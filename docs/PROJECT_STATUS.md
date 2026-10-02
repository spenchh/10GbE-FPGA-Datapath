# Project Checkpoint

Updated: 2026-09-30. This is the durable entry point for resumed work.

## Latest Procurement Planning

- Added `docs/BOM.md` and `docs/BOM.csv` for the USD 1,000 hardware budget.
- User owns no FPGA and expects to develop on the existing laptop. Local model
  identification and HP documentation establish a 5 Gb/s USB-C connection, not
  USB4/Thunderbolt; do not recommend a Thunderbolt 10G adapter for that laptop.
- Proposed physical lab: laptop for development, borrowed/refurbished Linux SFF
  PC with a PCIe X520-DA2, passive SFP+ DAC and KR260. Listed-price plan totals
  USD 931.92 including optional spare card and a USD 100 reserve. Not ordered.
- Public specifications/prices were researched September 30. The DAC/card/board
  pairing, board constraints and sustained packet-generation rate remain untested.
- Vivado licensing changed in 2026.1; confirm actual kit entitlement or a supported
  older Standard release, and separately resolve the Ethernet MAC license.
- One KR260 SFP+ link permits two logical feeds at 10G aggregate, not two physical
  10G inputs. The proposed dual-feed/recovery specialization is not implemented.
- Documentation only: no RTL changes, FPGA tests, purchases, commit or push.
- Checks passed: 13 CSV rows parsed, unique item IDs, USD 931.92 total, 16
  Markdown source references resolved, no checked personal identifiers in BOM,
  and `git diff --check`. These are document checks, not hardware validation.
- Next procurement step: check advisor loaner equipment, validate MAC/PCS and
  clock/pin/license choices before non-returnable purchases. Implementation can
  proceed now with the first decoder and cocotb tests described below.

## Implementation Status

- `tools/gen_packet.py`: existing synthetic quote generator, unchanged by the guide integration.
- `rtl/market_data_decoder.sv`: existing interface only; no behavior or simulation result yet.
- `guide/`: interactive roadmap, 37 source annotations, 22 RTL/software work packages,
  132 planned edge-case entries and 11 milestones totaling about 520 planned hours.
- The FPGA design, post-route timing and hardware performance remain unverified.

## Guide Integration (2026-09-21)

The guide was integrated into this repository on 2026-09-21. It uses standalone
local development and production commands. Private hosting registration,
dependencies and generated build output are excluded from Git.

Guide tests (8), type checks, authored-source lint and the standalone production
build passed on 2026-09-21. Dependency audit reports zero known vulnerabilities.
Browser smoke checks passed for all eight tabs, module/source search, packet
bounds, reset behavior, saved progress and assets. All eight views fit the tested
390px mobile viewport after fixing a table/grid overflow. No browser page errors
were observed. The compact result is committed in
`guide/research/browser-smoke-2026-09-21.json`; local screenshots are under ignored
`guide/work/browser-smoke/`. Full evidence boundaries are in
`guide/research/VALIDATION.md`.

## Resume Here

1. Read `guide/research/VALIDATION.md`, inspect Git status and use this repository
   as the canonical project. Preserve newer work if this note is stale.
2. Confirm the expected branch/remote before committing or pushing further changes.
3. Start the first FPGA block: write `docs/protocol_v1.md`, then implement
   `rtl/market_data_decoder.sv` and a cocotb known-vector test.

For the first decoder: inputs are `clk`, synchronous active-low `rst_n`,
`packet_valid`, and `packet_in[247:0]`. Outputs are the eight fields,
`decoded_valid` and a proposed `decode_error` flag. Define reset/idle/accept/reject
behavior explicitly. Type=1, bid<=ask and nonzero sizes are the proposed synthetic
snapshot policy. Consecutive accepted packets may keep valid high. Sample the
registered result after the accepting edge settles in simulation.

## Major Design Gates

- A complete frame must pass integrity checks before durable state or order effects.
- One KR260 SFP+ port is the candidate full-duplex 10G link. Exact pins, clocks,
  board availability and MAC/PCS licensing still need verification.
- The 31-byte payload is synthetic, not Nasdaq ITCH.
- Finite buffers, sequence gaps, state freshness, pending-order exposure and
  feedback races need explicit behavior and tests.
- Portable cocotb/Verilator tests and four-state/vendor-model tests are separate lanes.
- Guide research source dates remain 2026-09-07; the separate BOM was refreshed
  2026-09-30. Recheck changing facts when acting on them.

## Run the Guide

From the repository root: `cd guide`, `npm ci`, `npm run dev`. Open the printed
localhost URL in a browser and keep the terminal running. Full commands are in
`guide/README.md`. Browser checklist progress is device-local; use this checkpoint
for durable project status that belongs in Git.
