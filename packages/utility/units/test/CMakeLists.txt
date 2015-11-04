ADD_EXECUTABLE(tstElectronVoltUnit
  tstElectronVoltUnit.cpp
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstElectronVoltUnit utility_core)
ADD_TEST(ElectronVoltUnit_test tstElectronVoltUnit)

ADD_EXECUTABLE(tstAngstromUnit
  tstAngstromUnit.cpp
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstAngstromUnit utility_core)
ADD_TEST(AngstromUnit_test tstAngstromUnit)

ADD_EXECUTABLE(tstBarnUnit
  tstBarnUnit.cpp
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstBarnUnit utility_core)
ADD_TEST(BarnUnit_test tstBarnUnit)

ADD_EXECUTABLE(tstInverseAngstromUnit
  tstInverseAngstromUnit.cpp
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstInverseAngstromUnit utility_core)
ADD_TEST(InverseAngstromUnit_test tstInverseAngstromUnit)

ADD_EXECUTABLE(tstInverseCentimeterUnit
  tstInverseCentimeterUnit.cpp
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstInverseCentimeterUnit utility_core)
ADD_TEST(InverseCentimeterUnit_test tstInverseCentimeterUnit)

ADD_EXECUTABLE(tstInverseLengthConversion
  tstInverseLengthConversion.cpp
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstInverseLengthConversion utility_core)
ADD_TEST(InverseLengthConversion_test tstInverseLengthConversion)

ADD_EXECUTABLE(tstInverseSquareAngstromUnit
  tstInverseSquareAngstromUnit.cpp
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstInverseSquareAngstromUnit utility_core)
ADD_TEST(InverseSquareAngstromUnit_test tstInverseSquareAngstromUnit)

ADD_EXECUTABLE(tstInverseSquareCentimeterUnit
  tstInverseSquareCentimeterUnit.cpp
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstInverseSquareCentimeterUnit utility_core)
ADD_TEST(InverseSquareCentimeterUnit_test tstInverseSquareCentimeterUnit)

ADD_EXECUTABLE(tstInverseAreaConversion
  tstInverseAreaConversion.cpp
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstInverseAreaConversion utility_core)
ADD_TEST(InverseAreaConversion_test tstInverseAreaConversion)

ADD_EXECUTABLE(tstAtomUnit 
  tstAtomUnit.cpp
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstAtomUnit utility_core)
ADD_TEST(AtomUnit_test tstAtomUnit)

ADD_EXECUTABLE(tstShakeUnit 
  tstShakeUnit.cpp
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstShakeUnit utility_core)
ADD_TEST(ShakeUnit_test tstShakeUnit)