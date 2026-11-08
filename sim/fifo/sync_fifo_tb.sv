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
wire [WIDTH-1:0] o_data;
wire o_mem_full;
wire o_mem_empty;

// —— Instantiate FIFO DUT ——
sync_fifo #(.WIDTH(WIDTH), .DEPTH(DEPTH)) dut (.*);

// —— Stimulus ——
always #5 i_clk = ~i_clk;

initial begin
    i_clk = 0;

    // 1. Initialize the other DUT inputs.
    i_rst_n =  0;
    i_data  = '0;
    i_wr_en =  0;
    i_rd_en =  0;

    // 2. Assert reset, hold it across clock edges, then release it on a falling edge.
    
    #20; // wait 20 ns

    @(negedge i_clk);
    i_rst_n =  1;

    // 3. Drive a transaction.
    @(negedge i_clk);
    i_data  = 64'h616E67656C61777A;
    i_wr_en = 1;
    
    @(negedge i_clk);
    i_data  = '0;
    i_wr_en =  0;

    // 4. Wait for the DUT to process it,
    //    then check the result after its NBA updates.

    // 5. Repeat with more test cases.

    $finish;
end


endmodule;