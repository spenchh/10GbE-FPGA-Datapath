module packet_capture_tb;
    timeunit 1ns / 1ps;

    constant DATAWIDTH = 64;
    constant BYTE      =  8;
    
    logic                 clk = 0;
    logic                 rx_rst_n;

    logic [DATAWIDTH-1:0] rx_axis_tdata;  // AXI4-Stream Data
    logic [BYTE     -1:0] rx_axis_tkeep;  // AXI4-Stream Data control
    logic                 rx_axis_tvalid; // AXI4-Stream Data valid
    logic                 rx_axis_tuser;  // AXI4-Stream Sideband interface
    logic                 rx_axis_tlast;  // AXI4-Stream End of packet signal
  
    packet_capture dut (.rx_core_clk(clk), .*);

    always #3.2 clk = ~clk;

    initial begin
        @(negedge clk); // Drive stimulus on negedge bc of duty cycle
        rx_rst_n = 0;
        rx_axis_tdata = '0;
        rx_axis_tkeep = '0;
        rx_axis_tvalid = 0;
        rx_axis_tuser = 0;
        rx_axis_tlast = 0;
        
        @(posedge clk); #1ps;
        if (dut.WRADDR !== '0)
            $fatal(1, "Reset didn't clear write address");
        if (dut.counter !== '0)
            $fatal(1, "Reset didn't clear counter");
        if (dut.RDADDR !== '0)
            $fatal(1, "Reset didn't clear RDADDR");
        if (dut.DOUT   !== '0)
            $fatal(1, "Reset didn't clear DOUT");
        if (dut.rx_index !== '0)
            $fatal(1, "Reset didn't clear rx_index");
        if (dut.i != '0 || dut.j != 32'd8)
            $fatal(1, "Problem with either i or j");
        if (dut.WREN !== 0 || dut.RDEN !== 0)
            $fatal(1, "Problem with capture control");
        if (dut.control != CAPTURE)
            $fatal(1, "control didn't reset correctly");
        
        @(negedge clk);
        rx_rst_n = 1;
        // Transfer 1: eight valid bytes.
        rx_axis_tvalid = 1'b1;
        rx_axis_tuser  = 1'b0;
        rx_axis_tlast  = 1'b0;
        rx_axis_tkeep  = 8'hFF;
        rx_axis_tdata  = 64'h8877_6655_4433_2211;

        
        // Transfer 2: eight more valid bytes.
        @(negedge clk);
        rx_axis_tdata  = 64'hFFEE_DDCC_BBAA_9988;

        // Transfer 3: three valid bytes, end of a good frame.
        @(negedge clk);
        rx_axis_tdata  = 64'hFFEE_DDCC_BBAA_1234;
        rx_axis_tkeep  = 8'h07;
        rx_axis_tlast  = 1'b1;

        // Return the simulated MAC to idle.
        @(negedge clk);
        rx_axis_tvalid = 1'b0;
        rx_axis_tlast  = 1'b0;
        rx_axis_tkeep  = '0;
        rx_axis_tdata  = '0;

        if (dut.counter !== 9'd3 || dut.RDEN !== 1'b1)
        $fatal(1, "Expected three captured words and inspection enabled");

        repeat (8) @(negedge clk);
        if (dut.DOUT !== 64'h8877_6655_4433_2211)
            $fatal(1, "Word 0 mismatch: got %h", dut.DOUT);

        repeat (8) @(negedge clk);
        if (dut.DOUT !== 64'hFFEE_DDCC_BBAA_9988)
            $fatal(1, "Word 1 mismatch: got %h", dut.DOUT);

        repeat (8) @(negedge clk);
        if (dut.DOUT !== 64'h0000_0000_00AA_1234)
            $fatal(1, "Word 2 mismatch: got %h", dut.DOUT);

        if (dut.WREN !== 1'b1 || dut.RDEN !== 1'b0 ||
            dut.WRADDR !== '0 || dut.RDADDR !== '0 || dut.counter !== '0)
            $fatal(1, "Capture did not rearm after the final word");

        $display("PASS: reset, three-word readback, and rearm");
        $finish;
    end
endmodule