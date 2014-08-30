ADD_EXECUTABLE(tstLinearCongruentialGenerator
  tstLinearCongruentialGenerator.cpp
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstLinearCongruentialGenerator utility_core utility_prng)
ADD_TEST(LinearCongruentialGenerator_test tstLinearCongruentialGenerator)

ADD_EXECUTABLE(tstFakeGenerator
  tstFakeGenerator.cpp
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstFakeGenerator utility_core utility_prng)
ADD_TEST(FakeGenerator_test tstFakeGenerator)

ADD_EXECUTABLE(tstRandomNumberGenerator
  tstRandomNumberGenerator.cpp)
TARGET_LINK_LIBRARIES(tstRandomNumberGenerator utility_core utility_prng ${MPI_CXX_LIBRARIES})
ADD_TEST(RandomNumberGenerator_test tstRandomNumberGenerator)
IF(${FACEMC_ENABLE_MPI})
  ADD_TEST(ParallelRandomNumberGenerator_test 
    ${MPIEXEC} -n 2 tstRandomNumberGenerator)
ENDIF()
