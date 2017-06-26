cmake_minimum_required(VERSION 2.8)

Project(EZGL)
add_compile_options(-std=c++11)

add_subdirectory(ezgl)
add_subdirectory(tests)
add_subdirectory(platforms/opengl)
