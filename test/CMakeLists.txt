cmake_minimum_required(VERSION 3.20)

find_package(GTest CONFIG REQUIRED)

include(GoogleTest)

add_executable(result_tests
    "main.cpp"
    "test_result.cpp"
    "test_error.cpp"
    "test_failure.cpp"
    "test_success.cpp"
)

target_link_libraries(result_tests
    PRIVATE
        GTest::gtest
        GTest::gtest_main
        result
)

gtest_discover_tests(result_tests)
