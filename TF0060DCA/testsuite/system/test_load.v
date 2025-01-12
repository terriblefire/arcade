`timescale 1ns / 1ps

module test_load;

`include "system_fixture.vinc"   
`include "../unittest.vinc"

task setch;
input [2:1] ch;
input [7:0] val;
begin
    SD = val;
    #50;
    CLK = ch;
    #50;
    CLK = 2'b11;
    #5;
end 
endtask 



initial begin

	$dumpfile("test_load.vcd");
    $dumpvars(0, test_load);

    #1;

    #20000; 

    setch(2'b01, 'hFF);
    #2000;
    setch(2'b01, 'hFE);
    #2000;
    
    setch(2'b10, 'h00);
    #2000;

    $finish();

end 

endmodule
