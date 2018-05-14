# Process the root geometries (*.c -> *.root)
FRENSIE_PROCESS_ROOT_GEOM(test_root_geometry
  TARGET_NAME ${ROOT_GEOM_TEST_TARGET}
  PACKAGE_NAME monte_carlo_collision_kernel)
