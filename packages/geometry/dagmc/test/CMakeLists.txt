# Configure the test files
ADD_SUBDIRECTORY(test_files)

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

ADD_EXECUTABLE(tstDagMCModelPropertiesFactory
  tstDagMCModelPropertiesFactory.cpp
  ${FRENSIE_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstDagMCModelPropertiesFactory geometry_dagmc)
ADD_TEST(DagMCModelPropertiesFactory_test tstDagMCModelPropertiesFactory --test_basic_xml_file="${CMAKE_CURRENT_BINARY_DIR}/test_files/test_geom_basic.xml" --test_advanced_xml_file="${CMAKE_CURRENT_BINARY_DIR}/test_files/test_geom_advanced.xml")
SET_PROPERTY(TEST DagMCModelPropertiesFactory_test PROPERTY LABELS geometry_dagmc dagmc)

ADD_EXECUTABLE(tstDagMCModel
  tstDagMCModel.cpp
  ${FRENSIE_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstDagMCModel geometry_dagmc)
ADD_TEST(DagMCModel_test tstDagMCModel --test_xml_file="${CMAKE_CURRENT_BINARY_DIR}/test_files/test_geom.xml")
SET_PROPERTY(TEST DagMCModel_test PROPERTY LABELS geometry_dagmc dagmc)

ADD_EXECUTABLE(tstDagMCNavigator
  tstDagMCNavigator.cpp
  ${FRENSIE_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstDagMCNavigator geometry_dagmc)
ADD_TEST(DagMCNavigator_test tstDagMCNavigator --test_xml_file="${CMAKE_CURRENT_BINARY_DIR}/test_files/test_geom.xml")
SET_PROPERTY(TEST DagMCNavigator_test PROPERTY LABELS geometry_dagmc dagmc)

IF(${FRENSIE_ENABLE_OPENMP})
  ADD_EXECUTABLE(tstSharedParallelDagMCNavigator
    tstSharedParallelDagMCNavigator.cpp
    ${FRENSIE_STD_UNIT_TEST_MAIN})
  TARGET_LINK_LIBRARIES(tstSharedParallelDagMCNavigator geometry_dagmc)
  ADD_TEST(SharedParallelDagMCNavigator_2_test tstSharedParallelDagMCNavigator --test_xml_file="${CMAKE_CURRENT_BINARY_DIR}/test_files/test_geom.xml" --threads=2)
  ADD_TEST(SharedParallelDagMCNavigator_4_test tstSharedParallelDagMCNavigator --test_xml_file="${CMAKE_CURRENT_BINARY_DIR}/test_files/test_geom.xml" --threads=4)
  SET_PROPERTY(TEST SharedParallelDagMCNavigator_2_test PROPERTY LABELS geometry_dagmc dagmc openmp no_threads)
  SET_PROPERTY(TEST SharedParallelDagMCNavigator_4_test PROPERTY LABELS geometry_dagmc dagmc openmp no_threads)
ENDIF()

