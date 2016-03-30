# Define the minimum required version of CMake
CMAKE_MINIMUM_REQUIRED(VERSION 3.0.1 FATAL_ERROR)

# Add the custom modules to the module path
SET(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH}
  "${CMAKE_DIR}/share/cmake-3.0/Modules"
  ${PROJECT_SOURCE_DIR}/cmake)

# Define the project name
INCLUDE(ProjectName)

# Define the project version
INCLUDE(Version)

# Include the macros that have been defined for this project
INCLUDE(Macros)

# Enforce an out-of-source build
ENFORCE_OUT_OF_SOURCE_BUILD()

# Enable C++11 standard support
ENABLE_CXX11_STANDARD_SUPPORT()

# Load the patch files
SET(TEUCHOS_TWO_D_ARRAY_PATCH 
  ${CMAKE_SOURCE_DIR}/patches/Teuchos_TwoDArray_patch
  CACHE STRING "The Teuchos::TwoDArray patch file" FORCE)

SET(DAGMC_THREAD_SAFE_PATCH
  ${CMAKE_SOURCE_DIR}/patches/DagMC_cpp_patch
  CACHE STRING "The DagMC.cpp patch file" FORCE)

# Find the patch exec
FIND_PROGRAM(PATCH_EXEC NAMES patch)
IF(${PATCH_EXEC} MATCHES NOTFOUND)
  MESSAGE(FATAL_ERROR "The patch program could not be found!")
ENDIF()

# Enable OpenMP support
IF(${${PROJECT_NAME}_ENABLE_OPENMP})
  SET(HAVE_${PROJECT_NAME}_OPENMP "1")
  ENABLE_OPENMP_SUPPORT()
ENDIF()

