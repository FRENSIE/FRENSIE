ADD_EXECUTABLE(tstENDLFileHandler
  tstENDLFileHandler.cpp)
TARGET_LINK_LIBRARIES(tstENDLFileHandler data_endl)
ADD_TEST(ENDLFileHandler_test tstENDLFileHandler --first_header_test_file="${GLOBAL_ENDL_TEST_DATA_SOURCE_DIR}/test_first_header.txt" --second_header_test_file="${GLOBAL_ENDL_TEST_DATA_SOURCE_DIR}/test_second_header.txt" --full_header_test_file="${GLOBAL_ENDL_TEST_DATA_SOURCE_DIR}/test_full_header.txt" --two_column_table_test_file="${GLOBAL_ENDL_TEST_DATA_SOURCE_DIR}/test_two_column_table.txt" --three_column_table_test_file="${GLOBAL_ENDL_TEST_DATA_SOURCE_DIR}/test_three_column_table.txt" --three_column_table_test_file_vector="${GLOBAL_ENDL_TEST_DATA_SOURCE_DIR}/test_three_column_table_vector.txt" --four_column_table_test_file="${GLOBAL_ENDL_TEST_DATA_SOURCE_DIR}/test_four_column_table.txt" --two_two_column_tables_test_file="${GLOBAL_ENDL_TEST_DATA_SOURCE_DIR}/test_two_two_column_tables.txt" --two_three_column_tables_test_file="${GLOBAL_ENDL_TEST_DATA_SOURCE_DIR}/test_two_three_column_tables.txt" --two_four_column_tables_test_file="${GLOBAL_ENDL_TEST_DATA_SOURCE_DIR}/test_two_four_column_tables.txt")
SET_PROPERTY(TEST ENDLFileHandler_test PROPERTY LABELS data_endl endl)

ADD_EXECUTABLE(tstEPICSFileHandler
  tstEPICSFileHandler.cpp)
TARGET_LINK_LIBRARIES(tstEPICSFileHandler data_endl)
ADD_TEST(ENDLFileHandler_EPICS2014_test tstEPICSFileHandler --first_header_test_file="${GLOBAL_ENDL_TEST_DATA_SOURCE_DIR}/epics_test_first_header.txt" --second_header_test_file="${GLOBAL_ENDL_TEST_DATA_SOURCE_DIR}/epics_test_second_header.txt" --full_header_test_file="${GLOBAL_ENDL_TEST_DATA_SOURCE_DIR}/epics_test_full_header.txt" --two_column_table_test_file="${GLOBAL_ENDL_TEST_DATA_SOURCE_DIR}/epics_test_two_column_table.txt" --three_column_table_test_file="${GLOBAL_ENDL_TEST_DATA_SOURCE_DIR}/epics_test_three_column_table.txt" --three_column_table_test_file_vector="${GLOBAL_ENDL_TEST_DATA_SOURCE_DIR}/epics_test_three_column_table_vector.txt" --four_column_table_test_file="${GLOBAL_ENDL_TEST_DATA_SOURCE_DIR}/epics_test_four_column_table.txt" --two_two_column_tables_test_file="${GLOBAL_ENDL_TEST_DATA_SOURCE_DIR}/epics_test_two_two_column_tables.txt" --two_three_column_tables_test_file="${GLOBAL_ENDL_TEST_DATA_SOURCE_DIR}/epics_test_two_three_column_tables.txt" --two_four_column_tables_test_file="${GLOBAL_ENDL_TEST_DATA_SOURCE_DIR}/epics_test_two_four_column_tables.txt")
SET_PROPERTY(TEST ENDLFileHandler_EPICS2014_test PROPERTY LABELS data_endl endl)

ADD_EXECUTABLE(tstENDLDataContainer
  tstENDLDataContainer.cpp
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstENDLDataContainer data_endl)
ADD_TEST(ENDLDataContainer_test tstENDLDataContainer)
SET_PROPERTY(TEST ENDLDataContainer_test PROPERTY LABELS data_endl endl)
