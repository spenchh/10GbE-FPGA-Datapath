SIM ?= verilator
TOPLEVEL_LANG = verilog

TEST_DIR := $(dir $(abspath $(lastword $(MAKEFILE_LIST))))
PROJECT_ROOT := $(abspath $(TEST_DIR)/../..)
VERILOG_SOURCES = $(PROJECT_ROOT)/rtl/sync_fifo.sv
COCOTB_TOPLEVEL = sync_fifo
COCOTB_TEST_MODULES = sync_fifo_tb

# The existing directed tests use 16 entries; keep the RTL's default unchanged.
COMPILE_ARGS += -GDEPTH=16 -Wno-fatal

export PYTHONPATH := $(TEST_DIR):$(PYTHONPATH)
include $(shell cocotb-config --makefiles)/Makefile.sim
