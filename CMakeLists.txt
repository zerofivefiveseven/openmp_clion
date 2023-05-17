cmake_minimum_required(VERSION 3.9.1)
project(openmp_clion)

set(CMAKE_CXX_STANDARD 14)

# -fopenmp flag (enables OpenMP)
set(GCC_COVERAGE_COMPILE_FLAGS " -Wall -pedantic -lm -O3 -funroll-loops -fopenmp")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}")

add_executable(openmp_clion 5_OMP.cpp)

# MPI
#find_package(MPI REQUIRED)
#target_link_libraries(openmp_clion PUBLIC MPI::MPI_CXX)