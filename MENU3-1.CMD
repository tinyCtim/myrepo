
* Program .... : MENU3-1.CMD
* Notes ...... : This program "prints" customer lists either alphabetically
* .............: or by customer ID.

ERASE
IF choice = '1'
 SET INDEX TO Customer
ELSE
 SET INDEX TO Custid
ENDIF
GO TOP
* SET FORMAT TO PRINT 6/22/24
SET MARGIN TO 15
STORE 0 TO page
STORE 'MAILING LIST PRINTOUT AS OF '+cdate TO pagetitle

DO WHILE .NOT. EOF
 @ 6,15 SAY pagetitle
 STORE 8 TO line

 DO WHILE line<55 .AND. .NOT. EOF
  @ line,1  SAY CUSTID
  @ line,15 SAY NAME
  @ line,50 SAY PHONE
  IF .NOT. ATTN = '        '
   STORE line+1 TO line
   @ line,15 SAY ATTN
  ENDIF
  @ line+1,15  SAY ADDRESS
  @ line+2,15  SAY TRIM(CITY)+', '+STATE
  @ line+2,42  SAY ZIP
  STORE line+4 TO line
  SKIP
 ENDDO

 STORE page+1 TO page
 @ 62,40 SAY STR(page,3)
 EJECT
ENDDO

SET FORMAT TO SCREEN
SET MARGIN TO 0
RELEASE page,pagetitle,line
* lrb
WAIT

