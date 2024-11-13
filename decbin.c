
// this program decodes "binary" files

// by this we mean text files like
// 01001100 01100101 01100101 00100000 01001100 01100101 01100101 00001010 
// which are the ASCII codes (in binary) for Lee Lee

// https://www.facebook.com/groups/299317782048/permalink/10159528251382049/

// aaron west - 4/25/21

// if the file decbin.enc contains 01001100 01100101 01100101 00100000 01001100 01100101 01100101 00001010 
// decbin < decbin.enc
// would display
// Lee Lee

#include<stdio.h>
int main(){
	int i=0;
	int b=0,c=0;
	while((c=getchar())!=-1)
		{
		if(((unsigned)(c-48))<2) // if(c=='0'||c=='1')
			{
			b=b+b+(c&1);
			// preincrement i, bitwise and the rightmost 3 bits with 1s
			// result will be 0 when i is 8, 16, etc.
			// using the unary ! on this would give 1, i.e. true
			if(!(++i&7))
				{
				putchar(b);
				b=0;
				}
			}
		}
	putchar('\n');
	return 0;
	}

