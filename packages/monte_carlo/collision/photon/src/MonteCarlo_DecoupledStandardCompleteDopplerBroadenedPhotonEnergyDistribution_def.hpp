//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_DecoupledStandardCompleteDopplerBroadenedPhotonEnergyDistribution_def.hpp
//! \author Alex Robinson
//! \brief  The decoupled complete Doppler broadened photon energy dist. def.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_DECOUPLED_STANDARD_COMPLETE_DOPPLER_BROADENED_PHOTON_ENERGY_DISTRIBUTION_DEF_HPP
#define MONTE_CARLO_DECOUPLED_STANDARD_COMPLETE_DOPPLER_BROADENED_PHOTON_ENERGY_DISTRIBUTION_DEF_HPP

// Std Lib Includes
#include <algorithm>

// Boost Includes
#include <boost/function.hpp>
#include <boost/bind.hpp>

// FRENSIE Includes
#include "MonteCarlo_DecoupledStandardCompleteDopplerBroadenedPhotonEnergyDistribution.hpp"
#include "Utility_GaussKronrodIntegrator.hpp"
#include "Utility_DiscreteDistribution.hpp"
#include "Utility_ExplicitTemplateInstantiationMacros.hpp"
#include "Utility_DesignByContract.hpp"

namespace MonteCarlo{

// Constructor
/*! \details The Compton profile grids must be in me*c units (not atomic
 * units). The Compton profiles must be in inverse me*c units (not inverse
 * atomic units). Only half profiles should be provided (grid ranges from 0.0
 * to 1.0).
 */
template<typename ComptonProfilePolicy>
DecoupledStandardCompleteDopplerBroadenedPhotonEnergyDistribution<ComptonProfilePolicy>::DecoupledStandardCompleteDopplerBroadenedPhotonEnergyDistribution(
   const std::vector<double>& endf_subshell_occupancies,
   const std::vector<Data::SubshellType>& endf_subshell_order,
   const std::vector<double>& old_subshell_binding_energies,
   const std::vector<double>& old_subshell_occupancies,
   const std::shared_ptr<const ComptonProfileSubshellConverter>&
   subshell_converter,
   const CompleteDopplerBroadenedPhotonEnergyDistribution::ComptonProfileArray&
   compton_profile_array )
  : StandardCompleteDopplerBroadenedPhotonEnergyDistribution<ComptonProfilePolicy>(
                                                     endf_subshell_occupancies,
                                                     endf_subshell_order,
                                                     subshell_converter,
                                                     compton_profile_array ),
  d_old_subshell_occupancy_distribution(),
  d_old_subshell_binding_energy( old_subshell_binding_energies ),
  d_old_subshell_occupancies( old_subshell_occupancies ),
  d_min_binding_energy_index( 0 )
{
  // Make sure the old shell data is valid
  testPrecondition( old_subshell_binding_energies.size() > 0 );
  testPrecondition( old_subshell_occupancies.size() ==
		    old_subshell_binding_energies.size() );
  // Make sure the comptron profile array is valid
  testPrecondition( compton_profile_array.size() ==
		    old_subshell_binding_energies.size() );

  // Create the old subshell interaction distribution
  std::vector<double> dummy_indep_vals( old_subshell_occupancies.size() );

  d_old_subshell_occupancy_distribution.reset(
	       new Utility::DiscreteDistribution( dummy_indep_vals,
					          old_subshell_occupancies ) );

  // Calculate the min binding energy index
  std::vector<double>::iterator min_binding_energy_it =
    std::min_element( d_old_subshell_binding_energy.begin(),
                      d_old_subshell_binding_energy.end() );

  d_min_binding_energy_index =
    std::distance( d_old_subshell_binding_energy.begin(),
                   min_binding_energy_it );
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

// Return the occupancy of a subshell (default is the ENDF occupancy)
template<typename ComptonProfilePolicy>
double DecoupledStandardCompleteDopplerBroadenedPhotonEnergyDistribution<ComptonProfilePolicy>::getSubshellOccupancy(
                                            const Data::SubshellType subshell ) const
{
  // Make sure the subshell is valid
  testPrecondition( this->isValidSubshell( subshell ) );

  unsigned old_subshell_index = this->getOldSubshellIndex( subshell );

  return d_old_subshell_occupancies[old_subshell_index];
}

// Evaluate the distribution with electron momentum projection
/*! \details Because the old subshell binding energies and subshell occupancy
 * data are used the procedure for evaluating the total cross section must be
 * changed. The electron momentum projection must be in me*c units 
 * (a momentum value of me*c kg*m/s is 1.0 in me*c units). The distribution
 * will have units of barns since the unitless momentum is being used.
 */
template<typename ComptonProfilePolicy>
double DecoupledStandardCompleteDopplerBroadenedPhotonEnergyDistribution<ComptonProfilePolicy>::evaluateWithElectronMomentumProjection(
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

  // The total double differential cross section
  double cross_section = 0.0;

  // Evaluate each subshell
  for( unsigned i = 0; i < d_old_subshell_binding_energy.size(); ++i )
  {
    // Get the subshell binding energy
    const double subshell_binding_energy = d_old_subshell_binding_energy[i];

    // Calculate the max electron momentum projection
    ComptonProfile::MomentumQuantity max_electron_momentum_projection =
      calculateMaxElectronMomentumProjection( incoming_energy,
                                              subshell_binding_energy,
                                              scattering_angle_cosine )*
    ComptonProfile::MomentumUnit();

    // Get the subshell occupancy
    const double subshell_occupancy = d_old_subshell_occupancies[i];

    // Get the subshell Compton profile
    const ComptonProfile& compton_profile = this->getComptonProfile( i );

    cross_section += subshell_occupancy*
      ComptonProfilePolicy::evaluateWithPossibleLimit(
                   compton_profile,
                   electron_momentum_projection*ComptonProfile::MomentumUnit(),
                   max_electron_momentum_projection ).value();
  }

  cross_section *= this->evaluateMultiplier( incoming_energy,
                                             scattering_angle_cosine )*
    this->evaluateRelativisticTerm( incoming_energy,
                                    scattering_angle_cosine );

  // Make sure the cross section is valid
  testPostcondition( cross_section >= 0.0 );

  return cross_section;
}

// Evaluate the exact distribution
/*! \details Because the old subshell binding energies and subshell occupancy
 * data are used the procedure for evaluating the total cross section must be
 * changed. The distribution has units of barns/MeV.
 */
template<typename ComptonProfilePolicy>
double DecoupledStandardCompleteDopplerBroadenedPhotonEnergyDistribution<ComptonProfilePolicy>::evaluateExact(
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
    ComptonProfile::MomentumUnit()*
    calculateElectronMomentumProjection( incoming_energy,
                                         outgoing_energy,
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

  cross_section *= this->evaluateMultiplierExact( incoming_energy,
                                                  outgoing_energy,
                                                  scattering_angle_cosine )*
    this->evaluateRelativisticTermExact( incoming_energy,
                                         outgoing_energy,
                                         scattering_angle_cosine );

  // Make sure the cross section is valid
  testPostcondition( cross_section >= 0.0 );

  return cross_section;
}

// Evaluate the integrated cross section
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
    boost::bind<double>( &DecoupledStandardCompleteDopplerBroadenedPhotonEnergyDistribution::evaluateWithElectronMomentumProjection,
                         boost::cref( *this ),
                         incoming_energy,
                         _1,
                         scattering_angle_cosine );

  // Get the min subshell binding energy
  const double subshell_binding_energy =
      d_old_subshell_binding_energy[d_min_binding_energy_index];

  // Get the subshell Compton profile
  const ComptonProfile& compton_profile =
    this->getComptonProfile( d_min_binding_energy_index );

  // Calculate the max electron momentum projection
  double pz_max =
    calculateMaxElectronMomentumProjection( incoming_energy,
                                            subshell_binding_energy,
                                            scattering_angle_cosine );

  // Don't go above the table max (profile will evaluate to zero beyond it)
  pz_max = ComptonProfilePolicy::getUpperLimitOfIntegration(
                               compton_profile,
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

  // Evaluate the exact integrated cross section
template<typename ComptonProfilePolicy>
double DecoupledStandardCompleteDopplerBroadenedPhotonEnergyDistribution<ComptonProfilePolicy>::evaluateIntegratedCrossSectionExact( 
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
    boost::bind<double>( &DecoupledStandardCompleteDopplerBroadenedPhotonEnergyDistribution::evaluateExact,
                         boost::cref( *this ),
                         incoming_energy,
                         _1,
                         scattering_angle_cosine );
    

  // Get the min subshell binding energy
  const double subshell_binding_energy =
    d_old_subshell_binding_energy[d_min_binding_energy_index];

  // Calculate the max energy
  double energy_max = incoming_energy - subshell_binding_energy;

  // Calculate the max electron momentum projection
  double pz_max =
    calculateMaxElectronMomentumProjection( incoming_energy,
                                            subshell_binding_energy,
                                            scattering_angle_cosine );

  // Get the subshell Compton profile
  const ComptonProfile& compton_profile =
    this->getComptonProfile( d_min_binding_energy_index );

  // Calculate the max table energy
  const double pz_table_max =
    ComptonProfilePolicy::getUpperBoundOfMomentum( compton_profile ).value();

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

// Sample an interaction subshell
/*! \details The old subshell index used to select the Compton profile and
 * and the binding energy is not the same as the subshell (each are sampled
 * separately - i.e. they are decoupled).
 */
template<typename ComptonProfilePolicy>
void DecoupledStandardCompleteDopplerBroadenedPhotonEnergyDistribution<ComptonProfilePolicy>::sampleInteractionSubshell(
                                           size_t& old_subshell_index,
                                           double& subshell_binding_energy,
                                           Data::SubshellType& subshell ) const
{
  old_subshell_index = this->sampleOldInteractionSubshell();

  subshell_binding_energy = d_old_subshell_binding_energy[old_subshell_index];

  subshell = this->sampleENDFInteractionSubshell();
}

// Sample the old subshell that is interacted with
template<typename ComptonProfilePolicy>
size_t DecoupledStandardCompleteDopplerBroadenedPhotonEnergyDistribution<ComptonProfilePolicy>::sampleOldInteractionSubshell() const
{
  size_t old_subshell_of_interaction;

  d_old_subshell_occupancy_distribution->sampleAndRecordBinIndex(
                                                 old_subshell_of_interaction );

  return old_subshell_of_interaction;
}

EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( DecoupledStandardCompleteDopplerBroadenedPhotonEnergyDistribution<FullComptonProfilePolicy> );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( DecoupledStandardCompleteDopplerBroadenedPhotonEnergyDistribution<HalfComptonProfilePolicy> );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( DecoupledStandardCompleteDopplerBroadenedPhotonEnergyDistribution<DoubledHalfComptonProfilePolicy> );

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_DECOUPLED_STANDARD_COMPLETE_DOPPLER_BROADENED_PHOTON_ENERGY_DISTRIBUTION_DEF_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_DecoupledStandardCompleteDopplerBroadenedPhotonEnergyDistribution_def.hpp
//---------------------------------------------------------------------------//
