cmake_minimum_required(VERSION 3.1)

project(project_papa_server)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 14)

set(DEBUG_FLAGS "-g -O1 -Wall -Wextra -pedantic")
set(RELEASE_FLAGS "-O3 -Wall -Wextra -pedantic")

set(CMAKE_CXX_FLAGS ${RELEASE_FLAGS})
set(CMAKE_CXX_FLAGS_DEBUG ${DEBUG_FLAGS})
set(CMAKE_CONFIGURATION_TYPES Debug Release)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_BINARY_DIR})

# Boost
set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
find_package(Boost REQUIRED COMPONENTS system chrono)
include_directories(${Boost_INCLUDE_DIRS})

# OpenSSL
if(APPLE)
  set(OPENSSL_ROOT_DIR "/usr/local/opt/openssl/include")
endif()

find_package(OpenSSL REQUIRED)
include_directories(${OPENSSL_INCLUDE_DIR})

enable_testing()

add_subdirectory(lib)

set(INCLUDE_DIRECTORIES ${INCLUDE_DIRECTORIES} ${CMAKE_SOURCE_DIR}/include)

add_subdirectory(src)
add_subdirectory(test)

