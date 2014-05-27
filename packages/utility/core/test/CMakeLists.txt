ADD_EXECUTABLE(tstAssertion 
  tstAssertion.cpp 
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstAssertion utilitycore)
ADD_TEST(Assertion_test tstAssertion)

ADD_EXECUTABLE(tstContractException 
  tstContractException.cpp 
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstContractException utilitycore)
ADD_TEST(ContractException_test tstContractException)

ADD_EXECUTABLE(tstSortAlgorithms 
  tstSortAlgorithms.cpp 
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstSortAlgorithms utilitycore)
ADD_TEST(SortAlgorithms_test tstSortAlgorithms)

ADD_EXECUTABLE(tstSearchAlgorithms 
  tstSearchAlgorithms.cpp 
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstSearchAlgorithms utilitycore)
ADD_TEST(SearchAlgorithms_test tstSearchAlgorithms)

ADD_EXECUTABLE(tstExponentiationAlgorithms 
  tstExponentiationAlgorithms.cpp 
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstExponentiationAlgorithms utilitycore)
ADD_TEST(ExponentiationAlgorithms_test tstExponentiationAlgorithms)

ADD_EXECUTABLE(tstInterpolationPolicy 
  tstInterpolationPolicy.cpp 
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstInterpolationPolicy utilitycore)
ADD_TEST(InterpolationPolicy_test tstInterpolationPolicy)

ADD_EXECUTABLE(tstSetOperationFunctor 
  tstSetOperationFunctor.cpp 
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstSetOperationFunctor utilitycore)
ADD_TEST(SetOperationFunctor_test tstSetOperationFunctor)

ADD_EXECUTABLE(tstDirectionHelpers 
  tstDirectionHelpers.cpp 
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstDirectionHelpers utilitycore)
ADD_TEST(DirectionHelpers_test tstDirectionHelpers)

ADD_EXECUTABLE(tstCylindricalCoordinateHelpers 
  tstCylindricalCoordinateHelpers.cpp 
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstCylindricalCoordinateHelpers utilitycore)
ADD_TEST(CylindricalCoordinateHelpers_test tstCylindricalCoordinateHelpers)

ADD_EXECUTABLE(tstSphericalCoordinateHelpers 
  tstSphericalCoordinateHelpers.cpp 
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstSphericalCoordinateHelpers utilitycore)
ADD_TEST(SphericalCoordinateHelpers_test tstSphericalCoordinateHelpers)

ADD_EXECUTABLE(tstDataProcessor 
  tstDataProcessor.cpp 
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstDataProcessor utilitycore)
ADD_TEST(DataProcessor_test tstDataProcessor)