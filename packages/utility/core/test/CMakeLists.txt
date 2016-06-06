ADD_EXECUTABLE(tstAssertion 
  tstAssertion.cpp 
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstAssertion utility_core)
ADD_TEST(Assertion_test tstAssertion)
SET_PROPERTY(TEST Assertion_test PROPERTY LABELS utility_core)

ADD_EXECUTABLE(tstContractException 
  tstContractException.cpp 
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstContractException utility_core)
ADD_TEST(ContractException_test tstContractException)
SET_PROPERTY(TEST ContractException_test PROPERTY LABELS utility_core)

ADD_EXECUTABLE(tstSerialCommHelpers
  tstSerialCommHelpers.cpp
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstSerialCommHelpers utility_core)
ADD_TEST(SerialCommHelpers_test tstSerialCommHelpers)
SET_PROPERTY(TEST SerialCommHelpers_test PROPERTY LABELS utility_core)

IF(${FRENSIE_ENABLE_MPI})
  ADD_EXECUTABLE(tstMpiCommHelpers
    tstMpiCommHelpers.cpp)
  TARGET_LINK_LIBRARIES(tstMpiCommHelpers utility_core)
  ADD_TEST(MpiCommHelpers_2_test ${MPIEXEC} -n 2 tstMpiCommHelpers)
  ADD_TEST(MpiCommHelpers_4_test ${MPIEXEC} -n 4 tstMpiCommHelpers)
  SET_PROPERTY(TEST MpiCommHelpers_2_test PROPERTY LABELS utility_core mpi no_threads)
  SET_PROPERTY(TEST MpiCommHelpers_4_test PROPERTY LABELS utility_core mpi no_threads)
ENDIF()

ADD_EXECUTABLE(tstSortAlgorithms
  tstSortAlgorithms.cpp 
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstSortAlgorithms utility_core)
ADD_TEST(SortAlgorithms_test tstSortAlgorithms)
SET_PROPERTY(TEST SortAlgorithms_test PROPERTY LABELS utility_core)

ADD_EXECUTABLE(tstSearchAlgorithms
  tstSearchAlgorithms.cpp 
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstSearchAlgorithms utility_core)
ADD_TEST(SearchAlgorithms_test tstSearchAlgorithms)
SET_PROPERTY(TEST SearchAlgorithms_test PROPERTY LABELS utility_core)

ADD_EXECUTABLE(tstExponentiationAlgorithms
  tstExponentiationAlgorithms.cpp 
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstExponentiationAlgorithms utility_core)
ADD_TEST(ExponentiationAlgorithms_test tstExponentiationAlgorithms)
SET_PROPERTY(TEST ExponentiationAlgorithms_test PROPERTY LABELS utility_core)

ADD_EXECUTABLE(tstInterpolationPolicy
  tstInterpolationPolicy.cpp 
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstInterpolationPolicy utility_core)
ADD_TEST(InterpolationPolicy_test tstInterpolationPolicy)
SET_PROPERTY(TEST InterpolationPolicy_test PROPERTY LABELS utility_core)

ADD_EXECUTABLE(tstLinLinLinTwoDInterpolationPolicy
  tstLinLinLinTwoDInterpolationPolicy.cpp
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstLinLinLinTwoDInterpolationPolicy utility_core)
ADD_TEST(LinLinLinTwoDInterpolationPolicy_test tstLinLinLinTwoDInterpolationPolicy)
SET_PROPERTY(TEST LinLinLinTwoDInterpolationPolicy_test PROPERTY LABELS utility_core)

ADD_EXECUTABLE(tstLinLinLogTwoDInterpolationPolicy
  tstLinLinLogTwoDInterpolationPolicy.cpp
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstLinLinLogTwoDInterpolationPolicy utility_core)
ADD_TEST(LinLinLogTwoDInterpolationPolicy_test tstLinLinLogTwoDInterpolationPolicy)
SET_PROPERTY(TEST LinLinLogTwoDInterpolationPolicy_test PROPERTY LABELS utility_core)

