//---------------------------------------------------------------------------//
//!
//! \file   tstFRENSIEUnitTestHarnessCustomInit.cpp
//! \author Alex Robinson
//! \brief  FRENSIE Unit Test Harness test with custom initialization
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <csignal>
#include <cstdlib>

// FRENSIE Includes
#include "Utility_UnitTestHarness.hpp"
#include "Utility_GlobalMPISession.hpp"
#include "Utility_StaticOutputFormatter.hpp"

//---------------------------------------------------------------------------//
// Testing variables
//---------------------------------------------------------------------------//
int expected_number_of_tests = 0;
int expected_number_of_checks = 0;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the CHECK macro behaves correctly
FRENSIE_UNIT_TEST( UnitTestHarness_CHECK, CHECK )
{
  FRENSIE_CHECK( true );

  bool check_statement = true;

  FRENSIE_CHECK( check_statement );
}

//---------------------------------------------------------------------------//
// Check that the REQUIRE macro behaves correctly
FRENSIE_UNIT_TEST( UnitTestHarness_REQUIRE, REQUIRE )
{
  FRENSIE_REQUIRE( true );

  bool check_statement = true;

  FRENSIE_REQUIRE( check_statement );
}

//---------------------------------------------------------------------------//
// Check that the CHECK_EQUAL macro behaves correctly
FRENSIE_UNIT_TEST( UnitTestHarness_CHECK, CHECK_EQUAL )
{
  FRENSIE_CHECK_EQUAL( 0, 0 );
}

//---------------------------------------------------------------------------//
// Check that the REQUIRE_EQUAL macro behaves correctly
FRENSIE_UNIT_TEST( UnitTestHarness_REQUIRE, REQUIRE_EQUAL )
{
  FRENSIE_REQUIRE_EQUAL( 0, 0 );
}

//---------------------------------------------------------------------------//
// Check that the CHECK_DIFFERENT macro behaves correctly
FRENSIE_UNIT_TEST( UnitTestHarness_CHECK, CHECK_DIFFERENT )
{
  FRENSIE_CHECK_DIFFERENT( 0, 1 );
}

//---------------------------------------------------------------------------//
// Check that the REQUIRE_DIFFERENT macro behaves correctly
FRENSIE_UNIT_TEST( UnitTestHarness_REQUIRE, REQUIRE_DIFFERENT )
{
  FRENSIE_REQUIRE_DIFFERENT( 0, 1 );
}

//---------------------------------------------------------------------------//
// Check that the CHECK_GREATER macro behaves correctly
FRENSIE_UNIT_TEST( UnitTestHarness_CHECK, CHECK_GREATER )
{
  FRENSIE_CHECK_GREATER( 1, 0 );
}

//---------------------------------------------------------------------------//
// Check that the REQUIRE_GREATER macro behaves correctly
FRENSIE_UNIT_TEST( UnitTestHarness_REQUIRE, REQUIRE_GREATER )
{
  FRENSIE_REQUIRE_GREATER( 1, 0 );
}

//---------------------------------------------------------------------------//
// Check that the CHECK_GREATER_OR_EQUAL macro behaves correctly
FRENSIE_UNIT_TEST( UnitTestHarness_CHECK, CHECK_GREATER_OR_EQUAL )
{
  FRENSIE_CHECK_GREATER_OR_EQUAL( 0, 0 );
  FRENSIE_CHECK_GREATER_OR_EQUAL( 1, 0 );
}

//---------------------------------------------------------------------------//
// Check that the REQUIRE_GREATER_OR_EQUAL macro behaves correctly
FRENSIE_UNIT_TEST( UnitTestHarness_REQUIRE, REQUIRE_GREATER_OR_EQUAL )
{
  FRENSIE_REQUIRE_GREATER_OR_EQUAL( 0, 0 );
  FRENSIE_REQUIRE_GREATER_OR_EQUAL( 1, 0 );
}

//---------------------------------------------------------------------------//
// Check that the CHECK_LESS macro behaves correctly
FRENSIE_UNIT_TEST( UnitTestHarness_CHECK, CHECK_LESS )
{
  FRENSIE_CHECK_LESS( 0, 1 );
}

