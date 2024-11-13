{.HEPage #}
{.PL60}
{.PO2}
{
STARPS.PAS - lrb - 1/25/2008
Operating system: CP/M or Z-System
Compiler: Turbo Pascal 2.0

This program generates PLOT-compatible .VEC files of "star graphs."

Use PLOT33 or ZPLOT to generate .PLT files from the .VEC files.

An Epson-compatible dot matrix printer with graphics capability is needed
to print the .PLT files. Alternatively, you may export the .PLT file to the
DOS environment and use DOSPrinter.EXE, an Epson emulator.

Usage: STARPS p s r

where p is the number of points on the star, s is a "skip" number, r is an
optional radius.
}

PROGRAM main;
LABEL
    foo,bar;
TYPE
    PRIMES = set of 7..101;
    Str80 = string[80];
VAR
    x,y: ARRAY [1..101] of REAL;
    a: REAL;
    i,n: INTEGER;
    ip,jp: INTEGER;
    step,skip: INTEGER;
    radius: REAL;
    points,skips: string[3];
    radiuss: string[4];
    works: string[80];
    code: INTEGER;
    prime: PRIMES;
    work: INTEGER;
    good: BOOLEAN;
 {$I GRAF1.PAS}
 {$I GRAF2.PAS}
 {$I PARAMSTB.INC}
BEGIN
    Writeln(^J'STARPS - 1/25/2008 - lrb');
    prime := [7,11,13,17,19,23,29,31,37,41,43,47];
    prime := prime+[53,59,61,67,71,73,79,83,89,97,101];
    good := True;
    work := length(ParamStr(1));
    work := work*length(ParamStr(2));
    If work <> 0 THEN BEGIN
      points := ParamStr(1);
      Val(points,n,code);
      skips := ParamStr(2);
      Val(skips,skip,code);
      step := skip+1;
      IF NOT (n in prime) THEN good := False;
      IF (skip > (n-3)/2) or (skip < 1) THEN good := False;
    END
    ELSE good := False;
bar:
    IF NOT good THEN BEGIN
      Writeln(^J'Usage : STARPS points skip radius');
      Writeln(^J'points is a prime number in 7..101');
      Writeln('skip is <= (points-3)/2');
      Writeln('radius (optional) is radius of circle');
      Writeln('radius must be <= 0.5 (default = 0.5)');
      GOTO foo;
      END;
    grinit ('ST'+points+'S'+skips+'.VEC');
    radius := 0.5;
    radiuss := ParamStr(3);
    if length(radiuss) <> 0 then Val(radiuss,radius,code);
    if (radius < 0) or (radius > 0.5) then BEGIN
       good := False;
       GOTO bar;
       END;
    FOR i := 1 to n DO BEGIN
      a := 6.28318 * i / n;
      x[i] := cos(a)*radius + radius;
      y[i] := sin(a)*radius + radius;
    END;
    Str(radius:4:2,radiuss);
    works := points+'-point skip-'+skips;
    works := works+' radius '+radiuss+' star';
    Writeln(CON,'Plotting '+works);
    segmnt(x[1],y[1],x[1+step],y[1+step]);
    FOR i := 2 to n DO
    BEGIN
      ip := (step*i - (step - 1)) mod n;
      if ip = 0 then ip := n;
      jp := (ip + step) mod n;
      if jp = 0 then jp := n;
      vector( x[jp],y[jp] );
    END;
    if radius <= 0.45 then gstrng(radius,0.950,works);
    gprint;
    color(0);
    erase;
    color(127);
    Writeln(CON, ^J'Finished plotting!'^G^G);
    Writeln(CON,'ST'+points+'S'+skips+'.VEC ready for ZPLOT (or PLOT33)!');
    grfini;
foo:
END.
