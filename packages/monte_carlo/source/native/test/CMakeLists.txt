ADD_SUBDIRECTORY(test_files)

ADD_EXECUTABLE(tstStandardParticleSource
  tstStandardParticleSource.cpp)
TARGET_LINK_LIBRARIES(tstStandardParticleSource monte_carlo_source_native)
ADD_TEST(StandardParticleSource_test tstStandardParticleSource)

IF(${FRENSIE_ENABLE_OPENMP})
  ADD_TEST(SharedStandardParticleSource_2_test tstStandardParticleSource --threads=2)
  ADD_TEST(SharedStandardParticleSource_4_test tstStandardParticleSource --threads=4)
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
