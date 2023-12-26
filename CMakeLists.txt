cmake_minimum_required(VERSION 3.12)
project(data-structures CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add the source files for your library
set(SOURCES
    src/vector.cxx
)
# Create the static library
add_library(${PROJECT_NAME} STATIC)

target_compile_features(${PROJECT_NAME} PRIVATE c_std_11)

target_sources(${PROJECT_NAME} PRIVATE ${SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC include)
