//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_PhotonKinematicsHelpers.hpp
//! \author Alex Robinson
//! \brief  Photon kinematics helper function declarations
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_PHOTON_KINEMATICS_HELPERS_DEF_HPP
#define MONTE_CARLO_PHOTON_KINEMATICS_HELPERS_DEF_HPP

// FRENSIE Includes
#include "Utility_QuantityTraits.hpp"

namespace MonteCarlo{

// Calculate the Compton line energy quantity
template<typename InputEnergyQuantity>
inline ModuleTraits::EnergyQuantity calculateComptonLineEnergyQuantity(
                                      const InputEnergyQuantity initial_energy,
                                      const double scattering_angle_cosine )
{
  // Make sure the initial energy is valid
  testPrecondition( initial_energy >
                    Utility::QuantityTraits<InputEnergyQuantity>::zero() );
  // Make sure the scattering angle cosine is valid
  testPrecondition( scattering_angle_cosine >= -1.0 );
  testPrecondition( scattering_angle_cosine <= 1.0 );

  ModuleTraits::EnergyQuantity converted_initial_energy( initial_energy );

  return calculateComptonLineEnergyQuantity( converted_initial_energy,
                                             scattering_angle_cosine );
}

// Calculate the electron momentum projection quantity
template<typename InitialEnergyQuantity, typename FinalEnergyQuantity>
inline ComptonProfile::MomentumQuantity
calculateElectronMomentumProjectionQuantity(
                                    const InitialEnergyQuantity initial_energy,
                                    const FinalEnergyQuantity final_energy,
                                    const double scattering_angle_cosine )
{
  // Make sure the energies are valid
  testPrecondition( final_energy >=
                    Utility::QuantityTraits<FinalEnergyQuantity>::zero() );
  testPrecondition( FinalEnergyQuantity( initial_energy ) >= final_energy );
  // Make sure the scattering angle cosine is valid
  testPrecondition( scattering_angle_cosine >= -1.0 );
  testPrecondition( scattering_angle_cosine <= 1.0 );

  ModuleTraits::EnergyQuantity converted_initial_energy( initial_energy );
  ModuleTraits::EnergyQuantity converted_final_energy( final_energy );

  return calculateElectronMomentumProjectionQuantity( converted_initial_energy,
                                                      converted_final_energy,
                                                      scattering_angle_cosine);
}

// Calculate the maximum electron momentum projection quantity
template<typename InitialEnergyQuantity, typename BindingEnergyQuantity>
inline ComptonProfile::MomentumQuantity
calculateMaxElectronMomentumProjectionQuantity(
                                    const InitialEnergyQuantity initial_energy,
                                    const BindingEnergyQuantity binding_energy,
                                    const double scattering_angle_cosine )
{
  // Make sure the binding energy is valid
  testPrecondition( binding_energy >=
                    Utility::QuantityTraits<BindingEnergyQuantity>::zero() );
  // Make sure the initial energy is valid
  testPrecondition( BindingEnergyQuantity(initial_energy) >= binding_energy );
  // Make sure the scattering angle cosine is valid
  testPrecondition( scattering_angle_cosine >= -1.0 );
  testPrecondition( scattering_angle_cosine <= 1.0 );

  ModuleTraits::EnergyQuantity converted_initial_energy( initial_energy );
  ModuleTraits::EnergyQuantity converted_binding_energy( binding_energy );
  
  return calculateMaxElectronMomentumProjectionQuantity(
                                                     converted_initial_energy,
                                                     converted_binding_energy,
                                                     scattering_angle_cosine );
}

// Calculate the Doppler broadened energy quantity
/*! If the determinant that is calculated is less
 * than zero, an outgoing energy of 0.0 will be returned and the
 * energetically_possible boolean inout arg will be set to false.
 */
template<typename InputMomentumQuantity, typename InputEnergyQuantity>
inline ModuleTraits::EnergyQuantity calculateDopplerBroadenedEnergyQuantity(
                      const InputMomentumQuantity electron_momentum_projection,
                      const InputEnergyQuantity initial_energy,
                      const double scattering_angle_cosine,
                      bool& energetically_possible )
{
  // Make sure the initial energy is valid
  testPrecondition( initial_energy >
                    Utility::QuantityTraits<InputEnergyQuantity>::zero() );
  // Make sure the scattering angle cosine is valid
  testPrecondition( scattering_angle_cosine >= -1.0 );
  testPrecondition( scattering_angle_cosine <= 1.0 );

  ComptonProfile::MomentumQuantity converted_pz(electron_momentum_projection);
  ModuleTraits::EnergyQuantity converted_initial_energy( initial_energy );

  return calculateDopplerBroadenedEnergyQuantity( converted_pz,
                                                  converted_initial_energy,
                                                  scattering_angle_cosine,
                                                  energetically_possible );
}
  
} // end MonteCarlo namespace

#endif // end MONTE_CARLO_PHOTON_KINEMATICS_HELPERS_DEF_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_PhotonKinematicsHelpers_def.hpp
//---------------------------------------------------------------------------//
