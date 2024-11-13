#include <stdio.h>

// ref: https://www.geeksforgeeks.org/ruth-aaron-numbers/
// lrb - 10/28/21

/*
N = 714 
Sum of Proper Divisors of N (714) = 2 + 3 + 7 + 17 = 29 
Sum of Proper Divisors of N+1 (715) = 5 + 11 + 13 = 29
Therefore, N is a Ruth-Aaron number.
*/

/*
(5, 6), (24, 25), (49, 50), (77, 78), (104, 105), (153, 154), (369,
370), (492, 493), (714, 715), (1682, 1683), (2107, 2108)
*/
 
// Function to find prime divisors of
// all numbers from 1 to N
int Sum(int N)
{
    int SumOfPrimeDivisors[3000] = { 0 };
// this is Sieve of Eratosthenes
    for (int i = 2; i <= N; ++i) {
// if the number is prime
        if (!SumOfPrimeDivisors[i]) {
            // add this prime to all its multiples
            for (int j = i; j <= N; j += i) {
                SumOfPrimeDivisors[j] += i;
            }
        }
    }
    return SumOfPrimeDivisors[N];
}
 
// Function to check Ruth-Aaron number
int RuthAaronNumber(int n)
{
    if (Sum(n) == Sum(n + 1))
        return 1;
    else
        return 0;
}
 
// Driver code
int main()
{
    for (int N=2;N<3000;N++) {
        if (RuthAaronNumber(N)) printf("\n%d %d",N,N+1);
        }
    printf("\n");
    return 0;
}

