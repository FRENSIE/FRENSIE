FRENSIE_INITIALIZE_PACKAGE_TESTS(monte_carlo_event_particle_tracker)

FRENSIE_ADD_TEST_EXECUTABLE(ParticleTracker DEPENDS tstParticleTracker.cpp)
FRENSIE_ADD_TEST(ParticleTracker)

IF(${FRENSIE_ENABLE_OPENMP})
  FRENSIE_ADD_TEST(SharedParallelParticleTracker_2
    TEST_EXEC_NAME_ROOT ParticleTracker
    EXTRA_ARGS --threads=2
    OPENMP_TEST)
  FRENSIE_ADD_TEST(SharedParallelParticleTracker_4
    TEST_EXEC_NAME_ROOT ParticleTracker
    EXTRA_ARGS --threads=4
    OPENMP_TEST)
ENDIF()

IF(${FRENSIE_ENABLE_MPI})
  FRENSIE_ADD_TEST(DistributedParticleTracker
    TEST_EXEC_NAME_ROOT ParticleTracker
    MPI_PROCS 2)
  FRENSIE_ADD_TEST(DistributedParticleTracker
    TEST_EXEC_NAME_ROOT ParticleTracker
    MPI_PROCS 4)
ENDIF()

FRENSIE_FINALIZE_PACKAGE_TESTS(monte_carlo_event_particle_tracker)
