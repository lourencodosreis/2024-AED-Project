/******************************************************************************
 * (c) 2024 AED PROJECT - Guilherme Gameiro, Lourenço Reis
 *
 * NAME
 *   tasks.h
 *
 * DESCRIPTION
 *   Function declarations to solve each task separately.
 * 
 ******************************************************************************/

#ifndef BOUND_H
#define BOUND_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// Function declaration.
int bound(int l_m, int c_m, int K, int steps, int **matrix, 
          int l_initial, int c_initial, int l_matrix, int c_matrix, int **visited);

#endif // BOUND_H
