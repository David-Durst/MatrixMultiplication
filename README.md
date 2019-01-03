# Matrix Multiplication
## Overview
This is an optimized matrix multiplication implementation for arbitrary matrices of signed, 16 bit integers.

The final version of the implementation was 4.87 times faster than NumPy using MKL when multiplying a 1678x1693 matrix by a 1693x1622 matrix.

## Results
This chart shows the improvement of my implementation's performance over time relative to NumPy's on my Macbook Pro Summer 2017 with an Intel(R) Core(TM) i7-7920HQ CPU @ 3.10GHz and 16 GB of RAM.

![Chart of my implementation's performance vs NumPy's](https://raw.githubusercontent.com/David-Durst/MatrixMultiplication/master/results.png)

The major improvements came at 1/2/19 4:30 PM when I added tiling, 1/3/19 11:05 PM when I added vectorization, and 1/3/19 11:06 AM when I turned on -O3 to get improvements including loop unrolling.

The results.xlsx file contains these results in text form along with the git commit hashes of the code that produced each result and input matrix sizes.

## Implementation
The implementation is the multiply_matrices function in src/multiplication.cpp.

There is a build system and test harness.

## Installation
To build and run the code, you need cmake 3.12 or newer, clang or gcc, and python 3.6 or newer with numpy installed. Your processor must support the AVX2 instruction set.

After checking out the repository, follow the below steps to build and run unit tests:
```
cd build
cmake .. ; make ; ctest -V
```

This command will write results to the times.csv file. I converted it to results.xlsx to create the chart.
