FRENSIE_INITIALIZE_PACKAGE_TESTS(monte_carlo_manager)

FRENSIE_ADD_TEST_EXECUTABLE(ParticleSimulationManagerFactory
  DEPENDS tstParticleSimulationManagerFactory.cpp
  TARGET_DEPENDS ${COLLISION_DATABASE_XML_FILE_TARGET})
FRENSIE_ADD_TEST(ParticleSimulationManagerFactory
  ACE_LIB_DEPENDS 1001.70c
  EXTRA_ARGS
  --test_database=${COLLISION_DATABASE_XML_FILE})

IF(${FRENSIE_ENABLE_OPENMP})
  FRENSIE_ADD_TEST(SharedParallelParticleSimulationManagerFactory_2
    TEST_EXEC_NAME_ROOT ParticleSimulationManagerFactory
    ACE_LIB_DEPENDS 1001.70c
    EXTRA_ARGS
    --test_database=${COLLISION_DATABASE_XML_FILE}
    --threads=2
    OPENMP_TEST)
  FRENSIE_ADD_TEST(SharedParallelParticleSimulationManagerFactory_4
    TEST_EXEC_NAME_ROOT ParticleSimulationManagerFactory
    ACE_LIB_DEPENDS 1001.70c
    EXTRA_ARGS
    --test_database=${COLLISION_DATABASE_XML_FILE}
    --threads=4
    OPENMP_TEST)
ENDIF()

IF(${FRENSIE_ENABLE_MPI})
  FRENSIE_ADD_TEST(DistributedParalleParticleSimulationManagerFactory
    TEST_EXEC_NAME_ROOT ParticleSimulationManagerFactory
    ACE_LIB_DEPENDS 1001.70c
    EXTRA_ARGS --test_database=${COLLISION_DATABASE_XML_FILE}
    MPI_PROCS 2)
  FRENSIE_ADD_TEST(DistributedParallelParticleSimulationManagerFactory
    TEST_EXEC_NAME_ROOT ParticleSimulationManagerFactory
    ACE_LIB_DEPENDS 1001.70c
    EXTRA_ARGS --test_database=${COLLISION_DATABASE_XML_FILE}
    MPI_PROCS 4)
ENDIF()

FRENSIE_ADD_TEST_EXECUTABLE(ParticleSimulationManager
  DEPENDS tstParticleSimulationManager.cpp
  TARGET_DEPENDS ${COLLISION_DATABASE_XML_FILE_TARGET})
FRENSIE_ADD_TEST(ParticleSimulationManager
  ACE_LIB_DEPENDS 1001.70c
  EXTRA_ARGS
  --test_database=${COLLISION_DATABASE_XML_FILE})

IF(${FRENSIE_ENABLE_OPENMP})
  FRENSIE_ADD_TEST(SharedParallelParticleSimulationManager_2
    TEST_EXEC_NAME_ROOT ParticleSimulationManager
    ACE_LIB_DEPENDS 1001.70c
    EXTRA_ARGS
    --test_database=${COLLISION_DATABASE_XML_FILE}
    --threads=2
    OPENMP_TEST)
  FRENSIE_ADD_TEST(SharedParallelParticleSimulationManager_4
    TEST_EXEC_NAME_ROOT ParticleSimulationManager
    ACE_LIB_DEPENDS 1001.70c
    EXTRA_ARGS
    --test_database=${COLLISION_DATABASE_XML_FILE}
    --threads=4
    OPENMP_TEST)
ENDIF()

IF(${FRENSIE_ENABLE_MPI})
  FRENSIE_ADD_TEST_EXECUTABLE(DistributedParticleSimulationManager
    DEPENDS tstDistributedParticleSimulationManager.cpp
    TARGET_DEPENDS ${COLLISION_DATABASE_XML_FILE_TARGET})
  FRENSIE_ADD_TEST(DistributedParticleSimulationManager
    ACE_LIB_DEPENDS 1001.70c
    EXTRA_ARGS --test_database=${COLLISION_DATABASE_XML_FILE}
    MPI_PROCS 2)
  FRENSIE_ADD_TEST(DistributedParticleSimulationManager
    ACE_LIB_DEPENDS 1001.70c
    EXTRA_ARGS --test_database=${COLLISION_DATABASE_XML_FILE}
    MPI_PROCS 4)
ENDIF()
  
FRENSIE_FINALIZE_PACKAGE_TESTS(monte_carlo_manager)
