10 CLEAR 10000:WIDTH 80
20 PRINT CHR$(27)"EPILOT/80 Version 83.03.06"
30 PRINT "By Kurt Albrecht Copyright (c) 1983"
40 REM
50 REM *** Initialization ***
51 REM
60 ML%=100:MV%=10:MS%=10:MI%=70:DIM P$(100), V$(10,2), S%(10)
70 ER$="Error - ":ON ERROR GOTO 480
80 REM
90 REM *** Command Level ***
91 REM
100 EF%=0:PRINT CHR$(27)"q"CHR$(27)"G":PRINT "Command? ";: GOSUB 170:IF B$="" THEN 100
110 IF B$="NEW" THEN 580 ELSE
    IF LEFT$(B$,4)="EDIT" THEN 620 ELSE
    IF LEFT$(B$,6)="INSERT" THEN 660 ELSE 
    IF LEFT$(B$,6)="DELETE" THEN 720 ELSE
    IF LEFT$(B$,4)="LIST" THEN 780
120 IF LEFT$(B$,4)="SAVE" THEN 830 ELSE
    IF LEFT$(B$,4)="LOAD" THEN 880 ELSE
    IF LEFT$(B$,3)="RUN" THEN 940 ELSE
    IF B$="LLIST" THEN B$="SAVELP:":GOTO 830 ELSE
    IF B$="BYE" THEN 140
130 PRINT ER$"I don't recognize that command."
131 PRINT "Perhaps you made a typing mistake.":GOTO 100
140 PRINT "Are you sure you want to return to CP/M? (Y/N)":
    C$=INPUT$(1):IF C$="N" OR C$="n" THEN 100
    ELSE IF C$<>"Y" AND C$<>"y" THEN 140 ELSE PRINT "Bye!":SYSTEM
150 REM
160 REM *** String Input ***
161 REM
170 A$="":B$=""
180 C$=INPUT$(1):IF A$="" AND (C$="" OR C$=CHR$(9)) THEN 180
190 IF C$=CHR$(13) THEN PRINT:GOTO 270
200 IF C$=CHR$(8) THEN IF LEN(A$)=0 THEN 180
    ELSE A$=LEFT$(A$,LEN(A$)-1):B$=LEFT$(B$,LEN(B$)-1):
    PRINT C$" "C$;:GOTO 180
210 IF C$=CHR$(9) THEN IF LEN(A$)+8>MI% THEN 180
    ELSE A$=A$+SPACE$(8):B$=B$+SPACE$(8):PRINT SPC(8);:GOTO 180
220 IF LEN(A$)=MI% OR C$=CHR$(64) OR C$=CHR$(127) THEN 180
230 A$=A$+C$:PRINT C$;:IF C$>="a" AND C$<="z" THEN C$=CHR$(ASC(C$)-32)
240 B$=B$+C$:GOTO 180
250 REM
260 REM *** Remove Spaces ***
261 REM
270 I%=INSTR(B$," "):IF I%=0 THEN RETURN
    ELSE B$=LEFT$(B$,I%-1)+RIGHT$(B$,LEN(B$)-I%):GOTO 270
280 REM
290 *** INPUT PROGRAM LINE ***
291 REM
300 IF LN%>ML% THEN
    PRINT ER$"You have entered the maximum number of"ML%"program lines.":
    EF%=1:RETURN
310 PRINT LN%;:GOSUB 170:C$=LEFT$(B$,1)
320 IF B$="DONE" THEN EF%=1:RETURN
330 IF B$="" OR C$="*" THEN A$=B$:RETURN
    ELSE IF C$=":" THEN A$=C$+RIGHT$(A$,LEN(A$)-1):RETURN
340 IF INSTR("TAIMJUESR",C$)=0 THEN
    PRINT ER$"I don't know the program command in line"LN%".":GOTO 310
350 IF MID$(B$,2,1)<>":" AND MID$(B$,2,2)<>"Y:" AND MID$(B$,2,2)<>"N:" THEN
    PRINT ER$"The program command in line"LN%"must be followed by either
    :, Y:, or N:.":GOTO 310
