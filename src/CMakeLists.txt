# Create the static library
add_library(${PROJECT_NAME} INTERFACE)

target_include_directories(${PROJECT_NAME} INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)
target_compile_features(${PROJECT_NAME} INTERFACE cxx_std_20)
target_compile_options(${PROJECT_NAME} INTERFACE -Werror -Wall -pedantic -Wfloat-equal -Wuninitialized)
