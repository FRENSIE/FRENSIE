 ADD_EXECUTABLE(tstENDLFileHandler
  tstENDLFileHandler.cpp)
TARGET_LINK_LIBRARIES(tstENDLFileHandler data_endl)
ADD_TEST(ENDLFileHandler_test tstENDLFileHandler --first_header_test_file="${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_first_header.txt" --second_header_test_file="${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_second_header.txt" --full_header_test_file="${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_full_header.txt" --two_column_table_test_file="${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_two_column_table.txt" --three_column_table_test_file="${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_three_column_table.txt" --four_column_table_test_file="${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_four_column_table.txt" --two_two_column_tables_test_file="${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_two_two_column_tables.txt" --two_three_column_tables_test_file="${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_two_three_column_tables.txt" --two_four_column_tables_test_file="${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_two_four_column_tables.txt")

ADD_EXECUTABLE(tstEvaluatedElectronDataContainer
  tstEvaluatedElectronDataContainer.cpp
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstEvaluatedElectronDataContainer data_endl)
ADD_TEST(EvaluatedElectronDataContainer_test tstEvaluatedElectronDataContainer)
