##---------------------------------------------------------------------------##
## Initialize the FRENSIE Project
##---------------------------------------------------------------------------##
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

# Force shared libraries to be built
SET(BUILD_SHARED_LIBS ON)

# Add the CMAKE_BINARY_DIR to the include path to access config files
INCLUDE_DIRECTORIES(${CMAKE_BINARY_DIR})

##---------------------------------------------------------------------------##
## Command Line Options
##---------------------------------------------------------------------------##

OPTION(FRENSIE_ENABLE_DBC "Enable Design-by-Contract checks in FRENSIE" ON)
OPTION(FRENSIE_ENABLE_PROFILING "Enable profiling with FRENSIE" OFF)
OPTION(FRENSIE_ENABLE_COVERAGE "Enable coverage testing in FRENSIE" OFF)
OPTION(FRENSIE_ENABLE_OPENMP "Enable shared-memory parallelism in FRENSIE" ON)
OPTION(FRENSIE_ENABLE_MPI "Enable distributed-memory parallelism in FRENSIE" OFF)
OPTION(FRENSIE_ENABLE_PYTHON "Enable python interfaces in FRENSIE" OFF)
OPTION(FRENSIE_ENABLE_ROOT "Enable the Root geometry interfaces in FRENSIE" OFF)
OPTION(FRENSIE_ENABLE_DAGMC "Enable the DagMC geometry interfaces in FRENSIE" OFF)
OPTION(FRENSIE_ENABLE_DASHBOARD_CLIENT "Enable dashboard client support" OFF)
OPTION(FRENSIE_ENABLE_MANUAL "Enable the manual in FRENSIE" ON)

##---------------------------------------------------------------------------##
## Configure DBC Support
##---------------------------------------------------------------------------##
# Add Design-by-Contract support if requested
IF(FRENSIE_ENABLE_DBC)
  SET(HAVE_FRENSIE_DBC "1")
ELSE()
  SET(HAVE_FRENSIE_DBC "0")
ENDIF()

# Parse the DBC configure file so it can be used in the source files
CONFIGURE_FILE(${CMAKE_SOURCE_DIR}/cmake/dbc_config.hpp.in ${CMAKE_BINARY_DIR}/${PROJECT_NAME}_config.hpp)

