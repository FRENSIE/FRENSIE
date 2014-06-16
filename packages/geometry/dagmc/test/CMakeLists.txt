ADD_SUBDIRECTORY(test_files)

ADD_EXECUTABLE(tstDagMCHelpers
  tstDagMCHelpers.cpp)
TARGET_LINK_LIBRARIES(tstDagMCHelpers geometry_core geometry_dagmc)
ADD_TEST(DagMCHelpers_test tstDagMCHelpers --test_sat_file="${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_geom.sat")

ADD_EXECUTABLE(tstDagMCInstanceFactory
  tstDagMCInstanceFactory.cpp)
TARGET_LINK_LIBRARIES(tstDagMCInstanceFactory geometry_core geometry_dagmc)
ADD_TEST(DagMCInstanceFactory_test tstDagMCInstanceFactory --test_xml_file="${CMAKE_CURRENT_BINARY_DIR}/test_files/test_geom.xml")

ADD_EXECUTABLE(tstGeometryModuleInterface_DagMC
  tstModuleInterface.cpp)
TARGET_LINK_LIBRARIES(tstGeometryModuleInterface_DagMC geometry_core geometry_dagmc)
ADD_TEST(GeometryModuleInterface_DagMC_test tstGeometryModuleInterface_DagMC --test_xml_file="${CMAKE_CURRENT_BINARY_DIR}/test_files/test_geom.xml")
