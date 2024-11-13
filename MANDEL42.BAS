100 ' MANDEL42.BAS
110 ' by Larry Schnitger  Jan 4, 1992,  ZI/TEL BBS (617) 965-7046
120 '
130 ' Credit goes to Lee Bradley, Z-Node #12, (203) 665-1100
140 ' (or should it be the blame?) for getting me started
150 ' on this program by writing the earlier MANDEL version.
160 '
170 ' See the associated MANDEL4x.DOC file for an explanation of
180 ' some of the techniques and advanced features in this program.
190 '
200 DEFINT I-N  'all variables beginning with I thru N are integers by default
210 '
220 DEF FNSX$(I)=MKI$(INT(XF*(IB+I+1)))  ' scale col I, bias right IB col's
230 DEF FNSY$(J)=MKI$(INT(YF*(JB+J+1)))  ' scale row J, bias up JB rows
240 DEF FND$(I1, J1, I2, J2)="D"+FNSX$(I1)+FNSY$(J1)+FNSX$(I2)+FNSY$(J2) 'draw line
250 '
260 DIM Y(572) 'calc cy values once for multiple use later
270 DIM XO(250): DIM YO(250)  'iteration values of x and y  (orbits of Z(n) )
280 '
290 PRINT: PRINT "MANDEL, Version 4.2": PRINT
300 INPUT "Starting x:  "; XS: INPUT "Ending   x:  "; XE: PRINT
310 INPUT "Starting y:  "; YS: INPUT "Ending   y:  "; YE: PRINT
320 INPUT "Num x steps (478 max)"; NX
330 NY=INT(1.2*NX*(YE-YS)/(XE-XS)+.5)  'auto value for right size
340 PRINT "Num y steps (572 max), auto-scale ="; NY;: INPUT NY: PRINT
350 DELX=(XE-XS)/NX: DELY=(YE-YS)/NY: IB=0: JB=572-NY  ' Plot in upper left
360 PRINT "dx dy", DELX, DELY: PRINT
370 INPUT "Maximum iteration  (250 max)"; MAXIT: PRINT
380 CN$=CHR$(127)  'near point color = black
390 INPUT "Want black and grey plots (y/n)"; A$: PRINT
400 IF (A$="Y") OR (A$="y") THEN CM$=CHR$(63+32) ELSE CM$=CN$  'set M pt color
410 '
420 XF=32767/479: YF=32767/573  'NOTE: denom's are maxx maxy from PLOT program
430 FOR J=0 TO NY: Y(J)=((NY-J)*YS+J*YE)/NY: NEXT J  'calc Y's once
440 '
450 OPEN "O", #1, "MDL4.VEC"
460 GOSUB 2000  'out params to plot file
470 PRINT #1, "C"; CHR$(0); "E";  'erase plot to white
480 PRINT #1, "C"; CN$;: CC$=CN$  'set current color to black
490 GOSUB 3000  'add corners to plot
500 '
510 DELT=.5*SQR(DELX*DELX+DELY*DELY)  'distance cut-off for near M-point
520 DELT2=DELT*DELT  'faster if use squares for tests
530 HUGE=100000!  'HUGE is size limit for iterating Z
540 OV=2E+10  'OV is overflow value for deriv's
545 SD2=DELT2/2   'small dist so deriv underflow forced to plot as near point
550 EP=.001  'used to detect iteration cycling
560 SKIPVAL=16*(DELY+DELT)*(DELY+DELT)  'used for testing if points can be skipped over
570 '
580 FOR I=0 TO NX: CX=((NX-I)*XS+I*XE)/NX
590 NDOTS=0 'begin column calc with 0 dots in a row
600 PRINT USING "column ### of ###    X = +#.######"; I; NX; CX
610 P$="P"+FNSX$(I)  'prefix string for point plot since same for whole column
620 '
630 FOR J=0 TO NY: CY=Y(J)
640 ' >>> Here's where I checked the drive and turned it off if necessary <<<
650 GOSUB 1000  'calc distance from (CX, CY) to nearest M point
660 '
670 IF DIST2>DELT2 THEN GOTO 730  'not near an M pt
680 '
690 IF DIST2=0 THEN C$=CM$ ELSE C$=CN$  'on or near an M pt, select color
700 IF CC$<>C$ THEN GOSUB 4000: CC$=C$: PRINT #1, "C"; CC$;  'print old color dots, change color
710 NDOTS=NDOTS+1: LASTDOT=J: GOTO 750  'add new dot and end point
720 '
730 GOSUB 4000  'not an M point, plot accumulated dots
740 IF DIST2>SKIPVAL THEN J=J+INT((SQR(DIST2)/4-DELT)/DELY)  'skip to next possible point-1
750 NEXT J
760 '
770 IF NDOTS>0 THEN GOSUB 4000  'last J was M-point, so plot final dot or line
780 NEXT I
790 '
800 PRINT #1, "OQ";: CLOSE 1   'output image and quit PLOT commands
810 PRINT CHR$(7)  'run complete, beep terminal
820 END
997 '
998 ' Subroutines follow
999 ' ==================
1000 '
1010 ' Distance estimator method for points near M-set
1020 '
1030 X=0: Y=0: X2=0: Y2=0: DIST2=0: XO(0)=0: YO(0)=0: N=0
1040 '
1050 WHILE (N<MAXIT) AND ((X2+Y2)<=HUGE)  'iterate Z(n+1)=Z(n)^2+C and save orbits
1060 T=X2-Y2+CX: Y=2*X*Y+CY: X=T: X2=X*X: Y2=Y*Y: N=N+1
1070 XO(N)=X: YO(N)=Y
1080 IF ABS(X-XO(N\2))>EP THEN 1110  'x values too different
1090 IF ABS(Y-YO(N\2))>EP THEN 1110  'y values too different
1100 GOTO 1240  'apparently cycling, so M-point. skip rest of iterations
1110 WEND
1120 '
1130 Z2=X2+Y2: IF Z2<=HUGE THEN 1240  'didn't escape, so M-pt.  dist still 0
1140 XD=0: YD=0: K=0: IFLAG=0  ' 0 = false
1150 '
1160 WHILE (K<N) AND (NOT IFLAG)  'calc derivatives: Z'(k+1)=2*Z(k)*Z'(k)+1
1170 T=2*(XO(K)*XD-YO(K)*YD)+1
1180 YD=2*(YO(K)*XD+XO(K)*YD)
1190 XD=T: K=K+1
1200 IF (ABS(XD)+ABS(YD))>OV THEN DIST2=SD2: IFLAG=-1 'force near pt,  -1 = true
1210 WEND
1220 '
1230 IF NOT IFLAG THEN T=LOG(Z2): DIST2=T*T*Z2/(XD*XD+YD*YD)
1240 RETURN
2000 '
2010 ' Put param info in plot file
2020 '
2030 PRINT #1, "T"
2035 PRINT #1, "        Mandelbrot plot via MANDEL42": PRINT #1,
2040 PRINT #1, USING "X : +#.###### to +#.###### in #.###### steps"; XS; XE; DELX
2050 PRINT #1, USING "Y : +#.###### to +#.###### in #.###### steps"; YS; YE; DELY
2060 PRINT #1, "   nx ="; NX; "   ny ="; NY; "   max iter ="; MAXIT
2070 PRINT #1, CHR$(26)  'end-of-file if .VEC typed
2080 PRINT #1, CHR$(0);  'terminate text to plotter
2090 RETURN
3000 '
3010 ' Plot 4 corners
3020 '
3030 PRINT #1, FND$( 0, NY,    6, NY); FND$( 0, NY,  0, NY-7);  'ulc
3040 PRINT #1, FND$(NX, NY, NX-6, NY); FND$(NX, NY, NX, NY-7);  'urc
3050 PRINT #1, FND$( 0,  0,    6,  0); FND$( 0,  0,  0,    7);  'llc
3060 PRINT #1, FND$(NX,  0, NX-6,  0); FND$(NX,  0, NX,    7);  'lrc
3070 RETURN
4000 '
4010 ' Plot a dot or draw a line based on num of dots
4020 '
4030 IF NDOTS=0 THEN RETURN  'nothing to plot
4040 '
4050 IF NDOTS=1 THEN PRINT #1, P$; FNSY$(LASTDOT);: GOTO 4170  'plot a point
4060 '
4070 'must be a line...
4080 'case 1 - starts after row 0.  draw NDOTS+1 pts top down
4090 IF LASTDOT>=NDOTS THEN PRINT #1, FND$(I, LASTDOT, I, LASTDOT-NDOTS);: GOTO 4170
4100 '
4110 'case 2 - ends before last row.  draw NDOTS+1 pts bottom up
4120 IF LASTDOT<NY THEN PRINT #1, FND$(I, LASTDOT-NDOTS+1, I, LASTDOT+1);: GOTO 4170
4130 '
4140 'case 3 - full length line.  draw top down + point at 0
4150 PRINT #1, FND$(I, LASTDOT, I, 0); P$; FNSY$(0);
4160 '
4170 NDOTS=0: RETURN  'reset dot count

