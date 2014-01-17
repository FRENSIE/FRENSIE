# Add an uninstall target to the Makefile
MACRO(ADD_UNINSTALL_TARGET)

  # Configure the cmake_uninstall file
  CONFIGURE_FILE(${CMAKE_SOURCE_DIR}/cmake/cmake_uninstall.cmake.in
    ${CMAKE_BINARY_DIR}/cmake_uninstall.cmake
    IMMEDIATE @ONLY)

  # Add the uninstall target to the make file
  ADD_CUSTOM_TARGET(uninstall
    COMMAND ${CMAKE_COMMAND} -P ${CMAKE_BINARY_DIR}/cmake_uninstall.cmake)

ENDMACRO()