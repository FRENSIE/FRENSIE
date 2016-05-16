//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_DecoupledStandardCompleteDopplerBroadenedPhotonEnergyDistribution_def.hpp
//! \author Alex Robinson
//! \brief  The decoupled complete Doppler broadened photon energy dist. def.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_DECOUPLED_STANDARD_COMPLETE_DOPPLER_BROADENED_PHOTON_ENERGY_DISTRIBUTION_DEF_HPP
#define MONTE_CARLO_DECOUPLED_STANDARD_COMPLETE_DOPPLER_BROADENED_PHOTON_ENERGY_DISTRIBUTION_DEF_HPP

// Boost Includes
#include <boost/function.hpp>
#include <boost/bind.hpp>

// FRENSIE Includes
#include "MonteCarlo_DecoupledStandardCompleteDopplerBroadenedPhotonEnergyDistribution.hpp"
#include "Utility_GaussKronrodIntegrator.hpp"
#include "Utility_DiscreteDistribution.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Constructor
/*! \details The Compton profile grids must be in me*c units (not atomic 
 * units). The Compton profiles must be in inverse me*c units (not inverse 
 * atomic units). Only half profiles should be provided (grid ranges from 0.0 
 * to 1.0).
 */
template<typename ComptonProfilePolicy>
DecoupledStandardCompleteDopplerBroadenedPhotonEnergyDistribution<ComptonProfilePolicy>::DecoupledStandardCompleteDopplerBroadenedPhotonEnergyDistribution(
     const Teuchos::Array<double>& endf_subshell_occupancies,
     const Teuchos::Array<Data::SubshellType>& endf_subshell_order,
     const Teuchos::Array<double>& old_subshell_binding_energies,
     const Teuchos::Array<double>& old_subshell_occupancies,
     const std::shared_ptr<const ComptonProfileSubshellConverter>&
     subshell_converter,
     const DopplerBroadenedPhotonEnergyDistribution::ElectronMomentumDistArray&
     electron_momentum_dist_array )
  : StandardCompleteDopplerBroadenedPhotonEnergyDistribution<ComptonProfilePolicy>(
                                                endf_subshell_occupancies,
                                                endf_subshell_order,
                                                subshell_converter,
                                                electron_momentum_dist_array ),
    d_old_subshell_occupancy_distribution(),
    d_old_subshell_binding_energy( old_subshell_binding_energies ),
    d_old_subshell_occupancies( old_subshell_occupancies )
{
  // Make sure the old shell data is valid
  testPrecondition( old_subshell_binding_energies.size() > 0 );
  testPrecondition( old_subshell_occupancies.size() ==
		    old_subshell_binding_energies.size() );
  // Make sure the comptron profile array is valid
  testPrecondition( electron_momentum_dist_array.size() ==
		    old_subshell_binding_energies.size() );

  // Create the old subshell interaction distribution
  Teuchos::Array<double> dummy_indep_vals( old_subshell_occupancies.size() );

  d_old_subshell_occupancy_distribution.reset(
	       new Utility::DiscreteDistribution( dummy_indep_vals,
					          old_subshell_occupancies ) );
}

// Return the binding energy of a subshell
template<typename ComptonProfilePolicy>
double DecoupledStandardCompleteDopplerBroadenedPhotonEnergyDistribution<ComptonProfilePolicy>::getSubshellBindingEnergy( 
                                            const Data::SubshellType subshell ) const
{
  // Make sure the subshell is valid
  testPrecondition( this->isValidSubshell( subshell ) );

  unsigned old_subshell_index = this->getOldSubshellIndex( subshell );

  return d_old_subshell_binding_energy[old_subshell_index];
}
  
// Return the occupancy of a subshell (default is the ENDF occupacy)
template<typename ComptonProfilePolicy>
double DecoupledStandardCompleteDopplerBroadenedPhotonEnergyDistribution<ComptonProfilePolicy>::getSubshellOccupancy( 
                                            const Data::SubshellType subshell ) const
{
  // Make sure the subshell is valid
  testPrecondition( this->isValidSubshell( subshell ) );

  unsigned old_subshell_index = this->getOldSubshellIndex( subshell );

  return d_old_subshell_occupancies[old_subshell_index];
}

