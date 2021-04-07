FRENSIE_INITIALIZE_PACKAGE_TESTS(utility_core BOOST_TEST_LIB ${BOOST_TEST_LIBRARY})

##---------------------------------------------------------------------------##
# Before the FRENSIE unit test framework can be used we must test all of the
# dependencies using another test framework. These first tests will all use
# the Boost unit test framework.
##---------------------------------------------------------------------------##
FRENSIE_ADD_TEST_EXECUTABLE(ElectronVoltUnit DEPENDS tstElectronVoltUnit.cpp BOOST_TEST)
FRENSIE_ADD_TEST(ElectronVoltUnit VERBOSE_TEST_OUTPUT)

FRENSIE_ADD_TEST_EXECUTABLE(AngstromUnit DEPENDS tstAngstromUnit.cpp BOOST_TEST)
FRENSIE_ADD_TEST(AngstromUnit VERBOSE_TEST_OUTPUT)

FRENSIE_ADD_TEST_EXECUTABLE(BarnUnit DEPENDS tstBarnUnit.cpp BOOST_TEST)
FRENSIE_ADD_TEST(BarnUnit VERBOSE_TEST_OUTPUT)

FRENSIE_ADD_TEST_EXECUTABLE(InverseAngstromUnit DEPENDS tstInverseAngstromUnit.cpp BOOST_TEST)
FRENSIE_ADD_TEST(InverseAngstromUnit VERBOSE_TEST_OUTPUT)

FRENSIE_ADD_TEST_EXECUTABLE(InverseCentimeterUnit DEPENDS tstInverseCentimeterUnit.cpp BOOST_TEST)
FRENSIE_ADD_TEST(InverseCentimeterUnit VERBOSE_TEST_OUTPUT)

FRENSIE_ADD_TEST_EXECUTABLE(InverseLengthConversion DEPENDS tstInverseLengthConversion BOOST_TEST)
FRENSIE_ADD_TEST(InverseLengthConversion VERBOSE_TEST_OUTPUT)

FRENSIE_ADD_TEST_EXECUTABLE(InverseSquareAngstromUnit DEPENDS tstInverseSquareAngstromUnit.cpp BOOST_TEST)
FRENSIE_ADD_TEST(InverseSquareAngstromUnit VERBOSE_TEST_OUTPUT)

FRENSIE_ADD_TEST_EXECUTABLE(InverseSquareCentimeterUnit DEPENDS tstInverseSquareCentimeterUnit.cpp BOOST_TEST)
FRENSIE_ADD_TEST(InverseSquareCentimeterUnit VERBOSE_TEST_OUTPUT)

FRENSIE_ADD_TEST_EXECUTABLE(InverseAreaConversion DEPENDS tstInverseAreaConversion.cpp BOOST_TEST)
FRENSIE_ADD_TEST(InverseAreaConversion VERBOSE_TEST_OUTPUT)

FRENSIE_ADD_TEST_EXECUTABLE(AtomUnit DEPENDS tstAtomUnit.cpp BOOST_TEST)
FRENSIE_ADD_TEST(AtomUnit VERBOSE_TEST_OUTPUT)

FRENSIE_ADD_TEST_EXECUTABLE(ShakeUnit DEPENDS tstShakeUnit.cpp BOOST_TEST)
FRENSIE_ADD_TEST(ShakeUnit VERBOSE_TEST_OUTPUT)

FRENSIE_ADD_TEST_EXECUTABLE(AtomicMomentumUnit DEPENDS tstAtomicMomentumUnit.cpp BOOST_TEST)
FRENSIE_ADD_TEST(AtomicMomentumUnit VERBOSE_TEST_OUTPUT)

FRENSIE_ADD_TEST_EXECUTABLE(MeCMomentumUnit DEPENDS tstMeCMomentumUnit.cpp BOOST_TEST)
FRENSIE_ADD_TEST(MeCMomentumUnit VERBOSE_TEST_OUTPUT)

