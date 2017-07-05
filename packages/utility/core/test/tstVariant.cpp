//---------------------------------------------------------------------------//
//!
//! \file   tstVariant.cpp
//! \author Alex Robinson
//! \brief  Variant class unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <sstream>
#include <memory>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>

// FRENSIE Includes
#include "Utility_Variant.hpp"
#include "Utility_UnitTestHarnessExtensions.hpp"

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that a default variant can be constructed
TEUCHOS_UNIT_TEST( Variant, default_constructor )
{
  Utility::Variant variant;

  TEST_ASSERT( variant.isNull() );
  TEST_EQUALITY_CONST( variant.toString(), "" );
}

//---------------------------------------------------------------------------//
// Check that a variant can be created from a basic types
TEUCHOS_UNIT_TEST( Variant, constructor_basic_types )
{
  // Store a char
  std::unique_ptr<Utility::Variant> variant( new Utility::Variant( 'a' ) );
  bool conversion_success = false;

  TEST_ASSERT( !variant->isNull() );
  TEST_EQUALITY_CONST( variant->toChar( &conversion_success ), 'a' );
  TEST_ASSERT( conversion_success );

  // Store a char[]
  variant.reset( new Utility::Variant( "Test string" ) );
  
  TEST_ASSERT( !variant->isNull() );
  TEST_EQUALITY_CONST( variant->toString( &conversion_success ), "Test string" );
  TEST_ASSERT( conversion_success );

  variant->toChar( &conversion_success );

  TEST_ASSERT( !conversion_success );

  // Store a boolean
  variant.reset( new Utility::Variant( true ) );

  TEST_ASSERT( !variant->isNull() );
  TEST_EQUALITY_CONST( variant->toBool( &conversion_success ), true );
  TEST_ASSERT( conversion_success );

  variant.reset( new Utility::Variant( false ) );

  TEST_ASSERT( !variant->isNull() );
  TEST_EQUALITY_CONST( variant->toBool( &conversion_success ), false );
  TEST_ASSERT( conversion_success );

  variant.reset( new Utility::Variant( "true" ) );

  TEST_ASSERT( !variant->isNull() );
  TEST_EQUALITY_CONST( variant->toBool( &conversion_success ), true );
  TEST_ASSERT( conversion_success );

  variant.reset( new Utility::Variant( "false" ) );
  
  TEST_ASSERT( !variant->isNull() );
  TEST_EQUALITY_CONST( variant->toBool( &conversion_success ), false );
  TEST_ASSERT( conversion_success );

  // Store a signed char
  variant.reset( new Utility::Variant( (signed char)-1 ) );

  TEST_ASSERT( !variant->isNull() );
  TEST_EQUALITY_CONST( variant->toSignedChar( &conversion_success ), -1 );
  TEST_ASSERT( conversion_success );

  // Store an unsigned char
  variant.reset( new Utility::Variant( (unsigned char)0 ) );

  TEST_ASSERT( !variant->isNull() );
  TEST_EQUALITY_CONST( variant->toUnsignedChar( &conversion_success ), 0 );
  TEST_ASSERT( conversion_success );

  // Store an int8_t
  variant.reset( new Utility::Variant( (int8_t)-100 ) );

  TEST_ASSERT( !variant->isNull() );
  TEST_EQUALITY_CONST( variant->toInt8( &conversion_success ), -100 );
  TEST_ASSERT( conversion_success );

  // Store an uint8_t
  variant.reset( new Utility::Variant( (uint8_t)255 ) );

  TEST_ASSERT( !variant->isNull() );
  TEST_EQUALITY_CONST( variant->toUint8( &conversion_success ), 255 );
  TEST_ASSERT( conversion_success );

  // Store an int16_t
  variant.reset( new Utility::Variant( (int16_t)-200 ) );

  TEST_ASSERT( !variant->isNull() );
  TEST_EQUALITY_CONST( variant->toInt16( &conversion_success ), -200 );
  TEST_ASSERT( conversion_success );

  // Store a uint16_t
  variant.reset( new Utility::Variant( (uint16_t)300 ) );

  TEST_ASSERT( !variant->isNull() );
  TEST_EQUALITY_CONST( variant->toUint16( &conversion_success ), 300 );
  TEST_ASSERT( conversion_success );

  // Store an int32_t
  variant.reset( new Utility::Variant( (int32_t)-1000000000 ) );

  TEST_ASSERT( !variant->isNull() );
  TEST_EQUALITY_CONST( variant->toInt32( &conversion_success ), -1000000000 );
  TEST_ASSERT( conversion_success );

  // Store an uint32_t
  variant.reset( new Utility::Variant( (uint32_t)1000000000 ) );

  TEST_ASSERT( !variant->isNull() );
  TEST_EQUALITY_CONST( variant->toUint32( &conversion_success ), 1000000000 );
  TEST_ASSERT( conversion_success );

  // Store a short
  variant.reset( new Utility::Variant( (short)-100 ) );

  TEST_ASSERT( !variant->isNull() );
  TEST_EQUALITY_CONST( variant->toShort( &conversion_success ), -100 );
  TEST_ASSERT( conversion_success );

  // Store an unsigned short
  variant.reset( new Utility::Variant( (unsigned short)255 ) );

  TEST_ASSERT( !variant->isNull() );
  TEST_EQUALITY_CONST( variant->toUnsignedShort( &conversion_success ), 255 );
  TEST_ASSERT( conversion_success );

  // Store an int
  variant.reset( new Utility::Variant( -100000000 ) );

  TEST_ASSERT( !variant->isNull() );
  TEST_EQUALITY_CONST( variant->toInt( &conversion_success ), -100000000 );
  TEST_ASSERT( conversion_success );

  // Store an unsigned int
  variant.reset( new Utility::Variant( 100000000u ) );

  TEST_ASSERT( !variant->isNull() );
  TEST_EQUALITY_CONST( variant->toUnsignedInt( &conversion_success ), 100000000 );
  TEST_ASSERT( conversion_success );

  // Store a long
  variant.reset( new Utility::Variant( -100000000l ) );

  TEST_ASSERT( !variant->isNull() );
  TEST_EQUALITY_CONST( variant->toLong( &conversion_success ), -100000000 );
  TEST_ASSERT( conversion_success );

  // Store an unsigned long
  variant.reset( new Utility::Variant( 100000000ul ) );

  TEST_ASSERT( !variant->isNull() );
  TEST_EQUALITY_CONST( variant->toUnsignedLong( &conversion_success ), 100000000 );
  TEST_ASSERT( conversion_success );

  // Store a long long
  variant.reset( new Utility::Variant( -10000000000ll ) );

  TEST_ASSERT( !variant->isNull() );
  TEST_EQUALITY_CONST( variant->toLongLong( &conversion_success ), -10000000000 );
  TEST_ASSERT( conversion_success );
  
  // Store an unsigned long long
  variant.reset( new Utility::Variant( 10000000000ull ) );

  TEST_ASSERT( !variant->isNull() );
  TEST_EQUALITY_CONST( variant->toUnsignedLongLong( &conversion_success ), 10000000000 );
  TEST_ASSERT( conversion_success );

  // Store a float
  variant.reset( new Utility::Variant( 1.0f ) );

  TEST_ASSERT( !variant->isNull() );
  TEST_EQUALITY_CONST( variant->toFloat( &conversion_success ), 1.0f );
  TEST_ASSERT( conversion_success );

  variant.reset( new Utility::Variant( "-inf" ) );

  TEST_ASSERT( !variant->isNull() );
  TEST_EQUALITY_CONST( variant->toFloat( &conversion_success ),
                       -std::numeric_limits<float>::infinity() );
  TEST_ASSERT( conversion_success );

  variant.reset( new Utility::Variant( "-pi" ) );

  TEST_ASSERT( !variant->isNull() );
  TEST_EQUALITY_CONST( variant->toFloat( &conversion_success ),
                       -(float)Utility::PhysicalConstants::pi );
  TEST_ASSERT( conversion_success );

  // Store a double
  variant.reset( new Utility::Variant( -1.0 ) );

  TEST_ASSERT( !variant->isNull() );
  TEST_EQUALITY_CONST( variant->toDouble( &conversion_success ), -1.0 );
  TEST_ASSERT( conversion_success );

  variant.reset( new Utility::Variant( "Infty" ) );

  TEST_ASSERT( !variant->isNull() );
  TEST_EQUALITY_CONST( variant->toDouble( &conversion_success ),
                       std::numeric_limits<double>::infinity() );
  TEST_ASSERT( conversion_success );

  variant.reset( new Utility::Variant( "3pi/4" ) );

  TEST_ASSERT( !variant->isNull() );
  TEST_EQUALITY_CONST( variant->toDouble( &conversion_success ),
                       3*Utility::PhysicalConstants::pi/4 );
  TEST_ASSERT( conversion_success );
}

