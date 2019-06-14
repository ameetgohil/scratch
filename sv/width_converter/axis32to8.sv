module axis32to8
  (input wire[31:0] m_data,
   input wire        m_valid,
   output wire        m_ready,
   output wire [7:0] s_data,
   output wire       s_valid,
   input wire        s_ready,
   input wire        clk, rstf
   );

   reg [1:0]         cnt;

   assign s_data = (cnt == 0) ? m_data[7:0]:
                   (cnt == 1) ? m_data[15:8]:
                   (cnt == 2) ? m_data[23:16]:
                   m_data[31:24];

   assign s_valid = m_valid;

   assign m_ready = (cnt == 3) && s_ready? 1:0;

   always @(posedge clk or negedge rstf) begin
      if(~rstf) begin
         cnt <= 0;
      end
      else begin
         if(s_valid & s_ready)
           cnt <= cnt + 1;
      end
   end
endmodule
