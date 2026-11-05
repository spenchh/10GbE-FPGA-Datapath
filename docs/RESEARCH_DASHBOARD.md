# VCU118 Research Dashboard

[Open the public research hub](https://vcu118-week-two-spencer.bountifuldish.chatgpt.site)

The main page links to separate Week 1 and Week 2 dashboards. Each week contains five milestone days, a visual progress indicator, expandable task details, reasoning prompts, and per-day evidence notes.

- Week 1: understand the receive path, define the message, build the reference and streaming parser, and review board status.
- Week 2: verify continuous traffic, measure parser latency, and prepare the hardware handoff.

Source: `docs/index.html`. This is a standalone HTML/CSS/JavaScript application with no build step or external dependencies. Open it directly or serve `docs/` with a static server. Routes use `#home`, `#week-1`, and `#week-2`.

Progress and evidence notes are stored separately for each week in the visitor's browser. The existing Week 2 storage key is preserved. Notes and checkmarks are not committed or shared across visitors. The original Week 1 assignment link requires access to the ChatGPT document.

To also host this on GitHub Pages, select Settings → Pages → Deploy from a branch → main → /docs → Save. GitHub Pages has not been enabled by this commit.
