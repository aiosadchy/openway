################################################################################
#                                   openway                                    #
################################################################################

cmake_minimum_required (VERSION 3.8)

project(openway
    VERSION         0.1.0
    DESCRIPTION     "Some code, completely useless in its current state"
    HOMEPAGE_URL    "https://github.com/aiosadchy/openway"
)

function(msg level)
    message(${level} "openway: " ${ARGN})
endfunction()

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(external)


################################################################################
#                                  executable                                  #
################################################################################

add_executable(openway
    src/openway/gl/glad_session.cpp
    src/openway/gl/glfw_session.cpp
    src/openway/gl/shader.cpp
    src/openway/gl/shader_program.cpp

    src/openway/log.cpp

    src/openway/graphics/camera.cpp
    src/openway/graphics/orthographic_camera.cpp
    src/openway/graphics/perspective_camera.cpp

    src/openway/io/keyboard.cpp
    src/openway/io/mouse.cpp
    src/openway/io/window.cpp

    src/openway/utility/timer.cpp

    src/main.cpp
)

target_include_directories(openway
    PUBLIC include
)

target_link_libraries(openway
    PUBLIC glfw
    PUBLIC glad
    PUBLIC glm
    PUBLIC utl
)

target_compile_definitions(openway
    PUBLIC OPENWAY_SOURCE_ROOT="${CMAKE_SOURCE_DIR}"
    PUBLIC GLFW_INCLUDE_NONE
)

if(MSVC)
    target_compile_options(openway PRIVATE /W4 /WX)
else()
    target_compile_options(openway PRIVATE -fno-builtin-log -Wall -Wextra -pedantic -Werror)
endif()
