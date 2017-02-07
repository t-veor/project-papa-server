cmake_minimum_required(VERSION 3.1)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set (CMAKE_CXX_STANDARD 11)

project(project_papa_server)

include_directories(include)

file(GLOB SOURCES "src/*.cpp")

add_executable(server ${SOURCES})

target_link_libraries(server rt)
target_link_libraries(server pthread)

# Boost
set(Boost_USE_STATIC_LIBS OFF) 
set(Boost_USE_MULTITHREADED ON)  
set(Boost_USE_STATIC_RUNTIME OFF) 
find_package(Boost REQUIRED COMPONENTS system chrono)
include_directories(${Boost_INCLUDE_DIRS})
target_link_libraries(server ${Boost_LIBRARIES})
