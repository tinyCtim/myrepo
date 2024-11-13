// C calculator program by C. Bradley
// with much help via YouTube and edit suggestions by Lee on 3/8/23
// added modulus operator % 3/17/23
// calculator.2.1.c

// the user specifies what operator (+ - * / %) he/she wants to use for any
// two numbers.

// https://www.youtube.com/watch?v=2kKQbFsVCq8

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main(){

   char operator;
   double num1;
   double num2;
   double result;
   char pct = '%';

   printf("\nEnter an operator (+ - * / %c ) : ", pct);
   scanf("%c", &operator);
   if (strchr("+-*/%", operator) == NULL) {
      printf("\nillegal operator\n");
      exit(1);
      }

   printf("Enter a number : " );
   scanf("%lf", &num1);

   printf("Enter a number : " );
   scanf("%lf", &num2);

   switch(operator){
      case '+':
	     result = num1 + num2;
             break;                   // break out of the switch
      case '-':
	     result = num1 - num2;
	     break;                   // break out of the switch
      case '*':
	     result = num1 * num2;
	     break;                   // break out of the switch
      case '/':
	     result = num1 / num2;
             break;                  // break out of the switch
      case '%':
	     result = (int)num1 % (int)num2;
             break;                  // break out of the switch
      }
   printf("\n%lf\n", result);
   return 0;
}
