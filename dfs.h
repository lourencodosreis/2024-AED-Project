/******************************************************************************
 * (c) 2024 AED PROJECT - Guilherme Gameiro, LourenÃ§o Reis
 *
 * NAME
 *   dfs.h
 *
 * DESCRIPTION
 *   DFS's function declaration.
 * 
 ******************************************************************************/

#ifndef DFS_H
#define DFS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// Step structure declaration.
typedef struct {
    int row;
    int col;
    int cell_energy;
} Step;

// Function declarations.
void dfs(int row, int col, int steps, int energy, int **matrix, int l_m, int c_m, int l_matrix, int c_matrix, int K,
         int wanted_energy, int **visited, int *found, Step *path, int path_length,
         Step *solution_path, int *solution_length, int *solution_energy);
         
void dfs_max_energy(int row, int col, int steps, int energy, int **matrix, int l_m, int c_m, int l_matrix, int c_matrix, int K,
                    int **visited, Step *path, int path_length, Step *solution_path, int *solution_length, int *solution_energy);

#endif // DFS_H
