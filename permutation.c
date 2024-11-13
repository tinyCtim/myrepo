#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>

// https://www.codeconvert.ai/python-to-c-converter was used to create this
// lrb - 6/10/24

// Function to check if a permutation satisfies the equation
bool satisfies_equation(int *perm) {
    int product_sum = perm[0]*perm[1] + perm[2]*perm[3] + perm[4]*perm[5] + perm[6]*perm[7] + perm[8]*perm[9];
    int sum_1 = perm[7] + perm[0];
    int sum_2 = perm[1] + perm[2];
    int sum_3 = perm[3] + perm[4];
    int sum_4 = perm[5] + perm[6];
    int sum_5 = perm[8] + perm[9];
    bool bool_condition = sum_1 == 11 && sum_2 == 11 && sum_3 == 11 && sum_4 == 11 && sum_5 == 11;
    return product_sum == 121 && bool_condition && perm[0] == 1;
}

// Function to generate all permutations of the numbers 1 to 10
void generate_permutations(int *perm, int index, bool *used, int *solutions, int *num_solutions) {
    if (index == 10) {
        if (satisfies_equation(perm)) {
            solutions[*num_solutions * 10] = perm[6];
            solutions[*num_solutions * 10 + 1] = perm[7];
            solutions[*num_solutions * 10 + 2] = perm[1];
            solutions[*num_solutions * 10 + 3] = perm[0];
            solutions[*num_solutions * 10 + 4] = perm[2];
            solutions[*num_solutions * 10 + 5] = perm[3];
            solutions[*num_solutions * 10 + 6] = perm[5];
            solutions[*num_solutions * 10 + 7] = perm[4];
            solutions[*num_solutions * 10 + 8] = perm[8];
            solutions[*num_solutions * 10 + 9] = perm[9];
            (*num_solutions)++;
//          if (*num_solutions == 5 || *num_solutions == 11) {
                printf("Solution found:\n");
                printf("%d x %d  %d x %d  %d x %d  %d x %d  %d x %d\n",
                       perm[6], perm[7], perm[1], perm[0], perm[2], perm[3], perm[5], perm[4], perm[8], perm[9]);
//            }
            if (*num_solutions == 12) {
                return;
            }
        }
        return;
    }

    for (int i = 0; i < 10; i++) {
        if (!used[i]) {
            used[i] = true;
            perm[index] = i + 1;
            generate_permutations(perm, index + 1, used, solutions, num_solutions);
            used[i] = false;
        }
    }
}

int main() {
    int perm[10];
    bool used[10] = {false};
    int solutions[120];
    int num_solutions = 0;
	clock_t t;
	t = clock();
    generate_permutations(perm, 0, used, solutions, &num_solutions);
	t = clock() - t;
	double time_taken = ((double)t)/CLOCKS_PER_SEC; // calculate the elapsed time
	printf("The program took %f seconds to execute", time_taken);
	return 0;
}
