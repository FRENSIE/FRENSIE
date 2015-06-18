//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ComptonProfileHelpers.npp
//! \author Alex Robinson
//! \brief  The Compton profile helper function declarations.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_COMPTON_PROFILE_HELPERS_HPP
#define MONTE_CARLO_COMPTON_PROFILE_HELPERS_HPP

// Trilinos Includes
#include <Teuchos_Array.hpp>

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
			      const bool doubled_half_profile = true );

//! Convert the momentum grid from me*e^2/h_bar to me*c units	     
template<typename GridIterator>
void convertMomentumGridToMeCUnits( GridIterator momentum_grid_start,
				    GridIterator momentum_grid_end );

//! Convert the Compton profile from h_bar/(me*e^2) to 1/(me*c) units
template<typename ProfileIterator>
void convertProfileToInverseMeCUnits( ProfileIterator profile_start,
				      ProfileIterator profile_end );

//! Calculate the Compton line energy
double calculateComptonLineEnergy( const double initial_energy,
				   const double scattering_angle_cosine );

//! Calculate the electron momentum projection
double calculateElectronMomentumProjection(
					const double initial_energy,
					const double final_energy,
					const double scattering_angle_cosine );

//! Calculate the maximum electron momentum projection
double calculateMaxElectronMomentumProjection(
				  const double initial_energy,
				  const double binding_energy,
				  const double scattering_angle_cosine );

//! Calculate the Doppler broadened energy
double calculateDopplerBroadenedEnergy(
				     const double electron_momentum_projection,
				     const double initial_energy,
				     const double scattering_angle_cosine,
				     bool& energetically_possible );

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
