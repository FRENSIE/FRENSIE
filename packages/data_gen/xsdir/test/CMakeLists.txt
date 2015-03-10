ADD_EXECUTABLE(tstXsdirEntry 
  tstXsdirEntry.cpp
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstXsdirEntry data_gen_xsdir)
ADD_TEST(XsdirEntry_test tstXsdirEntry)