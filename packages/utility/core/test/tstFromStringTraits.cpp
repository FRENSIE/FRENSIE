//---------------------------------------------------------------------------//
//!
//! \file   tstFromStringTraits.cpp
//! \author Alex Robinson
//! \brief  FromStringTraits unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <sstream>
#include <type_traits>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>

// FRENSIE Includes
#include "Utility_FromStringTraits.hpp"
#include "Utility_UnitTestHarnessExtensions.hpp"

typedef long long longlong;

//---------------------------------------------------------------------------//
// Instantiation Macros
//---------------------------------------------------------------------------//
#define UNIT_TEST_TEMPLATE_1_INSTANT( type, name )      \
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, short ); \
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, int );   \
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, long );  \
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, longlong )

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that a string can be created from a string
TEUCHOS_UNIT_TEST( FromStringTraits, string_fromString )
{
  TEST_EQUALITY_CONST( Utility::fromString<std::string>( " " ), " " );
  TEST_EQUALITY_CONST( Utility::fromString<std::string>( "testing" ), "testing" );
}

//---------------------------------------------------------------------------//
// Check that a string can be extracted from a stream
TEUCHOS_UNIT_TEST( FromStringTraits, string_fromStream )
{
  std::istringstream iss;
  iss.str( " " );

  std::string string;
  
  Utility::fromStream( iss, string );

  TEST_EQUALITY_CONST( string, " " );

  iss.str( "testing" );
  iss.clear();

  Utility::fromStream( iss, string );

  TEST_EQUALITY_CONST( string, "testing" );

  string.clear();

  iss.str( "testing-1,testing-2" );
  iss.clear();

  Utility::fromStream( iss, string, "," );

  TEST_EQUALITY_CONST( string, "testing-1" );

  string.clear();

  Utility::moveInputStreamToNextElement( iss, ',', '}' );

  Utility::fromStream( iss, string );

  TEST_EQUALITY_CONST( string, "testing-2" );
}

//---------------------------------------------------------------------------//
// Check that a boolean can be created from a string
TEUCHOS_UNIT_TEST( FromStringTraits, bool_fromString )
{
  TEST_EQUALITY_CONST( Utility::fromString<bool>( "0" ), false );
  TEST_EQUALITY_CONST( Utility::fromString<bool>( "false" ), false );

  TEST_EQUALITY_CONST( Utility::fromString<bool>( "1" ), true );
  TEST_EQUALITY_CONST( Utility::fromString<bool>( "true" ), true );
}

//---------------------------------------------------------------------------//
// Check that a boolean can be extracted from a stream
TEUCHOS_UNIT_TEST( FromStringTraits, bool_fromStream )
{
  std::istringstream iss( "0" );

  bool boolean;

  Utility::fromStream( iss, boolean );

  TEST_EQUALITY_CONST( boolean, false );

  iss.str( "false" );
  iss.clear();

  Utility::fromStream( iss, boolean );

  TEST_EQUALITY_CONST( boolean, false );

  iss.str( "1" );
  iss.clear();

  Utility::fromStream( iss, boolean );

  TEST_EQUALITY_CONST( boolean, true );

  iss.str( "true" );
  iss.clear();

  Utility::fromStream( iss, boolean );

  TEST_EQUALITY_CONST( boolean, true );

  iss.str( "0, true" );
  iss.clear();

  Utility::fromStream( iss, boolean, "," );

  TEST_EQUALITY_CONST( boolean, false );

  Utility::moveInputStreamToNextElement( iss, ',', '}' );

  Utility::fromStream( iss, boolean );

  TEST_EQUALITY_CONST( boolean, true );
}

