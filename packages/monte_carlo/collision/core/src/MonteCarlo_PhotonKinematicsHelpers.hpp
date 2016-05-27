//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_PhotonKinematicsHelpers.hpp
//! \author Alex Robinson
//! \brief  Photon kinematics helper function declarations
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_PHOTON_KINEMATICS_HELPERS_HPP
#define MONTE_CARLO_PHOTON_KINEMATICS_HELPERS_HPP

// FRENSIE Includes
#include "MonteCarlo_ModuleTraits.hpp"
#include "MonteCarlo_ComptonProfile.hpp"

namespace MonteCarlo{

//! Calculate the Compton line energy
double calculateComptonLineEnergy( const double initial_energy,
				   const double scattering_angle_cosine );

//! Calculate the Compton line energy quantity
ModuleTraits::EnergyQuantity calculateComptonLineEnergyQuantity(
                             const ModuleTraits::EnergyQuantity initial_energy,
                             const double scattering_angle_cosine );

//! Calculate the Compton line energy quantity
template<typename InputEnergyQuantity>
ModuleTraits::EnergyQuantity calculateComptonLineEnergyQuantity(
                                      const InputEnergyQuantity initial_energy,
                                      const double scattering_angle_cosine );

//! Calculate the electron momentum projection
double calculateElectronMomentumProjection(
					const double initial_energy,
					const double final_energy,
					const double scattering_angle_cosine );

//! Calculate the electron momentum projection quantity
ComptonProfile::MomentumQuantity calculateElectronMomentumProjectionQuantity(
                             const ModuleTraits::EnergyQuantity initial_energy,
                             const ModuleTraits::EnergyQuantity final_energy,
                             const double scattering_angle_cosine );

//! Calculate the electron momentum projection quantity
template<typename InitialEnergyQuantity, typename FinalEnergyQuantity>
ComptonProfile::MomentumQuantity calculateElectronMomentumProjectionQuantity(
                                    const InitialEnergyQuantity initial_energy,
                                    const FinalEnergyQuantity final_energy,
                                    const double scattering_angle_cosine );

//! Calculate the maximum electron momentum projection
double calculateMaxElectronMomentumProjection(
				  const double initial_energy,
				  const double binding_energy,
				  const double scattering_angle_cosine );

//! Calculate the maximum electron momentum projection quantity
ComptonProfile::MomentumQuantity
calculateMaxElectronMomentumProjectionQuantity(
                             const ModuleTraits::EnergyQuantity initial_energy,
                             const ModuleTraits::EnergyQuantity binding_energy,
                             const double scattering_angle_cosine );

//! Calculate the maximum electron momentum projection quantity
template<typename InitialEnergyQuantity, typename BindingEnergyQuantity>
ComptonProfile::MomentumQuantity
calculateMaxElectronMomentumProjectionQuantity(
                                    const InitialEnergyQuantity initial_energy,
                                    const BindingEnergyQuantity binding_energy,
                                    const double scattering_angle_cosine );

//! Calculate the Doppler broadened energy
double calculateDopplerBroadenedEnergy(
				     const double electron_momentum_projection,
				     const double initial_energy,
				     const double scattering_angle_cosine,
				     bool& energetically_possible );

//! Calculate the Doppler broadened energy quantity
ModuleTraits::EnergyQuantity calculateDopplerBroadenedEnergyQuantity(
           const ComptonProfile::MomentumQuantity electron_momentum_projection,
           const ModuleTraits::EnergyQuantity initial_energy,
           const double scattering_angle_cosine,
           bool& energetically_possible );

//! Calculate the Doppler broadened energy quantity
template<typename InputMomentumQuantity, typename InputEnergyQuantity>
ModuleTraits::EnergyQuantity calculateDopplerBroadenedEnergyQuantity(
                      const InputMomentumQuantity electron_momentum_projection,
                      const InputEnergyQuantity initial_energy,
                      const double scattering_angle_cosine,
                      bool& energetically_possible );

} // end MonteCarlo

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "MonteCarlo_PhotonKinematicsHelpers_def.hpp"

//---------------------------------------------------------------------------//

#endif // end MONTE_CARLO_PHOTON_KINEMATICS_HELPERS_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_PhotonKinematicsHelpers.hpp
//---------------------------------------------------------------------------//