FRENSIE_ADD_TEST_EXECUTABLE(MomentumConversion DEPENDS tstMomentumConversion.cpp BOOST_TEST)
FRENSIE_ADD_TEST(MomentumConversion VERBOSE_TEST_OUTPUT)

FRENSIE_ADD_TEST_EXECUTABLE(InverseAtomicMomentumUnit DEPENDS tstInverseAtomicMomentumUnit.cpp BOOST_TEST)
FRENSIE_ADD_TEST(InverseAtomicMomentumUnit VERBOSE_TEST_OUTPUT)

FRENSIE_ADD_TEST_EXECUTABLE(InverseMeCMomentumUnit DEPENDS tstInverseMeCMomentumUnit.cpp BOOST_TEST)
FRENSIE_ADD_TEST(InverseMeCMomentumUnit VERBOSE_TEST_OUTPUT)

FRENSIE_ADD_TEST_EXECUTABLE(InverseMomentumConversion DEPENDS tstInverseMomentumConversion.cpp BOOST_TEST)
FRENSIE_ADD_TEST(InverseMomentumConversion VERBOSE_TEST_OUTPUT)

FRENSIE_ADD_TEST_EXECUTABLE(AtomicMassUnit DEPENDS tstAtomicMassUnit.cpp BOOST_TEST)
FRENSIE_ADD_TEST(AtomicMassUnit VERBOSE_TEST_OUTPUT)

FRENSIE_ADD_TEST_EXECUTABLE(UnitTraits DEPENDS tstUnitTraits.cpp BOOST_TEST)
FRENSIE_ADD_TEST(UnitTraits VERBOSE_TEST_OUTPUT)

FRENSIE_ADD_TEST_EXECUTABLE(QuantityTraits DEPENDS tstQuantityTraits.cpp BOOST_TEST)
FRENSIE_ADD_TEST(QuantityTraits VERBOSE_TEST_OUTPUT)

FRENSIE_ADD_TEST_EXECUTABLE(TypeTraits DEPENDS tstTypeTraits.cpp BOOST_TEST)
FRENSIE_ADD_TEST(TypeTraits VERBOSE_TEST_OUTPUT)

FRENSIE_ADD_TEST_EXECUTABLE(ToStringTraits DEPENDS tstToStringTraits.cpp BOOST_TEST)
FRENSIE_ADD_TEST(ToStringTraits VERBOSE_TEST_OUTPUT)

FRENSIE_ADD_TEST_EXECUTABLE(FromStringTraits DEPENDS tstFromStringTraits.cpp BOOST_TEST)
FRENSIE_ADD_TEST(FromStringTraits VERBOSE_TEST_OUTPUT)

FRENSIE_ADD_TEST_EXECUTABLE(TypeNameTraits DEPENDS tstTypeNameTraits.cpp BOOST_TEST)
FRENSIE_ADD_TEST(TypeNameTraits VERBOSE_TEST_OUTPUT)

FRENSIE_ADD_TEST_EXECUTABLE(LogRecordType DEPENDS tstLogRecordType.cpp BOOST_TEST)
FRENSIE_ADD_TEST(LogRecordType VERBOSE_TEST_OUTPUT)

FRENSIE_ADD_TEST_EXECUTABLE(IteratorTypeTraits DEPENDS tstIteratorTypeTraits.cpp BOOST_TEST)
FRENSIE_ADD_TEST(IteratorTypeTraits VERBOSE_TEST_OUTPUT)

FRENSIE_ADD_TEST_EXECUTABLE(StaticOutputFormatter DEPENDS tstStaticOutputFormatter.cpp BOOST_TEST)
FRENSIE_ADD_TEST(StaticOutputFormatter VERBOSE_TEST_OUTPUT)

FRENSIE_ADD_TEST_EXECUTABLE(StaticOutputFormatterFactory DEPENDS tstStaticOutputFormatterFactory.cpp BOOST_TEST)
FRENSIE_ADD_TEST(StaticOutputFormatterFactory VERBOSE_TEST_OUTPUT)