//---------------------------------------------------------------------------//
// Check that the REQUIRE_LESS macro behaves correctly
FRENSIE_UNIT_TEST( UnitTestHarness_REQUIRE, REQUIRE_LESS )
{
  FRENSIE_REQUIRE_LESS( 0, 1 );
}

//---------------------------------------------------------------------------//
// Check that the CHECK_LESS_OR_EQUAL macro behaves correctly
FRENSIE_UNIT_TEST( UnitTestHarness_CHECK, CHECK_LESS_OR_EQUAL )
{
  FRENSIE_CHECK_LESS_OR_EQUAL( 0, 0 );
  FRENSIE_CHECK_LESS_OR_EQUAL( 0, 1 );
}

//---------------------------------------------------------------------------//
// Check that the REQUIRE_LESS_OR_EQUAL macro behaves correctly
FRENSIE_UNIT_TEST( UnitTestHarness_REQUIRE, REQUIRE_LESS_OR_EQUAL )
{
  FRENSIE_REQUIRE_LESS_OR_EQUAL( 0, 0 );
  FRENSIE_REQUIRE_LESS_OR_EQUAL( 0, 1 );
}

//---------------------------------------------------------------------------//
// Check that the CHECK_CLOSE macro behaves correctly
FRENSIE_UNIT_TEST( UnitTestHarness_CHECK, CHECK_CLOSE )
{
  FRENSIE_CHECK_CLOSE( 1.0f, 1.0f, 1e-9f );
  FRENSIE_CHECK_CLOSE( 1.0f, (1.0f-1e-10f), 1e-9f );
  FRENSIE_CHECK_CLOSE( 1.0f, (1.0f+1e-10f), 1e-9f );
}

//---------------------------------------------------------------------------//
// Check that the REQUIRE_CLOSE macro behaves correctly
FRENSIE_UNIT_TEST( UnitTestHarness_REQUIRE, REQUIRE_CLOSE )
{
  FRENSIE_REQUIRE_CLOSE( 1.0f, 1.0f, 1e-9f );
  FRENSIE_REQUIRE_CLOSE( 1.0f, (1.0f-1e-10f), 1e-9f );
  FRENSIE_REQUIRE_CLOSE( 1.0f, (1.0f+1e-10f), 1e-9f );
}

//---------------------------------------------------------------------------//
// Check that the CHECK_SMALL macro behaves correctly
FRENSIE_UNIT_TEST( UnitTestHarness_CHECK, CHECK_SMALL )
{
  FRENSIE_CHECK_SMALL( 0.0f, 1e-9f );
  FRENSIE_CHECK_SMALL( 1e-9, 1e-8f );
  FRENSIE_CHECK_SMALL( -1e-9, 1e-8f );
}

//---------------------------------------------------------------------------//
// Check that the REQUIRE_SMALL macro behaves correctly
FRENSIE_UNIT_TEST( UnitTestHarness_REQUIRE, REQUIRE_SMALL )
{
  FRENSIE_REQUIRE_SMALL( 0.0f, 1e-9f );
  FRENSIE_REQUIRE_SMALL( 1e-9, 1e-8f );
  FRENSIE_REQUIRE_SMALL( -1e-9, 1e-8f );
}

//---------------------------------------------------------------------------//
// Check that the CHECK_FLOATING_EQUALITY macro behaves correctly
FRENSIE_UNIT_TEST( UnitTestHarness_CHECK, CHECK_FLOATING_EQUALITY )
{
  FRENSIE_CHECK_FLOATING_EQUALITY( 1.0f, 1.0f, 1e-9f );
  FRENSIE_CHECK_FLOATING_EQUALITY( 1.0f, (1.0f-1e-10f), 1e-9f );
  FRENSIE_CHECK_FLOATING_EQUALITY( 1.0f, (1.0f+1e-10f), 1e-9f );
}

//---------------------------------------------------------------------------//
// Check that the REQUIRE_FLOATING_EQUALITY macro behaves correctly
FRENSIE_UNIT_TEST( UnitTestHarness_REQUIRE, REQUIRE_FLOATING_EQUALITY )
{
  FRENSIE_REQUIRE_FLOATING_EQUALITY( 1.0f, 1.0f, 1e-9f );
  FRENSIE_REQUIRE_FLOATING_EQUALITY( 1.0f, (1.0f-1e-10f), 1e-9f );
  FRENSIE_REQUIRE_FLOATING_EQUALITY( 1.0f, (1.0f+1e-10f), 1e-9f );
}

