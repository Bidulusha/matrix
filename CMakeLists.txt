message(STATUS "set env var")
set(ENV{CC} "/usr/local/opt/llvm/bin/clang")
set(ENV{CXX} "/usr/local/opt/llvm/bin/clang++")
set(ENV{LDFLAGS} "-L/usr/local/opt/llvm/lib")
set(ENV{CPPFLAGS} "-I/usr/local/opt/llvm/include")


cmake_minimum_required(VERSION 4.3)

project(Matrix)

add_executable(matrix_main)
add_library(MatrixLibrary)

target_sources(
    MatrixLibrary
    PRIVATE
        src/matrix.cpp

    PUBLIC
        FILE_SET myHeaders
        TYPE HEADERS
        BASE_DIRS
            src
        FILES
            src/matrix.hpp
)

find_package(OpenMP REQUIRED)

target_compile_definitions(MatrixLibrary PRIVATE OMP_VERSION)
target_compile_definitions(MatrixLibrary PRIVATE NUM_THREADS=6)
target_link_libraries(MatrixLibrary PRIVATE OpenMP::OpenMP_CXX)

target_link_libraries(matrix_main PUBLIC MatrixLibrary)
target_sources(matrix_main PRIVATE main.cpp)
