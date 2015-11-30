enable_testing()
find_package(GTest REQUIRED)

include_directories (${TEST_SOURCE_DIR}/src) 
include_directories (${GTEST_INCLUDE_DIRS})
add_executable (coretest coretest.c ${TEST_SOURCE_DIR}/src/*.c) 
target_link_libraries(coretest ${GTEST_BOTH_LIBRARIES})

add_test(MyTest coretest)