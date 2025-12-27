cmake_minimum_required(VERSION 3.22)

project(voxel-engine)

find_package(glad CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(Stb REQUIRED)

add_executable(voxel-engine "src/main.cpp" "src/App.cpp")
target_link_libraries(voxel-engine PRIVATE glad::glad glfw glm::glm)
target_include_directories(voxel-engine PRIVATE ${Stb_INCLUDE_DIR})