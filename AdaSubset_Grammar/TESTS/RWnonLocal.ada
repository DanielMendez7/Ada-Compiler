procedure main is      -- RWnonLocal.ada
        x:integer;
        y:boolean;

  procedure inner is
     x : integer;
     procedure nested is
     begin
        read(x);
        read(y);
        write(x+x,y and y, 6);
     end;
  begin
     nested;
  end;

begin
   inner;
end;
