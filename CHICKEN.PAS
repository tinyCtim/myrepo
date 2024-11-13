
{$u-}

{
This program, "Chicken," is Copyright (c) 1984 by D. Griffith. It is
released by the author into the public domain for non-commercial uses,
only. "Chicken" is written in Turbo Pascal, which is Copyright (c) by
Borland International.
}

Program Chicken;

var
   s1y,s1x,s2y,s2x,s1dy,s1dx,s2dy,s2dx: integer;
   head1,head2,len1,len2,tail1,tail2,udelay,i,j,sc1,sc2,time: integer;
   again,quit,lose_bill,lose_bill_dubofem,lose_bill1,lose_bill2: boolean;
   key: char;
   player1,player2: string[10];
   chicken1,chicken2: array[1..850] of integer;
   screen: array[0..23,0..78] of char;
   s1,s2:char;

const
   null=^@;
   blank=' ';
   horiz='-';
   vert='|';
   corner='+';
   blick='o';
   ymask=31;

procedure CursorOff;

begin
   write(^['[?25l');  (* ANSI *)
end;

procedure CursorOn;

begin
   write(^['[?25h');  (* ANSI *)
end;

procedure write_at(y,x: integer; a: char); begin
   gotoxy(x+1,y+1);
   write(a);
end;

function cpeek(y,x: integer): char; begin
  cpeek:=screen[y,x];
end;

procedure refresh; var i,j: integer; begin
  clrscr;
  for j:=0 to 23 do
     for i:=0 to 78 do
        write_at(j,i,cpeek(j,i));
end;

function inkey: char; var k: char; begin
   k:=null;
   if keypressed then read(kbd,k);
   inkey:=upcase(k);
end;

procedure pause; begin read(kbd,key) end;

begin {ning of CHICKEN.PAS}

s1:='1';
s2:='2';
repeat
   sc1:=0; sc2:=0;
   again:=true;
   clrscr;
   writeln;
   writeln('Chicken is Copyright (c) 1984 by D. Griffith. It is released');
   writeln('into the public domain for non-commercial use only.');
   writeln;
   writeln('Two players collect points by maneuvering their chickens to the');
   writeln('seeds "',blick,'" that appear pseudo-randomly.  Players are not');
   writeln('to collide either with the other player, the walls or their');
   writeln('own tail.  Any collision gives the other player a point.  If the');
   writeln('players collide head-on, dubofem lose and no points are awarded.');
   writeln;
   writeln('Play may be paused with ^S, stopped with Esc or ^C.');
   writeln;
   writeln('Last changed on 6/13/17 Lee Bradley');
   writeln;
   cursorOn;
   write('Player 1 (E,S,D,X) please enter your name (10 chars): ');
   readln(player1);
   write('Player 2 (I,J,K,M) please enter your name (10 chars): ');
   readln(player2);
   writeln;
   repeat
      write('Speed level (1-fast, 100-slow): ');
      readln(udelay);
   until udelay in [1..100];
   cursorOff;
   repeat
      s1y:=11; s2y:=11; s1x:=30; s2x:=50;
      s1dy:=0; s2dy:=0; s1dx:=1; s2dx:=-1;
      time:=0;
      head1:=5; head2:=5; tail1:=1; tail2:=1; len1:=6; len2:=6;
      quit:=false;
      lose_bill_dubofem:=false; lose_bill1:=false; lose_bill2:=false;
      for i:=tail1 to head1 do
         begin
            chicken1[i]:=s1x shl 5 + s1y;
            chicken2[i]:=s2x shl 5 + s2y;
         end;
      clrscr;
      for j:=1 to 22 do for i:=1 to 77 do screen[j,i]:=' ';
      for i:=1 to 78 do begin;
         screen[0,i]:=horiz;  screen[23,i]:=horiz;
      end;
      for j:=1 to 22 do begin;
         screen[j,0]:=vert;  screen[j,78]:=vert;
      end;
      screen[0,0]:=corner; screen[0,78]:=corner; screen[23,0]:=corner; screen[23,78]:=corner;
      refresh;
   repeat
      key:=inkey;
      if key in [^[,^C] then quit:=true;
      if key in [^S,' '] then pause;
      if (key='E') and (s1dy<>1) then begin s1dy:=-1; s1dx:=0 end;
      if (key='S') and (s1dx<>1) then begin s1dy:=0; s1dx:=-1 end;
      if (key='X') and (s1dy<>-1) then begin s1dy:=1; s1dx:=0 end;
      if (key='D') and (s1dx<>-1) then begin s1dy:=0; s1dx:=1 end;
      if (key='I') and (s2dy<>1) then begin s2dy:=-1; s2dx:=0 end;
      if (key='J') and (s2dx<>1) then begin s2dy:=0; s2dx:=-1 end;
      if (key='M') and (s2dy<>-1) then begin s2dy:=1; s2dx:=0 end;
      if (key='K') and (s2dx<>-1) then begin s2dy:=0; s2dx:=1 end;
      s1y:=s1y+s1dy; s1x:=s1x+s1dx; s2y:=s2y+s2dy; s2x:=s2x+s2dx;
      if (s1y=s2y) and (s1x=s2x) then lose_bill_dubofem:=true;
      if cpeek(s1y,s1x)=blick then
         begin
            sc1:=sc1+1;
            len1:=len1+5;
            screen[s1y,s1x]:=blank;
            time:=0;
            gotoxy(2,24);
            write(sc1:5);
         end;
      if cpeek(s2y,s2x)=blick then
         begin
            sc2:=sc2+1;
            len2:=len2+5;
            screen[s2y,s2x]:=blank;
            time:=0;
            gotoxy(74,24);
            write(sc2:5);
         end;
      if cpeek(s1y,s1x)<>blank then begin lose_bill1:=true; sc2:=sc2+1 end;
      if cpeek(s2y,s2x)<>blank then begin lose_bill2:=true; sc1:=sc1+1 end;
      screen[s1y,s1x]:=s1; screen[s2y,s2x]:=s2; write_at(s1y,s1x,s1); write_at(s2y,s2x,s2);
      chicken1[head1]:=s1x shl 5 + s1y; chicken2[head2]:=s2x shl 5 + s2y;
      head1:=head1+1; if head1>850 then head1:=1;
      if (tail1+len1=head1) or (tail1+len1=head1+850) then
         begin
            j:=chicken1[tail1] and ymask; i:=chicken1[tail1] shr 5;
            screen[j,i]:=blank; write_at(j,i,cpeek(j,i));
            tail1:=tail1+1; if tail1>850 then tail1:=1;
         end;
      head2:=head2+1; if head2>850 then head2:=1;
      if (tail2+len2=head2) or (tail2+len2=head2+850) then
         begin
            j:=chicken2[tail2] and ymask; i:=chicken2[tail2] shr 5;
            screen[j,i]:=blank; write_at(j,i,cpeek(j,i));
            tail2:=tail2+1; if tail2>850 then tail2:=1;
         end;
      time:=time+1;
      lose_bill:=lose_bill_dubofem or lose_bill1 or lose_bill2;
      if time>21 then
         begin
            j:=random(22)+1; i:=random(78)+1;
            if (cpeek(j,i)=blank) then
               begin
                  screen[j,i]:=blick;
                  write_at(j,i,blick);
                  time:=0;
               end;
         end;
      gotoxy(1,1);
      Delay(udelay*1000);
   until lose_bill or quit;
   if not quit then
      begin
         gotoxy(2,24); write(sc1:5);
         gotoxy(74,24); write(sc2:5);
         gotoxy(2,1);
         if lose_bill_dubofem then write('Dubofuse');
         if lose_bill1 then write(player1);
         if lose_bill2 then write(player2);
         write(' lose');
         if not lose_bill_dubofem then write('s');
         write(' bill.');
      end;
   gotoxy(31,1);
   write('Continue? ');
   cursorOn;
   repeat key:=inkey until key in ['Y','N'];
   cursorOff;
   if key='Y' then again:=true else again:=false;
   until not again;
   if quit then begin
      cursorOn;
      gotoxy(31,1); write('Play again? ');
      repeat key:=inkey until key in ['Y','N'];
      if key='N' then quit:=true else quit:=false;
   end;
   cursorOff;
until quit;
cursorOn;
End. {of CHICKEN.PAS}

