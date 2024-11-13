
* Program .... : MENU.CMD
* Notes ...... : This is the Main Menu.

* Adding Mailing List and Labels etc. - 6/21/24

SET BELL OFF
SET TALK OFF
RESTORE FROM Date ADDITIVE
SET DATE TO &mdate
STORE ' ' TO choice

DO WHILE .NOT. choice = '8'
 ERASE

 @ 5,31 SAY "Lee's Books"
 @ 7,31 SAY cdate
 @ 10,25 SAY '1 - Change the Date'
 @ 11,25 SAY '2 - Customer File'
 @ 12,25 SAY '3 - Mailing Lists and Labels'
 @ 13,25 SAY '4 - Inventory'
 @ 14,25 SAY '5 - Sales Orders'
 @ 15,25 SAY '6 - Invoices'
 @ 16,25 SAY '7 - Accounts Receivables'
 
 @ 17,25 SAY '8 - dBASE II . Prompt'

 @ 19,25 SAY '0 - Quit dBASE II'
 @ 21,29 SAY 'Pick One'

 STORE ' ' TO choice
 @ 21,24 GET choice
 READ NOUPDATE
 
 IF choice = '0'
  QUIT
 ENDIF

 IF choice $'1234567'
  STORE 'MENU'+choice TO selection
  DO &selection
 ENDIF

 ERASE

ENDDO 
