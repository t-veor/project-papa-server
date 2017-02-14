include_directories(${INCLUDE_DIRECTORIES} include)

file(GLOB SOURCES "src/*.cpp")

add_library(websockets_interface ${SOURCES})

target_include_directories(websockets_interface PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
    PRIVATE src)
