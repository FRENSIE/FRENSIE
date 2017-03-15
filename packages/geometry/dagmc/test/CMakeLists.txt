# Configure the test files
ADD_SUBDIRECTORY(test_files)

ADD_EXECUTABLE(tstDagMCEstimatorType
  tstDagMCEstimatorType.cpp
  ${FRENSIE_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstDagMCEstimatorType geometry_dagmc)
ADD_TEST(DagMCEstimatorType_test tstDagMCEstimatorType)
SET_PROPERTY(TEST DagMCEstimatorType_test PROPERTY LABELS geometry_dagmc dagmc)

ADD_EXECUTABLE(tstDagMCRay
  tstDagMCRay.cpp
  ${FRENSIE_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstDagMCRay geometry_dagmc)
ADD_TEST(DagMCRay_test tstDagMCRay)
SET_PROPERTY(TEST DagMCRay_test PROPERTY LABELS geometry_dagmc dagmc)

ADD_EXECUTABLE(tstStandardDagMCCellHandler
  tstStandardDagMCCellHandler.cpp
  ${FRENSIE_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstStandardDagMCCellHandler geometry_dagmc)
ADD_TEST(StandardDagMCCellHandler_test tstStandardDagMCCellHandler --test_cad_file="${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_geom.sat")
SET_PROPERTY(TEST StandardDagMCCellHandler_test PROPERTY LABELS geometry_dagmc dagmc)

ADD_EXECUTABLE(tstFastDagMCCellHandler
  tstFastDagMCCellHandler.cpp
  ${FRENSIE_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstFastDagMCCellHandler geometry_dagmc)
ADD_TEST(FastDagMCCellHandler_test tstFastDagMCCellHandler --test_cad_file="${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_geom.sat")
SET_PROPERTY(TEST FastDagMCCellHandler_test PROPERTY LABELS geometry_dagmc dagmc)

ADD_EXECUTABLE(tstStandardDagMCSurfaceHandler
  tstStandardDagMCSurfaceHandler.cpp
  ${FRENSIE_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstStandardDagMCSurfaceHandler geometry_dagmc)
ADD_TEST(StandardDagMCSurfaceHandler_test tstStandardDagMCSurfaceHandler --test_cad_file="${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_geom.sat")
SET_PROPERTY(TEST StandardDagMCSurfaceHandler_test PROPERTY LABELS geometry_dagmc dagmc)

ADD_EXECUTABLE(tstFastDagMCSurfaceHandler
  tstFastDagMCSurfaceHandler.cpp
  ${FRENSIE_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstFastDagMCSurfaceHandler geometry_dagmc)
ADD_TEST(FastDagMCSurfaceHandler_test tstFastDagMCSurfaceHandler --test_cad_file="${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_geom.sat")
SET_PROPERTY(TEST FastDagMCSurfaceHandler_test PROPERTY LABELS geometry_dagmc dagmc)

ADD_EXECUTABLE(tstDagMCModelProperties
  tstDagMCModelProperties.cpp
  ${FRENSIE_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstDagMCModelProperties geometry_dagmc)
ADD_TEST(DagMCModelProperties_test tstDagMCModelProperties)
SET_PROPERTY(TEST DagMCModelProperties_test PROPERTY LABELS geometry_dagmc dagmc)

# ADD_EXECUTABLE(tstDagMCModel tstDagMCModel.cpp)
# TARGET_LINK_LIBRARIES(tstDagMCModel geometry_dagmc)
# ADD_TEST(DagMCModel_test tstDagMCModel --test_cad_file="${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_geom.sat")
# SET_PROPERTY(TEST DagMCModel_test PROPERTY LABELS geometry_dagmc dagmc)

# IF(${FRENSIE_ENABLE_OPENMP})
#   ADD_EXECUTABLE(tstSharedParallelDagMC tstSharedParallelDagMC.cpp)
#   TARGET_LINK_LIBRARIES(tstSharedParallelDagMC geometry_dagmc)
#   ADD_TEST(SharedParallelDagMC_2_test tstSharedParallelDagMC --test_cad_file="${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_geom.sat" --threads=2)
#   ADD_TEST(SharedParallelDagMC_4_test tstSharedParallelDagMC --test_cad_file="${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_geom.sat" --threads=4)
#   SET_PROPERTY(TEST SharedParallelDagMC_2_test PROPERTY LABELS geometry_dagmc dagmc openmp no_threads)
#   SET_PROPERTY(TEST SharedParallelDagMC_4_test PROPERTY LABELS geometry_dagmc dagmc openmp no_threads)
# ENDIF()

# ADD_EXECUTABLE(tstDagMCInstanceFactoryBasic
#   tstDagMCInstanceFactoryBasic.cpp)
# TARGET_LINK_LIBRARIES(tstDagMCInstanceFactoryBasic geometry_dagmc)
# ADD_TEST(DagMCInstanceFactoryBasic_test tstDagMCInstanceFactoryBasic --test_xml_file="${CMAKE_CURRENT_BINARY_DIR}/test_files/test_geom_basic.xml")
# SET_PROPERTY(TEST DagMCInstanceFactoryBasic_test PROPERTY LABELS geometry_dagmc dagmc)

# ADD_EXECUTABLE(tstDagMCInstanceFactoryAdvanced
#   tstDagMCInstanceFactoryAdvanced.cpp)
# TARGET_LINK_LIBRARIES(tstDagMCInstanceFactoryAdvanced geometry_dagmc)
# ADD_TEST(DagMCInstanceFactoryAdvanced_test tstDagMCInstanceFactoryAdvanced --test_xml_file="${CMAKE_CURRENT_BINARY_DIR}/test_files/test_geom_advanced.xml")
# SET_PROPERTY(TEST DagMCInstanceFactoryAdvanced_test PROPERTY LABELS geometry_dagmc dagmc)

# ADD_EXECUTABLE(tstGeometryModuleInterface_DagMC
#   tstModuleInterface.cpp)
# TARGET_LINK_LIBRARIES(tstGeometryModuleInterface_DagMC geometry_dagmc)
# ADD_TEST(GeometryModuleInterface_DagMC_test tstGeometryModuleInterface_DagMC --test_xml_file="${CMAKE_CURRENT_BINARY_DIR}/test_files/test_geom_advanced.xml")
# SET_PROPERTY(TEST GeometryModuleInterface_DagMC_test PROPERTY LABELS geometry_dagmc dagmc)

# IF(${FRENSIE_ENABLE_OPENMP})
#   ADD_EXECUTABLE(tstSharedParallelGeometryModuleInterface_DagMC
#   tstSharedParallelModuleInterface.cpp)
#   TARGET_LINK_LIBRARIES(tstSharedParallelGeometryModuleInterface_DagMC geometry_dagmc)
#   ADD_TEST(SharedParallelGeometryModuleInterface_DagMC_2_test tstSharedParallelGeometryModuleInterface_DagMC --test_xml_file="${CMAKE_CURRENT_BINARY_DIR}/test_files/test_geom_advanced.xml" --threads=2)
#   ADD_TEST(SharedParallelGeometryModuleInterface_DagMC_4_test tstSharedParallelGeometryModuleInterface_DagMC --test_xml_file="${CMAKE_CURRENT_BINARY_DIR}/test_files/test_geom_advanced.xml" --threads=4)
#   SET_PROPERTY(TEST SharedParallelGeometryModuleInterface_DagMC_2_test PROPERTY LABELS geometry_dagmc dagmc openmp no_threads)
#   SET_PROPERTY(TEST SharedParallelGeometryModuleInterface_DagMC_4_test PROPERTY LABELS geometry_dagmc dagmc openmp no_threads)
# ENDIF()

