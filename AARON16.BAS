10 REM
20 REM AARON16.BAS - original program written ~ 7/2001 - Lee Bradley
30 REM
40 PRINT "AARON, Version 1.6"
50 PRINT
60 PRINT "This program finds Ruth-Aaron pairs."
70 PRINT
80 PRINT "The sums of the prime divisors of these consecutive"
90 PRINT "numbers are equal."
100 PRINT
110 PRINT "Inspired by the work of Hungarian mathematician Paul Erdos."
120 PRINT
130 PRINT "Assisted by Howard Goldstein."
140 REM
150 DIM PRIMES(1230)
160 OPEN "O", #1, "AARON.OUT": OPEN "I", #2, "PRIMENUM.TXT"
170 FOR I = 1 TO 1229: INPUT #2, PRIMES(I): NEXT
180 PRINT
190 INPUT "Enter delay parameter between 10 and 100 : ", DL
200 INPUT "Enter beginning number between 2 and 32000 : ", N1
210 INPUT "Enter ending number between 2 and 32000 : ", N2
220 FOR N = N1 TO N2
230 M = N: AARON = 0: I = 1: UL = INT(SQR(N))
240 IF PRIMES(I) > UL THEN 280
250 IF M / PRIMES(I) <> INT(M / PRIMES(I)) THEN 270
260 PRINT PRIMES(I): M = M / PRIMES(I): AARON = AARON + PRIMES(I): GOTO 250
270 IF I < 1229 THEN I = I + 1: GOTO 240
280 IF M <> 1 AND AARON <> 0 THEN PRINT M: AARON = AARON + M
290 IF AARON = N - 1 THEN 310
300 IF NOT (AARON = SARON AND ATL2 >= 2) THEN 340
310 PRINT N - 1; N; "is a Ruth-Aaron pair."
320 PRINT #1, N - 1, N:
330 FOR Q1 = 1 TO DL: GOSUB 430: NEXT
340 IF AARON = 0 THEN 370
350 PRINT AARON; "is the sum of the prime factors of "; MID$(STR$(N), 2); "."
360 SARON = AARON: GOTO 380
370 PRINT N; "is a prime number.": ATL2 = 0: GOSUB 430
380 ATL2 = ATL2 + 1
390 NEXT N
400 CLOSE #1
410 CLOSE #2
420 SYSTEM
430 REM DELAY
440 FOR Q = 1 TO 32000: NEXT: RETURN
