//---------------------------------------------------------------------------//
//!
//! \file   tstFRENSIEUnitTestHarnessDefaultInit.cpp
//! \author Alex Robinson
//! \brief  FRENSIE Unit Test Harness test with default initialization
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <csignal>
#include <cstdlib>

// FRENSIE Includes
#include "Utility_UnitTestHarness.hpp"
#include "Utility_GlobalMPISession.hpp"
#include "Utility_Tuple.hpp"
#include "Utility_List.hpp"
#include "Utility_Deque.hpp"
#include "Utility_Array.hpp"
#include "Utility_Vector.hpp"
#include "Utility_Set.hpp"
#include "Utility_Map.hpp"
#include "Utility_StaticOutputFormatter.hpp"

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
// Check that the REQUIRE macro behaves correctly
FRENSIE_UNIT_TEST( UnitTestHarness, REQUIRE_pass )
{
  FRENSIE_REQUIRE( true );

  bool check_statement = true;

  FRENSIE_REQUIRE( check_statement );
}

//---------------------------------------------------------------------------//
// CHeck that the REQUIRE macro behaves correctly
FRENSIE_UNIT_TEST( UnitTestHarness, REQUIRE_fail )
{
  FRENSIE_REQUIRE( true );
  FRENSIE_REQUIRE( false );

  // We should never get here
  std::exit(EXIT_FAILURE);
}

