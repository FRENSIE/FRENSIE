ADD_SUBDIRECTORY(test_files)

ADD_EXECUTABLE(tstSourceHDF5FileHandler
  tstSourceHDF5FileHandler.cpp
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstSourceHDF5FileHandler monte_carlo_source_native)
ADD_TEST(SourceHDF5FileHandler_test tstSourceHDF5FileHandler)

ADD_EXECUTABLE(tstStandardParticleSource
  tstStandardParticleSource.cpp)
TARGET_LINK_LIBRARIES(tstStandardParticleSource monte_carlo_source_native)
ADD_TEST(StandardParticleSource_test tstStandardParticleSource)

IF(${FRENSIE_ENABLE_OPENMP})
  ADD_TEST(SharedStandardParticleSource_2_test tstStandardParticleSource --threads=2)
  ADD_TEST(SharedStandardParticleSource_4_test tstStandardParticleSource --threads=4)
ENDIF()

IF(${FRENSIE_ENABLE_MPI})
  ADD_EXECUTABLE(tstDistributedStandardParticleSource
  tstDistributedStandardParticleSource.cpp)
  TARGET_LINK_LIBRARIES(tstDistributedStandardParticleSource monte_carlo_source_native)
  ADD_TEST(DistributedStandardParticleSource_1_test ${MPIEXEC} -n 1 tstDistributedStandardParticleSource)
  ADD_TEST(DistributedStandardParticleSource_2_test ${MPIEXEC} -n 2 tstDistributedStandardParticleSource)
  ADD_TEST(DistributedStandardParticleSource_4_test ${MPIEXEC} -n 4 tstDistributedStandardParticleSource)
ENDIF()

IF(FRENSIE_ENABLE_DAGMC)
  ADD_EXECUTABLE(tstStandardParticleSourceRejection_DagMC
    tstStandardParticleSourceRejection_DagMC.cpp)
  TARGET_LINK_LIBRARIES(tstStandardParticleSourceRejection_DagMC monte_carlo_source_native geometry_dagmc)
  ADD_TEST(StandardParticleSourceRejection_DagMC_test tstStandardParticleSourceRejection_DagMC --test_geom_xml_file="${CMAKE_CURRENT_BINARY_DIR}/test_files/test_source_dagmc_geom.xml")

  IF(${FRENSIE_ENABLE_OPENMP})
    ADD_TEST(SharedStandardParticleSourceRejection_DagMC_2_test tstStandardParticleSourceRejection_DagMC --test_geom_xml_file="${CMAKE_CURRENT_BINARY_DIR}/test_files/test_source_dagmc_geom.xml" --threads=2)
    ADD_TEST(SharedStandardParticleSourceRejection_DagMC_4_test tstStandardParticleSourceRejection_DagMC --test_geom_xml_file="${CMAKE_CURRENT_BINARY_DIR}/test_files/test_source_dagmc_geom.xml" --threads=4)
  ENDIF()
ENDIF()

IF(FRENSIE_ENABLE_ROOT)
  ADD_EXECUTABLE(tstStandardParticleSourceRejection_Root
    tstStandardParticleSourceRejection_Root.cpp)
  TARGET_LINK_LIBRARIES(tstStandardParticleSourceRejection_Root monte_carlo_source_native geometry_root)
  ADD_TEST(StandardParticleSourceRejection_Root_test tstStandardParticleSourceRejection_Root --test_geom_xml_file="${CMAKE_CURRENT_BINARY_DIR}/test_files/test_source_dagmc_geom.xml")

  IF(${FRENSIE_ENABLE_OPENMP})
    ADD_TEST(SharedStandardParticleSourceRejection_Root_2_test tstStandardParticleSourceRejection_Root --test_geom_xml_file="${CMAKE_CURRENT_BINARY_DIR}/test_files/test_source_dagmc_geom.xml" --threads=2)
    ADD_TEST(SharedStandardParticleSourceRejection_Root_4_test tstStandardParticleSourceRejection_Root --test_geom_xml_file="${CMAKE_CURRENT_BINARY_DIR}/test_files/test_source_dagmc_geom.xml" --threads=4)
  ENDIF()
ENDIF()

ADD_EXECUTABLE(tstCompoundStandardParticleSource
  tstCompoundStandardParticleSource.cpp)
TARGET_LINK_LIBRARIES(tstCompoundStandardParticleSource monte_carlo_source_native)
ADD_TEST(CompoundStandardParticleSource_test tstCompoundStandardParticleSource)

IF(${FRENSIE_ENABLE_OPENMP})
  ADD_TEST(SharedCompoundStandardParticleSource_2_test tstCompoundStandardParticleSource --threads=2)
  ADD_TEST(SharedCompoundStandardParticleSource_4_test tstCompoundStandardParticleSource --threads=4)
ENDIF()

