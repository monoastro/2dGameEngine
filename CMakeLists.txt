cmake_minimum_required(VERSION 3.10)
if(POLICY CMP0072)
  cmake_policy(SET CMP0072 NEW)
endif()
project("2DgameEngine" VERSION 0.1.0 LANGUAGES CXX)
set(BINARY ${PROJECT_NAME})
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_options(-Wall -Wextra -Werror -pedantic)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/../bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../bin)
find_package(SFML 2.5 COMPONENTS system window graphics REQUIRED)
find_package(OpenGL REQUIRED)

file(GLOB_RECURSE SOURCES "src/*.cpp" "lib/imgui/*.cpp")
add_executable(${BINARY} ${SOURCES})
target_include_directories(${BINARY} PRIVATE include include/Engine lib/imgui lib/imgui/backends)
target_link_libraries(${BINARY} sfml-window sfml-system sfml-graphics sfml-audio sfml-network OpenGL::GL)