//---------------------------------------------------------------------------//
// Check that the CHECK_NO_THROW macro behaves correctly
FRENSIE_UNIT_TEST( UnitTestHarness_CHECK, CHECK_NO_THROW )
{
  FRENSIE_CHECK_NO_THROW( double dummy = 0.0 );
}

//---------------------------------------------------------------------------//
// Check that the REQUIRE_NO_THROW macro behaves correctly
FRENSIE_UNIT_TEST( UnitTestHarness_REQUIRE, REQUIRE_NO_THROW )
{
  FRENSIE_REQUIRE_NO_THROW( double dummy = 0.0 );
}

//---------------------------------------------------------------------------//
// Check that the CHECK_THROW macro behaves correctly
FRENSIE_UNIT_TEST( UnitTestHarness_CHECK, CHECK_THROW )
{
  FRENSIE_CHECK_THROW( throw std::runtime_error("fail"), std::runtime_error );
  FRENSIE_CHECK_THROW( throw std::logic_error("fail"), std::logic_error );
  FRENSIE_CHECK_THROW( throw 1, int );
}

//---------------------------------------------------------------------------//
// Check that the REQUIRE_THROW macro behaves correctly
FRENSIE_UNIT_TEST( UnitTestHarness_REQUIRE, REQUIRE_THROW )
{
  FRENSIE_REQUIRE_THROW( throw std::runtime_error("fail"), std::runtime_error );
  FRENSIE_REQUIRE_THROW( throw std::logic_error("fail"), std::logic_error );
  FRENSIE_REQUIRE_THROW( throw 1, int );
}

//---------------------------------------------------------------------------//
// Check that a data unit test can be constructed
FRENSIE_DATA_UNIT_TEST_DECL( UnitTestHarness_CHECK, DataDrivenTest )
{
  FETCH_FROM_TABLE( double, Input );
  FETCH_FROM_TABLE( double, abs_Input );
  FETCH_FROM_TABLE( double, Tolerance );

  FRENSIE_CHECK_FLOATING_EQUALITY( fabs(Input), abs_Input, Tolerance );
}

FRENSIE_DATA_UNIT_TEST_INST( UnitTestHarness_CHECK, DataDrivenTest )
{
  COLUMNS()               << "Input" << "abs_Input" << "Tolerance";
  NEW_ROW( "neg_input" )  << -1.0    << 1.0         << 1e-15;
  NEW_ROW( "zero_input" ) <<  0.0    << 0.0         << 0.0;
  NEW_ROW( "pos_input" )  <<  1.0    << 1.0         << 1e-15;
}

//---------------------------------------------------------------------------//
// Check that a template unit test can be constructed
FRENSIE_UNIT_TEST_TEMPLATE( UnitTestHarness_CHECK, TemplateTestRawParamPack,
                            bool, short, int, long, long long, float, double )
{
  FETCH_TEMPLATE_PARAM( 0, T );

  T value(0);

  FRENSIE_CHECK_EQUAL( value, T(0) );
}

//---------------------------------------------------------------------------//
// Check that a template unit test can be constructed
FRENSIE_UNIT_TEST_TEMPLATE( UnitTestHarness_CHECK, TemplateTestTupleTypes,
                            std::tuple<>,
                            std::tuple<int,int>,
                            std::tuple<int,int,int>,
                            std::tuple<int,int,int,int> )
{
  FETCH_TEMPLATE_PARAM( 0, Tuple );

  Tuple value;

  FRENSIE_CHECK_EQUAL( value, value );
}

//---------------------------------------------------------------------------//
// Check that a template unit test can be constructed
FRENSIE_UNIT_TEST_TEMPLATE_EXPAND( UnitTestHarness_CHECK,
                                   TemplateTestRawExpandedTupleTypes,
                                   std::tuple<int,int>,
                                   std::tuple<int,double>,
                                   std::tuple<double,double>,
                                   std::tuple<double,int> )
{
  FETCH_TEMPLATE_PARAM( 0, T0 );
  FETCH_TEMPLATE_PARAM( 1, T1 );

  T0 value_0(0);
  T1 value_1(1);

  FRENSIE_CHECK_EQUAL( value_0, T0(0) );
  FRENSIE_CHECK_EQUAL( value_1, T1(1) );
}

