ADD_EXECUTABLE(tstEstimatorType
  tstEstimatorType.cpp
  ${FRENSIE_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstEstimatorType geometry_core)
ADD_TEST(EstimatorType_test tstEstimatorType)
SET_PROPERTY(TEST EstimatorType_test PROPERTY LABELS geometry_core)

ADD_EXECUTABLE(tstRay
  tstRay.cpp
  ${FRENSIE_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstRay geometry_core utility_core)
ADD_TEST(Ray_test tstRay)
SET_PROPERTY(TEST Ray_test PROPERTY LABELS geometry_core)
