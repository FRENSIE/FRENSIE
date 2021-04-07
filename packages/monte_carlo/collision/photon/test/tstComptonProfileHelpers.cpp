//---------------------------------------------------------------------------//
//!
//! \file   tstComptonProfileHelpers.cpp
//! \author Alex Robinson
//! \brief  Compton profile helper function unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// FRENSIE Includes
#include "MonteCarlo_ComptonProfileHelpers.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that a full profile can be constructed from a half profile
FRENSIE_UNIT_TEST( ComptonProfileHelpers,
		   createFullProfileFromHalfProfile )
{
  std::vector<double> half_momentum_grid, half_profile;

  half_momentum_grid.push_back( 0.0 );
  half_momentum_grid.push_back( 10.0 );
  half_momentum_grid.push_back( 100.0 );

  half_profile.push_back( 1.69058145887700007 );
  half_profile.push_back( 1.63283486016400008e-06 );
  half_profile.push_back( 5.177281263934e-11 );

  std::vector<double> full_momentum_grid, full_profile;

  // Check that the grid can be preserved
  MonteCarlo::createFullProfileFromHalfProfile( half_momentum_grid.begin(),
						half_momentum_grid.end(),
						half_profile.begin(),
						half_profile.end(),
						full_momentum_grid,
						full_profile,
						false,
						false );

  FRENSIE_CHECK_EQUAL( full_momentum_grid.size(), 5 );
  FRENSIE_CHECK_EQUAL( full_momentum_grid.front(), -100.0 );
  FRENSIE_CHECK_EQUAL( full_momentum_grid.back(), 100.0 );
  FRENSIE_CHECK_EQUAL( full_momentum_grid[1], -10.0 );
  FRENSIE_CHECK_EQUAL( full_momentum_grid[3], 10.0 );
  FRENSIE_CHECK_EQUAL( full_momentum_grid[2], 0.0 );

  FRENSIE_CHECK_EQUAL( full_profile.size(), 5 );

  FRENSIE_CHECK_FLOATING_EQUALITY( full_profile.front(),
			  5.177281263934e-11,
			  1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( full_profile.back(),
			  5.177281263934e-11,
			  1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( full_profile[1],
			  1.63283486016400008e-06,
			  1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( full_profile[3],
			  1.63283486016400008e-06,
			  1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( full_profile[2],
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

  FRENSIE_CHECK_EQUAL( full_momentum_grid.size(), 7 );
  FRENSIE_CHECK_EQUAL( full_momentum_grid.front(),
		       -Utility::PhysicalConstants::inverse_fine_structure_constant );
  FRENSIE_CHECK_EQUAL( full_momentum_grid.back(),
		       Utility::PhysicalConstants::inverse_fine_structure_constant );
  FRENSIE_CHECK_EQUAL( full_momentum_grid[1], -100.0 );
  FRENSIE_CHECK_EQUAL( full_momentum_grid[5], 100.0 );
  FRENSIE_CHECK_EQUAL( full_momentum_grid[2], -10.0 );
  FRENSIE_CHECK_EQUAL( full_momentum_grid[4], 10.0 );
  FRENSIE_CHECK_EQUAL( full_momentum_grid[3], 0.0 );

  FRENSIE_CHECK_EQUAL( full_profile.size(), 7 );

  FRENSIE_CHECK_FLOATING_EQUALITY( full_profile.front(),
			  7.2908632235832003e-13,
			  1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( full_profile.back(),
			  7.2908632235832003e-13,
			  1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( full_profile[1],
			  5.177281263934e-11,
			  1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( full_profile[5],
			  5.177281263934e-11,
			  1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( full_profile[2],
			  1.63283486016400008e-06,
			  1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( full_profile[4],
			  1.63283486016400008e-06,
			  1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( full_profile[3],
			  1.69058145887700007,
			  1e-12 );
}

//---------------------------------------------------------------------------//
// Check that a full profile can be constructed from a half profile
FRENSIE_UNIT_TEST( ComptonProfileHelpers,
		   createFullProfileFromHalfProfile_doubled )
{
  std::vector<double> half_momentum_grid, half_profile;

  half_momentum_grid.push_back( 0.0 );
  half_momentum_grid.push_back( 10.0 );
  half_momentum_grid.push_back( 100.0 );

  half_profile.push_back( 1.69058145887700007 );
  half_profile.push_back( 1.63283486016400008e-06 );
  half_profile.push_back( 5.177281263934e-11 );

  std::vector<double> full_momentum_grid, full_profile;

  // Check that the grid can be preserved
  MonteCarlo::createFullProfileFromHalfProfile( half_momentum_grid.begin(),
						half_momentum_grid.end(),
						half_profile.begin(),
						half_profile.end(),
						full_momentum_grid,
						full_profile,
						false,
						true );

  FRENSIE_CHECK_EQUAL( full_momentum_grid.size(), 5 );
  FRENSIE_CHECK_EQUAL( full_momentum_grid.front(), -100.0 );
  FRENSIE_CHECK_EQUAL( full_momentum_grid.back(), 100.0 );
  FRENSIE_CHECK_EQUAL( full_momentum_grid[1], -10.0 );
  FRENSIE_CHECK_EQUAL( full_momentum_grid[3], 10.0 );
  FRENSIE_CHECK_EQUAL( full_momentum_grid[2], 0.0 );

  FRENSIE_CHECK_EQUAL( full_profile.size(), 5 );
  FRENSIE_CHECK_FLOATING_EQUALITY( full_profile.front(),
			  5.177281263934e-11/2,
			  1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( full_profile.back(),
			  5.177281263934e-11/2,
			  1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( full_profile[1],
			  1.63283486016400008e-06/2,
			  1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( full_profile[3],
			  1.63283486016400008e-06/2,
			  1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( full_profile[2],
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

  FRENSIE_CHECK_EQUAL( full_momentum_grid.size(), 7 );
  FRENSIE_CHECK_EQUAL( full_momentum_grid.front(),
		       -Utility::PhysicalConstants::inverse_fine_structure_constant );
  FRENSIE_CHECK_EQUAL( full_momentum_grid.back(),
		       Utility::PhysicalConstants::inverse_fine_structure_constant );
  FRENSIE_CHECK_EQUAL( full_momentum_grid[1], -100.0 );
  FRENSIE_CHECK_EQUAL( full_momentum_grid[5], 100.0 );
  FRENSIE_CHECK_EQUAL( full_momentum_grid[2], -10.0 );
  FRENSIE_CHECK_EQUAL( full_momentum_grid[4], 10.0 );
  FRENSIE_CHECK_EQUAL( full_momentum_grid[3], 0.0 );

  FRENSIE_CHECK_EQUAL( full_profile.size(), 7 );
  FRENSIE_CHECK_FLOATING_EQUALITY( full_profile.front(),
			  7.2908632235832003e-13/2,
			  1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( full_profile.back(),
			  7.2908632235832003e-13/2,
			  1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( full_profile[1],
			  5.177281263934e-11/2,
			  1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( full_profile[5],
			  5.177281263934e-11/2,
			  1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( full_profile[2],
			  1.63283486016400008e-06/2,
			  1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( full_profile[4],
			  1.63283486016400008e-06/2,
			  1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( full_profile[3],
			  1.69058145887700007/2,
			  1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the momentum grid can be converted to me*c units
FRENSIE_UNIT_TEST( ComptonProfileHelpers, convertMomentumGridToMeCUnits )
{
  std::vector<double> half_momentum_grid;

  half_momentum_grid.push_back( 0.0 );
  half_momentum_grid.push_back( 10.0 );
  half_momentum_grid.push_back( 100.0 );

  MonteCarlo::convertMomentumGridToMeCUnits( half_momentum_grid.begin(),
					     half_momentum_grid.end() );

  FRENSIE_CHECK_SMALL( half_momentum_grid[0], 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( half_momentum_grid[1],
                                   7.297352569816314971e-02,
                                   1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( half_momentum_grid[2],
                                   7.297352569816315526e-01,
                                   1e-15 );
}

//---------------------------------------------------------------------------//
// Check that the Compton profile can be converted to inverse me*c units
FRENSIE_UNIT_TEST( ComptonProfileHelpers, convertProfileToInverseMeCUnits )
{
  std::vector<double> half_profile;

  half_profile.push_back( 1.69058145887700007 );
  half_profile.push_back( 1.63283486016400008e-06 );
  half_profile.push_back( 5.177281263934e-11 );

  MonteCarlo::convertProfileToInverseMeCUnits( half_profile.begin(),
					       half_profile.end() );

  FRENSIE_CHECK_FLOATING_EQUALITY( half_profile,
                                   std::vector<double>({2.316705192331901344e+02, 2.237571563854288232e-04, 7.094739104902971188e-09}),
                                   1e-15 );
}

//---------------------------------------------------------------------------//
// end tstComptonProfileHelpers.cpp
//---------------------------------------------------------------------------//
