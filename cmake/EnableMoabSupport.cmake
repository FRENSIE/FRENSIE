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

  SET(MOAB ${MOAB} ${MOAB_LIBRARIES})

  IF(FRENSIE_ENABLE_DAGMC)
    # Check if the DagMC patch has been applied
    IF((NOT DEFINED DAGMC_THREAD_SAFE_PATCHED) OR (NOT ${DAGMC_THREAD_SAFE_PATCHED}))
      FIND_FILE(DAGMC_CPP
	NAMES "DagMC.cpp"
	PATHS ${MOAB_PREFIX}/src/tools/dagmc ${MOAB_SOURCE}/tools/dagmc)
      IF(${DAGMC_CPP} MATCHES NOTFOUND)
	MESSAGE(FATAL_ERROR "The DagMC.cpp file could not be found!")
      ENDIF()

      IF(NOT DEFINED DAGMC_THREAD_SAFE_PATCH)
	MESSAGE(FATAL_ERROR "The DagMC.cpp patch file needs to be defined!")
      ENDIF()

      IF(NOT DEFINED PATCH_EXEC)
	MESSAGE(FATAL_ERROR "The patch executable needs to be defined!")
      ENDIF()

      EXECUTE_PROCESS(COMMAND ${PATCH_EXEC} -s -N -r ${CMAKE_BINARY_DIR}/DagMC.cpp.rej ${DAGMC_CPP}
	${DAGMC_THREAD_SAFE_PATCH}
	OUTPUT_VARIABLE DAGMC_THREAD_SAFE_PATCH_OUTPUT
	ERROR_VARIABLE DAGMC_THREAD_SAFE_PATCH_ERROR
	RESULT_VARIABLE DAGMC_THREAD_SAFE_PATCH_RESULT)

      IF(${DAGMC_THREAD_SAFE_PATCH_OUTPUT} MATCHES "FAILED")
	MESSAGE(FATAL_ERROR "The DagMC.cpp file could not be patched: ${DAGMC_THREAD_SAFE_PATCH_OUTPUT}")
      ELSEIF(${DAGMC_THREAD_SAFE_PATCH_OUTPUT} MATCHES "refusing")
	MESSAGE(FATAL_ERROR "The DagMC.cpp file could not be patched: ${DAGMC_THREAD_SAFE_PATCH_OUTPUT}")
      ELSEIF(DAGMC_THREAD_SAFE_PATCH_RESULT EQUAL "0")
	MESSAGE(FATAL_ERROR "DagMC.cpp was successfully patched for the first time. Moab needs to be rebuilt before proceeding.")
      ELSE()
	SET(DAGMC_THREAD_SAFE_PATCHED "ON"
	  CACHE BOOL "Flag that indicates if the patch was successful." FORCE)
	MESSAGE("-- DagMC.cpp has been patched!")
      ENDIF()
    ENDIF()
    
    # DagMC patch has been applied - now find DagMC library
    FIND_LIBRARY(DAGMC dagmc ${MOAB_LIBRARY_DIRS})

    IF(${DAGMC} MATCHES NOTFOUND)
      MESSAGE(FATAL_ERROR "The dagmc library could not be found.")
    ENDIF()

    SET(MOAB ${DAGMC} ${MOAB})

    SET(HAVE_${PROJECT_NAME}_DAGMC "1")
  ENDIF()
  
  # Set the include paths for Moab
  INCLUDE_DIRECTORIES(${MOAB_INCLUDE_DIRS})

  # Set the link paths for Moab
  LINK_DIRECTORIES(${MOAB_LIBRARY_DIRS})

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