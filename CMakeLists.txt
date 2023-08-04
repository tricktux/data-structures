cmake_minimum_required(VERSION 3.12)
project(data-structures)

# Add the source files for your library
set(SOURCES
    src/array.c
)
# Create the static library
add_library(${PROJECT_NAME} STATIC)

target_compile_features(${PROJECT_NAME} PRIVATE c_std_11)

target_sources(${PROJECT_NAME} PRIVATE ${SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC include)

# Add an executable for testing
# add_executable("$(PROJECT_NAME)-tests" test/test.c)
# Link the library to the test executable
# target_link_libraries("$(PROJECT_NAME)-tests" PRIVATE $(PROJECT_NAME))
# Add a test
# include(CTest)
# add_test(NAME "$(PROJECT_NAME)-tests" COMMAND "$(PROJECT_NAME)-tests")

