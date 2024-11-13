10 '
20 '  BUZZ.BAS
30 '
40 '  Buzz Phrase Generator, Alan W. Hathway, January 1985
50 '  from "STARTING FORTH", by Leo Brodie
60 '
70 '  Updated on 02/15/90 at 16:57 by Lee Bradley
80 '  Small Computer Support, 24 East Cedar Street, Newington, CT 06111
90 '  (203) 666-3139
100 '
110 ' Changed dialog slightly, renamed from BUZZ.ASC, changed
120 ' random number generation slightly and RENUM bered source.  
130 ' Made "CLEAR SCREEN" a 24 line feed routine.  Fixed spelling
140 ' of "management", "commitment". Added pauses at 4th, 8th buzz 'graphs.
150 ' Screen, Printer or Both selection now does not require user to
160 ' hit the RETURN key.  Compiled with BASCOM/L80.  Added personal credits.
170 '
180 OPTION BASE 0
190 DIM OPN$(7),FILL0$(3),FILL1$(3),FILL2$(3),FILL3$(3),FILL4$(3)
200 DIM ADJ1$(15),ADJ2$(15),NOUN$(15),SENT$(8)
210 DEFINT H-M,P
220 GOSUB 1620 : REM CLEAR_SCREEN
230 PRINT:PRINT"BUZZ, A Random Report Generator"
240 PRINT "Alan W. Hathway, January 1985"
250 PRINT "Minor updates by Lee R. Bradley, February 15, 1990"
260 PRINT
270 GOSUB 1650 : REM START_RANDOM
280 PRNT = 0
290 PRINT"Send Output to Screen, Printer or Both."
300 PRINT
310 IF NOT (PRNT < 1 OR PRNT > 3) THEN 360
320 PRINT "Enter 1 (Screen), 2 (Printer) or 3 (Both) ";
330 PRNT$ = INKEY$ : IF PRNT$ = "" THEN 330
340 PRNT = VAL(PRNT$)
350 GOTO 310 : REM END WHILE
360 GOSUB 1220 : REM INIT_DAT
370 STOPKEY$=""
380 IF STOPKEY$ = "X" OR STOPKEY$ = "x" THEN 490
390 FOR I=0 TO 7
400 IF I<>4 THEN 430
410 PRINT "Press SPACE BAR to Continue ... ";
420 IF INKEY$="" THEN 420
430 GOSUB 520 : REM CREATE_SENT
440 GOSUB 890 : REM PRNT_SENT
450 NEXT I
460 PRINT "Press SPACE BAR to Continue or X to exit ... ";
470 STOPKEY$=INKEY$ : IF STOPKEY$ = "" THEN 470
480 GOTO 380 : REM END WHILE
490 PRINT:PRINT"Done."
500 SYSTEM
510 REM SUB CREATE_SENT
520 SENT$(0)=OPN$(I)
530 SENT$(1)=FILL0$(INT(4*RND))
540 SENT$(3)=FILL1$(INT(4*RND))
550 SENT$(5)=FILL2$(INT(4*RND))
560 SENT$(7)=FILL3$(INT(4*RND))
570 FOR K=2 TO 8 STEP 2
580 GOSUB 850 : REM PHRASE
590 SENT$(K)=DUMMY$
600 NEXT K
610 SENT$(8)=SENT$(8)+"."
620 LO=0:HI=1
630 IF NOT (HI <= 8) THEN 750
640 SENT$(LO)=SENT$(LO)+" "+SENT$(HI)
650 IF NOT (LEN(SENT$(LO)) <= 72) THEN 680
660 HI = HI + 1
670 GOTO 730 : REM ELSE
680 DUMMY$=SENT$(LO)
690 GOSUB 770 : REM BLANK_POINTER
700 SENT$(LO+1)=RIGHT$(SENT$(LO),LEN(SENT$(LO))-HPOINT)
710 SENT$(LO)=LEFT$(SENT$(LO),HPOINT)
720 LO=LO+1:HI=HI+1
730 REM END IF
740 GOTO 630 : REM END WHILE
750 RETURN
760 REM SUB BLANK_POINTER
770 HIPOINT=1
780 IF NOT (HIPOINT <= 72 AND HIPOINT > 0) THEN 830
790 HPOINT = HIPOINT
800 HIPOINT=HIPOINT+1
810 HIPOINT=INSTR(HIPOINT,DUMMY$," ")
820 GOTO 780 : REM END WHILE
830 RETURN
840 REM SUB PHRASE
850 DUMMY$=ADJ1$(INT(15*RND))+" "+ADJ2$(INT(15*RND))
860 DUMMY$=DUMMY$+" "+NOUN$(INT(15*RND))
870 RETURN
880 REM SUB PRNT_SENT
890 ON PRNT GOTO 910,930,950
900 GOTO 970 : REM CASE 1
910 GOSUB 1000 : REM PUT_CRT
920 GOTO 970 : REM CASE 2
930 GOSUB 1070 : REM PUT_PRNTR
940 GOTO 970 : REM CASE 3
950 GOSUB 1000 : REM PUT_CRT
960 GOSUB 1070 : REM PUT_PRNTR
970 REM END ON
980 RETURN
990 REM SUB PUT_CRT
1000 IF NOT (I=0) THEN 1020
1010 GOSUB 1620 : REM CLEAR_SCREEN
1020 REM END IF
1030 FOR L=0 TO LO : PRINT SENT$(L) : NEXT L
1040 PRINT
1050 RETURN
1060 REM SUB PUT_PRNTR
1070 IF NOT (I=0) THEN 1100
1080 LPRINT:LPRINT:LPRINT:LPRINT
1090 SLCOUNT=4
1100 REM END IF
1110 FOR L=0 TO LO : LPRINT SENT$(L) : NEXT L
1120 LPRINT:LPRINT
1130 SLCOUNT=SLCOUNT+LO+1
1140 IF NOT (I=7) THEN 1190
1150 IF NOT (SLCOUNT < 67) THEN 1190
1160 LPRINT CHR$(10);
1170 SLCOUNT=SLCOUNT+1
1180 GOTO 1150 : REM END WHILE
1190 REM END IF
1200 RETURN
1210 REM SUB INIT_DAT
1220 PRINT:PRINT"Initializing arrays."
1230 FOR M=0 TO 7 : READ OPN$(M) : NEXT M
1240 DATA "In this paper we will demonstrate that"
1250 DATA "On the one hand, studies have shown that"
1260 DATA "On the other hand, however, practical experience indicates that"
1270 DATA "An intensive search of applicable literature suggests that"
1280 DATA "However, leading experts propose evidence claiming that"
1290 DATA "The total body of secondary knowledge implies that"
1300 DATA "On a divergent course, current organizational policy directs that"
1310 DATA "In summary, then, we propose that"
1320 FOR M=0 TO 3 : READ FILL0$(M) : NEXT M
1330 DATA "by using","by applying available resources towards"
1340 DATA "with structured deployment of"
1350 DATA "by supplying total commitment towards"
1360 FOR M=0 TO 3 : READ FILL1$(M) : NEXT M
1370 DATA "coordinated with","to offset","balanced by","supported by"
1380 FOR M=0 TO 3 : READ FILL2$(M) : NEXT M
1390 DATA "it is possible for even the most","it is necessary for all"
1400 DATA "it becomes not unfeasable for all but the least"
1410 DATA "it is appropriate for the minimum"
1420 FOR M=0 TO 3 : READ FILL3$(M) : NEXT M
1430 DATA "to function as","to generate a high level of","to avoid"
1440 DATA "to digress from"
1450 FOR M=0 TO 15 : READ ADJ1$(M) : NEXT M
1460 DATA "integrated","total","systematized","parallel"
1470 DATA "functional","responsive","optimal","synchronized"
1480 DATA "compatible","qualified","partial","stand-alone"
1490 DATA "random","representative","optional","transient"
1500 FOR M=0 TO 15 : READ ADJ2$(M) : NEXT M
1510 DATA "management","organizational","monitored","reciprocal"
1520 DATA "digital","logistical","transitional","incremental"
1530 DATA "third generation","policy","decision","undocumented"
1540 DATA "context sensitive","fail-safe","omnirange","unilateral"
1550 FOR M=0 TO 15 : READ NOUN$(M) : NEXT M
1560 DATA "criteria","flexibility","capability","mobility"
1570 DATA "programming","concepts","time phasing","projections"
1580 DATA "hardware","through-put","engineering","outflow"
1590 DATA "superstructures","interaction","congruence","utilities"
1600 RETURN
1610 REM SUB CLEAR_SCREEN
1620 FOR M=1 TO 24 : PRINT : NEXT M
1630 RETURN
1640 REM SUB START_RANDOM
1650 PRINT"Strike Any Key ..."
1660 PRINT
1670 SCOUNT=0 : SKEY$=""
1680 IF NOT (SKEY$="") THEN 1720
1690 SCOUNT=SCOUNT+1
1700 SKEY$=INKEY$
1710 GOTO 1680 : REM END WHILE
1720 RANDOMIZE(INT(.14159*SCOUNT))
1730 RETURN
1740 REM END PROGRAM
