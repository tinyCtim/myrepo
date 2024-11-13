
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
proposition.c - tct - 3/19/15 12/22/21

This is a simple expression evaluator for propositional logic
expressions which have been written in postfix order. At most four
variables, p, q, r and s may be used. The output is "tautology,"
"contradiction" or "logically contingent."

Here is the "destructive dilemma" tautology.

C:\>in2po.exe -i "(((p>q)^(r>s))^(!qv!s))>(!pv!r)"

The infix proposition being tested is (((p>q)^(r>s))^(!qv!s))>(!pv!r)

The postfix is pq>rs>^q!s!v^p!r!v>

C:\>proposition.exe -p "pq>rs>^q!s!v^p!r!v>"

pq>rs>^q!s!v^p!r!v> : tautology.

Another example:

D:\my-git-repo>in2po.org -i "!p>q=pvq"

The infix proposition being tested is !p>q=pvq

The postfix is p!q>pqv=

Press any key to continue . . .

D:\my-git-repo>proposition -p "p!q>pqv="

proposition.c - tct - 3/19/2015
p!q>pqv= : tautology.

Another example

D:\my-git-repo>in2po.org -i "!(p^q)=!pv!q"

The infix proposition being tested is !(p^q)=!pv!q

The postfix is pq^!p!q!v=

Press any key to continue . . .

D:\my-git-repo>proposition -p "pq^!p!q!v="

proposition.c - tct - 3/19/2015
pq^!p!q!v= : tautology.

*/

#define size 5

struct stack {
 int stk[size],top;
 } st;

// truth table for implies, and, or, equals

char tt(char c,char p,char q) {
 switch(c) {
  case '>': // implies
   if ((p=='1')&&(q=='0')) return('0');else return('1');
  case '^': // and
   if ((p=='1')&&(q=='1')) return('1');else return('0');
  case 'v': // or
   if ((p=='0')&&(q=='0')) return('0');else return('1');
  case '=': // equals
   if (p==q) return('1');else return('0');
 }}

void push(int item) {
 st.top++;st.stk[st.top]=item;
 }

int pop() {
 int item;
 item=st.stk[st.top];st.top--;
 return(item);
 }

void usage() {
 printf("\nUsage: proposition -p \"postfix_expression\"\n");
 exit(1);
 }

int main(int argc,char *argv[]) {

 printf("\nproposition.c - tct - 12/22/21");

 char p,q,r,s,sp[50],prop[50],chr,w,w1,w2,*ss;
 char *tc[]={"tautology","contradiction","logically contingent"};
 unsigned int i,tautf=0,tautt=0,taut;

 if (argc==1) usage();
 for (i=1;i<argc;i++) {
  if (strcmp(argv[i],"-p")==0) {i++;strcpy(sp,argv[i]);}
  else usage();
  }

// cycle thru all 16 possible values of p, q, r and s ('0' and '1')

 st.top=-1;

 for (p='0';p<'2';++p) {
 for (q='0';q<'2';++q) {
 for (r='0';r<'2';++r) {
 for (s='0';s<'2';++s) {

  strcpy(prop,sp);

// replace all p's, q's, r's and s's w/ '0' or '1'

  while ((ss=strchr(prop,'p'))!=NULL) {ss[0]=p;}
  while ((ss=strchr(prop,'q'))!=NULL) {ss[0]=q;}
  while ((ss=strchr(prop,'r'))!=NULL) {ss[0]=r;}
  while ((ss=strchr(prop,'s'))!=NULL) {ss[0]=s;}

  for (i=0;i<strlen(prop);++i) {
   chr=prop[i];
   switch(chr) {
    case '0': // '0' or '1'
    case '1':
     push(chr);
     break;
    case '!': // negation
     w=pop();
     if (w=='0') push('1');else push('0');
     break;
    case '>': // binary relations
    case '^':
    case 'v':
    case '=':
     w2=pop();w1=pop();push(tt(chr,w1,w2));
   }}

  if ('1'==pop()) tautt++;else tautf++; // bump up true counter or false counter

  }}}}

 if (tautf==0) taut=0; // if it's never false, it's a tautology
 else if (tautt==0) taut=1; // else if it's never true, it's a contradiction
 else taut=2; // otherwise, it's logically contingent

 printf("\n%s : %s.\n",sp,tc[taut]); // report result
 printf("\n");exit(0);
 }