ADD_EXECUTABLE(tstLinLogLinTwoDInterpolationPolicy
  tstLinLogLinTwoDInterpolationPolicy.cpp
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstLinLogLinTwoDInterpolationPolicy utility_core)
ADD_TEST(LinLogLinTwoDInterpolationPolicy_test tstLinLogLinTwoDInterpolationPolicy)
SET_PROPERTY(TEST LinLogLinTwoDInterpolationPolicy_test PROPERTY LABELS utility_core)

ADD_EXECUTABLE(tstLinLogLogTwoDInterpolationPolicy
  tstLinLogLogTwoDInterpolationPolicy.cpp
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstLinLogLogTwoDInterpolationPolicy utility_core)
ADD_TEST(LinLogLogTwoDInterpolationPolicy_test tstLinLogLogTwoDInterpolationPolicy)
SET_PROPERTY(TEST LinLogLogTwoDInterpolationPolicy_test PROPERTY LABELS utility_core)

ADD_EXECUTABLE(tstLogLinLinTwoDInterpolationPolicy
  tstLogLinLinTwoDInterpolationPolicy.cpp
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstLogLinLinTwoDInterpolationPolicy utility_core)
ADD_TEST(LogLinLinTwoDInterpolationPolicy_test tstLogLinLinTwoDInterpolationPolicy)
SET_PROPERTY(TEST LogLinLinTwoDInterpolationPolicy_test PROPERTY LABELS utility_core)

ADD_EXECUTABLE(tstLogLogLinTwoDInterpolationPolicy
  tstLogLogLinTwoDInterpolationPolicy.cpp
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstLogLogLinTwoDInterpolationPolicy utility_core)
ADD_TEST(LogLogLinTwoDInterpolationPolicy_test tstLogLogLinTwoDInterpolationPolicy)
SET_PROPERTY(TEST LogLogLinTwoDInterpolationPolicy_test PROPERTY LABELS utility_core)

ADD_EXECUTABLE(tstLogLinLogTwoDInterpolationPolicy
  tstLogLinLogTwoDInterpolationPolicy.cpp
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstLogLinLogTwoDInterpolationPolicy utility_core)
ADD_TEST(LogLinLogTwoDInterpolationPolicy_test tstLogLinLogTwoDInterpolationPolicy)
SET_PROPERTY(TEST LogLinLogTwoDInterpolationPolicy_test PROPERTY LABELS utility_core)

ADD_EXECUTABLE(tstLogLogLogTwoDInterpolationPolicy
  tstLogLogLogTwoDInterpolationPolicy.cpp
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstLogLogLogTwoDInterpolationPolicy utility_core)
ADD_TEST(LogLogLogTwoDInterpolationPolicy_test tstLogLogLogTwoDInterpolationPolicy)
SET_PROPERTY(TEST LogLogLogTwoDInterpolationPolicy_test PROPERTY LABELS utility_core)

ADD_EXECUTABLE(tstSetOperationFunctor 
  tstSetOperationFunctor.cpp 
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstSetOperationFunctor utility_core)
ADD_TEST(SetOperationFunctor_test tstSetOperationFunctor)
SET_PROPERTY(TEST SetOperationFunctor_test PROPERTY LABELS utility_core)

ADD_EXECUTABLE(tstDirectionHelpers
  tstDirectionHelpers.cpp 
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstDirectionHelpers utility_core)
ADD_TEST(DirectionHelpers_test tstDirectionHelpers)
SET_PROPERTY(TEST DirectionHelpers_test PROPERTY LABELS utility_core)

ADD_EXECUTABLE(tstCylindricalCoordinateHelpers
  tstCylindricalCoordinateHelpers.cpp 
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstCylindricalCoordinateHelpers utility_core)
ADD_TEST(CylindricalCoordinateHelpers_test tstCylindricalCoordinateHelpers)
SET_PROPERTY(TEST CylindricalCoordinateHelpers_test PROPERTY LABELS utility_core)

ADD_EXECUTABLE(tstSphericalCoordinateHelpers
  tstSphericalCoordinateHelpers.cpp 
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstSphericalCoordinateHelpers utility_core)
ADD_TEST(SphericalCoordinateHelpers_test tstSphericalCoordinateHelpers)
SET_PROPERTY(TEST SphericalCoordinateHelpers_test PROPERTY LABELS utility_core)

