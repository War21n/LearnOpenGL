cmake_minimum_required(VERSION 3.10)
project(LearnOpenGL VERSION 1.0.0 LANGUAGES C CXX)

# output dir
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

# build glfw to static library
set(BUILD_SHARED_LIBS OFF CACHE BOOL "Build GLFW as a static library" FORCE)
add_subdirectory(third_party/glfw)

# build glad to static library
add_library(glad STATIC third_party/glad/src/glad.c)
target_include_directories(glad PUBLIC third_party/glad/include)

add_executable(application src/application.cpp
                           src/index_buffer_object.cpp
                           src/shader.cpp
                           src/vertex_array_object.cpp
                           src/vertex_buffer_object.cpp
                           src/util.cpp)
target_link_libraries(application glfw glad opengl32)