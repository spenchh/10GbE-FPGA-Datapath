# Project Handoff

This is a temporary, sanitized handoff for continuing the project in another
chat. It contains project and learning context but no raw meeting transcript,
device identifiers, credentials, or unpublished performance claims.

## Instructions for the Next Chat

Continue this repository as the source of truth. Before changing anything:

1. Read `AGENTS.md`, this file, `docs/PROJECT_STATUS.md`, `ReadMe.md`,
   `tools/gen_packet.py`, `rtl/market_data_decoder.sv`, and
   `guide/research/VALIDATION.md`.
2. Inspect the current working tree and preserve existing changes.
3. Distinguish planned architecture from implemented and verified behavior.
4. Keep the user in control of implementation according to the learning contract.

## User and Objective

The user is a computer-engineering student pursuing FPGA/RTL engineering. The
primary target is FPGA work at HFT firms such as HRT, Optiver, and IMC, but this
project must also be strong for FPGA, networking, ASIC, semiconductor, big-tech,
aerospace, and defense roles.

The user wants one difficult, year-scale flagship project demonstrating:

`specification -> RTL -> self-checking verification -> synthesis/implementation
-> timing/CDC evidence -> hardware integration -> measured behavior -> demo`

This is not an isolated Verilog exercise, a software-only trading simulator, or a
parser that accepts already-decoded fields. It is intended to become an end-to-end
FPGA packet-processing and control system using market data as its workload.

No project guarantees an HFT offer. The completed work must remain useful for
broader digital-design and networking roles.

## Public Project Identity

Project title:

**10GbE Low-Latency Packet Processing Datapath**

Repository:

`10GbE-Line-Rate-Packet-Datapath`

The broad title is intentional. HFT reviewers can identify the trading relevance
from the market-data, state, decision, risk, and latency details. Other hardware
reviewers first see 10GbE networking, pipelined RTL, protocols, verification,
timing, and system integration.

Do not call it a SmartNIC or DPU unless it eventually includes the host offload,
PCIe/DMA, and control behavior needed to support that description.

## Intended Skills and Deliverables

- Pipelined SystemVerilog RTL with explicit cycle-level contracts.
- 10GbE Ethernet, IPv4, and UDP receive and transmit processing.
- Stateful market-data decoding with bounded symbol state.
- Sequence, session, freshness, integrity, and recovery handling.
- Integer-scaled and fixed-point decision logic.
- Hardware-enforced risk admission and bounded queues.
- Simulated order intents and venue feedback; never real-money trading.
- Python reference models, fixtures, and cocotb self-checking tests.
- Verilator for portable simulation plus a separate four-state/vendor lane.
- C++ codecs, replay, simulated venue, control/status, and benchmarks.
- Tcl/XDC automation, constraints, synthesis, place/route, timing, DRC, and CDC.
- FPGA bring-up, ILA/counter evidence, calibrated traffic, and honest metrics.
- A controlled research comparison or advanced extension after the core works.

Python and C++ are essential system components, but they must not replace the
latency-critical RTL contribution.

## Intended Architecture

```text
C++/Python replay and control host
                |
          10G SFP+ MAC/PCS
                |
       Ethernet frame validation
                |
       IPv4 validation and filtering
                |
        UDP validation and filtering
                |
  feed/session framing + commit barrier
                |
         market-data decoder
                |
 sequence/freshness/feed-health handling
                |
       bounded per-symbol state
                |
 scaled-integer/fixed-point decision logic
                |
    atomic hardware risk admission
                |
 bounded TX queue + order-intent encoder
                |
       UDP/IPv4/Ethernet transmit
                |
 C++ simulated venue, feedback, and checker
```

Later control-plane components include AXI-Lite configuration, counters, bounded
tracing, a watchdog, and Arm-side software. Control must remain outside the
latency-critical decision path.

A complete frame must pass all relevant integrity checks before causing durable
state or order effects. An early field must not change state if a later length,
checksum, framing, or completeness check invalidates the packet.

The first protocol is synthetic, not Nasdaq ITCH. MoldUDP64 plus a declared ITCH
subset is a possible late extension. Do not claim a complete order book unless
the supported lifecycle, capacity, unsupported-event behavior, and recovery make
that claim true.

## Coffee-Chat Guidance from Gavin

This is a careful summary of a September 2026 coffee chat. The source notes were
machine-generated, so exact wording and speaker attribution may contain errors.
Treat these as observations, not industry-wide statistics.

- Gavin described substantial software work in his FPGA role, including host
  interaction, C/C++, Python verification, cocotb, and Verilator. An approximate
  percentage he mentioned described his experience, not a universal job ratio.
