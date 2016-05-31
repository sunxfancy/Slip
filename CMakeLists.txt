cmake_minimum_required(VERSION 2.8)
project(RedApple)

# Options. Turn on with 'cmake -Dtest=ON'.
option(test "Build all tests." OFF) # Makes boolean 'test' available.
option(COVERAGE "Test Codecov." OFF)


find_package(BISON)
find_package(FLEX)

SET (CMAKE_C_COMPILER_ENV_VAR "clang")
SET (CMAKE_C_FLAGS "-std=c99")
SET (CMAKE_C_FLAGS_DEBUG   "-g")
SET (CMAKE_C_FLAGS_MINSIZEREL  "-Os -DNDEBUG")
SET (CMAKE_C_FLAGS_RELEASE  "-O4 -DNDEBUG")
SET (CMAKE_C_FLAGS_RELWITHDEBINFO "-O2 -g")
SET (EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

IF (COVERAGE)
    SET (CMAKE_C_FLAGS "-std=c99 -coverage")
ENDIF()


FLEX_TARGET(MyScanner ${CMAKE_CURRENT_SOURCE_DIR}/src/lex.l
					  ${CMAKE_CURRENT_BINARY_DIR}/lex.c COMPILE_FLAGS -w)
BISON_TARGET(MyParser ${CMAKE_CURRENT_SOURCE_DIR}/src/parser.y
					  ${CMAKE_CURRENT_BINARY_DIR}/parser.c)
ADD_FLEX_BISON_DEPENDENCY(MyScanner MyParser)

include_directories(build include src)

file(GLOB_RECURSE source_files ${CMAKE_CURRENT_SOURCE_DIR}/src/*.c)
list(REMOVE_ITEM  source_files ${CMAKE_CURRENT_SOURCE_DIR}/src/main.c)

add_library(slip STATIC ${source_files} ${BISON_MyParser_OUTPUTS} ${FLEX_MyScanner_OUTPUTS})

add_executable(sliper src/main.c)
target_link_libraries(sliper slip)

install(TARGETS sliper RUNTIME DESTINATION bin)

FIND_PACKAGE(Doxygen)
OPTION(BUILD_DOCUMENTATION "Create and install the HTML based API documentation (requires Doxygen)" ${DOXYGEN_FOUND})

IF(BUILD_DOCUMENTATION)
    IF(NOT DOXYGEN_FOUND)
        MESSAGE(FATAL_ERROR "Doxygen is needed to build the documentation.")
    ENDIF()

    SET(doxyfile_in ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in)
    SET(doxyfile ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)

    CONFIGURE_FILE(${doxyfile_in} ${doxyfile} @ONLY)

    ADD_CUSTOM_TARGET(doc
        COMMAND ${DOXYGEN_EXECUTABLE} ${doxyfile}
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        COMMENT "Generating API documentation with Doxygen"
        VERBATIM)

    INSTALL(DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/html DESTINATION share/doc)
ENDIF()


if (test)
    add_subdirectory(test)
endif()
