file(GLOB RendererSrc
        "*.h"
        "*.cpp"
        )

include_directories(${CMAKE_SOURCE_DIR}/ezgl/renderer)

add_executable(ELRendererTests main.cpp ${RendererSrc})
target_link_libraries(ELRendererTests ELRenderer)