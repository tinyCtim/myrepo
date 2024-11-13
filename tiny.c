
/*
tiny interpreter by Les Hancock

The original version was dated 10/23/1979.
This program was published in Dr. Dobb's #41 (January 1980), pages 20-7.

Update log:

8/17/2010 - lrb - strings can have apostrophes now
8/20/2010 - lrb - stdio.h version
9/15,17/2010 - lrb - minor tweaks, put all functions above main
10/7-12/2010 - lrb - added command tail support - other cosmetic mod's
12/5/2010 - lrb - added modulus operator
6/10/23 - added  #includes - changed div to divide
7/24/24 - cosmetic mod to usage display

+ - / % * == > >= < <= <>
: prints a newline then its argument
; prints its argument
->A branches to line label A
= assignment
? prompts for numeric input
! halts execution
{expression} statement   executes statement if expression is evaluated to nonzero
" opens and closes a string
` opens a comment
' closes the comment

Expressions evaluate right to left. All identifiers must be single
lowercase characters. Line labels must be single uppercase characters.
*/

/* value types */

#define ident 0
#define label 1
#define constant 2
#define string 3

/* operators */

#define plus 1
#define minus 2
#define times 3
#define divide 4
#define getsp 5
#define print 6   /* print with newline */
#define prt 7   /* print sans newline */
#define gotox 8
#define eq 9
#define gt 10
#define ge 11
#define lt 12
#define le 13
#define ne 14
#define mod 15

/* Miscellaneous parameters */

#define symbols struct a
#define values struct b
#define sbufsize 81   /* max chars in string buffer */
#define staksize 24   /* max tokens in symbol table, value stack */
#define pbufsize 3001   /* max chars in the program buffer */
#define lcomment '`'
#define rcomment '\''
#define linefeed '\r'
#define newline '\n'
#define yes 1
#define green yes   /* for use with <flag> */
#define no 0
#define red no   /* for use with <flag> */

/* error codes */

#define lvalerr 1   /* lvalue error */
#define fopnerr 2   /* file open error */
#define ovrbuferr 3   /* program buffer overflow */
#define iferr 6   /* if - then error */
#define nolablerr 7   /* missing label */
#define idlaberr 8   /* attempt to use a label as lvalue */

#include <stdio.h>
#include <stdlib.h> // 6/10/23
#include <string.h> // 6/10/23
#include <ctype.h> // 6/10/23

/* symbol table, symbol table pointer */

symbols {char symbol;   /* may be ident or label */
union {
  int integer;   /* if symbol is ident */
  char *linex;   /* if symbol is label */
} quid;
} symtab[staksize], *symptr;

/* value stack, value stack pointer */

values {
int type;   /* may be ident, label, constant, string */
union {
   symbols *ptrsym;   /* if type is ident or label */
   char *substring;   /* if type is string */
} quod;
int value;   /* ignore if type is label or string */
} valuestack[staksize], *valsptr;

char progbuf[pbufsize], *bufptr, strings[sbufsize], *strptr;
int operatorstack[staksize], *opsptr;
int incomment, instring;
char flag;

/* print error message and set flag to stop further processing. */

void err(int errno) // lrb - 6/12/23
{
   switch(errno) {
   case lvalerr:
      printf("\n= wants lvalue");
      break;
   case fopnerr:
      printf("\nfile won't open");
      break;
   case ovrbuferr:
      printf("\noverflows input buffer");
      break;
   case iferr:
      printf("\nif-clause error");
      break;
   case nolablerr:
      printf("\nneed label");
      break;
   case idlaberr:
     printf("\nlabel must follow ->");
   }
   flag = red;   /* halt program */
}

/*
At this point the scanner has filled the operand and operator stacks.
<evaluate> pops operators and operands and carries out the prescribed
actions.
*/

