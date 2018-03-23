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

// FRENSIE Includes
#include "Utility_PropertyTree.hpp"
#include "Utility_Variant.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that a property tree can convert basic values correctly
FRENSIE_UNIT_TEST( PropertyTree, convert_basic_values )
{
  // boost::property_tree::ptree ptree;
  Utility::PropertyTree ptree;

  // Store a bool
  ptree.put( "test_bool", true );

  FRENSIE_CHECK_EQUAL( ptree.get<bool>( "test_bool" ), true );
  FRENSIE_CHECK_EQUAL( ptree.get<std::string>( "test_bool" ), "true" );

  ptree.put( "test_bool", false );

  FRENSIE_CHECK_EQUAL( ptree.get<bool>( "test_bool" ), false );
  FRENSIE_CHECK_EQUAL( ptree.get<std::string>( "test_bool" ), "false" );

  // Store a short
  ptree.put( "test_short", -1 );

  FRENSIE_CHECK_EQUAL( ptree.get<short>( "test_short" ), (short)-1 );
  FRENSIE_CHECK_EQUAL( ptree.get<std::string>( "test_short" ), "-1" );

  // Store an unsigned short
  ptree.put( "test_ushort", 1 );

  FRENSIE_CHECK_EQUAL( ptree.get<ushort>( "test_ushort" ), (ushort)1 );
  FRENSIE_CHECK_EQUAL( ptree.get<std::string>( "test_ushort" ), "1" );

  // Store an int
  ptree.put( "test_int", -11111 );

  FRENSIE_CHECK_EQUAL( ptree.get<int>( "test_int" ), -11111 );
  FRENSIE_CHECK_EQUAL( ptree.get<std::string>( "test_int" ), "-11111" );

  // Store an unsigned int
  ptree.put( "test_uint", 11111 );

  FRENSIE_CHECK_EQUAL( ptree.get<unsigned int>( "test_uint" ), 11111u );
  FRENSIE_CHECK_EQUAL( ptree.get<std::string>( "test_uint" ), "11111" );

  // Store a long
  ptree.put( "test_long", -11111 );

  FRENSIE_CHECK_EQUAL( ptree.get<long>( "test_long" ), -11111l );
  FRENSIE_CHECK_EQUAL( ptree.get<std::string>( "test_long" ), "-11111" );

  // Store an unsigned long
  ptree.put( "test_ulong", 11111 );

  FRENSIE_CHECK_EQUAL( ptree.get<unsigned long>( "test_ulong" ), 11111ul );
  FRENSIE_CHECK_EQUAL( ptree.get<std::string>( "test_ulong" ), "11111" );

  // Store a long long
  ptree.put( "test_long_long", -10000000000 );

  FRENSIE_CHECK_EQUAL( ptree.get<long long>( "test_long_long" ),
                       -10000000000ll );
  FRENSIE_CHECK_EQUAL( ptree.get<std::string>( "test_long_long" ),
                       "-10000000000" );

  // Store an unsigned long long
  ptree.put( "test_ulong_long", 10000000000 );

  FRENSIE_CHECK_EQUAL( ptree.get<unsigned long long>( "test_ulong_long" ),
                       10000000000ull );
  FRENSIE_CHECK_EQUAL( ptree.get<std::string>( "test_ulong_long" ),
                       "10000000000" );

  // Store a float
  ptree.put( "test_float", -1.0f );

  FRENSIE_CHECK_EQUAL( ptree.get<float>( "test_float" ), -1.0f );
  FRENSIE_CHECK_EQUAL( ptree.get<std::string>( "test_float" ), "-1.000000000e+00" );

  ptree.put( "test_float", "-inf" );

  FRENSIE_CHECK_EQUAL( ptree.get<float>( "test_float" ),
                       -std::numeric_limits<float>::infinity() );

  ptree.put( "test_float", "-pi/2" );

  FRENSIE_CHECK_EQUAL( ptree.get<float>( "test_float" ),
                       -(float)Utility::PhysicalConstants::pi/2 );

  // Store a double
  ptree.put( "test_double", 1.0 );

  FRENSIE_CHECK_EQUAL( ptree.get<double>( "test_double" ), 1.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<std::string>( "test_double" ), "1.000000000000000000e+00" );

  ptree.put( "test_double", "Infty" );

  FRENSIE_CHECK_EQUAL( ptree.get<double>( "test_double" ),
                       std::numeric_limits<double>::infinity() );

  ptree.put( "test_double", "3pi/4" );

  FRENSIE_CHECK_EQUAL( ptree.get<double>( "test_double" ),
                       3*Utility::PhysicalConstants::pi/4 );

  // Store a char
  ptree.put( "test_char", 'A' );

  FRENSIE_CHECK_EQUAL( ptree.get<char>( "test_char" ), 'A' );
  FRENSIE_CHECK_EQUAL( ptree.get<std::string>( "test_char" ), "A" );

  // Store a c-string
  ptree.put( "test_cstring", "Test" );

  FRENSIE_CHECK_EQUAL( ptree.get<std::string>( "test_cstring" ), "Test" );

  FRENSIE_CHECK_NO_THROW( boost::property_tree::write_json( "test_basic.json", ptree ) );
}

//---------------------------------------------------------------------------//
// Check that a property tree can convert container values correctly
FRENSIE_UNIT_TEST( PropertyTree, convert_container_values )
{
  Utility::PropertyTree ptree;

  // Store a string
  ptree.put( "test_string", std::string( "STest" ) );

  FRENSIE_CHECK_EQUAL( ptree.get<std::string>( "test_string" ), "STest" );

  // Store a vector of int
  ptree.put( "test_vector_int", std::vector<int>({-1, 0, 1}) );

  FRENSIE_CHECK_EQUAL( (ptree.get<std::vector<int> >( "test_vector_int" )),
                           std::vector<int>({-1, 0, 1}) );
  FRENSIE_CHECK_EQUAL( ptree.get<std::string>( "test_vector_int" ),
                       "{-1, 0, 1}" );

  ptree.put( "test_vector_int", "{0, 3i, 10000}" );

  FRENSIE_CHECK_EQUAL( (ptree.get<std::vector<int> >( "test_vector_int" )),
                           std::vector<int>({0, 2500, 5000, 7500, 10000}) );

  // Store a vector of float
  ptree.put( "test_vector_float", std::vector<float>({-1.0f, 0.0f, 1.0f}) );

  FRENSIE_CHECK_EQUAL( (ptree.get<std::vector<float> >( "test_vector_float" )),
                           std::vector<float>({-1.0f, 0.0f, 1.0f}) );
  FRENSIE_CHECK_EQUAL( ptree.get<std::string>( "test_vector_float" ),
                       "{-1.000000000e+00, 0.000000000e+00, 1.000000000e+00}" );

  ptree.put( "test_vector_float", "{-1, 3i, 1.0}" );

  FRENSIE_CHECK_FLOATING_EQUALITY( (ptree.get<std::vector<float> >( "test_vector_float" )),
                                    std::vector<float>({-1.0f, -0.5f, 0.0f, 0.5f, 1.0f}),
                                    1e-9 );

  ptree.put( "test_vector_float", "{1e-3, 2l, 1.0}" );

  FRENSIE_CHECK_FLOATING_EQUALITY( (ptree.get<std::vector<float> >( "test_vector_float" )),
                                    std::vector<float>({1e-3f, 1e-2f, 1e-1f, 1.0f}),
                                    1e-7 );

  // Store a vector of vector of int
  ptree.put( "test_vector_vector_int", std::vector<std::vector<int> >({std::vector<int>({-1,0}), std::vector<int>({1,2})}) );

  FRENSIE_CHECK_EQUAL( (ptree.get<std::vector<std::vector<int> > >( "test_vector_vector_int" )).size(), (size_t)2 );
  FRENSIE_CHECK_EQUAL( (ptree.get<std::vector<std::vector<int> > >( "test_vector_vector_int" ))[0], std::vector<int>({-1,0}) );
  FRENSIE_CHECK_EQUAL( (ptree.get<std::vector<std::vector<int> > >( "test_vector_vector_int" ))[1], std::vector<int>({1,2}) );

  // Store a map of int, double
  ptree.put( "test_map_int_double", std::map<int,double>({std::make_pair(0, 0.0), std::make_pair(1, -1.0), std::make_pair(2, -2.0)}) );

  FRENSIE_CHECK_EQUAL( (ptree.get<std::map<int,double> >( "test_map_int_double" )).size(), (size_t)3 );
  FRENSIE_CHECK_EQUAL( (ptree.get<std::map<int,double> >( "test_map_int_double" ))[0], 0.0 );
  FRENSIE_CHECK_EQUAL( (ptree.get<std::map<int,double> >( "test_map_int_double" ))[1], -1.0 );
  FRENSIE_CHECK_EQUAL( (ptree.get<std::map<int,double> >( "test_map_int_double" ))[2], -2.0 );

  FRENSIE_CHECK_NO_THROW( boost::property_tree::write_json( "test_container.json", ptree ) );
}

//---------------------------------------------------------------------------//
// Check if the property tree stores a JSON array
FRENSIE_UNIT_TEST( PropertyTree, doesPropertyTreeStoreJSONArray )
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

  FRENSIE_CHECK( !Utility::doesPropertyTreeStoreJSONArray( ptree ) );
  FRENSIE_CHECK( !Utility::doesPropertyTreeStoreJSONArray( ptree.get_child( "inline array" ) ) );
  FRENSIE_CHECK( Utility::doesPropertyTreeStoreJSONArray( ptree.get_child( "json array" ) ) );

  FRENSIE_CHECK_NO_THROW( boost::property_tree::write_json( "test_arrays.json", ptree ) );
}

//---------------------------------------------------------------------------//
// Check that basic types can be converted to a property tree
FRENSIE_UNIT_TEST( PropertyTree, toPropertyTree_basic_values )
{
  // Convert a bool
  Utility::PropertyTree ptree = Utility::toPropertyTree( true, true );

  FRENSIE_CHECK_EQUAL( ptree.data().toBool(), true );

  ptree = Utility::toPropertyTree( true, false );

  FRENSIE_CHECK_EQUAL( ptree.data().toBool(), true );

  ptree = Utility::toPropertyTree( false );

  FRENSIE_CHECK_EQUAL( ptree.data().toBool(), false );


  // Convert a short
  ptree = Utility::toPropertyTree( (short)-1, true );

  FRENSIE_CHECK_EQUAL( ptree.data().toShort(), (short)-1 );

  ptree = Utility::toPropertyTree( (short)0, false );

  FRENSIE_CHECK_EQUAL( ptree.data().toShort(), (short)0 );

  ptree = Utility::toPropertyTree( (short)1 );

  FRENSIE_CHECK_EQUAL( ptree.data().toShort(), (short)1 );

  // Convert an unsigned short
  ptree = Utility::toPropertyTree( (unsigned short)0, true );

  FRENSIE_CHECK_EQUAL( ptree.data().toUnsignedShort(), (unsigned short)0 );

  ptree = Utility::toPropertyTree( (unsigned short)10, false );

  FRENSIE_CHECK_EQUAL( ptree.data().toUnsignedShort(), (unsigned short)10 );

  ptree = Utility::toPropertyTree( (unsigned short)65535 );

  FRENSIE_CHECK_EQUAL( ptree.data().toUnsignedShort(), (unsigned short)65535 );

  // Convert an int
  ptree = Utility::toPropertyTree( -11111, true );

  FRENSIE_CHECK_EQUAL( ptree.data().toInt(), -11111 );

  ptree = Utility::toPropertyTree( 0, false );

  FRENSIE_CHECK_EQUAL( ptree.data().toInt(), 0 );

  ptree = Utility::toPropertyTree( 11111 );

  FRENSIE_CHECK_EQUAL( ptree.data().toInt(), 11111 );

  // Convert an unsigned int
  ptree = Utility::toPropertyTree( 0u, true );

  FRENSIE_CHECK_EQUAL( ptree.data().toUnsignedInt(), 0u );

  ptree = Utility::toPropertyTree( 10u, false );

  FRENSIE_CHECK_EQUAL( ptree.data().toUnsignedInt(), 10u );


  ptree = Utility::toPropertyTree( 11111u );

  FRENSIE_CHECK_EQUAL( ptree.data().toUnsignedInt(), 11111u );

  // Convert a long
  ptree = Utility::toPropertyTree( -11111l, true );

  FRENSIE_CHECK_EQUAL( ptree.data().toLong(), -11111l );

  ptree = Utility::toPropertyTree( 0l, false );

  FRENSIE_CHECK_EQUAL( ptree.data().toLong(), 0l );

  ptree = Utility::toPropertyTree( 11111l );

  FRENSIE_CHECK_EQUAL( ptree.data().toLong(), 11111l );

  // Convert an unsigned long
  ptree = Utility::toPropertyTree( 0ul, true );

  FRENSIE_CHECK_EQUAL( ptree.data().toUnsignedLong(), 0ul );

  ptree = Utility::toPropertyTree( 10ul, false );

  FRENSIE_CHECK_EQUAL( ptree.data().toUnsignedLong(), 10ul );

  ptree = Utility::toPropertyTree( 11111ul );

  FRENSIE_CHECK_EQUAL( ptree.data().toUnsignedLong(), 11111ul );

  // Convert a long long
  ptree = Utility::toPropertyTree( -10000000000ll, true );

  FRENSIE_CHECK_EQUAL( ptree.data().toLongLong(), -10000000000ll );

  ptree = Utility::toPropertyTree( 0ll, false );

  FRENSIE_CHECK_EQUAL( ptree.data().toLongLong(), 0ll );

  ptree = Utility::toPropertyTree( 10000000000ll );

  FRENSIE_CHECK_EQUAL( ptree.data().toLongLong(), 10000000000ll );

  // Convert an unsigned long long
  ptree = Utility::toPropertyTree( 0ull, true );

  FRENSIE_CHECK_EQUAL( ptree.data().toUnsignedLongLong(), 0ull );

  ptree = Utility::toPropertyTree( 10ull, false );

  FRENSIE_CHECK_EQUAL( ptree.data().toUnsignedLongLong(), 10ull );

  ptree = Utility::toPropertyTree( 10000000000ull );

  FRENSIE_CHECK_EQUAL( ptree.data().toUnsignedLongLong(), 10000000000ull );

  // Convert a float
  ptree = Utility::toPropertyTree( -1.0f, true );

  FRENSIE_CHECK_EQUAL( ptree.data().toFloat(), -1.0f );

  ptree = Utility::toPropertyTree( 0.0f, false );

  FRENSIE_CHECK_EQUAL( ptree.data().toFloat(), 0.0f );

  ptree = Utility::toPropertyTree( 1.0f );

  FRENSIE_CHECK_EQUAL( ptree.data().toFloat(), 1.0f );

  // Convert a double
  ptree = Utility::toPropertyTree( -1.0, true );

  FRENSIE_CHECK_EQUAL( ptree.data().toDouble(), -1.0 );

  ptree = Utility::toPropertyTree( 0.0, false );

  FRENSIE_CHECK_EQUAL( ptree.data().toDouble(), 0.0 );

  ptree = Utility::toPropertyTree( 1.0 );

  FRENSIE_CHECK_EQUAL( ptree.data().toDouble(), 1.0 );

  // Convert a char
  ptree = Utility::toPropertyTree( 'A', true );

  FRENSIE_CHECK_EQUAL( ptree.data().toChar(), 'A' );

  ptree = Utility::toPropertyTree( 'a', false );

  FRENSIE_CHECK_EQUAL( ptree.data().toChar(), 'a' );

  ptree = Utility::toPropertyTree( 'B' );

  FRENSIE_CHECK_EQUAL( ptree.data().toChar(), 'B' );

  // Convert a c-string
  ptree = Utility::toPropertyTree( "Test", true );

  FRENSIE_CHECK_EQUAL( ptree.data().toString(), "Test" );

  ptree = Utility::toPropertyTree( "String", false );

  FRENSIE_CHECK_EQUAL( ptree.data().toString(), "String" );

  ptree = Utility::toPropertyTree( "Test String" );

  FRENSIE_CHECK_EQUAL( ptree.data().toString(), "Test String" );

  // Convert a std::string
  ptree = Utility::toPropertyTree( std::string( "Test" ), true );

  FRENSIE_CHECK_EQUAL( ptree.data().toString(), "Test" );

  ptree = Utility::toPropertyTree( std::string( "String" ), false );

  FRENSIE_CHECK_EQUAL( ptree.data().toString(), "String" );

  ptree = Utility::toPropertyTree( std::string( "Test String" ) );

  FRENSIE_CHECK_EQUAL( ptree.data().toString(), "Test String" );
}

