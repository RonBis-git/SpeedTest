cmake_minimum_required(VERSION 3.12)
project(cppOps)

set(SOURCES
    bindpy.cpp
    eigOps.cpp
)

find_package(pybind11 REQUIRED)
pybind11_add_module(cppOps ${SOURCES})

find_package (Eigen3 3.3 REQUIRED NO_MODULE)
target_link_libraries(cppOps PRIVATE Eigen3::Eigen pybind11::module)
