//---------------------------------------------------------------------------//
//!
//! \file   tstPropertyTree.cpp
//! \author Alex Robinson
//! \brief  Property tree class unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <sstream>
#include <memory>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>

// FRENSIE Includes
#include "Utility_PropertyTree.hpp"
#include "Utility_Variant.hpp"
#include "Utility_UnitTestHarnessExtensions.hpp"

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that a property tree can convert basic values correctly
TEUCHOS_UNIT_TEST( PropertyTree, convert_basic_values )
{
  // boost::property_tree::ptree ptree;
  Utility::PropertyTree ptree;

  // Store a bool
  ptree.put( "test_bool", true );

  TEST_EQUALITY_CONST( ptree.get<bool>( "test_bool" ), true );
  TEST_EQUALITY_CONST( ptree.get<std::string>( "test_bool" ), "true" );

  ptree.put( "test_bool", false );

  TEST_EQUALITY_CONST( ptree.get<bool>( "test_bool" ), false );
  TEST_EQUALITY_CONST( ptree.get<std::string>( "test_bool" ), "false" );

  // Store a short
  ptree.put( "test_short", -1 );

  TEST_EQUALITY_CONST( ptree.get<short>( "test_short" ), -1 );
  TEST_EQUALITY_CONST( ptree.get<std::string>( "test_short" ), "-1" );

  // Store an unsigned short
  ptree.put( "test_ushort", 1 );

  TEST_EQUALITY_CONST( ptree.get<ushort>( "test_ushort" ), 1 );
  TEST_EQUALITY_CONST( ptree.get<std::string>( "test_ushort" ), "1" );

  // Store an int
  ptree.put( "test_int", -11111 );

  TEST_EQUALITY_CONST( ptree.get<int>( "test_int" ), -11111 );
  TEST_EQUALITY_CONST( ptree.get<std::string>( "test_int" ), "-11111" );

  // Store an unsigned int
  ptree.put( "test_uint", 11111 );

  TEST_EQUALITY_CONST( ptree.get<unsigned int>( "test_uint" ), 11111 );
  TEST_EQUALITY_CONST( ptree.get<std::string>( "test_uint" ), "11111" );

  // Store a long
  ptree.put( "test_long", -11111 );

  TEST_EQUALITY_CONST( ptree.get<long>( "test_long" ), -11111 );
  TEST_EQUALITY_CONST( ptree.get<std::string>( "test_long" ), "-11111" );

  // Store an unsigned long
  ptree.put( "test_ulong", 11111 );

  TEST_EQUALITY_CONST( ptree.get<unsigned long>( "test_ulong" ), 11111 );
  TEST_EQUALITY_CONST( ptree.get<std::string>( "test_ulong" ), "11111" );

  // Store a long long
  ptree.put( "test_long_long", -10000000000 );

  TEST_EQUALITY_CONST( ptree.get<long long>( "test_long_long" ),
                       -10000000000 );
  TEST_EQUALITY_CONST( ptree.get<std::string>( "test_long_long" ),
                       "-10000000000" );

  // Store an unsigned long long
  ptree.put( "test_ulong_long", 10000000000 );

  TEST_EQUALITY_CONST( ptree.get<unsigned long long>( "test_ulong_long" ),
                       10000000000 );
  TEST_EQUALITY_CONST( ptree.get<std::string>( "test_ulong_long" ),
                       "10000000000" );

  // Store a float
  ptree.put( "test_float", -1.0f );

  TEST_EQUALITY_CONST( ptree.get<float>( "test_float" ), -1.0f );
  TEST_EQUALITY_CONST( ptree.get<std::string>( "test_float" ), "-1.000000000e+00" );

  ptree.put( "test_float", "-inf" );

  TEST_EQUALITY_CONST( ptree.get<float>( "test_float" ),
                       -std::numeric_limits<float>::infinity() );

  ptree.put( "test_float", "-pi/2" );

  TEST_EQUALITY_CONST( ptree.get<float>( "test_float" ),
                       -(float)Utility::PhysicalConstants::pi/2 );

  // Store a double
  ptree.put( "test_double", 1.0 );

  TEST_EQUALITY_CONST( ptree.get<double>( "test_double" ), 1.0 );
  TEST_EQUALITY_CONST( ptree.get<std::string>( "test_double" ), "1.000000000000000000e+00" );

  ptree.put( "test_double", "Infty" );

  TEST_EQUALITY_CONST( ptree.get<double>( "test_double" ),
                       std::numeric_limits<double>::infinity() );

  ptree.put( "test_double", "3pi/4" );

  TEST_EQUALITY_CONST( ptree.get<double>( "test_double" ),
                       3*Utility::PhysicalConstants::pi/4 );

  // Store a char
  ptree.put( "test_char", 'A' );

  TEST_EQUALITY_CONST( ptree.get<char>( "test_char" ), 'A' );
  TEST_EQUALITY_CONST( ptree.get<std::string>( "test_char" ), "A" );

  // Store a c-string
  ptree.put( "test_cstring", "Test" );

  TEST_EQUALITY_CONST( ptree.get<std::string>( "test_cstring" ), "Test" );

  TEST_NOTHROW( boost::property_tree::write_json( "test_basic.json", ptree ) );
}

//---------------------------------------------------------------------------//
// Check that a property tree can convert container values correctly
TEUCHOS_UNIT_TEST( PropertyTree, convert_container_values )
{
  Utility::PropertyTree ptree;

  // Store a string
  ptree.put( "test_string", std::string( "STest" ) );

  TEST_EQUALITY_CONST( ptree.get<std::string>( "test_string" ), "STest" );

  // Store a vector of int
  ptree.put( "test_vector_int", std::vector<int>({-1, 0, 1}) );

  TEST_COMPARE_CONTAINERS( (ptree.get<std::vector<int> >( "test_vector_int" )),
                           std::vector<int>({-1, 0, 1}) );
  TEST_EQUALITY_CONST( ptree.get<std::string>( "test_vector_int" ),
                       "{-1, 0, 1}" );

  ptree.put( "test_vector_int", "{0, 3i, 10000}" );

  TEST_COMPARE_CONTAINERS( (ptree.get<std::vector<int> >( "test_vector_int" )),
                           std::vector<int>({0, 2500, 5000, 7500, 10000}) );

  // Store a vector of float
  ptree.put( "test_vector_float", std::vector<float>({-1.0f, 0.0f, 1.0f}) );

  TEST_COMPARE_CONTAINERS( (ptree.get<std::vector<float> >( "test_vector_float" )),
                           std::vector<float>({-1.0f, 0.0f, 1.0f}) );
  TEST_EQUALITY_CONST( ptree.get<std::string>( "test_vector_float" ),
                       "{-1.000000000e+00, 0.000000000e+00, 1.000000000e+00}" );

  ptree.put( "test_vector_float", "{-1, 3i, 1.0}" );

  TEST_COMPARE_FLOATING_CONTAINERS( (ptree.get<std::vector<float> >( "test_vector_float" )),
                                    std::vector<float>({-1.0f, -0.5f, 0.0f, 0.5f, 1.0f}),
                                    1e-9 );

  ptree.put( "test_vector_float", "{1e-3, 2l, 1.0}" );

  TEST_COMPARE_FLOATING_CONTAINERS( (ptree.get<std::vector<float> >( "test_vector_float" )),
                                    std::vector<float>({1e-3f, 1e-2f, 1e-1f, 1.0f}),
                                    1e-7 );

  // Store a vector of vector of int
  ptree.put( "test_vector_vector_int", std::vector<std::vector<int> >({std::vector<int>({-1,0}), std::vector<int>({1,2})}) );

  TEST_EQUALITY_CONST( (ptree.get<std::vector<std::vector<int> > >( "test_vector_vector_int" )).size(), 2 );
  TEST_COMPARE_CONTAINERS( (ptree.get<std::vector<std::vector<int> > >( "test_vector_vector_int" ))[0], std::vector<int>({-1,0}) );
  TEST_COMPARE_CONTAINERS( (ptree.get<std::vector<std::vector<int> > >( "test_vector_vector_int" ))[1], std::vector<int>({1,2}) );

  // Store a map of int, double
  ptree.put( "test_map_int_double", std::map<int,double>({std::make_pair(0, 0.0), std::make_pair(1, -1.0), std::make_pair(2, -2.0)}) );

  TEST_EQUALITY_CONST( (ptree.get<std::map<int,double> >( "test_map_int_double" )).size(), 3 );
  TEST_EQUALITY_CONST( (ptree.get<std::map<int,double> >( "test_map_int_double" ))[0], 0.0 );
  TEST_EQUALITY_CONST( (ptree.get<std::map<int,double> >( "test_map_int_double" ))[1], -1.0 );
  TEST_EQUALITY_CONST( (ptree.get<std::map<int,double> >( "test_map_int_double" ))[2], -2.0 );

  TEST_NOTHROW( boost::property_tree::write_json( "test_container.json", ptree ) );
}

//---------------------------------------------------------------------------//
// Check if the property tree stores a JSON array
TEUCHOS_UNIT_TEST( PropertyTree, doesPropertyTreeStoreJSONArray )
{
  // Create a property tree with standard nodes and JSON array nodes
  Utility::PropertyTree ptree;

  // Construct level 1 nodes
  {
    ptree.put( "inline array", std::vector<int>({-1, 0, 1}) );

    Utility::PropertyTree level_1_ptree;
    
    Utility::PropertyTree json_array_element;

    json_array_element.put( "", -1 );

    level_1_ptree.push_back( std::make_pair( "", json_array_element ) );
    
    json_array_element.put( "", 0 );

    level_1_ptree.push_back( std::make_pair( "", json_array_element ) );
    
    json_array_element.put( "", 1 );

    level_1_ptree.push_back( std::make_pair( "", json_array_element ) );

    ptree.add_child( "json array", level_1_ptree );
  }

  TEST_ASSERT( !Utility::doesPropertyTreeStoreJSONArray( ptree ) );
  TEST_ASSERT( !Utility::doesPropertyTreeStoreJSONArray( ptree.get_child( "inline array" ) ) );
  TEST_ASSERT( Utility::doesPropertyTreeStoreJSONArray( ptree.get_child( "json array" ) ) );
               
  TEST_NOTHROW( boost::property_tree::write_json( "test_arrays.json", ptree ) );
}

//---------------------------------------------------------------------------//
// Check that basic types can be converted to a property tree
TEUCHOS_UNIT_TEST( PropertyTree, toPropertyTree_basic_values )
{
  // Convert a bool
  Utility::PropertyTree ptree = Utility::toPropertyTree( true, true );

  TEST_EQUALITY_CONST( ptree.data().toBool(), true );

  ptree = Utility::toPropertyTree( true, false );

  TEST_EQUALITY_CONST( ptree.data().toBool(), true );

  ptree = Utility::toPropertyTree( false );

  TEST_EQUALITY_CONST( ptree.data().toBool(), false );
    

  // Convert a short
  ptree = Utility::toPropertyTree( (short)-1, true );

  TEST_EQUALITY_CONST( ptree.data().toShort(), -1 );

  ptree = Utility::toPropertyTree( (short)0, false );

  TEST_EQUALITY_CONST( ptree.data().toShort(), 0 );

  ptree = Utility::toPropertyTree( (short)1 );

  TEST_EQUALITY_CONST( ptree.data().toShort(), 1 );

  // Convert an unsigned short
  ptree = Utility::toPropertyTree( (unsigned short)0, true );

  TEST_EQUALITY_CONST( ptree.data().toUnsignedShort(), 0 );

  ptree = Utility::toPropertyTree( (unsigned short)10, false );

  TEST_EQUALITY_CONST( ptree.data().toUnsignedShort(), 10 );

  ptree = Utility::toPropertyTree( (unsigned short)65535 );
  
  TEST_EQUALITY_CONST( ptree.data().toUnsignedShort(), 65535 );

  // Convert an int
  ptree = Utility::toPropertyTree( -11111, true );

  TEST_EQUALITY_CONST( ptree.data().toInt(), -11111 );

  ptree = Utility::toPropertyTree( 0, false );

  TEST_EQUALITY_CONST( ptree.data().toInt(), 0 );

  ptree = Utility::toPropertyTree( 11111 );

  TEST_EQUALITY_CONST( ptree.data().toInt(), 11111 );

  // Convert an unsigned int
  ptree = Utility::toPropertyTree( 0u, true );

  TEST_EQUALITY_CONST( ptree.data().toUnsignedInt(), 0u );

  ptree = Utility::toPropertyTree( 10u, false );

  TEST_EQUALITY_CONST( ptree.data().toUnsignedInt(), 10u );


  ptree = Utility::toPropertyTree( 11111u );

  TEST_EQUALITY_CONST( ptree.data().toUnsignedInt(), 11111u );

  // Convert a long
  ptree = Utility::toPropertyTree( -11111l, true );

  TEST_EQUALITY_CONST( ptree.data().toLong(), -11111l );

  ptree = Utility::toPropertyTree( 0l, false );

  TEST_EQUALITY_CONST( ptree.data().toLong(), 0l );

  ptree = Utility::toPropertyTree( 11111l );

  TEST_EQUALITY_CONST( ptree.data().toLong(), 11111l );

  // Convert an unsigned long
  ptree = Utility::toPropertyTree( 0ul, true );

  TEST_EQUALITY_CONST( ptree.data().toUnsignedLong(), 0ul );

  ptree = Utility::toPropertyTree( 10ul, false );

  TEST_EQUALITY_CONST( ptree.data().toUnsignedLong(), 10ul );

  ptree = Utility::toPropertyTree( 11111ul );

  TEST_EQUALITY_CONST( ptree.data().toUnsignedLong(), 11111ul );

  // Convert a long long
  ptree = Utility::toPropertyTree( -10000000000ll, true );

  TEST_EQUALITY_CONST( ptree.data().toLongLong(), -10000000000ll );

  ptree = Utility::toPropertyTree( 0ll, false );

  TEST_EQUALITY_CONST( ptree.data().toLongLong(), 0ll );

  ptree = Utility::toPropertyTree( 10000000000ll );

  TEST_EQUALITY_CONST( ptree.data().toLongLong(), 10000000000ll );

  // Convert an unsigned long long
  ptree = Utility::toPropertyTree( 0ull, true );

  TEST_EQUALITY_CONST( ptree.data().toUnsignedLongLong(), 0ull );

  ptree = Utility::toPropertyTree( 10ull, false );

  TEST_EQUALITY_CONST( ptree.data().toUnsignedLongLong(), 10ull );
  
  ptree = Utility::toPropertyTree( 10000000000ull );

  TEST_EQUALITY_CONST( ptree.data().toUnsignedLongLong(), 10000000000ull );

  // Convert a float
  ptree = Utility::toPropertyTree( -1.0f, true );

  TEST_EQUALITY_CONST( ptree.data().toFloat(), -1.0f );

  ptree = Utility::toPropertyTree( 0.0f, false );

  TEST_EQUALITY_CONST( ptree.data().toFloat(), 0.0f );

  ptree = Utility::toPropertyTree( 1.0f );

  TEST_EQUALITY_CONST( ptree.data().toFloat(), 1.0f );

  // Convert a double
  ptree = Utility::toPropertyTree( -1.0, true );

  TEST_EQUALITY_CONST( ptree.data().toDouble(), -1.0 );

  ptree = Utility::toPropertyTree( 0.0, false );

  TEST_EQUALITY_CONST( ptree.data().toDouble(), 0.0 );

  ptree = Utility::toPropertyTree( 1.0 );

  TEST_EQUALITY_CONST( ptree.data().toDouble(), 1.0 );

  // Convert a char
  ptree = Utility::toPropertyTree( 'A', true );

  TEST_EQUALITY_CONST( ptree.data().toChar(), 'A' );

  ptree = Utility::toPropertyTree( 'a', false );

  TEST_EQUALITY_CONST( ptree.data().toChar(), 'a' );

  ptree = Utility::toPropertyTree( 'B' );

  TEST_EQUALITY_CONST( ptree.data().toChar(), 'B' );

  // Convert a c-string
  ptree = Utility::toPropertyTree( "Test", true );

  TEST_EQUALITY_CONST( ptree.data().toString(), "Test" );

  ptree = Utility::toPropertyTree( "String", false );

  TEST_EQUALITY_CONST( ptree.data().toString(), "String" );

  ptree = Utility::toPropertyTree( "Test String" );

  TEST_EQUALITY_CONST( ptree.data().toString(), "Test String" );

  // Convert a std::string
  ptree = Utility::toPropertyTree( std::string( "Test" ), true );

  TEST_EQUALITY_CONST( ptree.data().toString(), "Test" );

  ptree = Utility::toPropertyTree( std::string( "String" ), false );

  TEST_EQUALITY_CONST( ptree.data().toString(), "String" );

  ptree = Utility::toPropertyTree( std::string( "Test String" ) );

  TEST_EQUALITY_CONST( ptree.data().toString(), "Test String" );
}