- He sees market-data or UDP parser projects fairly often. After hearing that this
  project extends through networking layers and the larger system, he viewed it
  as more substantial than a parser-only exercise.
- His strongest differentiation suggestion was visible FPGA/software interaction,
  not merely adding protocol names. A later demo should configure a limit, read
  back the applied configuration, inject traffic, inspect results and counters,
  and show safe behavior after host timeout or restart.
- He emphasized combining SystemVerilog, networking, and C++ knowledge and being
  able to discuss hardware tradeoffs rather than only showing code.
- He recommended studying computer architecture, networking, and digital design
  while building, rather than postponing implementation until all reading is done.
- He warned about candidates unable to explain AI-generated work. The conversation
  supported using AI for knowledge and information; it did not require banning AI.
- Reproducible evidence and explainable decisions matter more than feature count.

The response is to complete and prove small components, then make software/hardware
interaction observable. Do not add TCP, PCIe, DMA, FIX, or a full exchange
protocol before the baseline works.

## Differentiation and Research Direction

The user wants genuine technical differentiation without abandoning HFT or the
Ethernet/IPv4/UDP architecture. Do not pivot to a hobby application merely to
sound different.

The leading proposed specialization, not implemented or claimed as novel, is:

**A dual-feed, recovery-aware FPGA trading pipeline with reproducible fault
injection and quantitative comparison of bounded recovery policies.**

Feeds A and B would be redundant copies of one sequenced feed. The system should:

- accept the first complete, valid copy of the next expected update;
- discard an already-applied duplicate from the other feed;
- avoid waiting for B if A already supplied the next valid update;
- use bounded reorder storage and explicit timeout behavior;
- detect gaps, conflicts, impossible transitions, and session changes;
- disarm affected trading when state integrity is unknown;
- re-arm only after a defined replay or resynchronization procedure.

Example: A sends `100, 101, 103` while B sends `100, 102, 103`. The committed
sequence should be `100, 101, 102, 103` exactly once. If neither feed supplies
102, do not silently commit dependent update 103 as though state were complete.

Candidate research question:

> How do bounded reordering and recovery policies affect healthy-path latency,
> sustained throughput, FPGA resource/buffer cost, and time unable to trade after
> packet loss?

Possible comparison: stop-and-resynchronize versus bounded replay recovery using
declared reorder-window sizes and identical traffic and faults. Evidence could
include state and order ledgers, coverage, waveforms, failing seeds, timing and
utilization, latency distributions, recovery duration, and drop counts.

Do not claim world-first novelty or superiority before related-work review and
controlled measurement. The KR260 candidate has one 10G SFP+ port. Two logical
feeds sharing it can exercise arbitration but do not demonstrate independent
physical paths or physical-link failover.

This specialization remains a proposal. Review it with the advisor and add it
only after the one-feed sequence/state baseline works.

## AI Learning Contract

The user does not want AI to build the project for him. AI should help him become
capable of designing, verifying, synthesizing, debugging, and explaining it.

1. Let the user write the RTL, Python tests, and C++ first. Do not silently produce
   complete modules, testbenches, or architecture layers.
2. Ask short reasoning questions when useful: expected output cycle, bit slice,
   handshake, reset priority, signedness, width, state transition, reject policy,
   or tradeoff. Make the user predict behavior before simulation.
3. Explain hardware concretely: registers, combinational paths, clock edges,
   nonblocking assignment timing, widths, valid alignment, and state.
4. When the user is stuck, isolate the smallest blocking concept or bug. Prefer a
   hint, timing table, pseudocode, or small fragment and review his attempt.
5. Give a complete implementation only when the user explicitly overrides this
   learning rule.
6. Ask the user to explain important code in his own words and predict at least
   one test. Optimize for interview understanding, not memorization.
7. Use AI actively for Internet research: find primary specifications and current
   vendor/tool facts, extract relevant sections, link them, and explain impact.
8. Prefer primary exchange specifications, official vendor documentation,
   standards, maintained project documentation, and original research. Label
   inference, anecdote, stale facts, and unverified compatibility.
9. Never invent test output, metrics, synthesis, timing closure, hardware results,
   or ownership. Separate roadmap, simulation, synthesis, implementation, board
   validation, and calibrated external measurement.
10. Keep a learning log: what the user wrote, predicted, misunderstood, fixed,
    and verified. These become interview examples.
11. Save useful work and update `docs/PROJECT_STATUS.md` at meaningful milestones
    and before pausing.

