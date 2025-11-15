add_library(Shader STATIC
    Shader.cpp
    Shader.h
)

target_link_libraries(Shader
    PRIVATE
    OpenGL::GL
    Utils
)