FRENSIE_ADD_TEST_EXECUTABLE(DynamicOutputFormatter DEPENDS tstDynamicOutputFormatter.cpp BOOST_TEST)
FRENSIE_ADD_TEST(DynamicOutputFormatter VERBOSE_TEST_OUTPUT)

FRENSIE_ADD_TEST_EXECUTABLE(DynamicOutputFormatterFactory DEPENDS tstDynamicOutputFormatterFactory.cpp BOOST_TEST)
FRENSIE_ADD_TEST(DynamicOutputFormatterFactory VERBOSE_TEST_OUTPUT)

FRENSIE_ADD_TEST_EXECUTABLE(LoggingMacros DEPENDS tstLoggingMacros.cpp BOOST_TEST)
FRENSIE_ADD_TEST(LoggingMacros VERBOSE_TEST_OUTPUT)

FRENSIE_ADD_TEST_EXECUTABLE(ExceptionCatchMacros DEPENDS tstExceptionCatchMacros.cpp BOOST_TEST)
FRENSIE_ADD_TEST(ExceptionCatchMacros VERBOSE_TEST_OUTPUT)

FRENSIE_ADD_TEST_EXECUTABLE(DesignByContract DEPENDS tstDesignByContract.cpp BOOST_TEST)
FRENSIE_ADD_TEST(DesignByContract VERBOSE_TEST_OUTPUT)

FRENSIE_ADD_TEST_EXECUTABLE(ComparisonPolicy DEPENDS tstComparisonPolicy.cpp BOOST_TEST)
FRENSIE_ADD_TEST(ComparisonPolicy VERBOSE_TEST_OUTPUT)

FRENSIE_ADD_TEST_EXECUTABLE(ComparisonTraits DEPENDS tstComparisonTraits.cpp BOOST_TEST)
FRENSIE_ADD_TEST(ComparisonTraits VERBOSE_TEST_OUTPUT)

FRENSIE_ADD_TEST_EXECUTABLE(Tuple DEPENDS tstTuple.cpp BOOST_TEST)
FRENSIE_ADD_TEST(Tuple VERBOSE_TEST_OUTPUT)

FRENSIE_ADD_TEST_EXECUTABLE(View DEPENDS tstView.cpp BOOST_TEST)
FRENSIE_ADD_TEST(View VERBOSE_TEST_OUTPUT)

FRENSIE_ADD_TEST_EXECUTABLE(ArrayView DEPENDS tstArrayView.cpp BOOST_TEST)
FRENSIE_ADD_TEST(ArrayView VERBOSE_TEST_OUTPUT)

FRENSIE_ADD_TEST_EXECUTABLE(Array DEPENDS tstArray.cpp BOOST_TEST)
FRENSIE_ADD_TEST(Array VERBOSE_TEST_OUTPUT)

FRENSIE_ADD_TEST_EXECUTABLE(Vector DEPENDS tstVector.cpp BOOST_TEST)
FRENSIE_ADD_TEST(Vector VERBOSE_TEST_OUTPUT)

FRENSIE_ADD_TEST_EXECUTABLE(List DEPENDS tstList.cpp BOOST_TEST)
FRENSIE_ADD_TEST(List VERBOSE_TEST_OUTPUT)

FRENSIE_ADD_TEST_EXECUTABLE(Deque DEPENDS tstDeque.cpp BOOST_TEST)
FRENSIE_ADD_TEST(Deque VERBOSE_TEST_OUTPUT)

FRENSIE_ADD_TEST_EXECUTABLE(Set DEPENDS tstSet.cpp BOOST_TEST)
FRENSIE_ADD_TEST(Set VERBOSE_TEST_OUTPUT)

FRENSIE_ADD_TEST_EXECUTABLE(Map DEPENDS tstMap.cpp BOOST_TEST)
FRENSIE_ADD_TEST(Map VERBOSE_TEST_OUTPUT)

FRENSIE_ADD_TEST_EXECUTABLE(Variant DEPENDS tstVariant.cpp BOOST_TEST)
FRENSIE_ADD_TEST(Variant VERBOSE_TEST_OUTPUT)

