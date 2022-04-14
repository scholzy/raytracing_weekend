cmake_minimum_required(VERSION 3.10)

project(Raytracing VERSION 0.1)

add_executable(
    raytracing
    src/color.hpp
    src/ray.hpp
    src/vec3.hpp
    src/main.cpp)

target_compile_features(raytracing PUBLIC cxx_std_17)
set_target_properties(raytracing PROPERTIES
                      CXX_EXTENSIONS OFF)
