//
// Created by David Durst on 2018-12-30.
//
#include <fstream>
#include <iostream>

int main (int argc, char * argv[]) {
    std::cout << "multiply ";
    for (int arg_index = 0; arg_index < argc; arg_index++) {
        std::cout << argv[arg_index] << " ";
    }
    std::cout << std::endl;

    return 0;
}
