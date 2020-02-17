cmake_minimum_required(VERSION 3.15)
project(MachineLearning)

set(CMAKE_CXX_STANDARD 20)

find_package (Eigen3 REQUIRED)

add_library(MachineLearning SHARED API/API.cpp API/API.h export.h Model/ModelManager.cpp Model/ModelManager.h Model/Model.cpp Model/Model.h Model/ModelLinear.cpp Model/ModelLinear.h)

target_link_libraries (MachineLearning Eigen3::Eigen)

SET(CMAKE_INSTALL_PREFIX ${CMAKE_CURRENT_SOURCE_DIR})
install(TARGETS MachineLearning DESTINATION lib)