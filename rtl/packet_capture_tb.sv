module packet_capture_tb;
    timeunit 1ns / 1ps;

    localparam int DATAWIDTH = 64;
    localparam int BYTE      = DATAWIDTH / 8;

    logic                 clk = 1'b0;
    logic                 rx_rst_n;
    logic [DATAWIDTH-1:0] rx_axis_tdata;
    logic [BYTE-1:0]      rx_axis_tkeep;
    logic                 rx_axis_tvalid;
    logic                 rx_axis_tuser;
    logic                 rx_axis_tlast;

    packet_capture dut (.rx_core_clk(clk), .*);

    always #3.2 clk = ~clk;

    // Call on a falling edge. The DUT samples this beat on the next rising edge.
    task automatic send_beat(
        input logic [DATAWIDTH-1:0] data,
        input logic [BYTE-1:0] keep,
        input logic last
    );
        rx_axis_tdata  = data;
        rx_axis_tkeep  = keep;
        rx_axis_tlast  = last;
        rx_axis_tvalid = 1'b1;
        @(negedge clk);
    endtask

    task automatic idle_rx();
        rx_axis_tdata  = '0;
        rx_axis_tkeep  = '0;
        rx_axis_tlast  = 1'b0;
        rx_axis_tvalid = 1'b0;
        rx_axis_tuser  = 1'b0;
    endtask

    task automatic check_word(input int beat, input logic [DATAWIDTH-1:0] expected);
        if (dut.DOUT !== expected)
            $fatal(1, "Readback beat %0d: expected %h, got %h", beat, expected, dut.DOUT);
    endtask

    task automatic check_rearmed();
        if ({dut.WREN, dut.RDEN} !== 2'b10 ||
            dut.WRADDR !== '0 || dut.RDADDR !== '0 || dut.counter !== '0)
            $fatal(1, "Capture did not rearm after the final BRAM fetch");
    endtask

    initial begin
        rx_rst_n = 1'b0;
        idle_rx();

        @(negedge clk);
        if ({dut.WREN, dut.RDEN, dut.read_valid} !== 3'b000 ||
            dut.WRADDR !== '0 || dut.RDADDR !== '0 ||
            dut.counter !== '0 || dut.DOUT !== '0)
            $fatal(1, "Reset did not clear capture state");

        rx_rst_n = 1'b1;
        @(negedge clk);
        check_rearmed();

        // Three MAC-interface beats, with only three valid bytes in the last beat.
        send_beat(64'h8877_6655_4433_2211, 8'hFF, 1'b0);
        send_beat(64'hFFEE_DDCC_BBAA_9988, 8'hFF, 1'b0);
        send_beat(64'hFFEE_DDCC_BBAA_1234, 8'h07, 1'b1);
        idle_rx();

        if (dut.counter !== 9'd3 || dut.RDEN !== 1'b1)
            $fatal(1, "Expected three stored beats and inspection enabled");

        @(negedge clk); // Fetch beat 0. DOUT still holds its reset value.
        if (dut.read_valid !== 1'b1 || dut.DOUT !== '0)
            $fatal(1, "First BRAM fetch did not align with the output pipeline");

        @(negedge clk); // Two clocks after accepting the final RX beat.
        check_word(0, 64'h8877_6655_4433_2211);

        @(negedge clk); // Fetch beat 2 while beat 1 reaches DOUT.
        check_word(1, 64'hFFEE_DDCC_BBAA_9988);
        check_rearmed();
        if (dut.read_valid !== 1'b1)
            $fatal(1, "Final fetched beat is missing its valid flag");

        @(negedge clk); // The final beat reaches DOUT with RDEN already low.
        check_word(2, 64'h0000_0000_00AA_1234);
        if ({dut.RDEN, dut.read_valid} !== 2'b00)
            $fatal(1, "The read pipeline did not drain");

        // Send a distinct frame without resetting to catch stale readback.
        send_beat(64'h0123_4567_89AB_CDEF, 8'hFF, 1'b1);
        idle_rx();
        repeat (2) @(negedge clk);
        check_word(0, 64'h0123_4567_89AB_CDEF);
        check_rearmed();

        $display("PASS: reset, pipelined readback, byte masking, and two captures without reset");
        $finish;
    end
endmodule