//---------------------------------------------------------------------------//
// Check that sequence container types can be converted to a property tree
FRENSIE_UNIT_TEST( PropertyTree, toPropertyTree_sequence_container_values )
{
  // Convert a std::array to a property tree
  Utility::PropertyTree ptree =
    Utility::toPropertyTree( std::array<int,3>({-1,0,1}), true );

  FRENSIE_CHECK_EQUAL( ptree.size(), (size_t)0 );
  FRENSIE_CHECK_EQUAL( ptree.data().toVector().size(), (size_t)3 );
  FRENSIE_CHECK_EQUAL( ptree.data().toVector()[0].toInt(), -1 );
  FRENSIE_CHECK_EQUAL( ptree.data().toVector()[1].toInt(), 0 );
  FRENSIE_CHECK_EQUAL( ptree.data().toVector()[2].toInt(), 1 );

  ptree = Utility::toPropertyTree( std::array<double,2>({-1.0,1.0}), false );

  FRENSIE_CHECK_EQUAL( ptree.size(), (size_t)2 );
  FRENSIE_CHECK_EQUAL( ptree.count( "" ), (size_t)2 );

  {
    Utility::PropertyTree::const_iterator it = ptree.begin();

    FRENSIE_CHECK_EQUAL( it->second.data().toDouble(), -1.0 );

    ++it;

    FRENSIE_CHECK_EQUAL( it->second.data().toDouble(), 1.0 );
  }

  ptree = Utility::toPropertyTree( std::array<unsigned long,4>({0l, 1l, 2l, 3l}) );

  FRENSIE_CHECK_EQUAL( ptree.size(), (size_t)0 );
  FRENSIE_CHECK_EQUAL( ptree.data().toVector().size(), (size_t)4 );
  FRENSIE_CHECK_EQUAL( ptree.data().toVector()[0].toLong(), 0l );
  FRENSIE_CHECK_EQUAL( ptree.data().toVector()[1].toLong(), 1l );
  FRENSIE_CHECK_EQUAL( ptree.data().toVector()[2].toLong(), 2l );
  FRENSIE_CHECK_EQUAL( ptree.data().toVector()[3].toLong(), 3l );

  // Convert a std::vector to a property tree
  ptree = Utility::toPropertyTree( std::vector<int>({-1,0,1}), true );

  FRENSIE_CHECK_EQUAL( ptree.size(), (size_t)0 );
  FRENSIE_CHECK_EQUAL( ptree.data().toVector().size(), (size_t)3 );
  FRENSIE_CHECK_EQUAL( ptree.data().toVector()[0].toInt(), -1 );
  FRENSIE_CHECK_EQUAL( ptree.data().toVector()[1].toInt(), 0 );
  FRENSIE_CHECK_EQUAL( ptree.data().toVector()[2].toInt(), 1 );

  ptree = Utility::toPropertyTree( std::vector<double>({-1.0,1.0}), false );

  FRENSIE_CHECK_EQUAL( ptree.size(), (size_t)2 );
  FRENSIE_CHECK_EQUAL( ptree.count( "" ), (size_t)2 );

  {
    Utility::PropertyTree::const_iterator it = ptree.begin();

    FRENSIE_CHECK_EQUAL( it->second.data().toDouble(), -1.0 );

    ++it;

    FRENSIE_CHECK_EQUAL( it->second.data().toDouble(), 1.0 );
  }

  ptree = Utility::toPropertyTree( std::vector<unsigned long>({0l, 1l, 2l, 3l}) );

  FRENSIE_CHECK_EQUAL( ptree.size(), (size_t)0 );
  FRENSIE_CHECK_EQUAL( ptree.data().toVector().size(), (size_t)4 );
  FRENSIE_CHECK_EQUAL( ptree.data().toVector()[0].toLong(), 0l );
  FRENSIE_CHECK_EQUAL( ptree.data().toVector()[1].toLong(), 1l );
  FRENSIE_CHECK_EQUAL( ptree.data().toVector()[2].toLong(), 2l );
  FRENSIE_CHECK_EQUAL( ptree.data().toVector()[3].toLong(), 3l );

  // Convert a std::list to a property tree
  ptree = Utility::toPropertyTree( std::list<int>({-1,0,1}), true );

  FRENSIE_CHECK_EQUAL( ptree.size(), (size_t)0 );
  FRENSIE_CHECK_EQUAL( ptree.data().toVector().size(), (size_t)3 );
  FRENSIE_CHECK_EQUAL( ptree.data().toVector()[0].toInt(), -1 );
  FRENSIE_CHECK_EQUAL( ptree.data().toVector()[1].toInt(), 0 );
  FRENSIE_CHECK_EQUAL( ptree.data().toVector()[2].toInt(), 1 );

  ptree = Utility::toPropertyTree( std::list<double>({-1.0,1.0}), false );

  FRENSIE_CHECK_EQUAL( ptree.size(), (size_t)2 );
  FRENSIE_CHECK_EQUAL( ptree.count( "" ), (size_t)2 );

  {
    Utility::PropertyTree::const_iterator it = ptree.begin();

    FRENSIE_CHECK_EQUAL( it->second.data().toDouble(), -1.0 );

    ++it;

    FRENSIE_CHECK_EQUAL( it->second.data().toDouble(), 1.0 );
  }

  ptree = Utility::toPropertyTree( std::list<unsigned long>({0l, 1l, 2l, 3l}) );

  FRENSIE_CHECK_EQUAL( ptree.size(), (size_t)0 );
  FRENSIE_CHECK_EQUAL( ptree.data().toVector().size(), (size_t)4 );
  FRENSIE_CHECK_EQUAL( ptree.data().toVector()[0].toLong(), 0l );
  FRENSIE_CHECK_EQUAL( ptree.data().toVector()[1].toLong(), 1l );
  FRENSIE_CHECK_EQUAL( ptree.data().toVector()[2].toLong(), 2l );
  FRENSIE_CHECK_EQUAL( ptree.data().toVector()[3].toLong(), 3l );

  // Convert a std::forward_list to a property tree
  ptree = Utility::toPropertyTree( std::forward_list<int>({-1,0,1}), true );

  FRENSIE_CHECK_EQUAL( ptree.size(), (size_t)0 );
  FRENSIE_CHECK_EQUAL( ptree.data().toVector().size(), (size_t)3 );
  FRENSIE_CHECK_EQUAL( ptree.data().toVector()[0].toInt(), -1 );
  FRENSIE_CHECK_EQUAL( ptree.data().toVector()[1].toInt(), 0 );
  FRENSIE_CHECK_EQUAL( ptree.data().toVector()[2].toInt(), 1 );

  ptree = Utility::toPropertyTree( std::forward_list<double>({-1.0,1.0}), false );

  FRENSIE_CHECK_EQUAL( ptree.size(), (size_t)2 );
  FRENSIE_CHECK_EQUAL( ptree.count( "" ), (size_t)2 );

  {
    Utility::PropertyTree::const_iterator it = ptree.begin();

    FRENSIE_CHECK_EQUAL( it->second.data().toDouble(), -1.0 );

    ++it;

    FRENSIE_CHECK_EQUAL( it->second.data().toDouble(), 1.0 );
  }

  ptree = Utility::toPropertyTree( std::forward_list<unsigned long>({0l, 1l, 2l, 3l}) );

  FRENSIE_CHECK_EQUAL( ptree.size(), 0 );
  FRENSIE_CHECK_EQUAL( ptree.data().toVector().size(), 4 );
  FRENSIE_CHECK_EQUAL( ptree.data().toVector()[0].toLong(), 0l );
  FRENSIE_CHECK_EQUAL( ptree.data().toVector()[1].toLong(), 1l );
  FRENSIE_CHECK_EQUAL( ptree.data().toVector()[2].toLong(), 2l );
  FRENSIE_CHECK_EQUAL( ptree.data().toVector()[3].toLong(), 3l );

  // Convert a std::deque to a property tree
  ptree = Utility::toPropertyTree( std::deque<int>({-1,0,1}), true );

  FRENSIE_CHECK_EQUAL( ptree.size(), 0 );
  FRENSIE_CHECK_EQUAL( ptree.data().toVector().size(), 3 );
  FRENSIE_CHECK_EQUAL( ptree.data().toVector()[0].toInt(), -1 );
  FRENSIE_CHECK_EQUAL( ptree.data().toVector()[1].toInt(), 0 );
  FRENSIE_CHECK_EQUAL( ptree.data().toVector()[2].toInt(), 1 );

  ptree = Utility::toPropertyTree( std::deque<double>({-1.0,1.0}), false );

  FRENSIE_CHECK_EQUAL( ptree.size(), 2 );
  FRENSIE_CHECK_EQUAL( ptree.count( "" ), 2 );

  {
    Utility::PropertyTree::const_iterator it = ptree.begin();

    FRENSIE_CHECK_EQUAL( it->second.data().toDouble(), -1.0 );

    ++it;

    FRENSIE_CHECK_EQUAL( it->second.data().toDouble(), 1.0 );
  }

  ptree = Utility::toPropertyTree( std::deque<unsigned long>({0l, 1l, 2l, 3l}) );

  FRENSIE_CHECK_EQUAL( ptree.size(), 0 );
  FRENSIE_CHECK_EQUAL( ptree.data().toVector().size(), 4 );
  FRENSIE_CHECK_EQUAL( ptree.data().toVector()[0].toLong(), 0l );
  FRENSIE_CHECK_EQUAL( ptree.data().toVector()[1].toLong(), 1l );
  FRENSIE_CHECK_EQUAL( ptree.data().toVector()[2].toLong(), 2l );
  FRENSIE_CHECK_EQUAL( ptree.data().toVector()[3].toLong(), 3l );

  // Convert a std::set to a property tree
  ptree = Utility::toPropertyTree( std::set<int>({-1,0,1}), true );

  FRENSIE_CHECK_EQUAL( ptree.size(), 0 );
  FRENSIE_CHECK_EQUAL( ptree.data().toVector().size(), 3 );
  FRENSIE_CHECK_EQUAL( ptree.data().toVector()[0].toInt(), -1 );
  FRENSIE_CHECK_EQUAL( ptree.data().toVector()[1].toInt(), 0 );
  FRENSIE_CHECK_EQUAL( ptree.data().toVector()[2].toInt(), 1 );

  ptree = Utility::toPropertyTree( std::set<double>({-1.0,1.0}), false );

  FRENSIE_CHECK_EQUAL( ptree.size(), 2 );
  FRENSIE_CHECK_EQUAL( ptree.count( "" ), 2 );

  {
    Utility::PropertyTree::const_iterator it = ptree.begin();

    FRENSIE_CHECK_EQUAL( it->second.data().toDouble(), -1.0 );

    ++it;

    FRENSIE_CHECK_EQUAL( it->second.data().toDouble(), 1.0 );
  }

  ptree = Utility::toPropertyTree( std::set<unsigned long>({0l, 1l, 2l, 3l}) );

  FRENSIE_CHECK_EQUAL( ptree.size(), 0 );
  FRENSIE_CHECK_EQUAL( ptree.data().toVector().size(), 4 );

  // Convert a std::unordered_set to a property tree
  ptree = Utility::toPropertyTree( std::unordered_set<int>({-1,0,1}), true );

  FRENSIE_CHECK_EQUAL( ptree.size(), 0 );
  FRENSIE_CHECK_EQUAL( ptree.data().toVector().size(), 3 );

  ptree = Utility::toPropertyTree( std::unordered_set<double>({-1.0,1.0}), false );

  FRENSIE_CHECK_EQUAL( ptree.size(), 2 );
  FRENSIE_CHECK_EQUAL( ptree.count( "" ), 2 );

  ptree = Utility::toPropertyTree( std::unordered_set<unsigned long>({0l, 1l, 2l, 3l}) );

  FRENSIE_CHECK_EQUAL( ptree.size(), 0 );
  FRENSIE_CHECK_EQUAL( ptree.data().toVector().size(), 4 );

  // Convert a std::vector<std::string> to a property tree
  ptree = Utility::toPropertyTree( std::vector<std::string>({"Test", "String"}), true );

  FRENSIE_CHECK_EQUAL( ptree.size(), 0 );
  FRENSIE_CHECK_EQUAL( ptree.data().toVector().size(), 2 );
  FRENSIE_CHECK_EQUAL( ptree.data().toVector()[0].toString(), "Test" );
  FRENSIE_CHECK_EQUAL( ptree.data().toVector()[1].toString(), "String" );

  ptree = Utility::toPropertyTree( std::vector<std::string>({"Test", "String", "JSON-Array"}), false );

  FRENSIE_CHECK_EQUAL( ptree.size(), 3 );
  FRENSIE_CHECK_EQUAL( ptree.count( "" ), 3 );

  {
    Utility::PropertyTree::const_iterator it = ptree.begin();

    FRENSIE_CHECK_EQUAL( it->second.data().toString(), "Test" );

    ++it;

    FRENSIE_CHECK_EQUAL( it->second.data().toString(), "String" );

    ++it;

    FRENSIE_CHECK_EQUAL( it->second.data().toString(), "JSON-Array" );
  }

  ptree = Utility::toPropertyTree( std::vector<std::string>({"Test", "String", "Default-Inlining"}) );

  FRENSIE_CHECK_EQUAL( ptree.size(), 0 );
  FRENSIE_CHECK_EQUAL( ptree.data().toVector().size(), 3 );
  FRENSIE_CHECK_EQUAL( ptree.data().toVector()[0].toString(), "Test" );
  FRENSIE_CHECK_EQUAL( ptree.data().toVector()[1].toString(), "String" );
  FRENSIE_CHECK_EQUAL( ptree.data().toVector()[2].toString(), "Default-Inlining" );

  // Convert a VariantVector to a property tree
  ptree = Utility::toPropertyTree( Utility::VariantVector({Utility::Variant("Test"), Utility::Variant(0), Utility::Variant(1.0)}), true );

  FRENSIE_CHECK_EQUAL( ptree.size(), 0 );
  FRENSIE_CHECK_EQUAL( ptree.data().toVector().size(), 3 );
  FRENSIE_CHECK_EQUAL( ptree.data().toVector()[0].toString(), "Test" );
  FRENSIE_CHECK_EQUAL( ptree.data().toVector()[1].toInt(), 0 );
  FRENSIE_CHECK_EQUAL( ptree.data().toVector()[2].toDouble(), 1.0 );

  ptree = Utility::toPropertyTree( Utility::VariantVector({Utility::Variant("Test"), Utility::Variant(0), Utility::Variant(std::vector<double>({-1.0,1.0}))}), false );

  FRENSIE_CHECK_EQUAL( ptree.size(), 3 );
  FRENSIE_CHECK_EQUAL( ptree.count( "" ), 3 );

  {
    Utility::PropertyTree::const_iterator it = ptree.begin();

    FRENSIE_CHECK_EQUAL( it->second.data().toString(), "Test" );

    ++it;

    FRENSIE_CHECK_EQUAL( it->second.data().toInt(), 0 );

    ++it;

    FRENSIE_CHECK_EQUAL( it->second.data().toVector().size(), 2 );
    FRENSIE_CHECK_EQUAL( it->second.data().toVector()[0].toFloat(), -1.0f );
    FRENSIE_CHECK_EQUAL( it->second.data().toVector()[1].toFloat(), 1.0f );
  }

  ptree = Utility::toPropertyTree( Utility::VariantVector({Utility::Variant("Test"), Utility::Variant(-1), Utility::Variant(std::vector<int>())}) );

  FRENSIE_CHECK_EQUAL( ptree.size(), 0 );
  FRENSIE_CHECK_EQUAL( ptree.data().toVector().size(), 3 );
  FRENSIE_CHECK_EQUAL( ptree.data().toVector()[0].toString(), "Test" );
  FRENSIE_CHECK_EQUAL( ptree.data().toVector()[1].toInt(), -1 );
  FRENSIE_CHECK_EQUAL( ptree.data().toVector()[2].toVector().size(), 0 );

  // Convert a std::vector<std::vector<int> > to a property tree
  ptree = Utility::toPropertyTree( std::vector<std::vector<int> >({std::vector<int>({-1,0,1}), std::vector<int>({2,3})}), true );

  FRENSIE_CHECK_EQUAL( ptree.size(), 0 );
  FRENSIE_CHECK_EQUAL( ptree.data().toVector().size(), 2 );
  FRENSIE_CHECK_EQUAL( ptree.data().toVector()[0].toVector().size(), 3 );
  FRENSIE_CHECK_EQUAL( ptree.data().toVector()[0].toVector()[0].toInt(), -1 );
  FRENSIE_CHECK_EQUAL( ptree.data().toVector()[0].toVector()[1].toInt(), 0 );
  FRENSIE_CHECK_EQUAL( ptree.data().toVector()[0].toVector()[2].toInt(), 1 );
  FRENSIE_CHECK_EQUAL( ptree.data().toVector()[1].toVector().size(), 2 );
  FRENSIE_CHECK_EQUAL( ptree.data().toVector()[1].toVector()[0].toInt(), 2 );
  FRENSIE_CHECK_EQUAL( ptree.data().toVector()[1].toVector()[1].toInt(), 3 );

  ptree = Utility::toPropertyTree( std::vector<std::vector<double> >({std::vector<double>({-1.0,0.0,1.0}), std::vector<double>({-1.0,1.0})}), false );

  FRENSIE_CHECK_EQUAL( ptree.size(), 2 );
  FRENSIE_CHECK_EQUAL( ptree.count( "" ), 2 );

  {
    Utility::PropertyTree::const_iterator it = ptree.begin();

    FRENSIE_CHECK_EQUAL( it->second.size(), 3 );

    Utility::PropertyTree::const_iterator child_it = it->second.begin();

    FRENSIE_CHECK_EQUAL( child_it->second.data().toDouble(), -1.0 );

    ++child_it;

    FRENSIE_CHECK_EQUAL( child_it->second.data().toDouble(), 0.0 );

    ++child_it;

    FRENSIE_CHECK_EQUAL( child_it->second.data().toDouble(), 1.0 );

    ++it;

    FRENSIE_CHECK_EQUAL( it->second.size(), 2 );

    child_it = it->second.begin();

    FRENSIE_CHECK_EQUAL( child_it->second.data().toDouble(), -1.0 );

    ++child_it;

    FRENSIE_CHECK_EQUAL( child_it->second.data().toDouble(), 1.0 );
  }

  ptree = Utility::toPropertyTree( std::vector<std::vector<unsigned long> >({std::vector<unsigned long>({0ul, 1ul, 2ul}),std::vector<unsigned long>({3ul,4ul})}) );

  FRENSIE_CHECK_EQUAL( ptree.size(), 0 );
  FRENSIE_CHECK_EQUAL( ptree.data().toVector().size(), 2 );
  FRENSIE_CHECK_EQUAL( ptree.data().toVector()[0].toVector().size(), 3 );
  FRENSIE_CHECK_EQUAL( ptree.data().toVector()[0].toVector()[0].toUnsignedLong(), 0ul );
  FRENSIE_CHECK_EQUAL( ptree.data().toVector()[0].toVector()[1].toUnsignedLong(), 1ul );
  FRENSIE_CHECK_EQUAL( ptree.data().toVector()[0].toVector()[2].toUnsignedLong(), 2ul );
  FRENSIE_CHECK_EQUAL( ptree.data().toVector()[1].toVector().size(), 2 );
  FRENSIE_CHECK_EQUAL( ptree.data().toVector()[1].toVector()[0].toUnsignedLong(), 3ul );
  FRENSIE_CHECK_EQUAL( ptree.data().toVector()[1].toVector()[1].toUnsignedLong(), 4ul );
}

