10 VER$ = "1.5b"
20 ON ERROR GOTO 430
30 ' COMMENT OUT NEXT LINE IF USING MBASIC
40 CALL CMD(COMMAND$)
50 GOSUB 510 : ' See if Z-System present
60 LEE$ = "LEE" : IF ENV<>0 THEN GOSUB 570 : LEE$ = EFCB$ : ' Get name
70 PRINT
80 PRINT LEE$+", (Letter Extractor / Enhancer), Version "+VER$
90 PRINT LEE$+" generates "+CHR$(34)+"handwritten"+CHR$(34);
100 PRINT " files from text files."
110 ' COMMENT OUT NEXT LINE IF USING MBASIC 
120 PRINT "Usage: "+LEE$+" [I=INPUT.TXT] [O=OUTPUT.HTM]"  
130 II = INSTR(COMMAND$,"I=") : IO = INSTR(COMMAND$,"O=")
140 IF II=0 THEN 170
150 IFN$ = MID$(COMMAND$,II+2)
160 ISP = INSTR(IFN$," ") : IF ISP<>0 THEN IFN$ = MID$(IFN$,1,ISP-1)
170 IF IO=0 THEN 200
180 OFN$ = MID$(COMMAND$,IO+2)
190 OSP = INSTR(OFN$," ") : IF OSP<>0 THEN OFN$ = MID$(OFN$,1,OSP-1)
200 PFN$ = "http://primepuzzle.com/mouse/"
210 IF LEN(IFN$)=0 THEN INPUT "Enter input file name ";IFN$
220 IF LEN(OFN$)=0 THEN INPUT "Enter output file name ";OFN$
230 LFSZ$ = "20"
240 OPEN "i",1,IFN$ : OPEN "o",2,OFN$
250 PRINT #2,"<table align=center width=85%><tr><td>" : PRINT #2,"<pre>"
260 LINE INPUT #1,L$
270 SC$ = "1234567890,;!.?':-_@&/()*+\=%#{}$~"
280 '               1111111111222222222233333
290 '      1234567890123456789012345678901234
300 FOR I=1 TO LEN(L$) : ' MAIN LOOP
310 IF INSTR(L$,"<") THEN PRINT #2,L$; : GOTO 400 : ' <img or <a tag detected
320 C$ = MID$(L$, I, 1)
330 CASE$ = "lc" 
340 IF C$>="A" AND C$<="Z" THEN CASE$ = "uc" : C$ = CHR$(ASC(C$)+97-65)
350 SP = INSTR(SC$, C$) : IF SP<>0 THEN CASE$ = "sc" : C$ = MID$(STR$(SP), 2)
360 IF C$=CHR$(34) THEN CASE$ = "sc" : C$ = "35"
370 IF C$=" " THEN CASE$ = "nc" : C$ = "32"
380 PRINT #2,"<img src="+PFN$+C$+CASE$+LFSZ$+".jpg>";
390 NEXT I
400 PRINT #2,"<br>"
410 LINE INPUT #1,L$
420 GOTO 300
430 IF ERR=62 THEN 460 : ' Reached end of input file
440 IF ERR=53 THEN PRINT "File "+IFN$+" not found." : GOTO 490
450 PRINT "Error Reason Code = ";ERR;" Error Line Number = ";ERL : GOTO 480
460 PRINT #2,""
470 PRINT "Done. File "+OFN$+" created."
480 CLOSE #2
490 CLOSE #1
500 SYSTEM
510 ' See if Z-System is present - set ENV accordingly
520 ENV = PEEK(&H109)+256*PEEK(&H10A)
530 ENV1 = PEEK(ENV+&H1B)+256*PEEK(ENV+&H1C)
540 IF ENV1=ENV THEN 560
550 ENV=0
560 RETURN
570 ' External File Control Block stuff
580 EFCBA = PEEK(ENV+&H24)+256*PEEK(ENV+&H25)+1
590 EFCB$ = ""
600 IF NOT(CHR$(PEEK(EFCBA))<>" " AND LEN(EFCB$)<8) THEN RETURN
610 EFCB$ = EFCB$+CHR$(PEEK(EFCBA)) : EFCBA = EFCBA+1 : GOTO 600
