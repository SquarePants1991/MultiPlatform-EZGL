file(GLOB PlatformSrc
        "*.h"
        "*.cpp"
        )

include_directories(${CMAKE_SOURCE_DIR}/ezgl/platform)

add_executable(ELPlatformTests main.cpp ${PlatformSrc})
target_link_libraries(ELPlatformTests ELPlatform)