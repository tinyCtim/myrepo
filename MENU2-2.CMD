
* Program .... : MENU2-2.CMD
* Notes ...    : This program edits the Customer File records.

STORE T TO editrec
DO WHILE editrec
 ERASE
 STORE '                             ' TO mname
 @ 21,1 SAY "ENTER THE CUSTOMER'S NAME OR CUSTOMER NUMBER " GET mname
 READ NOUPDATE

 IF mname = '                             '
  STORE F TO editrec
  LOOP
 ENDIF

 IF VAL(mname)>100000
  SET INDEX TO Custid,Customer,Zip
  STORE $(mname,1,6) TO findcust
 ELSE
  SET INDEX TO Customer,Custid,Zip
  STORE !(TRIM(mname)) TO findcust
 ENDIF

 FIND &findcust

 IF #=0
  @ 22,1 SAY findcust+' IS NOT IN THE DATABASE'
  LOOP
 ENDIF

 @ 22,0

 IF #>0
  STORE # TO placemark
  IF .NOT. CUSTID = findcust
   SKIP
   IF NAME = findcust .AND. .NOT. EOF
    ERASE
    @ 1,1 SAY 'MULTIPLE RECORDS FOR '+findcust
    SKIP -1
    DISPLAY NAME,ADDRESS WHILE NAME = findcust
    INPUT 'ENTER NUMBER FROM LEFT COLUMN - 0 TO ABORT' TO placemark
   ENDIF for case name = findcust
  ENDIF for case where we selected by customer name
  IF placemark>0
   GO placemark
   SET FORMAT TO Menu2-2
   READ
   CLEAR GETS
   SET FORMAT TO SCREEN
  ENDIF for valid record number
 ENDIF for case where we found the record
ENDDO

RELEASE editrec,mname,placemark,findcust
RETURN
