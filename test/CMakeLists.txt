ADD_EXECUTABLE(tstAssertion 
  tstAssertion.cpp 
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstAssertion ${PROJECT_NAME})
ADD_TEST(Assertion_test tstAssertion)

ADD_EXECUTABLE(tstContractException 
  tstContractException.cpp
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstContractException ${PROJECT_NAME})
ADD_TEST(ContractException_test tstContractException)

ADD_EXECUTABLE(tstSearchAlgorithms
  tstSearchAlgorithms.cpp
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstSearchAlgorithms ${PROJECT_NAME})
ADD_TEST(SearchAlgorithms_test tstSearchAlgorithms)

ADD_EXECUTABLE(tstExponentiationAlgorithms
  tstExponentiationAlgorithms.cpp
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstExponentiationAlgorithms ${PROJECT_NAME})
ADD_TEST(ExponentiationAlgorithms_test tstExponentiationAlgorithms)

ADD_EXECUTABLE(tstENDLIB97FileHandler
  tstENDLIB97FileHandler.cpp)
TARGET_LINK_LIBRARIES(tstENDLIB97FileHandler ${PROJECT_NAME})
ADD_TEST(ENDLIB97FileHandler_test tstENDLIB97FileHandler --first_header_test_file="${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_first_header.txt" --second_header_test_file="${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_second_header.txt" --full_header_test_file="${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_full_header.txt" --two_column_table_test_file="${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_two_column_table.txt" --three_column_table_test_file="${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_three_column_table.txt" --four_column_table_test_file="${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_four_column_table.txt" --two_two_column_tables_test_file="${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_two_two_column_tables.txt" --two_three_column_tables_test_file="${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_two_three_column_tables.txt" --two_four_column_tables_test_file="${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_two_four_column_tables.txt")

ADD_EXECUTABLE(tstHDF5FileHandler
  tstHDF5FileHandler.cpp
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstHDF5FileHandler ${PROJECT_NAME})
ADD_TEST(HDF5FileHandler_test tstHDF5FileHandler)

ADD_EXECUTABLE(tstDataProcessor
  tstDataProcessor.cpp
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstDataProcessor ${PROJECT_NAME})
ADD_TEST(DataProcessor_test tstDataProcessor)

ADD_EXECUTABLE(tstPhotonDataProcessorShellMap
  tstPhotonDataProcessorShellMap.cpp)
TARGET_LINK_LIBRARIES(tstPhotonDataProcessorShellMap ${PROJECT_NAME})
ADD_TEST(PhotonDataProcessorShellMap_test tstPhotonDataProcessorShellMap --epdl_test_file="${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_epdl_file.txt" --eadl_test_file="${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_eadl_file.txt" --compton_test_file_prefix="${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_compton_profile-")

# ADD_EXECUTABLE(tstPhotonDataProcessor
#   tstPhotonDataProcessor.cpp)
# TARGET_LINK_LIBRARIES(tstPhotonDataProcessor ${PROJECT_NAME})
# ADD_TEST(PhotonDataProcessor_test tstPhotonDataProcessor)

# ADD_EXECUTABLE(tstPhotonDataBasic
#   tstPhotonDataBasic.cpp)
# ADD_EXECUTABLE(tstPhotonDataFluorescence
#   tstPhotonDataFluorescence.cpp)
# ADD_EXECUTABLE(tstPhotonDataDopplerBroadening
#   tstPhotonDataDopplerBroadening.cpp)
# ADD_EXECUTABLE(tstPhotonData
#   tstPhotonData.cpp)

ADD_EXECUTABLE(tstMatrix
  tstMatrix.cpp
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstMatrix ${PROJECT_NAME})
ADD_TEST(Matrix_test tstMatrix)

ADD_EXECUTABLE(tstVector
  tstVector.cpp
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstVector ${PROJECT_NAME})
ADD_TEST(Vector_test tstVector)

ADD_EXECUTABLE(tstVectorHelpers
  tstVectorHelpers.cpp
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstVectorHelpers ${PROJECT_NAME})
ADD_TEST(VectorHelpers_test tstVectorHelpers)

