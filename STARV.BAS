10 ' STARV - lrb - 1/16,17/2008
20 ' there's 1 way to draw a 5-point star, 0 ways to draw a 6-point star and
30 ' 2 ways to draw a 7-point star. how many ways are there to draw a
40 ' 1000-point star?
50 ' solutions and their mirrors images are computed; unique counts are
60 ' displayed / written
70 PRINT : PRINT "STARV - lrb - 1/17/2008": PRINT
80 OPEN "o", #1, "STAR.OUT"
90 INPUT "number of points (7 or more) in the star "; POINTS: P# = POINTS
100 INPUT "want verbose reporting? type 1 for yes, 0 for no "; V
110 PRINT "": PRINT "Let the stargazing begin ... ": PRINT ""
120 FOR GAZE = 0 TO 100000! STEP 1: FOO = BAR: NEXT GAZE
130 IF LEN(INKEY$) <> 0 THEN PRINT "Aborted!": END
140 P# = POINTS
150 CTR = 0: CTRS = 0
160 FOR SKIP = 1 TO POINTS - 3 STEP 1
170   IF V = 0 THEN 220
180   IF CTR = CTRS THEN 200
190   PRINT " *"; : PRINT #1, " *"; : CTRS = CTR
200   PRINT "": PRINT "skip "; SKIP; " : ";
210   PRINT #1, "": PRINT #1, "skip "; SKIP; " : ";
220   FOR N = 0 TO POINTS STEP 1
230     W1# = N MOD POINTS
240     W2# = (SKIP + 1) MOD POINTS
250     W3# = W1# * W2#
260     IF W3# >= P# THEN W3# = W3# - P#: GOTO 260
270     IF W3# = POINTS - 1 THEN CTR = CTR + 1
280     IF V = 0 THEN 300
290     PRINT W3#; : PRINT #1, W3#;
300   NEXT N
310 NEXT SKIP
320 IF CTR = CTRS THEN 340
330 IF V = 1 THEN PRINT " *";: PRINT #1, " *";
340 PRINT "": PRINT "": PRINT POINTS, CTR / 2
350 PRINT #1, "": PRINT #1, "": PRINT #1, POINTS, CTR / 2
360 END
