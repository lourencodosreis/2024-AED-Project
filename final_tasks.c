/******************************************************************************
 * (c) 2024 AED PROJECT - Guilherme Gameiro, Lourenço Reis
 *
 * NAME
 *   final_tasks.c
 *
 * DESCRIPTION
 *   Functions to solve each task separately.
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
 * task_1F()
 *
 * Arguments: L - number of rows in the submatrix
 *            C - number of columns in the submatrix
 *            wanted_energy - target energy
 *            l_initial - initial row coordinate
 *            c_initial - initial column coordinate
 *            K - steps
 *            energy_initial - initial energy
 *            matrix - submatrix allocated (pointer to pointer)
 *            l_m - submatrix first row
 *            c_m - submatrix first column
 *            l_matrix - submatrix number of rows
 *            c_matrix - submatrix number of columns
 *            file_out - output file (pointer)
 * Returns: (void)
 *
 * Description: 
 *          This function performs task 1 on a valid problem.
 *****************************************************************************/
void task_1F(int L, int C, int wanted_energy, int l_initial, int c_initial, int K,
             int energy_initial, int **matrix, int l_m, int c_m, int l_matrix, int c_matrix, FILE *file_out) {
    
    // Check if the problem has no solution, and if so, print the correct output.
    if (K >= (L * C)) {
        fprintf(file_out, "%d %d %d %d %d %d %d %d\n", L, C, wanted_energy, l_initial, c_initial, K, energy_initial, invalid_problem);
        return;
    }

    // Variable declaration.
    int ans, i, j;

    // Memory allocation for the rows of visited matrix.
    int **visited = (int **) malloc((size_t)(l_matrix) * sizeof(int *));
    if (visited == NULL) {
        return;
    }
    // Memory allocation for the columns of visited matrix.
    for (i = 0; i < l_matrix; i++) {
        visited[i] = (int *) calloc((size_t)(c_matrix), sizeof(int));
        if (visited[i] == NULL) {
            // Free previously allocated rows.
            for (j = 0; j < i; j++) {
                free(visited[j]);
            }
            free(visited);
            return;
        }
    }

    // Variable declaration and initialization.
    int found = 0;
    int path_length = 0;
    int solution_length = 0;

    // Paths allocation.
    Step *path = (Step *) malloc((size_t)K * sizeof(Step));
    Step *solution_path = (Step *) malloc((size_t)K * sizeof(Step));
    if (path == NULL || solution_path == NULL) {
        // Free visited matrix.
        for (i = 0; i < l_matrix; i++) {
            free(visited[i]);
        }
        free(visited);
        free(path);
        free(solution_path);
        return;
    }

    // Variable declaration and initialization.
    int energy_o = energy_initial;
    int *solution_energy = (int *) malloc(sizeof(int));
    if (solution_energy == NULL) {
        // Free visited matrix.
        for (i = 0; i < l_matrix; i++) {
            free(visited[i]);
        }
        free(visited);
        free(path);
        free(solution_path);
        return;
    }

    *solution_energy = 0;

    // Call DFS to solve task 1.
    dfs(l_initial, c_initial, 0, energy_o, matrix, l_m, c_m, l_matrix, c_matrix, K,
        wanted_energy, visited, &found, path, path_length, solution_path, &solution_length, solution_energy);
    
    // Free visited matrix.
    for (i = 0; i < l_matrix; i++) {
        free(visited[i]);
    }
    free(visited);
    free(path);

    // Print the correct solution of the problem.
    ans = (found) ? *solution_energy : invalid_problem;
    fprintf(file_out, "%d %d %d %d %d %d %d %d\n", L, C, wanted_energy, l_initial, c_initial, K, energy_initial, ans);

    // If the problem has solution, print the path.
    if (found) {
        for (i = 0; i < solution_length; i++) {
            fprintf(file_out, "%d %d %d\n", solution_path[i].row, solution_path[i].col, solution_path[i].cell_energy);
        }
        fprintf(file_out, "\n");
    } else {
        fprintf(file_out, "\n");
    }

    free(solution_path);
    free(solution_energy);
}


 /*****************************************************************************
 * task_2F()
 *
 * Arguments: L - number of rows in the map
 *            C - number of columns in the map
 *            wanted_energy - flag to perform task 2
 *            l_initial - initial row coordinate
 *            c_initial - initial column coordinate
 *            K - steps
 *            energy_initial - initial energy
 *            matrix - submatrix allocated (pointer to pointer)
 *            l_m - submatrix first row
 *            c_m - submatrix first column
 *            l_matrix - submatrix number of rows
 *            c_matrix - submatrix number of columns
 *            file_out - output file (pointer)
 * Returns: (void)
 *
 * Description: 
 *          This function performs task 2 on a valid problem.
 *****************************************************************************/
 void task_2F(int L, int C, int wanted_energy, int l_initial, int c_initial, int K,
              int energy_initial, int **matrix, int l_m, int c_m, int l_matrix, int c_matrix, FILE *file_out) {
    
    // Check if the problem has no solution, and if so, print the correct output.
    if (K >= (L * C)) {
        fprintf(file_out, "%d %d %d %d %d %d %d %d\n", L, C, wanted_energy, l_initial, c_initial, K, energy_initial, invalid_problem);
        return;
    }

    // Variable declaration.
    int ans, i, j;

    // Memory allocation for the rows of visited matrix.
    int **visited = (int **) malloc((size_t)(l_matrix) * sizeof(int *));
    if (visited == NULL) {
        return;
    }
    // Memory allocation for the columns of visited matrix.
    for (i = 0; i < l_matrix; i++) {
        visited[i] = (int *) calloc((size_t)c_matrix, sizeof(int));
        if (visited[i] == NULL) {
            // Free previously allocated rows.
            for (j = 0; j < i; j++) {
                free(visited[j]);
            }
            free(visited);
            return;
        }
    }

    // Variable declaration and initialization.
    int path_length = 0;
    int solution_length = 0;

    // Paths allocation.
    Step *path = (Step *) malloc((size_t)K * sizeof(Step));
    Step *solution_path = (Step *) malloc((size_t)K * sizeof(Step));
    if (path == NULL || solution_path == NULL) {
        // Free visited matrix.
        for (i = 0; i < l_matrix; i++) {
            free(visited[i]);
        }
        free(visited);
        free(path);
        free(solution_path);
        return;
    }

    // Variable declaration and initialization.
    int *solution_energy = (int *) malloc(sizeof(int));
    if (solution_energy == NULL) {
        // Free visited matrix.
        for (i = 0; i < l_matrix; i++) {
            free(visited[i]);
        }
        free(visited);
        free(path);
        free(solution_path);
        return;
    }

    *solution_energy = 0;

    // Call DFS to solve task 2.
    dfs_max_energy(l_initial, c_initial, 0, energy_initial, matrix, l_m, c_m, l_matrix, c_matrix, K,
                   visited, path, path_length, solution_path, &solution_length, solution_energy);
    
    // Free visited matrix.
    for (i = 0; i < l_matrix; i++) {
        free(visited[i]);
    }
    free(visited);
    free(path);

    // Print the correct solution of the problem.
    ans = (solution_length > 0) ? *solution_energy : invalid_problem;
    fprintf(file_out, "%d %d %d %d %d %d %d %d\n", L, C, wanted_energy, l_initial, c_initial, K, energy_initial, ans);

    // Print the path.
    if (solution_length > 0) {
        for (i = 0; i < solution_length; i++) {
            fprintf(file_out, "%d %d %d\n", solution_path[i].row, solution_path[i].col, solution_path[i].cell_energy);
        }
        fprintf(file_out, "\n");
    } else {
        fprintf(file_out, "\n");
    }

    free(solution_path);
    free(solution_energy);
}
