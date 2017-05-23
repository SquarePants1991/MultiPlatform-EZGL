file(GLOB PlatformSrc
        "*.h"
        "*.cpp"
        "types/*.h"
        "types/*.cpp"
        )

# OpenGL IMP
file(GLOB OpenGL_PlatformSrc
        "impl_OpenGL/*.h"
        "impl_OpenGL/*.cpp"
        )
add_library(ELPlatform ${PlatformSrc} ${OpenGL_PlatformSrc})

find_package(glfw3 REQUIRED)
find_package(OpenGL REQUIRED)
include_directories(${OpenGL_INCLUDE_DIRS})
link_directories(${OpenGL_LIBRARY_DIRS})
add_definitions(${OpenGL_DEFINITIONS})
if(NOT OPENGL_FOUND)
    message(ERROR " OPENGL not found!")
endif(NOT OPENGL_FOUND)

target_link_libraries(ELPlatform ${GLUT_LIBRARY} ${OPENGL_LIBRARIES} glfw)
# OpenGL IMP END