360 IF C$="T" OR C$="R" THEN A$=LEFT$(B$,2)+RIGHT$(A$,LEN(A$)-2) ELSE A$=B$
370 RETURN
380 REM
390 REM *** Check Line Number Validity ***
391 REM
400 IF LL%=0 THEN PRINT ER$"There isn't a program presently in memory.":
    EF%=1:RETURN
410 FOR I%=1 TO LEN(B$):IF INSTR("0123456789-",MID$(B$,I%,1)) THEN NEXT
    ELSE PRINT ER$"A line number from 1 to"ML%"must follow that command.":
    EF%=1:FOR J%=1 TO 1:NEXT:RETURN
420 BL%=VAL(B$):LN%=BL%:GOSUB 450:IF EF%=1 THEN RETURN
430 IF INSTR(B$,"-")=0 THEN EL%=0 ELSE IF RIGHT$(B$,1)="-" THEN EL%=LL%
    ELSE EL%=VAL(RIGHT$(B$,LEN(B$)-INSTR(B$,"-"))):LN%=EL%:GOSUB 450:
    IF EF%=1 THEN RETURN ELSE IF BL%>EL%
    THEN PRINT ER$"The line numbers must be in ascending order.":EF%=1
440 RETURN
450 IF LN%<1 OR LN%>ML% THEN PRINT ER$"A line number from 1 to"ML%"must
    follow that command.":EF%=1:RETURN ELSE IF LN%>LL% AND EF%=0 THEN
    PRINT ER$"Line"LN%"does not exist.":EF%=1:RETURN ELSE EF%=0:RETURN
460 REM
470 REM *** Error Trapping ***
471 REM
480 IF ERR=6 THEN PRINT ER$"Numbers must be in the range of -32767 to32767.":
    RESUME 100
490 IF ERR=65 THEN PRINT ER$"A file name must follow this command. Basically,
    a file name may not"
500 IF ERR=65 THEN PRINT TAB(8) "exceed 8 characters in length, begin with a
    number, or contain special":PRINT TAB(8) "characters. See the PILOT/80
    documentation for a more detailed":PRINT TAB(8) "explanation of file
    names.":RESUME 100
510 IF ERR=53 THEN PRINT ER$B$" cannot be found on the indicated disk drive.":
    PRINT TAB(8) "Check your spelling, make sure you used the correct
    extension, and that":PRINT TAB(8) "you indicated the correct disk drive.":
    RESUME 100
520 IF ERR=62 THEN PRINT ER$"There is no space available on the designated
    disk drive.":CLOSE:RESUME 100
530 PRINT ER$"A Microsoft Basic error has occured.  See appendix A of the
    MBasic":PRINT TAB(8) "manual for an explanation of error"ERR".";
540 IF LL%>0 THEN PRINT "  I strongly suggest that you":
    PRINT TAB(8) "first LLIST your program in case you are unable to recover
    it.";
550 PRINT:CLOSE:RESUME 100
560 REM
570 REM *** New ***
571 REM
580 REM ERASE P$
585 DIM P$(100%):LN%=1:LL%=0
590 GOSUB 300:IF EF%=1 THEN 100 ELSE P$(LN%)=A$:LL%=LN%:LN%=LN%+1:GOTO 590
600 REM
610 REM *** Edit ***
611 REM
620 B$=RIGHT$(B$,LEN(B$)-4):GOSUB 400:LN%=BL%:IF EF%=1 THEN 100
630 PRINT LN% P$(LN%):GOSUB 300:IF EF%=1 THEN 100 ELSE P$(LN%)=A$:GOTO 100
640 REM
650 REM  Insert ***
651 REM
660 IF LL%=ML% THEN PRINT ER$"You have entered the maximum number of"ML%"
    program lines.":GOTO 100
670 B$=RIGHT$(B$,LEN(B$)-6):EF%=1:GOSUB 400:LN%=BL%:IF EF%=1 THEN 100
    ELSE IF LN%>LL%+1 THEN PRINT ER$"Line"LN%"does not exist.":GOTO 100
