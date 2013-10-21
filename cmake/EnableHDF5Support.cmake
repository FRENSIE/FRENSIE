# Configure the HDF5 options that will be required in this project. The 
# following variables will be set:
# 1.) HDF5 - stores the HDF5 cpp wrapper library and the HDF5 core library
MACRO(ENABLE_HDF5_SUPPORT)

  # Use the user supplied prefix to find the HDF5 libraries and include dirs.
  SET(HDF5_INCLUDE_DIRS 
    ${HDF5_PREFIX}/include
    ${HDF5_PREFIX}/include/cpp
    ${HDF5_PREFIX}/include/hl)
  SET(HDF5_LIBRARY_DIRS ${HDF5_PREFIX}/lib)
 
  # Find the HDF5 c++ wrapper library
  FIND_LIBRARY(HDF5CPP libhdf5_cpp.a ${HDF5_LIBRARY_DIRS})
  IF(${HDF5CPP} MATCHES NOTFOUND)
    MESSAGE(FATAL_ERROR "The HDF5 cpp library could not be found.")
  ENDIF(${HDF5CPP} MATCHES NOTFOUND)
  
  # Find the HDF5 core library
  FIND_LIBRARY(HDF5CORE libhdf5.a ${HDF5_LIBRARY_DIRS})
  IF(${HDF5CORE} MATCHES NOTFOUND)
    MESSAGE(FATAL_ERROR "The HDF5 core library could not be found.")
  ENDIF(${HDF5CORE} MATCHES NOTFOUND)

  # Any execs built off of HFD5 will need both libraries so they will both
  # be stored in a single variable
  SET(HDF5 ${HDF5CPP} ${HDF5CORE})
  
  # Set the include paths for HDF5
  INCLUDE_DIRECTORIES(${HDF5_INCLUDE_DIRS})
  
  # Set the link paths for HDF5
  LINK_DIRECTORIES(${HDF5_LIBRARY_DIRS})

  # Echo the HDF5 details if a verbose configure was requested
  IF(CMAKE_VERBOSE_CONFIGURE)
    MESSAGE("Found HDF5! Here are the details: ")
    MESSAGE(" HDF5_PREFIX = ${HDF5_PREFIX}")
    MESSAGE(" HDF5_INCLUDE_DIRS = ${HDF5_INCLUDE_DIRS}")
    MESSAGE(" HDF5_LIBRARY_DIRS = ${HDF5_LIBRARY_DIRS}")
    MESSAGE(" HDF5_LIBRARY = ${HDF5}")
    MESSAGE("End of HDF5 details\n")
  ENDIF()

ENDMACRO(ENABLE_HDF5_SUPPORT)