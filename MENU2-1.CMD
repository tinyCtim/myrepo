
* Program .... : MENU2-1.CMD
* Notes ...    : This program adds records to the Customer File.

SET INDEX TO Customer,Custid,Zip
STORE T TO addrec
DO WHILE addrec
 ERASE
 STORE '                             ' TO mname
 @ 23,1 SAY 'LAST ENTRY '+lastentry
 @ 21,1 SAY "ENTER THE NEW CUSTOMER'S NAME " GET mname
 READ NOUPDATE

 IF mname = '                             '
  STORE F TO addrec
  LOOP
 ENDIF
 
 STORE !(TRIM(mname)) TO trimname
 FIND &trimname
 STORE F TO oktoadd

 IF #>0
  ERASE
  @ 1,1 SAY 'RECORDS WHICH MATCH CANDIDATE NAME'
  DISPLAY OFF NAME,ADDRESS WHILE NAME = trimname
  INPUT "ADD THE NAME ANYWAY (Y/N)?" TO oktoadd
 ENDIF
  
 IF #=0 .OR. oktoadd
  APPEND BLANK
  STORE mcustid+1 TO mcustid
  SET FORMAT TO Menu2-1
  READ NOUPDATE
  REPLACE NAME WITH trimname,DATE WITH DATE(),;
   CUSTID WITH STR(mcustid,6)
  SET FORMAT TO SCREEN
  STORE CUSTID+'  '+NAME+' '+ADDRESS TO lastentry
 ENDIF
ENDDO

RELEASE addrec,mname,oktoadd,trimname
RETURN

