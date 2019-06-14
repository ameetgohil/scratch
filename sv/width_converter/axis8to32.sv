module axis8to32
  (input wire[7:0] m_data,
   input wire         m_valid,
   output wire        m_ready,
   output wire [31:0] s_data,
   output wire        s_valid,
   input wire         s_ready,
   input wire         clk, rstf
   );

   reg [31:0]         n_data;

   assign s_data = {m_data, data[23:0]};
   assign s_valid = (cnt == 3) ? 1:0;
   assign m_ready = (cnt == 3) ? s_ready:1;

   always @(posedge clk or negedge rstf) begin
      if(~rstf) begin
         cnt <= 0;
         data <= 0;
      end
      else begin
         case(cnt)
           0: data[7:0] <= m_data;
           1: data[15:8] <= m_data;
           2: data[23:16] <= m_data;
           3: data[31:23] <= m_data;
         endcase
         if(s_valid & s_ready)
           cnt <= cnt + 1;
      end
   end

endmodule
