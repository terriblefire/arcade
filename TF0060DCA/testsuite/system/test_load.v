`timescale 1ns / 1ps

module test_load;

`include "system_fixture.vinc"   
`include "../unittest.vinc"

initial begin

	$dumpfile("test_load.vcd");
    $dumpvars(0, test_load);

    #1;

    #20000; 

    SD = 8'hA5;
    #150;
    CLK[1] = 0;
    #60;
    CLK[1] = 1;
    
    #200000;


    $finish();

end 

endmodule
