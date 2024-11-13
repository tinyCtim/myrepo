
* Program .... : MENU4.CMD
* Notes ...    : This program is the Inventory File Menu program.

USE Inv
GO BOTTOM
IF .NOT. #=0
 STORE ISBN+'  '+TITLE TO lastentry
ELSE
 STORE '      ' TO lastentry
ENDIF

DO WHILE T
 STORE ' ' TO choice
 ERASE
 @  2,30 SAY "Lee's Books"
 @  4,32 SAY 'INVENTORY MENU'
 @  6,34 SAY cdate
 @  8,25 SAY '1 - Add Records'
 @  9,25 SAY '2 - Edit Records'
 @ 10,25 SAY '3 - Delete Records'
 @ 11,25 SAY '4 - Order Books'
 @ 12,25 SAY '5 - Update Stock'
 @ 14,25 SAY '0 - GO BACK TO MAIN MENU'
 @ 17,24 GET choice
 READ NOUPDATE

 IF choice='0'
  RELEASE lastentry,select
  RETURN
 ENDIF

 IF choice $'12345'
  STORE 'MENU4-'+choice TO select
  DO &select
 ENDIF
ENDDO
RETURN