//---------------------------------------------------------------------------//
// Check that sequence container types can be converted to a property tree
TEUCHOS_UNIT_TEST( PropertyTree, toPropertyTree_sequence_container_values )
{
  // Convert a std::array to a property tree
  Utility::PropertyTree ptree =
    Utility::toPropertyTree( std::array<int,3>({-1,0,1}), true );

  TEST_EQUALITY_CONST( ptree.size(), 0 );
  TEST_EQUALITY_CONST( ptree.data().toVector().size(), 3 );
  TEST_EQUALITY_CONST( ptree.data().toVector()[0].toInt(), -1 );
  TEST_EQUALITY_CONST( ptree.data().toVector()[1].toInt(), 0 );
  TEST_EQUALITY_CONST( ptree.data().toVector()[2].toInt(), 1 );

  ptree = Utility::toPropertyTree( std::array<double,2>({-1.0,1.0}), false );

  TEST_EQUALITY_CONST( ptree.size(), 2 );
  TEST_EQUALITY_CONST( ptree.count( "" ), 2 );

  {
    Utility::PropertyTree::const_iterator it = ptree.begin();

    TEST_EQUALITY_CONST( it->second.data().toDouble(), -1.0 );

    ++it;

    TEST_EQUALITY_CONST( it->second.data().toDouble(), 1.0 );
  }

  ptree = Utility::toPropertyTree( std::array<unsigned long,4>({0l, 1l, 2l, 3l}) );

  TEST_EQUALITY_CONST( ptree.size(), 0 );
  TEST_EQUALITY_CONST( ptree.data().toVector().size(), 4 );
  TEST_EQUALITY_CONST( ptree.data().toVector()[0].toLong(), 0l );
  TEST_EQUALITY_CONST( ptree.data().toVector()[1].toLong(), 1l );
  TEST_EQUALITY_CONST( ptree.data().toVector()[2].toLong(), 2l );
  TEST_EQUALITY_CONST( ptree.data().toVector()[3].toLong(), 3l );

  // Convert a std::vector to a property tree
  ptree = Utility::toPropertyTree( std::vector<int>({-1,0,1}), true );

  TEST_EQUALITY_CONST( ptree.size(), 0 );
  TEST_EQUALITY_CONST( ptree.data().toVector().size(), 3 );
  TEST_EQUALITY_CONST( ptree.data().toVector()[0].toInt(), -1 );
  TEST_EQUALITY_CONST( ptree.data().toVector()[1].toInt(), 0 );
  TEST_EQUALITY_CONST( ptree.data().toVector()[2].toInt(), 1 );

  ptree = Utility::toPropertyTree( std::vector<double>({-1.0,1.0}), false );

  TEST_EQUALITY_CONST( ptree.size(), 2 );
  TEST_EQUALITY_CONST( ptree.count( "" ), 2 );

  {
    Utility::PropertyTree::const_iterator it = ptree.begin();

    TEST_EQUALITY_CONST( it->second.data().toDouble(), -1.0 );

    ++it;

    TEST_EQUALITY_CONST( it->second.data().toDouble(), 1.0 );
  }

  ptree = Utility::toPropertyTree( std::vector<unsigned long>({0l, 1l, 2l, 3l}) );

  TEST_EQUALITY_CONST( ptree.size(), 0 );
  TEST_EQUALITY_CONST( ptree.data().toVector().size(), 4 );
  TEST_EQUALITY_CONST( ptree.data().toVector()[0].toLong(), 0l );
  TEST_EQUALITY_CONST( ptree.data().toVector()[1].toLong(), 1l );
  TEST_EQUALITY_CONST( ptree.data().toVector()[2].toLong(), 2l );
  TEST_EQUALITY_CONST( ptree.data().toVector()[3].toLong(), 3l );

  // Convert a std::list to a property tree
  ptree = Utility::toPropertyTree( std::list<int>({-1,0,1}), true );

  TEST_EQUALITY_CONST( ptree.size(), 0 );
  TEST_EQUALITY_CONST( ptree.data().toVector().size(), 3 );
  TEST_EQUALITY_CONST( ptree.data().toVector()[0].toInt(), -1 );
  TEST_EQUALITY_CONST( ptree.data().toVector()[1].toInt(), 0 );
  TEST_EQUALITY_CONST( ptree.data().toVector()[2].toInt(), 1 );

  ptree = Utility::toPropertyTree( std::list<double>({-1.0,1.0}), false );

  TEST_EQUALITY_CONST( ptree.size(), 2 );
  TEST_EQUALITY_CONST( ptree.count( "" ), 2 );

  {
    Utility::PropertyTree::const_iterator it = ptree.begin();

    TEST_EQUALITY_CONST( it->second.data().toDouble(), -1.0 );

    ++it;

    TEST_EQUALITY_CONST( it->second.data().toDouble(), 1.0 );
  }

  ptree = Utility::toPropertyTree( std::list<unsigned long>({0l, 1l, 2l, 3l}) );

  TEST_EQUALITY_CONST( ptree.size(), 0 );
  TEST_EQUALITY_CONST( ptree.data().toVector().size(), 4 );
  TEST_EQUALITY_CONST( ptree.data().toVector()[0].toLong(), 0l );
  TEST_EQUALITY_CONST( ptree.data().toVector()[1].toLong(), 1l );
  TEST_EQUALITY_CONST( ptree.data().toVector()[2].toLong(), 2l );
  TEST_EQUALITY_CONST( ptree.data().toVector()[3].toLong(), 3l );

  // Convert a std::forward_list to a property tree
  ptree = Utility::toPropertyTree( std::forward_list<int>({-1,0,1}), true );

  TEST_EQUALITY_CONST( ptree.size(), 0 );
  TEST_EQUALITY_CONST( ptree.data().toVector().size(), 3 );
  TEST_EQUALITY_CONST( ptree.data().toVector()[0].toInt(), -1 );
  TEST_EQUALITY_CONST( ptree.data().toVector()[1].toInt(), 0 );
  TEST_EQUALITY_CONST( ptree.data().toVector()[2].toInt(), 1 );

  ptree = Utility::toPropertyTree( std::forward_list<double>({-1.0,1.0}), false );

  TEST_EQUALITY_CONST( ptree.size(), 2 );
  TEST_EQUALITY_CONST( ptree.count( "" ), 2 );

  {
    Utility::PropertyTree::const_iterator it = ptree.begin();

    TEST_EQUALITY_CONST( it->second.data().toDouble(), -1.0 );

    ++it;

    TEST_EQUALITY_CONST( it->second.data().toDouble(), 1.0 );
  }

  ptree = Utility::toPropertyTree( std::forward_list<unsigned long>({0l, 1l, 2l, 3l}) );

  TEST_EQUALITY_CONST( ptree.size(), 0 );
  TEST_EQUALITY_CONST( ptree.data().toVector().size(), 4 );
  TEST_EQUALITY_CONST( ptree.data().toVector()[0].toLong(), 0l );
  TEST_EQUALITY_CONST( ptree.data().toVector()[1].toLong(), 1l );
  TEST_EQUALITY_CONST( ptree.data().toVector()[2].toLong(), 2l );
  TEST_EQUALITY_CONST( ptree.data().toVector()[3].toLong(), 3l );

  // Convert a std::deque to a property tree
  ptree = Utility::toPropertyTree( std::deque<int>({-1,0,1}), true );

  TEST_EQUALITY_CONST( ptree.size(), 0 );
  TEST_EQUALITY_CONST( ptree.data().toVector().size(), 3 );
  TEST_EQUALITY_CONST( ptree.data().toVector()[0].toInt(), -1 );
  TEST_EQUALITY_CONST( ptree.data().toVector()[1].toInt(), 0 );
  TEST_EQUALITY_CONST( ptree.data().toVector()[2].toInt(), 1 );

  ptree = Utility::toPropertyTree( std::deque<double>({-1.0,1.0}), false );

  TEST_EQUALITY_CONST( ptree.size(), 2 );
  TEST_EQUALITY_CONST( ptree.count( "" ), 2 );

  {
    Utility::PropertyTree::const_iterator it = ptree.begin();

    TEST_EQUALITY_CONST( it->second.data().toDouble(), -1.0 );

    ++it;

    TEST_EQUALITY_CONST( it->second.data().toDouble(), 1.0 );
  }

  ptree = Utility::toPropertyTree( std::deque<unsigned long>({0l, 1l, 2l, 3l}) );

  TEST_EQUALITY_CONST( ptree.size(), 0 );
  TEST_EQUALITY_CONST( ptree.data().toVector().size(), 4 );
  TEST_EQUALITY_CONST( ptree.data().toVector()[0].toLong(), 0l );
  TEST_EQUALITY_CONST( ptree.data().toVector()[1].toLong(), 1l );
  TEST_EQUALITY_CONST( ptree.data().toVector()[2].toLong(), 2l );
  TEST_EQUALITY_CONST( ptree.data().toVector()[3].toLong(), 3l );

  // Convert a std::set to a property tree
  ptree = Utility::toPropertyTree( std::set<int>({-1,0,1}), true );

  TEST_EQUALITY_CONST( ptree.size(), 0 );
  TEST_EQUALITY_CONST( ptree.data().toVector().size(), 3 );
  TEST_EQUALITY_CONST( ptree.data().toVector()[0].toInt(), -1 );
  TEST_EQUALITY_CONST( ptree.data().toVector()[1].toInt(), 0 );
  TEST_EQUALITY_CONST( ptree.data().toVector()[2].toInt(), 1 );

  ptree = Utility::toPropertyTree( std::set<double>({-1.0,1.0}), false );

  TEST_EQUALITY_CONST( ptree.size(), 2 );
  TEST_EQUALITY_CONST( ptree.count( "" ), 2 );

  {
    Utility::PropertyTree::const_iterator it = ptree.begin();

    TEST_EQUALITY_CONST( it->second.data().toDouble(), -1.0 );

    ++it;

    TEST_EQUALITY_CONST( it->second.data().toDouble(), 1.0 );
  }

  ptree = Utility::toPropertyTree( std::set<unsigned long>({0l, 1l, 2l, 3l}) );

  TEST_EQUALITY_CONST( ptree.size(), 0 );
  TEST_EQUALITY_CONST( ptree.data().toVector().size(), 4 );

  // Convert a std::unordered_set to a property tree
  ptree = Utility::toPropertyTree( std::unordered_set<int>({-1,0,1}), true );

  TEST_EQUALITY_CONST( ptree.size(), 0 );
  TEST_EQUALITY_CONST( ptree.data().toVector().size(), 3 );

  ptree = Utility::toPropertyTree( std::unordered_set<double>({-1.0,1.0}), false );

  TEST_EQUALITY_CONST( ptree.size(), 2 );
  TEST_EQUALITY_CONST( ptree.count( "" ), 2 );

  ptree = Utility::toPropertyTree( std::unordered_set<unsigned long>({0l, 1l, 2l, 3l}) );

  TEST_EQUALITY_CONST( ptree.size(), 0 );
  TEST_EQUALITY_CONST( ptree.data().toVector().size(), 4 );

  // Convert a std::vector<std::string> to a property tree
  ptree = Utility::toPropertyTree( std::vector<std::string>({"Test", "String"}), true );

  TEST_EQUALITY_CONST( ptree.size(), 0 );
  TEST_EQUALITY_CONST( ptree.data().toVector().size(), 2 );
  TEST_EQUALITY_CONST( ptree.data().toVector()[0].toString(), "Test" );
  TEST_EQUALITY_CONST( ptree.data().toVector()[1].toString(), "String" );

  ptree = Utility::toPropertyTree( std::vector<std::string>({"Test", "String", "JSON-Array"}), false );

  TEST_EQUALITY_CONST( ptree.size(), 3 );
  TEST_EQUALITY_CONST( ptree.count( "" ), 3 );

  {
    Utility::PropertyTree::const_iterator it = ptree.begin();

    TEST_EQUALITY_CONST( it->second.data().toString(), "Test" );

    ++it;

    TEST_EQUALITY_CONST( it->second.data().toString(), "String" );

    ++it;

    TEST_EQUALITY_CONST( it->second.data().toString(), "JSON-Array" );
  }

  ptree = Utility::toPropertyTree( std::vector<std::string>({"Test", "String", "Default-Inlining"}) );

  TEST_EQUALITY_CONST( ptree.size(), 0 );
  TEST_EQUALITY_CONST( ptree.data().toVector().size(), 3 );
  TEST_EQUALITY_CONST( ptree.data().toVector()[0].toString(), "Test" );
  TEST_EQUALITY_CONST( ptree.data().toVector()[1].toString(), "String" );
  TEST_EQUALITY_CONST( ptree.data().toVector()[2].toString(), "Default-Inlining" );

  // Convert a VariantVector to a property tree
  ptree = Utility::toPropertyTree( Utility::VariantVector({Utility::Variant("Test"), Utility::Variant(0), Utility::Variant(1.0)}), true );

  TEST_EQUALITY_CONST( ptree.size(), 0 );
  TEST_EQUALITY_CONST( ptree.data().toVector().size(), 3 );
  TEST_EQUALITY_CONST( ptree.data().toVector()[0].toString(), "Test" );
  TEST_EQUALITY_CONST( ptree.data().toVector()[1].toInt(), 0 );
  TEST_EQUALITY_CONST( ptree.data().toVector()[2].toDouble(), 1.0 );

  ptree = Utility::toPropertyTree( Utility::VariantVector({Utility::Variant("Test"), Utility::Variant(0), Utility::Variant(std::vector<double>({-1.0,1.0}))}), false );

  TEST_EQUALITY_CONST( ptree.size(), 3 );
  TEST_EQUALITY_CONST( ptree.count( "" ), 3 );

  {
    Utility::PropertyTree::const_iterator it = ptree.begin();

    TEST_EQUALITY_CONST( it->second.data().toString(), "Test" );

    ++it;

    TEST_EQUALITY_CONST( it->second.data().toInt(), 0 );

    ++it;

    TEST_EQUALITY_CONST( it->second.data().toVector().size(), 2 );
    TEST_EQUALITY_CONST( it->second.data().toVector()[0].toFloat(), -1.0f );
    TEST_EQUALITY_CONST( it->second.data().toVector()[1].toFloat(), 1.0f );
  }

  ptree = Utility::toPropertyTree( Utility::VariantVector({Utility::Variant("Test"), Utility::Variant(-1), Utility::Variant(std::vector<int>())}) );

  TEST_EQUALITY_CONST( ptree.size(), 0 );
  TEST_EQUALITY_CONST( ptree.data().toVector().size(), 3 );
  TEST_EQUALITY_CONST( ptree.data().toVector()[0].toString(), "Test" );
  TEST_EQUALITY_CONST( ptree.data().toVector()[1].toInt(), -1 );
  TEST_EQUALITY_CONST( ptree.data().toVector()[2].toVector().size(), 0 );

  // Convert a std::vector<std::vector<int> > to a property tree
  ptree = Utility::toPropertyTree( std::vector<std::vector<int> >({std::vector<int>({-1,0,1}), std::vector<int>({2,3})}), true );

  TEST_EQUALITY_CONST( ptree.size(), 0 );
  TEST_EQUALITY_CONST( ptree.data().toVector().size(), 2 );
  TEST_EQUALITY_CONST( ptree.data().toVector()[0].toVector().size(), 3 );
  TEST_EQUALITY_CONST( ptree.data().toVector()[0].toVector()[0].toInt(), -1 );
  TEST_EQUALITY_CONST( ptree.data().toVector()[0].toVector()[1].toInt(), 0 );
  TEST_EQUALITY_CONST( ptree.data().toVector()[0].toVector()[2].toInt(), 1 );
  TEST_EQUALITY_CONST( ptree.data().toVector()[1].toVector().size(), 2 );
  TEST_EQUALITY_CONST( ptree.data().toVector()[1].toVector()[0].toInt(), 2 );
  TEST_EQUALITY_CONST( ptree.data().toVector()[1].toVector()[1].toInt(), 3 );

  ptree = Utility::toPropertyTree( std::vector<std::vector<double> >({std::vector<double>({-1.0,0.0,1.0}), std::vector<double>({-1.0,1.0})}), false );

  TEST_EQUALITY_CONST( ptree.size(), 2 );
  TEST_EQUALITY_CONST( ptree.count( "" ), 2 );

  {
    Utility::PropertyTree::const_iterator it = ptree.begin();

    TEST_EQUALITY_CONST( it->second.size(), 3 );

    Utility::PropertyTree::const_iterator child_it = it->second.begin();
    
    TEST_EQUALITY_CONST( child_it->second.data().toDouble(), -1.0 );

    ++child_it;
    
    TEST_EQUALITY_CONST( child_it->second.data().toDouble(), 0.0 );

    ++child_it;
    
    TEST_EQUALITY_CONST( child_it->second.data().toDouble(), 1.0 );

    ++it;

    TEST_EQUALITY_CONST( it->second.size(), 2 );

    child_it = it->second.begin();
    
    TEST_EQUALITY_CONST( child_it->second.data().toDouble(), -1.0 );

    ++child_it;
    
    TEST_EQUALITY_CONST( child_it->second.data().toDouble(), 1.0 );
  }

  ptree = Utility::toPropertyTree( std::vector<std::vector<unsigned long> >({std::vector<unsigned long>({0ul, 1ul, 2ul}),std::vector<unsigned long>({3ul,4ul})}) );

  TEST_EQUALITY_CONST( ptree.size(), 0 );
  TEST_EQUALITY_CONST( ptree.data().toVector().size(), 2 );
  TEST_EQUALITY_CONST( ptree.data().toVector()[0].toVector().size(), 3 );
  TEST_EQUALITY_CONST( ptree.data().toVector()[0].toVector()[0].toUnsignedLong(), 0ul );
  TEST_EQUALITY_CONST( ptree.data().toVector()[0].toVector()[1].toUnsignedLong(), 1ul );
  TEST_EQUALITY_CONST( ptree.data().toVector()[0].toVector()[2].toUnsignedLong(), 2ul );
  TEST_EQUALITY_CONST( ptree.data().toVector()[1].toVector().size(), 2 );
  TEST_EQUALITY_CONST( ptree.data().toVector()[1].toVector()[0].toUnsignedLong(), 3ul );
  TEST_EQUALITY_CONST( ptree.data().toVector()[1].toVector()[1].toUnsignedLong(), 4ul );
}

