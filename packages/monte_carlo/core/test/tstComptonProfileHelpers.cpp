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

  MonteCarlo::createFullProfileFromHalfProfile( half_momentum_grid.begin(),
						half_momentum_grid.end(),
						half_profile.begin(),
						half_profile.end(),
						full_momentum_grid,
						full_profile,
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
			  7.290862715882092e-13,
			  1e-12 );
  TEST_FLOATING_EQUALITY( full_profile.back(),
			  7.290862715882092e-13,
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

  MonteCarlo::createFullProfileFromHalfProfile( half_momentum_grid.begin(),
						half_momentum_grid.end(),
						half_profile.begin(),
						half_profile.end(),
						full_momentum_grid,
						full_profile,
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
			  7.290862715882092e-13/2,
			  1e-12 );
  TEST_FLOATING_EQUALITY( full_profile.back(),
			  7.290862715882092e-13/2,
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
// Check that the Compton line energy can be calculated
TEUCHOS_UNIT_TEST( ComptonProfileHelpers, calculateComptonLineEnergy )
{
  double compton_line = MonteCarlo::calculateComptonLineEnergy( 0.1, -1.0 );

  TEST_FLOATING_EQUALITY( compton_line, 0.0718705616632476, 1e-15 );

  compton_line = MonteCarlo::calculateComptonLineEnergy( 0.1, 0.0 );

  TEST_FLOATING_EQUALITY( compton_line, 0.0836333586947441, 1e-15 );

  compton_line = MonteCarlo::calculateComptonLineEnergy( 0.1, 1.0 );

  TEST_FLOATING_EQUALITY( compton_line, 0.1, 1e-15 );

  compton_line = MonteCarlo::calculateComptonLineEnergy( 1.0, -1.0 );
  
  TEST_FLOATING_EQUALITY( compton_line, 0.20350423413905203, 1e-15 );

  compton_line = MonteCarlo::calculateComptonLineEnergy( 1.0, 0.0 );

  TEST_FLOATING_EQUALITY( compton_line, 0.3381861540098899, 1e-15 );

  compton_line = MonteCarlo::calculateComptonLineEnergy( 1.0, 1.0 );
  
  TEST_FLOATING_EQUALITY( compton_line, 1.0, 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that the electron momentum projection can be calculated
TEUCHOS_UNIT_TEST( ComptonProfileHelpers, calculateElectronMomentumProjection )
{
  double pz = 
    MonteCarlo::calculateElectronMomentumProjection( 1.0, 0.5, -1.0 );

  TEST_FLOATING_EQUALITY( pz, 0.9713008908317715, 1e-15 );

  pz = MonteCarlo::calculateElectronMomentumProjection( 1.0, 0.5, 0.0 );

  TEST_FLOATING_EQUALITY( pz, 0.42796164780180407, 1e-15 );

  pz = MonteCarlo::calculateElectronMomentumProjection( 1.0, 0.5, 1.0 );

  TEST_FLOATING_EQUALITY( pz, -1.0, 1e-15 );

  pz = MonteCarlo::calculateElectronMomentumProjection( 0.5, 0.1, -1.0 );

  TEST_FLOATING_EQUALITY( pz, -0.34050811062539044, 1e-15 );

  pz = MonteCarlo::calculateElectronMomentumProjection( 0.5, 0.1, 0.0 );

  TEST_FLOATING_EQUALITY( pz, -0.5925696741935385, 1e-15 );

  pz = MonteCarlo::calculateElectronMomentumProjection( 0.5, 0.1, 1.0 );

  TEST_FLOATING_EQUALITY( pz, -1.0, 1e-15 );

  pz = MonteCarlo::calculateElectronMomentumProjection( 0.1, 0.001, -1.0 );

  TEST_FLOATING_EQUALITY( pz, -0.9763228686410937, 1e-15 );

  pz = MonteCarlo::calculateElectronMomentumProjection( 0.1, 0.001, 0.0 );
  
  TEST_FLOATING_EQUALITY( pz, -0.9879936502161719, 1e-15 );

  pz = MonteCarlo::calculateElectronMomentumProjection( 0.1, 0.001, 1.0 );

  TEST_FLOATING_EQUALITY( pz, -1.0, 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that the max electron momentum projection can be calculated
TEUCHOS_UNIT_TEST( ComptonProfileHelpers, 
		   calculateMaxElectronMomentumProjection )
{
  double pz_max = 
    MonteCarlo::calculateMaxElectronMomentumProjection(1.0, 0.03, -1.0);

  TEST_FLOATING_EQUALITY( pz_max, 1.9119216204672362, 1e-15 );

  pz_max = MonteCarlo::calculateMaxElectronMomentumProjection(1.0, 0.03, 0.0);
  
  TEST_FLOATING_EQUALITY( pz_max, 1.3410091350301137, 1e-15 );

  pz_max = MonteCarlo::calculateMaxElectronMomentumProjection(1.0, 0.03, 1.0);
    
  TEST_FLOATING_EQUALITY( pz_max, -1.0, 1e-15 );

  pz_max = MonteCarlo::calculateMaxElectronMomentumProjection(0.1, 0.03, -1.0);

  TEST_FLOATING_EQUALITY( pz_max, -0.015309889956075224, 1e-14 );

  pz_max = MonteCarlo::calculateMaxElectronMomentumProjection(0.1, 0.03, 0.0);

  TEST_FLOATING_EQUALITY( pz_max, -0.13354578604675912, 1e-15 );

  pz_max = MonteCarlo::calculateMaxElectronMomentumProjection(0.1, 0.03, 1.0);
  
  TEST_FLOATING_EQUALITY( pz_max, -1.0, 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that the Doppler broadened energy can be calculated
TEUCHOS_UNIT_TEST( ComptonProfileHelpers, calculateDopplerBroadenedEnergy )
{
  bool possible;
  
  double energy = MonteCarlo::calculateDopplerBroadenedEnergy(
						    1.0, 1.0, -1.0, possible );

  TEST_ASSERT( possible );
  TEST_FLOATING_EQUALITY( energy, 0.5109989101300001, 1e-15 );

  energy = MonteCarlo::calculateDopplerBroadenedEnergy(
						     1.0, 1.0, 0.0, possible );

  TEST_ASSERT( possible );
  TEST_FLOATING_EQUALITY( energy, 0.7637187226885975, 1e-15 );

  energy = MonteCarlo::calculateDopplerBroadenedEnergy(
						    -1.0, 1.0, 1.0, possible );

  TEST_ASSERT( !possible );
  TEST_EQUALITY_CONST( energy, 0.0 );
  
  energy = MonteCarlo::calculateDopplerBroadenedEnergy(
						 -0.016, 0.1, -1.0, possible );

  TEST_ASSERT( possible );
  TEST_FLOATING_EQUALITY( energy, 0.06991664095581886, 1e-14 );

  energy = MonteCarlo::calculateDopplerBroadenedEnergy(
						   -0.14, 0.1, 0.0, possible );

  TEST_ASSERT( possible );
  TEST_FLOATING_EQUALITY( energy, 0.06938244760315788, 1e-15 );

  energy = MonteCarlo::calculateDopplerBroadenedEnergy(
						    -1.0, 0.1, 1.0, possible );

  TEST_ASSERT( !possible );
  TEST_EQUALITY_CONST( energy, 0.0 );
}

//---------------------------------------------------------------------------//
// end tstComptonProfileHelpers.cpp
//---------------------------------------------------------------------------//
