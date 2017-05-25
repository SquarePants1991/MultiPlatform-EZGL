file(GLOB PlatformSrc
        "*.h"
        "*.cpp"
        "types/*.h"
        "types/*.cpp"
        "utils/*.h"
        "utils/*.cpp"
        )

# OpenGL IMP
file(GLOB OpenGL_PlatformSrc
        "impl_OpenGL/*.h"
        "impl_OpenGL/*.cpp"
        "impl_OpenGL/soil/*.h"
        "impl_OpenGL/soil/*.cpp"
        "impl_OpenGL/soil/*.cc"
        )
add_library(ELPlatform ${PlatformSrc} ${OpenGL_PlatformSrc} impl_OpenGL/ELRenderPass.cpp)

find_package(glfw3 REQUIRED)

find_package(OpenGL REQUIRED)
if(NOT OPENGL_FOUND)
    message(ERROR " OPENGL not found!")
endif(NOT OPENGL_FOUND)
include_directories(${OpenGL_INCLUDE_DIRS})
link_directories(${OpenGL_LIBRARY_DIRS})
add_definitions(${OpenGL_DEFINITIONS})


find_package(GLEW REQUIRED)
if(NOT GLEW_FOUND)
    message(ERROR " GLEW not found!")
endif(NOT GLEW_FOUND)
include_directories(${GLEW_INCLUDE_DIRS})
link_directories(${GLEW_LIBRARY_DIRS})
add_definitions(${GLEW_DEFINITIONS})

target_link_libraries(ELPlatform ${GLUT_LIBRARY} ${OPENGL_LIBRARIES} glfw ${GLEW_LIBRARIES})
target_compile_definitions(ELPlatform PRIVATE Platform_OSX=1 Debug=1)
# OpenGL IMP END