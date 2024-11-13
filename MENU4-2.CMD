
* Program .... : MENU4-2.CMD
* Notes        : This program edits Inventory File records.

SET INDEX TO Isbn,Author,Title,Pubcode,Subject
SELE SECO
USE Publish INDEX Pubid
STORE T TO editrec
ERASE
DO WHILE editrec
 SELE PRIM
 STORE '             ' TO misbn
 @ 21,1 SAY "ENTER THE ISBN NUMBER" GET misbn PICTURE;
 "99999999999-!"
 READ NOUPDATE
 @ 20,0
 IF misbn = ' '
  STORE F TO editrec
  LOOP
 ENDIF
 FIND &misbn
 IF #=0
  DO Isbntest
  IF .NOT. validtest
   @ 20,1 SAY misbn+' IS AN INVALID ISBN NUMBER'
  ELSE
   @ 20,1 SAY misbn+ ' IS NOT IN THE DATABASE'
  ENDIF
  LOOP   
 ENDIF
 STORE PUBCODE TO mpub
 SELE SECO
 FIND &mpub
 SELE PRIMARY
 SET FORMAT TO Menu4-1
 READ
 SET FORMAT TO SCREEN
 CLEAR GETS
ENDDO
RELEASE editrec,misbn,mpub,validtest 
RETURN

