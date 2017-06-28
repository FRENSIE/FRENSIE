//---------------------------------------------------------------------------//
//!
//! \file   tstVector.cpp
//! \author Alex Robinson
//! \brief  Vector helper function unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <sstream>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>

// FRENSIE Includes
#include "Utility_Vector.hpp"
#include "Utility_Tuple.hpp"
#include "Utility_UnitTestHarnessExtensions.hpp"

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that a vector can be converted to a string
TEUCHOS_UNIT_TEST( ToStringTraits, vector_toString )
{
  TEST_EQUALITY_CONST( Utility::toString( std::vector<short>( {-1, 2} ) ),
                       "{-1, 2}" );
  TEST_EQUALITY_CONST( Utility::toString( std::vector<unsigned short>( {0, 10, 100} ) ),
                       "{0, 10, 100}" );
  TEST_EQUALITY_CONST( Utility::toString( std::vector<int>( {-11111, 0, 11111, 22222} ) ),
                       "{-11111, 0, 11111, 22222}" );
  TEST_EQUALITY_CONST( Utility::toString( std::vector<unsigned int>( {0, 10, 100, 1000, 10000} ) ),
                       "{0, 10, 100, 1000, 10000}" );
  TEST_EQUALITY_CONST( Utility::toString( std::vector<long>( {-11111, 0, 11111, 22222} ) ),
                       "{-11111, 0, 11111, 22222}" );
  TEST_EQUALITY_CONST( Utility::toString( std::vector<unsigned long>( {0, 10, 100, 1000, 10000} ) ),
                       "{0, 10, 100, 1000, 10000}" );
  TEST_EQUALITY_CONST( Utility::toString( std::vector<long long>( {-10000000000, 0, 10000000000} ) ),
                       "{-10000000000, 0, 10000000000}" );
  TEST_EQUALITY_CONST( Utility::toString( std::vector<unsigned long long>( {0, 1000000000, 1000000000000} ) ),
                       "{0, 1000000000, 1000000000000}" );
  TEST_EQUALITY_CONST( Utility::toString( std::vector<float>( {-1.0f, 0.0f, 1.0f} ) ),
                       "{-1.000000000e+00, 0.000000000e+00, 1.000000000e+00}" );
  TEST_EQUALITY_CONST( Utility::toString( std::vector<double>( {-1.0, 0.0, 1.0} ) ),
                       "{-1.000000000000000000e+00, 0.000000000000000000e+00, 1.000000000000000000e+00}" );
  TEST_EQUALITY_CONST( Utility::toString( std::vector<char>( {'T', 'e', 's', 't', ' ', 's', 't', 'r', 'i', 'n', 'g' } ) ),
                       "{T, e, s, t,  , s, t, r, i, n, g}" );
  TEST_EQUALITY_CONST( Utility::toString( std::vector<std::string>( {"Test", "string"} ) ),
                       "{Test, string}" );
  TEST_EQUALITY_CONST( Utility::toString( std::vector<std::pair<int, int> >( {std::pair<int, int>({0, 1}), std::pair<int,int>({-1, 2})} ) ),
                       "{{0, 1}, {-1, 2}}" );
  TEST_EQUALITY_CONST( Utility::toString( std::vector<std::tuple<unsigned, double, long> >( {std::make_tuple( 0u, 1.0, -100000 ), std::make_tuple( 1u, -1.0, 100001 )} ) ),
                       "{{0, 1.000000000000000000e+00, -100000}, {1, -1.000000000000000000e+00, 100001}}" );
}

