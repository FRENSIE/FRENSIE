ADD_EXECUTABLE(tstEndfFissionYieldsHelpers
  tstEndfFissionYieldsHelpers.cpp )
TARGET_LINK_LIBRARIES(tstEndfFissionYieldsHelpers data_endf)
ADD_TEST(ENDFFissionYieldsHelpers_test tstEndfFissionYieldsHelpers
--test_endf_file="${GLOBAL_ENDF_TEST_DATA_SOURCE_DIR}/U_235.txt")
SET_PROPERTY(TEST ENDFFissionYieldsHelpers_test PROPERTY LABELS data_endf endf)

ADD_EXECUTABLE(tstEndfFissionYieldsFileHandler
  tstEndfFissionYieldsFileHandler.cpp )
TARGET_LINK_LIBRARIES(tstEndfFissionYieldsFileHandler data_endf)
ADD_TEST(ENDFFissionYieldsFileHandler_test tstEndfFissionYieldsFileHandler
--test_endf_file="${GLOBAL_ENDF_TEST_DATA_SOURCE_DIR}/U_235.txt"
--zaid_name="92235")
SET_PROPERTY(TEST ENDFFissionYieldsFileHandler_test PROPERTY LABELS data_endf endf)