// Evaluate the distribution
template<typename ComptonProfilePolicy>
double DecoupledStandardCompleteDopplerBroadenedPhotonEnergyDistribution<ComptonProfilePolicy>::evaluate( 
				   const double incoming_energy,
				   const double outgoing_energy,
				   const double scattering_angle_cosine ) const
{
  // Make sure the incoming energy is valid
  testPrecondition( incoming_energy > 0.0 );
  // Make sure the outgoing energy is valid
  testPrecondition( outgoing_energy <= incoming_energy );
  testPrecondition( outgoing_energy >= 0.0 );
  // Make sure the scattering angle is valid
  testPrecondition( scattering_angle_cosine >= -1.0 );
  testPrecondition( scattering_angle_cosine <= 1.0 );

  // Calculate the electron momentum projection
  const ComptonProfile::MomentumQuantity electron_momentum_projection = 
    Utility::Units::mec_momentum*
    calculateElectronMomentumProjection( incoming_energy,
                                         outgoing_energy,
                                         scattering_angle_cosine );

  // Evaluate the multiplier
  const double multiplier = this->evaluateMultiplier(incoming_energy,
                                                     scattering_angle_cosine );

  // The total double differential cross section
  double cross_section = 0.0;

  // Evaluate each subshell
  for( unsigned i = 0; i < d_old_subshell_binding_energy.size(); ++i )
  {
    // Get the subshell binding energy
    const double subshell_binding_energy = d_old_subshell_binding_energy[i];

    // Get the subshell occupancy
    const double subshell_occupancy = d_old_subshell_occupancies[i];

    // Get the subshell Compton profile
    const ComptonProfile& compton_profile = this->getComptonProfile( i );

    if( outgoing_energy <= incoming_energy - subshell_binding_energy )
    {
      cross_section += subshell_occupancy*
        ComptonProfilePolicy::evaluate( compton_profile,
                                        electron_momentum_projection ).value();
    }
  }

  cross_section *= multiplier;

  // Make sure the cross section is valid
  testPostcondition( cross_section >= 0.0 );

  return cross_section;
}

// Evaluate the distribution
template<typename ComptonProfilePolicy>
double DecoupledStandardCompleteDopplerBroadenedPhotonEnergyDistribution<ComptonProfilePolicy>::evaluateIntegratedCrossSection( 
                                         const double incoming_energy,
                                         const double scattering_angle_cosine,
                                         const double precision ) const
{
  // Make sure the incoming energy is valid
  testPrecondition( incoming_energy > 0.0 );
  // Make sure the scattering angle is valid
  testPrecondition( scattering_angle_cosine >= -1.0 );
  testPrecondition( scattering_angle_cosine <= 1.0 );

  boost::function<double (double x)> double_diff_cs_wrapper = 
    boost::bind<double>( &DecoupledStandardCompleteDopplerBroadenedPhotonEnergyDistribution::evaluate,
                         boost::cref( *this ),
                         incoming_energy,
                         _1,
                         scattering_angle_cosine );

  double abs_error, diff_cs;

  Utility::GaussKronrodIntegrator<double> quadrature_set( precision );

  quadrature_set.integrateAdaptively<15>( double_diff_cs_wrapper,
                                          0.0,
                                          incoming_energy,
                                          diff_cs,
                                          abs_error );

  // Make sure that the differential cross section is valid
  testPostcondition( diff_cs >= 0.0 );

  return diff_cs;                         
}

// Sample an interaction subshell
/*! \details The old subshell index used to select the Compton profile and
 * and the binding energy is not the same as the subshell (each are sampled
 * separately - i.e. they are decoupled).
 */
template<typename ComptonProfilePolicy>
void DecoupledStandardCompleteDopplerBroadenedPhotonEnergyDistribution<ComptonProfilePolicy>::sampleInteractionSubshell( 
                                               unsigned& old_subshell_index,
                                               double& subshell_binding_energy,
                                               Data::SubshellType& subshell ) const
{
  old_subshell_index = this->sampleOldInteractionSubshell();

  subshell_binding_energy = d_old_subshell_binding_energy[old_subshell_index];

  subshell = this->sampleENDFInteractionSubshell();
}

// Sample the old subshell that is interacted with
template<typename ComptonProfilePolicy>
unsigned DecoupledStandardCompleteDopplerBroadenedPhotonEnergyDistribution<ComptonProfilePolicy>::sampleOldInteractionSubshell() const
{
  unsigned old_subshell_of_interaction;
  
  d_old_subshell_occupancy_distribution->sampleAndRecordBinIndex( 
                                                 old_subshell_of_interaction );

  return old_subshell_of_interaction;
}

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_DECOUPLED_STANDARD_COMPLETE_DOPPLER_BROADENED_PHOTON_ENERGY_DISTRIBUTION_DEF_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_DecoupledStandardCompleteDopplerBroadenedPhotonEnergyDistribution_def.hpp
//---------------------------------------------------------------------------//