//---------------------------------------------------------------------------//
// Check that associative container types can be converted to a property tree
TEUCHOS_UNIT_TEST( PropertyTree, toPropertyTree_associative_container_values )
{
  // Convert a std::map<int,int> to a property tree
  Utility::PropertyTree ptree = Utility::toPropertyTree( std::map<int,int>({std::make_pair(-1,-1), std::make_pair(0,0)}), true );

  TEST_EQUALITY_CONST( ptree.size(), 0 );
  TEST_EQUALITY_CONST( ptree.data().toMap().size(), 2 );
  TEST_EQUALITY_CONST( ptree.data().toMap()["-1"].toInt(), -1 );
  TEST_EQUALITY_CONST( ptree.data().toMap()["0"].toInt(), 0 );

  ptree = Utility::toPropertyTree( std::map<int,int>({std::make_pair(-1,-1), std::make_pair(0,0)}), false );

  TEST_EQUALITY_CONST( ptree.size(), 2 );
  TEST_EQUALITY_CONST( ptree.count( "-1" ), 1 );
  TEST_EQUALITY_CONST( ptree.get_child( "-1" ).data().toInt(), -1 );
  TEST_EQUALITY_CONST( ptree.count( "0" ), 1 );
  TEST_EQUALITY_CONST( ptree.get_child( "0" ).data().toInt(), 0 );

  ptree = Utility::toPropertyTree( std::map<int,int>({std::make_pair(-1,-1), std::make_pair(0,0)}) );

  TEST_EQUALITY_CONST( ptree.size(), 2 );
  TEST_EQUALITY_CONST( ptree.count( "-1" ), 1 );
  TEST_EQUALITY_CONST( ptree.get_child( "-1" ).data().toInt(), -1 );
  TEST_EQUALITY_CONST( ptree.count( "0" ), 1 );
  TEST_EQUALITY_CONST( ptree.get_child( "0" ).data().toInt(), 0 );

  // Convert a std::map<std::string,int> to a property tree
  ptree = Utility::toPropertyTree( std::map<std::string,int>({std::make_pair("value a", -1), std::make_pair("value b", 1)}), true );

  TEST_EQUALITY_CONST( ptree.size(), 0 );
  TEST_EQUALITY_CONST( ptree.data().toMap().size(), 2 );
  TEST_EQUALITY_CONST( ptree.data().toMap()["value a"].toInt(), -1 );
  TEST_EQUALITY_CONST( ptree.data().toMap()["value b"].toInt(), 1 );

  ptree = Utility::toPropertyTree( std::map<std::string,int>({std::make_pair("value a", -1), std::make_pair("value b", 1)}), false );

  TEST_EQUALITY_CONST( ptree.size(), 2 );
  TEST_EQUALITY_CONST( ptree.count( "value a" ), 1 );
  TEST_EQUALITY_CONST( ptree.get_child( "value a" ).data().toInt(), -1 );
  TEST_EQUALITY_CONST( ptree.count( "value b" ), 1 );
  TEST_EQUALITY_CONST( ptree.get_child( "value b" ).data().toInt(), 1 );

  ptree = Utility::toPropertyTree( std::map<std::string,int>({std::make_pair("value a", -1), std::make_pair("value b", 1)}) );

  TEST_EQUALITY_CONST( ptree.size(), 2 );
  TEST_EQUALITY_CONST( ptree.count( "value a" ), 1 );
  TEST_EQUALITY_CONST( ptree.get_child( "value a" ).data().toInt(), -1 );
  TEST_EQUALITY_CONST( ptree.count( "value b" ), 1 );
  TEST_EQUALITY_CONST( ptree.get_child( "value b" ).data().toInt(), 1 );

  // Convert a std::map<std::string,std::vector<double> > to a property tree
  ptree = Utility::toPropertyTree( std::map<std::string,std::vector<double> >({std::make_pair("value a", std::vector<double>({-1.0,0.0,1.0})), std::make_pair("value b", std::vector<double>({0.0,1.0}))}), true );

  TEST_EQUALITY_CONST( ptree.size(), 0 );
  TEST_EQUALITY_CONST( ptree.data().toMap().size(), 2 );
  TEST_EQUALITY_CONST( ptree.data().toMap()["value a"].toVector().size(), 3 );
  TEST_EQUALITY_CONST( ptree.data().toMap()["value b"].toVector().size(), 2 );

  ptree = Utility::toPropertyTree( std::map<std::string,std::vector<double> >({std::make_pair("value a", std::vector<double>({-1.0,0.0,1.0})), std::make_pair("value b", std::vector<double>({0.0,1.0}))}), false );

  TEST_EQUALITY_CONST( ptree.size(), 2 );
  TEST_EQUALITY_CONST( ptree.count( "value a" ), 1 );
  TEST_EQUALITY_CONST( ptree.get_child( "value a" ).size(), 3 );

  {
    Utility::PropertyTree::const_iterator it =
      ptree.get_child( "value a" ).begin();

    TEST_EQUALITY_CONST( it->second.data().toDouble(), -1.0 );

    ++it;

    TEST_EQUALITY_CONST( it->second.data().toDouble(), 0.0 );

    ++it;

    TEST_EQUALITY_CONST( it->second.data().toDouble(), 1.0 );
  }

  TEST_EQUALITY_CONST( ptree.count( "value b" ), 1 );
  TEST_EQUALITY_CONST( ptree.get_child( "value b" ).size(), 2 );

  {
    Utility::PropertyTree::const_iterator it =
      ptree.get_child( "value b" ).begin();

    TEST_EQUALITY_CONST( it->second.data().toDouble(), 0.0 );

    ++it;
    
    TEST_EQUALITY_CONST( it->second.data().toDouble(), 1.0 );
  }

  ptree = Utility::toPropertyTree( std::map<std::string,std::vector<double> >({std::make_pair("value a", std::vector<double>({-1.0,0.0,1.0})), std::make_pair("value b", std::vector<double>({0.0,1.0}))}) );

  TEST_EQUALITY_CONST( ptree.size(), 2 );
  TEST_EQUALITY_CONST( ptree.count( "value a" ), 1 );
  TEST_EQUALITY_CONST( ptree.get_child( "value a" ).size(), 3 );

  {
    Utility::PropertyTree::const_iterator it =
      ptree.get_child( "value a" ).begin();

    TEST_EQUALITY_CONST( it->second.data().toDouble(), -1.0 );

    ++it;

    TEST_EQUALITY_CONST( it->second.data().toDouble(), 0.0 );

    ++it;

    TEST_EQUALITY_CONST( it->second.data().toDouble(), 1.0 );
  }

  TEST_EQUALITY_CONST( ptree.count( "value b" ), 1 );
  TEST_EQUALITY_CONST( ptree.get_child( "value b" ).size(), 2 );

  {
    Utility::PropertyTree::const_iterator it =
      ptree.get_child( "value b" ).begin();

    TEST_EQUALITY_CONST( it->second.data().toDouble(), 0.0 );

    ++it;

    TEST_EQUALITY_CONST( it->second.data().toDouble(), 1.0 );
  }

  // Convert a std::unordered_map<int,int> to a property tree
  ptree = Utility::toPropertyTree( std::unordered_map<int,int>({std::make_pair(-1,-1), std::make_pair(0,0)}), true );

  TEST_EQUALITY_CONST( ptree.size(), 0 );
  TEST_EQUALITY_CONST( ptree.data().toMap().size(), 2 );
  TEST_EQUALITY_CONST( ptree.data().toMap()["-1"].toInt(), -1 );
  TEST_EQUALITY_CONST( ptree.data().toMap()["0"].toInt(), 0 );

  ptree = Utility::toPropertyTree( std::unordered_map<int,int>({std::make_pair(-1,-1), std::make_pair(0,0)}), false );

  TEST_EQUALITY_CONST( ptree.size(), 2 );
  TEST_EQUALITY_CONST( ptree.count( "-1" ), 1 );
  TEST_EQUALITY_CONST( ptree.get_child( "-1" ).data().toInt(), -1 );
  TEST_EQUALITY_CONST( ptree.count( "0" ), 1 );
  TEST_EQUALITY_CONST( ptree.get_child( "0" ).data().toInt(), 0 );

  ptree = Utility::toPropertyTree( std::unordered_map<int,int>({std::make_pair(-1,-1), std::make_pair(0,0)}) );

  TEST_EQUALITY_CONST( ptree.size(), 2 );
  TEST_EQUALITY_CONST( ptree.count( "-1" ), 1 );
  TEST_EQUALITY_CONST( ptree.get_child( "-1" ).data().toInt(), -1 );
  TEST_EQUALITY_CONST( ptree.count( "0" ), 1 );
  TEST_EQUALITY_CONST( ptree.get_child( "0" ).data().toInt(), 0 );

  // Convert a std::unordered_map<std::string,int> to a property tree
  ptree = Utility::toPropertyTree( std::unordered_map<std::string,int>({std::make_pair("value a", -1), std::make_pair("value b", 1)}), true );

  TEST_EQUALITY_CONST( ptree.size(), 0 );
  TEST_EQUALITY_CONST( ptree.data().toMap().size(), 2 );
  TEST_EQUALITY_CONST( ptree.data().toMap()["value a"].toInt(), -1 );
  TEST_EQUALITY_CONST( ptree.data().toMap()["value b"].toInt(), 1 );

  ptree = Utility::toPropertyTree( std::unordered_map<std::string,int>({std::make_pair("value a", -1), std::make_pair("value b", 1)}), false );

  TEST_EQUALITY_CONST( ptree.size(), 2 );
  TEST_EQUALITY_CONST( ptree.count( "value a" ), 1 );
  TEST_EQUALITY_CONST( ptree.get_child( "value a" ).data().toInt(), -1 );
  TEST_EQUALITY_CONST( ptree.count( "value b" ), 1 );
  TEST_EQUALITY_CONST( ptree.get_child( "value b" ).data().toInt(), 1 );

  ptree = Utility::toPropertyTree( std::unordered_map<std::string,int>({std::make_pair("value a", -1), std::make_pair("value b", 1)}) );

  TEST_EQUALITY_CONST( ptree.size(), 2 );
  TEST_EQUALITY_CONST( ptree.count( "value a" ), 1 );
  TEST_EQUALITY_CONST( ptree.get_child( "value a" ).data().toInt(), -1 );
  TEST_EQUALITY_CONST( ptree.count( "value b" ), 1 );
  TEST_EQUALITY_CONST( ptree.get_child( "value b" ).data().toInt(), 1 );

  // Convert a std::unordered_map<std::string,std::vector<double> > to a property tree
  ptree = Utility::toPropertyTree( std::unordered_map<std::string,std::vector<double> >({std::make_pair("value a", std::vector<double>({-1.0,0.0,1.0})), std::make_pair("value b", std::vector<double>({0.0,1.0}))}), true );

  TEST_EQUALITY_CONST( ptree.size(), 0 );
  TEST_EQUALITY_CONST( ptree.data().toMap().size(), 2 );
  TEST_EQUALITY_CONST( ptree.data().toMap()["value a"].toVector().size(), 3 );
  TEST_EQUALITY_CONST( ptree.data().toMap()["value b"].toVector().size(), 2 );

  ptree = Utility::toPropertyTree( std::unordered_map<std::string,std::vector<double> >({std::make_pair("value a", std::vector<double>({-1.0,0.0,1.0})), std::make_pair("value b", std::vector<double>({0.0,1.0}))}), false );

  TEST_EQUALITY_CONST( ptree.size(), 2 );
  TEST_EQUALITY_CONST( ptree.count( "value a" ), 1 );
  TEST_EQUALITY_CONST( ptree.get_child( "value a" ).size(), 3 );

  {
    Utility::PropertyTree::const_iterator it =
      ptree.get_child( "value a" ).begin();

    TEST_EQUALITY_CONST( it->second.data().toDouble(), -1.0 );

    ++it;

    TEST_EQUALITY_CONST( it->second.data().toDouble(), 0.0 );

    ++it;

    TEST_EQUALITY_CONST( it->second.data().toDouble(), 1.0 );
  }

  TEST_EQUALITY_CONST( ptree.count( "value b" ), 1 );
  TEST_EQUALITY_CONST( ptree.get_child( "value b" ).size(), 2 );

  {
    Utility::PropertyTree::const_iterator it =
      ptree.get_child( "value b" ).begin();

    TEST_EQUALITY_CONST( it->second.data().toDouble(), 0.0 );

    ++it;
    
    TEST_EQUALITY_CONST( it->second.data().toDouble(), 1.0 );
  }

  ptree = Utility::toPropertyTree( std::unordered_map<std::string,std::vector<double> >({std::make_pair("value a", std::vector<double>({-1.0,0.0,1.0})), std::make_pair("value b", std::vector<double>({0.0,1.0}))}) );

  TEST_EQUALITY_CONST( ptree.size(), 2 );
  TEST_EQUALITY_CONST( ptree.count( "value a" ), 1 );
  TEST_EQUALITY_CONST( ptree.get_child( "value a" ).size(), 3 );

  {
    Utility::PropertyTree::const_iterator it =
      ptree.get_child( "value a" ).begin();

    TEST_EQUALITY_CONST( it->second.data().toDouble(), -1.0 );

    ++it;

    TEST_EQUALITY_CONST( it->second.data().toDouble(), 0.0 );

    ++it;

    TEST_EQUALITY_CONST( it->second.data().toDouble(), 1.0 );
  }

  TEST_EQUALITY_CONST( ptree.count( "value b" ), 1 );
  TEST_EQUALITY_CONST( ptree.get_child( "value b" ).size(), 2 );

  {
    Utility::PropertyTree::const_iterator it =
      ptree.get_child( "value b" ).begin();

    TEST_EQUALITY_CONST( it->second.data().toDouble(), 0.0 );

    ++it;

    TEST_EQUALITY_CONST( it->second.data().toDouble(), 1.0 );
  }

  // Convert a VariantMap to a property tree
  ptree = Utility::toPropertyTree( Utility::VariantMap({std::make_pair("value a", Utility::Variant(-1)), std::make_pair("value b", Utility::Variant(std::vector<double>({-1.0,0.0,1.0})))}), true );

  TEST_EQUALITY_CONST( ptree.size(), 0 );
  TEST_EQUALITY_CONST( ptree.data().toMap().size(), 2 );
  TEST_EQUALITY_CONST( ptree.data().toMap()["value a"].toInt(), -1 );
  TEST_EQUALITY_CONST( ptree.data().toMap()["value b"].toVector().size(), 3 );

  ptree = Utility::toPropertyTree( Utility::VariantMap({std::make_pair("value a", Utility::Variant(-1)), std::make_pair("value b", Utility::Variant(std::vector<double>({-1.0,0.0,1.0})))}), false );

  TEST_EQUALITY_CONST( ptree.size(), 2 );
  TEST_EQUALITY_CONST( ptree.count( "value a" ), 1 );
  TEST_EQUALITY_CONST( ptree.get_child( "value a" ).size(), 0 );
  TEST_EQUALITY_CONST( ptree.get_child( "value a" ).data().toInt(), -1 );
  TEST_EQUALITY_CONST( ptree.count( "value b" ), 1 );
  TEST_EQUALITY_CONST( ptree.get_child( "value b" ).size(), 0 );
  TEST_EQUALITY_CONST( ptree.get_child( "value b" ).data().toVector().size(), 3 );

  ptree = Utility::toPropertyTree( Utility::VariantMap({std::make_pair("value a", Utility::Variant(-1)), std::make_pair("value b", Utility::Variant(std::vector<double>({-1.0,0.0,1.0})))}) );

  TEST_EQUALITY_CONST( ptree.size(), 2 );
  TEST_EQUALITY_CONST( ptree.count( "value a" ), 1 );
  TEST_EQUALITY_CONST( ptree.get_child( "value a" ).size(), 0 );
  TEST_EQUALITY_CONST( ptree.get_child( "value a" ).data().toInt(), -1 );
  TEST_EQUALITY_CONST( ptree.count( "value b" ), 1 );
  TEST_EQUALITY_CONST( ptree.get_child( "value b" ).size(), 0 );
  TEST_EQUALITY_CONST( ptree.get_child( "value b" ).data().toVector().size(), 3 );
}