//---------------------------------------------------------------------------//
// Check that a float can be created from a string
TEUCHOS_UNIT_TEST( FromStringTraits, float_fromString )
{
  TEST_EQUALITY_CONST( Utility::fromString<float>( "1" ), 1.0f );
  TEST_EQUALITY_CONST( Utility::fromString<float>( "-1.0" ), -1.0f );
  TEST_EQUALITY_CONST( Utility::fromString<float>( "0.000000000e+00" ), 0.0f );
  TEST_EQUALITY_CONST( Utility::fromString<float>( "inf" ),
                       std::numeric_limits<float>::infinity() );
  TEST_EQUALITY_CONST( Utility::fromString<float>( "infinity" ),
                       std::numeric_limits<float>::infinity() );
  TEST_EQUALITY_CONST( Utility::fromString<float>( "Inf" ),
                       std::numeric_limits<float>::infinity() );
  TEST_EQUALITY_CONST( Utility::fromString<float>( "Infinity" ),
                       std::numeric_limits<float>::infinity() );
  TEST_EQUALITY_CONST( Utility::fromString<float>( "InFiNiTy" ),
                       std::numeric_limits<float>::infinity() );
  TEST_EQUALITY_CONST( Utility::fromString<float>( "INF" ),
                       std::numeric_limits<float>::infinity() );
  TEST_EQUALITY_CONST( Utility::fromString<float>( "INFINITY" ),
                       std::numeric_limits<float>::infinity() );
  TEST_EQUALITY_CONST( Utility::fromString<float>( "-inf" ),
                       -std::numeric_limits<float>::infinity() );
  TEST_EQUALITY_CONST( Utility::fromString<float>( "-infinity" ),
                       -std::numeric_limits<float>::infinity() );
  TEST_EQUALITY_CONST( Utility::fromString<float>( "-Inf" ),
                       -std::numeric_limits<float>::infinity() );
  TEST_EQUALITY_CONST( Utility::fromString<float>( "-Infinity" ),
                       -std::numeric_limits<float>::infinity() );
  TEST_EQUALITY_CONST( Utility::fromString<float>( "-InFiNiTy" ),
                       -std::numeric_limits<float>::infinity() );
  TEST_EQUALITY_CONST( Utility::fromString<float>( "-INF" ),
                       -std::numeric_limits<float>::infinity() );
  TEST_EQUALITY_CONST( Utility::fromString<float>( "-INFINITY" ),
                       -std::numeric_limits<float>::infinity() );
  TEST_EQUALITY_CONST( Utility::fromString<float>( "pi" ),
                       (float)Utility::PhysicalConstants::pi );
  TEST_EQUALITY_CONST( Utility::fromString<float>( " Pi" ),
                       (float)Utility::PhysicalConstants::pi );
  TEST_EQUALITY_CONST( Utility::fromString<float>( " PI " ),
                       (float)Utility::PhysicalConstants::pi );
  TEST_EQUALITY_CONST( Utility::fromString<float>( "1*pi" ),
                       (float)Utility::PhysicalConstants::pi );
  TEST_EQUALITY_CONST( Utility::fromString<float>( "2Pi" ),
                       2*(float)Utility::PhysicalConstants::pi );
  TEST_EQUALITY_CONST( Utility::fromString<float>( "-pI" ),
                       -(float)Utility::PhysicalConstants::pi );
  TEST_FLOATING_EQUALITY( Utility::fromString<float>( "-5*pi" ),
                          -5*(float)Utility::PhysicalConstants::pi,
                          1e-7 );
  TEST_EQUALITY_CONST( Utility::fromString<float>( "pi/2" ),
                       (float)Utility::PhysicalConstants::pi/2 );
  TEST_EQUALITY_CONST( Utility::fromString<float>( "-pi /2" ),
                       -(float)Utility::PhysicalConstants::pi/2 );
  TEST_EQUALITY_CONST( Utility::fromString<float>( "pi / 3" ),
                       (float)Utility::PhysicalConstants::pi/3 );
  TEST_EQUALITY_CONST( Utility::fromString<float>( "2pi/3" ),
                       2*(float)Utility::PhysicalConstants::pi/3 );
  TEST_EQUALITY_CONST( Utility::fromString<float>( "-3pi/7" ),
                       -3*(float)Utility::PhysicalConstants::pi/7 );
  TEST_FLOATING_EQUALITY( Utility::fromString<float>( "5*pi / 3" ),
                          5*(float)Utility::PhysicalConstants::pi/3,
                          1e-7 );
  TEST_FLOATING_EQUALITY( Utility::fromString<float>( "-5*PI / 3" ),
                          -5*(float)Utility::PhysicalConstants::pi/3,
                          1e-7 );
}

