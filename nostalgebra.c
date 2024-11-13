#include<stdio.h>

/*
nostalgebra.c - 10/1,3,5/20 - lrb
https://facebook.com/groups/299317782048/permalink/10158984124932049/

This program solves a 2 x 2 system of linear equations
*/

float det(float m[2][2]) { // compute the determinant of m
	return m[0][0] * m[1][1] - m[0][1] * m[1][0];
	}

void main(void) {
	printf("\nnostalgebra.c - 10/5/20 - lrb\n\n");
	float c[2][3], m[2][2], detm, detx, dety;
	int i, j;
	for (i = 0; i <= 1; i++) { // load c
		for (j = 0; j <= 2; j++) {
			printf("Enter row %d column %d ", i + 1, j + 1);
			scanf("%f", &c[i][j]);
			}
		}
	m[0][0] = c[0][0]; m[0][1] = c[0][1]; // load m from c
	m[1][0] = c[1][0]; m[1][1] = c[1][1];
	detm = det(m);
	if (detm == 0) printf("\ndeterminant = 0\n"); // no solution	
	else {
		m[0][0] = c[0][2]; m[0][1] = c[0][1]; // load m from c
		m[1][0] = c[1][2]; m[1][1] = c[1][1];
		detx = det(m);
		m[0][0] = c[0][0]; m[0][1] = c[0][2]; // load m from c
		m[1][0] = c[1][0]; m[1][1] = c[1][2];
		dety = det(m);
		printf("\nx = %2.2f", detx / detm);
		printf("\ny = %2.2f\n", dety / detm);
		}
	}

