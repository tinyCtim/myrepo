
* Program .... : MENU2-3.CMD
* Notes ...    : This program deletes records from the Customer File.

SET INDEX TO Customer,Custid,Zip
STORE T TO delerec
STORE F TO drec
ERASE

DO WHILE delerec
 STORE '                             ' TO mname
 @ 21,1 SAY 'ENTER THE NAME TO BE DELETED' GET mname
 READ NOUPDATE

 IF mname = '                             '
  STORE F TO delerec
  LOOP
 ENDIF

 STORE !(mname) TO mname
 FIND &mname

 IF #=0
  ERASE
  @ 22,1 SAY TRIM(mname)+' IS NOT IN THE DATABASE'
  LOOP
 ENDIF

 @ 22,0
 IF #>0
  STORE # TO start,placemark
  SKIP
  IF NAME=mname .AND. .NOT. EOF
   ERASE
   @ 1,1 SAY 'MULTIPLE RECORDS FOR '+mname
   SKIP -1
   DISPLAY NAME,ADDRESS WHILE NAME=mname
   SKIP -1
   STORE # TO stop
   STORE T TO test
   DO WHILE test
    INPUT 'ENTER NUMBER FROM LEFT COLUMN - 0 TO ABORT' TO placemark
    IF placemark=0 .OR. (placemark>=start .AND. placemark<=stop)
     STORE F TO test
    ENDIF
   ENDDO
  ENDIF
  IF placemark>0
   GO placemark
   SET FORMAT TO Menu2-3
   READ
   SET FORMAT TO SCREEN
   INPUT 'DELETE THIS RECORD (Y/N)?' TO query
   IF query
    DELETE
    STORE T TO drec
   ELSE
    RECALL
   ENDIF
  ENDIF 
ENDDO

IF drec
 ERASE
 DISPLAY OFF NAME,ADDRESS FOR *
 INPUT 'FINISH DELETING THESE RECORDS (Y/N)?' TO query2
 IF query2
  PACK
 ELSE
  RECALL ALL
 ENDIF
ENDIF

RELEASE editrec,mname,placemark,drec,query,query2,test
RETURN