//---------------------------------------------------------------------------//
// Check that associative container types can be converted to a property tree
FRENSIE_UNIT_TEST( PropertyTree, toPropertyTree_associative_container_values )
{
  // Convert a std::map<int,int> to a property tree
  Utility::PropertyTree ptree = Utility::toPropertyTree( std::map<int,int>({std::make_pair(-1,-1), std::make_pair(0,0)}), true );

  FRENSIE_CHECK_EQUAL( ptree.size(), 0 );
  FRENSIE_CHECK_EQUAL( ptree.data().toMap().size(), 2 );
  FRENSIE_CHECK_EQUAL( ptree.data().toMap()["-1"].toInt(), -1 );
  FRENSIE_CHECK_EQUAL( ptree.data().toMap()["0"].toInt(), 0 );

  ptree = Utility::toPropertyTree( std::map<int,int>({std::make_pair(-1,-1), std::make_pair(0,0)}), false );

  FRENSIE_CHECK_EQUAL( ptree.size(), 2 );
  FRENSIE_CHECK_EQUAL( ptree.count( "-1" ), 1 );
  FRENSIE_CHECK_EQUAL( ptree.get_child( "-1" ).data().toInt(), -1 );
  FRENSIE_CHECK_EQUAL( ptree.count( "0" ), 1 );
  FRENSIE_CHECK_EQUAL( ptree.get_child( "0" ).data().toInt(), 0 );

  ptree = Utility::toPropertyTree( std::map<int,int>({std::make_pair(-1,-1), std::make_pair(0,0)}) );

  FRENSIE_CHECK_EQUAL( ptree.size(), 2 );
  FRENSIE_CHECK_EQUAL( ptree.count( "-1" ), 1 );
  FRENSIE_CHECK_EQUAL( ptree.get_child( "-1" ).data().toInt(), -1 );
  FRENSIE_CHECK_EQUAL( ptree.count( "0" ), 1 );
  FRENSIE_CHECK_EQUAL( ptree.get_child( "0" ).data().toInt(), 0 );

  // Convert a std::map<std::string,int> to a property tree
  ptree = Utility::toPropertyTree( std::map<std::string,int>({std::make_pair("value a", -1), std::make_pair("value b", 1)}), true );

  FRENSIE_CHECK_EQUAL( ptree.size(), 0 );
  FRENSIE_CHECK_EQUAL( ptree.data().toMap().size(), 2 );
  FRENSIE_CHECK_EQUAL( ptree.data().toMap()["value a"].toInt(), -1 );
  FRENSIE_CHECK_EQUAL( ptree.data().toMap()["value b"].toInt(), 1 );

  ptree = Utility::toPropertyTree( std::map<std::string,int>({std::make_pair("value a", -1), std::make_pair("value b", 1)}), false );

  FRENSIE_CHECK_EQUAL( ptree.size(), 2 );
  FRENSIE_CHECK_EQUAL( ptree.count( "value a" ), 1 );
  FRENSIE_CHECK_EQUAL( ptree.get_child( "value a" ).data().toInt(), -1 );
  FRENSIE_CHECK_EQUAL( ptree.count( "value b" ), 1 );
  FRENSIE_CHECK_EQUAL( ptree.get_child( "value b" ).data().toInt(), 1 );

  ptree = Utility::toPropertyTree( std::map<std::string,int>({std::make_pair("value a", -1), std::make_pair("value b", 1)}) );

  FRENSIE_CHECK_EQUAL( ptree.size(), 2 );
  FRENSIE_CHECK_EQUAL( ptree.count( "value a" ), 1 );
  FRENSIE_CHECK_EQUAL( ptree.get_child( "value a" ).data().toInt(), -1 );
  FRENSIE_CHECK_EQUAL( ptree.count( "value b" ), 1 );
  FRENSIE_CHECK_EQUAL( ptree.get_child( "value b" ).data().toInt(), 1 );

  // Convert a std::map<std::string,std::vector<double> > to a property tree
  ptree = Utility::toPropertyTree( std::map<std::string,std::vector<double> >({std::make_pair("value a", std::vector<double>({-1.0,0.0,1.0})), std::make_pair("value b", std::vector<double>({0.0,1.0}))}), true );

  FRENSIE_CHECK_EQUAL( ptree.size(), 0 );
  FRENSIE_CHECK_EQUAL( ptree.data().toMap().size(), 2 );
  FRENSIE_CHECK_EQUAL( ptree.data().toMap()["value a"].toVector().size(), 3 );
  FRENSIE_CHECK_EQUAL( ptree.data().toMap()["value b"].toVector().size(), 2 );

  ptree = Utility::toPropertyTree( std::map<std::string,std::vector<double> >({std::make_pair("value a", std::vector<double>({-1.0,0.0,1.0})), std::make_pair("value b", std::vector<double>({0.0,1.0}))}), false );

  FRENSIE_CHECK_EQUAL( ptree.size(), 2 );
  FRENSIE_CHECK_EQUAL( ptree.count( "value a" ), 1 );
  FRENSIE_CHECK_EQUAL( ptree.get_child( "value a" ).size(), 3 );

  {
    Utility::PropertyTree::const_iterator it =
      ptree.get_child( "value a" ).begin();

    FRENSIE_CHECK_EQUAL( it->second.data().toDouble(), -1.0 );

    ++it;

    FRENSIE_CHECK_EQUAL( it->second.data().toDouble(), 0.0 );

    ++it;

    FRENSIE_CHECK_EQUAL( it->second.data().toDouble(), 1.0 );
  }

  FRENSIE_CHECK_EQUAL( ptree.count( "value b" ), 1 );
  FRENSIE_CHECK_EQUAL( ptree.get_child( "value b" ).size(), 2 );

  {
    Utility::PropertyTree::const_iterator it =
      ptree.get_child( "value b" ).begin();

    FRENSIE_CHECK_EQUAL( it->second.data().toDouble(), 0.0 );

    ++it;

    FRENSIE_CHECK_EQUAL( it->second.data().toDouble(), 1.0 );
  }

  ptree = Utility::toPropertyTree( std::map<std::string,std::vector<double> >({std::make_pair("value a", std::vector<double>({-1.0,0.0,1.0})), std::make_pair("value b", std::vector<double>({0.0,1.0}))}) );

  FRENSIE_CHECK_EQUAL( ptree.size(), 2 );
  FRENSIE_CHECK_EQUAL( ptree.count( "value a" ), 1 );
  FRENSIE_CHECK_EQUAL( ptree.get_child( "value a" ).size(), 3 );

  {
    Utility::PropertyTree::const_iterator it =
      ptree.get_child( "value a" ).begin();

    FRENSIE_CHECK_EQUAL( it->second.data().toDouble(), -1.0 );

    ++it;

    FRENSIE_CHECK_EQUAL( it->second.data().toDouble(), 0.0 );

    ++it;

    FRENSIE_CHECK_EQUAL( it->second.data().toDouble(), 1.0 );
  }

  FRENSIE_CHECK_EQUAL( ptree.count( "value b" ), 1 );
  FRENSIE_CHECK_EQUAL( ptree.get_child( "value b" ).size(), 2 );

  {
    Utility::PropertyTree::const_iterator it =
      ptree.get_child( "value b" ).begin();

    FRENSIE_CHECK_EQUAL( it->second.data().toDouble(), 0.0 );

    ++it;

    FRENSIE_CHECK_EQUAL( it->second.data().toDouble(), 1.0 );
  }

  // Convert a std::unordered_map<int,int> to a property tree
  ptree = Utility::toPropertyTree( std::unordered_map<int,int>({std::make_pair(-1,-1), std::make_pair(0,0)}), true );

  FRENSIE_CHECK_EQUAL( ptree.size(), 0 );
  FRENSIE_CHECK_EQUAL( ptree.data().toMap().size(), 2 );
  FRENSIE_CHECK_EQUAL( ptree.data().toMap()["-1"].toInt(), -1 );
  FRENSIE_CHECK_EQUAL( ptree.data().toMap()["0"].toInt(), 0 );

  ptree = Utility::toPropertyTree( std::unordered_map<int,int>({std::make_pair(-1,-1), std::make_pair(0,0)}), false );

  FRENSIE_CHECK_EQUAL( ptree.size(), 2 );
  FRENSIE_CHECK_EQUAL( ptree.count( "-1" ), 1 );
  FRENSIE_CHECK_EQUAL( ptree.get_child( "-1" ).data().toInt(), -1 );
  FRENSIE_CHECK_EQUAL( ptree.count( "0" ), 1 );
  FRENSIE_CHECK_EQUAL( ptree.get_child( "0" ).data().toInt(), 0 );

  ptree = Utility::toPropertyTree( std::unordered_map<int,int>({std::make_pair(-1,-1), std::make_pair(0,0)}) );

  FRENSIE_CHECK_EQUAL( ptree.size(), 2 );
  FRENSIE_CHECK_EQUAL( ptree.count( "-1" ), 1 );
  FRENSIE_CHECK_EQUAL( ptree.get_child( "-1" ).data().toInt(), -1 );
  FRENSIE_CHECK_EQUAL( ptree.count( "0" ), 1 );
  FRENSIE_CHECK_EQUAL( ptree.get_child( "0" ).data().toInt(), 0 );

  // Convert a std::unordered_map<std::string,int> to a property tree
  ptree = Utility::toPropertyTree( std::unordered_map<std::string,int>({std::make_pair("value a", -1), std::make_pair("value b", 1)}), true );

  FRENSIE_CHECK_EQUAL( ptree.size(), 0 );
  FRENSIE_CHECK_EQUAL( ptree.data().toMap().size(), 2 );
  FRENSIE_CHECK_EQUAL( ptree.data().toMap()["value a"].toInt(), -1 );
  FRENSIE_CHECK_EQUAL( ptree.data().toMap()["value b"].toInt(), 1 );

  ptree = Utility::toPropertyTree( std::unordered_map<std::string,int>({std::make_pair("value a", -1), std::make_pair("value b", 1)}), false );

  FRENSIE_CHECK_EQUAL( ptree.size(), 2 );
  FRENSIE_CHECK_EQUAL( ptree.count( "value a" ), 1 );
  FRENSIE_CHECK_EQUAL( ptree.get_child( "value a" ).data().toInt(), -1 );
  FRENSIE_CHECK_EQUAL( ptree.count( "value b" ), 1 );
  FRENSIE_CHECK_EQUAL( ptree.get_child( "value b" ).data().toInt(), 1 );

  ptree = Utility::toPropertyTree( std::unordered_map<std::string,int>({std::make_pair("value a", -1), std::make_pair("value b", 1)}) );

  FRENSIE_CHECK_EQUAL( ptree.size(), 2 );
  FRENSIE_CHECK_EQUAL( ptree.count( "value a" ), 1 );
  FRENSIE_CHECK_EQUAL( ptree.get_child( "value a" ).data().toInt(), -1 );
  FRENSIE_CHECK_EQUAL( ptree.count( "value b" ), 1 );
  FRENSIE_CHECK_EQUAL( ptree.get_child( "value b" ).data().toInt(), 1 );

  // Convert a std::unordered_map<std::string,std::vector<double> > to a property tree
  ptree = Utility::toPropertyTree( std::unordered_map<std::string,std::vector<double> >({std::make_pair("value a", std::vector<double>({-1.0,0.0,1.0})), std::make_pair("value b", std::vector<double>({0.0,1.0}))}), true );

  FRENSIE_CHECK_EQUAL( ptree.size(), 0 );
  FRENSIE_CHECK_EQUAL( ptree.data().toMap().size(), 2 );
  FRENSIE_CHECK_EQUAL( ptree.data().toMap()["value a"].toVector().size(), 3 );
  FRENSIE_CHECK_EQUAL( ptree.data().toMap()["value b"].toVector().size(), 2 );

  ptree = Utility::toPropertyTree( std::unordered_map<std::string,std::vector<double> >({std::make_pair("value a", std::vector<double>({-1.0,0.0,1.0})), std::make_pair("value b", std::vector<double>({0.0,1.0}))}), false );

  FRENSIE_CHECK_EQUAL( ptree.size(), 2 );
  FRENSIE_CHECK_EQUAL( ptree.count( "value a" ), 1 );
  FRENSIE_CHECK_EQUAL( ptree.get_child( "value a" ).size(), 3 );

  {
    Utility::PropertyTree::const_iterator it =
      ptree.get_child( "value a" ).begin();

    FRENSIE_CHECK_EQUAL( it->second.data().toDouble(), -1.0 );

    ++it;

    FRENSIE_CHECK_EQUAL( it->second.data().toDouble(), 0.0 );

    ++it;

    FRENSIE_CHECK_EQUAL( it->second.data().toDouble(), 1.0 );
  }

  FRENSIE_CHECK_EQUAL( ptree.count( "value b" ), 1 );
  FRENSIE_CHECK_EQUAL( ptree.get_child( "value b" ).size(), 2 );

  {
    Utility::PropertyTree::const_iterator it =
      ptree.get_child( "value b" ).begin();

    FRENSIE_CHECK_EQUAL( it->second.data().toDouble(), 0.0 );

    ++it;

    FRENSIE_CHECK_EQUAL( it->second.data().toDouble(), 1.0 );
  }

  ptree = Utility::toPropertyTree( std::unordered_map<std::string,std::vector<double> >({std::make_pair("value a", std::vector<double>({-1.0,0.0,1.0})), std::make_pair("value b", std::vector<double>({0.0,1.0}))}) );

  FRENSIE_CHECK_EQUAL( ptree.size(), 2 );
  FRENSIE_CHECK_EQUAL( ptree.count( "value a" ), 1 );
  FRENSIE_CHECK_EQUAL( ptree.get_child( "value a" ).size(), 3 );

  {
    Utility::PropertyTree::const_iterator it =
      ptree.get_child( "value a" ).begin();

    FRENSIE_CHECK_EQUAL( it->second.data().toDouble(), -1.0 );

    ++it;

    FRENSIE_CHECK_EQUAL( it->second.data().toDouble(), 0.0 );

    ++it;

    FRENSIE_CHECK_EQUAL( it->second.data().toDouble(), 1.0 );
  }

  FRENSIE_CHECK_EQUAL( ptree.count( "value b" ), 1 );
  FRENSIE_CHECK_EQUAL( ptree.get_child( "value b" ).size(), 2 );

  {
    Utility::PropertyTree::const_iterator it =
      ptree.get_child( "value b" ).begin();

    FRENSIE_CHECK_EQUAL( it->second.data().toDouble(), 0.0 );

    ++it;

    FRENSIE_CHECK_EQUAL( it->second.data().toDouble(), 1.0 );
  }

  // Convert a VariantMap to a property tree
  ptree = Utility::toPropertyTree( Utility::VariantMap({std::make_pair("value a", Utility::Variant(-1)), std::make_pair("value b", Utility::Variant(std::vector<double>({-1.0,0.0,1.0})))}), true );

  FRENSIE_CHECK_EQUAL( ptree.size(), 0 );
  FRENSIE_CHECK_EQUAL( ptree.data().toMap().size(), 2 );
  FRENSIE_CHECK_EQUAL( ptree.data().toMap()["value a"].toInt(), -1 );
  FRENSIE_CHECK_EQUAL( ptree.data().toMap()["value b"].toVector().size(), 3 );

  ptree = Utility::toPropertyTree( Utility::VariantMap({std::make_pair("value a", Utility::Variant(-1)), std::make_pair("value b", Utility::Variant(std::vector<double>({-1.0,0.0,1.0})))}), false );

  FRENSIE_CHECK_EQUAL( ptree.size(), 2 );
  FRENSIE_CHECK_EQUAL( ptree.count( "value a" ), 1 );
  FRENSIE_CHECK_EQUAL( ptree.get_child( "value a" ).size(), 0 );
  FRENSIE_CHECK_EQUAL( ptree.get_child( "value a" ).data().toInt(), -1 );
  FRENSIE_CHECK_EQUAL( ptree.count( "value b" ), 1 );
  FRENSIE_CHECK_EQUAL( ptree.get_child( "value b" ).size(), 0 );
  FRENSIE_CHECK_EQUAL( ptree.get_child( "value b" ).data().toVector().size(), 3 );

  ptree = Utility::toPropertyTree( Utility::VariantMap({std::make_pair("value a", Utility::Variant(-1)), std::make_pair("value b", Utility::Variant(std::vector<double>({-1.0,0.0,1.0})))}) );

  FRENSIE_CHECK_EQUAL( ptree.size(), 2 );
  FRENSIE_CHECK_EQUAL( ptree.count( "value a" ), 1 );
  FRENSIE_CHECK_EQUAL( ptree.get_child( "value a" ).size(), 0 );
  FRENSIE_CHECK_EQUAL( ptree.get_child( "value a" ).data().toInt(), -1 );
  FRENSIE_CHECK_EQUAL( ptree.count( "value b" ), 1 );
  FRENSIE_CHECK_EQUAL( ptree.get_child( "value b" ).size(), 0 );
  FRENSIE_CHECK_EQUAL( ptree.get_child( "value b" ).data().toVector().size(), 3 );
}

