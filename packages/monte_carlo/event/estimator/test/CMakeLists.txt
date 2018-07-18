FRENSIE_INITIALIZE_PACKAGE_TESTS(monte_carlo_event_estimator)

FRENSIE_ADD_TEST_EXECUTABLE(Estimator DEPENDS tstEstimator.cpp)
FRENSIE_ADD_TEST(Estimator)

IF(${FRENSIE_ENABLE_OPENMP})
  FRENSIE_ADD_TEST(SharedParallelEstimator_2
    TEST_EXEC_NAME_ROOT Estimator
    EXTRA_ARGS --threads=2
    OPENMP_TEST)
  FRENSIE_ADD_TEST(SharedParallelEstimator_4
    TEST_EXEC_NAME_ROOT Estimator
    EXTRA_ARGS --threads=4
    OPENMP_TEST)
ENDIF()

FRENSIE_ADD_TEST_EXECUTABLE(EntityEstimator DEPENDS tstEntityEstimator.cpp)
FRENSIE_ADD_TEST(EntityEstimator)

IF(${FRENSIE_ENABLE_OPENMP})
  FRENSIE_ADD_TEST(SharedParallelEntityEstimator_2
    TEST_EXEC_NAME_ROOT EntityEstimator
    EXTRA_ARGS --threads=2
    OPENMP_TEST)
  FRENSIE_ADD_TEST(SharedParallelEntityEstimator_4
    TEST_EXEC_NAME_ROOT EntityEstimator
    EXTRA_ARGS --threads=2
    OPENMP_TEST)
ENDIF()

IF(${FRENSIE_ENABLE_MPI})
  FRENSIE_ADD_TEST(DistributedParallelEntityEstimator
    TEST_EXEC_NAME_ROOT EntityEstimator
    MPI_PROCS 2)
  FRENSIE_ADD_TEST(DistributedParallelEntityEstimator
    TEST_EXEC_NAME_ROOT EntityEstimator
    MPI_PROCS 4)
ENDIF()

FRENSIE_ADD_TEST_EXECUTABLE(StandardEntityEstimator DEPENDS tstStandardEntityEstimator.cpp)
FRENSIE_ADD_TEST(StandardEntityEstimator)

IF(${FRENSIE_ENABLE_OPENMP})
  FRENSIE_ADD_TEST(SharedParallelStandardEntityEstimator_2
    TEST_EXEC_NAME_ROOT StandardEntityEstimator
    EXTRA_ARGS --threads=2
    OPENMP_TEST)
  ADD_TEST(SharedParallelStandardEntityEstimator_4
    TEST_EXEC_NAME_ROOT StandardEntityEstimator
    EXTRA_ARGS --threads=4
    OPENMP_TEST)
ENDIF()

IF(${FRENSIE_ENABLE_MPI})
  FRENSIE_ADD_TEST(DistributedParallelEntityEstimator
    TEST_EXEC_NAME_ROOT StandardEntityEstimator
    MPI_PROCS 2)
  FRENSIE_ADD_TEST(DistributedParallelEntityEstimator
    TEST_EXEC_NAME_ROOT StandardEntityEstimator
    MPI_PROCS 4)
ENDIF()

FRENSIE_FINALIZE_PACKAGE_TESTS(monte_carlo_event_estimator)
