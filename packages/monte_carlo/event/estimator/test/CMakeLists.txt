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

FRENSIE_ADD_TEST_EXECUTABLE(StandardSurfaceEstimator DEPENDS tstStandardSurfaceEstimator.cpp)
FRENSIE_ADD_TEST(StandardSurfaceEstimator)

FRENSIE_ADD_TEST_EXECUTABLE(StandardCellEstimator DEPENDS tstStandardCellEstimator.cpp)
FRENSIE_ADD_TEST(StandardCellEstimator)

FRENSIE_ADD_TEST_EXECUTABLE(SurfaceFluxEstimator DEPENDS tstSurfaceFluxEstimator.cpp)
FRENSIE_ADD_TEST(SurfaceFluxEstimator)

# IF(${FRENSIE_ENABLE_OPENMP})
#   ADD_TEST(SharedParallelSurfaceFluxEstimator_2_test tstSurfaceFluxEstimator --threads=2)
#   ADD_TEST(SharedParallelSurfaceFluxEstimator_4_test tstSurfaceFluxEstimator --threads=4)
#   SET_PROPERTY(TEST SharedParallelSurfaceFluxEstimator_2_test PROPERTY LABELS monte_carlo_estimator_native openmp no_threads)
#   SET_PROPERTY(TEST SharedParallelSurfaceFluxEstimator_4_test PROPERTY LABELS monte_carlo_estimator_native openmp no_threads)
# ENDIF()

# Add_EXECUTABLE(tstSurfaceCurrentEstimator tstSurfaceCurrentEstimator.cpp)
# TARGET_LINK_LIBRARIES(tstSurfaceCurrentEstimator monte_carlo_estimator_native)
# ADD_TEST(SurfaceCurrentEstimator_test tstSurfaceCurrentEstimator)
# SET_PROPERTY(TEST SurfaceCurrentEstimator_test PROPERTY LABELS monte_carlo_estimator_native)

# IF(${FRENSIE_ENABLE_OPENMP})
#   ADD_TEST(SharedParallelSurfaceCurrentEstimator_2_test tstSurfaceCurrentEstimator --threads=2)
#   ADD_TEST(SharedParallelSurfaceCurrentEstimator_4_test tstSurfaceCurrentEstimator --threads=4)
#   SET_PROPERTY(TEST SharedParallelSurfaceCurrentEstimator_2_test PROPERTY LABELS monte_carlo_estimator_native openmp no_threads)
#   SET_PROPERTY(TEST SharedParallelSurfaceCurrentEstimator_4_test PROPERTY LABELS monte_carlo_estimator_native openmp no_threads)
# ENDIF()


FRENSIE_FINALIZE_PACKAGE_TESTS(monte_carlo_event_estimator)
