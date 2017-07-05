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
                                    1e-9 );

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
// Check that the property tree node types can be detected
TEUCHOS_UNIT_TEST( PropertyTree, doesPTreeNodeStoreJSONArray )
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

  TEST_ASSERT( !Utility::doesPTreeNodeStoreJSONArray( ptree ) );
  TEST_ASSERT( !Utility::doesPTreeNodeStoreJSONArray( ptree.get_child( "inline array" ) ) );
  TEST_ASSERT( Utility::doesPTreeNodeStoreJSONArray( ptree.get_child( "json array" ) ) );
               
  TEST_NOTHROW( boost::property_tree::write_json( "test_arrays.json", ptree ) );
}

//---------------------------------------------------------------------------//
// Check that a property tree node can be converted to a sequence container
TEUCHOS_UNIT_TEST( PropertyTree, convertPTreeNodeToSequenceContainer )
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

  // Convert the nodes to VariantVectors
  Utility::VariantVector vector =
    Utility::convertPTreeNodeToVariantVector( ptree );

  TEST_EQUALITY_CONST( vector.size(), 0 );

  vector = Utility::convertPTreeNodeToVariantVector( ptree.get_child( "value" ) );

  TEST_EQUALITY_CONST( vector.size(), 1 );
  TEST_EQUALITY_CONST( vector.front().toBool(), true );

  vector = Utility::convertPTreeNodeToVariantVector( ptree.get_child( "inline array" ) );

  TEST_EQUALITY_CONST( vector.size(), 3 );
  TEST_EQUALITY_CONST( vector[0].toInt(), -1 );
  TEST_EQUALITY_CONST( vector[1].toInt(), 0 );
  TEST_EQUALITY_CONST( vector[2].toInt(), 1 );

  vector = Utility::convertPTreeNodeToVariantVector( ptree.get_child( "json array" ) );

  TEST_EQUALITY_CONST( vector.size(), 3 );
  TEST_EQUALITY_CONST( vector[0].toInt(), -1 );
  TEST_EQUALITY_CONST( vector[1].toInt(), 0 );
  TEST_EQUALITY_CONST( vector[2].toInt(), 1 );

  // Convert the nodes to VariantDeques
  Utility::VariantDeque deque =
    Utility::convertPTreeNodeToVariantDeque( ptree );

  TEST_EQUALITY_CONST( deque.size(), 0 );

  deque = Utility::convertPTreeNodeToVariantDeque( ptree.get_child( "value" ) );

  TEST_EQUALITY_CONST( deque.size(), 1 );
  TEST_EQUALITY_CONST( deque.front().toBool(), true );

  deque = Utility::convertPTreeNodeToVariantDeque( ptree.get_child( "inline array" ) );

  TEST_EQUALITY_CONST( deque.size(), 3 );
  TEST_EQUALITY_CONST( deque.front().toInt(), -1 );
  TEST_EQUALITY_CONST( deque.back().toInt(), 1 );

  deque = Utility::convertPTreeNodeToVariantDeque( ptree.get_child( "json array" ) );

  TEST_EQUALITY_CONST( deque.size(), 3 );
  TEST_EQUALITY_CONST( deque.front().toInt(), -1 );
  TEST_EQUALITY_CONST( deque.back().toInt(), 1 );

  // Convert the nodes to VariantLists
  Utility::VariantList list =
    Utility::convertPTreeNodeToVariantList( ptree );

  TEST_EQUALITY_CONST( list.size(), 0 );

  list = Utility::convertPTreeNodeToVariantList( ptree.get_child( "value" ) );

  TEST_EQUALITY_CONST( list.size(), 1 );
  TEST_EQUALITY_CONST( list.front().toBool(), true );

  list = Utility::convertPTreeNodeToVariantList( ptree.get_child( "inline array" ) );

  TEST_EQUALITY_CONST( list.size(), 3 );
  TEST_EQUALITY_CONST( list.front().toInt(), -1 );
  TEST_EQUALITY_CONST( list.back().toInt(), 1 );

  list = Utility::convertPTreeNodeToVariantList( ptree.get_child( "json array" ) );

  TEST_EQUALITY_CONST( list.size(), 3 );
  TEST_EQUALITY_CONST( list.front().toInt(), -1 );
  TEST_EQUALITY_CONST( list.back().toInt(), 1 );

  // Convert the nodes to VariantForwardLists
  Utility::VariantForwardList forward_list =
    Utility::convertPTreeNodeToVariantForwardList( ptree );

  TEST_EQUALITY_CONST( std::distance(forward_list.begin(), forward_list.end()), 0 );

  forward_list = Utility::convertPTreeNodeToVariantForwardList( ptree.get_child( "value" ) );

  TEST_EQUALITY_CONST( std::distance(forward_list.begin(), forward_list.end()), 1 );
  TEST_EQUALITY_CONST( forward_list.front().toBool(), true );

  forward_list = Utility::convertPTreeNodeToVariantForwardList( ptree.get_child( "inline array" ) );

  TEST_EQUALITY_CONST( std::distance(forward_list.begin(), forward_list.end()), 3 );
  TEST_EQUALITY_CONST( forward_list.front().toInt(), -1 );

  forward_list = Utility::convertPTreeNodeToVariantForwardList( ptree.get_child( "json array" ) );

  TEST_EQUALITY_CONST( std::distance(forward_list.begin(), forward_list.end()), 3 );
  TEST_EQUALITY_CONST( forward_list.front().toInt(), -1 );
}