//---------------------------------------------------------------------------//
// Check that a variant can be constructed from containers
TEUCHOS_UNIT_TEST( Variant, constructor_container )
{
  // Store a string
  std::unique_ptr<Utility::Variant>
    variant( new Utility::Variant( std::string("Test string") ) );

  bool conversion_success = false;

  TEST_ASSERT( !variant->isNull() );
  TEST_EQUALITY_CONST( variant->toString( &conversion_success ), "Test string" );
  TEST_ASSERT( conversion_success );

  variant->toChar( &conversion_success );

  TEST_ASSERT( !conversion_success );

  // Store a vector of int
  variant.reset( new Utility::Variant( std::vector<int>({-1, 0, 1}) ) );

  TEST_ASSERT( !variant->isNull() );

  Utility::VariantVector extracted_vector =
    variant->toVector( &conversion_success );
  
  TEST_ASSERT( conversion_success );
  TEST_EQUALITY_CONST( extracted_vector.size(), 3 );
  TEST_EQUALITY_CONST( extracted_vector[0].toInt(), -1 );
  TEST_EQUALITY_CONST( extracted_vector[1].toInt(), 0 );
  TEST_EQUALITY_CONST( extracted_vector[2].toInt(), 1 );

  // Store a vector of vector of int
  variant.reset( new Utility::Variant( std::vector<std::vector<int> >({std::vector<int>({-1, 0}), std::vector<int>({1, 2})}) ) );

  TEST_ASSERT( !variant->isNull() );

  extracted_vector = variant->toVector( &conversion_success );

  TEST_ASSERT( conversion_success );
  TEST_EQUALITY_CONST( extracted_vector.size(), 2 );
  TEST_EQUALITY_CONST( extracted_vector[0].toVector().size(), 2 );
  TEST_EQUALITY_CONST( extracted_vector[0].toVector()[0].toInt(), -1 );
  TEST_EQUALITY_CONST( extracted_vector[0].toVector()[1].toInt(), 0 );

  variant.reset( new Utility::Variant( "{ {-1, 0},  {1, 2}  }" ) );

  TEST_ASSERT( !variant->isNull() );

  extracted_vector = variant->toVector( &conversion_success );

  TEST_ASSERT( conversion_success );
  TEST_EQUALITY_CONST( extracted_vector.size(), 2 );
  TEST_EQUALITY_CONST( extracted_vector[0].toVector().size(), 2 );
  TEST_EQUALITY_CONST( extracted_vector[0].toVector()[0].toInt(), -1 );
  TEST_EQUALITY_CONST( extracted_vector[0].toVector()[1].toInt(), 0 );

  // Store a vector of list of pair
  variant.reset( new Utility::Variant( std::vector<std::list<std::pair<int,float> > >({std::list<std::pair<int,float> >({std::make_pair(-1, 0.0f), std::make_pair(1, 1.0f)}), std::list<std::pair<int,float> >({std::make_pair(1, 1.0f), std::make_pair(-1, 0.0f)})}) ) );

  TEST_ASSERT( !variant->isNull() );

  extracted_vector = variant->toVector( &conversion_success );

  TEST_ASSERT( conversion_success );
  TEST_EQUALITY_CONST( extracted_vector.size(), 2 );
  TEST_EQUALITY_CONST( extracted_vector[0].toList().size(), 2 );
  TEST_EQUALITY_CONST( extracted_vector[0].toList().front().toString(), "{-1, 0.000000000e+00}" );
  TEST_EQUALITY_CONST( extracted_vector[0].toList().back().toString(), " {1, 1.000000000e+00}" );
  TEST_EQUALITY_CONST( extracted_vector[1].toList().size(), 2 );
  TEST_EQUALITY_CONST( extracted_vector[1].toList().front().toString(), "{1, 1.000000000e+00}" );
  TEST_EQUALITY_CONST( extracted_vector[1].toList().back().toString(), " {-1, 0.000000000e+00}" );

  // Store a list of int
  variant.reset( new Utility::Variant( std::list<int>({-1, 1}) ) );

  TEST_ASSERT( !variant->isNull() );

  Utility::VariantList extracted_list =
    variant->toList( &conversion_success );

  TEST_ASSERT( conversion_success );
  TEST_EQUALITY_CONST( extracted_list.size(), 2 );
  TEST_EQUALITY_CONST( extracted_list.front().toInt(), -1 );
  TEST_EQUALITY_CONST( extracted_list.back().toInt(), 1 );

  // Store a list of list of float
  variant.reset( new Utility::Variant( std::list<std::list<float> >({std::list<float>({-1.0f, 0.0f}), std::list<float>({0.0f, 1.0f})}) ) );

  TEST_ASSERT( !variant->isNull() );

  extracted_list = variant->toList( &conversion_success );

  TEST_ASSERT( conversion_success );
  TEST_EQUALITY_CONST( extracted_list.size(), 2 );
  TEST_EQUALITY_CONST( extracted_list.front().toList().size(), 2 );
  TEST_EQUALITY_CONST( extracted_list.front().toList().front().toFloat(), -1.0f );
  TEST_EQUALITY_CONST( extracted_list.front().toList().back().toFloat(), 0.0f );
  TEST_EQUALITY_CONST( extracted_list.back().toList().size(), 2 );
  TEST_EQUALITY_CONST( extracted_list.back().toList().front().toFloat(), 0.0f );
  TEST_EQUALITY_CONST( extracted_list.back().toList().back().toFloat(), 1.0f );

  // Store a forward list of int
  variant.reset( new Utility::Variant( std::forward_list<int>({0, 100}) ) );

  TEST_ASSERT( !variant->isNull() );

  Utility::VariantForwardList extracted_forward_list =
    variant->toForwardList( &conversion_success );

  TEST_ASSERT( conversion_success );
  TEST_EQUALITY_CONST( std::distance( extracted_forward_list.begin(), extracted_forward_list.end() ), 2 );
  TEST_EQUALITY_CONST( extracted_forward_list.front().toInt(), 0 );

  extracted_forward_list.pop_front();

  TEST_EQUALITY_CONST( extracted_forward_list.front().toInt(), 100 );

  // Store a forward list of forward list of double
  variant.reset( new Utility::Variant( std::forward_list<std::forward_list<double> >({std::forward_list<double>({-1.0, 0.0}), std::forward_list<double>({0.0, 1.0})}) ) );

  TEST_ASSERT( !variant->isNull() );

  extracted_forward_list = variant->toForwardList( &conversion_success );

  TEST_ASSERT( conversion_success );
  TEST_EQUALITY_CONST( std::distance( extracted_forward_list.begin(), extracted_forward_list.end() ), 2 );

  {
    Utility::VariantForwardList sub_forward_list =
      extracted_forward_list.front().toForwardList();
    
    TEST_EQUALITY_CONST( std::distance( sub_forward_list.begin(), sub_forward_list.end() ), 2 );
    TEST_EQUALITY_CONST( sub_forward_list.front().toDouble(), -1.0 );

    sub_forward_list.pop_front();
    
    TEST_EQUALITY_CONST( sub_forward_list.front().toDouble(), 0.0 );

    extracted_forward_list.pop_front();

    sub_forward_list = extracted_forward_list.front().toForwardList();

    TEST_EQUALITY_CONST( std::distance( sub_forward_list.begin(), sub_forward_list.end() ), 2 );
    TEST_EQUALITY_CONST( sub_forward_list.front().toDouble(), 0.0 );

    sub_forward_list.pop_front();
    
    TEST_EQUALITY_CONST( sub_forward_list.front().toDouble(), 1.0 );
  }

  // Store a deque of unsigned long long
  variant.reset( new Utility::Variant( std::deque<unsigned long long>({0ull, 1000000000000ull}) ) );

  TEST_ASSERT( !variant->isNull() );

  Utility::VariantDeque extracted_deque =
    variant->toDeque( &conversion_success );

  TEST_ASSERT( conversion_success );
  TEST_EQUALITY_CONST( extracted_deque.size(), 2 );
  TEST_EQUALITY_CONST( extracted_deque.front().toUnsignedLongLong(), 0ull );
  TEST_EQUALITY_CONST( extracted_deque.back().toUnsignedLongLong(), 1000000000000ull );

  // Store a deque of deque of double
  variant.reset( new Utility::Variant( std::deque<std::deque<double> >({std::deque<double>({-1.0, 0.0}), std::deque<double>({0.0, 1.0})}) ) );

  TEST_ASSERT( !variant->isNull() );

  extracted_deque = variant->toDeque( &conversion_success );
  
  TEST_ASSERT( conversion_success );
  TEST_EQUALITY_CONST( extracted_deque.size(), 2 );
  TEST_EQUALITY_CONST( extracted_deque.front().toDeque().size(), 2 );
  TEST_EQUALITY_CONST( extracted_deque.front().toDeque().front().toDouble(), -1.0 );
  TEST_EQUALITY_CONST( extracted_deque.front().toDeque().back().toDouble(), 0.0 );
  TEST_EQUALITY_CONST( extracted_deque.back().toDeque().size(), 2 );
  TEST_EQUALITY_CONST( extracted_deque.back().toDeque().front().toDouble(), 0.0 );
  TEST_EQUALITY_CONST( extracted_deque.back().toDeque().back().toDouble(), 1.0 );

  // Store a map of int, double
  variant.reset( new Utility::Variant( std::map<int,double>({std::make_pair(0, 0.0), std::make_pair(1, -1.0), std::make_pair(2, -2)}) ) );

  TEST_ASSERT( !variant->isNull() );
  
  Utility::VariantMap extracted_map =
    variant->toMap( &conversion_success );

  TEST_ASSERT( conversion_success );
  TEST_EQUALITY_CONST( extracted_map.size(), 3 );
  TEST_EQUALITY_CONST( extracted_map["0"].toDouble(), 0.0 );
  TEST_EQUALITY_CONST( extracted_map["1"].toDouble(), -1.0 );
  TEST_EQUALITY_CONST( extracted_map["2"].toDouble(), -2.0 );

  // Store a map of int, map<string,int>
  variant.reset( new Utility::Variant( std::map<int,std::map<std::string,int> >({std::make_pair(0, std::map<std::string,int>({std::make_pair("first", -1), std::make_pair("second", 1)})), std::make_pair(1, std::map<std::string,int>({std::make_pair("first", 0), std::make_pair("second", 10)}))}) ) );

  TEST_ASSERT( !variant->isNull() );

  extracted_map = variant->toMap( &conversion_success );

  TEST_ASSERT( conversion_success );
  TEST_EQUALITY_CONST( extracted_map.size(), 2 );
  TEST_EQUALITY_CONST( extracted_map["0"].toMap().size(), 2 );
  TEST_EQUALITY_CONST( extracted_map["0"].toMap()["first"].toInt(), -1 );
  TEST_EQUALITY_CONST( extracted_map["0"].toMap()["second"].toInt(), 1 );
  TEST_EQUALITY_CONST( extracted_map["1"].toMap().size(), 2 );
  TEST_EQUALITY_CONST( extracted_map["1"].toMap()["first"].toInt(), 0 );
  TEST_EQUALITY_CONST( extracted_map["1"].toMap()["second"].toInt(), 10 );
}

//---------------------------------------------------------------------------//
// Check the copy constructor
TEUCHOS_UNIT_TEST( Variant, copy_constructor )
{
  std::unique_ptr<Utility::Variant>
    variant( new Utility::Variant( 1 ) );

  std::unique_ptr<Utility::Variant> variant_copy(
                                            new Utility::Variant( *variant ) );

  TEST_ASSERT( !variant_copy->isNull() );
  TEST_EQUALITY_CONST( *variant_copy, *variant );
  TEST_EQUALITY_CONST( variant_copy->toInt(), 1 );
}

//---------------------------------------------------------------------------//
// Check the assignment operator
TEUCHOS_UNIT_TEST( Variant, assignment_operator )
{
  std::unique_ptr<Utility::Variant>
    variant( new Utility::Variant( 1.0 ) );

  std::unique_ptr<Utility::Variant> variant_copy( new Utility::Variant );

  *variant_copy = *variant;

  TEST_ASSERT( !variant_copy->isNull() );
  TEST_EQUALITY_CONST( *variant_copy, *variant );
  TEST_EQUALITY_CONST( variant_copy->toInt(), 1 );
}

//---------------------------------------------------------------------------//
// Check that the variant factory method can be used to create a variant
TEUCHOS_UNIT_TEST( Variant, fromValue_basic_types )
{
  // From a char
  Utility::Variant variant = Utility::Variant::fromValue( 'a' );
  bool conversion_success = false;

  TEST_ASSERT( !variant.isNull() );
  TEST_EQUALITY_CONST( variant.toChar( &conversion_success ), 'a' );
  TEST_ASSERT( conversion_success );

  // From a char[]
  variant = Utility::Variant::fromValue( "Test string" );
  
  TEST_ASSERT( !variant.isNull() );
  TEST_EQUALITY_CONST( variant.toString( &conversion_success ), "Test string" );
  TEST_ASSERT( conversion_success );

  variant.toChar( &conversion_success );

  TEST_ASSERT( !conversion_success );

  // From a boolean
  variant = Utility::Variant::fromValue( true );

  TEST_ASSERT( !variant.isNull() );
  TEST_EQUALITY_CONST( variant.toBool( &conversion_success ), true );
  TEST_ASSERT( conversion_success );

  variant = Utility::Variant::fromValue( false );

  TEST_ASSERT( !variant.isNull() );
  TEST_EQUALITY_CONST( variant.toBool( &conversion_success ), false );
  TEST_ASSERT( conversion_success );

  variant = Utility::Variant::fromValue( "true" );

  TEST_ASSERT( !variant.isNull() );
  TEST_EQUALITY_CONST( variant.toBool( &conversion_success ), true );
  TEST_ASSERT( conversion_success );

  variant = Utility::Variant::fromValue( "false" );
  
  TEST_ASSERT( !variant.isNull() );
  TEST_EQUALITY_CONST( variant.toBool( &conversion_success ), false );
  TEST_ASSERT( conversion_success );

  // From a signed char
  variant = Utility::Variant::fromValue( (signed char)-1 );

  TEST_ASSERT( !variant.isNull() );
  TEST_EQUALITY_CONST( variant.toSignedChar( &conversion_success ), -1 );
  TEST_ASSERT( conversion_success );

  // From an unsigned char
  variant = Utility::Variant::fromValue( (unsigned char)0 );

  TEST_ASSERT( !variant.isNull() );
  TEST_EQUALITY_CONST( variant.toUnsignedChar( &conversion_success ), 0 );
  TEST_ASSERT( conversion_success );

  // From an int8_t
  variant = Utility::Variant::fromValue( (int8_t)-100 );

  TEST_ASSERT( !variant.isNull() );
  TEST_EQUALITY_CONST( variant.toInt8( &conversion_success ), -100 );
  TEST_ASSERT( conversion_success );

  // From an uint8_t
  variant = Utility::Variant::fromValue( (uint8_t)255 );

  TEST_ASSERT( !variant.isNull() );
  TEST_EQUALITY_CONST( variant.toUint8( &conversion_success ), 255 );
  TEST_ASSERT( conversion_success );

  // From an int16_t
  variant = Utility::Variant::fromValue( (int16_t)-200 );

  TEST_ASSERT( !variant.isNull() );
  TEST_EQUALITY_CONST( variant.toInt16( &conversion_success ), -200 );
  TEST_ASSERT( conversion_success );

  // From a uint16_t
  variant = Utility::Variant::fromValue( (uint16_t)300 );

  TEST_ASSERT( !variant.isNull() );
  TEST_EQUALITY_CONST( variant.toUint16( &conversion_success ), 300 );
  TEST_ASSERT( conversion_success );

  // From an int32_t
  variant = Utility::Variant::fromValue( (int32_t)-1000000000 );

  TEST_ASSERT( !variant.isNull() );
  TEST_EQUALITY_CONST( variant.toInt32( &conversion_success ), -1000000000 );
  TEST_ASSERT( conversion_success );

  // From an uint32_t
  variant = Utility::Variant::fromValue( (uint32_t)1000000000 );

  TEST_ASSERT( !variant.isNull() );
  TEST_EQUALITY_CONST( variant.toUint32( &conversion_success ), 1000000000 );
  TEST_ASSERT( conversion_success );

  // From a short
  variant = Utility::Variant::fromValue( (short)-100 );

  TEST_ASSERT( !variant.isNull() );
  TEST_EQUALITY_CONST( variant.toShort( &conversion_success ), -100 );
  TEST_ASSERT( conversion_success );

  // From an unsigned short
  variant = Utility::Variant::fromValue( (unsigned short)255 );

  TEST_ASSERT( !variant.isNull() );
  TEST_EQUALITY_CONST( variant.toUnsignedShort( &conversion_success ), 255 );
  TEST_ASSERT( conversion_success );

  // From an int
  variant = Utility::Variant::fromValue( -100000000 );

  TEST_ASSERT( !variant.isNull() );
  TEST_EQUALITY_CONST( variant.toInt( &conversion_success ), -100000000 );
  TEST_ASSERT( conversion_success );

  // From an unsigned int
  variant = Utility::Variant::fromValue( 100000000u );

  TEST_ASSERT( !variant.isNull() );
  TEST_EQUALITY_CONST( variant.toUnsignedInt( &conversion_success ), 100000000 );
  TEST_ASSERT( conversion_success );

  // From a long
  variant = Utility::Variant::fromValue( -100000000l );

  TEST_ASSERT( !variant.isNull() );
  TEST_EQUALITY_CONST( variant.toLong( &conversion_success ), -100000000 );
  TEST_ASSERT( conversion_success );

  // From an unsigned long
  variant = Utility::Variant::fromValue( 100000000ul );

  TEST_ASSERT( !variant.isNull() );
  TEST_EQUALITY_CONST( variant.toUnsignedLong( &conversion_success ), 100000000 );
  TEST_ASSERT( conversion_success );

  // From a long long
  variant = Utility::Variant::fromValue( -10000000000ll );

  TEST_ASSERT( !variant.isNull() );
  TEST_EQUALITY_CONST( variant.toLongLong( &conversion_success ), -10000000000 );
  TEST_ASSERT( conversion_success );
  
  // From an unsigned long long
  variant = Utility::Variant::fromValue( 10000000000ull );
  
  TEST_ASSERT( !variant.isNull() );
  TEST_EQUALITY_CONST( variant.toUnsignedLongLong( &conversion_success ), 10000000000 );
  TEST_ASSERT( conversion_success );

  // From a float
  variant = Utility::Variant::fromValue( 1.0f );
  
  TEST_ASSERT( !variant.isNull() );
  TEST_EQUALITY_CONST( variant.toFloat( &conversion_success ), 1.0f );
  TEST_ASSERT( conversion_success );
  
  variant = Utility::Variant::fromValue( "-inf" );
  
  TEST_ASSERT( !variant.isNull() );
  TEST_EQUALITY_CONST( variant.toFloat( &conversion_success ),
                       -std::numeric_limits<float>::infinity() );
  TEST_ASSERT( conversion_success );
                       
  variant = Utility::Variant::fromValue( "-pi" );

  TEST_ASSERT( !variant.isNull() );
  TEST_EQUALITY_CONST( variant.toFloat( &conversion_success ),
                       -(float)Utility::PhysicalConstants::pi );
  TEST_ASSERT( conversion_success );

  // From a double
  variant = Utility::Variant::fromValue( -1.0 );

  TEST_ASSERT( !variant.isNull() );
  TEST_EQUALITY_CONST( variant.toDouble( &conversion_success ), -1.0 );
  TEST_ASSERT( conversion_success );

  variant = Utility::Variant::fromValue( "Infty" );

  TEST_ASSERT( !variant.isNull() );
  TEST_EQUALITY_CONST( variant.toDouble( &conversion_success ),
                       std::numeric_limits<double>::infinity() );
  TEST_ASSERT( conversion_success );

  variant = Utility::Variant::fromValue( "3pi/4" );

  TEST_ASSERT( !variant.isNull() );
  TEST_EQUALITY_CONST( variant.toDouble( &conversion_success ),
                       3*Utility::PhysicalConstants::pi/4 );
  TEST_ASSERT( conversion_success );
}