//---------------------------------------------------------------------------//
// Check that a property tree node can be converted to a sequence container
FRENSIE_UNIT_TEST( PropertyTree, fromPropertyTree_sequence_container )
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

  FRENSIE_CHECK_THROW( Utility::fromPropertyTree<std::vector<int> >( ptree, unused_children ),
              Utility::PropertyTreeConversionException );
  FRENSIE_CHECK_THROW( Utility::fromPropertyTree<std::vector<double> >( ptree, unused_children ),
              Utility::PropertyTreeConversionException );
  FRENSIE_CHECK_THROW( Utility::fromPropertyTree<std::vector<std::string> >( ptree, unused_children ),
              Utility::PropertyTreeConversionException );
  FRENSIE_CHECK_THROW( Utility::fromPropertyTree<Utility::VariantVector>( ptree, unused_children ),
              Utility::PropertyTreeConversionException );

  FRENSIE_CHECK_THROW( Utility::fromPropertyTree<std::vector<int> >( ptree.get_child( "value" ), unused_children ),
              Utility::PropertyTreeConversionException );
  FRENSIE_CHECK_THROW( Utility::fromPropertyTree<std::vector<double> >( ptree.get_child( "value" ), unused_children ),
              Utility::PropertyTreeConversionException );
  FRENSIE_CHECK_THROW( Utility::fromPropertyTree<std::vector<std::string> >( ptree.get_child( "value" ), unused_children ),
              Utility::PropertyTreeConversionException );

  Utility::VariantVector vector =
    Utility::fromPropertyTree<Utility::VariantVector>( ptree.get_child( "value" ), unused_children );

  FRENSIE_CHECK_EQUAL( vector.size(), 1 );
  FRENSIE_CHECK_EQUAL( vector.front().toBool(), true );
  FRENSIE_CHECK_EQUAL( unused_children.size(), 0 );

  std::vector<int> int_vector =
    Utility::fromPropertyTree<std::vector<int> >( ptree.get_child( "inline array" ) );

  FRENSIE_CHECK_EQUAL( int_vector.size(), 3 );
  FRENSIE_CHECK_EQUAL( int_vector[0], -1 );
  FRENSIE_CHECK_EQUAL( int_vector[1], 0 );
  FRENSIE_CHECK_EQUAL( int_vector[2], 1 );

  std::vector<double> double_vector =
    Utility::fromPropertyTree<std::vector<double> >( ptree.get_child( "inline array" ) );

  FRENSIE_CHECK_EQUAL( double_vector.size(), 3 );
  FRENSIE_CHECK_EQUAL( double_vector[0], -1.0 );
  FRENSIE_CHECK_EQUAL( double_vector[1], 0.0 );
  FRENSIE_CHECK_EQUAL( double_vector[2], 1.0 );

  std::vector<std::string> string_vector =
    Utility::fromPropertyTree<std::vector<std::string> >( ptree.get_child( "inline array" ) );

  FRENSIE_CHECK_EQUAL( string_vector.size(), 3 );
  FRENSIE_CHECK_EQUAL( string_vector[0], "-1" );
  FRENSIE_CHECK_EQUAL( string_vector[1], "0" );
  FRENSIE_CHECK_EQUAL( string_vector[2], "1" );

  vector = Utility::fromPropertyTree<Utility::VariantVector>( ptree.get_child( "inline array" ) );

  FRENSIE_CHECK_EQUAL( vector.size(), 3 );
  FRENSIE_CHECK_EQUAL( vector[0].toInt(), -1 );
  FRENSIE_CHECK_EQUAL( vector[1].toInt(), 0 );
  FRENSIE_CHECK_EQUAL( vector[2].toInt(), 1 );

  int_vector =  Utility::fromPropertyTree<std::vector<int> >( ptree.get_child( "json array" ) );

  FRENSIE_CHECK_EQUAL( int_vector.size(), 3 );
  FRENSIE_CHECK_EQUAL( int_vector[0], -1 );
  FRENSIE_CHECK_EQUAL( int_vector[1], 0 );
  FRENSIE_CHECK_EQUAL( int_vector[2], 1 );

  double_vector = Utility::fromPropertyTree<std::vector<double> >( ptree.get_child( "json array" ) );

  FRENSIE_CHECK_EQUAL( double_vector.size(), 3 );
  FRENSIE_CHECK_EQUAL( double_vector[0], -1.0 );
  FRENSIE_CHECK_EQUAL( double_vector[1], 0.0 );
  FRENSIE_CHECK_EQUAL( double_vector[2], 1.0 );

  string_vector = Utility::fromPropertyTree<std::vector<std::string> >( ptree.get_child( "json array" ) );

  FRENSIE_CHECK_EQUAL( string_vector.size(), 3 );
  FRENSIE_CHECK_EQUAL( string_vector[0], "-1" );
  FRENSIE_CHECK_EQUAL( string_vector[1], "0" );
  FRENSIE_CHECK_EQUAL( string_vector[2], "1" );

  vector = Utility::fromPropertyTree<Utility::VariantVector>( ptree.get_child( "json array" ) );

  FRENSIE_CHECK_EQUAL( vector.size(), 3 );
  FRENSIE_CHECK_EQUAL( vector[0].toInt(), -1 );
  FRENSIE_CHECK_EQUAL( vector[1].toInt(), 0 );
  FRENSIE_CHECK_EQUAL( vector[2].toInt(), 1 );

  // Convert the nodes to deques
  FRENSIE_CHECK_THROW( Utility::fromPropertyTree<std::deque<int> >( ptree, unused_children ),
              Utility::PropertyTreeConversionException );
  FRENSIE_CHECK_THROW( Utility::fromPropertyTree<std::deque<double> >( ptree, unused_children ),
              Utility::PropertyTreeConversionException );
  FRENSIE_CHECK_THROW( Utility::fromPropertyTree<std::deque<std::string> >( ptree, unused_children ),
              Utility::PropertyTreeConversionException );
  FRENSIE_CHECK_THROW( Utility::fromPropertyTree<Utility::VariantDeque>( ptree, unused_children ),
              Utility::PropertyTreeConversionException );

  FRENSIE_CHECK_THROW( Utility::fromPropertyTree<std::deque<int> >( ptree.get_child( "value" ), unused_children ),
              Utility::PropertyTreeConversionException );
  FRENSIE_CHECK_THROW( Utility::fromPropertyTree<std::deque<double> >( ptree.get_child( "value" ), unused_children ),
              Utility::PropertyTreeConversionException );
  FRENSIE_CHECK_THROW( Utility::fromPropertyTree<std::deque<std::string> >( ptree.get_child( "value" ), unused_children ),
              Utility::PropertyTreeConversionException );

  Utility::VariantDeque deque =
    Utility::fromPropertyTree<Utility::VariantDeque>( ptree.get_child( "value" ), unused_children );

  FRENSIE_CHECK_EQUAL( deque.size(), 1 );
  FRENSIE_CHECK_EQUAL( deque.front().toBool(), true );
  FRENSIE_CHECK_EQUAL( unused_children.size(), 0 );

  std::deque<int> int_deque =
    Utility::fromPropertyTree<std::deque<int> >( ptree.get_child( "inline array" ) );

  FRENSIE_CHECK_EQUAL( int_deque.size(), 3 );
  FRENSIE_CHECK_EQUAL( int_deque.front(), -1 );
  FRENSIE_CHECK_EQUAL( int_deque.back(), 1 );

  std::deque<double> double_deque =
    Utility::fromPropertyTree<std::deque<double> >( ptree.get_child( "inline array" ) );

  FRENSIE_CHECK_EQUAL( double_deque.size(), 3 );
  FRENSIE_CHECK_EQUAL( double_deque.front(), -1.0 );
  FRENSIE_CHECK_EQUAL( double_deque.back(), 1.0 );

  std::deque<std::string> string_deque =
    Utility::fromPropertyTree<std::deque<std::string> >( ptree.get_child( "inline array" ) );

  FRENSIE_CHECK_EQUAL( string_deque.size(), 3 );
  FRENSIE_CHECK_EQUAL( string_deque.front(), "-1" );
  FRENSIE_CHECK_EQUAL( string_deque.back(), "1" );

  deque = Utility::fromPropertyTree<Utility::VariantDeque>( ptree.get_child( "inline array" ) );

  FRENSIE_CHECK_EQUAL( deque.size(), 3 );
  FRENSIE_CHECK_EQUAL( deque.front().toInt(), -1 );
  FRENSIE_CHECK_EQUAL( deque.back().toInt(), 1 );

  int_deque =  Utility::fromPropertyTree<std::deque<int> >( ptree.get_child( "json array" ) );

  FRENSIE_CHECK_EQUAL( int_deque.size(), 3 );
  FRENSIE_CHECK_EQUAL( int_deque.front(), -1 );
  FRENSIE_CHECK_EQUAL( int_deque.back(), 1 );

  double_deque = Utility::fromPropertyTree<std::deque<double> >( ptree.get_child( "json array" ) );

  FRENSIE_CHECK_EQUAL( double_deque.size(), 3 );
  FRENSIE_CHECK_EQUAL( double_deque.front(), -1.0 );
  FRENSIE_CHECK_EQUAL( double_deque.back(), 1.0 );

  string_deque = Utility::fromPropertyTree<std::deque<std::string> >( ptree.get_child( "json array" ) );

  FRENSIE_CHECK_EQUAL( string_deque.size(), 3 );
  FRENSIE_CHECK_EQUAL( string_deque.front(), "-1" );
  FRENSIE_CHECK_EQUAL( string_deque.back(), "1" );

  deque = Utility::fromPropertyTree<Utility::VariantDeque>( ptree.get_child( "json array" ) );

  FRENSIE_CHECK_EQUAL( deque.size(), 3 );
  FRENSIE_CHECK_EQUAL( deque.front().toInt(), -1 );
  FRENSIE_CHECK_EQUAL( deque.back().toInt(), 1 );

  // Convert the nodes to lists
  FRENSIE_CHECK_THROW( Utility::fromPropertyTree<std::list<int> >( ptree, unused_children ),
              Utility::PropertyTreeConversionException );
  FRENSIE_CHECK_THROW( Utility::fromPropertyTree<std::list<double> >( ptree, unused_children ),
              Utility::PropertyTreeConversionException );
  FRENSIE_CHECK_THROW( Utility::fromPropertyTree<std::list<std::string> >( ptree, unused_children ),
              Utility::PropertyTreeConversionException );
  FRENSIE_CHECK_THROW( Utility::fromPropertyTree<Utility::VariantList>( ptree ),
              Utility::PropertyTreeConversionException );

  FRENSIE_CHECK_THROW( Utility::fromPropertyTree<std::list<int> >( ptree.get_child( "value" ), unused_children ),
              Utility::PropertyTreeConversionException );
  FRENSIE_CHECK_THROW( Utility::fromPropertyTree<std::list<double> >( ptree.get_child( "value" ), unused_children ),
              Utility::PropertyTreeConversionException );
  FRENSIE_CHECK_THROW( Utility::fromPropertyTree<std::list<std::string> >( ptree.get_child( "value" ), unused_children ),
              Utility::PropertyTreeConversionException );

  Utility::VariantList list =
    Utility::fromPropertyTree<Utility::VariantList>( ptree.get_child( "value" ), unused_children );

  FRENSIE_CHECK_EQUAL( list.size(), 1 );
  FRENSIE_CHECK_EQUAL( list.front().toBool(), true );
  FRENSIE_CHECK_EQUAL( unused_children.size(), 0 );

  std::list<int> int_list =
    Utility::fromPropertyTree<std::list<int> >( ptree.get_child( "inline array" ) );

  FRENSIE_CHECK_EQUAL( int_list.size(), 3 );
  FRENSIE_CHECK_EQUAL( int_list.front(), -1 );
  FRENSIE_CHECK_EQUAL( int_list.back(), 1 );

  std::list<double> double_list =
    Utility::fromPropertyTree<std::list<double> >( ptree.get_child( "inline array" ) );

  FRENSIE_CHECK_EQUAL( double_list.size(), 3 );
  FRENSIE_CHECK_EQUAL( double_list.front(), -1.0 );
  FRENSIE_CHECK_EQUAL( double_list.back(), 1.0 );

  std::list<std::string> string_list =
    Utility::fromPropertyTree<std::list<std::string> >( ptree.get_child( "inline array" ) );

  FRENSIE_CHECK_EQUAL( string_list.size(), 3 );
  FRENSIE_CHECK_EQUAL( string_list.front(), "-1" );
  FRENSIE_CHECK_EQUAL( string_list.back(), "1" );

  list = Utility::fromPropertyTree<Utility::VariantList>( ptree.get_child( "inline array" ) );

  FRENSIE_CHECK_EQUAL( list.size(), 3 );
  FRENSIE_CHECK_EQUAL( list.front().toInt(), -1 );
  FRENSIE_CHECK_EQUAL( list.back().toInt(), 1 );

  int_list =  Utility::fromPropertyTree<std::list<int> >( ptree.get_child( "json array" ) );

  FRENSIE_CHECK_EQUAL( int_list.size(), 3 );
  FRENSIE_CHECK_EQUAL( int_list.front(), -1 );
  FRENSIE_CHECK_EQUAL( int_list.back(), 1 );

  double_list = Utility::fromPropertyTree<std::list<double> >( ptree.get_child( "json array" ) );

  FRENSIE_CHECK_EQUAL( double_list.size(), 3 );
  FRENSIE_CHECK_EQUAL( double_list.front(), -1.0 );
  FRENSIE_CHECK_EQUAL( double_list.back(), 1.0 );

  string_list = Utility::fromPropertyTree<std::list<std::string> >( ptree.get_child( "json array" ) );

  FRENSIE_CHECK_EQUAL( string_list.size(), 3 );
  FRENSIE_CHECK_EQUAL( string_list.front(), "-1" );
  FRENSIE_CHECK_EQUAL( string_list.back(), "1" );

  list = Utility::fromPropertyTree<Utility::VariantList>( ptree.get_child( "json array" ) );

  FRENSIE_CHECK_EQUAL( list.size(), 3 );
  FRENSIE_CHECK_EQUAL( list.front().toInt(), -1 );
  FRENSIE_CHECK_EQUAL( list.back().toInt(), 1 );

  // Convert the nodes to forward lists
  FRENSIE_CHECK_THROW( Utility::fromPropertyTree<std::forward_list<int> >( ptree, unused_children ),
              Utility::PropertyTreeConversionException );
  FRENSIE_CHECK_THROW( Utility::fromPropertyTree<std::forward_list<double> >( ptree, unused_children ),
              Utility::PropertyTreeConversionException );
  FRENSIE_CHECK_THROW( Utility::fromPropertyTree<std::forward_list<std::string> >( ptree, unused_children ),
              Utility::PropertyTreeConversionException );
  FRENSIE_CHECK_THROW( Utility::fromPropertyTree<Utility::VariantForwardList>( ptree, unused_children ),
              Utility::PropertyTreeConversionException );

  FRENSIE_CHECK_THROW( Utility::fromPropertyTree<std::forward_list<int> >( ptree.get_child( "value" ), unused_children ),
              Utility::PropertyTreeConversionException );
  FRENSIE_CHECK_THROW( Utility::fromPropertyTree<std::forward_list<double> >( ptree.get_child( "value" ), unused_children ),
              Utility::PropertyTreeConversionException );
  FRENSIE_CHECK_THROW( Utility::fromPropertyTree<std::forward_list<std::string> >( ptree.get_child( "value" ), unused_children ),
              Utility::PropertyTreeConversionException );

  Utility::VariantForwardList forward_list =
    Utility::fromPropertyTree<Utility::VariantForwardList>( ptree.get_child( "value" ), unused_children );

  FRENSIE_CHECK_EQUAL( std::distance(forward_list.begin(), forward_list.end()), 1 );
  FRENSIE_CHECK_EQUAL( forward_list.front().toBool(), true );
  FRENSIE_CHECK_EQUAL( unused_children.size(), 0 );

  std::forward_list<int> int_forward_list =
    Utility::fromPropertyTree<std::forward_list<int> >( ptree.get_child( "inline array" ) );

  FRENSIE_CHECK_EQUAL( std::distance(int_forward_list.begin(), int_forward_list.end()), 3 );
  FRENSIE_CHECK_EQUAL( int_forward_list.front(), -1 );

  std::forward_list<double> double_forward_list =
    Utility::fromPropertyTree<std::forward_list<double> >( ptree.get_child( "inline array" ) );

  FRENSIE_CHECK_EQUAL( std::distance(double_forward_list.begin(), double_forward_list.end()), 3 );
  FRENSIE_CHECK_EQUAL( double_forward_list.front(), -1.0 );

  std::forward_list<std::string> string_forward_list =
    Utility::fromPropertyTree<std::forward_list<std::string> >( ptree.get_child( "inline array" ) );

  FRENSIE_CHECK_EQUAL( std::distance(string_forward_list.begin(), string_forward_list.end()), 3 );
  FRENSIE_CHECK_EQUAL( string_forward_list.front(), "-1" );

  forward_list = Utility::fromPropertyTree<Utility::VariantForwardList>( ptree.get_child( "inline array" ) );

  FRENSIE_CHECK_EQUAL( std::distance(forward_list.begin(), forward_list.end()), 3 );
  FRENSIE_CHECK_EQUAL( forward_list.front().toInt(), -1 );

  int_forward_list =  Utility::fromPropertyTree<std::forward_list<int> >( ptree.get_child( "json array" ) );

  FRENSIE_CHECK_EQUAL( std::distance(int_forward_list.begin(), int_forward_list.end()), 3 );
  FRENSIE_CHECK_EQUAL( int_forward_list.front(), -1 );

  double_forward_list = Utility::fromPropertyTree<std::forward_list<double> >( ptree.get_child( "json array" ) );

  FRENSIE_CHECK_EQUAL( std::distance(double_forward_list.begin(), double_forward_list.end()), 3 );
  FRENSIE_CHECK_EQUAL( double_forward_list.front(), -1.0 );

  string_forward_list = Utility::fromPropertyTree<std::forward_list<std::string> >( ptree.get_child( "json array" ) );

  FRENSIE_CHECK_EQUAL( std::distance(string_forward_list.begin(), string_forward_list.end()), 3 );
  FRENSIE_CHECK_EQUAL( string_forward_list.front(), "-1" );

  forward_list = Utility::fromPropertyTree<Utility::VariantForwardList>( ptree.get_child( "json array" ) );

  FRENSIE_CHECK_EQUAL( std::distance(forward_list.begin(), forward_list.end()), 3 );
  FRENSIE_CHECK_EQUAL( forward_list.front().toInt(), -1 );

  // Convert the nodes to sets
  FRENSIE_CHECK_THROW( Utility::fromPropertyTree<std::set<int> >( ptree, unused_children ),
              Utility::PropertyTreeConversionException );
  FRENSIE_CHECK_THROW( Utility::fromPropertyTree<std::set<double> >( ptree, unused_children ),
              Utility::PropertyTreeConversionException );
  FRENSIE_CHECK_THROW( Utility::fromPropertyTree<std::set<std::string> >( ptree, unused_children ),
              Utility::PropertyTreeConversionException );

  FRENSIE_CHECK_THROW( Utility::fromPropertyTree<std::set<int> >( ptree.get_child( "value" ), unused_children ),
              Utility::PropertyTreeConversionException );
  FRENSIE_CHECK_THROW( Utility::fromPropertyTree<std::set<double> >( ptree.get_child( "value" ), unused_children ),
              Utility::PropertyTreeConversionException );
  FRENSIE_CHECK_THROW( Utility::fromPropertyTree<std::set<std::string> >( ptree.get_child( "value" ), unused_children ),
              Utility::PropertyTreeConversionException );

  std::set<int> int_set =
    Utility::fromPropertyTree<std::set<int> >( ptree.get_child( "inline array" ) );

  FRENSIE_CHECK_EQUAL( int_set.size(), 3 );
  FRENSIE_CHECK_EQUAL( int_set.count( -1 ), 1 );
  FRENSIE_CHECK_EQUAL( int_set.count( 0 ), 1 );
  FRENSIE_CHECK_EQUAL( int_set.count( 1 ), 1 );

  std::set<double> double_set =
    Utility::fromPropertyTree<std::set<double> >( ptree.get_child( "inline array" ) );

  FRENSIE_CHECK_EQUAL( double_set.size(), 3 );
  FRENSIE_CHECK_EQUAL( double_set.count( -1.0 ), 1 );
  FRENSIE_CHECK_EQUAL( double_set.count( 0.0 ), 1 );
  FRENSIE_CHECK_EQUAL( double_set.count( 1.0 ), 1 );

  std::set<std::string> string_set =
    Utility::fromPropertyTree<std::set<std::string> >( ptree.get_child( "inline array" ) );

  FRENSIE_CHECK_EQUAL( string_set.size(), 3 );
  FRENSIE_CHECK_EQUAL( string_set.count( "-1" ), 1 );
  FRENSIE_CHECK_EQUAL( string_set.count( "0" ), 1 );
  FRENSIE_CHECK_EQUAL( string_set.count( "1" ), 1 );

  int_set =  Utility::fromPropertyTree<std::set<int> >( ptree.get_child( "json array" ) );

  FRENSIE_CHECK_EQUAL( int_set.size(), 3 );
  FRENSIE_CHECK_EQUAL( int_set.count( -1 ), 1 );
  FRENSIE_CHECK_EQUAL( int_set.count( 0 ), 1 );
  FRENSIE_CHECK_EQUAL( int_set.count( 1 ), 1 );

  double_set = Utility::fromPropertyTree<std::set<double> >( ptree.get_child( "json array" ) );

  FRENSIE_CHECK_EQUAL( double_set.size(), 3 );
  FRENSIE_CHECK_EQUAL( double_set.count( -1.0 ), 1 );
  FRENSIE_CHECK_EQUAL( double_set.count( 0.0 ), 1 );
  FRENSIE_CHECK_EQUAL( double_set.count( 1.0 ), 1 );

  string_set = Utility::fromPropertyTree<std::set<std::string> >( ptree.get_child( "json array" ) );

  FRENSIE_CHECK_EQUAL( string_set.size(), 3 );
  FRENSIE_CHECK_EQUAL( string_set.count( "-1" ), 1 );
  FRENSIE_CHECK_EQUAL( string_set.count( "0" ), 1 );
  FRENSIE_CHECK_EQUAL( string_set.count( "1" ), 1 );

  // Convert the nodes to unordered sets
  FRENSIE_CHECK_THROW( Utility::fromPropertyTree<std::unordered_set<int> >( ptree, unused_children ),
              Utility::PropertyTreeConversionException );
  FRENSIE_CHECK_THROW( Utility::fromPropertyTree<std::unordered_set<double> >( ptree, unused_children ),
              Utility::PropertyTreeConversionException );
  FRENSIE_CHECK_THROW( Utility::fromPropertyTree<std::unordered_set<std::string> >( ptree, unused_children ),
              Utility::PropertyTreeConversionException );

  FRENSIE_CHECK_THROW( Utility::fromPropertyTree<std::unordered_set<int> >( ptree.get_child( "value" ), unused_children ),
              Utility::PropertyTreeConversionException );
  FRENSIE_CHECK_THROW( Utility::fromPropertyTree<std::unordered_set<double> >( ptree.get_child( "value" ), unused_children ),
              Utility::PropertyTreeConversionException );
  FRENSIE_CHECK_THROW( Utility::fromPropertyTree<std::unordered_set<std::string> >( ptree.get_child( "value" ), unused_children ),
              Utility::PropertyTreeConversionException );

  std::unordered_set<int> int_unordered_set =
    Utility::fromPropertyTree<std::unordered_set<int> >( ptree.get_child( "inline array" ) );

  FRENSIE_CHECK_EQUAL( int_unordered_set.size(), 3 );
  FRENSIE_CHECK_EQUAL( int_unordered_set.count( -1 ), 1 );
  FRENSIE_CHECK_EQUAL( int_unordered_set.count( 0 ), 1 );
  FRENSIE_CHECK_EQUAL( int_unordered_set.count( 1 ), 1 );

  std::unordered_set<double> double_unordered_set =
    Utility::fromPropertyTree<std::unordered_set<double> >( ptree.get_child( "inline array" ) );

  FRENSIE_CHECK_EQUAL( double_unordered_set.size(), 3 );
  FRENSIE_CHECK_EQUAL( double_unordered_set.count( -1.0 ), 1 );
  FRENSIE_CHECK_EQUAL( double_unordered_set.count( 0.0 ), 1 );
  FRENSIE_CHECK_EQUAL( double_unordered_set.count( 1.0 ), 1 );

  std::unordered_set<std::string> string_unordered_set =
    Utility::fromPropertyTree<std::unordered_set<std::string> >( ptree.get_child( "inline array" ) );

  FRENSIE_CHECK_EQUAL( string_unordered_set.size(), 3 );
  FRENSIE_CHECK_EQUAL( string_unordered_set.count( "-1" ), 1 );
  FRENSIE_CHECK_EQUAL( string_unordered_set.count( "0" ), 1 );
  FRENSIE_CHECK_EQUAL( string_unordered_set.count( "1" ), 1 );

  int_unordered_set =  Utility::fromPropertyTree<std::unordered_set<int> >( ptree.get_child( "json array" ) );

  FRENSIE_CHECK_EQUAL( int_unordered_set.size(), 3 );
  FRENSIE_CHECK_EQUAL( int_unordered_set.count( -1 ), 1 );
  FRENSIE_CHECK_EQUAL( int_unordered_set.count( 0 ), 1 );
  FRENSIE_CHECK_EQUAL( int_unordered_set.count( 1 ), 1 );

  double_unordered_set = Utility::fromPropertyTree<std::unordered_set<double> >( ptree.get_child( "json array" ) );

  FRENSIE_CHECK_EQUAL( double_unordered_set.size(), 3 );
  FRENSIE_CHECK_EQUAL( double_unordered_set.count( -1.0 ), 1 );
  FRENSIE_CHECK_EQUAL( double_unordered_set.count( 0.0 ), 1 );
  FRENSIE_CHECK_EQUAL( double_unordered_set.count( 1.0 ), 1 );

  string_unordered_set = Utility::fromPropertyTree<std::unordered_set<std::string> >( ptree.get_child( "json array" ) );

  FRENSIE_CHECK_EQUAL( string_unordered_set.size(), 3 );
  FRENSIE_CHECK_EQUAL( string_unordered_set.count( "-1" ), 1 );
  FRENSIE_CHECK_EQUAL( string_unordered_set.count( "0" ), 1 );
  FRENSIE_CHECK_EQUAL( string_unordered_set.count( "1" ), 1 );
}