int evaluate()
{
   values *val;
   if (flag == red)
      return (0);
   while (--opsptr >= operatorstack && valsptr > valuestack) {
      val = --valsptr;
      --valsptr;
      switch (*opsptr) {
      case plus:   /* binary operators */
      case minus:
      case times:
      case divide:
      case eq:
      case gt:
      case ge:
      case lt:
      case le:
      case ne:
      case mod:
         switch (*opsptr) {
         case plus:
            valsptr->value = valsptr->value + val->value;
            break;
         case minus:
            valsptr->value = valsptr->value - val->value;
            break;
         case times:
            valsptr->value = valsptr->value * val->value;
            break;
         case divide:
            valsptr->value = valsptr->value / val->value;
            break;
         case mod:
            valsptr->value = valsptr->value % val->value;
            break;
         case eq:
            if (valsptr->value == val->value)
               valsptr->value = 1;
            else
               valsptr->value = 0;
            break;
         case gt:
            if (valsptr->value > val->value)
               valsptr->value = 1;
            else
               valsptr->value = 0;
            break;
         case ge:
            if (valsptr->value >= val->value)
               valsptr->value = 1;
            else
               valsptr->value = 0;
            break;
         case lt:
            if (valsptr->value < val->value)
               valsptr->value = 1;
            else
               valsptr->value = 0;
            break;
         case le:
            if (valsptr->value <= val->value)
               valsptr->value = 1;
            else
               valsptr->value = 0;
            break;
         case ne:
            if (valsptr->value != val->value)
               valsptr->value = 1;
            else
              valsptr->value = 0;
         }
         (valsptr++)->type = constant;   /* ++ puts valsptr back on stack */
         break;
      case getsp:   /* special binary operator */
         if (valsptr->type == ident) {   /* must be lvalue */
             valsptr->value = valsptr->quod.ptrsym->quid.integer
              = val->value;
             ++valsptr;
         }
         else
            err(lvalerr);
         break;
      default:   /* unary operators */
      switch (*opsptr) {
      case print:   /* print with newline */
         if (val->type == constant || val->type == ident)
            printf("\n%d", val->value);
         else   /* must be string */
            printf("\n%s", val->quod.substring);
         break;
      case prt:   /* print sans newline */
         if (val->type == constant || val->type == ident)
            printf("%d", val->value);
         else
            printf("%s", val->quod.substring);
         break;
      case gotox:
         if (val->type == label)   /* must be label */
            bufptr = val->quod.ptrsym->quid.linex;
         else
            err(nolablerr);
      }
      goto getout;
      }
   }
getout:  return ((--valsptr)->value);   /* return value */
}

/*
Read a new (buffered) character from the input file, ignoring linefeeds
and comments. Note that <incomment> indicates how deeply we're nested in
comments.
*/

int readchar(fp) FILE *fp;
{
   int c;
   while ((c = fgetc(fp)) == linefeed)
      ;
   if (c == lcomment)
      ++incomment;
   else if (c == rcomment && !instring)
      --incomment;
   if (incomment || (c == rcomment && !instring))
      return (readchar(fp));
   else
      return (c);
}

/*
Read the contents of named file into the input buffer. Strip off labels,
comments and all blanks not inside "".
*/

int prescan(name) char *name;
{
int c;
FILE *filedescr;
if ((filedescr = fopen(name, "r")) == 0) { /* open for buffer input */
   err(fopnerr);
   return (0);   /* report failure to open file */
   }
incomment = 0;   /* see <readchar> */
instring = no;
do {
   c = readchar(filedescr);   /* get next non-linefeed, non-comment from file */
   if (c == ' ' && !instring)   /* ignore blanks not in strings */
      continue;
   if (c == '"')
      instring ^= yes;   /* if yes make no, if no make yes */
   if (bufptr < &progbuf[pbufsize]) {
      if (isupper(c) && (bufptr == progbuf || *(bufptr - 1) == newline)) {
         symptr->symbol = c;   /* put label in symbol table */
         symptr->quid.linex = bufptr;   /* put pointer in symbol table */
         ++symptr;
      }
      else /* it wasn't a label */
         *bufptr++ = c;
   }
   else {
      fclose(filedescr);
      err(ovrbuferr);
      return (0);
      }
   } while (c != EOF);
   fclose (filedescr);   /* close the input file */
   return (1);   /* report success */
}

/* Install an identifier in the symbol table. */

symbols *idinstall(c) char c;
{
   symptr->symbol = c;
   return (symptr++);   /* return pointer to the new entry */
}

/*
Look up identifier in symbol table (simple linear search). If there,
return pointer to the entry; If not, return null pointer.
*/

symbols *idlookup(c) char c;
{
   symbols *p;
   p = symtab;
   while (p < symptr) { /* <symptr> is current top of table */
      if (p->symbol == c)
         return (p);
      p++;
      }
   return (0);
}

/*
Scan a line for tokens. Carry out keyword actions (if, then, stop,
input).
*/

