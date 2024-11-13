
* Program .... : MENU3-2.CMD
* Notes ...... : This program "prints" the mailing lists either alphabetically by zip

ERASE
SET INDEX TO Zip
GO TOP
* SET FORMAT TO PRINT 6/22/24
SET MARGIN TO 15
STORE 0 TO page

DO WHILE .NOT. EOF
 @ 6,25 SAY 'MAILING LIST FOR ZIP CODE '+ZIP+' AS OF '+DATE()
 STORE ZIP TO mzip
 STORE 8 TO line

 DO WHILE ZIP = mzip .AND. line<55 .AND. .NOT. EOF
  @ line,1  SAY CUSTID
  @ line,15 SAY NAME
  IF .NOT. ATTN = '        '
   STORE line+1 TO line
   @ line,15 SAY ATTN
  ENDIF
  @ line,50 SAY PHONE
  @ line+1,15  SAY ADDRESS
  @ line+2,15  SAY TRIM(CITY)+', '+STATE
  @ line+2,42  SAY ZIP
  STORE line+4 TO line
  SKIP
  WAIT
  ERASE
 ENDDO

 STORE page+1 TO page
 @ 62,40 SAY STR(page,3)
 EJECT
ENDDO

SET FORMAT TO SCREEN
SET MARGIN TO 0
RELEASE page,line,mzip
* lrb
WAIT

