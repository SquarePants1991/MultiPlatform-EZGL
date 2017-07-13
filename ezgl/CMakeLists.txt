add_subdirectory(platform)
add_subdirectory(renderer)

add_library(EZGLib EZGL.hpp EZGL.cpp ../tests/renderer/BaseRendererTests.cpp ../tests/renderer/BaseRendererTests.h)