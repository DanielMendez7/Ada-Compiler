procedure main is         --nonLocalParm.ada
a, b : integer;

   procedure mess is 
   N, M : integer;
   b : integer;
      procedure nest is
      a, c : integer;
         procedure inner (x : in out integer; y : out integer;  q : in integer) is
         z : integer;
         begin
            x := 2;
            y := 5;
            z := 3;
            a := b;
         end;

      begin
         inner (c, a, 7);
      end;
   begin
      nest;
   end;   
begin
   mess;
end;
