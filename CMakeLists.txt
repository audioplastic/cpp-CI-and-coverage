cmake_minimum_required(VERSION 2.8.11) #for target_include_directories
project(decibelly)

option(BUILD_TESTS "Build all tests." ON)
option(COVERALLS "Turn on coveralls support" OFF) #better than pyton version as no sudo pip install is neededtouch sr
option(COVERALLS_UPLOAD "Upload the generated coveralls json" ON)
option(CODECOV "Build with coverage." OFF)


if (NOT MSVC) #Reduce some CI warnings
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
endif ()
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DDEBUG=1")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -DDEBUG=0")

# Force static runtime libraries
if(MSVC)
   foreach(flag
    CMAKE_C_FLAGS_RELEASE CMAKE_C_FLAGS_RELWITHDEBINFO
    CMAKE_C_FLAGS_DEBUG CMAKE_C_FLAGS_DEBUG_INIT
    CMAKE_CXX_FLAGS_RELEASE  CMAKE_CXX_FLAGS_RELWITHDEBINFO
    CMAKE_CXX_FLAGS_DEBUG  CMAKE_CXX_FLAGS_DEBUG_INIT)
    STRING(REPLACE "/MD"  "/MT" "${flag}" "${${flag}}")
    SET("${flag}" "${${flag}} /EHsc")
   endforeach()
endif()

if (COVERALLS)
    list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/extern/coveralls-cmake/cmake)
    include(Coveralls)
    coveralls_turn_on_coverage()
endif()

add_subdirectory(src)


# Options. Turn on with 'cmake -DBUILD_TESTS=ON/OFF'.
if (BUILD_TESTS)
    set(PROJECT_TEST_NAME all_tests)
    set(BUILD_GTEST ON)
    set(BUILD_GMOCK OFF)
    add_subdirectory(extern/gtest)
    include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

    enable_testing()
    add_subdirectory(test)
endif()


if (CODECOV)
    if(NOT CMAKE_BUILD_TYPE STREQUAL "Debug")
        message(FATAL_ERROR "Codecov: Code coverage results with an optimised (non-Debug) build may be misleading! Add -DCMAKE_BUILD_TYPE=Debug")
    endif()

    if(CMAKE_COMPILER_IS_GNUCXX)
        message("Making gcc coverage")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O0 -fprofile-arcs -ftest-coverage")
        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -O0 -fprofile-arcs -ftest-coverage")
    endif()

    if (CMAKE_CXX_COMPILER_ID MATCHES "Clang") # using regular Clang or AppleClang
        message("Making clang coverage")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage")
        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} --coverage")
    endif()
endif()

if (COVERALLS)
    file(GLOB MY_LIB_SRC
            "src/*.h"
            "src/*.cpp"
            )

#    get_directory_property(LIB_SRC
#            DIRECTORY ${CMAKE_SOURCE_DIR}/src
#            DEFINITION LIB_SRC)
#
#    #    http://stackoverflow.com/a/27630120/276193
#    FUNCTION(PREPEND var prefix)
#        SET(listVar "")
#        FOREACH(f ${ARGN})
#            LIST(APPEND listVar "${prefix}/${f}")
#        ENDFOREACH(f)
#        SET(${var} "${listVar}" PARENT_SCOPE)
#    ENDFUNCTION(PREPEND)
#
#    PREPEND(LIB_SRC src/ ${LIB_SRC})

    coveralls_setup(
            "${MY_LIB_SRC}"
            ${COVERALLS_UPLOAD}
            "${PROJECT_SOURCE_DIR}/extern/coveralls-cmake/cmake")
endif()