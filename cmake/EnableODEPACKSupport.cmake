# Configure the ODEPACK options that will be required in this project. The 
# following variables will be set:
MACRO(ENABLE_ODEPACK_SUPPORT)

  SET(ODEPACK_LIBRARY_DIR ${ODEPACK_PREFIX})

  # Find the ODEPACK library
#  FIND_LIBRARY(ODEPACK libodepack.a ${ODEPACK_LIBRARY_DIR})
#  IF(${ODEPACK} MATCHES NOTFOUND)
#    MESSAGE(FATAL_ERROR "The odepack library could not be found.")
#  ENDIF(${ODEPACK} MATCHES NOTFOUND)
  SET(ODEPACK /home/kliberty/frensie/deps/install/odepack/lib/libodepack.a)
  
  # Set the link paths for HDF5
  LINK_DIRECTORIES(${ODEPACK_LIBRARY_DIR})

  # Echo the HDF5 details if a verbose configure was requested
  IF(CMAKE_VERBOSE_CONFIGURE)
    MESSAGE("Found ODEPACK! Here are the details: ")
    MESSAGE(" ODEPACK_PREFIX = ${ODEPACK_PREFIX}")
    MESSAGE(" ODEPACK_LIBRARY_DIR = ${ODEPACK_LIBRARY_DIR}")
    MESSAGE(" ODEPACK_LIBRARY = ${ODEPACK}")
    MESSAGE("End of ODEPACK details\n")
  ENDIF()

ENDMACRO(ENABLE_ODEPACK_SUPPORT)
