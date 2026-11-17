import ethernet_pkg::*;
module ethernet_parser(
    input i_clk,
    input i_rst_n,
    input i_packet
);

logic [(BYTE*6)-1:0] DST_ADDR;
logic [(BYTE*6)-1:0] SRC_ADDR;
logic [(BYTE*2)-1:0] LEN_TYPE;


enum logic {LENGTH, TYPE} e_control; // controls wither LEN_TYPE is length or type
logic []

endmodule