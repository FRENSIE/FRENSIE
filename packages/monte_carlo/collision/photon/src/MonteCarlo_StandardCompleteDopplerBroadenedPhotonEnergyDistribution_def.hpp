//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_StandardCompleteDopplerBroadenedPhotonEnergyDistribution_def.hpp
//! \author Alex Robinson
//! \brief  The complete Doppler broadened photon energy distribution def.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_STANDARD_COMPLETE_DOPPLER_BROADENED_PHOTON_ENERGY_DISTRIBUTION_DEF_HPP
#define MONTE_CARLO_STANDARD_COMPLETE_DOPPLER_BROADENED_PHOTON_ENERGY_DISTRIBUTION_DEF_HPP

// Boost Includes
#include <boost/function.hpp>
#include <boost/bind.hpp>

// FRENSIE Includes
#include "MonteCarlo_PhotonKinematicsHelpers.hpp"
#include "Utility_DiscreteDistribution.hpp"
#include "Utility_GaussKronrodIntegrator.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_ExplicitTemplateInstantiationMacros.hpp"
#include "Utility_DesignByContract.hpp"

namespace MonteCarlo{

// Constructor
template<typename ComptonProfilePolicy>
StandardCompleteDopplerBroadenedPhotonEnergyDistribution<ComptonProfilePolicy>::StandardCompleteDopplerBroadenedPhotonEnergyDistribution(
		const std::vector<double>& endf_subshell_occupancies,
                const std::vector<Data::SubshellType>& endf_subshell_order,
                const std::shared_ptr<const ComptonProfileSubshellConverter>&
                subshell_converter,
                const ComptonProfileArray& electron_momentum_dist_array )
  : d_endf_subshell_occupancy_distribution(),
    d_endf_subshell_order(),
    d_endf_subshell_occupancies( endf_subshell_occupancies ),
    d_subshell_converter( subshell_converter ),
    d_compton_profile_array( electron_momentum_dist_array )
{
  // Make sure the shell interaction data is valid
  testPrecondition( endf_subshell_occupancies.size() > 0 );
  testPrecondition( endf_subshell_order.size() ==
		    endf_subshell_occupancies.size() );
  // Make sure that the subshell converter is valid
  testPrecondition( subshell_converter.get() );
  // Make sure the comptron profile array is valid
  testPrecondition( electron_momentum_dist_array.size() > 0 );
  testPrecondition( ComptonProfilePolicy::isValidProfile( *electron_momentum_dist_array.front() ) );
  testPrecondition( ComptonProfilePolicy::isValidProfile( *electron_momentum_dist_array.back() ) );

  // Create the ENDF subshell interaction distribution
  std::vector<double> dummy_indep_vals( endf_subshell_occupancies.size() );

  d_endf_subshell_occupancy_distribution.reset(
	      new Utility::DiscreteDistribution( dummy_indep_vals,
						 endf_subshell_occupancies ) );

  // Create the endf subshell order bimap
  for( unsigned i = 0; i < endf_subshell_order.size(); ++i )
  {
    d_endf_subshell_order.insert( SubshellOrderMapType::value_type(
                                                 i, endf_subshell_order[i] ) );
  }
}

// Evaluate the distribution with the electron momentum projection
/*! \details The electron momentum projection must be in me*c units
 * (a momentum value of me*c kg*m/s is 1.0 in me*c units). The distribution
 * will have units of barns since the unitless momentum is being used.
 */
template<typename ComptonProfilePolicy>
double StandardCompleteDopplerBroadenedPhotonEnergyDistribution<ComptonProfilePolicy>::evaluateWithElectronMomentumProjection(
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
  SubshellOrderMapType::const_iterator subshell_it =
    d_endf_subshell_order.begin();

  while( subshell_it != d_endf_subshell_order.end() )
  {
    cross_section += this->evaluateSubshellWithElectronMomentumProjection(
                                                  incoming_energy,
                                                  electron_momentum_projection,
                                                  scattering_angle_cosine,
                                                  subshell_it->right );

    ++subshell_it;
  }

  // Make sure the cross section is valid
  testPrecondition( cross_section >= 0.0 );

  return cross_section;
}

// Evaluate the exact distribution
/*! \details The distribution has units of barns/MeV.
 */
template<typename ComptonProfilePolicy>
double StandardCompleteDopplerBroadenedPhotonEnergyDistribution<ComptonProfilePolicy>::evaluateExact(
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

  // The total double differential cross section
  double cross_section = 0.0;

  // Evaluate each subshell
  SubshellOrderMapType::const_iterator subshell_it =
    d_endf_subshell_order.begin();

  while( subshell_it != d_endf_subshell_order.end() )
  {
    cross_section += this->evaluateSubshellExact( incoming_energy,
                                                  outgoing_energy,
                                                  scattering_angle_cosine,
                                                  subshell_it->right );

    ++subshell_it;
  }

  // Make sure the cross section is valid
  testPostcondition( cross_section >= 0.0 );

  return cross_section;
}

// Evaluate the subshell distribution with the electron momentum projection
/*! \details The electron momentum projection must be in me*c units
 * (a momentum value of me*c kg*m/s is 1.0 in me*c units). The distribution
 * will have units of barns since the unitless momentum is being used.
 */
template<typename ComptonProfilePolicy>
double StandardCompleteDopplerBroadenedPhotonEnergyDistribution<ComptonProfilePolicy>::evaluateSubshellWithElectronMomentumProjection(
                                                                                                                     const double incoming_energy,
                                     const double electron_momentum_projection,
                                     const double scattering_angle_cosine,
                                     const Data::SubshellType subshell ) const
{
  // Make sure the incoming energy is valid
  testPrecondition( incoming_energy > 0.0 );
  // Make sure the electron momentum projection is valid
  testPrecondition( electron_momentum_projection >= -1.0 );
  // Make sure the scattering angle is valid
  testPrecondition( scattering_angle_cosine >= -1.0 );
  testPrecondition( scattering_angle_cosine <= 1.0 );
  // Make sure the subshell is valid
  testPrecondition( this->isValidSubshell( subshell ) );

  // Get the subshell binding energy
  const double subshell_binding_energy =
    this->getSubshellBindingEnergy( subshell );

  // Calculate the max electron momentum projection
  ComptonProfile::MomentumQuantity max_electron_momentum_projection =
    calculateMaxElectronMomentumProjection( incoming_energy,
                                            subshell_binding_energy,
                                            scattering_angle_cosine )*
    ComptonProfile::MomentumUnit();

  // Get the subshell occupancy
  const double subshell_occupancy =
    this->getSubshellOccupancy( subshell );

  // Get the Compton profile for the subshell
  const ComptonProfile& compton_profile =
    this->getComptonProfile( subshell );

  // Evaluate the Compton profile
  ComptonProfile::ProfileQuantity compton_profile_quantity =
    ComptonProfilePolicy::evaluateWithPossibleLimit(
                   compton_profile,
                   electron_momentum_projection*ComptonProfile::MomentumUnit(),
                   max_electron_momentum_projection );

  // Evaluate the cross section
  const double multiplier = this->evaluateMultiplier(incoming_energy,
                                                     scattering_angle_cosine );

  const double relativistic_term = this->evaluateRelativisticTerm(
                                                     incoming_energy,
                                                     scattering_angle_cosine );

  const double cross_section = multiplier*relativistic_term*subshell_occupancy*
    compton_profile_quantity.value();

  // Make sure the cross section is valid
  testPostcondition( cross_section >= 0.0 );

  return cross_section;
}

// Evaluate the exact subshell distribution
  /*! \details The distribution has units of barns/MeV.
 */
template<typename ComptonProfilePolicy>
double StandardCompleteDopplerBroadenedPhotonEnergyDistribution<ComptonProfilePolicy>::evaluateSubshellExact(
				      const double incoming_energy,
                                      const double outgoing_energy,
                                      const double scattering_angle_cosine,
				      const Data::SubshellType subshell ) const
{
  // Make sure the incoming energy is valid
  testPrecondition( incoming_energy > 0.0 );
  // Make sure the outgoing energy is valid
  testPrecondition( outgoing_energy <= incoming_energy );
  testPrecondition( outgoing_energy >= 0.0 );
  // Make sure the scattering angle is valid
  testPrecondition( scattering_angle_cosine >= -1.0 );
  testPrecondition( scattering_angle_cosine <= 1.0 );
  // Make sure the subshell is valid
  testPrecondition( this->isValidSubshell( subshell ) );

  // Get the subshell binding energy
  const double subshell_binding_energy =
    this->getSubshellBindingEnergy( subshell );

  // The evaluated double differential cross section
  double cross_section;

  if( outgoing_energy <= incoming_energy - subshell_binding_energy )
  {
    // Get the Compton profile for the subshell
    const ComptonProfile& compton_profile =
      this->getComptonProfile( subshell );

    // Get the subshell occupancy
    const double subshell_occupancy = this->getSubshellOccupancy( subshell );

    // Calculate the electron momentum projection
    const ComptonProfile::MomentumQuantity electron_momentum_projection =
      ComptonProfile::MomentumUnit()*
      calculateElectronMomentumProjection( incoming_energy,
                                           outgoing_energy,
                                           scattering_angle_cosine);

    // Evaluate the Compton profile
    ComptonProfile::ProfileQuantity compton_profile_quantity =
      ComptonProfilePolicy::evaluate( compton_profile,
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

    cross_section = multiplier*relativistic_term*subshell_occupancy*
      compton_profile_quantity.value();
  }
  else
    cross_section = 0.0;

  // Make sure the cross section is valid
  testPostcondition( cross_section >= 0.0 );

  return cross_section;
}

// Evaluate the PDF with the electron momentum projection
/*! \details The electron momentum projection must be in me*c units
 * (a momentum value of me*c kg*m/s is 1.0 in me*c units). The PDF
 * will be unitless since the unitless momentum is being used.
 */
template<typename ComptonProfilePolicy>
double StandardCompleteDopplerBroadenedPhotonEnergyDistribution<ComptonProfilePolicy>::evaluatePDFWithElectronMomentumProjection(
                                   const double incoming_energy,
                                   const double electron_momentum_projection,
                                   const double scattering_angle_cosine,
                                   const double precision ) const
{
  // Make sure the precision is valid
  testPrecondition( precision > 0.0 );
  testPrecondition( precision < 1.0 );

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

// Evaluate the exact PDF
/*! \details The PDF has units of inverse MeV.
 */
template<typename ComptonProfilePolicy>
double StandardCompleteDopplerBroadenedPhotonEnergyDistribution<ComptonProfilePolicy>::evaluatePDFExact(
				   const double incoming_energy,
				   const double outgoing_energy,
				   const double scattering_angle_cosine,
                                   const double precision ) const
{
  // Make sure the precision is valid
  testPrecondition( precision > 0.0 );
  testPrecondition( precision < 1.0 );

  const double diff_cross_section = this->evaluateExact(
                                                     incoming_energy,
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

// Evaluate the subshell PDF with the electron momentum projection
/*! \details The electron momentum projection must be in me*c units
 * (a momentum value of me*c kg*m/s is 1.0 in me*c units). The PDF
 * will be unitless since the unitless momentum is being used.
 */
template<typename ComptonProfilePolicy>
double StandardCompleteDopplerBroadenedPhotonEnergyDistribution<ComptonProfilePolicy>::evaluateSubshellPDFWithElectronMomentumProjection(
                                 const double incoming_energy,
                                 const double electron_momentum_projection,
                                 const double scattering_angle_cosine,
                                 const Data::SubshellType subshell,
                                 const double precision ) const
{
  // Make sure the precision is valid
  testPrecondition( precision > 0.0 );
  testPrecondition( precision < 1.0 );

  const double diff_cross_section =
    this->evaluateSubshellWithElectronMomentumProjection(
                                                  incoming_energy,
                                                  electron_momentum_projection,
                                                  scattering_angle_cosine,
                                                  subshell );

  const double integrated_cross_section =
    this->evaluateSubshellIntegratedCrossSection( incoming_energy,
                                                  scattering_angle_cosine,
                                                  subshell,
                                                  precision );

  if( integrated_cross_section > 0.0 )
    return diff_cross_section/integrated_cross_section;
  else
    return 0.0;
}

// Evaluate the exact subshell PDF
/*! \details The PDF has units of inverse MeV.
 */
template<typename ComptonProfilePolicy>
double StandardCompleteDopplerBroadenedPhotonEnergyDistribution<ComptonProfilePolicy>::evaluateSubshellPDFExact(
					  const double incoming_energy,
					  const double outgoing_energy,
				          const double scattering_angle_cosine,
					  const Data::SubshellType subshell,
                                          const double precision ) const
{
  // Make sure the precision is valid
  testPrecondition( precision > 0.0 );
  testPrecondition( precision < 1.0 );

  const double diff_cross_section =
    this->evaluateSubshellExact( incoming_energy,
                                 outgoing_energy,
                                 scattering_angle_cosine,
                                 subshell );

  const double integrated_cross_section =
    this->evaluateSubshellIntegratedCrossSectionExact( incoming_energy,
                                                       scattering_angle_cosine,
                                                       subshell,
                                                       precision );

  if( integrated_cross_section > 0.0 )
    return diff_cross_section/integrated_cross_section;
  else
    return 0.0;
}

// Evaluate the integrated cross section (b/mu)
/*! \details This will integrate the approximate double differential cross
 * section as function of unitless momentum from pz=-1.0 to pz=pz_max.
 */
template<typename ComptonProfilePolicy>
double StandardCompleteDopplerBroadenedPhotonEnergyDistribution<ComptonProfilePolicy>::evaluateIntegratedCrossSection(
					  const double incoming_energy,
					  const double scattering_angle_cosine,
					  const double precision ) const
{
  // Make sure the incoming energy is valid
  testPrecondition( incoming_energy > 0.0 );
  // Make sure the scattering angle is valid
  testPrecondition( scattering_angle_cosine >= -1.0 );
  testPrecondition( scattering_angle_cosine <= 1.0 );

  double cross_section = 0.0;

  // Evaluate the integrated cross section for each subshell
  SubshellOrderMapType::const_iterator subshell_it =
    d_endf_subshell_order.begin();

  while( subshell_it != d_endf_subshell_order.end() )
  {
    cross_section += this->evaluateSubshellIntegratedCrossSection(
                                                       incoming_energy,
                                                       scattering_angle_cosine,
                                                       subshell_it->right,
                                                       precision );

    ++subshell_it;
  }

  // Make sure the integrated cross section is valid
  testPrecondition( cross_section >= 0.0 );

  return cross_section;
}

// Evaluate the exact integrated cross section (b/mu)
/*! \details This will integrate the exact double differential cross
 * section as function of outgoing energy from E=0.0 MeV to E=E_in-E_b^max.
 */
template<typename ComptonProfilePolicy>
double StandardCompleteDopplerBroadenedPhotonEnergyDistribution<ComptonProfilePolicy>::evaluateIntegratedCrossSectionExact(
					  const double incoming_energy,
					  const double scattering_angle_cosine,
					  const double precision ) const
{
  // Make sure the incoming energy is valid
  testPrecondition( incoming_energy > 0.0 );
  // Make sure the scattering angle is valid
  testPrecondition( scattering_angle_cosine >= -1.0 );
  testPrecondition( scattering_angle_cosine <= 1.0 );

  double cross_section = 0.0;

  // Evaluate the integrated cross section for each subshell
  SubshellOrderMapType::const_iterator subshell_it =
    d_endf_subshell_order.begin();

  while( subshell_it != d_endf_subshell_order.end() )
  {
    cross_section += this->evaluateSubshellIntegratedCrossSectionExact(
                                                       incoming_energy,
                                                       scattering_angle_cosine,
                                                       subshell_it->right,
                                                       precision );

    ++subshell_it;
  }

  // Make sure the integrated cross section is valid
  testPrecondition( cross_section >= 0.0 );

  return cross_section;
}

// Evaluate the integrated cross section (b/mu)
/*! \details This will integrate the approximate double differential cross
 * section as a function of unitless momentum. If full profiles are being
 * used the limits of integration are pz=-1.0 and pz=pz_max. If half profiles
 * are being used the limits of integration are pz=-pz_max and pz=pz_max
 * (unless pz_max is <= 0.0 in which case the integrated cross section
 * will be 0.0).
 */
template<typename ComptonProfilePolicy>
double StandardCompleteDopplerBroadenedPhotonEnergyDistribution<ComptonProfilePolicy>::evaluateSubshellIntegratedCrossSection(
				          const double incoming_energy,
					  const double scattering_angle_cosine,
					  const Data::SubshellType subshell,
					  const double precision ) const
{
  // Make sure the incoming energy is valid
  testPrecondition( incoming_energy > 0.0 );
  // Make sure the scattering angle is valid
  testPrecondition( scattering_angle_cosine >= -1.0 );
  testPrecondition( scattering_angle_cosine <= 1.0 );
  // Make sure the subshell is valid
  testPrecondition( this->isValidSubshell( subshell ) );

  // Create the evaluation function wrapper
  boost::function<double (double x)> double_diff_cs_wrapper =
    boost::bind<double>( &StandardCompleteDopplerBroadenedPhotonEnergyDistribution::evaluateSubshellWithElectronMomentumProjection,
                         boost::cref( *this ),
                         incoming_energy,
                         _1,
                         scattering_angle_cosine,
                         subshell );

  // Get the subshell binding energy
  const double subshell_binding_energy =
    this->getSubshellBindingEnergy( subshell );

  // Calculate the max electron momentum projection
  double pz_max =
    calculateMaxElectronMomentumProjection( incoming_energy,
                                            subshell_binding_energy,
                                            scattering_angle_cosine );

  // Don't go above the table max (profile will evaluate to zero beyond it)
  pz_max = ComptonProfilePolicy::getUpperLimitOfIntegration(
                               this->getComptonProfile( subshell ),
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

// Evaluate the integrated cross section (b/mu)
/*! \details This will integrate the exact double differential cross
 * section as a function of outgoing energy. The limits of integration are
 * E=0.0 and E=E_in-E_b,i (for both half profiles and full profiles).
 */
template<typename ComptonProfilePolicy>
double StandardCompleteDopplerBroadenedPhotonEnergyDistribution<ComptonProfilePolicy>::evaluateSubshellIntegratedCrossSectionExact(
				          const double incoming_energy,
					  const double scattering_angle_cosine,
					  const Data::SubshellType subshell,
					  const double precision ) const
{
  // Make sure the incoming energy is valid
  testPrecondition( incoming_energy > 0.0 );
  // Make sure the scattering angle is valid
  testPrecondition( scattering_angle_cosine >= -1.0 );
  testPrecondition( scattering_angle_cosine <= 1.0 );
  // Make sure the subshell is valid
  testPrecondition( this->isValidSubshell( subshell ) );

  // Create the evaluation function wrapper
  boost::function<double (double x)> double_diff_cs_wrapper =
    boost::bind<double>( &StandardCompleteDopplerBroadenedPhotonEnergyDistribution::evaluateSubshellExact,
                         boost::cref( *this ),
                         incoming_energy,
                         _1,
                         scattering_angle_cosine,
                         subshell );

  // Get the Compton profile for this subshell
  const ComptonProfile& compton_profile = this->getComptonProfile( subshell );

  // Calculate the max energy
  double energy_max = incoming_energy -
    this->getSubshellBindingEnergy( subshell );

  // Calculate the max electron momentum projection
  double pz_max = calculateMaxElectronMomentumProjection(
                                  incoming_energy,
                                  this->getSubshellBindingEnergy( subshell ),
                                  scattering_angle_cosine );

  // Calculate the max table energy
  const double pz_table_max =
    ComptonProfilePolicy::getUpperBoundOfMomentum( compton_profile ).value();

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
void StandardCompleteDopplerBroadenedPhotonEnergyDistribution<ComptonProfilePolicy>::sample(
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
/*! \details The sampling of the Compton profile and the interaction subshell
 * are decoupled in this procedure.
 */
template<typename ComptonProfilePolicy>
void StandardCompleteDopplerBroadenedPhotonEnergyDistribution<ComptonProfilePolicy>::sampleAndRecordTrials(
				     const double incoming_energy,
				     const double scattering_angle_cosine,
				     double& outgoing_energy,
				     Data::SubshellType& shell_of_interaction,
				     Counter& trials ) const
{
  // Make sure the incoming energy is valid
  testPrecondition( incoming_energy > 0.0 );
  // Make sure the scattering angle cosine is valid
  testPrecondition( scattering_angle_cosine >= -1.0 );
  testPrecondition( scattering_angle_cosine <= 1.0 );

  // The electron momentum projection
  double pz;

  // Sample the electron momentum projection
  this->sampleMomentumAndRecordTrials( incoming_energy,
                                       scattering_angle_cosine,
                                       pz,
                                       shell_of_interaction,
                                       trials );

  bool energetically_possible;

  outgoing_energy = calculateDopplerBroadenedEnergy( pz,
                                                     incoming_energy,
                                                     scattering_angle_cosine,
                                                     energetically_possible );

  // If a valid outgoing energy could not be calculated default to the
  // Compton line energy (no Doppler broadening).
  if( !energetically_possible || outgoing_energy < 0.0 )
  {
      outgoing_energy = calculateComptonLineEnergy( incoming_energy,
                                                    scattering_angle_cosine );
  }
  else
  {
    // An energy of zero isn't allowed by the rest of the code
    if( outgoing_energy == 0.0 )
      outgoing_energy = std::numeric_limits<double>::min();
  }

  // Make sure the outgoing energy is valid
  testPostcondition( outgoing_energy <= incoming_energy );
  testPostcondition( outgoing_energy > 0.0 );
  // Make sure that the sampled subshell is valid
  testPostcondition( shell_of_interaction !=Data::UNKNOWN_SUBSHELL );
  testPostcondition( shell_of_interaction != Data::INVALID_SUBSHELL );
}

// Sample an electron momentum from the distribution
/*! \details The sampling of the Compton profile and the interaction subshell
 * are decoupled in this procedure.
 */
template<typename ComptonProfilePolicy>
void StandardCompleteDopplerBroadenedPhotonEnergyDistribution<ComptonProfilePolicy>::sampleMomentumAndRecordTrials(
                                    const double incoming_energy,
                                    const double scattering_angle_cosine,
                                    double& electron_momentum,
                                    Data::SubshellType& shell_of_interaction,
                                    Counter& trials ) const
{
  // Make sure the incoming energy is valid
  testPrecondition( incoming_energy > 0.0 );
  // Make sure the scattering angle cosine is valid
  testPrecondition( scattering_angle_cosine >= -1.0 );
  testPrecondition( scattering_angle_cosine <= 1.0 );

  // Record the number of iterations
  Counter iterations = 0;

  // Sample the shell that is interacted with
  size_t compton_subshell_index;
  double subshell_binding_energy;

  // Only allow the selection of subshells where an incoherent interaction is
  // energetically possible - there is definitely a more efficient way to do
  // this!
  while( true )
  {
    ++iterations;

    this->sampleInteractionSubshell( compton_subshell_index,
                                     subshell_binding_energy,
                                     shell_of_interaction );

    // Calculate the maximum outgoing photon energy
    double energy_max = incoming_energy - subshell_binding_energy;

    if( energy_max >= 0.0 )
      break;
  }

  // Get the Compton profile for the sampled subshell
  const ComptonProfile& compton_profile =
    *d_compton_profile_array[compton_subshell_index];

  electron_momentum = this->sampleSubshellMomentum( incoming_energy,
                                                    scattering_angle_cosine,
                                                    subshell_binding_energy,
                                                    compton_profile );

  // Increment the number of trials
  trials += iterations;
}

// Sample an electron momentum from the subshell distribution
template<typename ComptonProfilePolicy>
double StandardCompleteDopplerBroadenedPhotonEnergyDistribution<ComptonProfilePolicy>::sampleSubshellMomentum(
                                     const double incoming_energy,
                                     const double scattering_angle_cosine,
                                     Data::SubshellType subshell ) const
{
  // Make sure the incoming energy is valid
  testPrecondition( incoming_energy >=
                    this->getSubshellBindingEnergy( subshell ) );
  // Make sure the scattering angle cosine is valid
  testPrecondition( scattering_angle_cosine >= -1.0 );
  testPrecondition( scattering_angle_cosine <= 1.0 );
  // Make sure the subshell is valid
  testPrecondition( this->isValidSubshell( subshell ) );

  // Get the subshell binding energy
  const double subshell_binding_energy =
    this->getSubshellBindingEnergy( subshell );

  // Get the Compton profile for the subshell
  const ComptonProfile& compton_profile = this->getComptonProfile( subshell );

  return this->sampleSubshellMomentum( incoming_energy,
                                       scattering_angle_cosine,
                                       subshell_binding_energy,
                                       compton_profile );
}

// Sample an electron momentum from the subshell distribution
template<typename ComptonProfilePolicy>
double StandardCompleteDopplerBroadenedPhotonEnergyDistribution<ComptonProfilePolicy>::sampleSubshellMomentum(
                                 const double incoming_energy,
                                 const double scattering_angle_cosine,
                                 const double subshell_binding_energy,
                                 const ComptonProfile& compton_profile ) const
{
  // Make sure the incoming energy is valid
  testPrecondition( incoming_energy > 0.0 );
  // Make sure the scattering angle cosine is valid
  testPrecondition( scattering_angle_cosine >= -1.0 );
  testPrecondition( scattering_angle_cosine <= 1.0 );

  // Calculate the maximum electron momentum projection
  ComptonProfile::MomentumQuantity pz_max = ComptonProfile::MomentumUnit()*
    calculateMaxElectronMomentumProjection( incoming_energy,
                                            subshell_binding_energy,
                                            scattering_angle_cosine );

  // Sample an electron momentum projection
  ComptonProfile::MomentumQuantity pz =
    ComptonProfilePolicy::sample( compton_profile, pz_max );

  return pz.value();
}

// Check if the subshell is valid
template<typename ComptonProfilePolicy>
bool StandardCompleteDopplerBroadenedPhotonEnergyDistribution<ComptonProfilePolicy>::isValidSubshell(
                                            const Data::SubshellType subshell ) const
{
  return d_endf_subshell_order.right.find( subshell ) !=
    d_endf_subshell_order.right.end();
}

// Return the occupancy of a subshell (default is the ENDF occupancy)
template<typename ComptonProfilePolicy>
inline double StandardCompleteDopplerBroadenedPhotonEnergyDistribution<ComptonProfilePolicy>::getSubshellOccupancy( const Data::SubshellType subshell ) const
{
  // Make sure the subshell is valid
  testPrecondition( this->isValidSubshell( subshell ) );

  unsigned endf_subshell_index = this->getENDFSubshellIndex( subshell );

  return d_endf_subshell_occupancies[endf_subshell_index];
}

// Return the old subshell index corresponding to the subshell
template<typename ComptonProfilePolicy>
unsigned StandardCompleteDopplerBroadenedPhotonEnergyDistribution<ComptonProfilePolicy>::getOldSubshellIndex(
                                            const Data::SubshellType subshell ) const
{
  return d_subshell_converter->convertSubshellToIndex( subshell );
}

// Return the endf subshell index corresponding to the subshell
template<typename ComptonProfilePolicy>
unsigned StandardCompleteDopplerBroadenedPhotonEnergyDistribution<ComptonProfilePolicy>::getENDFSubshellIndex(
                                            const Data::SubshellType subshell ) const
{
  // Make sure the subshell is valid
  testPrecondition( this->isValidSubshell( subshell ) );

  return d_endf_subshell_order.right.find( subshell )->second;
}

// Return the subshell corresponding to the endf subshell index
template<typename ComptonProfilePolicy>
Data::SubshellType StandardCompleteDopplerBroadenedPhotonEnergyDistribution<ComptonProfilePolicy>::getSubshell(
                                     const size_t endf_subshell_index ) const
{
  SubshellOrderMapType::left_map::const_iterator endf_subshell_index_it =
    d_endf_subshell_order.left.find( endf_subshell_index );

  // Make sure the index was found
  testPostcondition( endf_subshell_index_it !=
                     d_endf_subshell_order.left.end() );

  return endf_subshell_index_it->second;
}

// Return the Compton profile for a subshell
template<typename ComptonProfilePolicy>
const ComptonProfile& StandardCompleteDopplerBroadenedPhotonEnergyDistribution<ComptonProfilePolicy>::getComptonProfile(
                                           const Data::SubshellType& subshell ) const
{
  // Make sure the subshell is valid
  testPrecondition( this->isValidSubshell( subshell ) );

  // Get the old subshell corresponding to the subshell type
  unsigned old_subshell_index = this->getOldSubshellIndex( subshell );

  return *d_compton_profile_array[old_subshell_index];
}

// Return the Compton profile for an old subshell index
template<typename ComptonProfilePolicy>
const ComptonProfile& StandardCompleteDopplerBroadenedPhotonEnergyDistribution<ComptonProfilePolicy>::getComptonProfile(
                                     const unsigned& old_subshell_index ) const
{
  // Make sure the old subshell index is valid
  testPrecondition( old_subshell_index <
                    d_compton_profile_array.size() );

  return *d_compton_profile_array[old_subshell_index];
}

// Sample an ENDF subshell
template<typename ComptonProfilePolicy>
Data::SubshellType StandardCompleteDopplerBroadenedPhotonEnergyDistribution<ComptonProfilePolicy>::sampleENDFInteractionSubshell() const
{
  size_t endf_subshell_index;

  d_endf_subshell_occupancy_distribution->sampleAndRecordBinIndex(
                                                         endf_subshell_index );

  return this->getSubshell( endf_subshell_index );
}

EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( StandardCompleteDopplerBroadenedPhotonEnergyDistribution<FullComptonProfilePolicy> );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( StandardCompleteDopplerBroadenedPhotonEnergyDistribution<HalfComptonProfilePolicy> );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( StandardCompleteDopplerBroadenedPhotonEnergyDistribution<DoubledHalfComptonProfilePolicy> );

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_STANDARD_COMPLETE_DOPPLER_BROADENED_PHOTON_ENERGY_DISTRIBUTION_DEF_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_StandardCompleteDopplerBroadenedPhotonEnergyDistribution_def.hpp
//---------------------------------------------------------------------------//
