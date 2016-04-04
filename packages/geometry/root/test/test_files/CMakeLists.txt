# Configure files needing absolute paths
CONFIGURE_FILE(${CMAKE_CURRENT_SOURCE_DIR}/test_geom_basic.xml.in
	${CMAKE_CURRENT_BINARY_DIR}/test_geom_basic.xml)

CONFIGURE_FILE(${CMAKE_CURRENT_SOURCE_DIR}/test_geom_advanced.xml.in
	${CMAKE_CURRENT_BINARY_DIR}/test_geom_advanced.xml)

# Build basic root test file binary
EXECUTE_PROCESS(COMMAND ${ROOT_EXE} ${CMAKE_CURRENT_SOURCE_DIR}/basic_root_geometry.c
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
  OUTPUT_QUIET
  ERROR_QUIET)

# Build advanced root test file binary
EXECUTE_PROCESS(COMMAND ${ROOT_EXE} ${CMAKE_CURRENT_SOURCE_DIR}/advanced_root_geometry.c
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
  OUTPUT_QUIET
  ERROR_QUIET)