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

################################################################################
#                                 dependencies                                 #
################################################################################

include(FetchContent)
FetchContent_Declare(utl
    GIT_REPOSITORY https://github.com/aiosadchy/utl.git
    GIT_TAG fa9271e573c3415fe1705cbad7bb7458b6c96794
)
FetchContent_MakeAvailable(utl)

################################################################################
#                                  executable                                  #
################################################################################

add_executable(openway
    src/main.cpp
)

target_include_directories(openway PUBLIC include)
target_link_libraries(openway PUBLIC utl)

if(MSVC)
    target_compile_options(openway PRIVATE /W4 /WX)
else()
    target_compile_options(openway PRIVATE -Wall -Wextra -pedantic -Werror)
endif()
