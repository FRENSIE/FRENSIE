//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ComptonProfileHelpers.npp
//! \author Alex Robinson
//! \brief  The Compton profile helper function declarations.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_COMPTON_PROFILE_HELPERS_HPP
#define MONTE_CARLO_COMPTON_PROFILE_HELPERS_HPP

// FRENSIE Includes
#include "Utility_Vector.hpp"

namespace MonteCarlo{

//! Create a full profile from a doubled half profile
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
			      const bool extend_if_possible = false,
			      const bool doubled_half_profile = true );

//! Convert the momentum grid from me*e^2/h_bar to me*c units
template<typename GridIterator>
void convertMomentumGridToMeCUnits( GridIterator momentum_grid_start,
				    GridIterator momentum_grid_end );

//! Convert the Compton profile from h_bar/(me*e^2) to 1/(me*c) units
template<typename ProfileIterator>
void convertProfileToInverseMeCUnits( ProfileIterator profile_start,
				      ProfileIterator profile_end );

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "MonteCarlo_ComptonProfileHelpers_def.hpp"

//---------------------------------------------------------------------------//

#endif // end MONTE_CARLO_COMPTON_PROFILE_HELPERS_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ComptonProfileHelpers.hpp
//---------------------------------------------------------------------------//
