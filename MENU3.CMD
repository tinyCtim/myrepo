
* Program .... : MENU3.CMD
* Notes ...... : This program is the Mailing Menu program.

USE Customer
DO WHILE T
 STORE ' ' TO choice
 ERASE
 @   2,30 SAY "Lee's Better Books"
 @ $+2,29 SAY 'Mailing Menu Program'
 @ $+2,32 SAY cdate
 @ $+2,16 SAY '1 - Print the list alphabetically'
 @ $+1,16 SAY '2 - Print the list alphabetically by zip code'
 @ $+1,16 SAY '3 - Print the list by customer number'
 @ $+1,16 SAY '4 - Select and print items from list'
 @ $+1,16 SAY '0   Get out of this menu system'
 @ $+2,20 SAY 'PICK ONE'
 @ $,15 GET choice
 READ NOUPDATE

 DO CASE
  CASE choice='1'
   DO Menu3-1
  CASE choice='2'
   DO Menu3-2
  CASE choice='3'
   DO Menu3-1
  CASE choice='4'
   DO Menu3-4
  CASE choice='0'
   RETURN
 ENDCASE
ENDDO
