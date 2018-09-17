# Configure the ROOT options that will be required in this project. The
# following variables are set:
#  1.) ROOT - stores the root library names
MACRO(ENABLE_ROOT_SUPPORT)

  # Add the user supplied ROOT prefix to help find ROOT
  IF(ROOT_PREFIX)
    SET(CMAKE_PREFIX_PATH ${ROOT_PREFIX} ${CMAKE_PREFIX_PATH})
  ELSE()
    MESSAGE(FATAL_ERROR "The ROOT_PREFIX must be set currently!")
  ENDIF()

  # Find the ROOT package available on this system
  FIND_PACKAGE(ROOT 6.02.05 REQUIRED)

  # Set the include paths for ROOT
  INCLUDE_DIRECTORIES(${ROOT_INCLUDE_DIRS})

  # Find extra root libraries
  FIND_LIBRARY(ROOT_GEOM libGeom.so
    PATHS ${ROOT_LIBRARY_DIR})

  FIND_LIBRARY(ROOT_CORE libCore.so
    PATHS ${ROOT_LIBRARY_DIR})

  FIND_LIBRARY(ROOT_THREAD libThread.so
    PATHS ${ROOT_LIBRARY_DIR})

  # Store ROOT libraries in the ROOT variable
  SET(ROOT ${ROOT_GEOM} ${ROOT_CORE} ${ROOT_THREAD})

  # Find the root executable
  FIND_PROGRAM(ROOT_EXE root PATHS ${ROOT_BINARY_DIR})
  SET(ROOT_EXE ${ROOT_EXE} -b -q -l)

  # Echo ROOT build info if a verbose configure is requested
  IF(CMAKE_VERBOSE_CONFIGURE)
    MESSAGE("\nFound ROOT!  Here are the details: ")
    MESSAGE("   ROOT_INCLUDE_DIRS = ${ROOT_INCLUDE_DIRS}")
    MESSAGE("   ROOT_LIBRARY_DIR = ${ROOT_LIBRARY_DIR}")
    MESSAGE("   ROOT_LIBRARIES = ${ROOT}")
    MESSAGE("   ROOT_EXECUTABLES = ${ROOT_EXE}")
    MESSAGE("   ROOT_CXX_FLAGS = ${ROOT_CXX_FLAGS}")
    MESSAGE("End of ROOT details\n")
  ENDIF()

ENDMACRO()
