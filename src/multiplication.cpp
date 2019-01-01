//
// Created by David Durst on 2018-12-30.
//
#include <fstream>
#include <iostream>
#include <stdio.h>
#include "MatrixConfig.h"

int main (int argc, char * argv[]) {
    fprintf(stdout, "%s Version %d.%d", argv[0], Matrix_VERSION_MAJOR,
        Matrix_VERSION_MINOR);
    for (int arg_index = 1; arg_index < argc; arg_index++) {
        std::cout << argv[arg_index] << " ";
    }
    std::cout << std::endl;

    return 0;
}
