/*
find the minimum value in an array of integers
a recursive solution in C
*/
/* ed davis - 4/6/22 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define ARR_SIZE 16
#define randnum(min, max) \
((rand() % (int)(((max) + 1) - (min))) + (min))
int minf(int x, int y) {
return x < y ? x : y;
}
int minarr(int arr[], int n) {
return n == 0 ? arr[0] : minf(arr[n - 1], minarr(arr, n - 1));
}
int main() {
int arr[ARR_SIZE], i;
time_t t;
srand((unsigned) time(&t));
for (i = 0; i < ARR_SIZE; ++i) {
arr[i] = randnum(-100, 100);
printf("%d ", arr[i]);
}
printf("\n");
printf("%d\n", minarr(arr, ARR_SIZE));
return 0;
}

