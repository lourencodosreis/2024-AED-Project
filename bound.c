/******************************************************************************
 * (c) 2024 AED PROJECT - Guilherme Gameiro, Lourenço Reis
 *
 * NAME
 *   bound.c
 *
 * DESCRIPTION
 *   DFS Optimization function.
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
 * bound()
 *
 * Arguments: L - number of rows in the submatrix
 *            C - number of columns in the submatrix
 *            l_m - submatrix first row
 *            c_m - submatrix first column
 *            K - steps
 *            steps - current steps
 *            matrix - submatrix allocated (pointer to pointer)
 *            l_initial - initial row coordinate
 *            c_initial - initial column coordinate
 *            l_matrix - submatrix number of rows
 *            c_matrix - submatrix number of columns
 *            visited - visited matrix (pointer to pointer)
 * Returns: (int)
 *
 * Description:
 *          DFS Optimization function.
 *****************************************************************************/
int bound(int l_m, int c_m, int K, int steps, int **matrix, 
           int l_initial, int c_initial, int l_matrix, int c_matrix, int **visited) {
    
    // Declaration and initialization of sum_cell_energy. 
    int sum_cell_energy = 0;
    
   
    const int remaining_steps = K - steps;
    
    // Set the iteration bounds for rows, adjusting for the map limits.
    int l_start = l_initial - remaining_steps;
    if (l_start < l_m) {
        l_start = l_m;
    }
    int l_end = l_initial + remaining_steps;
    if (l_end >= l_m + l_matrix) {
        l_end = l_m + l_matrix - 1;
    }

    // Variable declaration
    int l, delta_l, delta, c_idx;
    int c_start_current, c_end_current;

    // Traverse the submatrix within the calculated bounds.
    for (l = l_start; l <= l_end; l++) {

        const int l_idx = l - l_m;
        
        delta_l = l_initial > l ? l_initial - l : l - l_initial;
        // Calculate the remaining delta for columns.
        delta = remaining_steps - delta_l;
        if (delta < 0) {
            continue;
        }

        // Set the dynamic column bounds for this row
        c_start_current = c_initial - delta;
        if (c_start_current < c_m) {
            c_start_current = c_m;
        }

        c_end_current = c_initial + delta;
        if (c_end_current >= c_m + c_matrix) {
            c_end_current = c_m + c_matrix - 1;
        }

        const int c_idx_start = c_start_current - c_m;
        const int c_idx_end = c_end_current - c_m;
        int *current_matrix_row = matrix[l_idx];
        
        // Traverse the columns within the dynamic bounds.
        for (c_idx = c_idx_start; c_idx <= c_idx_end; c_idx++) {
                if (current_matrix_row[c_idx] > 0 && visited[l_idx][c_idx] == 0) {
                    sum_cell_energy += current_matrix_row[c_idx];
                }
            
        }
    }

    return sum_cell_energy;
}