//---------------------------------------------------------------------------//
// Check that the variant factory method can be used to create a variant
TEUCHOS_UNIT_TEST( Variant, fromValue_container )
{
  // From a string
  Utility::Variant variant = Utility::Variant::fromValue( std::string("Test string") );

  bool conversion_success = false;

  TEST_ASSERT( !variant.isNull() );
  TEST_EQUALITY_CONST( variant.toString( &conversion_success ), "Test string" );
  TEST_ASSERT( conversion_success );

  variant.toChar( &conversion_success );

  TEST_ASSERT( !conversion_success );

  // From a vector of int
  variant = Utility::Variant::fromValue( std::vector<int>({-1, 0, 1}) );

  TEST_ASSERT( !variant.isNull() );

  Utility::VariantVector extracted_vector =
    variant.toVector( &conversion_success );
  
  TEST_ASSERT( conversion_success );
  TEST_EQUALITY_CONST( extracted_vector.size(), 3 );
  TEST_EQUALITY_CONST( extracted_vector[0].toInt(), -1 );
  TEST_EQUALITY_CONST( extracted_vector[1].toInt(), 0 );
  TEST_EQUALITY_CONST( extracted_vector[2].toInt(), 1 );

  // From a vector of vector of int
  variant = Utility::Variant::fromValue( std::vector<std::vector<int> >({std::vector<int>({-1, 0}), std::vector<int>({1, 2})}) );

  TEST_ASSERT( !variant.isNull() );

  extracted_vector = variant.toVector( &conversion_success );

  TEST_ASSERT( conversion_success );
  TEST_EQUALITY_CONST( extracted_vector.size(), 2 );
  TEST_EQUALITY_CONST( extracted_vector[0].toVector().size(), 2 );
  TEST_EQUALITY_CONST( extracted_vector[0].toVector()[0].toInt(), -1 );
  TEST_EQUALITY_CONST( extracted_vector[0].toVector()[1].toInt(), 0 );

  variant = Utility::Variant::fromValue( "{ {-1, 0},  {1, 2}  }" );

  TEST_ASSERT( !variant.isNull() );

  extracted_vector = variant.toVector( &conversion_success );

  TEST_ASSERT( conversion_success );
  TEST_EQUALITY_CONST( extracted_vector.size(), 2 );
  TEST_EQUALITY_CONST( extracted_vector[0].toVector().size(), 2 );
  TEST_EQUALITY_CONST( extracted_vector[0].toVector()[0].toInt(), -1 );
  TEST_EQUALITY_CONST( extracted_vector[0].toVector()[1].toInt(), 0 );

  // From a vector of list of pair
  variant = Utility::Variant::fromValue( std::vector<std::list<std::pair<int,float> > >({std::list<std::pair<int,float> >({std::make_pair(-1, 0.0f), std::make_pair(1, 1.0f)}), std::list<std::pair<int,float> >({std::make_pair(1, 1.0f), std::make_pair(-1, 0.0f)})}) );

  TEST_ASSERT( !variant.isNull() );

  extracted_vector = variant.toVector( &conversion_success );

  TEST_ASSERT( conversion_success );
  TEST_EQUALITY_CONST( extracted_vector.size(), 2 );
  TEST_EQUALITY_CONST( extracted_vector[0].toList().size(), 2 );
  TEST_EQUALITY_CONST( extracted_vector[0].toList().front().toString(), "{-1, 0.000000000e+00}" );
  TEST_EQUALITY_CONST( extracted_vector[0].toList().back().toString(), " {1, 1.000000000e+00}" );
  TEST_EQUALITY_CONST( extracted_vector[1].toList().size(), 2 );
  TEST_EQUALITY_CONST( extracted_vector[1].toList().front().toString(), "{1, 1.000000000e+00}" );
  TEST_EQUALITY_CONST( extracted_vector[1].toList().back().toString(), " {-1, 0.000000000e+00}" );

  // From a list of int
  variant = Utility::Variant::fromValue( std::list<int>({-1, 1}) );

  TEST_ASSERT( !variant.isNull() );

  Utility::VariantList extracted_list =
    variant.toList( &conversion_success );

  TEST_ASSERT( conversion_success );
  TEST_EQUALITY_CONST( extracted_list.size(), 2 );
  TEST_EQUALITY_CONST( extracted_list.front().toInt(), -1 );
  TEST_EQUALITY_CONST( extracted_list.back().toInt(), 1 );

  // From a list of list of float
  variant = Utility::Variant::fromValue( std::list<std::list<float> >({std::list<float>({-1.0f, 0.0f}), std::list<float>({0.0f, 1.0f})}) );

  TEST_ASSERT( !variant.isNull() );

  extracted_list = variant.toList( &conversion_success );

  TEST_ASSERT( conversion_success );
  TEST_EQUALITY_CONST( extracted_list.size(), 2 );
  TEST_EQUALITY_CONST( extracted_list.front().toList().size(), 2 );
  TEST_EQUALITY_CONST( extracted_list.front().toList().front().toFloat(), -1.0f );
  TEST_EQUALITY_CONST( extracted_list.front().toList().back().toFloat(), 0.0f );
  TEST_EQUALITY_CONST( extracted_list.back().toList().size(), 2 );
  TEST_EQUALITY_CONST( extracted_list.back().toList().front().toFloat(), 0.0f );
  TEST_EQUALITY_CONST( extracted_list.back().toList().back().toFloat(), 1.0f );

  // From a forward list of int
  variant = Utility::Variant::fromValue( std::forward_list<int>({0, 100}) );

  TEST_ASSERT( !variant.isNull() );

  Utility::VariantForwardList extracted_forward_list =
    variant.toForwardList( &conversion_success );

  TEST_ASSERT( conversion_success );
  TEST_EQUALITY_CONST( std::distance( extracted_forward_list.begin(), extracted_forward_list.end() ), 2 );
  TEST_EQUALITY_CONST( extracted_forward_list.front().toInt(), 0 );

  extracted_forward_list.pop_front();

  TEST_EQUALITY_CONST( extracted_forward_list.front().toInt(), 100 );

  // From a forward list of forward list of double
  variant = Utility::Variant::fromValue( std::forward_list<std::forward_list<double> >({std::forward_list<double>({-1.0, 0.0}), std::forward_list<double>({0.0, 1.0})}) );

  TEST_ASSERT( !variant.isNull() );

  extracted_forward_list = variant.toForwardList( &conversion_success );

  TEST_ASSERT( conversion_success );
  TEST_EQUALITY_CONST( std::distance( extracted_forward_list.begin(), extracted_forward_list.end() ), 2 );

  {
    Utility::VariantForwardList sub_forward_list =
      extracted_forward_list.front().toForwardList();
    
    TEST_EQUALITY_CONST( std::distance( sub_forward_list.begin(), sub_forward_list.end() ), 2 );
    TEST_EQUALITY_CONST( sub_forward_list.front().toDouble(), -1.0 );

    sub_forward_list.pop_front();
    
    TEST_EQUALITY_CONST( sub_forward_list.front().toDouble(), 0.0 );

    extracted_forward_list.pop_front();

    sub_forward_list = extracted_forward_list.front().toForwardList();

    TEST_EQUALITY_CONST( std::distance( sub_forward_list.begin(), sub_forward_list.end() ), 2 );
    TEST_EQUALITY_CONST( sub_forward_list.front().toDouble(), 0.0 );

    sub_forward_list.pop_front();
    
    TEST_EQUALITY_CONST( sub_forward_list.front().toDouble(), 1.0 );
  }

  // From a deque of unsigned long long
  variant = Utility::Variant::fromValue( std::deque<unsigned long long>({0ull, 1000000000000ull}) );

  TEST_ASSERT( !variant.isNull() );

  Utility::VariantDeque extracted_deque =
    variant.toDeque( &conversion_success );

  TEST_ASSERT( conversion_success );
  TEST_EQUALITY_CONST( extracted_deque.size(), 2 );
  TEST_EQUALITY_CONST( extracted_deque.front().toUnsignedLongLong(), 0ull );
  TEST_EQUALITY_CONST( extracted_deque.back().toUnsignedLongLong(), 1000000000000ull );

  // From a deque of deque of double
  variant = Utility::Variant::fromValue( std::deque<std::deque<double> >({std::deque<double>({-1.0, 0.0}), std::deque<double>({0.0, 1.0})}) );

  TEST_ASSERT( !variant.isNull() );

  extracted_deque = variant.toDeque( &conversion_success );
  
  TEST_ASSERT( conversion_success );
  TEST_EQUALITY_CONST( extracted_deque.size(), 2 );
  TEST_EQUALITY_CONST( extracted_deque.front().toDeque().size(), 2 );
  TEST_EQUALITY_CONST( extracted_deque.front().toDeque().front().toDouble(), -1.0 );
  TEST_EQUALITY_CONST( extracted_deque.front().toDeque().back().toDouble(), 0.0 );
  TEST_EQUALITY_CONST( extracted_deque.back().toDeque().size(), 2 );
  TEST_EQUALITY_CONST( extracted_deque.back().toDeque().front().toDouble(), 0.0 );
  TEST_EQUALITY_CONST( extracted_deque.back().toDeque().back().toDouble(), 1.0 );

  // From a map of int, double
  variant = Utility::Variant::fromValue( std::map<int,double>({std::make_pair(0, 0.0), std::make_pair(1, -1.0), std::make_pair(2, -2)}) );

  TEST_ASSERT( !variant.isNull() );
  
  Utility::VariantMap extracted_map =
    variant.toMap( &conversion_success );

  TEST_ASSERT( conversion_success );
  TEST_EQUALITY_CONST( extracted_map.size(), 3 );
  TEST_EQUALITY_CONST( extracted_map["0"].toDouble(), 0.0 );
  TEST_EQUALITY_CONST( extracted_map["1"].toDouble(), -1.0 );
  TEST_EQUALITY_CONST( extracted_map["2"].toDouble(), -2.0 );

  // From a map of int, map<string,int>
  variant = Utility::Variant::fromValue( std::map<int,std::map<std::string,int> >({std::make_pair(0, std::map<std::string,int>({std::make_pair("first", -1), std::make_pair("second", 1)})), std::make_pair(1, std::map<std::string,int>({std::make_pair("first", 0), std::make_pair("second", 10)}))}) );

  TEST_ASSERT( !variant.isNull() );

  extracted_map = variant.toMap( &conversion_success );

  TEST_ASSERT( conversion_success );
  TEST_EQUALITY_CONST( extracted_map.size(), 2 );
  TEST_EQUALITY_CONST( extracted_map["0"].toMap().size(), 2 );
  TEST_EQUALITY_CONST( extracted_map["0"].toMap()["first"].toInt(), -1 );
  TEST_EQUALITY_CONST( extracted_map["0"].toMap()["second"].toInt(), 1 );
  TEST_EQUALITY_CONST( extracted_map["1"].toMap().size(), 2 );
  TEST_EQUALITY_CONST( extracted_map["1"].toMap()["first"].toInt(), 0 );
  TEST_EQUALITY_CONST( extracted_map["1"].toMap()["second"].toInt(), 10 );
}

