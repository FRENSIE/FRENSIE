# Configure files needing absolute paths
CONFIGURE_FILE(${CMAKE_CURRENT_SOURCE_DIR}/test_geom_dagmc.xml.in
	${CMAKE_CURRENT_BINARY_DIR}/test_geom_dagmc.xml)
CONFIGURE_FILE(${CMAKE_CURRENT_SOURCE_DIR}/test_geom_root.xml.in
	${CMAKE_CURRENT_BINARY_DIR}/test_geom_root.xml)
CONFIGURE_FILE(${CMAKE_CURRENT_SOURCE_DIR}/test_observers_root.xml.in
  ${CMAKE_CURRENT_BINARY_DIR}/test_observers_root.xml)
  CONFIGURE_FILE(${CMAKE_CURRENT_SOURCE_DIR}/test_observers_ptrac.xml.in
  ${CMAKE_CURRENT_BINARY_DIR}/test_observers_ptrac.xml)
CONFIGURE_FILE(${CMAKE_CURRENT_SOURCE_DIR}/test_observers_dagmc.xml.in
  ${CMAKE_CURRENT_BINARY_DIR}/test_observers_dagmc.xml)
CONFIGURE_FILE(${CMAKE_CURRENT_SOURCE_DIR}/test_observers_root_factory.xml.in
  ${CMAKE_CURRENT_BINARY_DIR}/test_observers_root_factory.xml)
CONFIGURE_FILE(${CMAKE_CURRENT_SOURCE_DIR}/test_observers_dagmc_factory.xml.in
  ${CMAKE_CURRENT_BINARY_DIR}/test_observers_dagmc_factory.xml)
CONFIGURE_FILE(${CMAKE_CURRENT_SOURCE_DIR}/test_response_functions.xml.in
  ${CMAKE_CURRENT_BINARY_DIR}/test_response_functions.xml)

# Build root test file binary
EXECUTE_PROCESS(COMMAND ${ROOT_EXE} ${CMAKE_CURRENT_SOURCE_DIR}/Test_Root_Geometry.C
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
  OUTPUT_QUIET
  ERROR_QUIET)