FRENSIE_ADD_TEST_EXECUTABLE(StandardTimer DEPENDS tstStandardTimer.cpp BOOST_TEST)
FRENSIE_ADD_TEST(StandardTimer VERBOSE_TEST_OUTPUT)

FRENSIE_ADD_TEST_EXECUTABLE(OpenMPProperties DEPENDS tstOpenMPProperties BOOST_TEST)

FRENSIE_ADD_TEST_EXECUTABLE(GlobalMPISessionInit DEPENDS tstGlobalMPISessionInit.cpp BOOST_TEST)

SET(GlobalMPISessionInitProcs 1)
IF(${FRENSIE_ENABLE_MPI})
  SET(GlobalMPISessionInitProcs 4)
ENDIF()

FRENSIE_ADD_TEST(GlobalMPISessionInit
  MPI_PROCS ${GlobalMPISessionInitProcs}
  EXTRA_ARGS constructor_type=default
  VERBOSE_TEST_OUTPUT)

FRENSIE_ADD_TEST(GlobalMPISessionAdvancedInit
  TEST_EXEC_NAME_ROOT GlobalMPISessionInit
  MPI_PROCS ${GlobalMPISessionInitProcs}
  EXTRA_ARGS constructor_type=advanced
  VERBOSE_TEST_OUTPUT)

FRENSIE_ADD_TEST(GlobalMPISessionBasicSingleThreadingInit
  TEST_EXEC_NAME_ROOT GlobalMPISessionInit
  MPI_PROCS ${GlobalMPISessionInitProcs}
  EXTRA_ARGS constructor_type=basic_single
  VERBOSE_TEST_OUTPUT)

FRENSIE_ADD_TEST(GlobalMPISessionAdvancedSingleThreadingInit
  TEST_EXEC_NAME_ROOT GlobalMPISessionInit
  MPI_PROCS ${GlobalMPISessionInitProcs}
  EXTRA_ARGS constructor_type=advanced_single
  VERBOSE_TEST_OUTPUT)

FRENSIE_ADD_TEST(GlobalMPISessionBasicFunneledThreadingInit
  TEST_EXEC_NAME_ROOT GlobalMPISessionInit
  MPI_PROCS ${GlobalMPISessionInitProcs}
  EXTRA_ARGS constructor_type=basic_funneled
  VERBOSE_TEST_OUTPUT)

FRENSIE_ADD_TEST(GlobalMPISessionAdvancedFunneledThreadingInit
  TEST_EXEC_NAME_ROOT GlobalMPISessionInit
  MPI_PROCS ${GlobalMPISessionInitProcs}
  EXTRA_ARGS constructor_type=advanced_funneled
  VERBOSE_TEST_OUTPUT)

FRENSIE_ADD_TEST(GlobalMPISessionBasicSerializedThreadingInit
  TEST_EXEC_NAME_ROOT GlobalMPISessionInit
  MPI_PROCS ${GlobalMPISessionInitProcs}
  EXTRA_ARGS constructor_type=basic_serialized
  VERBOSE_TEST_OUTPUT)

FRENSIE_ADD_TEST(GlobalMPISessionAdvancedSerializedThreadingInit
  TEST_EXEC_NAME_ROOT GlobalMPISessionInit
  MPI_PROCS ${GlobalMPISessionInitProcs}
  EXTRA_ARGS constructor_type=advanced_serialized
  VERBOSE_TEST_OUTPUT)

FRENSIE_ADD_TEST(GlobalMPISessionBasicMultipleThreadingInit
  TEST_EXEC_NAME_ROOT GlobalMPISessionInit
  MPI_PROCS ${GlobalMPISessionInitProcs}
  EXTRA_ARGS constructor_type=basic_multiple
  VERBOSE_TEST_OUTPUT)

