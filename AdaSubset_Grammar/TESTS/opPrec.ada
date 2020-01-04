procedure Main is             --opPrec.ada
   X,Y,Z : integer;
   procedure Helper is
      A,B,C : integer;
   begin

      A := 3; 
      B := 2;
      
      
      C := A = B;
      Z := B = A;
      
      Z := C + Y;
      Y := A + B;
      X := X * Y;
      Y := Z / X;
      Z := X - Y;
   end;

begin
   X := 5;
   Y := 6;

   Z := X + Y * Y;
end;
