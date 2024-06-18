`timescale 1ns/10ps
module MAC (
    clock,
    reset,
    a,
    b,
    c,
    a_out,
    b_out,
    c_out,
    result,
    done
);

input                       clock, reset;
input           [  3:0 ]    a, b;
input           [  7:0 ]    c;

output reg      [  3:0 ]    a_out, b_out;
output reg      [  7:0 ]    c_out;
output reg      [  8:0 ]    result;
output reg                  done;

// Implement your HDL here
always @(posedge clock or posedge reset) begin
    if (reset) begin
        a_out <= 4'b0;
        b_out <= 4'b0;
        c_out <= 8'b0;
        result <= 9'b0;
        done <= 0;
    end else begin
        a_out <= a;
        b_out <= b;
        c_out <= c;
        result <= (a * b) + c;
        done <= 1;
    end
end
endmodule
