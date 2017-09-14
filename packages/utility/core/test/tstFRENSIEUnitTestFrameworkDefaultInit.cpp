//---------------------------------------------------------------------------//
//!
//! \file   tstFRENSIEUnitTestFrameworkDefaultInit.cpp
//! \author Alex Robinson
//! \brief  FRENSIE Unit Test Framework test with default initialization
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <csignal>

// FRENSIE Includes
#include "Utility_UnitTestHarness.hpp"
#include "Utility_Tuple.hpp"
#include "Utility_List.hpp"
#include "Utility_Deque.hpp"
#include "Utility_Array.hpp"
#include "Utility_Vector.hpp"
#include "Utility_Set.hpp"
#include "Utility_Map.hpp"

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the CHECK macro behaves correctly
FRENSIE_UNIT_TEST( UnitTestHarness, CHECK_pass )
{
  FRENSIE_CHECK( true );

  bool check_statement = true;

  FRENSIE_CHECK( check_statement );
}

//---------------------------------------------------------------------------//
// Check that the CHECK macro behaves correctly
FRENSIE_UNIT_TEST( UnitTestHarness, CHECK_fail )
{
  FRENSIE_CHECK( true );
  FRENSIE_CHECK( false );

  bool check_statement = false;

  FRENSIE_CHECK( check_statement );
}

//---------------------------------------------------------------------------//
// Check that the CHECK_EQUAL macro behaves correctly
FRENSIE_UNIT_TEST( UnitTestHarness, CHECK_EQUAL_pass )
{
  FRENSIE_CHECK_EQUAL( true, true );
  FRENSIE_CHECK_EQUAL( 0, 0 );
  FRENSIE_CHECK_EQUAL( 1u, 1u );
  FRENSIE_CHECK_EQUAL( -2l, -2l );
  FRENSIE_CHECK_EQUAL( 3ul, 3ul );
  FRENSIE_CHECK_EQUAL( -4ll, -4ll );
  FRENSIE_CHECK_EQUAL( 3ull, 3ull );
  FRENSIE_CHECK_EQUAL( 1.0f, 1.0f );
  FRENSIE_CHECK_EQUAL( -1.0, -1.0 );
  
  FRENSIE_CHECK_EQUAL( std::string( "test string" ), std::string( "test string" ) );

  FRENSIE_CHECK_EQUAL( std::make_tuple(0), std::make_tuple(0) );
  FRENSIE_CHECK_EQUAL( std::make_tuple(0.), std::make_tuple(0.) );
  FRENSIE_CHECK_EQUAL( std::make_tuple(0, 1.0, std::string("test string")),
                       std::make_tuple(0, 1.0, std::string("test string")) );
  FRENSIE_CHECK_EQUAL( std::make_pair(0, 1.0), std::make_pair(0, 1.0) );
  
  FRENSIE_CHECK_EQUAL( std::list<int>({0, 1, 2}), std::list<int>({0, 1, 2}) );
  FRENSIE_CHECK_EQUAL( std::list<double>({0., 1., 2.}), std::list<double>({0., 1., 2.}) );
  FRENSIE_CHECK_EQUAL( std::list<std::string>({"test", "string"} ), std::list<std::string>({"test", "string"}) );

  FRENSIE_CHECK_EQUAL( std::forward_list<int>({0, 1, 2}), std::forward_list<int>({0, 1, 2}) );
  FRENSIE_CHECK_EQUAL( std::forward_list<double>({0., 1., 2.}), std::forward_list<double>({0., 1., 2.}) );
  FRENSIE_CHECK_EQUAL( std::forward_list<std::string>({"test", "string"} ), std::forward_list<std::string>({"test", "string"}) );

  FRENSIE_CHECK_EQUAL( std::deque<int>({0, 1, 2}), std::deque<int>({0, 1, 2}) );
  FRENSIE_CHECK_EQUAL( std::deque<double>({0., 1., 2.}), std::deque<double>({0., 1., 2.}) );
  FRENSIE_CHECK_EQUAL( std::deque<std::string>({"test", "string"} ), std::deque<std::string>({"test", "string"}) );

  FRENSIE_CHECK_EQUAL( (std::array<int,3>({0, 1, 2})), (std::array<int,3>({0, 1, 2})) );
  FRENSIE_CHECK_EQUAL( (std::array<double,3>({0., 1., 2.})), (std::array<double,3>({0., 1., 2.})) );
  
  FRENSIE_CHECK_EQUAL( std::vector<int>({0, 1, 2}), std::vector<int>({0, 1, 2}) );
  FRENSIE_CHECK_EQUAL( std::vector<double>({0., 1., 2.}), std::vector<double>({0., 1., 2.}) );
  FRENSIE_CHECK_EQUAL( std::vector<std::string>({"test", "string"} ), std::vector<std::string>({"test", "string"}) );

  FRENSIE_CHECK_EQUAL( std::set<int>({0, 1, 2}), std::set<int>({0, 1, 2}) );
  FRENSIE_CHECK_EQUAL( std::set<std::string>({"test", "string"}), std::set<std::string>({"test", "string"}) );

  FRENSIE_CHECK_EQUAL( std::unordered_set<int>({0, 1, 2}), std::unordered_set<int>({0, 1, 2}) );
  FRENSIE_CHECK_EQUAL( std::unordered_set<std::string>({"test", "string"}), std::unordered_set<std::string>({"test", "string"}) );

  FRENSIE_CHECK_EQUAL( (std::map<int,int>({{0, 0}, {1, 1}})), (std::map<int,int>({{0, 0}, {1, 1}})) );
  FRENSIE_CHECK_EQUAL( (std::map<int,double>({{0, 0.}, {1, 1.}})), (std::map<int,double>({{0, 0.}, {1, 1.}})) );

  FRENSIE_CHECK_EQUAL( (std::unordered_map<int,int>({{0, 0}, {1, 1}})), (std::unordered_map<int,int>({{0, 0}, {1, 1}})) );
  FRENSIE_CHECK_EQUAL( (std::unordered_map<int,double>({{0, 0.}, {1, 1.}})), (std::unordered_map<int,double>({{0, 0.}, {1, 1.}})) );
}

