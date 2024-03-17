# 需要的最低 CMake 版本
cmake_minimum_required(VERSION 3.12)

# 工程名
project(3-opengl)

# 支持的 C++ 版本
set(CMAKE_CXX_STANDARD 17)
file(GLOB ASSETS "./Shader")
file(COPY ${ASSETS} DESTINATION ${CMAKE_BINARY_DIR})

file(GLOB ASSETS1 "./Textures")
file(COPY ${ASSETS1} DESTINATION ${CMAKE_BINARY_DIR})

include_directories(
	SYSTEM ${CMAKE_CURRENT_SOURCE_DIR}/NewFolder/include
)
link_directories(
	SYSTEM ${CMAKE_CURRENT_SOURCE_DIR}/NewFolder/lib
)

# 本工程生成 exe
add_executable(openglStudy "main.cpp" "glad.c""CVector.h" "camera.h" "graph.h" "NewFolder/include/stb_image.h" "NewFolder/include/stb_image.h")

# 链接所需的库
target_link_libraries(openglStudy glfw3.lib)