//---------------------------------------------------------------------------//
// Check that a float can be extracted from a stream
TEUCHOS_UNIT_TEST( FromStringTraits, float_fromStream )
{
  std::istringstream iss( "1" );

  float test_float;

  Utility::fromStream( iss, test_float );

  TEST_EQUALITY_CONST( test_float, 1.0f );

  iss.str( "-1.0" );
  iss.clear();

  Utility::fromStream( iss, test_float );

  TEST_EQUALITY_CONST( test_float, -1.0f );

  iss.str( "0.000000000e+00" );
  iss.clear();

  Utility::fromStream( iss, test_float );

  TEST_EQUALITY_CONST( test_float, 0.0f );

  iss.str( "inf" );
  iss.clear();

  Utility::fromStream( iss, test_float );

  TEST_EQUALITY_CONST( test_float, std::numeric_limits<float>::infinity() );

  iss.str( "infinity" );
  iss.clear();

  Utility::fromStream( iss, test_float );

  TEST_EQUALITY_CONST( test_float, std::numeric_limits<float>::infinity() );

  iss.str( "Inf" );
  iss.clear();

  Utility::fromStream( iss, test_float );

  TEST_EQUALITY_CONST( test_float, std::numeric_limits<float>::infinity() );

  iss.str( "Infinity" );
  iss.clear();

  Utility::fromStream( iss, test_float );

  TEST_EQUALITY_CONST( test_float, std::numeric_limits<float>::infinity() );

  iss.str( "InFiNiTy" );
  iss.clear();

  Utility::fromStream( iss, test_float );

  TEST_EQUALITY_CONST( test_float, std::numeric_limits<float>::infinity() );

  iss.str( "INF" );
  iss.clear();

  Utility::fromStream( iss, test_float );

  TEST_EQUALITY_CONST( test_float, std::numeric_limits<float>::infinity() );

  iss.str( "INFINITY" );
  iss.clear();

  Utility::fromStream( iss, test_float );

  TEST_EQUALITY_CONST( test_float, std::numeric_limits<float>::infinity() );

  iss.str( "-inf" );
  iss.clear();

  Utility::fromStream( iss, test_float );

  TEST_EQUALITY_CONST( test_float, -std::numeric_limits<float>::infinity() );

  iss.str( "-infinity" );
  iss.clear();

  Utility::fromStream( iss, test_float );

  TEST_EQUALITY_CONST( test_float, -std::numeric_limits<float>::infinity() );

  iss.str( "-Inf" );
  iss.clear();

  Utility::fromStream( iss, test_float );

  TEST_EQUALITY_CONST( test_float, -std::numeric_limits<float>::infinity() );

  iss.str( "-Infinity" );
  iss.clear();

  Utility::fromStream( iss, test_float );

  TEST_EQUALITY_CONST( test_float, -std::numeric_limits<float>::infinity() );

  iss.str( "-InFiNiTy" );
  iss.clear();

  Utility::fromStream( iss, test_float );

  TEST_EQUALITY_CONST( test_float, -std::numeric_limits<float>::infinity() );

  iss.str( "-INF" );
  iss.clear();

  Utility::fromStream( iss, test_float );

  TEST_EQUALITY_CONST( test_float, -std::numeric_limits<float>::infinity() );

  iss.str( "-INFINITY" );
  iss.clear();

  Utility::fromStream( iss, test_float );

  TEST_EQUALITY_CONST( test_float, -std::numeric_limits<float>::infinity() );
  
  iss.str( "pi" );
  iss.clear();

  Utility::fromStream( iss, test_float );

  TEST_EQUALITY_CONST( test_float, (float)Utility::PhysicalConstants::pi );

  iss.str( " Pi" );
  iss.clear();

  Utility::fromStream( iss, test_float );

  TEST_EQUALITY_CONST( test_float, (float)Utility::PhysicalConstants::pi );

  iss.str( " PI " );
  iss.clear();

  Utility::fromStream( iss, test_float );

  TEST_EQUALITY_CONST( test_float, (float)Utility::PhysicalConstants::pi );
                       
  iss.str( "1*pi" );
  iss.clear();

  Utility::fromStream( iss, test_float );

  TEST_EQUALITY_CONST( test_float, (float)Utility::PhysicalConstants::pi );

  iss.str( "2Pi" );
  iss.clear();

  Utility::fromStream( iss, test_float );

  TEST_EQUALITY_CONST( test_float, 2*(float)Utility::PhysicalConstants::pi );
  
  iss.str( "-pI" );
  iss.clear();

  Utility::fromStream( iss, test_float );

  TEST_EQUALITY_CONST( test_float, -(float)Utility::PhysicalConstants::pi );

  iss.str( "-5*pi" );
  iss.clear();

  Utility::fromStream( iss, test_float );

  TEST_FLOATING_EQUALITY( test_float,
                          -5*(float)Utility::PhysicalConstants::pi,
                          1e-7 );

  iss.str( "pi/2" );
  iss.clear();

  Utility::fromStream( iss, test_float );

  
  TEST_EQUALITY_CONST( test_float, (float)Utility::PhysicalConstants::pi/2 );

  iss.str( "-pi /2" );
  iss.clear();

  Utility::fromStream( iss, test_float );

  TEST_EQUALITY_CONST( test_float, -(float)Utility::PhysicalConstants::pi/2 );

  iss.str( "pi / 3" );
  iss.clear();

  Utility::fromStream( iss, test_float );
  
  TEST_EQUALITY_CONST( test_float, (float)Utility::PhysicalConstants::pi/3 );

  iss.str( "2pi/3" );
  iss.clear();

  Utility::fromStream( iss, test_float );

  TEST_EQUALITY_CONST( test_float, 2*(float)Utility::PhysicalConstants::pi/3 );

  iss.str( "-3pi/7" );
  iss.clear();
  
  Utility::fromStream( iss, test_float );
  
  TEST_EQUALITY_CONST( test_float,
                       -3*(float)Utility::PhysicalConstants::pi/7 );

  iss.str( "5*pi / 3" );
  iss.clear();

  Utility::fromStream( iss, test_float );

  TEST_FLOATING_EQUALITY( test_float,
                          5*(float)Utility::PhysicalConstants::pi/3,
                          1e-7 );

  iss.str( "-5*PI / 3" );
  iss.clear();

  Utility::fromStream( iss, test_float );
  
  TEST_FLOATING_EQUALITY( test_float,
                          -5*(float)Utility::PhysicalConstants::pi/3,
                          1e-7 );

  iss.str( "-1, 1.000000000000000000e+00" );
  iss.clear();

  Utility::fromStream( iss, test_float, "," );

  TEST_EQUALITY_CONST( test_float, -1.0f );

  Utility::moveInputStreamToNextElement( iss, ',', '}' );

  Utility::fromStream( iss, test_float );

  TEST_EQUALITY_CONST( test_float, 1.0f );

  iss.str( "-1, 2*pi/3" );
  iss.clear();

  Utility::fromStream( iss, test_float, "," );

  TEST_EQUALITY_CONST( test_float, -1.0f );

  Utility::moveInputStreamToNextElement( iss, ',', '}' );

  Utility::fromStream( iss, test_float );

  TEST_EQUALITY_CONST( test_float, 2*(float)Utility::PhysicalConstants::pi/3 );

  iss.str( "-PI, Pi/2" );
  iss.clear();

  Utility::fromStream( iss, test_float, "," );

  TEST_EQUALITY_CONST( test_float, -(float)Utility::PhysicalConstants::pi );

  Utility::moveInputStreamToNextElement( iss, ',', '}' );

  Utility::fromStream( iss, test_float );

  TEST_EQUALITY_CONST( test_float, (float)Utility::PhysicalConstants::pi/2 );
}