//---------------------------------------------------------------------------//
// Check that the CHECK_EQUAL macro behaves correctly
FRENSIE_UNIT_TEST( UnitTestHarness, CHECK_EQUAL_fail )
{
  FRENSIE_CHECK_EQUAL( true, true );
  FRENSIE_CHECK_EQUAL( false, true );
  FRENSIE_CHECK_EQUAL( true, false );
  
  FRENSIE_CHECK_EQUAL( 0, 0 );
  FRENSIE_CHECK_EQUAL( 1, 0 );
  FRENSIE_CHECK_EQUAL( 0, 1 );
  
  FRENSIE_CHECK_EQUAL( 1u, 1u );
  FRENSIE_CHECK_EQUAL( 0u, 1u );
  FRENSIE_CHECK_EQUAL( 1u, 0u );
  
  FRENSIE_CHECK_EQUAL( -2l, -2l );
  FRENSIE_CHECK_EQUAL( 2l, -2l );
  FRENSIE_CHECK_EQUAL( -2l, 2l );
  
  FRENSIE_CHECK_EQUAL( 3ul, 3ul );
  FRENSIE_CHECK_EQUAL( 3ul, 2ul );
  FRENSIE_CHECK_EQUAL( 2ul, 3ul );
  
  FRENSIE_CHECK_EQUAL( -4ll, -4ll );
  FRENSIE_CHECK_EQUAL( -4ll, 4ll );
  FRENSIE_CHECK_EQUAL( 4ll, -4ll );
  
  FRENSIE_CHECK_EQUAL( 3ull, 3ull );
  FRENSIE_CHECK_EQUAL( 3ull, 4ull );
  FRENSIE_CHECK_EQUAL( 4ull, 3ull );
  
  FRENSIE_CHECK_EQUAL( 1.0f, 1.0f );
  FRENSIE_CHECK_EQUAL( -1.0f, 1.0f );
  FRENSIE_CHECK_EQUAL( 1.0f, -1.0f );
  
  FRENSIE_CHECK_EQUAL( -1.0, -1.0 );
  FRENSIE_CHECK_EQUAL( 1.0, -1.0 );
  FRENSIE_CHECK_EQUAL( -1.0, 1.0 );
  
  FRENSIE_CHECK_EQUAL( std::string( "test string" ), std::string( "test string" ) );
  FRENSIE_CHECK_EQUAL( std::string( "test string" ), std::string( "string" ) );
  FRENSIE_CHECK_EQUAL( std::string( "string" ), std::string( "test string" ) );

  FRENSIE_CHECK_EQUAL( std::make_tuple(0), std::make_tuple(0) );
  FRENSIE_CHECK_EQUAL( std::make_tuple(0), std::make_tuple(1) );
  FRENSIE_CHECK_EQUAL( std::make_tuple(1), std::make_tuple(0) );
  
  FRENSIE_CHECK_EQUAL( std::make_tuple(0.), std::make_tuple(0.) );
  FRENSIE_CHECK_EQUAL( std::make_tuple(1.), std::make_tuple(0.) );
  FRENSIE_CHECK_EQUAL( std::make_tuple(1.), std::make_tuple(1.) );
  
  FRENSIE_CHECK_EQUAL( std::make_tuple(0, 1.0, std::string("test string")),
                       std::make_tuple(0, 1.0, std::string("test string")) );
  FRENSIE_CHECK_EQUAL( std::make_tuple(0, 1.0, std::string("test string")),
                       std::make_tuple(0, 1.0, std::string("string")) );
  FRENSIE_CHECK_EQUAL( std::make_tuple(0, 0.0, std::string("test string")),
                       std::make_tuple(0, 1.0, std::string("test string")) );
  FRENSIE_CHECK_EQUAL( std::make_tuple(1, 1.0, std::string("test string")),
                       std::make_tuple(0, 1.0, std::string("test string")) );
  
  FRENSIE_CHECK_EQUAL( std::make_pair(0, 1.0), std::make_pair(0, 1.0) );
  FRENSIE_CHECK_EQUAL( std::make_pair(0, 0.0), std::make_pair(0, 1.0) );
  FRENSIE_CHECK_EQUAL( std::make_pair(0, 1.0), std::make_pair(1, 1.0) );
  FRENSIE_CHECK_EQUAL( std::make_pair(0, 1.0), std::make_pair(1, 0.0) );
  
  FRENSIE_CHECK_EQUAL( std::list<int>({0, 1, 2}), std::list<int>({0, 1, 2}) );
  FRENSIE_CHECK_EQUAL( std::list<int>({0, 1, 2}), std::list<int>({0, 1}) );
  FRENSIE_CHECK_EQUAL( std::list<int>({0, 1, 2}), std::list<int>({0, 1, 3}) );
  
  FRENSIE_CHECK_EQUAL( std::list<double>({0., 1., 2.}), std::list<double>({0., 1., 2.}) );
  FRENSIE_CHECK_EQUAL( std::list<double>({0., 1.}), std::list<double>({0., 1., 2.}) );
  FRENSIE_CHECK_EQUAL( std::list<double>({0., 1., 3.}), std::list<double>({0., 1., 2.}) );
  
  FRENSIE_CHECK_EQUAL( std::list<std::string>({"test", "string"} ), std::list<std::string>({"test", "string"}) );
  FRENSIE_CHECK_EQUAL( std::list<std::string>({"test", "string"} ), std::list<std::string>({"test"}) );
  FRENSIE_CHECK_EQUAL( std::list<std::string>({"test", "string"} ), std::list<std::string>({"test", ""}) );

  FRENSIE_CHECK_EQUAL( std::forward_list<int>({0, 1, 2}), std::forward_list<int>({0, 1, 2}) );
  FRENSIE_CHECK_EQUAL( std::forward_list<int>({0, 1, 2}), std::forward_list<int>({0, 1}) );
  FRENSIE_CHECK_EQUAL( std::forward_list<int>({0, 1, 2}), std::forward_list<int>({0, 1, 3}) );
  
  FRENSIE_CHECK_EQUAL( std::forward_list<double>({0., 1., 2.}), std::forward_list<double>({0., 1., 2.}) );
  FRENSIE_CHECK_EQUAL( std::forward_list<double>({0., 1.}), std::forward_list<double>({0., 1., 2.}) );
  FRENSIE_CHECK_EQUAL( std::forward_list<double>({0., -1., 2.}), std::forward_list<double>({0., 1., 2.}) );
  
  FRENSIE_CHECK_EQUAL( std::forward_list<std::string>({"test", "string"} ), std::forward_list<std::string>({"test", "string"}) );
  FRENSIE_CHECK_EQUAL( std::forward_list<std::string>({"test"} ), std::forward_list<std::string>({"test", "string"}) );
  FRENSIE_CHECK_EQUAL( std::forward_list<std::string>({"test", "string"} ), std::forward_list<std::string>({"test", "what"}) );

  FRENSIE_CHECK_EQUAL( std::deque<int>({0, 1, 2}), std::deque<int>({0, 1, 2}) );
  FRENSIE_CHECK_EQUAL( std::deque<int>({0, 2}), std::deque<int>({0, 1, 2}) );
  FRENSIE_CHECK_EQUAL( std::deque<int>({0, 3, 2}), std::deque<int>({0, 1, 2}) );
  
  FRENSIE_CHECK_EQUAL( std::deque<double>({0., 1., 2.}), std::deque<double>({0., 1., 2.}) );
  FRENSIE_CHECK_EQUAL( std::deque<double>({1., 2.}), std::deque<double>({0., 1., 2.}) );
  FRENSIE_CHECK_EQUAL( std::deque<double>({-1., 1., 2.}), std::deque<double>({0., 1., 2.}) );
  
  FRENSIE_CHECK_EQUAL( std::deque<std::string>({"test", "string"} ), std::deque<std::string>({"test", "string"}) );
  FRENSIE_CHECK_EQUAL( std::deque<std::string>({"test", "string"} ), std::deque<std::string>({"test"}) );
  FRENSIE_CHECK_EQUAL( std::deque<std::string>({"t", "string"} ), std::deque<std::string>({"test", "string"}) );

  FRENSIE_CHECK_EQUAL( (std::array<int,3>({0, 1, 2})), (std::array<int,3>({0, 1, 2})) );
  FRENSIE_CHECK_EQUAL( (std::array<int,3>({0, 1, 3})), (std::array<int,3>({0, 1, 2})) );
  FRENSIE_CHECK_EQUAL( (std::array<double,3>({0., 3., 2.})), (std::array<double,3>({0., 1., 2.})) );
  
  FRENSIE_CHECK_EQUAL( std::vector<int>({0, 1, 2}), std::vector<int>({0, 1, 2}) );
  FRENSIE_CHECK_EQUAL( std::vector<int>({0, 2}), std::vector<int>({0, 1, 2}) );
  FRENSIE_CHECK_EQUAL( std::vector<int>({0, 1, 2}), std::vector<int>({0, 3, 2}) );
  
  FRENSIE_CHECK_EQUAL( std::vector<double>({0., 1., 2.}), std::vector<double>({0., 1., 2.}) );
  FRENSIE_CHECK_EQUAL( std::vector<double>({0., 1., 2.}), std::vector<double>({1., 2.}) );
  FRENSIE_CHECK_EQUAL( std::vector<double>({0., -1., 2.}), std::vector<double>({0., 1., 2.}) );
  
  FRENSIE_CHECK_EQUAL( std::vector<std::string>({"test", "string"} ), std::vector<std::string>({"test", "string"}) );
  FRENSIE_CHECK_EQUAL( std::vector<std::string>({"test"} ), std::vector<std::string>({"test", "string"}) );
  FRENSIE_CHECK_EQUAL( std::vector<std::string>({"test", "string"} ), std::vector<std::string>({"test", "ring"}) );

  FRENSIE_CHECK_EQUAL( std::set<int>({0, 1, 2}), std::set<int>({0, 1, 2}) );
  FRENSIE_CHECK_EQUAL( std::set<int>({0, 2}), std::set<int>({0, 1, 2}) );
  FRENSIE_CHECK_EQUAL( std::set<int>({0, 3, 2}), std::set<int>({0, 1, 2}) );
  
  FRENSIE_CHECK_EQUAL( std::set<std::string>({"test", "string"}), std::set<std::string>({"test", "string"}) );
  FRENSIE_CHECK_EQUAL( std::set<std::string>({"test"}), std::set<std::string>({"test", "string"}) );
  FRENSIE_CHECK_EQUAL( std::set<std::string>({"test", "string"}), std::set<std::string>({"test", "sing"}) );

  FRENSIE_CHECK_EQUAL( std::unordered_set<int>({0, 1, 2}), std::unordered_set<int>({0, 1, 2}) );
  FRENSIE_CHECK_EQUAL( std::unordered_set<int>({0, 2}), std::unordered_set<int>({0, 1, 2}) );
  FRENSIE_CHECK_EQUAL( std::unordered_set<int>({0, 1, 2}), std::unordered_set<int>({0, 3, 2}) );
  
  FRENSIE_CHECK_EQUAL( std::unordered_set<std::string>({"test", "string"}), std::unordered_set<std::string>({"test", "string"}) );
  FRENSIE_CHECK_EQUAL( std::unordered_set<std::string>({"test", "string"}), std::unordered_set<std::string>({"test"}) );
  FRENSIE_CHECK_EQUAL( std::unordered_set<std::string>({"test", "string"}), std::unordered_set<std::string>({"tst", "string"}) );

  FRENSIE_CHECK_EQUAL( (std::map<int,int>({{0, 0}, {1, 1}})), (std::map<int,int>({{0, 0}, {1, 1}})) );
  FRENSIE_CHECK_EQUAL( (std::map<int,int>({{0, 0}})), (std::map<int,int>({{0, 0}, {1, 1}})) );
  FRENSIE_CHECK_EQUAL( (std::map<int,int>({{0, 1}, {1, 1}})), (std::map<int,int>({{0, 0}, {1, 1}})) );
  
  FRENSIE_CHECK_EQUAL( (std::map<int,double>({{0, 0.}, {1, 1.}})), (std::map<int,double>({{0, 0.}, {1, 1.}})) );
  FRENSIE_CHECK_EQUAL( (std::map<int,double>({{0, 0.}, {1, 1.}})), (std::map<int,double>({{0, 0.}})) );
  FRENSIE_CHECK_EQUAL( (std::map<int,double>({{0, 0.}, {1, 1.}})), (std::map<int,double>({{0, 0.}, {1, 2.}})) );

  FRENSIE_CHECK_EQUAL( (std::unordered_map<int,int>({{0, 0}, {1, 1}})), (std::unordered_map<int,int>({{0, 0}, {1, 1}})) );
  FRENSIE_CHECK_EQUAL( (std::unordered_map<int,int>({{0, 0}, {1, 1}})), (std::unordered_map<int,int>({{1, 1}})) );
  FRENSIE_CHECK_EQUAL( (std::unordered_map<int,int>({{0, 0}, {1, 1}})), (std::unordered_map<int,int>({{0, 1}, {1, 1}})) );
  
  FRENSIE_CHECK_EQUAL( (std::unordered_map<int,double>({{0, 0.}, {1, 1.}})), (std::unordered_map<int,double>({{0, 0.}, {1, 1.}})) );
  FRENSIE_CHECK_EQUAL( (std::unordered_map<int,double>({{0, 0.}, {1, 1.}})), (std::unordered_map<int,double>({{0, 0.}})) );
  FRENSIE_CHECK_EQUAL( (std::unordered_map<int,double>({{0, 0.}, {1, 1.}})), (std::unordered_map<int,double>({{0, 1.}, {1, 1.}})) );
}

// A custom signal handler for seg faults
void SegFaultSignalHandler( int signal )      
{                                             
  throw std::logic_error( "Seg Fault Detected!" ); 
}

// A custom main function for running the mock unit tests
int main( int argc, char** argv )                  
{                                                  
  signal( SIGSEGV, &SegFaultSignalHandler );
  
  Utility::UnitTestManager& unit_test_manager =
    Utility::UnitTestManager::getInstance();

  unit_test_manager.runUnitTests( argc, argv );
}

//---------------------------------------------------------------------------//
// end tstFRENSIEUnitTestFrameworkDefaultInit.cpp
//---------------------------------------------------------------------------//
