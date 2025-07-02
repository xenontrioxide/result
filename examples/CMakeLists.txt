cmake_minimum_required(VERSION 3.20)

add_executable(result_examples
    "basic.cpp"
)

target_link_libraries(result_examples
    PRIVATE
        result
)