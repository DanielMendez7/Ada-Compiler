procedure main is         --final.ada
   a, x : integer;
   type arree is array (0 .. 3) of integer;

   procedure bbb is
      n, m : integer;
      excObj  : exception;
      find : arree;
   begin
      if n = m then
         raise excObj;
      elsif n = 52 then
         if m < 0 then
            loop
               find(n) := 0;
               exit;
            end loop;
         elsif m = 0 then
            n := 0;
         end if;
      else
         n := 73;
      end if;
      x := m;
      exception
         when excObj => raise numeric_error;
   end;

   procedure ddd (x : in out integer) is
      i, j, k : integer;

      procedure eee (y : in integer) is
         aa, bb, cc, dd : integer;
      begin
         bbb;
      end;

   begin
      eee(x+2);
   end;

begin
   a := 4;
   ddd (a);
   exception
      when constraint_error => x := 44;
      when others => x := 46;
end;