//---------------------------------------------------------------------------//
// Check that a template unit test can be constructed
FRENSIE_UNIT_TEST_TEMPLATE_EXPAND( UnitTestHarness_CHECK,
                                   TemplateTestWrappedExpandedTupleTypes,
                                   std::tuple<std::tuple<int,int>,
                                              std::tuple<int,double>,
                                              std::tuple<double,double>,
                                              std::tuple<double,int> > )
{
  FETCH_TEMPLATE_PARAM( 0, T0 );
  FETCH_TEMPLATE_PARAM( 1, T1 );

  T0 value_0(0);
  T1 value_1(1);

  FRENSIE_CHECK_EQUAL( value_0, T0(0) );
  FRENSIE_CHECK_EQUAL( value_1, T1(1) );
}

//---------------------------------------------------------------------------//
// Custom Setup
//---------------------------------------------------------------------------//
FRENSIE_CUSTOM_UNIT_TEST_SETUP_BEGIN();

FRENSIE_CUSTOM_UNIT_TEST_COMMAND_LINE_OPTIONS()
{
  ADD_OPTION( "number_of_tests",
              boost::program_options::value<int>()->default_value(0),
              "expected number of tests" );

  ADD_STANDARD_OPTION_AND_ASSIGN_VALUE( "number_of_checks",
                                        expected_number_of_checks, 0,
                                        "expected number of checks" );
}

FRENSIE_CUSTOM_UNIT_TEST_INIT()
{
  ASSIGN_OPTION_VALUE( expected_number_of_tests, "number_of_tests" );
  expected_number_of_tests *= Utility::GlobalMPISession::size();

  expected_number_of_checks *= Utility::GlobalMPISession::size();
}

FRENSIE_CUSTOM_UNIT_TEST_FINAL()
{
  std::cout << "Nothing to clear!" << std::endl;
}

FRENSIE_CUSTOM_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// A custom signal handler for seg faults
//---------------------------------------------------------------------------//
void SignalHandler( int signal )      
{
  if( signal == SIGSEGV )
    throw std::logic_error( "Seg Fault Detected!" );
}

//---------------------------------------------------------------------------//
// A custom main function
//---------------------------------------------------------------------------//
int main( int argc, char** argv )
{
  Utility::GlobalMPISession mpi_session;
  
  signal( SIGSEGV, &SignalHandler );
  
  Utility::UnitTestManager& unit_test_manager =
    Utility::UnitTestManager::getInstance();

  int return_value = unit_test_manager.runUnitTests( argc, argv, mpi_session );

  int number_of_tests =
    mpi_session.sum( unit_test_manager.getNumberOfRunTests() );
  
  int number_of_checks =
    mpi_session.sum( unit_test_manager.getNumberOfChecks() );

  const bool report_details = (mpi_session.rank() == 0 ? true : false);

  if( report_details )
  {
    std::cout << "\nIgnore previous results - "
              << "custom checks need to be conducted..."
              << std::endl;
  }

  bool correct_return_value =
    Utility::compare<Utility::EqualityComparisonPolicy,2,2>(
                                   return_value, "return value",
                                   0, "expected return value",
                                   std::cout, 0, report_details );
  bool correct_number_of_tests =
    Utility::compare<Utility::EqualityComparisonPolicy,2,2>(
                          number_of_tests, "number of tests",
                          expected_number_of_tests, "expected number of tests",
                          std::cout, 0, report_details );

  bool correct_number_of_checks =
    Utility::compare<Utility::EqualityComparisonPolicy,2,2>(
                        number_of_checks, "number of checks",
                        expected_number_of_checks, "expected number of checks",
                        std::cout, 0, report_details );
  if( report_details )
    std::cout << "\nActual End Result: ";

  mpi_session.barrier();

  if( correct_return_value &&
      correct_number_of_tests &&
      correct_number_of_checks )
  {
    if( report_details )
      std::cout << Utility::Green("TEST PASSED") << std::endl;

    return 0;
  }
  else
  {
    if( report_details )
      std::cout << Utility::Red("TEST FAILED") << std::endl;

    return 1;
  }
}

//---------------------------------------------------------------------------//
// end tstFRENSIEUnitTestHarnessCustomInit.cpp
//---------------------------------------------------------------------------//
