cmake_minimum_required(VERSION 3.22)

project(voxel-engine)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

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
)
target_link_libraries(voxel-engine PRIVATE glad::glad glfw glm::glm)
target_include_directories(voxel-engine PRIVATE ${Stb_INCLUDE_DIR})
