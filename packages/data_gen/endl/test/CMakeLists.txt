FRENSIE_INITIALIZE_PACKAGE_TESTS(data_gen_endl)

# Add ENDL data generator test
FRENSIE_ADD_TEST_EXECUTABLE(StandardENDLDataGenerator DEPENDS tstStandardENDLDataGenerator.cpp)
FRENSIE_ADD_TEST(StandardENDLDataGenerator
  EXTRA_ARGS
  --test_h_eadl_file=${GLOBAL_ENDL_TEST_DATA_SOURCE_DIR}/test_h_eadl_endl_file.txt
  --test_h_epdl_file=${GLOBAL_ENDL_TEST_DATA_SOURCE_DIR}/test_h_epdl_endl_file.txt
  --test_h_eedl_file=${GLOBAL_ENDL_TEST_DATA_SOURCE_DIR}/test_h_eedl_endl_file.txt
  --test_c_eadl_file=${GLOBAL_ENDL_TEST_DATA_SOURCE_DIR}/test_c_eadl_endl_file.txt
  --test_c_epdl_file=${GLOBAL_ENDL_TEST_DATA_SOURCE_DIR}/test_c_epdl_endl_file.txt
  --test_c_eedl_file=${GLOBAL_ENDL_TEST_DATA_SOURCE_DIR}/test_c_eedl_endl_file.txt)

FRENSIE_FINALIZE_PACKAGE_TESTS(data_gen_endl)