
/* Routine to sum the squares of the digits of a number passed on the command line,
** then repeat on the sum
** until a repeat of a sum is found, 
** in multiple bases up to (probably) base 36.
** Inspired by a post by Lee Bradley to the Not Just Tiny C Facebook Group:
** https://www.facebook.com/groups/299317782048/permalink/10158931086097049/
** http://primepuzzle.com/not.just.tiny.c/steinhaus.tc
**
** Joel Rees, Amagasaki, Japan, Sept. 2020
*/


#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>


char chconv( int digit )
{  digit += '0';
   if ( digit > '9' )
   {  digit += 'A' - '9' - 1;
   }
/*dbg* / printf( "digit: %d:%c\n", digit, digit ); */
   return (char) digit;
}


#define MAXCONV_DIGITS 64 /* for 64 bit int CPUs */

/* buffer must be long enough for long long in binary, plus termination!
** Make it MAXCONV_DIGITS + 1 long.
*/
char * outint( char buffer[], int d, int base )
{  char * convpt = buffer + MAXCONV_DIGITS;

   * convpt = 0;
   while ( ( convpt > buffer ) && ( d > 0 ) )
   {  * --convpt = chconv( d % base );
      d /= base;
   }
   return convpt;
}


long base = 10;


int todigit( int ch )
{  char digitbuffer[ 2 ]; /* It's all we need. */
   char * endpt = digitbuffer;
   long val;

   digitbuffer[ 0 ] = (char) ch;
   digitbuffer[ 1 ] = 0;
   val = strtol( digitbuffer, &endpt, base );
   if ( endpt != digitbuffer + 1 )
   {  val = -1;
   }
   return (int) val;
}


int digsquaresum( char * digits )
{  int sum = 0; /* Even 16 bit int allows length > 655. */
   int ch = 0;

   while ( isalnum( ch = * digits++ ) )
   {  int dig = todigit( ch );
      sum += dig * dig;
   }
   return sum;
}


#define SEQUENCEMAX 64


int sequence( char * start )
{  int sum, i;
   int repeater = 0;
   static int last[ SEQUENCEMAX + 1 ];
   char newval[ MAXCONV_DIGITS + 1 ] = { 0 }; /* Note MAXCONV_DIGITS plus terminator! */

   for ( i = 0; i <= SEQUENCEMAX; ++i )
   {  last[ i ] = -1;
   }
   do 
   {  int i;
      char * convpt = newval;

      sum = digsquaresum( start );
      for ( i = SEQUENCEMAX; i > 0; --i )
      {  last[ i ] = last[ i - 1 ];
      }
      last[ 0 ] = sum;
      for ( i = 0; ( i < SEQUENCEMAX ) && ( last[ i ] != -1 ); ++i )
      {  int j;
         for ( j = i + 1; ( j <= SEQUENCEMAX ) && ( last[ j ] != -1 ); ++j )
         {  if ( last[ i ] == last[ j ] )
            {  repeater = last[ i ];
            }
         }
      } 
      convpt = outint( newval, sum, base );
      puts( convpt );
      start = convpt;
   } while ( ( sum != 1 ) && ( repeater == 0 ) && ( last[ SEQUENCEMAX ] != 0 ) );
   return repeater;
}


int main( int argc, char * args[] )
{
   if ( argc < 2 )
   {  printf( "\nUsage %s [-<base> ] <number>\n", args[ 0  ] );
      return EXIT_FAILURE;
   }
   else
   {  if ( args[ 1 ][ 0 ] == '-' )
      {  if ( args[ 1 ][ 1 ] != '?' )
         {  base = (int) strtol( args[ 1 ] + 1, NULL, 10 );
         }
         if ( ( base < 2 ) || ( argc == 2 ) )
         {  printf( "%s [-<base> ] <number>\n", args[ 0 ] );
            puts( "\tbase unimplemented." );
         }
         if ( args[ 1 ][ 1 ] == '?' )
         {  return EXIT_SUCCESS;
         }
         if ( ( base < 2 ) || ( argc == 2 ) )
         {  return EXIT_FAILURE;
         }
         printf( "\n" );
         sequence( args[ 2 ] );
      }
      else
      {  printf( "\n" );
         sequence( args[ 1 ] );
      }
   }

   return EXIT_SUCCESS;
}
