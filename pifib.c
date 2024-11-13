#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#define MCERR        24

/*x	STEP 1: Create a sub-directory for the plug in code.
 *	Copy this file into that directory with the same name 
 *	as your plugin and dot-c as extent. Edit the copy 
 *	following the STEPs 2 and up below.
 */

/*x	STEP 2: Code plug-in functions here: remove or change names
 *	of pi_X functions. Add more functions to form your complete 
 *	plug in library. Provide the Mxx functions with nargs,args
 *	MC calling sequence. These are your machine calls.
 */

// gives nth Fibonacci number (w/o recursion)

int Mfib(int nargs, int* args) {
	int n;
	if(nargs<1){eset(MCERR); return -1; }
	n=args[0];
	fib(n);
}
int fib(int n){
	double fab,u,v,rt5;
	rt5=pow(5,.5);
	u=pow((1+rt5)/2,n);
	v=pow((1-rt5)/2,n);
	fab=(u-v)/rt5;
	return((int)fab);
}

/*x	STEP 4: Assure #if 0 above to turn on plug-in 
 *	infrastructure. 
 */

/*	INFRASTRUCTURE...
 */

/*x	STEP 5: register your M functions in McList array. Placement 
 *	in the array determines the MC number starting with 1001.
 *	This is the only change that should be made in the code below.
 *	
 *x	STEP 6: Use buildPlugIn.sh to manufacture the shared object.
 *	Technically the plug-in is complete and plugged in. You 
 *	should see a dot-so file in your current working directory.
 *		
 *	STEP 7: Write a small test tc program that uses the plug-in
 *	functions. Don't forget the #loadMC <myPlug-in> at the top.
 *	
 *	STEP 8: Run you test tc program. Use the -l option to see
 *	that your dot-so file is loaded. You are now debugging the
 *	combo of your test tc program, and your plug-in.
 */

// define plug-in's eset to call real eset in tc
int (*callEset)(int);
int eset(int err){
	return (*callEset)(err);
}
// tcMain calls this with address of real eset
void register_eset( void (*eset)(int) )
{
    callEset = eset;
}

typedef int (*McList)(int,int*);
void naf(){
	eset(MCERR);
}
McList plugInList[] =            // do STEP 5 here...
	{ &Mfib, &naf
	};

void plugInMC(int mcno, int nargs, int *args) {
	if(mcno<1 || mcno>(sizeof(plugInList)/sizeof(void*))) {
		eset(MCERR);
	}
	else {
	    int x = plugInList[mcno-1](nargs, args);
	}
}


