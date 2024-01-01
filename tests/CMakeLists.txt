enable_testing()

find_package(GTest REQUIRED)

set(TEST_FILES
    test_vector.cxx
)
add_executable(${PROJECT_NAME}_tests ${TEST_FILES})
target_compile_features(${PROJECT_NAME}_tests PRIVATE cxx_std_20)
target_link_libraries(${PROJECT_NAME}_tests GTest::gtest_main ${PROJECT_NAME})
include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME}_tests)
