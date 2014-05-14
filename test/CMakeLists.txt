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

ADD_EXECUTABLE(tstSortAlgorithms
  tstSortAlgorithms.cpp
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstSortAlgorithms ${PROJECT_NAME})
ADD_TEST(SortAlgorithms_test tstSortAlgorithms)

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

ADD_EXECUTABLE(tstInterpolationPolicy
  tstInterpolationPolicy.cpp
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstInterpolationPolicy ${PROJECT_NAME})
ADD_TEST(InterpolationPolicy_test tstInterpolationPolicy)

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

ADD_EXECUTABLE(tstDirectionHelpers
  tstDirectionHelpers.cpp
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstDirectionHelpers ${PROJECT_NAME})
ADD_TEST(DirectionHelpers_test tstDirectionHelpers)

ADD_EXECUTABLE(tstParticleStateCore
  tstParticleStateCore.cpp
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstParticleStateCore ${PROJECT_NAME})
ADD_TEST(ParticleStateCore_test tstParticleStateCore)

ADD_EXECUTABLE(tstParticleState
  tstParticleState.cpp
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstParticleState ${PROJECT_NAME})
ADD_TEST(ParticleState_test tstParticleState)

ADD_EXECUTABLE(tstPhotonState
  tstPhotonState.cpp
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstPhotonState ${PROJECT_NAME})
ADD_TEST(PhotonState_test tstPhotonState)

ADD_EXECUTABLE(tstNeutronState
  tstNeutronState.cpp
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstNeutronState ${PROJECT_NAME})
ADD_TEST(NeutronState_test tstNeutronState)

ADD_EXECUTABLE(tstParticleBank
  tstParticleBank.cpp
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstParticleBank ${PROJECT_NAME})
ADD_TEST(ParticleBank_test tstParticleBank)

ADD_EXECUTABLE(tstDagMCHelpers
  tstDagMCHelpers.cpp)
TARGET_LINK_LIBRARIES(tstDagMCHelpers ${PROJECT_NAME})
ADD_TEST(DagMCHelpers_test tstDagMCHelpers --test_sat_file="${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_geom.sat")

ADD_EXECUTABLE(tstGeometryModuleInterface
  tstGeometryModuleInterface.cpp)
TARGET_LINK_LIBRARIES(tstGeometryModuleInterface ${PROJECT_NAME})
ADD_TEST(GeometryModuleInterface_test tstGeometryModuleInterface --test_sat_file="${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_geom.sat")

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

ADD_EXECUTABLE(tstTabularDistribution
  tstTabularDistribution.cpp
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstTabularDistribution ${PROJECT_NAME})
ADD_TEST(TabularDistribution_test tstTabularDistribution)

ADD_EXECUTABLE(tstThirtyTwoEquiprobableBinDistribution
  tstThirtyTwoEquiprobableBinDistribution.cpp
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstThirtyTwoEquiprobableBinDistribution ${PROJECT_NAME})
ADD_TEST(32EquiprobableBinDistribution_test tstThirtyTwoEquiprobableBinDistribution)

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

ADD_EXECUTABLE(tstCylindricalCoordinateHelpers
  tstCylindricalCoordinateHelpers.cpp
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstCylindricalCoordinateHelpers ${PROJECT_NAME})
ADD_TEST(CylindricalCoordinateHelpers_test tstCylindricalCoordinateHelpers)

ADD_EXECUTABLE(tstCylindricalSpatialDistribution
  tstCylindricalSpatialDistribution.cpp
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstCylindricalSpatialDistribution ${PROJECT_NAME})
ADD_TEST(CylindricalSpatialDistribution_test tstCylindricalSpatialDistribution)

ADD_EXECUTABLE(tstDirectionalDistribution
  tstDirectionalDistribution.cpp
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstDirectionalDistribution ${PROJECT_NAME})
ADD_TEST(DirectionalDistribution_test tstDirectionalDistribution)

ADD_EXECUTABLE(tstStateSource
  tstStateSource.cpp
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstStateSource ${PROJECT_NAME})
ADD_TEST(StateSource_test tstStateSource)

ADD_EXECUTABLE(tstDistributedSource
  tstDistributedSource.cpp)
TARGET_LINK_LIBRARIES(tstDistributedSource ${PROJECT_NAME})
ADD_TEST(DistributedSource_test tstDistributedSource --test_sat_file="${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_source_geom.sat")

ADD_EXECUTABLE(tstCompoundSource
  tstCompoundSource.cpp)
