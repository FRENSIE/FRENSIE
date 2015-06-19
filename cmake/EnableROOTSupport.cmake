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
  FIND_LIBRARY(ROOT_EXTRA_LIBS libGeom.so 
    PATHS ${ROOT_PREFIX}/lib)

  # Store ROOT libraries in the ROOT variable
  SET(ROOT ${ROOT_LIBRARIES} ${ROOT_EXTRA_LIBS})

  # Echo ROOT build info if a verbose configure is requested
  IF(CMAKE_VERBOSE_CONFIGURE)
    MESSAGE("\nFound ROOT!  Here are the details: ")
    MESSAGE("   ROOT_INCLUDE_DIRS = ${ROOT_INCLUDE_DIRS}")
    MESSAGE("   ROOT_LIBRARY_DIR = ${ROOT_LIBRARY_DIR}")
    MESSAGE("   ROOT_LIBRARIES = ${ROOT}")
    MESSAGE("   ROOT_CXX_FLAGS = ${ROOT_CXX_FLAGS}")
    MESSAGE("End of ROOT details\n")
  ENDIF()

ENDMACRO()