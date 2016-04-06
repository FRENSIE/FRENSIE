ADD_EXECUTABLE(tstStandardENDLDataGenerator tstStandardENDLDataGenerator.cpp)
TARGET_LINK_LIBRARIES(tstStandardENDLDataGenerator data_gen_endl)
ADD_TEST(StandardENDLDataGenerator_test tstStandardENDLDataGenerator --test_h_eadl_file="${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_h_eadl_endl_file.txt" --test_h_epdl_file="${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_h_epdl_endl_file.txt" --test_h_eedl_file="${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_h_eedl_endl_file.txt" --test_c_eadl_file="${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_c_eadl_endl_file.txt" --test_c_epdl_file="${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_c_epdl_endl_file.txt" --test_c_eedl_file="${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_c_eedl_endl_file.txt")



