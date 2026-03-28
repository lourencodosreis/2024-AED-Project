/******************************************************************************
 * (c) 2024 AED PROJECT - Guilherme Gameiro, Lourenço Reis
 *
 * NAME
 *   dfs.c
 *
 * DESCRIPTION
 *   DFS function.
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

// Possible movements definition: up, down, left and right.
static const int directions[4][2] = {{-1,0}, {1,0}, {0,-1}, {0,1}};

/******************************************************************************
 * dfs()
 *
 * Arguments: row - current row
 *            col - current columns
 *            steps - current steps
 *            energy - current energy
 *            matrix - submatrix allocated (pointer to pointer)
 *            l_m - submatrix first row
 *            c_m - submatrix first column
 *            l_matrix - submatrix number of rows
 *            c_matrix - submatrix number of columns
 *            K - final steps
 *            wanted_energy - target energy
 *            visited - visited matrix (pointer to pointer)
 *            found - solution found flag (pointer)
 *            path - current path (pointer)
 *            path_length - current path length
 *            solution_path - solution path (pointer)
 *            solution_length - solution length (pointer)
 *            solution_energy - solution energy (pointer)

 * Returns: (void)
 *
 * Description:
 *          Recursive DFS to perform task 1.
 *****************************************************************************/
void dfs(int row, int col, int steps, int energy, int **matrix, int l_m, int c_m,
         int l_matrix, int c_matrix, int K, int wanted_energy,
         int **visited, int *found, Step *path, int path_length,
         Step *solution_path, int *solution_length, int *solution_energy) {
    
    // Early exit if a solution has been found, or if current steps exceed final steps.
    if (*found || steps > K)
        return;

    if (steps > 0) {
        // Check if new cell is within the limits of submatrix.
        if (row - l_m < 0 || row - l_m >= l_matrix || col - c_m < 0 || col - c_m >= c_matrix) {
            return;
        }
        // Add new cell's energy to the current energy.
        energy += matrix[row - l_m][col - c_m];

        // If energy becomes negative or zero, backtrack.
        if (energy <= 0 || path_length >= K)
            return;

        // Record the current step in the path.
        path[path_length].row = row;
        path[path_length].col = col;
        path[path_length].cell_energy = matrix[row - l_m][col - c_m];
        path_length++;
    }

    // If the final number of steps is reached, check if current energy is bigger or equal than the target energy.
    if (steps == K) {
        if (energy >= wanted_energy) {
            *found = 1;
            // Copy information to the solution variables.
            memcpy(solution_path, path,(size_t) path_length * sizeof(Step));
            *solution_length = path_length;
            *solution_energy = energy;
        }
        return;
    }
    
    // If potencial energy is smaller than target energy, backtrack.
    int potencial_energy = energy + bound(l_m, c_m, K, steps, matrix, row, col, l_matrix, c_matrix, visited);
    if (potencial_energy < wanted_energy) {
        return;
    }

    // Update visited matrix.
    visited[row - l_m][col - c_m] = 1;

    // Variable declaration.
    int i, new_row, new_col;

    // Explore all possible directions.
    for (i = 0; i < 4; i++) {

        new_row = row + directions[i][0];
        new_col = col + directions[i][1];
        
        // Check if new cell is within the limits of submatrix and if it has already been visited.
        if (new_row >= l_m && new_row < (l_m + l_matrix) && new_col >= c_m && new_col < (c_m + c_matrix) &&
            !visited[new_row - l_m][new_col - c_m]) {
            
            // Recursive call of DFS.
            dfs(new_row, new_col, steps + 1, energy, matrix, l_m, c_m,
                l_matrix, c_matrix, K, wanted_energy, visited, found, 
                path, path_length, solution_path, solution_length, solution_energy);
            
            // Early exit if a solution has been found.
            if (*found) {
                break;
            }
        }
    }

    // Backtrack.
    visited[row - l_m][col - c_m] = 0;

    // Decrease the path's length.
    if (steps > 0) {
        path_length--;
    }
}


/******************************************************************************
 * dfs_max_energy()
 *
 * Arguments: row - current row
 *            col - current column
 *            steps - current steps
 *            energy - current energy
 *            matrix - submatrix allocated (pointer to pointer)
 *            l_m - submatrix first row
 *            c_m - submatrix first column
 *            l_matrix - submatrix number of rows
 *            c_matrix - submatrix number of columns
 *            K - final steps
 *            visited - visited matrix (pointer to pointer)
 *            path - current path (pointer)
 *            path_length - current path length
 *            solution_path - solution path (pointer)
 *            solution_length - solution length (pointer)
 *            solution_energy - solution energy (pointer)           
 * Returns: (void)
 *
 * Description:
 *          Recursive DFS to perform task 2.
 *****************************************************************************/
void dfs_max_energy(int row, int col, int steps, int energy, int **matrix, int l_m, int c_m, int l_matrix, int c_matrix, int K,
                    int **visited, Step *path, int path_length, Step *solution_path, int *solution_length, int *solution_energy) {

    // Variable declaration.
    int i, new_row, new_col;

    // Early exit if a solution has been found.
    if (steps > K) {
        return;
    }

    if (steps > 0) {

        // Add the current cell's energy.
        energy += matrix[row - l_m][col - c_m];
        if (energy <= 0) {
            return;
        }

        // Prevent out-of-bounds access.
        if (path_length >= K) {
            return;
        }

        // Record the current step.
        path[path_length].row = row;
        path[path_length].col = col;
        path[path_length].cell_energy = matrix[row - l_m][col - c_m];
        (path_length)++;
    }

    // If potencial energy is smaller than target energy, backtrack.
    int potencial_energy = energy + bound(l_m, c_m, K, steps, matrix, row, col, l_matrix, c_matrix, visited);
    if (potencial_energy <= *solution_energy) {
        return;
    }
    
    // If the final number of steps is reached, check if current energy is bigger or equal than the previously max energy.
    if (steps == K) {
        if (energy > *solution_energy) {

            *solution_energy = energy;
            // Copy information to the solution variables.
            memcpy(solution_path, path, (size_t)path_length * sizeof(Step));
            *solution_length = path_length;
        }
        return;
    }

    // Update visited matrix.
    visited[row - l_m][col - c_m] = 1;

    // Explore all possible directions.
    for (i = 0; i < 4; i++) {

        new_row = row + directions[i][0];
        new_col = col + directions[i][1];

        // Check boundaries and if the cell has not been visited.
        if (new_row >= l_m && new_row < (l_m + l_matrix) && new_col >= c_m && new_col < (c_m + c_matrix) &&
            !visited[new_row - l_m][new_col - c_m]) {

            dfs_max_energy(new_row, new_col, steps + 1, energy, matrix, l_m, c_m, l_matrix, c_matrix, K,
                           visited, path, path_length, solution_path, solution_length, solution_energy);

        }
    }

    // Backtracking
    visited[row - l_m][col - c_m] = 0;

    // Decrease the path's length.
    if (steps > 0) {
        (path_length)--;
    }

}
