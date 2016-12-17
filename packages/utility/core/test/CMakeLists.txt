# This test cannot use the FRENSIE_STD_UNIT_TEST_MAIN because it is one
# of the dependencies
ADD_EXECUTABLE(tstStaticOutputFormatter
  tstStaticOutputFormatter.cpp
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstStaticOutputFormatter utility_core)
ADD_TEST(StaticOutputFormatter_test tstStaticOutputFormatter)
SET_PROPERTY(TEST StaticOutputFormatter_test PROPERTY LABELS utility_core)

# This test cannout use the FRENSIE_STD_UNIT_TEST_MAIN because it is one
# of the dependencies
ADD_EXECUTABLE(tstDynamicOutputFormatter
  tstDynamicOutputFormatter.cpp
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstDynamicOutputFormatter utility_core)
ADD_TEST(DynamicOutputFormatter_test tstDynamicOutputFormatter)
SET_PROPERTY(TEST DynamicOutputFormatter_test PROPERTY LABELS utility_core)

ADD_EXECUTABLE(tstAssertion
  tstAssertion.cpp
  ${FRENSIE_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstAssertion utility_core)
ADD_TEST(Assertion_test tstAssertion)
SET_PROPERTY(TEST Assertion_test PROPERTY LABELS utility_core)

ADD_EXECUTABLE(tstContractException
  tstContractException.cpp
  ${FRENSIE_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstContractException utility_core)
ADD_TEST(ContractException_test tstContractException)
SET_PROPERTY(TEST ContractException_test PROPERTY LABELS utility_core)

ADD_EXECUTABLE(tstElectronVoltUnit
  tstElectronVoltUnit.cpp
  ${FRENSIE_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstElectronVoltUnit utility_core)
ADD_TEST(ElectronVoltUnit_test tstElectronVoltUnit)
SET_PROPERTY(TEST ElectronVoltUnit_test PROPERTY LABELS utility_core)

ADD_EXECUTABLE(tstAngstromUnit
  tstAngstromUnit.cpp
  ${FRENSIE_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstAngstromUnit utility_core)
ADD_TEST(AngstromUnit_test tstAngstromUnit)
SET_PROPERTY(TEST AngstromUnit_test PROPERTY LABELS utility_core)

ADD_EXECUTABLE(tstBarnUnit
  tstBarnUnit.cpp
  ${FRENSIE_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstBarnUnit utility_core)
ADD_TEST(BarnUnit_test tstBarnUnit)
SET_PROPERTY(TEST BarnUnit_test PROPERTY LABELS utility_core)

ADD_EXECUTABLE(tstInverseAngstromUnit
  tstInverseAngstromUnit.cpp
  ${FRENSIE_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstInverseAngstromUnit utility_core)
ADD_TEST(InverseAngstromUnit_test tstInverseAngstromUnit)
SET_PROPERTY(TEST InverseAngstromUnit_test PROPERTY LABELS utility_core)

ADD_EXECUTABLE(tstInverseCentimeterUnit
  tstInverseCentimeterUnit.cpp
  ${FRENSIE_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstInverseCentimeterUnit utility_core)
ADD_TEST(InverseCentimeterUnit_test tstInverseCentimeterUnit)
SET_PROPERTY(TEST InverseCentimeterUnit_test PROPERTY LABELS utility_core)

ADD_EXECUTABLE(tstInverseLengthConversion
  tstInverseLengthConversion.cpp
  ${FRENSIE_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstInverseLengthConversion utility_core)
ADD_TEST(InverseLengthConversion_test tstInverseLengthConversion)
SET_PROPERTY(TEST InverseLengthConversion_test PROPERTY LABELS utility_core)

ADD_EXECUTABLE(tstInverseSquareAngstromUnit
  tstInverseSquareAngstromUnit.cpp
  ${FRENSIE_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstInverseSquareAngstromUnit utility_core)
ADD_TEST(InverseSquareAngstromUnit_test tstInverseSquareAngstromUnit)
SET_PROPERTY(TEST InverseSquareAngstromUnit_test PROPERTY LABELS utility_core)

ADD_EXECUTABLE(tstInverseSquareCentimeterUnit
  tstInverseSquareCentimeterUnit.cpp
  ${FRENSIE_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstInverseSquareCentimeterUnit utility_core)
ADD_TEST(InverseSquareCentimeterUnit_test tstInverseSquareCentimeterUnit)
SET_PROPERTY(TEST InverseSquareCentimeterUnit_test PROPERTY LABELS utility_core)

ADD_EXECUTABLE(tstInverseAreaConversion
  tstInverseAreaConversion.cpp
  ${FRENSIE_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstInverseAreaConversion utility_core)
ADD_TEST(InverseAreaConversion_test tstInverseAreaConversion)
SET_PROPERTY(TEST InverseAreaConversion_test PROPERTY LABELS utility_core)

ADD_EXECUTABLE(tstAtomUnit
  tstAtomUnit.cpp
  ${FRENSIE_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstAtomUnit utility_core)
ADD_TEST(AtomUnit_test tstAtomUnit)
SET_PROPERTY(TEST AtomUnit_test PROPERTY LABELS utility_core)

ADD_EXECUTABLE(tstShakeUnit
  tstShakeUnit.cpp
  ${FRENSIE_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstShakeUnit utility_core)
ADD_TEST(ShakeUnit_test tstShakeUnit)
SET_PROPERTY(TEST ShakeUnit_test PROPERTY LABELS utility_core)

ADD_EXECUTABLE(tstAtomicMomentumUnit
  tstAtomicMomentumUnit.cpp
  ${FRENSIE_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstAtomicMomentumUnit utility_core)
ADD_TEST(AtomicMomentumUnit_test tstAtomicMomentumUnit)
SET_PROPERTY(TEST AtomicMomentumUnit_test PROPERTY LABELS utility_core)

ADD_EXECUTABLE(tstMeCMomentumUnit
  tstMeCMomentumUnit.cpp
  ${FRENSIE_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstMeCMomentumUnit utility_core)
ADD_TEST(MeCMomentumUnit_test tstMeCMomentumUnit)
SET_PROPERTY(TEST MeCMomentumUnit_test PROPERTY LABELS utility_core)

ADD_EXECUTABLE(tstMomentumConversion
  tstMomentumConversion.cpp
  ${FRENSIE_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstMomentumConversion utility_core)
ADD_TEST(MomentumConversion_test tstMomentumConversion)
SET_PROPERTY(TEST MomentumConversion_test PROPERTY LABELS utility_core)

ADD_EXECUTABLE(tstInverseAtomicMomentumUnit
  tstInverseAtomicMomentumUnit.cpp
  ${FRENSIE_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstInverseAtomicMomentumUnit utility_core)
ADD_TEST(InverseAtomicMomentumUnit_test tstInverseAtomicMomentumUnit)
SET_PROPERTY(TEST InverseAtomicMomentumUnit_test PROPERTY LABELS utility_core)

ADD_EXECUTABLE(tstInverseMeCMomentumUnit
  tstInverseMeCMomentumUnit.cpp
  ${FRENSIE_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstInverseMeCMomentumUnit utility_core)
ADD_TEST(InverseMeCMomentumUnit_test tstInverseMeCMomentumUnit)
SET_PROPERTY(TEST InverseMeCMomentumUnit_test PROPERTY LABELS utility_core)

ADD_EXECUTABLE(tstInverseMomentumConversion
  tstInverseMomentumConversion.cpp
  ${FRENSIE_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstInverseMomentumConversion utility_core)
ADD_TEST(InverseMomentumConversion_test tstInverseMomentumConversion)
SET_PROPERTY(TEST InverseMomentumConversion_test PROPERTY LABELS utility_core)

ADD_EXECUTABLE(tstAtomicMassUnit
  tstAtomicMassUnit.cpp
  ${FRENSIE_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstAtomicMassUnit utility_core)
ADD_TEST(AtomicMassUnit_test tstAtomicMassUnit)
SET_PROPERTY(TEST AtomicMassUnit_test PROPERTY LABELS utility_core)

ADD_EXECUTABLE(tstSerialCommHelpers
  tstSerialCommHelpers.cpp
  ${FRENSIE_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstSerialCommHelpers utility_core)
ADD_TEST(SerialCommHelpers_test tstSerialCommHelpers)
SET_PROPERTY(TEST SerialCommHelpers_test PROPERTY LABELS utility_core)

IF(${FRENSIE_ENABLE_MPI})
  ADD_EXECUTABLE(tstMpiCommHelpers
    tstMpiCommHelpers.cpp
    ${FRENSIE_STD_UNIT_TEST_MAIN})
  TARGET_LINK_LIBRARIES(tstMpiCommHelpers utility_core)
  ADD_TEST(MpiCommHelpers_2_test ${MPIEXEC} -n 2 tstMpiCommHelpers)
  ADD_TEST(MpiCommHelpers_4_test ${MPIEXEC} -n 4 tstMpiCommHelpers)
  SET_PROPERTY(TEST MpiCommHelpers_2_test PROPERTY LABELS utility_core mpi no_threads)
  SET_PROPERTY(TEST MpiCommHelpers_4_test PROPERTY LABELS utility_core mpi no_threads)
ENDIF()

ADD_EXECUTABLE(tstSortAlgorithms
  tstSortAlgorithms.cpp
  ${FRENSIE_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstSortAlgorithms utility_core)
ADD_TEST(SortAlgorithms_test tstSortAlgorithms)
SET_PROPERTY(TEST SortAlgorithms_test PROPERTY LABELS utility_core)

ADD_EXECUTABLE(tstSearchAlgorithms
  tstSearchAlgorithms.cpp
  ${FRENSIE_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstSearchAlgorithms utility_core)
ADD_TEST(SearchAlgorithms_test tstSearchAlgorithms)
SET_PROPERTY(TEST SearchAlgorithms_test PROPERTY LABELS utility_core)

ADD_EXECUTABLE(tstExponentiationAlgorithms
  tstExponentiationAlgorithms.cpp
  ${FRENSIE_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstExponentiationAlgorithms utility_core)
ADD_TEST(ExponentiationAlgorithms_test tstExponentiationAlgorithms)
SET_PROPERTY(TEST ExponentiationAlgorithms_test PROPERTY LABELS utility_core)

ADD_EXECUTABLE(tstSetOperationFunctor
  tstSetOperationFunctor.cpp
  ${FRENSIE_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstSetOperationFunctor utility_core)
ADD_TEST(SetOperationFunctor_test tstSetOperationFunctor)
SET_PROPERTY(TEST SetOperationFunctor_test PROPERTY LABELS utility_core)

ADD_EXECUTABLE(tstDirectionHelpers
  tstDirectionHelpers.cpp
  ${FRENSIE_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstDirectionHelpers utility_core)
ADD_TEST(DirectionHelpers_test tstDirectionHelpers)
SET_PROPERTY(TEST DirectionHelpers_test PROPERTY LABELS utility_core)

ADD_EXECUTABLE(tst3DCartesianVectorHelpers
  tst3DCartesianVectorHelpers.cpp
  ${FRENSIE_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tst3DCartesianVectorHelpers utility_core)
ADD_TEST(3DCartesianVectorHelpers_test tst3DCartesianVectorHelpers)
SET_PROPERTY(TEST 3DCartesianVectorHelpers_test PROPERTY LABELS utility_core)

ADD_EXECUTABLE(tstCartesianCoordinateConversionPolicy
  tstCartesianCoordinateConversionPolicy.cpp
  ${FRENSIE_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstCartesianCoordinateConversionPolicy utility_core)
ADD_TEST(CartesianCoordinateConversionPolicy_test tstCartesianCoordinateConversionPolicy)
SET_PROPERTY(TEST CartesianCoordinateConversionPolicy_test PROPERTY LABELS utility_core)

ADD_EXECUTABLE(tstBasicCartesianCoordinateConversionPolicy
  tstBasicCartesianCoordinateConversionPolicy.cpp
  ${FRENSIE_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstBasicCartesianCoordinateConversionPolicy utility_core)
ADD_TEST(BasicCartesianCoordinateConversionPolicy_test tstBasicCartesianCoordinateConversionPolicy)
SET_PROPERTY(TEST BasicCartesianCoordinateConversionPolicy_test PROPERTY LABELS utility_core)

ADD_EXECUTABLE(tstDataProcessor
  tstDataProcessor.cpp
  ${FRENSIE_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstDataProcessor utility_core)
ADD_TEST(DataProcessor_test tstDataProcessor)
SET_PROPERTY(TEST DataProcessor_test PROPERTY LABELS utility_core)

ADD_EXECUTABLE(tstFortranStringHelpers
  tstFortranStringHelpers.cpp
  string_conversion.F90
  ${FRENSIE_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstFortranStringHelpers utility_core)
ADD_TEST(FortranStringHelpers_test tstFortranStringHelpers)
SET_PROPERTY(TEST FortranStringHelpers_test PROPERTY LABELS utility_core)

ADD_EXECUTABLE(tstFortranFileHelpers
  tstFortranFileHelpers.cpp
  ${FRENSIE_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstFortranFileHelpers utility_core)
ADD_TEST(FortranFileHelpers_test tstFortranFileHelpers
--test_file="${CMAKE_CURRENT_SOURCE_DIR}/test_files/check_file.txt")
SET_PROPERTY(TEST FortranFileHelpers_test PROPERTY LABELS utility_core)

ADD_EXECUTABLE(tstKinematicHelpers
  tstKinematicHelpers.cpp
  ${FRENSIE_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstKinematicHelpers utility_core)
ADD_TEST(KinematicHelpers_test tstKinematicHelpers)
SET_PROPERTY(TEST KinematicHelpers_test PROPERTY LABELS utility_core)

ADD_EXECUTABLE(tstLegendrePolynomial
  tstLegendrePolynomial.cpp
  ${FRENSIE_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstLegendrePolynomial utility_core)
ADD_TEST(LegendrePolynomial_test tstLegendrePolynomial)
SET_PROPERTY(TEST LegendrePolynomial_test PROPERTY LABELS utility_core)

ADD_EXECUTABLE(tstGaussLegendreQuadratureSet
  tstGaussLegendreQuadratureSet.cpp
  ${FRENSIE_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstGaussLegendreQuadratureSet utility_core)
ADD_TEST(GaussLegendreQuadratureSet_test tstGaussLegendreQuadratureSet)
SET_PROPERTY(TEST GaussLegendreQuadratureSet_test PROPERTY LABELS utility_core)

ADD_EXECUTABLE(tstSloanRadauQuadrature
  tstSloanRadauQuadrature.cpp
  ${FRENSIE_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstSloanRadauQuadrature utility_core)
ADD_TEST(SloanRadauQuadrature_test tstSloanRadauQuadrature)
SET_PROPERTY(TEST SloanRadauQuadrature_test PROPERTY LABELS utility_core)

ADD_EXECUTABLE(tstTetrahedronHelpers
  tstTetrahedronHelpers.cpp
  ${FRENSIE_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstTetrahedronHelpers utility_core)
ADD_TEST(TetrahedronHelpers_test tstTetrahedronHelpers)
SET_PROPERTY(TEST TetrahedronHelpers_test PROPERTY LABELS utility_core)

ADD_EXECUTABLE(tstArrayString
  tstArrayString.cpp
  ${FRENSIE_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstArrayString utility_core)
ADD_TEST(ArrayString_test tstArrayString --test_array_xml_file="${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_arrays.xml")
SET_PROPERTY(TEST ArrayString_test PROPERTY LABELS utility_core)

ADD_EXECUTABLE(tstMeasurement
  tstMeasurement.cpp
  ${FRENSIE_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstMeasurement utility_core)
ADD_TEST(Measurement_test tstMeasurement)
SET_PROPERTY(TEST Measurement_test PROPERTY LABELS utility_core)

ADD_EXECUTABLE(tstActiveCounter
  tstActiveCounter.cpp
  ${FRENSIE_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstActiveCounter utility_core)
ADD_TEST(ActiveCounter_test tstActiveCounter)
SET_PROPERTY(TEST ActiveCounter_test PROPERTY LABELS utility_core)

ADD_EXECUTABLE(tstInactiveCounter
  tstInactiveCounter.cpp
  ${FRENSIE_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstInactiveCounter utility_core)
ADD_TEST(InactiveCounter_test tstInactiveCounter)
SET_PROPERTY(TEST InactiveCounter_test PROPERTY LABELS utility_core)

ADD_EXECUTABLE(tstIncrementPolicy
  tstIncrementPolicy.cpp
  ${FRENSIE_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstIncrementPolicy utility_core)
ADD_TEST(IncrementPolicy_test tstIncrementPolicy)
SET_PROPERTY(TEST IncrementPolicy_test PROPERTY LABELS utility_core)

ADD_EXECUTABLE(tstStructuredHexMesh
  tstStructuredHexMesh.cpp
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstStructuredHexMesh utility_core)
ADD_TEST(StructuredHexMesh_test tstStructuredHexMesh)
SET_PROPERTY(TEST StructuredHexMesh_test PROPERTY LABELS utility_core)
