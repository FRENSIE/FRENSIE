ADD_SUBDIRECTORY(test_files)

ADD_EXECUTABLE(tstRoot tstRoot.cpp)
TARGET_LINK_LIBRARIES(tstRoot geometry_core geometry_root ${MPI_CXX_LIBRARIES} ${ROOT})
ADD_TEST(Root_test tstRoot --test_root_file="${CMAKE_CURRENT_BINARY_DIR}/test_files/basic_root_geometry.root")

IF(${FRENSIE_ENABLE_OPENMP})
  ADD_EXECUTABLE(tstSharedParallelRoot tstSharedParallelRoot.cpp)
  TARGET_LINK_LIBRARIES(tstSharedParallelRoot geometry_core geometry_root ${MPI_CXX_LIBRARIES} ${ROOT})
  ADD_TEST(SharedParallelRoot_2_test tstSharedParallelRoot --test_root_file="${CMAKE_CURRENT_BINARY_DIR}/test_files/basic_root_geometry.root" --threads=2)
  ADD_TEST(SharedParallelRoot_4_test tstSharedParallelRoot --test_root_file="${CMAKE_CURRENT_BINARY_DIR}/test_files/basic_root_geometry.root" --threads=4)
ENDIF()

ADD_EXECUTABLE(tstRootInstanceFactoryBasic
  tstRootInstanceFactoryBasic.cpp)
TARGET_LINK_LIBRARIES(tstRootInstanceFactoryBasic geometry_root)
ADD_TEST(RootInstanceFactoryBasic_test tstRootInstanceFactory --test_xml_file="${CMAKE_CURRENT_BINARY_DIR}/test_files/test_geom_basic.xml")

ADD_EXECUTABLE(tstRootInstanceFactoryAdvanced
  tstRootInstanceFactoryAdvanced.cpp)
TARGET_LINK_LIBRARIES(tstRootInstanceFactoryAdvanced geometry_root)
ADD_TEST(RootInstanceFactoryAdvanced_test tstRootInstanceFactory --test_xml_file="${CMAKE_CURRENT_BINARY_DIR}/test_files/test_geom_advanced.xml")

ADD_EXECUTABLE(tstGeometryModuleInterface_Root
  tstModuleInterface.cpp)
TARGET_LINK_LIBRARIES(tstGeometryModuleInterface_Root geometry_core geometry_root ${MPI_CXX_LIBRARIES} ${ROOT})
ADD_TEST(GeometryModuleInterface_Root_test tstGeometryModuleInterface_Root --test_root_file="${CMAKE_CURRENT_BINARY_DIR}/test_files/basic_root_geometry.root")

IF(${FRENSIE_ENABLE_MPI})
  ADD_TEST(DistributedParallelGeometryModuleInterface_Root_2_test 
    ${MPIEXEC} -n 2 tstGeometryModuleInterface_Root --test_root_file="${CMAKE_CURRENT_BINARY_DIR}/test_files/basic_root_geometry.root")
  ADD_TEST(DistributedParallelGeometryModuleInterface_Root_4_test
    ${MPIEXEC} -n 4 tstGeometryModuleInterface_Root --test_root_file="${CMAKE_CURRENT_BINARY_DIR}/test_files/basic_root_geometry.root")
ENDIF()