//---------------------------------------------------------------------------//
// Check that a property tree node can be converted to a sequence container
TEUCHOS_UNIT_TEST( PropertyTree, fromPropertyTree_sequence_container )
{
  // Create a property tree with standard nodes and JSON array nodes
  Utility::PropertyTree ptree;

  // Construct level 1 nodes
  {
    ptree.put( "value", true );
    ptree.put( "inline array", std::vector<int>({-1, 0, 1}) );

    Utility::PropertyTree level_1_ptree;
    
    Utility::PropertyTree json_array_element;

    json_array_element.put( "", -1 );

    level_1_ptree.push_back( std::make_pair( "", json_array_element ) );
    
    json_array_element.put( "", 0 );

    level_1_ptree.push_back( std::make_pair( "", json_array_element ) );
    
    json_array_element.put( "", 1 );

    level_1_ptree.push_back( std::make_pair( "", json_array_element ) );

    ptree.add_child( "json array", level_1_ptree );
  }

  // Convert the nodes to vectors
  std::vector<std::string> unused_children;

  TEST_THROW( Utility::fromPropertyTree<std::vector<int> >( ptree, unused_children ),
              Utility::PropertyTreeConversionException );
  TEST_THROW( Utility::fromPropertyTree<std::vector<double> >( ptree, unused_children ),
              Utility::PropertyTreeConversionException );
  TEST_THROW( Utility::fromPropertyTree<std::vector<std::string> >( ptree, unused_children ),
              Utility::PropertyTreeConversionException );              
  TEST_THROW( Utility::fromPropertyTree<Utility::VariantVector>( ptree, unused_children ),
              Utility::PropertyTreeConversionException );

  TEST_THROW( Utility::fromPropertyTree<std::vector<int> >( ptree.get_child( "value" ), unused_children ),
              Utility::PropertyTreeConversionException );
  TEST_THROW( Utility::fromPropertyTree<std::vector<double> >( ptree.get_child( "value" ), unused_children ),
              Utility::PropertyTreeConversionException );
  TEST_THROW( Utility::fromPropertyTree<std::vector<std::string> >( ptree.get_child( "value" ), unused_children ),
              Utility::PropertyTreeConversionException );
  
  Utility::VariantVector vector =
    Utility::fromPropertyTree<Utility::VariantVector>( ptree.get_child( "value" ), unused_children );

  TEST_EQUALITY_CONST( vector.size(), 1 );
  TEST_EQUALITY_CONST( vector.front().toBool(), true );
  TEST_EQUALITY_CONST( unused_children.size(), 0 );

  std::vector<int> int_vector =
    Utility::fromPropertyTree<std::vector<int> >( ptree.get_child( "inline array" ) );

  TEST_EQUALITY_CONST( int_vector.size(), 3 );
  TEST_EQUALITY_CONST( int_vector[0], -1 );
  TEST_EQUALITY_CONST( int_vector[1], 0 );
  TEST_EQUALITY_CONST( int_vector[2], 1 );

  std::vector<double> double_vector =
    Utility::fromPropertyTree<std::vector<double> >( ptree.get_child( "inline array" ) );

  TEST_EQUALITY_CONST( double_vector.size(), 3 );
  TEST_EQUALITY_CONST( double_vector[0], -1.0 );
  TEST_EQUALITY_CONST( double_vector[1], 0.0 );
  TEST_EQUALITY_CONST( double_vector[2], 1.0 );

  std::vector<std::string> string_vector =
    Utility::fromPropertyTree<std::vector<std::string> >( ptree.get_child( "inline array" ) );

  TEST_EQUALITY_CONST( string_vector.size(), 3 );
  TEST_EQUALITY_CONST( string_vector[0], "-1" );
  TEST_EQUALITY_CONST( string_vector[1], "0" );
  TEST_EQUALITY_CONST( string_vector[2], "1" );
  
  vector = Utility::fromPropertyTree<Utility::VariantVector>( ptree.get_child( "inline array" ) );

  TEST_EQUALITY_CONST( vector.size(), 3 );
  TEST_EQUALITY_CONST( vector[0].toInt(), -1 );
  TEST_EQUALITY_CONST( vector[1].toInt(), 0 );
  TEST_EQUALITY_CONST( vector[2].toInt(), 1 );

  int_vector =  Utility::fromPropertyTree<std::vector<int> >( ptree.get_child( "json array" ) );

  TEST_EQUALITY_CONST( int_vector.size(), 3 );
  TEST_EQUALITY_CONST( int_vector[0], -1 );
  TEST_EQUALITY_CONST( int_vector[1], 0 );
  TEST_EQUALITY_CONST( int_vector[2], 1 );

  double_vector = Utility::fromPropertyTree<std::vector<double> >( ptree.get_child( "json array" ) );

  TEST_EQUALITY_CONST( double_vector.size(), 3 );
  TEST_EQUALITY_CONST( double_vector[0], -1.0 );
  TEST_EQUALITY_CONST( double_vector[1], 0.0 );
  TEST_EQUALITY_CONST( double_vector[2], 1.0 );

  string_vector = Utility::fromPropertyTree<std::vector<std::string> >( ptree.get_child( "json array" ) );

  TEST_EQUALITY_CONST( string_vector.size(), 3 );
  TEST_EQUALITY_CONST( string_vector[0], "-1" );
  TEST_EQUALITY_CONST( string_vector[1], "0" );
  TEST_EQUALITY_CONST( string_vector[2], "1" );

  vector = Utility::fromPropertyTree<Utility::VariantVector>( ptree.get_child( "json array" ) );

  TEST_EQUALITY_CONST( vector.size(), 3 );
  TEST_EQUALITY_CONST( vector[0].toInt(), -1 );
  TEST_EQUALITY_CONST( vector[1].toInt(), 0 );
  TEST_EQUALITY_CONST( vector[2].toInt(), 1 );

  // Convert the nodes to deques
  TEST_THROW( Utility::fromPropertyTree<std::deque<int> >( ptree, unused_children ),
              Utility::PropertyTreeConversionException );
  TEST_THROW( Utility::fromPropertyTree<std::deque<double> >( ptree, unused_children ),
              Utility::PropertyTreeConversionException );
  TEST_THROW( Utility::fromPropertyTree<std::deque<std::string> >( ptree, unused_children ),
              Utility::PropertyTreeConversionException );              
  TEST_THROW( Utility::fromPropertyTree<Utility::VariantDeque>( ptree, unused_children ),
              Utility::PropertyTreeConversionException );

  TEST_THROW( Utility::fromPropertyTree<std::deque<int> >( ptree.get_child( "value" ), unused_children ),
              Utility::PropertyTreeConversionException );
  TEST_THROW( Utility::fromPropertyTree<std::deque<double> >( ptree.get_child( "value" ), unused_children ),
              Utility::PropertyTreeConversionException );
  TEST_THROW( Utility::fromPropertyTree<std::deque<std::string> >( ptree.get_child( "value" ), unused_children ),
              Utility::PropertyTreeConversionException );

  Utility::VariantDeque deque =
    Utility::fromPropertyTree<Utility::VariantDeque>( ptree.get_child( "value" ), unused_children );

  TEST_EQUALITY_CONST( deque.size(), 1 );
  TEST_EQUALITY_CONST( deque.front().toBool(), true );
  TEST_EQUALITY_CONST( unused_children.size(), 0 );

  std::deque<int> int_deque =
    Utility::fromPropertyTree<std::deque<int> >( ptree.get_child( "inline array" ) );

  TEST_EQUALITY_CONST( int_deque.size(), 3 );
  TEST_EQUALITY_CONST( int_deque.front(), -1 );
  TEST_EQUALITY_CONST( int_deque.back(), 1 );

  std::deque<double> double_deque =
    Utility::fromPropertyTree<std::deque<double> >( ptree.get_child( "inline array" ) );

  TEST_EQUALITY_CONST( double_deque.size(), 3 );
  TEST_EQUALITY_CONST( double_deque.front(), -1.0 );
  TEST_EQUALITY_CONST( double_deque.back(), 1.0 );

  std::deque<std::string> string_deque =
    Utility::fromPropertyTree<std::deque<std::string> >( ptree.get_child( "inline array" ) );

  TEST_EQUALITY_CONST( string_deque.size(), 3 );
  TEST_EQUALITY_CONST( string_deque.front(), "-1" );
  TEST_EQUALITY_CONST( string_deque.back(), "1" );

  deque = Utility::fromPropertyTree<Utility::VariantDeque>( ptree.get_child( "inline array" ) );

  TEST_EQUALITY_CONST( deque.size(), 3 );
  TEST_EQUALITY_CONST( deque.front().toInt(), -1 );
  TEST_EQUALITY_CONST( deque.back().toInt(), 1 );

  int_deque =  Utility::fromPropertyTree<std::deque<int> >( ptree.get_child( "json array" ) );

  TEST_EQUALITY_CONST( int_deque.size(), 3 );
  TEST_EQUALITY_CONST( int_deque.front(), -1 );
  TEST_EQUALITY_CONST( int_deque.back(), 1 );

  double_deque = Utility::fromPropertyTree<std::deque<double> >( ptree.get_child( "json array" ) );

  TEST_EQUALITY_CONST( double_deque.size(), 3 );
  TEST_EQUALITY_CONST( double_deque.front(), -1.0 );
  TEST_EQUALITY_CONST( double_deque.back(), 1.0 );

  string_deque = Utility::fromPropertyTree<std::deque<std::string> >( ptree.get_child( "json array" ) );

  TEST_EQUALITY_CONST( string_deque.size(), 3 );
  TEST_EQUALITY_CONST( string_deque.front(), "-1" );
  TEST_EQUALITY_CONST( string_deque.back(), "1" );

  deque = Utility::fromPropertyTree<Utility::VariantDeque>( ptree.get_child( "json array" ) );

  TEST_EQUALITY_CONST( deque.size(), 3 );
  TEST_EQUALITY_CONST( deque.front().toInt(), -1 );
  TEST_EQUALITY_CONST( deque.back().toInt(), 1 );

  // Convert the nodes to lists
  TEST_THROW( Utility::fromPropertyTree<std::list<int> >( ptree, unused_children ),
              Utility::PropertyTreeConversionException );
  TEST_THROW( Utility::fromPropertyTree<std::list<double> >( ptree, unused_children ),
              Utility::PropertyTreeConversionException );
  TEST_THROW( Utility::fromPropertyTree<std::list<std::string> >( ptree, unused_children ),
              Utility::PropertyTreeConversionException );              
  TEST_THROW( Utility::fromPropertyTree<Utility::VariantList>( ptree ),
              Utility::PropertyTreeConversionException );

  TEST_THROW( Utility::fromPropertyTree<std::list<int> >( ptree.get_child( "value" ), unused_children ),
              Utility::PropertyTreeConversionException );
  TEST_THROW( Utility::fromPropertyTree<std::list<double> >( ptree.get_child( "value" ), unused_children ),
              Utility::PropertyTreeConversionException );
  TEST_THROW( Utility::fromPropertyTree<std::list<std::string> >( ptree.get_child( "value" ), unused_children ),
              Utility::PropertyTreeConversionException );

  Utility::VariantList list =
    Utility::fromPropertyTree<Utility::VariantList>( ptree.get_child( "value" ), unused_children );

  TEST_EQUALITY_CONST( list.size(), 1 );
  TEST_EQUALITY_CONST( list.front().toBool(), true );
  TEST_EQUALITY_CONST( unused_children.size(), 0 );

  std::list<int> int_list =
    Utility::fromPropertyTree<std::list<int> >( ptree.get_child( "inline array" ) );

  TEST_EQUALITY_CONST( int_list.size(), 3 );
  TEST_EQUALITY_CONST( int_list.front(), -1 );
  TEST_EQUALITY_CONST( int_list.back(), 1 );

  std::list<double> double_list =
    Utility::fromPropertyTree<std::list<double> >( ptree.get_child( "inline array" ) );

  TEST_EQUALITY_CONST( double_list.size(), 3 );
  TEST_EQUALITY_CONST( double_list.front(), -1.0 );
  TEST_EQUALITY_CONST( double_list.back(), 1.0 );

  std::list<std::string> string_list =
    Utility::fromPropertyTree<std::list<std::string> >( ptree.get_child( "inline array" ) );

  TEST_EQUALITY_CONST( string_list.size(), 3 );
  TEST_EQUALITY_CONST( string_list.front(), "-1" );
  TEST_EQUALITY_CONST( string_list.back(), "1" );

  list = Utility::fromPropertyTree<Utility::VariantList>( ptree.get_child( "inline array" ) );

  TEST_EQUALITY_CONST( list.size(), 3 );
  TEST_EQUALITY_CONST( list.front().toInt(), -1 );
  TEST_EQUALITY_CONST( list.back().toInt(), 1 );

  int_list =  Utility::fromPropertyTree<std::list<int> >( ptree.get_child( "json array" ) );

  TEST_EQUALITY_CONST( int_list.size(), 3 );
  TEST_EQUALITY_CONST( int_list.front(), -1 );
  TEST_EQUALITY_CONST( int_list.back(), 1 );

  double_list = Utility::fromPropertyTree<std::list<double> >( ptree.get_child( "json array" ) );

  TEST_EQUALITY_CONST( double_list.size(), 3 );
  TEST_EQUALITY_CONST( double_list.front(), -1.0 );
  TEST_EQUALITY_CONST( double_list.back(), 1.0 );

  string_list = Utility::fromPropertyTree<std::list<std::string> >( ptree.get_child( "json array" ) );

  TEST_EQUALITY_CONST( string_list.size(), 3 );
  TEST_EQUALITY_CONST( string_list.front(), "-1" );
  TEST_EQUALITY_CONST( string_list.back(), "1" );

  list = Utility::fromPropertyTree<Utility::VariantList>( ptree.get_child( "json array" ) );

  TEST_EQUALITY_CONST( list.size(), 3 );
  TEST_EQUALITY_CONST( list.front().toInt(), -1 );
  TEST_EQUALITY_CONST( list.back().toInt(), 1 );

  // Convert the nodes to forward lists
  TEST_THROW( Utility::fromPropertyTree<std::forward_list<int> >( ptree, unused_children ),
              Utility::PropertyTreeConversionException );
  TEST_THROW( Utility::fromPropertyTree<std::forward_list<double> >( ptree, unused_children ),
              Utility::PropertyTreeConversionException );
  TEST_THROW( Utility::fromPropertyTree<std::forward_list<std::string> >( ptree, unused_children ),
              Utility::PropertyTreeConversionException );              
  TEST_THROW( Utility::fromPropertyTree<Utility::VariantForwardList>( ptree, unused_children ),
              Utility::PropertyTreeConversionException );

  TEST_THROW( Utility::fromPropertyTree<std::forward_list<int> >( ptree.get_child( "value" ), unused_children ),
              Utility::PropertyTreeConversionException );
  TEST_THROW( Utility::fromPropertyTree<std::forward_list<double> >( ptree.get_child( "value" ), unused_children ),
              Utility::PropertyTreeConversionException );
  TEST_THROW( Utility::fromPropertyTree<std::forward_list<std::string> >( ptree.get_child( "value" ), unused_children ),
              Utility::PropertyTreeConversionException );

  Utility::VariantForwardList forward_list =
    Utility::fromPropertyTree<Utility::VariantForwardList>( ptree.get_child( "value" ), unused_children );

  TEST_EQUALITY_CONST( std::distance(forward_list.begin(), forward_list.end()), 1 );
  TEST_EQUALITY_CONST( forward_list.front().toBool(), true );
  TEST_EQUALITY_CONST( unused_children.size(), 0 );

  std::forward_list<int> int_forward_list =
    Utility::fromPropertyTree<std::forward_list<int> >( ptree.get_child( "inline array" ) );

  TEST_EQUALITY_CONST( std::distance(int_forward_list.begin(), int_forward_list.end()), 3 );
  TEST_EQUALITY_CONST( int_forward_list.front(), -1 );

  std::forward_list<double> double_forward_list =
    Utility::fromPropertyTree<std::forward_list<double> >( ptree.get_child( "inline array" ) );

  TEST_EQUALITY_CONST( std::distance(double_forward_list.begin(), double_forward_list.end()), 3 );
  TEST_EQUALITY_CONST( double_forward_list.front(), -1.0 );

  std::forward_list<std::string> string_forward_list =
    Utility::fromPropertyTree<std::forward_list<std::string> >( ptree.get_child( "inline array" ) );

  TEST_EQUALITY_CONST( std::distance(string_forward_list.begin(), string_forward_list.end()), 3 );
  TEST_EQUALITY_CONST( string_forward_list.front(), "-1" );

  forward_list = Utility::fromPropertyTree<Utility::VariantForwardList>( ptree.get_child( "inline array" ) );

  TEST_EQUALITY_CONST( std::distance(forward_list.begin(), forward_list.end()), 3 );
  TEST_EQUALITY_CONST( forward_list.front().toInt(), -1 );

  int_forward_list =  Utility::fromPropertyTree<std::forward_list<int> >( ptree.get_child( "json array" ) );

  TEST_EQUALITY_CONST( std::distance(int_forward_list.begin(), int_forward_list.end()), 3 );
  TEST_EQUALITY_CONST( int_forward_list.front(), -1 );

  double_forward_list = Utility::fromPropertyTree<std::forward_list<double> >( ptree.get_child( "json array" ) );

  TEST_EQUALITY_CONST( std::distance(double_forward_list.begin(), double_forward_list.end()), 3 );
  TEST_EQUALITY_CONST( double_forward_list.front(), -1.0 );

  string_forward_list = Utility::fromPropertyTree<std::forward_list<std::string> >( ptree.get_child( "json array" ) );

  TEST_EQUALITY_CONST( std::distance(string_forward_list.begin(), string_forward_list.end()), 3 );
  TEST_EQUALITY_CONST( string_forward_list.front(), "-1" );

  forward_list = Utility::fromPropertyTree<Utility::VariantForwardList>( ptree.get_child( "json array" ) );

  TEST_EQUALITY_CONST( std::distance(forward_list.begin(), forward_list.end()), 3 );
  TEST_EQUALITY_CONST( forward_list.front().toInt(), -1 );

  // Convert the nodes to sets
  TEST_THROW( Utility::fromPropertyTree<std::set<int> >( ptree, unused_children ),
              Utility::PropertyTreeConversionException );
  TEST_THROW( Utility::fromPropertyTree<std::set<double> >( ptree, unused_children ),
              Utility::PropertyTreeConversionException );
  TEST_THROW( Utility::fromPropertyTree<std::set<std::string> >( ptree, unused_children ),
              Utility::PropertyTreeConversionException );              

  TEST_THROW( Utility::fromPropertyTree<std::set<int> >( ptree.get_child( "value" ), unused_children ),
              Utility::PropertyTreeConversionException );
  TEST_THROW( Utility::fromPropertyTree<std::set<double> >( ptree.get_child( "value" ), unused_children ),
              Utility::PropertyTreeConversionException );
  TEST_THROW( Utility::fromPropertyTree<std::set<std::string> >( ptree.get_child( "value" ), unused_children ),
              Utility::PropertyTreeConversionException );

  std::set<int> int_set =
    Utility::fromPropertyTree<std::set<int> >( ptree.get_child( "inline array" ) );

  TEST_EQUALITY_CONST( int_set.size(), 3 );
  TEST_EQUALITY_CONST( int_set.count( -1 ), 1 );
  TEST_EQUALITY_CONST( int_set.count( 0 ), 1 );
  TEST_EQUALITY_CONST( int_set.count( 1 ), 1 );

  std::set<double> double_set =
    Utility::fromPropertyTree<std::set<double> >( ptree.get_child( "inline array" ) );

  TEST_EQUALITY_CONST( double_set.size(), 3 );
  TEST_EQUALITY_CONST( double_set.count( -1.0 ), 1 );
  TEST_EQUALITY_CONST( double_set.count( 0.0 ), 1 );
  TEST_EQUALITY_CONST( double_set.count( 1.0 ), 1 );

  std::set<std::string> string_set =
    Utility::fromPropertyTree<std::set<std::string> >( ptree.get_child( "inline array" ) );

  TEST_EQUALITY_CONST( string_set.size(), 3 );
  TEST_EQUALITY_CONST( string_set.count( "-1" ), 1 );
  TEST_EQUALITY_CONST( string_set.count( "0" ), 1 );
  TEST_EQUALITY_CONST( string_set.count( "1" ), 1 );

  int_set =  Utility::fromPropertyTree<std::set<int> >( ptree.get_child( "json array" ) );

  TEST_EQUALITY_CONST( int_set.size(), 3 );
  TEST_EQUALITY_CONST( int_set.count( -1 ), 1 );
  TEST_EQUALITY_CONST( int_set.count( 0 ), 1 );
  TEST_EQUALITY_CONST( int_set.count( 1 ), 1 );

  double_set = Utility::fromPropertyTree<std::set<double> >( ptree.get_child( "json array" ) );

  TEST_EQUALITY_CONST( double_set.size(), 3 );
  TEST_EQUALITY_CONST( double_set.count( -1.0 ), 1 );
  TEST_EQUALITY_CONST( double_set.count( 0.0 ), 1 );
  TEST_EQUALITY_CONST( double_set.count( 1.0 ), 1 );

  string_set = Utility::fromPropertyTree<std::set<std::string> >( ptree.get_child( "json array" ) );

  TEST_EQUALITY_CONST( string_set.size(), 3 );
  TEST_EQUALITY_CONST( string_set.count( "-1" ), 1 );
  TEST_EQUALITY_CONST( string_set.count( "0" ), 1 );
  TEST_EQUALITY_CONST( string_set.count( "1" ), 1 );

  // Convert the nodes to unordered sets
  TEST_THROW( Utility::fromPropertyTree<std::unordered_set<int> >( ptree, unused_children ),
              Utility::PropertyTreeConversionException );
  TEST_THROW( Utility::fromPropertyTree<std::unordered_set<double> >( ptree, unused_children ),
              Utility::PropertyTreeConversionException );
  TEST_THROW( Utility::fromPropertyTree<std::unordered_set<std::string> >( ptree, unused_children ),
              Utility::PropertyTreeConversionException );              

  TEST_THROW( Utility::fromPropertyTree<std::unordered_set<int> >( ptree.get_child( "value" ), unused_children ),
              Utility::PropertyTreeConversionException );
  TEST_THROW( Utility::fromPropertyTree<std::unordered_set<double> >( ptree.get_child( "value" ), unused_children ),
              Utility::PropertyTreeConversionException );
  TEST_THROW( Utility::fromPropertyTree<std::unordered_set<std::string> >( ptree.get_child( "value" ), unused_children ),
              Utility::PropertyTreeConversionException );

  std::unordered_set<int> int_unordered_set =
    Utility::fromPropertyTree<std::unordered_set<int> >( ptree.get_child( "inline array" ) );

  TEST_EQUALITY_CONST( int_unordered_set.size(), 3 );
  TEST_EQUALITY_CONST( int_unordered_set.count( -1 ), 1 );
  TEST_EQUALITY_CONST( int_unordered_set.count( 0 ), 1 );
  TEST_EQUALITY_CONST( int_unordered_set.count( 1 ), 1 );

  std::unordered_set<double> double_unordered_set =
    Utility::fromPropertyTree<std::unordered_set<double> >( ptree.get_child( "inline array" ) );

  TEST_EQUALITY_CONST( double_unordered_set.size(), 3 );
  TEST_EQUALITY_CONST( double_unordered_set.count( -1.0 ), 1 );
  TEST_EQUALITY_CONST( double_unordered_set.count( 0.0 ), 1 );
  TEST_EQUALITY_CONST( double_unordered_set.count( 1.0 ), 1 );

  std::unordered_set<std::string> string_unordered_set =
    Utility::fromPropertyTree<std::unordered_set<std::string> >( ptree.get_child( "inline array" ) );

  TEST_EQUALITY_CONST( string_unordered_set.size(), 3 );
  TEST_EQUALITY_CONST( string_unordered_set.count( "-1" ), 1 );
  TEST_EQUALITY_CONST( string_unordered_set.count( "0" ), 1 );
  TEST_EQUALITY_CONST( string_unordered_set.count( "1" ), 1 );

  int_unordered_set =  Utility::fromPropertyTree<std::unordered_set<int> >( ptree.get_child( "json array" ) );

  TEST_EQUALITY_CONST( int_unordered_set.size(), 3 );
  TEST_EQUALITY_CONST( int_unordered_set.count( -1 ), 1 );
  TEST_EQUALITY_CONST( int_unordered_set.count( 0 ), 1 );
  TEST_EQUALITY_CONST( int_unordered_set.count( 1 ), 1 );

  double_unordered_set = Utility::fromPropertyTree<std::unordered_set<double> >( ptree.get_child( "json array" ) );

  TEST_EQUALITY_CONST( double_unordered_set.size(), 3 );
  TEST_EQUALITY_CONST( double_unordered_set.count( -1.0 ), 1 );
  TEST_EQUALITY_CONST( double_unordered_set.count( 0.0 ), 1 );
  TEST_EQUALITY_CONST( double_unordered_set.count( 1.0 ), 1 );

  string_unordered_set = Utility::fromPropertyTree<std::unordered_set<std::string> >( ptree.get_child( "json array" ) );

  TEST_EQUALITY_CONST( string_unordered_set.size(), 3 );
  TEST_EQUALITY_CONST( string_unordered_set.count( "-1" ), 1 );
  TEST_EQUALITY_CONST( string_unordered_set.count( "0" ), 1 );
  TEST_EQUALITY_CONST( string_unordered_set.count( "1" ), 1 );
}