int scan(c) int c;
{
   switch (c) {
   case '{':   /* keyword if */
      valsptr = valuestack;
      opsptr = operatorstack;
      while ((c = *bufptr++) != newline && c != EOF && flag == green && scan(c))
         ;
      if (c == newline || c == EOF || flag != green) {
         err(iferr);
         return (0);
       }
      if (evaluate()) {   /* finish the line */
         valsptr = valuestack;
         opsptr = operatorstack;
         return (1);
       }
      while (*bufptr++ != newline)   /* skip to next line */
         ;
      return (0);
   case '}':   /* keyword then */
      return (0);
   case '!':   /* keyword stop */
      flag = red;   /* this will stop <evaluate()> and <main()> */
      return (0);   /* no more scanning this line */
   case '?':   /* keyword input */
      printf("\n?");   /* print prompt character */
      scanf("%d", &(valsptr++)->value);   /* get input */
      break;
   case '"':   /* keyword " */
      valsptr->type = string;
      (valsptr++)->quod.substring = strptr;
      while (*bufptr !='"')
         *strptr++ = *bufptr++;
      *strptr++ = 0;   /* terminate substring with 0 */
      ++bufptr;   /* skip the " */
      break;
   case '+':
      *opsptr++ = plus;
      break;
   case '-':   /* could be minus (-) or neg or goto (->) */
       if (*bufptr == '>') {   /* it's goto */
          if (isupper(*++bufptr))   /* next token must be label */
             *opsptr++ = gotox;
          else
             err(nolablerr);
    }
    else if (!islower(*(bufptr - 2))   /* char preceding - not identifier */
       && !isdigit(*(bufptr - 2))   /* and not a digit */
       && isdigit(*bufptr)) {   /* it's neg */
       scan(*bufptr);   /* get the integer */
    }
    else   /* it's minus */
       *opsptr++ = minus;
    break;
   case '*':
      *opsptr++ = times;
      break;
   case '/':
      *opsptr++ = divide;
      break;
   case '%':
      *opsptr++ = mod;
      break;
   case '<':
      if (*bufptr == '=') {
         *opsptr++ = le;
         ++bufptr;
         }
      else if (*bufptr == '>') {
         *opsptr++ = ne;
         ++bufptr;
         }
      else
         *opsptr++ = lt;
      break;
   case '=':
      if (*bufptr == '=') {
         *opsptr++ = eq;
         ++bufptr;
         }
      else
         *opsptr++ = getsp;
      break;
   case ':':   /* print with newline */
      *opsptr++ = print;
      break;
   case ';':   /* print sans newline */
      *opsptr++ = prt;
      break;
   case '>':   /* could be ge (a>=b) or gt (a>b) */
      if (*bufptr == '=') {
         *opsptr++ = ge;
         ++bufptr;
         }
      else
         *opsptr++ = gt;
      break;
   default:   /* we have an operand (label, ident, constant) or an error */
      if (isupper(c)) {   /* label */
         if (*(bufptr - 2) == '>') {   /* must follow goto */
            if ((valsptr->quod.ptrsym = idlookup(c)))   /* in symtab */
               (valsptr++)->type = label;
            else
               err(nolablerr);
            }
         else
            err(idlaberr);
         }
      else if (islower(c)) {   /* identifier */
         /* if not in symbol table, install it  */
         if ((valsptr->quod.ptrsym = idlookup(c)) == 0)
            valsptr->quod.ptrsym = idinstall(c);
         valsptr->value = valsptr->quod.ptrsym->quid.integer;
         (valsptr++)->type = ident;
         }
      else if (isdigit(c)) {  /* constant */
/*
accumulate value, put in operand stack. note that if this is a recursive
call from case '-', backing up one char (in atoi(bufptr - 1)) includes
the - and makes the number negative. otherwise <scan> will have been
called with argument *bufptr++, so backing up one is necessary to get
the first digit of a positive number.
*/
         valsptr->value = atoi(bufptr - 1);
         (valsptr++)->type = constant;
         while (isdigit(*bufptr))
            ++bufptr;   /* advance to next nondigit */
         }
      else {   /* error */
         printf("\ncan't scan %c", c);
         err(0);   /* no further message needed */
         }
   }
   return (1);
}

int main(argc,argv) int argc;char *argv[];
{
   int c;
   char name[20];
   flag = green;   /* a red <flag> halts the program */
   bufptr = progbuf;   /* set buffer ptr to head of buffer */
   symptr = symtab;   /* set symbol table pointer */
   printf("\ntiny interpreter by Les Hancock\n");
   printf("\nUsage ./tiny [file.TIN]\n");
   if (argc == 2) strcpy(name,argv[argc-1]);
   else {
      printf("\nName of program: ");
      fgets(name,20,stdin);
      name[strlen(name)-1] = 0;   /* replace newline with 0 */
      }
   if (prescan(name)) {   /* source file read successfully */
      bufptr = progbuf;   /* reset buffer pointer */
      while (flag == green) {
         valsptr = valuestack;   /* set value stack pointer */
         opsptr = operatorstack;   /* set operator stack ptr */
         strptr = strings;   /* set string pointer */
         /* scan a line for tokens. newline ends line. */
         while ((c = *bufptr++) != newline && c != EOF
            && flag == green && scan(c))
                ;
         if (c == EOF) flag = red;
         evaluate();
         }
      }
   return (1);
}

