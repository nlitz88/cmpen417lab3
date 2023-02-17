`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 02/16/2023 09:41:27 PM
// Design Name: 
// Module Name: complex_multiplier
// Project Name: 
// Target Devices: 
// Tool Versions: 
// Description: 
// 
// Dependencies: 
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
//////////////////////////////////////////////////////////////////////////////////


module complex_multiplier
    # (parameter AWIDTH = 18, BWIDTH = 18)
    (   input clk,
        input signed [AWIDTH-1:0]       ar, ai,
        input signed [BWIDTH-1:0]       br, bi,
        output signed [AWIDTH+BWIDTH:0] pr, pi
    );

// Define first stage input registers.
reg signed [AWIDTH-1:0] ar_d;
reg signed [AWIDTH-1:0] ai_d;
reg signed [AWIDTH-1:0] br_d;
reg signed [AWIDTH-1:0] bi_d;

// Define second stage multiplication output registers
reg signed [AWIDTH-1:0] arbr;
reg signed [AWIDTH-1:0] aibi;
reg signed [AWIDTH-1:0] aibr;
reg signed [AWIDTH-1:0] arbi;

// Define registers to store result --> value assigned to outputs.
reg signed [AWIDTH+BWIDTH:0] pr_d;
reg signed [AWIDTH+BWIDTH:0] pi_d;

// Behavioral description for 4 parallel multiplications using DSP.
always @(posedge clk)
    begin
        
        // Read new values into input registers each clock cycle.
        ar_d <= ar;
        ai_d <= ai;
        br_d <= br;
        bi_d <= bi;
        
        // Perform multiplication and store result.
        arbr <= ar_d * br_d;
        aibi <= ai_d * bi_d;
        aibr <= ai_d * br_d;
        arbi <= ar_d * bi_d;
        
        // Subtract/add the various parts together to form the real/imaginary parts, respectively.
        pr_d <= arbr - aibi;
        pi_d <= arbi + aibr;
        
    end
    
assign pr = pr_d;
assign pi = pi_d;
    
endmodule