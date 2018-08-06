# Set the global test data file path
ADD_SUBDIRECTORY(test_files)

SET(GLOBAL_TEST_DATA_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/test_files)
SET(GLOBAL_TEST_DATA_BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR}/test_files)

SET(GLOBAL_TOOLS_TEST_DATA_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/test_files/tools)
SET(GLOBAL_ACE_TEST_DATA_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/test_files/ace)
SET(GLOBAL_ENDF_TEST_DATA_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/test_files/endf)
SET(GLOBAL_ENDL_TEST_DATA_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/test_files/endl)
SET(GLOBAL_NATIVE_TEST_DATA_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/test_files/native)
SET(GLOBAL_DAGMC_TEST_DATA_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/test_files/dagmc)
SET(GLOBAL_DAGMC_TEST_DATA_BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR}/test_files/dagmc)
SET(GLOBAL_ROOT_TEST_DATA_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/test_files/root)
SET(GLOBAL_ROOT_TEST_DATA_BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR}/test_files/root)

# Set up the packages directory hierarchy
ADD_SUBDIRECTORY(utility)
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_BINARY_DIR}/utility/core/src
utility/core/src utility/archive/src utility/archive/test utility/system/src utility/mpi/src utility/prng/src utility/interpolation/src utility/distribution/src utility/integrator/src utility/grid/src utility/mesh/src)

ADD_SUBDIRECTORY(geometry)
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_BINARY_DIR}/geometry geometry/core/src)

IF(FRENSIE_ENABLE_ROOT)
  INCLUDE_DIRECTORIES(geometry/root/src)
ENDIF()

IF(FRENSIE_ENABLE_DAGMC)
  INCLUDE_DIRECTORIES(geometry/dagmc/src)
ENDIF()

ADD_SUBDIRECTORY(data)
INCLUDE_DIRECTORIES(data/core/src data/ace/src data/endf/src data/endl/src data/native/src data/database/src)

# Create the database generator for the test data
ADD_EXECUTABLE(database_generator ${GLOBAL_TOOLS_TEST_DATA_SOURCE_DIR}/database_generator.cpp)
TARGET_LINK_LIBRARIES(database_generator data_database)

# Use this variable in the argument list of tests that require the test
# database (e.g. EXTRA_ARGS --test_database=${COLLISION_DATABASE_XML_FILE})
SET(COLLISION_DATABASE_XML_FILE ${CMAKE_CURRENT_BINARY_DIR}/database.xml)

ADD_CUSTOM_COMMAND(OUTPUT ${COLLISION_DATABASE_XML_FILE}
  DEPENDS database_generator
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
  COMMAND database_generator
  --ace_dir=${GLOBAL_ACE_TEST_DATA_SOURCE_DIR}
  --endl_dir=${GLOBAL_ENDL_TEST_DATA_SOURCE_DIR}
  --native_dir=${GLOBAL_NATIVE_TEST_DATA_SOURCE_DIR}
  --database_name=database.xml)

# Use this variable in the target dependencies list of a FRENSIE test
# executable (e.g. TARGET_DEPENDS ${COLLISION_DATABASE_XML_FILE_TARGET})
SET(COLLISION_DATABASE_XML_FILE_TARGET monte_carlo_collision_database_xml)

ADD_CUSTOM_TARGET(${COLLISION_DATABASE_XML_FILE_TARGET} ALL
  DEPENDS ${COLLISION_DATABASE_XML_FILE})

ADD_SUBDIRECTORY(monte_carlo)
INCLUDE_DIRECTORIES(monte_carlo/core/src monte_carlo/collision/core/src monte_carlo/collision/neutron/src monte_carlo/collision/photon/src monte_carlo/collision/electron/src monte_carlo/collision/kernel/src monte_carlo/active_region/core/src monte_carlo/active_region/response/src monte_carlo/active_region/source/src monte_carlo/event/core/src monte_carlo/event/estimator/src monte_carlo/event/particle_tracker/src monte_carlo/event/dispatcher/src )

# ADD_SUBDIRECTORY(data_gen)
# INCLUDE_DIRECTORIES(data_gen/free_gas_sab/src data_gen/endl/src data_gen/electron_photon/src)

ADD_SUBDIRECTORY(PyFrensie)

