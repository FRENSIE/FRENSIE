FRENSIE_INITIALIZE_PACKAGE_TESTS(monte_carlo_active_region_source)

ADD_EXECUTABLE(tstStandardParticleSource
  tstStandardParticleSource.cpp
  ${FRENSIE_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstStandardParticleSource monte_carlo_source_native)
ADD_TEST(StandardParticleSource_test tstStandardParticleSource)
SET_PROPERTY(TEST StandardParticleSource_test PROPERTY LABELS monte_carlo_source_native)

IF(FRENSIE_ENABLE_DAGMC OR FRENSIE_ENABLE_ROOT)
  ADD_EXECUTABLE(tstEmbeddedStandardParticleSource
    tstEmbeddedStandardParticleSource.cpp
    ${FRENSIE_STD_UNIT_TEST_MAIN})
  TARGET_LINK_LIBRARIES(tstEmbeddedStandardParticleSource monte_carlo_source_native geometry_factory)

  IF(FRENSIE_ENABLE_DAGMC)
    ADD_TEST(StandardParticleSource_DagMC_test tstEmbeddedStandardParticleSource --test_geom_xml_file="${CMAKE_CURRENT_BINARY_DIR}/test_files/test_source_dagmc_geom.xml")
    SET_PROPERTY(TEST StandardParticleSource_DagMC_test PROPERTY LABELS monte_carlo_source_native)
  ENDIF()

  IF(FRENSIE_ENABLE_ROOT)
    ADD_TEST(StandardParticleSource_Root_test tstEmbeddedStandardParticleSource --test_geom_xml_file="${CMAKE_CURRENT_BINARY_DIR}/test_files/test_source_root_geom.xml")
    SET_PROPERTY(TEST StandardParticleSource_Root_test PROPERTY LABELS monte_carlo_source_native)
  ENDIF()
ENDIF()

IF(FRENSIE_ENABLE_OPENPM OR FRENSIE_ENABLE_MPI)
  ADD_EXECUTABLE(tstParallelStandardParticleSource
    tstParallelStandardParticleSource.cpp
    ${FRENSIE_STD_UNIT_TEST_MAIN})
  TARGET_LINK_LIBRARIES(tstParallelStandardParticleSource monte_carlo_source_native)

  IF(FRENSIE_ENABLE_OPENMP)
    ADD_TEST(SharedParallelStandardParticleSource_2_test tstParallelStandardParticleSource --threads=2)
    ADD_TEST(SharedParallelStandardParticleSource_4_test tstParallelStandardParticleSource --threads=4)
    SET_PROPERTY(TEST SharedParallelStandardParticleSource_2_test PROPERTY LABELS monte_carlo_source_native)
    SET_PROPERTY(TEST SharedParallelStandardParticleSource_4_test PROPERTY LABELS monte_carlo_source_native)
  ENDIF()

  IF(FRENSIE_ENABLE_MPI)
    ADD_TEST(DistributedParallelStandardParticleSource_1_test ${MPIEXEC} -n 1 tstParallelStandardParticleSource)
    ADD_TEST(DistributedParallelStandardParticleSource_2_test ${MPIEXEC} -n 2 tstParallelStandardParticleSource)
    ADD_TEST(DistributedParallelStandardParticleSource_4_test ${MPIEXEC} -n 4 tstParallelStandardParticleSource)
    SET_PROPERTY(TEST DistributedParallelStandardParticleSource_1_test PROPERTY LABELS monte_carlo_source_native)
    SET_PROPERTY(TEST DistributedParallelStandardParticleSource_2_test PROPERTY LABELS monte_carlo_source_native)
    SET_PROPERTY(TEST DistributedParallelStandardParticleSource_4_test PROPERTY LABELS monte_carlo_source_native)
  ENDIF()

  IF(FRENSIE_ENABLE_OPENMP AND FRENSIE_ENABLE_MPI)
    ADD_TEST(HybridParallelStandardParticleSource_2_2_test ${MPIEXEC} -n 2 tstParallelStandardParticleSource --threads=2)
    SET_PROPERTY(TEST HybridParallelStandardParticleSource_2_2_test PROPERTY LABELS monte_carlo_source_native)
  ENDIF()
ENDIF()

ADD_EXECUTABLE(tstCachedStateParticleSource
  tstCachedStateParticleSource.cpp
  ${FRENSIE_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstCachedStateParticleSource monte_carlo_source_native)
ADD_TEST(CachedStateParticleSource_test tstCachedStateParticleSource)
SET_PROPERTY(TEST CachedStateParticleSource_test PROPERTY LABELS monte_carlo_source_native)

IF(FRENSIE_ENABLE_DAGMC OR FRENSIE_ENABLE_ROOT)
  ADD_EXECUTABLE(tstEmbeddedCachedStateParticleSource
    tstEmbeddedCachedStateParticleSource.cpp
    ${FRENSIE_STD_UNIT_TEST_MAIN})
  TARGET_LINK_LIBRARIES(tstEmbeddedCachedStateParticleSource monte_carlo_source_native geometry_factory)

  IF(FRENSIE_ENABLE_DAGMC)
    ADD_TEST(CachedStateParticleSource_DagMC_test tstEmbeddedCachedStateParticleSource --test_geom_xml_file="${CMAKE_CURRENT_BINARY_DIR}/test_files/test_source_dagmc_geom.xml")
    SET_PROPERTY(TEST CachedStateParticleSource_DagMC_test PROPERTY LABELS monte_carlo_source_native)
  ENDIF()

  IF(FRENSIE_ENABLE_ROOT)
    ADD_TEST(CachedStateParticleSource_Root_test tstEmbeddedCachedStateParticleSource --test_geom_xml_file="${CMAKE_CURRENT_BINARY_DIR}/test_files/test_source_root_geom.xml")
    SET_PROPERTY(TEST CachedStateParticleSource_Root_test PROPERTY LABELS monte_carlo_source_native)
  ENDIF()
ENDIF()

IF(FRENSIE_ENABLE_OPENPM OR FRENSIE_ENABLE_MPI)
  ADD_EXECUTABLE(tstParallelCachedStateParticleSource
    tstParallelCachedStateParticleSource.cpp
    ${FRENSIE_STD_UNIT_TEST_MAIN})
  TARGET_LINK_LIBRARIES(tstParallelCachedStateParticleSource monte_carlo_source_native)

  IF(FRENSIE_ENABLE_OPENMP)
    ADD_TEST(SharedParallelCachedStateParticleSource_2_test tstParallelCachedStateParticleSource --threads=2)
    ADD_TEST(SharedParallelCachedStateParticleSource_4_test tstParallelCachedStateParticleSource --threads=4)
    SET_PROPERTY(TEST SharedParallelCachedStateParticleSource_2_test PROPERTY LABELS monte_carlo_source_native)
    SET_PROPERTY(TEST SharedParallelCachedStateParticleSource_4_test PROPERTY LABELS monte_carlo_source_native)
  ENDIF()

  IF(FRENSIE_ENABLE_MPI)
    ADD_TEST(DistributedParallelCachedStateParticleSource_1_test ${MPIEXEC} -n 1 tstParallelCachedStateParticleSource)
    ADD_TEST(DistributedParallelCachedStateParticleSource_2_test ${MPIEXEC} -n 2 tstParallelCachedStateParticleSource)
    ADD_TEST(DistributedParallelCachedStateParticleSource_4_test ${MPIEXEC} -n 4 tstParallelCachedStateParticleSource)
    SET_PROPERTY(TEST DistributedParallelCachedStateParticleSource_1_test PROPERTY LABELS monte_carlo_source_native)
    SET_PROPERTY(TEST DistributedParallelCachedStateParticleSource_2_test PROPERTY LABELS monte_carlo_source_native)
    SET_PROPERTY(TEST DistributedParallelCachedStateParticleSource_4_test PROPERTY LABELS monte_carlo_source_native)
  ENDIF()

  IF(FRENSIE_ENABLE_OPENMP AND FRENSIE_ENABLE_MPI)
    ADD_TEST(HybridParallelCachedStateParticleSource_2_2_test ${MPIEXEC} -n 2 tstParallelCachedStateParticleSource --threads=2)
    SET_PROPERTY(TEST HybridParallelCachedStateParticleSource_2_2_test PROPERTY LABELS monte_carlo_source_native)
  ENDIF()
ENDIF()

# IF(${FRENSIE_ENABLE_OPENMP})
#   ADD_TEST(SharedParallelCachedStateParticleSource_2_test tstCachedStateParticleSource --threads=2)
#   ADD_TEST(SharedParallelCachedStateParticleSource_4_test tstCachedStateParticleSource --threads=4)
#   SET_PROPERTY(TEST SharedParallelCachedStateParticleSource_2_test PROPERTY LABELS monte_carlo_source_native openmp no_threads)
#   SET_PROPERTY(TEST SharedParallelCachedStateParticleSource_4_test PROPERTY LABELS monte_carlo_source_native openmp no_threads)
# ENDIF()

# IF(${FRENSIE_ENABLE_MPI})
#   ADD_EXECUTABLE(tstDistributedParallelCachedStateParticleSource
#   tstDistributedCachedStateParticleSource.cpp)
#   TARGET_LINK_LIBRARIES(tstDistributedParallelCachedStateParticleSource monte_carlo_source_native)
#   ADD_TEST(DistributedParallelCachedStateParticleSource_1_test ${MPIEXEC} -n 1 tstDistributedParallelCachedStateParticleSource)
#   ADD_TEST(DistributedParallelCachedStateParticleSource_2_test ${MPIEXEC} -n 2 tstDistributedParallelCachedStateParticleSource)
#   ADD_TEST(DistributedParallelCachedStateParticleSource_4_test ${MPIEXEC} -n 4 tstDistributedParallelCachedStateParticleSource)
#   SET_PROPERTY(TEST DistributedParallelCachedStateParticleSource_1_test PROPERTY LABELS monte_carlo_source_native mpi no_threads)
#   SET_PROPERTY(TEST DistributedParallelCachedStateParticleSource_2_test PROPERTY LABELS monte_carlo_source_native mpi no_threads)
#   SET_PROPERTY(TEST DistributedParallelCachedStateParticleSource_4_test PROPERTY LABELS monte_carlo_source_native mpi no_threads)
# ENDIF()

# IF(FRENSIE_ENABLE_DAGMC)
#   ADD_EXECUTABLE(tstStandardParticleSourceFactory_DagMC
#     tstStandardParticleSourceFactory_DagMC.cpp)
#   TARGET_LINK_LIBRARIES(tstStandardParticleSourceFactory_DagMC monte_carlo_source_native geometry_dagmc)
#   ADD_TEST(StandardParticleSourceFactory_DagMC_test tstStandardParticleSourceFactory_DagMC --test_simple_source_xml_file="${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_simple_source.xml" --test_complex_source_xml_file="${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_complex_source.xml" --test_compound_source_xml_file="${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_compound_source.xml" --test_geom_xml_file="${CMAKE_CURRENT_BINARY_DIR}/test_files/test_source_dagmc_geom.xml")
#   SET_PROPERTY(TEST StandardParticleSourceFactory_DagMC_test PROPERTY LABELS monte_carlo_source_native dagmc)
# ENDIF()

# IF(FRENSIE_ENABLE_ROOT)
#   ADD_EXECUTABLE(tstStandardParticleSourceFactory_Root
#     tstStandardParticleSourceFactory_Root.cpp)
#   TARGET_LINK_LIBRARIES(tstStandardParticleSourceFactory_Root monte_carlo_source_native geometry_root)
#   ADD_TEST(StandardParticleSourceFactory_Root_test tstStandardParticleSourceFactory_Root --test_simple_source_xml_file="${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_simple_source.xml" --test_complex_source_xml_file="${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_complex_source.xml" --test_compound_source_xml_file="${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_compound_source.xml" --test_geom_xml_file="${CMAKE_CURRENT_BINARY_DIR}/test_files/test_source_root_geom.xml")
#   SET_PROPERTY(TEST StandardParticleSourceFactory_Root_test PROPERTY LABELS monte_carlo_source_native root)
# ENDIF()

FRENSIE_FINALIZE_PACKAGE_TESTS(monte_carlo_active_region_source)