//---------------------------------------------------------------------------//
// Check that a double can be created from a string
TEUCHOS_UNIT_TEST( FromStringTraits, double_fromString )
{
  TEST_EQUALITY_CONST( Utility::fromString<double>( "1" ), 1.0 );
  TEST_EQUALITY_CONST( Utility::fromString<double>( "-1.0" ), -1.0 );
  TEST_EQUALITY_CONST( Utility::fromString<double>( "0.000000000000000000e+00" ), 0.0 );
  TEST_EQUALITY_CONST( Utility::fromString<double>( "inf" ),
                       std::numeric_limits<double>::infinity() );
  TEST_EQUALITY_CONST( Utility::fromString<double>( "infinity" ),
                       std::numeric_limits<double>::infinity() );
  TEST_EQUALITY_CONST( Utility::fromString<double>( "Inf" ),
                       std::numeric_limits<double>::infinity() );
  TEST_EQUALITY_CONST( Utility::fromString<double>( "Infinity" ),
                       std::numeric_limits<double>::infinity() );
  TEST_EQUALITY_CONST( Utility::fromString<double>( "InFiNiTy" ),
                       std::numeric_limits<double>::infinity() );
  TEST_EQUALITY_CONST( Utility::fromString<double>( "INF" ),
                       std::numeric_limits<double>::infinity() );
  TEST_EQUALITY_CONST( Utility::fromString<double>( "INFINITY" ),
                       std::numeric_limits<double>::infinity() );
  TEST_EQUALITY_CONST( Utility::fromString<double>( "-inf" ),
                       -std::numeric_limits<double>::infinity() );
  TEST_EQUALITY_CONST( Utility::fromString<double>( "-infinity" ),
                       -std::numeric_limits<double>::infinity() );
  TEST_EQUALITY_CONST( Utility::fromString<double>( "-Inf" ),
                       -std::numeric_limits<double>::infinity() );
  TEST_EQUALITY_CONST( Utility::fromString<double>( "-Infinity" ),
                       -std::numeric_limits<double>::infinity() );
  TEST_EQUALITY_CONST( Utility::fromString<double>( "-InFiNiTy" ),
                       -std::numeric_limits<double>::infinity() );
  TEST_EQUALITY_CONST( Utility::fromString<double>( "-INF" ),
                       -std::numeric_limits<double>::infinity() );
  TEST_EQUALITY_CONST( Utility::fromString<double>( "-INFINITY" ),
                       -std::numeric_limits<double>::infinity() );
  TEST_EQUALITY_CONST( Utility::fromString<double>( "pi" ),
                       Utility::PhysicalConstants::pi );
  TEST_EQUALITY_CONST( Utility::fromString<double>( " Pi" ),
                       Utility::PhysicalConstants::pi );
  TEST_EQUALITY_CONST( Utility::fromString<double>( " PI " ),
                       Utility::PhysicalConstants::pi );
  TEST_EQUALITY_CONST( Utility::fromString<double>( "1*pi" ),
                       Utility::PhysicalConstants::pi );
  TEST_EQUALITY_CONST( Utility::fromString<double>( "2Pi" ),
                       2*Utility::PhysicalConstants::pi );
  TEST_EQUALITY_CONST( Utility::fromString<double>( "-pI" ),
                       -Utility::PhysicalConstants::pi );
  TEST_FLOATING_EQUALITY( Utility::fromString<double>( "-5*pi" ),
                          -5*Utility::PhysicalConstants::pi,
                          1e-7 );
  TEST_EQUALITY_CONST( Utility::fromString<double>( "pi/2" ),
                       Utility::PhysicalConstants::pi/2 );
  TEST_EQUALITY_CONST( Utility::fromString<double>( "-pi /2" ),
                       -Utility::PhysicalConstants::pi/2 );
  TEST_EQUALITY_CONST( Utility::fromString<double>( "pi / 3" ),
                       Utility::PhysicalConstants::pi/3 );
  TEST_EQUALITY_CONST( Utility::fromString<double>( "2pi/3" ),
                       2*Utility::PhysicalConstants::pi/3 );
  TEST_EQUALITY_CONST( Utility::fromString<double>( "-3pi/7" ),
                       -3*Utility::PhysicalConstants::pi/7 );
  TEST_FLOATING_EQUALITY( Utility::fromString<double>( "5*pi / 3" ),
                          5*Utility::PhysicalConstants::pi/3,
                          1e-7 );
  TEST_FLOATING_EQUALITY( Utility::fromString<double>( "-5*PI / 3" ),
                          -5*Utility::PhysicalConstants::pi/3,
                          1e-7 );
}

