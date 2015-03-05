//---------------------------------------------------------------------------//
//!
//! \file   DataGen_ComptonProfileHelpers.cpp
//! \author Alex Robinson
//! \brief  The Compton profile helper function declarations.
//!
//---------------------------------------------------------------------------//

#ifndef DATA_GEN_COMPTON_PROFILE_HELPERS_HPP
#define DATA_GEN_COMPTON_PROFILE_HELPERS_HPP

// Trilinos Includes
#include <Teuchos_Array.hpp>

namespace DataGen{

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
			      const bool doubled_half_profile = true );

//! Convert the momentum grid from me*e^2/h_bar to me*c units	     
template<typename GridIterator>
void convertMomentumGridToMeCUnits( GridIterator momentum_grid_start,
				    GridIterator momentum_grid_end );

//! Convert the Compton profile from h_bar/(me*e^2) to 1/(me*c) units
template<typename ProfileIterator>
void convertProfileToInverseMeCUnits( ProfileIterator profile_start,
				      ProfileIterator profile_end );

} // end DataGen namespace

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "DataGen_ComptonProfileHelpers_def.hpp"

//---------------------------------------------------------------------------//

#endif // end DATA_GEN_COMPTON_PROFILE_HELPERS_HPP

//---------------------------------------------------------------------------//
// end DataGen_ComptonProfileHelpers.hpp
//---------------------------------------------------------------------------//
