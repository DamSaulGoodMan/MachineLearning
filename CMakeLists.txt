cmake_minimum_required(VERSION 3.15)
project(MachineLearning)

set(CMAKE_CXX_STANDARD 20)

#find_package (Eigen3 3.7 REQUIRED)

add_library(MachineLearning SHARED api.cpp api.h export.h)

#target_link_libraries (MachineLearning Eigen3::Eigen)