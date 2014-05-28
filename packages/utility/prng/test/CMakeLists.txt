ADD_EXECUTABLE(tstLinearCongruentialGenerator
  tstLinearCongruentialGenerator.cpp
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstLinearCongruentialGenerator utilitycore utilityprng)
ADD_TEST(LinearCongruentialGenerator_test tstLinearCongruentialGenerator)

ADD_EXECUTABLE(tstFakeGenerator
  tstFakeGenerator.cpp
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstFakeGenerator utilitycore utilityprng)
ADD_TEST(FakeGenerator_test tstFakeGenerator)

ADD_EXECUTABLE(tstRandomNumberGenerator
  tstRandomNumberGenerator.cpp
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstRandomNumberGenerator utilitycore utilityprng)
ADD_TEST(RandomNumberGenerator_test tstRandomNumberGenerator)
IF(${FACEMC_ENABLE_MPI})
  ADD_TEST(ParallelRandomNumberGenerator_test 
    mpiexec -n 2 tstRandomNumberGenerator)
ENDIF()