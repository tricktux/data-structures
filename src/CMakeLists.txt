# Create the static library
add_library(${PROJECT_NAME} STATIC)

target_sources(${PROJECT_NAME} PRIVATE vector.cxx)
# target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_include_directories(${PROJECT_NAME} PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)