680 GOSUB 300:IF EF%=1 THEN 100
690 FOR I%=LL% TO LN% STEP -1:P$(I%+1)=P$(I%):NEXT:P$(LN%)=A$:LL%=LL%+1
    LN%=LN%+1:GOTO 680
700 REM
710 REM *** Delete ***
711 REM
720 B$=RIGHT$(B$,LEN(B$)-6):GOSUB 400:IF EF%=1 THEN 100
730 IF BL%=ML% OR EL%=LL% THEN LL%=BL%-1:GOTO 100
740 IF EL%-BL%<1 THEN DF%=1 ELSE DF%=EL%-BL%+1
750 LL%=LL%-DF%:FOR I%=BL% TO LL%:P$(I%)=P$(I%+DF%):NEXT:GOTO 100
760 REM
770 REM *** List ***
771 REM
780 IF B$="LIST" AND LL%>0 THEN BL%=1:EL%=LL%:GOTO 800
790 B$=RIGHT$(B$,LEN(B$)-4):GOSUB 400:IF EF%=1 THEN 100
800 FOR I%=BL% TO EL%:PRINT I% P$(I%):NEXT:GOTO 100
810 REM
820 REM *** Save ***
821 REM
830 IF LL%=0 THEN PRINT ER$"There isn't a program presently in memory.":
    GOTO 100
840 B$=RIGHT$(B$,LEN(B$)-4):GOSUB 270:IF RIGHT$(B$,4)<>".PIL" THEN B$=B$+".PIL"
850 OPEN "O",1,B$:FOR LN%=1 TO LL%:PRINT #1,P$(LN%):NEXT:CLOSE:GOTO 100
860 REM
870 REM *** Load ***
871 REM
880 B$=RIGHT$(B$,LEN(B$)-4):GOSUB 270:IF RIGHT$(B$,4)<>".PIL" THEN B$=B$+".PIL"
890 OPEN "I",1,B$:LN%=0
900 LN%=LN%+1:LINE INPUT #1,P$(LN%):IF EOF(1) OR LN%=ML% THEN LL%=LN%:CLOSE:
    GOTO 100
910 GOTO 900
920 REM
930 REM *** Run ***
931 REM
940 VP%=0:SP%=0:C%=0:LF%=0
950 IF B$="RUN" AND LL%>0 THEN LN%=1 ELSE B$=RIGHT$(B$,LEN(B$)-3):GOSUB 400:
    IF EF%=1 THEN 100 ELSE LN%=BL%
960 P$=P$(LN%):C$=LEFT$(P$,1)
970 IF P$="" OR C$="*" THEN 1020 ELSE IF C$=":" THEN P$=RIGHT$(P$,LEN(P$)-1):
    GOTO 1010
980 C%=INSTR("TAIMJUESR",C$):IF C%=0 THEN PRINT ER$"I don't know the program
    command in line"LN%".":GOTO 100
990 IF MID$(P$,2,1)<>":" AND MID$(P$,2,2)<>"Y:" AND MID$(P$,2,2)<>"N:" THEN
    PRINT ER$"The program command in line"LN%"must be followed by
    either :, Y:, or N:.":GOTO 100
1000 IF MID$(P$,2,1)=":" THEN P$=RIGHT$(P$,LEN(P$)-2)
     ELSE IF MID$(P$,2,2)="Y:" AND LF%=1 OR MID$(P$,2,2)="N:"
     AND LF%=0 THEN P$=RIGHT$(P$,LEN(P$)-3) ELSE 1020
