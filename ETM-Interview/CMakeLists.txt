# CMakeList.txt : CMake project for ETM-Interview, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project ("ETM-Interview")

add_executable(Main Main.cpp)
set_property(TARGET Main PROPERTY CXX_STANDARD 23)