## Current Implementation State

Implemented:

- `tools/gen_packet.py` defines eight unsigned quote fields, validates their
  widths, concatenates a 248-bit MSB-first vector, and prints binary, 62-digit
  hexadecimal, and expected fields.
- The user ran the script successfully after fixing its width calculation.
- The interactive guide and its web checks exist. These validate the guide, not
  the FPGA implementation.
- A hardware BOM was researched locally. No hardware has been purchased.

Not implemented or verified:

- `rtl/market_data_decoder.sv` has only a port declaration and lacks behavior and
  `endmodule`.
- No cocotb FPGA test or selected simulator pairing has run.
- No C++ replay, codec, or simulated venue exists.
- Ethernet/IPv4/UDP RTL, sequence state, quote state, decisions, risk, TX,
  AXI-Lite, tracing, dual-feed recovery, and real protocols are roadmap items.
- No synthesis, place/route, timing closure, CDC review, board programming,
  physical 10GbE link, line-rate result, or latency result is verified.

Do not mistake the guide's 132 planned scenarios for executed tests or its
approximately 520-hour estimate for completed work.

At handoff creation, the local checkout also had uncommitted procurement files
and a status update. Inspect and preserve the live tree rather than assuming every
local file is already on GitHub.

## Packet V1

The first protocol is a 31-byte, 248-bit, unsigned, MSB-first quote snapshot:

| Field | Width | `packet_in` bits | Example |
| --- | ---: | --- | ---: |
| `message_type` | 8 | `[247:240]` | 1 |
| `sequence_number` | 32 | `[239:208]` | 42 |
| `symbol_id` | 16 | `[207:192]` | 7 |
| `bid_price` | 32 | `[191:160]` | 1743100 |
| `ask_price` | 32 | `[159:128]` | 1743300 |
| `bid_size` | 32 | `[127:96]` | 800 |
| `ask_size` | 32 | `[95:64]` | 500 |
| `timestamp` | 64 | `[63:0]` | 123456789 |

Prices use four implied decimal places in this learning protocol. The current
Python script uses binary strings. A later Milestone 1 task refactors it into
byte-oriented pack/unpack helpers, independent fixtures, and a CLI.

Proposed decoder contract, to be reviewed and written by the user before RTL:

- Inputs: `clk`, synchronous active-low `rst_n`, `packet_valid`, and
  `packet_in[247:0]`.
- Outputs: eight registered fields, `decoded_valid`, and new `decode_error`.
- An input presented for an accepting rising edge produces registered outputs
  after that edge, with exact alignment defined by the cycle table.
- Reset clears outputs and flags and wins if asserted with `packet_valid`.
- Idle clears one-cycle flags and holds previously accepted data fields.
- Proposed policy: message type 1, nonzero bid/ask sizes, and
  `bid_price <= ask_price`. Encoding validity and quote policy are separate.
- Rejection asserts `decode_error`, deasserts `decoded_valid`, and preserves prior
  accepted fields.
- Consecutive accepted packets need no bubble; `decoded_valid` may remain high on
  consecutive output cycles.
- Sequence history belongs in a later module. This decoder extracts the number.

These rules are proposed, not implemented. The user should understand and record
the behavior table before writing RTL.

## Exact Step to Resume

The project is at **Milestone 1: One packet, one trustworthy result**, immediately
before the first behavioral RTL block.

Continue in this order:

1. The user writes `docs/protocol_v1.md` with the field map and a cycle table for
   reset, idle, accepted input, rejected input, first input after reset, and two
   consecutive accepted packets.
2. Have the user predict at least five output cycles. Ask whether `decoded_valid`
   needs a low bubble between accepted packets and require a timing explanation.
3. The user implements `rtl/market_data_decoder.sv` with `always_ff`, nonblocking
   assignments, explicit slices, deterministic flags, `decode_error`, and
   `endmodule`.
4. Review one driver per signal, exact slices, reset priority, state semantics,
   and valid/data alignment. Do not replace the implementation silently.
5. Recheck official documentation and select a released compatible Python,
   cocotb, and Verilator combination. None has been verified yet.
6. The user writes tests for an independently hand-checked vector, field boundaries,
   idle, reset, rejection rules, and two distinct consecutive packets. Sample
   registered outputs correctly and add timeouts.
7. Save exact versions, command, output, and waveform. Only then move to the
   64-bit ready/valid packet assembler.

Read packed vectors, clock-edge behavior, nonblocking assignments, synchronous
reset, and cocotb scheduling alongside implementation. Do not postpone Milestone 1
to read every Ethernet or exchange specification.