TARGET_LINK_LIBRARIES(tstCompoundSource ${PROJECT_NAME})
ADD_TEST(CompoundSource_test tstCompoundSource --test_sat_file="${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_source_geom.sat")

ADD_EXECUTABLE(tstResponseFunction
  tstResponseFunction.cpp
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstResponseFunction ${PROJECT_NAME})
ADD_TEST(ResponseFunction_test tstResponseFunction)

ADD_EXECUTABLE(tstEnergySpaceResponseFunction
  tstEnergySpaceResponseFunction.cpp
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstEnergySpaceResponseFunction ${PROJECT_NAME})
ADD_TEST(EnergySpaceResponseFunction_test tstEnergySpaceResponseFunction)

ADD_EXECUTABLE(tstPhaseSpaceResponseFunction
  tstPhaseSpaceResponseFunction.cpp
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstPhaseSpaceResponseFunction ${PROJECT_NAME})
ADD_TEST(PhaseSpaceResponseFunction_test tstPhaseSpaceResponseFunction)

ADD_EXECUTABLE(tstGeneralEstimatorDimensionDiscretization
  tstGeneralEstimatorDimensionDiscretization.cpp
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstGeneralEstimatorDimensionDiscretization ${PROJECT_NAME})
ADD_TEST(GeneralEstimatorDimensionDiscretization_test tstGeneralEstimatorDimensionDiscretization)

ADD_EXECUTABLE(tstEstimator
  tstEstimator.cpp
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstEstimator ${PROJECT_NAME})
ADD_TEST(Estimator_test tstEstimator)

Add_EXECUTABLE(tstEntityEstimator
  tstEntityEstimator.cpp
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstEntityEstimator ${PROJECT_NAME})
ADD_TEST(EntityEstimator_test tstEntityEstimator)

Add_EXECUTABLE(tstStandardEntityEstimator
  tstStandardEntityEstimator.cpp
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstStandardEntityEstimator ${PROJECT_NAME})
ADD_TEST(StandardEntityEstimator_test tstStandardEntityEstimator)

Add_EXECUTABLE(tstStandardSurfaceEstimator
  tstStandardSurfaceEstimator.cpp
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstStandardSurfaceEstimator ${PROJECT_NAME})
ADD_TEST(StandardSurfaceEstimator_test tstStandardSurfaceEstimator)

Add_EXECUTABLE(tstSurfaceFluxEstimator
  tstSurfaceFluxEstimator.cpp
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstSurfaceFluxEstimator ${PROJECT_NAME})
ADD_TEST(SurfaceFluxEstimator_test tstSurfaceFluxEstimator)

Add_EXECUTABLE(tstSurfaceCurrentEstimator
  tstSurfaceCurrentEstimator.cpp
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstSurfaceCurrentEstimator ${PROJECT_NAME})
ADD_TEST(SurfaceCurrentEstimator_test tstSurfaceCurrentEstimator)

Add_EXECUTABLE(tstCellPulseHeightEstimator
  tstCellPulseHeightEstimator.cpp
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstCellPulseHeightEstimator ${PROJECT_NAME})
ADD_TEST(CellPulseHeightEstimator_test tstCellPulseHeightEstimator)

Add_EXECUTABLE(tstStandardCellEstimator
  tstStandardCellEstimator.cpp
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstStandardCellEstimator ${PROJECT_NAME})
ADD_TEST(StandardCellEstimator_test tstStandardCellEstimator)

Add_EXECUTABLE(tstCellCollisionFluxEstimator
  tstCellCollisionFluxEstimator.cpp
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstCellCollisionFluxEstimator ${PROJECT_NAME})
ADD_TEST(CellCollisionFluxEstimator_test tstCellCollisionFluxEstimator)

Add_EXECUTABLE(tstCellTrackLengthFluxEstimator
  tstCellTrackLengthFluxEstimator.cpp
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstCellTrackLengthFluxEstimator ${PROJECT_NAME})
ADD_TEST(CellTrackLengthFluxEstimator_test tstCellTrackLengthFluxEstimator)

ADD_EXECUTABLE(tstACEFileHandler
  tstACEFileHandler.cpp)
TARGET_LINK_LIBRARIES(tstACEFileHandler ${PROJECT_NAME})
ADD_TEST(ACEFileHandler_test tstACEFileHandler --test_ace_file="${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_h1_ace_file.txt")