//---------------------------------------------------------------------------//
// Check that the value of a variant can be set
TEUCHOS_UNIT_TEST( Variant, setValue_basic_types )
{
  // From a char
  Utility::Variant variant;
  variant.setValue( 'a' );
  
  bool conversion_success = false;

  TEST_ASSERT( !variant.isNull() );
  TEST_EQUALITY_CONST( variant.toChar( &conversion_success ), 'a' );
  TEST_ASSERT( conversion_success );

  // From a char[]
  variant.setValue( "Test string" );
  
  TEST_ASSERT( !variant.isNull() );
  TEST_EQUALITY_CONST( variant.toString( &conversion_success ), "Test string" );
  TEST_ASSERT( conversion_success );

  variant.toChar( &conversion_success );

  TEST_ASSERT( !conversion_success );

  // From a boolean
  variant.setValue( true );

  TEST_ASSERT( !variant.isNull() );
  TEST_EQUALITY_CONST( variant.toBool( &conversion_success ), true );
  TEST_ASSERT( conversion_success );

  variant.setValue( false );

  TEST_ASSERT( !variant.isNull() );
  TEST_EQUALITY_CONST( variant.toBool( &conversion_success ), false );
  TEST_ASSERT( conversion_success );

  variant.setValue( "true" );

  TEST_ASSERT( !variant.isNull() );
  TEST_EQUALITY_CONST( variant.toBool( &conversion_success ), true );
  TEST_ASSERT( conversion_success );

  variant.setValue( "false" );
  
  TEST_ASSERT( !variant.isNull() );
  TEST_EQUALITY_CONST( variant.toBool( &conversion_success ), false );
  TEST_ASSERT( conversion_success );

  // From a signed char
  variant.setValue( (signed char)-1 );

  TEST_ASSERT( !variant.isNull() );
  TEST_EQUALITY_CONST( variant.toSignedChar( &conversion_success ), -1 );
  TEST_ASSERT( conversion_success );

  // From an unsigned char
  variant.setValue( (unsigned char)0 );

  TEST_ASSERT( !variant.isNull() );
  TEST_EQUALITY_CONST( variant.toUnsignedChar( &conversion_success ), 0 );
  TEST_ASSERT( conversion_success );

  // From an int8_t
  variant.setValue( (int8_t)-100 );

  TEST_ASSERT( !variant.isNull() );
  TEST_EQUALITY_CONST( variant.toInt8( &conversion_success ), -100 );
  TEST_ASSERT( conversion_success );

  // From an uint8_t
  variant.setValue( (uint8_t)255 );

  TEST_ASSERT( !variant.isNull() );
  TEST_EQUALITY_CONST( variant.toUint8( &conversion_success ), 255 );
  TEST_ASSERT( conversion_success );

  // From an int16_t
  variant.setValue( (int16_t)-200 );

  TEST_ASSERT( !variant.isNull() );
  TEST_EQUALITY_CONST( variant.toInt16( &conversion_success ), -200 );
  TEST_ASSERT( conversion_success );

  // From a uint16_t
  variant.setValue( (uint16_t)300 );

  TEST_ASSERT( !variant.isNull() );
  TEST_EQUALITY_CONST( variant.toUint16( &conversion_success ), 300 );
  TEST_ASSERT( conversion_success );

  // From an int32_t
  variant.setValue( (int32_t)-1000000000 );

  TEST_ASSERT( !variant.isNull() );
  TEST_EQUALITY_CONST( variant.toInt32( &conversion_success ), -1000000000 );
  TEST_ASSERT( conversion_success );

  // From an uint32_t
  variant.setValue( (uint32_t)1000000000 );

  TEST_ASSERT( !variant.isNull() );
  TEST_EQUALITY_CONST( variant.toUint32( &conversion_success ), 1000000000 );
  TEST_ASSERT( conversion_success );

  // From a short
  variant.setValue( (short)-100 );

  TEST_ASSERT( !variant.isNull() );
  TEST_EQUALITY_CONST( variant.toShort( &conversion_success ), -100 );
  TEST_ASSERT( conversion_success );

  // From an unsigned short
  variant.setValue( (unsigned short)255 );

  TEST_ASSERT( !variant.isNull() );
  TEST_EQUALITY_CONST( variant.toUnsignedShort( &conversion_success ), 255 );
  TEST_ASSERT( conversion_success );

  // From an int
  variant.setValue( -100000000 );

  TEST_ASSERT( !variant.isNull() );
  TEST_EQUALITY_CONST( variant.toInt( &conversion_success ), -100000000 );
  TEST_ASSERT( conversion_success );

  // From an unsigned int
  variant.setValue( 100000000u );

  TEST_ASSERT( !variant.isNull() );
  TEST_EQUALITY_CONST( variant.toUnsignedInt( &conversion_success ), 100000000 );
  TEST_ASSERT( conversion_success );

  // From a long
  variant.setValue( -100000000l );

  TEST_ASSERT( !variant.isNull() );
  TEST_EQUALITY_CONST( variant.toLong( &conversion_success ), -100000000 );
  TEST_ASSERT( conversion_success );

  // From an unsigned long
  variant.setValue( 100000000ul );

  TEST_ASSERT( !variant.isNull() );
  TEST_EQUALITY_CONST( variant.toUnsignedLong( &conversion_success ), 100000000 );
  TEST_ASSERT( conversion_success );

  // From a long long
  variant.setValue( -10000000000ll );

  TEST_ASSERT( !variant.isNull() );
  TEST_EQUALITY_CONST( variant.toLongLong( &conversion_success ), -10000000000 );
  TEST_ASSERT( conversion_success );
  
  // From an unsigned long long
  variant.setValue( 10000000000ull );
  
  TEST_ASSERT( !variant.isNull() );
  TEST_EQUALITY_CONST( variant.toUnsignedLongLong( &conversion_success ), 10000000000 );
  TEST_ASSERT( conversion_success );

  // From a float
  variant.setValue( 1.0f );
  
  TEST_ASSERT( !variant.isNull() );
  TEST_EQUALITY_CONST( variant.toFloat( &conversion_success ), 1.0f );
  TEST_ASSERT( conversion_success );
  
  variant.setValue( "-inf" );
  
  TEST_ASSERT( !variant.isNull() );
  TEST_EQUALITY_CONST( variant.toFloat( &conversion_success ),
                       -std::numeric_limits<float>::infinity() );
  TEST_ASSERT( conversion_success );
                       
  variant.setValue( "-pi" );

  TEST_ASSERT( !variant.isNull() );
  TEST_EQUALITY_CONST( variant.toFloat( &conversion_success ),
                       -(float)Utility::PhysicalConstants::pi );
  TEST_ASSERT( conversion_success );

  // From a double
  variant.setValue( -1.0 );

  TEST_ASSERT( !variant.isNull() );
  TEST_EQUALITY_CONST( variant.toDouble( &conversion_success ), -1.0 );
  TEST_ASSERT( conversion_success );

  variant.setValue( "Infty" );

  TEST_ASSERT( !variant.isNull() );
  TEST_EQUALITY_CONST( variant.toDouble( &conversion_success ),
                       std::numeric_limits<double>::infinity() );
  TEST_ASSERT( conversion_success );

  variant.setValue( "3pi/4" );

  TEST_ASSERT( !variant.isNull() );
  TEST_EQUALITY_CONST( variant.toDouble( &conversion_success ),
                       3*Utility::PhysicalConstants::pi/4 );
  TEST_ASSERT( conversion_success );
}

//---------------------------------------------------------------------------//
// Check that the value of a variant can be set
TEUCHOS_UNIT_TEST( Variant, setValue_container )
{
  // From a string
  Utility::Variant variant;
  variant.setValue( std::string("Test string") );

  bool conversion_success = false;

  TEST_ASSERT( !variant.isNull() );
  TEST_EQUALITY_CONST( variant.toString( &conversion_success ), "Test string" );
  TEST_ASSERT( conversion_success );

  variant.toChar( &conversion_success );

  TEST_ASSERT( !conversion_success );

  // From a vector of int
  variant.setValue( std::vector<int>({-1, 0, 1}) );

  TEST_ASSERT( !variant.isNull() );

  Utility::VariantVector extracted_vector =
    variant.toVector( &conversion_success );
  
  TEST_ASSERT( conversion_success );
  TEST_EQUALITY_CONST( extracted_vector.size(), 3 );
  TEST_EQUALITY_CONST( extracted_vector[0].toInt(), -1 );
  TEST_EQUALITY_CONST( extracted_vector[1].toInt(), 0 );
  TEST_EQUALITY_CONST( extracted_vector[2].toInt(), 1 );

  // From a vector of vector of int
  variant.setValue( std::vector<std::vector<int> >({std::vector<int>({-1, 0}), std::vector<int>({1, 2})}) );

  TEST_ASSERT( !variant.isNull() );

  extracted_vector = variant.toVector( &conversion_success );

  TEST_ASSERT( conversion_success );
  TEST_EQUALITY_CONST( extracted_vector.size(), 2 );
  TEST_EQUALITY_CONST( extracted_vector[0].toVector().size(), 2 );
  TEST_EQUALITY_CONST( extracted_vector[0].toVector()[0].toInt(), -1 );
  TEST_EQUALITY_CONST( extracted_vector[0].toVector()[1].toInt(), 0 );

  variant.setValue( "{ {-1, 0},  {1, 2}  }" );

  TEST_ASSERT( !variant.isNull() );

  extracted_vector = variant.toVector( &conversion_success );

  TEST_ASSERT( conversion_success );
  TEST_EQUALITY_CONST( extracted_vector.size(), 2 );
  TEST_EQUALITY_CONST( extracted_vector[0].toVector().size(), 2 );
  TEST_EQUALITY_CONST( extracted_vector[0].toVector()[0].toInt(), -1 );
  TEST_EQUALITY_CONST( extracted_vector[0].toVector()[1].toInt(), 0 );

  // From a vector of list of pair
  variant.setValue( std::vector<std::list<std::pair<int,float> > >({std::list<std::pair<int,float> >({std::make_pair(-1, 0.0f), std::make_pair(1, 1.0f)}), std::list<std::pair<int,float> >({std::make_pair(1, 1.0f), std::make_pair(-1, 0.0f)})}) );

  TEST_ASSERT( !variant.isNull() );

  extracted_vector = variant.toVector( &conversion_success );

  TEST_ASSERT( conversion_success );
  TEST_EQUALITY_CONST( extracted_vector.size(), 2 );
  TEST_EQUALITY_CONST( extracted_vector[0].toList().size(), 2 );
  TEST_EQUALITY_CONST( extracted_vector[0].toList().front().toString(), "{-1, 0.000000000e+00}" );
  TEST_EQUALITY_CONST( extracted_vector[0].toList().back().toString(), " {1, 1.000000000e+00}" );
  TEST_EQUALITY_CONST( extracted_vector[1].toList().size(), 2 );
  TEST_EQUALITY_CONST( extracted_vector[1].toList().front().toString(), "{1, 1.000000000e+00}" );
  TEST_EQUALITY_CONST( extracted_vector[1].toList().back().toString(), " {-1, 0.000000000e+00}" );

  // From a list of int
  variant.setValue( std::list<int>({-1, 1}) );

  TEST_ASSERT( !variant.isNull() );

  Utility::VariantList extracted_list =
    variant.toList( &conversion_success );

  TEST_ASSERT( conversion_success );
  TEST_EQUALITY_CONST( extracted_list.size(), 2 );
  TEST_EQUALITY_CONST( extracted_list.front().toInt(), -1 );
  TEST_EQUALITY_CONST( extracted_list.back().toInt(), 1 );

  // From a list of list of float
  variant.setValue( std::list<std::list<float> >({std::list<float>({-1.0f, 0.0f}), std::list<float>({0.0f, 1.0f})}) );

  TEST_ASSERT( !variant.isNull() );

  extracted_list = variant.toList( &conversion_success );

  TEST_ASSERT( conversion_success );
  TEST_EQUALITY_CONST( extracted_list.size(), 2 );
  TEST_EQUALITY_CONST( extracted_list.front().toList().size(), 2 );
  TEST_EQUALITY_CONST( extracted_list.front().toList().front().toFloat(), -1.0f );
  TEST_EQUALITY_CONST( extracted_list.front().toList().back().toFloat(), 0.0f );
  TEST_EQUALITY_CONST( extracted_list.back().toList().size(), 2 );
  TEST_EQUALITY_CONST( extracted_list.back().toList().front().toFloat(), 0.0f );
  TEST_EQUALITY_CONST( extracted_list.back().toList().back().toFloat(), 1.0f );

  // From a forward list of int
  variant.setValue( std::forward_list<int>({0, 100}) );

  TEST_ASSERT( !variant.isNull() );

  Utility::VariantForwardList extracted_forward_list =
    variant.toForwardList( &conversion_success );

  TEST_ASSERT( conversion_success );
  TEST_EQUALITY_CONST( std::distance( extracted_forward_list.begin(), extracted_forward_list.end() ), 2 );
  TEST_EQUALITY_CONST( extracted_forward_list.front().toInt(), 0 );

  extracted_forward_list.pop_front();

  TEST_EQUALITY_CONST( extracted_forward_list.front().toInt(), 100 );

  // From a forward list of forward list of double
  variant.setValue( std::forward_list<std::forward_list<double> >({std::forward_list<double>({-1.0, 0.0}), std::forward_list<double>({0.0, 1.0})}) );

  TEST_ASSERT( !variant.isNull() );

  extracted_forward_list = variant.toForwardList( &conversion_success );

  TEST_ASSERT( conversion_success );
  TEST_EQUALITY_CONST( std::distance( extracted_forward_list.begin(), extracted_forward_list.end() ), 2 );

  {
    Utility::VariantForwardList sub_forward_list =
      extracted_forward_list.front().toForwardList();
    
    TEST_EQUALITY_CONST( std::distance( sub_forward_list.begin(), sub_forward_list.end() ), 2 );
    TEST_EQUALITY_CONST( sub_forward_list.front().toDouble(), -1.0 );

    sub_forward_list.pop_front();
    
    TEST_EQUALITY_CONST( sub_forward_list.front().toDouble(), 0.0 );

    extracted_forward_list.pop_front();

    sub_forward_list = extracted_forward_list.front().toForwardList();

    TEST_EQUALITY_CONST( std::distance( sub_forward_list.begin(), sub_forward_list.end() ), 2 );
    TEST_EQUALITY_CONST( sub_forward_list.front().toDouble(), 0.0 );

    sub_forward_list.pop_front();
    
    TEST_EQUALITY_CONST( sub_forward_list.front().toDouble(), 1.0 );
  }

  // From a deque of unsigned long long
  variant.setValue( std::deque<unsigned long long>({0ull, 1000000000000ull}) );

  TEST_ASSERT( !variant.isNull() );

  Utility::VariantDeque extracted_deque =
    variant.toDeque( &conversion_success );

  TEST_ASSERT( conversion_success );
  TEST_EQUALITY_CONST( extracted_deque.size(), 2 );
  TEST_EQUALITY_CONST( extracted_deque.front().toUnsignedLongLong(), 0ull );
  TEST_EQUALITY_CONST( extracted_deque.back().toUnsignedLongLong(), 1000000000000ull );

  // From a deque of deque of double
  variant.setValue( std::deque<std::deque<double> >({std::deque<double>({-1.0, 0.0}), std::deque<double>({0.0, 1.0})}) );

  TEST_ASSERT( !variant.isNull() );

  extracted_deque = variant.toDeque( &conversion_success );
  
  TEST_ASSERT( conversion_success );
  TEST_EQUALITY_CONST( extracted_deque.size(), 2 );
  TEST_EQUALITY_CONST( extracted_deque.front().toDeque().size(), 2 );
  TEST_EQUALITY_CONST( extracted_deque.front().toDeque().front().toDouble(), -1.0 );
  TEST_EQUALITY_CONST( extracted_deque.front().toDeque().back().toDouble(), 0.0 );
  TEST_EQUALITY_CONST( extracted_deque.back().toDeque().size(), 2 );
  TEST_EQUALITY_CONST( extracted_deque.back().toDeque().front().toDouble(), 0.0 );
  TEST_EQUALITY_CONST( extracted_deque.back().toDeque().back().toDouble(), 1.0 );

  // From a map of int, double
  variant.setValue( std::map<int,double>({std::make_pair(0, 0.0), std::make_pair(1, -1.0), std::make_pair(2, -2)}) );

  TEST_ASSERT( !variant.isNull() );
  
  Utility::VariantMap extracted_map =
    variant.toMap( &conversion_success );

  TEST_ASSERT( conversion_success );
  TEST_EQUALITY_CONST( extracted_map.size(), 3 );
  TEST_EQUALITY_CONST( extracted_map["0"].toDouble(), 0.0 );
  TEST_EQUALITY_CONST( extracted_map["1"].toDouble(), -1.0 );
  TEST_EQUALITY_CONST( extracted_map["2"].toDouble(), -2.0 );

  // From a map of int, map<string,int>
  variant.setValue( std::map<int,std::map<std::string,int> >({std::make_pair(0, std::map<std::string,int>({std::make_pair("first", -1), std::make_pair("second", 1)})), std::make_pair(1, std::map<std::string,int>({std::make_pair("first", 0), std::make_pair("second", 10)}))}) );

  TEST_ASSERT( !variant.isNull() );

  extracted_map = variant.toMap( &conversion_success );

  TEST_ASSERT( conversion_success );
  TEST_EQUALITY_CONST( extracted_map.size(), 2 );
  TEST_EQUALITY_CONST( extracted_map["0"].toMap().size(), 2 );
  TEST_EQUALITY_CONST( extracted_map["0"].toMap()["first"].toInt(), -1 );
  TEST_EQUALITY_CONST( extracted_map["0"].toMap()["second"].toInt(), 1 );
  TEST_EQUALITY_CONST( extracted_map["1"].toMap().size(), 2 );
  TEST_EQUALITY_CONST( extracted_map["1"].toMap()["first"].toInt(), 0 );
  TEST_EQUALITY_CONST( extracted_map["1"].toMap()["second"].toInt(), 10 );
}