//---------------------------------------------------------------------------//
// Check that a property tree node can be converted to an associative container
TEUCHOS_UNIT_TEST( PropertyTree, convertPTreeNodeToAssociativeContainer )
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
  Utility::VariantMap map = Utility::convertPTreeNodeToVariantMap( ptree );
  
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
  map = Utility::convertPTreeNodeToVariantMap( ptree );

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
  map = Utility::convertPTreeNodeToVariantMap( ptree );

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
  map = Utility::convertPTreeNodeToVariantMap( ptree );

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

  Utility::VariantMap map = Utility::convertPTreeNodeToVariantMap( ptree );

  TEST_EQUALITY_CONST( map.size(), 1 );
  TEST_EQUALITY_CONST( map["repeated_value"].toVector().size(), 4 );
  TEST_EQUALITY_CONST( map["repeated_value"].toVector()[0].toBool(), true );
  TEST_EQUALITY_CONST( map["repeated_value"].toVector()[1].toDouble(), -1.0 );
  TEST_EQUALITY_CONST( map["repeated_value"].toVector()[2].toDouble(), 0.0 );
  TEST_EQUALITY_CONST( map["repeated_value"].toVector()[3].toDouble(), 1.0 );

  ptree = Utility::fromString<Utility::PropertyTree>( "{\"repeated_value\":\"true\",\"repeated_value\":\"{-1.000000000000000000e+00, 0.000000000000000000e+00, 1.000000000000000000e+00}\",\"inline array\":\"{-1, 0, 1}\"}" );
  
  map = Utility::convertPTreeNodeToVariantMap( ptree );

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
  
  map = Utility::convertPTreeNodeToVariantMap( ptree );

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

  map = Utility::convertPTreeNodeToVariantMap( ptree );

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

  Utility::VariantMap map = Utility::convertPTreeNodeToVariantMap( ptree );

  TEST_EQUALITY_CONST( map.size(), 1 );
  TEST_EQUALITY_CONST( map["repeated_value"].toVector().size(), 4 );
  TEST_EQUALITY_CONST( map["repeated_value"].toVector()[0].toBool(), true );
  TEST_EQUALITY_CONST( map["repeated_value"].toVector()[1].toDouble(), -1.0 );
  TEST_EQUALITY_CONST( map["repeated_value"].toVector()[2].toDouble(), 0.0 );
  TEST_EQUALITY_CONST( map["repeated_value"].toVector()[3].toDouble(), 1.0 );

  iss.str( "{\"repeated_value\":\"true\",\"repeated_value\":\"{-1.000000000000000000e+00, 0.000000000000000000e+00, 1.000000000000000000e+00}\",\"inline array\":\"{-1, 0, 1}\"}" );

  Utility::fromStream( iss, ptree );
  
  map = Utility::convertPTreeNodeToVariantMap( ptree );

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
  
  map = Utility::convertPTreeNodeToVariantMap( ptree );

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

  map = Utility::convertPTreeNodeToVariantMap( ptree );

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

  Utility::VariantMap map = Utility::convertPTreeNodeToVariantMap( ptree );

  TEST_EQUALITY_CONST( map.size(), 1 );
  TEST_EQUALITY_CONST( map["repeated_value"].toVector().size(), 4 );
  TEST_EQUALITY_CONST( map["repeated_value"].toVector()[0].toBool(), true );
  TEST_EQUALITY_CONST( map["repeated_value"].toVector()[1].toDouble(), -1.0 );
  TEST_EQUALITY_CONST( map["repeated_value"].toVector()[2].toDouble(), 0.0 );
  TEST_EQUALITY_CONST( map["repeated_value"].toVector()[3].toDouble(), 1.0 );

  iss.str( "{\"repeated_value\":\"true\",\"repeated_value\":\"{-1.000000000000000000e+00, 0.000000000000000000e+00, 1.000000000000000000e+00}\",\"inline array\":\"{-1, 0, 1}\"}" );

  iss >> ptree;
  
  map = Utility::convertPTreeNodeToVariantMap( ptree );

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
  
  map = Utility::convertPTreeNodeToVariantMap( ptree );

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

  map = Utility::convertPTreeNodeToVariantMap( ptree );

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
