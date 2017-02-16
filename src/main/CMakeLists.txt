include_directories(${INCLUDE_DIRECTORIES} include)

file(GLOB SOURCES "src/*.cpp")

add_executable(server ${SOURCES})

target_link_libraries(server osc_interface)
target_link_libraries(server websockets_interface)

target_link_libraries(server rt)
target_link_libraries(server pthread)

# Boost
set(Boost_USE_STATIC_LIBS OFF) 
set(Boost_USE_MULTITHREADED ON)  
set(Boost_USE_STATIC_RUNTIME OFF) 
find_package(Boost REQUIRED COMPONENTS system chrono)
include_directories(${Boost_INCLUDE_DIRS})
target_link_libraries(server ${Boost_LIBRARIES})

# OpenSSL
if(APPLE)
  set(OPENSSL_ROOT_DIR "/usr/local/opt/openssl")
endif()

find_package(OpenSSL REQUIRED)
#include_directories(${OPENSSL_INCLUDE_DIR})
target_link_libraries(server ${OPENSSL_CRYPTO_LIBRARY})

if(MSYS)
    target_link_libraries(server ws2_32 wsock32)
endif()
