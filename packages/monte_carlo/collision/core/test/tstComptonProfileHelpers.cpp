//---------------------------------------------------------------------------//
//!
//! \file   tstComptonProfileHelpers.cpp
//! \author Alex Robinson
//! \brief  Compton profile helper function unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>

// FRENSIE Includes
#include "MonteCarlo_ComptonProfileHelpers.hpp"
#include "MonteCarlo_UnitTestHarnessExtensions.hpp"
#include "Utility_PhysicalConstants.hpp"

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that a full profile can be constructed from a half profile
TEUCHOS_UNIT_TEST( ComptonProfileHelpers, 
		   createFullProfileFromHalfProfile )
{
  std::vector<double> half_momentum_grid, half_profile;

  half_momentum_grid.push_back( 0.0 );
  half_momentum_grid.push_back( 10.0 );
  half_momentum_grid.push_back( 100.0 );

  half_profile.push_back( 1.69058145887700007 );
  half_profile.push_back( 1.63283486016400008e-06 );
  half_profile.push_back( 5.177281263934e-11 );
  
  Teuchos::Array<double> full_momentum_grid, full_profile;

  // Check that the grid can be preserved
  MonteCarlo::createFullProfileFromHalfProfile( half_momentum_grid.begin(),
						half_momentum_grid.end(),
						half_profile.begin(),
						half_profile.end(),
						full_momentum_grid,
						full_profile,
						false,
						false );

  TEST_EQUALITY_CONST( full_momentum_grid.size(), 5 );
  TEST_EQUALITY_CONST( full_momentum_grid.front(), -100.0 );
  TEST_EQUALITY_CONST( full_momentum_grid.back(), 100.0 );
  TEST_EQUALITY_CONST( full_momentum_grid[1], -10.0 );
  TEST_EQUALITY_CONST( full_momentum_grid[3], 10.0 );
  TEST_EQUALITY_CONST( full_momentum_grid[2], 0.0 );

  TEST_EQUALITY_CONST( full_profile.size(), 5 );
  
  TEST_FLOATING_EQUALITY( full_profile.front(),
			  5.177281263934e-11,
			  1e-12 );
  TEST_FLOATING_EQUALITY( full_profile.back(),
			  5.177281263934e-11,
			  1e-12 );
  TEST_FLOATING_EQUALITY( full_profile[1],
			  1.63283486016400008e-06,
			  1e-12 );
  TEST_FLOATING_EQUALITY( full_profile[3],
			  1.63283486016400008e-06,
			  1e-12 );
  TEST_FLOATING_EQUALITY( full_profile[2],
			  1.69058145887700007,
			  1e-12 );

  full_momentum_grid.clear();
  full_profile.clear();

  // Check that the grid can be extended
  MonteCarlo::createFullProfileFromHalfProfile( half_momentum_grid.begin(),
						half_momentum_grid.end(),
						half_profile.begin(),
						half_profile.end(),
						full_momentum_grid,
						full_profile,
						true,
						false );

  TEST_EQUALITY_CONST( full_momentum_grid.size(), 7 );
  TEST_EQUALITY_CONST( full_momentum_grid.front(), 
		       -Utility::PhysicalConstants::inverse_fine_structure_constant );
  TEST_EQUALITY_CONST( full_momentum_grid.back(), 
		       Utility::PhysicalConstants::inverse_fine_structure_constant );
  TEST_EQUALITY_CONST( full_momentum_grid[1], -100.0 );
  TEST_EQUALITY_CONST( full_momentum_grid[5], 100.0 );
  TEST_EQUALITY_CONST( full_momentum_grid[2], -10.0 );
  TEST_EQUALITY_CONST( full_momentum_grid[4], 10.0 );
  TEST_EQUALITY_CONST( full_momentum_grid[3], 0.0 );

  TEST_EQUALITY_CONST( full_profile.size(), 7 );
  
  TEST_FLOATING_EQUALITY( full_profile.front(),
			  7.2908632235832003e-13,
			  1e-12 );
  TEST_FLOATING_EQUALITY( full_profile.back(),
			  7.2908632235832003e-13,
			  1e-12 );
  TEST_FLOATING_EQUALITY( full_profile[1],
			  5.177281263934e-11,
			  1e-12 );
  TEST_FLOATING_EQUALITY( full_profile[5],
			  5.177281263934e-11,
			  1e-12 );
  TEST_FLOATING_EQUALITY( full_profile[2],
			  1.63283486016400008e-06,
			  1e-12 );
  TEST_FLOATING_EQUALITY( full_profile[4],
			  1.63283486016400008e-06,
			  1e-12 );
  TEST_FLOATING_EQUALITY( full_profile[3],
			  1.69058145887700007,
			  1e-12 );
}

