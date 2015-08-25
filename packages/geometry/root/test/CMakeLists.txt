ADD_SUBDIRECTORY(test_files)

ADD_EXECUTABLE(tstRootInstanceFactory
  tstRootInstanceFactory.cpp)
TARGET_LINK_LIBRARIES(tstRootInstanceFactory geometry_root)
ADD_TEST(RootInstanceFactory_test tstRootInstanceFactory --test_xml_file="${CMAKE_CURRENT_BINARY_DIR}/test_files/test_geom_parameter_list.xml")

ADD_EXECUTABLE(tstGeometryModuleInterface_Root
  tstModuleInterface.cpp)
TARGET_LINK_LIBRARIES(tstGeometryModuleInterface_Root geometry_core geometry_root ${MPI_CXX_LIBRARIES} ${ROOT})
ADD_TEST(GeometryModuleInterface_Root_test tstGeometryModuleInterface_Root --test_root_file="${CMAKE_CURRENT_SOURCE_DIR}/test_files/Test_Root_Geometry.root")

IF(${FRENSIE_ENABLE_MPI})
  ADD_TEST(DistributedParallelGeometryModuleInterface_Root_2_test 
    ${MPIEXEC} -n 2 tstGeometryModuleInterface_Root --test_root_file="${CMAKE_CURRENT_SOURCE_DIR}/test_files/Test_Root_Geometry.root")
  ADD_TEST(DistributedParallelGeometryModuleInterface_Root_4_test
    ${MPIEXEC} -n 4 tstGeometryModuleInterface_Root --test_root_file="${CMAKE_CURRENT_SOURCE_DIR}/test_files/Test_Root_Geometry.root")
ENDIF()
