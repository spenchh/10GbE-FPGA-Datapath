import ethernet_pkg::*;
module ethernet_top(
    input logic i_clk,
    input logic i_rst_n
);
wire [DATAWIDTH-1:0] packet;
packet_capture i1(.rx_core_clk(i_clk), 
                  .rx_rst_n(i_rst_n), 
                  .DOUT(packet),
                  .rx_axis_tdata(),
                  .rx_axis_tkeep(),
                  .rx_axis_tvalid(),
                  .rx_axis_tuser(),
                  .rx_axis_tlast());
ethernet_parser i2(.*, .i_packet(packet))
                
endmodule