//---------------------------------------------------------------------------//
// Check that the CHECK_EQUAL macro behaves correctly
FRENSIE_UNIT_TEST( UnitTestHarness, CHECK_EQUAL_pass )
{
  FRENSIE_CHECK_EQUAL( true, true );
  FRENSIE_CHECK_EQUAL( 0, 0 );
  FRENSIE_CHECK_EQUAL( 1u, 1u, SHOW_LHS );
  FRENSIE_CHECK_EQUAL( -2l, -2l, SHOW_RHS );
  FRENSIE_CHECK_EQUAL( 3ul, 3ul, SHOW_BOTH );
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

//---------------------------------------------------------------------------//
// Check that the REQUIRE_EQUAL macro behaves correctly
FRENSIE_UNIT_TEST( UnitTestHarness, REQUIRE_EQUAL_pass )
{
  FRENSIE_REQUIRE_EQUAL( true, true );
  FRENSIE_REQUIRE_EQUAL( 0, 0 );
  FRENSIE_REQUIRE_EQUAL( 1u, 1u, SHOW_LHS );
  FRENSIE_REQUIRE_EQUAL( -2l, -2l, SHOW_RHS );
  FRENSIE_REQUIRE_EQUAL( 3ul, 3ul, SHOW_BOTH );
  FRENSIE_REQUIRE_EQUAL( -4ll, -4ll );
  FRENSIE_REQUIRE_EQUAL( 3ull, 3ull );
  FRENSIE_REQUIRE_EQUAL( 1.0f, 1.0f );
  FRENSIE_REQUIRE_EQUAL( -1.0, -1.0 );
  
  FRENSIE_REQUIRE_EQUAL( std::string( "test string" ), std::string( "test string" ) );

  FRENSIE_REQUIRE_EQUAL( std::make_tuple(0), std::make_tuple(0) );
  FRENSIE_REQUIRE_EQUAL( std::make_tuple(0.), std::make_tuple(0.) );
  FRENSIE_REQUIRE_EQUAL( std::make_tuple(0, 1.0, std::string("test string")),
                       std::make_tuple(0, 1.0, std::string("test string")) );
  FRENSIE_REQUIRE_EQUAL( std::make_pair(0, 1.0), std::make_pair(0, 1.0) );
  
  FRENSIE_REQUIRE_EQUAL( std::list<int>({0, 1, 2}), std::list<int>({0, 1, 2}) );
  FRENSIE_REQUIRE_EQUAL( std::list<double>({0., 1., 2.}), std::list<double>({0., 1., 2.}) );
  FRENSIE_REQUIRE_EQUAL( std::list<std::string>({"test", "string"} ), std::list<std::string>({"test", "string"}) );

  FRENSIE_REQUIRE_EQUAL( std::forward_list<int>({0, 1, 2}), std::forward_list<int>({0, 1, 2}) );
  FRENSIE_REQUIRE_EQUAL( std::forward_list<double>({0., 1., 2.}), std::forward_list<double>({0., 1., 2.}) );
  FRENSIE_REQUIRE_EQUAL( std::forward_list<std::string>({"test", "string"} ), std::forward_list<std::string>({"test", "string"}) );

  FRENSIE_REQUIRE_EQUAL( std::deque<int>({0, 1, 2}), std::deque<int>({0, 1, 2}) );
  FRENSIE_REQUIRE_EQUAL( std::deque<double>({0., 1., 2.}), std::deque<double>({0., 1., 2.}) );
  FRENSIE_REQUIRE_EQUAL( std::deque<std::string>({"test", "string"} ), std::deque<std::string>({"test", "string"}) );

  FRENSIE_REQUIRE_EQUAL( (std::array<int,3>({0, 1, 2})), (std::array<int,3>({0, 1, 2})) );
  FRENSIE_REQUIRE_EQUAL( (std::array<double,3>({0., 1., 2.})), (std::array<double,3>({0., 1., 2.})) );
  
  FRENSIE_REQUIRE_EQUAL( std::vector<int>({0, 1, 2}), std::vector<int>({0, 1, 2}) );
  FRENSIE_REQUIRE_EQUAL( std::vector<double>({0., 1., 2.}), std::vector<double>({0., 1., 2.}) );
  FRENSIE_REQUIRE_EQUAL( std::vector<std::string>({"test", "string"} ), std::vector<std::string>({"test", "string"}) );

  FRENSIE_REQUIRE_EQUAL( std::set<int>({0, 1, 2}), std::set<int>({0, 1, 2}) );
  FRENSIE_REQUIRE_EQUAL( std::set<std::string>({"test", "string"}), std::set<std::string>({"test", "string"}) );

  FRENSIE_REQUIRE_EQUAL( std::unordered_set<int>({0, 1, 2}), std::unordered_set<int>({0, 1, 2}) );
  FRENSIE_REQUIRE_EQUAL( std::unordered_set<std::string>({"test", "string"}), std::unordered_set<std::string>({"test", "string"}) );

  FRENSIE_REQUIRE_EQUAL( (std::map<int,int>({{0, 0}, {1, 1}})), (std::map<int,int>({{0, 0}, {1, 1}})) );
  FRENSIE_REQUIRE_EQUAL( (std::map<int,double>({{0, 0.}, {1, 1.}})), (std::map<int,double>({{0, 0.}, {1, 1.}})) );

  FRENSIE_REQUIRE_EQUAL( (std::unordered_map<int,int>({{0, 0}, {1, 1}})), (std::unordered_map<int,int>({{0, 0}, {1, 1}})) );
  FRENSIE_REQUIRE_EQUAL( (std::unordered_map<int,double>({{0, 0.}, {1, 1.}})), (std::unordered_map<int,double>({{0, 0.}, {1, 1.}})) );
}

//---------------------------------------------------------------------------//
// Check that the REQUIRE_EQUAL macro behaves correctly
FRENSIE_UNIT_TEST( UnitTestHarness, REQUIRE_EQUAL_fail )
{
  FRENSIE_REQUIRE_EQUAL( true, true );
  FRENSIE_REQUIRE_EQUAL( false, true );

  // We should never get here
  std::exit(EXIT_FAILURE);
}

//---------------------------------------------------------------------------//
// Check that the CHECK_DIFFERENT macro behaves correctly
FRENSIE_UNIT_TEST( UnitTestHarness, CHECK_DIFFERENT_pass )
{
  FRENSIE_CHECK_DIFFERENT( true, false );
  FRENSIE_CHECK_DIFFERENT( 0, 1 );
  FRENSIE_CHECK_DIFFERENT( 1u, 0u, SHOW_LHS );
  FRENSIE_CHECK_DIFFERENT( -2l, 2l, SHOW_RHS );
  FRENSIE_CHECK_DIFFERENT( 3ul, 2ul, SHOW_BOTH );
  FRENSIE_CHECK_DIFFERENT( -4ll, 4ll );
  FRENSIE_CHECK_DIFFERENT( 4ull, 3ull );
  FRENSIE_CHECK_DIFFERENT( 1.0f, -1.0f );
  FRENSIE_CHECK_DIFFERENT( 1.0, -1.0 );
  
  FRENSIE_CHECK_DIFFERENT( std::string( "lhs test string" ), std::string( "rhs test string" ) );

  FRENSIE_CHECK_DIFFERENT( std::make_tuple(0), std::make_tuple(1) );
  FRENSIE_CHECK_DIFFERENT( std::make_tuple(0.), std::make_tuple(1.) );
  FRENSIE_CHECK_DIFFERENT( std::make_tuple(0, 1.0, std::string("test string")),
                           std::make_tuple(1, 1.0, std::string("test string")) );
  FRENSIE_CHECK_DIFFERENT( std::make_pair(0, 1.0), std::make_pair(1, 2.0) );
  
  FRENSIE_CHECK_DIFFERENT( std::list<int>({0, 1, 2}), std::list<int>({1, 2}) );
  FRENSIE_CHECK_DIFFERENT( std::list<double>({1., 1., 2.}), std::list<double>({0., 1., 2.}) );
  FRENSIE_CHECK_DIFFERENT( std::list<std::string>({"test", "string"} ), std::list<std::string>({"string"}) );

  FRENSIE_CHECK_DIFFERENT( std::forward_list<int>({0, 1, 2}), std::forward_list<int>({0, 1, 3}) );
  FRENSIE_CHECK_DIFFERENT( std::forward_list<double>({0., 1., 2.}), std::forward_list<double>({0., 3., 2.}) );
  FRENSIE_CHECK_DIFFERENT( std::forward_list<std::string>({"test", "string"} ), std::forward_list<std::string>({"test", "sing"}) );

  FRENSIE_CHECK_DIFFERENT( std::deque<int>({1, 2}), std::deque<int>({0, 1, 2}) );
  FRENSIE_CHECK_DIFFERENT( std::deque<double>({0., 2.}), std::deque<double>({0., 1., 2.}) );
  FRENSIE_CHECK_DIFFERENT( std::deque<std::string>({"test", "string"} ), std::deque<std::string>({"t", "string"}) );

  FRENSIE_CHECK_DIFFERENT( (std::array<int,3>({0, 3, 2})), (std::array<int,3>({0, 1, 2})) );
  FRENSIE_CHECK_DIFFERENT( (std::array<double,3>({0., 1., 2.})), (std::array<double,3>({0., 1., 3.})) );
  
  FRENSIE_CHECK_DIFFERENT( std::vector<int>({0, 2}), std::vector<int>({0, 1, 2}) );
  FRENSIE_CHECK_DIFFERENT( std::vector<double>({0., 1., 2.}), std::vector<double>({0., 2.}) );
  FRENSIE_CHECK_DIFFERENT( std::vector<std::string>({"tst", "string"} ), std::vector<std::string>({"test", "string"}) );

  FRENSIE_CHECK_DIFFERENT( std::set<int>({0, 2}), std::set<int>({0, 1, 2}) );
  FRENSIE_CHECK_DIFFERENT( std::set<std::string>({"test", "string"}), std::set<std::string>({"test"}) );

  FRENSIE_CHECK_DIFFERENT( std::unordered_set<int>({0, 1, 2}), std::unordered_set<int>({0, 1, 3}) );
  FRENSIE_CHECK_DIFFERENT( std::unordered_set<std::string>({"test", "sing"}), std::unordered_set<std::string>({"test", "string"}) );

  FRENSIE_CHECK_DIFFERENT( (std::map<int,int>({{0, 0}, {1, 1}})), (std::map<int,int>({{0, 0}, {1, 1}, {2, 2}})) );
  FRENSIE_CHECK_DIFFERENT( (std::map<int,double>({{0, 0.}, {1, 1.}})), (std::map<int,double>({{0, 0.}, {1, 1.}, {2, 2.}})) );

  FRENSIE_CHECK_DIFFERENT( (std::unordered_map<int,int>({{0, 0}, {1, 1}, {2, 2}})), (std::unordered_map<int,int>({{0, 0}, {1, 1}})) );
  FRENSIE_CHECK_DIFFERENT( (std::unordered_map<int,double>({{0, 0.}, {1, 1.}, {2, 2.}})), (std::unordered_map<int,double>({{0, 0.}, {1, 1.}})) );
}

//---------------------------------------------------------------------------//
// Check that the CHECK_DIFFERENT macro behaves correctly
FRENSIE_UNIT_TEST( UnitTestHarness, CHECK_DIFFERENT_fail )
{
  FRENSIE_CHECK_DIFFERENT( true, true );
  FRENSIE_CHECK_DIFFERENT( 0, 0 );
  FRENSIE_CHECK_DIFFERENT( 1u, 1u );
  FRENSIE_CHECK_DIFFERENT( -2l, -2l );
  FRENSIE_CHECK_DIFFERENT( 3ul, 3ul );
  FRENSIE_CHECK_DIFFERENT( -4ll, -4ll );
  FRENSIE_CHECK_DIFFERENT( 3ull, 3ull );
  FRENSIE_CHECK_DIFFERENT( 1.0f, 1.0f );
  FRENSIE_CHECK_DIFFERENT( -1.0, -1.0 );
  
  FRENSIE_CHECK_DIFFERENT( std::string( "test string" ), std::string( "test string" ) );

  FRENSIE_CHECK_DIFFERENT( std::make_tuple(0), std::make_tuple(0) );
  FRENSIE_CHECK_DIFFERENT( std::make_tuple(0.), std::make_tuple(0.) );
  FRENSIE_CHECK_DIFFERENT( std::make_tuple(0, 1.0, std::string("test string")),
                           std::make_tuple(0, 1.0, std::string("test string")) );
  FRENSIE_CHECK_DIFFERENT( std::make_pair(0, 1.0), std::make_pair(0, 1.0) );
  
  FRENSIE_CHECK_DIFFERENT( std::list<int>({0, 1, 2}), std::list<int>({0, 1, 2}) );
  FRENSIE_CHECK_DIFFERENT( std::list<double>({0., 1., 2.}), std::list<double>({0., 1., 2.}) );
  FRENSIE_CHECK_DIFFERENT( std::list<std::string>({"test", "string"} ), std::list<std::string>({"test", "string"}) );

  FRENSIE_CHECK_DIFFERENT( std::forward_list<int>({0, 1, 2}), std::forward_list<int>({0, 1, 2}) );
  FRENSIE_CHECK_DIFFERENT( std::forward_list<double>({0., 1., 2.}), std::forward_list<double>({0., 1., 2.}) );
  FRENSIE_CHECK_DIFFERENT( std::forward_list<std::string>({"test", "string"} ), std::forward_list<std::string>({"test", "string"}) );

  FRENSIE_CHECK_DIFFERENT( std::deque<int>({0, 1, 2}), std::deque<int>({0, 1, 2}) );
  FRENSIE_CHECK_DIFFERENT( std::deque<double>({0., 1., 2.}), std::deque<double>({0., 1., 2.}) );
  FRENSIE_CHECK_DIFFERENT( std::deque<std::string>({"test", "string"} ), std::deque<std::string>({"test", "string"}) );

  FRENSIE_CHECK_DIFFERENT( (std::array<int,3>({0, 1, 2})), (std::array<int,3>({0, 1, 2})) );
  FRENSIE_CHECK_DIFFERENT( (std::array<double,3>({0., 1., 2.})), (std::array<double,3>({0., 1., 2.})) );
  
  FRENSIE_CHECK_DIFFERENT( std::vector<int>({0, 1, 2}), std::vector<int>({0, 1, 2}) );
  FRENSIE_CHECK_DIFFERENT( std::vector<double>({0., 1., 2.}), std::vector<double>({0., 1., 2.}) );
  FRENSIE_CHECK_DIFFERENT( std::vector<std::string>({"test", "string"} ), std::vector<std::string>({"test", "string"}) );

  FRENSIE_CHECK_DIFFERENT( std::set<int>({0, 1, 2}), std::set<int>({0, 1, 2}) );
  FRENSIE_CHECK_DIFFERENT( std::set<std::string>({"test", "string"}), std::set<std::string>({"test", "string"}) );

  FRENSIE_CHECK_DIFFERENT( std::unordered_set<int>({0, 1, 2}), std::unordered_set<int>({0, 1, 2}) );
  FRENSIE_CHECK_DIFFERENT( std::unordered_set<std::string>({"test", "string"}), std::unordered_set<std::string>({"test", "string"}) );

  FRENSIE_CHECK_DIFFERENT( (std::map<int,int>({{0, 0}, {1, 1}})), (std::map<int,int>({{0, 0}, {1, 1}})) );
  FRENSIE_CHECK_DIFFERENT( (std::map<int,double>({{0, 0.}, {1, 1.}})), (std::map<int,double>({{0, 0.}, {1, 1.}})) );

  FRENSIE_CHECK_DIFFERENT( (std::unordered_map<int,int>({{0, 0}, {1, 1}})), (std::unordered_map<int,int>({{0, 0}, {1, 1}})) );
  FRENSIE_CHECK_DIFFERENT( (std::unordered_map<int,double>({{0, 0.}, {1, 1.}})), (std::unordered_map<int,double>({{0, 0.}, {1, 1.}})) );
}

//---------------------------------------------------------------------------//
// Check that the REQUIRE_DIFFERENT macro behaves correctly
FRENSIE_UNIT_TEST( UnitTestHarness, REQUIRE_DIFFERENT_pass )
{
  FRENSIE_REQUIRE_DIFFERENT( true, false );
  FRENSIE_REQUIRE_DIFFERENT( 0, 1 );
  FRENSIE_REQUIRE_DIFFERENT( 1u, 0u, SHOW_LHS );
  FRENSIE_REQUIRE_DIFFERENT( -2l, 2l, SHOW_RHS );
  FRENSIE_REQUIRE_DIFFERENT( 3ul, 2ul, SHOW_BOTH );
  FRENSIE_REQUIRE_DIFFERENT( -4ll, 4ll );
  FRENSIE_REQUIRE_DIFFERENT( 4ull, 3ull );
  FRENSIE_REQUIRE_DIFFERENT( 1.0f, -1.0f );
  FRENSIE_REQUIRE_DIFFERENT( 1.0, -1.0 );
  
  FRENSIE_REQUIRE_DIFFERENT( std::string( "lhs test string" ), std::string( "rhs test string" ) );

  FRENSIE_REQUIRE_DIFFERENT( std::make_tuple(0), std::make_tuple(1) );
  FRENSIE_REQUIRE_DIFFERENT( std::make_tuple(0.), std::make_tuple(1.) );
  FRENSIE_REQUIRE_DIFFERENT( std::make_tuple(0, 1.0, std::string("test string")),
                           std::make_tuple(1, 1.0, std::string("test string")) );
  FRENSIE_REQUIRE_DIFFERENT( std::make_pair(0, 1.0), std::make_pair(1, 2.0) );
  
  FRENSIE_REQUIRE_DIFFERENT( std::list<int>({0, 1, 2}), std::list<int>({1, 2}) );
  FRENSIE_REQUIRE_DIFFERENT( std::list<double>({1., 1., 2.}), std::list<double>({0., 1., 2.}) );
  FRENSIE_REQUIRE_DIFFERENT( std::list<std::string>({"test", "string"} ), std::list<std::string>({"string"}) );

  FRENSIE_REQUIRE_DIFFERENT( std::forward_list<int>({0, 1, 2}), std::forward_list<int>({0, 1, 3}) );
  FRENSIE_REQUIRE_DIFFERENT( std::forward_list<double>({0., 1., 2.}), std::forward_list<double>({0., 3., 2.}) );
  FRENSIE_REQUIRE_DIFFERENT( std::forward_list<std::string>({"test", "string"} ), std::forward_list<std::string>({"test", "sing"}) );

  FRENSIE_REQUIRE_DIFFERENT( std::deque<int>({1, 2}), std::deque<int>({0, 1, 2}) );
  FRENSIE_REQUIRE_DIFFERENT( std::deque<double>({0., 2.}), std::deque<double>({0., 1., 2.}) );
  FRENSIE_REQUIRE_DIFFERENT( std::deque<std::string>({"test", "string"} ), std::deque<std::string>({"t", "string"}) );

  FRENSIE_REQUIRE_DIFFERENT( (std::array<int,3>({0, 3, 2})), (std::array<int,3>({0, 1, 2})) );
  FRENSIE_REQUIRE_DIFFERENT( (std::array<double,3>({0., 1., 2.})), (std::array<double,3>({0., 1., 3.})) );
  
  FRENSIE_REQUIRE_DIFFERENT( std::vector<int>({0, 2}), std::vector<int>({0, 1, 2}) );
  FRENSIE_REQUIRE_DIFFERENT( std::vector<double>({0., 1., 2.}), std::vector<double>({0., 2.}) );
  FRENSIE_REQUIRE_DIFFERENT( std::vector<std::string>({"tst", "string"} ), std::vector<std::string>({"test", "string"}) );

  FRENSIE_REQUIRE_DIFFERENT( std::set<int>({0, 2}), std::set<int>({0, 1, 2}) );
  FRENSIE_REQUIRE_DIFFERENT( std::set<std::string>({"test", "string"}), std::set<std::string>({"test"}) );

  FRENSIE_REQUIRE_DIFFERENT( std::unordered_set<int>({0, 1, 2}), std::unordered_set<int>({0, 1, 3}) );
  FRENSIE_REQUIRE_DIFFERENT( std::unordered_set<std::string>({"test", "sing"}), std::unordered_set<std::string>({"test", "string"}) );

  FRENSIE_REQUIRE_DIFFERENT( (std::map<int,int>({{0, 0}, {1, 1}})), (std::map<int,int>({{0, 0}, {1, 1}, {2, 2}})) );
  FRENSIE_REQUIRE_DIFFERENT( (std::map<int,double>({{0, 0.}, {1, 1.}})), (std::map<int,double>({{0, 0.}, {1, 1.}, {2, 2.}})) );

  FRENSIE_REQUIRE_DIFFERENT( (std::unordered_map<int,int>({{0, 0}, {1, 1}, {2, 2}})), (std::unordered_map<int,int>({{0, 0}, {1, 1}})) );
  FRENSIE_REQUIRE_DIFFERENT( (std::unordered_map<int,double>({{0, 0.}, {1, 1.}, {2, 2.}})), (std::unordered_map<int,double>({{0, 0.}, {1, 1.}})) );
}

//---------------------------------------------------------------------------//
// Check that the REQUIRE_DIFFERENT macro behaves correctly
FRENSIE_UNIT_TEST( UnitTestHarness, REQUIRE_DIFFERENT_fail )
{
  FRENSIE_REQUIRE_DIFFERENT( true, false );
  FRENSIE_REQUIRE_DIFFERENT( true, true );

  // We should never get here
  std::exit(EXIT_FAILURE);
}

//---------------------------------------------------------------------------//
// Check that the CHECK_GREATER macro behaves correctly
FRENSIE_UNIT_TEST( UnitTestHarness, CHECK_GREATER_pass )
{
  FRENSIE_CHECK_GREATER( 1, 0 );
  FRENSIE_CHECK_GREATER( 2u, 1u, SHOW_LHS );
  FRENSIE_CHECK_GREATER( 2l, -2l, SHOW_RHS );
  FRENSIE_CHECK_GREATER( 10ul, 3ul, SHOW_BOTH );
  FRENSIE_CHECK_GREATER( 4ll, -4ll );
  FRENSIE_CHECK_GREATER( 4ull, 3ull );
  FRENSIE_CHECK_GREATER( 2.0f, 1.0f );
  FRENSIE_CHECK_GREATER( 1.0, -1.0 );
  
  FRENSIE_CHECK_GREATER( std::string( "b" ), std::string( "a" ) );
  FRENSIE_CHECK_GREATER( std::make_tuple(1), std::make_tuple(0) );
  FRENSIE_CHECK_GREATER( std::make_tuple(1,2), std::make_tuple(0,1) );
  FRENSIE_CHECK_GREATER( std::make_pair(1,2), std::make_pair(0,1) );
}

//---------------------------------------------------------------------------//
// Check that the CHECK_GREATER macro behaves correctly
FRENSIE_UNIT_TEST( UnitTestHarness, CHECK_GREATER_fail )
{
  FRENSIE_CHECK_GREATER( 0, 0 );
  FRENSIE_CHECK_GREATER( 0, 1 );
  
  FRENSIE_CHECK_GREATER( 2u, 2u );
  FRENSIE_CHECK_GREATER( 1u, 2u );
  
  FRENSIE_CHECK_GREATER( 2l, 2l );
  FRENSIE_CHECK_GREATER( -2l, 2l );
  
  FRENSIE_CHECK_GREATER( 3ul, 3ul );
  FRENSIE_CHECK_GREATER( 3ul, 10ul );
  
  FRENSIE_CHECK_GREATER( 4ll, 4ll );
  FRENSIE_CHECK_GREATER( -4ll, 4ll );
  
  FRENSIE_CHECK_GREATER( 4ull, 4ull );
  FRENSIE_CHECK_GREATER( 3ull, 4ull );
  
  FRENSIE_CHECK_GREATER( 2.0f, 2.0f );
  FRENSIE_CHECK_GREATER( 1.0f, 2.0f );
  
  FRENSIE_CHECK_GREATER( 1.0, 1.0 );
  FRENSIE_CHECK_GREATER( -1.0, 1.0 );
  
  FRENSIE_CHECK_GREATER( std::string( "a" ), std::string( "a" ) );
  FRENSIE_CHECK_GREATER( std::string( "a" ), std::string( "b" ) );
  
  FRENSIE_CHECK_GREATER( std::make_tuple(0), std::make_tuple(0) );
  FRENSIE_CHECK_GREATER( std::make_tuple(0), std::make_tuple(1) );
  
  FRENSIE_CHECK_GREATER( std::make_tuple(1,2), std::make_tuple(1,2) );
  FRENSIE_CHECK_GREATER( std::make_tuple(0,1), std::make_tuple(1,2) );
  
  FRENSIE_CHECK_GREATER( std::make_pair(1,2), std::make_pair(1,2) );
  FRENSIE_CHECK_GREATER( std::make_pair(0,1), std::make_pair(1,2) );
}

//---------------------------------------------------------------------------//
// Check that the REQUIRE_GREATER macro behaves correctly
FRENSIE_UNIT_TEST( UnitTestHarness, REQUIRE_GREATER_pass )
{
  FRENSIE_REQUIRE_GREATER( 1, 0 );
  FRENSIE_REQUIRE_GREATER( 2u, 1u, SHOW_LHS );
  FRENSIE_REQUIRE_GREATER( 2l, -2l, SHOW_RHS );
  FRENSIE_REQUIRE_GREATER( 10ul, 3ul, SHOW_BOTH );
  FRENSIE_REQUIRE_GREATER( 4ll, -4ll );
  FRENSIE_REQUIRE_GREATER( 4ull, 3ull );
  FRENSIE_REQUIRE_GREATER( 2.0f, 1.0f );
  FRENSIE_REQUIRE_GREATER( 1.0, -1.0 );
  
  FRENSIE_REQUIRE_GREATER( std::string( "b" ), std::string( "a" ) );
  FRENSIE_REQUIRE_GREATER( std::make_tuple(1), std::make_tuple(0) );
  FRENSIE_REQUIRE_GREATER( std::make_tuple(1,2), std::make_tuple(0,1) );
  FRENSIE_REQUIRE_GREATER( std::make_pair(1,2), std::make_pair(0,1) );
}

//---------------------------------------------------------------------------//
// Check that the REQUIRE_GREATER macro behaves correctly
FRENSIE_UNIT_TEST( UnitTestHarness, REQUIRE_GREATER_fail )
{
  FRENSIE_REQUIRE_GREATER( 1, 0 );
  FRENSIE_REQUIRE_GREATER( 0, 0 );

  // We should never get here
  std::exit(EXIT_FAILURE);
}

//---------------------------------------------------------------------------//
// Check that the CHECK_GREATER_OR_EQUAL macro behaves correctly
FRENSIE_UNIT_TEST( UnitTestHarness, CHECK_GREATER_OR_EQUAL_pass )
{
  FRENSIE_CHECK_GREATER_OR_EQUAL( 0, 0 );
  FRENSIE_CHECK_GREATER_OR_EQUAL( 1, 0 );

  FRENSIE_CHECK_GREATER_OR_EQUAL( 1u, 1u, SHOW_LHS );
  FRENSIE_CHECK_GREATER_OR_EQUAL( 2u, 1u );

  FRENSIE_CHECK_GREATER_OR_EQUAL( 2l, 2l, SHOW_RHS );
  FRENSIE_CHECK_GREATER_OR_EQUAL( 2l, -2l );
  
  FRENSIE_CHECK_GREATER_OR_EQUAL( 3ul, 3ul, SHOW_BOTH );
  FRENSIE_CHECK_GREATER_OR_EQUAL( 10ul, 3ul );

  FRENSIE_CHECK_GREATER_OR_EQUAL( 4ll, 4ll );
  FRENSIE_CHECK_GREATER_OR_EQUAL( 4ll, -4ll );
  
  FRENSIE_CHECK_GREATER_OR_EQUAL( 3ull, 3ull );
  FRENSIE_CHECK_GREATER_OR_EQUAL( 4ull, 3ull );
  
  FRENSIE_CHECK_GREATER_OR_EQUAL( 2.0f, 2.0f );
  FRENSIE_CHECK_GREATER_OR_EQUAL( 2.0f, 1.0f );

  FRENSIE_CHECK_GREATER_OR_EQUAL( 1.0, 1.0 );
  FRENSIE_CHECK_GREATER_OR_EQUAL( 1.0, -1.0 );
  
  FRENSIE_CHECK_GREATER_OR_EQUAL( std::string( "b" ), std::string( "b" ) );
  FRENSIE_CHECK_GREATER_OR_EQUAL( std::string( "b" ), std::string( "a" ) );

  FRENSIE_CHECK_GREATER_OR_EQUAL( std::make_tuple(0), std::make_tuple(0) );
  FRENSIE_CHECK_GREATER_OR_EQUAL( std::make_tuple(1), std::make_tuple(0) );

  FRENSIE_CHECK_GREATER_OR_EQUAL( std::make_tuple(0,1), std::make_tuple(0,1) );
  FRENSIE_CHECK_GREATER_OR_EQUAL( std::make_tuple(1,2), std::make_tuple(0,1) );
  
  FRENSIE_CHECK_GREATER_OR_EQUAL( std::make_pair(0,1), std::make_pair(0,1) );
  FRENSIE_CHECK_GREATER_OR_EQUAL( std::make_pair(1,2), std::make_pair(0,1) );
}

//---------------------------------------------------------------------------//
// Check that the CHECK_GREATER_OR_EQUAL macro behaves correctly
FRENSIE_UNIT_TEST( UnitTestHarness, CHECK_GREATER_OR_EQUAL_fail )
{
  FRENSIE_CHECK_GREATER_OR_EQUAL( 0, 1 );
  FRENSIE_CHECK_GREATER_OR_EQUAL( 1u, 2u );
  FRENSIE_CHECK_GREATER_OR_EQUAL( -2l, 2l );
  FRENSIE_CHECK_GREATER_OR_EQUAL( 3ul, 10ul );
  FRENSIE_CHECK_GREATER_OR_EQUAL( -4ll, 4ll );
  FRENSIE_CHECK_GREATER_OR_EQUAL( 3ull, 4ull );
  FRENSIE_CHECK_GREATER_OR_EQUAL( 1.0f, 2.0f );
  FRENSIE_CHECK_GREATER_OR_EQUAL( -1.0, 1.0 );
  FRENSIE_CHECK_GREATER_OR_EQUAL( std::string( "a" ), std::string( "b" ) );
  FRENSIE_CHECK_GREATER_OR_EQUAL( std::make_tuple(0), std::make_tuple(1) );
  FRENSIE_CHECK_GREATER_OR_EQUAL( std::make_tuple(0,1), std::make_tuple(1,2) );
  FRENSIE_CHECK_GREATER_OR_EQUAL( std::make_pair(0,1), std::make_pair(1,2) );
}

//---------------------------------------------------------------------------//
// Check that the REQUIRE_GREATER_OR_EQUAL macro behaves correctly
FRENSIE_UNIT_TEST( UnitTestHarness, REQUIRE_GREATER_OR_EQUAL_pass )
{
  FRENSIE_REQUIRE_GREATER_OR_EQUAL( 0, 0 );
  FRENSIE_REQUIRE_GREATER_OR_EQUAL( 1, 0 );

  FRENSIE_REQUIRE_GREATER_OR_EQUAL( 1u, 1u, SHOW_LHS );
  FRENSIE_REQUIRE_GREATER_OR_EQUAL( 2u, 1u );

  FRENSIE_REQUIRE_GREATER_OR_EQUAL( 2l, 2l, SHOW_RHS );
  FRENSIE_REQUIRE_GREATER_OR_EQUAL( 2l, -2l );
  
  FRENSIE_REQUIRE_GREATER_OR_EQUAL( 3ul, 3ul, SHOW_BOTH );
  FRENSIE_REQUIRE_GREATER_OR_EQUAL( 10ul, 3ul );

  FRENSIE_REQUIRE_GREATER_OR_EQUAL( 4ll, 4ll );
  FRENSIE_REQUIRE_GREATER_OR_EQUAL( 4ll, -4ll );
  
  FRENSIE_REQUIRE_GREATER_OR_EQUAL( 3ull, 3ull );
  FRENSIE_REQUIRE_GREATER_OR_EQUAL( 4ull, 3ull );
  
  FRENSIE_REQUIRE_GREATER_OR_EQUAL( 2.0f, 2.0f );
  FRENSIE_REQUIRE_GREATER_OR_EQUAL( 2.0f, 1.0f );

  FRENSIE_REQUIRE_GREATER_OR_EQUAL( 1.0, 1.0 );
  FRENSIE_REQUIRE_GREATER_OR_EQUAL( 1.0, -1.0 );
  
  FRENSIE_REQUIRE_GREATER_OR_EQUAL( std::string( "b" ), std::string( "b" ) );
  FRENSIE_REQUIRE_GREATER_OR_EQUAL( std::string( "b" ), std::string( "a" ) );

  FRENSIE_REQUIRE_GREATER_OR_EQUAL( std::make_tuple(0), std::make_tuple(0) );
  FRENSIE_REQUIRE_GREATER_OR_EQUAL( std::make_tuple(1), std::make_tuple(0) );

  FRENSIE_REQUIRE_GREATER_OR_EQUAL( std::make_tuple(0,1), std::make_tuple(0,1) );
  FRENSIE_REQUIRE_GREATER_OR_EQUAL( std::make_tuple(1,2), std::make_tuple(0,1) );
  
  FRENSIE_REQUIRE_GREATER_OR_EQUAL( std::make_pair(0,1), std::make_pair(0,1) );
  FRENSIE_REQUIRE_GREATER_OR_EQUAL( std::make_pair(1,2), std::make_pair(0,1) );
}

//---------------------------------------------------------------------------//
// Check that the REQUIRE_GREATER_OR_EQUAL macro behaves correctly
FRENSIE_UNIT_TEST( UnitTestHarness, REQUIRE_GREATER_OR_EQUAL_fail )
{
  FRENSIE_REQUIRE_GREATER_OR_EQUAL( 0, 1 );

  // We should never get here
  std::exit(EXIT_FAILURE);
}

//---------------------------------------------------------------------------//
// Check that the CHECK_LESS macro behaves correctly
FRENSIE_UNIT_TEST( UnitTestHarness, CHECK_LESS_pass )
{
  FRENSIE_CHECK_LESS( 0, 1 );
  FRENSIE_CHECK_LESS( 1u, 2u, SHOW_LHS );
  FRENSIE_CHECK_LESS( -2l, 2l, SHOW_RHS );
  FRENSIE_CHECK_LESS( 3ul, 10ul, SHOW_BOTH );
  FRENSIE_CHECK_LESS( -4ll, 4ll );
  FRENSIE_CHECK_LESS( 3ull, 4ull );
  FRENSIE_CHECK_LESS( 1.0f, 2.0f );
  FRENSIE_CHECK_LESS( -1.0, 1.0 );
  FRENSIE_CHECK_LESS( std::string( "a" ), std::string( "b" ) );
  FRENSIE_CHECK_LESS( std::make_tuple(0), std::make_tuple(1) );
  FRENSIE_CHECK_LESS( std::make_tuple(0,1), std::make_tuple(1,2) );
  FRENSIE_CHECK_LESS( std::make_pair(0,1), std::make_pair(1,2) );
}

//---------------------------------------------------------------------------//
// Check that the CHECK_LESS macro behaves correctly
FRENSIE_UNIT_TEST( UnitTestHarness, CHECK_LESS_fail )
{
  FRENSIE_CHECK_LESS( 0, 0 );
  FRENSIE_CHECK_LESS( 1, 0 );

  FRENSIE_CHECK_LESS( 1u, 1u );
  FRENSIE_CHECK_LESS( 2u, 1u );

  FRENSIE_CHECK_LESS( 2l, 2l );
  FRENSIE_CHECK_LESS( 2l, -2l );
  
  FRENSIE_CHECK_LESS( 3ul, 3ul );
  FRENSIE_CHECK_LESS( 10ul, 3ul );

  FRENSIE_CHECK_LESS( 4ll, 4ll );
  FRENSIE_CHECK_LESS( 4ll, -4ll );
  
  FRENSIE_CHECK_LESS( 3ull, 3ull );
  FRENSIE_CHECK_LESS( 4ull, 3ull );
  
  FRENSIE_CHECK_LESS( 2.0f, 2.0f );
  FRENSIE_CHECK_LESS( 2.0f, 1.0f );

  FRENSIE_CHECK_LESS( 1.0, 1.0 );
  FRENSIE_CHECK_LESS( 1.0, -1.0 );
  
  FRENSIE_CHECK_LESS( std::string( "b" ), std::string( "b" ) );
  FRENSIE_CHECK_LESS( std::string( "b" ), std::string( "a" ) );

  FRENSIE_CHECK_LESS( std::make_tuple(0), std::make_tuple(0) );
  FRENSIE_CHECK_LESS( std::make_tuple(1), std::make_tuple(0) );

  FRENSIE_CHECK_LESS( std::make_tuple(0,1), std::make_tuple(0,1) );
  FRENSIE_CHECK_LESS( std::make_tuple(1,2), std::make_tuple(0,1) );
  
  FRENSIE_CHECK_LESS( std::make_pair(0,1), std::make_pair(0,1) );
  FRENSIE_CHECK_LESS( std::make_pair(1,2), std::make_pair(0,1) );
}

//---------------------------------------------------------------------------//
// Check that the REQUIRE_LESS macro behaves correctly
FRENSIE_UNIT_TEST( UnitTestHarness, REQUIRE_LESS_pass )
{
  FRENSIE_REQUIRE_LESS( 0, 1 );
  FRENSIE_REQUIRE_LESS( 1u, 2u, SHOW_LHS );
  FRENSIE_REQUIRE_LESS( -2l, 2l, SHOW_RHS );
  FRENSIE_REQUIRE_LESS( 3ul, 10ul, SHOW_BOTH );
  FRENSIE_REQUIRE_LESS( -4ll, 4ll );
  FRENSIE_REQUIRE_LESS( 3ull, 4ull );
  FRENSIE_REQUIRE_LESS( 1.0f, 2.0f );
  FRENSIE_REQUIRE_LESS( -1.0, 1.0 );
  FRENSIE_REQUIRE_LESS( std::string( "a" ), std::string( "b" ) );
  FRENSIE_REQUIRE_LESS( std::make_tuple(0), std::make_tuple(1) );
  FRENSIE_REQUIRE_LESS( std::make_tuple(0,1), std::make_tuple(1,2) );
  FRENSIE_REQUIRE_LESS( std::make_pair(0,1), std::make_pair(1,2) );
}

//---------------------------------------------------------------------------//
// Check that the REQUIRE_LESS macro behaves correctly
FRENSIE_UNIT_TEST( UnitTestHarness, REQUIRE_LESS_fail )
{
  FRENSIE_REQUIRE_LESS( 0, 0 );

  // We should never get here
  std::exit(EXIT_FAILURE);
}

//---------------------------------------------------------------------------//
// Check that the CHECK_LESS_OR_EQUAL macro behaves correctly
FRENSIE_UNIT_TEST( UnitTestHarness, CHECK_LESS_OR_EQUAL_pass )
{
  FRENSIE_CHECK_LESS_OR_EQUAL( 0, 0 );
  FRENSIE_CHECK_LESS_OR_EQUAL( 0, 1 );
  
  FRENSIE_CHECK_LESS_OR_EQUAL( 1u, 1u, SHOW_LHS );
  FRENSIE_CHECK_LESS_OR_EQUAL( 1u, 2u );

  FRENSIE_CHECK_LESS_OR_EQUAL( 2l, 2l, SHOW_RHS );
  FRENSIE_CHECK_LESS_OR_EQUAL( -2l, 2l );

  FRENSIE_CHECK_LESS_OR_EQUAL( 3ul, 3ul, SHOW_BOTH );
  FRENSIE_CHECK_LESS_OR_EQUAL( 3ul, 10ul );

  FRENSIE_CHECK_LESS_OR_EQUAL( 4ll, 4ll );
  FRENSIE_CHECK_LESS_OR_EQUAL( -4ll, 4ll );

  FRENSIE_CHECK_LESS_OR_EQUAL( 3ull, 3ull );
  FRENSIE_CHECK_LESS_OR_EQUAL( 3ull, 4ull );

  FRENSIE_CHECK_LESS_OR_EQUAL( 1.0f, 1.0f );
  FRENSIE_CHECK_LESS_OR_EQUAL( 1.0f, 2.0f );

  FRENSIE_CHECK_LESS_OR_EQUAL( 1.0, 1.0 );
  FRENSIE_CHECK_LESS_OR_EQUAL( -1.0, 1.0 );

  FRENSIE_CHECK_LESS_OR_EQUAL( std::string( "a" ), std::string( "a" ) );
  FRENSIE_CHECK_LESS_OR_EQUAL( std::string( "a" ), std::string( "b" ) );

  FRENSIE_CHECK_LESS_OR_EQUAL( std::make_tuple(0), std::make_tuple(0) );
  FRENSIE_CHECK_LESS_OR_EQUAL( std::make_tuple(0), std::make_tuple(1) );
  
  FRENSIE_CHECK_LESS_OR_EQUAL( std::make_tuple(0,1), std::make_tuple(0,1) );
  FRENSIE_CHECK_LESS_OR_EQUAL( std::make_tuple(0,1), std::make_tuple(1,2) );
  
  FRENSIE_CHECK_LESS_OR_EQUAL( std::make_pair(0,1), std::make_pair(0,1) );
  FRENSIE_CHECK_LESS_OR_EQUAL( std::make_pair(0,1), std::make_pair(1,2) );
}

//---------------------------------------------------------------------------//
// Check that the CHECK_LESS_OR_EQUAL macro behaves correctly
FRENSIE_UNIT_TEST( UnitTestHarness, CHECK_LESS_OR_EQUAL_fail )
{
  FRENSIE_CHECK_LESS_OR_EQUAL( 1, 0 );
  FRENSIE_CHECK_LESS_OR_EQUAL( 2u, 1u );
  FRENSIE_CHECK_LESS_OR_EQUAL( 2l, -2l );
  FRENSIE_CHECK_LESS_OR_EQUAL( 10ul, 3ul );
  FRENSIE_CHECK_LESS_OR_EQUAL( 4ll, -4ll );
  FRENSIE_CHECK_LESS_OR_EQUAL( 4ull, 3ull );
  FRENSIE_CHECK_LESS_OR_EQUAL( 2.0f, 1.0f );
  FRENSIE_CHECK_LESS_OR_EQUAL( 1.0, -1.0 );
  FRENSIE_CHECK_LESS_OR_EQUAL( std::string( "b" ), std::string( "a" ) );
  FRENSIE_CHECK_LESS_OR_EQUAL( std::make_tuple(1), std::make_tuple(0) );
  FRENSIE_CHECK_LESS_OR_EQUAL( std::make_tuple(1,2), std::make_tuple(0,1) );
  FRENSIE_CHECK_LESS_OR_EQUAL( std::make_pair(1,2), std::make_pair(0,1) );
}

//---------------------------------------------------------------------------//
// Check that the REQUIRE_LESS_OR_EQUAL macro behaves correctly
FRENSIE_UNIT_TEST( UnitTestHarness, REQUIRE_LESS_OR_EQUAL_pass )
{
  FRENSIE_REQUIRE_LESS_OR_EQUAL( 0, 0 );
  FRENSIE_REQUIRE_LESS_OR_EQUAL( 0, 1 );
  
  FRENSIE_REQUIRE_LESS_OR_EQUAL( 1u, 1u, SHOW_LHS );
  FRENSIE_REQUIRE_LESS_OR_EQUAL( 1u, 2u );

  FRENSIE_REQUIRE_LESS_OR_EQUAL( 2l, 2l, SHOW_RHS );
  FRENSIE_REQUIRE_LESS_OR_EQUAL( -2l, 2l );

  FRENSIE_REQUIRE_LESS_OR_EQUAL( 3ul, 3ul, SHOW_BOTH );
  FRENSIE_REQUIRE_LESS_OR_EQUAL( 3ul, 10ul );

  FRENSIE_REQUIRE_LESS_OR_EQUAL( 4ll, 4ll );
  FRENSIE_REQUIRE_LESS_OR_EQUAL( -4ll, 4ll );

  FRENSIE_REQUIRE_LESS_OR_EQUAL( 3ull, 3ull );
  FRENSIE_REQUIRE_LESS_OR_EQUAL( 3ull, 4ull );

  FRENSIE_REQUIRE_LESS_OR_EQUAL( 1.0f, 1.0f );
  FRENSIE_REQUIRE_LESS_OR_EQUAL( 1.0f, 2.0f );

  FRENSIE_REQUIRE_LESS_OR_EQUAL( 1.0, 1.0 );
  FRENSIE_REQUIRE_LESS_OR_EQUAL( -1.0, 1.0 );

  FRENSIE_REQUIRE_LESS_OR_EQUAL( std::string( "a" ), std::string( "a" ) );
  FRENSIE_REQUIRE_LESS_OR_EQUAL( std::string( "a" ), std::string( "b" ) );

  FRENSIE_REQUIRE_LESS_OR_EQUAL( std::make_tuple(0), std::make_tuple(0) );
  FRENSIE_REQUIRE_LESS_OR_EQUAL( std::make_tuple(0), std::make_tuple(1) );
  
  FRENSIE_REQUIRE_LESS_OR_EQUAL( std::make_tuple(0,1), std::make_tuple(0,1) );
  FRENSIE_REQUIRE_LESS_OR_EQUAL( std::make_tuple(0,1), std::make_tuple(1,2) );
  
  FRENSIE_REQUIRE_LESS_OR_EQUAL( std::make_pair(0,1), std::make_pair(0,1) );
  FRENSIE_REQUIRE_LESS_OR_EQUAL( std::make_pair(0,1), std::make_pair(1,2) );
}

//---------------------------------------------------------------------------//
// Check that the REQUIRE_LESS_OR_EQUAL macro behaves correctly
FRENSIE_UNIT_TEST( UnitTestHarness, REQUIRE_LESS_OR_EQUAL_fail )
{
  FRENSIE_REQUIRE_LESS_OR_EQUAL( 1, 0 );

  // We should never get here
  std::exit(EXIT_FAILURE);
}

//---------------------------------------------------------------------------//
// Check that the CHECK_CLOSE macro behaves correctly
FRENSIE_UNIT_TEST( UnitTestHarness, CHECK_CLOSE_pass )
{
  FRENSIE_CHECK_CLOSE( 1.0f, 1.0f, 1e-9f );
  FRENSIE_CHECK_CLOSE( 1.0f, (1.0f-1e-10f), 1e-9f );
  FRENSIE_CHECK_CLOSE( 1.0f, (1.0f+1e-10f), 1e-9f );
  
  FRENSIE_CHECK_CLOSE( -1.0, -1.0, 1e-15, SHOW_LHS );
  FRENSIE_CHECK_CLOSE( -1.0, -1.0-1e-16, 1e-15 );
  FRENSIE_CHECK_CLOSE( -1.0, -1.0+1e-16, 1e-15 );
  
  FRENSIE_CHECK_CLOSE( std::make_tuple(-1.), std::make_tuple(-1.), 1e-15, SHOW_RHS );
  FRENSIE_CHECK_CLOSE( std::make_tuple(-1.), std::make_tuple(-1.0-1e-16), 1e-15 );
  FRENSIE_CHECK_CLOSE( std::make_tuple(-1.), std::make_tuple(-1.0+1e-16), 1e-15 );

  FRENSIE_CHECK_CLOSE( std::make_pair(0, 1.0), std::make_pair(0, 1.0), 1e-15, SHOW_BOTH );
  FRENSIE_CHECK_CLOSE( std::make_pair(0, 1.0), std::make_pair(0, 1.0-1e-16), 1e-15 );
  FRENSIE_CHECK_CLOSE( std::make_pair(0, 1.0), std::make_pair(0, 1.0+1e-16), 1e-15 );
  
  FRENSIE_CHECK_CLOSE( std::list<double>({0., 1., 2.}), std::list<double>({0., 1., 2.}), 1e-15 );
  FRENSIE_CHECK_CLOSE( std::list<double>({0., 1.0+1e-16, 2.}), std::list<double>({0., 1., 2.-1e-16}), 1e-15 );
  
  FRENSIE_CHECK_CLOSE( std::forward_list<double>({0., 1., 2.}), std::forward_list<double>({0., 1., 2.}), 1e-15 );
  FRENSIE_CHECK_CLOSE( std::forward_list<double>({0., 1.0+1e-16, 2.}), std::forward_list<double>({0., 1.0, 2.0-1e-16}), 1e-15 );
  
  FRENSIE_CHECK_CLOSE( std::deque<double>({0., 1., 2.}), std::deque<double>({0., 1., 2.}), 1e-15 );
  FRENSIE_CHECK_CLOSE( std::deque<double>({0., 1.+1e-16, 2.}), std::deque<double>({0., 1., 2.-1e-16}), 1e-15 );
  
  FRENSIE_CHECK_CLOSE( (std::array<double,3>({0., 1., 2.})), (std::array<double,3>({0., 1., 2.})), 1e-15 );
  FRENSIE_CHECK_CLOSE( (std::array<double,3>({0., 1.+1e-16, 2.})), (std::array<double,3>({0., 1., 2.-1e-16})), 1e-15 );
  
  FRENSIE_CHECK_CLOSE( std::vector<double>({0., 1., 2.}), std::vector<double>({0., 1., 2.}), 1e-15 );
  FRENSIE_CHECK_CLOSE( std::vector<double>({0., 1.+1e-16, 2.}), std::vector<double>({0., 1., 2.-1e-16}), 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that the CHECK_CLOSE macro behaves correctly
FRENSIE_UNIT_TEST( UnitTestHarness, CHECK_CLOSE_fail )
{
  FRENSIE_CHECK_CLOSE( 1.0f, (1.0f-1e-8f), 1e-9f );
  FRENSIE_CHECK_CLOSE( 1.0f, (1.0f+1e-8f), 1e-9f );
  
  FRENSIE_CHECK_CLOSE( -1.0, -1.0, 1e-15 );
  FRENSIE_CHECK_CLOSE( -1.0, -1.0-1e-14, 1e-15 );
  FRENSIE_CHECK_CLOSE( -1.0, -1.0+1e-14, 1e-15 );
  
  FRENSIE_CHECK_CLOSE( std::make_tuple(-1.), std::make_tuple(-1.), 1e-15 );
  FRENSIE_CHECK_CLOSE( std::make_tuple(-1.), std::make_tuple(-1.0-1e-14), 1e-15 );
  FRENSIE_CHECK_CLOSE( std::make_tuple(-1.), std::make_tuple(-1.0+1e-14), 1e-15 );

  FRENSIE_CHECK_CLOSE( std::make_pair(0, 1.0), std::make_pair(0, 1.0), 1e-15 );
  FRENSIE_CHECK_CLOSE( std::make_pair(0, 1.0), std::make_pair(0, 1.0-1e-14), 1e-15 );
  FRENSIE_CHECK_CLOSE( std::make_pair(0, 1.0), std::make_pair(0, 1.0+1e-14), 1e-15 );
  
  FRENSIE_CHECK_CLOSE( std::list<double>({0., 1., 2.}), std::list<double>({0., 1., 2.}), 1e-15 );
  FRENSIE_CHECK_CLOSE( std::list<double>({0., 1.0+1e-14, 2.}), std::list<double>({0., 1., 2.-1e-14}), 1e-15 );
  
  FRENSIE_CHECK_CLOSE( std::forward_list<double>({0., 1., 2.}), std::forward_list<double>({0., 1., 2.}), 1e-15 );
  FRENSIE_CHECK_CLOSE( std::forward_list<double>({0., 1.0+1e-14, 2.}), std::forward_list<double>({0., 1.0, 2.0-1e-14}), 1e-15 );
  
  FRENSIE_CHECK_CLOSE( std::deque<double>({0., 1., 2.}), std::deque<double>({0., 1., 2.}), 1e-15 );
  FRENSIE_CHECK_CLOSE( std::deque<double>({0., 1.+1e-14, 2.}), std::deque<double>({0., 1., 2.-1e-14}), 1e-15 );
  
  FRENSIE_CHECK_CLOSE( (std::array<double,3>({0., 1., 2.})), (std::array<double,3>({0., 1., 2.})), 1e-15 );
  FRENSIE_CHECK_CLOSE( (std::array<double,3>({0., 1.+1e-14, 2.})), (std::array<double,3>({0., 1., 2.-1e-14})), 1e-15 );
  
  FRENSIE_CHECK_CLOSE( std::vector<double>({0., 1., 2.}), std::vector<double>({0., 1., 2.}), 1e-15 );
  FRENSIE_CHECK_CLOSE( std::vector<double>({0., 1.+1e-14, 2.}), std::vector<double>({0., 1., 2.-1e-14}), 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that the REQUIRE_CLOSE macro behaves correctly
FRENSIE_UNIT_TEST( UnitTestHarness, REQUIRE_CLOSE_pass )
{
  FRENSIE_REQUIRE_CLOSE( 1.0f, 1.0f, 1e-9f );
  FRENSIE_REQUIRE_CLOSE( 1.0f, (1.0f-1e-10f), 1e-9f );
  FRENSIE_REQUIRE_CLOSE( 1.0f, (1.0f+1e-10f), 1e-9f );
  
  FRENSIE_REQUIRE_CLOSE( -1.0, -1.0, 1e-15, SHOW_LHS );
  FRENSIE_REQUIRE_CLOSE( -1.0, -1.0-1e-16, 1e-15 );
  FRENSIE_REQUIRE_CLOSE( -1.0, -1.0+1e-16, 1e-15 );
  
  FRENSIE_REQUIRE_CLOSE( std::make_tuple(-1.), std::make_tuple(-1.), 1e-15, SHOW_RHS );
  FRENSIE_REQUIRE_CLOSE( std::make_tuple(-1.), std::make_tuple(-1.0-1e-16), 1e-15 );
  FRENSIE_REQUIRE_CLOSE( std::make_tuple(-1.), std::make_tuple(-1.0+1e-16), 1e-15 );

  FRENSIE_REQUIRE_CLOSE( std::make_pair(0, 1.0), std::make_pair(0, 1.0), 1e-15, SHOW_BOTH );
  FRENSIE_REQUIRE_CLOSE( std::make_pair(0, 1.0), std::make_pair(0, 1.0-1e-16), 1e-15 );
  FRENSIE_REQUIRE_CLOSE( std::make_pair(0, 1.0), std::make_pair(0, 1.0+1e-16), 1e-15 );
  
  FRENSIE_REQUIRE_CLOSE( std::list<double>({0., 1., 2.}), std::list<double>({0., 1., 2.}), 1e-15 );
  FRENSIE_REQUIRE_CLOSE( std::list<double>({0., 1.0+1e-16, 2.}), std::list<double>({0., 1., 2.-1e-16}), 1e-15 );
  
  FRENSIE_REQUIRE_CLOSE( std::forward_list<double>({0., 1., 2.}), std::forward_list<double>({0., 1., 2.}), 1e-15 );
  FRENSIE_REQUIRE_CLOSE( std::forward_list<double>({0., 1.0+1e-16, 2.}), std::forward_list<double>({0., 1.0, 2.0-1e-16}), 1e-15 );
  
  FRENSIE_REQUIRE_CLOSE( std::deque<double>({0., 1., 2.}), std::deque<double>({0., 1., 2.}), 1e-15 );
  FRENSIE_REQUIRE_CLOSE( std::deque<double>({0., 1.+1e-16, 2.}), std::deque<double>({0., 1., 2.-1e-16}), 1e-15 );
  
  FRENSIE_REQUIRE_CLOSE( (std::array<double,3>({0., 1., 2.})), (std::array<double,3>({0., 1., 2.})), 1e-15 );
  FRENSIE_REQUIRE_CLOSE( (std::array<double,3>({0., 1.+1e-16, 2.})), (std::array<double,3>({0., 1., 2.-1e-16})), 1e-15 );
  
  FRENSIE_REQUIRE_CLOSE( std::vector<double>({0., 1., 2.}), std::vector<double>({0., 1., 2.}), 1e-15 );
  FRENSIE_REQUIRE_CLOSE( std::vector<double>({0., 1.+1e-16, 2.}), std::vector<double>({0., 1., 2.-1e-16}), 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that the REQUIRE_CLOSE macro behaves correctly
FRENSIE_UNIT_TEST( UnitTestHarness, REQUIRE_CLOSE_fail )
{
  FRENSIE_REQUIRE_CLOSE( 1.0f, 1.1f, 1e-8f );

  // We should never get here
  std::exit(EXIT_FAILURE);
}

//---------------------------------------------------------------------------//
// Check that the CHECK_SMALL macro behaves correctly
FRENSIE_UNIT_TEST( UnitTestHarness, CHECK_SMALL_pass )
{
  FRENSIE_CHECK_SMALL( 0.0f, 1e-9f );
  FRENSIE_CHECK_SMALL( 1e-9, 1e-8f );
  FRENSIE_CHECK_SMALL( -1e-9, 1e-8f );
  
  FRENSIE_CHECK_SMALL( 0.0, 1e-15 );
  FRENSIE_CHECK_SMALL( 1e-15, 1e-14 );
  FRENSIE_CHECK_SMALL( -1e-15, 1e-14 );
  
  FRENSIE_CHECK_SMALL( std::make_tuple(0.0), 1e-15 );
  FRENSIE_CHECK_SMALL( std::make_tuple(1e-15), 1e-14 );
  FRENSIE_CHECK_SMALL( std::make_tuple(-1e-15), 1e-14 );

  FRENSIE_CHECK_SMALL( std::make_pair(0, 0.0), 1e-15 );
  FRENSIE_CHECK_SMALL( std::make_pair(0, 1e-15), 1e-14 );
  FRENSIE_CHECK_SMALL( std::make_pair(0, -1e-15), 1e-14 );
  
  FRENSIE_CHECK_SMALL( std::list<double>({0., 0., 0.}), 1e-15 );
  FRENSIE_CHECK_SMALL( std::list<double>({0., 1e-15, -1e-15}), 1e-14 );

  FRENSIE_CHECK_SMALL( std::forward_list<double>({0., 0., 0.}), 1e-15 );
  FRENSIE_CHECK_SMALL( std::forward_list<double>({0., 1e-15, -1e-15}), 1e-14 );

  FRENSIE_CHECK_SMALL( std::deque<double>({0., 0., 0.}), 1e-15 );
  FRENSIE_CHECK_SMALL( std::deque<double>({0., 1e-15, -1e-15}), 1e-14 );
      
  FRENSIE_CHECK_SMALL( (std::array<double,3>({0., 0., 0.})), 1e-15 );
  FRENSIE_CHECK_SMALL( (std::array<double,3>({0., 1e-15, -1e-15})), 1e-14 );
  
  FRENSIE_CHECK_SMALL( std::vector<double>({0., 0., 0.}), 1e-15 );
  FRENSIE_CHECK_SMALL( std::vector<double>({0., 1e-15, -1e-15}), 1e-14 );
}

//---------------------------------------------------------------------------//
// Check that the CHECK_SMALL macro behaves correctly
FRENSIE_UNIT_TEST( UnitTestHarness, CHECK_SMALL_fail )
{
  FRENSIE_CHECK_SMALL( 1e-8, 1e-9f );
  FRENSIE_CHECK_SMALL( -1e-8, 1e-9f );
  
  FRENSIE_CHECK_SMALL( 1e-14, 1e-15 );
  FRENSIE_CHECK_SMALL( -1e-14, 1e-15 );
  
  FRENSIE_CHECK_SMALL( std::make_tuple(1e-14), 1e-15 );
  FRENSIE_CHECK_SMALL( std::make_tuple(-1e-14), 1e-15 );

  FRENSIE_CHECK_SMALL( std::make_pair(0, 1e-14), 1e-15 );
  FRENSIE_CHECK_SMALL( std::make_pair(0, -1e-14), 1e-15 );
  
  FRENSIE_CHECK_SMALL( std::list<double>({0., 1e-14, -1e-14}), 1e-15 );
  FRENSIE_CHECK_SMALL( std::forward_list<double>({0., 1e-14, -1e-14}), 1e-15 );
  FRENSIE_CHECK_SMALL( std::deque<double>({0., 1e-14, -1e-14}), 1e-15 );
  FRENSIE_CHECK_SMALL( (std::array<double,3>({0., 1e-14, -1e-14})), 1e-15 );
  FRENSIE_CHECK_SMALL( std::vector<double>({0., 1e-14, -1e-14}), 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that the REQUIRE_SMALL macro behaves correctly
FRENSIE_UNIT_TEST( UnitTestHarness, REQUIRE_SMALL_pass )
{
  FRENSIE_REQUIRE_SMALL( 0.0f, 1e-9f );
  FRENSIE_REQUIRE_SMALL( 1e-9, 1e-8f );
  FRENSIE_REQUIRE_SMALL( -1e-9, 1e-8f );
  
  FRENSIE_REQUIRE_SMALL( 0.0, 1e-15 );
  FRENSIE_REQUIRE_SMALL( 1e-15, 1e-14 );
  FRENSIE_REQUIRE_SMALL( -1e-15, 1e-14 );
  
  FRENSIE_REQUIRE_SMALL( std::make_tuple(0.0), 1e-15 );
  FRENSIE_REQUIRE_SMALL( std::make_tuple(1e-15), 1e-14 );
  FRENSIE_REQUIRE_SMALL( std::make_tuple(-1e-15), 1e-14 );

  FRENSIE_REQUIRE_SMALL( std::make_pair(0, 0.0), 1e-15 );
  FRENSIE_REQUIRE_SMALL( std::make_pair(0, 1e-15), 1e-14 );
  FRENSIE_REQUIRE_SMALL( std::make_pair(0, -1e-15), 1e-14 );
  
  FRENSIE_REQUIRE_SMALL( std::list<double>({0., 0., 0.}), 1e-15 );
  FRENSIE_REQUIRE_SMALL( std::list<double>({0., 1e-15, -1e-15}), 1e-14 );

  FRENSIE_REQUIRE_SMALL( std::forward_list<double>({0., 0., 0.}), 1e-15 );
  FRENSIE_REQUIRE_SMALL( std::forward_list<double>({0., 1e-15, -1e-15}), 1e-14 );

  FRENSIE_REQUIRE_SMALL( std::deque<double>({0., 0., 0.}), 1e-15 );
  FRENSIE_REQUIRE_SMALL( std::deque<double>({0., 1e-15, -1e-15}), 1e-14 );
      
  FRENSIE_REQUIRE_SMALL( (std::array<double,3>({0., 0., 0.})), 1e-15 );
  FRENSIE_REQUIRE_SMALL( (std::array<double,3>({0., 1e-15, -1e-15})), 1e-14 );
  
  FRENSIE_REQUIRE_SMALL( std::vector<double>({0., 0., 0.}), 1e-15 );
  FRENSIE_REQUIRE_SMALL( std::vector<double>({0., 1e-15, -1e-15}), 1e-14 );
}

//---------------------------------------------------------------------------//
// Check that the REQUIRE_SMALL macro behaves correctly
FRENSIE_UNIT_TEST( UnitTestHarness, REQUIRE_SMALL_fail )
{
  FRENSIE_REQUIRE_SMALL( 1e-7, 1e-8f );

  // We should never get here
  std::exit(EXIT_FAILURE);
}

//---------------------------------------------------------------------------//
// Check that the CHECK_FLOATING_EQUALITY macro behaves correctly
FRENSIE_UNIT_TEST( UnitTestHarness, CHECK_FLOATING_EQUALITY_pass )
{
  FRENSIE_CHECK_FLOATING_EQUALITY( 1.0f, 1.0f, 1e-9f );
  FRENSIE_CHECK_FLOATING_EQUALITY( 1.0f, (1.0f-1e-10f), 1e-9f );
  FRENSIE_CHECK_FLOATING_EQUALITY( 1.0f, (1.0f+1e-10f), 1e-9f );
  
  FRENSIE_CHECK_FLOATING_EQUALITY( -1.0, -1.0, 1e-15, SHOW_LHS );
  FRENSIE_CHECK_FLOATING_EQUALITY( -1.0, -1.0-1e-16, 1e-15, SHOW_RHS );
  FRENSIE_CHECK_FLOATING_EQUALITY( -1.0, -1.0+1e-16, 1e-15, SHOW_BOTH );
  
  FRENSIE_CHECK_FLOATING_EQUALITY( std::make_tuple(-1.), std::make_tuple(-1.), 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( std::make_tuple(-1.), std::make_tuple(-1.0-1e-16), 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( std::make_tuple(-1.), std::make_tuple(-1.0+1e-16), 1e-15 );

  FRENSIE_CHECK_FLOATING_EQUALITY( std::make_pair(0, 1.0), std::make_pair(0, 1.0), 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( std::make_pair(0, 1.0), std::make_pair(0, 1.0-1e-16), 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( std::make_pair(0, 1.0), std::make_pair(0, 1.0+1e-16), 1e-15 );
  
  FRENSIE_CHECK_FLOATING_EQUALITY( std::list<double>({0., 1., 2.}), std::list<double>({0., 1., 2.}), 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( std::list<double>({0., 1.0+1e-16, 2.}), std::list<double>({0., 1., 2.-1e-16}), 1e-15 );
  
  FRENSIE_CHECK_FLOATING_EQUALITY( std::forward_list<double>({0., 1., 2.}), std::forward_list<double>({0., 1., 2.}), 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( std::forward_list<double>({0., 1.0+1e-16, 2.}), std::forward_list<double>({0., 1.0, 2.0-1e-16}), 1e-15 );
  
  FRENSIE_CHECK_FLOATING_EQUALITY( std::deque<double>({0., 1., 2.}), std::deque<double>({0., 1., 2.}), 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( std::deque<double>({0., 1.+1e-16, 2.}), std::deque<double>({0., 1., 2.-1e-16}), 1e-15 );
  
  FRENSIE_CHECK_FLOATING_EQUALITY( (std::array<double,3>({0., 1., 2.})), (std::array<double,3>({0., 1., 2.})), 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( (std::array<double,3>({0., 1.+1e-16, 2.})), (std::array<double,3>({0., 1., 2.-1e-16})), 1e-15 );
  
  FRENSIE_CHECK_FLOATING_EQUALITY( std::vector<double>({0., 1., 2.}), std::vector<double>({0., 1., 2.}), 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( std::vector<double>({0., 1.+1e-16, 2.}), std::vector<double>({0., 1., 2.-1e-16}), 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that the CHECK_FLOATING_EQUALITY macro behaves correctly
FRENSIE_UNIT_TEST( UnitTestHarness, CHECK_FLOATING_EQUALITY_fail )
{
  FRENSIE_CHECK_FLOATING_EQUALITY( 1.0f, (1.0f-1e-8f), 1e-9f );
  FRENSIE_CHECK_FLOATING_EQUALITY( 1.0f, (1.0f+1e-8f), 1e-9f );
  
  FRENSIE_CHECK_FLOATING_EQUALITY( -1.0, -1.0, 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( -1.0, -1.0-1e-14, 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( -1.0, -1.0+1e-14, 1e-15 );
  
  FRENSIE_CHECK_FLOATING_EQUALITY( std::make_tuple(-1.), std::make_tuple(-1.), 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( std::make_tuple(-1.), std::make_tuple(-1.0-1e-14), 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( std::make_tuple(-1.), std::make_tuple(-1.0+1e-14), 1e-15 );

  FRENSIE_CHECK_FLOATING_EQUALITY( std::make_pair(0, 1.0), std::make_pair(0, 1.0), 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( std::make_pair(0, 1.0), std::make_pair(0, 1.0-1e-14), 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( std::make_pair(0, 1.0), std::make_pair(0, 1.0+1e-14), 1e-15 );
  
  FRENSIE_CHECK_FLOATING_EQUALITY( std::list<double>({0., 1., 2.}), std::list<double>({0., 1., 2.}), 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( std::list<double>({0., 1.0+1e-14, 2.}), std::list<double>({0., 1., 2.-1e-14}), 1e-15 );
  
  FRENSIE_CHECK_FLOATING_EQUALITY( std::forward_list<double>({0., 1., 2.}), std::forward_list<double>({0., 1., 2.}), 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( std::forward_list<double>({0., 1.0+1e-14, 2.}), std::forward_list<double>({0., 1.0, 2.0-1e-14}), 1e-15 );
  
  FRENSIE_CHECK_FLOATING_EQUALITY( std::deque<double>({0., 1., 2.}), std::deque<double>({0., 1., 2.}), 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( std::deque<double>({0., 1.+1e-14, 2.}), std::deque<double>({0., 1., 2.-1e-14}), 1e-15 );
  
  FRENSIE_CHECK_FLOATING_EQUALITY( (std::array<double,3>({0., 1., 2.})), (std::array<double,3>({0., 1., 2.})), 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( (std::array<double,3>({0., 1.+1e-14, 2.})), (std::array<double,3>({0., 1., 2.-1e-14})), 1e-15 );
  
  FRENSIE_CHECK_FLOATING_EQUALITY( std::vector<double>({0., 1., 2.}), std::vector<double>({0., 1., 2.}), 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( std::vector<double>({0., 1.+1e-14, 2.}), std::vector<double>({0., 1., 2.-1e-14}), 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that the REQUIRE_FLOATING_EQUALITY macro behaves correctly
FRENSIE_UNIT_TEST( UnitTestHarness, REQUIRE_FLOATING_EQUALITY_pass )
{
  FRENSIE_REQUIRE_FLOATING_EQUALITY( 1.0f, 1.0f, 1e-9f );
  FRENSIE_REQUIRE_FLOATING_EQUALITY( 1.0f, (1.0f-1e-10f), 1e-9f );
  FRENSIE_REQUIRE_FLOATING_EQUALITY( 1.0f, (1.0f+1e-10f), 1e-9f );
  
  FRENSIE_REQUIRE_FLOATING_EQUALITY( -1.0, -1.0, 1e-15, SHOW_LHS );
  FRENSIE_REQUIRE_FLOATING_EQUALITY( -1.0, -1.0-1e-16, 1e-15, SHOW_RHS );
  FRENSIE_REQUIRE_FLOATING_EQUALITY( -1.0, -1.0+1e-16, 1e-15, SHOW_BOTH );
  
  FRENSIE_REQUIRE_FLOATING_EQUALITY( std::make_tuple(-1.), std::make_tuple(-1.), 1e-15 );
  FRENSIE_REQUIRE_FLOATING_EQUALITY( std::make_tuple(-1.), std::make_tuple(-1.0-1e-16), 1e-15 );
  FRENSIE_REQUIRE_FLOATING_EQUALITY( std::make_tuple(-1.), std::make_tuple(-1.0+1e-16), 1e-15 );

  FRENSIE_REQUIRE_FLOATING_EQUALITY( std::make_pair(0, 1.0), std::make_pair(0, 1.0), 1e-15 );
  FRENSIE_REQUIRE_FLOATING_EQUALITY( std::make_pair(0, 1.0), std::make_pair(0, 1.0-1e-16), 1e-15 );
  FRENSIE_REQUIRE_FLOATING_EQUALITY( std::make_pair(0, 1.0), std::make_pair(0, 1.0+1e-16), 1e-15 );
  
  FRENSIE_REQUIRE_FLOATING_EQUALITY( std::list<double>({0., 1., 2.}), std::list<double>({0., 1., 2.}), 1e-15 );
  FRENSIE_REQUIRE_FLOATING_EQUALITY( std::list<double>({0., 1.0+1e-16, 2.}), std::list<double>({0., 1., 2.-1e-16}), 1e-15 );
  
  FRENSIE_REQUIRE_FLOATING_EQUALITY( std::forward_list<double>({0., 1., 2.}), std::forward_list<double>({0., 1., 2.}), 1e-15 );
  FRENSIE_REQUIRE_FLOATING_EQUALITY( std::forward_list<double>({0., 1.0+1e-16, 2.}), std::forward_list<double>({0., 1.0, 2.0-1e-16}), 1e-15 );
  
  FRENSIE_REQUIRE_FLOATING_EQUALITY( std::deque<double>({0., 1., 2.}), std::deque<double>({0., 1., 2.}), 1e-15 );
  FRENSIE_REQUIRE_FLOATING_EQUALITY( std::deque<double>({0., 1.+1e-16, 2.}), std::deque<double>({0., 1., 2.-1e-16}), 1e-15 );
  
  FRENSIE_REQUIRE_FLOATING_EQUALITY( (std::array<double,3>({0., 1., 2.})), (std::array<double,3>({0., 1., 2.})), 1e-15 );
  FRENSIE_REQUIRE_FLOATING_EQUALITY( (std::array<double,3>({0., 1.+1e-16, 2.})), (std::array<double,3>({0., 1., 2.-1e-16})), 1e-15 );
  
  FRENSIE_REQUIRE_FLOATING_EQUALITY( std::vector<double>({0., 1., 2.}), std::vector<double>({0., 1., 2.}), 1e-15 );
  FRENSIE_REQUIRE_FLOATING_EQUALITY( std::vector<double>({0., 1.+1e-16, 2.}), std::vector<double>({0., 1., 2.-1e-16}), 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that the REQUIRE_FLOATING_EQUALITY macro behaves correctly
FRENSIE_UNIT_TEST( UnitTestHarness, REQUIRE_FLOATING_EQUALITY_fail )
{
  FRENSIE_REQUIRE_FLOATING_EQUALITY( 1.0f, (1.0f-1e-6f), 1e-8f );

  // We should never get here
  std::exit(EXIT_FAILURE);
}

//---------------------------------------------------------------------------//
// Check that the CHECK_NO_THROW macro behaves correctly
FRENSIE_UNIT_TEST( UnitTestHarness, CHECK_NO_THROW_pass )
{
  FRENSIE_CHECK_NO_THROW( double dummy = 0.0 );
}

//---------------------------------------------------------------------------//
// Check that the CHECK_NO_THROW macro behaves correctly
FRENSIE_UNIT_TEST( UnitTestHarness, CHECK_NO_THROW_fail )
{
  FRENSIE_CHECK_NO_THROW( throw std::runtime_error("fail") );
  FRENSIE_CHECK_NO_THROW( throw 1 );
  FRENSIE_CHECK_NO_THROW( throw std::string("fail") );
}

//---------------------------------------------------------------------------//
// Check that the REQUIRE_NO_THROW macro behaves correctly
FRENSIE_UNIT_TEST( UnitTestHarness, REQUIRE_NO_THROW_pass )
{
  FRENSIE_REQUIRE_NO_THROW( double dummy = 0.0 );
}

//---------------------------------------------------------------------------//
// Check that the REQUIRE_NO_THROW macro behaves correctly
FRENSIE_UNIT_TEST( UnitTestHarness, REQUIRE_NO_THROW_fail )
{
  FRENSIE_REQUIRE_NO_THROW( throw std::runtime_error("fail") );

  // We should never get here
  std::exit(EXIT_FAILURE);
}

//---------------------------------------------------------------------------//
// Check that the CHECK_THROW macro behaves correctly
FRENSIE_UNIT_TEST( UnitTestHarness, CHECK_THROW_pass )
{
  FRENSIE_CHECK_THROW( throw std::runtime_error("fail"), std::runtime_error );
  FRENSIE_CHECK_THROW( throw std::logic_error("fail"), std::logic_error );
  FRENSIE_CHECK_THROW( throw 1, int );
}

//---------------------------------------------------------------------------//
// Check that the CHECK_THROW macro behaves correctly
FRENSIE_UNIT_TEST( UnitTestHarness, CHECK_THROW_fail )
{
  FRENSIE_CHECK_THROW( throw std::runtime_error("fail"), std::logic_error );
  FRENSIE_CHECK_THROW( throw std::logic_error("fail"), std::runtime_error );
  FRENSIE_CHECK_THROW( throw 1, std::runtime_error );
  
  FRENSIE_CHECK_THROW( double dummy = 0.0, std::runtime_error );
}

//---------------------------------------------------------------------------//
// Check that the REQUIRE_THROW macro behaves correctly
FRENSIE_UNIT_TEST( UnitTestHarness, REQUIRE_THROW_pass )
{
  FRENSIE_REQUIRE_THROW( throw std::runtime_error("fail"), std::runtime_error );
  FRENSIE_REQUIRE_THROW( throw std::logic_error("fail"), std::logic_error );
  FRENSIE_REQUIRE_THROW( throw 1, int );
}

//---------------------------------------------------------------------------//
// Check that the REQUIRE_THROW macro behaves correctly
FRENSIE_UNIT_TEST( UnitTestHarness, REQUIRE_THROW_fail )
{
  FRENSIE_REQUIRE_THROW( throw std::runtime_error("fail"), std::logic_error );

  // We should never get here
  std::exit(EXIT_FAILURE);
}

//---------------------------------------------------------------------------//
// Check that a seg. fault will be caught and reported by the unit test manager
FRENSIE_UNIT_TEST( UnitTestHarness, SegFault_fail )
{
  int* invalid_pointer = NULL;

  FRENSIE_CHECKPOINT();
  
  // This should cause a seg fault, which will then be handled by our
  // custom signal handler
  *invalid_pointer = 1;
}

//---------------------------------------------------------------------------//
// Check that an abort signal will be caught and reported by the unit test
// manager
FRENSIE_UNIT_TEST( UnitTestHarness, Abort_fail )
{
  std::raise( SIGABRT );
}

//---------------------------------------------------------------------------//
// Check that a data unit test can be constructed
FRENSIE_DATA_UNIT_TEST_DECL( UnitTestHarness, DataDrivenTest_pass )
{
  FETCH_FROM_TABLE( double, Input );
  FETCH_FROM_TABLE( double, abs_Input );
  FETCH_FROM_TABLE( double, Tolerance );

  FRENSIE_CHECK_FLOATING_EQUALITY( fabs(Input), abs_Input, Tolerance );
}

FRENSIE_DATA_UNIT_TEST_INST( UnitTestHarness, DataDrivenTest_pass )
{
  COLUMNS()               << "Input" << "abs_Input" << "Tolerance";
  NEW_ROW( "neg_input" )  << -1.0    << 1.0         << 1e-15;
  NEW_ROW( "zero_input" ) <<  0.0    << 0.0         << 0.0;
  NEW_ROW( "pos_input" )  <<  1.0    << 1.0         << 1e-15;
}

//---------------------------------------------------------------------------//
// Check that a data unit test can be constructed
FRENSIE_DATA_UNIT_TEST_INST( UnitTestHarness, DataDrivenTest_fail )
{
  COLUMNS()                << "RawString"   << "StringChunk" << "ChunkStart" << "ChunkSize";
  NEW_ROW( "all_words" )   << "Hello World" << "Say What?"   << 0            << 11;
  NEW_ROW( "first_word" )  << "Hello World" << "Hi"          << 0            << 5;
  NEW_ROW( "second_word" ) << "Hello World" << "Universe"    << 6            << 5;
  NEW_ROW( "nothing" )     << "Hello World" << "Oops"        << 0            << 0;
}

FRENSIE_DATA_UNIT_TEST_DECL( UnitTestHarness, DataDrivenTest_fail )
{
  FETCH_FROM_TABLE( std::string, RawString );
  FETCH_FROM_TABLE( std::string, StringChunk );
  FETCH_FROM_TABLE( size_t, ChunkStart );
  FETCH_FROM_TABLE( size_t, ChunkSize );

  std::string test_chunk = RawString.substr( ChunkStart, ChunkSize );

  FRENSIE_CHECK_EQUAL( test_chunk, StringChunk );
}

//---------------------------------------------------------------------------//
// Check that a data unit test can be constructed
FRENSIE_DATA_TABLE( FloatingPointCompTestTable )
{
  COLUMNS()               << "Input" << "abs_Input" << "Tolerance";
  NEW_ROW( "neg_input" )  << -1.0    << 1.0         << 1e-15;
  NEW_ROW( "zero_input" ) <<  0.0    << 0.0         << 0.0;
  NEW_ROW( "pos_input" )  <<  1.0    << 1.0         << 1e-15;
}

FRENSIE_DATA_UNIT_TEST( UnitTestHarness,
                        InlineDataDrivenTest_double_pass,
                        FloatingPointCompTestTable )
{
  FETCH_FROM_TABLE( double, Input );
  FETCH_FROM_TABLE( double, abs_Input );
  FETCH_FROM_TABLE( double, Tolerance );

  FRENSIE_CHECK_FLOATING_EQUALITY( fabs(Input), abs_Input, Tolerance );
}

FRENSIE_DATA_UNIT_TEST( UnitTestHarness,
                        InlineDataDrivenTest_float_pass,
                        FloatingPointCompTestTable )
{
  FETCH_FROM_TABLE( float, Input );
  FETCH_FROM_TABLE( float, abs_Input );
  FETCH_FROM_TABLE( float, Tolerance );

  FRENSIE_CHECK_FLOATING_EQUALITY( fabs(Input), abs_Input, Tolerance );
}

//---------------------------------------------------------------------------//
// Check that a data unit test can be constructed
FRENSIE_DATA_TABLE( StringChunkTestTable )
{
  COLUMNS()                << "RawString"   << "StringChunk" << "ChunkStart" << "ChunkSize";
  NEW_ROW( "all_words" )   << "Hello World" << "Say What?"   << 0            << 11;
  NEW_ROW( "first_word" )  << "Hello World" << "Hi"          << 0            << 5;
  NEW_ROW( "second_word" ) << "Hello World" << "Universe"    << 6            << 5;
  NEW_ROW( "nothing" )     << "Hello World" << "Oops"        << 0            << 0;
}

FRENSIE_DATA_UNIT_TEST( UnitTestHarness,
                        InlineDataDrivenTest_string_fail,
                        StringChunkTestTable )
{
  FETCH_FROM_TABLE( std::string, RawString );
  FETCH_FROM_TABLE( std::string, StringChunk );
  FETCH_FROM_TABLE( size_t, ChunkStart );
  FETCH_FROM_TABLE( size_t, ChunkSize );

  std::string test_chunk = RawString.substr( ChunkStart, ChunkSize );

  FRENSIE_CHECK_EQUAL( test_chunk, StringChunk );
}

FRENSIE_DATA_UNIT_TEST( UnitTestHarness,
                        InlineDataDrivenTest_string_pass,
                        StringChunkTestTable )
{
  FETCH_FROM_TABLE( std::string, RawString );
  FETCH_FROM_TABLE( std::string, StringChunk );
  FETCH_FROM_TABLE( size_t, ChunkStart );
  FETCH_FROM_TABLE( size_t, ChunkSize );

  std::string test_chunk = RawString.substr( ChunkStart, ChunkSize );

  FRENSIE_CHECK_DIFFERENT( test_chunk, StringChunk );
}

//---------------------------------------------------------------------------//
// Check that a template unit test can be constructed
// Note: bool and double have been added multiple times on purpose - the
//       harness should filter out multiple type instances to ensure that each
//       test is unique.
FRENSIE_UNIT_TEST_TEMPLATE( UnitTestHarness, TemplateTestRawParamPack_pass,
                            bool, bool, short, int, long, long long, bool, float, double, double )
{
  FETCH_TEMPLATE_PARAM( 0, T );

  T value(0);

  FRENSIE_CHECK_EQUAL( value, T(0) );
}

//---------------------------------------------------------------------------//
// Check that a template unit test can be constructed
// Note: bool and double have been added multiple times on purpose - the
//       harness should filter out multiple type instances to ensure that each
//       test is unique.
FRENSIE_UNIT_TEST_TEMPLATE( UnitTestHarness, TemplateTestWrappedParamPack_pass,
                            std::tuple<bool, bool, short, int, long, long long, bool, float, double, double> )
{
  FETCH_TEMPLATE_PARAM( 0, T );

  T value(0);

  FRENSIE_CHECK_EQUAL( value, T(0) );
}

//---------------------------------------------------------------------------//
// Check that a template unit test can be constructed
// Note: Every tuple type has been added multiple times on purpose - the
//       harness should filter out multiple type instances to ensure that each
//       test is unique
FRENSIE_UNIT_TEST_TEMPLATE( UnitTestHarness, TemplateTestTupleTypes_pass,
                            std::tuple<>, std::tuple<>,
                            std::tuple<int,int>, std::tuple<int,int>,
                            std::tuple<int,int,int>, std::tuple<int,int,int>,
                            std::tuple<int,int,int,int>, std::tuple<int,int,int,int> )
{
  FETCH_TEMPLATE_PARAM( 0, Tuple );

  Tuple value;

  FRENSIE_CHECK_EQUAL( value, value );
}

//---------------------------------------------------------------------------//
// Check that a template unit test can be constructed
// Note: Every tuple type has been added multiple times on purpose - the
//       harness should filter out multiple type instances to ensure that each
//       test is unique
FRENSIE_UNIT_TEST_TEMPLATE_EXPAND( UnitTestHarness, TemplateTestRawExpandedTupleTypes_pass,
                                   std::tuple<int,int>, std::tuple<int,int>,
                                   std::tuple<int,double>, std::tuple<int,double>,
                                   std::tuple<double,double>, std::tuple<double,double>,
                                   std::tuple<double,int>, std::tuple<double,int> )
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
// Note: Every tuple type has been added multiple times on purpose - the
//       harness should filter out multiple type instances to ensure that each
//       test is unique
FRENSIE_UNIT_TEST_TEMPLATE_EXPAND( UnitTestHarness, TemplateTestWrappedExpandedTupleTypes_pass,
                                   std::tuple<
                                     std::tuple<int,int>, std::tuple<int,int>,
                                     std::tuple<int,double>, std::tuple<int,double>,
                                     std::tuple<double,double>, std::tuple<double,double>,
                                     std::tuple<double,int>, std::tuple<double,int>
                                   > )
{
  FETCH_TEMPLATE_PARAM( 0, T0 );
  FETCH_TEMPLATE_PARAM( 1, T1 );

  T0 value_0(0);
  T1 value_1(1);

  FRENSIE_CHECK_EQUAL( value_0, T0(0) );
  FRENSIE_CHECK_EQUAL( value_1, T1(1) );
}

//---------------------------------------------------------------------------//
// Custom setup
//---------------------------------------------------------------------------//
// A custom signal handler for seg faults
void SignalHandler( int signal )      
{
  if( signal == SIGSEGV )
    throw std::logic_error( "Seg Fault Detected!" );
  else
    throw signal;
}

// A custom main function for running the mock unit tests
int main( int argc, char** argv )                  
{
  Utility::GlobalMPISession mpi_session;
  
  signal( SIGSEGV, &SignalHandler );
  signal( SIGABRT, &SignalHandler );
  
  Utility::UnitTestManager& unit_test_manager =
    Utility::UnitTestManager::getInstance();

  int local_return_value =
    unit_test_manager.runUnitTests( argc, argv, mpi_session );

  int return_value = mpi_session.sum( local_return_value );    

  int number_of_tests =
    mpi_session.sum( unit_test_manager.getNumberOfTests() );
  int number_of_run_tests =
    mpi_session.sum( unit_test_manager.getNumberOfRunTests() );
  int number_of_passed_tests =
    mpi_session.sum( unit_test_manager.getNumberOfPassedTests() );
  
  int number_of_checks =
    mpi_session.sum( unit_test_manager.getNumberOfChecks() );
  int number_of_passed_checks =
    mpi_session.sum( unit_test_manager.getNumberOfPassedChecks() );
  
  int number_of_unexpected_exceptions =
    mpi_session.sum( unit_test_manager.getNumberOfUnexpectedExceptions() );

  const bool report_details = (mpi_session.rank() == 0 ? true : false);

  if( report_details )
  {
    std::cout << "\nIgnore previous results - failures are expected..."
              << std::endl;
  }

  bool expected_return_value =
    Utility::compare<Utility::EqualityComparisonPolicy,2,2>(
                                   return_value, "return value",
                                   mpi_session.size(), "expected return value",
                                   std::cout, 0, report_details );
  bool expected_number_of_tests =
    Utility::compare<Utility::EqualityComparisonPolicy,2,2>(
                             number_of_tests, "number of tests",
                             97*mpi_session.size(), "expected number of tests",
                             std::cout, 0, report_details );

  bool expected_number_of_run_tests =
    Utility::compare<Utility::EqualityComparisonPolicy,2,2>(
                         number_of_run_tests, "number of run tests",
                         97*mpi_session.size(), "expected number of run tests",
                         std::cout, 0, report_details );

  bool expected_number_of_passed_tests =
    Utility::compare<Utility::EqualityComparisonPolicy,2,2>(
                      number_of_passed_tests, "number of passed tests",
                      63*mpi_session.size(), "expected number of passed tests",
                      std::cout, 0, report_details );

  bool expected_number_of_checks =
    Utility::compare<Utility::EqualityComparisonPolicy,2,2>(
                           number_of_checks, "number of checks",
                           783*mpi_session.size(), "expected number of checks",
                           std::cout, 0, report_details );

  bool expected_number_of_passed_checks =
    Utility::compare<Utility::EqualityComparisonPolicy,2,2>(
                    number_of_passed_checks, "number of passed checks",
                    540*mpi_session.size(), "expected number of passed checks",
                    std::cout, 0, report_details );

  bool expected_number_of_unexpected_exceptions =
    Utility::compare<Utility::EqualityComparisonPolicy,2,2>(
            number_of_unexpected_exceptions, "number of unexpected exceptions",
            2*mpi_session.size(), "expected number of unexpected exceptions",
            std::cout, 0, report_details );

  if( report_details )
    std::cout << "\nActual End Result: ";

  mpi_session.barrier();

  if( expected_return_value &&
      expected_number_of_tests &&
      expected_number_of_run_tests &&
      expected_number_of_passed_tests &&
      expected_number_of_checks &&
      expected_number_of_passed_checks &&
      expected_number_of_unexpected_exceptions )
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
// end tstFRENSIEUnitTestHarnessDefaultInit.cpp
//---------------------------------------------------------------------------//
