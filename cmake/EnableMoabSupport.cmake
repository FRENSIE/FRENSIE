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

  # Verify that the same compiler used to compile moab has been requested
  MESSAGE("-- Comparing C compiler with Moab C compiler")
  COMPARE_COMPILERS(C ${CMAKE_C_COMPILER} ${MOAB_CC})
  IF(SAME_VENDOR AND SAME_VERSION)
    MESSAGE("-- Comparing C compiler with Moab C compiler - done")
  ELSEIF(NOT SAME_VENDOR)
    MESSAGE(FATAL_ERROR "Moab was compiled with ${MOAB_CC}, which is incompatible with ${CMAKE_C_COMPILER}")
  ELSEIF(SAME_VENDOR AND NOT SAME_VERSION)
    MESSAGE(WARNING "Moab was compiled with a different version of ${CMAKE_C_COMPILER}. There may be conflicts!")
  ENDIF()
  
  MESSAGE("-- Comparing CXX compiler with Moab CXX compiler")
  COMPARE_COMPILERS(CXX ${CMAKE_CXX_COMPILER} ${MOAB_CXX})
  IF(SAME_VENDOR AND SAME_VERSION)
    MESSAGE("-- Comparing CXX compiler with Moab CXX compiler - done")
  ELSEIF(NOT SAME_VENDOR)
    MESSAGE(FATAL_ERROR "Moab was compiled with ${MOAB_CXX}, which is incompatible with ${CMAKE_CXX_COMPILER}")
  ELSEIF(SAME_VENDOR AND NOT SAME_VERSION)
    MESSAGE(WARNING "Moab was compiled with a different version of ${CMAKE_CXX_COMPILER}. There may be conflicts!")
  ENDIF()

  MESSAGE("-- Comparing Fortran compiler with Moab Fortran compiler")
  COMPARE_COMPILERS(Fortran ${CMAKE_Fortran_COMPILER} ${MOAB_FC})
  IF(SAME_VENDOR AND SAME_VERSION)
  MESSAGE("-- Comparing Fortran compiler with Moab Fortran compiler - done")
  ELSEIF(NOT SAME_VENDOR)
    MESSAGE(FATAL_ERROR "Moab was compiled with ${MOAB_FC}, which is incompatible with ${CMAKE_Fortran_COMPILER}")
  ELSEIF(SAME_VENDOR AND NOT SAME_VERSION)
    MESSAGE(WARNING "Moab was compiled with a different version of ${CMAKE_Fortran_COMPILER}. There may be conflicts!")
  ENDIF()
  
  UNSET(SAME_VENDOR)
  UNSET(SAME_VERSION)

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