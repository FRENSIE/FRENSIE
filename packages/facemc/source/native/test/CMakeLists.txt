 ADD_EXECUTABLE(tstStateSource
  tstStateSource.cpp
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstStateSource facemc_source_native)
ADD_TEST(StateSource_test tstStateSource)

ADD_EXECUTABLE(tstDistributedSource
  tstDistributedSource.cpp)
TARGET_LINK_LIBRARIES(tstDistributedSource facemc_source_native)
ADD_TEST(DistributedSource_test tstDistributedSource --test_sat_file="${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_source_geom.sat")

ADD_EXECUTABLE(tstCompoundSource
  tstCompoundSource.cpp)
TARGET_LINK_LIBRARIES(tstCompoundSource facemc_source_native)
ADD_TEST(CompoundSource_test tstCompoundSource --test_sat_file="${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_source_geom.sat")

ADD_EXECUTABLE(tstStandardParticleSourceFactory
  tstStandardParticleSourceFactory.cpp)
TARGET_LINK_LIBRARIES(tstStandardParticleSourceFactory facemc_source_native)
ADD_TEST(StandardParticleSourceFactory_test tstStandardParticleSourceFactory --test_simple_source_xml_file="${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_simple_source.xml" --test_complex_source_xml_file="${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_complex_source.xml" --test_compound_source_xml_file="${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_compound_source.xml" --test_sat_file="${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_source_geom.sat")

ADD_EXECUTABLE(tstSourceModuleInterface_Native
  tstModuleInterface.cpp)
TARGET_LINK_LIBRARIES(tstSourceModuleInterface_Native facemc_source_native)
ADD_TEST(SourceModuleInterface_Native_test tstSourceModuleInterface_Native --test_source_xml_file="${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_complex_source.xml" --test_sat_file="${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_source_geom.sat")
