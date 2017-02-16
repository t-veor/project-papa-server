message(STATUS "Building tests")

set(CTEST_OUTPUT_ON_FAILURE 1)

include_directories(${INCLUDE_DIRECTORIES} ${INCLUDE_CATCH_DIRECTORY})

file(GLOB SOURCES "*.cpp")

add_executable(tests ${SOURCES})
target_link_libraries(tests osc_interface)

target_link_libraries(tests pthread)

# Boost
set(Boost_USE_STATIC_LIBS OFF) 
set(Boost_USE_MULTITHREADED ON)  
set(Boost_USE_STATIC_RUNTIME OFF) 
find_package(Boost REQUIRED COMPONENTS system chrono)
include_directories(${Boost_INCLUDE_DIRS})
target_link_libraries(tests ${Boost_LIBRARIES})


add_test(all ${EXECUTABLE_OUTPUT_PATH}/tests)
