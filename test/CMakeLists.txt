add_executable( ${PROJECT_TEST_NAME}
        demo_test.cpp
        )

target_link_libraries(${PROJECT_TEST_NAME} gtest gtest_main decibelly)
target_include_directories(${PROJECT_TEST_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/src)

add_test( NAME     runtests
          COMMAND  ${PROJECT_TEST_NAME} )