//---------------------------------------------------------------------------//
// Check that a vector can be placed in a stream
TEUCHOS_UNIT_TEST( ToStringTraits, vector_toStream )
{
  std::ostringstream oss;

  Utility::toStream( oss, std::vector<short>( {-1, 2} ) );
  
  TEST_EQUALITY_CONST( oss.str(), "{-1, 2}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::vector<unsigned short>( {0, 10, 100} ) );
  
  TEST_EQUALITY_CONST( oss.str(), "{0, 10, 100}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::vector<int>( {-11111, 0, 11111, 22222} ) );
  
  TEST_EQUALITY_CONST( oss.str(), "{-11111, 0, 11111, 22222}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::vector<unsigned int>( {0, 10, 100, 1000, 10000} ) );
  
  TEST_EQUALITY_CONST( oss.str(), "{0, 10, 100, 1000, 10000}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::vector<long>( {-11111, 0, 11111, 22222} ) );
  
  TEST_EQUALITY_CONST( oss.str(), "{-11111, 0, 11111, 22222}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::vector<unsigned long>( {0, 10, 100, 1000, 10000} ) );
  
  TEST_EQUALITY_CONST( oss.str(), "{0, 10, 100, 1000, 10000}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::vector<long long>( {-10000000000, 0, 10000000000} ) );
  
  TEST_EQUALITY_CONST( oss.str(), "{-10000000000, 0, 10000000000}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::vector<unsigned long long>( {0, 1000000000, 1000000000000} ) );
  
  TEST_EQUALITY_CONST( oss.str(), "{0, 1000000000, 1000000000000}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::vector<float>( {-1.0f, 0.0f, 1.0f} ) );
  
  TEST_EQUALITY_CONST( oss.str(),
                       "{-1.000000000e+00, 0.000000000e+00, 1.000000000e+00}" );
  
  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::vector<double>( {-1.0, 0.0, 1.0} ) );
  
  TEST_EQUALITY_CONST( oss.str(),
                       "{-1.000000000000000000e+00, 0.000000000000000000e+00, 1.000000000000000000e+00}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::vector<char>( {'T', 'e', 's', 't', ' ', 's', 't', 'r', 'i', 'n', 'g' } ) );
  
  TEST_EQUALITY_CONST( oss.str(), "{T, e, s, t,  , s, t, r, i, n, g}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::vector<std::string>( {"Test", "string"} ) );
  
  TEST_EQUALITY_CONST( oss.str(), "{Test, string}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::vector<std::pair<int, int>>( {std::pair<int, int>({0, 1}), std::pair<int,int>({-1, 2})} ) );
  
  TEST_EQUALITY_CONST( oss.str(), "{{0, 1}, {-1, 2}}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::vector<std::tuple<unsigned, double, long>>( {std::make_tuple( 0u, 1.0, -100000 ), std::make_tuple( 1u, -1.0, 100001 )} ) );
  
  TEST_EQUALITY_CONST( oss.str(),
                       "{{0, 1.000000000000000000e+00, -100000}, {1, -1.000000000000000000e+00, 100001}}" );
}

//---------------------------------------------------------------------------//
// Check that a vector can be created from a string
TEUCHOS_UNIT_TEST( FromStringTraits, vector_fromString )
{
  // Extract vector of short
  TEST_COMPARE_CONTAINERS( (Utility::fromString<std::vector<short> >( "{-1, 2}" )),
                           std::vector<short>({-1, 2}) );
  TEST_COMPARE_CONTAINERS( (Utility::fromString<std::vector<short> >( "{-1, 2i, 2}" )),
                           std::vector<short>({-1, 0, 1, 2}) );

  // Extract vector of unsigned short
  TEST_COMPARE_CONTAINERS( (Utility::fromString<std::vector<unsigned short> >( "{0, 10, 100}" )),
                           std::vector<unsigned short>({0, 10, 100}) );
  TEST_COMPARE_CONTAINERS( (Utility::fromString<std::vector<unsigned short> >( "{0, 3i, 100}" )),
                           std::vector<unsigned short>({0, 25, 50, 75, 100}) );

  // Extract vector of int
  TEST_COMPARE_CONTAINERS( (Utility::fromString<std::vector<int> >( "{-11111, 0, 11111, 22222}" )),
                           std::vector<int>({-11111, 0, 11111, 22222}) );
  TEST_COMPARE_CONTAINERS( (Utility::fromString<std::vector<int> >( "{-11111, 2i, 22222}" )),
                           std::vector<int>({-11111, 0, 11111, 22222}) );

  // Extract vector of unsigned int
  TEST_COMPARE_CONTAINERS( (Utility::fromString<std::vector<unsigned int> >( "{0, 10, 100, 1000, 10000}" )),
                           std::vector<unsigned int>({0, 10, 100, 1000, 10000}) );
  
  TEST_COMPARE_CONTAINERS( (Utility::fromString<std::vector<unsigned int> >( "{0, 3i, 10000}" )),
                           std::vector<unsigned int>({0, 2500, 5000, 7500, 10000}) );

  // Extract vector of long
  TEST_COMPARE_CONTAINERS( (Utility::fromString<std::vector<long> >( "{-11111, 0, 11111, 22222}" )),
                           std::vector<long>({-11111, 0, 11111, 22222}) );
  TEST_COMPARE_CONTAINERS( (Utility::fromString<std::vector<long> >( "{-11111, 2i, 22222}" )),
                           std::vector<long>({-11111, 0, 11111, 22222}) );

  // Extract vector of unsigned long
  TEST_COMPARE_CONTAINERS( (Utility::fromString<std::vector<unsigned long> >( "{0, 10, 100, 1000, 10000}" )),
                           std::vector<unsigned long>({0, 10, 100, 1000, 10000}) );
  TEST_COMPARE_CONTAINERS( (Utility::fromString<std::vector<unsigned long> >( "{0, 3i, 10000}" )),
                           std::vector<unsigned long>({0, 2500, 5000, 7500, 10000}) );

  // Extract vector of long long
  TEST_COMPARE_CONTAINERS( (Utility::fromString<std::vector<long long> >( "{-1000000000, 0, 1000000000}" )),
                           std::vector<long long>({-1000000000, 0, 1000000000}) );
  TEST_COMPARE_CONTAINERS( (Utility::fromString<std::vector<long long> >( "{-1000000000, 1i, 1000000000}" )),
                           std::vector<long long>({-1000000000, 0, 1000000000}) );

  // Extract vector of unsigned long long
  TEST_COMPARE_CONTAINERS( (Utility::fromString<std::vector<unsigned long long> >( "{0, 1000000000, 10000000000}" )),
                           std::vector<unsigned long long>({0, 1000000000, 10000000000}) );
  TEST_COMPARE_CONTAINERS( (Utility::fromString<std::vector<unsigned long long> >( "{0, 1i, 10000000000}" )),
                           std::vector<unsigned long long>({0, 5000000000, 10000000000}) );

  // Extract vector of float
  TEST_COMPARE_CONTAINERS( (Utility::fromString<std::vector<float> >( "{-1, 0.0, 1.000000000e+00}" )),
                           std::vector<float>({-1.0f, 0.0f, 1.0f}) );
  TEST_COMPARE_CONTAINERS( (Utility::fromString<std::vector<float> >( "{-1, 3i, 1.000000000e+00}" )),
                           std::vector<float>({-1.0f, -0.5f, 0.0f, 0.5f, 1.0f}) );
  TEST_COMPARE_FLOATING_CONTAINERS( (Utility::fromString<std::vector<float> >( "{1e-3, 2l, 1.0}" )),
                                    std::vector<float>({1e-3f, 1e-2f, 1e-1f, 1.0f}),
                                    1e-9 );
  TEST_COMPARE_CONTAINERS( (Utility::fromString<std::vector<float> >( "{1.0, 1l, 100, 3i, 200}" )),
                           std::vector<float>({1.0f, 10.0f, 100.0f, 125.0f, 150.0f, 175.0f, 200.0f}) );
  TEST_COMPARE_CONTAINERS( (Utility::fromString<std::vector<float> >( "{0.0, pi/2, 3Pi / 4, PI, 2*pi}" )),
                           std::vector<float>({0.0f, (float)Utility::PhysicalConstants::pi/2, 3*(float)Utility::PhysicalConstants::pi/4, (float)Utility::PhysicalConstants::pi, 2*(float)Utility::PhysicalConstants::pi}) );
  TEST_COMPARE_CONTAINERS( (Utility::fromString<std::vector<float> >( "{-pi, 3i, 0}" )),
                           std::vector<float>({-(float)Utility::PhysicalConstants::pi, -3*(float)Utility::PhysicalConstants::pi/4, -(float)Utility::PhysicalConstants::pi/2, -(float)Utility::PhysicalConstants::pi/4, 0.0}) );
  TEST_COMPARE_CONTAINERS( (Utility::fromString<std::vector<float> >( "{-inf, 0, Infinity}" )),
                           std::vector<float>({-std::numeric_limits<float>::infinity(), 0.0f, std::numeric_limits<float>::infinity()}) );
  
  
  // Extract vector of double
  TEST_COMPARE_CONTAINERS( (Utility::fromString<std::vector<double> >( "{-1, 0.0, 1.000000000000000000e+00}" )),
                           std::vector<double>({-1.0, 0.0, 1.0}) );
  TEST_COMPARE_CONTAINERS( (Utility::fromString<std::vector<double> >( "{-1, 3i, 1.000000000e+00}" )),
                           std::vector<double>({-1.0, -0.5, 0.0, 0.5, 1.0}) );
  TEST_COMPARE_FLOATING_CONTAINERS( (Utility::fromString<std::vector<double> >( "{1e-3, 2l, 1.0}" )),
                                    std::vector<double>({1e-3, 1e-2, 1e-1, 1.0}),
                                    1e-9 );
  TEST_COMPARE_FLOATING_CONTAINERS( (Utility::fromString<std::vector<double> >( "{1.0, 1l, 100, 3i, 200}" )),
                                    std::vector<double>({1.0, 10.0, 100.0, 125.0, 150.0, 175.0, 200.0}),
                                    1e-9 );
  TEST_COMPARE_CONTAINERS( (Utility::fromString<std::vector<double> >( "{0.0, pi/2, 3Pi / 4, PI, 2*pi}" )),
                           std::vector<double>({0.0, Utility::PhysicalConstants::pi/2, 3*Utility::PhysicalConstants::pi/4, Utility::PhysicalConstants::pi, 2*Utility::PhysicalConstants::pi}) );
  TEST_COMPARE_CONTAINERS( (Utility::fromString<std::vector<double> >( "{-pi, 3i, 0}" )),
                           std::vector<double>({-Utility::PhysicalConstants::pi, -3*Utility::PhysicalConstants::pi/4, -Utility::PhysicalConstants::pi/2, -Utility::PhysicalConstants::pi/4, 0.0}) );
  TEST_COMPARE_CONTAINERS( (Utility::fromString<std::vector<double> >( "{-Infinity, 0, inf}" )),
                           std::vector<double>({-std::numeric_limits<double>::infinity(), 0, std::numeric_limits<double>::infinity()}) );

  // Extract vector of char
  TEST_COMPARE_CONTAINERS( (Utility::fromString<std::vector<char> >( "{T, e, s, t,  , s, t, r, i, n, g}" )),
                           std::vector<char>({'T', 'e', 's', 't', ' ', 's', 't', 'r', 'i', 'n', 'g'}) );

  // Extract vector of string
  TEST_COMPARE_CONTAINERS( (Utility::fromString<std::vector<std::string> >( "{Test, string}" )),
                           std::vector<std::string>({"Test","string"}) );

  // Extract vector of pair
  TEST_COMPARE_CONTAINERS( (Utility::fromString<std::vector<std::pair<int, int> > >( "{{0, 1}, {-1, 2}}" )),
                           (std::vector<std::pair<int,int> >({std::make_pair(0, 1), std::make_pair(-1, 2)})) );

  // Extract vector of tuple
  TEST_COMPARE_CONTAINERS( (Utility::fromString<std::vector<std::tuple<unsigned, double, long> > >( "{{0, 1.0, -100000}, {1, -1.00, 100001}}" )),
                           (std::vector<std::tuple<unsigned,double,long> >({std::make_tuple(0u, 1.0, -100000l), std::make_tuple(1u, -1.0, 100001l)})) );

  // Extract vector of vectors
  std::vector<std::vector<double> > test_vector =
    Utility::fromString<std::vector<std::vector<double> > >( "{{-1, 3i, 1}, {1e-3, 2l, 1.0}, {-Inf, Inf}, {-pi/2, 1i, pi/2}}" );

  TEST_EQUALITY_CONST( test_vector.size(), 4 );
  TEST_COMPARE_CONTAINERS( test_vector[0],
                           (std::vector<double>({-1.0, -0.5, 0.0, 0.5, 1.0})) );
  TEST_COMPARE_FLOATING_CONTAINERS( test_vector[1],
                                    (std::vector<double>({1e-3, 1e-2, 1e-1, 1.0})),
                                    1e-9 );
  TEST_COMPARE_CONTAINERS( test_vector[2],
                           (std::vector<double>({-std::numeric_limits<double>::infinity(), std::numeric_limits<double>::infinity()})) );
  TEST_COMPARE_CONTAINERS( test_vector[3],
                           (std::vector<double>({-Utility::PhysicalConstants::pi/2, 0.0, Utility::PhysicalConstants::pi/2})) );
}

//---------------------------------------------------------------------------//
// Check that a vector can be extracted from a stream
TEUCHOS_UNIT_TEST( FromStringTraits, vector_fromStream )
{
  std::cout << "vector stream" << std::endl;
  // Extract vector of short
  std::istringstream iss( "{-1, 2}" );

  {
    std::vector<short> test_vector;

    Utility::fromStream( iss, test_vector );

    TEST_COMPARE_CONTAINERS( test_vector, std::vector<short>({-1, 2}) );

    iss.str( "{-1, 2i, 2}" );
    iss.clear();

    Utility::fromStream( iss, test_vector );

    TEST_COMPARE_CONTAINERS( test_vector, std::vector<short>({-1, 0, 1, 2}) );
  }

  // Extract vector of unsigned short
  iss.str( "{0, 10, 100}" );
  iss.clear();

  {
    std::vector<unsigned short> test_vector;

    Utility::fromStream( iss, test_vector );

    TEST_COMPARE_CONTAINERS( test_vector, std::vector<unsigned short>({0, 10, 100}) );

    iss.str( "{0, 3i, 100}" );
    iss.clear();

    Utility::fromStream( iss, test_vector );

    TEST_COMPARE_CONTAINERS( test_vector, std::vector<unsigned short>({0, 25, 50, 75, 100}) );
  }

  // Extract vector of int
  iss.str( "{-11111, 0, 11111, 22222}" );
  iss.clear();

  {
    std::vector<int> test_vector;

    Utility::fromStream( iss, test_vector );

    TEST_COMPARE_CONTAINERS( test_vector, std::vector<int>({-11111, 0, 11111, 22222}) );

    iss.str( "{-11111, 2i, 22222}" );
    iss.clear();

    Utility::fromStream( iss, test_vector );

    TEST_COMPARE_CONTAINERS( test_vector, std::vector<int>({-11111, 0, 11111, 22222}) );
  }

  // Extract vector of unsigned int
  iss.str( "{0, 10, 100, 1000, 10000}" );
  iss.clear();

  {
    std::vector<unsigned> test_vector;

    Utility::fromStream( iss, test_vector );

    TEST_COMPARE_CONTAINERS( test_vector, std::vector<unsigned>({0, 10, 100, 1000, 10000}) );

    iss.str( "{0, 3i, 10000}" );
    iss.clear();

    Utility::fromStream( iss, test_vector );

    TEST_COMPARE_CONTAINERS( test_vector, std::vector<unsigned>({0, 2500, 5000, 7500, 10000}) );
  }

  // Extract vector of long
  iss.str( "{-11111, 0, 11111, 22222}" );
  iss.clear();

  {
    std::vector<long> test_vector;

    Utility::fromStream( iss, test_vector );

    TEST_COMPARE_CONTAINERS( test_vector, std::vector<long>({-11111, 0, 11111, 22222}) );

    iss.str( "{-11111, 2i, 22222}" );
    iss.clear();

    Utility::fromStream( iss, test_vector );

    TEST_COMPARE_CONTAINERS( test_vector, std::vector<long>({-11111, 0, 11111, 22222}) );
  }

  // Extract vector of unsigned long
  iss.str( "{0, 10, 100, 1000, 10000}" );
  iss.clear();

  {
    std::vector<unsigned long> test_vector;

    Utility::fromStream( iss, test_vector );

    TEST_COMPARE_CONTAINERS( test_vector, std::vector<unsigned long>({0, 10, 100, 1000, 10000}) );

    iss.str( "{0, 3i, 10000}" );
    iss.clear();

    Utility::fromStream( iss, test_vector );

    TEST_COMPARE_CONTAINERS( test_vector, std::vector<unsigned long>({0, 2500, 5000, 7500, 10000}) );
  }

  // Extract vector of long long
  iss.str( "{-1000000000, 0, 1000000000}" );
  iss.clear();

  {
    std::vector<long long> test_vector;

    Utility::fromStream( iss, test_vector );

    TEST_COMPARE_CONTAINERS( test_vector, std::vector<long long>({-1000000000, 0, 1000000000}) );

    iss.str( "{-1000000000, 1i, 1000000000}" );
    iss.clear();

    Utility::fromStream( iss, test_vector );

    TEST_COMPARE_CONTAINERS( test_vector, std::vector<long long>({-1000000000, 0, 1000000000}) );
  }

  // Extract vector of unsigned long long
  iss.str( "{0, 1000000000, 10000000000}" );
  iss.clear();

  {
    std::vector<unsigned long long> test_vector;

    Utility::fromStream( iss, test_vector );

    TEST_COMPARE_CONTAINERS( test_vector, std::vector<unsigned long long>({0, 1000000000, 10000000000}) );

    iss.str( "{0, 1i, 10000000000}" );
    iss.clear();

    Utility::fromStream( iss, test_vector );

    TEST_COMPARE_CONTAINERS( test_vector, std::vector<unsigned long long>({0, 5000000000, 10000000000}) );
  }

  // Extract vector of float
  iss.str( "{-1, 0.0, 1.000000000e+00}" );
  iss.clear();

  {
    std::vector<float> test_vector;

    Utility::fromStream( iss, test_vector );

    TEST_COMPARE_CONTAINERS( test_vector, std::vector<float>({-1.0f, 0.0f, 1.0f}) );

    iss.str( "{-1, 3i, 1.000000000e+00}" );
    iss.clear();

    Utility::fromStream( iss, test_vector );

    TEST_COMPARE_CONTAINERS( test_vector, std::vector<float>({-1.0f, -0.5f, 0.0f, 0.5f, 1.0f}) );

    iss.str( "{1e-3, 2l, 1.0}" );
    iss.clear();

    Utility::fromStream( iss, test_vector );

    TEST_COMPARE_FLOATING_CONTAINERS( test_vector,
                                      std::vector<float>({1e-3f, 1e-2f, 1e-1f, 1.0f}),
                                      1e-9 );

    iss.str( "{1.0, 1l, 100, 3i, 200}" );
    iss.clear();

    Utility::fromStream( iss, test_vector );
    
    TEST_COMPARE_CONTAINERS( test_vector,
                             std::vector<float>({1.0f, 10.0f, 100.0f, 125.0f, 150.0f, 175.0f, 200.0f}) );

    iss.str( "{0.0, pi/2, 3Pi / 4, PI, 2*pi}" );
    iss.clear();

    Utility::fromStream( iss, test_vector );
    
    TEST_COMPARE_CONTAINERS( test_vector,
                             std::vector<float>({0.0f, (float)Utility::PhysicalConstants::pi/2, 3*(float)Utility::PhysicalConstants::pi/4, (float)Utility::PhysicalConstants::pi, 2*(float)Utility::PhysicalConstants::pi}) );

    iss.str( "{-pi, 3i, 0}" );
    iss.clear();

    Utility::fromStream( iss, test_vector );
    
    TEST_COMPARE_CONTAINERS( test_vector,
                             std::vector<float>({-(float)Utility::PhysicalConstants::pi, -3*(float)Utility::PhysicalConstants::pi/4, -(float)Utility::PhysicalConstants::pi/2, -(float)Utility::PhysicalConstants::pi/4, 0.0}) );

    iss.str( "{-inf, 0, Infinity}" );
    iss.clear();

    Utility::fromStream( iss, test_vector );
    
    TEST_COMPARE_CONTAINERS( test_vector,
                             std::vector<float>({-std::numeric_limits<float>::infinity(), 0.0f, std::numeric_limits<float>::infinity()}) );
  }

  // Extract vector of double
  iss.str( "{-1, 0.0, 1.000000000000000000e+00}" );
  iss.clear();

  {
    std::vector<double> test_vector;

    Utility::fromStream( iss, test_vector );

    TEST_COMPARE_CONTAINERS( test_vector, std::vector<double>({-1.0, 0.0, 1.0}) );

    iss.str( "{-1, 3i, 1.000000000e+00}" );
    iss.clear();

    Utility::fromStream( iss, test_vector );

    TEST_COMPARE_CONTAINERS( test_vector, std::vector<double>({-1.0, -0.5, 0.0, 0.5, 1.0}) );

    iss.str( "{1e-3, 2l, 1.0}" );
    iss.clear();

    Utility::fromStream( iss, test_vector );

    TEST_COMPARE_FLOATING_CONTAINERS( test_vector,
                                      std::vector<double>({1e-3, 1e-2, 1e-1, 1.0}),
                                      1e-9 );

    iss.str( "{1.0, 1l, 100, 3i, 200}" );
    iss.clear();

    Utility::fromStream( iss, test_vector );
    
    TEST_COMPARE_FLOATING_CONTAINERS( test_vector,
                                      std::vector<double>({1.0, 10.0, 100.0, 125.0, 150.0, 175.0, 200.0}),
                                      1e-15 );

    iss.str( "{0.0, pi/2, 3Pi / 4, PI, 2*pi}" );
    iss.clear();

    Utility::fromStream( iss, test_vector );
    
    TEST_COMPARE_CONTAINERS( test_vector,
                             std::vector<double>({0.0, Utility::PhysicalConstants::pi/2, 3*Utility::PhysicalConstants::pi/4, Utility::PhysicalConstants::pi, 2*Utility::PhysicalConstants::pi}) );

    iss.str( "{-pi, 3i, 0}" );
    iss.clear();

    Utility::fromStream( iss, test_vector );
    
    TEST_COMPARE_CONTAINERS( test_vector,
                             std::vector<double>({-Utility::PhysicalConstants::pi, -3*Utility::PhysicalConstants::pi/4, -Utility::PhysicalConstants::pi/2, -Utility::PhysicalConstants::pi/4, 0.0}) );

    iss.str( "{-inf, 0, Infinity}" );
    iss.clear();

    Utility::fromStream( iss, test_vector );
    
    TEST_COMPARE_CONTAINERS( test_vector,
                             std::vector<double>({-std::numeric_limits<float>::infinity(), 0.0, std::numeric_limits<float>::infinity()}) );
  }

  // Extract vector of char
  iss.str( "{T, e, s, t,  , s, t, r, i, n, g}" );
  iss.clear();

  {
    std::vector<char> test_vector;

    Utility::fromStream( iss, test_vector );

    TEST_COMPARE_CONTAINERS( test_vector, std::vector<char>({'T', 'e', 's', 't', ' ', 's', 't', 'r', 'i', 'n', 'g'}) );
  }

  // Extract vector of string
  iss.str( "{Test, string}" );
  iss.clear();

  {
    std::vector<std::string> test_vector;

    Utility::fromStream( iss, test_vector );

    TEST_COMPARE_CONTAINERS( test_vector, std::vector<std::string>({"Test","string"}) );
  }

  // Extract vector of pair
  iss.str( "{{0, 1}, {-1, 2}}" );
  iss.clear();

  {
    std::vector<std::pair<int,int> > test_vector;

    Utility::fromStream( iss, test_vector );

    TEST_COMPARE_CONTAINERS( test_vector, (std::vector<std::pair<int,int> >({std::make_pair(0, 1), std::make_pair(-1, 2)})) );
  }

  // Extract vector of tuple
  iss.str( "{{0, 1.0, -100000}, {1, -1.00, 100001}}" );
  iss.clear();

  {
    std::vector<std::tuple<unsigned,double,long> > test_vector;

    Utility::fromStream( iss, test_vector );

    TEST_COMPARE_CONTAINERS( test_vector, (std::vector<std::tuple<unsigned,double,long> >({std::make_tuple(0u, 1.0, -100000l), std::make_tuple(1u, -1.0, 100001l)})) );
  }

  // Extract multiple vectors of pairs
  iss.str( "{{0, 1}, {-1, 2}}, {{1, 0}, {2, -1}}" );
  iss.clear();

  {
    std::vector<std::pair<long,long> > test_vector;

    Utility::fromStream( iss, test_vector, "," );

    TEST_COMPARE_CONTAINERS( test_vector, (std::vector<std::pair<long,long> >({std::make_pair(0l, 1l), std::make_pair(-1l, 2l)})) );

    Utility::moveInputStreamToNextElement( iss, ',', '}' );

    Utility::fromStream( iss, test_vector );

    TEST_COMPARE_CONTAINERS( test_vector, (std::vector<std::pair<long,long> >({std::make_pair(1l, 0l), std::make_pair(2l, -1l)})) );
  }

  // Extract vector of vectors
  iss.str( "{{-1, 3i, 1}, {1e-3, 2l, 1.0}, {-Inf, Inf}, {-pi/2, 1i, pi/2}}" );
  iss.clear();

  {
    std::vector<std::vector<double> > test_vector;
    
    Utility::fromStream( iss, test_vector );
    
    TEST_EQUALITY_CONST( test_vector.size(), 4 );
    TEST_COMPARE_CONTAINERS( test_vector[0],
                             (std::vector<double>({-1.0, -0.5, 0.0, 0.5, 1.0})) );
    TEST_COMPARE_FLOATING_CONTAINERS( test_vector[1],
                                      (std::vector<double>({1e-3, 1e-2, 1e-1, 1.0})),
                                      1e-9 );
    TEST_COMPARE_CONTAINERS( test_vector[2],
                             (std::vector<double>({-std::numeric_limits<double>::infinity(), std::numeric_limits<double>::infinity()})) );
    TEST_COMPARE_CONTAINERS( test_vector[3],
                             (std::vector<double>({-Utility::PhysicalConstants::pi/2, 0.0, Utility::PhysicalConstants::pi/2})) );
  }
}

//---------------------------------------------------------------------------//
// Check that a vector can be placed in a stream
TEUCHOS_UNIT_TEST( StreamHelpers, vector_ostream )
{
  std::ostringstream oss;

  oss << std::vector<short>( {-1, 2} );
  
  TEST_EQUALITY_CONST( oss.str(), "{-1, 2}" );

  oss.str( "" );
  oss.clear();

  oss << std::vector<unsigned short>( {0, 10, 100} );
  
  TEST_EQUALITY_CONST( oss.str(), "{0, 10, 100}" );

  oss.str( "" );
  oss.clear();

  oss << std::vector<int>( {-11111, 0, 11111, 22222} );
  
  TEST_EQUALITY_CONST( oss.str(), "{-11111, 0, 11111, 22222}" );

  oss.str( "" );
  oss.clear();

  oss << std::vector<unsigned int>( {0, 10, 100, 1000, 10000} );
  
  TEST_EQUALITY_CONST( oss.str(), "{0, 10, 100, 1000, 10000}" );

  oss.str( "" );
  oss.clear();

  oss << std::vector<long>( {-11111, 0, 11111, 22222} );
  
  TEST_EQUALITY_CONST( oss.str(), "{-11111, 0, 11111, 22222}" );

  oss.str( "" );
  oss.clear();

  oss << std::vector<unsigned long>( {0, 10, 100, 1000, 10000} );
  
  TEST_EQUALITY_CONST( oss.str(), "{0, 10, 100, 1000, 10000}" );

  oss.str( "" );
  oss.clear();

  oss << std::vector<long long>( {-10000000000, 0, 10000000000} );
  
  TEST_EQUALITY_CONST( oss.str(), "{-10000000000, 0, 10000000000}" );

  oss.str( "" );
  oss.clear();

  oss << std::vector<unsigned long long>( {0, 1000000000, 1000000000000} );
  
  TEST_EQUALITY_CONST( oss.str(), "{0, 1000000000, 1000000000000}" );

  oss.str( "" );
  oss.clear();

  oss << std::vector<float>( {-1.0f, 0.0f, 1.0f} );
  
  TEST_EQUALITY_CONST( oss.str(),
                       "{-1.000000000e+00, 0.000000000e+00, 1.000000000e+00}" );
  
  oss.str( "" );
  oss.clear();

  oss << std::vector<double>( {-1.0, 0.0, 1.0} );
  
  TEST_EQUALITY_CONST( oss.str(),
                       "{-1.000000000000000000e+00, 0.000000000000000000e+00, 1.000000000000000000e+00}" );

  oss.str( "" );
  oss.clear();

  oss << std::vector<char>( {'T', 'e', 's', 't', ' ', 's', 't', 'r', 'i', 'n', 'g' } );
  
  TEST_EQUALITY_CONST( oss.str(), "{T, e, s, t,  , s, t, r, i, n, g}" );

  oss.str( "" );
  oss.clear();

  oss << std::vector<std::string>( {"Test", "string"} );
  
  TEST_EQUALITY_CONST( oss.str(), "{Test, string}" );

  oss.str( "" );
  oss.clear();

  oss << std::vector<std::pair<int, int>>( {std::pair<int, int>({0, 1}), std::pair<int,int>({-1, 2})} );
  
  TEST_EQUALITY_CONST( oss.str(), "{{0, 1}, {-1, 2}}" );

  oss.str( "" );
  oss.clear();

  oss << std::vector<std::tuple<unsigned, double, long>>( {std::make_tuple( 0u, 1.0, -100000 ), std::make_tuple( 1u, -1.0, 100001 )} );
  
  TEST_EQUALITY_CONST( oss.str(),
                       "{{0, 1.000000000000000000e+00, -100000}, {1, -1.000000000000000000e+00, 100001}}" );
}

//---------------------------------------------------------------------------//
// Check that a vector can be extracted from a stream
TEUCHOS_UNIT_TEST( StreamHelpers, vector_istream )
{
  std::istringstream iss( "{-1, 2}" );

  {
    std::vector<short> test_vector;

    iss >> test_vector;

    TEST_COMPARE_CONTAINERS( test_vector, std::vector<short>({-1, 2}) );
  }

  iss.str( "{0, 10, 100}" );
  iss.clear();

  {
    std::vector<unsigned short> test_vector;

    iss >> test_vector;

    TEST_COMPARE_CONTAINERS( test_vector, std::vector<unsigned short>({0, 10, 100}) );
  }

  iss.str( "{-11111, 0, 11111, 22222}" );
  iss.clear();

  {
    std::vector<int> test_vector;

    iss >> test_vector;

    TEST_COMPARE_CONTAINERS( test_vector, std::vector<int>({-11111, 0, 11111, 22222}) );
  }
                      
  iss.str( "{0, 10, 100, 1000, 10000}" );
  iss.clear();

  {
    std::vector<unsigned> test_vector;

    iss >> test_vector;

    TEST_COMPARE_CONTAINERS( test_vector, std::vector<unsigned>({0, 10, 100, 1000, 10000}) );
  }

  iss.str( "{-11111, 0, 11111, 22222}" );
  iss.clear();

  {
    std::vector<long> test_vector;

    iss >> test_vector;

    TEST_COMPARE_CONTAINERS( test_vector, std::vector<long>({-11111, 0, 11111, 22222}) );
  }

  iss.str( "{0, 10, 100, 1000, 10000}" );
  iss.clear();

  {
    std::vector<unsigned long> test_vector;

    iss >> test_vector;

    TEST_COMPARE_CONTAINERS( test_vector, std::vector<unsigned long>({0, 10, 100, 1000, 10000}) );
  }

  iss.str( "{-1000000000, 0, 1000000000}" );
  iss.clear();

  {
    std::vector<long long> test_vector;

    iss >> test_vector;

    TEST_COMPARE_CONTAINERS( test_vector, std::vector<long long>({-1000000000, 0, 1000000000}) );
  }

  iss.str( "{0, 1000000000, 10000000000}" );
  iss.clear();

  {
    std::vector<unsigned long long> test_vector;

    iss >> test_vector;

    TEST_COMPARE_CONTAINERS( test_vector, std::vector<unsigned long long>({0, 1000000000, 10000000000}) );
  }

  iss.str( "{-1, 0.0, 1.000000000e+00}" );
  iss.clear();

  {
    std::vector<float> test_vector;

    iss >> test_vector;

    TEST_COMPARE_CONTAINERS( test_vector, std::vector<float>({-1.0f, 0.0f, 1.0f}) );
  }

  iss.str( "{-1, 0.0, 1.000000000000000000e+00}" );
  iss.clear();

  {
    std::vector<double> test_vector;

    iss >> test_vector;

    TEST_COMPARE_CONTAINERS( test_vector, std::vector<double>({-1.0, 0.0, 1.0}) );
  }

  iss.str( "{T, e, s, t,  , s, t, r, i, n, g}" );
  iss.clear();

  {
    std::vector<char> test_vector;

    iss >> test_vector;

    TEST_COMPARE_CONTAINERS( test_vector, std::vector<char>({'T', 'e', 's', 't', ' ', 's', 't', 'r', 'i', 'n', 'g'}) );
  }

  iss.str( "{Test, string}" );
  iss.clear();

  {
    std::vector<std::string> test_vector;

    iss >> test_vector;

    TEST_COMPARE_CONTAINERS( test_vector, std::vector<std::string>({"Test","string"}) );
  }

  iss.str( "{{0, 1}, {-1, 2}}" );
  iss.clear();

  {
    std::vector<std::pair<int,int> > test_vector;

    iss >> test_vector;

    TEST_COMPARE_CONTAINERS( test_vector, (std::vector<std::pair<int,int> >({std::make_pair(0, 1), std::make_pair(-1, 2)})) );
  }

  iss.str( "{{0, 1.0, -100000}, {1, -1.00, 100001}}" );
  iss.clear();

  {
    std::vector<std::tuple<unsigned,double,long> > test_vector;

    iss >> test_vector;

    TEST_COMPARE_CONTAINERS( test_vector, (std::vector<std::tuple<unsigned,double,long> >({std::make_tuple(0u, 1.0, -100000l), std::make_tuple(1u, -1.0, 100001l)})) );
  }

  iss.str( "{{0, 1}, {-1, 2}}, {{1, 0}, {2, -1}}" );
  iss.clear();

  {
    std::vector<std::pair<long,long> > test_vector;

    Utility::fromStream( iss, test_vector, "," );

    TEST_COMPARE_CONTAINERS( test_vector, (std::vector<std::pair<long,long> >({std::make_pair(0l, 1l), std::make_pair(-1l, 2l)})) );

    Utility::moveInputStreamToNextElement( iss, ',', '}' );

    iss >> test_vector;

    TEST_COMPARE_CONTAINERS( test_vector, (std::vector<std::pair<long,long> >({std::make_pair(1l, 0l), std::make_pair(2l, -1l)})) );
  }
}

//---------------------------------------------------------------------------//
// end tstVector.cpp
//---------------------------------------------------------------------------//
