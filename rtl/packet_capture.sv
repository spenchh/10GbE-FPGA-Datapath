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
logic                       RDADDREN;           // Low = Hold, High = set
logic                       WRADDREN;           // Low = Hold, High = set   
//logic                     SLEEP;              // Takes two clock cycles to wakeup. 

assign DIN    = rx_axis_tdata;
assign DINP   = rx_axis_tkeep;
assign RSTRAM = !rx_rst_n;     

// Clock polarity is posedge
always_ff @(posedge rx_core_clk) begin
    if (!rx_rst_n) begin
        RDEN    <=  0;
        WREN    <=  0;
        DOUT    <= '0;
        DOUTP   <= '0;
        WRADDR  <= '0;                   // initial write pointer
        RDADDR  <= '0;                   // initlal read  pointer
    end else begin
        if (rx_axis_tvalid) begin

            // —— Read logic for BRAM ——
            if (RDEN) begin    
                {DOUT, DOUTP} <= BRAM[RDADDR];

                if (RDADDREN) begin            // Which address to read from. High = new address, Low = holds prev address
                    if (RDADDR == ENTRIES - 1) // can you &RDADDR aswell to check if it reached last entry
                        RDADDR <= '0;
                    else
                        RDADDR <= RDADDR + 1;
                end
            end

            // —— Write logic for BRAM ——
            if (WREN) begin
                BRAM[WRADDR] <= {DIN, DINP};

                if (WRADDREN) begin
                    if (WRADDR == ENTRIES - 1)
                        WRADDR <= '0;
                    else
                        WRADDR <= WRADDR + 1;
                end
            end

        end
    end
end

endmodule