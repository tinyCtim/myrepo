
* Program .... : MENU4-1.CMD
* Notes ...    : This program adds records to the Inventory File.

SET INDEX TO Isbn,Author,Title,Pubcode,Subject
SELE SECO
USE Publish INDEX Pubid,Pubname
SELE PRIM
STORE T TO addrec
ERASE
STORE '             ' TO misbn
@ 23,1 SAY 'LAST ENTRY '+lastentry

DO WHILE addrec
 @ 21,1 SAY "ENTER NEW ISBN NUMBER" GET misbn PICTURE;
 "99999999999-!"
 READ NOUPDATE
 @ 20,0
 
 IF misbn = ' '
  STORE F TO addrec
  LOOP
 ENDIF

 DO Isbntest
 
 IF .NOT. validtest
  @ 20,1 SAY 'INVALID ISBN NUMBER'
  LOOP
 ENDIF
 
 FIND &misbn
 
 IF #>0
  @ 20,1 SAY 'THE BOOK '+ISBN+' NUMBER IS ALREADY IN THE INVENTORY'
  LOOP
 ENDIF
 
 SELE SECO
 SET EXACT ON
 FIND &mpub
 IF #=0
  SET FORMAT TO Menu4-1A
  APPEND BLANK
  READ NOUPDATE
  REPL PUBID WITH mpub
 ENDIF

 SELE PRIM
 SET EXACT OFF
 APPEND BLANK
 SET FORMAT TO Menu4-1
 READ NOUPDATE
 REPL ISBN WITH misbn,PUBCODE WITH mpub
 SET FORMAT TO SCREEN
 STORE '             ' TO misbn
ENDDO
RELEASE addrec,misbn,mpub
RETURN

