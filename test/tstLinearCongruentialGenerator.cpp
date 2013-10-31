//---------------------------------------------------------------------------//
//!
//! \file   tstLinearCongruentialGenerator.cpp
//! \author Alex Robinson
//! \brief  Linear Congruential Generator class unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_ScalarTraits.hpp>

// FACEMC Includes
#include "FACEMC_UnitTestHarnessExtensions.hpp"
#include "LinearCongruentialGenerator.hpp"

//---------------------------------------------------------------------------//
// Instantiation Macros.
//---------------------------------------------------------------------------//
#define UNIT_TEST_INSTANTIATION( type, name ) \
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, float ) \
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, double ) 

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that a random number in the interval [0,1) can be obtained
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( LinearCongruentialGenerator, 
				   rnd, 
				   ScalarType )
{
  FACEMC::LinearCongruentialGenerator<ScalarType> lcg;
  
  ScalarType random_number = lcg.rnd();

  TEST_COMPARE( random_number, >=, Teuchos::ScalarTraits<ScalarType>::zero() );
  TEST_COMPARE( random_number, <, Teuchos::ScalarTraits<ScalarType>::one() );
}

UNIT_TEST_INSTANTIATION( LinearCongruentialGenerator, rnd );

//---------------------------------------------------------------------------//
// Check that the basic statistics of the generator are correct for a single
// history
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( LinearCongruentialGenerator,
				   statistics_single_history,
				   ScalarType )
{
  FACEMC::LinearCongruentialGenerator<ScalarType> lcg;
  
  double test_average = 0;
  double test_variance = 0;
  ScalarType random_number;
  int samples = 100000000;  

  for( int i = 0; i < samples; ++i )
  {
    random_number = lcg.rnd();
    test_average += random_number;
    test_variance += random_number*random_number;    
  }
  
  test_average /= samples;
  test_variance /= samples;
  test_variance -= test_average*test_average;
  
  TEST_FLOATING_EQUALITY( static_cast<ScalarType>( test_average ), 
			  Teuchos::ScalarTraits<ScalarType>::one()/2, 
			  static_cast<ScalarType>( 1e-4 ) );
  TEST_FLOATING_EQUALITY( static_cast<ScalarType>( test_variance ),
			  Teuchos::ScalarTraits<ScalarType>::one()/12,
			  static_cast<ScalarType>( 1e-4 ) );
}

UNIT_TEST_INSTANTIATION( LinearCongruentialGenerator, 
			 statistics_single_history );

//---------------------------------------------------------------------------//
// Check that the basic statistics of the generator are correct for multiple
// histories
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( LinearCongruentialGenerator,
				   statistics_multiple_histories,
				   ScalarType )
{
  FACEMC::LinearCongruentialGenerator<ScalarType> lcg;
  
  double test_average = 0;
  double test_variance = 0;
  ScalarType random_number;
  int samples = 100000000;
  int histories = 1000;
  

  for( int i = 0; i < histories; ++i )
  {
    for( int j = 0; j < samples/histories; ++j )
    {
      random_number = lcg.rnd();
      test_average += random_number;
      test_variance += random_number*random_number;
    }
    
    lcg.changeHistory( i+1 );
  }
  
  test_average /= samples;
  test_variance /= samples;
  test_variance -= test_average*test_average;
  
  TEST_FLOATING_EQUALITY( static_cast<ScalarType>( test_average ), 
			  Teuchos::ScalarTraits<ScalarType>::one()/2, 
			  static_cast<ScalarType>( 5e-3 ) );
  TEST_FLOATING_EQUALITY( static_cast<ScalarType>( test_variance ),
			  Teuchos::ScalarTraits<ScalarType>::one()/12,
			  static_cast<ScalarType>( 5e-3 ) );
}

UNIT_TEST_INSTANTIATION( LinearCongruentialGenerator, 
			 statistics_multiple_histories );


//---------------------------------------------------------------------------//
// end tstLinearCongruentialGenerator.cpp
//---------------------------------------------------------------------------//

