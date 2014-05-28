 ADD_EXECUTABLE(tstRay 
  tstRay.cpp 
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstRay geometrycore utilitycore)
ADD_TEST(Ray_test tstRay)