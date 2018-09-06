FRENSIE_INITIALIZE_PACKAGE_TESTS(data_endl)

INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR})

FRENSIE_ADD_TEST_EXECUTABLE(ENDLPhotoatomicDataProperties DEPENDS tstENDLPhotoatomicDataProperties.cpp)
FRENSIE_ADD_TEST(ENDLPhotoatomicDataProperties)

FRENSIE_ADD_TEST_EXECUTABLE(ENDLElectroatomicDataProperties DEPENDS tstENDLElectroatomicDataProperties.cpp)
FRENSIE_ADD_TEST(ENDLElectroatomicDataProperties)

FRENSIE_ADD_TEST_EXECUTABLE(ENDLFileHandler DEPENDS tstENDLFileHandler.cpp)
FRENSIE_ADD_TEST(ENDLFileHandler
  EXTRA_ARGS
  --first_header_test_file=${GLOBAL_ENDL_TEST_DATA_SOURCE_DIR}/test_first_header.txt
  --second_header_test_file=${GLOBAL_ENDL_TEST_DATA_SOURCE_DIR}/test_second_header.txt
  --full_header_test_file=${GLOBAL_ENDL_TEST_DATA_SOURCE_DIR}/test_full_header.txt
  --two_column_table_test_file=${GLOBAL_ENDL_TEST_DATA_SOURCE_DIR}/test_two_column_table.txt
  --three_column_table_test_file=${GLOBAL_ENDL_TEST_DATA_SOURCE_DIR}/test_three_column_table.txt
  --three_column_table_test_file_vector=${GLOBAL_ENDL_TEST_DATA_SOURCE_DIR}/test_three_column_table_vector.txt
  --four_column_table_test_file=${GLOBAL_ENDL_TEST_DATA_SOURCE_DIR}/test_four_column_table.txt
  --two_two_column_tables_test_file=${GLOBAL_ENDL_TEST_DATA_SOURCE_DIR}/test_two_two_column_tables.txt
  --two_three_column_tables_test_file=${GLOBAL_ENDL_TEST_DATA_SOURCE_DIR}/test_two_three_column_tables.txt
  --two_four_column_tables_test_file=${GLOBAL_ENDL_TEST_DATA_SOURCE_DIR}/test_two_four_column_tables.txt)

FRENSIE_ADD_TEST_EXECUTABLE(EPICSFileHandler DEPENDS tstEPICSFileHandler.cpp)
FRENSIE_ADD_TEST(EPICSFileHandler
  EXTRA_ARGS
  --first_header_test_file=${GLOBAL_ENDL_TEST_DATA_SOURCE_DIR}/epics_test_first_header.txt
  --second_header_test_file=${GLOBAL_ENDL_TEST_DATA_SOURCE_DIR}/epics_test_second_header.txt
  --full_header_test_file=${GLOBAL_ENDL_TEST_DATA_SOURCE_DIR}/epics_test_full_header.txt
  --two_column_table_test_file=${GLOBAL_ENDL_TEST_DATA_SOURCE_DIR}/epics_test_two_column_table.txt
  --three_column_table_test_file=${GLOBAL_ENDL_TEST_DATA_SOURCE_DIR}/epics_test_three_column_table.txt
  --three_column_table_test_file_vector=${GLOBAL_ENDL_TEST_DATA_SOURCE_DIR}/epics_test_three_column_table_vector.txt
  --four_column_table_test_file=${GLOBAL_ENDL_TEST_DATA_SOURCE_DIR}/epics_test_four_column_table.txt
  --two_two_column_tables_test_file=${GLOBAL_ENDL_TEST_DATA_SOURCE_DIR}/epics_test_two_two_column_tables.txt
  --two_three_column_tables_test_file=${GLOBAL_ENDL_TEST_DATA_SOURCE_DIR}/epics_test_two_three_column_tables.txt
  --two_four_column_tables_test_file=${GLOBAL_ENDL_TEST_DATA_SOURCE_DIR}/epics_test_two_four_column_tables.txt)

FRENSIE_ADD_TEST_EXECUTABLE(ENDLDataContainer DEPENDS tstENDLDataContainer.cpp)
FRENSIE_ADD_TEST(ENDLDataContainer)

FRENSIE_FINALIZE_PACKAGE_TESTS(data_endl)
