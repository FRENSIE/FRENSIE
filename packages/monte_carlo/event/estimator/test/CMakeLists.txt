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
  FRENSIE_ADD_TEST(DistributedEntityEstimator
    TEST_EXEC_NAME_ROOT EntityEstimator
    MPI_PROCS 2)
  FRENSIE_ADD_TEST(DistributedEntityEstimator
    TEST_EXEC_NAME_ROOT EntityEstimator
    MPI_PROCS 4)
ENDIF()

FRENSIE_ADD_TEST_EXECUTABLE(StandardEntityEstimator DEPENDS tstStandardEntityEstimator.cpp)
FRENSIE_ADD_TEST(StandardEntityEstimator)

# IF(${FRENSIE_ENABLE_OPENMP})
#   ADD_TEST(SharedParallelStandardEntityEstimator_2_test
#     tstStandardEntityEstimator --threads=2)
#   ADD_TEST(SharedParallelStandardEntityEstimator_4_test
#     tstStandardEntityEstimator --threads=4)
#   SET_PROPERTY(TEST SharedParallelStandardEntityEstimator_2_test PROPERTY LABELS monte_carlo_estimator_native openmp no_threads)
#   SET_PROPERTY(TEST SharedParallelStandardEntityEstimator_4_test PROPERTY LABELS monte_carlo_estimator_native openmp no_threads)
# ENDIF()

# IF(${FRENSIE_ENABLE_MPI})
#   Add_EXECUTABLE(tstDistributedStandardEntityEstimator
#     tstDistributedStandardEntityEstimator.cpp)
#   TARGET_LINK_LIBRARIES(tstDistributedStandardEntityEstimator monte_carlo_estimator_native)
#   ADD_TEST(DistributedParallelStandardEntityEstimator_1_test
#     ${MPIEXEC} -n 1 tstDistributedStandardEntityEstimator)
#   ADD_TEST(DistributedParallelStandardEntityEstimator_2_test
#     ${MPIEXEC} -n 2 tstDistributedStandardEntityEstimator)
#   ADD_TEST(DistributedParallelStandardEntityEstimator_4_test
#     ${MPIEXEC} -n 4 tstDistributedStandardEntityEstimator)
#   SET_PROPERTY(TEST DistributedParallelStandardEntityEstimator_1_test PROPERTY LABELS monte_carlo_estimator_native mpi no_threads)
#   SET_PROPERTY(TEST DistributedParallelStandardEntityEstimator_2_test PROPERTY LABELS monte_carlo_estimator_native mpi no_threads)
#   SET_PROPERTY(TEST DistributedParallelStandardEntityEstimator_4_test PROPERTY LABELS monte_carlo_estimator_native mpi no_threads)
# ENDIF()

FRENSIE_FINALIZE_PACKAGE_TESTS(monte_carlo_event_estimator)
