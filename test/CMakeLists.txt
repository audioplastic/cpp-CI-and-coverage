add_executable( all_tests
        demo_test.cpp
        )

target_link_libraries(all_tests gtest gtest_main)

add_test( NAME     runtests
          COMMAND  all_tests )