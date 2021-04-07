//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_PhotonKinematicsHelpers.hpp
//! \author Alex Robinson
//! \brief  Photon kinematics helper function declarations
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_PHOTON_KINEMATICS_HELPERS_HPP
#define MONTE_CARLO_PHOTON_KINEMATICS_HELPERS_HPP

namespace MonteCarlo{

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

//! Calculate the scattering angle cosine
double calculateScatteringAngleCosine(
                                     const double initial_energy,
                                     const double final_energy,
                                     const double electron_momentum_projection,
                                     bool& energetically_possible );

} // end MonteCarlo

#endif // end MONTE_CARLO_PHOTON_KINEMATICS_HELPERS_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_PhotonKinematicsHelpers.hpp
//---------------------------------------------------------------------------//
