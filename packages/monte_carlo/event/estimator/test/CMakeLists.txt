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

# Add parallel tests

FRENSIE_FINALIZE_PACKAGE_TESTS(monte_carlo_event_estimator)
