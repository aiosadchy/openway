include(FetchContent)


FetchContent_Declare(utl
    GIT_REPOSITORY https://github.com/aiosadchy/utl.git
    GIT_TAG fa9271e573c3415fe1705cbad7bb7458b6c96794
)
FetchContent_MakeAvailable(utl)


FetchContent_Declare(secs
    GIT_REPOSITORY https://github.com/aiosadchy/secs.git
)
FetchContent_MakeAvailable(secs)


FetchContent_Declare(glm
    GIT_REPOSITORY https://github.com/g-truc/glm.git
    GIT_TAG bf71a834948186f4097caa076cd2663c69a10e1e
)
FetchContent_MakeAvailable(glm)
