# Configure the test files
ADD_SUBDIRECTORY(test_files)

ADD_EXECUTABLE(tstModelFactory
  tstModelFactory.cpp
  ${FRENSIE_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstModelFactory geometry_factory)
ADD_TEST(ModelFactory_test tstModelFactory --test_dagmc_xml_file="${CMAKE_CURRENT_BINARY_DIR}/test_files/test_dagmc_geom.xml" --test_root_xml_file="${CMAKE_CURRENT_BINARY_DIR}/test_files/test_root_geom.xml")
SET_PROPERTY(TEST ModelFactory_test PROPERTY LABELS geometry_factory)
