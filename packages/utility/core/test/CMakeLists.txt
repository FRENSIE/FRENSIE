##---------------------------------------------------------------------------##
# Before the FRENSIE unit test framework can be used we must test all of the
# dependecies using another test framework. These first tests will all use
# the Boost unit test framework.
##---------------------------------------------------------------------------##
ADD_EXECUTABLE(tstAssertion tstAssertion.cpp)
TARGET_LINK_LIBRARIES(tstAssertion utility_core ${BOOST_TEST_LIBRARY})
ADD_TEST(Assertion_test tstAssertion --report_level=detailed)
SET_PROPERTY(TEST Assertion_test PROPERTY LABELS utility_core)

ADD_EXECUTABLE(tstElectronVoltUnit tstElectronVoltUnit.cpp)
TARGET_LINK_LIBRARIES(tstElectronVoltUnit utility_core ${BOOST_TEST_LIBRARY})
ADD_TEST(ElectronVoltUnit_test tstElectronVoltUnit --report_level=detailed)
SET_PROPERTY(TEST ElectronVoltUnit_test PROPERTY LABELS utility_core)

ADD_EXECUTABLE(tstAngstromUnit tstAngstromUnit.cpp)
TARGET_LINK_LIBRARIES(tstAngstromUnit utility_core ${BOOST_TEST_LIBRARY})
ADD_TEST(AngstromUnit_test tstAngstromUnit --report_level=detailed)
SET_PROPERTY(TEST AngstromUnit_test PROPERTY LABELS utility_core)

ADD_EXECUTABLE(tstBarnUnit tstBarnUnit.cpp)
TARGET_LINK_LIBRARIES(tstBarnUnit utility_core ${BOOST_TEST_LIBRARY})
ADD_TEST(BarnUnit_test tstBarnUnit --report_level=detailed)
SET_PROPERTY(TEST BarnUnit_test PROPERTY LABELS utility_core)

ADD_EXECUTABLE(tstInverseAngstromUnit tstInverseAngstromUnit.cpp)
TARGET_LINK_LIBRARIES(tstInverseAngstromUnit utility_core ${BOOST_TEST_LIBRARY})
ADD_TEST(InverseAngstromUnit_test tstInverseAngstromUnit --report_level=detailed)
SET_PROPERTY(TEST InverseAngstromUnit_test PROPERTY LABELS utility_core)

ADD_EXECUTABLE(tstInverseCentimeterUnit tstInverseCentimeterUnit.cpp)
TARGET_LINK_LIBRARIES(tstInverseCentimeterUnit utility_core ${BOOST_TEST_LIBRARY})
ADD_TEST(InverseCentimeterUnit_test tstInverseCentimeterUnit --report_level=detailed)
SET_PROPERTY(TEST InverseCentimeterUnit_test PROPERTY LABELS utility_core)

ADD_EXECUTABLE(tstInverseLengthConversion tstInverseLengthConversion.cpp)
TARGET_LINK_LIBRARIES(tstInverseLengthConversion utility_core ${BOOST_TEST_LIBRARY})
ADD_TEST(InverseLengthConversion_test tstInverseLengthConversion --report_level=detailed)
SET_PROPERTY(TEST InverseLengthConversion_test PROPERTY LABELS utility_core)

ADD_EXECUTABLE(tstInverseSquareAngstromUnit tstInverseSquareAngstromUnit.cpp)
TARGET_LINK_LIBRARIES(tstInverseSquareAngstromUnit utility_core ${BOOST_TEST_LIBRARY})
ADD_TEST(InverseSquareAngstromUnit_test tstInverseSquareAngstromUnit --report_level=detailed)
SET_PROPERTY(TEST InverseSquareAngstromUnit_test PROPERTY LABELS utility_core)

ADD_EXECUTABLE(tstInverseSquareCentimeterUnit tstInverseSquareCentimeterUnit.cpp)
TARGET_LINK_LIBRARIES(tstInverseSquareCentimeterUnit utility_core ${BOOST_TEST_LIBRARY})
ADD_TEST(InverseSquareCentimeterUnit_test tstInverseSquareCentimeterUnit --report_level=detailed)
SET_PROPERTY(TEST InverseSquareCentimeterUnit_test PROPERTY LABELS utility_core)

ADD_EXECUTABLE(tstInverseAreaConversion tstInverseAreaConversion.cpp)
TARGET_LINK_LIBRARIES(tstInverseAreaConversion utility_core ${BOOST_TEST_LIBRARY})
ADD_TEST(InverseAreaConversion_test tstInverseAreaConversion --report_level=detailed)
SET_PROPERTY(TEST InverseAreaConversion_test PROPERTY LABELS utility_core)

ADD_EXECUTABLE(tstAtomUnit tstAtomUnit.cpp)
TARGET_LINK_LIBRARIES(tstAtomUnit utility_core ${BOOST_TEST_LIBRARY})
ADD_TEST(AtomUnit_test tstAtomUnit --report_level=detailed)
SET_PROPERTY(TEST AtomUnit_test PROPERTY LABELS utility_core)

ADD_EXECUTABLE(tstShakeUnit tstShakeUnit.cpp)
TARGET_LINK_LIBRARIES(tstShakeUnit utility_core ${BOOST_TEST_LIBRARY})
ADD_TEST(ShakeUnit_test tstShakeUnit --report_level=detailed)
SET_PROPERTY(TEST ShakeUnit_test PROPERTY LABELS utility_core)

ADD_EXECUTABLE(tstAtomicMomentumUnit tstAtomicMomentumUnit.cpp)
TARGET_LINK_LIBRARIES(tstAtomicMomentumUnit utility_core ${BOOST_TEST_LIBRARY})
ADD_TEST(AtomicMomentumUnit_test tstAtomicMomentumUnit --report_level=detailed)
SET_PROPERTY(TEST AtomicMomentumUnit_test PROPERTY LABELS utility_core)

ADD_EXECUTABLE(tstMeCMomentumUnit tstMeCMomentumUnit.cpp)
TARGET_LINK_LIBRARIES(tstMeCMomentumUnit utility_core ${BOOST_TEST_LIBRARY})
ADD_TEST(MeCMomentumUnit_test tstMeCMomentumUnit --report_level=detailed)
SET_PROPERTY(TEST MeCMomentumUnit_test PROPERTY LABELS utility_core)

ADD_EXECUTABLE(tstMomentumConversion tstMomentumConversion.cpp)
TARGET_LINK_LIBRARIES(tstMomentumConversion utility_core ${BOOST_TEST_LIBRARY})
ADD_TEST(MomentumConversion_test tstMomentumConversion --report_level=detailed)
SET_PROPERTY(TEST MomentumConversion_test PROPERTY LABELS utility_core)