## Roadmap After Milestone 1

1. Registered decoder and independent cocotb scoreboard.
2. 64-bit ready/valid stream and bounded 31-byte assembler.
3. Bounded quote state, sequence/freshness health, and integer decisions.
4. Atomic risk/exposure accounting and C++ simulated venue.
5. Ethernet/IPv4/UDP validation with integrity-before-effects.
6. KR260 physical link, wrapper, constraints, and control/status.
7. Cross-layer fault regression and four-state/vendor verification.
8. Timing closure, calibrated load, throughput, and latency measurement.
9. Controlled comparison of integrity-preserving receive architectures.
10. One advanced extension: real protocol, networking feature, or focused
    UVM/formal work, not all three by default.
11. Clean rebuild, evidence, hardware demo, and interview preparation.

Add dual-feed recovery only after the one-feed baseline works and after reviewing
the remaining schedule.

## Hardware Context

- Budget: USD 1,000. No FPGA has been purchased.
- Candidate board: AMD Kria KR260 with one 10G SFP+ port.
- The existing laptop can handle initial work, but its USB-C port is 5 Gb/s USB,
  not USB4/Thunderbolt. Do not recommend a Thunderbolt 10G adapter for it.
- Proposed lab: development laptop plus borrowed/refurbished Linux SFF desktop,
  PCIe Intel X520-DA2, passive SFP+ DAC, and KR260.
- Researched planning total: about USD 932 with reserve, or about USD 633 if the
  traffic host is borrowed. Refresh all prices and availability before purchase.
- Resolve exact KR260 clocks/pins, board wrapper, Vivado entitlement, and Ethernet
  MAC/PCS licensing before a non-returnable order. Vivado licensing changed in
  2026.1; a PCS entitlement does not necessarily include the MAC.
- Hardware is unnecessary for the current decoder/cocotb work. Ask the advisor
  about loaners and measurement equipment first.

## Resume Framing

Current evidence-safe entry:

```latex
\project
  {10GbE Low-Latency Packet Processing Datapath}
  {SystemVerilog, Python, Ethernet/IPv4/UDP}
  {August 2026 -- Present}
\begin{itemize}
  \resumeItem{Designed a pipelined 10GbE FPGA architecture targeting a Kria KR260, spanning Ethernet/IPv4/UDP ingestion, stateful packet processing, fixed-point decision logic, and hardware-enforced risk checks}
  \resumeItem{Defined a 248-bit synthetic market-data packet format and developed a Python generator with fixed-width serialization, range validation, and reproducible packet vectors for RTL verification}
\end{itemize}\vspace{-0.8pt}
```

“Designed an architecture” is accurate now. Do not claim implementation on the
KR260, completed cocotb/C++, line rate, timing closure, or latency until evidence
exists. Replace architecture language incrementally with measured results.

## Evidence Boundaries

- Proposed is not implemented.
- Simulated is not synthesized.
- Synthesized is not timing-closed.
- Timing-closed is not board-validated.
- Internal fabric cycles are not calibrated wire-to-wire latency.
- A generated report is not a passing report until criteria are checked.
- Some transmitted traffic is not proof of minimum-frame 10GbE line rate.
- A synthetic quote is not Nasdaq ITCH or a complete order book.
- One SFP+ port is not redundant dual-link hardware.
- Guide tests are not FPGA tests.
- Resume metrics require committed artifacts and reproducible logs.

The project should stand out through complete contracts, difficult edge cases,
reproducible faults, measured tradeoffs, software/hardware interaction, and the
user's ability to explain every decision—not inflated naming or copied RTL.

## Suggested First Prompt

```text
Read HANDOFF.md, AGENTS.md, docs/PROJECT_STATUS.md, ReadMe.md,
tools/gen_packet.py, rtl/market_data_decoder.sv, and
guide/research/VALIDATION.md. Inspect the working tree and preserve changes.

Continue my 10GbE Low-Latency Packet Processing Datapath project. Follow the AI
learning contract in HANDOFF.md: I write the RTL, tests, and C++ first; guide me
with questions, explanations, targeted hints, debugging, and review. Only give a
complete implementation if I explicitly override that rule. Use Internet research
to find and summarize relevant primary documentation.

I am at Milestone 1. Help me write docs/protocol_v1.md and reason through the
decoder cycle table. Do not jump ahead to Ethernet RTL, dual-feed recovery, or
hardware purchasing. Separate planned work from verified evidence.
```

After the new chat reads this file, it can be deleted from the current branch.
Ordinary deletion does not erase it from Git history.