FRENSIE_ADD_TEST(GlobalMPISessionAdvancedMultipleThreadingInit
  TEST_EXEC_NAME_ROOT GlobalMPISessionInit
  MPI_PROCS ${GlobalMPISessionInitProcs}
  EXTRA_ARGS constructor_type=advanced_multiple
  VERBOSE_TEST_OUTPUT)

UNSET(GlobalMPISessionInitProcs)

FRENSIE_ADD_TEST_EXECUTABLE(GlobalMPISession DEPENDS tstGlobalMPISession.cpp BOOST_TEST)
FRENSIE_ADD_TEST(GlobalMPISession VERBOSE_TEST_OUTPUT)

IF(${FRENSIE_ENABLE_MPI})
  FRENSIE_ADD_TEST(GlobalMPISession MPI_PROCS 2 VERBOSE_TEST_OUTPUT)
  FRENSIE_ADD_TEST(GlobalMPISession MPI_PROCS 4 VERBOSE_TEST_OUTPUT)
ENDIF()

FRENSIE_ADD_TEST_EXECUTABLE(UnitTest DEPENDS tstUnitTest.cpp BOOST_TEST)
FRENSIE_ADD_TEST(UnitTest VERBOSE_TEST_OUTPUT)

FRENSIE_ADD_TEST_EXECUTABLE(UnitTestDataTable DEPENDS tstUnitTestDataTable.cpp BOOST_TEST)
FRENSIE_ADD_TEST(UnitTestDataTable)

FRENSIE_ADD_TEST_EXECUTABLE(DataUnitTest DEPENDS tstDataUnitTest.cpp BOOST_TEST)
FRENSIE_ADD_TEST(DataUnitTest)

FRENSIE_ADD_TEST_EXECUTABLE(DataUnitTestWrapper DEPENDS tstDataUnitTestWrapper.cpp BOOST_TEST)
FRENSIE_ADD_TEST(DataUnitTestWrapper)

FRENSIE_ADD_TEST_EXECUTABLE(TemplateUnitTest DEPENDS tstTemplateUnitTest.cpp BOOST_TEST)
FRENSIE_ADD_TEST(TemplateUnitTest)

FRENSIE_ADD_TEST_EXECUTABLE(TemplateUnitTestWrapper DEPENDS tstTemplateUnitTestWrapper.cpp BOOST_TEST)
FRENSIE_ADD_TEST(TemplateUnitTestWrapper)

FRENSIE_ADD_TEST_EXECUTABLE(FRENSIEUnitTestHarnessDefaultInit DEPENDS tstFRENSIEUnitTestHarnessDefaultInit.cpp)
FRENSIE_ADD_TEST(FRENSIEUnitTestHarnessDefaultInit)

IF(${FRENSIE_ENABLE_MPI})
  FRENSIE_ADD_TEST(FRENSIEUnitTestHarnessDefaultInit MPI_PROCS 2 VERBOSE_TEST_OUTPUT)
  FRENSIE_ADD_TEST(FRENSIEUnitTestHarnessDefaultInit MPI_PROCS 4 VERBOSE_TEST_OUTPUT)
ENDIF()

FRENSIE_ADD_TEST_EXECUTABLE(FRENSIEUnitTestHarnessCustomInit DEPENDS tstFRENSIEUnitTestHarnessCustomInit.cpp)
FRENSIE_ADD_TEST(FRENSIEUnitTestHarnessCustomInit
  EXTRA_ARGS --number_of_tests=46 --number_of_checks=76)

IF(${FRENSIE_ENABLE_MPI})
  FRENSIE_ADD_TEST(FRENSIEUnitTestHarnessCustomInit MPI_PROCS 2
    EXTRA_ARGS --number_of_tests=46 --number_of_checks=76)
ENDIF()

# Check that no tests are run if the -h flag is passed
FRENSIE_ADD_TEST(FRENSIEUnitTestHarnessCustomInit_h_flag
  TEST_EXEC_NAME_ROOT FRENSIEUnitTestHarnessCustomInit
  EXTRA_ARGS -h --number_of_tests=0 --number_of_checks=0)

