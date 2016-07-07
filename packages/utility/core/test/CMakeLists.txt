ADD_EXECUTABLE(tstAssertion 
  tstAssertion.cpp 
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstAssertion utility_core)
ADD_TEST(Assertion_test tstAssertion)

ADD_EXECUTABLE(tstContractException 
  tstContractException.cpp 
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstContractException utility_core)
ADD_TEST(ContractException_test tstContractException)

ADD_EXECUTABLE(tstSerialCommHelpers
  tstSerialCommHelpers.cpp
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstSerialCommHelpers utility_core)
ADD_TEST(SerialCommHelpers_test tstSerialCommHelpers)

IF(${FRENSIE_ENABLE_MPI})
  ADD_EXECUTABLE(tstMpiCommHelpers
    tstMpiCommHelpers.cpp)
  TARGET_LINK_LIBRARIES(tstMpiCommHelpers utility_core)
  ADD_TEST(MpiCommHelpers_2_test ${MPIEXEC} -n 2 tstMpiCommHelpers)
  ADD_TEST(MpiCommHelpers_4_test ${MPIEXEC} -n 4 tstMpiCommHelpers)
ENDIF()

ADD_EXECUTABLE(tstSortAlgorithms 
  tstSortAlgorithms.cpp 
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstSortAlgorithms utility_core)
ADD_TEST(SortAlgorithms_test tstSortAlgorithms)

ADD_EXECUTABLE(tstSearchAlgorithms 
  tstSearchAlgorithms.cpp 
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstSearchAlgorithms utility_core)
ADD_TEST(SearchAlgorithms_test tstSearchAlgorithms)

ADD_EXECUTABLE(tstExponentiationAlgorithms 
  tstExponentiationAlgorithms.cpp 
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstExponentiationAlgorithms utility_core)
ADD_TEST(ExponentiationAlgorithms_test tstExponentiationAlgorithms)

ADD_EXECUTABLE(tstSetOperationFunctor 
  tstSetOperationFunctor.cpp 
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstSetOperationFunctor utility_core)
ADD_TEST(SetOperationFunctor_test tstSetOperationFunctor)

ADD_EXECUTABLE(tstDirectionHelpers 
  tstDirectionHelpers.cpp 
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstDirectionHelpers utility_core)
ADD_TEST(DirectionHelpers_test tstDirectionHelpers)

ADD_EXECUTABLE(tstCylindricalCoordinateHelpers 
  tstCylindricalCoordinateHelpers.cpp 
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstCylindricalCoordinateHelpers utility_core)
ADD_TEST(CylindricalCoordinateHelpers_test tstCylindricalCoordinateHelpers)

ADD_EXECUTABLE(tstSphericalCoordinateHelpers 
  tstSphericalCoordinateHelpers.cpp 
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstSphericalCoordinateHelpers utility_core)
ADD_TEST(SphericalCoordinateHelpers_test tstSphericalCoordinateHelpers)

ADD_EXECUTABLE(tstDataProcessor 
  tstDataProcessor.cpp 
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstDataProcessor utility_core)
ADD_TEST(DataProcessor_test tstDataProcessor)

ADD_EXECUTABLE(tstFortranStringHelpers 
  tstFortranStringHelpers.cpp 
  string_conversion.F90 
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstFortranStringHelpers utility_core)
ADD_TEST(FortranStringHelpers_test tstFortranStringHelpers)

ADD_EXECUTABLE(tstFortranFileHelpers 
  tstFortranFileHelpers.cpp )
TARGET_LINK_LIBRARIES(tstFortranFileHelpers utility_core)
ADD_TEST(FortranFileHelpers_test tstFortranFileHelpers
--test_file="${CMAKE_CURRENT_SOURCE_DIR}/test_files/check_file.txt")

ADD_EXECUTABLE(tstKinematicHelpers 
  tstKinematicHelpers.cpp
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstKinematicHelpers utility_core)
ADD_TEST(KinematicHelpers_test tstKinematicHelpers)

ADD_EXECUTABLE(tstTetrahedronHelpers
  tstTetrahedronHelpers.cpp
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstTetrahedronHelpers utility_core)
ADD_TEST(TetrahedronHelpers_test tstTetrahedronHelpers)

ADD_EXECUTABLE(tstArrayString tstArrayString.cpp)
TARGET_LINK_LIBRARIES(tstArrayString utility_core)
ADD_TEST(ArrayString_test tstArrayString --test_array_xml_file="${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_arrays.xml")

ADD_EXECUTABLE(tstMeasurement 
  tstMeasurement.cpp
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstMeasurement utility_core)
ADD_TEST(Measurement_test tstMeasurement)

ADD_EXECUTABLE(tstActiveCounter
  tstActiveCounter.cpp
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstActiveCounter utility_core)
ADD_TEST(ActiveCounter_test tstActiveCounter)

ADD_EXECUTABLE(tstInactiveCounter
  tstInactiveCounter.cpp
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstInactiveCounter utility_core)
ADD_TEST(InactiveCounter_test tstInactiveCounter)

ADD_EXECUTABLE(tstIncrementPolicy
  tstIncrementPolicy.cpp
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstIncrementPolicy utility_core)
ADD_TEST(IncrementPolicy_test tstIncrementPolicy)
