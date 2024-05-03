add_executable(${PROJECT_NAME}_tests ${CMAKE_SOURCE_DIR}/tests/test_vector.cxx)

target_include_directories(
  ${PROJECT_NAME} PUBLIC $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>)

target_compile_features(${PROJECT_NAME}_tests PRIVATE cxx_std_20)
target_compile_options(${PROJECT_NAME}_tests PRIVATE -Werror -Wall -pedantic -Wfloat-equal -Wuninitialized)
target_link_libraries(${PROJECT_NAME}_tests GTest::gtest_main ${PROJECT_NAME})
gtest_discover_tests(${PROJECT_NAME}_tests)

add_custom_target(
  run_tests ALL
  COMMAND ${CMAKE_CTEST_COMMAND}
  DEPENDS ${PROJECT_NAME}_tests)
