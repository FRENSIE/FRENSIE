ADD_EXECUTABLE(tstENDLIB97FileHandler
  tstENDLIB97FileHandler.cpp)
TARGET_LINK_LIBRARIES(tstENDLIB97FileHandler data_epdl)
ADD_TEST(ENDLIB97FileHandler_test tstENDLIB97FileHandler --first_header_test_file="${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_first_header.txt" --second_header_test_file="${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_second_header.txt" --full_header_test_file="${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_full_header.txt" --two_column_table_test_file="${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_two_column_table.txt" --three_column_table_test_file="${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_three_column_table.txt" --four_column_table_test_file="${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_four_column_table.txt" --two_two_column_tables_test_file="${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_two_two_column_tables.txt" --two_three_column_tables_test_file="${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_two_three_column_tables.txt" --two_four_column_tables_test_file="${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_two_four_column_tables.txt")

ADD_EXECUTABLE(tstPhotonDataProcessorShellMap
  tstPhotonDataProcessorShellMap.cpp)
TARGET_LINK_LIBRARIES(tstPhotonDataProcessorShellMap data_epdl)
ADD_TEST(PhotonDataProcessorShellMap_test tstPhotonDataProcessorShellMap --epdl_test_file="${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_epdl_file.txt" --eadl_test_file="${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_eadl_file.txt" --compton_test_file_prefix="${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_compton_profile-")

# ADD_EXECUTABLE(tstPhotonDataProcessor
#   tstPhotonDataProcessor.cpp)
# TARGET_LINK_LIBRARIES(tstPhotonDataProcessor data_epdl)
# ADD_TEST(PhotonDataProcessor_test tstPhotonDataProcessor) 
