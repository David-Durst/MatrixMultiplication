import numpy as np
import os
import time
from random import randint
import filecmp
import sys

path_to_binary = sys.argv[1]

MIN_ROWS_OR_COLS = 30
MAX_ROWS_OR_COLS = 60
num_rows_left_matrix = randint(MIN_ROWS_OR_COLS,MAX_ROWS_OR_COLS)
# number of cols in left matrix must match number of rows in right
num_cols_left_matrix = randint(MIN_ROWS_OR_COLS,MAX_ROWS_OR_COLS)
num_cols_right_matrix = randint(MIN_ROWS_OR_COLS,MAX_ROWS_OR_COLS)

left_matrix = np.random.rand(num_rows_left_matrix, num_cols_left_matrix)
right_matrix = np.random.rand(num_cols_left_matrix, num_cols_right_matrix)
product_matrix = np.matmul(left_matrix, right_matrix)

output_dir = "{}x{}_by_{}x{}_{}".format(str(num_rows_left_matrix), str(num_cols_left_matrix), str(num_rows_left_matrix),
                                        str(num_cols_right_matrix), time.strftime("%Y%m%d-%H%M%S"))

os.mkdir(output_dir)

np.savetxt(output_dir + "/left_matrix.csv", left_matrix, delimiter=",")
np.savetxt(output_dir + "/right_matrix.csv", right_matrix, delimiter=",")
np.savetxt(output_dir + "/product_matrix.csv", product_matrix, delimiter=",")

os.system("%s/matrix_multiplication %s %s %s %s %s %s".format(
    path_to_binary,
    output_dir + "/left_matrix.csv",
    output_dir + "/right_matrix.csv",
    output_dir + "/cxx_product_matrix.csv",
    num_rows_left_matrix,
    num_cols_left_matrix,
    num_cols_right_matrix))

if not filecmp.cmp(output_dir + "/product_matrix.csv",
                   output_dir + "/cxx_product_matrix.csv"):
    #raise ValueError("numpy and my implementation don't match")
    print("hi")
else:
    print("Success!")
