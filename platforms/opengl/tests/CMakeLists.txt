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

include_directories(${CMAKE_SOURCE_DIR}/ezgl/)

macro(NewTest keyword entry baseOnList)
    include_directories(${CMAKE_SOURCE_DIR}/tests/${keyword})

    list(APPEND ${keyword}SRCLIST
            "${entry}"
            "../../../tests/${keyword}/*.h"
            "../../../tests/${keyword}/*.cpp")
    foreach (baseOn ${baseOnList})
        list(APPEND ${keyword}SRCLIST
                "../../../ezgl/${baseOn}/*.h"
                "../../../ezgl/${baseOn}/*.cpp"
                "../../../ezgl/${baseOn}/**/*.h"
                "../../../ezgl/${baseOn}/**/*.cpp"
                "../impl_${baseOn}/*.h"
                "../impl_${baseOn}/*.cpp"
                "../impl_${baseOn}/**/*.h"
                "../impl_${baseOn}/**/*.cpp"
                "../impl_${baseOn}/**/*.cc")
    endforeach ()

    message(${${keyword}SRCLIST})
    file(GLOB Src
            ${${keyword}SRCLIST}
            )
    add_executable(${keyword}Tests ${Src})
    target_link_libraries(${keyword}Tests ${GLUT_LIBRARY} ${OPENGL_LIBRARIES} glfw ${GLEW_LIBRARIES})
    add_definitions(-DPlatform_OSX -DDEBUG -DDebug)
endmacro(NewTest)

NewTest(platform PlatformTests.cpp "platform")
NewTest(renderer RendererTests.cpp "platform;renderer")
NewTest(geometry GeometryTests.cpp "platform;renderer;geometry")

add_custom_target(
        compileShader
        COMMAND python ${CMAKE_CURRENT_SOURCE_DIR}/../impl_renderer/shaders/src/build.py ${CMAKE_CURRENT_SOURCE_DIR}/../impl_renderer/shaders/src/
)
add_dependencies(rendererTests compileShader)




