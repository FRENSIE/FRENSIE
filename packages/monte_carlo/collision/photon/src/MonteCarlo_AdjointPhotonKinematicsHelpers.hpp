//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_AdjointPhotonKinematicsHelpers.hpp
//! \author Alex Robinson
//! \brief  Adjoint photon kinematics helper function delcarations
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_ADJOINT_PHOTON_KINEMATICS_HELPERS_HPP
#define MONTE_CARLO_ADJOINT_PHOTON_KINEMATICS_HELPERS_HPP

namespace MonteCarlo{

//! Calculate the adjoint Compton line energy
double calculateAdjointComptonLineEnergy(
				        const double incoming_energy,
				        const double scattering_angle_cosine );

//! Calculate the scattering angle cosine
double calculateScatteringAngleCosineAdjoint( const double incoming_energy,
					      const double outgoing_energy );

//! Calculate the minimum scattering angle cosine
double calculateMinScatteringAngleCosine( const double incoming_energy,
					  const double max_energy );

//! Calculate the absolute minimum scattering angle cosine
double calculateAbsoluteMinScatteringAngleCosine(
						const double incoming_energy );

//! Calculate the min inverse energy gain ratio
double calculateMinInverseEnergyGainRatio( const double incoming_energy,
					   const double max_energy );

//! Calculate the absolute min inverse energy gain ratio
double calculateAbsoluteMinInverseEnergyGainRatio(
						const double incoming_energy );

//! Calculate the electron momentum projection
double calculateElectronMomentumProjectionAdjoint(
					const double initial_energy,
					const double final_energy,
					const double scattering_angle_cosine );

//! Calculate the maximum electron momentum projection
double calculateMaxElectronMomentumProjectionAdjoint(
				        const double initial_energy,
					const double binding_energy,
					const double scattering_angle_cosine );

//! Calculate the minimum electron momentum projection
double calculateMinElectronMomentumProjectionAdjoint(
				        const double initial_energy,
					const double max_energy,
					const double scattering_angle_cosine );

//! Calculate the absolute minimum electron momentum projection
double calculateAbsoluteMinElectronMomentumProjectionAdjoint(
					const double initial_energy,
					const double scattering_angle_cosine );

//! Calculate the Doppler broadened energy
double calculateDopplerBroadenedEnergyAdjoint(
				     const double electron_momentum_projection,
				     const double initial_energy,
				     const double scattering_angle_cosine,
				     bool& energetically_possible );

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_ADJOINT_PHOTON_KINEMATICS_HELPERS_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_AdjointPhotonKinematicsHelpers.hpp
//---------------------------------------------------------------------------//
