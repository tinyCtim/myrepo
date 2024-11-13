
#include <windows.h>
#include <stdlib.h>
#include <stdio.h>

#define MAX_LINE 1500

#define MCERR 24

// lrb - 8/27/21

// prototypes for callback functions
void (*callEset)(int) = NULL;

// urldownloadpi.c - lrb - 8/26/21

int urldownload(int nargs, int *args) {

	char* url = (char*)args[0];

	char destination[MAX_LINE] = "url.txt";

    HRESULT    dl;
    
    typedef HRESULT (WINAPI * URLDownloadToFileA_t)(LPUNKNOWN pCaller, LPCSTR szURL, LPCSTR szFileName, DWORD dwReserved, void * lpfnCB);
    URLDownloadToFileA_t xURLDownloadToFileA;
    xURLDownloadToFileA = (URLDownloadToFileA_t)GetProcAddress(LoadLibraryA("urlmon"), "URLDownloadToFileA");

    dl = xURLDownloadToFileA(NULL, url, destination, 0, NULL);
    
    if(dl == S_OK)
    {
		return(1);
    } 
    else if(dl == E_OUTOFMEMORY)
    {
		return 0;
    }
    else
    {
		return 0;
    }
}	
	

/*	INFRASTRUCTURE...
 *	Comment out your test main and uncomment this infrastructure.
 *	first in this list is MC 1001. Change the names to functions
 *	written above. Enlarge the list for larger libraries.
 */
typedef int (*McList)(int,int*);

McList plugInList[] =
	{ &urldownload
	};

/*	code the MC above and register in McList array. Placement in the array
 *	determines the MC number starting with 1001.
 */
void plugInMC(int mcno, int nargs, int *args) {
	if (mcno<1 || mcno>(sizeof(plugInList) / sizeof(void*))) {
		callEset(MCERR);
	}
	else {
	    int x = plugInList[mcno-1](nargs, args);
	}
}

// register callbacks to specific tc functions...
void register_eset( int eset )
{
	callEset = eset;
}

