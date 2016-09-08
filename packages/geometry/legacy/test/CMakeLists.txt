 ADD_EXECUTABLE(tstMatrix
  tstMatrix.cpp
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstMatrix geometry_core geometry_native)
ADD_TEST(Matrix_test tstMatrix)
SET_PROPERTY(TEST Matrix_test PROPERTY LABELS geometry_native)

ADD_EXECUTABLE(tstVector
  tstVector.cpp
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstVector geometry_core geometry_native)
ADD_TEST(Vector_test tstVector)
SET_PROPERTY(TEST Vector_test PROPERTY LABELS geometry_native)

ADD_EXECUTABLE(tstVectorHelpers
  tstVectorHelpers.cpp
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstVectorHelpers geometry_core geometry_native)
ADD_TEST(VectorHelpers_test tstVectorHelpers)
SET_PROPERTY(TEST VectorHelpers_test PROPERTY LABELS geometry_native)

ADD_EXECUTABLE(tstMatrixHelpers
  tstMatrixHelpers.cpp
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstMatrixHelpers geometry_core geometry_native)
ADD_TEST(MatrixHelpers_test tstMatrixHelpers)
SET_PROPERTY(TEST MatrixHelpers_test PROPERTY LABELS geometry_native)

ADD_EXECUTABLE(tstLinearAlgebraAlgorithms
  tstLinearAlgebraAlgorithms.cpp
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstLinearAlgebraAlgorithms geometry_core geometry_native)
ADD_TEST(LinearAlgebraAlgorithms_test tstLinearAlgebraAlgorithms)
SET_PROPERTY(TEST LinearAlgebraAlgorithms_test PROPERTY LABELS geometry_native)

ADD_EXECUTABLE(tstSurface
  tstSurface.cpp
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstSurface geometry_core geometry_native)
ADD_TEST(Surface_test tstSurface)
SET_PROPERTY(TEST Surface_test PROPERTY LABELS geometry_native)

ADD_EXECUTABLE(tstBooleanCellFunctor
  tstBooleanCellFunctor.cpp
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstBooleanCellFunctor geometry_core geometry_native)
ADD_TEST(BooleanCellFunctor_test tstBooleanCellFunctor)
SET_PROPERTY(TEST BooleanCellFunctor_test PROPERTY LABELS geometry_native)

ADD_EXECUTABLE(tstCell
  tstCell.cpp
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstCell geometry_core geometry_native)
ADD_TEST(Cell_test tstCell)
SET_PROPERTY(TEST Cell_test PROPERTY LABELS geometry_native)

ADD_EXECUTABLE(tstIntersectionPoint
  tstIntersectionPoint.cpp
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstIntersectionPoint geometry_core geometry_native)
ADD_TEST(IntersectionPoint_test tstIntersectionPoint)
SET_PROPERTY(TEST IntersectionPoint_test PROPERTY LABELS geometry_native)

ADD_EXECUTABLE(tstIntersectionPointHelpers
  tstIntersectionPointHelpers.cpp
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstIntersectionPointHelpers geometry_core geometry_native)
ADD_TEST(IntersectionPointHelpers_test tstIntersectionPointHelpers)
SET_PROPERTY(TEST IntersectionPointHelpers_test PROPERTY LABELS geometry_native)

ADD_EXECUTABLE(tstPolygon
  tstPolygon.cpp
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstPolygon geometry_core geometry_native)
ADD_TEST(Polygon_test tstPolygon)
SET_PROPERTY(TEST Polygon_test PROPERTY LABELS geometry_native)

ADD_EXECUTABLE(tstCellPolygonFactory
  tstCellPolygonFactory.cpp
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstCellPolygonFactory geometry_core geometry_native)
ADD_TEST(CellPolygonFactory_test tstCellPolygonFactory)
SET_PROPERTY(TEST CellPolygonFactory_test PROPERTY LABELS geometry_native)

ADD_EXECUTABLE(tstCellFactory
  tstCellFactory.cpp
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstCellFactory geometry_core geometry_native)
ADD_TEST(CellFactory_test tstCellFactory)
SET_PROPERTY(TEST CellFactory_test PROPERTY LABELS geometry_native)

# ADD_EXECUTABLE(tstCellBoundingBox
#   tstCellBoundingBox.cpp
#   ${TEUCHOS_STD_UNIT_TEST_MAIN})
# TARGET_LINK_LIBRARIES(tstCellBoundingBox geometry_core geometry_native)
# ADD_TEST(CellBoundingBox_test tstCellBoundingBox)
# SET_PROPERTY(TEST CellBoundingBox_test PROPERTY LABELS geometry_native)

ADD_EXECUTABLE(tstSurfaceInputValidatorHelpers
  tstSurfaceInputValidatorHelpers.cpp
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstSurfaceInputValidatorHelpers geometry_core geometry_native)
ADD_TEST(SurfaceInputValidatorHelpers_test tstSurfaceInputValidatorHelpers)
SET_PROPERTY(TEST SurfaceInputValidatorHelpers_test PROPERTY LABELS geometry_native)

ADD_EXECUTABLE(tstSurfaceInputValidator
  tstSurfaceInputValidator.cpp)
TARGET_LINK_LIBRARIES(tstSurfaceInputValidator geometry_core geometry_native)
ADD_TEST(SurfaceInputValidator_test tstSurfaceInputValidator --test_xml_file="${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_surfaces.xml")
SET_PROPERTY(TEST SurfaceInputValidator_test PROPERTY LABELS geometry_native)

ADD_EXECUTABLE(tstCellInputValidatorHelpers
  tstCellInputValidatorHelpers.cpp
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstCellInputValidatorHelpers geometry_core geometry_native)
ADD_TEST(CellInputValidatorHelpers_test tstCellInputValidatorHelpers)
SET_PROPERTY(TEST CellInputValidatorHelpers_test PROPERTY LABELS geometry_native)

ADD_EXECUTABLE(tstCellInputValidator
  tstCellInputValidator.cpp)
TARGET_LINK_LIBRARIES(tstCellInputValidator geometry_core geometry_native)
ADD_TEST(CellInputValidator_test tstCellInputValidator --test_xml_file="${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_geom.xml")
SET_PROPERTY(TEST CellInputValidator_test PROPERTY LABELS geometry_native)