//---------------------------------------------------------------------------//
// Check that a double can be extracted from a stream
TEUCHOS_UNIT_TEST( FromStringTraits, double_fromStream )
{
  std::istringstream iss( "1" );

  double test_double;

  Utility::fromStream( iss, test_double );

  TEST_EQUALITY_CONST( test_double, 1.0 );

  iss.str( "-1.0" );
  iss.clear();

  Utility::fromStream( iss, test_double );

  TEST_EQUALITY_CONST( test_double, -1.0 );

  iss.str( "0.000000000000000000e+00" );
  iss.clear();

  Utility::fromStream( iss, test_double );

  TEST_EQUALITY_CONST( test_double, 0.0 );

  iss.str( "inf" );
  iss.clear();

  Utility::fromStream( iss, test_double );

  TEST_EQUALITY_CONST( test_double, std::numeric_limits<float>::infinity() );

  iss.str( "infinity" );
  iss.clear();

  Utility::fromStream( iss, test_double );

  TEST_EQUALITY_CONST( test_double, std::numeric_limits<float>::infinity() );

  iss.str( "Inf" );
  iss.clear();

  Utility::fromStream( iss, test_double );

  TEST_EQUALITY_CONST( test_double, std::numeric_limits<float>::infinity() );

  iss.str( "Infinity" );
  iss.clear();

  Utility::fromStream( iss, test_double );

  TEST_EQUALITY_CONST( test_double, std::numeric_limits<float>::infinity() );

  iss.str( "InFiNiTy" );
  iss.clear();

  Utility::fromStream( iss, test_double );

  TEST_EQUALITY_CONST( test_double, std::numeric_limits<float>::infinity() );

  iss.str( "INF" );
  iss.clear();

  Utility::fromStream( iss, test_double );

  TEST_EQUALITY_CONST( test_double, std::numeric_limits<float>::infinity() );

  iss.str( "INFINITY" );
  iss.clear();

  Utility::fromStream( iss, test_double );

  TEST_EQUALITY_CONST( test_double, std::numeric_limits<float>::infinity() );

  iss.str( "-inf" );
  iss.clear();

  Utility::fromStream( iss, test_double );

  TEST_EQUALITY_CONST( test_double, -std::numeric_limits<float>::infinity() );

  iss.str( "-infinity" );
  iss.clear();

  Utility::fromStream( iss, test_double );

  TEST_EQUALITY_CONST( test_double, -std::numeric_limits<float>::infinity() );

  iss.str( "-Inf" );
  iss.clear();

  Utility::fromStream( iss, test_double );

  TEST_EQUALITY_CONST( test_double, -std::numeric_limits<float>::infinity() );

  iss.str( "-Infinity" );
  iss.clear();

  Utility::fromStream( iss, test_double );

  TEST_EQUALITY_CONST( test_double, -std::numeric_limits<float>::infinity() );

  iss.str( "-InFiNiTy" );
  iss.clear();

  Utility::fromStream( iss, test_double );

  TEST_EQUALITY_CONST( test_double, -std::numeric_limits<float>::infinity() );

  iss.str( "-INF" );
  iss.clear();

  Utility::fromStream( iss, test_double );

  TEST_EQUALITY_CONST( test_double, -std::numeric_limits<float>::infinity() );

  iss.str( "-INFINITY" );
  iss.clear();

  Utility::fromStream( iss, test_double );

  TEST_EQUALITY_CONST( test_double, -std::numeric_limits<float>::infinity() );
  
  iss.str( "pi" );
  iss.clear();

  Utility::fromStream( iss, test_double );

  TEST_EQUALITY_CONST( test_double, Utility::PhysicalConstants::pi );

  iss.str( " Pi" );
  iss.clear();

  Utility::fromStream( iss, test_double );

  TEST_EQUALITY_CONST( test_double, Utility::PhysicalConstants::pi );

  iss.str( " PI " );
  iss.clear();

  Utility::fromStream( iss, test_double );

  TEST_EQUALITY_CONST( test_double, Utility::PhysicalConstants::pi );
                       
  iss.str( "1*pi" );
  iss.clear();

  Utility::fromStream( iss, test_double );

  TEST_EQUALITY_CONST( test_double, Utility::PhysicalConstants::pi );

  iss.str( "2Pi" );
  iss.clear();

  Utility::fromStream( iss, test_double );

  TEST_EQUALITY_CONST( test_double, 2*Utility::PhysicalConstants::pi );
  
  iss.str( "-pI" );
  iss.clear();

  Utility::fromStream( iss, test_double );

  TEST_EQUALITY_CONST( test_double, -Utility::PhysicalConstants::pi );

  iss.str( "-5*pi" );
  iss.clear();

  Utility::fromStream( iss, test_double );

  TEST_FLOATING_EQUALITY( test_double,
                          -5*Utility::PhysicalConstants::pi,
                          1e-7 );

  iss.str( "pi/2" );
  iss.clear();

  Utility::fromStream( iss, test_double );

  
  TEST_EQUALITY_CONST( test_double, Utility::PhysicalConstants::pi/2 );

  iss.str( "-pi /2" );
  iss.clear();

  Utility::fromStream( iss, test_double );

  TEST_EQUALITY_CONST( test_double, -Utility::PhysicalConstants::pi/2 );

  iss.str( "pi / 3" );
  iss.clear();

  Utility::fromStream( iss, test_double );
  
  TEST_EQUALITY_CONST( test_double, Utility::PhysicalConstants::pi/3 );

  iss.str( "2pi/3" );
  iss.clear();

  Utility::fromStream( iss, test_double );

  TEST_EQUALITY_CONST( test_double, 2*Utility::PhysicalConstants::pi/3 );

  iss.str( "-3pi/7" );
  iss.clear();
  
  Utility::fromStream( iss, test_double );
  
  TEST_EQUALITY_CONST( test_double,
                       -3*Utility::PhysicalConstants::pi/7 );

  iss.str( "5*pi / 3" );
  iss.clear();

  Utility::fromStream( iss, test_double );

  TEST_FLOATING_EQUALITY( test_double,
                          5*Utility::PhysicalConstants::pi/3,
                          1e-7 );

  iss.str( "-5*PI / 3" );
  iss.clear();

  Utility::fromStream( iss, test_double );
  
  TEST_FLOATING_EQUALITY( test_double,
                          -5*Utility::PhysicalConstants::pi/3,
                          1e-7 );

  iss.str( "-1, 1.000000000e+00" );
  iss.clear();

  Utility::fromStream( iss, test_double, "," );

  TEST_EQUALITY_CONST( test_double, -1.0 );

  Utility::moveInputStreamToNextElement( iss, ',', '}' );

  Utility::fromStream( iss, test_double );

  TEST_EQUALITY_CONST( test_double, 1.0 );

  iss.str( "-1, 2*pi/3" );
  iss.clear();

  Utility::fromStream( iss, test_double, "," );

  TEST_EQUALITY_CONST( test_double, -1.0 );

  Utility::moveInputStreamToNextElement( iss, ',', '}' );

  Utility::fromStream( iss, test_double );

  TEST_EQUALITY_CONST( test_double, 2*Utility::PhysicalConstants::pi/3 );

  iss.str( "-PI, Pi/2" );
  iss.clear();

  Utility::fromStream( iss, test_double, "," );

  TEST_EQUALITY_CONST( test_double, -Utility::PhysicalConstants::pi );

  Utility::moveInputStreamToNextElement( iss, ',', '}' );

  Utility::fromStream( iss, test_double );

  TEST_EQUALITY_CONST( test_double, Utility::PhysicalConstants::pi/2 );
}

