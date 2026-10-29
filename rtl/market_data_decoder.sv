/*
Market Data Decoder:
  Extracts and decodes a 248 bit, 31 byte payload into usable fields
  Quote comes from UDP payload
*/
module market_data_decoder(
  input logic          i_clk,
  input logic          i_rst_n,

  input logic  [247:0] i_payload, // 248 bit
  input logic          i_valid,   // tells us when there is a new quote

  output logic [ 7:0]  o_message_type,    // What kind of message it is (type 1 = quote update)
  output logic [31:0]  o_sequence_number, // enables later logic to detect gaps
  output logic [15:0]  o_symbol_id,       // Which stock 
  output logic [31:0]  o_bid_price,
  output logic [31:0]  o_bid_size,
  output logic [31:0]  o_ask_price,
  output logic [31:0]  o_ask_size,
  output logic [63:0]  o_timestamp,       // What time the quote was generated
  
  output logic         o_valid,           // outputs contain a decoded quote
  output logic         o_decode_error
);

logic [ 7:0]  message_type;
logic [31:0]  sequence_number;
logic [15:0]  symbol_id;
logic [31:0]  bid_price;
logic [31:0]  bid_size;
logic [31:0]  ask_price;
logic [31:0]  ask_size;
logic [63:0]  timestamp;
logic         packet_valid;

assign message_type    = i_payload [247 : 240];
assign sequence_number = i_payload [239 : 208];
assign symbol_id       = i_payload [207 : 192];
assign bid_price       = i_payload [191 : 160];
assign ask_price       = i_payload [159 : 128];
assign bid_size        = i_payload [127 :  96];
assign ask_size        = i_payload [95  :  64];
assign timestamp       = i_payload [63  :   0];

assign packet_valid = (
  (message_type == 8'd1) && // message type 1 = quote update
  (bid_size != 32'd0) &&
  (ask_size != 32'd0) &&
  (bid_price <= ask_price)
);


always_ff @(posedge i_clk) begin
  if (!i_rst_n) begin
    o_valid           <= '0;
    o_message_type    <= '0;
    o_sequence_number <= '0;
    o_symbol_id       <= '0;
    o_bid_price       <= '0;
    o_bid_size        <= '0;
    o_ask_price       <= '0;
    o_ask_size        <= '0;
    o_timestamp       <= '0;
    o_decode_error      <= '0;
  end else begin
    if (i_valid) begin
      o_decode_error <= 0;
      if (packet_valid) begin
        o_message_type    <= message_type;
        o_sequence_number <= sequence_number;
        o_symbol_id       <= symbol_id;
        o_bid_price       <= bid_price;
        o_bid_size        <= bid_size;
        o_ask_price       <= ask_price;
        o_ask_size        <= ask_size;
        o_timestamp       <= timestamp;
        o_valid           <= 1'b1;
      end else begin
        o_decode_error      <= 1'b1;
        o_valid           <= 1'b0;
      end
    end else begin
      o_valid      <= 1'b0;
      o_decode_error <= 1'b0; // clear during idle
    end
  end
end
endmodule