IF(${FRENSIE_ENABLE_MPI})
  FRENSIE_ADD_TEST(FRENSIEUnitTestHarnessCustomInit_h_flag
    MPI_PROCS 2
    TEST_EXEC_NAME_ROOT FRENSIEUnitTestHarnessCustomInit
    EXTRA_ARGS -h --number_of_tests=0 --number_of_checks=0)
ENDIF()

# Check that no tests are run if the --help flag is passed
FRENSIE_ADD_TEST(FRENSIEUnitTestHarnessCustomInit_help_flag
  TEST_EXEC_NAME_ROOT FRENSIEUnitTestHarnessCustomInit
  EXTRA_ARGS --help --number_of_tests=0 --number_of_checks=0)

IF(${FRENSIE_ENABLE_MPI})
  FRENSIE_ADD_TEST(FRENSIEUnitTestHarnessCustomInit_help_flag
    MPI_PROCS 2
    TEST_EXEC_NAME_ROOT FRENSIEUnitTestHarnessCustomInit
    EXTRA_ARGS --help --number_of_tests=0 --number_of_checks=0)
ENDIF()

# Check that no tests are run if the -g flag is passed
FRENSIE_ADD_TEST(FRENSIEUnitTestHarnessCustomInit_g_flag
  TEST_EXEC_NAME_ROOT FRENSIEUnitTestHarnessCustomInit
  EXTRA_ARGS -g --number_of_tests=0 --number_of_checks=0)

IF(${FRENSIE_ENABLE_MPI})
  FRENSIE_ADD_TEST(FRENSIEUnitTestHarnessCustomInit_g_flag
    MPI_PROCS 2
    TEST_EXEC_NAME_ROOT FRENSIEUnitTestHarnessCustomInit
    EXTRA_ARGS -g --number_of_tests=0 --number_of_checks=0)
ENDIF()

# Check that no tests are run if the --show_groups flag is passed
FRENSIE_ADD_TEST(FRENSIEUnitTestHarnessCustomInit_show_groups_flag
  TEST_EXEC_NAME_ROOT FRENSIEUnitTestHarnessCustomInit
  EXTRA_ARGS --show_groups --number_of_tests=0 --number_of_checks=0)

IF(${FRENSIE_ENABLE_MPI})
  FRENSIE_ADD_TEST(FRENSIEUnitTestHarnessCustomInit_show_groups_flag
    MPI_PROCS 2
    TEST_EXEC_NAME_ROOT FRENSIEUnitTestHarnessCustomInit
    EXTRA_ARGS --show_groups --number_of_tests=0 --number_of_checks=0)
ENDIF()

# Check that no tests are run if the -t flag is passed
FRENSIE_ADD_TEST(FRENSIEUnitTestHarnessCustomInit_t_flag
  TEST_EXEC_NAME_ROOT FRENSIEUnitTestHarnessCustomInit
  EXTRA_ARGS -t --number_of_tests=0 --number_of_checks=0)

IF(${FRENSIE_ENABLE_MPI})
  FRENSIE_ADD_TEST(FRENSIEUnitTestHarnessCustomInit_t_flag
    MPI_PROCS 2
    TEST_EXEC_NAME_ROOT FRENSIEUnitTestHarnessCustomInit
    EXTRA_ARGS -t --number_of_tests=0 --number_of_checks=0)
ENDIF()

# Check that no tests are run if the --show_tests flag is passed
FRENSIE_ADD_TEST(FRENSIEUnitTestHarnessCustomInit_show_tests_flag
  TEST_EXEC_NAME_ROOT FRENSIEUnitTestHarnessCustomInit
  EXTRA_ARGS --show_tests --number_of_tests=0 --number_of_checks=0)

IF(${FRENSIE_ENABLE_MPI})
  FRENSIE_ADD_TEST(FRENSIEUnitTestHarnessCustomInit_show_tests_flag
    MPI_PROCS 2
    TEST_EXEC_NAME_ROOT FRENSIEUnitTestHarnessCustomInit
    EXTRA_ARGS --show_tests --number_of_tests=0 --number_of_checks=0)
