# Configure the Moab options that will be required in this project. The
# following variables will be set:
# 1.) MOAB - stores the Moab library name
MACRO(ENABLE_MOAB_SUPPORT)

  # Add the user supplied Moab prefix to help find Moab
  IF(DEFINED MOAB_PREFIX)
    SET(CMAKE_PREFIX_PATH ${MOAB_PREFIX}/lib ${MOAB_PREFIX}/lib/cmake/MOAB/ ${CMAKE_PREFIX_PATH})
  ELSE()
    MESSAGE(FATAL_ERROR "The MOAB_PREFIX must be set currently.")
  ENDIF()

  # Find the Moab package available on this system (version checking is
  # not currently supported)
  FIND_PACKAGE(MOAB REQUIRED)

  # Make sure that the MOABConfig.cmake was found and that the required
  # variables were set
  SET(MOAB_ERROR_MESSAGE "was not set. There may be a problem with the MOABConfig.cmake file generated during the MOAB build.")
  
  IF(NOT DEFINED MOAB_INCLUDE_DIRS)
    MESSAGE(FATAL_ERROR "MOAB_INCLUDE_DIRS ${MOAB_ERROR_MESSAGE}")
  ENDIF()

  IF(NOT DEFINED MOAB_LIBRARY_DIRS)
    MESSAGE(FATAL_ERROR "MOAB_LIBRARY_DIRS ${MOAB_ERROR_MESSAGE}")
  ENDIF()

  IF(NOT DEFINED MOAB_USE_EIGEN)
    MESSAGE(FATAL_ERROR "MOAB_USE_EIGEN ${MOAB_ERROR_MESSAGE}")
  ENDIF()

  # Make sure that MOAB was configured with eigen
  IF(NOT ${MOAB_USE_EIGEN})
    MESSAGE(FATAL_ERROR "MOAB was not built with eigen3! Rebuild MOAB with eigen3 (and install eigen3 if necessare - e.g. 'sudo apt-get install libeigen3-dev')")
  ENDIF()

  # Find the MOAB library
  FIND_LIBRARY(MOAB MOAB ${MOAB_LIBRARY_DIRS})

  IF(${MOAB} MATCHES NOTFOUND)
    MESSAGE(FATAL_ERROR "The moab library could not be found.")
  ENDIF()

  # IF(FRENSIE_ENABLE_DAGMC)
  #   # Check if the Moab patch has been applied
  #   IF((NOT DEFINED MOAB_THREAD_SAFE_PATCHED) OR (NOT ${MOAB_THREAD_SAFE_PATCHED}))
  #     FIND_FILE(GEOM_QUERY_TOOL_CPP
  #     NAMES "GeomQueryTool.cpp"
  #     PATHS ${MOAB_PREFIX}/src/src ${MOAB_SOURCE}/src)
  #     IF(${GEOM_QUERY_TOOL_CPP} MATCHES NOTFOUND)
  #         MESSAGE(FATAL_ERROR "The GeomQueryTool.cpp file could not be found!")
  #     ENDIF()

  #     IF(NOT DEFINED MOAB_THREAD_SAFE_PATCH)
  #       MESSAGE(FATAL_ERROR "The GeomQueryTool.cpp patch file needs to be defined!")
  #     ENDIF()

  #     IF(NOT DEFINED PATCH_EXEC)
  #       MESSAGE(FATAL_ERROR "The patch executable needs to be defined!")
  #     ENDIF()

  #     EXECUTE_PROCESS(COMMAND ${PATCH_EXEC} -s -N -r ${CMAKE_BINARY_DIR}/GeomQueryTool.cpp.rej ${GEOM_QUERY_TOOL_CPP}
  #       ${MOAB_THREAD_SAFE_PATCH}
  #       OUTPUT_VARIABLE MOAB_THREAD_SAFE_PATCH_OUTPUT
  #       ERROR_VARIABLE MOAB_THREAD_SAFE_PATCH_ERROR
  #       RESULT_VARIABLE MOAB_THREAD_SAFE_PATCH_RESULT)

  #     IF(${MOAB_THREAD_SAFE_PATCH_OUTPUT} MATCHES "FAILED")
  #       MESSAGE(FATAL_ERROR "The GeomQueryTool.cpp file could not be patched: ${MOAB_THREAD_SAFE_PATCH_OUTPUT}")
  #     ELSEIF(${MOAB_THREAD_SAFE_PATCH_OUTPUT} MATCHES "refusing")
  #       MESSAGE(FATAL_ERROR "The GeomQueryTool.cpp file could not be patched: ${MOAB_THREAD_SAFE_PATCH_OUTPUT}")
  #     ELSEIF(MOAB_THREAD_SAFE_PATCH_RESULT EQUAL "0")
  #       MESSAGE(FATAL_ERROR "GeomQueryTool.cpp was successfully patched for the first time. Moab needs to be rebuilt before proceeding.")
  #     ELSE()
  #       SET(MOAB_THREAD_SAFE_PATCHED "ON"
  #         CACHE BOOL "Flag that indicates if the patch was successful." FORCE)
  #       MESSAGE("-- GeomQueryTool.cpp has been patched!")
  #     ENDIF()
  #   ENDIF()

  #   # Moab patch has been applied - now find DagMC library
  #   # Use the user supplied prefix to find the DagMC libraries and include dirs.
  #   SET(DAGMC_INCLUDE_DIRS ${DAGMC_PREFIX}/include)
  #   SET(DAGMC_LIBRARY_DIRS ${DAGMC_PREFIX}/lib)
  #   FIND_LIBRARY(DAGMC dagmc ${DAGMC_LIBRARY_DIRS})

  #   IF(${DAGMC} MATCHES NOTFOUND)
  #     MESSAGE(FATAL_ERROR "The dagmc library could not be found.")
  #   ENDIF()

  #   SET(MOAB ${DAGMC} ${MOAB})

  #   SET(HAVE_FRENSIE_DAGMC "1")
  # ENDIF()

  # Set the include paths for Moab and DagMC
  INCLUDE_DIRECTORIES(${MOAB_INCLUDE_DIRS})
  #INCLUDE_DIRECTORIES(${DAGMC_INCLUDE_DIRS})

  # Set the link paths for Moab and DagMC
  LINK_DIRECTORIES(${MOAB_LIBRARY_DIRS})
  #LINK_DIRECTORIES(${DAGMC_LIBRARY_DIRS})

  # Check if C compiler compatibility needs to be checked
  STRING(COMPARE NOTEQUAL "${MOAB_C_COMPILER}" "${MOAB_CC}" NEW_COMPILER)
  IF(NEW_COMPILER)
    # Verify that the same compiler used to compile moab has been requested
    MESSAGE("-- Checking C compiler and Moab C compiler compatibility")
    COMPARE_COMPILERS(C ${CMAKE_C_COMPILER} ${MOAB_CC})
    IF(SAME_VENDOR AND SAME_VERSION)
      MESSAGE("-- Checking C compiler and Moab C compiler compatibility - done")
    ELSEIF(NOT SAME_VENDOR)
      MESSAGE(FATAL_ERROR "Moab was compiled with ${MOAB_CC}, which is incompatible with ${CMAKE_C_COMPILER}")
    ELSEIF(SAME_VENDOR AND NOT SAME_VERSION)
      MESSAGE(WARNING "Moab was compiled with a different version of ${CMAKE_C_COMPILER}. There may be conflicts!")
    ENDIF()

    # Cache the MOAB C compiler
    SET(MOAB_C_COMPILER ${MOAB_CC}
      CACHE STRING "The MOAB C compiler" FORCE)
  ENDIF()

  # Check if the CXX compiler compatibility needs to be checked
  STRING(COMPARE NOTEQUAL "${MOAB_CXX_COMPILER}" "${MOAB_CXX}" NEW_COMPILER)
  IF(NEW_COMPILER)
    MESSAGE("-- Checking CXX compiler and Moab CXX compiler compatibility")
    COMPARE_COMPILERS(CXX ${CMAKE_CXX_COMPILER} ${MOAB_CXX})
    IF(SAME_VENDOR AND SAME_VERSION)
      MESSAGE("-- Checking CXX compiler and Moab CXX compiler compatibility - done")
    ELSEIF(NOT SAME_VENDOR)
      MESSAGE(FATAL_ERROR "Moab was compiled with ${MOAB_CXX}, which is incompatible with ${CMAKE_CXX_COMPILER}")
    ELSEIF(SAME_VENDOR AND NOT SAME_VERSION)
      MESSAGE(WARNING "Moab was compiled with a different version of ${CMAKE_CXX_COMPILER}. There may be conflicts!")
    ENDIF()

    # Cache the MOAB CXX compiler
    SET(MOAB_CXX_COMPILER ${MOAB_CXX}
      CACHE STRING "The MOAB CXX compiler" FORCE)
  ENDIF()

  # Check if the Fortran compiler compatibility needs to be checked
  STRING(COMPARE NOTEQUAL "${MOAB_Fortran_COMPILER}" "${MOAB_FC}" NEW_COMPILER)
  IF(NEW_COMPILER)
    MESSAGE("-- Checking Fortran compiler and Moab Fortran compiler compatibility")
    COMPARE_COMPILERS(Fortran ${CMAKE_Fortran_COMPILER} ${MOAB_FC})
    IF(SAME_VENDOR AND SAME_VERSION)
      MESSAGE("-- Checking Fortran compiler and Moab Fortran compiler compatibility - done")
    ELSEIF(NOT SAME_VENDOR)
      MESSAGE(FATAL_ERROR "Moab was compiled with ${MOAB_FC}, which is incompatible with ${CMAKE_Fortran_COMPILER}")
    ELSEIF(SAME_VENDOR AND NOT SAME_VERSION)
      MESSAGE(WARNING "Moab was compiled with a different version of ${CMAKE_Fortran_COMPILER}. There may be conflicts!")
    ENDIF()

    # Cache the MOAB Fortran compiler
    SET(MOAB_Fortran_COMPILER ${MOAB_FC}
      CACHE STRING "The MOAB Fortran compiler" FORCE)
  ENDIF()

  UNSET(SAME_VENDOR)
  UNSET(SAME_VERSION)

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
