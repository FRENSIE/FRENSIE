ADD_SUBDIRECTORY(test_files)

ADD_EXECUTABLE(tstRoot tstRoot.cpp)
TARGET_LINK_LIBRARIES(tstRoot geometry_root)
ADD_TEST(Root_test tstRoot --test_root_file="${CMAKE_CURRENT_BINARY_DIR}/test_files/basic_root_geometry.root")

IF(${FRENSIE_ENABLE_OPENMP})
  ADD_EXECUTABLE(tstSharedParallelRoot tstSharedParallelRoot.cpp)
  TARGET_LINK_LIBRARIES(tstSharedParallelRoot geometry_root)
  ADD_TEST(SharedParallelRoot_2_test tstSharedParallelRoot --test_root_file="${CMAKE_CURRENT_BINARY_DIR}/test_files/basic_root_geometry.root" --threads=2)
  ADD_TEST(SharedParallelRoot_4_test tstSharedParallelRoot --test_root_file="${CMAKE_CURRENT_BINARY_DIR}/test_files/basic_root_geometry.root" --threads=4)
ENDIF()

ADD_EXECUTABLE(tstRootInstanceFactoryBasic
  tstRootInstanceFactoryBasic.cpp)
TARGET_LINK_LIBRARIES(tstRootInstanceFactoryBasic geometry_root)
ADD_TEST(RootInstanceFactoryBasic_test tstRootInstanceFactoryBasic --test_xml_file="${CMAKE_CURRENT_BINARY_DIR}/test_files/test_geom_basic.xml")

ADD_EXECUTABLE(tstRootInstanceFactoryAdvanced
  tstRootInstanceFactoryAdvanced.cpp)
TARGET_LINK_LIBRARIES(tstRootInstanceFactoryAdvanced geometry_root)
ADD_TEST(RootInstanceFactoryAdvanced_test tstRootInstanceFactoryAdvanced --test_xml_file="${CMAKE_CURRENT_BINARY_DIR}/test_files/test_geom_advanced.xml")

ADD_EXECUTABLE(tstGeometryModuleInterface_Root
  tstModuleInterface.cpp)
TARGET_LINK_LIBRARIES(tstGeometryModuleInterface_Root geometry_root)
ADD_TEST(GeometryModuleInterface_Root_test tstGeometryModuleInterface_Root --test_xml_file="${CMAKE_CURRENT_BINARY_DIR}/test_files/test_geom_basic.xml")

IF(${FRENSIE_ENABLE_OPENMP})
  ADD_EXECUTABLE(tstSharedParallelGeometryModuleInterface_Root tstSharedParallelModuleInterface.cpp)
  TARGET_LINK_LIBRARIES(tstSharedParallelGeometryModuleInterface_Root geometry_root)
  ADD_TEST(SharedParallelGeometryModuleInterface_Root_2_test tstSharedParallelGeometryModuleInterface_Root --test_xml_file="${CMAKE_CURRENT_BINARY_DIR}/test_files/test_geom_basic.xml" --threads=2)
  ADD_TEST(SharedParallelGeometryModuleInterface_Root_4_test tstSharedParallelGeometryModuleInterface_Root --test_xml_file="${CMAKE_CURRENT_BINARY_DIR}/test_files/test_geom_basic.xml" --threads=4)
ENDIF()
