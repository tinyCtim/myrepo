10   '
20   ' TCAP.BAS, Version 2.4
30   '
40   ' Original Idea: Biff Bueffel
50   ' Date: 7 May 90
60   ' By: Lee Bradley 
70   '
80   ' TCAP began life as a sample program to show how Basic code 
90   ' and the proper use of the linker can be used to capture 
100  ' terminal capability data if available on a Z-System 
110  ' computer. It seems to have evolved into a fairly handy 
120  ' (albeit still simple) Z-System viewing tool.
130  '
140  ' TCAP determines if ZCPR3 is running and if so, gathers 
150  ' environment and tcap data, signs on, displays cpu speed, 
160  ' terminal id and ...
170  '
180  ' if the wheel is set ...
190  '
200  ' a command line which includes a help selection.  From here, 
210  ' the user may select various memory display options, 
220  ' (forward, backward, specific address, character, hex or 
230  ' both) or toggle the quiet flag or reset the wheel byte.  
240  ' Pressing the return key, the reset wheel key (W) or any key 
250  ' other than the memory display selection keys (>,<,A,C,H,B), 
260  ' the quiet toggle key (Q) or the help key (/) will quit the 
270  ' program.
280  '
290  ' Lee Bradley, Sysop, Z-Node #12 (203) 665-1100
300  '
310  ' To compile and link:
320  '
330  ' BASCOM =TCAP24/Z/E
340  ' L80 Z3HDR,TCAPxx,TCAPxx/N/E
350  '
360  ' where Z3HDR.REL is the Microsoft REL form of:
370  '
380  '   CSEG
390  '   DEFB 'Z3ENV'
400  '   DEFB 1
410  '   DEFW 0
420  '   END
430  '
440 ON ERROR GOTO 1560
450 VER$="2.4"
460 D$="C" ' Set display mode to char ("H" would give hex, "B", both) 
470 GOSUB 1740 ' Get environment address
480 TINDEX=0:GOSUB 1970:TID$=X$ ' Get terminal id string
490 TINDEX=1:GOSUB 1970:CL$=X$  ' clear screen
500 TINDEX=4:GOSUB 1970:SO$=X$  ' start highlighting
510 TINDEX=5:GOSUB 1970:SE$=X$  ' stop highlighting
520 GOSUB 2680 ' Get wheel address
530 GOSUB 2690 ' Get wheel status
540 GOSUB 2700 ' Get cpu speed
550 PRINT CL$+ "TCAP, Version "+VER$
560 GOSUB 2670 ' Get quiet flag
570 PRINT:PRINT SO$+"Cpu Speed:"+SE$;MHZ;"MHz "+SO$+" Terminal:"+SE$+" "+TID$
580 IF WHEEL=0 THEN END ELSE 910
590 PRINT "Enter hex address or <ret> for Z3 env ("+HEX$(ENV)+") ";:ADR$=""
600 IF LEN(ADR$)=4 THEN PRINT CL$;:GOTO 670
610 IN$=INKEY$:IF LEN(IN$)=0 THEN 610
620 IF IN$=CHR$(13) THEN PRINT CL$;:GOTO 670
630 IF (IN$>="a" AND IN$<="f") THEN IN$=CHR$(ASC(IN$)-32) ' Upper case
640 IF (IN$>="0" AND IN$<="9") OR (IN$>="A" AND IN$<="F") THEN 660
650 PRINT CHR$(7);:GOTO 600
660 PRINT IN$;:ADR$=ADR$+IN$:GOTO 600
670 IF LEN(ADR$)=0 THEN ADR$=HEX$(ENV)
680 GOSUB 1230 ' Convert hex to decimal
690 '
700 ' Display selected sector(s) entry point
710 '
720 ULIM=15:IF D$="B" THEN ULIM=7:PASS=1
730 FOR I=0 TO ULIM
740 IF I=0 OR I=8 THEN GOSUB 1160 ' Output heading line
750 FOR J=0 TO 15
760 IF J<>0 THEN 800
770 ADR$=HEX$(ADR+16*I)
780 IF LEN(ADR$)<>4 THEN ADR$="0"+ADR$:GOTO 780
790 PRINT SO$+ADR$+SE$+"           ";
800 BYTE=PEEK(ADR+16*I+J)
810 BYTEHEX$=HEX$(BYTE)+" "
820 IF LEN(BYTEHEX$)=2 THEN BYTEHEX$="0"+BYTEHEX$
830 BYTECHR$=" . ":IF BYTE>=32 AND BYTE<=126 THEN BYTECHR$=" "+CHR$(BYTE)+" "
840 IF D$="H" THEN BYTE$=BYTEHEX$:GOTO 870
850 IF D$="C" THEN BYTE$=BYTECHR$:GOTO 870
860 IF PASS=1 THEN BYTE$=BYTEHEX$ ELSE BYTE$=BYTECHR$
870 PRINT BYTE$;
880 NEXT:PRINT:NEXT
890 IF D$="B" AND PASS=1 THEN PASS=2:GOTO 730
900 '
910 ' Build command prompt
920 '
930 IF D$="C" THEN MODE$="H,B,"
940 IF D$="H" THEN MODE$="C,B,"
950 IF D$="B" THEN MODE$="H,C,"
960 CMD$="(/ for help) "
970 IF QUIET=0 THEN CMD$="(>,<,A,"+MODE$+"W,Q,X or / for help) "
980 PRINT:PRINT "Cmd "+CMD$;
990 A$=INKEY$:IF LEN(A$)=0 THEN 990
1000 IF A$=CHR$(13) THEN 1140
1010 IF D$="B" THEN INCR=128 ELSE INCR=256
1020 IF A$=">" OR A$="." THEN ADR=ADR+INCR:PRINT CL$;:GOTO 700
1030 IF A$="<" OR A$="," THEN ADR=ADR-INCR:PRINT CL$;:GOTO 700
1040 IF A$="A" OR A$="a" THEN PRINT CL$;:GOTO 590
1050 IF A$="/" OR A$="?" THEN PRINT CL$;:GOSUB 1340:GOTO 900
1060 IF NOT (A$="Q" OR A$="q") THEN 1090
1070 IF QUIET<>0 THEN POKE ENV+&H28,0 ELSE POKE ENV+&H28,1
1080 GOTO 550 ' Loop back to beginning
1090 IF NOT (A$="W" OR A$="w") THEN 1110
1100 POKE WHLA,0:GOTO 1140
1110 IF (A$="C" OR A$="c") THEN D$="C":PRINT CL$;:GOTO 700
1120 IF (A$="H" OR A$="h") THEN D$="H":PRINT CL$;:GOTO 700
1130 IF (A$="B" OR A$="b") THEN D$="B":PRINT CL$;:GOTO 700
1140 PRINT CL$
1150 END
1160 '
1170 ' Heading line subroutine
1180 '
1190 PRINT:PRINT "              "+SO$;
1200 FOR K=0 TO 15:PRINT " 0"+HEX$(K);:NEXT:PRINT SE$
1210 PRINT
1220 RETURN
1230 '
1240 ' Convert hex string ADR$ to decimal number ADR
1250 '
1260 IF LEN(ADR$)<4 THEN ADR$="0"+ADR$:GOTO 1260
1270 ADR=0
1280 FOR I=0 TO 3
1290 ASCII=ASC(MID$(ADR$,I+1,1))-&H30
1300 IF ASCII>9 THEN ASCII=ASCII-7
1310 ADR=ADR+ASCII*16^(3-I)
1320 NEXT
1330 RETURN
1340 '
1350 ' Help subroutine
1360 '
1370 PRINT CL$
1380 PRINT "            "+SO$+"Memory Viewing Commands"+SE$
1390 PRINT
1400 PRINT "> or .  show the next" INCR "bytes, from hex "+HEX$(ADR+INCR) 
1410 PRINT "< or ,  show the previous" INCR "bytes, from hex "+HEX$(ADR-INCR)
1420 PRINT "A or a  enter a start address to view"
1430 PRINT     
1440 PRINT "H or h  hex display"
1450 PRINT "C or c  character display"
1460 PRINT "B or b  both hex and character display"
1470 PRINT
1480 PRINT "            "+SO$+"Other Commands"+SE$
1490 PRINT
1500 PRINT "Q or q  toggle quiet state, clear display"
1510 PRINT "W or w  turn wheel off and quit"
1520 PRINT
1530 PRINT "X or x  (or <ret> etc.) quit"
1540 RETURN
1550 '
1560 ' Error handler
1570 '
1580 PRINT "Error " ERN "on line" ERL:PRINT " Aborting ...":END
1590 '
1600 ' Z3BAS.LIB
1610 '
1620 ' Version: 1.0.  Date: 6/7/90
1630 ' Author: Lee Bradley, Sysop, Z-Node 12, 203-665-1100
1640 '
1650 ' Include these routines in your program and reference them
1660 ' when you need to determine environment address, load a tcap 
1670 ' string, position the cursor, determine the status of the 
1680 ' wheel byte, quiet flag etc.
1690 '
1700 ' ---
1710 ' Load ENV with environment address.
1720 ' ---
1730 '
1740 IF CHR$(PEEK(&H103))+CHR$(PEEK(&H104))="Z3" THEN 1810
1750 ' ==> NOTE! Edit &H value below. Will be used under MBASIC.
1760 ENV=&HE780+65536! ' Note need to make positive by adding 2^16
1770 ENV1=PEEK(ENV+&H1B)+256*PEEK(ENV+&H1C)
1780 IF ENV1=ENV THEN 1880
1790 PRINT:PRINT "ZCPR3 required. If running ZCPR3, change statement"
1800 PRINT "ENV=&H ...  above.":SYSTEM
1810 IF PEEK(&H10A)<> 0 THEN 1840
1820 PRINT "If not ZCPR3 version ZCPR33+ you must use Z3INS "
1830 PRINT "ZCPR33+ was not found. ":ENV=0:GOTO 1880
1840 ENV=PEEK(&H109)+256*PEEK(&H10A)
1850 ENV1=PEEK(ENV+&H1B)+256*PEEK(ENV+&H1C)
1860 IF ENV1=ENV THEN 1880
1870 PRINT:PRINT "Environment self-reference error detected":END
1880 RETURN
1890 '
1900 ' ---
1910 ' Load X$ with tcap string based on TINDEX, a tcap string "index"
1920 ' and ENV, the environment address.
1930 ' X$ will hold terminal id string if TINDEX is 0
1940 ' X$ will hold clear screen string if TINDEX is 1. Etc.
1950 ' ---
1960 '
1970 J=128                  ' Start at beginning of tcap segment
1980 IF TINDEX=0 THEN 2070 ' No need to skip anything if looking for id
1990 J=J+16+4+3             ' Get past id, arrow and delay bytes 
2000 IF TINDEX=1 THEN 2070 ' No need to skip any more if clear scr wanted
2010 FOR I=1 TO TINDEX-1    ' Skip the strings we don't want
2020 IF CHR$(PEEK(ENV+J))<>"\" THEN 2040     ' Catch literals
2030 J=J+2                                    ' advance to next character 
2040 IF PEEK(ENV+J)<>0 THEN J=J+1:GOTO 2020  ' Loop till null found
2050 J=J+1                  ' Advance and move to next string
2060 NEXT
2070 ' Build tcap string
2080 X$=""                  ' Null out work string 
2090 IF CHR$(PEEK(ENV+J))<>"\" THEN 2110     ' Catch literals
2100 J=J+1:GOTO 2140                         ' Advance to literal
2110 IF J=128+13 AND TINDEX=0 THEN RETURN     ' Get out if id complete
2120 IF PEEK(ENV+J)<>0 THEN 2140             ' If null
2130 RETURN                                   ' return
2140 X$=X$+CHR$(PEEK(ENV+J)):J=J+1:GOTO 2090 ' else, grab it and loop  
2150 '
2160 ' ---
2170 ' Cursor motion macro interpreter
2180 ' Input: R,C,CM$ (row,col,cursor motion macro)
2190 ' Output: CMO$ (string to output to the terminal)
2200 ' Ref: ZCPR3 The Manual, Richard Conn, Ch 22.
2210 ' ---
2220 '
2230 DIM OFFSET(2),PREINFIX$(2),RC(2),CMD$(2)
2240 WK$="":PCTR=0:I1=0:OFFSET(1)=0:OFFSET(2)=0 ' Initialize
2250 PREINFIX$(1) = "":PREINFIX$(2) = "":RC(1)=R:RC(2)=C ' Initialize 
2260 I1=I1+1:IF I1>LEN(CM$) THEN 2570  ' Top of loop
2270 CMC$=MID$(CM$,I1,1)                ' Load cursor motion macro char.
2280 IF CMC$<>"%" THEN 2540            ' If not a %, tack onto work string
2290 I1=I1+1:CMC$=MID$(CM$,I1,1)        ' Advance
2300 RI=INSTR("RrIi",CMC$)
2310 IF RI=1 OR RI=2 THEN CB4R$="ON":GOTO 2260 ' Handle R,I commands
2320 IF RI=3 OR RI=4 THEN HOME=1:GOTO 2260
2330 PCTR=PCTR+1                      ' Update % counter
2340 PREINFIX$(PCTR)=WK$              ' Save work string 
2350 WK$=""                           ' Null out for future build
2360 IF CMC$<>"." THEN 2390          ' Binary ?
2370 CMD$(PCTR)=CHR$(RC(PCTR)+HOME)
2380 GOTO 2260   ' Loop
2390 D23=INSTR("D23d",CMC$):IF D23=0 THEN 2450 ' Ascii?
2400 CMD$(PCTR)=MID$(STR$(RC(PCTR)+HOME),2)
2410 IF LEN(CMD$(PCTR))=1 AND D23=2 THEN CMD$(PCTR)="0"+CMD$(PCTR) ' Fix
2420 IF LEN(CMD$(PCTR))=1 AND D23=3 THEN CMD$(PCTR)="00"+CMD$(PCTR)
2430 IF LEN(CMD$(PCTR))=2 AND D23=3 THEN CMD$(PCTR)="0"+CMD$(PCTR)
2440 GOTO 2260  ' Loop
2450 IF CMC$<>"+" THEN 2500  ' Offset?
2460 I1=I1+1:CMC$=MID$(CM$,I1,1)
2470 OFFSET(PCTR)=ASC(CMC$)
2480 CMD$(PCTR)=CHR$(RC(PCTR)+HOME+OFFSET(PCTR))
2490 GOTO 2260  ' Loop
2500 IF CMC$<>">" THEN PRINT "Error in cursor motion macro ... ":END
2510 I1=I1+1:CMC1$=MID$(CM$,I1,1):I1=I1+1:CMC$=MID$(CM$,I1,1)
2520 IF CHR$(RC(PCTR))>CMC1$ THEN 2470 ELSE 2480
2530 ' Compute conditional offset, then use "+" code
2540 ' We have a character that's not part of a % command. Just add it
2550 WK$=WK$+CMC$
2560 GOTO 2260  ' Loop
2570 ' All done. Anything left (in WK$) is the postfix part.
2580 IF CB4R$="ON" THEN SWAP CMD$(1),CMD$(2)  ' If col before row, swap
2590 CMO$=PREINFIX$(1)+CMD$(1)+PREINFIX$(2)+CMD$(2)+WK$  ' Build CMO$
2600 RETURN
2610 '
2620 ' ---
2630 ' Load variables (QUIET, WHEEL etc.) based on ENV,
2640 ' the environment address. 
2650 ' ---
2660 '
2670 QUIET=PEEK(ENV+&H28):RETURN
2680 WHLA=PEEK(ENV+&H29)+256*PEEK(ENV+&H2A):RETURN
2690 WHEEL=PEEK(WHLA):RETURN
2700 MHZ=PEEK(ENV+&H2B):RETURN
2710 MAXD=PEEK(ENV+&H2C):RETURN
2720 MAXU=PEEK(ENV+&H2D):RETURN
2730 DUOK=PEEK(ENV+&H2E):RETURN
2740 '
