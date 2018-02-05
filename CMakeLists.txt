cmake_minimum_required(VERSION 3.8)
project(a3)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES main.cpp JOB.h constants.h JOB.cpp RandGenQSim.h RandGenQSim.cpp)
add_executable(a3 ${SOURCE_FILES})