//---------------------------------------------------------------------------//
// Check that a property tree node can be converted to an associative container
FRENSIE_UNIT_TEST( PropertyTree, fromPropertyTree_associative_container )
{
  Utility::PropertyTree ptree;

  ptree.put( "-1", -1 );
  ptree.put( "0", 0 );
  ptree.put( "1", 1 );

  std::map<int,int> int_int_map =
    Utility::fromPropertyTree<std::map<int,int> >( ptree );

  FRENSIE_CHECK_EQUAL( int_int_map.size(), 3 );
  FRENSIE_CHECK_EQUAL( int_int_map[-1], -1 );
  FRENSIE_CHECK_EQUAL( int_int_map[0], 0 );
  FRENSIE_CHECK_EQUAL( int_int_map[1], 1 );

  std::unordered_map<int,int> int_int_unordered_map =
    Utility::fromPropertyTree<std::unordered_map<int,int> >( ptree );

  FRENSIE_CHECK_EQUAL( int_int_unordered_map.size(), 3 );
  FRENSIE_CHECK_EQUAL( int_int_unordered_map[-1], -1 );
  FRENSIE_CHECK_EQUAL( int_int_unordered_map[0], 0 );
  FRENSIE_CHECK_EQUAL( int_int_unordered_map[1], 1 );

  std::map<std::string,double> string_double_map =
    Utility::fromPropertyTree<std::map<std::string,double> >( ptree );

  FRENSIE_CHECK_EQUAL( string_double_map.size(), 3 );
  FRENSIE_CHECK_EQUAL( string_double_map["-1"], -1.0 );
  FRENSIE_CHECK_EQUAL( string_double_map["0"], 0.0 );
  FRENSIE_CHECK_EQUAL( string_double_map["1"], 1.0 );

  std::unordered_map<std::string,double> string_double_unordered_map =
    Utility::fromPropertyTree<std::unordered_map<std::string,double> >( ptree );

  FRENSIE_CHECK_EQUAL( string_double_unordered_map.size(), 3 );
  FRENSIE_CHECK_EQUAL( string_double_unordered_map["-1"], -1.0 );
  FRENSIE_CHECK_EQUAL( string_double_unordered_map["0"], 0.0 );
  FRENSIE_CHECK_EQUAL( string_double_unordered_map["1"], 1.0 );

  FRENSIE_CHECK_THROW( (Utility::fromPropertyTree<std::map<int,std::vector<int> > >( ptree )),
              Utility::PropertyTreeConversionException );
  FRENSIE_CHECK_THROW( (Utility::fromPropertyTree<std::map<std::string,std::vector<double> > >( ptree )),
              Utility::PropertyTreeConversionException );

  // Create a property tree with array (both inline and JSON) values
  ptree.clear();

  ptree.put( "-1", std::vector<int>({-1,0,1}) );
  ptree.put_child( "0", Utility::toPropertyTree( std::vector<int>({-1,1}), false ) );
  ptree.put( "1", std::vector<int>({0}) );

  FRENSIE_CHECK_THROW( (Utility::fromPropertyTree<std::map<int,int> >( ptree )),
              Utility::PropertyTreeConversionException );
  FRENSIE_CHECK_THROW( (Utility::fromPropertyTree<std::map<std::string,double> >( ptree )),
              Utility::PropertyTreeConversionException );

  std::map<int,std::vector<int> > int_vector_int_map =
    Utility::fromPropertyTree<std::map<int,std::vector<int> > >( ptree );

  FRENSIE_CHECK_EQUAL( int_vector_int_map.size(), 3 );
  FRENSIE_CHECK_EQUAL( int_vector_int_map.count( -1 ), 1 );
  FRENSIE_CHECK_EQUAL( int_vector_int_map[-1], std::vector<int>({-1,0,1}) );
  FRENSIE_CHECK_EQUAL( int_vector_int_map.count( 0 ), 1 );
  FRENSIE_CHECK_EQUAL( int_vector_int_map[0], std::vector<int>({-1,1}) );
  FRENSIE_CHECK_EQUAL( int_vector_int_map.count( 1 ), 1 );
  FRENSIE_CHECK_EQUAL( int_vector_int_map[1], std::vector<int>({0}) );

  std::unordered_map<int,std::vector<int> > int_vector_int_unordered_map =
    Utility::fromPropertyTree<std::unordered_map<int,std::vector<int> > >( ptree );

  FRENSIE_CHECK_EQUAL( int_vector_int_unordered_map.size(), 3 );
  FRENSIE_CHECK_EQUAL( int_vector_int_unordered_map.count( -1 ), 1 );
  FRENSIE_CHECK_EQUAL( int_vector_int_unordered_map[-1], std::vector<int>({-1,0,1}) );
  FRENSIE_CHECK_EQUAL( int_vector_int_unordered_map.count( 0 ), 1 );
  FRENSIE_CHECK_EQUAL( int_vector_int_unordered_map[0], std::vector<int>({-1,1}) );
  FRENSIE_CHECK_EQUAL( int_vector_int_unordered_map.count( 1 ), 1 );
  FRENSIE_CHECK_EQUAL( int_vector_int_unordered_map[1], std::vector<int>({0}) );

  std::map<std::string,std::vector<double> > string_vector_double_map =
    Utility::fromPropertyTree<std::map<std::string,std::vector<double> > >( ptree );

  FRENSIE_CHECK_EQUAL( string_vector_double_map.size(), 3 );
  FRENSIE_CHECK_EQUAL( string_vector_double_map.count( "-1" ), 1 );
  FRENSIE_CHECK_EQUAL( string_vector_double_map["-1"], std::vector<double>({-1.,0.,1.}) );
  FRENSIE_CHECK_EQUAL( string_vector_double_map.count( "0" ), 1 );
  FRENSIE_CHECK_EQUAL( string_vector_double_map["0"], std::vector<double>({-1.,1.}) );
  FRENSIE_CHECK_EQUAL( string_vector_double_map.count( "1" ), 1 );
  FRENSIE_CHECK_EQUAL( string_vector_double_map["1"], std::vector<double>({0.}) );

  std::unordered_map<std::string,std::vector<double> > string_vector_double_unordered_map =
    Utility::fromPropertyTree<std::unordered_map<std::string,std::vector<double> > >( ptree );

  FRENSIE_CHECK_EQUAL( string_vector_double_unordered_map.size(), 3 );
  FRENSIE_CHECK_EQUAL( string_vector_double_unordered_map.count( "-1" ), 1 );
  FRENSIE_CHECK_EQUAL( string_vector_double_unordered_map["-1"], std::vector<double>({-1.,0.,1.}) );
  FRENSIE_CHECK_EQUAL( string_vector_double_unordered_map.count( "0" ), 1 );
  FRENSIE_CHECK_EQUAL( string_vector_double_unordered_map["0"], std::vector<double>({-1.,1.}) );
  FRENSIE_CHECK_EQUAL( string_vector_double_unordered_map.count( "1" ), 1 );
  FRENSIE_CHECK_EQUAL( string_vector_double_unordered_map["1"], std::vector<double>({0.}) );

  // Create an invalid property tree (JSON Array)
  ptree = Utility::toPropertyTree( std::vector<int>({-1,0,1}), false );

  FRENSIE_CHECK_THROW( (Utility::fromPropertyTree<std::map<int,int> >( ptree )),
              Utility::PropertyTreeConversionException );
  FRENSIE_CHECK_THROW( (Utility::fromPropertyTree<std::map<std::string,double> >( ptree )),
              Utility::PropertyTreeConversionException );
  FRENSIE_CHECK_THROW( (Utility::fromPropertyTree<std::unordered_map<int,int> >( ptree )),
              Utility::PropertyTreeConversionException );
  FRENSIE_CHECK_THROW( (Utility::fromPropertyTree<std::unordered_map<std::string,double> >( ptree )),
              Utility::PropertyTreeConversionException );
  FRENSIE_CHECK_THROW( (Utility::fromPropertyTree<std::map<int,std::vector<int> > >( ptree )),
              Utility::PropertyTreeConversionException );
  FRENSIE_CHECK_THROW( (Utility::fromPropertyTree<std::map<std::string,std::vector<double> > >( ptree )),
              Utility::PropertyTreeConversionException );
  FRENSIE_CHECK_THROW( (Utility::fromPropertyTree<std::unordered_map<int,std::vector<int> > >( ptree )),
              Utility::PropertyTreeConversionException );
  FRENSIE_CHECK_THROW( (Utility::fromPropertyTree<std::unordered_map<std::string,std::vector<double> > >( ptree )),
              Utility::PropertyTreeConversionException );

  // Create an invalid property tree (repeated keys)
  ptree.put( "-1", -1 );
  ptree.add( "-1", 0 );

  FRENSIE_CHECK_THROW( (Utility::fromPropertyTree<std::map<int,int> >( ptree )),
              Utility::PropertyTreeConversionException );
  FRENSIE_CHECK_THROW( (Utility::fromPropertyTree<std::map<std::string,double> >( ptree )),
              Utility::PropertyTreeConversionException );
  FRENSIE_CHECK_THROW( (Utility::fromPropertyTree<std::unordered_map<int,int> >( ptree )),
              Utility::PropertyTreeConversionException );
  FRENSIE_CHECK_THROW( (Utility::fromPropertyTree<std::unordered_map<std::string,double> >( ptree )),
              Utility::PropertyTreeConversionException );

  // Create a property tree with nested trees
  ptree.clear();

  ptree.put_child( "-1", Utility::toPropertyTree( std::map<int,int>({std::make_pair(-1,-1),std::make_pair(0,0)}), false ) );
  ptree.put_child( "0", Utility::toPropertyTree( std::map<int,int>({std::make_pair(-1,-1),std::make_pair(1,1)}), true ) );
  ptree.put_child( "1", Utility::toPropertyTree( std::map<int,int>({std::make_pair(0,0),std::make_pair(1,1)}), false ) );

  std::map<int,std::map<int,int> > int_int_int_map_map =
    Utility::fromPropertyTree<decltype(int_int_int_map_map)>( ptree );

  FRENSIE_CHECK_EQUAL( int_int_int_map_map.size(), 3 );

  FRENSIE_CHECK_EQUAL( int_int_int_map_map.count( -1 ), 1 );
  FRENSIE_CHECK_EQUAL( int_int_int_map_map[-1].size(), 2 );
  FRENSIE_CHECK_EQUAL( int_int_int_map_map[-1].count( -1 ), 1 );
  FRENSIE_CHECK_EQUAL( int_int_int_map_map[-1][-1], -1 );
  FRENSIE_CHECK_EQUAL( int_int_int_map_map[-1].count( 0 ), 1 );
  FRENSIE_CHECK_EQUAL( int_int_int_map_map[-1][0], 0 );

  FRENSIE_CHECK_EQUAL( int_int_int_map_map.count( 0 ), 1 );
  FRENSIE_CHECK_EQUAL( int_int_int_map_map[0].size(), 2 );
  FRENSIE_CHECK_EQUAL( int_int_int_map_map[0].count( -1 ), 1 );
  FRENSIE_CHECK_EQUAL( int_int_int_map_map[0][-1], -1 );
  FRENSIE_CHECK_EQUAL( int_int_int_map_map[0].count( 1 ), 1 );
  FRENSIE_CHECK_EQUAL( int_int_int_map_map[0][1], 1 );

  FRENSIE_CHECK_EQUAL( int_int_int_map_map.count( 1 ), 1 );
  FRENSIE_CHECK_EQUAL( int_int_int_map_map[1].size(), 2 );
  FRENSIE_CHECK_EQUAL( int_int_int_map_map[1].count( 0 ), 1 );
  FRENSIE_CHECK_EQUAL( int_int_int_map_map[1][0], 0 );
  FRENSIE_CHECK_EQUAL( int_int_int_map_map[1].count( 1 ), 1 );
  FRENSIE_CHECK_EQUAL( int_int_int_map_map[1][1], 1 );

  // Create a property tree with an inline nested map
  ptree.clear();
  ptree = Utility::toPropertyTree( int_int_int_map_map, true );

  int_int_int_map_map.clear();
  int_int_int_map_map = Utility::fromPropertyTree<decltype(int_int_int_map_map)>( ptree );

  FRENSIE_CHECK_EQUAL( int_int_int_map_map.size(), 3 );

  FRENSIE_CHECK_EQUAL( int_int_int_map_map.count( -1 ), 1 );
  FRENSIE_CHECK_EQUAL( int_int_int_map_map[-1].size(), 2 );
  FRENSIE_CHECK_EQUAL( int_int_int_map_map[-1].count( -1 ), 1 );
  FRENSIE_CHECK_EQUAL( int_int_int_map_map[-1][-1], -1 );
  FRENSIE_CHECK_EQUAL( int_int_int_map_map[-1].count( 0 ), 1 );
  FRENSIE_CHECK_EQUAL( int_int_int_map_map[-1][0], 0 );

  FRENSIE_CHECK_EQUAL( int_int_int_map_map.count( 0 ), 1 );
  FRENSIE_CHECK_EQUAL( int_int_int_map_map[0].size(), 2 );
  FRENSIE_CHECK_EQUAL( int_int_int_map_map[0].count( -1 ), 1 );
  FRENSIE_CHECK_EQUAL( int_int_int_map_map[0][-1], -1 );
  FRENSIE_CHECK_EQUAL( int_int_int_map_map[0].count( 1 ), 1 );
  FRENSIE_CHECK_EQUAL( int_int_int_map_map[0][1], 1 );

  FRENSIE_CHECK_EQUAL( int_int_int_map_map.count( 1 ), 1 );
  FRENSIE_CHECK_EQUAL( int_int_int_map_map[1].size(), 2 );
  FRENSIE_CHECK_EQUAL( int_int_int_map_map[1].count( 0 ), 1 );
  FRENSIE_CHECK_EQUAL( int_int_int_map_map[1][0], 0 );
  FRENSIE_CHECK_EQUAL( int_int_int_map_map[1].count( 1 ), 1 );
  FRENSIE_CHECK_EQUAL( int_int_int_map_map[1][1], 1 );
}

