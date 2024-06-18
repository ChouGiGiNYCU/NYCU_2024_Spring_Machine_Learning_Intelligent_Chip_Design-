`timescale 1 ps / 1 ps

module cwr_cosim_top;

wire        cwr_HARDWARE_v_i_MAC_v_clock;
wire        cwr_HARDWARE_v_i_MAC_v_reset;
wire [3:0] cwr_HARDWARE_v_i_MAC_v_a;
wire [3:0] cwr_HARDWARE_v_i_MAC_v_b;
wire [7:0] cwr_HARDWARE_v_i_MAC_v_c;
wire [3:0] cwr_HARDWARE_v_i_MAC_v_a_out;
wire [3:0] cwr_HARDWARE_v_i_MAC_v_b_out;
wire [7:0] cwr_HARDWARE_v_i_MAC_v_c_out;
wire [8:0] cwr_HARDWARE_v_i_MAC_v_result;
wire        cwr_HARDWARE_v_i_MAC_v_done;

MAC cwr_HARDWARE_v_i_MAC(
  cwr_HARDWARE_v_i_MAC_v_clock,
  cwr_HARDWARE_v_i_MAC_v_reset,
  cwr_HARDWARE_v_i_MAC_v_a,
  cwr_HARDWARE_v_i_MAC_v_b,
  cwr_HARDWARE_v_i_MAC_v_c,
  cwr_HARDWARE_v_i_MAC_v_a_out,
  cwr_HARDWARE_v_i_MAC_v_b_out,
  cwr_HARDWARE_v_i_MAC_v_c_out,
  cwr_HARDWARE_v_i_MAC_v_result,
  cwr_HARDWARE_v_i_MAC_v_done
);

cwr_cosim_shell cwr_cosim_shell_i(
  .HARDWARE_v_i_MAC_v_clock(cwr_HARDWARE_v_i_MAC_v_clock),
  .HARDWARE_v_i_MAC_v_reset(cwr_HARDWARE_v_i_MAC_v_reset),
  .HARDWARE_v_i_MAC_v_a(cwr_HARDWARE_v_i_MAC_v_a),
  .HARDWARE_v_i_MAC_v_b(cwr_HARDWARE_v_i_MAC_v_b),
  .HARDWARE_v_i_MAC_v_c(cwr_HARDWARE_v_i_MAC_v_c),
  .HARDWARE_v_i_MAC_v_a_out(cwr_HARDWARE_v_i_MAC_v_a_out),
  .HARDWARE_v_i_MAC_v_b_out(cwr_HARDWARE_v_i_MAC_v_b_out),
  .HARDWARE_v_i_MAC_v_c_out(cwr_HARDWARE_v_i_MAC_v_c_out),
  .HARDWARE_v_i_MAC_v_result(cwr_HARDWARE_v_i_MAC_v_result),
  .HARDWARE_v_i_MAC_v_done(cwr_HARDWARE_v_i_MAC_v_done)
);

endmodule

