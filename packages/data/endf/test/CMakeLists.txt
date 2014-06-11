ADD_EXECUTABLE(tstEndfFissionYieldsHelpers 
  tstEndfFissionYieldsHelpers.cpp )
TARGET_LINK_LIBRARIES(tstEndfFissionYieldsHelpers data_endf)
ADD_TEST(ENDF_Fission_Yields_Helpers_test tstEndfFissionYieldsHelpers
--test_endf_file="${CMAKE_CURRENT_SOURCE_DIR}/test_files/U-235.txt")

