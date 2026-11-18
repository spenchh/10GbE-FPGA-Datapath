import ethernet_pkg::*;
module ethernet_parser(
    input i_clk,
    input i_rst_n,
    input i_packet
);

typedef struct packed {
    logic [(BYTE*6)-1:0] dst_addr;
    logic [(BYTE*6)-1:0] src_addr;
    logic [(BYTE*2)-1:0] len_type;
    logic [(BYTE*1500)-1:0] data;
    logic [(BYTE*46)  -1:0] pad; // ensures frame length is at least 64 bytes
    logic [(BYTE*4)   -1:0] fcs;
} frame_t;

parse_control_t control;
state_control_t state;
frame_t frame;

localparam int FRAME_BYTES = $bits(frame) / BYTE;

int counter;

always_comb begin

end

always_ff @(posedge i_clk) begin
    if (!i_rst_n) begin
        counter <= 0;
        state   <= DST_ADDR;
    end else begin
        case (state)
            DST_ADDR : begin
                state <= (counter == 5) ? SRC_ADDR : DST_ADDR;
            end

            SRC_ADDR : begin
                state <= (counter == 11) ? LEN_TYPE : SRC_ADDR;
            end

            LEN_TYPE : begin
                state <= (counter == 13) ? DATA : LEN_TYPE;
            end

            // Draw state machine 

            
        endcase;
    end
end



endmodule