//---------------------------------------------------------------------------//
// Check that a variant can be converted to a type
TEUCHOS_UNIT_TEST( Variant, convert_basic_types )
{
  // Store a char
  Utility::Variant variant( 'a' );

  TEST_ASSERT( variant.canConvert<char>() );

  char extracted_char;
  variant.convert( extracted_char );
  
  TEST_EQUALITY_CONST( extracted_char, 'a' );

  // Store a boolean
  variant.setValue( true );

  TEST_ASSERT( variant.canConvert<bool>() );
  
  bool extracted_bool;
  variant.convert( extracted_bool );
  
  TEST_EQUALITY_CONST( extracted_bool, true );

  variant.setValue( false );

  TEST_ASSERT( variant.canConvert<bool>() );

  variant.convert( extracted_bool );

  TEST_EQUALITY_CONST( extracted_bool, false );

  variant.setValue( "True" );

  TEST_ASSERT( variant.canConvert<bool>() );
  
  variant.convert( extracted_bool );
  
  TEST_EQUALITY_CONST( extracted_bool, true );

  variant.setValue( "FALSE" );

  TEST_ASSERT( variant.canConvert<bool>() );
  
  variant.convert( extracted_bool );
  
  TEST_EQUALITY_CONST( extracted_bool, false );

  // Store a signed char
  variant.setValue( static_cast<signed char>(-1) );

  TEST_ASSERT( variant.canConvert<signed char>() );
  
  signed char extracted_signed_char;
  variant.convert( extracted_signed_char );

  TEST_EQUALITY_CONST( extracted_signed_char, -1 );
  
  // Store an unsigned char
  variant.setValue( static_cast<unsigned char>(0) );

  TEST_ASSERT( variant.canConvert<unsigned char>() );

  unsigned char extracted_unsigned_char;
  variant.convert( extracted_unsigned_char );

  TEST_EQUALITY_CONST( extracted_unsigned_char, 0 );

  // Store an int8_t
  variant.setValue( static_cast<int8_t>(-100) );

  TEST_ASSERT( variant.canConvert<int8_t>() );

  int8_t extracted_int8;

  variant.convert( extracted_int8 );

  TEST_EQUALITY_CONST( extracted_int8, -100 );

  // Store an uint8_t
  variant.setValue( static_cast<uint8_t>(255) );

  TEST_ASSERT( variant.canConvert<uint8_t>() );

  uint8_t extracted_uint8;

  variant.convert( extracted_uint8 );

  TEST_EQUALITY_CONST( extracted_uint8, 255 );

  // Store an int16_t
  variant.setValue( static_cast<int16_t>(-200) );

  TEST_ASSERT( variant.canConvert<int16_t>() );

  int16_t extracted_int16;

  variant.convert( extracted_int16 );

  TEST_EQUALITY_CONST( extracted_int16, -200 );

  // Store a uint16_t
  variant.setValue( static_cast<uint16_t>(300) );

  TEST_ASSERT( variant.canConvert<uint16_t>() );

  uint16_t extracted_uint16;

  variant.convert( extracted_uint16 );

  TEST_EQUALITY_CONST( extracted_uint16, 300 );

  // Store an int32_t
  variant.setValue( static_cast<int32_t>(-1000000000) );

  TEST_ASSERT( variant.canConvert<int32_t>() );

  int32_t extracted_int32;

  variant.convert( extracted_int32 );

  TEST_EQUALITY_CONST( extracted_int32, -1000000000 );

  // Store an uint32_t
  variant.setValue( static_cast<uint32_t>(1000000000) );

  TEST_ASSERT( variant.canConvert<uint32_t>() );

  uint32_t extracted_uint32;

  variant.convert( extracted_uint32 );

  TEST_EQUALITY_CONST( extracted_uint32, 1000000000 );

  // Store a short
  variant.setValue( static_cast<short>(-100) );

  TEST_ASSERT( variant.canConvert<short>() );

  short extracted_short;
  
  variant.convert( extracted_short );

  TEST_EQUALITY_CONST( extracted_short, -100 );

  // Store an unsigned short
  variant.setValue( static_cast<unsigned short>(255) );

  TEST_ASSERT( variant.canConvert<unsigned short>() );

  unsigned short extracted_unsigned_short;

  variant.convert( extracted_unsigned_short );

  TEST_EQUALITY_CONST( extracted_unsigned_short, 255 );
  
  // Store an int
  variant.setValue( -100000000 );

  TEST_ASSERT( variant.canConvert<int>() );

  int extracted_int;

  variant.convert( extracted_int );

  TEST_EQUALITY_CONST( extracted_int, -100000000 );

  // Store an unsigned int
  variant.setValue( 100000000u );

  TEST_ASSERT( variant.canConvert<unsigned int>() );

  unsigned int extracted_unsigned_int;

  variant.convert( extracted_unsigned_int );

  TEST_EQUALITY_CONST( extracted_unsigned_int, 100000000u );

  // Store a long
  variant.setValue( -100000000l );

  TEST_ASSERT( variant.canConvert<long>() );

  long extracted_long;

  variant.convert( extracted_long );

  TEST_EQUALITY_CONST( extracted_long, -100000000l );

  // Store an unsigned long
  variant.setValue( 100000000ul );

  TEST_ASSERT( variant.canConvert<unsigned long>() );

  unsigned long extracted_unsigned_long;

  variant.convert( extracted_unsigned_long );

  TEST_EQUALITY_CONST( extracted_unsigned_long, 100000000ul );

  // Store a long long
  variant.setValue( -10000000000ll );

  TEST_ASSERT( variant.canConvert<long long>() );

  long long extracted_long_long;

  variant.convert( extracted_long_long );

  TEST_EQUALITY_CONST( extracted_long_long, -10000000000ll );
  
  // Store an unsigned long long
  variant.setValue( 10000000000ull );

  TEST_ASSERT( variant.canConvert<unsigned long long>() );

  unsigned long long extracted_unsigned_long_long;

  variant.convert( extracted_unsigned_long_long );

  TEST_EQUALITY_CONST( extracted_unsigned_long_long, 10000000000ull );
  
  // Store a float
  variant.setValue( 1.0f );

  TEST_ASSERT( variant.canConvert<float>() );

  float extracted_float;

  variant.convert( extracted_float );

  TEST_EQUALITY_CONST( extracted_float, 1.0f );

  variant.setValue( "-INF" );

  TEST_ASSERT( variant.canConvert<float>() );

  variant.convert( extracted_float );

  TEST_EQUALITY_CONST( extracted_float,
                       -std::numeric_limits<float>::infinity() );

  variant.setValue( "-PI" );

  TEST_ASSERT( variant.canConvert<float>() );

  variant.convert( extracted_float );

  TEST_EQUALITY_CONST( extracted_float,
                       -(float)Utility::PhysicalConstants::pi );

  // Store a double
  variant.setValue( -1.0 );

  TEST_ASSERT( variant.canConvert<double>() );

  double extracted_double;

  variant.convert( extracted_double );

  TEST_EQUALITY_CONST( extracted_double, -1.0 );

  variant.setValue( "INFty" );

  TEST_ASSERT( variant.canConvert<double>() );

  variant.convert( extracted_double );

  TEST_EQUALITY_CONST( extracted_double,
                       std::numeric_limits<double>::infinity() );
  
  variant.setValue( "3pi/4" );

  TEST_ASSERT( variant.canConvert<double>() );

  variant.convert( extracted_double );
  TEST_EQUALITY_CONST( extracted_double, 3*Utility::PhysicalConstants::pi/4 );
}

//---------------------------------------------------------------------------//
// Check that a variant can be converted to a type
TEUCHOS_UNIT_TEST( Variant, convert_container )
{
  // Store a basic value
  Utility::Variant variant( " 1 " );

  TEST_ASSERT( variant.canConvert<int>() );

  // Convert to a string
  TEST_ASSERT( variant.canConvert<std::string>() );

  std::string extracted_string;

  variant.convert( extracted_string );

  TEST_EQUALITY_CONST( extracted_string, " 1 " );

  // Convert to a general vector
  TEST_ASSERT( variant.canConvert<Utility::VariantVector>() );
  TEST_ASSERT( !variant.canConvert<std::vector<int> >() );

  Utility::VariantVector extracted_vector;
  
  variant.convert( extracted_vector );

  TEST_EQUALITY_CONST( extracted_vector.size(), 1 );
  TEST_EQUALITY_CONST( extracted_vector[0].toInt(), 1 );

  // Convert to a general list
  TEST_ASSERT( variant.canConvert<Utility::VariantList>() );
  TEST_ASSERT( !variant.canConvert<std::list<int> >() );

  Utility::VariantList extracted_list;

  variant.convert( extracted_list );

  TEST_EQUALITY_CONST( extracted_list.size(), 1 );
  TEST_EQUALITY_CONST( extracted_list.front().toInt(), 1 );

  // Convert to a general forward list
  TEST_ASSERT( variant.canConvert<Utility::VariantForwardList>() );
  TEST_ASSERT( !variant.canConvert<std::forward_list<int> >() );

  Utility::VariantForwardList extracted_forward_list;

  variant.convert( extracted_forward_list );

  TEST_EQUALITY_CONST( std::distance( extracted_forward_list.begin(), extracted_forward_list.end() ), 1 );
  TEST_EQUALITY_CONST( extracted_forward_list.front().toInt(), 1 );

  // Convert to a general deque
  TEST_ASSERT( variant.canConvert<Utility::VariantDeque>() );
  TEST_ASSERT( !variant.canConvert<std::deque<int> >() );

  Utility::VariantDeque extracted_deque;

  variant.convert( extracted_deque );

  TEST_EQUALITY_CONST( extracted_deque.size(), 1 );
  TEST_EQUALITY_CONST( extracted_deque.front().toInt(), 1 );

  // Cannot convert to a map
  TEST_ASSERT( !(variant.canConvert<Utility::VariantMap>()) );
  
  // Store a container
  variant.setValue( " { -1, 0, 1 } " );

  TEST_ASSERT( !variant.canConvert<char>() );

  // Convert to a string
  TEST_ASSERT( variant.canConvert<std::string>() );

  variant.convert( extracted_string );

  TEST_EQUALITY_CONST( extracted_string, " { -1, 0, 1 } " );

  // Convert to a general vector
  TEST_ASSERT( variant.canConvert<Utility::VariantVector>() );
  
  variant.convert( extracted_vector );
  
  TEST_EQUALITY_CONST( extracted_vector.size(), 3 );
  TEST_EQUALITY_CONST( extracted_vector[0].toInt(), -1 );
  TEST_EQUALITY_CONST( extracted_vector[1].toInt(), 0 );
  TEST_EQUALITY_CONST( extracted_vector[2].toInt(), 1 );

  // Convert to a vector of int
  TEST_ASSERT( variant.canConvert<std::vector<int> >() );

  std::vector<int> extracted_vector_int;

  variant.convert( extracted_vector_int );

  TEST_EQUALITY_CONST( extracted_vector_int.size(), 3 );
  TEST_EQUALITY_CONST( extracted_vector_int[0], -1 );
  TEST_EQUALITY_CONST( extracted_vector_int[1], 0 );
  TEST_EQUALITY_CONST( extracted_vector_int[2], 1 );

  // Convert to a general list
  TEST_ASSERT( variant.canConvert<Utility::VariantList>() );

  variant.convert( extracted_list );

  TEST_EQUALITY_CONST( extracted_list.size(), 3 );
  TEST_EQUALITY_CONST( extracted_list.front().toInt(), -1 );
  TEST_EQUALITY_CONST( extracted_list.back().toInt(), 1 );

  // Convert to a list of int
  TEST_ASSERT( variant.canConvert<std::list<int> >() );

  std::list<int> extracted_list_int;

  variant.convert( extracted_list_int );

  TEST_EQUALITY_CONST( extracted_list_int.size(), 3 );
  TEST_EQUALITY_CONST( extracted_list_int.front(), -1 );
  TEST_EQUALITY_CONST( extracted_list_int.back(), 1 );

  // Convert to a general forward_list
  TEST_ASSERT( variant.canConvert<Utility::VariantForwardList>() );

  variant.convert( extracted_forward_list );

  TEST_EQUALITY_CONST( std::distance( extracted_forward_list.begin(), extracted_forward_list.end() ), 3 );
  TEST_EQUALITY_CONST( extracted_forward_list.front().toInt(), -1 );

  // Convert to a forward_list of int
  TEST_ASSERT( variant.canConvert<std::forward_list<int> >() );

  std::forward_list<int> extracted_forward_list_int;

  variant.convert( extracted_forward_list_int );

  TEST_EQUALITY_CONST( std::distance( extracted_forward_list_int.begin(), extracted_forward_list_int.end() ), 3 );
  TEST_EQUALITY_CONST( extracted_forward_list_int.front(), -1 );

  // Convert to a general deque
  TEST_ASSERT( variant.canConvert<Utility::VariantDeque>() );

  variant.convert( extracted_deque );

  TEST_EQUALITY_CONST( extracted_deque.size(), 3 );
  TEST_EQUALITY_CONST( extracted_deque.front().toInt(), -1 );
  TEST_EQUALITY_CONST( extracted_deque.back().toInt(), 1 );

  // Convert to a deque of int
  TEST_ASSERT( variant.canConvert<std::deque<int> >() );

  std::deque<int> extracted_deque_int;

  variant.convert( extracted_deque_int );

  TEST_EQUALITY_CONST( extracted_deque_int.size(), 3 );
  TEST_EQUALITY_CONST( extracted_deque_int.front(), -1 );
  TEST_EQUALITY_CONST( extracted_deque_int.back(), 1 );

  // Cannot convert to a map
  TEST_ASSERT( !(variant.canConvert<Utility::VariantMap>()) );
  TEST_ASSERT( !(variant.canConvert<std::map<int,int> >()) );

  // Store a container of containers
  variant.setValue( "{ {-1, 0} ,  {1, 2} }" );

  // Convert to a general vector
  TEST_ASSERT( variant.canConvert<Utility::VariantVector>() );

  variant.convert( extracted_vector );
  
  TEST_EQUALITY_CONST( extracted_vector.size(), 2 )
  TEST_EQUALITY_CONST( extracted_vector[0].toVector().size(), 2 );
  TEST_EQUALITY_CONST( extracted_vector[0].toVector()[0].toInt(), -1 );
  TEST_EQUALITY_CONST( extracted_vector[0].toVector()[1].toInt(), 0 );
  TEST_EQUALITY_CONST( extracted_vector[1].toVector().size(), 2 );
  TEST_EQUALITY_CONST( extracted_vector[1].toVector()[0].toInt(), 1 );
  TEST_EQUALITY_CONST( extracted_vector[1].toVector()[1].toInt(), 2 );

  // Convert to a vector of vector of int
  TEST_ASSERT( variant.canConvert<std::vector<std::vector<int> > >() );

  std::vector<std::vector<int> > extracted_vector_vector_int;
  
  variant.convert( extracted_vector_vector_int );

  TEST_EQUALITY_CONST( extracted_vector_vector_int.size(), 2 )
  TEST_EQUALITY_CONST( extracted_vector_vector_int[0].size(), 2 );
  TEST_EQUALITY_CONST( extracted_vector_vector_int[0][0], -1 );
  TEST_EQUALITY_CONST( extracted_vector_vector_int[0][1], 0 );
  TEST_EQUALITY_CONST( extracted_vector_vector_int[1].size(), 2 );
  TEST_EQUALITY_CONST( extracted_vector_vector_int[1][0], 1 );
  TEST_EQUALITY_CONST( extracted_vector_vector_int[1][1], 2 );

  // Convert to a vector of pairs
  TEST_ASSERT( (variant.canConvert<std::vector<std::pair<int,int> > >()) );

  std::vector<std::pair<int,int> > extracted_vector_pair;

  variant.convert( extracted_vector_pair );

  TEST_EQUALITY_CONST( extracted_vector_pair.size(), 2 );
  TEST_EQUALITY_CONST( extracted_vector_pair[0].first, -1 );
  TEST_EQUALITY_CONST( extracted_vector_pair[0].second, 0 );
  TEST_EQUALITY_CONST( extracted_vector_pair[1].first, 1 );
  TEST_EQUALITY_CONST( extracted_vector_pair[1].second, 2 );

  // Convert to a vector of tuples
  TEST_ASSERT( (variant.canConvert<std::vector<std::tuple<int,int> > >()) );
  TEST_ASSERT( !(variant.canConvert<std::vector<std::tuple<int,int,int> > >()) );
  
  std::vector<std::tuple<int,int> > extracted_vector_tuple;

  variant.convert( extracted_vector_tuple );

  TEST_EQUALITY_CONST( extracted_vector_tuple.size(), 2 );
  TEST_EQUALITY_CONST( Utility::get<0>(extracted_vector_tuple[0]), -1 );
  TEST_EQUALITY_CONST( Utility::get<1>(extracted_vector_tuple[0]), 0 );
  TEST_EQUALITY_CONST( Utility::get<0>(extracted_vector_tuple[1]), 1 );
  TEST_EQUALITY_CONST( Utility::get<1>(extracted_vector_tuple[1]), 2 );

  // Convert to a general map
  TEST_ASSERT( (variant.canConvert<Utility::VariantMap>()) );

  Utility::VariantMap extracted_map;

  variant.convert( extracted_map );

  TEST_EQUALITY_CONST( extracted_map.size(), 2 );
  TEST_EQUALITY_CONST( extracted_map["-1"].toInt(), 0 );
  TEST_EQUALITY_CONST( extracted_map["1"].toInt(), 2 );

  // Convert to a map of int, int
  TEST_ASSERT( (variant.canConvert<std::map<int,int> >()) );

  std::map<int,int> extracted_map_int_int;

  variant.convert( extracted_map_int_int );

  TEST_EQUALITY_CONST( extracted_map_int_int.size(), 2 );
  TEST_EQUALITY_CONST( extracted_map_int_int[-1], 0 );
  TEST_EQUALITY_CONST( extracted_map_int_int[1], 2 );
}

