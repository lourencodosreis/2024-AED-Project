/******************************************************************************
 * (c) 2024 AED PROJECT - Guilherme Gameiro, Lourenço Reis
 *
 * NAME
 *   final_tasks.h
 *
 * DESCRIPTION
 *   Function declaration to solve each task separately.
 * 
 ******************************************************************************/

#ifndef FINAL_TASKS_H
#define FINAL_TASKS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// Function declaration.
void task_1F(int L, int C, int wanted_energy, int l_initial, int c_initial, int K,
             int energy_initial, int **matrix, int l_m, int c_m, int l_matrix, int c_matrix, FILE *file_out);
void task_2F(int L, int C, int wanted_energy, int l_initial, int c_initial, int K,
             int energy_initial, int **matrix, int l_m, int c_m, int l_matrix, int c_matrix, FILE *file_out);

#endif // FINAL_TASKS_H
