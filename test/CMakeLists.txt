enable_testing()
find_package(GTest REQUIRED)

SET (CMAKE_CXX_COMPILER_ENV_VAR "clang++")
SET (CMAKE_CXX_FLAGS "-std=c++11 -g")
include_directories (${CMAKE_CURRENT_SOURCE_DIR})
include_directories (${GTEST_INCLUDE_DIRS})
file(GLOB_RECURSE test_source_files ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)

IF (COVERAGE)
    SET (CMAKE_CXX_FLAGS "-std=c++11 -g -coverage")
ENDIF()

add_executable (coretest ${test_source_files})

target_link_libraries(coretest slip ${GTEST_BOTH_LIBRARIES} pthread)

add_test(MyTest coretest)

add_custom_target( runtest ALL
                   DEPENDS coretest)

add_custom_command(TARGET runtest
                   POST_BUILD
                   COMMAND coretest)
