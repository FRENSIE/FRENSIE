# Configure the Moab options that will be required in this project. The 
# following variables will be set:
# 1.) MOAB - stores the Moab library name
MACRO(ENABLE_MOAB_SUPPORT)

  # Use the user supplied prefix to find the Moab libraries and include dirs.
  SET(MOAB_INCLUDE_DIRS ${MOAB_PREFIX}/include)
  SET(MOAB_LIBRARY_DIRS ${MOAB_PREFIX}/lib)
  FIND_LIBRARY(MOAB MOAB ${MOAB_LIBRARY_DIRS})
  
  IF(${MOAB} MATCHES NOTFOUND)
    MESSAGE(FATAL_ERROR "The moab library could not be found.")
  ENDIF(${MOAB} MATCHES NOTFOUND)

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