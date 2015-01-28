# Configure files needing absolute paths
CONFIGURE_FILE(${CMAKE_CURRENT_SOURCE_DIR}/test_geom.xml.in
	${CMAKE_CURRENT_BINARY_DIR}/test_geom.xml)
CONFIGURE_FILE(${CMAKE_CURRENT_SOURCE_DIR}/test_estimators.xml.in
  ${CMAKE_CURRENT_BINARY_DIR}/test_estimators.xml)
