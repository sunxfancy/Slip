enable_testing()
find_package(GTest REQUIRED)

SET (CMAKE_CXX_COMPILER_ENV_VAR "clang++")
SET (CMAKE_CXX_FLAGS "-std=c++11 -g")
include_directories (${CMAKE_CURRENT_SOURCE_DIR}) 
include_directories (${GTEST_INCLUDE_DIRS})
file(GLOB_RECURSE test_source_files ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
file(GLOB_RECURSE src_source_files ${CMAKE_CURRENT_SOURCE_DIR}/../src/*.c)
list(REMOVE_ITEM src_source_files ${CMAKE_CURRENT_SOURCE_DIR}/../src/main.c)

add_executable (coretest ${test_source_files} ${src_source_files}
						 ${BISON_MyParser_OUTPUTS} 
						 ${FLEX_MyScanner_OUTPUTS})
target_link_libraries(coretest ${GTEST_BOTH_LIBRARIES} pthread)

add_test(MyTest coretest)