//---------------------------------------------------------------------------//
// Check that a variant can be cast to a type
TEUCHOS_UNIT_TEST( Variant, variant_cast_basic_types )
{
  // Store a char
  Utility::Variant variant( 'a' );

  char extracted_char;  
  TEST_NOTHROW( extracted_char = Utility::variant_cast<char>( variant ) );
  
  TEST_EQUALITY_CONST( extracted_char, 'a' );

  // Store a boolean
  variant.setValue( true );
  
  bool extracted_bool;
  TEST_NOTHROW( extracted_bool = Utility::variant_cast<bool>( variant ) );
  
  TEST_EQUALITY_CONST( extracted_bool, true );

  variant.setValue( false );

  TEST_NOTHROW( extracted_bool = Utility::variant_cast<bool>( variant ) );

  TEST_EQUALITY_CONST( extracted_bool, false );

  variant.setValue( "True" );
  
  TEST_NOTHROW( extracted_bool = Utility::variant_cast<bool>( variant ) );
  
  TEST_EQUALITY_CONST( extracted_bool, true );

  variant.setValue( "FALSE" );
  
  TEST_NOTHROW( extracted_bool = Utility::variant_cast<bool>( variant ) );
  
  TEST_EQUALITY_CONST( extracted_bool, false );

  // Store a signed char
  variant.setValue( static_cast<signed char>(-1) );
  
  signed char extracted_signed_char;
  TEST_NOTHROW( extracted_signed_char = Utility::variant_cast<signed char>( variant ) );

  TEST_EQUALITY_CONST( extracted_signed_char, -1 );
  
  // Store an unsigned char
  variant.setValue( static_cast<unsigned char>(0) );

  unsigned char extracted_unsigned_char;
  TEST_NOTHROW( extracted_unsigned_char = Utility::variant_cast<unsigned char>( variant ) );

  TEST_EQUALITY_CONST( extracted_unsigned_char, 0 );

  // Store an int8_t
  variant.setValue( static_cast<int8_t>(-100) );

  int8_t extracted_int8;
  TEST_NOTHROW( extracted_int8 = Utility::variant_cast<int8_t>( variant ) );

  TEST_EQUALITY_CONST( extracted_int8, -100 );

  // Store an uint8_t
  variant.setValue( static_cast<uint8_t>(255) );

  uint8_t extracted_uint8;
  TEST_NOTHROW( extracted_uint8 = Utility::variant_cast<uint8_t>( variant ) );

  TEST_EQUALITY_CONST( extracted_uint8, 255 );

  // Store an int16_t
  variant.setValue( static_cast<int16_t>(-200) );

  int16_t extracted_int16;
  TEST_NOTHROW( extracted_int16 = Utility::variant_cast<int16_t>( variant ) );

  TEST_EQUALITY_CONST( extracted_int16, -200 );

  // Store a uint16_t
  variant.setValue( static_cast<uint16_t>(300) );

  uint16_t extracted_uint16;
  TEST_NOTHROW( extracted_uint16 = Utility::variant_cast<uint16_t>( variant ) );

  TEST_EQUALITY_CONST( extracted_uint16, 300 );

  // Store an int32_t
  variant.setValue( static_cast<int32_t>(-1000000000) );

  int32_t extracted_int32;
  TEST_NOTHROW( extracted_int32 = Utility::variant_cast<int32_t>( variant ) );

  TEST_EQUALITY_CONST( extracted_int32, -1000000000 );

  // Store an uint32_t
  variant.setValue( static_cast<uint32_t>(1000000000) );

  uint32_t extracted_uint32;
  TEST_NOTHROW( extracted_uint32 = Utility::variant_cast<uint32_t>( variant ) );

  TEST_EQUALITY_CONST( extracted_uint32, 1000000000 );

  // Store a short
  variant.setValue( static_cast<short>(-100) );

  short extracted_short;
  TEST_NOTHROW( extracted_short = Utility::variant_cast<short>( variant ) );

  TEST_EQUALITY_CONST( extracted_short, -100 );

  // Store an unsigned short
  variant.setValue( static_cast<unsigned short>(255) );

  unsigned short extracted_unsigned_short;
  TEST_NOTHROW( extracted_unsigned_short = Utility::variant_cast<unsigned short>( variant ) );

  TEST_EQUALITY_CONST( extracted_unsigned_short, 255 );
  
  // Store an int
  variant.setValue( -100000000 );

  int extracted_int;
  TEST_NOTHROW( extracted_int = Utility::variant_cast<int>( variant ) );

  TEST_EQUALITY_CONST( extracted_int, -100000000 );

  // Store an unsigned int
  variant.setValue( 100000000u );

  unsigned int extracted_unsigned_int;
  TEST_NOTHROW( extracted_unsigned_int = Utility::variant_cast<unsigned>( variant ) );

  TEST_EQUALITY_CONST( extracted_unsigned_int, 100000000u );

  // Store a long
  variant.setValue( -100000000l );

  long extracted_long;
  TEST_NOTHROW( extracted_long = Utility::variant_cast<long>( variant ) );

  TEST_EQUALITY_CONST( extracted_long, -100000000l );

  // Store an unsigned long
  variant.setValue( 100000000ul );

  unsigned long extracted_unsigned_long;
  TEST_NOTHROW( extracted_unsigned_long = Utility::variant_cast<unsigned long>( variant ) );

  TEST_EQUALITY_CONST( extracted_unsigned_long, 100000000ul );

  // Store a long long
  variant.setValue( -10000000000ll );

  long long extracted_long_long;
  TEST_NOTHROW( extracted_long_long = Utility::variant_cast<long long>( variant ) );

  TEST_EQUALITY_CONST( extracted_long_long, -10000000000ll );
  
  // Store an unsigned long long
  variant.setValue( 10000000000ull );

  unsigned long long extracted_unsigned_long_long;
  TEST_NOTHROW( extracted_unsigned_long_long = Utility::variant_cast<unsigned long long>( variant ) );

  TEST_EQUALITY_CONST( extracted_unsigned_long_long, 10000000000ull );
  
  // Store a float
  variant.setValue( 1.0f );

  float extracted_float;
  TEST_NOTHROW( extracted_float = Utility::variant_cast<float>( variant ) );

  TEST_EQUALITY_CONST( extracted_float, 1.0f );

  variant.setValue( "-INF" );
  TEST_NOTHROW( extracted_float = Utility::variant_cast<float>( variant ) );

  TEST_EQUALITY_CONST( extracted_float,
                       -std::numeric_limits<float>::infinity() );

  variant.setValue( "-PI" );
  TEST_NOTHROW( extracted_float = Utility::variant_cast<float>( variant ) );

  TEST_EQUALITY_CONST( extracted_float,
                       -(float)Utility::PhysicalConstants::pi );

  // Store a double
  variant.setValue( -1.0 );

  double extracted_double;
  TEST_NOTHROW( extracted_double = Utility::variant_cast<double>( variant ) );

  TEST_EQUALITY_CONST( extracted_double, -1.0 );

  variant.setValue( "INFty" );
  TEST_NOTHROW( extracted_double = Utility::variant_cast<double>( variant ) );

  TEST_EQUALITY_CONST( extracted_double,
                       std::numeric_limits<double>::infinity() );
  
  variant.setValue( "3pi/4" );
  TEST_NOTHROW( extracted_double = Utility::variant_cast<double>( variant ) );
  
  TEST_EQUALITY_CONST( extracted_double, 3*Utility::PhysicalConstants::pi/4 );
}