//---------------------------------------------------------------------------//
// Check that a property tree node can be converted to an associative container
TEUCHOS_UNIT_TEST( PropertyTree, fromPropertyTree_associative_container )
{
  Utility::PropertyTree ptree;

  ptree.put( "-1", -1 );
  ptree.put( "0", 0 );
  ptree.put( "1", 1 );

  std::map<int,int> int_int_map =
    Utility::fromPropertyTree<std::map<int,int> >( ptree );

  TEST_EQUALITY_CONST( int_int_map.size(), 3 );
  TEST_EQUALITY_CONST( int_int_map[-1], -1 );
  TEST_EQUALITY_CONST( int_int_map[0], 0 );
  TEST_EQUALITY_CONST( int_int_map[1], 1 );

  std::unordered_map<int,int> int_int_unordered_map =
    Utility::fromPropertyTree<std::unordered_map<int,int> >( ptree );

  TEST_EQUALITY_CONST( int_int_unordered_map.size(), 3 );
  TEST_EQUALITY_CONST( int_int_unordered_map[-1], -1 );
  TEST_EQUALITY_CONST( int_int_unordered_map[0], 0 );
  TEST_EQUALITY_CONST( int_int_unordered_map[1], 1 );

  std::map<std::string,double> string_double_map =
    Utility::fromPropertyTree<std::map<std::string,double> >( ptree );

  TEST_EQUALITY_CONST( string_double_map.size(), 3 );
  TEST_EQUALITY_CONST( string_double_map["-1"], -1.0 );
  TEST_EQUALITY_CONST( string_double_map["0"], 0.0 );
  TEST_EQUALITY_CONST( string_double_map["1"], 1.0 );

  std::unordered_map<std::string,double> string_double_unordered_map =
    Utility::fromPropertyTree<std::unordered_map<std::string,double> >( ptree );

  TEST_EQUALITY_CONST( string_double_unordered_map.size(), 3 );
  TEST_EQUALITY_CONST( string_double_unordered_map["-1"], -1.0 );
  TEST_EQUALITY_CONST( string_double_unordered_map["0"], 0.0 );
  TEST_EQUALITY_CONST( string_double_unordered_map["1"], 1.0 );

  TEST_THROW( (Utility::fromPropertyTree<std::map<int,std::vector<int> > >( ptree )),
              Utility::PropertyTreeConversionException );
  TEST_THROW( (Utility::fromPropertyTree<std::map<std::string,std::vector<double> > >( ptree )),
              Utility::PropertyTreeConversionException );

  // Create a property tree with array (both inline and JSON) values
  ptree.clear();

  ptree.put( "-1", std::vector<int>({-1,0,1}) );
  ptree.put_child( "0", Utility::toPropertyTree( std::vector<int>({-1,1}), false ) );
  ptree.put( "1", std::vector<int>({0}) );

  TEST_THROW( (Utility::fromPropertyTree<std::map<int,int> >( ptree )),
              Utility::PropertyTreeConversionException );
  TEST_THROW( (Utility::fromPropertyTree<std::map<std::string,double> >( ptree )),
              Utility::PropertyTreeConversionException );
  
  std::map<int,std::vector<int> > int_vector_int_map =
    Utility::fromPropertyTree<std::map<int,std::vector<int> > >( ptree );

  TEST_EQUALITY_CONST( int_vector_int_map.size(), 3 );
  TEST_EQUALITY_CONST( int_vector_int_map.count( -1 ), 1 );
  TEST_COMPARE_CONTAINERS( int_vector_int_map[-1], std::vector<int>({-1,0,1}) );
  TEST_EQUALITY_CONST( int_vector_int_map.count( 0 ), 1 );
  TEST_COMPARE_CONTAINERS( int_vector_int_map[0], std::vector<int>({-1,1}) );
  TEST_EQUALITY_CONST( int_vector_int_map.count( 1 ), 1 );
  TEST_COMPARE_CONTAINERS( int_vector_int_map[1], std::vector<int>({0}) );

  std::unordered_map<int,std::vector<int> > int_vector_int_unordered_map =
    Utility::fromPropertyTree<std::unordered_map<int,std::vector<int> > >( ptree );

  TEST_EQUALITY_CONST( int_vector_int_unordered_map.size(), 3 );
  TEST_EQUALITY_CONST( int_vector_int_unordered_map.count( -1 ), 1 );
  TEST_COMPARE_CONTAINERS( int_vector_int_unordered_map[-1], std::vector<int>({-1,0,1}) );
  TEST_EQUALITY_CONST( int_vector_int_unordered_map.count( 0 ), 1 );
  TEST_COMPARE_CONTAINERS( int_vector_int_unordered_map[0], std::vector<int>({-1,1}) );
  TEST_EQUALITY_CONST( int_vector_int_unordered_map.count( 1 ), 1 );
  TEST_COMPARE_CONTAINERS( int_vector_int_unordered_map[1], std::vector<int>({0}) );

  std::map<std::string,std::vector<double> > string_vector_double_map =
    Utility::fromPropertyTree<std::map<std::string,std::vector<double> > >( ptree );

  TEST_EQUALITY_CONST( string_vector_double_map.size(), 3 );
  TEST_EQUALITY_CONST( string_vector_double_map.count( "-1" ), 1 );
  TEST_COMPARE_CONTAINERS( string_vector_double_map["-1"], std::vector<double>({-1.,0.,1.}) );
  TEST_EQUALITY_CONST( string_vector_double_map.count( "0" ), 1 );
  TEST_COMPARE_CONTAINERS( string_vector_double_map["0"], std::vector<double>({-1.,1.}) );
  TEST_EQUALITY_CONST( string_vector_double_map.count( "1" ), 1 );
  TEST_COMPARE_CONTAINERS( string_vector_double_map["1"], std::vector<double>({0.}) );

  std::unordered_map<std::string,std::vector<double> > string_vector_double_unordered_map =
    Utility::fromPropertyTree<std::unordered_map<std::string,std::vector<double> > >( ptree );

  TEST_EQUALITY_CONST( string_vector_double_unordered_map.size(), 3 );
  TEST_EQUALITY_CONST( string_vector_double_unordered_map.count( "-1" ), 1 );
  TEST_COMPARE_CONTAINERS( string_vector_double_unordered_map["-1"], std::vector<double>({-1.,0.,1.}) );
  TEST_EQUALITY_CONST( string_vector_double_unordered_map.count( "0" ), 1 );
  TEST_COMPARE_CONTAINERS( string_vector_double_unordered_map["0"], std::vector<double>({-1.,1.}) );
  TEST_EQUALITY_CONST( string_vector_double_unordered_map.count( "1" ), 1 );
  TEST_COMPARE_CONTAINERS( string_vector_double_unordered_map["1"], std::vector<double>({0.}) );

  // Create an invalid property tree (JSON Array)
  ptree = Utility::toPropertyTree( std::vector<int>({-1,0,1}), false );

  TEST_THROW( (Utility::fromPropertyTree<std::map<int,int> >( ptree )),
              Utility::PropertyTreeConversionException );
  TEST_THROW( (Utility::fromPropertyTree<std::map<std::string,double> >( ptree )),
              Utility::PropertyTreeConversionException );
  TEST_THROW( (Utility::fromPropertyTree<std::unordered_map<int,int> >( ptree )),
              Utility::PropertyTreeConversionException );
  TEST_THROW( (Utility::fromPropertyTree<std::unordered_map<std::string,double> >( ptree )),
              Utility::PropertyTreeConversionException );
  TEST_THROW( (Utility::fromPropertyTree<std::map<int,std::vector<int> > >( ptree )),
              Utility::PropertyTreeConversionException );
  TEST_THROW( (Utility::fromPropertyTree<std::map<std::string,std::vector<double> > >( ptree )),
              Utility::PropertyTreeConversionException );
  TEST_THROW( (Utility::fromPropertyTree<std::unordered_map<int,std::vector<int> > >( ptree )),
              Utility::PropertyTreeConversionException );
  TEST_THROW( (Utility::fromPropertyTree<std::unordered_map<std::string,std::vector<double> > >( ptree )),
              Utility::PropertyTreeConversionException );

  // Create an invalid property tree (repeated keys)
  ptree.put( "-1", -1 );
  ptree.add( "-1", 0 );

  TEST_THROW( (Utility::fromPropertyTree<std::map<int,int> >( ptree )),
              Utility::PropertyTreeConversionException );
  TEST_THROW( (Utility::fromPropertyTree<std::map<std::string,double> >( ptree )),
              Utility::PropertyTreeConversionException );
  TEST_THROW( (Utility::fromPropertyTree<std::unordered_map<int,int> >( ptree )),
              Utility::PropertyTreeConversionException );
  TEST_THROW( (Utility::fromPropertyTree<std::unordered_map<std::string,double> >( ptree )),
              Utility::PropertyTreeConversionException );

  // Create a property tree with nested trees
  ptree.clear();
  
  ptree.put_child( "-1", Utility::toPropertyTree( std::map<int,int>({std::make_pair(-1,-1),std::make_pair(0,0)}), false ) );
  ptree.put_child( "0", Utility::toPropertyTree( std::map<int,int>({std::make_pair(-1,-1),std::make_pair(1,1)}), true ) );
  ptree.put_child( "1", Utility::toPropertyTree( std::map<int,int>({std::make_pair(0,0),std::make_pair(1,1)}), false ) );

  std::map<int,std::map<int,int> > int_int_int_map_map =
    Utility::fromPropertyTree<decltype(int_int_int_map_map)>( ptree );

  TEST_EQUALITY_CONST( int_int_int_map_map.size(), 3 );
  
  TEST_EQUALITY_CONST( int_int_int_map_map.count( -1 ), 1 );
  TEST_EQUALITY_CONST( int_int_int_map_map[-1].size(), 2 );
  TEST_EQUALITY_CONST( int_int_int_map_map[-1].count( -1 ), 1 );
  TEST_EQUALITY_CONST( int_int_int_map_map[-1][-1], -1 );
  TEST_EQUALITY_CONST( int_int_int_map_map[-1].count( 0 ), 1 );
  TEST_EQUALITY_CONST( int_int_int_map_map[-1][0], 0 );

  TEST_EQUALITY_CONST( int_int_int_map_map.count( 0 ), 1 );
  TEST_EQUALITY_CONST( int_int_int_map_map[0].size(), 2 );
  TEST_EQUALITY_CONST( int_int_int_map_map[0].count( -1 ), 1 );
  TEST_EQUALITY_CONST( int_int_int_map_map[0][-1], -1 );
  TEST_EQUALITY_CONST( int_int_int_map_map[0].count( 1 ), 1 );
  TEST_EQUALITY_CONST( int_int_int_map_map[0][1], 1 );

  TEST_EQUALITY_CONST( int_int_int_map_map.count( 1 ), 1 );
  TEST_EQUALITY_CONST( int_int_int_map_map[1].size(), 2 );
  TEST_EQUALITY_CONST( int_int_int_map_map[1].count( 0 ), 1 );
  TEST_EQUALITY_CONST( int_int_int_map_map[1][0], 0 );
  TEST_EQUALITY_CONST( int_int_int_map_map[1].count( 1 ), 1 );
  TEST_EQUALITY_CONST( int_int_int_map_map[1][1], 1 );

  // Create a property tree with an inline nested map
  ptree.clear();
  ptree = Utility::toPropertyTree( int_int_int_map_map, true );

  int_int_int_map_map.clear();
  int_int_int_map_map = Utility::fromPropertyTree<decltype(int_int_int_map_map)>( ptree );

  TEST_EQUALITY_CONST( int_int_int_map_map.size(), 3 );
  
  TEST_EQUALITY_CONST( int_int_int_map_map.count( -1 ), 1 );
  TEST_EQUALITY_CONST( int_int_int_map_map[-1].size(), 2 );
  TEST_EQUALITY_CONST( int_int_int_map_map[-1].count( -1 ), 1 );
  TEST_EQUALITY_CONST( int_int_int_map_map[-1][-1], -1 );
  TEST_EQUALITY_CONST( int_int_int_map_map[-1].count( 0 ), 1 );
  TEST_EQUALITY_CONST( int_int_int_map_map[-1][0], 0 );

  TEST_EQUALITY_CONST( int_int_int_map_map.count( 0 ), 1 );
  TEST_EQUALITY_CONST( int_int_int_map_map[0].size(), 2 );
  TEST_EQUALITY_CONST( int_int_int_map_map[0].count( -1 ), 1 );
  TEST_EQUALITY_CONST( int_int_int_map_map[0][-1], -1 );
  TEST_EQUALITY_CONST( int_int_int_map_map[0].count( 1 ), 1 );
  TEST_EQUALITY_CONST( int_int_int_map_map[0][1], 1 );

  TEST_EQUALITY_CONST( int_int_int_map_map.count( 1 ), 1 );
  TEST_EQUALITY_CONST( int_int_int_map_map[1].size(), 2 );
  TEST_EQUALITY_CONST( int_int_int_map_map[1].count( 0 ), 1 );
  TEST_EQUALITY_CONST( int_int_int_map_map[1][0], 0 );
  TEST_EQUALITY_CONST( int_int_int_map_map[1].count( 1 ), 1 );
  TEST_EQUALITY_CONST( int_int_int_map_map[1][1], 1 );
}

