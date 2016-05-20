add_executable( all_tests
        demo_test.cpp
        )

target_link_libraries(all_tests gtest gtest_main decibelly)
target_include_directories(all_tests PUBLIC ${CMAKE_SOURCE_DIR}/src)

add_test( NAME     runtests
          COMMAND  all_tests )