//---------------------------------------------------------------------------//
// Check that a full profile can be constructed from a half profile
TEUCHOS_UNIT_TEST( ComptonProfileHelpers, 
		   createFullProfileFromHalfProfile_doubled )
{
  std::vector<double> half_momentum_grid, half_profile;

  half_momentum_grid.push_back( 0.0 );
  half_momentum_grid.push_back( 10.0 );
  half_momentum_grid.push_back( 100.0 );

  half_profile.push_back( 1.69058145887700007 );
  half_profile.push_back( 1.63283486016400008e-06 );
  half_profile.push_back( 5.177281263934e-11 );
  
  Teuchos::Array<double> full_momentum_grid, full_profile;

  // Check that the grid can be preserved
  MonteCarlo::createFullProfileFromHalfProfile( half_momentum_grid.begin(),
						half_momentum_grid.end(),
						half_profile.begin(),
						half_profile.end(),
						full_momentum_grid,
						full_profile,
						false,
						true );

  TEST_EQUALITY_CONST( full_momentum_grid.size(), 5 );
  TEST_EQUALITY_CONST( full_momentum_grid.front(), -100.0 );
  TEST_EQUALITY_CONST( full_momentum_grid.back(), 100.0 );
  TEST_EQUALITY_CONST( full_momentum_grid[1], -10.0 );
  TEST_EQUALITY_CONST( full_momentum_grid[3], 10.0 );
  TEST_EQUALITY_CONST( full_momentum_grid[2], 0.0 );

  TEST_EQUALITY_CONST( full_profile.size(), 5 );
  TEST_FLOATING_EQUALITY( full_profile.front(),
			  5.177281263934e-11/2,
			  1e-12 );
  TEST_FLOATING_EQUALITY( full_profile.back(),
			  5.177281263934e-11/2,
			  1e-12 );
  TEST_FLOATING_EQUALITY( full_profile[1],
			  1.63283486016400008e-06/2,
			  1e-12 );
  TEST_FLOATING_EQUALITY( full_profile[3],
			  1.63283486016400008e-06/2,
			  1e-12 );
  TEST_FLOATING_EQUALITY( full_profile[2],
			  1.69058145887700007/2,
			  1e-12 );
  
  // Check that the grid can be extended
  MonteCarlo::createFullProfileFromHalfProfile( half_momentum_grid.begin(),
						half_momentum_grid.end(),
						half_profile.begin(),
						half_profile.end(),
						full_momentum_grid,
						full_profile,
						true,
						true );

  TEST_EQUALITY_CONST( full_momentum_grid.size(), 7 );
  TEST_EQUALITY_CONST( full_momentum_grid.front(), 
		       -Utility::PhysicalConstants::inverse_fine_structure_constant );
  TEST_EQUALITY_CONST( full_momentum_grid.back(), 
		       Utility::PhysicalConstants::inverse_fine_structure_constant );
  TEST_EQUALITY_CONST( full_momentum_grid[1], -100.0 );
  TEST_EQUALITY_CONST( full_momentum_grid[5], 100.0 );
  TEST_EQUALITY_CONST( full_momentum_grid[2], -10.0 );
  TEST_EQUALITY_CONST( full_momentum_grid[4], 10.0 );
  TEST_EQUALITY_CONST( full_momentum_grid[3], 0.0 );

  TEST_EQUALITY_CONST( full_profile.size(), 7 );
  TEST_FLOATING_EQUALITY( full_profile.front(),
			  7.2908632235832003e-13/2,
			  1e-12 );
  TEST_FLOATING_EQUALITY( full_profile.back(),
			  7.2908632235832003e-13/2,
			  1e-12 );
  TEST_FLOATING_EQUALITY( full_profile[1],
			  5.177281263934e-11/2,
			  1e-12 );
  TEST_FLOATING_EQUALITY( full_profile[5],
			  5.177281263934e-11/2,
			  1e-12 );
  TEST_FLOATING_EQUALITY( full_profile[2],
			  1.63283486016400008e-06/2,
			  1e-12 );
  TEST_FLOATING_EQUALITY( full_profile[4],
			  1.63283486016400008e-06/2,
			  1e-12 );
  TEST_FLOATING_EQUALITY( full_profile[3],
			  1.69058145887700007/2,
			  1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the momentum grid can be converted to me*c units
TEUCHOS_UNIT_TEST( ComptonProfileHelpers, convertMomentumGridToMeCUnits )
{
  std::vector<double> half_momentum_grid;

  half_momentum_grid.push_back( 0.0 );
  half_momentum_grid.push_back( 10.0 );
  half_momentum_grid.push_back( 100.0 );

  MonteCarlo::convertMomentumGridToMeCUnits( half_momentum_grid.begin(),
					     half_momentum_grid.end() );  
}

//---------------------------------------------------------------------------//
// Check that the Compton profile can be converted to inverse me*c units
TEUCHOS_UNIT_TEST( ComptonProfileHelpers, convertProfileToInverseMeCUnits )
{
  std::vector<double> half_profile;
  
  half_profile.push_back( 1.69058145887700007 );
  half_profile.push_back( 1.63283486016400008e-06 );
  half_profile.push_back( 5.177281263934e-11 );

  MonteCarlo::convertProfileToInverseMeCUnits( half_profile.begin(),
					       half_profile.end() );
}

//---------------------------------------------------------------------------//
// end tstComptonProfileHelpers.cpp
//---------------------------------------------------------------------------//
