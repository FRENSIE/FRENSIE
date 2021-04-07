# Process the root geometries (*.c -> *.root)
FRENSIE_PROCESS_ROOT_GEOM(basic_root_geometry
  TARGET_NAME ${ROOT_GEOM_TEST_TARGET}
  PACKAGE_NAME geometry_root)

# Configure files needing absolute paths
CONFIGURE_FILE(${CMAKE_CURRENT_SOURCE_DIR}/basic_root_model_archive_full_path.xml.in
  ${CMAKE_CURRENT_BINARY_DIR}/basic_root_model_archive_full_path.xml)
