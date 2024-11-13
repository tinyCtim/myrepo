
(* revived 6/9/17 - tct *)

program snake;

const
   playerchar   = 'I';
   snakechar    = 'S';
   moneychar    = '$';
   doorchar     = '#';

   upcommand    = 'U';
   downcommand  = 'N';
   leftcommand  = 'H';
   rightcommand = 'J';
   quitcommand  = 'Q';

   snakelength = 5;
   height      = 23;
   width       = 79;
   moneyworth  = 25;

type
   coordinate = record
      x : integer;
      y : integer;
      end;
  snaketype = array[1..snakelength] of coordinate;
  thing = (playerthing, snakething, moneything, doorthing, emptything, scorething);

var
   snake : snaketype;
   player, money, door : coordinate;
   score : integer;
   left, eaten : boolean;

   screen : array[0..width] of array[0..height] of thing;

   lookslike : array[thing] of char;

procedure CursorOff;

begin
   write(^['[?25l');  (* ANSI *)
end;

procedure CursorOn;

begin
   write(^['[?25h');  (* ANSI *)
end;

(* returns a random integer between min and max *)

function rand(min, max: integer) : integer;

begin
   rand := min + random(max-min+1);
end;

procedure instructions;

var
   answer : char;
begin
  writeln('SNAKE.PAS 6/9/17');
  write('Do you want instructions? ');
  read(trm,answer);
  writeln;
  while not(upcase(answer) in ['Y','N']) do
     begin
     writeln('Please enter Yes or No.');
     read(trm,answer);
     writeln;
     end;
  if upcase(answer) = 'Y' then
     begin
     writeln;
     writeln('The object of SNAKE is to get as much money ($) to the door (#) as possible.');
     writeln('The snake tries to prevent you (I). As you get more money, he tries');
     writeln('more and more successfully. You move up, down, left, and right');
     writeln('by typing U, N, H, and J respectively. You cannot move diagonally');
     writeln('though the snake can. You may quit with Q.');
     writeln;
     write('Type any key to continue ');
     read(trm,answer);
     end;
end;

procedure initialize;

var
   x, y : integer;
begin
   instructions;
   CursorOff;
   for x := 0 to width do
      for y := 0 to height do
         screen[x][y] := emptything;
   randomize;
   lookslike[snakething] := snakechar;
   lookslike[playerthing] := playerchar;
   lookslike[moneything] := moneychar;
   lookslike[emptything] := ' ';
   lookslike[doorthing] := doorchar;
   left := false;
   eaten := false;
   score := 0;
   for x := 0 to 10 do
      screen[x,0] := scorething;
   ClrScr;
end;

(* returns true if the position is valid and empty *)

function freespot(pos : coordinate) : boolean;

begin
   if (pos.x in [0..width]) and (pos.y in [0..height]) then
      freespot := screen[pos.x, pos.y] = emptything
   else freespot := false;
end;

(* assigns the coordinates of a position on the screen that is not being used *)

procedure makespace(var newpos : coordinate; forwhat : thing);

begin
   with newpos do
      begin
         repeat
            x := rand(0, width - 1);
            y := rand(0, height - 1);
         until freespot(newpos);
         gotoxy(x, y);
         write(lookslike[forwhat]);
         screen[x, y] := forwhat;
      end;
end;

(*
finds a free coordinate adjacent to the argument coordinate
and places the thing there
*)

procedure placenearby(var near, coord : coordinate);

var deltax, deltay : integer;

begin
   repeat
      repeat
         deltax := rand(-1,1);
         deltay := rand(-1,1);
      until (deltax <> 0) or (deltay <> 0);
      near.x := coord.x + deltax;
      near.y := coord.y + deltay;
   until (freespot(near) or ((near.x = player.x) and (near.y = player.y)));
   gotoxy(near.x, near.y);
   screen[near.x, near.y] := snakething;
   write(lookslike[snakething]);
end;

(*
removes whatever is at the coordinates from the terminal screen
and the array screen
*)

procedure remove(pos : coordinate);

begin
   gotoxy(pos.x, pos.y);
   write(' '); 
   screen[pos.x, pos.y] := emptything;
end;

procedure takegold;

begin
   score := score + moneyworth;
   gotoxy(0,0);
   write('$',score);
   screen[money.x, money.y] := emptything;
   makespace(money, moneything);
end;

(* position all items in game making sure none overlap *)

procedure placeobjects;

var
   snakebody : integer;

begin
   makespace(snake[1], snakething);
   for snakebody := 2 to snakelength do
      placenearby(snake[snakebody], snake[snakebody - 1]);
   makespace(player, playerthing);
   makespace(money, moneything);
   makespace(door, doorthing);
end;

(*
read player's move from the keyboard, not input so letter
is not echoed and mess up the display
*)

procedure playermove;

var
   command : char;
   oldpos : coordinate;

begin
   oldpos := player;
   read(kbd, command);
   command := upcase(command);
   with player do
      begin
      case command of
         upcommand : if y > 0 then y := y - 1;
         downcommand : if y < height then y := y + 1;
         leftcommand : if x > 0 then x := x - 1;
         rightcommand : if x < width then x := x + 1;
         quitcommand : left := true;
      end;   
      if screen[x, y] = scorething then
         player := oldpos
      else
         begin
         remove(oldpos);
         if (player.x = money.x) and (player.y = money.y) then
            takegold
         else if (player.x = door.x) and (player.y = door.y) then
             left := true;
         gotoxy(x, y);
         write(playerchar);
         screen[x, y] := playerthing;
         end;
   end;
end;

(*
used by snakemove to figure out which way is the direction
toward the player
*)

function sign(x : integer) : integer;

begin
   if x = 0 then
      sign := 0
   else if x > 0 then
      sign := 1
   else
      sign := -1;
end;

(* snake moves randomly at first then more directly toward player *)

procedure snakemove;

var
   newpos : coordinate;
   bodypart : integer;

begin
   if rand(0, score) < 100 then
      placenearby(newpos, snake[1])
   else
      begin
      newpos.x := snake[1].x + sign(player.x - snake[1].x);
      newpos.y := snake[1].y + sign(player.y - snake[1].y);
      if (screen[newpos.x, newpos.y] = emptything) or
         ((newpos.x = player.x) and (newpos.y = player.y)) then
         begin
         gotoxy(newpos.x, newpos.y);
         write(snakechar);
         screen[newpos.x, newpos.y] := snakething;
         end
      else
         placenearby(newpos, snake[1]);
      end;
   remove(snake[snakelength]);
   if (newpos.x = player.x) and (newpos.y = player.y) then
      eaten := true;
   for bodypart := snakelength downto 2 do
      begin
      snake[bodypart] := snake[bodypart -1];
      if (snake[bodypart].x = player.x) and (snake[bodypart].y = player.y) then
         eaten := true;
      end;
   snake[1] := newpos;
end;

begin (* main *)
   initialize;
   placeobjects;
   repeat
      playermove;
      if not left then
         snakemove;
   until left or eaten;
   gotoxy(0, height);
   writeln;
   if left then
      writeln('You have escaped with $', score)
   else
      writeln('The snake has eaten you.');
   CursorOn;
end.