//---------------------------------------------------------------------------//
// Check that a variant can be converted to a type
TEUCHOS_UNIT_TEST( Variant, variant_cast_container )
{
  // Store a basic value
  Utility::Variant variant( " 1 " );

  TEST_THROW( Utility::variant_cast<char>( variant ),
              std::runtime_error );

  // Convert to a string
  std::string extracted_string;

  TEST_NOTHROW( extracted_string = Utility::variant_cast<std::string>( variant ) );
  TEST_EQUALITY_CONST( extracted_string, " 1 " );

  // Convert to a general vector
  TEST_THROW( Utility::variant_cast<std::vector<int> >( variant ),
              std::runtime_error );
  
  Utility::VariantVector extracted_vector;
  
  TEST_NOTHROW( extracted_vector = Utility::variant_cast<Utility::VariantVector>( variant ) );
  TEST_EQUALITY_CONST( extracted_vector.size(), 1 );
  TEST_EQUALITY_CONST( extracted_vector[0].toInt(), 1 );

  // Convert to a general list
  TEST_THROW( Utility::variant_cast<std::list<int> >( variant ),
              std::runtime_error );
  
  Utility::VariantList extracted_list;

  TEST_NOTHROW( extracted_list = Utility::variant_cast<Utility::VariantList>( variant ) );
  TEST_EQUALITY_CONST( extracted_list.size(), 1 );
  TEST_EQUALITY_CONST( extracted_list.front().toInt(), 1 );

  // Convert to a general forward list
  TEST_THROW( Utility::variant_cast<std::forward_list<int> >( variant ),
              std::runtime_error );

  Utility::VariantForwardList extracted_forward_list;

  TEST_NOTHROW( extracted_forward_list = Utility::variant_cast<Utility::VariantForwardList>( variant ) );
  TEST_EQUALITY_CONST( std::distance( extracted_forward_list.begin(), extracted_forward_list.end() ), 1 );
  TEST_EQUALITY_CONST( extracted_forward_list.front().toInt(), 1 );

  // Convert to a general deque
  TEST_THROW( Utility::variant_cast<std::deque<int> >( variant ),
              std::runtime_error );

  Utility::VariantDeque extracted_deque;

  TEST_NOTHROW( extracted_deque = Utility::variant_cast<Utility::VariantDeque>( variant ) );
  TEST_EQUALITY_CONST( extracted_deque.size(), 1 );
  TEST_EQUALITY_CONST( extracted_deque.front().toInt(), 1 );

  // Cannot convert to a map
  TEST_THROW( (Utility::variant_cast<Utility::VariantMap>( variant )),
              std::runtime_error );
  
  // Store a container
  variant.setValue( " { -1, 0, 1 } " );

  TEST_THROW( Utility::variant_cast<char>( variant ),
              std::runtime_error );

  // Convert to a string
  TEST_NOTHROW( extracted_string = Utility::variant_cast<std::string>( variant ) );
  TEST_EQUALITY_CONST( extracted_string, " { -1, 0, 1 } " );

  // Convert to a general vector
  TEST_NOTHROW( extracted_vector = Utility::variant_cast<Utility::VariantVector>( variant ) );  
  TEST_EQUALITY_CONST( extracted_vector.size(), 3 );
  TEST_EQUALITY_CONST( extracted_vector[0].toInt(), -1 );
  TEST_EQUALITY_CONST( extracted_vector[1].toInt(), 0 );
  TEST_EQUALITY_CONST( extracted_vector[2].toInt(), 1 );

  // Convert to a vector of int
  std::vector<int> extracted_vector_int;

  TEST_NOTHROW( extracted_vector_int = Utility::variant_cast<std::vector<int> >( variant ) );
  TEST_EQUALITY_CONST( extracted_vector_int.size(), 3 );
  TEST_EQUALITY_CONST( extracted_vector_int[0], -1 );
  TEST_EQUALITY_CONST( extracted_vector_int[1], 0 );
  TEST_EQUALITY_CONST( extracted_vector_int[2], 1 );

  // Convert to a general list
  TEST_NOTHROW( extracted_list = Utility::variant_cast<Utility::VariantList>( variant ) );
  TEST_EQUALITY_CONST( extracted_list.size(), 3 );
  TEST_EQUALITY_CONST( extracted_list.front().toInt(), -1 );
  TEST_EQUALITY_CONST( extracted_list.back().toInt(), 1 );

  // Convert to a list of int
  std::list<int> extracted_list_int;

  TEST_NOTHROW( extracted_list_int = Utility::variant_cast<std::list<int> >( variant ) );
  TEST_EQUALITY_CONST( extracted_list_int.size(), 3 );
  TEST_EQUALITY_CONST( extracted_list_int.front(), -1 );
  TEST_EQUALITY_CONST( extracted_list_int.back(), 1 );

  // Convert to a general forward_list
  TEST_NOTHROW( extracted_forward_list = Utility::variant_cast<Utility::VariantForwardList>( variant ) );
  TEST_EQUALITY_CONST( std::distance( extracted_forward_list.begin(), extracted_forward_list.end() ), 3 );
  TEST_EQUALITY_CONST( extracted_forward_list.front().toInt(), -1 );

  // Convert to a forward_list of int
  std::forward_list<int> extracted_forward_list_int;

  TEST_NOTHROW( extracted_forward_list_int = Utility::variant_cast<std::forward_list<int> >( variant ) );
  TEST_EQUALITY_CONST( std::distance( extracted_forward_list_int.begin(), extracted_forward_list_int.end() ), 3 );
  TEST_EQUALITY_CONST( extracted_forward_list_int.front(), -1 );

  // Convert to a general deque
  TEST_NOTHROW( extracted_deque = Utility::variant_cast<Utility::VariantDeque>( variant ) );
  TEST_EQUALITY_CONST( extracted_deque.size(), 3 );
  TEST_EQUALITY_CONST( extracted_deque.front().toInt(), -1 );
  TEST_EQUALITY_CONST( extracted_deque.back().toInt(), 1 );

  // Convert to a deque of int
  std::deque<int> extracted_deque_int;

  TEST_NOTHROW( extracted_deque_int = Utility::variant_cast<std::deque<int> >( variant ) );
  TEST_EQUALITY_CONST( extracted_deque_int.size(), 3 );
  TEST_EQUALITY_CONST( extracted_deque_int.front(), -1 );
  TEST_EQUALITY_CONST( extracted_deque_int.back(), 1 );

  // Cannot convert to a map
  TEST_THROW( (Utility::variant_cast<Utility::VariantMap>( variant )),
              std::runtime_error );
  TEST_THROW( (Utility::variant_cast<std::map<int,int> >( variant )),
              std::runtime_error );

  // Store a container of containers
  variant.setValue( "{ {-1, 0} ,  {1, 2} }" );

  // Convert to a general vector
  TEST_NOTHROW( extracted_vector = Utility::variant_cast<Utility::VariantVector>( variant ) );  
  TEST_EQUALITY_CONST( extracted_vector.size(), 2 )
  TEST_EQUALITY_CONST( extracted_vector[0].toVector().size(), 2 );
  TEST_EQUALITY_CONST( extracted_vector[0].toVector()[0].toInt(), -1 );
  TEST_EQUALITY_CONST( extracted_vector[0].toVector()[1].toInt(), 0 );
  TEST_EQUALITY_CONST( extracted_vector[1].toVector().size(), 2 );
  TEST_EQUALITY_CONST( extracted_vector[1].toVector()[0].toInt(), 1 );
  TEST_EQUALITY_CONST( extracted_vector[1].toVector()[1].toInt(), 2 );

  // Convert to a vector of vector of int
  std::vector<std::vector<int> > extracted_vector_vector_int;
  
  TEST_NOTHROW( extracted_vector_vector_int = Utility::variant_cast<std::vector<std::vector<int> > >( variant ) );
  TEST_EQUALITY_CONST( extracted_vector_vector_int.size(), 2 )
  TEST_EQUALITY_CONST( extracted_vector_vector_int[0].size(), 2 );
  TEST_EQUALITY_CONST( extracted_vector_vector_int[0][0], -1 );
  TEST_EQUALITY_CONST( extracted_vector_vector_int[0][1], 0 );
  TEST_EQUALITY_CONST( extracted_vector_vector_int[1].size(), 2 );
  TEST_EQUALITY_CONST( extracted_vector_vector_int[1][0], 1 );
  TEST_EQUALITY_CONST( extracted_vector_vector_int[1][1], 2 );

  // Convert to a vector of pairs
  std::vector<std::pair<int,int> > extracted_vector_pair;

  TEST_NOTHROW( (extracted_vector_pair = Utility::variant_cast<std::vector<std::pair<int,int> > >( variant )) );
  TEST_EQUALITY_CONST( extracted_vector_pair.size(), 2 );
  TEST_EQUALITY_CONST( extracted_vector_pair[0].first, -1 );
  TEST_EQUALITY_CONST( extracted_vector_pair[0].second, 0 );
  TEST_EQUALITY_CONST( extracted_vector_pair[1].first, 1 );
  TEST_EQUALITY_CONST( extracted_vector_pair[1].second, 2 );

  // Convert to a vector of tuples
  TEST_THROW( (Utility::variant_cast<std::vector<std::tuple<int,int,int> > >( variant )),
              std::runtime_error );
  
  std::vector<std::tuple<int,int> > extracted_vector_tuple;

  TEST_NOTHROW( (extracted_vector_tuple = Utility::variant_cast<std::vector<std::tuple<int,int> > >( variant )) );
  TEST_EQUALITY_CONST( extracted_vector_tuple.size(), 2 );
  TEST_EQUALITY_CONST( Utility::get<0>(extracted_vector_tuple[0]), -1 );
  TEST_EQUALITY_CONST( Utility::get<1>(extracted_vector_tuple[0]), 0 );
  TEST_EQUALITY_CONST( Utility::get<0>(extracted_vector_tuple[1]), 1 );
  TEST_EQUALITY_CONST( Utility::get<1>(extracted_vector_tuple[1]), 2 );

  // Convert to a general map
  Utility::VariantMap extracted_map;

  TEST_NOTHROW( (extracted_map = Utility::variant_cast<Utility::VariantMap>( variant )) );
  TEST_EQUALITY_CONST( extracted_map.size(), 2 );
  TEST_EQUALITY_CONST( extracted_map["-1"].toInt(), 0 );
  TEST_EQUALITY_CONST( extracted_map["1"].toInt(), 2 );

  // Convert to a map of int, int
  std::map<int,int> extracted_map_int_int;

  TEST_NOTHROW( (extracted_map_int_int = Utility::variant_cast<std::map<int,int> >( variant )) );
  TEST_EQUALITY_CONST( extracted_map_int_int.size(), 2 );
  TEST_EQUALITY_CONST( extracted_map_int_int[-1], 0 );
  TEST_EQUALITY_CONST( extracted_map_int_int[1], 2 );
}

//---------------------------------------------------------------------------//
// Check that a variant can be cleared
TEUCHOS_UNIT_TEST( Variant, clear )
{
  Utility::Variant variant( 1 );

  TEST_ASSERT( !variant.isNull() );

  variant.clear();

  TEST_ASSERT( variant.isNull() );
  TEST_EQUALITY_CONST( variant.toString(), std::string() );
}

//---------------------------------------------------------------------------//
// Check if the variant stores a basic type
TEUCHOS_UNIT_TEST( Variant, stores_type )
{
  // Store a char
  Utility::Variant variant( 'a' );

  TEST_ASSERT( variant.storesBasicType() );
  TEST_ASSERT( !variant.storesContainerType() );

  variant.setValue( '{' );

  TEST_ASSERT( variant.storesBasicType() );
  TEST_ASSERT( !variant.storesContainerType() );

  variant.setValue( '}' );

  TEST_ASSERT( variant.storesBasicType() );
  TEST_ASSERT( !variant.storesContainerType() );

  // Store a boolean
  variant.setValue( true );

  TEST_ASSERT( variant.storesBasicType() );
  TEST_ASSERT( !variant.storesContainerType() );

  variant.setValue( false );

  TEST_ASSERT( variant.storesBasicType() );
  TEST_ASSERT( !variant.storesContainerType() );

  // Store a signed char
  variant.setValue( static_cast<signed char>(-1) );

  TEST_ASSERT( variant.storesBasicType() );
  TEST_ASSERT( !variant.storesContainerType() );
  
  // Store an unsigned char
  variant.setValue( static_cast<unsigned char>(0) );

  TEST_ASSERT( variant.storesBasicType() );
  TEST_ASSERT( !variant.storesContainerType() );

  // Store an int8_t
  variant.setValue( static_cast<int8_t>(-100) );

  TEST_ASSERT( variant.storesBasicType() );
  TEST_ASSERT( !variant.storesContainerType() );

  // Store an uint8_t
  variant.setValue( static_cast<uint8_t>(255) );

  TEST_ASSERT( variant.storesBasicType() );
  TEST_ASSERT( !variant.storesContainerType() );

  // Store an int16_t
  variant.setValue( static_cast<int16_t>(-200) );

  TEST_ASSERT( variant.storesBasicType() );
  TEST_ASSERT( !variant.storesContainerType() );

  // Store a uint16_t
  variant.setValue( static_cast<uint16_t>(300) );

  TEST_ASSERT( variant.storesBasicType() );
  TEST_ASSERT( !variant.storesContainerType() );

  // Store an int32_t
  variant.setValue( static_cast<int32_t>(-1000000000) );

  TEST_ASSERT( variant.storesBasicType() );
  TEST_ASSERT( !variant.storesContainerType() );

  // Store an uint32_t
  variant.setValue( static_cast<uint32_t>(1000000000) );

  TEST_ASSERT( variant.storesBasicType() );
  TEST_ASSERT( !variant.storesContainerType() );

  // Store a short
  variant.setValue( static_cast<short>(-100) );

  TEST_ASSERT( variant.storesBasicType() );
  TEST_ASSERT( !variant.storesContainerType() );

  // Store an unsigned short
  variant.setValue( static_cast<unsigned short>(255) );

  TEST_ASSERT( variant.storesBasicType() );
  TEST_ASSERT( !variant.storesContainerType() );
  
  // Store an int
  variant.setValue( -100000000 );

  TEST_ASSERT( variant.storesBasicType() );
  TEST_ASSERT( !variant.storesContainerType() );

  // Store an unsigned int
  variant.setValue( 100000000u );

  TEST_ASSERT( variant.storesBasicType() );
  TEST_ASSERT( !variant.storesContainerType() );

  // Store a long
  variant.setValue( -100000000l );

  TEST_ASSERT( variant.storesBasicType() );
  TEST_ASSERT( !variant.storesContainerType() );

  // Store an unsigned long
  variant.setValue( 100000000ul );

  TEST_ASSERT( variant.storesBasicType() );
  TEST_ASSERT( !variant.storesContainerType() );

  // Store a long long
  variant.setValue( -10000000000ll );

  TEST_ASSERT( variant.storesBasicType() );
  TEST_ASSERT( !variant.storesContainerType() );
  
  // Store an unsigned long long
  variant.setValue( 10000000000ull );

  TEST_ASSERT( variant.storesBasicType() );
  TEST_ASSERT( !variant.storesContainerType() );
  
  // Store a float
  variant.setValue( 1.0f );

  TEST_ASSERT( variant.storesBasicType() );
  TEST_ASSERT( !variant.storesContainerType() );
  
  variant.setValue( "-INF" );

  TEST_ASSERT( variant.storesBasicType() );
  TEST_ASSERT( !variant.storesContainerType() );

  variant.setValue( "-PI" );

  TEST_ASSERT( variant.storesBasicType() );
  TEST_ASSERT( !variant.storesContainerType() );

  // Store a double
  variant.setValue( -1.0 );

  TEST_ASSERT( variant.storesBasicType() );
  TEST_ASSERT( !variant.storesContainerType() );
  
  variant.setValue( "INFty" );

  TEST_ASSERT( variant.storesBasicType() );
  TEST_ASSERT( !variant.storesContainerType() );
  
  variant.setValue( "3pi/4" );

  TEST_ASSERT( variant.storesBasicType() );
  TEST_ASSERT( !variant.storesContainerType() );

  // Store a string value
  variant.setValue( " 1 " );

  TEST_ASSERT( variant.storesBasicType() );
  TEST_ASSERT( !variant.storesContainerType() );
  
  // Store a container
  variant.setValue( " { -1, 0, 1 } " );

  TEST_ASSERT( !variant.storesBasicType() );
  TEST_ASSERT( variant.storesContainerType() );

  // Store a container of containers
  variant.setValue( "{ {-1, 0} ,  {1, 2} }" );

  TEST_ASSERT( !variant.storesBasicType() );
  TEST_ASSERT( variant.storesContainerType() );
}

