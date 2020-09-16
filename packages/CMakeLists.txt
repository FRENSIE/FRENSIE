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
  utility/core/src 
  utility/archive/src 
  utility/archive/test 
  utility/system/src 
  utility/mpi/src 
  utility/prng/src 
  utility/interpolation/src 
  utility/direction_discretization/src 
  utility/distribution/src 
  utility/stats/src 
  utility/integrator/src 
  utility/grid/src 
  utility/mesh/src)

ADD_SUBDIRECTORY(geometry)
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_BINARY_DIR}/geometry geometry/core/src)

IF(FRENSIE_ENABLE_ROOT)
  INCLUDE_DIRECTORIES(geometry/root/src)
ENDIF()

IF(FRENSIE_ENABLE_DAGMC)
  INCLUDE_DIRECTORIES(geometry/dagmc/src)
ENDIF()

ADD_SUBDIRECTORY(data)
INCLUDE_DIRECTORIES(data/core/src data/ace/src data/endf/src data/endl/src data/native/src data/database/src data/xsdir/src)

# Create the database generator for the test data
ADD_EXECUTABLE(database_generator ${GLOBAL_TOOLS_TEST_DATA_SOURCE_DIR}/database_generator.cpp)
TARGET_LINK_LIBRARIES(database_generator data_database)

# Use this variable in the argument list of tests that require the test
# database (e.g. EXTRA_ARGS --test_database=${COLLISION_DATABASE_XML_FILE})
SET(COLLISION_DATABASE_XML_FILE ${CMAKE_CURRENT_BINARY_DIR}/database.xml)

SET(DATABASE_GENERATOR_CLA
  --1000_12p_available=1000.12p:available
  --1000_12p_filepath=1000.12p:filepath
  --1000_12p_filestartline=1000.12p:filestartline
  --1000_14p_available=1000.14p:available
  --1000_14p_filepath=1000.14p:filepath
  --1000_14p_filestartline=1000.14p:filestartline
  --5000_12p_available=5000.12p:available
  --5000_12p_filepath=5000.12p:filepath
  --5000_12p_filestartline=5000.12p:filestartline
  --6000_12p_available=6000.12p:available
  --6000_12p_filepath=6000.12p:filepath
  --6000_12p_filestartline=6000.12p:filestartline
  --8000_12p_available=8000.12p:available
  --8000_12p_filepath=8000.12p:filepath
  --8000_12p_filestartline=8000.12p:filestartline
  --79000_14p_available=79000.14p:available
  --79000_14p_filepath=79000.14p:filepath
  --79000_14p_filestartline=79000.14p:filestartline
  --82000_12p_available=82000.12p:available
  --82000_12p_filepath=82000.12p:filepath
  --82000_12p_filestartline=82000.12p:filestartline
  --82000_14p_available=82000.14p:available
  --82000_14p_filepath=82000.14p:filepath
  --82000_14p_filestartline=82000.14p:filestartline
  --92000_12p_available=92000.12p:available
  --92000_12p_filepath=92000.12p:filepath
  --92000_12p_filestartline=92000.12p:filestartline
  --82000_04p_available=82000.04p:available
  --82000_04p_filepath=82000.04p:filepath
  --82000_04p_filestartline=82000.04p:filestartline
  --5000_03e_available=5000.03e:available
  --5000_03e_filepath=5000.03e:filepath
  --5000_03e_filestartline=5000.03e:filestartline
  --82000_03e_available=82000.03e:available
  --82000_03e_filepath=82000.03e:filepath
  --82000_03e_filestartline=82000.03e:filestartline
  --1002_24u_available=1002.24u:available
  --1002_24u_filepath=1002.24u:filepath
  --1002_24u_filestartline=1002.24u:filestartline
  --6012_24u_available=6012.24u:available
  --6012_24u_filepath=6012.24u:filepath
  --6012_24u_filestartline=6012.24u:filestartline
  --1001_70c_available=1001.70c:available
  --1001_70c_filepath=1001.70c:filepath
  --1001_70c_filestartline=1001.70c:filestartline
  --8016_70c_available=8016.70c:available
  --8016_70c_filepath=8016.70c:filepath
  --8016_70c_filestartline=8016.70c:filestartline
  --82208_70c_available=82208.70c:available
  --82208_70c_filepath=82208.70c:filepath
  --82208_70c_filestartline=82208.70c:filestartline
  --92238_70c_available=92238.70c:available
  --92238_70c_filepath=92238.70c:filepath
  --92238_70c_filestartline=92238.70c:filestartline
  --grph_10t_available=grph.10t:available
  --grph_10t_filepath=grph.10t:filepath
  --grph_10t_filestartline=grph.10t:filestartline
  --lwtr_10t_available=lwtr.10t:available
  --lwtr_10t_filepath=lwtr.10t:filepath
  --lwtr_10t_filestartline=lwtr.10t:filestartline
  --poly_10t_available=poly.10t:available
  --poly_10t_filepath=poly.10t:filepath
  --poly_10t_filestartline=poly.10t:filestartline
  --native_dir=${GLOBAL_NATIVE_TEST_DATA_SOURCE_DIR}
  --database_name=database.xml)
REPLACE_ACE_PLACEHOLDER_ARGS(DATABASE_GENERATOR_CLA)

ADD_CUSTOM_COMMAND(OUTPUT ${COLLISION_DATABASE_XML_FILE}
  DEPENDS database_generator
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
  COMMAND database_generator ${DATABASE_GENERATOR_CLA})

UNSET(DATABASE_GENERATOR_CLA)

# Use this variable in the target dependencies list of a FRENSIE test
# executable (e.g. TARGET_DEPENDS ${COLLISION_DATABASE_XML_FILE_TARGET})
SET(COLLISION_DATABASE_XML_FILE_TARGET monte_carlo_collision_database_xml)

ADD_CUSTOM_TARGET(${COLLISION_DATABASE_XML_FILE_TARGET} ALL
  DEPENDS ${COLLISION_DATABASE_XML_FILE})

ADD_SUBDIRECTORY(monte_carlo)
INCLUDE_DIRECTORIES(monte_carlo/core/src 
                    monte_carlo/collision/core/src 
                    monte_carlo/collision/neutron/src 
                    monte_carlo/collision/photon/src 
                    monte_carlo/collision/electron/src 
                    monte_carlo/collision/kernel/src 
                    monte_carlo/active_region/core/src 
                    monte_carlo/active_region/response/src 
                    monte_carlo/active_region/source/src 
                    monte_carlo/event/core/src 
                    monte_carlo/event/estimator/src 
                    monte_carlo/event/particle_tracker/src 
                    monte_carlo/event/dispatcher/src 
                    monte_carlo/event/population_control/src 
                    monte_carlo/event/weight_cutoff/src 
                    monte_carlo/event/forced_collisions/src 
                    monte_carlo/manager/src )

ADD_SUBDIRECTORY(data_gen)
INCLUDE_DIRECTORIES(data_gen/free_gas_sab/src data_gen/endl/src data_gen/electron_photon/src)

ADD_SUBDIRECTORY(PyFrensie)

