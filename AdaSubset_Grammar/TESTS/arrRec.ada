-- arrRec.ada

procedure main is
   a : integer;       --offset is 4
   type aType is array (0..2) of integer;  -- size is 3
   type dateType is record
      month : integer;
      year  : aType;   --could change this to be type aType!
   end record;                             -- size is 4
   arr  : aType;      --offset is 5
   b    : integer;    --offset is 8
   date : dateType;   --offset is 9
   c    : integer;    --offset is 13
                      --size of AR is 14 (4 + 1+3+1+4+1)
   procedure green is
      c : integer;    --offset is 4
   begin
      c := arr (2);
      date.year(1) := c;
   end;

begin
   a := 1;
   arr(1) := date.year(2);
   --c := arr ( date.month );
end;
