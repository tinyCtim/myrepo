
* Program .... : MENU4-3.CMD
* Notes        : This program deletes Inventory File records.

SET INDEX TO Isbn,Author,Title,Pubcode,Subject
STORE T TO delerec
ERASE
DO WHILE delerec
 STORE '             ' TO misbn
 @ 21,1 SAY "ENTER THE ISBN NUMBER" GET misbn PICTURE;
 "99999999999-!"
 READ NOUPDATE
 @ 20,0
 IF misbn = ' '
  STORE F TO delerec
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
 @ 1,1 SAY TITLE
 @ 2,1 SAY AUTHOR
 @ 3,1 SAY SUBJECT
 STORE ' ' TO QUERY
 DO WHILE .NOT. query$'YN'
  @ 5,1 SAY 'DELETE THIS BOOK (Y/N)?' GET query PICTURE '!' 
  READ
  CLEAR GETS
 ENDDO
 IF QUERY='Y'
  DELETE
 ENDIF 
ENDDO
RELEASE delerec,misbn,validtest,query
PACK
RETURN

