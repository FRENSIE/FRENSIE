ADD_EXECUTABLE(tstHDF5FileHandler 
  tstHDF5FileHandler.cpp 
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstHDF5FileHandler utility_hdf5)
ADD_TEST(HDF5FileHandler_test tstHDF5FileHandler)
