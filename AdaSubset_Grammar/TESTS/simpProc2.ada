procedure Main is             --simpProc2.ada
   X : integer;
   procedure Helper is
      A : integer;
   begin
      A := 3;

   end;
   
    procedure Pur is
      A : integer;
   begin
      A := 3;

   end;

begin
   Helper;
   X := 5;

end;