ADD_EXECUTABLE(tstMatrixHelpers
  tstMatrixHelpers.cpp
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstMatrixHelpers ${PROJECT_NAME})
ADD_TEST(MatrixHelpers_test tstMatrixHelpers)

ADD_EXECUTABLE(tstLinearAlgebraAlgorithms
  tstLinearAlgebraAlgorithms.cpp
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstLinearAlgebraAlgorithms ${PROJECT_NAME})
ADD_TEST(LinearAlgebraAlgorithms_test tstLinearAlgebraAlgorithms)

ADD_EXECUTABLE(tstSurface
  tstSurface.cpp
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstSurface ${PROJECT_NAME})
ADD_TEST(Surface_test tstSurface)

ADD_EXECUTABLE(tstSetOperationFunctor
  tstSetOperationFunctor.cpp
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstSetOperationFunctor ${PROJECT_NAME})
ADD_TEST(SetOperationFunctor_test tstSetOperationFunctor)

ADD_EXECUTABLE(tstBooleanCellFunctor
  tstBooleanCellFunctor.cpp
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstBooleanCellFunctor ${PROJECT_NAME})
ADD_TEST(BooleanCellFunctor_test tstBooleanCellFunctor)

ADD_EXECUTABLE(tstCell
  tstCell.cpp
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstCell ${PROJECT_NAME})
ADD_TEST(Cell_test tstCell)

ADD_EXECUTABLE(tstIntersectionPoint
  tstIntersectionPoint.cpp
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstIntersectionPoint ${PROJECT_NAME})
ADD_TEST(IntersectionPoint_test tstIntersectionPoint)

ADD_EXECUTABLE(tstIntersectionPointHelpers
  tstIntersectionPointHelpers.cpp
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstIntersectionPointHelpers ${PROJECT_NAME})
ADD_TEST(IntersectionPointHelpers_test tstIntersectionPointHelpers)

ADD_EXECUTABLE(tstPolygon
  tstPolygon.cpp
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstPolygon ${PROJECT_NAME})
ADD_TEST(Polygon_test tstPolygon)

ADD_EXECUTABLE(tstCellPolygonFactory
  tstCellPolygonFactory.cpp
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstCellPolygonFactory ${PROJECT_NAME})
ADD_TEST(CellPolygonFactory_test tstCellPolygonFactory)

ADD_EXECUTABLE(tstCellFactory
  tstCellFactory.cpp
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstCellFactory ${PROJECT_NAME})
ADD_TEST(CellFactory_test tstCellFactory)

ADD_EXECUTABLE(tstLinearCongruentialGenerator
  tstLinearCongruentialGenerator.cpp
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstLinearCongruentialGenerator ${PROJECT_NAME})
ADD_TEST(LinearCongruentialGenerator_test tstLinearCongruentialGenerator)

ADD_EXECUTABLE(tstFakeGenerator
  tstFakeGenerator.cpp
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstFakeGenerator ${PROJECT_NAME})
ADD_TEST(FakeGenerator_test tstFakeGenerator)

ADD_EXECUTABLE(tstRandomNumberGenerator
  tstRandomNumberGenerator.cpp
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstRandomNumberGenerator ${PROJECT_NAME})
ADD_TEST(RandomNumberGenerator_test tstRandomNumberGenerator)
IF(${FACEMC_ENABLE_MPI})
  ADD_TEST(ParallelRandomNumberGenerator_test 
    mpiexec -n 2 tstRandomNumberGenerator)
ENDIF()

# ADD_EXECUTABLE(tstCellBoundingBox
#   tstCellBoundingBox.cpp
#   ${TEUCHOS_STD_UNIT_TEST_MAIN})
# TARGET_LINK_LIBRARIES(tstCellBoundingBox ${PROJECT_NAME})
# ADD_TEST(CellBoundingBox_test tstCellBoundingBox)

ADD_EXECUTABLE(tstSurfaceInputValidatorHelpers
  tstSurfaceInputValidatorHelpers.cpp
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstSurfaceInputValidatorHelpers ${PROJECT_NAME})
ADD_TEST(SurfaceInputValidatorHelpers_test tstSurfaceInputValidatorHelpers) 

ADD_EXECUTABLE(tstSurfaceInputValidator
  tstSurfaceInputValidator.cpp)
