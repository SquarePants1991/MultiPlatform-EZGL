file(GLOB GeometrySrc
        "*.h"
        "*.cpp"
        "simple/*.h"
        "simple/*.cpp"
        "utils/*.h"
        "utils/*.cpp"
        )
add_library(geometry ${GeometrySrc})