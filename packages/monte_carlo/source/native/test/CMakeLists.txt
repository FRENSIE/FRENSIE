ADD_SUBDIRECTORY(test_files)

ADD_EXECUTABLE(tstPhaseSpaceDimension
  tstPhaseSpaceDimension.cpp
  ${FRENSIE_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstPhaseSpaceDimension monte_carlo_source_native)
ADD_TEST(PhaseSpaceDimension_test tstPhaseSpaceDimension)
SET_PROPERTY(TEST PhaseSpaceDimension_test PROPERTY LABELS monte_carlo_source_native)

ADD_EXECUTABLE(tstPhaseSpaceDimensionClass
  tstPhaseSpaceDimensionClass.cpp
  ${FRENSIE_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstPhaseSpaceDimensionClass monte_carlo_source_native)
ADD_TEST(PhaseSpaceDimensionClass_test tstPhaseSpaceDimensionClass)
SET_PROPERTY(TEST PhaseSpaceDimensionClass_test PROPERTY LABELS monte_carlo_source_native)

ADD_EXECUTABLE(tstPhaseSpacePoint
  tstPhaseSpacePoint.cpp
  ${FRENSIE_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstPhaseSpacePoint monte_carlo_source_native)
ADD_TEST(PhaseSpacePoint_test tstPhaseSpacePoint)
SET_PROPERTY(TEST PhaseSpacePoint_test PROPERTY LABELS monte_carlo_source_native)

ADD_EXECUTABLE(tstPhaseSpaceDimensionTraits
  tstPhaseSpaceDimensionTraits.cpp
  ${FRENSIE_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstPhaseSpaceDimensionTraits monte_carlo_source_native)
ADD_TEST(PhaseSpaceDimensionTraits_test tstPhaseSpaceDimensionTraits)
SET_PROPERTY(TEST PhaseSpaceDimensionTraits_test PROPERTY LABELS monte_carlo_source_native)

ADD_EXECUTABLE(tstIndependentPhaseSpaceDimensionDistribution
  tstIndependentPhaseSpaceDimensionDistribution.cpp
  ${FRENSIE_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstIndependentPhaseSpaceDimensionDistribution monte_carlo_source_native)
ADD_TEST(IndependentPhaseSpaceDimensionDistribution_test tstIndependentPhaseSpaceDimensionDistribution)
SET_PROPERTY(TEST IndependentPhaseSpaceDimensionDistribution_test PROPERTY LABELS monte_carlo_source_native)

ADD_EXECUTABLE(tstImportanceSampledIndependentPhaseSpaceDimensionDistribution
  tstImportanceSampledIndependentPhaseSpaceDimensionDistribution.cpp
  ${FRENSIE_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstImportanceSampledIndependentPhaseSpaceDimensionDistribution monte_carlo_source_native)
ADD_TEST(ImportanceSampledIndependentPhaseSpaceDimensionDistribution_test tstImportanceSampledIndependentPhaseSpaceDimensionDistribution)
SET_PROPERTY(TEST ImportanceSampledIndependentPhaseSpaceDimensionDistribution_test PROPERTY LABELS monte_carlo_source_native)

ADD_EXECUTABLE(tstFullyTabularDependentPhaseSpaceDimensionDistribution
  tstFullyTabularDependentPhaseSpaceDimensionDistribution.cpp
  ${FRENSIE_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstFullyTabularDependentPhaseSpaceDimensionDistribution monte_carlo_source_native)
ADD_TEST(FullyTabularDependentPhaseSpaceDimensionDistribution_test tstFullyTabularDependentPhaseSpaceDimensionDistribution)
SET_PROPERTY(TEST FullyTabularDependentPhaseSpaceDimensionDistribution_test PROPERTY LABELS monte_carlo_source_native)

ADD_EXECUTABLE(tstPartiallyTabularDependentPhaseSpaceDimensionDistribution
  tstPartiallyTabularDependentPhaseSpaceDimensionDistribution.cpp
  ${FRENSIE_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstPartiallyTabularDependentPhaseSpaceDimensionDistribution monte_carlo_source_native)
ADD_TEST(PartiallyTabularDependentPhaseSpaceDimensionDistribution_test tstPartiallyTabularDependentPhaseSpaceDimensionDistribution)
SET_PROPERTY(TEST PartiallyTabularDependentPhaseSpaceDimensionDistribution_test PROPERTY LABELS monte_carlo_source_native)

ADD_EXECUTABLE(tstImportanceSampledFullyTabularDependentPhaseSpaceDimensionDistribution
  tstImportanceSampledFullyTabularDependentPhaseSpaceDimensionDistribution.cpp
  ${FRENSIE_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstImportanceSampledFullyTabularDependentPhaseSpaceDimensionDistribution monte_carlo_source_native)
ADD_TEST(ImportanceSampledFullyTabularDependentPhaseSpaceDimensionDistribution_test tstImportanceSampledFullyTabularDependentPhaseSpaceDimensionDistribution)
SET_PROPERTY(TEST ImportanceSampledFullyTabularDependentPhaseSpaceDimensionDistribution_test PROPERTY LABELS monte_carlo_source_native)

ADD_EXECUTABLE(tstImportanceSampledPartiallyTabularDependentPhaseSpaceDimensionDistribution
  tstImportanceSampledPartiallyTabularDependentPhaseSpaceDimensionDistribution.cpp
  ${FRENSIE_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstImportanceSampledPartiallyTabularDependentPhaseSpaceDimensionDistribution monte_carlo_source_native)
ADD_TEST(ImportanceSampledPartiallyTabularDependentPhaseSpaceDimensionDistribution_test tstImportanceSampledPartiallyTabularDependentPhaseSpaceDimensionDistribution)
SET_PROPERTY(TEST ImportanceSampledPartiallyTabularDependentPhaseSpaceDimensionDistribution_test PROPERTY LABELS monte_carlo_source_native)

ADD_EXECUTABLE(tstPhaseSpaceDimensionDistribution
  tstPhaseSpaceDimensionDistribution.cpp
  ${FRENSIE_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstPhaseSpaceDimensionDistribution monte_carlo_source_native)
ADD_TEST(PhaseSpaceDimensionDistribution_test tstPhaseSpaceDimensionDistribution)
SET_PROPERTY(TEST PhaseSpaceDimensionDistribution_test PROPERTY LABELS monte_carlo_source_native)

ADD_EXECUTABLE(tstStandardParticleDistribution
  tstStandardParticleDistribution.cpp
  ${FRENSIE_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstStandardParticleDistribution monte_carlo_source_native)
ADD_TEST(StandardParticleDistribution_test tstStandardParticleDistribution)
SET_PROPERTY(TEST StandardParticleDistribution_test PROPERTY LABELS monte_carlo_source_native)

ADD_EXECUTABLE(tstResponseFunction
  tstResponseFunction.cpp
  ${FRENSIE_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstResponseFunction monte_carlo_source_native)
ADD_TEST(ResponseFunction_test tstResponseFunction)
SET_PROPERTY(TEST ResponseFunction_test PROPERTY LABELS monte_carlo_source_native)

ADD_EXECUTABLE(tstStandardResponseFunction
  tstStandardResponseFunction.cpp
  ${FRENSIE_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstStandardResponseFunction monte_carlo_source_native)
ADD_TEST(StandardResponseFunction_test tstStandardResponseFunction)
SET_PROPERTY(TEST StandardResponseFunction_test PROPERTY LABELS monte_carlo_source_native)

# ADD_EXECUTABLE(tstResponseFunctionFactory
#   tstResponseFunctionFactory.cpp)
# TARGET_LINK_LIBRARIES(tstResponseFunctionFactory monte_carlo_estimator_native)
# ADD_TEST(ResponseFunctionFactory_test tstResponseFunctionFactory --test_resp_func_xml_file="${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_response_functions.xml")
# SET_PROPERTY(TEST ResponseFunctionFactory_test PROPERTY LABELS monte_carlo_estimator_native)

ADD_EXECUTABLE(tstSourceHDF5FileHandler
  tstSourceHDF5FileHandler.cpp
  ${FRENSIE_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstSourceHDF5FileHandler monte_carlo_source_native)
ADD_TEST(SourceHDF5FileHandler_test tstSourceHDF5FileHandler)
SET_PROPERTY(TEST SourceHDF5FileHandler_test PROPERTY LABELS monte_carlo_source_native)

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
