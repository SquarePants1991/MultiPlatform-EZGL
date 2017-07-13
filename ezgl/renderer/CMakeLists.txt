file(GLOB RendererSrc
        "*.h"
        "*.cpp"
        )

add_library(renderer ${RendererSrc})
add_dependencies(renderer platform)