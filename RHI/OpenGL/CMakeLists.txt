add_library(OpenGLRHI
        OpenGLGraphicsManager.cpp
        ${PROJECT_SOURCE_DIR}/External/src/GL/src/glad.c
)
target_include_directories(OpenGLRHI PRIVATE "${PROJECT_SOURCE_DIR}/External/src/GL/include")

