ENABLE_TESTING()
find_package( PythonInterp 3.6 REQUIRED )
add_test(NAME equality_and_timing_test
    COMMAND ${PYTHON_EXECUTABLE}
        ${CMAKE_SOURCE_DIR}/python/matrix_generator.py
        ${CMAKE_BINARY_DIR}
    WORKING_DIRECTORY ${EXECUTABLE_OUTPUT_PATH})
