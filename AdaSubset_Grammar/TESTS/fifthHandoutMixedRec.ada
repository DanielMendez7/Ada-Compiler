procedure Test is 
   a : integer;       --offset is 4
   type w is array(0..2) of integer;
   d : w;             --offset is 5, size is 3
   type far is array(4..7) of integer;
   b : integer;       --offset is 8
   c : far;           --offset is 9
		      -- sized of AR is 13 (4+1+3+1+4).
   
   
   type R2 is -- Begin record declaration
   record
     first : integer;
     second : boolean;  
     third : w; 
     fourth : far;
   end record;
   
begin 
   
   --  
   --
   
end;
  