ENDIF()

# Check that no tests are run if the -d flag is passed
FRENSIE_ADD_TEST(FRENSIEUnitTestHarnessCustomInit_d_flag
  TEST_EXEC_NAME_ROOT FRENSIEUnitTestHarnessCustomInit
  EXTRA_ARGS -d --number_of_tests=0 --number_of_checks=0)

IF(${FRENSIE_ENABLE_MPI})
  FRENSIE_ADD_TEST(FRENSIEUnitTestHarnessCustomInit_d_flag
    MPI_PROCS 2
    TEST_EXEC_NAME_ROOT FRENSIEUnitTestHarnessCustomInit
    EXTRA_ARGS -d --number_of_tests=0 --number_of_checks=0)
ENDIF()

# Check that no tests are run if the --show_data flag is passed
FRENSIE_ADD_TEST(FRENSIEUnitTestHarnessCustomInit_show_data_flag
  TEST_EXEC_NAME_ROOT FRENSIEUnitTestHarnessCustomInit
  EXTRA_ARGS --show_data --number_of_tests=0 --number_of_checks=0)

IF(${FRENSIE_ENABLE_MPI})
  FRENSIE_ADD_TEST(FRENSIEUnitTestHarnessCustomInit_show_data_flag
    MPI_PROCS 2
    TEST_EXEC_NAME_ROOT FRENSIEUnitTestHarnessCustomInit
    EXTRA_ARGS --show_data --number_of_tests=0 --number_of_checks=0)
ENDIF()

# Check that the test group can be filtered
FRENSIE_ADD_TEST(FRENSIEUnitTestHarnessCustomInit_group_filter
  TEST_EXEC_NAME_ROOT FRENSIEUnitTestHarnessCustomInit
  EXTRA_ARGS --group_filter=CHECK --number_of_tests=34 --number_of_checks=53)

IF(${FRENSIE_ENABLE_MPI})
  FRENSIE_ADD_TEST(FRENSIEUnitTestHarnessCustomInit_group_filter
    MPI_PROCS 2
    TEST_EXEC_NAME_ROOT FRENSIEUnitTestHarnessCustomInit
    EXTRA_ARGS --group_filter=CHECK --number_of_tests=34 --number_of_checks=53)
ENDIF()

# Check that the tests can be filtered
FRENSIE_ADD_TEST(FRENSIEUnitTestHarnessCustomInit_test_filter
  TEST_EXEC_NAME_ROOT FRENSIEUnitTestHarnessCustomInit
  EXTRA_ARGS --test_filter=EQUAL --number_of_tests=8 --number_of_checks=16)

IF(${FRENSIE_ENABLE_MPI})
  FRENSIE_ADD_TEST(FRENSIEUnitTestHarnessCustomInit_test_filter
    MPI_PROCS 2
    TEST_EXEC_NAME_ROOT FRENSIEUnitTestHarnessCustomInit
    EXTRA_ARGS --test_filter=EQUAL --number_of_tests=8 --number_of_checks=16)
ENDIF()

# Check that the data can be filtered
FRENSIE_ADD_TEST(FRENSIEUnitTestHarnessCustomInit_data_filter
  TEST_EXEC_NAME_ROOT FRENSIEUnitTestHarnessCustomInit
  EXTRA_ARGS --data_filter=zero_input --number_of_tests=1 --number_of_checks=1)

IF(${FRENIE_ENABLE_MPI})
  FRENSIE_ADD_TEST(FRENSIEUnitTestHarnessCustomInit_data_filter
    MPI_PROCS 2
    TEST_EXEC_NAME_ROOT FRENSIEUnitTestHarnessCustomInit
    EXTRA_ARGS --data_filter=zero_input --number_of_tests=1 --number_of_checks=1)
ENDIF()

