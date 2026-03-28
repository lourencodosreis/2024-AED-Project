/******************************************************************************
 * (c) 2024 AED PROJECT - Guilherme Gameiro, Lourenço Reis
 *
 * NAME
 *   navigate.c
 *
 * DESCRIPTION
 *   Main file to solve the NAVIGATE problem.
 *
 *****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "solving.h"
#include "final_tasks.h"
#include "dfs.h"
#include "bound.h"

/******************************************************************************
 * main()
 *
 * Description: 
 *          Main function.
 *****************************************************************************/
int main(int argc, char *argv[]) {
    
    // Incorrect execution of the program.
    if (argc != 2) {
        return 0;
    }

    // Check if input file has the correct extension: ".maps".
    size_t arg1len = strlen(argv[1]);
    if (arg1len <= 5 || strcmp(argv[1] + arg1len - 5, ".maps") != 0) {
        return 0;
    }

    // Open input file to read.
    FILE *file_in = fopen(argv[1], "r");
    if (file_in == NULL) {
        return 0;
    }

    // Create output file with the correct extension: ".solmaps".
    char *file_out_name = (char*) malloc(arg1len - 5 + 9);
    if (file_out_name == NULL) {
        return 0;
    }
    strcpy(file_out_name, argv[1]);
    file_out_name[arg1len - 5] = '\0';
    strcat(file_out_name, ".solmaps");

    // Open output file to write.
    FILE *file_out = fopen(file_out_name, "w");
    if (file_out == NULL) {
        free(file_out_name);
        fclose(file_in);
        return 0;
    }

    // Invoke the function that solves the problem.
    problem_solving(file_in, file_out);

    // Free allocated memory.
    free(file_out_name);

    // Close input and output files.
    fclose(file_in);
    fclose(file_out);

    return 0;
}
