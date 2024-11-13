
* Program .... : MENU3-4.CMD
* Notes ...... : This program "prints" selected records

SET INDEX TO Customer
GO TOP
ERASE
STORE '                                              ' TO mname
STORE '                                        ' TO mstreet
STORE '                            ' TO mcity
STORE '  ' TO mstate
STORE '     ' TO mzip
@ 1,10 SAY 'FILL IN THE ITEMS YOU ARE INTERESTED IN'
@ 3,10 SAY 'NAME' GET mname
@ 4,10 SAY 'STREET' GET mstreet
@ 5,10 SAY 'CITY' GET mcity
@ 6,10 SAY 'STATE' GET mstate
@ 7,10 SAY 'ZIP CODE' GET mzip
READ NOUPDATE

STORE !(TRIM(mname)) TO mname
STORE !(TRIM(mstreet)) TO mstreet
STORE !(TRIM(mcity)) TO mcity
STORE !(TRIM(mstate)) TO mstate
STORE !(TRIM(mzip)) TO mzip

IF mname+mstreet+mcity+mstate+mzip = '    '
 RETURN
ELSE
 STORE ' NEXT 65535 FOR ' TO command
 IF .NOT. mname = ' '
  STORE command+'NAME=mname .AND.' TO command
  FIND &mname
 ENDIF
 IF .NOT. mstreet = ' '
  STORE command+'mstreet$ADDRESS .AND.' TO command
 ENDIF
 IF .NOT. mcity = ' '
  STORE command+'CITY=mcity .AND.' TO command
 ENDIF
 IF .NOT. mstate = ' '
  STORE command+'STATE=mstate .AND.' TO command
 ENDIF
 IF .NOT. mzip = ' '
  STORE command+'ZIP=mzip .AND.' TO command
 ENDIF
 STORE $(command,1,LEN(command)-5) TO command
 LOCATE &command
 * SET FORMAT TO PRINT
 STORE 0 TO page
 ERASE
 DO WHILE .NOT. EOF
  @ 6,15 SAY DATE()+' SPECIAL CUSTOMER FILE LIST'
  STORE 10 TO LINE
  DO WHILE line<55 .AND. .NOT. EOF
   @ line,1  SAY CUSTID
   @ line,15 SAY NAME
   @ line,50 SAY PHONE
   IF .NOT. ATTN = '    '
    STORE line+1 to line
    @ line,15 SAY ATTN
   ENDIF
   @ line+1,15 SAY ADDRESS
   @ line+2,15 SAY TRIM(CITY)+', '+STATE
   @ line+2,42 SAY ZIP
   STORE line+4 TO line
   SKIP
   WAIT
   LOCATE &command
  ENDDO
  STORE page+1 TO page
  @ 62,40 SAY STR(page,3)
  EJECT
 ENDDO
ENDIF
SET FORMAT TO SCREEN
RELEASE page,line,command,mname,mstreet,mcity,mstate,mzip
RETURN

