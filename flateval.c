
// https://stackoverflow.com/questions/1384811/code-golf-mathematical-expression-evaluator-that-respects-pemdas
// search for flatEval

// "-1^(-3*4/-6)" -> 1
// "-2^(2^(4-1))" -> 256
// "2*6/4^2*4/3" -> 1
// "(1/2)^(9*9*9)" -> 3.54106e-220

// written by Ed Davis

// command tail must be an expression which uses single digit #s and is
// enclosed by double quotes

#include <stdio.h>
#include <math.h>
#include <string.h>

#define TOPPRI '3'
#define getsym() token = *x++;

const char opByPri[] = "+0-0*1/1^2";
char token, *x;
double rhEval(int);

#pragma argsused
int main(int ac, char **av) {
	x = av[1];
	getsym();
	printf("%g\n", rhEval('0'));
	return 0; // lrb - 7/21/23
}

double flatEval(char op, double a, double b) {
		switch (op) {
		case '*': return a * b;
		case '/': return a / b;
		case '+': return a + b;
		case '-': return a - b;
		case '^': return pow(a, b);
	}
	return 0;
}

double factor(void) {
	double d;
	char t = token;
	getsym();
	switch (t) {
		case '-': return -factor();
		case '0': case '1': case '2': case '3': case '4':
		case '5': case '6': case '7': case '8': case '9':
			return t - '0';
		case '(': d = rhEval('0');
			getsym();
	}
	return d;
}

double rhEval(int pri) {
	double v; char *q;
	if (pri >= TOPPRI)
		return factor();
	v = rhEval(pri + 1);
	while ((q = strchr(opByPri, token)) != NULL && q[1] == pri) {
		char op = token;
		getsym();
		v = flatEval(op, v, rhEval(pri + 1));
	}
	return v;
}

