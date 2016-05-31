ADD_EXECUTABLE(tstElectronVoltUnit
  tstElectronVoltUnit.cpp
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstElectronVoltUnit utility_units)
ADD_TEST(ElectronVoltUnit_test tstElectronVoltUnit)
SET_PROPERTY(TEST ElectronVoltUnit_test PROPERTY LABELS utility_units)

ADD_EXECUTABLE(tstAngstromUnit
  tstAngstromUnit.cpp
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstAngstromUnit utility_units)
ADD_TEST(AngstromUnit_test tstAngstromUnit)
SET_PROPERTY(TEST AngstromUnit_test PROPERTY LABELS utility_units)

ADD_EXECUTABLE(tstBarnUnit
  tstBarnUnit.cpp
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstBarnUnit utility_units)
ADD_TEST(BarnUnit_test tstBarnUnit)
SET_PROPERTY(TEST BarnUnit_test PROPERTY LABELS utility_units)

ADD_EXECUTABLE(tstInverseAngstromUnit
  tstInverseAngstromUnit.cpp
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstInverseAngstromUnit utility_units)
ADD_TEST(InverseAngstromUnit_test tstInverseAngstromUnit)
SET_PROPERTY(TEST InverseAngstromUnit_test PROPERTY LABELS utility_units)

ADD_EXECUTABLE(tstInverseCentimeterUnit
  tstInverseCentimeterUnit.cpp
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstInverseCentimeterUnit utility_units)
ADD_TEST(InverseCentimeterUnit_test tstInverseCentimeterUnit)
SET_PROPERTY(TEST InverseCentimeterUnit_test PROPERTY LABELS utility_units)

ADD_EXECUTABLE(tstInverseLengthConversion
  tstInverseLengthConversion.cpp
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstInverseLengthConversion utility_units)
ADD_TEST(InverseLengthConversion_test tstInverseLengthConversion)
SET_PROPERTY(TEST InverseLengthConversion_test PROPERTY LABELS utility_units)

ADD_EXECUTABLE(tstInverseSquareAngstromUnit
  tstInverseSquareAngstromUnit.cpp
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstInverseSquareAngstromUnit utility_units)
ADD_TEST(InverseSquareAngstromUnit_test tstInverseSquareAngstromUnit)
SET_PROPERTY(TEST InverseSquareAngstromUnit_test PROPERTY LABELS utility_units)

ADD_EXECUTABLE(tstInverseSquareCentimeterUnit
  tstInverseSquareCentimeterUnit.cpp
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstInverseSquareCentimeterUnit utility_units)
ADD_TEST(InverseSquareCentimeterUnit_test tstInverseSquareCentimeterUnit)
SET_PROPERTY(TEST InverseSquareCentimeterUnit_test PROPERTY LABELS utility_units)

ADD_EXECUTABLE(tstInverseAreaConversion
  tstInverseAreaConversion.cpp
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstInverseAreaConversion utility_units)
ADD_TEST(InverseAreaConversion_test tstInverseAreaConversion)
SET_PROPERTY(TEST InverseAreaConversion_test PROPERTY LABELS utility_units)

ADD_EXECUTABLE(tstAtomUnit
  tstAtomUnit.cpp
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstAtomUnit utility_units)
ADD_TEST(AtomUnit_test tstAtomUnit)
SET_PROPERTY(TEST AtomUnit_test PROPERTY LABELS utility_units)

ADD_EXECUTABLE(tstShakeUnit
  tstShakeUnit.cpp
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstShakeUnit utility_units)
ADD_TEST(ShakeUnit_test tstShakeUnit)
SET_PROPERTY(TEST ShakeUnit_test PROPERTY LABELS utility_units)

ADD_EXECUTABLE(tstAtomicMomentumUnit
  tstAtomicMomentumUnit.cpp
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstAtomicMomentumUnit utility_units)
ADD_TEST(AtomicMomentumUnit_test tstAtomicMomentumUnit)
SET_PROPERTY(TEST AtomicMomentumUnit_test PROPERTY LABELS utility_units)

ADD_EXECUTABLE(tstMeCMomentumUnit
  tstMeCMomentumUnit.cpp
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstMeCMomentumUnit utility_units)
ADD_TEST(MeCMomentumUnit_test tstMeCMomentumUnit)
SET_PROPERTY(TEST MeCMomentumUnit_test PROPERTY LABELS utility_units)

ADD_EXECUTABLE(tstMomentumConversion
  tstMomentumConversion.cpp
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstMomentumConversion utility_units)
ADD_TEST(MomentumConversion_test tstMomentumConversion)
SET_PROPERTY(TEST MomentumConversion_test PROPERTY LABELS utility_units)

ADD_EXECUTABLE(tstInverseAtomicMomentumUnit
  tstInverseAtomicMomentumUnit.cpp
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstInverseAtomicMomentumUnit utility_units)
ADD_TEST(InverseAtomicMomentumUnit_test tstInverseAtomicMomentumUnit)
SET_PROPERTY(TEST InverseAtomicMomentumUnit_test PROPERTY LABELS utility_units)

ADD_EXECUTABLE(tstInverseMeCMomentumUnit
  tstInverseMeCMomentumUnit.cpp
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstInverseMeCMomentumUnit utility_units)
ADD_TEST(InverseMeCMomentumUnit_test tstInverseMeCMomentumUnit)
SET_PROPERTY(TEST InverseMeCMomentumUnit_test PROPERTY LABELS utility_units)

ADD_EXECUTABLE(tstInverseMomentumConversion
  tstInverseMomentumConversion.cpp
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstInverseMomentumConversion utility_units)
ADD_TEST(InverseMomentumConversion_test tstInverseMomentumConversion)
SET_PROPERTY(TEST InverseMomentumConversion_test PROPERTY LABELS utility_units)

ADD_EXECUTABLE(tstAtomicMassUnit
  tstAtomicMassUnit.cpp
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstAtomicMassUnit utility_units)
ADD_TEST(AtomicMassUnit_test tstAtomicMassUnit)
SET_PROPERTY(TEST AtomicMassUnit_test PROPERTY LABELS utility_units)
