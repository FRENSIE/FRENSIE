//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ComptonProfileHelpers_def.hpp
//! \author Alex Robinson
//! \brief  The Compton profile helper function template definitions
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_COMPTON_PROFILE_HELPERS_DEF_HPP
#define MONTE_CARLO_COMPTON_PROFILE_HELPERS_DEF_HPP

// Std Lib Includes
#include <iterator>

// FRENSIE Includes
#include "Utility_SortAlgorithms.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_DesignByContract.hpp"

namespace MonteCarlo{

// Create a full profile from a doubled half profile
/*! \details Compton profiles are typically only given on the positive half
 * of the momentum grid. To ensure that they still integrate to 1.0 they are
 * also usually multiplied by 2. If only half of the grid is given and it
 * it is not multiplied by two, the doubled_half_profile parameter should
 * be passed in as false. Additionally, the momentum grid should be in
 * units of me*e^2/h_bar (atomic units) and not me*c units. The Compton
 * profile should have units of h_bar/(me*e^2) and not 1/(me*c) units.
 */
template<typename GridIterator,
	 typename ProfileIterator,
	 typename STLCompliantArrayA,
	 typename STLCompliantArrayB>
void createFullProfileFromHalfProfile(
			      const GridIterator half_momentum_grid_start,
			      const GridIterator half_momentum_grid_end,
			      const ProfileIterator half_profile_start,
			      const ProfileIterator half_profile_end,
			      STLCompliantArrayA& full_momentum_grid,
			      STLCompliantArrayB& full_profile,
			      const bool extend_if_possible,
			      const bool doubled_half_profile )
{
  // Make sure the half grid and the half profile have the same size
  testPrecondition( std::distance( half_momentum_grid_start,
				   half_momentum_grid_end ) ==
		    std::distance( half_profile_start, half_profile_end ) );
  // Make sure the half momentum grid starts at 0.0
  testPrecondition( *half_momentum_grid_start == 0.0 );
  // Make sure the half profile grid is valid
  testPrecondition( Utility::Sort::isSortedAscending(half_momentum_grid_start,
						     half_momentum_grid_end) );
  // Make sure the half profile grid is valid
  remember( ProfileIterator half_profile_true_end = half_profile_end );
  remember( --half_profile_true_end );
  testPrecondition( *half_profile_start > *half_profile_true_end );

  full_momentum_grid.clear();
  full_profile.clear();

  // Check if a grid extension is possible
  bool grid_extension_possible;

  unsigned half_grid_size =
    std::distance( half_momentum_grid_start, half_momentum_grid_end );

  GridIterator half_momentum_grid_true_end = half_momentum_grid_end;
  --half_momentum_grid_true_end;

  if( *half_momentum_grid_true_end <
      Utility::PhysicalConstants::inverse_fine_structure_constant )
    grid_extension_possible = true;
  else
    grid_extension_possible = false;

  // Calculate the size of the full grid
  unsigned full_grid_size, middle_index;

  if( grid_extension_possible && extend_if_possible )
  {
    full_grid_size = (half_grid_size + 1)*2 - 1;

    middle_index = half_grid_size;
  }
  else
  {
    full_grid_size = half_grid_size*2 - 1;

    middle_index = half_grid_size - 1;
  }

  full_momentum_grid.resize( full_grid_size );
  full_profile.resize( full_grid_size );

  // Create the full grid
  GridIterator half_momentum_grid_point = half_momentum_grid_start;
  ProfileIterator half_profile_point = half_profile_start;
  unsigned half_grid_index = 0u;

  while( half_momentum_grid_point != half_momentum_grid_end )
  {
    if( half_grid_index != 0u )
    {
      // Positive side of profile
      full_momentum_grid[middle_index+half_grid_index] =
	*half_momentum_grid_point;

      full_profile[middle_index+half_grid_index] = *half_profile_point;

      // Negative side of profile
      full_momentum_grid[middle_index-half_grid_index] =
	-(*half_momentum_grid_point);

      full_profile[middle_index-half_grid_index] = *half_profile_point;
    }
    else // Middle of profile (pz = 0.0)
    {
      full_momentum_grid[middle_index] = 0.0;

      full_profile[middle_index] = *half_profile_point;
    }

    ++half_momentum_grid_point;
    ++half_profile_point;
    ++half_grid_index;
  }

  // Renormalize the grid
  if( doubled_half_profile )
  {
    for( unsigned i = 0; i < full_profile.size(); ++i )
      full_profile[i] /= 2.0;
  }

  // Extend the grid if required
  if( grid_extension_possible && extend_if_possible )
  {
    double profile_0 =
      full_profile[full_profile.size()-3];
    double profile_1 =
      full_profile[full_profile.size()-2];
    double momentum_0 =
      full_momentum_grid[full_momentum_grid.size()-3];
    double momentum_1 =
      full_momentum_grid[full_momentum_grid.size()-2];

    double processed_slope = (log(profile_1)-log(profile_0))/
      (momentum_1-momentum_0);

    double extrapolated_profile = exp( log(profile_0) +processed_slope*(
     Utility::PhysicalConstants::inverse_fine_structure_constant-momentum_0) );

    full_momentum_grid.front() =
      -Utility::PhysicalConstants::inverse_fine_structure_constant;
    full_profile.front() = extrapolated_profile;

    full_momentum_grid.back() =
      Utility::PhysicalConstants::inverse_fine_structure_constant;
    full_profile.back() = extrapolated_profile;
  }
}

// Convert the momentum grid from me*e^2/h_bar to me*c units
template<typename GridIterator>
void convertMomentumGridToMeCUnits( GridIterator momentum_grid_start,
				    GridIterator momentum_grid_end )
{
  // Make sure the grid is valid
  testPrecondition( std::distance(momentum_grid_start, momentum_grid_end) > 1);

  while( momentum_grid_start != momentum_grid_end )
  {
    *momentum_grid_start /=
      Utility::PhysicalConstants::inverse_fine_structure_constant;

    ++momentum_grid_start;
  }
}

// Convert the Compton profile from h_bar/(me*e^2) to 1/(me*c) units
template<typename ProfileIterator>
void convertProfileToInverseMeCUnits( ProfileIterator profile_start,
				      ProfileIterator profile_end )
{
  // Make sure the profile is valid
  testPrecondition( std::distance( profile_start, profile_end ) > 1 );

  while( profile_start != profile_end )
  {
    *profile_start *=
      Utility::PhysicalConstants::inverse_fine_structure_constant;

    ++profile_start;
  }
}

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_COMPTON_PROFILE_HELPERS_DEF_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ComptonProfileHelpers_def.hpp
//---------------------------------------------------------------------------//
