cmake_minimum_required(VERSION 3.12)
# Data Structure and Algorithms (dsa)
project(dsa CXX)

# Add the source files for your library
set(SOURCES
    src/vector.cxx
)
# Create the static library
add_library(${PROJECT_NAME} STATIC)

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)

include(FetchContent)

add_subdirectory(third_party)

add_subdirectory(tests)

target_sources(${PROJECT_NAME} PRIVATE ${SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC include)