//---------------------------------------------------------------------------//
// Check that a property tree node can be converted to an associative container
TEUCHOS_UNIT_TEST( PropertyTree, fromPropertyTree_VariantMap )
{
  // Create a property tree with standard nodes and JSON array nodes
  Utility::PropertyTree ptree;

  // Construct level 1 nodes
  {
    ptree.add( "repeated_value", true );
    ptree.add( "repeated_value", std::vector<double>({-1.0, 0.0, 1.0}) );
    ptree.put( "inline array", std::vector<int>({-1, 0, 1}) );

    Utility::PropertyTree level_1_ptree;
    
    Utility::PropertyTree json_array_element;

    json_array_element.put( "", -1 );

    level_1_ptree.push_back( std::make_pair( "", json_array_element ) );
    
    json_array_element.put( "", 0 );

    level_1_ptree.push_back( std::make_pair( "", json_array_element ) );
    
    json_array_element.put( "", 1 );

    level_1_ptree.push_back( std::make_pair( "", json_array_element ) );

    ptree.add_child( "json array", level_1_ptree );
    ptree.add_child( "repeated_value", level_1_ptree );

    level_1_ptree.clear();

    // Construct level 2 nodes
    level_1_ptree.put( "level 2 string", "test string" );
    level_1_ptree.put( "level 2 inline array", std::vector<std::string>({"test", "string", "array"}) );

    ptree.add_child( "child tree", level_1_ptree );
    ptree.add_child( "repeated_value", level_1_ptree );
  }

  // Convert the nodes to a VariantMap
  std::vector<std::string> unused_children;
  
  Utility::VariantMap map =
    Utility::fromPropertyTree<Utility::VariantMap>( ptree, unused_children );
  
  TEST_EQUALITY_CONST( map.size(), 4 );
  TEST_EQUALITY_CONST( unused_children.size(), 0 );
  TEST_EQUALITY_CONST( map["inline array"].toVector().size(), 3 );
  TEST_EQUALITY_CONST( map["inline array"].toVector()[0].toInt(), -1 );
  TEST_EQUALITY_CONST( map["inline array"].toVector()[1].toInt(), 0 );
  TEST_EQUALITY_CONST( map["inline array"].toVector()[2].toInt(), 1 );
  TEST_EQUALITY_CONST( map["json array"].toVector().size(), 3 );
  TEST_EQUALITY_CONST( map["json array"].toVector()[0].toInt(), -1 );
  TEST_EQUALITY_CONST( map["json array"].toVector()[1].toInt(), 0 );
  TEST_EQUALITY_CONST( map["json array"].toVector()[2].toInt(), 1 );
  TEST_EQUALITY_CONST( map["child tree"].toMap().size(), 2 );
  TEST_EQUALITY_CONST( map["child tree"].toMap()["level 2 string"].toString(), "test string" );
  TEST_EQUALITY_CONST( map["child tree"].toMap()["level 2 inline array"].compactify().toString(), "{test,string,array}" );
  TEST_EQUALITY_CONST( map["repeated_value"].toVector().size(), 9 );
  TEST_EQUALITY_CONST( map["repeated_value"].toVector()[0].toBool(), true );
  TEST_EQUALITY_CONST( map["repeated_value"].toVector()[1].toDouble(), -1.0 );
  TEST_EQUALITY_CONST( map["repeated_value"].toVector()[2].toDouble(), 0.0 );
  TEST_EQUALITY_CONST( map["repeated_value"].toVector()[3].toDouble(), 1.0 );
  TEST_EQUALITY_CONST( map["repeated_value"].toVector()[4].toInt(), -1 );
  TEST_EQUALITY_CONST( map["repeated_value"].toVector()[5].toInt(), 0 );
  TEST_EQUALITY_CONST( map["repeated_value"].toVector()[6].toInt(), 1 );
  TEST_EQUALITY_CONST( (map["repeated_value"].toVector()[7].toType<std::pair<std::string,Utility::Variant> >().first), "level 2 inline array" );
  TEST_EQUALITY_CONST( (map["repeated_value"].toVector()[7].toType<std::pair<std::string,Utility::Variant> >().second.compactify().toString()), "{test,string,array}" );
  TEST_EQUALITY_CONST( (map["repeated_value"].toVector()[8].toType<std::pair<std::string,std::string> >().first), "level 2 string" );
  TEST_EQUALITY_CONST( (map["repeated_value"].toVector()[8].toType<std::pair<std::string,std::string> >().second), "test string" );
  
  // Reorder the ptree contents
  ptree.clear();

  // Construct level 1 nodes
  {
    ptree.add( "repeated_value", std::vector<double>({-1.0, 0.0, 1.0}) );
    ptree.add( "repeated_value", true );
    ptree.put( "inline array", std::vector<int>({-1, 0, 1}) );

    Utility::PropertyTree level_1_ptree;
    
    Utility::PropertyTree json_array_element;

    json_array_element.put( "", -1 );

    level_1_ptree.push_back( std::make_pair( "", json_array_element ) );
    
    json_array_element.put( "", 0 );

    level_1_ptree.push_back( std::make_pair( "", json_array_element ) );
    
    json_array_element.put( "", 1 );

    level_1_ptree.push_back( std::make_pair( "", json_array_element ) );

    ptree.add_child( "json array", level_1_ptree );
    ptree.add_child( "repeated_value", level_1_ptree );

    level_1_ptree.clear();

    // Construct level 2 nodes
    level_1_ptree.put( "level 2 string", "test string" );
    level_1_ptree.put( "level 2 inline array", std::vector<std::string>({"test", "string", "array"}) );

    ptree.add_child( "child tree", level_1_ptree );
    ptree.add_child( "repeated_value", level_1_ptree );
  }

  // Convert the nodes to a VariantMap
  map = Utility::fromPropertyTree<Utility::VariantMap>( ptree );

  TEST_EQUALITY_CONST( map.size(), 4 );
  TEST_EQUALITY_CONST( map["inline array"].toVector().size(), 3 );
  TEST_EQUALITY_CONST( map["inline array"].toVector()[0].toInt(), -1 );
  TEST_EQUALITY_CONST( map["inline array"].toVector()[1].toInt(), 0 );
  TEST_EQUALITY_CONST( map["inline array"].toVector()[2].toInt(), 1 );
  TEST_EQUALITY_CONST( map["json array"].toVector().size(), 3 );
  TEST_EQUALITY_CONST( map["json array"].toVector()[0].toInt(), -1 );
  TEST_EQUALITY_CONST( map["json array"].toVector()[1].toInt(), 0 );
  TEST_EQUALITY_CONST( map["json array"].toVector()[2].toInt(), 1 );
  TEST_EQUALITY_CONST( map["child tree"].toMap().size(), 2 );
  TEST_EQUALITY_CONST( map["child tree"].toMap()["level 2 string"].toString(), "test string" );
  TEST_EQUALITY_CONST( map["child tree"].toMap()["level 2 inline array"].compactify().toString(), "{test,string,array}" );
  TEST_EQUALITY_CONST( map["repeated_value"].toVector().size(), 9 );
  TEST_EQUALITY_CONST( map["repeated_value"].toVector()[0].toDouble(), -1.0 );
  TEST_EQUALITY_CONST( map["repeated_value"].toVector()[1].toDouble(), 0.0 );
  TEST_EQUALITY_CONST( map["repeated_value"].toVector()[2].toDouble(), 1.0 );
  TEST_EQUALITY_CONST( map["repeated_value"].toVector()[3].toBool(), true );
  TEST_EQUALITY_CONST( map["repeated_value"].toVector()[4].toInt(), -1 );
  TEST_EQUALITY_CONST( map["repeated_value"].toVector()[5].toInt(), 0 );
  TEST_EQUALITY_CONST( map["repeated_value"].toVector()[6].toInt(), 1 );
  TEST_EQUALITY_CONST( (map["repeated_value"].toVector()[7].toType<std::pair<std::string,Utility::Variant> >().first), "level 2 inline array" );
  TEST_EQUALITY_CONST( (map["repeated_value"].toVector()[7].toType<std::pair<std::string,Utility::Variant> >().second.compactify().toString()), "{test,string,array}" );
  TEST_EQUALITY_CONST( (map["repeated_value"].toVector()[8].toType<std::pair<std::string,std::string> >().first), "level 2 string" );
  TEST_EQUALITY_CONST( (map["repeated_value"].toVector()[8].toType<std::pair<std::string,std::string> >().second), "test string" );

  // Reorder the ptree contents
  ptree.clear();

  // Construct level 1 nodes
  {
    Utility::PropertyTree level_1_ptree;
    
    Utility::PropertyTree json_array_element;

    json_array_element.put( "", -1 );

    level_1_ptree.push_back( std::make_pair( "", json_array_element ) );
    
    json_array_element.put( "", 0 );

    level_1_ptree.push_back( std::make_pair( "", json_array_element ) );
    
    json_array_element.put( "", 1 );

    level_1_ptree.push_back( std::make_pair( "", json_array_element ) );

    ptree.add_child( "json array", level_1_ptree );
    ptree.add_child( "repeated_value", level_1_ptree );

    ptree.add( "repeated_value", std::vector<double>({-1.0, 0.0, 1.0}) );
    ptree.add( "repeated_value", true );
    ptree.put( "inline array", std::vector<int>({-1, 0, 1}) );

    level_1_ptree.clear();

    // Construct level 2 nodes
    level_1_ptree.put( "level 2 string", "test string" );
    level_1_ptree.put( "level 2 inline array", std::vector<std::string>({"test", "string", "array"}) );

    ptree.add_child( "child tree", level_1_ptree );
    ptree.add_child( "repeated_value", level_1_ptree );
  }

  // Convert the nodes to a VariantMap
  map = Utility::fromPropertyTree<Utility::VariantMap>( ptree );

  TEST_EQUALITY_CONST( map.size(), 4 );
  TEST_EQUALITY_CONST( map["inline array"].toVector().size(), 3 );
  TEST_EQUALITY_CONST( map["inline array"].toVector()[0].toInt(), -1 );
  TEST_EQUALITY_CONST( map["inline array"].toVector()[1].toInt(), 0 );
  TEST_EQUALITY_CONST( map["inline array"].toVector()[2].toInt(), 1 );
  TEST_EQUALITY_CONST( map["json array"].toVector().size(), 3 );
  TEST_EQUALITY_CONST( map["json array"].toVector()[0].toInt(), -1 );
  TEST_EQUALITY_CONST( map["json array"].toVector()[1].toInt(), 0 );
  TEST_EQUALITY_CONST( map["json array"].toVector()[2].toInt(), 1 );
  TEST_EQUALITY_CONST( map["child tree"].toMap().size(), 2 );
  TEST_EQUALITY_CONST( map["child tree"].toMap()["level 2 string"].toString(), "test string" );
  TEST_EQUALITY_CONST( map["child tree"].toMap()["level 2 inline array"].compactify().toString(), "{test,string,array}" );
  TEST_EQUALITY_CONST( map["repeated_value"].toVector().size(), 9 );
  TEST_EQUALITY_CONST( map["repeated_value"].toVector()[0].toInt(), -1 );
  TEST_EQUALITY_CONST( map["repeated_value"].toVector()[1].toInt(), 0 );
  TEST_EQUALITY_CONST( map["repeated_value"].toVector()[2].toInt(), 1 );
  TEST_EQUALITY_CONST( map["repeated_value"].toVector()[3].toDouble(), -1.0 );
  TEST_EQUALITY_CONST( map["repeated_value"].toVector()[4].toDouble(), 0.0 );
  TEST_EQUALITY_CONST( map["repeated_value"].toVector()[5].toDouble(), 1.0 );
  TEST_EQUALITY_CONST( map["repeated_value"].toVector()[6].toBool(), true );
  TEST_EQUALITY_CONST( (map["repeated_value"].toVector()[7].toType<std::pair<std::string,Utility::Variant> >().first), "level 2 inline array" );
  TEST_EQUALITY_CONST( (map["repeated_value"].toVector()[7].toType<std::pair<std::string,Utility::Variant> >().second.compactify().toString()), "{test,string,array}" );
  TEST_EQUALITY_CONST( (map["repeated_value"].toVector()[8].toType<std::pair<std::string,std::string> >().first), "level 2 string" );
  TEST_EQUALITY_CONST( (map["repeated_value"].toVector()[8].toType<std::pair<std::string,std::string> >().second), "test string" );

  // Reorder the ptree contents
  ptree.clear();

  // Construct level 1 nodes
  {
    Utility::PropertyTree level_1_ptree;

    // Construct level 2 nodes
    level_1_ptree.put( "level 2 string", "test string" );
    level_1_ptree.put( "level 2 inline array", std::vector<std::string>({"test", "string", "array"}) );

    ptree.add_child( "child tree", level_1_ptree );
    ptree.add_child( "repeated_value", level_1_ptree );
    
    level_1_ptree.clear();
    
    Utility::PropertyTree json_array_element;

    json_array_element.put( "", -1 );

    level_1_ptree.push_back( std::make_pair( "", json_array_element ) );
    
    json_array_element.put( "", 0 );

    level_1_ptree.push_back( std::make_pair( "", json_array_element ) );
    
    json_array_element.put( "", 1 );

    level_1_ptree.push_back( std::make_pair( "", json_array_element ) );

    ptree.add_child( "json array", level_1_ptree );
    ptree.add_child( "repeated_value", level_1_ptree );

    ptree.add( "repeated_value", std::vector<double>({-1.0, 0.0, 1.0}) );
    ptree.add( "repeated_value", true );
    ptree.put( "inline array", std::vector<int>({-1, 0, 1}) );
  }

  // Convert the nodes to a VariantMap
  map = Utility::fromPropertyTree<Utility::VariantMap>( ptree );

  TEST_EQUALITY_CONST( map.size(), 4 );
  TEST_EQUALITY_CONST( map["inline array"].toVector().size(), 3 );
  TEST_EQUALITY_CONST( map["inline array"].toVector()[0].toInt(), -1 );
  TEST_EQUALITY_CONST( map["inline array"].toVector()[1].toInt(), 0 );
  TEST_EQUALITY_CONST( map["inline array"].toVector()[2].toInt(), 1 );
  TEST_EQUALITY_CONST( map["json array"].toVector().size(), 3 );
  TEST_EQUALITY_CONST( map["json array"].toVector()[0].toInt(), -1 );
  TEST_EQUALITY_CONST( map["json array"].toVector()[1].toInt(), 0 );
  TEST_EQUALITY_CONST( map["json array"].toVector()[2].toInt(), 1 );
  TEST_EQUALITY_CONST( map["child tree"].toMap().size(), 2 );
  TEST_EQUALITY_CONST( map["child tree"].toMap()["level 2 string"].toString(), "test string" );
  TEST_EQUALITY_CONST( map["child tree"].toMap()["level 2 inline array"].compactify().toString(), "{test,string,array}" );
  TEST_EQUALITY_CONST( map["repeated_value"].toVector().size(), 9 );
  TEST_EQUALITY_CONST( (map["repeated_value"].toVector()[0].toType<std::pair<std::string,Utility::Variant> >().first), "level 2 inline array" );
  TEST_EQUALITY_CONST( (map["repeated_value"].toVector()[0].toType<std::pair<std::string,Utility::Variant> >().second.compactify().toString()), "{test,string,array}" );
  TEST_EQUALITY_CONST( (map["repeated_value"].toVector()[1].toType<std::pair<std::string,std::string> >().first), "level 2 string" );
  TEST_EQUALITY_CONST( (map["repeated_value"].toVector()[1].toType<std::pair<std::string,std::string> >().second), "test string" );
  TEST_EQUALITY_CONST( map["repeated_value"].toVector()[2].toInt(), -1 );
  TEST_EQUALITY_CONST( map["repeated_value"].toVector()[3].toInt(), 0 );
  TEST_EQUALITY_CONST( map["repeated_value"].toVector()[4].toInt(), 1 );
  TEST_EQUALITY_CONST( map["repeated_value"].toVector()[5].toDouble(), -1.0 );
  TEST_EQUALITY_CONST( map["repeated_value"].toVector()[6].toDouble(), 0.0 );
  TEST_EQUALITY_CONST( map["repeated_value"].toVector()[7].toDouble(), 1.0 );
  TEST_EQUALITY_CONST( map["repeated_value"].toVector()[8].toBool(), true );

  TEST_THROW( Utility::fromPropertyTree<Utility::VariantMap>( ptree.get_child( "json array" ) ),
              Utility::PropertyTreeConversionException );

  TEST_NOTHROW( boost::property_tree::write_json( "test_maps.json", ptree ) );
}

