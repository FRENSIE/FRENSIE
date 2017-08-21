//---------------------------------------------------------------------------//
//!
//! \file   tstBremsstrahlungAngularDistributionType.cpp
//! \author Luke Kersting
//! \brief  Bremsstrahlung angular distribution type helper unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <sstream>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>

// FRENSIE Includes
#include "MonteCarlo_BremsstrahlungAngularDistributionType.hpp"
#include "Utility_UnitTestHarnessExtensions.hpp"

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the bremsstrahlung angular distribution types can be converted to int
TEUCHOS_UNIT_TEST( BremsstrahlungAngularDistributionType, convert_to_int )
{
  TEST_EQUALITY_CONST( (unsigned)MonteCarlo::DIPOLE_DISTRIBUTION, 1 );
  TEST_EQUALITY_CONST( (unsigned)MonteCarlo::TABULAR_DISTRIBUTION, 2 );
  TEST_EQUALITY_CONST( (unsigned)MonteCarlo::TWOBS_DISTRIBUTION, 3 );
}

//---------------------------------------------------------------------------//
// Check that a bremsstrahlung angular distribution type can be converted to a string
TEUCHOS_UNIT_TEST( BremsstrahlungAngularDistributionType,
                   convertBremsstrahlungAngularDistributionEnumToString )
{
  std::string type_string =
    MonteCarlo::convertBremsstrahlungAngularDistributionEnumToString( MonteCarlo::DIPOLE_DISTRIBUTION );
  
  TEST_EQUALITY_CONST( type_string, "Dipole Distribution" );

  type_string =
    MonteCarlo::convertBremsstrahlungAngularDistributionEnumToString( MonteCarlo::TABULAR_DISTRIBUTION );

  TEST_EQUALITY_CONST( type_string, "Tabular Distribution" );

  type_string =
    MonteCarlo::convertBremsstrahlungAngularDistributionEnumToString( MonteCarlo::TWOBS_DISTRIBUTION );

  TEST_EQUALITY_CONST( type_string, "2BS Distribution" );
}


//---------------------------------------------------------------------------//
// Check that a bremsstrahlung angular distribution type can be sent to a stream
TEUCHOS_UNIT_TEST( BremsstrahlungAngularDistributionType, stream_operator )
{
  std::stringstream ss;

  ss << MonteCarlo::DIPOLE_DISTRIBUTION;

  TEST_EQUALITY_CONST( ss.str(), "Dipole Distribution" );

  ss.str( "" );
  ss << MonteCarlo::TABULAR_DISTRIBUTION;

  TEST_EQUALITY_CONST( ss.str(), "Tabular Distribution" );

  ss.str( "" );
  ss << MonteCarlo::TWOBS_DISTRIBUTION;

  TEST_EQUALITY_CONST( ss.str(), "2BS Distribution" );
}

//---------------------------------------------------------------------------//
// end tstBremsstrahlungAngularDistributionType.cpp
//---------------------------------------------------------------------------//
