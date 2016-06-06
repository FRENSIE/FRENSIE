 ADD_EXECUTABLE(tstRay 
  tstRay.cpp 
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstRay geometry_core utility_core)
ADD_TEST(Ray_test tstRay)
SET_PROPERTY(TEST Ray_test PROPERTY LABELS geometry_core)
