FRENSIE_INITIALIZE_PACKAGE_TESTS(monte_carlo_active_region_source)

SET(ROOT_GEOM_TEST_TARGET monte_carlo_active_region_source_test_root_geom)

ADD_SUBDIRECTORY(test_files)
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR})


FRENSIE_ADD_TEST_EXECUTABLE(StandardParticleSourceComponent DEPENDS tstStandardParticleSourceComponent.cpp)
FRENSIE_ADD_TEST(StandardParticleSourceComponent)

IF(FRENSIE_ENABLE_DAGMC)
  FRENSIE_ADD_TEST_EXECUTABLE(StandardParticleSourceComponentDagMC
    DEPENDS tstStandardParticleSourceComponentDagMC.cpp
    LIB_DEPENDS geometry_dagmc)
  FRENSIE_ADD_TEST(StandardParticleSourceComponentDagMC
    EXTRA_ARGS
    --test_cad_file=${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_source_geom.h5m)
ENDIF()

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
    --test_cad_file=${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_source_geom.h5m)
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

IF(FRENSIE_ENABLE_DAGMC)
  IF(${FRENSIE_ENABLE_OPENMP} OR ${FRENSIE_ENABLE_MPI})
    FRENSIE_ADD_TEST_EXECUTABLE(ParallelStandardParticleSourceComponentDagMC
      DEPENDS tstParallelStandardParticleSourceComponentDagMC.cpp
      LIB_DEPENDS geometry_dagmc)

    IF(${FRENSIE_ENABLE_OPENMP})
      FRENSIE_ADD_TEST(SharedParallelStandardParticleSourceComponentDagMC_2
        TEST_EXEC_NAME_ROOT ParallelStandardParticleSourceComponentDagMC
        EXTRA_ARGS
        --threads=2
        --test_cad_file=${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_source_geom.h5m
        OPENMP_TEST)
      FRENSIE_ADD_TEST(SharedParallelStandardParticleSourceComponentDagMC_4
        TEST_EXEC_NAME_ROOT ParallelStandardParticleSourceComponentDagMC
        EXTRA_ARGS
        --threads=4
        --test_cad_file=${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_source_geom.h5m
        OPENMP_TEST)
    ENDIF()

    IF(${FRENSIE_ENABLE_MPI})
      FRENSIE_ADD_TEST(DistributedParallelStandardParticleSourceComponentDagMC
        TEST_EXEC_NAME_ROOT ParallelStandardParticleSourceComponentDagMC
        EXTRA_ARGS
        --test_cad_file=${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_source_geom.h5m
        MPI_PROCS 1)
      FRENSIE_ADD_TEST(DistributedParallelStandardParticleSourceComponentDagMC
        TEST_EXEC_NAME_ROOT ParallelStandardParticleSourceComponentDagMC
        EXTRA_ARGS
        --test_cad_file=${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_source_geom.h5m
        MPI_PROCS 2)
      FRENSIE_ADD_TEST(DistributedParallelStandardParticleSourceComponentDagMC
        TEST_EXEC_NAME_ROOT ParallelStandardParticleSourceComponentDagMC
        EXTRA_ARGS
        --test_cad_file=${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_source_geom.h5m
        MPI_PROCS 4)
    ENDIF()

    IF(${FRENSIE_ENABLE_OPENMP} AND ${FRENSIE_ENABLE_MPI})
      FRENSIE_ADD_TEST(HybridParallelStandardParticleSourceComponentDagMC_2
        TEST_EXEC_NAME_ROOT ParallelStandardParticleSourceComponentDagMC
        EXTRA_ARGS
        --threads=2
        --test_cad_file=${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_source_geom.h5m
        MPI_PROCS 2
        OPENMP_TEST)
    ENDIF()
  ENDIF()
ENDIF()

IF(FRENSIE_ENABLE_ROOT)
  IF(${FRENSIE_ENABLE_OPENMP} OR ${FRENSIE_ENABLE_MPI})
    FRENSIE_ADD_TEST_EXECUTABLE(ParallelStandardParticleSourceComponentRoot
      DEPENDS tstParallelStandardParticleSourceComponentRoot.cpp
      LIB_DEPENDS geometry_root)

    IF(${FRENSIE_ENABLE_OPENMP})
      FRENSIE_ADD_TEST(SharedParallelStandardParticleSourceComponentRoot_2
        TEST_EXEC_NAME_ROOT ParallelStandardParticleSourceComponentRoot
        EXTRA_ARGS
        --threads=2
        --test_root_file=${CMAKE_CURRENT_BINARY_DIR}/test_files/test_source_geom.root
        OPENMP_TEST)
      FRENSIE_ADD_TEST(SharedParallelStandardParticleSourceComponentRoot_4
        TEST_EXEC_NAME_ROOT ParallelStandardParticleSourceComponentRoot
        EXTRA_ARGS
        --threads=4
        --test_root_file=${CMAKE_CURRENT_BINARY_DIR}/test_files/test_source_geom.root
        OPENMP_TEST)
    ENDIF()

    IF(${FRENSIE_ENABLE_MPI})
      FRENSIE_ADD_TEST(DistributedParallelStandardParticleSourceComponentRoot
        TEST_EXEC_NAME_ROOT ParallelStandardParticleSourceComponentRoot
        EXTRA_ARGS
        --test_root_file=${CMAKE_CURRENT_BINARY_DIR}/test_files/test_source_geom.root
        MPI_PROCS 1)
      FRENSIE_ADD_TEST(DistributedParallelStandardParticleSourceComponentRoot
        TEST_EXEC_NAME_ROOT ParallelStandardParticleSourceComponentRoot
        EXTRA_ARGS
        --test_root_file=${CMAKE_CURRENT_BINARY_DIR}/test_files/test_source_geom.root
        MPI_PROCS 2)
      FRENSIE_ADD_TEST(DistributedParallelStandardParticleSourceComponentRoot
        TEST_EXEC_NAME_ROOT ParallelStandardParticleSourceComponentRoot
        EXTRA_ARGS
        --test_root_file=${CMAKE_CURRENT_BINARY_DIR}/test_files/test_source_geom.root
        MPI_PROCS 4)
    ENDIF()

    IF(${FRENSIE_ENABLE_OPENMP} AND ${FRENSIE_ENABLE_MPI})
      FRENSIE_ADD_TEST(HybridParallelStandardParticleSourceComponentRoot_2
        TEST_EXEC_NAME_ROOT ParallelStandardParticleSourceComponentRoot
        MPI_PROCS 2
        EXTRA_ARGS
        --threads=2
        --test_root_file=${CMAKE_CURRENT_BINARY_DIR}/test_files/test_source_geom.root
        OPENMP_TEST)
    ENDIF()
  ENDIF()
ENDIF()

FRENSIE_ADD_TEST_EXECUTABLE(StandardParticleSource DEPENDS tstStandardParticleSource.cpp)
FRENSIE_ADD_TEST(StandardParticleSource)

IF(${FRENSIE_ENABLE_OPENMP} OR ${FRENSIE_ENABLE_MPI})
  FRENSIE_ADD_TEST_EXECUTABLE(ParallelStandardParticleSource DEPENDS tstParallelStandardParticleSource.cpp)

  IF(${FRENSIE_ENABLE_OPENMP})
    FRENSIE_ADD_TEST(SharedParallelStandardParticleSource_2
      TEST_EXEC_NAME_ROOT ParallelStandardParticleSource
      EXTRA_ARGS --threads=2
      OPENMP_TEST)
    FRENSIE_ADD_TEST(SharedParallelStandardParticleSource_4
      TEST_EXEC_NAME_ROOT ParallelStandardParticleSource
      EXTRA_ARGS --threads=4
      OPENMP_TEST)
  ENDIF()

  IF(${FRENSIE_ENABLE_MPI})
    FRENSIE_ADD_TEST(DistributedParallelStandardParticleSource
      TEST_EXEC_NAME_ROOT ParallelStandardParticleSource
      MPI_PROCS 1)
    FRENSIE_ADD_TEST(DistributedParallelStandardParticleSource
      TEST_EXEC_NAME_ROOT ParallelStandardParticleSource
      MPI_PROCS 2)
    FRENSIE_ADD_TEST(DistributedParallelStandardParticleSource
      TEST_EXEC_NAME_ROOT ParallelStandardParticleSource
      MPI_PROCS 4)
  ENDIF()

  IF(${FRENSIE_ENABLE_OPENMP} AND ${FRENSIE_ENABLE_MPI})
    FRENSIE_ADD_TEST(HybridParallelStandardParticleSource_2
      TEST_EXEC_NAME_ROOT ParallelStandardParticleSource
      MPI_PROCS 2
      EXTRA_ARGS --threads=2
      OPENMP_TEST)
  ENDIF()
ENDIF()

FRENSIE_FINALIZE_PACKAGE_TESTS(monte_carlo_active_region_source)
