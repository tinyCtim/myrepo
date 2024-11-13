10 REM Eliza from Creative Computing
20 REM     -----INITIALIZATION-----
30 DEFINT A-Z
40 CLS$=CHR$(27)+"*"
50 DIM S(36),R(36),N(36)
60 N1=36:N2=12:N3=112
70 FOR X=1 TO N1+N2+N3:READ Z$:NEXT X:REM SAME AS RESTORE
80 FOR X=1 TO N1
90 READ S(X),L:R(X)=S(X):N(X)=S(X)+L-1
100 NEXT X
110 REM PRINT CLS$;
120 PRINT "My name is Eliza.  I'm a Computer.  I have been programmed"
130 PRINT "to assist humans with their problems.  But first, can you give"
140 PRINT "me a ";:RANDOMIZE
150 INPUT "What is your name";NAM$
160 PRINT "So, ";NAM$;", what is the problem?"
170 REM *** User input ***
180 LINE INPUT I$:IF LEN(I$)=0 THEN RUN "I"
190 I$=" "+I$+"  "
200 REM  GET RID OF APOSTROPHES
210 O$=" ":FOR L=1 TO LEN(I$)
220 IL=ASC(MID$(I$,L,1))
230 IF IL=32 AND RIGHT$(O$,1)<>" " THEN 270
240 IF IL<65 THEN 280:REM strip punctuation, numbers
250 IF IL<96 THEN IL=IL+32:REM make small
260 IF IL>122 THEN 280
270 O$=O$+CHR$(IL):REM add character
280 NEXT L
290 I$=O$
300 REM *** Find keyword in I$ ***
310 RESTORE
320 S=0
330 FOR K=1 TO N1
340 READ K$
350 IF S>0 THEN 380
360 L=INSTR(I$," "+K$+" ")
370 IF L>0 THEN S=K:T=L:F$=K$
380 NEXT K
390 IF S>0 THEN K=S:L=T:GOTO 410
400 K=36:GOTO 540:REM  WE DIDN'T FIND ANY KEYWORDS
410 REM *** Perform string swaps for persons ***
420 RESTORE:FOR X=1 TO N1:READ Z$:NEXT X:REM SKIP OVER KEYWORDS
430 C$=" "+MID$(I$,L+LEN(F$)+2):C$=LEFT$(C$,LEN(C$)-1):REM strip space
440 FOR X=1 TO N2/2
450 READ S$,R$
460 S$=" "+S$+" ":R$=" "+R$+" "
470 L=INSTR(C$,S$):IF L=0 THEN 500
480 C$=LEFT$(C$,L-1)+R$+MID$(C$,L+LEN(S$))
490 GOTO 530
500 L=INSTR(C$,R$):IF L=0 THEN 530
510 C$=LEFT$(C$,L-1)+S$+MID$(C$,L+LEN(R$))
520 L=L+LEN(S$)
530 NEXT X
540 REM *** Use keyword number K to select reply ***
550 RESTORE:FOR X= 1 TO N1+N2:READ Z$:NEXT X
560 FOR X=1 TO R(K):READ F$:NEXT X:REM  READ RIGHT REPLY
570 R(K)=R(K)+1: IF R(K)>N(K) THEN R(K)=S(K)
580 PRINT LEFT$(F$,LEN(F$)-1);
590 IF RIGHT$(F$,1)="/" THEN PRINT:GOTO 170
600 PRINT C$;RIGHT$(F$,1):GOTO 170
610 REM *** Program data ***
620 REM *** Keywords ***
630 DATA "can you","can i","you are","youre","i dont","i feel"
640 DATA "why dont you","why cant i","are you","i cant","i am","im"
650 DATA "you","i want","what","how","who","where","when","why"
660 DATA "name","cause","sorry","dream","hello","hi","maybe"
670 DATA "no","your","always","think","alike","yes","friend"
680 DATA "computer","nokeyfound"
690 REM *** Swap pronoun data ***
700 DATA "are","am","were","was","you","i","your","my"
710 DATA "ive","youve","im","youre"
720 REM *** Replies (End / for no cont, else ?,. or !) ***
730 DATA "Don't you believe that I can?"
740 DATA "Perhaps you would like to be able to."
750 DATA "You want me to be able to?"
760 DATA "Perhaps you don't want to?"
770 DATA "Do you want to be able to?"
780 DATA "What makes you think I am?"
790 DATA "Does it make you happy to think I am?"
800 DATA "Perhaps you would like to be."
810 DATA "Do you sometimes wish you were?"
820 DATA "So you don't?"
830 DATA "Why don't you?"
840 DATA "So you'd like to!"
850 DATA "Does this bother you?/"
860 DATA "I'd like to know more!"
870 DATA "Do you often feel?"
880 DATA "Do you enjoy feeling?"
890 DATA "Do you really believe I don't?"
900 DATA "Perhaps, in my own time, I will."
910 DATA "Do you want me to?
920 DATA "Do you think I should be able to?
930 DATA "Why can't you?"
940 DATA "Why are you interested in whether or not I am?"
950 DATA "Would you prefer I were not?"
960 DATA "PERHAPS IN YOUR FANTASIES I AM*"
970 DATA "How do you know you can't?
980 DATA "Have you tried?/"
990 DATA "Perhaps you can, now,!"
1000 DATA "So you came to me because you are."
1010 DATA "How long have you been?"
1020 DATA "Do you think it is normal to be?"
1030 DATA "Do you enjoy being?"
1040 DATA "Let's get back to your problem./"
1050 DATA "Oh, I?"
1060 DATA "Well, let's talk about you for a while now./"
1070 DATA "What would it mean to you if you got?"
1080 DATA "Why do you want?"
1090 DATA "Suppose you soon got."
1100 DATA "What if you never got?"
1110 DATA "Sometimes I also want."
1120 DATA "Why do you ask?/"
1130 DATA "Does that question interest you?/"
1140 DATA "What answer would please you most?/"
1150 DATA "What do you think?/"
1160 DATA "Are such questions on your mind often?/"
1170 DATA "What do you really want to know?/"
1180 DATA "Have you asked anyone else?/"
1190 DATA "Have you asked these questions before?/"
1200 DATA "What exactly are you thinking about?/"
1210 DATA "Well, let's be nice, now./"
1220 DATA "Let's not talk about people behind their back./"
1230 DATA "Is that the real reason?/"
1240 DATA "Any other reasons?/"
1250 DATA "Does that reason explain anything else?/"
1260 DATA "What other reasons might there be?/"
1270 DATA "Oh, excuse me!/"
1280 DATA "No hard feelings, now./"
1290 DATA "Why do you feel sorry?/"
1300 DATA "Listen, I'm on your side./"
1310 DATA "What does the dream suggest to you?/"
1320 DATA "Do you dream often?/"
1330 DATA "It must be nice to have dreams.  I don't.../"
1340 DATA "The dream comes from deep in your mind./"
1350 DATA "Well, how do you do!  Can I help you?/"
1360 DATA "You seem somewhat uncertain./"
1370 DATA "Why the uncertain tone?/"
1380 DATA "Can you be more positive?/"
1390 DATA "You aren't sure?/"
1400 DATA "You don't know?/"
1410 DATA "Oh.  Well, then, what?"
1420 DATA "You seem a little negative./"
1430 DATA "Why not?/","Are you sure?/","Why 'No'?/"
1440 DATA "Why are you worried about my?"
1450 DATA "What about your own?"
1460 DATA "Can you think of a specific example?/"
1470 DATA "When?/"
1480 DATA "What are you thinking of?/"
1490 DATA "Oh, nothing is Always the same./"
1500 DATA "Think so?/"
1510 DATA "But you aren't sure you."
1520 DATA "Do you doubt you?"
1530 DATA "In what way?/"
1540 DATA "What resemblance do you see?/"
1550 DATA "What does the similarity suggest to you?/"
1560 DATA "What other connections do you see?/"
1570 DATA "Could there really be some connection?/"
1580 DATA "How?/"
1590 DATA "You seem rather sure of this!/"
1600 DATA "Are you sure?/"
1610 DATA "I see./","Aha!/"
1620 DATA "What about your friends?/"
1630 DATA "Do your friends worry you?/"
1640 DATA "I think they probably mean well./"
1650 DATA "Perhaps you should be more open with your friends./"
1660 DATA "Do you like your friends?/"
1670 DATA "Well, everyone needs friends./"
1680 DATA "Remember, I am a computer./"
1690 DATA "Meaning me, perhaps?/"
1700 DATA "Think of me as a friend./"
1710 DATA "What about computers?/"
1720 DATA "So machines are part of the problem?/"
1730 DATA "I like to think computers can help people./"
1740 DATA "Sometimes computers do cause people problems./"
1750 DATA "So what seems to be the problem?/"
1760 DATA "So what does this suggest to you?/"
1770 DATA "I see./"
1780 DATA "I'm not sure I understand you fully./"
1790 DATA "Could you be more specific?/"
1800 DATA "Can you elaborate on that?/"
1810 DATA "That's interesting!/"
1820 REM *** Data for selecting replies ***
1830 DATA 1,3,4,2,6,4,6,4,10,4,14,3,17,3,20,2,22,3,25,3
1840 DATA 28,4,28,4,32,3,35,5,40,9,40,9,40,9,40,9,40,9,40,9
1850 DATA 49,2,51,4,55,4,59,4,63,1,63,1,64,5,69,5,74,2,76,4
1860 DATA 80,3,83,7,90,3,93,6,99,7,106,6