//---------------------------------------------------------------------------//
// Check that a property tree can be converted to a string
TEUCHOS_UNIT_TEST( PropertyTree, toString )
{
  Utility::PropertyTree ptree;

  TEST_EQUALITY_CONST( Utility::toString( ptree ), "{}" );

  ptree.add( "repeated_value", true );

  TEST_EQUALITY_CONST( Utility::toString( ptree ), "{\"repeated_value\":\"true\"}" );

  ptree.add( "repeated_value", std::vector<double>({-1.0, 0.0, 1.0}) );

  TEST_EQUALITY_CONST( Utility::toString( ptree ), "{\"repeated_value\":\"true\",\"repeated_value\":\"{-1.000000000000000000e+00, 0.000000000000000000e+00, 1.000000000000000000e+00}\"}" );
  
  ptree.put( "inline array", std::vector<int>({-1, 0, 1}) );

  TEST_EQUALITY_CONST( Utility::toString( ptree ), "{\"repeated_value\":\"true\",\"repeated_value\":\"{-1.000000000000000000e+00, 0.000000000000000000e+00, 1.000000000000000000e+00}\",\"inline array\":\"{-1, 0, 1}\"}" );
  
  // Construct level 1 nodes
  {
    Utility::PropertyTree level_1_ptree;

    // Construct level 2 nodes
    level_1_ptree.put( "level 2 string", "test string" );
    level_1_ptree.put( "level 2 inline array", std::vector<std::string>({"test", "string", "array"}) );

    ptree.add_child( "child tree", level_1_ptree );
  }

  TEST_EQUALITY_CONST( Utility::toString( ptree ), "{\"repeated_value\":\"true\",\"repeated_value\":\"{-1.000000000000000000e+00, 0.000000000000000000e+00, 1.000000000000000000e+00}\",\"inline array\":\"{-1, 0, 1}\",\"child tree\":{\"level 2 string\":\"test string\",\"level 2 inline array\":\"{test, string, array}\"}}" );

  {
    Utility::PropertyTree level_1_ptree, json_array_element;

    json_array_element.put( "", -1 );

    level_1_ptree.push_back( std::make_pair( "", json_array_element ) );
    
    json_array_element.put( "", 0 );

    level_1_ptree.push_back( std::make_pair( "", json_array_element ) );
    
    json_array_element.put( "", 1 );

    level_1_ptree.push_back( std::make_pair( "", json_array_element ) );

    ptree.add_child( "json array", level_1_ptree );
  }

  TEST_EQUALITY_CONST( Utility::toString( ptree ), "{\"repeated_value\":\"true\",\"repeated_value\":\"{-1.000000000000000000e+00, 0.000000000000000000e+00, 1.000000000000000000e+00}\",\"inline array\":\"{-1, 0, 1}\",\"child tree\":{\"level 2 string\":\"test string\",\"level 2 inline array\":\"{test, string, array}\"},\"json array\":[\"-1\",\"0\",\"1\"]}" );
}

//---------------------------------------------------------------------------//
// Check that a property tree can be placed in a stream
TEUCHOS_UNIT_TEST( PropertyTree, toStream )
{
  Utility::PropertyTree ptree;

  std::ostringstream oss;

  Utility::toStream( oss, ptree );
  
  TEST_EQUALITY_CONST( boost::algorithm::trim_copy(oss.str()), "{}" );

  oss.str( "" );
  oss.clear();

  ptree.add( "repeated_value", true );

  Utility::toStream( oss, ptree );

  TEST_EQUALITY_CONST( boost::algorithm::trim_copy(oss.str()), "{\"repeated_value\":\"true\"}" );

  oss.str( "" );
  oss.clear();

  ptree.add( "repeated_value", std::vector<double>({-1.0, 0.0, 1.0}) );

  Utility::toStream( oss, ptree );

  TEST_EQUALITY_CONST( boost::algorithm::trim_copy(oss.str()), "{\"repeated_value\":\"true\",\"repeated_value\":\"{-1.000000000000000000e+00, 0.000000000000000000e+00, 1.000000000000000000e+00}\"}" );

  oss.str( "" );
  oss.clear();
  
  ptree.put( "inline array", std::vector<int>({-1, 0, 1}) );

  Utility::toStream( oss, ptree );

  TEST_EQUALITY_CONST( boost::algorithm::trim_copy(oss.str()), "{\"repeated_value\":\"true\",\"repeated_value\":\"{-1.000000000000000000e+00, 0.000000000000000000e+00, 1.000000000000000000e+00}\",\"inline array\":\"{-1, 0, 1}\"}" );

  oss.str( "" );
  oss.clear();
  
  // Construct level 1 nodes
  {
    Utility::PropertyTree level_1_ptree;

    // Construct level 2 nodes
    level_1_ptree.put( "level 2 string", "test string" );
    level_1_ptree.put( "level 2 inline array", std::vector<std::string>({"test", "string", "array"}) );

    ptree.add_child( "child tree", level_1_ptree );
  }

  Utility::toStream( oss, ptree );

  TEST_EQUALITY_CONST( boost::algorithm::trim_copy(oss.str()), "{\"repeated_value\":\"true\",\"repeated_value\":\"{-1.000000000000000000e+00, 0.000000000000000000e+00, 1.000000000000000000e+00}\",\"inline array\":\"{-1, 0, 1}\",\"child tree\":{\"level 2 string\":\"test string\",\"level 2 inline array\":\"{test, string, array}\"}}" );

  oss.str( "" );
  oss.clear();

  {
    Utility::PropertyTree level_1_ptree, json_array_element;

    json_array_element.put( "", -1 );

    level_1_ptree.push_back( std::make_pair( "", json_array_element ) );
    
    json_array_element.put( "", 0 );

    level_1_ptree.push_back( std::make_pair( "", json_array_element ) );
    
    json_array_element.put( "", 1 );

    level_1_ptree.push_back( std::make_pair( "", json_array_element ) );

    ptree.add_child( "json array", level_1_ptree );
  }

  Utility::toStream( oss, ptree );

  TEST_EQUALITY_CONST( boost::algorithm::trim_copy(oss.str()), "{\"repeated_value\":\"true\",\"repeated_value\":\"{-1.000000000000000000e+00, 0.000000000000000000e+00, 1.000000000000000000e+00}\",\"inline array\":\"{-1, 0, 1}\",\"child tree\":{\"level 2 string\":\"test string\",\"level 2 inline array\":\"{test, string, array}\"},\"json array\":[\"-1\",\"0\",\"1\"]}" );
}

//---------------------------------------------------------------------------//
// Check that a property tree can be placed in a stream
TEUCHOS_UNIT_TEST( PropertyTree, ostream_operator )
{
  Utility::PropertyTree ptree;

  std::ostringstream oss;

  oss << ptree;
  
  TEST_EQUALITY_CONST( boost::algorithm::trim_copy(oss.str()), "{}" );

  oss.str( "" );
  oss.clear();

  ptree.add( "repeated_value", true );

  oss << ptree;

  TEST_EQUALITY_CONST( boost::algorithm::trim_copy(oss.str()), "{\"repeated_value\":\"true\"}" );

  oss.str( "" );
  oss.clear();

  ptree.add( "repeated_value", std::vector<double>({-1.0, 0.0, 1.0}) );

  oss << ptree;

  TEST_EQUALITY_CONST( boost::algorithm::trim_copy(oss.str()), "{\"repeated_value\":\"true\",\"repeated_value\":\"{-1.000000000000000000e+00, 0.000000000000000000e+00, 1.000000000000000000e+00}\"}" );

  oss.str( "" );
  oss.clear();
  
  ptree.put( "inline array", std::vector<int>({-1, 0, 1}) );

  oss << ptree;

  TEST_EQUALITY_CONST( boost::algorithm::trim_copy(oss.str()), "{\"repeated_value\":\"true\",\"repeated_value\":\"{-1.000000000000000000e+00, 0.000000000000000000e+00, 1.000000000000000000e+00}\",\"inline array\":\"{-1, 0, 1}\"}" );

  oss.str( "" );
  oss.clear();
  
  // Construct level 1 nodes
  {
    Utility::PropertyTree level_1_ptree;

    // Construct level 2 nodes
    level_1_ptree.put( "level 2 string", "test string" );
    level_1_ptree.put( "level 2 inline array", std::vector<std::string>({"test", "string", "array"}) );

    ptree.add_child( "child tree", level_1_ptree );
  }

  oss << ptree;

  TEST_EQUALITY_CONST( boost::algorithm::trim_copy(oss.str()), "{\"repeated_value\":\"true\",\"repeated_value\":\"{-1.000000000000000000e+00, 0.000000000000000000e+00, 1.000000000000000000e+00}\",\"inline array\":\"{-1, 0, 1}\",\"child tree\":{\"level 2 string\":\"test string\",\"level 2 inline array\":\"{test, string, array}\"}}" );

  oss.str( "" );
  oss.clear();

  {
    Utility::PropertyTree level_1_ptree, json_array_element;

    json_array_element.put( "", -1 );

    level_1_ptree.push_back( std::make_pair( "", json_array_element ) );
    
    json_array_element.put( "", 0 );

    level_1_ptree.push_back( std::make_pair( "", json_array_element ) );
    
    json_array_element.put( "", 1 );

    level_1_ptree.push_back( std::make_pair( "", json_array_element ) );

    ptree.add_child( "json array", level_1_ptree );
  }

  oss << ptree;

  TEST_EQUALITY_CONST( boost::algorithm::trim_copy(oss.str()), "{\"repeated_value\":\"true\",\"repeated_value\":\"{-1.000000000000000000e+00, 0.000000000000000000e+00, 1.000000000000000000e+00}\",\"inline array\":\"{-1, 0, 1}\",\"child tree\":{\"level 2 string\":\"test string\",\"level 2 inline array\":\"{test, string, array}\"},\"json array\":[\"-1\",\"0\",\"1\"]}" );
}

//---------------------------------------------------------------------------//
// Check that a property tree can be created from a string
TEUCHOS_UNIT_TEST( PropertyTree, fromString )
{
  Utility::PropertyTree ptree = Utility::fromString<Utility::PropertyTree>( "{}" );

  TEST_EQUALITY_CONST( ptree.size(), 0 );

  ptree = Utility::fromString<Utility::PropertyTree>( "{\"repeated_value\":\"true\"}" );

  TEST_EQUALITY_CONST( ptree.size(), 1 );
  TEST_EQUALITY_CONST( ptree.get<bool>( "repeated_value" ), true );

  ptree = Utility::fromString<Utility::PropertyTree>( "{\"repeated_value\":\"true\",\"repeated_value\":\"{-1.000000000000000000e+00, 0.000000000000000000e+00, 1.000000000000000000e+00}\"}" );

  TEST_EQUALITY_CONST( ptree.size(), 2 );
  TEST_EQUALITY_CONST( ptree.count( "repeated_value" ), 2 );

  Utility::VariantMap map =
    Utility::fromPropertyTree<Utility::VariantMap>( ptree );

  TEST_EQUALITY_CONST( map.size(), 1 );
  TEST_EQUALITY_CONST( map["repeated_value"].toVector().size(), 4 );
  TEST_EQUALITY_CONST( map["repeated_value"].toVector()[0].toBool(), true );
  TEST_EQUALITY_CONST( map["repeated_value"].toVector()[1].toDouble(), -1.0 );
  TEST_EQUALITY_CONST( map["repeated_value"].toVector()[2].toDouble(), 0.0 );
  TEST_EQUALITY_CONST( map["repeated_value"].toVector()[3].toDouble(), 1.0 );

  ptree = Utility::fromString<Utility::PropertyTree>( "{\"repeated_value\":\"true\",\"repeated_value\":\"{-1.000000000000000000e+00, 0.000000000000000000e+00, 1.000000000000000000e+00}\",\"inline array\":\"{-1, 0, 1}\"}" );
  
  map = Utility::fromPropertyTree<Utility::VariantMap>( ptree );

  TEST_EQUALITY_CONST( map.size(), 2 );
  TEST_EQUALITY_CONST( map["repeated_value"].toVector().size(), 4 );
  TEST_EQUALITY_CONST( map["repeated_value"].toVector()[0].toBool(), true );
  TEST_EQUALITY_CONST( map["repeated_value"].toVector()[1].toDouble(), -1.0 );
  TEST_EQUALITY_CONST( map["repeated_value"].toVector()[2].toDouble(), 0.0 );
  TEST_EQUALITY_CONST( map["repeated_value"].toVector()[3].toDouble(), 1.0 );
  TEST_EQUALITY_CONST( map["inline array"].toVector().size(), 3 );
  TEST_EQUALITY_CONST( map["inline array"].toVector()[0].toInt(), -1 );
  TEST_EQUALITY_CONST( map["inline array"].toVector()[1].toInt(), 0 );
  TEST_EQUALITY_CONST( map["inline array"].toVector()[2].toInt(), 1 );

  ptree = Utility::fromString<Utility::PropertyTree>( "{\"repeated_value\":\"true\",\"repeated_value\":\"{-1.000000000000000000e+00, 0.000000000000000000e+00, 1.000000000000000000e+00}\",\"inline array\":\"{-1, 0, 1}\",\"child tree\":{\"level 2 string\":\"test string\",\"level 2 inline array\":\"{test, string, array}\"}}" );
  
  map = Utility::fromPropertyTree<Utility::VariantMap>( ptree );

  TEST_EQUALITY_CONST( map.size(), 3 );
  TEST_EQUALITY_CONST( map["repeated_value"].toVector().size(), 4 );
  TEST_EQUALITY_CONST( map["repeated_value"].toVector()[0].toBool(), true );
  TEST_EQUALITY_CONST( map["repeated_value"].toVector()[1].toDouble(), -1.0 );
  TEST_EQUALITY_CONST( map["repeated_value"].toVector()[2].toDouble(), 0.0 );
  TEST_EQUALITY_CONST( map["repeated_value"].toVector()[3].toDouble(), 1.0 );
  TEST_EQUALITY_CONST( map["inline array"].toVector().size(), 3 );
  TEST_EQUALITY_CONST( map["inline array"].toVector()[0].toInt(), -1 );
  TEST_EQUALITY_CONST( map["inline array"].toVector()[1].toInt(), 0 );
  TEST_EQUALITY_CONST( map["inline array"].toVector()[2].toInt(), 1 );
  TEST_EQUALITY_CONST( map["child tree"].toMap().size(), 2 );
  TEST_EQUALITY_CONST( map["child tree"].toMap()["level 2 string"].toString(), "test string" );
  TEST_EQUALITY_CONST( map["child tree"].toMap()["level 2 inline array"].compactify().toString(), "{test,string,array}" );

  ptree = Utility::fromString<Utility::PropertyTree>( "{\"repeated_value\":\"true\",\"repeated_value\":\"{-1.000000000000000000e+00, 0.000000000000000000e+00, 1.000000000000000000e+00}\",\"inline array\":\"{-1, 0, 1}\",\"child tree\":{\"level 2 string\":\"test string\",\"level 2 inline array\":\"{test, string, array}\"},\"json array\":[\"-1\",\"0\",\"1\"]}" );

  map = Utility::fromPropertyTree<Utility::VariantMap>( ptree );

  TEST_EQUALITY_CONST( map.size(), 4 );
  TEST_EQUALITY_CONST( map["repeated_value"].toVector().size(), 4 );
  TEST_EQUALITY_CONST( map["repeated_value"].toVector()[0].toBool(), true );
  TEST_EQUALITY_CONST( map["repeated_value"].toVector()[1].toDouble(), -1.0 );
  TEST_EQUALITY_CONST( map["repeated_value"].toVector()[2].toDouble(), 0.0 );
  TEST_EQUALITY_CONST( map["repeated_value"].toVector()[3].toDouble(), 1.0 );
  TEST_EQUALITY_CONST( map["inline array"].toVector().size(), 3 );
  TEST_EQUALITY_CONST( map["inline array"].toVector()[0].toInt(), -1 );
  TEST_EQUALITY_CONST( map["inline array"].toVector()[1].toInt(), 0 );
  TEST_EQUALITY_CONST( map["inline array"].toVector()[2].toInt(), 1 );
  TEST_EQUALITY_CONST( map["child tree"].toMap().size(), 2 );
  TEST_EQUALITY_CONST( map["child tree"].toMap()["level 2 string"].toString(), "test string" );
  TEST_EQUALITY_CONST( map["child tree"].toMap()["level 2 inline array"].compactify().toString(), "{test,string,array}" );
  TEST_EQUALITY_CONST( map["json array"].toVector().size(), 3 );
  TEST_EQUALITY_CONST( map["json array"].toVector()[0].toInt(), -1 );
  TEST_EQUALITY_CONST( map["json array"].toVector()[1].toInt(), 0 );
  TEST_EQUALITY_CONST( map["json array"].toVector()[2].toInt(), 1 );
}