ADD_EXECUTABLE(tstDataProcessor
  tstDataProcessor.cpp 
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstDataProcessor utility_core)
ADD_TEST(DataProcessor_test tstDataProcessor)
SET_PROPERTY(TEST DataProcessor_test PROPERTY LABELS utility_core)

ADD_EXECUTABLE(tstFortranStringHelpers
  tstFortranStringHelpers.cpp 
  string_conversion.F90 
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstFortranStringHelpers utility_core)
ADD_TEST(FortranStringHelpers_test tstFortranStringHelpers)
SET_PROPERTY(TEST FortranStringHelpers_test PROPERTY LABELS utility_core)

ADD_EXECUTABLE(tstFortranFileHelpers
  tstFortranFileHelpers.cpp )
TARGET_LINK_LIBRARIES(tstFortranFileHelpers utility_core)
ADD_TEST(FortranFileHelpers_test tstFortranFileHelpers
--test_file="${CMAKE_CURRENT_SOURCE_DIR}/test_files/check_file.txt")
SET_PROPERTY(TEST FortranFileHelpers_test PROPERTY LABELS utility_core)

ADD_EXECUTABLE(tstKinematicHelpers
  tstKinematicHelpers.cpp
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstKinematicHelpers utility_core)
ADD_TEST(KinematicHelpers_test tstKinematicHelpers)
SET_PROPERTY(TEST KinematicHelpers_test PROPERTY LABELS utility_core)

ADD_EXECUTABLE(tstGridGenerator
  tstGridGenerator.cpp
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstGridGenerator utility_core)
ADD_TEST(GridGenerator_test tstGridGenerator)
SET_PROPERTY(TEST GridGenerator_test PROPERTY LABELS utility_core)

ADD_EXECUTABLE(tstTetrahedronHelpers
  tstTetrahedronHelpers.cpp
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstTetrahedronHelpers utility_core)
ADD_TEST(TetrahedronHelpers_test tstTetrahedronHelpers)
SET_PROPERTY(TEST TetrahedronHelpers_test PROPERTY LABELS utility_core)

ADD_EXECUTABLE(tstStandardHashBasedGridSearcher
  tstStandardHashBasedGridSearcher.cpp)
TARGET_LINK_LIBRARIES(tstStandardHashBasedGridSearcher utility_core)
ADD_TEST(StandardHashBasedGridSearcher_test tstStandardHashBasedGridSearcher)
SET_PROPERTY(TEST StandardHashBasedGridSearcher_test PROPERTY LABELS utility_core)

ADD_EXECUTABLE(tstArrayString tstArrayString.cpp)
TARGET_LINK_LIBRARIES(tstArrayString utility_core)
ADD_TEST(ArrayString_test tstArrayString --test_array_xml_file="${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_arrays.xml")
SET_PROPERTY(TEST ArrayString_test PROPERTY LABELS utility_core)

ADD_EXECUTABLE(tstMeasurement
  tstMeasurement.cpp
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstMeasurement utility_core)
ADD_TEST(Measurement_test tstMeasurement)
SET_PROPERTY(TEST Measurement_test PROPERTY LABELS utility_core)

ADD_EXECUTABLE(tstActiveCounter
  tstActiveCounter.cpp
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstActiveCounter utility_core)
ADD_TEST(ActiveCounter_test tstActiveCounter)
SET_PROPERTY(TEST ActiveCounter_test PROPERTY LABELS utility_core)

ADD_EXECUTABLE(tstInactiveCounter
  tstInactiveCounter.cpp
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstInactiveCounter utility_core)
ADD_TEST(InactiveCounter_test tstInactiveCounter)
SET_PROPERTY(TEST InactiveCounter_test PROPERTY LABELS utility_core)

ADD_EXECUTABLE(tstIncrementPolicy
  tstIncrementPolicy.cpp
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstIncrementPolicy utility_core)
ADD_TEST(IncrementPolicy_test tstIncrementPolicy)
SET_PROPERTY(TEST IncrementPolicy_test PROPERTY LABELS utility_core)
