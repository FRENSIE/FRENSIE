# Configure the Trilinos options that will be required in this project. The
# following variables will be set:
# 1.) BLAS - stores the blas library name used to compile teuchos
# 2.) LAPACK - stores the lapack library name used to compile teuchos
# 3.) TEUCHOS_CORE - stores the teuchoscore library name
# 4.) TEUCHOS_NUMERICS - stores the teuchosnumercics library name
# 5.) TEUCHOS_COMM - stores the teuchoscomm library name
# 6.) TEUCHOS_PARAMETER_LIST - stores the teuchosparameter list library name
# 7.) TEUCHOS_STD_UNIT_TEST_MAIN - the path to the main .cpp file that is 
#                                  needed for all unit tests using the Teuchos
#                                  unit test harness
MACRO(ENABLE_TRILINOS_SUPPORT)
  
  # Add the user supplied Trilinos prefix to help find Trilinos
  SET(CMAKE_PREFIX_PATH ${TRILINOS_PREFIX} ${CMAKE_PREFIX_PATH})

  # Find the Trilinos package available on this system
  FIND_PACKAGE(Trilinos 11.4.1 REQUIRED)

  # Check if C compiler compatibility needs to be checked
  STRING(COMPARE NOTEQUAL 
    "${CACHED_TRILINOS_C_COMPILER}" "${Trilinos_C_COMPILER}" NEW_COMPILER)
  IF(NEW_COMPILER)
    # Verify that the same compiler used to compile trilinos has been requested
    MESSAGE("-- Checking C compiler and Trilinos C compiler compatibility")
    COMPARE_COMPILERS(C ${CMAKE_C_COMPILER} ${Trilinos_C_COMPILER})
    IF(SAME_VENDOR AND SAME_VERSION)
      MESSAGE("-- Checking C compiler and Trilinos C compiler compatibility - done")
    ELSEIF(NOT SAME_VENDOR)
      MESSAGE(FATAL_ERROR "Trilinos was compiled with ${Trilinos_C_COMPILER}, which is incompatible with ${CMAKE_C_COMPILER}")
    ELSEIF(SAME_VENDOR AND NOT SAME_VERSION)
      MESSAGE(WARNING "Trilinos was compiled with a different version of ${CMAKE_C_COMPILER}. There may be conflicts!")
    ENDIF()
    
    # Cache the Trilinos C compiler
    SET(CACHED_TRILINOS_C_COMPILER ${Trilinos_C_COMPILER}
      CACHE STRING "The Trilinos C compiler" FORCE)
  ENDIF()

  # Use the trilinos C compiler
  SET(CMAKE_C_COMPILER ${Trilinos_C_COMPILER})
  IF(NEW_COMPILER)
    MESSAGE("-- Switching to Trilinos C Compiler: ${Trilinos_C_COMPILER}")
  ENDIF()
  
  # Check if CXX compiler compatibility needs to be checked
  STRING(COMPARE NOTEQUAL 
    "${CACHED_TRILINOS_CXX_COMPILER}" "${Trilinos_CXX_COMPILER}" NEW_COMPILER)
  IF(NEW_COMPILER)
    MESSAGE("-- Checking CXX compiler and Trilinos CXX compiler compatibility")
    COMPARE_COMPILERS(CXX ${CMAKE_CXX_COMPILER} ${Trilinos_CXX_COMPILER})
    IF(SAME_VENDOR AND SAME_VERSION)
      MESSAGE("-- Checking CXX compiler and Trilinos CXX compiler compatibility - done")
    ELSEIF(NOT SAME_VENDOR)
      MESSAGE(FATAL_ERROR "Trilinos was compiled with ${Trilinos_CXX_COMPILER}, which is incompatible with ${CMAKE_CXX_COMPILER}")
    ELSEIF(SAME_VENDOR AND NOT SAME_VERSION)
      MESSAGE(WARNING "Trilinos was compiled with a different version of ${CMAKE_CXX_COMPILER}. There may be conflicts!")
    ENDIF()
    
    # Cache the Trilinos CXX compiler
    SET(CACHED_TRILINOS_CXX_COMPILER ${Trilinos_CXX_COMPILER}
      CACHE STRING "The Trilinos CXX compiler" FORCE)
  ENDIF()

  # Use the trilinos CXX compiler
  SET(CMAKE_CXX_COMPILER ${Trilinos_CXX_COMPILER})
  IF(NEW_COMPILER)
    MESSAGE("-- Switching to Trilinos CXX Compiler: ${Trilinos_CXX_COMPILER}")
  ENDIF()
  
  # Check if Fortran compiler compatibility needs to be checked
  STRING(COMPARE NOTEQUAL 
    "${CACHED_TRILINOS_Fortran_COMPILER}" "${Trilinos_Fortran_COMPILER}" 
    NEW_COMPILER)
  IF(NEW_COMPILER)
    MESSAGE("-- Checking Fortran compiler and Trilinos Fortran compiler compatibility")
    COMPARE_COMPILERS(Fortran ${CMAKE_Fortran_COMPILER} ${Trilinos_Fortran_COMPILER})
    IF(SAME_VENDOR AND SAME_VERSION)
      MESSAGE("-- Checking Fortran compiler and Trilinos Fortran compiler compatibility - done")
    ELSEIF(NOT SAME_VENDOR)
      MESSAGE(FATAL_ERROR "Trilinos was compiled with ${Trilinos_Fortran_COMPILER}, which is incompatible with ${CMAKE_Fortran_COMPILER}")
    ELSEIF(SAME_VENDOR AND NOT SAME_VERSION)
      MESSAGE(WARNING "Trilinos was compiled with a different version of ${CMAKE_Fortran_COMPILER}. There may be conflicts!")
    ENDIF()
  
    # Cache the Trilinos Fortran compiler
    SET(CACHED_TRILINOS_Fortran_COMPILER ${Trilinos_Fortran_COMPILER}
      CACHE STRING "The Trilinos Fortran compiler" FORCE)
  ENDIF()

  # Use the trilinos Fortran compiler
  SET(CMAKE_Fortran_COMPILER ${Trilinos_Fortran_COMPILER})

  IF(NEW_COMPILER)
    MESSAGE("-- Switching to Trilinos Fortran Compiler: ${Trilinos_Fortran_COMPILER}")
  ENDIF()
  
  UNSET(NEW_COMPILER)
  UNSET(SAME_VENDOR)
  UNSET(SAME_VERSION)
    
  # Find the teuchos core library
  FIND_LIBRARY(TEUCHOS_CORE teuchoscore ${TRILINOS_LIBRARY_DIRS})
  IF(${TEUCHOS_CORE} MATCHES NOTFOUND)
    MESSAGE(FATAL_ERROR "The teuchoscore library could not be found")
  ENDIF(${TEUCHOS_CORE} MATCHES NOTFOUND)
  
  # Find the teuchos numerics library
  FIND_LIBRARY(TEUCHOS_NUMERICS teuchosnumerics ${TRILINOS_LIBRARY_DIRS})
  IF(${TEUCHOS_NUMERICS} MATCHES NOTFOUND)
    MESSAGE(FATAL_ERROR "The teuchosnumerics library could not be found")
  ENDIF(${TEUCHOS_NUMERICS} MATCHES NOTFOUND)
  
  # Find the teuchos comm library
  FIND_LIBRARY(TEUCHOS_COMM teuchoscomm ${TRILINOS_LIBRARY_DIRS})
  IF(${TEUCHOS_COMM} MATCHES NOTFOUND)
    MESSAGE(FATAL_ERROR "The teuchoscomm library could not be found")
  ENDIF(${TEUCHOS_COMM} MATCHES NOTFOUND)
  
  # Find the teuchos parameter list library
  FIND_LIBRARY(TEUCHOS_PARAMETER_LIST teuchosparameterlist ${TRILINOS_LIBRARY_DIRS})
  IF(${TEUCHOS_PARAMETER_LIST} MATCHES NOTFOUND)
    MESSAGE(FATAL_ERROR "The teuchosparameterlist library could not be found")
  ENDIF(${TEUCHOS_PARAMETER_LIST} MATCHES NOTFOUND)

  # Find the standard Teuchos Unit Test main file
  FIND_PATH(TEUCHOS_STD_UNIT_TEST_MAIN_PATH
    NAMES Teuchos_StandardUnitTestMain.cpp
    PATHS ${Trilinos_DIR}/../../../src/packages/teuchos/core/test/UnitTest/
      ${TRILINOS_SOURCE}/packages/teuchos/core/test/UnitTest/
      ${TRILINOS_SOURCE}/src/packages/teuchos/core/test/UnitTest )
  IF(${TEUCHOS_STD_UNIT_TEST_MAIN_PATH} MATCHES NOTFOUND)
    MESSAGE(FATAL_ERROR "The teuchos standard Unit Test Main could not be found!")
  ENDIF()
  
  # Set the absolute path to the Teuchos standard unit test main file
  SET(TEUCHOS_STD_UNIT_TEST_MAIN
    ${TEUCHOS_STD_UNIT_TEST_MAIN_PATH}/Teuchos_StandardUnitTestMain.cpp
    CACHE PATH "The standard unit test main file for building unit tests")
    

  # Set the include paths for Trilinos
  INCLUDE_DIRECTORIES(${Trilinos_INCLUDE_DIRS} ${Trilinos_TPL_INCLUDE_DIRS})

  # Set the link paths for Trilinos
  LINK_DIRECTORIES(${Trilinos_LIBRARY_DIRS} ${Trilinos_TPL_LIBRARY_DIRS})

  # Apply the Teuchos::TwoDArray patch 
  IF((NOT DEFINED TEUCHOS_TWO_D_ARRAY_PATCHED) OR (NOT ${TEUCHOS_TWO_D_ARRAY_PATCHED}))
    FIND_FILE(TEUCHOS_TWO_D_ARRAY_HPP
      NAMES "Teuchos_TwoDArray.hpp"
      PATHS ${Trilinos_INCLUDE_DIRS})
    IF(${TEUCHOS_TWO_D_ARRAY_HPP} MATCHES NOTFOUND)
      MESSAGE(FATAL_ERROR "The Teuchos::TwoDArray.hpp file could not be found!")
    ENDIF()
        
    IF(NOT DEFINED TEUCHOS_TWO_D_ARRAY_PATCH)
      MESSAGE(FATAL_ERROR "The Teuchos::TwoDArray.hpp patch needs to be defined!" )
    ENDIF()

    IF(NOT DEFINED PATCH_EXEC)
      MESSAGE(FATAL_ERROR "The patch executable needs to be defined!")
    ENDIF()
    
    EXECUTE_PROCESS(COMMAND ${PATCH_EXEC} -s -N -r ${CMAKE_BINARY_DIR}/Teuchos_TwoDArray.hpp.rej ${TEUCHOS_TWO_D_ARRAY_HPP} 
      ${TEUCHOS_TWO_D_ARRAY_PATCH}
      OUTPUT_VARIABLE TEUCHOS_TWO_D_ARRAY_PATCH_OUTPUT
      ERROR_VARIABLE TEUCHOS_TWO_D_ARRAY_PATCH_ERROR
      RESULT_VARIABLE TEUCHOS_TWO_D_ARRAY_PATCH_RESULT)

    IF(TEUCHOS_TWO_D_ARRAY_PATCH_OUTPUT MATCHES "FAILED")
      MESSAGE(FATAL_ERROR "The Teuchos::TwoDArray.hpp file could not be patched: ${TEUCHOS_TWO_D_ARRAY_PATCH_OUTPUT}")
    ELSEIF(TEUCHOS_TWO_D_ARRAY_PATCH_OUTPUT MATCHES "refusing")
      MESSAGE(FATAL_ERROR "The Teuchos::TwoDArray.hpp file could not be patched: ${TEUCHOS_TWO_D_ARRAY_PATCH_OUTPUT}")
    ELSE()
      SET(TEUCHOS_TWO_D_ARRAY_PATCHED "ON"
	CACHE BOOL "Flag that indicates if the patch was successful." FORCE)
      MESSAGE("-- Teuchos_TwoDArray.hpp has been patched!")
    ENDIF()
  ENDIF()

  # Echo Trilinos build info if a verbose configure is requested
  IF(CMAKE_VERBOSE_CONFIGURE)
    MESSAGE("\nFound Trilinos!  Here are the details: ")
    MESSAGE("   Trilinos_DIR = ${Trilinos_DIR}")
    MESSAGE("   Trilinos_VERSION = ${Trilinos_VERSION}")
    MESSAGE("   Trilinos_PACKAGE_LIST = ${Trilinos_PACKAGE_LIST}")
    MESSAGE("   Trilinos_LIBRARIES = ${Trilinos_LIBRARIES}")
    MESSAGE("   Trilinos_INCLUDE_DIRS = ${Trilinos_INCLUDE_DIRS}")
    MESSAGE("   Trilinos_LIBRARY_DIRS = ${Trilinos_LIBRARY_DIRS}")
    MESSAGE("   Trilinos_TPL_LIST = ${Trilinos_TPL_LIST}")
    MESSAGE("   Trilinos_TPL_INCLUDE_DIRS = ${Trilinos_TPL_INCLUDE_DIRS}")
    MESSAGE("   Trilinos_TPL_LIBRARIES = ${Trilinos_TPL_LIBRARIES}")
    MESSAGE("   Trilinos_TPL_LIBRARY_DIRS = ${Trilinos_TPL_LIBRARY_DIRS}")
    MESSAGE("   Trilinos_BUILD_SHARED_LIBS = ${Trilinos_BUILD_SHARED_LIBS}")
    MESSAGE("   Trilinos_CXX_COMPILER_FLAGS = ${Trilinos_CXX_COMPILER_FLAGS}")
    MESSAGE("   Trilinos_C_COMPILER_FLAGS = ${Trilinos_C_COMPILER_FLAGS}")
    MESSAGE("   Trilinos_Fortran_COMPILER_FLAGS = ${Trilinos_Fortran_COMPILER_FLAGS}")
    MESSAGE("End of Trilinos details\n")
  ENDIF()
  
  # Echo the teuchos library info if a verbose configure is requested
  IF(CMAKE_VERBOSE_CONFIGURE)
    MESSAGE("Found the following Teuchos libraries: ")
    MESSAGE(" TEUCHOS_CORE_LIBRARY = ${TEUCHOS_CORE}")
    MESSAGE(" TEUCHOS_NUMERICS_LIBRARY = ${TEUCHOS_NUMERICS}")
    MESSAGE(" TEUCHOS_COMM_LIBRARY = ${TEUCHOS_COMM}")
    MESSAGE(" TEUCHOS_PARAMETER_LIST_LIBRARY = ${TEUCHOS_PARAMETER_LIST}")
    MESSAGE("End of Teuchos details\n")
  ENDIF()

ENDMACRO(ENABLE_TRILINOS_SUPPORT)

