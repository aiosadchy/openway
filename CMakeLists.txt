cmake_minimum_required (VERSION 3.8)

project(
    openway
    VERSION         0.0.1
    DESCRIPTION     "A simple general purpose utility library for modern C++"
    HOMEPAGE_URL    "https://github.com/aiosadchy/openway"
)

function(msg level)
    message(${level} "utl: " ${ARGN})
endfunction()

set(CMAKE_CXX_STANDARD 17)

add_executable(openway
    src/main.cpp
)

target_include_directories(openway PRIVATE include)

if(MSVC)
    target_compile_options(openway PRIVATE /W4 /WX)
else()
    target_compile_options(openway PRIVATE -Wall -Wextra -pedantic -Werror)
endif()
