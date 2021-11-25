cmake_minimum_required(VERSION 3.20)
project(class_csr_matrix)

set(CMAKE_CXX_STANDARD 14)

add_executable(class_csr_matrix main.cpp csr_matrix.cpp csr_matrix.h)
