// =======================================
//  Captures packets from Rx MAC outputs
// =======================================
module packet_capture#(
    parameter BYTE = 8
)(
    input logic            rx_core_clk,

    input logic [63:0]     rx_axis_tdata,  // AXI4-Stream Data
    input logic [BYTE-1:0] rx_axis_tkeep,  // AXI4-Stream Data control
    input logic            rx_axis_tvalid, // AXI4-Stream Data valid
    input logic            rx_axis_tuser,  // AXI4-Stream Sideband interface
    input logic            rx_axis_tlast   // AXI4-Stream End of packet signal
);
// —— Counter to check how many are valid ——
    // FCS error occurs
    // Packet shorter than 64 bytes
    // Frames of length greater than MTU size programmed are received
    // Any control frame received not exactly the min frame length
    // XGMII data stream contains error codes

// —— Counter to check how many are valid ——
always_comb begin
    null;
end

always_ff @(posedge rx_core_clk) begin
    if (rx_axis_tvalid) begin

        if (rx_axis_tuser && rx_axis_tlast) begin // Frame is bad so discard

        end 
    end

end

endmodule