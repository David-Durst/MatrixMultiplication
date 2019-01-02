//
// Created by David Durst on 2018-12-30.
//
#include <fstream>
#include <iostream>
#include <stdio.h>
#include <string>
#include "MatrixConfig.h"

void load_matrix(std::ifstream &matrix_file, int matrix_rows, int matrix_cols, int **matrix);

void multiply_matrices(int left_matrix_rows, int left_matrix_cols, int right_matrix_cols, int **left_matrix,
                       int **right_matrix, int **output_matrix);

int main (int argc, char * argv[]) {
    fprintf(stdout, "%s Version %d.%d \n", argv[0], Matrix_VERSION_MAJOR,
        Matrix_VERSION_MINOR);

    // get files and make sure open inputs
    std::ifstream left_matrix_file(argv[1]);
    std::ifstream right_matrix_file(argv[2]);
    std::ofstream output_matrix_file(argv[3]);

    if (!left_matrix_file.is_open()) {
        std::cerr << "UNABLE TO OPEN LEFT MATRIX FILE: " << argv[1] << std::endl;
        return 1;
    }

    if (!right_matrix_file.is_open()) {
        std::cerr << "UNABLE TO OPEN RIGHT MATRIX FILE: " << argv[2] << std::endl;
        return 1;
    }

    if (!output_matrix_file.is_open()) {
        std::cerr << "UNABLE TO OPEN OUTPUT FILE: " << argv[3] << std::endl;
        return 1;
    }

    // load matrix parameters
    int left_matrix_rows = std::stoi(argv[4]);
    int left_matrix_cols = std::stoi(argv[5]);
    int right_matrix_rows = std::stoi(argv[5]);
    int right_matrix_cols = std::stoi(argv[6]);
    int output_matrix_rows = left_matrix_rows;
    int output_matrix_cols = right_matrix_cols;

    // setup matrices in memory
    int **left_matrix = new int*[left_matrix_rows];
    int **right_matrix = new int*[right_matrix_rows];
    int **output_matrix = new int*[output_matrix_rows];
    for (int i = 0; i < left_matrix_rows; i++) {
        left_matrix[i] = new int[left_matrix_cols];
    }
    for (int i = 0; i < right_matrix_rows; i++) {
        right_matrix[i] = new int[right_matrix_cols];
    }
    for (int i = 0; i < output_matrix_rows; i++) {
        output_matrix[i] = new int[output_matrix_cols];
    }

    // load the matrices data from disk to memory

#ifdef PRINT_DEBUG
    std::cout << "loading left matrix" << std::endl;
#endif

    load_matrix(left_matrix_file, left_matrix_rows, left_matrix_cols, left_matrix);
    left_matrix_file.close();

#ifdef PRINT_DEBUG
    std::cout << "loading right matrix" << std::endl;
#endif

    load_matrix(right_matrix_file, right_matrix_rows, right_matrix_cols, right_matrix);
    right_matrix_file.close();

    multiply_matrices(left_matrix_rows, left_matrix_cols, right_matrix_cols, left_matrix, right_matrix, output_matrix);

    // save output
    for (int output_row = 0; output_row < output_matrix_rows; output_row++) {
        for (int output_col = 0; output_col < output_matrix_cols; output_col++) {
            output_matrix_file << std::to_string(output_matrix[output_row][output_col]);
            if (output_col < output_matrix_cols - 1) {
                output_matrix_file << ",";
            }
        }
        output_matrix_file << std::endl;
    }
    output_matrix_file.close();

    // clean up matrices in memory
    for (int i = 0; i < left_matrix_rows; i++) {
        delete [] left_matrix[i];
    }
    delete [] left_matrix;
    for (int i = 0; i < right_matrix_rows; i++) {
        delete [] right_matrix[i];
    }
    delete [] right_matrix;
    for (int i = 0; i < output_matrix_rows; i++) {
        delete [] output_matrix[i];
    }
    delete [] output_matrix;

    return 0;
}

void multiply_matrices(int left_matrix_rows, int left_matrix_cols, int right_matrix_cols, int **left_matrix,
                       int **right_matrix, int **output_matrix) {
    for (int left_row = 0; left_row < left_matrix_rows; left_row++) {
        for (int right_col = 0; right_col < right_matrix_cols; right_col++) {
            output_matrix[left_row][right_col] = 0;
            for (int shared_dim = 0; shared_dim < left_matrix_cols; shared_dim++) {
#ifdef PRINT_DEBUG
                printf("Left  (%d, %d): %d \n", left_row, shared_dim, left_matrix[left_row][shared_dim]);
                printf("Right (%d, %d): %d \n", shared_dim, right_col, right_matrix[shared_dim][right_col]);
#endif
                output_matrix[left_row][right_col] +=
                    left_matrix[left_row][shared_dim] *
                    right_matrix[shared_dim][right_col];

#ifdef PRINT_DEBUG
                printf("Output (%d, %d): %d \n", left_row, right_col, output_matrix[left_row][right_col]);
#endif
            }
        }
    }
}

void load_matrix(std::ifstream &matrix_file, int matrix_rows, int matrix_cols, int **matrix) {// load data into matrices
    for (int current_row = 0; current_row < matrix_rows; current_row++) {
        std::string line;
        std::getline(matrix_file, line);

#ifdef PRINT_DEBUG
        std::cout << "Line: " << line << std::endl;
#endif

        size_t last_comma = 0, next_comma = 0, position = 0;
        for (int current_col = 0; current_col < matrix_cols; current_col++) {
            // no comma for the last entry, need to pretend comma after last character
            if (current_col < matrix_cols - 1) {
                next_comma = line.substr(position).find(",") + position;
            }
            else {
                next_comma = line.length();
            }

#ifdef PRINT_DEBUG
            std::cout << "Position: " << position << std::endl;
            std::cout << "next_comma: " << next_comma << std::endl;
            std::cout << "last_comma: " << last_comma << std::endl;
            std::cout << "next_comma - last_comma: " << next_comma - last_comma << std::endl;
            std::cout << "Trying to convert " << line.substr(position, next_comma - last_comma) << std::endl;
#endif

            matrix[current_row][current_col] =
                stoi(line.substr(position, next_comma - last_comma));

#ifdef PRINT_DEBUG
            printf("Matrix (%d, %d): %d \n", current_row, current_col, matrix[current_row][current_col]);
#endif

            last_comma = next_comma;
            position = last_comma + 1;
        }
    }
}


