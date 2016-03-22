# Configure files needing absolute paths
CONFIGURE_FILE(${CMAKE_CURRENT_SOURCE_DIR}/test_geom.xml.in
	${CMAKE_CURRENT_BINARY_DIR}/test_geom.xml)
CONFIGURE_FILE(${CMAKE_CURRENT_SOURCE_DIR}/test_geom_root.xml.in
    ${CMAKE_CURRENT_BINARY_DIR}/test_geom_root.xml)

# Build root test file binary
EXECUTE_PROCESS(COMMAND ${ROOT_EXE} ${CMAKE_CURRENT_SOURCE_DIR}/Test_Root_Geometry.C
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
  OUTPUT_QUIET
  ERROR_QUIET)