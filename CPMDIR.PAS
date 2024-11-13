{.HEPage #}
{.PL60}
{.PO2}
PROGRAM CPM80Dir;

  { This program gives a directory of the logged drive/user area. }
  { Update log. Lee Bradley
    6/24/86, Fixed treatment of drive byte and added user number
             display.
    6/27/86, Removed redundant code.
    6/29/86, Made more efficient.  Capitalized key words.  Adding
             formatting logic. }

CONST
  Search_First         : integer = $11;
  Search_Next          : integer = $12;
  Set_DMA              : integer = $1A;
  Return_Cur_Disk      : integer = $19;
  Get_Cur_User         : integer = $20;

VAR
  Error, Loop, Start   : integer;
  FCB                  : ARRAY[0..25] OF byte ABSOLUTE $005C;
  DMA                  : ARRAY[0..255] OF byte;
  first_time           : boolean;
  d,u                  : STRING[1];
  i                    : integer;

BEGIN
  first_time := true;
  i := 0;
  Error := BDos(Set_DMA,Addr(DMA));
  FCB[0] := 0;
  FOR Loop := 1 TO 11 DO
    FCB[Loop] := ord('?');
  d := Chr(BDos(Return_Cur_Disk)+65);
  u := Chr(BDos(Get_Cur_User,$ff)+48);
  Writeln;
  Writeln('CPMDIR.PAS, Version 1.1, 6/29/86');
  Writeln;
  REPEAT
    IF NOT first_time THEN Error := BDos(Search_Next)
    ELSE
      BEGIN
        Error := BDos(Search_First,Addr(FCB));
        first_time := false;
      END;
    Start := Error * 32;
    IF Error <> 255 THEN
      BEGIN
        IF i = 4 THEN BEGIN Writeln; i := 0; END;
        IF i <> 0 THEN Write(' | ');
        Write(d,u,': ');
        FOR Loop:= Start+1 TO Start+8 do
          Write(Chr(Mem[Addr(DMA)+Loop]));
        Write('.');
        FOR Loop:= Start+9 TO Start+11 DO
          Write(Chr(Mem[Addr(DMA)+Loop]));
        i := i + 1
      END
  UNTIL Error=255;
  Writeln
END. { CPM80Dir }