ADD_EXECUTABLE(tstXSSNeutronDataExtractor
  tstXSSNeutronDataExtractor.cpp)
TARGET_LINK_LIBRARIES(tstXSSNeutronDataExtractor ${PROJECT_NAME})
ADD_TEST(XSSNeutronDataExtractor_test tstXSSNeutronDataExtractor --test_basic_ace_file="${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_h1_ace_file.txt" --test_basic_ace_table="1001.70c")

ADD_EXECUTABLE(tstNeutronScatteringDistribution
  tstNeutronScatteringDistribution.cpp
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstNeutronScatteringDistribution ${PROJECT_NAME})
ADD_TEST(NeutronScatteringDistribution_test tstNeutronScatteringDistribution)

ADD_EXECUTABLE(tstElasticNeutronScatteringDistribution
  tstElasticNeutronScatteringDistribution.cpp
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstElasticNeutronScatteringDistribution ${PROJECT_NAME})
ADD_TEST(ElasticNeutronScatteringDistribution_test tstElasticNeutronScatteringDistribution)

ADD_EXECUTABLE(tstNeutronScatteringDistributionFactory
  tstNeutronScatteringDistributionFactory.cpp)
TARGET_LINK_LIBRARIES(tstNeutronScatteringDistributionFactory ${PROJECT_NAME})
ADD_TEST(NeutronScatteringDistributionFactory_test tstNeutronScatteringDistributionFactory --test_basic_ace_file="${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_h1_ace_file.txt" --test_basic_ace_table="1001.70c")

ADD_EXECUTABLE(tstNuclearReaction
  tstNuclearReaction.cpp)
TARGET_LINK_LIBRARIES(tstNuclearReaction ${PROJECT_NAME})
ADD_TEST(NuclearReaction_test tstNuclearReaction --test_basic_ace_file="${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_h1_ace_file.txt" --test_basic_ace_table="1001.70c")

ADD_EXECUTABLE(tstNeutronScatteringReaction
  tstNeutronScatteringReaction.cpp)
TARGET_LINK_LIBRARIES(tstNeutronScatteringReaction ${PROJECT_NAME})
ADD_TEST(NeutronScatteringReaction_test tstNeutronScatteringReaction --test_basic_ace_file="${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_h1_ace_file.txt" --test_basic_ace_table="1001.70c")

ADD_EXECUTABLE(tstNeutronAbsorptionReaction
  tstNeutronAbsorptionReaction.cpp)
TARGET_LINK_LIBRARIES(tstNeutronAbsorptionReaction ${PROJECT_NAME})
ADD_TEST(NeutronAbsorptionReaction_test tstNeutronAbsorptionReaction --test_basic_ace_file="${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_h1_ace_file.txt" --test_basic_ace_table="1001.70c")

ADD_EXECUTABLE(tstNuclearReactionFactory
  tstNuclearReactionFactory.cpp)
TARGET_LINK_LIBRARIES(tstNuclearReactionFactory ${PROJECT_NAME})
ADD_TEST(NuclearReactionFactory_test tstNuclearReactionFactory --test_basic_ace_file="${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_h1_ace_file.txt" --test_basic_ace_table="1001.70c")

ADD_EXECUTABLE(tstNuclide
  tstNuclide.cpp)
TARGET_LINK_LIBRARIES(tstNuclide ${PROJECT_NAME})
ADD_TEST(Nuclide_test tstNuclide --test_basic_ace_file="${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_h1_ace_file.txt" --test_basic_ace_table="1001.70c")

ADD_EXECUTABLE(tstNuclideFactory
  tstNuclideFactory.cpp)
TARGET_LINK_LIBRARIES(tstNuclideFactory ${PROJECT_NAME})
ADD_TEST(NuclideFactory_test tstNuclideFactory --test_cross_sections_xml_directory="${CMAKE_CURRENT_SOURCE_DIR}/test_files")

ADD_EXECUTABLE(tstMaterialHelpers
  tstMaterialHelpers.cpp
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstMaterialHelpers ${PROJECT_NAME})
ADD_TEST(MaterialHelpers_test tstMaterialHelpers)

ADD_EXECUTABLE(tstNeutronMaterial
  tstNeutronMaterial.cpp)
TARGET_LINK_LIBRARIES(tstNeutronMaterial ${PROJECT_NAME})
ADD_TEST(NeutronMaterial_test tstNeutronMaterial --test_cross_sections_xml_directory="${CMAKE_CURRENT_SOURCE_DIR}/test_files")