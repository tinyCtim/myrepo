10 REM Echo Command Line Argument (ECHO.BAS)
20 REM
30 REM A demonstration of how to pull command line arguments
40 REM into BASIC. Note, that this only works with compiled BASCOM
50 REM programs. MBASIC sets the CCP arguments field to zeros.
60 REM
70 REM by Jim McClanahan W4JBM (July 2020)
80 REM
90 REM The first character is usually a space and can
100 REM be ignored.
110 REM
120 REM CCP converts all alpha characters to upper case.
130 REM
140 REM Commands to save and build:
150 REM in MBASIC...
160 REM   SAVE "ECHO.BAS",A
170 REM   SYSTEM
180 REM from CP/M prompt...
190 REM   BASCOM =ECHO/Z/O/E
200 REM   L80 ECHO,BASECHO/N/E
210 REM
220 L%=PEEK(128)
230 IF L%=0 THEN 320
240 FOR M%=129 TO 128+L%
250 C%=PEEK(M%)
260 IF M%=129 AND C%=32 THEN GOTO 290
270 N%=N%+C%
280 PRINT CHR$(C%);
290 NEXT M%
300 PRINT N%
310 PRINT
320 END
