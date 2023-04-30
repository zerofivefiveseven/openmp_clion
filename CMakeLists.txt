cmake_minimum_required(VERSION 3.6)
project(openmp_clion C CXX)

# added -fopenmp
add_executable(openmp_clion 9_OMP.cpp)
set_property(TARGET ${PROJECT_NAME} PROPERTY C_STANDARD 99)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -std=gnu11 -fopenmp")
