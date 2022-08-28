# CMakeList.txt : CMake project for ETM-Interview, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project ("ETM-Interview")

add_executable(main main.cpp)
set_property(TARGET main PROPERTY CXX_STANDARD 23)
