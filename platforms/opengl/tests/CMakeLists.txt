file(GLOB PlatformSrc
        "*.h"
        "*.cpp"
        "../../../tests/**/*.h"
        "../../../tests/**/*.cpp"
        "../impl_platform/*.h"
        "../impl_platform/*.cpp"
        "../impl_platform/**/*.h"
        "../impl_platform/**/*.cpp"
        "../impl_platform/**/*.cc"

        "../impl_renderer/*.h"
        "../impl_renderer/*.cpp"
        "../impl_renderer/**/*.h"
        "../impl_renderer/**/*.cpp"
        "../impl_renderer/**/*.cc"
        )

include_directories(${CMAKE_SOURCE_DIR}/ezgl/)
include_directories(${CMAKE_SOURCE_DIR}/tests/platform)
include_directories(${CMAKE_SOURCE_DIR}/tests/renderer)

find_package(glfw3 REQUIRED)
find_package(GLEW REQUIRED)
if (GLEW_FOUND)
    include_directories(${GLEW_INCLUDE_DIRS})
endif()
find_package(OpenGL REQUIRED)
include_directories(${OpenGL_INCLUDE_DIRS})
link_directories(${OpenGL_LIBRARY_DIRS})
add_definitions(${OpenGL_DEFINITIONS})
if(NOT OPENGL_FOUND)
    message(ERROR " OPENGL not found!")
endif(NOT OPENGL_FOUND)

add_executable(ELPlatformTests main.cpp ${PlatformSrc})
target_link_libraries(ELPlatformTests ELPlatform ${GLUT_LIBRARY} ${OPENGL_LIBRARIES} glfw ${GLEW_LIBRARIES})
add_definitions(-DPlatform_OSX)


include(../../../CopyFiles.text)
copy_files(CopyAssets .. ${CMAKE_BINARY_DIR})

add_dependencies(ELPlatformTests CopyAssets)