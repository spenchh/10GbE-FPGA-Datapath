// ===================================================
//  Captures packets from Rx MAC outputs into BRAM
// ===================================================
module packet_capture#(
    parameter int BYTE      = 8,
    parameter int DATAWIDTH = 64,
    parameter int ENTRIES   = 256
)(
    input logic                 rx_core_clk,    // Clock controls RXAXI, bram - RDCLK, bram - WRCLK
//  input logic                 RDCLK,          // Port A
//  input logic                 WRCLK,          // Port B

    input logic [DATAWIDTH-1:0] rx_axis_tdata,  // AXI4-Stream Data
    input logic [BYTE     -1:0] rx_axis_tkeep,  // AXI4-Stream Data control
    input logic                 rx_axis_tvalid, // AXI4-Stream Data valid
    input logic                 rx_axis_tuser,  // AXI4-Stream Sideband interface
    input logic                 rx_axis_tlast,  // AXI4-Stream End of packet signal

    input logic                 rx_rst_n
);

// —— SDP BRAM (RAMB36E2) ——
logic [DATAWIDTH+BYTE-1 :0] BRAM [ENTRIES-1:0]; // 64 Data bits + 8 validity bids
logic                       RDEN;               // Port A Enable (active-High)
logic                       WREN;               // Port B Enable (active-High)
//logic                     REGCEA;             // Register enable (active-High) - optional
logic                       RSTRAM;             // Forces data output latches to contain value SRVAL
//logic                     DO_REG;             // Optional output register
logic [35               :0] SRVAL_A; 
logic [35               :0] SRVAL_B;
logic [$clog2(ENTRIES)-1:0] WRADDR;             // Write pointer
logic [$clog2(ENTRIES)-1:0] RDADDR;             // Read  pointer
logic [DATAWIDTH-1      :0] DIN;        
logic [BYTE-1           :0] DINP;               // DIN Parity
logic [DATAWIDTH-1      :0] DOUT;
logic [BYTE-1           :0] DOUTP;              // DOUT Parity
//logic                       RDADDREN;           // Low = Hold, High = set
//logic                       WRADDREN;           // Low = Hold, High = set   
//logic                     SLEEP;              // Takes two clock cycles to wakeup. 

assign DIN    = rx_axis_tdata;
assign DINP   = rx_axis_tkeep;
assign RSTRAM = !rx_rst_n;

// NOTE: Capture, then Insepct. (Write to mem first, then Inspect from mem)
enum logic {CAPTURE, INSPECT} control;

logic [$clog2(ENTRIES + 1) - 1:0] counter; // Need extra bit for 256

// —— Write Procedural Block ——
always_ff @(posedge rx_core_clk) begin
    if (!rx_rst_n) begin
        WRADDR   <= '0;
        WRADDREN <=  0;
        counter  <=  0;
    end else begin
        // —— Write logic for BRAM ——
        if (rx_axis_tvalid) begin
            if (WREN) begin
                BRAM[WRADDR] <= {DIN, DINP};
                counter <= counter + 1'b1;
                WRADDR  <= WRADDR  + 1;

                if (WRADDR == ENTRIES - 1) begin
                    WRADDR  <= '0;
                    counter <= '0;
                end
            end
        end
    end
end

// —— Read Procedural Block ——
always_ff @(posedge rx_core_clk) begin
    if (!rx_rst_n) begin
        RDADDR   <= '0;
        RDADDREN <=  0;
        DOUT     <= '0;
        DOUTP    <= '0;
    end else begin
        // —— Read logic for BRAM ——
        if (RDEN) begin    
            {DOUT, DOUTP} <= BRAM[RDADDR];
            RDADDR <= RDADDR + 1;
            
            if (RDADDR == ENTRIES - 1) // can use &RDADDR aswell to check if it reached last entry
                RDADDR <= '0;
        end
    end
end

// —— Control: Capture | Inspect Procedural Block ——
always_comb begin
    if (!rx_rst_n) begin
        WREN = 0;
        RDEN = 0;
    end else begin
        case (control)
            CAPTURE : begin // Only Write when Frame Capture
                WREN <= 1;
                RDEN <= 0;
            end
      
            INSPECT : begin // Only Read when Inspecting Frame
                WREN <= 0;
                RDEN <= 1;
            end
     
        endcase;
    end
end

always_ff @(posedge rx_core_clk) begin
    if (!rx_rst_n) begin
        control <= CAPTURE; // Default Capture to overwrite into bram
    end else begin
        if (rx_axis_tlast & !rx_axis_tuser) // after last packet comes and user is deasserted, switch to read
            control <= INSPECT;
        if (RDADDR == counter - 1)          // if inspect has read all the memory, switch to capture
            control <= CAPTURE;
        
    end
end

endmodule