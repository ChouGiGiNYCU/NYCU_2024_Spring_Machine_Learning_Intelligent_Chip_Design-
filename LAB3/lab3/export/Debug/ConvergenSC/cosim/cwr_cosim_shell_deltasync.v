`timescale 1 ps / 1 ps

module cwr_cosim_shell_deltasync (
  cwr_ToggleSig,
  HARDWARE_v_i_MAC_v_clock,
  HARDWARE_v_i_MAC_v_reset,
  HARDWARE_v_i_MAC_v_a,
  HARDWARE_v_i_MAC_v_b,
  HARDWARE_v_i_MAC_v_c,
  HARDWARE_v_i_MAC_v_a_out,
  HARDWARE_v_i_MAC_v_b_out,
  HARDWARE_v_i_MAC_v_c_out,
  HARDWARE_v_i_MAC_v_result,
  HARDWARE_v_i_MAC_v_done
);

output         cwr_ToggleSig;
output         HARDWARE_v_i_MAC_v_clock;
output         HARDWARE_v_i_MAC_v_reset;
output  [3:0] HARDWARE_v_i_MAC_v_a;
output  [3:0] HARDWARE_v_i_MAC_v_b;
output  [7:0] HARDWARE_v_i_MAC_v_c;
input   [3:0] HARDWARE_v_i_MAC_v_a_out;
input   [3:0] HARDWARE_v_i_MAC_v_b_out;
input   [7:0] HARDWARE_v_i_MAC_v_c_out;
input   [8:0] HARDWARE_v_i_MAC_v_result;
input          HARDWARE_v_i_MAC_v_done;

reg            HARDWARE_v_i_MAC_v_clock;
reg            HARDWARE_v_i_MAC_v_reset;
reg     [3:0] HARDWARE_v_i_MAC_v_a;
reg     [3:0] HARDWARE_v_i_MAC_v_b;
reg     [7:0] HARDWARE_v_i_MAC_v_c;
reg            cwr_ToggleSig;

parameter CWR_HDL_SHELL = "primary";

initial
  begin
    $cwr_cosim_init;
  end

endmodule

