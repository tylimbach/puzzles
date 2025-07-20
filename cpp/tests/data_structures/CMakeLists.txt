add_executable(vector_test vector_test.cpp)
target_link_libraries(vector_test
    PRIVATE
        data_structures
        test_main
        gtest
        gmock
)

add_test(NAME VectorTest COMMAND vector_test)