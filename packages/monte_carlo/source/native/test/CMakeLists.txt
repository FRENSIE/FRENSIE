ADD_SUBDIRECTORY(test_files)

ADD_EXECUTABLE(tstDistributedParticleSource
  tstDistributedParticleSource.cpp)
TARGET_LINK_LIBRARIES(tstDistributedParticleSource monte_carlo_source_native)
ADD_TEST(DistributedParticleSource_test tstDistributedParticleSource)

IF(${FRENSIE_ENABLE_OPENMP})
  ADD_TEST(SharedDistributedParticleSource_2_test tstDistributedParticleSource --threads=2)
  ADD_TEST(SharedDistributedParticleSource_4_test tstDistributedParticleSource --threads=4)
ENDIF()

IF(FRENSIE_ENABLE_DAGMC)
  ADD_EXECUTABLE(tstDistributedParticleSourceRejection_DagMC
    tstDistributedParticleSourceRejection_DagMC.cpp)
  TARGET_LINK_LIBRARIES(tstDistributedParticleSourceRejection_DagMC monte_carlo_source_native geometry_dagmc)
  ADD_TEST(DistributedParticleSourceRejection_DagMC_test tstDistributedParticleSourceRejection_DagMC --test_geom_xml_file="${CMAKE_CURRENT_BINARY_DIR}/test_files/test_source_dagmc_geom.xml")

  IF(${FRENSIE_ENABLE_OPENMP})
    ADD_TEST(SharedDistributedParticleSourceRejection_DagMC_2_test tstDistributedParticleSourceRejection_DagMC --test_geom_xml_file="${CMAKE_CURRENT_BINARY_DIR}/test_files/test_source_dagmc_geom.xml" --threads=2)
    ADD_TEST(SharedDistributedParticleSourceRejection_DagMC_4_test tstDistributedParticleSourceRejection_DagMC --test_geom_xml_file="${CMAKE_CURRENT_BINARY_DIR}/test_files/test_source_dagmc_geom.xml" --threads=4)
  ENDIF()
ENDIF()

IF(FRENSIE_ENABLE_ROOT)
  ADD_EXECUTABLE(tstDistributedParticleSourceRejection_Root
    tstDistributedParticleSourceRejection_Root.cpp)
  TARGET_LINK_LIBRARIES(tstDistributedParticleSourceRejection_Root monte_carlo_source_native geometry_root)
  ADD_TEST(DistributedParticleSourceRejection_Root_test tstDistributedParticleSourceRejection_Root --test_geom_xml_file="${CMAKE_CURRENT_BINARY_DIR}/test_files/test_source_dagmc_geom.xml")

  IF(${FRENSIE_ENABLE_OPENMP})
    ADD_TEST(SharedDistributedParticleSourceRejection_Root_2_test tstDistributedParticleSourceRejection_Root --test_geom_xml_file="${CMAKE_CURRENT_BINARY_DIR}/test_files/test_source_dagmc_geom.xml" --threads=2)
    ADD_TEST(SharedDistributedParticleSourceRejection_Root_4_test tstDistributedParticleSourceRejection_Root --test_geom_xml_file="${CMAKE_CURRENT_BINARY_DIR}/test_files/test_source_dagmc_geom.xml" --threads=4)
  ENDIF()
ENDIF()

ADD_EXECUTABLE(tstCompoundDistributedParticleSource
  tstCompoundDistributedParticleSource.cpp)
TARGET_LINK_LIBRARIES(tstCompoundDistributedParticleSource monte_carlo_source_native)
ADD_TEST(CompoundDistributedParticleSource_test tstCompoundDistributedParticleSource)

IF(${FRENSIE_ENABLE_OPENMP})
  ADD_TEST(SharedCompoundDistributedParticleSource_2_test tstCompoundDistributedParticleSource --threads=2)
  ADD_TEST(SharedCompoundDistributedParticleSource_4_test tstCompoundDistributedParticleSource --threads=4)
ENDIF()

ADD_EXECUTABLE(tstCachedStateParticleSource
  tstCachedStateParticleSource.cpp)
TARGET_LINK_LIBRARIES(tstCachedStateParticleSource monte_carlo_source_native)
ADD_TEST(CachedStateParticleSource_test tstCachedStateParticleSource)

IF(${FRENSIE_ENABLE_OPENMP})
  ADD_TEST(SharedCachedStateParticleSource_2_test tstCachedStateParticleSource --threads=2)
  ADD_TEST(SharedCachedStateParticleSource_4_test tstCachedStateParticleSource --threads=4)
ENDIF()

# IF(FRENSIE_ENABLE_DAGMC)
#   ADD_EXECUTABLE(tstStandardParticleSourceFactory
#     tstStandardParticleSourceFactory.cpp)
#   TARGET_LINK_LIBRARIES(tstStandardParticleSourceFactory monte_carlo_source_native)
#   ADD_TEST(StandardParticleSourceFactory_test tstStandardParticleSourceFactory --test_simple_source_xml_file="${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_simple_source.xml" --test_complex_source_xml_file="${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_complex_source.xml" --test_compound_source_xml_file="${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_compound_source.xml" --test_sat_file="${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_source_geom.sat")
# ENDIF()

# IF(FRENSIE_ENABLE_DAGMC)
#   ADD_EXECUTABLE(tstSourceModuleInterface_Native
#     tstModuleInterface.cpp)
#   TARGET_LINK_LIBRARIES(tstSourceModuleInterface_Native monte_carlo_source_native)
#   ADD_TEST(SourceModuleInterface_Native_test tstSourceModuleInterface_Native --test_source_xml_file="${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_complex_source.xml" --test_sat_file="${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_source_geom.sat")
# ENDIF()
