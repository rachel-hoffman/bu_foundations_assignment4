#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>

// matrix looks something like:
// int matrix[rows][cols];

// "Generates a nrows x ncols matrix filled with random values using rand()" (from README instructions)
void generate_random_matrix(int rows, int cols, int *matrix) {
    // Create n rows
    for (int i = 0; i < rows; i++){
        // Create n cols
        for (int j = 0; j < cols; j++){
            matrix[i*cols + j] = rand();
        }
    }
}

// "Generates a new output matrix by performing a matrix multiply between input matrix A and B." (from README instructions)
// c(ij) = a(ik)b(kj) for n times, where k is incremented by one each time.
void multiply_matrices(int rows1, int cols1, int *matrix1,
                       int rows2, int cols2, int *matrix2,
                       int *result) {
    // Loop through matrix1's rows
    for (int r = 0; r < cols1; r++){
        // Loop thorugh matrix2's columns
        for (int c = 0; c < rows1; c++){
            for (int k = 0; k < cols1; k++){
                // Multiply martix1's rows by matrix2's columns
                result[r*cols2 + c] = matrix1[r*cols1 + k] * matrix2 [k*cols2 + c];
            }
        }
    } 
}

// "Prints the matrix to STDOUT for debugging purposes." (from README instructions)
void display_matrix(int rows, int cols, int *matrix) {
    // Loop through rows
    for (int i = 0; i < rows; i++){
        // Loop through columns
        for (int j = 0; j < cols; j++){
            // Print each value
            printf("%d, ", matrix[i*cols + j]);
        }
        printf("\n");
    }
}

// "Main 'engine' of the program. It should generate matrices of the specified size, multiply them, either one time if forever =0, or in a loop if forever=1." (from README instructions)
float do_job(int rows1, int cols1, int cols2, int forever) {
    struct timespec t0, t1;

    // Set up matrix 1, 2, and result pointers
    int* matrix1 = malloc(rows1 * cols1 * sizeof(int));
    int* matrix2 = malloc(rows1 * cols2 * sizeof(int));
    int* matrix3 = malloc(rows1 * cols2 * sizeof(int));
    // Generate matrices
    generate_random_matrix(rows1, cols1, matrix1);
    generate_random_matrix(cols1, cols2, matrix2);
    
    // Start timing
    timespec_get(&t0, TIME_UTC);

    // Multiply the matrices (infinitely, if forever = 1)
    switch (forever){
    case 0:
        multiply_matrices(rows1, cols1, matrix1, cols1, cols2, matrix2, matrix3);
        break;
    case 1:
        while (true)
            multiply_matrices(rows1, cols1, matrix1, cols1, cols2, matrix2, matrix3);
        break;
    default:
        printf("'Forever' value is invalid (expecting 0 or 1).");
        break;
    }

    // End timing
    timespec_get(&t1, TIME_UTC);

    // Convert time (nano seconds to fractional seconds)
    float dns = (float)(t1.tv_nsec - t0.tv_nsec) / 1000000000;
    // seconds elapsed
    float ds = (float)(t1.tv_sec - t0.tv_sec);
    float total_time = dns+ds;

    return total_time;
}

