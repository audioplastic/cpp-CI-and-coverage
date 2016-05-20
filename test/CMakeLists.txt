add_executable( all_tests
        demo_test.cpp
        )


target_link_libraries(all_tests gtest gtest_main)
add_test( runtests all_tests )