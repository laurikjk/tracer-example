cmake_minimum_required(VERSION 3.12)
project(Tracer)

add_subdirectory(pybind11)
pybind11_add_module(tracer tracer.cpp)
