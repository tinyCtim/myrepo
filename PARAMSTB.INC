
Function ParamStr(i:integer):Str80;

{
9/8/07 - This version uses the Transient Buffer Area.
}

Var
  j,p,tba   : Integer;
  current   : Str80;

Begin
  tba := $080;
  j := 1; {init. j}
  While (j <= Mem[$080]) Do Begin
    current[j] := Chr(Mem[tba+j]); {load work string}
    j := j+1;
    End;
  current[0] := Chr(Mem[$080]); {fill in command length}
  {Writeln(j-1);}
  {Writeln(current);}
  p := Pos(' ',current); {locate first space}
  If (i > 0) And (p = 0) Then current := '';
  While (i <> 0) And (p <> 0) Do Begin  {grab the ith parm}
    i := i-1; {decrement parm counter}
    Delete(current,1,p);   {lop off the leading parm}
    p := Pos(' ',current); {locate next space}
  End;
  If (i > 0) And (p = 0) Then current := '';
  If p=0 Then {if at end, use what's left}
    ParamStr := current
  Else
    ParamStr := Copy(current,1,p-1);
           {else, what's at the beginning}
End;   {of what's left}

