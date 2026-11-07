// ================================
//    TESTBENCH for sync_fifo.sv
// ================================
module sync_fifo_tb;
timeunit 1ns / 1ps;

parameter WIDTH = 64;
parameter DEPTH = 16;

// —— TB drives inputs of DUT ——
logic i_clk;
logic i_rst_n;
logic [WIDTH-1:0] i_data;
logic i_wr_en;
logic i_rd_en;

// —— Signals for outputs ——
wire [WDITH-1:0] o_data;
wire o_mem_full;
wire o_mem_empty;

// —— Stimulus ——