# Configure the Trilinos options that will be required in this project. The
# following variables will be set:
# 1.) BLAS - stores the blas library name used to compile teuchos
# 2.) LAPACK - stores the lapack library name used to compile teuchos
# 3.) TEUCHOS_CORE - stores the teuchoscore library name
# 4.) TEUCHOS_NUMERICS - stores the teuchosnumercics library name
# 5.) TEUCHOS_COMM - stores the teuchoscomm library name
# 6.) TEUCHOS_PARAMETER_LIST - stores the teuchosparameter list library name
# 8.) PYTRILINOS - stores the pytrilinos library name
#                  (only if FRENSIE_ENABLE_PYTHON=ON)
# 7.) TEUCHOS_STD_UNIT_TEST_MAIN - the path to the main .cpp file that is
#                                  needed for all unit tests using the Teuchos
#                                  unit test harness
MACRO(ENABLE_TRILINOS_SUPPORT)

  # Add the user supplied Trilinos prefix to help find Trilinos
  IF(DEFINED TRILINOS_PREFIX)
    SET(CMAKE_PREFIX_PATH ${TRILINOS_PREFIX} ${CMAKE_PREFIX_PATH})
  ELSE()
    MESSAGE(FATAL_ERROR "The TRILINOS_PREFIX must currently be set.")
  ENDIF()

  # Find the Trilinos package available on this system
  FIND_PACKAGE(Trilinos 11.14.3 REQUIRED)

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

  # Find the PyTrilinos library if building PyFrensie package
  IF(FRENSIE_ENABLE_PYTHON)
    FIND_LIBRARY(PYTRILINOS pytrilinos ${TRILINOS_LIBRARY_DIRS})
    IF(${PYTRILINOS} MATCHES NOTFOUND)
      MESSAGE(FATAL_ERROR "The pytrilinos library could not be found")
    ENDIF()
  ENDIF()

  # Find the standard Teuchos Unit Test main file
  FIND_PATH(TEUCHOS_STD_UNIT_TEST_MAIN_PATH
    NAMES Teuchos_StandardUnitTestMain.cpp
    PATHS ${Trilinos_DIR}/../../../src/packages/teuchos/core/test/UnitTest/
      ${TRILINOS_PREFIX}/src/packages/teuchos/core/test/UnitTest/
      ${TRILINOS_SOURCE}/packages/teuchos/core/test/UnitTest/
      ${TRILINOS_SOURCE}/src/packages/teuchos/core/test/UnitTest )
  IF(${TEUCHOS_STD_UNIT_TEST_MAIN_PATH} MATCHES NOTFOUND)
    MESSAGE(FATAL_ERROR "The teuchos standard Unit Test Main could not be found!")
  ENDIF()

  # Set the absolute path to the Teuchos standard unit test main file
  SET(TEUCHOS_STD_UNIT_TEST_MAIN
    ${TEUCHOS_STD_UNIT_TEST_MAIN_PATH}/Teuchos_StandardUnitTestMain.cpp
    CACHE PATH "The standard unit test main file for building unit tests")

  # Set the path to the PyTrilinos package source directory
  FIND_PATH(PYTRILINOS_SRC_DIR_PATH
    NAMES Teuchos_Array.i
    PATHS ${Trilinos_DIR}/../../../src/packages/PyTrilinos/src/
    ${TRILINOS_PREFIX}/src/packages/PyTrilinos/src/
    ${TRILINOS_SOURCE}/packages/PyTrilinos/src/
    ${TRILINOS_SOURCE}/src/packages/PyTrilinos/src)
  IF(${PYTRILINOS_SRC_DIR_PATH} MATCHES NOTFOUND)
    MESSAGE(FATAL_ERROR "The PyTrilinos/src directory could not be found!")
  ENDIF()

  # Set the path to the PyTrilinos cmake directory
  FIND_PATH(PYTRILINOS_CMAKE_DIR_PATH
    NAMES UseSWIG.cmake
    PATHS ${Trilinos_DIR}/../../../src/packages/PyTrilinos/cmake/
    ${TRILINOS_PREFIX}/src/packages/PyTrilinos/cmake/
    ${TRILINOS_SOURCE}/packages/PyTrilinos/cmake/
    ${TRILINOS_SOURCE}/src/packages/PyTrilinos/cmake)
  IF(${PYTRILINOS_CMAKE_DIR_PATH} MATCHES NOTFOUND)
    MESSAGE(FATAL_ERROR "The PyTrilinos/cmake directory could not be found!")
  ENDIF()

  # Set the path to the PyTrilinos util directory
  FIND_PATH(PYTRILINOS_UTIL_DIR_PATH
    NAMES copyWithCMakeSubstitutions.py.in
    PATHS ${Trilinos_DIR}/../../../src/packages/Pytrilinos/util/
    ${TRILINOS_PREFIX}/src/packages/PyTrilinos/util/
    ${TRILINOS_SOURCE}/packages/PyTrilinos/util/
    ${TRILINOS_SOURCE}/src/packages/PyTrilinos/util)
  IF(${PYTRILINOS_UTIL_DIR_PATH} MATCHES NOTFOUND)
    MESSAGE(FATAL_ERROR "The PyTrilinos/util directory could not be found!")
  ENDIF()

  # Set the include paths for Trilinos
  INCLUDE_DIRECTORIES(${Trilinos_INCLUDE_DIRS} ${Trilinos_TPL_INCLUDE_DIRS})

  # Set the link paths for Trilinos
  LINK_DIRECTORIES(${Trilinos_LIBRARY_DIRS} ${Trilinos_TPL_LIBRARY_DIRS})

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
    MESSAGE(" PYTRILINOS = ${PYTRILINOS}")
    MESSAGE("End of Teuchos details\n")
  ENDIF()

ENDMACRO(ENABLE_TRILINOS_SUPPORT)