//---------------------------------------------------------------------------//
// Check that a property tree node can be converted to an associative container
FRENSIE_UNIT_TEST( PropertyTree, fromPropertyTree_VariantMap )
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

  FRENSIE_CHECK_EQUAL( map.size(), 4 );
  FRENSIE_CHECK_EQUAL( unused_children.size(), 0 );
  FRENSIE_CHECK_EQUAL( map["inline array"].toVector().size(), 3 );
  FRENSIE_CHECK_EQUAL( map["inline array"].toVector()[0].toInt(), -1 );
  FRENSIE_CHECK_EQUAL( map["inline array"].toVector()[1].toInt(), 0 );
  FRENSIE_CHECK_EQUAL( map["inline array"].toVector()[2].toInt(), 1 );
  FRENSIE_CHECK_EQUAL( map["json array"].toVector().size(), 3 );
  FRENSIE_CHECK_EQUAL( map["json array"].toVector()[0].toInt(), -1 );
  FRENSIE_CHECK_EQUAL( map["json array"].toVector()[1].toInt(), 0 );
  FRENSIE_CHECK_EQUAL( map["json array"].toVector()[2].toInt(), 1 );
  FRENSIE_CHECK_EQUAL( map["child tree"].toMap().size(), 2 );
  FRENSIE_CHECK_EQUAL( map["child tree"].toMap()["level 2 string"].toString(), "test string" );
  FRENSIE_CHECK_EQUAL( map["child tree"].toMap()["level 2 inline array"].compactify().toString(), "{test,string,array}" );
  FRENSIE_CHECK_EQUAL( map["repeated_value"].toVector().size(), 9 );
  FRENSIE_CHECK_EQUAL( map["repeated_value"].toVector()[0].toBool(), true );
  FRENSIE_CHECK_EQUAL( map["repeated_value"].toVector()[1].toDouble(), -1.0 );
  FRENSIE_CHECK_EQUAL( map["repeated_value"].toVector()[2].toDouble(), 0.0 );
  FRENSIE_CHECK_EQUAL( map["repeated_value"].toVector()[3].toDouble(), 1.0 );
  FRENSIE_CHECK_EQUAL( map["repeated_value"].toVector()[4].toInt(), -1 );
  FRENSIE_CHECK_EQUAL( map["repeated_value"].toVector()[5].toInt(), 0 );
  FRENSIE_CHECK_EQUAL( map["repeated_value"].toVector()[6].toInt(), 1 );
  FRENSIE_CHECK_EQUAL( (map["repeated_value"].toVector()[7].toType<std::pair<std::string,Utility::Variant> >().first), "level 2 inline array" );
  FRENSIE_CHECK_EQUAL( (map["repeated_value"].toVector()[7].toType<std::pair<std::string,Utility::Variant> >().second.compactify().toString()), "{test,string,array}" );
  FRENSIE_CHECK_EQUAL( (map["repeated_value"].toVector()[8].toType<std::pair<std::string,std::string> >().first), "level 2 string" );
  FRENSIE_CHECK_EQUAL( (map["repeated_value"].toVector()[8].toType<std::pair<std::string,std::string> >().second), "test string" );

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

  FRENSIE_CHECK_EQUAL( map.size(), 4 );
  FRENSIE_CHECK_EQUAL( map["inline array"].toVector().size(), 3 );
  FRENSIE_CHECK_EQUAL( map["inline array"].toVector()[0].toInt(), -1 );
  FRENSIE_CHECK_EQUAL( map["inline array"].toVector()[1].toInt(), 0 );
  FRENSIE_CHECK_EQUAL( map["inline array"].toVector()[2].toInt(), 1 );
  FRENSIE_CHECK_EQUAL( map["json array"].toVector().size(), 3 );
  FRENSIE_CHECK_EQUAL( map["json array"].toVector()[0].toInt(), -1 );
  FRENSIE_CHECK_EQUAL( map["json array"].toVector()[1].toInt(), 0 );
  FRENSIE_CHECK_EQUAL( map["json array"].toVector()[2].toInt(), 1 );
  FRENSIE_CHECK_EQUAL( map["child tree"].toMap().size(), 2 );
  FRENSIE_CHECK_EQUAL( map["child tree"].toMap()["level 2 string"].toString(), "test string" );
  FRENSIE_CHECK_EQUAL( map["child tree"].toMap()["level 2 inline array"].compactify().toString(), "{test,string,array}" );
  FRENSIE_CHECK_EQUAL( map["repeated_value"].toVector().size(), 9 );
  FRENSIE_CHECK_EQUAL( map["repeated_value"].toVector()[0].toDouble(), -1.0 );
  FRENSIE_CHECK_EQUAL( map["repeated_value"].toVector()[1].toDouble(), 0.0 );
  FRENSIE_CHECK_EQUAL( map["repeated_value"].toVector()[2].toDouble(), 1.0 );
  FRENSIE_CHECK_EQUAL( map["repeated_value"].toVector()[3].toBool(), true );
  FRENSIE_CHECK_EQUAL( map["repeated_value"].toVector()[4].toInt(), -1 );
  FRENSIE_CHECK_EQUAL( map["repeated_value"].toVector()[5].toInt(), 0 );
  FRENSIE_CHECK_EQUAL( map["repeated_value"].toVector()[6].toInt(), 1 );
  FRENSIE_CHECK_EQUAL( (map["repeated_value"].toVector()[7].toType<std::pair<std::string,Utility::Variant> >().first), "level 2 inline array" );
  FRENSIE_CHECK_EQUAL( (map["repeated_value"].toVector()[7].toType<std::pair<std::string,Utility::Variant> >().second.compactify().toString()), "{test,string,array}" );
  FRENSIE_CHECK_EQUAL( (map["repeated_value"].toVector()[8].toType<std::pair<std::string,std::string> >().first), "level 2 string" );
  FRENSIE_CHECK_EQUAL( (map["repeated_value"].toVector()[8].toType<std::pair<std::string,std::string> >().second), "test string" );

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

  FRENSIE_CHECK_EQUAL( map.size(), 4 );
  FRENSIE_CHECK_EQUAL( map["inline array"].toVector().size(), 3 );
  FRENSIE_CHECK_EQUAL( map["inline array"].toVector()[0].toInt(), -1 );
  FRENSIE_CHECK_EQUAL( map["inline array"].toVector()[1].toInt(), 0 );
  FRENSIE_CHECK_EQUAL( map["inline array"].toVector()[2].toInt(), 1 );
  FRENSIE_CHECK_EQUAL( map["json array"].toVector().size(), 3 );
  FRENSIE_CHECK_EQUAL( map["json array"].toVector()[0].toInt(), -1 );
  FRENSIE_CHECK_EQUAL( map["json array"].toVector()[1].toInt(), 0 );
  FRENSIE_CHECK_EQUAL( map["json array"].toVector()[2].toInt(), 1 );
  FRENSIE_CHECK_EQUAL( map["child tree"].toMap().size(), 2 );
  FRENSIE_CHECK_EQUAL( map["child tree"].toMap()["level 2 string"].toString(), "test string" );
  FRENSIE_CHECK_EQUAL( map["child tree"].toMap()["level 2 inline array"].compactify().toString(), "{test,string,array}" );
  FRENSIE_CHECK_EQUAL( map["repeated_value"].toVector().size(), 9 );
  FRENSIE_CHECK_EQUAL( map["repeated_value"].toVector()[0].toInt(), -1 );
  FRENSIE_CHECK_EQUAL( map["repeated_value"].toVector()[1].toInt(), 0 );
  FRENSIE_CHECK_EQUAL( map["repeated_value"].toVector()[2].toInt(), 1 );
  FRENSIE_CHECK_EQUAL( map["repeated_value"].toVector()[3].toDouble(), -1.0 );
  FRENSIE_CHECK_EQUAL( map["repeated_value"].toVector()[4].toDouble(), 0.0 );
  FRENSIE_CHECK_EQUAL( map["repeated_value"].toVector()[5].toDouble(), 1.0 );
  FRENSIE_CHECK_EQUAL( map["repeated_value"].toVector()[6].toBool(), true );
  FRENSIE_CHECK_EQUAL( (map["repeated_value"].toVector()[7].toType<std::pair<std::string,Utility::Variant> >().first), "level 2 inline array" );
  FRENSIE_CHECK_EQUAL( (map["repeated_value"].toVector()[7].toType<std::pair<std::string,Utility::Variant> >().second.compactify().toString()), "{test,string,array}" );
  FRENSIE_CHECK_EQUAL( (map["repeated_value"].toVector()[8].toType<std::pair<std::string,std::string> >().first), "level 2 string" );
  FRENSIE_CHECK_EQUAL( (map["repeated_value"].toVector()[8].toType<std::pair<std::string,std::string> >().second), "test string" );

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

  FRENSIE_CHECK_EQUAL( map.size(), 4 );
  FRENSIE_CHECK_EQUAL( map["inline array"].toVector().size(), 3 );
  FRENSIE_CHECK_EQUAL( map["inline array"].toVector()[0].toInt(), -1 );
  FRENSIE_CHECK_EQUAL( map["inline array"].toVector()[1].toInt(), 0 );
  FRENSIE_CHECK_EQUAL( map["inline array"].toVector()[2].toInt(), 1 );
  FRENSIE_CHECK_EQUAL( map["json array"].toVector().size(), 3 );
  FRENSIE_CHECK_EQUAL( map["json array"].toVector()[0].toInt(), -1 );
  FRENSIE_CHECK_EQUAL( map["json array"].toVector()[1].toInt(), 0 );
  FRENSIE_CHECK_EQUAL( map["json array"].toVector()[2].toInt(), 1 );
  FRENSIE_CHECK_EQUAL( map["child tree"].toMap().size(), 2 );
  FRENSIE_CHECK_EQUAL( map["child tree"].toMap()["level 2 string"].toString(), "test string" );
  FRENSIE_CHECK_EQUAL( map["child tree"].toMap()["level 2 inline array"].compactify().toString(), "{test,string,array}" );
  FRENSIE_CHECK_EQUAL( map["repeated_value"].toVector().size(), 9 );
  FRENSIE_CHECK_EQUAL( (map["repeated_value"].toVector()[0].toType<std::pair<std::string,Utility::Variant> >().first), "level 2 inline array" );
  FRENSIE_CHECK_EQUAL( (map["repeated_value"].toVector()[0].toType<std::pair<std::string,Utility::Variant> >().second.compactify().toString()), "{test,string,array}" );
  FRENSIE_CHECK_EQUAL( (map["repeated_value"].toVector()[1].toType<std::pair<std::string,std::string> >().first), "level 2 string" );
  FRENSIE_CHECK_EQUAL( (map["repeated_value"].toVector()[1].toType<std::pair<std::string,std::string> >().second), "test string" );
  FRENSIE_CHECK_EQUAL( map["repeated_value"].toVector()[2].toInt(), -1 );
  FRENSIE_CHECK_EQUAL( map["repeated_value"].toVector()[3].toInt(), 0 );
  FRENSIE_CHECK_EQUAL( map["repeated_value"].toVector()[4].toInt(), 1 );
  FRENSIE_CHECK_EQUAL( map["repeated_value"].toVector()[5].toDouble(), -1.0 );
  FRENSIE_CHECK_EQUAL( map["repeated_value"].toVector()[6].toDouble(), 0.0 );
  FRENSIE_CHECK_EQUAL( map["repeated_value"].toVector()[7].toDouble(), 1.0 );
  FRENSIE_CHECK_EQUAL( map["repeated_value"].toVector()[8].toBool(), true );

  FRENSIE_CHECK_THROW( Utility::fromPropertyTree<Utility::VariantMap>( ptree.get_child( "json array" ) ),
              Utility::PropertyTreeConversionException );

  FRENSIE_CHECK_NO_THROW( boost::property_tree::write_json( "test_maps.json", ptree ) );
}

