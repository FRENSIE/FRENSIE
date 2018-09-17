# Configure the DagMC options that will be required in this project. The
# following variables will be set
# 1.) DagMC - stores the DagMC library name
MACRO(ENABLE_DAGMC_SUPPORT)

  # Add the user supplied DagMC prefix to help find DagMC
  IF(DEFINED DAGMC_PREFIX)
    SET(CMAKE_PREFIX_PATH ${DAGMC_PREFIX}/lib ${CMAKE_PREFIX_PATH})
  ELSE()
    MESSAGE(FATAL_ERROR "The DAGMC_PREFIX must be set currently.")
  ENDIF()

  SET(DAGMC_INCLUDE_DIRS ${DAGMC_PREFIX}/include)
  INCLUDE_DIRECTORIES(${DAGMC_INCLUDE_DIRS})
  
  SET(DAGMC_LIBRARY_DIRS ${DAGMC_PREFIX}/lib)
  LINK_DIRECTORIES(${DAGMC_LIBRARY_DIRS})
  FIND_LIBRARY(DAGMC dagmc ${DAGMC_LIBRARY_DIRS})
  FIND_LIBRARY(PYNE_DAGMC pyne_dagmc ${DAGMC_LIBRARY_DIRS})

  IF(${DAGMC} MATCHES NOTFOUND)
    MESSAGE(FATAL_ERROR "The dagmc library could not be found.")
  ENDIF()

  IF(${PYNE_DAGMC} MATCHES NOTFOUND)
    MESSAGE(FATAL_ERROR "The pyne_dagmc libray could not be found.")
  ENDIF()

  SET(DAGMC ${DAGMC} ${PYNE_DAGMC})

  # Echo the Moab details if a verbose configure was requested
  IF(CMAKE_VERBOSE_CONFIGURE)
    MESSAGE("Found DAGMC!  Here are the details: ")
    MESSAGE(" DAGMC_PREFIX = ${DAGMC_PREFIX}")
    MESSAGE(" DAGMC_INCLUDE_DIRS = ${DAGMC_INCLUDE_DIRS}")
    MESSAGE(" DAGMC_LIBRARY_DIRS = ${DAGMC_LIBRARY_DIRS}")
    MESSAGE(" DAGMC_LIBRARIES = ${DAGMC}")
    MESSAGE("End of DAGMC details\n")
  ENDIF()
  
ENDMACRO()
