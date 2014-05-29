 ADD_EXECUTABLE(tstACEFileHandler
  tstACEFileHandler.cpp)
TARGET_LINK_LIBRARIES(tstACEFileHandler data_ace)
ADD_TEST(ACEFileHandler_test tstACEFileHandler --test_ace_file="${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_h1_ace_file.txt")

ADD_EXECUTABLE(tstXSSNeutronDataExtractor
  tstXSSNeutronDataExtractor.cpp)
TARGET_LINK_LIBRARIES(tstXSSNeutronDataExtractor data_ace)
ADD_TEST(XSSNeutronDataExtractor_test tstXSSNeutronDataExtractor --test_basic_ace_file="${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_h1_ace_file.txt" --test_basic_ace_table="1001.70c")