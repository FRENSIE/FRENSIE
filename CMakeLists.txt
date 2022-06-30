##---------------------------------------------------------------------------##
## Initialize the FRENSIE Project
##---------------------------------------------------------------------------##

# Define the minimum required version of CMake
CMAKE_MINIMUM_REQUIRED(VERSION 3.10.1 FATAL_ERROR)

# Define the project
SET(PROJECT_NAME FRENSIE)
PROJECT(${PROJECT_NAME} C CXX Fortran)

# Add the custom modules to the module path
SET(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH}
  ${PROJECT_SOURCE_DIR}/cmake)

# Define the project name
#INCLUDE(ProjectName)

# Define the project version
INCLUDE(Version)

# Include cmake macros (ones that aren't automatically available)
INCLUDE(${CMAKE_ROOT}/Modules/CMakeDependentOption.cmake)

# Include the macros that have been defined for this project
INCLUDE(Macros)

# Capture the command line and add to cache
CAPTURE_COMMAND_LINE()

# Enforce an out-of-source build
ENFORCE_OUT_OF_SOURCE_BUILD()

# Enable C++11 standard support
ENABLE_CXX_STANDARD_SUPPORT( 14 )

# Force shared libraries to be built
SET(BUILD_SHARED_LIBS ON)

# Set the install rpath to the lib install path - this should prevent the
# installed targets from reporting undefined .so files (check with ldd tool)
SET(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib")

# Set the PyFrensie Install directory
SET(PyFrensie_INSTALL_DIR "${CMAKE_INSTALL_PREFIX}/lib/python2.7/site-packages/PyFrensie")

##---------------------------------------------------------------------------##
## Command Line Options
##---------------------------------------------------------------------------##
OPTION(FRENSIE_ENABLE_DBC "Enable Design-by-Contract checks in FRENSIE" ON)
OPTION(FRENSIE_ENABLE_DETAILED_LOGGING "Enable detailed logging in FRENSIE" OFF)
OPTION(FRENSIE_ENABLE_EXPLICIT_TEMPLATE_INST "Enable explicit template instantiation to speed up build times and reduce build memory overhead" ON)
OPTION(FRENSIE_ENABLE_COLOR_OUTPUT "Enable color output from FRENSIE" ON)
OPTION(FRENSIE_ENABLE_PROFILING "Enable profiling with FRENSIE" OFF)
OPTION(FRENSIE_ENABLE_COVERAGE "Enable coverage testing in FRENSIE" OFF)
OPTION(FRENSIE_ENABLE_OPENMP "Enable shared-memory parallelism in FRENSIE" ON)
OPTION(FRENSIE_ENABLE_MPI "Enable distributed-memory parallelism in FRENSIE" OFF)
OPTION(FRENSIE_ENABLE_ROOT "Enable the Root geometry interfaces in FRENSIE" OFF)
OPTION(FRENSIE_ENABLE_HDF5 "Enable the HDF5 file interfaces in FRENSIE" OFF)
OPTION(FRENSIE_ENABLE_MOAB "Enable the Moab mesh interfaces in FRENSIE" OFF)
CMAKE_DEPENDENT_OPTION(FRENSIE_ENABLE_DAGMC "Enable the DagMC geometry interfaces in FRENSIE (MOAB required)" OFF
  "FRENSIE_ENABLE_MOAB" OFF)
OPTION(FRENSIE_ENABLE_DASHBOARD_CLIENT "Enable dashboard client support" OFF)
OPTION(FRENSIE_ENABLE_MANUAL "Enable the manual in FRENSIE" ON)

##---------------------------------------------------------------------------##
## Setup FRENSIE Configuration
##---------------------------------------------------------------------------##
# Add Design-by-Contract support if requested
IF(FRENSIE_ENABLE_DBC)
  SET(HAVE_FRENSIE_DBC "1")
ELSE()
  SET(HAVE_FRENSIE_DBC "0")
ENDIF()

# Add detailed logging support if requested
IF(FRENSIE_ENABLE_DETAILED_LOGGING)
  SET(HAVE_FRENSIE_DETAILED_LOGGING "1")
ELSE()
  SET(HAVE_FRENSIE_DETAILED_LOGGING "0")
ENDIF()

# Add explicit template instantiation support if requested
IF(FRENSIE_ENABLE_EXPLICIT_TEMPLATE_INST)
  SET(HAVE_FRENSIE_ENABLE_EXPLICIT_TEMPLATE_INSTANTIATION "1")
ELSE()
  SET(HAVE_FRENSIE_ENABLE_EXPLICIT_TEMPLATE_INSTANTIATION "0")
ENDIF()

# Add MPI support if requested
# If the MPI package is in a non-standard location, set the MPI_PREFIX variable
IF(FRENSIE_ENABLE_MPI)
  SET(HAVE_FRENSIE_MPI "1")
  ENABLE_MPI_SUPPORT()
ENDIF()

# Add openmp support if requested
IF(FRENSIE_ENABLE_OPENMP)
  SET(HAVE_FRENSIE_OPENMP "1")
  ENABLE_OPENMP_SUPPORT()
ENDIF()

SET(CMAKEDEFINE \#cmakedefine)

##---------------------------------------------------------------------------##
## Enable Color Output Support
##---------------------------------------------------------------------------##
# Check if the required header files are present on the system
# Note: Color output is only supported in tty terminals
IF(FRENSIE_ENABLE_COLOR_OUTPUT)
  INCLUDE(CheckIncludeFiles)
  CHECK_INCLUDE_FILES("unistd.h" IS_TTY_FORMATTING_SUPPORTED)

  IF(IS_TTY_FORMATTING_SUPPORTED)
    SET(TTY_FORMATTING_SUPPORTED "1")
  ENDIF()
ENDIF()

SET(CMAKEDEFINE \#cmakedefine)
CONFIGURE_FILE(${CMAKE_SOURCE_DIR}/cmake/tty_format_config.hpp.in
  ${CMAKE_BINARY_DIR}/${PROJECT_NAME}_tty_format_config.hpp.in)
CONFIGURE_FILE(${CMAKE_BINARY_DIR}/${PROJECT_NAME}_tty_format_config.hpp.in
  ${CMAKE_BINARY_DIR}/${PROJECT_NAME}_tty_format_config.hpp)

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
## Configure Python Support
##---------------------------------------------------------------------------##
# SWIG will be used to generate the Python interfaces. If SWIG is located
# in a non-standard location set the SWIG_PREFIX variable.
ENABLE_SWIG_SUPPORT()

##---------------------------------------------------------------------------##
## Configure HDF5 Support
##---------------------------------------------------------------------------##
# If the HDF5 package is in a non-standard location, set the HDF5_PREFIX
# variable.
IF(FRENSIE_ENABLE_HDF5)
  SET(HAVE_FRENSIE_HDF5 "1")
  ENABLE_HDF5_SUPPORT()
ENDIF()

##---------------------------------------------------------------------------##
## Configure Boost Support
##---------------------------------------------------------------------------##
# If the Boost package is in a non-standard location, set the BOOST_PREFIX
# variable. The boost subpackages that must be found can be passed to
# the ENABLE_BOOST_SUPPORT macro.
ENABLE_BOOST_SUPPORT()

##---------------------------------------------------------------------------##
## Configure MOAB Support
##---------------------------------------------------------------------------##
# If the MOAB package is in a non-standard location, set the MOAB_PREFIX
# variable. 
IF(FRENSIE_ENABLE_MOAB)
  SET(HAVE_FRENSIE_MOAB "1")
  ENABLE_MOAB_SUPPORT()
ENDIF()

##---------------------------------------------------------------------------##
## Configure DagMC Support
##---------------------------------------------------------------------------##
# If the DagMC package is in a non-standard location, set the DAGMC_PREFIX
# variable.
IF(FRENSIE_ENABLE_DAGMC)
  SET(HAVE_FRENSIE_DAGMC "1")
  ENABLE_DAGMC_SUPPORT()
ENDIF()

##---------------------------------------------------------------------------##
## Configure Root Support
##---------------------------------------------------------------------------##
# If the Root package is in a non-standard location, set the ROOT_PREFIX
# variable.
IF(FRENSIE_ENABLE_ROOT)
  SET(HAVE_FRENSIE_ROOT "1")
  ENABLE_ROOT_SUPPORT()
ENDIF()

##---------------------------------------------------------------------------##
## Parse the FRENSIE config file
##---------------------------------------------------------------------------##

CONFIGURE_FILE(${CMAKE_SOURCE_DIR}/cmake/config.hpp.in ${CMAKE_BINARY_DIR}/${PROJECT_NAME}_config.hpp.in)
CONFIGURE_FILE(${CMAKE_BINARY_DIR}/${PROJECT_NAME}_config.hpp.in ${CMAKE_BINARY_DIR}/${PROJECT_NAME}_config.hpp)

# Add the CMAKE_BINARY_DIR to the include path to access config file
INCLUDE_DIRECTORIES(${CMAKE_BINARY_DIR})

# Add the config file to the install target
INSTALL(FILES ${CMAKE_BINARY_DIR}/${PROJECT_NAME}_config.hpp
  DESTINATION ${CMAKE_INSTALL_PREFIX}/include
  PERMISSIONS OWNER_READ GROUP_READ WORLD_READ)

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
##---------------------------------------------------------------------------##

#ADD_SUBDIRECTORY(scripts)

ADD_SUBDIRECTORY(packages)

ADD_SUBDIRECTORY(tools)

ADD_SUBDIRECTORY(doc)

ADD_SUBDIRECTORY(examples)
