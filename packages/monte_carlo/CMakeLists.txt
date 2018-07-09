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

# Set up the monte carlo package directory hierarchy
ADD_SUBDIRECTORY(core)
INCLUDE_DIRECTORIES(core/src)

ADD_SUBDIRECTORY(collision)
INCLUDE_DIRECTORIES(collision/core/src collision/photon/src collision/electron/src collision/neutron/src collision/kernel/src)

ADD_SUBDIRECTORY(active_region)
INCLUDE_DIRECTORIES(active_region/core/src active_region/source/src active_region/response/src)

ADD_SUBDIRECTORY(event)
INCLUDE_DIRECTORIES(event/core/src event/estimator/src event/particle_tracker/src event/weight_window/src event/dispatcher/src)

# ADD_SUBDIRECTORY(manager)
# INCLUDE_DIRECTORIES(manager/src)