# Parse the OpenMP configure file so that it can be used in our source files
SET(CMAKEDEFINE \#cmakedefine)
CONFIGURE_FILE(${CMAKE_SOURCE_DIR}/cmake/openmp_config.hpp.in
  ${CMAKE_BINARY_DIR}/${PROJECT_NAME}_openmp_config.hpp.in)
CONFIGURE_FILE(${CMAKE_BINARY_DIR}/${PROJECT_NAME}_openmp_config.hpp.in
  ${CMAKE_BINARY_DIR}/${PROJECT_NAME}_openmp_config.hpp)

# Enable MPI support 
IF(${${PROJECT_NAME}_ENABLE_MPI})
  SET(HAVE_${PROJECT_NAME}_MPI "1")
  ENABLE_MPI_SUPPORT()
ENDIF()

# Parse the MPI configure file so that it can be used in our source files
SET(CMAKEDEFINE \#cmakedefine)
CONFIGURE_FILE(${CMAKE_SOURCE_DIR}/cmake/mpi_config.hpp.in
  ${CMAKE_BINARY_DIR}/${PROJECT_NAME}_mpi_config.hpp.in)
CONFIGURE_FILE(${CMAKE_BINARY_DIR}/${PROJECT_NAME}_mpi_config.hpp.in
  ${CMAKE_BINARY_DIR}/${PROJECT_NAME}_mpi_config.hpp)
    
# Enable Trilinos Support
IF(TRILINOS_PREFIX)
  ENABLE_TRILINOS_SUPPORT()
ELSE()
  MESSAGE(FATAL_ERROR "The TRILINOS_PREFIX must be set!")
ENDIF()

# Enable MOAB Support
IF(MOAB_PREFIX)
  ENABLE_MOAB_SUPPORT()
ELSE()
  MESSAGE(FATAL_ERROR "The MOAB_PREFIX must be set!")
ENDIF()

# Enable HDF5 Support
IF(HDF5_PREFIX)
  ENABLE_HDF5_SUPPORT()
ELSE()
  MESSAGE(FATAL_ERROR "The HDF5_PREFIX must be set!")
ENDIF()

# Enable BOOST Support
IF(BOOST_PREFIX)
  ENABLE_BOOST_SUPPORT(serialization)
ELSE()
  MESSAGE(STATUS "The BOOST_PREFIX has not been set. The system default will be used.")
ENDIF()

# Enable ROOT Support
IF(${FRENSIE_ENABLE_ROOT})
  IF(ROOT_PREFIX)
    ENABLE_ROOT_SUPPORT()
  ELSE()
    MESSAGE(FATAL_ERROR "The ROOT_PREFIX must be set!")
  ENDIF()
ENDIF()

# Add Design-by-Contract support if requested
IF(${${PROJECT_NAME}_ENABLE_DBC})
  SET(HAVE_${PROJECT_NAME}_DBC "1")
ELSE()
  SET(HAVE_${PROJECT_NAME}_DBC "0")
ENDIF()

# Enable profiling support if requested
IF(${${PROJECT_NAME}_ENABLE_PROFILING})
  SET(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -pg")
  SET(CMAKE_Fortran_FLAGS_DEBUG "${CMAKE_Fortran_FLAGS_DEBUG} -pg")
  SET(CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS} -pg")
  
  IF(NOT ${CMAKE_BUILD_TYPE} STREQUAL "DEBUG")
    MESSAGE(WARNING "profiling can only be done in debug builds!")
  ENDIF()
ENDIF()

# Enable coverage support if requested
IF(${${PROJECT_NAME}_ENABLE_COVERAGE})
  SET(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g -O0 -Wall -W -Wshadow -Wunused-variable -Wunused-parameter -Wunused-function -Wunused -Wno-system-headers -Wno-deprecated -Woverloaded-virtual -Wwrite-strings -fprofile-arcs -ftest-coverage")
  SET(CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS} -fprofile-arcs -ftest-coverage")

  IF(NOT ${CMAKE_BUILD_TYPE} STREQUAL "DEBUG")
    MESSAGE(WARNING "coverage testing can only be done in debug builds!")
  ENDIF()
ENDIF()

# Parse the DBC configure file so it can be used in the source files
CONFIGURE_FILE(${CMAKE_SOURCE_DIR}/cmake/dbc_config.hpp.in ${CMAKE_BINARY_DIR}/${PROJECT_NAME}_config.hpp)

# Parse the HDF5 data file names configure file
SET(${PROJECT_NAME}_DATA_DIRECTORY ${CMAKE_SOURCE_DIR}/data/)
CONFIGURE_FILE(${CMAKE_SOURCE_DIR}/cmake/HDF5DataFileNames.hpp.in ${CMAKE_BINARY_DIR}/HDF5DataFileNames.hpp)

# Parse the Fission Product Data Path configure file
CONFIGURE_FILE(${CMAKE_SOURCE_DIR}/cmake/FissionProductDataPath.hpp.in ${CMAKE_BINARY_DIR}/FissionProductDataPath.hpp)

# Parse the Decay Data Path configure file
CONFIGURE_FILE(${CMAKE_SOURCE_DIR}/cmake/DecayDataPath.hpp.in ${CMAKE_BINARY_DIR}/DecayDataPath.hpp)

# Add the CMAKE_BINARY_DIR to the include path to access config files
INCLUDE_DIRECTORIES(${CMAKE_BINARY_DIR})

# Add an uninstall target
ADD_UNINSTALL_TARGET()

# Set up the testing dashboard
IF(${SETUP_DASHBOARD_CLIENT})
  SET(DART_TESTING_TIMEOUT "43200" CACHE STRING "Amount of time (s) to wait for processes to complete during testing." FORCE)
  
  # Set the BuildName used by the dashboard (see DartConfiguration.tcl)
  DETERMINE_COMPILER_ID(CXX ${CMAKE_CXX_COMPILER})
  STRING(TOLOWER ${CMAKE_BUILD_TYPE} BUILD_TYPE)
  
  IF(NOT BUILDNAME_PREFIX)
    SET(BUILDNAME_PREFIX ${CMAKE_SYSTEM_NAME})
  ENDIF()
  
  SET(BUILDNAME "${BUILDNAME_PREFIX}_${ID}-${VERSION}_${BUILD_TYPE}")

  UNSET(ID)
  UNSET(VERSION)
  UNSET(BUILD_TYPE)

  # Set the valgrind supressions file
  SET(MEMORYCHECK_SUPPRESSIONS_FILE ${CMAKE_SOURCE_DIR}/valgrind/frensie-deps.supp CACHE STRING "File that contains suppressions for the memory checker" FORCE)
  
  # Initialize CTest
  INCLUDE(CTest)

  # Configure the CTestCustom.cake file for extended output for dashboard
  CONFIGURE_FILE(${CMAKE_SOURCE_DIR}/CTestCustom.cmake.in
    ${CMAKE_BINARY_DIR}/CTestCustom.cmake)
ELSE()
  ENABLE_TESTING()
ENDIF()

# Set up the project directory hierarchy
ADD_SUBDIRECTORY(scripts)

ADD_SUBDIRECTORY(packages)

ADD_SUBDIRECTORY(tools)

ADD_SUBDIRECTORY(doc)

# Add additional testing targets for convenience
ADD_CUSTOM_TARGET(test-fast 
  COMMAND ctest -E Facemc
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR})
ADD_CUSTOM_TARGET(test-facemc
  COMMAND ctest -R Facemc
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR})
