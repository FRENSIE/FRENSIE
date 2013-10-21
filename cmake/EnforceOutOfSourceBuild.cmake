# This macro will ensure that in-source build will fail.
# NOTE: The CMAKE_SOURCE_DIR variable stores the location of the project root
#       directory. The CMAKE_BINARY_DIR variable stores the location of the
#       build directory. When these two variables are equal a fatal error is
#       passed to cmake.
MACRO(ENFORCE_OUT_OF_SOURCE_BUILD)
  IF(${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
    MESSAGE(STATUS "This project requires an out-of-source build.")
    MESSAGE(STATUS "The following procedure is recommended for building: ")
    MESSAGE(STATUS "  1.) Exit the project root directory (${CMAKE_SOURCE_DIR}).")
    MESSAGE(STATUS "  2.) Create a new parent directory for the project.")
    MESSAGE(STATUS "  3.) Move ${CMAKE_SOURCE_DIR} to the new parent directory.")
    MESSAGE(STATUS "  4.) Create a directory called build at the same level as ${CMAKE_SOURCE_DIR}.")
    MESSAGE(STATUS "  5.) Copy the example configuration script to the build directory.")
    MESSAGE(STATUS "  6.) Change CMAKE_INSTALL_PREFIX to the parent directory of the build directory (../) .")
    MESSAGE(STATUS "  7.) Change the SRC_DIR variable in the script to ${CMAKE_SOURCE_DIR}.")
    MESSAGE(STATUS "  8.) Run the configure.sh script from the build directory")
    MESSAGE(FATAL_ERROR "In-source build detected!")
  ENDIF()
ENDMACRO()
      