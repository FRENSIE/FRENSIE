FRENSIE_INITIALIZE_PACKAGE_TESTS(utility_prng)

FRENSIE_ADD_TEST_EXECUTABLE(LinearCongruentialGenerator DEPENDS tstLinearCongruentialGenerator.cpp)
FRENSIE_ADD_TEST(LinearCongruentialGenerator)

FRENSIE_ADD_TEST_EXECUTABLE(FakeGenerator DEPENDS tstFakeGenerator.cpp)
FRENSIE_ADD_TEST(FakeGenerator)

FRENSIE_ADD_TEST_EXECUTABLE(RandomNumberGenerator DEPENDS tstRandomNumberGenerator.cpp)
FRENSIE_ADD_TEST(RandomNumberGenerator)

IF(${FRENSIE_ENABLE_OPENMP})
  FRENSIE_ADD_TEST(SharedParallelRandomNumberGenerator_2
    TEST_EXEC_NAME_ROOT RandomNumberGenerator
    EXTRA_ARGS --threads=2
    OPENMP_TEST)
  FRENSIE_ADD_TEST(SharedParallelRandomNumberGenerator_4
    TEST_EXEC_NAME_ROOT RandomNumberGenerator
    EXTRA_ARGS --threads=4
    OPENMP_TEST)
ENDIF()

IF(${FRENSIE_ENABLE_MPI})
  FRENSIE_ADD_TEST(RandomNumberGenerator MPI_PROCS 2)
  FRENSIE_ADD_TEST(RandomNumberGenerator MPI_PROCS 4)
ENDIF()

IF(${FRENSIE_ENABLE_OPENMP} AND ${FRENSIE_ENABLE_MPI})
  FRENSIE_ADD_TEST(HybridParallelRandomNumberGenerator_2
    TEST_EXEC_NAME_ROOT RandomNumberGenerator
    MPI_PROCS 2
    EXTRA_ARGS --threads=2
    OPENMP_TEST)
ENDIF()

FRENSIE_FINALIZE_PACKAGE_TESTS(utility_prng)

