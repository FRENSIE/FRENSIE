# Configure files needing absolute paths
CONFIGURE_FILE(${CMAKE_CURRENT_SOURCE_DIR}/test_model_archive.xml.in
  ${CMAKE_CURRENT_BINARY_DIR}/test_model_archive.xml)
CONFIGURE_FILE(${CMAKE_CURRENT_SOURCE_DIR}/test_navigator_archive.xml.in
  ${CMAKE_CURRENT_BINARY_DIR}/test_navigator_archive.xml)
