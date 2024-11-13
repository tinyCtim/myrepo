
* Program .... : MENU2.CMD
* Notes ...    : This program is the Customer File Menu.

USE Customer
GO BOTTOM

IF #>0
 STORE VAL(CUSTID) TO mcustid
 STORE CUSTID+'  '+NAME+' '+ADDRESS TO lastentry
ELSE
 STORE '  ' TO lastentry
 STORE 100000 TO mcustid
ENDIF

DO WHILE T

 STORE ' ' TO choice
 ERASE
 @  2,30 SAY "   Lee's Books"
 @  4,32 SAY 'Customer Menu'
 @  6,34 SAY cdate
 @  8,25 SAY '1 - Add Customer Records'
 @  9,25 SAY '2 - Edit Customer Records'
 @ 10,25 SAY '3 - Delete Customer Records'
 @ 14,25 SAY '0 - Go Back To The Main Menu'
 @ 17,25 SAY '  - Pick One'
 @ 17,24 GET choice
 READ NOUPDATE

 DO CASE
  CASE choice='1'
   DO Menu2-1
  CASE choice='2'
   DO Menu2-2
  CASE choice='3'
   DO Menu2-3
  CASE choice='0'
   RELEASE mcustid,lastentry
   RETURN
 ENDCASE
ENDDO

