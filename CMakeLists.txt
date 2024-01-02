cmake_minimum_required(VERSION 3.12)
# Data Structure and Algorithms (dsa)
project(
  dsa
  VERSION 0.0.1
  LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(CTest)
include(CMakeDependentOption)
include(GNUInstallDirs)
include(InstallRequiredSystemLibraries)
include(CMakePackageConfigHelpers)

# Custom modules and scripts
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake") # Make our
                                                                 # cmake scripts
                                                                 # available
include(BuildHelpers) # Helpers for writing cmake files

# ##############################################################################
# Options  ##
# ##############################################################################

option(
  ENABLE_INSTALL
  "Should ${PROJECT_NAME} be added to the install list? Useful if included using add_subdirectory."
  ON)
option(ENABLE_TESTING "Should unit tests be compiled." ON)

set(${PROJECT_NAME}_INSTALL_CMAKEDIR
    "${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}"
    CACHE STRING "Path to install ${PROJECT_NAME} Config*.cmake files to.")

add_subdirectory(src)

if(ENABLE_TESTING)
  find_package(GTest REQUIRED)
  include(GoogleTest)
  add_subdirectory(tests)
endif()

# ##############################################################################
# Packaging ##
# ##############################################################################

if(ENABLE_INSTALL)
  write_basic_package_version_file(
    "${PROJECT_NAME}ConfigVersion.cmake"
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY SameMajorVersion)
  configure_package_config_file(
    ${PROJECT_SOURCE_DIR}/cmake/Config.cmake.in
    ${PROJECT_BINARY_DIR}/${PROJECT_NAME}Config.cmake
    INSTALL_DESTINATION ${${PROJECT_NAME}_INSTALL_CMAKEDIR}
    NO_SET_AND_CHECK_MACRO NO_CHECK_REQUIRED_COMPONENTS_MACRO)
  # Adjust the paths as per your project source structure
  install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
  install(
    TARGETS ${PROJECT_NAME}
    EXPORT ${PROJECT_NAME}Targets
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
  install(
    EXPORT ${PROJECT_NAME}Targets
    FILE ${PROJECT_NAME}Targets.cmake
    NAMESPACE ${PROJECT_NAME}::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME})
  install(FILES "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
                "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
          DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME})
endif()
