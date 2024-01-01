enable_testing()

find_package(GTest REQUIRED)

add_executable(${PROJECT_NAME}_tests ${CMAKE_SOURCE_DIR}/tests/test_vector.cxx)
target_compile_features(${PROJECT_NAME}_tests PRIVATE cxx_std_20)
target_link_libraries(${PROJECT_NAME}_tests GTest::gtest_main ${PROJECT_NAME})
include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME}_tests)
