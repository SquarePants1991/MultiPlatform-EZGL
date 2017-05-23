file(GLOB PlatformSrc
        "*.h"
        "*.cpp"
        "types/*.h"
        "types/*.cpp"
        )

add_library(ELPlatform ${PlatformSrc})