#include <windows.h>
#include <stdio.h>

// https://www.go4expert.com/articles/download-file-using-urldownloadtofile-c-t28721/

#define MAX_LINE 512

int main()
{
    char destination[MAX_LINE] = "url.txt";
    printf("\nEnter url you want to read : ");
    char str[100];
    fgets(str, 100, stdin);
    char url[MAX_LINE];
    strcpy(url, str);
    url[strlen(url)-1] = 0;
    printf("\n%s\n", url);

    char buffer[MAX_LINE];

    HRESULT    dl;
    
    typedef HRESULT (WINAPI * URLDownloadToFileA_t)(LPUNKNOWN pCaller, LPCSTR szURL, LPCSTR szFileName, DWORD dwReserved, void * lpfnCB);
    URLDownloadToFileA_t xURLDownloadToFileA;
    xURLDownloadToFileA = (URLDownloadToFileA_t)GetProcAddress(LoadLibraryA("urlmon"), "URLDownloadToFileA");

    dl = xURLDownloadToFileA(NULL, url, destination, 0, NULL);

    sprintf( buffer, "Downloading File From: %s, To: %s", url, destination);

    if(dl == S_OK)
    {
        sprintf(buffer, "File Successfully Downloaded To: %s", destination);
        printf("\n%s\n", buffer);
    } 
    else if(dl == E_OUTOFMEMORY) 
    {
        sprintf(buffer, "Failed To Download File Reason: Insufficient Memory");
        printf("\n%s\n", buffer);
        return 0;
    } 
    else 
    {
        sprintf( buffer, "Failed To Download File Reason: Unknown");
        return 0;
    }
}
