cmake_minimum_required(VERSION 3.15)
project(MachineLearning)

set(CMAKE_CXX_STANDARD 20)
set(EIGEN_DIR "./eigen-3.3.7/build_dir")
include_directories(${EIGEN_DIR})

add_library(MachineLearning SHARED API/API.cpp API/API.h export.h Model/ModelManager.cpp Model/ModelManager.h Model/Model.cpp Model/Model.h Model/ModelLinear.cpp Model/ModelLinear.h Model/ModelMultiLayers.cpp Model/ModelMultiLayers.h)

SET(CMAKE_INSTALL_PREFIX ${CMAKE_CURRENT_SOURCE_DIR})
install(TARGETS MachineLearning DESTINATION lib)

add_executable(Test test_main.cpp API/API.cpp API/API.h export.h Model/ModelManager.cpp Model/ModelManager.h Model/Model.cpp Model/Model.h Model/ModelLinear.cpp Model/ModelLinear.h Model/ModelMultiLayers.cpp Model/ModelMultiLayers.h Commun.h)