//---------------------------------------------------------------------------//
// Check that signed integer types can be created from a string
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( FromStringTraits, fromString, T )
{
  TEST_EQUALITY_CONST( Utility::fromString<T>( "-10" ), -10 );
  TEST_EQUALITY_CONST( Utility::fromString<T>( "0" ), 0 );
  TEST_EQUALITY_CONST( Utility::fromString<T>( "0.0" ), 0 );
  TEST_EQUALITY_CONST( Utility::fromString<T>( "0.000000000e+00" ), 0 );
  TEST_EQUALITY_CONST( Utility::fromString<T>( "10" ), 10 );
}

UNIT_TEST_TEMPLATE_1_INSTANT( FromStringTraits, fromString );

//---------------------------------------------------------------------------//
// Check that signed integer types can be extracted from a stream
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( FromStringTraits, fromStream, T )
{
  std::istringstream iss( "-10" );

  T test_int;

  Utility::fromStream( iss, test_int );

  TEST_EQUALITY_CONST( test_int, -10 );

  iss.str( "0" );
  iss.clear();

  Utility::fromStream( iss, test_int );

  TEST_EQUALITY_CONST( test_int, 0 );

  iss.str( "0.0" );
  iss.clear();

  Utility::fromStream( iss, test_int );

  TEST_EQUALITY_CONST( test_int, 0 );

  iss.str( "0.000000000000000000e+00" );
  iss.clear();

  Utility::fromStream( iss, test_int );

  TEST_EQUALITY_CONST( test_int, 0 );

  iss.str( "10" );
  iss.clear();

  Utility::fromStream( iss, test_int );

  TEST_EQUALITY_CONST( test_int, 10 );

  iss.str( "-10, 1.000000000e+00" );
  iss.clear();
  
  Utility::fromStream( iss, test_int, "," );

  TEST_EQUALITY_CONST( test_int, -10 );

  Utility::moveInputStreamToNextElement( iss, ',', '}' );

  Utility::fromStream( iss, test_int );

  TEST_EQUALITY_CONST( test_int, 1 );
}

