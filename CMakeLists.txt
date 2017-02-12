cmake_minimum_required(VERSION 3.1)

project(project_papa_server)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 11)

set(DEBUG_FLAGS "-std=c++11 -g -O1 -Wall -Wextra -pedantic")
set(RELEASE_FLAGS "-std=c++11 -O3 -Wall -Wextra -pedantic")

set(CMAKE_CXX_FLAGS ${RELEASE_FLAGS})
set(CMAKE_CXX_FLAGS_DEBUG ${DEBUG_FLAGS})
set(CMAKE_CONFIGURATION_TYPES Debug Release)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_BINARY_DIR})

enable_testing()

add_subdirectory(lib)
add_subdirectory(src)
add_subdirectory(test)

