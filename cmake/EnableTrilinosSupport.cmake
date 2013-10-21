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

  # Use the same compilers and flags as Trilinos
  SET(CMAKE_CXX_COMPILER ${Trilinos_CXX_COMPILER} )
  SET(CMAKE_C_COMPILER ${Trilinos_C_COMPILER} )
  SET(CMAKE_Fortran_COMPILER ${Trilinos_Fortran_COMPILER} )
  SET(CMAKE_CXX_FLAGS  "${Trilinos_CXX_COMPILER_FLAGS} ${CMAKE_CXX_FLAGS}")
  SET(CMAKE_C_FLAGS  "${Trilinos_C_COMPILER_FLAGS} ${CMAKE_C_FLAGS}")
  SET(CMAKE_Fortran_FLAGS  "${Trilinos_Fortran_COMPILER_FLAGS} ${CMAKE_Fortran_FLAGS}")
  
  # Find the BLAS and LAPACK libraries that were used
  FOREACH(I ${Trilinos_TPL_LIBRARIES})
    STRING(REGEX MATCH [libapck.][libapck.][libapck.][libapck.][libapck.][libapck.][libapck.][libapck.][libapck.][libapck.][libapck.] FOUND_LAPACK_STRING ${I})
    STRING(REGEX MATCH [libas.][libas.][libas.][libas.][libas.][libas.][libas.][libas.][libas.] FOUND_BLAS_STRING ${I})
    IF(FOUND_LAPACK_STRING)
      SET(BLAS ${I})
    ELSEIF(FOUND_BLAS_STRING)
      SET(LAPACK ${I})
    ENDIF()
    UNSET(FOUND_LAPACK_STRING)
    UNSET(FOUND_BLAS_STRING)
  ENDFOREACH(I)
  
  IF(NOT BLAS)
    MESSAGE(FATAL_ERROR "Could not find the BLAS library used by Trilinos.")
  ENDIF()

  
  IF(NOT LAPACK)
    MESSAGE(FATAL_ERROR "Could not find the LAPACK library used by Trilinos.")
  ENDIF()

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
    PATHS ${Trilinos_DIR}/../../../src/packages/teuchos/core/test/UnitTest/)
  IF(${TEUCHOS_STD_UNIT_TEST_MAIN_PATH} MATCHES NOTFOUND)
    MESSAGE(FATAL_ERROR "The teuchos standard Unit Test Main could not be found")
  ENDIF(${TEUCHOS_STD_UNIT_TEST_MAIN_PATH} MATCHES NOTFOUND)
  
  # Set the absolute path to the Teuchos standard unit test main file
  SET(TEUCHOS_STD_UNIT_TEST_MAIN 
    ${TEUCHOS_STD_UNIT_TEST_MAIN_PATH}/Teuchos_StandardUnitTestMain.cpp)

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

  # Echo Blas info if a verbose configure is requested
  IF(BLAS)
    IF(CMAKE_VERBOSE_CONFIGURE)
      MESSAGE("Found BLAS library used by Trilinos! Here are the details: ")
      MESSAGE(" BLAS_LIBRARY = ${BLAS}")
      MESSAGE("End of BLAS details\n")
    ENDIF()
  ENDIF()

  # Echo Lapack info if a verbose configure is requested
  IF(LAPACK)
    IF(CMAKE_VERBOSE_CONFIGURE)
      MESSAGE("Found LAPACK library used by Trilinos! Here are the details: ")
      MESSAGE(" LAPACK_LIBRARY = ${LAPACK}")
      MESSAGE("End of LAPACK details\n")
    ENDIF()
  ENDIF()

ENDMACRO(ENABLE_TRILINOS_SUPPORT)

