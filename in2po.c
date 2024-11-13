
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
in2po.c - tct - 3/15/15 12/22/21

This is a simple infix to postfix expression translator for
propositional logic expressions. At most four variables, p,q,r and s,
may be used.
*/

#define size 5
struct stack {
 int stk[size],top;
 } st;

void push(int item) {
 st.top++;
 st.stk[st.top]=item;
 }

int pop() {
 int item;
 item=st.stk[st.top];
 st.top--;
 return(item);
 }

void usage() {
 printf("\nin2po.c - tct - 12/22/21");
 printf("\nUsage: in2po -i \"infix_expression\"\n");
 exit(1);
 }

int main(int argc,char *argv[]) {

 char prop[50],pout[50],chr;
 unsigned int i,oidx;
 st.top=-1;
 oidx=0;

 if (argc==1) usage();
 for (i=1;i<argc;i++) {
  if (strcmp(argv[i],"-i")==0) {i++;strcpy(prop,argv[i]);}
  else usage();
  }

 printf("\nThe infix proposition being tested is %s\n\n",prop);
  
 for (i=0;i<strlen(prop);++i) {
  chr=prop[i];
  switch(chr) {
   case 'p': // p,q,r,s
   case 'q':
   case 'r':
   case 's':
    pout[oidx++]=chr;
    break;
   case '!': // (,!
   case '(':
    push(chr);
    break; 
   case 'v': // binary relation
   case '^':
   case '>':
   case '=':
    while (
     st.stk[st.top]=='v'||
     st.stk[st.top]=='^'||
     st.stk[st.top]=='>'||
     st.stk[st.top]=='!') {
     pout[oidx++]=pop();
     }
    push(chr);
    break;
   case ')':
    while (st.stk[st.top]!='(') {
     pout[oidx++]=pop();
     }
    pop();
   }
  }
 while (st.top!=-1) {
  pout[oidx++]=pop();
  }
 pout[oidx]=(int)NULL;  
 printf("\nThe postfix is %s\n\n",pout);
 printf("\n");
 exit(0);
 }

