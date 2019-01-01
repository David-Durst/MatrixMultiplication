cmake_minimum_required (VERSION 3.12)
project (Matrix_Multiplication)

include_directories(${PROJECT_BINARY_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/include)
file(GLOB MULT_SOURCES "${PROJECT_SOURCE_DIR}/src/*.cpp")

# The version number
set (Matrix_VERSION_MAJOR 0)
set (Matrix_VERSION_MINOR 1)

get_cmake_property(_variableNames VARIABLES)
list (SORT _variableNames)
foreach (_variableName ${_variableNames})
    message(STATUS "${_variableName}=${${_variableName}}")
endforeach()

# from OpenCV via https://medium.com/@onur.dundar1/cmake-tutorial-585dd180109b
# Disable in-source builds to prevent source tree corruption.
if(" ${CMAKE_SOURCE_DIR}" STREQUAL " ${CMAKE_BINARY_DIR}")
    message(STATUS "CMAKE_SOURCE_DIR is ${CMAKE_SOURCE_DIR}")
    message(STATUS "CMAKE_BINARY_DIR is ${CMAKE_BINARY_DIR}")
    message(FATAL_ERROR "
FATAL: In-source builds are not allowed.
       You should create a separate directory for build files.
")
endif()

# configure a header file to pass some fo the CMake settings
# to the source code
configure_file(
    "${PROJECT_SOURCE_DIR}/include/MatrixConfig.h.in"
    "${PROJECT_BINARY_DIR}/include/MatrixConfig.h"
)

add_executable(matrix_multiplication ${MULT_SOURCES})


# add the install targets
install (TARGETS matrix_multiplication DESTINATION bin)
install (FILES "${PROJECT_BINARY_DIR}/include/MatrixConfig.h"
    DESTINATION include)

# build a CPack driven installer package
include (InstallRequiredSystemLibraries)
set (CPACK_RESOURCE_FILE_LICENSE
    "${CMAKE_CURRENT_SOURCE_DIR}/License.txt")
set (CPACK_PACKAGE_VERSION_MAJOR "${Tutorial_VERSION_MAJOR}")
set (CPACK_PACKAGE_VERSION_MINOR "${Tutorial_VERSION_MINOR}")
include (CPack)