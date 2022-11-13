include(FetchContent)


function(add_dependency name repository tag)
    FetchContent_Declare(${name}
        GIT_REPOSITORY ${repository}
        GIT_TAG ${tag}
    )
    FetchContent_MakeAvailable(${name})
endfunction()


add_dependency(glad
    https://github.com/Dav1dde/glad.git
    v0.1.36
)

add_dependency(glfw
    https://github.com/glfw/glfw.git
    3.3.7
)

add_dependency(glm
    https://github.com/g-truc/glm.git
    0.9.9.8
)

add_dependency(tinyobjloader
    https://github.com/tinyobjloader/tinyobjloader.git
    v1.0.7
)

add_dependency(utl
    https://github.com/aiosadchy/utl.git
    master
)
