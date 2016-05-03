ADD_EXECUTABLE(tstLinearCongruentialGenerator
  tstLinearCongruentialGenerator.cpp
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstLinearCongruentialGenerator utility_prng)
ADD_TEST(LinearCongruentialGenerator_test tstLinearCongruentialGenerator)

ADD_EXECUTABLE(tstFakeGenerator
  tstFakeGenerator.cpp
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstFakeGenerator utility_prng)
ADD_TEST(FakeGenerator_test tstFakeGenerator)

ADD_EXECUTABLE(tstRandomNumberGenerator
  tstRandomNumberGenerator.cpp)
TARGET_LINK_LIBRARIES(tstRandomNumberGenerator utility_prng)
ADD_TEST(RandomNumberGenerator_test tstRandomNumberGenerator)

IF(${FRENSIE_ENABLE_OPENMP})
  ADD_TEST(SharedParallelRandomNumberGenerator_2_test
    tstRandomNumberGenerator --threads=2)
  ADD_TEST(SharedParallelRandomNumberGenerator_4_test
    tstRandomNumberGenerator --threads=4)
ENDIF()

IF(${FRENSIE_ENABLE_MPI})
  ADD_TEST(DistributedParallelRandomNumberGenerator_2_test 
    ${MPIEXEC} -n 2 tstRandomNumberGenerator)
  ADD_TEST(DistributedParallelRandomNumberGenerator_4_test
    ${MPIEXEC} -n 4 tstRandomNumberGenerator)
ENDIF()

IF(${FRENSIE_ENABLE_OPENMP} AND ${FRENSIE_ENABLE_MPI})
  ADD_TEST(HybridParallelRandomNumberGenerator_2_2_test
    ${MPIEXEC} -n 2 tstRandomNumberGenerator --threads=2)
ENDIF()
