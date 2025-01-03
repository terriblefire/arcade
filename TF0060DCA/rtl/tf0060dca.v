
module tf0060dca(
    input       CLKOUT, 
    
    output      SCLK, 
    output reg  LOAD_SHIFT, 
    output      DI, 

    input [2:1] CLK, 
    input [7:0] SD
);

localparam CH1_ADDRESS = 0;
localparam LOAD_CH1_START = 15;
localparam LOAD_CH1A      = LOAD_CH1_START - 'd1;
localparam LOAD_CH1D      = LOAD_CH1A + 'd16;
localparam LOAD_CH1_END   = LOAD_CH1D + 'd16;

localparam CH2_ADDRESS = 1;
localparam LOAD_CH2_START = 63;
localparam LOAD_CH2A      = LOAD_CH2_START - 'd1;
localparam LOAD_CH2D      = LOAD_CH2A + 'd16;
localparam LOAD_CH2_END   = LOAD_CH2D + 'd16;


initial begin 
    LOAD_SHIFT = 1'b1;
end 

reg [7:0] _ch1_data = 0;
reg [7:0] _ch2_data = 0;

always @(negedge CLK[1]) begin 
    _ch1_data <= SD;
end 

always @(negedge CLK[2]) begin 
    _ch2_data <= SD;
end 

reg [8:0] counter = 0;
reg [8:0]  shift_reg = 0;

always @(posedge CLKOUT) begin 

    counter     <= counter + 'd1;

    if (counter == LOAD_CH1_START) LOAD_SHIFT <= 1'b0; 
    if (counter == LOAD_CH2_START) LOAD_SHIFT <= 1'b0; 

    if (counter == LOAD_CH1_END)   LOAD_SHIFT <= 1'b1;
    if (counter == LOAD_CH2_END)   LOAD_SHIFT <= 1'b1;

    if (counter[0] == 1'b1) begin 

        shift_reg <= {shift_reg[7:0], 1'b1};

    end else begin 

        case (counter)
            LOAD_CH1A: shift_reg[7:0] <= CH1_ADDRESS;
            LOAD_CH1D: shift_reg[7:0] <= _ch1_data;
            LOAD_CH2A: shift_reg[7:0] <= CH2_ADDRESS;
            LOAD_CH2D: shift_reg[7:0] <= _ch2_data;
        endcase

    end 

end 

assign SCLK = counter[0];
assign DI   = shift_reg[8];

endmodule