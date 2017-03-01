message(STATUS "Building tests")

set(CTEST_OUTPUT_ON_FAILURE 1)

include_directories(${INCLUDE_DIRECTORIES} ${INCLUDE_CATCH_DIRECTORY})

file(GLOB SOURCES "*.cpp")

add_executable(tests ${SOURCES})
target_link_libraries(tests osc_interface)

target_link_libraries(tests pthread)

target_link_libraries(tests ${Boost_LIBRARIES})
target_link_libraries(tests ${OPENSSL_LIBRARIES})


add_test(all ${EXECUTABLE_OUTPUT_PATH}/tests)