1010 ON C% GOTO 1050,1140,1140,1210,1260,1290,1330,1360,1020
1020 IF LN%>=LL% THEN 100 ELSE LN%=LN%+1:GOTO 960
1030 REM
1040 REM *** Type ***
1041 REM
1050 FOR I%=1 TO LEN(P$):C$=MID$(P$,I%,1):IF C$="$" AND VP%>0 THEN 1080
1060 PRINT C$;
1070 NEXT I%:PRINT:GOTO 1020
1080 A$=MID$(P$,I%+1,10):B$="":FOR J%=1 TO LEN(A$):C1$=MID$(A$,J%,1)
1090 IF C1$>="a" AND C1$<="z" THEN C1$=CHR$(ASC(C1$)-32)
1100 IF C1$>="A" AND C1$<="Z" THEN B$=B$+C1$:NEXT J%
1110 FOR K%=1 TO VP%:IF B$=V$(K%,1) THEN PRINT V$(K%,2);:I%=I%+LEN(V$(K%,1)):
     GOTO 1070 ELSE NEXT K%:GOTO 1060
1120 REM
1130 REM *** Ask ***
1131 REM
1140 IF C%=2 THEN GOSUB 170 ELSE B$=INPUT$(1):IF B$>="a" AND B$<="z" THEN
     B$=CHR$(ASC(B$)-32)
1150 V$(0,2)=B$:IF LEFT$(P$,1)<>"$" THEN 1020 ELSE P$=MID$(P$,2,10):
     IF VP%=0 THEN 1180
1160 FOR J%=1 TO VP%:IF V$(J%,1)=P$ THEN V$(J%,2)=A$:GOTO 1020 ELSE NEXT
1170 IF VP%=10 THEN PRINT ER$"Line"LN%"may not define a new variable, the
     maximum of"MV%"variables has":PRINT TAB(8) "already been defined.
     However, one of these may be re-defined.":GOTO 100
1180 VP%=VP%+1:V$(VP%,1)=P$:V$(VP%,2)=A$:GOTO 1020
1190 REM
1200 REM *** Match ***
1201 REM
1210 I%=INSTR(P$,","):IF I%=0 THEN A$=P$ ELSE A$=LEFT$(P$,I%-1)
1220 IF A$<>"" AND INSTR(V$(0,2),A$) THEN LF%=1:GOTO 1020
1230 IF I%=0 THEN LF%=0:GOTO 1020 ELSE P$=RIGHT$(P$,LEN(P$)-I%):GOTO 1210
1240 REM
1250 REM *** Jump ***
1251 REM
1260 A$="*"+LEFT$(P$,10):FOR I%=1 TO LL%:IF LEFT$(P$(I%),11)=A$ THEN LN%=I%:
     FOR J%=1 TO 1:NEXT:GOTO 1020 ELSE NEXT:PRINT ER$"Line"LN%"jumps to a
     label that does not exist.":GOTO 100
1270 REM
1280 REM *** User Subroutine ***
1281 REM
1290 IF SP%=MS% THEN PRINT ER$"Before line"LN%"may jump to a subroutine, one
     of the"MS%"presently being":PRINT TAB(8) "used must be ended.":GOTO 100
1300 A$="*"+LEFT$(P$,10):FOR I%=1 TO LL%:IF LEFT$(P$(I%),10)=A$ THEN
     SP%=SP%+1:S%(SP%)=LN%+1:LN%=I%:FOR J%=1 TO 1:NEXT:GOTO 1020
     ELSE NEXT:PRINT ER$"Line"LN%"jumps to a label that does not exist.":
     GOTO 100
1310 REM
1320 REM *** End User Subroutine / End Program ***
1330 IF SP%=0 THEN 100 ELSE LN%=S%(SP%):SP%=SP%-1:GOTO 1020
1340 REM
1350 REM *** Screen ***
1360 IF P$="CLEAR" THEN PRINT CHR$(27)"E";:GOTO 1020
1370 IF P$="REVERSE" THEN PRINT CHR$(27)"p";:GOTO 1020
1380 IF P$="GRAPHICS" THEN PRINT CHR$(27)"F";:GOTO 1020
1390 IF P$="NORMAL" THEN PRINT CHR$(27)"q";CHR$(27)"G":GOTO 1020
1400 IF P$="BEEP" THEN PRINT "";:GOTO 1020
1410 PRINT ER$"I don't recognize the screen command in line"LN%".":GOTO 100
1420 END
