# Configure the Moab options that will be required in this project. The 
# following variables will be set:
# 1.) MOAB - stores the Moab library name
MACRO(ENABLE_MOAB_SUPPORT)

  # Add the user supplied Moab prefix to help find Moab
  SET(CMAKE_PREFIX_PATH ${MOAB_PREFIX}/lib ${CMAKE_PREFIX_PATH})

  # Find the Moab package available on this system
  FIND_PACKAGE(MOAB REQUIRED)

  # Use the user supplied prefix to find the Moab libraries and include dirs.
  # SET(MOAB_INCLUDE_DIRS ${MOAB_PREFIX}/include)
  SET(MOAB_LIBRARY_DIRS ${MOAB_PREFIX}/lib)
  FIND_LIBRARY(MOAB MOAB ${MOAB_LIBRARY_DIRS})
  
  IF(${MOAB} MATCHES NOTFOUND)
    MESSAGE(FATAL_ERROR "The moab library could not be found.")
  ENDIF()

  FIND_LIBRARY(DAGMC dagmc ${MOAB_LIBRARY_DIRS})

  IF(${DAGMC} MATCHES NOTFOUND)
    MESSAGE(FATAL_ERROR "The dagmc library could not be found.")
  ENDIF()

  SET(MOAB ${DAGMC} ${MOAB} ${MOAB_LIBRARIES})

  # Set the include paths for Moab
  INCLUDE_DIRECTORIES(${MOAB_INCLUDE_DIRS})

  # Set the link paths for Moab
  LINK_DIRECTORIES(${MOAB_LIBRARY_DIRS})

  # Echo the Moab details if a verbose configure was requested
  IF(CMAKE_VERBOSE_CONFIGURE)
    MESSAGE("Found MOAB!  Here are the details: ")
    MESSAGE(" MOAB_PREFIX = ${MOAB_PREFIX}")
    MESSAGE(" MOAB_INCLUDE_DIRS = ${MOAB_INCLUDE_DIRS}")
    MESSAGE(" MOAB_LIBRARY_DIRS = ${MOAB_LIBRARY_DIRS}")
    MESSAGE(" MOAB_LIBRARY = ${MOAB}")
    MESSAGE("End of MOAB details\n")
  ENDIF()

ENDMACRO(ENABLE_MOAB_SUPPORT)