TARGET_LINK_LIBRARIES(tstSurfaceInputValidator ${PROJECT_NAME})
ADD_TEST(SurfaceInputValidator_test tstSurfaceInputValidator --test_xml_file="${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_surfaces.xml")

ADD_EXECUTABLE(tstCellInputValidatorHelpers
  tstCellInputValidatorHelpers.cpp
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstCellInputValidatorHelpers ${PROJECT_NAME})
ADD_TEST(CellInputValidatorHelpers_test tstCellInputValidatorHelpers)

ADD_EXECUTABLE(tstCellInputValidator
  tstCellInputValidator.cpp)
TARGET_LINK_LIBRARIES(tstCellInputValidator ${PROJECT_NAME})
ADD_TEST(CellInputValidator_test tstCellInputValidator --test_xml_file="${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_geom.xml")

ADD_EXECUTABLE(tstParticleState
  tstParticleState.cpp
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstParticleState ${PROJECT_NAME})
ADD_TEST(ParticleState_test tstParticleState)

ADD_EXECUTABLE(tstDagMCHelpers
  tstDagMCHelpers.cpp)
TARGET_LINK_LIBRARIES(tstDagMCHelpers ${PROJECT_NAME})
ADD_TEST(DagMCHelpers_test tstDagMCHelpers --test_sat_file="${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_geom.sat")

ADD_EXECUTABLE(tstGeometryHandlerTraits
  tstGeometryHandlerTraits.cpp)
TARGET_LINK_LIBRARIES(tstGeometryHandlerTraits ${PROJECT_NAME})
ADD_TEST(GeometryHandlerTraits_test tstGeometryHandlerTraits --test_sat_file="${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_geom.sat")

ADD_EXECUTABLE(tstDeltaDistribution
  tstDeltaDistribution.cpp
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstDeltaDistribution ${PROJECT_NAME})
ADD_TEST(DeltaDistribution_test tstDeltaDistribution)

ADD_EXECUTABLE(tstDiscreteDistribution
  tstDiscreteDistribution.cpp
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstDiscreteDistribution ${PROJECT_NAME})
ADD_TEST(DiscreteDistribution_test tstDiscreteDistribution )

ADD_EXECUTABLE(tstUniformDistribution
  tstUniformDistribution.cpp
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstUniformDistribution ${PROJECT_NAME})
ADD_TEST(UniformDistribution_test tstUniformDistribution )

ADD_EXECUTABLE(tstHistogramDistribution
  tstHistogramDistribution.cpp
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstHistogramDistribution ${PROJECT_NAME})
ADD_TEST(HistogramDistribution_test tstHistogramDistribution )

ADD_EXECUTABLE(tstExponentialDistribution
  tstExponentialDistribution.cpp
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstExponentialDistribution ${PROJECT_NAME})
ADD_TEST(ExponentialDistribution_test tstExponentialDistribution)

ADD_EXECUTABLE(tstNormalDistribution
  tstNormalDistribution.cpp
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstNormalDistribution ${PROJECT_NAME})
ADD_TEST(NormalDistribution_test tstNormalDistribution)

ADD_EXECUTABLE(tstPowerDistribution
  tstPowerDistribution.cpp
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstPowerDistribution ${PROJECT_NAME})
ADD_TEST(PowerDistribution_test tstPowerDistribution)

ADD_EXECUTABLE(tstCartesianSpatialDistribution
  tstCartesianSpatialDistribution.cpp
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstCartesianSpatialDistribution ${PROJECT_NAME})
ADD_TEST(CartesianSpatialDistribution_test tstCartesianSpatialDistribution)

ADD_EXECUTABLE(tstSphericalCoordinateHelpers
  tstSphericalCoordinateHelpers.cpp
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstSphericalCoordinateHelpers ${PROJECT_NAME})
ADD_TEST(SphericalCoordinateHelpers_test tstSphericalCoordinateHelpers)

ADD_EXECUTABLE(tstSphericalSpatialDistribution
  tstSphericalSpatialDistribution.cpp
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstSphericalSpatialDistribution ${PROJECT_NAME})
ADD_TEST(SphericalSpatialDistribution_test tstSphericalSpatialDistribution)