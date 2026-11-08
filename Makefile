.PHONY: test test-decoder test-fifo

test: test-decoder test-fifo

test-decoder:
	$(MAKE) -C sim

test-fifo:
	$(MAKE) -C sim/fifo
