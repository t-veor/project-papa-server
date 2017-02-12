message(STATUS "Building tests")

include_directories("../include")
include_directories("../lib/catch")

file(GLOB SOURCES "*.cpp")

add_executable(tests ${SOURCES})
add_test(all ${EXECUTABLE_OUTPUT_PATH}/tests)
