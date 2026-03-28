/******************************************************************************
 * (c) 2024 AED PROJECT - Guilherme Gameiro, Lourenço Reis
 *
 * NAME
 *   solving.h
 *
 * DESCRIPTION
 *   Support function declaration.
 * 
 ******************************************************************************/

#ifndef SOLVING_H
#define SOLVING_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// Constant definition.
#define invalid_problem -1

// Function declaration.
int distance(int l_initial, int c_initial, int l_current, int c_current);
int **matrix_alloc(int L, int C, int l_initial, int c_initial, int K, FILE *file_in, int *l_m, int *c_m, int *l_matrix, int *c_matrix);
void problem_solving(FILE *file_in, FILE *file_out);

#endif // SOLVING_H
