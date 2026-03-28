/******************************************************************************
 * (c) 2024 AED PROJECT - Guilherme Gameiro, Lourenço Reis
 *
 * NAME
 *   solving.c
 *
 * DESCRIPTION
 *   Support functions.
 * 
 ******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "solving.h"
#include "final_tasks.h"
#include "dfs.h"
#include "bound.h"

/******************************************************************************
 * distance()
 *
 * Arguments: l_initial - initial row
 *            c_initial - initial column
 *            l_current - current row
 *            c_current - current column
 * Returns: (int)
 *
 * Description: 
 *          Manhattan distance calculation.
 *****************************************************************************/
int distance(int l_initial, int c_initial, int l_current, int c_current) {
    return abs(c_current - c_initial) + abs(l_current - l_initial);
}


/******************************************************************************
 * matrix_alloc()
 *
 * Arguments: L - number of rows in the map
 *            C - number of columns in the map
 *            l_initial - initial row coordinate
 *            c_initial - initial column coordinate
 *            K - steps
 *            file_in - input file (pointer)
 *            l_m - submatrix first row (pointer)
 *            c_m - submatrix first column (pointer)
 *            l_matrix - submatrix number of rows (pointer)
 *            c_matrix - submatrix number of columns (pointer)
 *
 * Returns: (int **)
 *
 * Description: 
 *          Allocates a submatrix.
 *****************************************************************************/
 int **matrix_alloc(int L, int C, int l_initial, int c_initial, int K, FILE *file_in, int *l_m, int *c_m, int *l_matrix, int *c_matrix) {

    // Variable declaration and initialization of matrix and first.    
    int **matrix = NULL;
    int cell_energy;
    int i, j, l, l_aux, c, c_aux, first = 0;

    // Calculation of how many rows and columns would be extra in an allocation (2*K + 1)^2.
    int r_up = (l_initial - K < 1) ? (1 - (l_initial - K)) : 0;
    int r_down = (l_initial + K > L) ? (l_initial + K - L) : 0;
    int c_left = (c_initial - K < 1) ? (1 - (c_initial - K)) : 0;
    int c_right = (c_initial + K > C) ? (c_initial + K - C) : 0;

    // Calculation of how many rows and columns have to be allocated.
    *l_matrix = (2 * K + 1) - r_up - r_down;
    *c_matrix = (2 * K + 1) - c_left - c_right;

    // Memory allocation for the rows, considering extrapolations.
    matrix = (int**) malloc((size_t)(*l_matrix) * sizeof(int *));
    if (matrix == NULL) {
        return NULL;
    }

    // Memory allocation for the columns, considering extrapolations.
    for (i = 0; i < *l_matrix; i++) {
        matrix[i] = (int*) malloc((size_t)(*c_matrix) * sizeof(int));
        if (matrix[i] == NULL) {
            for (j = 0; j < i; j++) {
                free(matrix[j]);
            }
            free(matrix);
            return NULL;
        }
    }

    // Submatrix limits definition.
    int start_row = l_initial - K + r_up;
    int end_row = l_initial + K - r_down;
    int start_column = c_initial - K + c_left;
    int end_column = c_initial + K - c_right;
    
    // Fill the submatrix with the values read from the input file considering limitations.
    l_aux = 0;
    for (l = 1; l <= L; l++) {
        if ((l >= start_row) && (l <= end_row)) {
            c_aux = 0;
            for (c = 1; c <= C; c++) {
                if (fscanf(file_in, "%d", &cell_energy) != 1) {
                    for (i = 0; i < *l_matrix; i++) {
                        free(matrix[i]);
                    }
                    free(matrix);
                    return NULL;
                }

                if ((c >= start_column) && (c <= end_column) && (c_aux < *c_matrix) && (l_aux < *l_matrix)) {
                        matrix[l_aux][c_aux] = cell_energy;
                        // Save the coordinates of the first element of the submatrix.
                        if (first == 0) {
                            *l_m = l;
                            *c_m = c;
                            first = 1;
                        }
                        c_aux++;
                }
            }
            l_aux++;
        } else {
            // Read undesirable rows.
            for (c = 1; c <= C; c++) {
                if (fscanf(file_in, "%d", &cell_energy) != 1) {
                    for (i = 0; i < *l_matrix; i++) {
                        free(matrix[i]);
                    }
                    free(matrix);
                    return NULL;
                }
            }
        }
    }

    return matrix;
}


/******************************************************************************
 * problem_solving()
 *
 * Arguments: file_in - input file (pointer)
 *            file_out - output file (pointer)
 * Returns: (void)
 *
 * Description:
 *          Read input file, check if it contains a valid problem, and if
 *          so, call the correct function to solve it.
 *****************************************************************************/
void problem_solving(FILE *file_in, FILE *file_out) {

    // Variable declaration.
    int L, C, wanted_energy, l_initial, c_initial, K, energy_initial;
    int aux, i;

    // Loop to read and process the problems from the input file.
    while (1) {
        
        // Read the first 7 integers of the problem, checking if the reading was successful.
        if (fscanf(file_in, "%d %d %d %d %d %d %d", &L, &C, &wanted_energy, &l_initial, &c_initial, &K, &energy_initial) != 7) {
            if (feof(file_in) != 0) {
                // Exit the loop if it is the end of the file.
                break;
            } else {
                // Goes to the next iteration of the while loop.
                continue;
            }
        }

        // Check if the problem is valid.
        if (L < 1 || C < 1 || (wanted_energy < -2 || (wanted_energy > -2 && wanted_energy < 1)) || l_initial < 1 || c_initial < 1 || l_initial > L || c_initial > C || K <= 0 || energy_initial < 1) {
            
            // Print the correct output if it is an invalid problem.
            fprintf(file_out, "%d %d %d %d %d %d %d\n\n", L, C, wanted_energy, l_initial, c_initial, K, energy_initial);

            // Read the L*C integers that follow the header of an invalid problem.
            for (i = 0; i < (L * C); i++) {
                if (fscanf(file_in, "%d", &aux) != 1) {
                    return;
                }
            }

            continue;
        }

        // Variable declaration and initialization of matrix.
        int **matrix = NULL;
        int l_m, c_m;
        int l_matrix, c_matrix;
        
        // Submatrix allocation.
        matrix = matrix_alloc(L, C, l_initial, c_initial, K, file_in, &l_m, &c_m, &l_matrix, &c_matrix);
        if (matrix == NULL) {
            return;
        }

        // Call the correct function based on the value of wanted_energy.
        if (wanted_energy == -2) {
            task_2F(L, C, wanted_energy, l_initial, c_initial, K, energy_initial, matrix, l_m, c_m, l_matrix, c_matrix, file_out);
        } else {
            task_1F(L, C, wanted_energy, l_initial, c_initial, K, energy_initial, matrix, l_m, c_m, l_matrix, c_matrix, file_out);
        }

        // Free allocated submatrix.
        if (K != 0) {
            for (i = 0; i < l_matrix; i++) {
                free(matrix[i]);
            }
            free(matrix);
        }

        // After processing the problem, the while loop continues.
    }

    return;
}