##---------------------------------------------------------------------------##
## Configure Profiling Support
##---------------------------------------------------------------------------##
IF(FRENSIE_ENABLE_PROFILING)
  SET(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -pg")
  SET(CMAKE_Fortran_FLAGS_DEBUG "${CMAKE_Fortran_FLAGS_DEBUG} -pg")
  SET(CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS} -pg")
  
  IF(NOT ${CMAKE_BUILD_TYPE} STREQUAL "DEBUG")
    MESSAGE(WARNING "profiling can only be done in debug builds!")
  ENDIF()
ENDIF()

##---------------------------------------------------------------------------##
## Configure Coverage Support
##---------------------------------------------------------------------------##
IF(FRENSIE_ENABLE_COVERAGE)
  SET(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g -O0 -Wall -W -Wshadow -Wunused-variable -Wunused-parameter -Wunused-function -Wunused -Wno-system-headers -Wno-deprecated -Woverloaded-virtual -Wwrite-strings -fprofile-arcs -ftest-coverage")
  SET(CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS} -fprofile-arcs -ftest-coverage")

  IF(NOT ${CMAKE_BUILD_TYPE} STREQUAL "DEBUG")
    MESSAGE(WARNING "coverage testing can only be done in debug builds!")
  ENDIF()
ENDIF()

##---------------------------------------------------------------------------##
## Configure OpenMP Support
##---------------------------------------------------------------------------##
IF(FRENSIE_ENABLE_OPENMP)
  SET(HAVE_FRENSIE_OPENMP "1")
  ENABLE_OPENMP_SUPPORT()
ENDIF()

# Parse the OpenMP configure file so that it can be used in our source files
SET(CMAKEDEFINE \#cmakedefine)
CONFIGURE_FILE(${CMAKE_SOURCE_DIR}/cmake/openmp_config.hpp.in
  ${CMAKE_BINARY_DIR}/${PROJECT_NAME}_openmp_config.hpp.in)
CONFIGURE_FILE(${CMAKE_BINARY_DIR}/${PROJECT_NAME}_openmp_config.hpp.in
  ${CMAKE_BINARY_DIR}/${PROJECT_NAME}_openmp_config.hpp)

##---------------------------------------------------------------------------##
## Configure MPI Support
##---------------------------------------------------------------------------##
# If the MPI package is in a non-standard location, set the MPI_PREFIX variable
IF(FRENSIE_ENABLE_MPI)
  SET(HAVE_FRENSIE_MPI "1")
  ENABLE_MPI_SUPPORT()
ENDIF()

# Parse the MPI configure file so that it can be used in our source files
SET(CMAKEDEFINE \#cmakedefine)
CONFIGURE_FILE(${CMAKE_SOURCE_DIR}/cmake/mpi_config.hpp.in
  ${CMAKE_BINARY_DIR}/${PROJECT_NAME}_mpi_config.hpp.in)
CONFIGURE_FILE(${CMAKE_BINARY_DIR}/${PROJECT_NAME}_mpi_config.hpp.in
  ${CMAKE_BINARY_DIR}/${PROJECT_NAME}_mpi_config.hpp)

##---------------------------------------------------------------------------##
## Configure Python Support
##---------------------------------------------------------------------------##
# SWIG will be used to generate the Python interfaces. If SWIG is located
# in a non-standard location set the SWIG_PREFIX variable.
IF(FRENSIE_ENABLE_PYTHON)
  ENABLE_SWIG_SUPPORT()
ENDIF()

##---------------------------------------------------------------------------##
## Configure HDF5 Support
##---------------------------------------------------------------------------##
# If the HDF5 package is in a non-standard location, set the HDF5_PREFIX
# variable.
ENABLE_HDF5_SUPPORT()

##---------------------------------------------------------------------------##
## Configure MOAB Support
##---------------------------------------------------------------------------##
# If the MOAB package is in a non-standard location, set the MOAB_PREFIX
# variable. If FRENSIE_ENABLE_DAGMC is set to ON, the DagMC library will
# be found.
ENABLE_MOAB_SUPPORT()

##---------------------------------------------------------------------------##
## Configure Trilinos Support
##---------------------------------------------------------------------------##
# If the Trilinos package is in a non-standard location, set the 
# TRILINOS_PREFIX variable. If the Trilinos source directory is not located
# in the TRILINOS_PREFIX directory, the TRILINOS_SOURCE variable can also be
# set.
ENABLE_TRILINOS_SUPPORT()

##---------------------------------------------------------------------------##
## Configure Boost Support
##---------------------------------------------------------------------------##
# If the Boost package is in a non-standard location, set the BOOST_PREFIX
# variable. The boost subpackages that must be found can be passed to
# the ENABLE_BOOST_SUPPORT macro.
ENABLE_BOOST_SUPPORT(serialization)

##---------------------------------------------------------------------------##
## Configure Root Support
##---------------------------------------------------------------------------##
# If the Root package is in a non-standard location, set the ROOT_PREFIX
# variable.
IF(FRENSIE_ENABLE_ROOT)
  ENABLE_ROOT_SUPPORT()
ENDIF()

##---------------------------------------------------------------------------##
## Configure Dashboard Client Support
##---------------------------------------------------------------------------##
# The default build name is CMAKE_SYSTEM_NAME, which is often not very 
# descriptive. Set the BUILDNAME_PREFIX if a more descriptive name is 
# desired. It can be useful to use the following command:
# BUILDNAME_PREFIX="$(lsb_release -i -s)-$(lsb_release -r -s)"
IF(FRENSIE_ENABLE_DASHBOARD_CLIENT)
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
  CONFIGURE_FILE(${CMAKE_SOURCE_DIR}/cmake/CTestCustom.cmake.in
    ${CMAKE_BINARY_DIR}/CTestCustom.cmake)
ELSE()
  ENABLE_TESTING()
ENDIF()

##---------------------------------------------------------------------------##
## Add an Unistall Target
##---------------------------------------------------------------------------##
# run `make uninstall` to remove all installed files
ADD_UNINSTALL_TARGET()

##---------------------------------------------------------------------------##
## Set Up the Project Directory Hierarchy
ADD_SUBDIRECTORY(scripts)

ADD_SUBDIRECTORY(packages)

ADD_SUBDIRECTORY(tools)

ADD_SUBDIRECTORY(doc)

##---------------------------------------------------------------------------##
## Add additional testing targets for convenience
##---------------------------------------------------------------------------##
ADD_CUSTOM_TARGET(test-fast 
  COMMAND ctest -E Facemc
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR})
ADD_CUSTOM_TARGET(test-facemc
  COMMAND ctest -R Facemc
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR})
