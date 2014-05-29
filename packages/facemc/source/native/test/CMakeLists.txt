 ADD_EXECUTABLE(tstStateSource
  tstStateSource.cpp
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstStateSource facemc_source_native)
ADD_TEST(StateSource_test tstStateSource)

ADD_EXECUTABLE(tstDistributedSource
  tstDistributedSource.cpp)
TARGET_LINK_LIBRARIES(tstDistributedSource geometry_dagmc facemc_source_native)
ADD_TEST(DistributedSource_test tstDistributedSource --test_sat_file="${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_source_geom.sat")

ADD_EXECUTABLE(tstCompoundSource
  tstCompoundSource.cpp)
TARGET_LINK_LIBRARIES(tstCompoundSource geometry_dagmc facemc_source_native)
ADD_TEST(CompoundSource_test tstCompoundSource --test_sat_file="${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_source_geom.sat")
