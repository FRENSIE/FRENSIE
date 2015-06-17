ADD_SUBDIRECTORY(test_files)

ADD_EXECUTABLE(tstDagMCProperties
  tstDagMCProperties.cpp
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstDagMCProperties geometry_core geometry_dagmc)
ADD_TEST(DagMCProperties_test tstDagMCProperties)
