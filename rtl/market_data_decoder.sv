/*
  Receive 248-bit payload, validate, split into named fields,
  register fields for next stage

*/
module market_data_decoder (
  input logic         i_clk,
  input logic         i_rst_n,
  input logic         i_packet_valid,
  input logic [247:0] i_packet_in,

  output logic        o_decoded_valid,
  output logic        o_decode_error,
  output logic [7:0]  o_message_type,
  output logic [31:0] o_sequence_number,
  output logic [15:0] o_symbol_id,
  output logic [31:0] o_bid_price,
  output logic [31:0] o_ask_price,
  output logic [31:0] o_bid_size,
  output logic [31:0] o_ask_size,
  output logic [63:0] o_timestamp 
);

assign [7:0]  incoming_message_type        = i_packet_in[247:240];
assign [31:0] incoming_sequence_number     = i_packet_in[239:208];
assign [15:0] incoming_symbol_id           = i_packet_in[207:192];
assign [31:0] incoming_bid_price           = i_packet_in[191:160];
assign [31:0] incoming_ask_price           = i_packet_in[159:128];
assign [31:0] incoming_bid_size            = i_packet_in[127:96];
assign [31:0] incoming_ask_size            = i_packet_in[95:64];
assign [63:0] incoming_timestamp           = i_packet_in[63:0];

logic packet_acceptable;
/*
Current split:  
  Message type    - Confirm supported type
  Sequence number - Extract now, validate later
  Symbol ID       - Extract now, bounds-check later
  Bid price       - Extract and compare w/ask
  Ask price       - Extract and compare w/bid
  Bid size        - Nonzero
  Ask size        - Nonzero
  Timestamp       - Extract now, validate later
*/
assign packet_acceptable = 
  (incoming_message_type = 8'd1) &&
  (incoming_bid_size     = 32'd0) &&
  (incoming_ask_size     = 32'd0) &&
  /*
    bid price is highest price buyer offers
    ask price is lowest price seller offers
  */
  (incoming_bid_price <= incoming_ask_price);

always_ff @ (posedge i_clk) begin
  if (!i_rst_n) begin
    o_decoded_valid   <= 1'b0;
    o_message_type    <= 8'b0;
    o_sequence_number <= 32'b0;
    o_symbol_id       <= 16'b0;
    o_bid_price       <= 32'b0;
    o_ask_price       <= 32'b0;
    o_bid_size        <= 32'b0;
    o_ask_size        <= 32'b0;
    o_timestamp       <= 64'b0;
  end else 
    o_decode_error  <= 1'b0;
    o_decoded_valid <= 1'b0;
    if (i_packet_valid) begin
      if begin

      end else begin
        o_decode_error = 1'b1;
      end

    end
end
endmodule