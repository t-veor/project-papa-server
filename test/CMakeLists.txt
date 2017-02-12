message(STATUS "Building tests")

include_directories(${INCLUDE_DIRECTORIES} ${INCLUDE_CATCH_DIRECTORY})

file(GLOB SOURCES "*.cpp")

add_executable(tests ${SOURCES})
add_test(all ${EXECUTABLE_OUTPUT_PATH}/tests)
