cmake_minimum_required(VERSION 3.7)
project(MVHADM001)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES driver.cpp lib/Image.cpp lib/Image.h unit_tests.cpp)
add_executable(MVHADM001 ${SOURCE_FILES})