//---------------------------------------------------------------------------//
// Check that a property tree can be converted to a string
FRENSIE_UNIT_TEST( PropertyTree, toString )
{
  Utility::PropertyTree ptree;

  FRENSIE_CHECK_EQUAL( Utility::toString( ptree ), "{}" );

  ptree.add( "repeated_value", true );

  FRENSIE_CHECK_EQUAL( Utility::toString( ptree ), "{\"repeated_value\":\"true\"}" );

  ptree.add( "repeated_value", std::vector<double>({-1.0, 0.0, 1.0}) );

  FRENSIE_CHECK_EQUAL( Utility::toString( ptree ), "{\"repeated_value\":\"true\",\"repeated_value\":\"{-1.000000000000000000e+00, 0.000000000000000000e+00, 1.000000000000000000e+00}\"}" );

  ptree.put( "inline array", std::vector<int>({-1, 0, 1}) );

  FRENSIE_CHECK_EQUAL( Utility::toString( ptree ), "{\"repeated_value\":\"true\",\"repeated_value\":\"{-1.000000000000000000e+00, 0.000000000000000000e+00, 1.000000000000000000e+00}\",\"inline array\":\"{-1, 0, 1}\"}" );

  // Construct level 1 nodes
  {
    Utility::PropertyTree level_1_ptree;

    // Construct level 2 nodes
    level_1_ptree.put( "level 2 string", "test string" );
    level_1_ptree.put( "level 2 inline array", std::vector<std::string>({"test", "string", "array"}) );

    ptree.add_child( "child tree", level_1_ptree );
  }

  FRENSIE_CHECK_EQUAL( Utility::toString( ptree ), "{\"repeated_value\":\"true\",\"repeated_value\":\"{-1.000000000000000000e+00, 0.000000000000000000e+00, 1.000000000000000000e+00}\",\"inline array\":\"{-1, 0, 1}\",\"child tree\":{\"level 2 string\":\"test string\",\"level 2 inline array\":\"{test, string, array}\"}}" );

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

  FRENSIE_CHECK_EQUAL( Utility::toString( ptree ), "{\"repeated_value\":\"true\",\"repeated_value\":\"{-1.000000000000000000e+00, 0.000000000000000000e+00, 1.000000000000000000e+00}\",\"inline array\":\"{-1, 0, 1}\",\"child tree\":{\"level 2 string\":\"test string\",\"level 2 inline array\":\"{test, string, array}\"},\"json array\":[\"-1\",\"0\",\"1\"]}" );
}

//---------------------------------------------------------------------------//
// Check that a property tree can be placed in a stream
FRENSIE_UNIT_TEST( PropertyTree, toStream )
{
  Utility::PropertyTree ptree;

  std::ostringstream oss;

  Utility::toStream( oss, ptree );

  FRENSIE_CHECK_EQUAL( boost::algorithm::trim_copy(oss.str()), "{}" );

  oss.str( "" );
  oss.clear();

  ptree.add( "repeated_value", true );

  Utility::toStream( oss, ptree );

  FRENSIE_CHECK_EQUAL( boost::algorithm::trim_copy(oss.str()), "{\"repeated_value\":\"true\"}" );

  oss.str( "" );
  oss.clear();

  ptree.add( "repeated_value", std::vector<double>({-1.0, 0.0, 1.0}) );

  Utility::toStream( oss, ptree );

  FRENSIE_CHECK_EQUAL( boost::algorithm::trim_copy(oss.str()), "{\"repeated_value\":\"true\",\"repeated_value\":\"{-1.000000000000000000e+00, 0.000000000000000000e+00, 1.000000000000000000e+00}\"}" );

  oss.str( "" );
  oss.clear();

  ptree.put( "inline array", std::vector<int>({-1, 0, 1}) );

  Utility::toStream( oss, ptree );

  FRENSIE_CHECK_EQUAL( boost::algorithm::trim_copy(oss.str()), "{\"repeated_value\":\"true\",\"repeated_value\":\"{-1.000000000000000000e+00, 0.000000000000000000e+00, 1.000000000000000000e+00}\",\"inline array\":\"{-1, 0, 1}\"}" );

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

  FRENSIE_CHECK_EQUAL( boost::algorithm::trim_copy(oss.str()), "{\"repeated_value\":\"true\",\"repeated_value\":\"{-1.000000000000000000e+00, 0.000000000000000000e+00, 1.000000000000000000e+00}\",\"inline array\":\"{-1, 0, 1}\",\"child tree\":{\"level 2 string\":\"test string\",\"level 2 inline array\":\"{test, string, array}\"}}" );

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

  FRENSIE_CHECK_EQUAL( boost::algorithm::trim_copy(oss.str()), "{\"repeated_value\":\"true\",\"repeated_value\":\"{-1.000000000000000000e+00, 0.000000000000000000e+00, 1.000000000000000000e+00}\",\"inline array\":\"{-1, 0, 1}\",\"child tree\":{\"level 2 string\":\"test string\",\"level 2 inline array\":\"{test, string, array}\"},\"json array\":[\"-1\",\"0\",\"1\"]}" );
}

//---------------------------------------------------------------------------//
// Check that a property tree can be placed in a stream
FRENSIE_UNIT_TEST( PropertyTree, ostream_operator )
{
  Utility::PropertyTree ptree;

  std::ostringstream oss;

  oss << ptree;

  FRENSIE_CHECK_EQUAL( boost::algorithm::trim_copy(oss.str()), "{}" );

  oss.str( "" );
  oss.clear();

  ptree.add( "repeated_value", true );

  oss << ptree;

  FRENSIE_CHECK_EQUAL( boost::algorithm::trim_copy(oss.str()), "{\"repeated_value\":\"true\"}" );

  oss.str( "" );
  oss.clear();

  ptree.add( "repeated_value", std::vector<double>({-1.0, 0.0, 1.0}) );

  oss << ptree;

  FRENSIE_CHECK_EQUAL( boost::algorithm::trim_copy(oss.str()), "{\"repeated_value\":\"true\",\"repeated_value\":\"{-1.000000000000000000e+00, 0.000000000000000000e+00, 1.000000000000000000e+00}\"}" );

  oss.str( "" );
  oss.clear();

  ptree.put( "inline array", std::vector<int>({-1, 0, 1}) );

  oss << ptree;

  FRENSIE_CHECK_EQUAL( boost::algorithm::trim_copy(oss.str()), "{\"repeated_value\":\"true\",\"repeated_value\":\"{-1.000000000000000000e+00, 0.000000000000000000e+00, 1.000000000000000000e+00}\",\"inline array\":\"{-1, 0, 1}\"}" );

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

  FRENSIE_CHECK_EQUAL( boost::algorithm::trim_copy(oss.str()), "{\"repeated_value\":\"true\",\"repeated_value\":\"{-1.000000000000000000e+00, 0.000000000000000000e+00, 1.000000000000000000e+00}\",\"inline array\":\"{-1, 0, 1}\",\"child tree\":{\"level 2 string\":\"test string\",\"level 2 inline array\":\"{test, string, array}\"}}" );

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

  FRENSIE_CHECK_EQUAL( boost::algorithm::trim_copy(oss.str()), "{\"repeated_value\":\"true\",\"repeated_value\":\"{-1.000000000000000000e+00, 0.000000000000000000e+00, 1.000000000000000000e+00}\",\"inline array\":\"{-1, 0, 1}\",\"child tree\":{\"level 2 string\":\"test string\",\"level 2 inline array\":\"{test, string, array}\"},\"json array\":[\"-1\",\"0\",\"1\"]}" );
}

//---------------------------------------------------------------------------//
// Check that a property tree can be created from a string
FRENSIE_UNIT_TEST( PropertyTree, fromString )
{
  Utility::PropertyTree ptree = Utility::fromString<Utility::PropertyTree>( "{}" );

  FRENSIE_CHECK_EQUAL( ptree.size(), 0 );

  ptree = Utility::fromString<Utility::PropertyTree>( "{\"repeated_value\":\"true\"}" );

  FRENSIE_CHECK_EQUAL( ptree.size(), 1 );
  FRENSIE_CHECK_EQUAL( ptree.get<bool>( "repeated_value" ), true );

  ptree = Utility::fromString<Utility::PropertyTree>( "{\"repeated_value\":\"true\",\"repeated_value\":\"{-1.000000000000000000e+00, 0.000000000000000000e+00, 1.000000000000000000e+00}\"}" );

  FRENSIE_CHECK_EQUAL( ptree.size(), 2 );
  FRENSIE_CHECK_EQUAL( ptree.count( "repeated_value" ), 2 );

  Utility::VariantMap map =
    Utility::fromPropertyTree<Utility::VariantMap>( ptree );

  FRENSIE_CHECK_EQUAL( map.size(), 1 );
  FRENSIE_CHECK_EQUAL( map["repeated_value"].toVector().size(), 4 );
  FRENSIE_CHECK_EQUAL( map["repeated_value"].toVector()[0].toBool(), true );
  FRENSIE_CHECK_EQUAL( map["repeated_value"].toVector()[1].toDouble(), -1.0 );
  FRENSIE_CHECK_EQUAL( map["repeated_value"].toVector()[2].toDouble(), 0.0 );
  FRENSIE_CHECK_EQUAL( map["repeated_value"].toVector()[3].toDouble(), 1.0 );

  ptree = Utility::fromString<Utility::PropertyTree>( "{\"repeated_value\":\"true\",\"repeated_value\":\"{-1.000000000000000000e+00, 0.000000000000000000e+00, 1.000000000000000000e+00}\",\"inline array\":\"{-1, 0, 1}\"}" );

  map = Utility::fromPropertyTree<Utility::VariantMap>( ptree );

  FRENSIE_CHECK_EQUAL( map.size(), 2 );
  FRENSIE_CHECK_EQUAL( map["repeated_value"].toVector().size(), 4 );
  FRENSIE_CHECK_EQUAL( map["repeated_value"].toVector()[0].toBool(), true );
  FRENSIE_CHECK_EQUAL( map["repeated_value"].toVector()[1].toDouble(), -1.0 );
  FRENSIE_CHECK_EQUAL( map["repeated_value"].toVector()[2].toDouble(), 0.0 );
  FRENSIE_CHECK_EQUAL( map["repeated_value"].toVector()[3].toDouble(), 1.0 );
  FRENSIE_CHECK_EQUAL( map["inline array"].toVector().size(), 3 );
  FRENSIE_CHECK_EQUAL( map["inline array"].toVector()[0].toInt(), -1 );
  FRENSIE_CHECK_EQUAL( map["inline array"].toVector()[1].toInt(), 0 );
  FRENSIE_CHECK_EQUAL( map["inline array"].toVector()[2].toInt(), 1 );

  ptree = Utility::fromString<Utility::PropertyTree>( "{\"repeated_value\":\"true\",\"repeated_value\":\"{-1.000000000000000000e+00, 0.000000000000000000e+00, 1.000000000000000000e+00}\",\"inline array\":\"{-1, 0, 1}\",\"child tree\":{\"level 2 string\":\"test string\",\"level 2 inline array\":\"{test, string, array}\"}}" );

  map = Utility::fromPropertyTree<Utility::VariantMap>( ptree );

  FRENSIE_CHECK_EQUAL( map.size(), 3 );
  FRENSIE_CHECK_EQUAL( map["repeated_value"].toVector().size(), 4 );
  FRENSIE_CHECK_EQUAL( map["repeated_value"].toVector()[0].toBool(), true );
  FRENSIE_CHECK_EQUAL( map["repeated_value"].toVector()[1].toDouble(), -1.0 );
  FRENSIE_CHECK_EQUAL( map["repeated_value"].toVector()[2].toDouble(), 0.0 );
  FRENSIE_CHECK_EQUAL( map["repeated_value"].toVector()[3].toDouble(), 1.0 );
  FRENSIE_CHECK_EQUAL( map["inline array"].toVector().size(), 3 );
  FRENSIE_CHECK_EQUAL( map["inline array"].toVector()[0].toInt(), -1 );
  FRENSIE_CHECK_EQUAL( map["inline array"].toVector()[1].toInt(), 0 );
  FRENSIE_CHECK_EQUAL( map["inline array"].toVector()[2].toInt(), 1 );
  FRENSIE_CHECK_EQUAL( map["child tree"].toMap().size(), 2 );
  FRENSIE_CHECK_EQUAL( map["child tree"].toMap()["level 2 string"].toString(), "test string" );
  FRENSIE_CHECK_EQUAL( map["child tree"].toMap()["level 2 inline array"].compactify().toString(), "{test,string,array}" );

  ptree = Utility::fromString<Utility::PropertyTree>( "{\"repeated_value\":\"true\",\"repeated_value\":\"{-1.000000000000000000e+00, 0.000000000000000000e+00, 1.000000000000000000e+00}\",\"inline array\":\"{-1, 0, 1}\",\"child tree\":{\"level 2 string\":\"test string\",\"level 2 inline array\":\"{test, string, array}\"},\"json array\":[\"-1\",\"0\",\"1\"]}" );

  map = Utility::fromPropertyTree<Utility::VariantMap>( ptree );

  FRENSIE_CHECK_EQUAL( map.size(), 4 );
  FRENSIE_CHECK_EQUAL( map["repeated_value"].toVector().size(), 4 );
  FRENSIE_CHECK_EQUAL( map["repeated_value"].toVector()[0].toBool(), true );
  FRENSIE_CHECK_EQUAL( map["repeated_value"].toVector()[1].toDouble(), -1.0 );
  FRENSIE_CHECK_EQUAL( map["repeated_value"].toVector()[2].toDouble(), 0.0 );
  FRENSIE_CHECK_EQUAL( map["repeated_value"].toVector()[3].toDouble(), 1.0 );
  FRENSIE_CHECK_EQUAL( map["inline array"].toVector().size(), 3 );
  FRENSIE_CHECK_EQUAL( map["inline array"].toVector()[0].toInt(), -1 );
  FRENSIE_CHECK_EQUAL( map["inline array"].toVector()[1].toInt(), 0 );
  FRENSIE_CHECK_EQUAL( map["inline array"].toVector()[2].toInt(), 1 );
  FRENSIE_CHECK_EQUAL( map["child tree"].toMap().size(), 2 );
  FRENSIE_CHECK_EQUAL( map["child tree"].toMap()["level 2 string"].toString(), "test string" );
  FRENSIE_CHECK_EQUAL( map["child tree"].toMap()["level 2 inline array"].compactify().toString(), "{test,string,array}" );
  FRENSIE_CHECK_EQUAL( map["json array"].toVector().size(), 3 );
  FRENSIE_CHECK_EQUAL( map["json array"].toVector()[0].toInt(), -1 );
  FRENSIE_CHECK_EQUAL( map["json array"].toVector()[1].toInt(), 0 );
  FRENSIE_CHECK_EQUAL( map["json array"].toVector()[2].toInt(), 1 );
}

