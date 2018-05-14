# Configure files needing absolute paths
CONFIGURE_FILE(${CMAKE_CURRENT_SOURCE_DIR}/test_source_dagmc_geom.xml.in
  ${CMAKE_CURRENT_BINARY_DIR}/test_source_dagmc_geom.xml)
CONFIGURE_FILE(${CMAKE_CURRENT_SOURCE_DIR}/test_source_root_geom.xml.in
  ${CMAKE_CURRENT_BINARY_DIR}/test_source_root_geom.xml)

# Build the root source test file binary
EXECUTE_PROCESS(COMMAND ${ROOT_EXE} ${CMAKE_CURRENT_SOURCE_DIR}/test_source_geom.c
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
  OUTPUT_QUIET
  ERROR_QUIET)