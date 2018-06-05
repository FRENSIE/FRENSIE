FRENSIE_INITIALIZE_PACKAGE_TESTS(monte_carlo_active_region_source)

SET(ROOT_GEOM_TEST_TARGET monte_carlo_active_region_source_test_root_geom)

ADD_SUBDIRECTORY(test_files)
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR})

FRENSIE_ADD_TEST_EXECUTABLE(StandardParticleSourceComponent DEPENDS tstStandardParticleSourceComponent.cpp)
FRENSIE_ADD_TEST(StandardParticleSourceComponent)

FRENSIE_ADD_TEST_EXECUTABLE(StandardAdjointParticleSourceComponent
  DEPENDS tstStandardAdjointParticleSourceComponent.cpp
  TARGET_DEPENDS ${COLLISION_DATABASE_XML_FILE_TARGET})
FRENSIE_ADD_TEST(StandardAdjointParticleSourceComponent
  EXTRA_ARGS
  --test_database=${COLLISION_DATABASE_XML_FILE})

IF(FRENSIE_ENABLE_DAGMC)
  FRENSIE_ADD_TEST_EXECUTABLE(StandardParticleSourceComponentDagMCRejection
    DEPENDS tstStandardParticleSourceComponentDagMCRejection.cpp
    LIB_DEPENDS geometry_dagmc)
  FRENSIE_ADD_TEST(StandardParticleSourceComponentDagMCRejection
    EXTRA_ARGS
    --test_cad_file=${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_source_geom.sat)
ENDIF()

IF(FRENSIE_ENABLE_ROOT)
  FRENSIE_ADD_TEST_EXECUTABLE(StandardParticleSourceComponentRootRejection
    DEPENDS tstStandardParticleSourceComponentRootRejection.cpp
    TARGET_DEPENDS ${ROOT_GEOM_TEST_TARGET}
    LIB_DEPENDS geometry_root)
  FRENSIE_ADD_TEST(StandardParticleSourceComponentRootRejection
    EXTRA_ARGS
    --test_root_file=${CMAKE_CURRENT_BINARY_DIR}/test_files/test_source_geom.root)
ENDIF()

IF(${FRENSIE_ENABLE_OPENMP} OR ${FRENSIE_ENABLE_MPI})
  FRENSIE_ADD_TEST_EXECUTABLE(ParallelStandardParticleSourceComponent DEPENDS tstParallelStandardParticleSourceComponent.cpp)

  IF(${FRENSIE_ENABLE_OPENMP})
    FRENSIE_ADD_TEST(SharedParallelStandardParticleSourceComponent_2
      TEST_EXEC_NAME_ROOT ParallelStandardParticleSourceComponent
      EXTRA_ARGS --threads=2
      OPENMP_TEST)
    FRENSIE_ADD_TEST(SharedParallelStandardParticleSourceComponent_4
      TEST_EXEC_NAME_ROOT ParallelStandardParticleSourceComponent
      EXTRA_ARGS --threads=4
      OPENMP_TEST)
  ENDIF()

  IF(${FRENSIE_ENABLE_MPI})
    FRENSIE_ADD_TEST(DistributedParallelStandardParticleSourceComponent
      TEST_EXEC_NAME_ROOT ParallelStandardParticleSourceComponent
      MPI_PROCS 1)
    FRENSIE_ADD_TEST(DistributedParallelStandardParticleSourceComponent
      TEST_EXEC_NAME_ROOT ParallelStandardParticleSourceComponent
      MPI_PROCS 2)
    FRENSIE_ADD_TEST(DistributedParallelStandardParticleSourceComponent
      TEST_EXEC_NAME_ROOT ParallelStandardParticleSourceComponent
      MPI_PROCS 4)
  ENDIF()

  IF(${FRENSIE_ENABLE_OPENMP} AND ${FRENSIE_ENABLE_MPI})
    FRENSIE_ADD_TEST(HybridParallelStandardParticleSourceComponent_2
      TEST_EXEC_NAME_ROOT ParallelStandardParticleSourceComponent
      MPI_PROCS 2
      EXTRA_ARGS --threads=2
      OPENMP_TEST)
  ENDIF()
ENDIF()

FRENSIE_FINALIZE_PACKAGE_TESTS(monte_carlo_active_region_source)
