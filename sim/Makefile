SIM            = verilator
TOPLEVEL_LANG  = verilog

VERILOG_SOURCES = $(abspath ../rtl/market_data_decoder.sv)

COCOTB_TOPLEVEL     = market_data_decoder
COCOTB_TEST_MODULES = market_data_decoder_tb

COCOTB_HDL_TIMEUNIT      = 1ns
COCOTB_HDL_TIMEPRECISION = 1ns 


export PYTHONPATH := $(abspath ..):$(PYTHONPATH)
include $(shell cocotb-config --makefile)/Makefile.sim
