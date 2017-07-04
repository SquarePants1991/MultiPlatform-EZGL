add_subdirectory(platform)
add_subdirectory(renderer)

add_library(EZGLib EZGL.hpp EZGL.cpp ../tests/renderer/BasicRendererTests.cpp ../tests/renderer/BasicRendererTests.h)