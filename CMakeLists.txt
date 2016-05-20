cmake_minimum_required(VERSION 2.8.11) #for target_include_directories
project(decibelly)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/extern/cmake-modules)
set(PROJECT_TEST_NAME all_tests)

option(BUILD_COVERAGE "Build with coverage." OFF)
if (BUILD_COVERAGE)
    if(CMAKE_COMPILER_IS_GNUCXX)
        SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O0 -fprofile-arcs -ftest-coverage")
        set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fprofile-arcs -ftest-coverage")
    endif()
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DDEBUG=1")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -DDEBUG=0")

add_subdirectory(src)

# Options. Turn on with 'cmake -DBUILD_TESTS=ON/OFF'.
option(BUILD_TESTS "Build all tests." ON) # Makes boolean 'test' available.
if (BUILD_TESTS)
    set(BUILD_GTEST ON)
    set(BUILD_GMOCK OFF)
    add_subdirectory(extern/gtest)
    include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

    enable_testing()
    add_subdirectory(test)
endif()
