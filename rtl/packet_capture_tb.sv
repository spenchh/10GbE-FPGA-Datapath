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
        rx_rst_n = 1;
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
    end


endmodule