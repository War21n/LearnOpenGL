# 设置 CMake 最低版本和项目名称
cmake_minimum_required(VERSION 3.10)
project(LearnOpenGL VERSION 1.0.0 LANGUAGES CXX)

# 设置输出目录
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

# 配置 GLFW
# 添加 GLFW 源代码所在目录
add_subdirectory(third_party/glfw)

# 设置 GLFW 编译为静态库（如果你希望使用动态库，设置为 ON）
set(GLFW_BUILD_SHARED_LIBS OFF CACHE BOOL "Build GLFW as a static library" FORCE)

# 添加项目的源文件
# add_executable(LearnOpenGL src/main.cpp)

# 链接 GLFW 库
# target_link_libraries(LearnOpenGL PRIVATE glfw)