# Check that multiple filters can be applied
FRENSIE_ADD_TEST(FRENSIEUnitTestHarnessCustomInit_multiple_filter
  TEST_EXEC_NAME_ROOT FRENSIEUnitTestHarnessCustomInit
  EXTRA_ARGS --group_filter=REQUIRE --test_filter=SMALL --number_of_tests=1 --number_of_checks=3)

IF(${FRENSIE_ENABLE_MPI})
  FRENSIE_ADD_TEST(FRENSIEUnitTestHarnessCustomInit_multiple_filter
    MPI_PROCS 2
    TEST_EXEC_NAME_ROOT FRENSIEUnitTestHarnessCustomInit
    EXTRA_ARGS --group_filter=REQUIRE --test_filter=SMALL --number_of_tests=1 --number_of_checks=3)
ENDIF()

##---------------------------------------------------------------------------##
# All FRENSIE unit test framework dependencies have been tested. All tests
# beyond this point can use the FRENSIE unit tests framework.
##---------------------------------------------------------------------------##
FRENSIE_ADD_TEST_EXECUTABLE(SortAlgorithms DEPENDS tstSortAlgorithms.cpp)
FRENSIE_ADD_TEST(SortAlgorithms)

FRENSIE_ADD_TEST_EXECUTABLE(SearchAlgorithms DEPENDS tstSearchAlgorithms.cpp)
FRENSIE_ADD_TEST(SearchAlgorithms)

FRENSIE_ADD_TEST_EXECUTABLE(ExponentiationAlgorithms DEPENDS tstExponentiationAlgorithms.cpp)
FRENSIE_ADD_TEST(ExponentiationAlgorithms)

FRENSIE_ADD_TEST_EXECUTABLE(SetOperationFunctor DEPENDS tstSetOperationFunctor.cpp)
FRENSIE_ADD_TEST(SetOperationFunctor)

FRENSIE_ADD_TEST_EXECUTABLE(DataProcessor DEPENDS tstDataProcessor.cpp)
FRENSIE_ADD_TEST(DataProcessor)

FRENSIE_ADD_TEST_EXECUTABLE(FortranStringHelpers DEPENDS
  tstFortranStringHelpers.cpp
  string_conversion.F90)
FRENSIE_ADD_TEST(FortranStringHelpers)

FRENSIE_ADD_TEST_EXECUTABLE(FortranFileHelpers DEPENDS tstFortranFileHelpers.cpp)
FRENSIE_ADD_TEST(FortranFileHelpers
  EXTRA_ARGS --test_file=${CMAKE_CURRENT_SOURCE_DIR}/test_files/check_file.txt)

FRENSIE_ADD_TEST_EXECUTABLE(3DCartesianVectorHelpers DEPENDS tst3DCartesianVectorHelpers.cpp)
FRENSIE_ADD_TEST(3DCartesianVectorHelpers)

FRENSIE_ADD_TEST_EXECUTABLE(PropertyTree DEPENDS tstPropertyTree.cpp)
FRENSIE_ADD_TEST(PropertyTree)

FRENSIE_ADD_TEST_EXECUTABLE(HDF5File DEPENDS tstHDF5File.cpp)
FRENSIE_ADD_TEST(HDF5File)

IF(${FRENSIE_ENABLE_HDF5})
FRENSIE_ADD_TEST_EXECUTABLE(HDF5FileDataSetHelpers DEPENDS tstHDF5FileDataSetHelpers.cpp)
FRENSIE_ADD_TEST(HDF5FileDataSetHelpers)

FRENSIE_ADD_TEST_EXECUTABLE(HDF5FileDataSetAttributeHelpers DEPENDS tstHDF5FileDataSetAttributeHelpers.cpp)
FRENSIE_ADD_TEST(HDF5FileDataSetAttributeHelpers)

FRENSIE_ADD_TEST_EXECUTABLE(HDF5FileGroupAttributeHelpers DEPENDS tstHDF5FileGroupAttributeHelpers.cpp)
FRENSIE_ADD_TEST(HDF5FileGroupAttributeHelpers)
ENDIF()

FRENSIE_FINALIZE_PACKAGE_TESTS(utility_core)

