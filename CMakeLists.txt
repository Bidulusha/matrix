message(STATUS "set env var")
set(ENV{CC} "/usr/local/opt/llvm/bin/clang")
set(ENV{CXX} "/usr/local/opt/llvm/bin/clang++")
set(ENV{LDFLAGS} "-L/usr/local/opt/llvm/lib")
set(ENV{CPPFLAGS} "-I/usr/local/opt/llvm/include")


cmake_minimum_required(VERSION 4.3)

project(Matrix)

add_library(matrix)

target_sources(
    matrix
    PRIVATE
        src/matrix_io.cc
        src/matrix_operators.cc
        src/matrix_gauss_method.cc
        src/matrix_constructors.cc
        src/matrix_getters.cc

    PUBLIC
        FILE_SET myHeaders
        TYPE HEADERS
        BASE_DIRS
            src
        FILES
            src/matrix.hpp
)

find_package(OpenMP REQUIRED)

# target_compile_definitions(matrix PRIVATE OMP_VERSION)
# target_compile_definitions(matrix PRIVATE NUM_THREADS=6)
target_link_libraries(matrix PRIVATE OpenMP::OpenMP_CXX)