ADD_EXECUTABLE(tstInverseAtomicMomentumUnit tstInverseAtomicMomentumUnit.cpp)
TARGET_LINK_LIBRARIES(tstInverseAtomicMomentumUnit utility_core ${BOOST_TEST_LIBRARY})
ADD_TEST(InverseAtomicMomentumUnit_test tstInverseAtomicMomentumUnit --report_level=detailed)
SET_PROPERTY(TEST InverseAtomicMomentumUnit_test PROPERTY LABELS utility_core)

ADD_EXECUTABLE(tstInverseMeCMomentumUnit tstInverseMeCMomentumUnit.cpp)
TARGET_LINK_LIBRARIES(tstInverseMeCMomentumUnit utility_core ${BOOST_TEST_LIBRARY})
ADD_TEST(InverseMeCMomentumUnit_test tstInverseMeCMomentumUnit --report_level=detailed)
SET_PROPERTY(TEST InverseMeCMomentumUnit_test PROPERTY LABELS utility_core)

ADD_EXECUTABLE(tstInverseMomentumConversion tstInverseMomentumConversion.cpp)
TARGET_LINK_LIBRARIES(tstInverseMomentumConversion utility_core ${BOOST_TEST_LIBRARY})
ADD_TEST(InverseMomentumConversion_test tstInverseMomentumConversion --report_level=detailed)
SET_PROPERTY(TEST InverseMomentumConversion_test PROPERTY LABELS utility_core)

ADD_EXECUTABLE(tstAtomicMassUnit tstAtomicMassUnit.cpp)
TARGET_LINK_LIBRARIES(tstAtomicMassUnit utility_core ${BOOST_TEST_LIBRARY})
ADD_TEST(AtomicMassUnit_test tstAtomicMassUnit --report_level=detailed)
SET_PROPERTY(TEST AtomicMassUnit_test PROPERTY LABELS utility_core)

ADD_EXECUTABLE(tstUnitTraits tstUnitTraits.cpp)
TARGET_LINK_LIBRARIES(tstUnitTraits utility_core ${BOOST_TEST_LIBRARY})
ADD_TEST(UnitTraits_test tstUnitTraits --report_level=detailed)
SET_PROPERTY(TEST UnitTraits_test PROPERTY LABELS utility_core)

ADD_EXECUTABLE(tstQuantityTraits tstQuantityTraits.cpp)
TARGET_LINK_LIBRARIES(tstQuantityTraits utility_core ${BOOST_TEST_LIBRARY})
ADD_TEST(QuantityTraits_test tstQuantityTraits --report_level=detailed)
SET_PROPERTY(TEST QuantityTraits_test PROPERTY LABELS utility_core)

ADD_EXECUTABLE(tstTypeTraits tstTypeTraits.cpp)
TARGET_LINK_LIBRARIES(tstTypeTraits utility_core ${BOOST_TEST_LIBRARY})
ADD_TEST(TypeTraits_test tstTypeTraits --report_level=detailed)
SET_PROPERTY(TEST TypeTraits_test PROPERTY LABELS utility_core)

ADD_EXECUTABLE(tstToStringTraits tstToStringTraits.cpp)
TARGET_LINK_LIBRARIES(tstToStringTraits utility_core ${BOOST_TEST_LIBRARY})
ADD_TEST(ToStringTraits_test tstToStringTraits --report_level=detailed)
SET_PROPERTY(TEST ToStringTraits_test PROPERTY LABELS utility_core)

ADD_EXECUTABLE(tstFromStringTraits tstFromStringTraits.cpp)
TARGET_LINK_LIBRARIES(tstFromStringTraits utility_core ${BOOST_TEST_LIBRARY})
ADD_TEST(FromStringTraits_test tstFromStringTraits --report_level=detailed)
SET_PROPERTY(TEST FromStringTraits_test PROPERTY LABELS utility_core)

ADD_EXECUTABLE(tstTypeNameTraits tstTypeNameTraits.cpp)
TARGET_LINK_LIBRARIES(tstTypeNameTraits utility_core ${BOOST_TEST_LIBRARY})
ADD_TEST(TypeNameTraits_test tstTypeNameTraits --report_level=detailed)
SET_PROPERTY(TEST TypeNameTraits_test PROPERTY LABELS utility_core)

ADD_EXECUTABLE(tstLogRecordType tstLogRecordType.cpp)
TARGET_LINK_LIBRARIES(tstLogRecordType utility_core ${BOOST_TEST_LIBRARY})
ADD_TEST(LogRecordType_test tstLogRecordType --report_level=detailed)
SET_PROPERTY(TEST LogRecordType_test PROPERTY LABELS utility_core)

