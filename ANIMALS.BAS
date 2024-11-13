10 '
20 ' ANIMALS.BAS 
30 '
40 ' This program reads a file named ANIMALS.DAT on the logged
50 ' drive.  In case you're missing this file, create one with
60 ' the following in it.
70 '
80 ' 4
90 ' \QIs it sometimes mean and often red\n 3\y 2\
100 ' \AFox
110 ' \AWhale
120 '
130 PRINT
140 PRINT TAB(17); "Guess the Animal"
150 PRINT
160 PRINT "Think of an animal and I will try to guess it."
170 DIM A$(200)
180 OPEN "I",#1,"ANIMALS.DAT"
190 INPUT#1,A$(0)
200 N5=VAL(A$(0))
210 FOR I=1 TO N5-1
220 INPUT #1,A$(I)
230 NEXT I
240 N=VAL(A$(0))
250 '  main control section
260 FOR J=1 TO 5
270 PRINT
280 NEXT J
290 INPUT "Are you thinking of an animal (Y/N)";A$
300 IF A$="list" OR A$="LIST" THEN 790
310 IF LEFT$(A$,1)<>"y" AND LEFT$(A$,1)<>"Y" THEN 900
320 K=1
330 GOSUB 570
340 IF LEN(A$(K))=0 THEN 960
350 IF LEFT$(A$(K),2)="\Q" THEN 330
360 PRINT "Is it a ";RIGHT$(A$(K),LEN(A$(K))-2);
370 INPUT A$
380 A$=LEFT$(A$,1)
390 IF INSTR("yY",A$)=0 THEN 410
400 PRINT:PRINT "Why not try another animal?": GOTO 250
410 INPUT "The animal you were thinking of was a ";V$
420 PRINT
430 PRINT "Please type in a question that would distinguish a ";V$
440 PRINT "from a ";RIGHT$(A$(K),LEN(A$(K))-2);"."
450 INPUT X$
460 PRINT "For a ";V$;" the answer would be ";
470 INPUT A$
480 A$=LEFT$(A$,1): IF A$<>"y" AND A$<>"n" AND A$<>"Y" AND A$<>"N" THEN 460
490 IF A$="y" OR A$="Y" THEN B$="N"
500 IF A$="n" OR A$="N" THEN B$="Y"
510 Z1=VAL(A$(0))
520 A$(0)=STR$(Z1+2)
530 A$(Z1)=A$(K)
540 A$(Z1+1)="\A"+V$
550 A$(K)="\Q"+X$+"\"+A$+STR$(Z1+1)+"\"+B$+STR$(Z1)+"\"
560 GOTO 250
570 '      subroutine to print questions
580 Q$=A$(K)
590 FOR Z=3 TO LEN(Q$)
600 IF MID$(Q$,Z,1)<>"\" THEN PRINT MID$(Q$,Z,1);: NEXT Z
610 INPUT C$
620 C$=LEFT$(C$,1)
630 IF INSTR("nyYN",C$)=0 THEN 590
640 IF C$="n" THEN C1$="N"
650 IF C$="y" THEN C1$="Y"
660 IF C$="Y" THEN C1$="y"
670 IF C$="N" THEN C1$="n"
680 T$="\"+C$ : T1$="\"+C1$
690 FOR X=3 TO LEN(Q$)-1
700 IF MID$(Q$,X,2)=T$ OR MID$(Q$,X,2)=T1$ THEN 730
710 NEXT X
720 STOP
730 FOR Y=X+1 TO LEN(Q$)
740 IF MID$(Q$,Y,1)="\" THEN 770
750 NEXT Y
760 SYSTEM
770 K=VAL(MID$(Q$,X+2,Y-X-2))
780 RETURN
790 PRINT: PRINT "Animals I already know are:"
800 FOR I=1 TO 200
810 IF LEFT$(A$(I),2)<>"\A" THEN 860
820 PRINT TAB(18*X);
830 FOR Z=3 TO LEN(A$(I))
840 IF MID$(A$(I),Z,1)<>"\" THEN PRINT MID$(A$(I),Z,1);: NEXT Z
850 PRINT
860 NEXT I
870 PRINT
880 PRINT
890 GOTO 290
900 N5=VAL(A$(0))     
910 OPEN "O",#2,"ANIMALS.DAT"
920 FOR I=0 TO N5-1
930 PRINT #2,A$(I)
940 NEXT I
950 SYSTEM
960 END

