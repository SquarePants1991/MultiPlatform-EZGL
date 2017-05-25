file(GLOB PlatformSrc
        "*.h"
        "*.cpp"
        )

include_directories(${CMAKE_SOURCE_DIR}/ezgl/platform)

find_package(glfw3 REQUIRED)
find_package(OpenGL REQUIRED)
include_directories(${OpenGL_INCLUDE_DIRS})
link_directories(${OpenGL_LIBRARY_DIRS})
add_definitions(${OpenGL_DEFINITIONS})
if(NOT OPENGL_FOUND)
    message(ERROR " OPENGL not found!")
endif(NOT OPENGL_FOUND)

add_executable(ELPlatformTests main.cpp ${PlatformSrc})
target_link_libraries(ELPlatformTests ELPlatform ${GLUT_LIBRARY} ${OPENGL_LIBRARIES} glfw)


include(../../CopyFiles.text)
copy_files(CopyAssets ./ ${CMAKE_BINARY_DIR})

add_dependencies(ELPlatformTests CopyAssets)