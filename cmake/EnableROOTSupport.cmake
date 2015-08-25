# Configure the ROOT options that will be required in this project. The 
# following variables are set:
#  1.) ROOT - stores the root library names
MACRO(ENABLE_ROOT_SUPPORT)

  # Add the user supplied ROOT prefix to help find ROOT
  IF(ROOT_PREFIX)
    SET(CMAKE_PREFIX_PATH ${ROOT_PREFIX} ${CMAKE_PREFIX_PATH})
  ENDIF()

  # Find the ROOT package available on this system
  FIND_PACKAGE(ROOT 6.02.05 REQUIRED)

  # Set the include paths for ROOT
  INCLUDE_DIRECTORIES(${ROOT_INCLUDE_DIRS})

  # Find extra root libraries
  FIND_LIBRARY(ROOT_GEOM libGeom.so
    PATHS ${ROOT_PREFIX}/lib)

  FIND_LIBRARY(ROOT_CORE libCore.so
    PATHS ${ROOT_PREFIX}/lib)

  # Store ROOT libraries in the ROOT variable
  SET(ROOT ${ROOT_GEOM} ${ROOT_CORE})

  # Configure the root_config.hpp header file
  SET(HAVE_${PROJECT_NAME}_ROOT "1")

  SET(CMAKEDEFINE \#cmakedefine)
  CONFIGURE_FILE(${CMAKE_SOURCE_DIR}/cmake/root_config.hpp.in
    ${CMAKE_BINARY_DIR}/${PROJECT_NAME}_root_config.hpp.in)
  CONFIGURE_FILE(${CMAKE_BINARY_DIR}/${PROJECT_NAME}_root_config.hpp.in
    ${CMAKE_BINARY_DIR}/${PROJECT_NAME}_root_config.hpp)

  # Echo ROOT build info if a verbose configure is requested
  IF(CMAKE_VERBOSE_CONFIGURE)
    MESSAGE("\nFound ROOT!  Here are the details: ")
    MESSAGE("   ROOT_INCLUDE_DIRS = ${ROOT_INCLUDE_DIRS}")
    MESSAGE("   ROOT_LIBRARY_DIR = ${ROOT_LIBRARY_DIR}")
    MESSAGE("   DEFAULT_ROOT_LIBRARIES = ${ROOT_LIBRARIES}")
    MESSAGE("   ROOT_LIBRARIES = ${ROOT}")
    MESSAGE("   ROOT_CXX_FLAGS = ${ROOT_CXX_FLAGS}")
    MESSAGE("End of ROOT details\n")
  ENDIF()

ENDMACRO()