UNIT_TEST_TEMPLATE_1_INSTANT( FromStringTraits, fromStream );

//---------------------------------------------------------------------------//
// Check that unsigned integer types can be created from a string
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( FromStringTraits, unsigned_fromString, T )
{
  typedef typename std::make_unsigned<T>::type UnsignedT;
  
  TEST_EQUALITY_CONST( Utility::fromString<UnsignedT>( "0" ), 0 );
  TEST_EQUALITY_CONST( Utility::fromString<UnsignedT>( "0.0" ), 0 );
  TEST_EQUALITY_CONST( Utility::fromString<UnsignedT>( "0.000000000e+00" ), 0 );
  TEST_EQUALITY_CONST( Utility::fromString<UnsignedT>( "10" ), 10 );
  TEST_EQUALITY_CONST( Utility::fromString<UnsignedT>( "255" ), 255 );
}

UNIT_TEST_TEMPLATE_1_INSTANT( FromStringTraits, unsigned_fromString );

//---------------------------------------------------------------------------//
// Check that unsigned integer types can be extracted from a stream
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( FromStringTraits, unsigned_fromStream, T )
{
  std::istringstream iss( "0" );

  T test_int;

  Utility::fromStream( iss, test_int );

  TEST_EQUALITY_CONST( test_int, 0 );

  iss.str( "0.0" );
  iss.clear();

  Utility::fromStream( iss, test_int );

  TEST_EQUALITY_CONST( test_int, 0 );

  iss.str( "0.000000000000000000e+00" );
  iss.clear();

  Utility::fromStream( iss, test_int );

  TEST_EQUALITY_CONST( test_int, 0 );

  iss.str( "10" );
  iss.clear();

  Utility::fromStream( iss, test_int );

  TEST_EQUALITY_CONST( test_int, 10 );

  iss.str( "255" );
  iss.clear();

  Utility::fromStream( iss, test_int );

  TEST_EQUALITY_CONST( test_int, 255 );

  iss.str( "255, 1.000000000e+00" );
  iss.clear();
  
  Utility::fromStream( iss, test_int, "," );

  TEST_EQUALITY_CONST( test_int, 255 );

  Utility::moveInputStreamToNextElement( iss, ',', '}' );

  Utility::fromStream( iss, test_int );

  TEST_EQUALITY_CONST( test_int, 1 );
}

UNIT_TEST_TEMPLATE_1_INSTANT( FromStringTraits, unsigned_fromStream );

//---------------------------------------------------------------------------//
// end tstFromStringTraits.cpp
//---------------------------------------------------------------------------//
