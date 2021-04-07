FRENSIE_INITIALIZE_PACKAGE_TESTS(data_gen_endl)

# Add ENDL data generator test
FRENSIE_ADD_TEST_EXECUTABLE(StandardENDLDataGenerator DEPENDS tstStandardENDLDataGenerator.cpp)
FRENSIE_ADD_TEST(StandardENDLDataGenerator
  EXTRA_ARGS
  --test_h_eadl_file=${eadl1}
  --test_h_epdl_file=${epdl1}
  --test_h_eedl_file=${eedl1}
  --test_c_eadl_file=${eadl6}
  --test_c_epdl_file=${epdl6}
  --test_c_eedl_file=${eedl6})

FRENSIE_FINALIZE_PACKAGE_TESTS(data_gen_endl)
