add_subdirectory(platform)
add_subdirectory(renderer)

add_library(EZGLib EZGL.hpp EZGL.cpp)
target_link_libraries(EZGLib ELPlatform)