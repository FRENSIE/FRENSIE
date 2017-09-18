//---------------------------------------------------------------------------//
//!
//! \file   tstElasticElectronDistributionType.cpp
//! \author Luke Kersting
//! \brief  Elastic electron distribution type helper unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <sstream>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>

// FRENSIE Includes
#include "MonteCarlo_ElasticElectronDistributionType.hpp"
#include "Utility_UnitTestHarnessExtensions.hpp"

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the elastic electron distribution types can be converted to int
TEUCHOS_UNIT_TEST( ElasticElectronDistributionType, convert_to_int )
{
  TEST_EQUALITY_CONST( (unsigned)MonteCarlo::COUPLED_DISTRIBUTION, 1 );
  TEST_EQUALITY_CONST( (unsigned)MonteCarlo::DECOUPLED_DISTRIBUTION, 2 );
  TEST_EQUALITY_CONST( (unsigned)MonteCarlo::HYBRID_DISTRIBUTION, 3 );
  TEST_EQUALITY_CONST( (unsigned)MonteCarlo::CUTOFF_DISTRIBUTION, 4 );
  TEST_EQUALITY_CONST( (unsigned)MonteCarlo::SCREENED_RUTHERFORD_DISTRIBUTION, 5 );
}

//---------------------------------------------------------------------------//
// Check that an elastic electron distribution type can be converted to a string
TEUCHOS_UNIT_TEST( ElasticElectronDistributionType,
                   convertElasticElectronDistributionTypeToString )
{
  std::string type_string =
    MonteCarlo::convertElasticElectronDistributionTypeToString( MonteCarlo::COUPLED_DISTRIBUTION );
  
  TEST_EQUALITY_CONST( type_string, "Coupled Distribution" );

  type_string =
    MonteCarlo::convertElasticElectronDistributionTypeToString( MonteCarlo::DECOUPLED_DISTRIBUTION );

  TEST_EQUALITY_CONST( type_string, "Decoupled Distribution" );

  type_string =
    MonteCarlo::convertElasticElectronDistributionTypeToString( MonteCarlo::HYBRID_DISTRIBUTION );

  TEST_EQUALITY_CONST( type_string, "Hybrid Distribution" );

  type_string =
    MonteCarlo::convertElasticElectronDistributionTypeToString( MonteCarlo::CUTOFF_DISTRIBUTION );

  TEST_EQUALITY_CONST( type_string, "Cutoff Distribution" );

  type_string =
    MonteCarlo::convertElasticElectronDistributionTypeToString( MonteCarlo::SCREENED_RUTHERFORD_DISTRIBUTION );

  TEST_EQUALITY_CONST( type_string, "Screened Rutherford Distribution" );
}

//---------------------------------------------------------------------------//
// Check that a coupled elastic electron sampling method can be converted to a string
TEUCHOS_UNIT_TEST( CoupledElasticSamplingMethod,
                   convertCoupledElasticSamplingMethodToString )
{
  std::string type_string =
    MonteCarlo::convertCoupledElasticSamplingMethodToString( MonteCarlo::ONE_D_UNION );
  
  TEST_EQUALITY_CONST( type_string, "One D Union" );

  type_string =
    MonteCarlo::convertCoupledElasticSamplingMethodToString( MonteCarlo::TWO_D_UNION );

  TEST_EQUALITY_CONST( type_string, "Two D Union" );

  type_string =
    MonteCarlo::convertCoupledElasticSamplingMethodToString( MonteCarlo::SIMPLIFIED_UNION );

  TEST_EQUALITY_CONST( type_string, "Simplified Union" );
}

//---------------------------------------------------------------------------//
// Check that an elastic electron distribution type can be sent to a stream
TEUCHOS_UNIT_TEST( ElasticElectronDistributionType, stream_operator )
{
  std::stringstream ss;

  ss << MonteCarlo::COUPLED_DISTRIBUTION;

  TEST_EQUALITY_CONST( ss.str(), "Coupled Distribution" );

  ss.str( "" );
  ss << MonteCarlo::DECOUPLED_DISTRIBUTION;

  TEST_EQUALITY_CONST( ss.str(), "Decoupled Distribution" );

  ss.str( "" );
  ss << MonteCarlo::HYBRID_DISTRIBUTION;

  TEST_EQUALITY_CONST( ss.str(), "Hybrid Distribution" );

  ss.str( "" );
  ss << MonteCarlo::CUTOFF_DISTRIBUTION;

  TEST_EQUALITY_CONST( ss.str(), "Cutoff Distribution" );

  ss.str( "" );
  ss << MonteCarlo::SCREENED_RUTHERFORD_DISTRIBUTION;

  TEST_EQUALITY_CONST( ss.str(), "Screened Rutherford Distribution" );
}

//---------------------------------------------------------------------------//
// Check that an elastic electron distribution type can be sent to a stream
TEUCHOS_UNIT_TEST( CoupledElasticSamplingMethod, stream_operator )
{
  std::stringstream ss;

  ss << MonteCarlo::ONE_D_UNION;

  TEST_EQUALITY_CONST( ss.str(), "One D Union" );

  ss.str( "" );
  ss << MonteCarlo::TWO_D_UNION;

  TEST_EQUALITY_CONST( ss.str(), "Two D Union" );

  ss.str( "" );
  ss << MonteCarlo::SIMPLIFIED_UNION;

  TEST_EQUALITY_CONST( ss.str(), "Simplified Union" );
}

//---------------------------------------------------------------------------//
// end tstElasticElectronDistributionType.cpp
//---------------------------------------------------------------------------//
