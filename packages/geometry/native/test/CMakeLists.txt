 ADD_EXECUTABLE(tstMatrix
  tstMatrix.cpp
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstMatrix geometrycore geometrynative)
ADD_TEST(Matrix_test tstMatrix)

ADD_EXECUTABLE(tstVector
  tstVector.cpp
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstVector geometrycore geometrynative)
ADD_TEST(Vector_test tstVector)

ADD_EXECUTABLE(tstVectorHelpers
  tstVectorHelpers.cpp
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstVectorHelpers geometrycore geometrynative)
ADD_TEST(VectorHelpers_test tstVectorHelpers)

ADD_EXECUTABLE(tstMatrixHelpers
  tstMatrixHelpers.cpp
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstMatrixHelpers geometrycore geometrynative)
ADD_TEST(MatrixHelpers_test tstMatrixHelpers)

ADD_EXECUTABLE(tstLinearAlgebraAlgorithms
  tstLinearAlgebraAlgorithms.cpp
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstLinearAlgebraAlgorithms geometrycore geometrynative)
ADD_TEST(LinearAlgebraAlgorithms_test tstLinearAlgebraAlgorithms)

ADD_EXECUTABLE(tstSurface
  tstSurface.cpp
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstSurface geometrycore geometrynative)
ADD_TEST(Surface_test tstSurface)

ADD_EXECUTABLE(tstBooleanCellFunctor
  tstBooleanCellFunctor.cpp
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstBooleanCellFunctor geometrycore geometrynative)
ADD_TEST(BooleanCellFunctor_test tstBooleanCellFunctor)

ADD_EXECUTABLE(tstCell
  tstCell.cpp
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstCell geometrycore geometrynative)
ADD_TEST(Cell_test tstCell)

ADD_EXECUTABLE(tstIntersectionPoint
  tstIntersectionPoint.cpp
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstIntersectionPoint geometrycore geometrynative)
ADD_TEST(IntersectionPoint_test tstIntersectionPoint)

ADD_EXECUTABLE(tstIntersectionPointHelpers
  tstIntersectionPointHelpers.cpp
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstIntersectionPointHelpers geometrycore geometrynative)
ADD_TEST(IntersectionPointHelpers_test tstIntersectionPointHelpers)

ADD_EXECUTABLE(tstPolygon
  tstPolygon.cpp
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstPolygon geometrycore geometrynative)
ADD_TEST(Polygon_test tstPolygon)

ADD_EXECUTABLE(tstCellPolygonFactory
  tstCellPolygonFactory.cpp
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstCellPolygonFactory geometrycore geometrynative)
ADD_TEST(CellPolygonFactory_test tstCellPolygonFactory)

ADD_EXECUTABLE(tstCellFactory
  tstCellFactory.cpp
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstCellFactory geometrycore geometrynative)
ADD_TEST(CellFactory_test tstCellFactory)

# ADD_EXECUTABLE(tstCellBoundingBox
#   tstCellBoundingBox.cpp
#   ${TEUCHOS_STD_UNIT_TEST_MAIN})
# TARGET_LINK_LIBRARIES(tstCellBoundingBox geometrycore geometrynative)
# ADD_TEST(CellBoundingBox_test tstCellBoundingBox)

ADD_EXECUTABLE(tstSurfaceInputValidatorHelpers
  tstSurfaceInputValidatorHelpers.cpp
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstSurfaceInputValidatorHelpers geometrycore geometrynative)
ADD_TEST(SurfaceInputValidatorHelpers_test tstSurfaceInputValidatorHelpers) 

ADD_EXECUTABLE(tstSurfaceInputValidator
  tstSurfaceInputValidator.cpp)
TARGET_LINK_LIBRARIES(tstSurfaceInputValidator geometrycore geometrynative)
ADD_TEST(SurfaceInputValidator_test tstSurfaceInputValidator --test_xml_file="${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_surfaces.xml")

ADD_EXECUTABLE(tstCellInputValidatorHelpers
  tstCellInputValidatorHelpers.cpp
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstCellInputValidatorHelpers geometrycore geometrynative)
ADD_TEST(CellInputValidatorHelpers_test tstCellInputValidatorHelpers)

ADD_EXECUTABLE(tstCellInputValidator
  tstCellInputValidator.cpp)
TARGET_LINK_LIBRARIES(tstCellInputValidator geometrycore geometrynative)
ADD_TEST(CellInputValidator_test tstCellInputValidator --test_xml_file="${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_geom.xml")