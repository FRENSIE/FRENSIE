# Configure files needing absolute paths
CONFIGURE_FILE(${CMAKE_CURRENT_SOURCE_DIR}/test_geom_basic.xml.in
  ${CMAKE_CURRENT_BINARY_DIR}/test_geom_basic.xml)
CONFIGURE_FILE(${CMAKE_CURRENT_SOURCE_DIR}/test_geom_advanced.xml.in
  ${CMAKE_CURRENT_BINARY_DIR}/test_geom_advanced.xml)
CONFIGURE_FILE(${CMAKE_CURRENT_SOURCE_DIR}/test_geom.xml.in
  ${CMAKE_CURRENT_BINARY_DIR}/test_geom.xml)
