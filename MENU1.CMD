
* Program .... : MENU1.CMD
* Notes ...    : This program stores the date to a memory file

CLEAR GETS
STORE '01 02 03 04 05 06 07 08 09 10 11 12' TO monthmask
STORE '31 28 31 30 31 30 31 31 30 31 30 31' TO daymask
STORE 'JANFEBMARAPRMAYJUNJULAUGSEPOCTNOVDEC' TO calendar
STORE T TO baddate
ERASE
@ 7,0

DO WHILE baddate
 @ 7,1 SAY 'ENTER THE DATE AS MM/DD/YY' GET mdate PICTURE '99/99/99'
 READ
 @ 8,0
 SET DATE TO &mdate
 STORE DATE() TO mdate
 
 IF $(mdate,1,2)$monthmask
  STORE $(daymask,@($(mdate,1,2),monthmask),2) TO days

  IF $(mdate,1,2)='02' .AND. $(mdate,7,2)$'08,12,16,20,24,28,32,36'
   STORE '29' TO days
  ENDIF  
 
  IF $(mdate,4,2)>='01' .AND. $(mdate,4,2)<=days
   STORE F TO baddate
  ELSE
   @ 8,20 SAY 'INVALID DAY'
  ENDIF
  
 ELSE
  @ 8,1 SAY 'INVALID MONTH'
 ENDIF
ENDDO

@ 8,0 
SET DATE TO &mdate
STORE DATE() TO mdate
STORE $(calendar,@($(mdate,1,2),monthmask),3) TO cdate
STORE $(mdate,4,2)+' '+cdate+' 20'+$(mdate,7,2) TO cdate
SAVE ALL LIKE ?date TO DATE
RELEASE month,day,monthmask,daymask,calendar,days,baddate
RETURN