ADD_EXECUTABLE(tstIteratorTypeTraits
  tstIteratorTypeTraits.cpp
  ${FRENSIE_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstIteratorTypeTraits utility_core)
ADD_TEST(IteratorTypeTraits_test tstIteratorTypeTraits)
SET_PROPERTY(TEST IteratorTypeTraits_test PROPERTY LABELS utility_core)

ADD_EXECUTABLE(tstStaticOutputFormatter tstStaticOutputFormatter.cpp)
TARGET_LINK_LIBRARIES(tstStaticOutputFormatter utility_core ${BOOST_TEST_LIBRARY})
ADD_TEST(StaticOutputFormatter_test tstStaticOutputFormatter --report_level=detailed)
SET_PROPERTY(TEST StaticOutputFormatter_test PROPERTY LABELS utility_core)

ADD_EXECUTABLE(tstStaticOutputFormatterFactory tstStaticOutputFormatterFactory.cpp)
TARGET_LINK_LIBRARIES(tstStaticOutputFormatterFactory utility_core ${BOOST_TEST_LIBRARY})
ADD_TEST(StaticOutputFormatterFactory_test tstStaticOutputFormatterFactory --report_level=detailed)
SET_PROPERTY(TEST StaticOutputFormatterFactory_test PROPERTY LABELS utility_core)

ADD_EXECUTABLE(tstDynamicOutputFormatter tstDynamicOutputFormatter.cpp)
TARGET_LINK_LIBRARIES(tstDynamicOutputFormatter utility_core ${BOOST_TEST_LIBRARY})
ADD_TEST(DynamicOutputFormatter_test tstDynamicOutputFormatter --report_level=detailed)
SET_PROPERTY(TEST DynamicOutputFormatter_test PROPERTY LABELS utility_core)

ADD_EXECUTABLE(tstDynamicOutputFormatterFactory tstDynamicOutputFormatterFactory.cpp)
TARGET_LINK_LIBRARIES(tstDynamicOutputFormatterFactory utility_core ${BOOST_TEST_LIBRARY})
ADD_TEST(DynamicOutputFormatterFactory_test tstDynamicOutputFormatterFactory --report_level=detailed)
SET_PROPERTY(TEST DynamicOutputFormatterFactory_test PROPERTY LABELS utility_core)

ADD_EXECUTABLE(tstLoggingMacros tstLoggingMacros.cpp)
TARGET_LINK_LIBRARIES(tstLoggingMacros utility_core ${BOOST_TEST_LIBRARY})
ADD_TEST(LoggingMacros_test tstLoggingMacros --report_level=detailed)
SET_PROPERTY(TEST LoggingMacros_test PROPERTY LABELS utility_core)

ADD_EXECUTABLE(tstExceptionCatchMacros tstExceptionCatchMacros.cpp)
TARGET_LINK_LIBRARIES(tstExceptionCatchMacros utility_core ${BOOST_TEST_LIBRARY})
ADD_TEST(ExceptionCatchMacros_test tstExceptionCatchMacros --report_level=detailed)
SET_PROPERTY(TEST ExceptionCatchMacros_test PROPERTY LABELS utility_core)

ADD_EXECUTABLE(tstContractException tstContractException.cpp)
TARGET_LINK_LIBRARIES(tstContractException utility_core ${BOOST_TEST_LIBRARY})
ADD_TEST(ContractException_test tstContractException --report_level=detailed)
SET_PROPERTY(TEST ContractException_test PROPERTY LABELS utility_core)

ADD_EXECUTABLE(tstComparisonPolicy tstComparisonPolicy.cpp)
TARGET_LINK_LIBRARIES(tstComparisonPolicy utility_core ${BOOST_TEST_LIBRARY})
ADD_TEST(ComparisonPolicy_test tstComparisonPolicy --report_level=detailed)
SET_PROPERTY(TEST ComparisonPolicy_test PROPERTY LABELS utility_core)

ADD_EXECUTABLE(tstComparisonTraits tstComparisonTraits.cpp)
TARGET_LINK_LIBRARIES(tstComparisonTraits utility_core ${BOOST_TEST_LIBRARY})
ADD_TEST(ComparisonTraits_test tstComparisonTraits --report_level=detailed)
SET_PROPERTY(TEST ComparisonTraits_test PROPERTY LABELS utility_core)

ADD_EXECUTABLE(tstTuple tstTuple.cpp)
TARGET_LINK_LIBRARIES(tstTuple utility_core ${BOOST_TEST_LIBRARY})
ADD_TEST(Tuple_test tstTuple --report_level=detailed)
SET_PROPERTY(TEST Tuple_test PROPERTY LABELS utility_core)

ADD_EXECUTABLE(tstView tstView.cpp)
TARGET_LINK_LIBRARIES(tstView utility_core ${BOOST_TEST_LIBRARY})
ADD_TEST(View_test tstView --report_level=detailed)
SET_PROPERTY(TEST View_test PROPERTY LABELS utility_core)

ADD_EXECUTABLE(tstArrayView tstArrayView.cpp)
TARGET_LINK_LIBRARIES(tstArrayView utility_core ${BOOST_TEST_LIBRARY})
ADD_TEST(ArrayView_test tstArrayView --report_level=detailed)
SET_PROPERTY(TEST ArrayView_test PROPERTY LABELS utility_core)

ADD_EXECUTABLE(tstArray tstArray.cpp)
TARGET_LINK_LIBRARIES(tstArray utility_core ${BOOST_TEST_LIBRARY})
ADD_TEST(Array_test tstArray --report_level=detailed)
SET_PROPERTY(TEST Array_test PROPERTY LABELS utility_core)

ADD_EXECUTABLE(tstVector tstVector.cpp)
TARGET_LINK_LIBRARIES(tstVector utility_core ${BOOST_TEST_LIBRARY})
ADD_TEST(Vector_test tstVector --report_level=detailed)
SET_PROPERTY(TEST Vector_test PROPERTY LABELS utility_core)

ADD_EXECUTABLE(tstList tstList.cpp)
TARGET_LINK_LIBRARIES(tstList utility_core ${BOOST_TEST_LIBRARY})
ADD_TEST(List_test tstList --report_level=detailed)
SET_PROPERTY(TEST List_test PROPERTY LABELS utility_core)

ADD_EXECUTABLE(tstDeque tstDeque.cpp)
TARGET_LINK_LIBRARIES(tstDeque utility_core ${BOOST_TEST_LIBRARY})
ADD_TEST(Deque_test tstDeque --report_level=detailed)
SET_PROPERTY(TEST Deque_test PROPERTY LABELS utility_core)

ADD_EXECUTABLE(tstSet tstSet.cpp)
TARGET_LINK_LIBRARIES(tstSet utility_core ${BOOST_TEST_LIBRARY})
ADD_TEST(Set_test tstSet --report_level=detailed)
SET_PROPERTY(TEST Set_test PROPERTY LABELS utility_core)

ADD_EXECUTABLE(tstMap tstMap.cpp)
TARGET_LINK_LIBRARIES(tstMap utility_core ${BOOST_TEST_LIBRARY})
ADD_TEST(Map_test tstMap --report_level=detailed)
SET_PROPERTY(TEST Map_test PROPERTY LABELS utility_core)

ADD_EXECUTABLE(tstVariant tstVariant.cpp)
TARGET_LINK_LIBRARIES(tstVariant utility_core ${BOOST_TEST_LIBRARY})
ADD_TEST(Variant_test tstVariant --report_level=detailed)
SET_PROPERTY(TEST Variant_test PROPERTY LABELS utility_core)

ADD_EXECUTABLE(tstStandardTimer tstStandardTimer.cpp)
TARGET_LINK_LIBRARIES(tstStandardTimer utility_core ${BOOST_TEST_LIBRARY})
ADD_TEST(StandardTimer_test tstStandardTimer --report_level=detailed)
SET_PROPERTY(TEST StandardTimer_test PROPERTY LABLES utility_core)

ADD_EXECUTABLE(tstGlobalOpenMPSession tstGlobalOpenMPSession.cpp)
TARGET_LINK_LIBRARIES(tstGlobalOpenMPSession utility_core ${BOOST_TEST_LIBRARY})
ADD_TEST(GlobalOpenMPSession_test tstGlobalOpenMPSession --report_level=detailed)
SET_PROPERTY(TEST GlobalOpenMPSession_test PROPERTY LABELS utility_core)

ADD_EXECUTABLE(tstGlobalMPISessionInit tstGlobalMPISessionInit.cpp)
TARGET_LINK_LIBRARIES(tstGlobalMPISessionInit utility_core ${BOOST_TEST_LIBRARY})

SET(MPI_TEST_EXEC_PREAMBLE "")

IF(${FRENSIE_ENABLE_MPI})
  SET(MPI_TEST_EXEC_PREAMBLE ${MPIEXEC} -n 4)
ENDIF()

ADD_TEST(GlobalMPISessionDefaultInit_test ${MPI_TEST_EXEC_PREAMBLE} tstGlobalMPISessionInit --constructor_type=default --report_level=detailed)
SET_PROPERTY(TEST GlobalMPISessionDefaultInit_test PROPERTY LABELS utility_core)
ADD_TEST(GlobalMPISessionAdvancedInit_test ${MPI_TEST_EXEC_PREAMBLE} tstGlobalMPISessionInit --constructor_type=advanced --report_level=detailed)
SET_PROPERTY(TEST GlobalMPISessionAdvancedInit_test PROPERTY LABELS utility_core)
ADD_TEST(GlobalMPISessionBasicSingleThreadingInit_test ${MPI_TEST_EXEC_PREAMBLE} tstGlobalMPISessionInit --constructor_type=basic_single --report_level=detailed)
SET_PROPERTY(TEST GlobalMPISessionBasicSingleThreadingInit_test PROPERTY LABELS utility_core)
ADD_TEST(GlobalMPISessionAdvancedSingleThreadingInit_test ${MPI_TEST_EXEC_PREAMBLE} tstGlobalMPISessionInit --constructor_type=advanced_single --report_level=detailed)
SET_PROPERTY(TEST GlobalMPISessionAdvancedSingleThreadingInit_test PROPERTY LABELS utility_core)
ADD_TEST(GlobalMPISessionBasicFunneledThreadingInit_test ${MPI_TEST_EXEC_PREAMBLE} tstGlobalMPISessionInit --constructor_type=basic_funneled --report_level=detailed)
SET_PROPERTY(TEST GlobalMPISessionBasicFunneledThreadingInit_test PROPERTY LABELS utility_core)
ADD_TEST(GlobalMPISessionAdvancedFunneledThreadingInit_test ${MPI_TEST_EXEC_PREAMBLE} tstGlobalMPISessionInit --constructor_type=advanced_funneled --report_level=detailed)
SET_PROPERTY(TEST GlobalMPISessionAdvancedFunneledThreadingInit_test PROPERTY LABELS utility_core)
ADD_TEST(GlobalMPISessionBasicSerializedThreadingInit_test ${MPI_TEST_EXEC_PREAMBLE} tstGlobalMPISessionInit --constructor_type=basic_serialized --report_level=detailed)
SET_PROPERTY(TEST GlobalMPISessionBasicSerializedThreadingInit_test PROPERTY LABELS utility_core)
ADD_TEST(GlobalMPISessionAdvancedSerializedThreadingInit_test ${MPI_TEST_EXEC_PREAMBLE} tstGlobalMPISessionInit --constructor_type=advanced_serialized --report_level=detailed)
SET_PROPERTY(TEST GlobalMPISessionAdvancedSerializedThreadingInit_test PROPERTY LABELS utility_core)
ADD_TEST(GlobalMPISessionBasicMultipleThreadingInit_test ${MPI_TEST_EXEC_PREAMBLE} tstGlobalMPISessionInit --constructor_type=basic_multiple --report_level=detailed)
SET_PROPERTY(TEST GlobalMPISessionBasicMultipleThreadingInit_test PROPERTY LABELS utility_core)
ADD_TEST(GlobalMPISessionAdvancedMultipleThreadingInit_test ${MPI_TEST_EXEC_PREAMBLE} tstGlobalMPISessionInit --constructor_type=advanced_multiple --report_level=detailed)
SET_PROPERTY(TEST GlobalMPISessionAdvancedMultipleThreadingInit_test PROPERTY LABELS utility_core)

UNSET(MPI_TEST_EXEC_PREAMBLE)

ADD_EXECUTABLE(tstGlobalMPISession tstGlobalMPISession.cpp)
TARGET_LINK_LIBRARIES(tstGlobalMPISession utility_core ${BOOST_TEST_LIBRARY})
ADD_TEST(GlobalMPISession_test tstGlobalMPISession --report_level=detailed)
SET_PROPERTY(TEST GlobalMPISession_test PROPERTY LABELS utility_core)

IF(${FRENSIE_ENABLE_MPI})
  ADD_TEST(GlobalMPISession_2_test ${MPIEXEC} -n 2 tstGlobalMPISession --report_level=detailed)
  SET_PROPERTY(TEST GlobalMPISession_2_test PROPERTY LABELS utility_core)
  
  ADD_TEST(GlobalMPISession_4_test ${MPIEXEC} -n 4 tstGlobalMPISession --report_level=detailed)
  SET_PROPERTY(TEST GlobalMPISession_4_test PROPERTY LABELS utility_core)
ENDIF()

ADD_EXECUTABLE(tstUnitTest tstUnitTest.cpp)
TARGET_LINK_LIBRARIES(tstUnitTest utility_core ${BOOST_TEST_LIBRARY})
ADD_TEST(UnitTest_test tstUnitTest --report_level=detailed)
SET_PROPERTY(TEST UnitTest_test PROPERTY LABELS utility_core)

ADD_EXECUTABLE(tstUnitTestDataTable tstUnitTestDataTable.cpp)
TARGET_LINK_LIBRARIES(tstUnitTestDataTable utility_core ${BOOST_TEST_LIBRARY})
ADD_TEST(UnitTestDataTable_test tstUnitTestDataTable --report_level=detailed)
SET_PROPERTY(TEST UnitTestDataTable_test PROPERTY LABELS utility_core)

ADD_EXECUTABLE(tstDataUnitTest tstDataUnitTest.cpp)
TARGET_LINK_LIBRARIES(tstDataUnitTest utility_core ${BOOST_TEST_LIBRARY})
ADD_TEST(DataUnitTest_test tstDataUnitTest --report_level=detailed)
SET_PROPERTY(TEST DataUnitTest_test PROPERTY LABELS utility_core)

ADD_EXECUTABLE(tstDataUnitTestWrapper tstDataUnitTestWrapper.cpp)
TARGET_LINK_LIBRARIES(tstDataUnitTestWrapper utility_core ${BOOST_TEST_LIBRARY})
ADD_TEST(DataUnitTestWrapper_test tstDataUnitTestWrapper --report_level=detailed)
SET_PROPERTY(TEST DataUnitTestWrapper_test PROPERTY LABELS utility_core)

ADD_EXECUTABLE(tstTemplateUnitTest tstTemplateUnitTest.cpp)
TARGET_LINK_LIBRARIES(tstTemplateUnitTest utility_core ${BOOST_TEST_LIBRARY})
ADD_TEST(TemplateUnitTest_test tstTemplateUnitTest --report_level=detailed)
SET_PROPERTY(TEST TemplateUnitTest_test PROPERTY LABELS utility_core)

ADD_EXECUTABLE(tstTemplateUnitTestWrapper tstTemplateUnitTestWrapper.cpp)
TARGET_LINK_LIBRARIES(tstTemplateUnitTestWrapper utility_core ${BOOST_TEST_LIBRARY})
ADD_TEST(TemplateUnitTestWrapper_test tstTemplateUnitTestWrapper --report_level=detailed)
SET_PROPERTY(TEST TemplateUnitTestWrapper_test PROPERTY LABELS utility_core)

ADD_EXECUTABLE(tstFRENSIEUnitTestHarnessDefaultInit tstFRENSIEUnitTestHarnessDefaultInit)
TARGET_LINK_LIBRARIES(tstFRENSIEUnitTestHarnessDefaultInit utility_core)
ADD_TEST(FRENSIEUnitTestHarnessDefaultInit_test tstFRENSIEUnitTestHarnessDefaultInit --report_level=detailed)
SET_PROPERTY(TEST FRENSIEUnitTestHarnessDefaultInit_test PROPERTY LABELS utility_core)

IF(${FRENSIE_ENABLE_MPI})
  ADD_TEST(FRENSIEUnitTestHarnessDefaultInit_2_test ${MPIEXEC} -n 2 tstFRENSIEUnitTestHarnessDefaultInit)
  SET_PROPERTY(TEST FRENSIEUnitTestHarnessDefaultInit_2_test PROPERTY LABELS utility_core)

  ADD_TEST(FRENSIEUnitTestHarnessDefaultInit_4_test ${MPIEXEC} -n 4 tstFRENSIEUnitTestHarnessDefaultInit)
  SET_PROPERTY(TEST FRENSIEUnitTestHarnessDefaultInit_4_test PROPERTY LABELS utility_core)
ENDIF()

ADD_EXECUTABLE(tstFRENSIEUnitTestHarnessCustomInit tstFRENSIEUnitTestHarnessCustomInit)
TARGET_LINK_LIBRARIES(tstFRENSIEUnitTestHarnessCustomInit utility_core)
ADD_TEST(FRENSIEUnitTestHarnessCustomInit_test tstFRENSIEUnitTestHarnessCustomInit --number_of_tests=46 --number_of_checks=76)
SET_PROPERTY(TEST FRENSIEUnitTestHarnessCustomInit_test PROPERTY LABELS utility_core)

# Check that no tests are run if the -h flag is passed
ADD_TEST(FRENSIEUnitTestHarnessCustomInit_h_flag_test tstFRENSIEUnitTestHarnessCustomInit -h --number_of_tests=0 --number_of_checks=0)
SET_PROPERTY(TEST FRENSIEUnitTestHarnessCustomInit_h_flag_test PROPERTY LABELS utility_core)

# Check that no tests are run if the --help flag is passed
ADD_TEST(FRENSIEUnitTestHarnessCustomInit_help_flag_test tstFRENSIEUnitTestHarnessCustomInit --help --number_of_tests=0 --number_of_checks=0)
SET_PROPERTY(TEST FRENSIEUnitTestHarnessCustomInit_help_flag_test PROPERTY LABELS utility_core)

# Check that no tests are run if the -g flag is passed
ADD_TEST(FRENSIEUnitTestHarnessCustomInit_g_flag_test tstFRENSIEUnitTestHarnessCustomInit -g --number_of_tests=0 --number_of_checks=0)
SET_PROPERTY(TEST FRENSIEUnitTestHarnessCustomInit_g_flag_test PROPERTY LABELS utility_core)

# Check that no tests are run if the --show_groups flag is passed
ADD_TEST(FRENSIEUnitTestHarnessCustomInit_show_groups_flag_test tstFRENSIEUnitTestHarnessCustomInit --show_groups --number_of_tests=0 --number_of_checks=0)
SET_PROPERTY(TEST FRENSIEUnitTestHarnessCustomInit_show_groups_flag_test PROPERTY LABELS utility_core)

# Check that no tests are run if the -t flag is passed
ADD_TEST(FRENSIEUnitTestHarnessCustomInit_t_flag_test tstFRENSIEUnitTestHarnessCustomInit -t --number_of_tests=0 --number_of_checks=0)
SET_PROPERTY(TEST FRENSIEUnitTestHarnessCustomInit_t_flag_test PROPERTY LABELS utility_core)

# Check that no tests are run if the --show_tests flag is passed
ADD_TEST(FRENSIEUnitTestHarnessCustomInit_show_tests_flag_test tstFRENSIEUnitTestHarnessCustomInit -show_tests --number_of_tests=0 --number_of_checks=0)
SET_PROPERTY(TEST FRENSIEUnitTestHarnessCustomInit_show_tests_flag_test PROPERTY LABELS utility_core)

# Check that no tests are run if the -d flag is passed
ADD_TEST(FRENSIEUnitTestHarnessCustomInit_d_flag_test tstFRENSIEUnitTestHarnessCustomInit -d --number_of_tests=0 --number_of_checks=0)
SET_PROPERTY(TEST FRENSIEUnitTestHarnessCustomInit_d_flag_test PROPERTY LABELS utility_core)

# Check that no tests are run if the --show_data flag is passed
ADD_TEST(FRENSIEUnitTestHarnessCustomInit_show_data_flag_test tstFRENSIEUnitTestHarnessCustomInit --show_data --number_of_tests=0 --number_of_checks=0)
SET_PROPERTY(TEST FRENSIEUnitTestHarnessCustomInit_show_data_flag_test PROPERTY LABELS utility_core)

# Check that the test group can be filtered
ADD_TEST(FRENSIEUnitTestHarnessCustomInit_group_filter_test tstFRENSIEUnitTestHarnessCustomInit --group_filter=CHECK --number_of_tests=8 --number_of_checks=16)
SET_PROPERTY(TEST FRENSIEUnitTestHarnessCustomInit_group_filter_test PROPERTY LABELS utility_core)

# Check that the tests can be filtered
ADD_TEST(FRENSIEUnitTestHarnessCustomInit_test_filter_test tstFRENSIEUnitTestHarnessCustomInit --test_filter=EQUAL --number_of_tests=34 --number_of_checks=53)
SET_PROPERTY(TEST FRENSIEUnitTestHarnessCustomInit_test_filter_test PROPERTY LABELS utility_core)

# Check that the data can be filtered
ADD_TEST(FRENSIEUnitTestHarnessCustomInit_data_filter_test tstFRENSIEUnitTestHarnessCustomInit --data_filter=zero_input --number_of_tests=1 --number_of_checks=1)
SET_PROPERTY(TEST FRENSIEUnitTestHarnessCustomInit_data_filter_test PROPERTY LABELS utility_core)

# Check that multiple filters can be applied
ADD_TEST(FRENSIEUnitTestHarnessCustomInit_multiple_filter_test tstFRENSIEUnitTestHarnessCustomInit --group_filter=REQUIRE --test_filter=SMALL --number_of_tests=1 --number_of_checks=3)
SET_PROPERTY(TEST FRENSIEUnitTestHarnessCustomInit_multiple_filter_test PROPERTY LABELS utility_core)

IF(${FRENSIE_ENABLE_MPI})
  ADD_TEST(FRENSIEUnitTestHarnessCustomInit_2_test ${MPIEXEC} -n 2 tstFRENSIEUnitTestHarnessCustomInit --number_of_tests=46 --number_of_checks=76)
  SET_PROPERTY(TEST FRENSIEUnitTestHarnessCustomInit_test PROPERTY LABELS utility_core)

  # Check that no tests are run if the -h flag is passed
  ADD_TEST(FRENSIEUnitTestHarnessCustomInit_h_flag_2_test ${MPIEXEC} -n 2 tstFRENSIEUnitTestHarnessCustomInit -h --number_of_tests=0 --number_of_checks=0)
  SET_PROPERTY(TEST FRENSIEUnitTestHarnessCustomInit_h_flag_2_test PROPERTY LABELS utility_core)

  # Check that no tests are run if the --help flag is passed
  ADD_TEST(FRENSIEUnitTestHarnessCustomInit_help_flag_2_test ${MPIEXEC} -n 2 tstFRENSIEUnitTestHarnessCustomInit --help --number_of_tests=0 --number_of_checks=0)
  SET_PROPERTY(TEST FRENSIEUnitTestHarnessCustomInit_help_flag_2_test PROPERTY LABELS utility_core)
  
  # Check that no tests are run if the -g flag is passed
  ADD_TEST(FRENSIEUnitTestHarnessCustomInit_g_flag_2_test ${MPIEXEC} -n 2 tstFRENSIEUnitTestHarnessCustomInit -g --number_of_tests=0 --number_of_checks=0)
  SET_PROPERTY(TEST FRENSIEUnitTestHarnessCustomInit_g_flag_2_test PROPERTY LABELS utility_core)
  
  # Check that no tests are run if the --show_groups flag is passed
  ADD_TEST(FRENSIEUnitTestHarnessCustomInit_show_groups_flag_2_test ${MPIEXEC} -n 2 tstFRENSIEUnitTestHarnessCustomInit --show_groups --number_of_tests=0 --number_of_checks=0)
  SET_PROPERTY(TEST FRENSIEUnitTestHarnessCustomInit_show_groups_flag_2_test PROPERTY LABELS utility_core)
  
  # Check that no tests are run if the -t flag is passed
  ADD_TEST(FRENSIEUnitTestHarnessCustomInit_t_flag_2_test ${MPIEXEC} -n 2 tstFRENSIEUnitTestHarnessCustomInit -t --number_of_tests=0 --number_of_checks=0)
  SET_PROPERTY(TEST FRENSIEUnitTestHarnessCustomInit_t_flag_2_test PROPERTY LABELS utility_core)
  
  # Check that no tests are run if the --show_tests flag is passed
  ADD_TEST(FRENSIEUnitTestHarnessCustomInit_show_tests_flag_2_test ${MPIEXEC} -n 2 tstFRENSIEUnitTestHarnessCustomInit -show_tests --number_of_tests=0 --number_of_checks=0)
  SET_PROPERTY(TEST FRENSIEUnitTestHarnessCustomInit_show_tests_flag_2_test PROPERTY LABELS utility_core)

  # Check that no tests are run if the -d flag is passed
  ADD_TEST(FRENSIEUnitTestHarnessCustomInit_d_flag_2_test ${MPIEXEC} -n 2 tstFRENSIEUnitTestHarnessCustomInit -d --number_of_tests=0 --number_of_checks=0)
  SET_PROPERTY(TEST FRENSIEUnitTestHarnessCustomInit_d_flag_test PROPERTY LABELS utility_core)
  
  # Check that no tests are run if the --show_data flag is passed
  ADD_TEST(FRENSIEUnitTestHarnessCustomInit_show_data_flag_2_test ${MPIEXEC} -n 2 tstFRENSIEUnitTestHarnessCustomInit --show_data --number_of_tests=0 --number_of_checks=0)
  SET_PROPERTY(TEST FRENSIEUnitTestHarnessCustomInit_show_data_flag_2_test PROPERTY LABELS utility_core)
  
  # Check that the test group can be filtered
  ADD_TEST(FRENSIEUnitTestHarnessCustomInit_group_filter_2_test ${MPIEXEC} -n 2 tstFRENSIEUnitTestHarnessCustomInit --group_filter=CHECK --number_of_tests=8 --number_of_checks=16)
  SET_PROPERTY(TEST FRENSIEUnitTestHarnessCustomInit_group_filter_2_test PROPERTY LABELS utility_core)
  
  # Check that the tests can be filtered
  ADD_TEST(FRENSIEUnitTestHarnessCustomInit_test_filter_2_test ${MPIEXEC} -n 2 tstFRENSIEUnitTestHarnessCustomInit --test_filter=EQUAL --number_of_tests=34 --number_of_checks=53)
  SET_PROPERTY(TEST FRENSIEUnitTestHarnessCustomInit_test_filter_2_test PROPERTY LABELS utility_core)
  
  # Check that the data can be filtered
  ADD_TEST(FRENSIEUnitTestHarnessCustomInit_data_filter_2_test ${MPIEXEC} -n 2 tstFRENSIEUnitTestHarnessCustomInit --data_filter=zero_input --number_of_tests=1 --number_of_checks=1)
  SET_PROPERTY(TEST FRENSIEUnitTestHarnessCustomInit_data_filter_2_test PROPERTY LABELS utility_core)
  
  # Check that multiple filters can be applied
  ADD_TEST(FRENSIEUnitTestHarnessCustomInit_multiple_filter_2_test ${MPIEXEC} -n 2 tstFRENSIEUnitTestHarnessCustomInit --group_filter=REQUIRE --test_filter=SMALL --number_of_tests=1 --number_of_checks=3)
  SET_PROPERTY(TEST FRENSIEUnitTestHarnessCustomInit_multiple_filter_2_test PROPERTY LABELS utility_core)
ENDIF()

##---------------------------------------------------------------------------##
# All FRENSIE unit test framework dependencies have been tested. All tests
# beyond this point can use the FRENSIE unit tests framework.
##---------------------------------------------------------------------------##
ADD_EXECUTABLE(tstSortAlgorithms tstSortAlgorithms.cpp)
TARGET_LINK_LIBRARIES(tstSortAlgorithms utility_core)
ADD_TEST(SortAlgorithms_test tstSortAlgorithms)
SET_PROPERTY(TEST SortAlgorithms_test PROPERTY LABELS utility_core)

ADD_EXECUTABLE(tstSearchAlgorithms tstSearchAlgorithms.cpp)
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

ADD_EXECUTABLE(tstSpatialCoordinateSystemType
  tstSpatialCoordinateSystemType.cpp
  ${FRENSIE_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstSpatialCoordinateSystemType utility_core)
ADD_TEST(SpatialCoordinateSystemType_test tstSpatialCoordinateSystemType)
SET_PROPERTY(TEST SpatialCoordinateSystemType_test PROPERTY LABELS utility_core )

ADD_EXECUTABLE(tstDirectionalCoordinateSystemType
  tstDirectionalCoordinateSystemType.cpp
  ${FRENSIE_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstDirectionalCoordinateSystemType utility_core)
ADD_TEST(DirectionalCoordinateSystemType_test tstDirectionalCoordinateSystemType)
SET_PROPERTY(TEST DirectionalCoordinateSystemType_test PROPERTY LABELS utility_core )

ADD_EXECUTABLE(tstSpatialDimensionType
  tstSpatialDimensionType.cpp
  ${FRENSIE_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstSpatialDimensionType utility_core)
ADD_TEST(SpatialDimensionType_test tstSpatialDimensionType)
SET_PROPERTY(TEST SpatialDimensionType_test PROPERTY LABELS utility_core )

ADD_EXECUTABLE(tstDirectionalDimensionType
  tstDirectionalDimensionType.cpp
  ${FRENSIE_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstDirectionalDimensionType utility_core)
ADD_TEST(DirectionalDimensionType_test tstDirectionalDimensionType)
SET_PROPERTY(TEST DirectionalDimensionType_test PROPERTY LABELS utility_core )

ADD_EXECUTABLE(tstSpatialCoordinateSystemTraits
  tstSpatialCoordinateSystemTraits.cpp
  ${FRENSIE_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstSpatialCoordinateSystemTraits utility_core)
ADD_TEST(SpatialCoordinateSystemTraits_test tstSpatialCoordinateSystemTraits)
SET_PROPERTY(TEST SpatialCoordinateSystemTraits_test PROPERTY LABELS utility_core )

ADD_EXECUTABLE(tstDirectionalCoordinateSystemTraits
  tstDirectionalCoordinateSystemTraits.cpp
  ${FRENSIE_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstDirectionalCoordinateSystemTraits utility_core)
ADD_TEST(DirectionalCoordinateSystemTraits_test tstDirectionalCoordinateSystemTraits)
SET_PROPERTY(TEST DirectionalCoordinateSystemTraits_test PROPERTY LABELS utility_core )

ADD_EXECUTABLE(tst3DCartesianVectorHelpers
  tst3DCartesianVectorHelpers.cpp
  ${FRENSIE_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tst3DCartesianVectorHelpers utility_core)
ADD_TEST(3DCartesianVectorHelpers_test tst3DCartesianVectorHelpers)
SET_PROPERTY(TEST 3DCartesianVectorHelpers_test PROPERTY LABELS utility_core)

ADD_EXECUTABLE(tstCartesianSpatialCoordinateConversionPolicy
  tstCartesianSpatialCoordinateConversionPolicy.cpp
  ${FRENSIE_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstCartesianSpatialCoordinateConversionPolicy utility_core)
ADD_TEST(CartesianSpatialCoordinateConversionPolicy_test tstCartesianSpatialCoordinateConversionPolicy)
SET_PROPERTY(TEST CartesianSpatialCoordinateConversionPolicy_test PROPERTY LABELS utility_core)

ADD_EXECUTABLE(tstCartesianDirectionalCoordinateConversionPolicy
  tstCartesianDirectionalCoordinateConversionPolicy.cpp
  ${FRENSIE_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstCartesianDirectionalCoordinateConversionPolicy utility_core)
ADD_TEST(CartesianDirectionalCoordinateConversionPolicy_test tstCartesianDirectionalCoordinateConversionPolicy)
SET_PROPERTY(TEST CartesianDirectionalCoordinateConversionPolicy_test PROPERTY LABELS utility_core)

ADD_EXECUTABLE(tstBasicCartesianCoordinateConversionPolicy
  tstBasicCartesianCoordinateConversionPolicy.cpp
  ${FRENSIE_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstBasicCartesianCoordinateConversionPolicy utility_core)
ADD_TEST(BasicCartesianCoordinateConversionPolicy_test tstBasicCartesianCoordinateConversionPolicy)
SET_PROPERTY(TEST BasicCartesianCoordinateConversionPolicy_test PROPERTY LABELS utility_core)

ADD_EXECUTABLE(tstTranslationCartesianSpatialCoordinateConversionPolicy
  tstTranslationCartesianSpatialCoordinateConversionPolicy.cpp
  ${FRENSIE_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstTranslationCartesianSpatialCoordinateConversionPolicy utility_core)
ADD_TEST(TranslationCartesianSpatialCoordinateConversionPolicy_test tstTranslationCartesianSpatialCoordinateConversionPolicy)
SET_PROPERTY(TEST TranslationCartesianSpatialCoordinateConversionPolicy_test PROPERTY LABELS utility_core)

ADD_EXECUTABLE(tstRotationCartesianCoordinateConversionPolicy
  tstRotationCartesianCoordinateConversionPolicy.cpp
  ${FRENSIE_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstRotationCartesianCoordinateConversionPolicy utility_core)
ADD_TEST(RotationCartesianCoordinateConversionPolicy_test tstRotationCartesianCoordinateConversionPolicy)
SET_PROPERTY(TEST RotationCartesianCoordinateConversionPolicy_test PROPERTY LABELS utility_core)

ADD_EXECUTABLE(tstGeneralCartesianSpatialCoordinateConversionPolicy
  tstGeneralCartesianSpatialCoordinateConversionPolicy.cpp
  ${FRENSIE_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstGeneralCartesianSpatialCoordinateConversionPolicy utility_core)
ADD_TEST(GeneralCartesianSpatialCoordinateConversionPolicy_test tstGeneralCartesianSpatialCoordinateConversionPolicy)
SET_PROPERTY(TEST GeneralCartesianSpatialCoordinateConversionPolicy_test PROPERTY LABELS utility_core)

ADD_EXECUTABLE(tstSphericalSpatialCoordinateConversionPolicy
  tstSphericalSpatialCoordinateConversionPolicy.cpp
  ${FRENSIE_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstSphericalSpatialCoordinateConversionPolicy utility_core)
ADD_TEST(SphericalSpatialCoordinateConversionPolicy_test tstSphericalSpatialCoordinateConversionPolicy)
SET_PROPERTY(TEST SphericalSpatialCoordinateConversionPolicy_test PROPERTY LABELS utility_core)

ADD_EXECUTABLE(tstSphericalDirectionalCoordinateConversionPolicy
  tstSphericalDirectionalCoordinateConversionPolicy.cpp
  ${FRENSIE_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstSphericalDirectionalCoordinateConversionPolicy utility_core)
ADD_TEST(SphericalDirectionalCoordinateConversionPolicy_test tstSphericalDirectionalCoordinateConversionPolicy)
SET_PROPERTY(TEST SphericalDirectionalCoordinateConversionPolicy_test PROPERTY LABELS utility_core)

ADD_EXECUTABLE(tstBasicSphericalCoordinateConversionPolicy
  tstBasicSphericalCoordinateConversionPolicy.cpp
  ${FRENSIE_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstBasicSphericalCoordinateConversionPolicy utility_core)
ADD_TEST(BasicSphericalCoordinateConversionPolicy_test tstBasicSphericalCoordinateConversionPolicy)
SET_PROPERTY(TEST BasicSphericalCoordinateConversionPolicy_test PROPERTY LABELS utility_core)

ADD_EXECUTABLE(tstTranslationSphericalSpatialCoordinateConversionPolicy
  tstTranslationSphericalSpatialCoordinateConversionPolicy.cpp
  ${FRENSIE_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstTranslationSphericalSpatialCoordinateConversionPolicy utility_core)
ADD_TEST(TranslationSphericalSpatialCoordinateConversionPolicy_test tstTranslationSphericalSpatialCoordinateConversionPolicy)
SET_PROPERTY(TEST TranslationSphericalSpatialCoordinateConversionPolicy_test PROPERTY LABELS utility_core)

ADD_EXECUTABLE(tstRotationSphericalCoordinateConversionPolicy
  tstRotationSphericalCoordinateConversionPolicy.cpp
  ${FRENSIE_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstRotationSphericalCoordinateConversionPolicy utility_core)
ADD_TEST(RotationSphericalCoordinateConversionPolicy_test tstRotationSphericalCoordinateConversionPolicy)
SET_PROPERTY(TEST RotationSphericalCoordinateConversionPolicy_test PROPERTY LABELS utility_core)

ADD_EXECUTABLE(tstGeneralSphericalSpatialCoordinateConversionPolicy
  tstGeneralSphericalSpatialCoordinateConversionPolicy.cpp
  ${FRENSIE_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstGeneralSphericalSpatialCoordinateConversionPolicy utility_core)
ADD_TEST(GeneralSphericalSpatialCoordinateConversionPolicy_test tstGeneralSphericalSpatialCoordinateConversionPolicy)
SET_PROPERTY(TEST GeneralSphericalSpatialCoordinateConversionPolicy_test PROPERTY LABELS utility_core)

ADD_EXECUTABLE(tstCylindricalSpatialCoordinateConversionPolicy
  tstCylindricalSpatialCoordinateConversionPolicy.cpp
  ${FRENSIE_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstCylindricalSpatialCoordinateConversionPolicy utility_core)
ADD_TEST(CylindricalSpatialCoordinateConversionPolicy_test tstCylindricalSpatialCoordinateConversionPolicy)
SET_PROPERTY(TEST CylindricalSpatialCoordinateConversionPolicy_test PROPERTY LABELS utility_core)

ADD_EXECUTABLE(tstBasicCylindricalSpatialCoordinateConversionPolicy
  tstBasicCylindricalSpatialCoordinateConversionPolicy.cpp
  ${FRENSIE_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstBasicCylindricalSpatialCoordinateConversionPolicy utility_core)
ADD_TEST(BasicCylindricalSpatialCoordinateConversionPolicy_test tstBasicCylindricalSpatialCoordinateConversionPolicy)
SET_PROPERTY(TEST BasicCylindricalSpatialCoordinateConversionPolicy_test PROPERTY LABELS utility_core)

ADD_EXECUTABLE(tstTranslationCylindricalSpatialCoordinateConversionPolicy
  tstTranslationCylindricalSpatialCoordinateConversionPolicy.cpp
  ${FRENSIE_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstTranslationCylindricalSpatialCoordinateConversionPolicy utility_core)
ADD_TEST(TranslationCylindricalSpatialCoordinateConversionPolicy_test tstTranslationCylindricalSpatialCoordinateConversionPolicy)
SET_PROPERTY(TEST TranslationCylindricalSpatialCoordinateConversionPolicy_test PROPERTY LABELS utility_core)

ADD_EXECUTABLE(tstRotationCylindricalSpatialCoordinateConversionPolicy
  tstRotationCylindricalSpatialCoordinateConversionPolicy.cpp
  ${FRENSIE_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstRotationCylindricalSpatialCoordinateConversionPolicy utility_core)
ADD_TEST(RotationCylindricalSpatialCoordinateConversionPolicy_test tstRotationCylindricalSpatialCoordinateConversionPolicy)
SET_PROPERTY(TEST RotationCylindricalSpatialCoordinateConversionPolicy_test PROPERTY LABELS utility_core)

ADD_EXECUTABLE(tstGeneralCylindricalSpatialCoordinateConversionPolicy
  tstGeneralCylindricalSpatialCoordinateConversionPolicy.cpp
  ${FRENSIE_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstGeneralCylindricalSpatialCoordinateConversionPolicy utility_core)
ADD_TEST(GeneralCylindricalSpatialCoordinateConversionPolicy_test tstGeneralCylindricalSpatialCoordinateConversionPolicy)
SET_PROPERTY(TEST GeneralCylindricalSpatialCoordinateConversionPolicy_test PROPERTY LABELS utility_core)

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

ADD_EXECUTABLE(tstSampleMoment
  tstSampleMoment.cpp
  ${FRENSIE_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstSampleMoment utility_core)
ADD_TEST(SampleMoment_test tstSampleMoment)
SET_PROPERTY(TEST SampleMoment_test PROPERTY LABELS utility_core)

ADD_EXECUTABLE(tstSampleMomentCollection
  tstSampleMomentCollection.cpp
  ${FRENSIE_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstSampleMomentCollection utility_core)
ADD_TEST(SampleMomentCollection_test tstSampleMomentCollection)
SET_PROPERTY(TEST SampleMomentCollection_test PROPERTY LABELS utility_core)

ADD_EXECUTABLE(tstMeasurement
  tstMeasurement.cpp
  ${FRENSIE_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstMeasurement utility_core)
ADD_TEST(Measurement_test tstMeasurement)
SET_PROPERTY(TEST Measurement_test PROPERTY LABELS utility_core)

ADD_EXECUTABLE(tstPropertyTree tstPropertyTree.cpp)
TARGET_LINK_LIBRARIES(tstPropertyTree utility_core)
ADD_TEST(PropertyTree_test tstPropertyTree)
SET_PROPERTY(TEST PropertyTree_test PROPERTY LABELS utility_core)

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

ADD_EXECUTABLE(tstStructuredHexMesh
  tstStructuredHexMesh.cpp
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstStructuredHexMesh utility_core)
ADD_TEST(StructuredHexMesh_test tstStructuredHexMesh)
SET_PROPERTY(TEST StructuredHexMesh_test PROPERTY LABELS utility_core)
