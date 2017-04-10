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

ADD_EXECUTABLE(tstSourceHDF5FileHandler
  tstSourceHDF5FileHandler.cpp
  ${FRENSIE_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstSourceHDF5FileHandler monte_carlo_source_native)
ADD_TEST(SourceHDF5FileHandler_test tstSourceHDF5FileHandler)
SET_PROPERTY(TEST SourceHDF5FileHandler_test PROPERTY LABELS monte_carlo_source_native)

# ADD_EXECUTABLE(tstResponseFunction
#   tstResponseFunction.cpp
#   ${TEUCHOS_STD_UNIT_TEST_MAIN})
# TARGET_LINK_LIBRARIES(tstResponseFunction monte_carlo_estimator_native)
# ADD_TEST(ResponseFunction_test tstResponseFunction)
# SET_PROPERTY(TEST ResponseFunction_test PROPERTY LABELS monte_carlo_estimator_native)

# ADD_EXECUTABLE(tstResponseFunctionFactory
#   tstResponseFunctionFactory.cpp)
# TARGET_LINK_LIBRARIES(tstResponseFunctionFactory monte_carlo_estimator_native)
# ADD_TEST(ResponseFunctionFactory_test tstResponseFunctionFactory --test_resp_func_xml_file="${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_response_functions.xml")
# SET_PROPERTY(TEST ResponseFunctionFactory_test PROPERTY LABELS monte_carlo_estimator_native)

# ADD_EXECUTABLE(tstStandardParticleSource
#   tstStandardParticleSource.cpp)
# TARGET_LINK_LIBRARIES(tstStandardParticleSource monte_carlo_source_native)
# ADD_TEST(StandardParticleSource_test tstStandardParticleSource)
# SET_PROPERTY(TEST StandardParticleSource_test PROPERTY LABELS monte_carlo_source_native)

# IF(${FRENSIE_ENABLE_OPENMP})
#   ADD_TEST(SharedParallelStandardParticleSource_2_test tstStandardParticleSource --threads=2)
#   ADD_TEST(SharedParallelStandardParticleSource_4_test tstStandardParticleSource --threads=4)
#   SET_PROPERTY(TEST SharedParallelStandardParticleSource_2_test PROPERTY LABELS monte_carlo_source_native openmp no_threads)
#   SET_PROPERTY(TEST SharedParallelStandardParticleSource_4_test PROPERTY LABELS monte_carlo_source_native openmp no_threads)
# ENDIF()

# IF(${FRENSIE_ENABLE_MPI})
#   ADD_EXECUTABLE(tstDistributedParallelStandardParticleSource
#   tstDistributedStandardParticleSource.cpp)
#   TARGET_LINK_LIBRARIES(tstDistributedParallelStandardParticleSource monte_carlo_source_native)
#   ADD_TEST(DistributedParallelStandardParticleSource_1_test ${MPIEXEC} -n 1 tstDistributedParallelStandardParticleSource)
#   ADD_TEST(DistributedParallelStandardParticleSource_2_test ${MPIEXEC} -n 2 tstDistributedParallelStandardParticleSource)
#   ADD_TEST(DistributedParallelStandardParticleSource_4_test ${MPIEXEC} -n 4 tstDistributedParallelStandardParticleSource)
#   SET_PROPERTY(TEST DistributedParallelStandardParticleSource_1_test PROPERTY LABELS monte_carlo_source_native mpi no_threads)
#   SET_PROPERTY(TEST DistributedParallelStandardParticleSource_2_test PROPERTY LABELS monte_carlo_source_native mpi no_threads)
#   SET_PROPERTY(TEST DistributedParallelStandardParticleSource_4_test PROPERTY LABELS monte_carlo_source_native mpi no_threads)
# ENDIF()

# IF(FRENSIE_ENABLE_DAGMC)
#   ADD_EXECUTABLE(tstStandardParticleSourceRejection_DagMC
#     tstStandardParticleSourceRejection_DagMC.cpp)
#   TARGET_LINK_LIBRARIES(tstStandardParticleSourceRejection_DagMC monte_carlo_source_native geometry_dagmc)
#   ADD_TEST(StandardParticleSourceRejection_DagMC_test tstStandardParticleSourceRejection_DagMC --test_geom_xml_file="${CMAKE_CURRENT_BINARY_DIR}/test_files/test_source_dagmc_geom.xml")
#   SET_PROPERTY(TEST StandardParticleSourceRejection_DagMC_test PROPERTY LABELS monte_carlo_source_native dagmc)

#   IF(${FRENSIE_ENABLE_OPENMP})
#     ADD_TEST(SharedParallelStandardParticleSourceRejection_DagMC_2_test tstStandardParticleSourceRejection_DagMC --test_geom_xml_file="${CMAKE_CURRENT_BINARY_DIR}/test_files/test_source_dagmc_geom.xml" --threads=2)
#     ADD_TEST(SharedParallelStandardParticleSourceRejection_DagMC_4_test tstStandardParticleSourceRejection_DagMC --test_geom_xml_file="${CMAKE_CURRENT_BINARY_DIR}/test_files/test_source_dagmc_geom.xml" --threads=4)
#     SET_PROPERTY(TEST SharedParallelStandardParticleSourceRejection_DagMC_2_test PROPERTY LABELS monte_carlo_source_native openmp dagmc no_threads)
#     SET_PROPERTY(TEST SharedParallelStandardParticleSourceRejection_DagMC_4_test PROPERTY LABELS monte_carlo_source_native openmp dagmc no_threads)
#   ENDIF()
# ENDIF()

# IF(FRENSIE_ENABLE_ROOT)
#   ADD_EXECUTABLE(tstStandardParticleSourceRejection_Root
#     tstStandardParticleSourceRejection_Root.cpp)
#   TARGET_LINK_LIBRARIES(tstStandardParticleSourceRejection_Root monte_carlo_source_native geometry_root)
#   ADD_TEST(StandardParticleSourceRejection_Root_test tstStandardParticleSourceRejection_Root --test_geom_xml_file="${CMAKE_CURRENT_BINARY_DIR}/test_files/test_source_root_geom.xml")
#   SET_PROPERTY(TEST StandardParticleSourceRejection_Root_test PROPERTY LABELS monte_carlo_source_native root)

#   IF(${FRENSIE_ENABLE_OPENMP})
#     ADD_TEST(SharedParallelStandardParticleSourceRejection_Root_2_test tstStandardParticleSourceRejection_Root --test_geom_xml_file="${CMAKE_CURRENT_BINARY_DIR}/test_files/test_source_root_geom.xml" --threads=2)
#     ADD_TEST(SharedParallelStandardParticleSourceRejection_Root_4_test tstStandardParticleSourceRejection_Root --test_geom_xml_file="${CMAKE_CURRENT_BINARY_DIR}/test_files/test_source_root_geom.xml" --threads=4)
#     SET_PROPERTY(TEST SharedParallelStandardParticleSourceRejection_Root_2_test PROPERTY LABELS monte_carlo_source_native openmp root no_threads)
#     SET_PROPERTY(TEST SharedParallelStandardParticleSourceRejection_Root_4_test PROPERTY LABELS monte_carlo_source_native openmp root no_threads)
#   ENDIF()
# ENDIF()

# ADD_EXECUTABLE(tstCompoundStandardParticleSource
#   tstCompoundStandardParticleSource.cpp)
# TARGET_LINK_LIBRARIES(tstCompoundStandardParticleSource monte_carlo_source_native)
# ADD_TEST(CompoundStandardParticleSource_test tstCompoundStandardParticleSource)
# SET_PROPERTY(TEST CompoundStandardParticleSource_test PROPERTY LABELS monte_carlo_source_native)

# IF(${FRENSIE_ENABLE_OPENMP})
#   ADD_TEST(SharedParallelCompoundStandardParticleSource_2_test tstCompoundStandardParticleSource --threads=2)
#   ADD_TEST(SharedParallelCompoundStandardParticleSource_4_test tstCompoundStandardParticleSource --threads=4)
#   SET_PROPERTY(TEST SharedParallelCompoundStandardParticleSource_2_test PROPERTY LABELS monte_carlo_source_native openmp no_threads)
#   SET_PROPERTY(TEST SharedParallelCompoundStandardParticleSource_4_test PROPERTY LABELS monte_carlo_source_native openmp no_threads)
# ENDIF()

# IF(${FRENSIE_ENABLE_MPI})
#   ADD_EXECUTABLE(tstDistributedParallelCompoundStandardParticleSource
#   tstDistributedCompoundStandardParticleSource.cpp)
#   TARGET_LINK_LIBRARIES(tstDistributedParallelCompoundStandardParticleSource monte_carlo_source_native)
#   ADD_TEST(DistributedParallelCompoundStandardParticleSource_1_test ${MPIEXEC} -n 1 tstDistributedParallelCompoundStandardParticleSource)
#   ADD_TEST(DistributedParallelCompoundStandardParticleSource_2_test ${MPIEXEC} -n 2 tstDistributedParallelCompoundStandardParticleSource)
#   ADD_TEST(DistributedParallelCompoundStandardParticleSource_4_test ${MPIEXEC} -n 4 tstDistributedParallelCompoundStandardParticleSource)
#   SET_PROPERTY(TEST DistributedParallelCompoundStandardParticleSource_1_test PROPERTY LABELS monte_carlo_source_native mpi no_threads)
#   SET_PROPERTY(TEST DistributedParallelCompoundStandardParticleSource_2_test PROPERTY LABELS monte_carlo_source_native mpi no_threads)
#   SET_PROPERTY(TEST DistributedParallelCompoundStandardParticleSource_4_test PROPERTY LABELS monte_carlo_source_native mpi no_threads)
# ENDIF()

# ADD_EXECUTABLE(tstCachedStateParticleSource
#   tstCachedStateParticleSource.cpp)
# TARGET_LINK_LIBRARIES(tstCachedStateParticleSource monte_carlo_source_native)
# ADD_TEST(CachedStateParticleSource_test tstCachedStateParticleSource)
# SET_PROPERTY(TEST CachedStateParticleSource_test PROPERTY LABELS monte_carlo_source_native)

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

# ADD_EXECUTABLE(tstSourceModuleInterface_Native
#   tstModuleInterface.cpp)
# TARGET_LINK_LIBRARIES(tstSourceModuleInterface_Native monte_carlo_source_native)
# ADD_TEST(SourceModuleInterface_Native_test tstSourceModuleInterface_Native)
# SET_PROPERTY(TEST SourceModuleInterface_Native_test PROPERTY LABELS monte_carlo_source_native)

# IF(${FRENSIE_ENABLE_OPENMP})
#   ADD_TEST(SharedParallelSourceModuleInterface_Native_2_test tstSourceModuleInterface_Native --threads=2)
#   ADD_TEST(SharedParallelSourceModuleInterface_Native_4_test tstSourceModuleInterface_Native --threads=4)
#   SET_PROPERTY(TEST SharedParallelSourceModuleInterface_Native_2_test PROPERTY LABELS monte_carlo_source_native openmp no_threads)
#   SET_PROPERTY(TEST SharedParallelSourceModuleInterface_Native_4_test PROPERTY LABELS monte_carlo_source_native openmp no_threads)
# ENDIF()

# IF(${FRENSIE_ENABLE_MPI})
#   ADD_EXECUTABLE(tstDistributedParallelSourceModuleInterface_Native
#   tstDistributedModuleInterface.cpp)
#   TARGET_LINK_LIBRARIES(tstDistributedParallelSourceModuleInterface_Native monte_carlo_source_native)
#   ADD_TEST(DistributedParallelSourceModuleInterface_Native_1_test ${MPIEXEC} -n 1 tstDistributedParallelSourceModuleInterface_Native)
#   ADD_TEST(DistributedParallelSourceModuleInterface_Native_2_test ${MPIEXEC} -n 2 tstDistributedParallelSourceModuleInterface_Native)
#   ADD_TEST(DistributedParallelSourceModuleInterface_Native_4_test ${MPIEXEC} -n 4 tstDistributedParallelSourceModuleInterface_Native)
#   SET_PROPERTY(TEST DistributedParallelSourceModuleInterface_Native_1_test PROPERTY LABELS monte_carlo_source_native mpi no_threads)
#   SET_PROPERTY(TEST DistributedParallelSourceModuleInterface_Native_2_test PROPERTY LABELS monte_carlo_source_native mpi no_threads)
#   SET_PROPERTY(TEST DistributedParallelSourceModuleInterface_Native_4_test PROPERTY LABELS monte_carlo_source_native mpi no_threads)
# ENDIF()
