//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_SubshellDopplerBroadenedPhotonEnergyDistribution_def.hpp
//! \author Alex Robinson
//! \brief  The subshell Doppler broadened photon energy distribution def.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_SUBSHELL_DOPPLER_BROADENED_PHOTON_ENERGY_DISTRIBUTION_DEF_HPP
#define MONTE_CARLO_SUBSHELL_DOPPLER_BROADENED_PHOTON_ENERGY_DISTRIBUTION_DEF_HPP

// Boost Includes
#include <boost/function.hpp>
#include <boost/bind.hpp>

// FRENSIE Includes
#include "MonteCarlo_SubshellDopplerBroadenedPhotonEnergyDistribution.hpp"
#include "MonteCarlo_PhotonKinematicsHelpers.hpp"
#include "Utility_GaussKronrodQuadratureSet.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Constructor
/*! \details The occupation number and Compton profile grid be in me*c units.
 * The Compton profile must be in inverse me*c units.
 */
template<typename ComptonProfilePolicy>
SubshellDopplerBroadenedPhotonEnergyDistribution<ComptonProfilePolicy>::SubshellDopplerBroadenedPhotonEnergyDistribution(
		 const SubshellType interaction_subshell,
		 const double subshell_occupancy,
		 const double subshell_binding_energy,
		 const std::shared_ptr<const ComptonProfile>&
		 compton_profile )
  : d_interaction_subshell( interaction_subshell ),
    d_subshell_occupancy( subshell_occupancy ),
    d_subshell_binding_energy( subshell_binding_energy ),
    d_compton_profile( compton_profile )
{
  // Make sure the interaction subshell is valid
  testPrecondition( interaction_subshell != INVALID_SUBSHELL &&
                    interaction_subshell != UNKNOWN_SUBSHELL );
  // Make sure the subshell occupancy is valid
  testPrecondition( subshell_occupancy > 0.0 );
  // Make sure the subshell binding energy is valid
  testPrecondition( subshell_binding_energy > 0.0 );
  // Make sure the Compton profile is valid
  testPrecondition( compton_profile.get() );
}

// Return the subshell
template<typename ComptonProfilePolicy>
SubshellType SubshellDopplerBroadenedPhotonEnergyDistribution<ComptonProfilePolicy>::getSubshell() const
{
  return d_interaction_subshell;
}
  
// Return the number of electrons in the subshell
template<typename ComptonProfilePolicy>
double SubshellDopplerBroadenedPhotonEnergyDistribution<ComptonProfilePolicy>::getSubshellOccupancy() const
{
  return d_subshell_occupancy;
}

// Return the binding energy
template<typename ComptonProfilePolicy>
double SubshellDopplerBroadenedPhotonEnergyDistribution<ComptonProfilePolicy>::getSubshellBindingEnergy() const
{
  return d_subshell_binding_energy;
}

// Evaluate the distribution
template<typename ComptonProfilePolicy>
double SubshellDopplerBroadenedPhotonEnergyDistribution<ComptonProfilePolicy>::evaluate( 
				   const double incoming_energy,
				   const double outgoing_energy,
				   const double scattering_angle_cosine ) const
{
  // Make sure the incoming energy is valid
  testPrecondition( incoming_energy > 0.0 );
  // Make sure the outgoing energy is valid
  testPrecondition( outgoing_energy <= 
                    incoming_energy - d_subshell_binding_energy );
  // Make sure the scattering angle is valid
  testPrecondition( scattering_angle_cosine >= -1.0 );
  testPrecondition( scattering_angle_cosine <= 1.0 );

  // The evaluated double differential cross section
  double cross_section;

  if( outgoing_energy < incoming_energy - d_subshell_binding_energy )
  {
    // Calculate the electron momentum projection
    const ComptonProfile::MomentumQuantity electron_momentum_projection = 
      Utility::Units::mec_momentum*
      calculateElectronMomentumProjection( incoming_energy,
                                           outgoing_energy,
                                           scattering_angle_cosine );

    // Evaluate the Compton profile
    ComptonProfile::ProfileQuantity compton_profile_quantity = 
      ComptonProfilePolicy::evaluate( d_compton_profile,
                                      electron_momentum_projection );

    // Evaluate the cross section
    const double multiplier = this->evaluateMultiplier(
                                                     incoming_energy,
                                                     scattering_angle_cosine );

    cross_section = multiplier*d_subshell_occupancy*
      compton_profile_quantity.value();
  }
  else
    cross_section = 0.0;

  // Make sure the cross section is valid
  testPostcondition( cross_section >= 0.0 );
  
  return cross_section;
}

// Evaluate the PDF
template<typename ComptonProfilePolicy>
double SubshellDopplerBroadenedPhotonEnergyDistribution<ComptonProfilePolicy>::evaluatePDF( 
			           const double incoming_energy,
				   const double outgoing_energy,
			           const double scattering_angle_cosine ) const
{
  return this->evaluate( incoming_energy,
                         outgoing_energy,
                         scattering_angle_cosine )/
    this->evaluateIntegratedCrossSection( incoming_energy,
                                          scattering_angle_cosine,
                                          1e-3 );
}

