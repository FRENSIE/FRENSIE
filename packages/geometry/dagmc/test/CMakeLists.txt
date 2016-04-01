ADD_SUBDIRECTORY(test_files)

ADD_EXECUTABLE(tstDagMCRay 
  tstDagMCRay.cpp
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstDagMCRay geometry_dagmc)
ADD_TEST(DagMCRay_test tstDagMCRay)

ADD_EXECUTABLE(tstStandardDagMCCellHandler tstStandardDagMCCellHandler.cpp)
TARGET_LINK_LIBRARIES(tstStandardDagMCCellHandler geometry_dagmc)
ADD_TEST(StandardDagMCCellHandler_test tstStandardDagMCCellHandler --test_cad_file="${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_geom.sat")

ADD_EXECUTABLE(tstFastDagMCCellHandler tstFastDagMCCellHandler.cpp)
TARGET_LINK_LIBRARIES(tstFastDagMCCellHandler geometry_dagmc)
ADD_TEST(FastDagMCCellHandler_test tstFastDagMCCellHandler --test_cad_file="${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_geom.sat")

ADD_EXECUTABLE(tstStandardDagMCSurfaceHandler tstStandardDagMCSurfaceHandler.cpp)
TARGET_LINK_LIBRARIES(tstStandardDagMCSurfaceHandler geometry_dagmc)
ADD_TEST(StandardDagMCSurfaceHandler_test tstStandardDagMCSurfaceHandler --test_cad_file="${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_geom.sat")

ADD_EXECUTABLE(tstFastDagMCSurfaceHandler tstFastDagMCSurfaceHandler.cpp)
TARGET_LINK_LIBRARIES(tstFastDagMCSurfaceHandler geometry_dagmc)
ADD_TEST(FastDagMCSurfaceHandler_test tstFastDagMCSurfaceHandler --test_cad_file="${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_geom.sat")

ADD_EXECUTABLE(tstDagMC tstDagMC.cpp)
TARGET_LINK_LIBRARIES(tstDagMC geometry_dagmc)
ADD_TEST(DagMC_test tstDagMC --test_cad_file="${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_geom.sat")

IF(${FRENSIE_ENABLE_OPENMP})
  ADD_EXECUTABLE(tstSharedParallelDagMC tstSharedParallelDagMC.cpp)
  TARGET_LINK_LIBRARIES(tstSharedParallelDagMC geometry_dagmc)
  ADD_TEST(SharedParallelDagMC_2_test tstSharedParallelDagMC --test_cad_file="${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_geom.sat" --threads=2)
  ADD_TEST(SharedParallelDagMC_4_test tstSharedParallelDagMC --test_cad_file="${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_geom.sat" --threads=4)
ENDIF()

ADD_EXECUTABLE(tstDagMCInstanceFactoryBasic
  tstDagMCInstanceFactoryBasic.cpp)
TARGET_LINK_LIBRARIES(tstDagMCInstanceFactoryBasic geometry_dagmc)
ADD_TEST(DagMCInstanceFactoryBasic_test tstDagMCInstanceFactoryBasic --test_xml_file="${CMAKE_CURRENT_BINARY_DIR}/test_files/test_geom_basic.xml")

ADD_EXECUTABLE(tstDagMCInstanceFactoryAdvanced
  tstDagMCInstanceFactoryAdvanced.cpp)
TARGET_LINK_LIBRARIES(tstDagMCInstanceFactoryAdvanced geometry_dagmc)
ADD_TEST(DagMCInstanceFactoryAdvanced_test tstDagMCInstanceFactoryAdvanced --test_xml_file="${CMAKE_CURRENT_BINARY_DIR}/test_files/test_geom_advanced.xml")

ADD_EXECUTABLE(tstGeometryModuleInterface_DagMC
  tstModuleInterface.cpp)
TARGET_LINK_LIBRARIES(tstGeometryModuleInterface_DagMC geometry_dagmc)
ADD_TEST(GeometryModuleInterface_DagMC_test tstGeometryModuleInterface_DagMC --test_xml_file="${CMAKE_CURRENT_BINARY_DIR}/test_files/test_geom_advanced.xml")

IF(${FRENSIE_ENABLE_OPENMP})
  ADD_EXECUTABLE(tstSharedParallelGeometryModuleInterface_DagMC
  tstSharedParallelModuleInterface.cpp)
  TARGET_LINK_LIBRARIES(tstSharedParallelGeometryModuleInterface_DagMC geometry_dagmc)
  ADD_TEST(SharedParallelGeometryModuleInterface_DagMC_2_test tstSharedParallelGeometryModuleInterface_DagMC --test_xml_file="${CMAKE_CURRENT_BINARY_DIR}/test_files/test_geom_advanced.xml" --threads=2)
  ADD_TEST(SharedParallelGeometryModuleInterface_DagMC_4_test tstSharedParallelGeometryModuleInterface_DagMC --test_xml_file="${CMAKE_CURRENT_BINARY_DIR}/test_files/test_geom_advanced.xml" --threads=4)
ENDIF()
