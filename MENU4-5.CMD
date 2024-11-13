
* Program ......: MENU4-5.CMD (or MENU4-5.PRG)
* Notes	........: This program updates the Inventory.

ERASE
USE Onorder
COPY NEXT 1 FIELDS ISBN,QTYRCVD TO Update FOR QTYRCVD>10000
USE Inv INDEX Isbn
SELE SECO
USE Update
STORE T TO mupdate
STORE '                           '  TO misbn
@ 1,1  SAY 'ISBN NUMBER	   QTY     TITLE'
STORE 2 TO line
SET COLON OFF
DO WHILE mupdate
   @ line,1   GET misbn PICTURE "99999999999-!"
   READ NOUPDATE
   IF .NOT. misbn = ' '
      SELE PRIM
      FIND &misbn
      IF #=0
         @ line,20 SAY misbn+'  IS NOT IN THE DATABASE'
         LOOP
      ENDIF
      @ line,20 SAY TITLE
      SELE SECO
      APPEND BLANK
      @ line,15 GET QTYRCVD
      READ NOUPDATE
      CLEAR GETS
      REPLACE ISBN WITH misbn
      SELE PRIM
      REPLACE QTYONHAND WITH QTYONHAND+QTYRCVD, LASTRCV WITH
                                                DATE() NOUPDATE
      IF line<23
         STORE line+1 TO line
      ELSE
         ?
      ENDIF
      STORE '           ' TO misbn
   ELSE
      STORE F TO mupdate
  ENDIF
ENDDO

SET COLON ON
SELE SECO
USE
SELE PRIM
USE Onorder INDEX O-isbn
UPDATE FROM Update ON ISBN RANDOM ADD QTYRCVD
GO TOP
STORE 0 TO excess
STORE '   '  TO misbn
DO WHILE .NOT. EOF
   IF ORDERSIZE>QTYRCVD .AND. ISBN=misbn .AND. excess>0
      REPL QTYRCVD WITH QTYRCVD+excess
   ENDIF
   IF QTYRCVD>ORDERSIZE
     STORE QTYRCVD-ORDERSIZE TO excess
     STORE ISBN TO misbn
   ENDIF
   IF ORDERSIZE<=QTYRCVD
      DELETE
   ENDIF
   SKIP
ENDDO

SELE PRIM
USE inv INDEX Isbn
SELE SECO
USE Update

? 'MAKE SURE THE PRINTER IS TURNED ON'
SET FORMAT TO PRINT
DO WHILE .NOT. EOF
   STORE 9 TO line
   @ 5,30 SAY 'INVENTORY UPDATE FOR '+cdate
   @ 7,15 SAY 'ISBN NUMBER'
   @ 7,35 SAY 'QTY'
   @ 7,45 SAY 'TITLE'

   DO WHILE .NOT. EOF .AND. line<55
     @ line,15 SAY ISBN
     @ line,35 SAY QTYRCVD
     STORE ISBN TO misbn
     SELE PRIM
     FIND &misbn
     @ line,45 SAY TITLE
     STORE line+1 TO line
     SELE SECO
     SKIP
   ENDDO
   EJECT
ENDDO
SET FORMAT TO SCREEN
USE
SELE PRIM
RELEASE mupdate,misbn,line,excess
RETURN
