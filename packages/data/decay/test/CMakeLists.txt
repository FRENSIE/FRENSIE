ADD_EXECUTABLE(tstDecayData 
  tstDecayData.cpp )
TARGET_LINK_LIBRARIES(tstDecayData data_decay)
ADD_TEST(DecayData_test tstDecayData
--test_decay_data_file="${CMAKE_CURRENT_SOURCE_DIR}/test_files/endf7.dk.xml"
--zaid_name="94239")
