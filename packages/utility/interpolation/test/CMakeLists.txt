ADD_EXECUTABLE(tstInterpolationType 
  tstInterpolationType.cpp 
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstInterpolationType utility_interp)
ADD_TEST(InterpolationType_test tstInterpolationType)

ADD_EXECUTABLE(tstInterpolationPolicy 
  tstInterpolationPolicy.cpp 
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstInterpolationPolicy utility_interp)
ADD_TEST(InterpolationPolicy_test tstInterpolationPolicy)

ADD_EXECUTABLE(tstStandardInterpolator
  tstStandardInterpolator.cpp
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstStandardInterpolator utility_interp)
ADD_TEST(StandardInterpolator_test tstStandardInterpolator)

ADD_EXECUTABLE(tstHistogramInterpolator
  tstHistogramInterpolator.cpp
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstHistogramInterpolator utility_interp)
ADD_TEST(HistogramInterpolator_test tstHistogramInterpolator)

ADD_EXECUTABLE(tstGamowInterpolator
  tstGamowInterpolator.cpp
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstGamowInterpolator utility_interp)
ADD_TEST(GamowInterpolator_test tstGamowInterpolator)

ADD_EXECUTABLE(tstLinLinLinTwoDInterpolationPolicy
  tstLinLinLinTwoDInterpolationPolicy.cpp
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstLinLinLinTwoDInterpolationPolicy utility_interp)
ADD_TEST(LinLinLinTwoDInterpolationPolicy_test tstLinLinLinTwoDInterpolationPolicy)

# ADD_EXECUTABLE(tstLinLinLogTwoDInterpolationPolicy
#   tstLinLinLogTwoDInterpolationPolicy.cpp
#   ${TEUCHOS_STD_UNIT_TEST_MAIN})
# TARGET_LINK_LIBRARIES(tstLinLinLogTwoDInterpolationPolicy utility_interp)
# ADD_TEST(LinLinLogTwoDInterpolationPolicy_test tstLinLinLogTwoDInterpolationPolicy)

# ADD_EXECUTABLE(tstLinLogLinTwoDInterpolationPolicy
#   tstLinLogLinTwoDInterpolationPolicy.cpp
#   ${TEUCHOS_STD_UNIT_TEST_MAIN})
# TARGET_LINK_LIBRARIES(tstLinLogLinTwoDInterpolationPolicy utility_interp)
# ADD_TEST(LinLogLinTwoDInterpolationPolicy_test tstLinLogLinTwoDInterpolationPolicy)

# ADD_EXECUTABLE(tstLinLogLogTwoDInterpolationPolicy
#   tstLinLogLogTwoDInterpolationPolicy.cpp
#   ${TEUCHOS_STD_UNIT_TEST_MAIN})
# TARGET_LINK_LIBRARIES(tstLinLogLogTwoDInterpolationPolicy utility_interp)
# ADD_TEST(LinLogLogTwoDInterpolationPolicy_test tstLinLogLogTwoDInterpolationPolicy)

# ADD_EXECUTABLE(tstLogLinLinTwoDInterpolationPolicy
#   tstLogLinLinTwoDInterpolationPolicy.cpp
#   ${TEUCHOS_STD_UNIT_TEST_MAIN})
# TARGET_LINK_LIBRARIES(tstLogLinLinTwoDInterpolationPolicy utility_interp)
# ADD_TEST(LogLinLinTwoDInterpolationPolicy_test tstLogLinLinTwoDInterpolationPolicy)

# ADD_EXECUTABLE(tstLogLogLinTwoDInterpolationPolicy
#   tstLogLogLinTwoDInterpolationPolicy.cpp
#   ${TEUCHOS_STD_UNIT_TEST_MAIN})
# TARGET_LINK_LIBRARIES(tstLogLogLinTwoDInterpolationPolicy utility_interp)
# ADD_TEST(LogLogLinTwoDInterpolationPolicy_test tstLogLogLinTwoDInterpolationPolicy)

# ADD_EXECUTABLE(tstLogLinLogTwoDInterpolationPolicy
#   tstLogLinLogTwoDInterpolationPolicy.cpp
#   ${TEUCHOS_STD_UNIT_TEST_MAIN})
# TARGET_LINK_LIBRARIES(tstLogLinLogTwoDInterpolationPolicy utility_interp)
# ADD_TEST(LogLinLogTwoDInterpolationPolicy_test tstLogLinLogTwoDInterpolationPolicy)

# ADD_EXECUTABLE(tstLogLogLogTwoDInterpolationPolicy
#   tstLogLogLogTwoDInterpolationPolicy.cpp
#   ${TEUCHOS_STD_UNIT_TEST_MAIN})
# TARGET_LINK_LIBRARIES(tstLogLogLogTwoDInterpolationPolicy utility_interp)
# ADD_TEST(LogLogLogTwoDInterpolationPolicy_test tstLogLogLogTwoDInterpolationPolicy)
