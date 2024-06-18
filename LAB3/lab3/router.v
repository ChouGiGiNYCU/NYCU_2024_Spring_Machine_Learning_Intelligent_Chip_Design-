module Router (
    input wire clk,
    input wire rst,
    // transmit flit
    output reg [33:0] out_flit_0,
    output reg [33:0] out_flit_1,
    output reg [33:0] out_flit_2,
    output reg [33:0] out_flit_3,
    output reg [33:0] out_flit_4,
    output reg out_req_0,
    output reg out_req_1,
    output reg out_req_2,
    output reg out_req_3,
    output reg out_req_4,
    input wire in_ack_0,
    input wire in_ack_1,
    input wire in_ack_2,
    input wire in_ack_3,
    input wire in_ack_4,
    // receive flit
    input wire [33:0] in_flit_0,
    input wire [33:0] in_flit_1,
    input wire [33:0] in_flit_2,
    input wire [33:0] in_flit_3,
    input wire [33:0] in_flit_4,
    input wire in_req_0,
    input wire in_req_1,
    input wire in_req_2,
    input wire in_req_3,
    input wire in_req_4,
    output reg out_ack_0,
    output reg out_ack_1,
    output reg out_ack_2,
    output reg out_ack_3,
    output reg out_ack_4
);

    reg [33:0] packet [0:1000000000]; // Assuming max packet size of 10000000 flits
    reg [24:0] packet_size; // Enough bits to represent the packet size
    reg packet_complete;
    reg [2:0] dir; // use 3-bit register to represent direction
    reg [2:0] i; // use 3-bit register to represent loop variable

    initial begin
        out_flit_0 = 34'b0;
        out_flit_1 = 34'b0;
        out_flit_2 = 34'b0;
        out_flit_3 = 34'b0;
        out_flit_4 = 34'b0;
        out_req_0 = 1'b0;
        out_req_1 = 1'b0;
        out_req_2 = 1'b0;
        out_req_3 = 1'b0;
        out_req_4 = 1'b0;
        out_ack_0 = 1'b0;
        out_ack_1 = 1'b0;
        out_ack_2 = 1'b0;
        out_ack_3 = 1'b0;
        out_ack_4 = 1'b0;
        packet_size = 0;
        packet_complete = 0;
    end

    always @(posedge clk or posedge rst) begin
        if (rst) begin
            out_flit_0 <= 34'b0;
            out_flit_1 <= 34'b0;
            out_flit_2 <= 34'b0;
            out_flit_3 <= 34'b0;
            out_flit_4 <= 34'b0;
            out_req_0 <= 1'b0;
            out_req_1 <= 1'b0;
            out_req_2 <= 1'b0;
            out_req_3 <= 1'b0;
            out_req_4 <= 1'b0;
            out_ack_0 <= 1'b0;
            out_ack_1 <= 1'b0;
            out_ack_2 <= 1'b0;
            out_ack_3 <= 1'b0;
            out_ack_4 <= 1'b0;
            packet_size <= 0;
            packet_complete <= 0;
        end else begin
            for (dir = 0; dir < 5; dir = dir + 1) begin
                if ((dir == 0 && in_req_0) || (dir == 1 && in_req_1) || (dir == 2 && in_req_2) || (dir == 3 && in_req_3) || (dir == 4 && in_req_4)) begin
                    receive_and_route_packet(dir);
                end
            end
        end
    end

    task receive_and_route_packet(input [2:0] dir);
        reg [33:0] flit;
        begin
            packet_size = 0;
            packet_complete = 0;
            case (dir)
                0: out_ack_0 = 1;
                1: out_ack_1 = 1;
                2: out_ack_2 = 1;
                3: out_ack_3 = 1;
                4: out_ack_4 = 1;
            endcase
            #1; // Ensure the ack is registered
            case (dir)
                0: out_ack_0 = 0;
                1: out_ack_1 = 0;
                2: out_ack_2 = 0;
                3: out_ack_3 = 0;
                4: out_ack_4 = 0;
            endcase

            while (!packet_complete) begin
                @(posedge clk);
                case (dir)
                    0: flit = in_flit_0;
                    1: flit = in_flit_1;
                    2: flit = in_flit_2;
                    3: flit = in_flit_3;
                    4: flit = in_flit_4;
                endcase
                packet[packet_size] = flit;
                packet_size = packet_size + 1;
                case (dir)
                    0: out_ack_0 = 1;
                    1: out_ack_1 = 1;
                    2: out_ack_2 = 1;
                    3: out_ack_3 = 1;
                    4: out_ack_4 = 1;
                endcase
                #1; // Ensure the ack is registered
                case (dir)
                    0: out_ack_0 = 0;
                    1: out_ack_1 = 0;
                    2: out_ack_2 = 0;
                    3: out_ack_3 = 0;
                    4: out_ack_4 = 0;
                endcase

                if (flit[32] == 1) begin
                    packet_complete = 1;
                end
            end

            route_packet(dir);
        end
    endtask

    task route_packet(input [2:0] dir);
        reg [2:0] out_dir;
        reg [3:0] core_dest;
        reg [3:0] dest_x, dest_y;
        begin
            if (packet[0][31:0] == 32'hFFFFFFFF) begin
                if ((y * 4 + x) != 0) begin
                    out_dir = determine_direction(x, y, 0, 0);
                end else begin
                    out_dir = 4; // NORTH
                end
            end else begin
                core_dest = packet[0][31:28];
                dest_x = core_dest % 4;
                dest_y = core_dest / 4;
                out_dir = determine_direction(x, y, dest_x, dest_y);
            end

            if (out_dir != -1) begin
                case (out_dir)
                    0: out_req_0 = 1;
                    1: out_req_1 = 1;
                    2: out_req_2 = 1;
                    3: out_req_3 = 1;
                    4: out_req_4 = 1;
                endcase
                case (out_dir)
                    0: wait(in_ack_0 == 1);
                    1: wait(in_ack_1 == 1);
                    2: wait(in_ack_2 == 1);
                    3: wait(in_ack_3 == 1);
                    4: wait(in_ack_4 == 1);
                endcase
                case (out_dir)
                    0: out_req_0 = 0;
                    1: out_req_1 = 0;
                    2: out_req_2 = 0;
                    3: out_req_3 = 0;
                    4: out_req_4 = 0;
                endcase
                for (i = 0; i < packet_size; i = i + 1) begin
                    case (out_dir)
                        0: out_flit_0 = packet[i];
                        1: out_flit_1 = packet[i];
                        2: out_flit_2 = packet[i];
                        3: out_flit_3 = packet[i];
                        4: out_flit_4 = packet[i];
                    endcase
                    case (out_dir)
                        0: wait(in_ack_0 == 1);
                        1: wait(in_ack_1 == 1);
                        2: wait(in_ack_2 == 1);
                        3: wait(in_ack_3 == 1);
                        4: wait(in_ack_4 == 1);
                    endcase
                end
            end
        end
    endtask

    function [2:0] determine_direction(input [2:0] src_x, input [2:0] src_y, input [2:0] dest_x, input [2:0] dest_y);
        begin
            if (dest_x == src_x && dest_y == src_y) begin
                determine_direction = -1;
            end else if (src_y == dest_y) begin
                if (src_x < dest_x) begin
                    determine_direction = 0; // EAST
                end else begin
                    determine_direction = 1; // WEST
                end
            end else if (src_x == dest_x) begin
                if (src_y < dest_y) begin
                    determine_direction = 2; // SOUTH
                end else begin
                    determine_direction = 3; // NORTH
                end
            end else if (src_y < dest_y) begin
                determine_direction = (src_x > dest_x) ? 1 : 2; // WEST : SOUTH
            end else begin
                determine_direction = (src_x < dest_x) ? 0 : 3; // EAST : NORTH
            end
        end
    endfunction
endmodule
