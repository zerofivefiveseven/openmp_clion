cmake_minimum_required(VERSION 3.6)
project(openmp_clion C CXX)
# sudo apt-get install libomp-de
# added -fopenmp
add_executable(openmp_clion 4_MPI.cpp)
set_property(TARGET ${PROJECT_NAME} PROPERTY C_STANDARD 99)
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -std=gnu11 -fopenmp")


# sudo apt install libopenmpi-dev
# sudo apt install mpich
# openmp part of project
find_package(MPI REQUIRED)
include_directories(${MPI_INCLUDE_PATH})
set(CMAKE_CXX_COMPILE_FLAGS ${CMAKE_CXX_COMPILE_FLAGS} ${MPI_COMPILE_FLAGS})
set(CMAKE_CXX_LINK_FLAGS ${CMAKE_CXX_LINK_FLAGS} ${MPI_LINK_FLAGS})
target_link_libraries(openmp_clion ${MPI_LIBRARIES})