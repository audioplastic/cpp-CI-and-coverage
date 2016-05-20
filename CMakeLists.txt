cmake_minimum_required(VERSION 3.1)
project(decibelly)


add_executable(thing src/dummy.cpp)

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