//---------------------------------------------------------------------------//
// Check that variants can be swapped
TEUCHOS_UNIT_TEST( Variant, swap )
{
  Utility::Variant variant_a( 1 );
  Utility::Variant variant_b( std::vector<int>({-1, 0, 1}) );

  variant_a.swap( variant_b );

  TEST_EQUALITY_CONST( variant_a.toVector().size(), 3 );
  TEST_EQUALITY_CONST( variant_b.toInt(), 1 );

  std::swap( variant_a, variant_b );

  TEST_EQUALITY_CONST( variant_a.toInt(), 1 );
  TEST_EQUALITY_CONST( variant_b.toVector().size(), 3 );
}

//---------------------------------------------------------------------------//
// Check that a variant can be compactified
TEUCHOS_UNIT_TEST( Variant, compactify )
{
  Utility::Variant variant( "     1       " );
  
  variant.compactify();

  TEST_EQUALITY_CONST( variant.toString(), "1" );

  variant.setValue( "{ {1, 0 } , { -1, 2 }  }  " );
  variant.compactify();

  TEST_EQUALITY_CONST( variant.toString(), "{{1,0},{-1,2}}" );
  TEST_EQUALITY_CONST( (variant.toType<std::vector<std::pair<int,int> > >().size()), 2 );
}

//---------------------------------------------------------------------------//
// Check that variants can be compared
TEUCHOS_UNIT_TEST( Variant, comparison_operators )
{
  Utility::Variant variant_a, variant_b;

  TEST_ASSERT( variant_a == variant_b );

  variant_b.setValue( " " );

  TEST_ASSERT( variant_a != variant_b );

  variant_a.setValue( " " );

  TEST_ASSERT( variant_a == variant_b );
}

//---------------------------------------------------------------------------//
// Check that a variant can be converted to a string
TEUCHOS_UNIT_TEST( Variant, toString )
{
  Utility::Variant variant;

  TEST_EQUALITY_CONST( Utility::toString( variant ), std::string() );

  variant.setValue( 1 );

  TEST_EQUALITY_CONST( Utility::toString( variant ), "1" );

  variant.setValue( 1.0 );

  TEST_EQUALITY_CONST( Utility::toString( variant ), "1.000000000000000000e+00" );

  variant.setValue( std::make_pair(1u, 0.0f) );
  variant.compactify();

  TEST_EQUALITY_CONST( Utility::toString( variant ), "{1,0.000000000e+00}" );

  variant.setValue( std::make_tuple(1ll, -1.0, 'a') );
  variant.compactify();

  TEST_EQUALITY_CONST( Utility::toString( variant ), "{1,-1.000000000000000000e+00,a}" );

  variant.setValue( std::vector<int>({-1, 0, 1}) );
  variant.compactify();

  TEST_EQUALITY_CONST( Utility::toString( variant ), "{-1,0,1}" );

  variant.setValue( std::map<int,int>({std::make_pair(0, 0), std::make_pair(1, 1)}) );
  variant.compactify();

  TEST_EQUALITY_CONST( Utility::toString( variant ), "{{0,0},{1,1}}" ); 
}

//---------------------------------------------------------------------------//
// Check that a variant can be placed in a stream
TEUCHOS_UNIT_TEST( Variant, toStream )
{
  std::ostringstream oss;

  Utility::toStream( oss, Utility::Variant() );
  
  TEST_EQUALITY_CONST( oss.str(), std::string() );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, Utility::Variant::fromValue( 1 ) );

  TEST_EQUALITY_CONST( oss.str(), "1" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, Utility::Variant::fromValue( 1.0 ) );

  TEST_EQUALITY_CONST( oss.str(), "1.000000000000000000e+00" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, Utility::Variant::fromValue(std::make_pair(1u, 0.0f)).compactify() );

  TEST_EQUALITY_CONST( oss.str(), "{1,0.000000000e+00}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, Utility::Variant::fromValue(std::make_tuple(1ll, -1.0, 'a')).compactify() );

  TEST_EQUALITY_CONST( oss.str(), "{1,-1.000000000000000000e+00,a}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, Utility::Variant::fromValue(std::vector<int>({-1, 0, 1})).compactify() );

  TEST_EQUALITY_CONST( oss.str(), "{-1,0,1}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, Utility::Variant::fromValue(std::map<int,int>({std::make_pair(0, 0), std::make_pair(1, 1)})).compactify() );

  TEST_EQUALITY_CONST( oss.str(), "{{0,0},{1,1}}" ); 
}

//---------------------------------------------------------------------------//
// Check that a variant can be placed in a stream
TEUCHOS_UNIT_TEST( Variant, ostream_operator )
{
  std::ostringstream oss;
  
  oss << Utility::Variant();
  
  TEST_EQUALITY_CONST( oss.str(), std::string() );

  oss.str( "" );
  oss.clear();

  oss << Utility::Variant::fromValue( 1 );

  TEST_EQUALITY_CONST( oss.str(), "1" );

  oss.str( "" );
  oss.clear();

  oss << Utility::Variant::fromValue( 1.0 );

  TEST_EQUALITY_CONST( oss.str(), "1.000000000000000000e+00" );

  oss.str( "" );
  oss.clear();

  oss << Utility::Variant::fromValue(std::make_pair(1u, 0.0f)).compactify();

  TEST_EQUALITY_CONST( oss.str(), "{1,0.000000000e+00}" );

  oss.str( "" );
  oss.clear();

  oss << Utility::Variant::fromValue(std::make_tuple(1ll, -1.0, 'a')).compactify();

  TEST_EQUALITY_CONST( oss.str(), "{1,-1.000000000000000000e+00,a}" );

  oss.str( "" );
  oss.clear();

  oss << Utility::Variant::fromValue(std::vector<int>({-1, 0, 1})).compactify();

  TEST_EQUALITY_CONST( oss.str(), "{-1,0,1}" );

  oss.str( "" );
  oss.clear();

  oss << Utility::Variant::fromValue(std::map<int,int>({std::make_pair(0, 0), std::make_pair(1, 1)})).compactify();

  TEST_EQUALITY_CONST( oss.str(), "{{0,0},{1,1}}" ); 
}

//---------------------------------------------------------------------------//
// Check that a variant can be created from a string
TEUCHOS_UNIT_TEST( Variant, fromString )
{
  Utility::Variant variant = Utility::fromString<Utility::Variant>( " " );

  TEST_EQUALITY_CONST( variant.toString(), " " );

  variant = Utility::fromString<Utility::Variant>( "1" );

  TEST_EQUALITY_CONST( variant.toInt(), 1 );

  variant = Utility::fromString<Utility::Variant>( "1.0" );

  TEST_EQUALITY_CONST( variant.toDouble(), 1.0 );

  variant = Utility::fromString<Utility::Variant>( "{1, 0.0}" );

  TEST_EQUALITY_CONST( (variant.toType<std::pair<int,float> >()),
                       std::make_pair(1, 0.0f) );

  variant = Utility::fromString<Utility::Variant>( "{1, -1, a}" );

  TEST_EQUALITY_CONST( (variant.toType<std::tuple<long long, double, char> >()),
                       std::make_tuple(1ll, -1.0, 'a') );

  variant = Utility::fromString<Utility::Variant>( "{-1, 0, 1}" );

  TEST_COMPARE_CONTAINERS( variant.toType<std::vector<int> >(),
                           std::vector<int>({-1, 0, 1}) );

  variant = Utility::fromString<Utility::Variant>( "{{0,0},{1,1}}" );

  TEST_EQUALITY_CONST( variant.toMap().size(), 2 );
  TEST_EQUALITY_CONST( variant.toMap()["0"].toInt(), 0 );
  TEST_EQUALITY_CONST( variant.toMap()["1"].toInt(), 1 );

  Utility::VariantVector vector =
    Utility::fromString<Utility::VariantVector>( "{{0,0},{1,1}}" );

  TEST_EQUALITY_CONST( vector.size(), 2 );
  TEST_EQUALITY_CONST( vector[0].toString(), "{0,0}" );
  TEST_EQUALITY_CONST( vector[1].toString(), "{1,1}" );

  Utility::VariantMap map =
    Utility::fromString<Utility::VariantMap>( "{{0,0},{1,1}}" );

  TEST_EQUALITY_CONST( variant.toMap().size(), 2 );
  TEST_EQUALITY_CONST( variant.toMap()["0"].toInt(), 0 );
  TEST_EQUALITY_CONST( variant.toMap()["1"].toInt(), 1 );
}

//---------------------------------------------------------------------------//
// Check that a variant can be extracted from a stream
TEUCHOS_UNIT_TEST( Variant, fromStream )
{
  std::istringstream iss( " " );
  
  Utility::Variant variant;

  Utility::fromStream( iss, variant );

  TEST_EQUALITY_CONST( variant.toString(), " " );

  iss.str( "1" );
  iss.clear();

  Utility::fromStream( iss, variant );

  TEST_EQUALITY_CONST( variant.toInt(), 1 );

  iss.str( "pi" );
  iss.clear();

  Utility::fromStream( iss, variant );
  
  TEST_EQUALITY_CONST( variant.toDouble(), Utility::PhysicalConstants::pi );

  iss.str( "{1, 0.0}" );
  iss.clear();

  Utility::fromStream( iss, variant );
  
  TEST_EQUALITY_CONST( (variant.toType<std::pair<int,float> >()),
                       std::make_pair(1, 0.0f) );

  iss.str( "{1, -1, a}" );
  iss.clear();

  Utility::fromStream( iss, variant );

  TEST_EQUALITY_CONST( (variant.toType<std::tuple<long long, double, char> >()),
                       std::make_tuple(1ll, -1.0, 'a') );

  iss.str( "{-1, 0, 1}" );
  iss.clear();

  Utility::fromStream( iss, variant );

  TEST_COMPARE_CONTAINERS( variant.toType<std::vector<int> >(),
                           std::vector<int>({-1, 0, 1}) );

  iss.str( "{{0,0},{1,1}}" );
  iss.clear();

  Utility::fromStream( iss, variant );

  TEST_EQUALITY_CONST( variant.toMap().size(), 2 );
  TEST_EQUALITY_CONST( variant.toMap()["0"].toInt(), 0 );
  TEST_EQUALITY_CONST( variant.toMap()["1"].toInt(), 1 );

  iss.str( "{{0,0},{1,1}}" );
  iss.clear();
  
  Utility::VariantVector vector;

  Utility::fromStream( iss, vector );

  TEST_EQUALITY_CONST( vector.size(), 2 );
  TEST_EQUALITY_CONST( vector[0].toString(), "{0,0}" );
  TEST_EQUALITY_CONST( vector[1].toString(), "{1,1}" );

  iss.str( "{{0,0},{1,1}}" );
  iss.clear();
  
  Utility::VariantMap map;

  Utility::fromStream( iss, map );

  TEST_EQUALITY_CONST( variant.toMap().size(), 2 );
  TEST_EQUALITY_CONST( variant.toMap()["0"].toInt(), 0 );
  TEST_EQUALITY_CONST( variant.toMap()["1"].toInt(), 1 );
}

//---------------------------------------------------------------------------//
// Check that a variant can be extracted from a stream
TEUCHOS_UNIT_TEST( Variant, istream_operator )
{
  std::istringstream iss( " " );
  
  Utility::Variant variant;

  iss >> variant;

  TEST_EQUALITY_CONST( variant.toString(), " " );

  iss.str( "1" );
  iss.clear();

  iss >> variant;

  TEST_EQUALITY_CONST( variant.toInt(), 1 );

  iss.str( "pi" );
  iss.clear();

  iss >> variant;
  
  TEST_EQUALITY_CONST( variant.toDouble(), Utility::PhysicalConstants::pi );

  iss.str( "{1, 0.0}" );
  iss.clear();

  iss >> variant;
  
  TEST_EQUALITY_CONST( (variant.toType<std::pair<int,float> >()),
                       std::make_pair(1, 0.0f) );

  iss.str( "{1, -1, a}" );
  iss.clear();

  iss >> variant;

  TEST_EQUALITY_CONST( (variant.toType<std::tuple<long long, double, char> >()),
                       std::make_tuple(1ll, -1.0, 'a') );

  iss.str( "{-1, 0, 1}" );
  iss.clear();

  iss >> variant;

  TEST_COMPARE_CONTAINERS( variant.toType<std::vector<int> >(),
                           std::vector<int>({-1, 0, 1}) );

  iss.str( "{{0,0},{1,1}}" );
  iss.clear();

  iss >> variant;

  TEST_EQUALITY_CONST( variant.toMap().size(), 2 );
  TEST_EQUALITY_CONST( variant.toMap()["0"].toInt(), 0 );
  TEST_EQUALITY_CONST( variant.toMap()["1"].toInt(), 1 );

  iss.str( "{{0,0},{1,1}}" );
  iss.clear();
  
  Utility::VariantVector vector;

  iss >> vector;

  TEST_EQUALITY_CONST( vector.size(), 2 );
  TEST_EQUALITY_CONST( vector[0].toString(), "{0,0}" );
  TEST_EQUALITY_CONST( vector[1].toString(), "{1,1}" );

  iss.str( "{{0,0},{1,1}}" );
  iss.clear();
  
  Utility::VariantMap map;

  iss >> map;

  TEST_EQUALITY_CONST( variant.toMap().size(), 2 );
  TEST_EQUALITY_CONST( variant.toMap()["0"].toInt(), 0 );
  TEST_EQUALITY_CONST( variant.toMap()["1"].toInt(), 1 );
}

//---------------------------------------------------------------------------//
// end tstVariant.cpp
//---------------------------------------------------------------------------//