// Evaluate the integrated cross section (b/mu)
template<typename ComptonProfilePolicy>
double SubshellDopplerBroadenedPhotonEnergyDistribution<ComptonProfilePolicy>::evaluateIntegratedCrossSection( 
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
    boost::bind<double>( &SubshellDopplerBroadenedPhotonEnergyDistribution::evaluate,
                         boost::cref( *this ),
                         incoming_energy,
                         _1,
                         scattering_angle_cosine );
  
  double abs_error, diff_cs;
  
  const double binding_energy = this->getSubshellBindingEnergy( subshell );

  Utility::GausKronrodQuandratureSet quadrature_set( precision );

  quadrature_set.integrateAdaptively<15>( double_diff_cs_wrapper,
                                          0.0,
                                          incoming_energy - d_subshell_binding_energy,
                                          diff_cs,
                                          abs_error );

  // Make sure that the differential cross section is valid
  testPostcondition( diff_cs >= 0.0 );

  return diff_cs;
}

// Sample an outgoing energy from the distribution
template<typename ComptonProfilePolicy>
void SubshellDopplerBroadenedPhotonEnergyDistribution<ComptonProfilePolicy>::sample( 
				     const double incoming_energy,
				     const double scattering_angle_cosine,
				     double& outgoing_energy,
				     SubshellType& shell_of_interaction ) const
{
  unsigned trial_dummy;

  this->sampleAndRecordTrials( incoming_energy,
			       scattering_angle_cosine,
			       outgoing_energy,
			       shell_of_interaction,
			       trial_dummy );
}

// Sample an outgoing energy and record the number of trials
template<typename ComptonProfilePolicy>
void SubshellDopplerBroadenedPhotonEnergyDistribution<ComptonProfilePolicy>::sampleAndRecordTrials( 
				          const double incoming_energy,
					  const double scattering_angle_cosine,
					  double& outgoing_energy,
					  SubshellType& shell_of_interaction,
					  unsigned& trials ) const
{
  // Make sure the incoming energy is valid
  testPrecondition( incoming_energy >= d_subshell_binding_energy );
  // Make sure the scattering angle cosine is valid
  testPrecondition( scattering_angle_cosine >= -1.0 );
  testPrecondition( scattering_angle_cosine <= 1.0 );

  // Calculate the max electron momentum projection
  ComptonProfile::MomentumQuantity pz_max = Utility::Units::mec_momentum*
    calculateMaxElectronMomentumProjection( incoming_energy,
					    d_subshell_binding_energy,
					    scattering_angle_cosine );

  // Calculate the doppler broadened energy
  bool energetically_possible = false;

  while( !energetically_possible )
  {
    this->sampleMomentumAndRecordTrials( incoming_energy,
                                         scattering_angle_cosine,
                                         electron_momentum_projection,
                                         shell_of_interaction,
                                         trials );
    
    outgoing_energy = calculateDopplerBroadenedEnergy(pz.value(),
						      incoming_energy,
						      scattering_angle_cosine,
						      energetically_possible );
  }

  // An energy of zero is not allowed in the rest of the code
  if( outgoing_energy == 0.0 )
    outgoing_energy = std::numeric_limits<double>::min();

  // Make sure the outgoing energy is valid
  testPostcondition( energetically_possible );
  testPostcondition( outgoing_energy >= 0.0 );
}

// Sample an electron momentum projection and record the number of trials
template<typename ComptonProfilePolicy>
void SubshellDopplerBroadenedPhotonEnergyDistribution<ComptonProfilePolicy>::sampleMomentumAndRecordTrials( 
                                      const double incoming_energy,
                                      const double scattering_angle_cosine,
                                      double& electron_momentum_projection,
                                      Subshell& shell_of_interaction,
                                      unsigned& trials ) const
{
  // Make sure the incoming energy is valid
  testPrecondition( incoming_energy >= d_subshell_binding_energy );
  // Make sure the scattering angle cosine is valid
  testPrecondition( scattering_angle_cosine >= -1.0 );
  testPrecondition( scattering_angle_cosine <= 1.0 );

  ++trials;

  // Calculate the max electron momentum projection
  ComptonProfile::MomentumQuantity pz_max = Utility::Units::mec_momentum*
    calculateMaxElectronMomentumProjection( incoming_energy,
					    d_subshell_binding_energy,
					    scattering_angle_cosine );

  // Calculate the doppler broadened energy
  ComptonProfile::MomentumQuantity pz = 
    ComptonProfilePolicy::sample( d_compton_profile, pz_max );

  electron_momentum_projection = pz.value();
    
  shell_of_interaction = d_interaction_subshell;
}

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_SUBSHELL_DOPPLER_BROADENED_PHOTON_ENERGY_DISTRIBUTION_DEF_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_SubshellDopplerBroadenedPhotonEnergyDistribution_def.hpp
//---------------------------------------------------------------------------//
