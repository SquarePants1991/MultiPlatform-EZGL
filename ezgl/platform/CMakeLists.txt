file(GLOB PlatformSrc
        "*.h"
        "*.cpp"
        "types/*.h"
        "types/*.cpp"
        "utils/*.h"
        "utils/*.cpp"
        )
add_library(ELPlatform ${PlatformSrc})