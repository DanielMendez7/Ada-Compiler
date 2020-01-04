procedure test is 
   A : integer;  -- offset of 4
   B : boolean;  -- offset of 5
   
   type aType is array (2..4) of integer;  -- size is 3
   
   type R2 is -- Begin record declaration  -- size is 7
   record
     First, Second : integer;   --no offset yet until type of R2 is declared
     Third, Fourth : boolean;  --no offet yet until type of R2 is declared
     Fifth         : aType;
   end record;
   
   arr : aType;         -- offset of 6    -- but size is 3
   C : integer;         --offset of 9
   D : R2;              -- offset of 10   -- but size of 7
   E : integer;         -- offset of 17
   
begin 
   --C := D.Second; 
    arr(2) := D.Fifth(4);
   --E := 5;
   --
end;
  
