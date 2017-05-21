file(GLOB PlatformSrc
        "*.h"
        "*.cpp"
        )

add_library(ELPlatform ${PlatformSrc})