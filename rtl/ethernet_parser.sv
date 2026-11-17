import ethernet_pkg::*;
module ethernet_parser(
    input i_clk,
    input i_rst_n,
    input i_packet
);

logic [(BYTE*6)-1:0] dst_addr;
logic [(BYTE*6)-1:0] src_addr;
logic [(BYTE*2)-1:0] len_type;
logic [(BYTE*1500)-1:0] data;
logic [(BYTE*46)  -1:0] pad; // ensures frame length is at least 64 bytes
logic [(BYTE*4)   -1:0] fcs;

parse_control_t control;
state_control_t state;
endmodule