//---------------------------------------------------------------------------//
// Check that a property tree can be extracted from a stream
TEUCHOS_UNIT_TEST( PropertyTree, fromStream )
{
  Utility::PropertyTree ptree;
  
  std::istringstream iss( "{}" );

  Utility::fromStream( iss, ptree );

  TEST_EQUALITY_CONST( ptree.size(), 0 );

  iss.str( "{\"repeated_value\":\"true\"}" );
  iss.clear();

  Utility::fromStream( iss, ptree );

  TEST_EQUALITY_CONST( ptree.size(), 1 );
  TEST_EQUALITY_CONST( ptree.get<bool>( "repeated_value" ), true );

  iss.str( "{\"repeated_value\":\"true\",\"repeated_value\":\"{-1.000000000000000000e+00, 0.000000000000000000e+00, 1.000000000000000000e+00}\"}" );
  iss.clear();

  Utility::fromStream( iss, ptree );

  TEST_EQUALITY_CONST( ptree.size(), 2 );
  TEST_EQUALITY_CONST( ptree.count( "repeated_value" ), 2 );

  Utility::VariantMap map = Utility::fromPropertyTree<Utility::VariantMap>( ptree );

  TEST_EQUALITY_CONST( map.size(), 1 );
  TEST_EQUALITY_CONST( map["repeated_value"].toVector().size(), 4 );
  TEST_EQUALITY_CONST( map["repeated_value"].toVector()[0].toBool(), true );
  TEST_EQUALITY_CONST( map["repeated_value"].toVector()[1].toDouble(), -1.0 );
  TEST_EQUALITY_CONST( map["repeated_value"].toVector()[2].toDouble(), 0.0 );
  TEST_EQUALITY_CONST( map["repeated_value"].toVector()[3].toDouble(), 1.0 );

  iss.str( "{\"repeated_value\":\"true\",\"repeated_value\":\"{-1.000000000000000000e+00, 0.000000000000000000e+00, 1.000000000000000000e+00}\",\"inline array\":\"{-1, 0, 1}\"}" );

  Utility::fromStream( iss, ptree );
  
  map = Utility::fromPropertyTree<Utility::VariantMap>( ptree );

  TEST_EQUALITY_CONST( map.size(), 2 );
  TEST_EQUALITY_CONST( map["repeated_value"].toVector().size(), 4 );
  TEST_EQUALITY_CONST( map["repeated_value"].toVector()[0].toBool(), true );
  TEST_EQUALITY_CONST( map["repeated_value"].toVector()[1].toDouble(), -1.0 );
  TEST_EQUALITY_CONST( map["repeated_value"].toVector()[2].toDouble(), 0.0 );
  TEST_EQUALITY_CONST( map["repeated_value"].toVector()[3].toDouble(), 1.0 );
  TEST_EQUALITY_CONST( map["inline array"].toVector().size(), 3 );
  TEST_EQUALITY_CONST( map["inline array"].toVector()[0].toInt(), -1 );
  TEST_EQUALITY_CONST( map["inline array"].toVector()[1].toInt(), 0 );
  TEST_EQUALITY_CONST( map["inline array"].toVector()[2].toInt(), 1 );

  iss.str( "{\"repeated_value\":\"true\",\"repeated_value\":\"{-1.000000000000000000e+00, 0.000000000000000000e+00, 1.000000000000000000e+00}\",\"inline array\":\"{-1, 0, 1}\",\"child tree\":{\"level 2 string\":\"test string\",\"level 2 inline array\":\"{test, string, array}\"}}" );
  iss.clear();

  Utility::fromStream( iss, ptree );
  
  map = Utility::fromPropertyTree<Utility::VariantMap>( ptree );

  TEST_EQUALITY_CONST( map.size(), 3 );
  TEST_EQUALITY_CONST( map["repeated_value"].toVector().size(), 4 );
  TEST_EQUALITY_CONST( map["repeated_value"].toVector()[0].toBool(), true );
  TEST_EQUALITY_CONST( map["repeated_value"].toVector()[1].toDouble(), -1.0 );
  TEST_EQUALITY_CONST( map["repeated_value"].toVector()[2].toDouble(), 0.0 );
  TEST_EQUALITY_CONST( map["repeated_value"].toVector()[3].toDouble(), 1.0 );
  TEST_EQUALITY_CONST( map["inline array"].toVector().size(), 3 );
  TEST_EQUALITY_CONST( map["inline array"].toVector()[0].toInt(), -1 );
  TEST_EQUALITY_CONST( map["inline array"].toVector()[1].toInt(), 0 );
  TEST_EQUALITY_CONST( map["inline array"].toVector()[2].toInt(), 1 );
  TEST_EQUALITY_CONST( map["child tree"].toMap().size(), 2 );
  TEST_EQUALITY_CONST( map["child tree"].toMap()["level 2 string"].toString(), "test string" );
  TEST_EQUALITY_CONST( map["child tree"].toMap()["level 2 inline array"].compactify().toString(), "{test,string,array}" );

  iss.str( "{\"repeated_value\":\"true\",\"repeated_value\":\"{-1.000000000000000000e+00, 0.000000000000000000e+00, 1.000000000000000000e+00}\",\"inline array\":\"{-1, 0, 1}\",\"child tree\":{\"level 2 string\":\"test string\",\"level 2 inline array\":\"{test, string, array}\"},\"json array\":[\"-1\",\"0\",\"1\"]}" );
  iss.clear();

  Utility::fromStream( iss, ptree );

  map = Utility::fromPropertyTree<Utility::VariantMap>( ptree );

  TEST_EQUALITY_CONST( map.size(), 4 );
  TEST_EQUALITY_CONST( map["repeated_value"].toVector().size(), 4 );
  TEST_EQUALITY_CONST( map["repeated_value"].toVector()[0].toBool(), true );
  TEST_EQUALITY_CONST( map["repeated_value"].toVector()[1].toDouble(), -1.0 );
  TEST_EQUALITY_CONST( map["repeated_value"].toVector()[2].toDouble(), 0.0 );
  TEST_EQUALITY_CONST( map["repeated_value"].toVector()[3].toDouble(), 1.0 );
  TEST_EQUALITY_CONST( map["inline array"].toVector().size(), 3 );
  TEST_EQUALITY_CONST( map["inline array"].toVector()[0].toInt(), -1 );
  TEST_EQUALITY_CONST( map["inline array"].toVector()[1].toInt(), 0 );
  TEST_EQUALITY_CONST( map["inline array"].toVector()[2].toInt(), 1 );
  TEST_EQUALITY_CONST( map["child tree"].toMap().size(), 2 );
  TEST_EQUALITY_CONST( map["child tree"].toMap()["level 2 string"].toString(), "test string" );
  TEST_EQUALITY_CONST( map["child tree"].toMap()["level 2 inline array"].compactify().toString(), "{test,string,array}" );
  TEST_EQUALITY_CONST( map["json array"].toVector().size(), 3 );
  TEST_EQUALITY_CONST( map["json array"].toVector()[0].toInt(), -1 );
  TEST_EQUALITY_CONST( map["json array"].toVector()[1].toInt(), 0 );
  TEST_EQUALITY_CONST( map["json array"].toVector()[2].toInt(), 1 );
}

//---------------------------------------------------------------------------//
// Check that a property tree can be extracted from a stream
TEUCHOS_UNIT_TEST( PropertyTree, istream_operator )
{
  Utility::PropertyTree ptree;
  
  std::istringstream iss( "{}" );

  iss >> ptree;

  TEST_EQUALITY_CONST( ptree.size(), 0 );

  iss.str( "{\"repeated_value\":\"true\"}" );
  iss.clear();

  iss >> ptree;

  TEST_EQUALITY_CONST( ptree.size(), 1 );
  TEST_EQUALITY_CONST( ptree.get<bool>( "repeated_value" ), true );

  iss.str( "{\"repeated_value\":\"true\",\"repeated_value\":\"{-1.000000000000000000e+00, 0.000000000000000000e+00, 1.000000000000000000e+00}\"}" );
  iss.clear();

  iss >> ptree;

  TEST_EQUALITY_CONST( ptree.size(), 2 );
  TEST_EQUALITY_CONST( ptree.count( "repeated_value" ), 2 );

  Utility::VariantMap map = Utility::fromPropertyTree<Utility::VariantMap>( ptree );

  TEST_EQUALITY_CONST( map.size(), 1 );
  TEST_EQUALITY_CONST( map["repeated_value"].toVector().size(), 4 );
  TEST_EQUALITY_CONST( map["repeated_value"].toVector()[0].toBool(), true );
  TEST_EQUALITY_CONST( map["repeated_value"].toVector()[1].toDouble(), -1.0 );
  TEST_EQUALITY_CONST( map["repeated_value"].toVector()[2].toDouble(), 0.0 );
  TEST_EQUALITY_CONST( map["repeated_value"].toVector()[3].toDouble(), 1.0 );

  iss.str( "{\"repeated_value\":\"true\",\"repeated_value\":\"{-1.000000000000000000e+00, 0.000000000000000000e+00, 1.000000000000000000e+00}\",\"inline array\":\"{-1, 0, 1}\"}" );

  iss >> ptree;
  
  map = Utility::fromPropertyTree<Utility::VariantMap>( ptree );

  TEST_EQUALITY_CONST( map.size(), 2 );
  TEST_EQUALITY_CONST( map["repeated_value"].toVector().size(), 4 );
  TEST_EQUALITY_CONST( map["repeated_value"].toVector()[0].toBool(), true );
  TEST_EQUALITY_CONST( map["repeated_value"].toVector()[1].toDouble(), -1.0 );
  TEST_EQUALITY_CONST( map["repeated_value"].toVector()[2].toDouble(), 0.0 );
  TEST_EQUALITY_CONST( map["repeated_value"].toVector()[3].toDouble(), 1.0 );
  TEST_EQUALITY_CONST( map["inline array"].toVector().size(), 3 );
  TEST_EQUALITY_CONST( map["inline array"].toVector()[0].toInt(), -1 );
  TEST_EQUALITY_CONST( map["inline array"].toVector()[1].toInt(), 0 );
  TEST_EQUALITY_CONST( map["inline array"].toVector()[2].toInt(), 1 );

  iss.str( "{\"repeated_value\":\"true\",\"repeated_value\":\"{-1.000000000000000000e+00, 0.000000000000000000e+00, 1.000000000000000000e+00}\",\"inline array\":\"{-1, 0, 1}\",\"child tree\":{\"level 2 string\":\"test string\",\"level 2 inline array\":\"{test, string, array}\"}}" );
  iss.clear();

  iss >> ptree;
  
  map = Utility::fromPropertyTree<Utility::VariantMap>( ptree );

  TEST_EQUALITY_CONST( map.size(), 3 );
  TEST_EQUALITY_CONST( map["repeated_value"].toVector().size(), 4 );
  TEST_EQUALITY_CONST( map["repeated_value"].toVector()[0].toBool(), true );
  TEST_EQUALITY_CONST( map["repeated_value"].toVector()[1].toDouble(), -1.0 );
  TEST_EQUALITY_CONST( map["repeated_value"].toVector()[2].toDouble(), 0.0 );
  TEST_EQUALITY_CONST( map["repeated_value"].toVector()[3].toDouble(), 1.0 );
  TEST_EQUALITY_CONST( map["inline array"].toVector().size(), 3 );
  TEST_EQUALITY_CONST( map["inline array"].toVector()[0].toInt(), -1 );
  TEST_EQUALITY_CONST( map["inline array"].toVector()[1].toInt(), 0 );
  TEST_EQUALITY_CONST( map["inline array"].toVector()[2].toInt(), 1 );
  TEST_EQUALITY_CONST( map["child tree"].toMap().size(), 2 );
  TEST_EQUALITY_CONST( map["child tree"].toMap()["level 2 string"].toString(), "test string" );
  TEST_EQUALITY_CONST( map["child tree"].toMap()["level 2 inline array"].compactify().toString(), "{test,string,array}" );

  iss.str( "{\"repeated_value\":\"true\",\"repeated_value\":\"{-1.000000000000000000e+00, 0.000000000000000000e+00, 1.000000000000000000e+00}\",\"inline array\":\"{-1, 0, 1}\",\"child tree\":{\"level 2 string\":\"test string\",\"level 2 inline array\":\"{test, string, array}\"},\"json array\":[\"-1\",\"0\",\"1\"]}" );
  iss.clear();

  iss >> ptree;

  map = Utility::fromPropertyTree<Utility::VariantMap>( ptree );

  TEST_EQUALITY_CONST( map.size(), 4 );
  TEST_EQUALITY_CONST( map["repeated_value"].toVector().size(), 4 );
  TEST_EQUALITY_CONST( map["repeated_value"].toVector()[0].toBool(), true );
  TEST_EQUALITY_CONST( map["repeated_value"].toVector()[1].toDouble(), -1.0 );
  TEST_EQUALITY_CONST( map["repeated_value"].toVector()[2].toDouble(), 0.0 );
  TEST_EQUALITY_CONST( map["repeated_value"].toVector()[3].toDouble(), 1.0 );
  TEST_EQUALITY_CONST( map["inline array"].toVector().size(), 3 );
  TEST_EQUALITY_CONST( map["inline array"].toVector()[0].toInt(), -1 );
  TEST_EQUALITY_CONST( map["inline array"].toVector()[1].toInt(), 0 );
  TEST_EQUALITY_CONST( map["inline array"].toVector()[2].toInt(), 1 );
  TEST_EQUALITY_CONST( map["child tree"].toMap().size(), 2 );
  TEST_EQUALITY_CONST( map["child tree"].toMap()["level 2 string"].toString(), "test string" );
  TEST_EQUALITY_CONST( map["child tree"].toMap()["level 2 inline array"].compactify().toString(), "{test,string,array}" );
  TEST_EQUALITY_CONST( map["json array"].toVector().size(), 3 );
  TEST_EQUALITY_CONST( map["json array"].toVector()[0].toInt(), -1 );
  TEST_EQUALITY_CONST( map["json array"].toVector()[1].toInt(), 0 );
  TEST_EQUALITY_CONST( map["json array"].toVector()[2].toInt(), 1 );
}

//---------------------------------------------------------------------------//
// end tstPropertyTree.cpp
//---------------------------------------------------------------------------//
