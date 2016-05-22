set(LIB_SRC
        adder.cpp
        adder.h
        )

add_library(decibelly ${LIB_SRC})

if (COVERALLS)
    coveralls_setup(
            "${LIB_SRC}"
            ${COVERALLS_UPLOAD}
            "${PROJECT_SOURCE_DIR}/extern/coveralls-cmake/cmake")
endif()