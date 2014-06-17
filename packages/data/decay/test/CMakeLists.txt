ADD_EXECUTABLE(tstISCDecayData 
  tstISCDecayData.cpp )
TARGET_LINK_LIBRARIES(tstISCDecayData data_decay)
ADD_TEST(ISCDecayData_test tstISCDecayData
--test_decay_data_file="${CMAKE_CURRENT_SOURCE_DIR}/test_files/endf7.dk.xml"
--zaid_name="94239")
