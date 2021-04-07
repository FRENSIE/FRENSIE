//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_StandardSubshellDopplerBroadenedPhotonEnergyDistribution_def.hpp
//! \author Alex Robinson
//! \brief  The standard subshell Doppler broadened photon energy distribution
//!         def.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_STANDARD_SUBSHELL_DOPPLER_BROADENED_PHOTON_ENERGY_DISTRIBUTION_DEF_HPP
#define MONTE_CARLO_STANDARD_SUBSHELL_DOPPLER_BROADENED_PHOTON_ENERGY_DISTRIBUTION_DEF_HPP

// Boost Includes
#include <boost/function.hpp>
#include <boost/bind.hpp>

// FRENSIE Includes
#include "MonteCarlo_PhotonKinematicsHelpers.hpp"
#include "Utility_GaussKronrodIntegrator.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_ExplicitTemplateInstantiationMacros.hpp"
#include "Utility_DesignByContract.hpp"

namespace MonteCarlo{

// Constructor
template<typename ComptonProfilePolicy>
StandardSubshellDopplerBroadenedPhotonEnergyDistribution<ComptonProfilePolicy>::StandardSubshellDopplerBroadenedPhotonEnergyDistribution(
		 const Data::SubshellType interaction_subshell,
		 const double subshell_occupancy,
		 const double subshell_binding_energy,
		 const std::shared_ptr<const ComptonProfile>& compton_profile )
  : SubshellDopplerBroadenedPhotonEnergyDistribution(interaction_subshell,
                                                     subshell_occupancy,
                                                     subshell_binding_energy ),
    d_compton_profile( compton_profile )
{
  // Make sure the interaction subshell is valid
  testPrecondition( interaction_subshell != Data::INVALID_SUBSHELL &&
                    interaction_subshell !=Data::UNKNOWN_SUBSHELL );
  // Make sure the subshell occupancy is valid
  testPrecondition( subshell_occupancy > 0.0 );
  // Make sure the subshell binding energy is valid
  testPrecondition( subshell_binding_energy > 0.0 );
  // Make sure the Compton profile is valid
  testPrecondition( compton_profile.get() );
  testPrecondition( ComptonProfilePolicy::isValidProfile( *compton_profile ) );
}

// Evaluate the distribution
/*! \details The electron momentum projection must be in me*c units 
 * (a momentum value of me*c kg*m/s is 1.0 in me*c units). The distribution
 * will have units of barns since the unitless momentum is being used.
 */
template<typename ComptonProfilePolicy>
double StandardSubshellDopplerBroadenedPhotonEnergyDistribution<ComptonProfilePolicy>::evaluateWithElectronMomentumProjection(
                              const double incoming_energy,
                              const double electron_momentum_projection,
                              const double scattering_angle_cosine ) const
{
  // Make sure the incoming energy is valid
  testPrecondition( incoming_energy > 0.0 );
  // Make sure the electron momentum projection is valid
  testPrecondition( electron_momentum_projection >= -1.0 );
  // Make sure the scattering angle is valid
  testPrecondition( scattering_angle_cosine >= -1.0 );
  testPrecondition( scattering_angle_cosine <= 1.0 );

  // Calculate the max electron momentum projection
  ComptonProfile::MomentumQuantity max_electron_momentum_projection =
    calculateMaxElectronMomentumProjection( incoming_energy,
                                            this->getSubshellBindingEnergy(),
                                            scattering_angle_cosine )*
    ComptonProfile::MomentumUnit();

  // Evaluate the Compton profile
  ComptonProfile::ProfileQuantity compton_profile_quantity = 
    ComptonProfilePolicy::evaluateWithPossibleLimit(
                   *d_compton_profile,
                   electron_momentum_projection*ComptonProfile::MomentumUnit(),
                   max_electron_momentum_projection );

  // Evaluate the cross section
  const double multiplier = this->evaluateMultiplier(incoming_energy,
                                                     scattering_angle_cosine );

  const double relativistic_term = this->evaluateRelativisticTerm(
                                                     incoming_energy,
                                                     scattering_angle_cosine );

  const double cross_section =
    multiplier*relativistic_term*this->getSubshellOccupancy()*
    compton_profile_quantity.value();

  // Make sure the cross section is valid
  testPostcondition( cross_section >= 0.0 );

  return cross_section;
}

// Evaluate the distribution
/*! \details The distribution has units of barns/MeV.
 */
template<typename ComptonProfilePolicy>
double StandardSubshellDopplerBroadenedPhotonEnergyDistribution<ComptonProfilePolicy>::evaluateExact( 
				   const double incoming_energy,
				   const double outgoing_energy,
				   const double scattering_angle_cosine ) const
{
  // Make sure the incoming energy is valid
  testPrecondition( incoming_energy > 0.0 );
  // Make sure the scattering angle is valid
  testPrecondition( scattering_angle_cosine >= -1.0 );
  testPrecondition( scattering_angle_cosine <= 1.0 );

  // The evaluated double differential cross section
  double cross_section;

  if( outgoing_energy <= incoming_energy - this->getSubshellBindingEnergy() )
  {
    // Calculate the electron momentum projection
    const ComptonProfile::MomentumQuantity electron_momentum_projection = 
      ComptonProfile::MomentumUnit()*
      calculateElectronMomentumProjection( incoming_energy,
                                           outgoing_energy,
                                           scattering_angle_cosine );

    // Evaluate the Compton profile
    ComptonProfile::ProfileQuantity compton_profile_quantity =
      ComptonProfilePolicy::evaluate( *d_compton_profile,
                                      electron_momentum_projection );

    // Evaluate the cross section
    const double multiplier = this->evaluateMultiplierExact(
                                                     incoming_energy,
                                                     outgoing_energy,
                                                     scattering_angle_cosine );

    const double relativistic_term = this->evaluateRelativisticTermExact(
                                                     incoming_energy,
                                                     outgoing_energy,
                                                     scattering_angle_cosine );

    cross_section = multiplier*relativistic_term*this->getSubshellOccupancy()*
      compton_profile_quantity.value();
  }
  else
    cross_section = 0.0;

  // Make sure the cross section is valid
  testPostcondition( cross_section >= 0.0 );

  return cross_section;
}

// Evaluate the PDF with electron momentum projection
/*! \details The electron momentum projection must be in me*c units 
 * (a momentum value of me*c kg*m/s is 1.0 in me*c units). The PDF
 * will be unitless since the unitless momentum is being used.
 */
template<typename ComptonProfilePolicy>
double StandardSubshellDopplerBroadenedPhotonEnergyDistribution<ComptonProfilePolicy>::evaluatePDFWithElectronMomentumProjection(
                              const double incoming_energy,
                              const double electron_momentum_projection,
                              const double scattering_angle_cosine,
                              const double precision ) const
{
  const double diff_cross_section =
    this->evaluateWithElectronMomentumProjection( incoming_energy,
                                                  electron_momentum_projection,
                                                  scattering_angle_cosine );

  const double integrated_cross_section =
    this->evaluateIntegratedCrossSection( incoming_energy,
                                          scattering_angle_cosine,
                                          precision );

  if( integrated_cross_section > 0.0 )
    return diff_cross_section/integrated_cross_section;
  else
    return 0.0;
}

// Evaluate the PDF
/*! \details The PDF has units of inverse MeV.
 */
template<typename ComptonProfilePolicy>
double StandardSubshellDopplerBroadenedPhotonEnergyDistribution<ComptonProfilePolicy>::evaluatePDFExact( 
			           const double incoming_energy,
				   const double outgoing_energy,
			           const double scattering_angle_cosine,
                                   const double precision ) const
{
  const double diff_cross_section =
    this->evaluateExact( incoming_energy,
                         outgoing_energy,
                         scattering_angle_cosine );
  
  const double integrated_cross_section =
    this->evaluateIntegratedCrossSectionExact( incoming_energy,
                                               scattering_angle_cosine,
                                               precision );

  if( integrated_cross_section > 0.0 )
    return diff_cross_section/integrated_cross_section;
  else
    return 0.0;
}

// Evaluate the integrated cross section (b/mu)
template<typename ComptonProfilePolicy>
double StandardSubshellDopplerBroadenedPhotonEnergyDistribution<ComptonProfilePolicy>::evaluateIntegratedCrossSection(
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
    boost::bind<double>( &StandardSubshellDopplerBroadenedPhotonEnergyDistribution::evaluateWithElectronMomentumProjection,
                         boost::cref( *this ),
                         incoming_energy,
                         _1,
                         scattering_angle_cosine );

  // Get the subshell binding energy
  const double binding_energy = this->getSubshellBindingEnergy();

  // Calculate the max electron momentum projection
  double pz_max =
    calculateMaxElectronMomentumProjection( incoming_energy,
                                            binding_energy,
                                            scattering_angle_cosine );

  // Don't go above the table max (profile will evaluate to zero beyond it)
  pz_max = ComptonProfilePolicy::getUpperLimitOfIntegration(
                               *d_compton_profile,
                               pz_max*ComptonProfile::MomentumUnit() ).value();

  // Calculate the min electron momentum projection
  double pz_min = ComptonProfilePolicy::getLowerLimitOfIntegration(
                               pz_max*ComptonProfile::MomentumUnit() ).value();

  // Calculate the absolute error and the integrated cross section
  double abs_error, diff_cs;
  
  Utility::GaussKronrodIntegrator<double> quadrature_set( precision );

  if( pz_min < pz_max )
  {
    quadrature_set.integrateAdaptively<15>( double_diff_cs_wrapper,
                                            pz_min,
                                            pz_max,
                                            diff_cs,
                                            abs_error );
  }
  else
  {
    abs_error = 0.0;
    diff_cs = 0.0;
  }

  // Make sure that the differential cross section is valid
  testPostcondition( diff_cs >= 0.0 );

  return diff_cs;
}

// Evaluate the exact integrated cross section (b/mu)
template<typename ComptonProfilePolicy>
double StandardSubshellDopplerBroadenedPhotonEnergyDistribution<ComptonProfilePolicy>::evaluateIntegratedCrossSectionExact( 
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
    boost::bind<double>( &StandardSubshellDopplerBroadenedPhotonEnergyDistribution::evaluateExact,
                         boost::cref( *this ),
                         incoming_energy,
                         _1,
                         scattering_angle_cosine );

  // Calculate the max energy
  double energy_max = incoming_energy - this->getSubshellBindingEnergy();

  // Calculate the max electron momentum projection
  double pz_max =
    calculateMaxElectronMomentumProjection( incoming_energy,
                                            this->getSubshellBindingEnergy(),
                                            scattering_angle_cosine );

  // Calculate the max table energy
  const double pz_table_max =
    ComptonProfilePolicy::getUpperBoundOfMomentum(*d_compton_profile).value();

  // Don't go above the table max (profile will evaluate to zero beyond it)
  if( pz_max > pz_table_max )
  {
    bool energetically_possible;
    
    energy_max = calculateDopplerBroadenedEnergy( pz_table_max,
                                                  incoming_energy,
                                                  scattering_angle_cosine,
                                                  energetically_possible );
  }

  // Calculate the absolute error and the integrated cross section
  double abs_error, diff_cs;

  Utility::GaussKronrodIntegrator<double> quadrature_set( precision );

  quadrature_set.integrateAdaptively<15>( double_diff_cs_wrapper,
                                          0.0,
                                          energy_max,
                                          diff_cs,
                                          abs_error );

  // Make sure that the differential cross section is valid
  testPostcondition( diff_cs >= 0.0 );

  return diff_cs;
}

// Sample an outgoing energy from the distribution
template<typename ComptonProfilePolicy>
void StandardSubshellDopplerBroadenedPhotonEnergyDistribution<ComptonProfilePolicy>::sample(
				     const double incoming_energy,
				     const double scattering_angle_cosine,
				     double& outgoing_energy,
				     Data::SubshellType& shell_of_interaction ) const
{
  Counter trial_dummy;

  this->sampleAndRecordTrials( incoming_energy,
			       scattering_angle_cosine,
			       outgoing_energy,
			       shell_of_interaction,
			       trial_dummy );
}

// Sample an outgoing energy and record the number of trials
template<typename ComptonProfilePolicy>
void StandardSubshellDopplerBroadenedPhotonEnergyDistribution<ComptonProfilePolicy>::sampleAndRecordTrials(
                                      const double incoming_energy,
                                      const double scattering_angle_cosine,
                                      double& outgoing_energy,
				      Data::SubshellType& shell_of_interaction,
                                      Counter& trials ) const
{
  // Make sure the incoming energy is valid
  testPrecondition( incoming_energy >= this->getSubshellBindingEnergy() );
  // Make sure the scattering angle cosine is valid
  testPrecondition( scattering_angle_cosine >= -1.0 );
  testPrecondition( scattering_angle_cosine <= 1.0 );

  // Calculate the max electron momentum projection
  ComptonProfile::MomentumQuantity pz_max = ComptonProfile::MomentumUnit()*
    calculateMaxElectronMomentumProjection( incoming_energy,
					    this->getSubshellBindingEnergy(),
					    scattering_angle_cosine );

  // Calculate the doppler broadened energy
  bool energetically_possible = false;

  while( !energetically_possible )
  {
    double pz;

    this->sampleMomentumAndRecordTrials( incoming_energy,
                                         scattering_angle_cosine,
                                         pz,
                                         shell_of_interaction,
                                         trials );

    outgoing_energy = calculateDopplerBroadenedEnergy(pz,
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
void StandardSubshellDopplerBroadenedPhotonEnergyDistribution<ComptonProfilePolicy>::sampleMomentumAndRecordTrials(
                                      const double incoming_energy,
                                      const double scattering_angle_cosine,
                                      double& electron_momentum_projection,
                                      Data::SubshellType& shell_of_interaction,
                                      Counter& trials ) const
{
  // Make sure the incoming energy is valid
  testPrecondition( incoming_energy >= this->getSubshellBindingEnergy() );
  // Make sure the scattering angle cosine is valid
  testPrecondition( scattering_angle_cosine >= -1.0 );
  testPrecondition( scattering_angle_cosine <= 1.0 );

  ++trials;

  // Calculate the max electron momentum projection
  ComptonProfile::MomentumQuantity pz_max = ComptonProfile::MomentumUnit()*
    calculateMaxElectronMomentumProjection( incoming_energy,
					    this->getSubshellBindingEnergy(),
					    scattering_angle_cosine );

  // Calculate the doppler broadened energy
  ComptonProfile::MomentumQuantity pz =
    ComptonProfilePolicy::sample( *d_compton_profile, pz_max );

  electron_momentum_projection = pz.value();

  shell_of_interaction = this->getSubshell();
}

EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( StandardSubshellDopplerBroadenedPhotonEnergyDistribution<FullComptonProfilePolicy> );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( StandardSubshellDopplerBroadenedPhotonEnergyDistribution<HalfComptonProfilePolicy> );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( StandardSubshellDopplerBroadenedPhotonEnergyDistribution<DoubledHalfComptonProfilePolicy> );

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_STANDARD_SUBSHELL_DOPPLER_BROADENED_PHOTON_ENERGY_DISTRIBUTION_DEF_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_StandardSubshellDopplerBroadenedPhotonEnergyDistribution_def.hpp
//---------------------------------------------------------------------------//
