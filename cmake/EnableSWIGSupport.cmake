# Configure the SWIG options that will be required in this project. The
# following variables will be set
# 1.) 
MACRO(ENABLE_SWIG_SUPPORT)
  
  # Add the user supplied SWIG prefix to help find SWIG
  SET(CMAKE_PREFIX_PATH ${SWIG_PREFIX} ${CMAKE_PREFIX_PATH})

  # Find the SWIG package available on this system
  FIND_PACKAGE(SWIG 3.0.8 REQUIRED)

  # Use the local UseSWIG.cmake file
  INCLUDE(${CMAKE_SOURCE_DIR}/cmake/UseSWIG.cmake)
  
  IF(CMAKE_VERBOSE_CONFIGURE)
    MESSAGE("Found SWIG! Here are the details: ")
    MESSAGE("  SWIG_DIR = ${SWIG_DIR}")
    MESSAGE("  SWIG_EXECUTABLE = ${SWIG_EXECUTABLE}")
    MESSAGE("  SWIG_VERSION = ${SWIG_VERSION}")
    MESSAGE("End of SWIG details\n")
  ENDIF()
  
ENDMACRO()