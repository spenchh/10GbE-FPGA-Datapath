SIM            = verilator
TOPLEVEL_LANG  = verilog

TEST_DIR := $(dir $(abspath $(lastword $(MAKEFILE_LIST))))
PROJECT_ROOT := $(abspath $(TEST_DIR)/..)
VERILOG_SOURCES = $(PROJECT_ROOT)/rtl/market_data_decoder.sv

COCOTB_TOPLEVEL     = market_data_decoder
COCOTB_TEST_MODULES = market_data_decoder_tb

COCOTB_HDL_TIMEUNIT      = 1ns
COCOTB_HDL_TIMEPRECISION = 1ns 


export PYTHONPATH := $(TEST_DIR):$(PROJECT_ROOT):$(PYTHONPATH)
include $(shell cocotb-config --makefiles)/Makefile.sim
