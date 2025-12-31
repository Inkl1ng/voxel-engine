cmake_minimum_required(VERSION 3.22)

project(voxel-engine)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(glad CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(Stb REQUIRED)

add_executable(voxel-engine
    "src/main.cpp"
    "src/App.cpp"
    "src/Chunk.cpp"
    "src/Block.cpp"
    "src/Shader.cpp"
    "src/Player.cpp"
    "src/debug.cpp"
    "src/Input_handler.cpp"
)
target_link_libraries(voxel-engine PRIVATE glad::glad glfw glm::glm)
target_include_directories(voxel-engine PRIVATE ${Stb_INCLUDE_DIR})
