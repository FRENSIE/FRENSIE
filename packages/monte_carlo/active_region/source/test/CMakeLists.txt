FRENSIE_INITIALIZE_PACKAGE_TESTS(monte_carlo_active_region_source)

FRENSIE_ADD_TEST_EXECUTABLE(StandardParticleSourceComponent DEPENDS tstStandardParticleSourceComponent.cpp)
FRENSIE_ADD_TEST(StandardParticleSourceComponent)

FRENSIE_ADD_TEST_EXECUTABLE(StandardAdjointParticleSourceComponent
  DEPENDS tstStandardAdjointParticleSourceComponent.cpp
  TARGET_DEPENDS ${COLLISION_DATABASE_XML_FILE_TARGET})
FRENSIE_ADD_TEST(StandardAdjointParticleSourceComponent
  EXTRA_ARGS
  --test_database=${COLLISION_DATABASE_XML_FILE})

# ADD_EXECUTABLE(tstStandardParticleSource
#   tstStandardParticleSource.cpp
#   ${FRENSIE_STD_UNIT_TEST_MAIN})
# TARGET_LINK_LIBRARIES(tstStandardParticleSource monte_carlo_source_native)
# ADD_TEST(StandardParticleSource_test tstStandardParticleSource)
# SET_PROPERTY(TEST StandardParticleSource_test PROPERTY LABELS monte_carlo_source_native)

# IF(FRENSIE_ENABLE_DAGMC OR FRENSIE_ENABLE_ROOT)
#   ADD_EXECUTABLE(tstEmbeddedStandardParticleSource
#     tstEmbeddedStandardParticleSource.cpp
#     ${FRENSIE_STD_UNIT_TEST_MAIN})
#   TARGET_LINK_LIBRARIES(tstEmbeddedStandardParticleSource monte_carlo_source_native geometry_factory)

#   IF(FRENSIE_ENABLE_DAGMC)
#     ADD_TEST(StandardParticleSource_DagMC_test tstEmbeddedStandardParticleSource --test_geom_xml_file="${CMAKE_CURRENT_BINARY_DIR}/test_files/test_source_dagmc_geom.xml")
#     SET_PROPERTY(TEST StandardParticleSource_DagMC_test PROPERTY LABELS monte_carlo_source_native)
#   ENDIF()

#   IF(FRENSIE_ENABLE_ROOT)
#     ADD_TEST(StandardParticleSource_Root_test tstEmbeddedStandardParticleSource --test_geom_xml_file="${CMAKE_CURRENT_BINARY_DIR}/test_files/test_source_root_geom.xml")
#     SET_PROPERTY(TEST StandardParticleSource_Root_test PROPERTY LABELS monte_carlo_source_native)
#   ENDIF()
# ENDIF()

# IF(FRENSIE_ENABLE_OPENPM OR FRENSIE_ENABLE_MPI)
#   ADD_EXECUTABLE(tstParallelStandardParticleSource
#     tstParallelStandardParticleSource.cpp
#     ${FRENSIE_STD_UNIT_TEST_MAIN})
#   TARGET_LINK_LIBRARIES(tstParallelStandardParticleSource monte_carlo_source_native)

#   IF(FRENSIE_ENABLE_OPENMP)
#     ADD_TEST(SharedParallelStandardParticleSource_2_test tstParallelStandardParticleSource --threads=2)
#     ADD_TEST(SharedParallelStandardParticleSource_4_test tstParallelStandardParticleSource --threads=4)
#     SET_PROPERTY(TEST SharedParallelStandardParticleSource_2_test PROPERTY LABELS monte_carlo_source_native)
#     SET_PROPERTY(TEST SharedParallelStandardParticleSource_4_test PROPERTY LABELS monte_carlo_source_native)
#   ENDIF()

#   IF(FRENSIE_ENABLE_MPI)
#     ADD_TEST(DistributedParallelStandardParticleSource_1_test ${MPIEXEC} -n 1 tstParallelStandardParticleSource)
#     ADD_TEST(DistributedParallelStandardParticleSource_2_test ${MPIEXEC} -n 2 tstParallelStandardParticleSource)
#     ADD_TEST(DistributedParallelStandardParticleSource_4_test ${MPIEXEC} -n 4 tstParallelStandardParticleSource)
#     SET_PROPERTY(TEST DistributedParallelStandardParticleSource_1_test PROPERTY LABELS monte_carlo_source_native)
#     SET_PROPERTY(TEST DistributedParallelStandardParticleSource_2_test PROPERTY LABELS monte_carlo_source_native)
#     SET_PROPERTY(TEST DistributedParallelStandardParticleSource_4_test PROPERTY LABELS monte_carlo_source_native)
#   ENDIF()

#   IF(FRENSIE_ENABLE_OPENMP AND FRENSIE_ENABLE_MPI)
#     ADD_TEST(HybridParallelStandardParticleSource_2_2_test ${MPIEXEC} -n 2 tstParallelStandardParticleSource --threads=2)
#     SET_PROPERTY(TEST HybridParallelStandardParticleSource_2_2_test PROPERTY LABELS monte_carlo_source_native)
#   ENDIF()
# ENDIF()

FRENSIE_FINALIZE_PACKAGE_TESTS(monte_carlo_active_region_source)