//---------------------------------------------------------------------------//
// Check that a property tree can be extracted from a stream
FRENSIE_UNIT_TEST( PropertyTree, fromStream )
{
  Utility::PropertyTree ptree;

  std::istringstream iss( "{}" );

  Utility::fromStream( iss, ptree );

  FRENSIE_CHECK_EQUAL( ptree.size(), 0 );

  iss.str( "{\"repeated_value\":\"true\"}" );
  iss.clear();

  Utility::fromStream( iss, ptree );

  FRENSIE_CHECK_EQUAL( ptree.size(), 1 );
  FRENSIE_CHECK_EQUAL( ptree.get<bool>( "repeated_value" ), true );

  iss.str( "{\"repeated_value\":\"true\",\"repeated_value\":\"{-1.000000000000000000e+00, 0.000000000000000000e+00, 1.000000000000000000e+00}\"}" );
  iss.clear();

  Utility::fromStream( iss, ptree );

  FRENSIE_CHECK_EQUAL( ptree.size(), 2 );
  FRENSIE_CHECK_EQUAL( ptree.count( "repeated_value" ), 2 );

  Utility::VariantMap map = Utility::fromPropertyTree<Utility::VariantMap>( ptree );

  FRENSIE_CHECK_EQUAL( map.size(), 1 );
  FRENSIE_CHECK_EQUAL( map["repeated_value"].toVector().size(), 4 );
  FRENSIE_CHECK_EQUAL( map["repeated_value"].toVector()[0].toBool(), true );
  FRENSIE_CHECK_EQUAL( map["repeated_value"].toVector()[1].toDouble(), -1.0 );
  FRENSIE_CHECK_EQUAL( map["repeated_value"].toVector()[2].toDouble(), 0.0 );
  FRENSIE_CHECK_EQUAL( map["repeated_value"].toVector()[3].toDouble(), 1.0 );

  iss.str( "{\"repeated_value\":\"true\",\"repeated_value\":\"{-1.000000000000000000e+00, 0.000000000000000000e+00, 1.000000000000000000e+00}\",\"inline array\":\"{-1, 0, 1}\"}" );

  Utility::fromStream( iss, ptree );

  map = Utility::fromPropertyTree<Utility::VariantMap>( ptree );

  FRENSIE_CHECK_EQUAL( map.size(), 2 );
  FRENSIE_CHECK_EQUAL( map["repeated_value"].toVector().size(), 4 );
  FRENSIE_CHECK_EQUAL( map["repeated_value"].toVector()[0].toBool(), true );
  FRENSIE_CHECK_EQUAL( map["repeated_value"].toVector()[1].toDouble(), -1.0 );
  FRENSIE_CHECK_EQUAL( map["repeated_value"].toVector()[2].toDouble(), 0.0 );
  FRENSIE_CHECK_EQUAL( map["repeated_value"].toVector()[3].toDouble(), 1.0 );
  FRENSIE_CHECK_EQUAL( map["inline array"].toVector().size(), 3 );
  FRENSIE_CHECK_EQUAL( map["inline array"].toVector()[0].toInt(), -1 );
  FRENSIE_CHECK_EQUAL( map["inline array"].toVector()[1].toInt(), 0 );
  FRENSIE_CHECK_EQUAL( map["inline array"].toVector()[2].toInt(), 1 );

  iss.str( "{\"repeated_value\":\"true\",\"repeated_value\":\"{-1.000000000000000000e+00, 0.000000000000000000e+00, 1.000000000000000000e+00}\",\"inline array\":\"{-1, 0, 1}\",\"child tree\":{\"level 2 string\":\"test string\",\"level 2 inline array\":\"{test, string, array}\"}}" );
  iss.clear();

  Utility::fromStream( iss, ptree );

  map = Utility::fromPropertyTree<Utility::VariantMap>( ptree );

  FRENSIE_CHECK_EQUAL( map.size(), 3 );
  FRENSIE_CHECK_EQUAL( map["repeated_value"].toVector().size(), 4 );
  FRENSIE_CHECK_EQUAL( map["repeated_value"].toVector()[0].toBool(), true );
  FRENSIE_CHECK_EQUAL( map["repeated_value"].toVector()[1].toDouble(), -1.0 );
  FRENSIE_CHECK_EQUAL( map["repeated_value"].toVector()[2].toDouble(), 0.0 );
  FRENSIE_CHECK_EQUAL( map["repeated_value"].toVector()[3].toDouble(), 1.0 );
  FRENSIE_CHECK_EQUAL( map["inline array"].toVector().size(), 3 );
  FRENSIE_CHECK_EQUAL( map["inline array"].toVector()[0].toInt(), -1 );
  FRENSIE_CHECK_EQUAL( map["inline array"].toVector()[1].toInt(), 0 );
  FRENSIE_CHECK_EQUAL( map["inline array"].toVector()[2].toInt(), 1 );
  FRENSIE_CHECK_EQUAL( map["child tree"].toMap().size(), 2 );
  FRENSIE_CHECK_EQUAL( map["child tree"].toMap()["level 2 string"].toString(), "test string" );
  FRENSIE_CHECK_EQUAL( map["child tree"].toMap()["level 2 inline array"].compactify().toString(), "{test,string,array}" );

  iss.str( "{\"repeated_value\":\"true\",\"repeated_value\":\"{-1.000000000000000000e+00, 0.000000000000000000e+00, 1.000000000000000000e+00}\",\"inline array\":\"{-1, 0, 1}\",\"child tree\":{\"level 2 string\":\"test string\",\"level 2 inline array\":\"{test, string, array}\"},\"json array\":[\"-1\",\"0\",\"1\"]}" );
  iss.clear();

  Utility::fromStream( iss, ptree );

  map = Utility::fromPropertyTree<Utility::VariantMap>( ptree );

  FRENSIE_CHECK_EQUAL( map.size(), 4 );
  FRENSIE_CHECK_EQUAL( map["repeated_value"].toVector().size(), 4 );
  FRENSIE_CHECK_EQUAL( map["repeated_value"].toVector()[0].toBool(), true );
  FRENSIE_CHECK_EQUAL( map["repeated_value"].toVector()[1].toDouble(), -1.0 );
  FRENSIE_CHECK_EQUAL( map["repeated_value"].toVector()[2].toDouble(), 0.0 );
  FRENSIE_CHECK_EQUAL( map["repeated_value"].toVector()[3].toDouble(), 1.0 );
  FRENSIE_CHECK_EQUAL( map["inline array"].toVector().size(), 3 );
  FRENSIE_CHECK_EQUAL( map["inline array"].toVector()[0].toInt(), -1 );
  FRENSIE_CHECK_EQUAL( map["inline array"].toVector()[1].toInt(), 0 );
  FRENSIE_CHECK_EQUAL( map["inline array"].toVector()[2].toInt(), 1 );
  FRENSIE_CHECK_EQUAL( map["child tree"].toMap().size(), 2 );
  FRENSIE_CHECK_EQUAL( map["child tree"].toMap()["level 2 string"].toString(), "test string" );
  FRENSIE_CHECK_EQUAL( map["child tree"].toMap()["level 2 inline array"].compactify().toString(), "{test,string,array}" );
  FRENSIE_CHECK_EQUAL( map["json array"].toVector().size(), 3 );
  FRENSIE_CHECK_EQUAL( map["json array"].toVector()[0].toInt(), -1 );
  FRENSIE_CHECK_EQUAL( map["json array"].toVector()[1].toInt(), 0 );
  FRENSIE_CHECK_EQUAL( map["json array"].toVector()[2].toInt(), 1 );
}

//---------------------------------------------------------------------------//
// Check that a property tree can be extracted from a stream
FRENSIE_UNIT_TEST( PropertyTree, istream_operator )
{
  Utility::PropertyTree ptree;

  std::istringstream iss( "{}" );

  iss >> ptree;

  FRENSIE_CHECK_EQUAL( ptree.size(), 0 );

  iss.str( "{\"repeated_value\":\"true\"}" );
  iss.clear();

  iss >> ptree;

  FRENSIE_CHECK_EQUAL( ptree.size(), 1 );
  FRENSIE_CHECK_EQUAL( ptree.get<bool>( "repeated_value" ), true );

  iss.str( "{\"repeated_value\":\"true\",\"repeated_value\":\"{-1.000000000000000000e+00, 0.000000000000000000e+00, 1.000000000000000000e+00}\"}" );
  iss.clear();

  iss >> ptree;

  FRENSIE_CHECK_EQUAL( ptree.size(), 2 );
  FRENSIE_CHECK_EQUAL( ptree.count( "repeated_value" ), 2 );

  Utility::VariantMap map = Utility::fromPropertyTree<Utility::VariantMap>( ptree );

  FRENSIE_CHECK_EQUAL( map.size(), 1 );
  FRENSIE_CHECK_EQUAL( map["repeated_value"].toVector().size(), 4 );
  FRENSIE_CHECK_EQUAL( map["repeated_value"].toVector()[0].toBool(), true );
  FRENSIE_CHECK_EQUAL( map["repeated_value"].toVector()[1].toDouble(), -1.0 );
  FRENSIE_CHECK_EQUAL( map["repeated_value"].toVector()[2].toDouble(), 0.0 );
  FRENSIE_CHECK_EQUAL( map["repeated_value"].toVector()[3].toDouble(), 1.0 );

  iss.str( "{\"repeated_value\":\"true\",\"repeated_value\":\"{-1.000000000000000000e+00, 0.000000000000000000e+00, 1.000000000000000000e+00}\",\"inline array\":\"{-1, 0, 1}\"}" );

  iss >> ptree;

  map = Utility::fromPropertyTree<Utility::VariantMap>( ptree );

  FRENSIE_CHECK_EQUAL( map.size(), 2 );
  FRENSIE_CHECK_EQUAL( map["repeated_value"].toVector().size(), 4 );
  FRENSIE_CHECK_EQUAL( map["repeated_value"].toVector()[0].toBool(), true );
  FRENSIE_CHECK_EQUAL( map["repeated_value"].toVector()[1].toDouble(), -1.0 );
  FRENSIE_CHECK_EQUAL( map["repeated_value"].toVector()[2].toDouble(), 0.0 );
  FRENSIE_CHECK_EQUAL( map["repeated_value"].toVector()[3].toDouble(), 1.0 );
  FRENSIE_CHECK_EQUAL( map["inline array"].toVector().size(), 3 );
  FRENSIE_CHECK_EQUAL( map["inline array"].toVector()[0].toInt(), -1 );
  FRENSIE_CHECK_EQUAL( map["inline array"].toVector()[1].toInt(), 0 );
  FRENSIE_CHECK_EQUAL( map["inline array"].toVector()[2].toInt(), 1 );

  iss.str( "{\"repeated_value\":\"true\",\"repeated_value\":\"{-1.000000000000000000e+00, 0.000000000000000000e+00, 1.000000000000000000e+00}\",\"inline array\":\"{-1, 0, 1}\",\"child tree\":{\"level 2 string\":\"test string\",\"level 2 inline array\":\"{test, string, array}\"}}" );
  iss.clear();

  iss >> ptree;

  map = Utility::fromPropertyTree<Utility::VariantMap>( ptree );

  FRENSIE_CHECK_EQUAL( map.size(), 3 );
  FRENSIE_CHECK_EQUAL( map["repeated_value"].toVector().size(), 4 );
  FRENSIE_CHECK_EQUAL( map["repeated_value"].toVector()[0].toBool(), true );
  FRENSIE_CHECK_EQUAL( map["repeated_value"].toVector()[1].toDouble(), -1.0 );
  FRENSIE_CHECK_EQUAL( map["repeated_value"].toVector()[2].toDouble(), 0.0 );
  FRENSIE_CHECK_EQUAL( map["repeated_value"].toVector()[3].toDouble(), 1.0 );
  FRENSIE_CHECK_EQUAL( map["inline array"].toVector().size(), 3 );
  FRENSIE_CHECK_EQUAL( map["inline array"].toVector()[0].toInt(), -1 );
  FRENSIE_CHECK_EQUAL( map["inline array"].toVector()[1].toInt(), 0 );
  FRENSIE_CHECK_EQUAL( map["inline array"].toVector()[2].toInt(), 1 );
  FRENSIE_CHECK_EQUAL( map["child tree"].toMap().size(), 2 );
  FRENSIE_CHECK_EQUAL( map["child tree"].toMap()["level 2 string"].toString(), "test string" );
  FRENSIE_CHECK_EQUAL( map["child tree"].toMap()["level 2 inline array"].compactify().toString(), "{test,string,array}" );

  iss.str( "{\"repeated_value\":\"true\",\"repeated_value\":\"{-1.000000000000000000e+00, 0.000000000000000000e+00, 1.000000000000000000e+00}\",\"inline array\":\"{-1, 0, 1}\",\"child tree\":{\"level 2 string\":\"test string\",\"level 2 inline array\":\"{test, string, array}\"},\"json array\":[\"-1\",\"0\",\"1\"]}" );
  iss.clear();

  iss >> ptree;

  map = Utility::fromPropertyTree<Utility::VariantMap>( ptree );

  FRENSIE_CHECK_EQUAL( map.size(), 4 );
  FRENSIE_CHECK_EQUAL( map["repeated_value"].toVector().size(), 4 );
  FRENSIE_CHECK_EQUAL( map["repeated_value"].toVector()[0].toBool(), true );
  FRENSIE_CHECK_EQUAL( map["repeated_value"].toVector()[1].toDouble(), -1.0 );
  FRENSIE_CHECK_EQUAL( map["repeated_value"].toVector()[2].toDouble(), 0.0 );
  FRENSIE_CHECK_EQUAL( map["repeated_value"].toVector()[3].toDouble(), 1.0 );
  FRENSIE_CHECK_EQUAL( map["inline array"].toVector().size(), 3 );
  FRENSIE_CHECK_EQUAL( map["inline array"].toVector()[0].toInt(), -1 );
  FRENSIE_CHECK_EQUAL( map["inline array"].toVector()[1].toInt(), 0 );
  FRENSIE_CHECK_EQUAL( map["inline array"].toVector()[2].toInt(), 1 );
  FRENSIE_CHECK_EQUAL( map["child tree"].toMap().size(), 2 );
  FRENSIE_CHECK_EQUAL( map["child tree"].toMap()["level 2 string"].toString(), "test string" );
  FRENSIE_CHECK_EQUAL( map["child tree"].toMap()["level 2 inline array"].compactify().toString(), "{test,string,array}" );
  FRENSIE_CHECK_EQUAL( map["json array"].toVector().size(), 3 );
  FRENSIE_CHECK_EQUAL( map["json array"].toVector()[0].toInt(), -1 );
  FRENSIE_CHECK_EQUAL( map["json array"].toVector()[1].toInt(), 0 );
  FRENSIE_CHECK_EQUAL( map["json array"].toVector()[2].toInt(), 1 );
}

//---------------------------------------------------------------------------//
// end tstPropertyTree.cpp
//---------------------------------------------------------------------------//