IF(${FRENSIE_ENABLE_MPI})
  ADD_EXECUTABLE(tstDistributedCompoundStandardParticleSource
  tstDistributedCompoundStandardParticleSource.cpp)
  TARGET_LINK_LIBRARIES(tstDistributedCompoundStandardParticleSource monte_carlo_source_native)
  ADD_TEST(DistributedCompoundStandardParticleSource_1_test ${MPIEXEC} -n 1 tstDistributedCompoundStandardParticleSource)
  ADD_TEST(DistributedCompoundStandardParticleSource_2_test ${MPIEXEC} -n 2 tstDistributedCompoundStandardParticleSource)
  ADD_TEST(DistributedCompoundStandardParticleSource_4_test ${MPIEXEC} -n 4 tstDistributedCompoundStandardParticleSource)
ENDIF()

ADD_EXECUTABLE(tstCachedStateParticleSource
  tstCachedStateParticleSource.cpp)
TARGET_LINK_LIBRARIES(tstCachedStateParticleSource monte_carlo_source_native)
ADD_TEST(CachedStateParticleSource_test tstCachedStateParticleSource)

IF(${FRENSIE_ENABLE_OPENMP})
  ADD_TEST(SharedCachedStateParticleSource_2_test tstCachedStateParticleSource --threads=2)
  ADD_TEST(SharedCachedStateParticleSource_4_test tstCachedStateParticleSource --threads=4)
ENDIF()

IF(${FRENSIE_ENABLE_MPI})
  ADD_EXECUTABLE(tstDistributedCachedStateParticleSource
  tstDistributedCachedStateParticleSource.cpp)
  TARGET_LINK_LIBRARIES(tstDistributedCachedStateParticleSource monte_carlo_source_native)
  ADD_TEST(DistributedCachedStateParticleSource_1_test ${MPIEXEC} -n 1 tstDistributedCachedStateParticleSource)
  ADD_TEST(DistributedCachedStateParticleSource_2_test ${MPIEXEC} -n 2 tstDistributedCachedStateParticleSource)
  ADD_TEST(DistributedCachedStateParticleSource_4_test ${MPIEXEC} -n 4 tstDistributedCachedStateParticleSource)
ENDIF()

IF(FRENSIE_ENABLE_DAGMC)
  ADD_EXECUTABLE(tstStandardParticleSourceFactory_DagMC
    tstStandardParticleSourceFactory_DagMC.cpp)
  TARGET_LINK_LIBRARIES(tstStandardParticleSourceFactory_DagMC monte_carlo_source_native geometry_dagmc)
  ADD_TEST(StandardParticleSourceFactory_DagMC_test tstStandardParticleSourceFactory_DagMC --test_simple_source_xml_file="${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_simple_source.xml" --test_complex_source_xml_file="${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_complex_source.xml" --test_compound_source_xml_file="${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_compound_source.xml" --test_geom_xml_file="${CMAKE_CURRENT_BINARY_DIR}/test_files/test_source_dagmc_geom.xml")
ENDIF()

IF(FRENSIE_ENABLE_ROOT)
  ADD_EXECUTABLE(tstStandardParticleSourceFactory_Root
    tstStandardParticleSourceFactory_Root.cpp)
  TARGET_LINK_LIBRARIES(tstStandardParticleSourceFactory_Root monte_carlo_source_native geometry_root)
  ADD_TEST(StandardParticleSourceFactory_Root_test tstStandardParticleSourceFactory_Root --test_simple_source_xml_file="${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_simple_source.xml" --test_complex_source_xml_file="${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_complex_source.xml" --test_compound_source_xml_file="${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_compound_source.xml" --test_geom_xml_file="${CMAKE_CURRENT_BINARY_DIR}/test_files/test_source_root_geom.xml")
ENDIF()

ADD_EXECUTABLE(tstSourceModuleInterface_Native
  tstModuleInterface.cpp)
TARGET_LINK_LIBRARIES(tstSourceModuleInterface_Native monte_carlo_source_native)
ADD_TEST(SourceModuleInterface_Native_test tstSourceModuleInterface_Native)

IF(${FRENSIE_ENABLE_OPENMP})
  ADD_TEST(SharedSourceModuleInterface_Native_2_test tstSourceModuleInterface_Native --threads=2)
  ADD_TEST(SharedSourceModuleInterface_Native_4_test tstSourceModuleInterface_Native --threads=4)
ENDIF()

IF(${FRENSIE_ENABLE_MPI})
  ADD_EXECUTABLE(tstDistributedSourceModuleInterface_Native
  tstDistributedModuleInterface.cpp)
  TARGET_LINK_LIBRARIES(tstDistributedSourceModuleInterface_Native monte_carlo_source_native)
  ADD_TEST(DistributedSourceModuleInterface_Native_1_test ${MPIEXEC} -n 1 tstDistributedSourceModuleInterface_Native)
  ADD_TEST(DistributedSourceModuleInterface_Native_2_test ${MPIEXEC} -n 2 tstDistributedSourceModuleInterface_Native)
  ADD_TEST(DistributedSourceModuleInterface_Native_4_test ${MPIEXEC} -n 4 tstDistributedSourceModuleInterface_Native)
ENDIF()