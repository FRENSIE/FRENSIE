//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_DecoupledCompleteDopplerBroadenedPhotonEnergyDistribution.cpp
//! \author Alex Robinson
//! \brief  The decoupled complete Doppler broadened photon energy dist. def.
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_DecoupledCompleteDopplerBroadenedPhotonEnergyDistribution.hpp"
#include "MonteCarlo_PhotonKinematicsHelpers.hpp"
#include "Utility_DiscreteDistribution.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Constructor
/*! \details The Compton profile grids must be in me*c units (not atomic 
 * units). The Compton profiles must be in inverse me*c units (not inverse 
 * atomic units). Only half profiles should be provided (grid ranges from 0.0 
 * to 1.0).
 */
DecoupledCompleteDopplerBroadenedPhotonEnergyDistribution::DecoupledCompleteDopplerBroadenedPhotonEnergyDistribution(
	       const Teuchos::Array<double>& endf_subshell_occupancies,
	       const Teuchos::Array<SubshellType>& endf_subshell_order,
	       const Teuchos::Array<double>& old_subshell_binding_energies,
	       const Teuchos::Array<double>& old_subshell_occupancies,
	       const ElectronMomentumDistArray& electron_momentum_dist_array )
  : CompleteDopplerBroadenedPhotonEnergyDistribution(endf_subshell_occupancies,
						     endf_subshell_order ),
    d_old_subshell_occupancy_distribution(),
    d_old_subshell_binding_energy( old_subshell_binding_energies ),
    d_old_subshell_occupancies( old_subshell_occupancies ),
    d_half_profiles( true ),
    d_electron_momentum_distribution( electron_momentum_dist_array )
{
  // Make sure the shell interaction data is valid
  testPrecondition( endf_subshell_occupancies.size() > 0 );
  testPrecondition( endf_subshell_order.size() == 
		    endf_subshell_occupancies.size() );
  // Make sure the old shell data is valid
  testPrecondition( old_subshell_binding_energies.size() > 0 );
  testPrecondition( old_subshell_occupancies.size() ==
		    old_subshell_binding_energies.size() );
  // Make sure the comptron profile array is valid
  testPrecondition( electron_momentum_dist_array.size() ==
		    old_subshell_binding_energies.size() );
  testPrecondition( electron_momentum_dist_array.front()->getLowerBoundOfIndepVar() >= -1.0 );
  testPrecondition( electron_momentum_dist_array.back()->getLowerBoundOfIndepVar() >= -1.0 );
  testPrecondition( electron_momentum_dist_array.front()->getUpperBoundOfIndepVar() <= 1.0 );
  testPrecondition( electron_momentum_dist_array.back()->getUpperBoundOfIndepVar() <= 1.0 );

  // Create the old subshell interaction distribution
  Teuchos::Array<double> dummy_indep_vals( old_subshell_occupancies.size() );

  d_old_subshell_occupancy_distribution.reset(
	       new Utility::DiscreteDistribution( dummy_indep_vals,
					          old_subshell_occupancies ) );

  // Check if a half (standard) or full profile is being used.
  if( electron_momentum_dist_array.front()->getLowerBoundOfIndepVar() < 0.0 )
    d_half_profiles = false;
  else
    d_half_profiles = true;
}

// Evaluate the distribution
double DecoupledCompleteDopplerBroadenedPhotonEnergyDistribution::evaluate( 
				   const double incoming_energy,
				   const double outgoing_energy,
				   const double scattering_angle_cosine ) const
{
  // Make sure the incoming energy is valid
  testPrecondition( incoming_energy > 0.0 );
  // Make sure the outgoing energy is valid
  testPrecondition( outgoing_energy < incoming_energy );
  // Make sure the scattering angle is valid
  testPrecondition( scattering_angle_cosine >= -1.0 );
  testPrecondition( scattering_angle_cosine <= 1.0 );

  const double compton_line_energy = 
    calculateComptonLineEnergy( incoming_energy, scattering_angle_cosine );

  const double electron_momentum_projection = 
    calculateElectronMomentumProjection( incoming_energy,
					 outgoing_energy,
					 scattering_angle_cosine );

  const double multiplier = this->evaluateMultiplier(incoming_energy,
						     outgoing_energy,
						     scattering_angle_cosine);
  
  double compton_profile_terms = 0.0;				       

  for( unsigned i = 0; i < d_old_subshell_binding_energy.size(); ++i )
  {
    if( incoming_energy >= d_old_subshell_binding_energy[i] )
    {
      // Half profiles are multiplied by 2 two keep them normalized - divide
      // by two after evaluating the profile.
      if( d_half_profiles )
      {
	compton_profile_terms += 
	  d_electron_momentum_distribution[i]->evaluate( 
				      fabs( electron_momentum_projection ) )/2;
      }
      else
      {
	compton_profile_terms +=
	  d_electron_momentum_distribution[i]->evaluate(
					        electron_momentum_projection );
      }
    }
  }

  return multiplier*compton_profile_terms;
}
    
// Evaluate the subshell distribution
double DecoupledCompleteDopplerBroadenedPhotonEnergyDistribution::evaluateSubshell( 
				          const double incoming_energy,
					  const double outgoing_energy,
				          const double scattering_angle_cosine,
					  const SubshellType subshell ) const
{
  
}

// Evaluate the PDF
double DecoupledCompleteDopplerBroadenedPhotonEnergyDistribution::evaluatePDF( 
				   const double incoming_energy,
				   const double outgoing_energy,
				   const double scattering_angle_cosine ) const
{
  return 0.0;
}

// Evaluate the PDF
double DecoupledCompleteDopplerBroadenedPhotonEnergyDistribution::evaluateSubshellPDF( 
					  const double incoming_energy,
					  const double outgoing_energy,
				          const double scattering_angle_cosine,
					  const SubshellType subshell ) const
{
  return 0.0;
}

// Evaluate the integrated cross section (b/mu)
double DecoupledCompleteDopplerBroadenedPhotonEnergyDistribution::evaluateIntegratedCrossSection( 
					  const double incoming_energy,
					  const double scattering_angle_cosine,
					  const double precision ) const
{
  return 0.0;
}

// Evaluate the integrated cross section (b/mu)
double DecoupledCompleteDopplerBroadenedPhotonEnergyDistribution::evaluateSubshellIntegratedCrossSection( 
				          const double incoming_energy,
					  const double scattering_angle_cosine,
					  const SubshellType subshell,
					  const double precision ) const
{
  return 0.0;
}

// Sample an outgoing energy from the distribution
void DecoupledCompleteDopplerBroadenedPhotonEnergyDistribution::sample( 
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
/*! \details The sampling of the Compton profile and the interaction subshell
 * are decoupled in this procedure.
 */
void DecoupledCompleteDopplerBroadenedPhotonEnergyDistribution::sampleAndRecordTrials( 
				     const double incoming_energy,
				     const double scattering_angle_cosine,
				     double& outgoing_energy,
				     SubshellType& shell_of_interaction,
				     unsigned& trials ) const
{
  // Make sure the incoming energy is valid
  testPrecondition( incoming_energy > 0.0 );
  // Make sure the scattering angle cosine is valid
  testPrecondition( scattering_angle_cosine >= -1.0 );
  testPrecondition( scattering_angle_cosine <= 1.0 );

  // Record if a valid Doppler broadening energy is calculated
  bool valid_doppler_broadening = false;

  while( true )
  {
    // Sample the shell that is interacted with
    unsigned compton_shell_index;
    double subshell_binding_energy;

    this->sampleOldInteractionSubshell( compton_shell_index,
					subshell_binding_energy );

    // Get the Compton profile for the sampled subshell
    const Utility::TabularOneDDistribution& compton_profile = 
      *d_electron_momentum_distribution[compton_shell_index];

    // Calculate the maximum outgoing photon energy
    double energy_max = incoming_energy - subshell_binding_energy;

    // Compton scattering can only occur if there is enough energy to release
    // the electron from its shell
    if( energy_max <= 0.0 )
    {
      valid_doppler_broadening = false;

      ++trials;
      
      break;
    }

    // Calculate the maximum electron momentum projection
    double pz_max = calculateMaxElectronMomentumProjection( 
						     incoming_energy,
						     subshell_binding_energy,
						     scattering_angle_cosine );

    // If using a half profile, make sure the maximum electron momentum 
    // projection is positive (why? - pz_max >= -1.0 is acceptable...)
    if( pz_max < compton_profile.getLowerBoundOfIndepVar() )
    {
      valid_doppler_broadening = false;

      ++trials;

      break;
    }

    double pz_table_max = compton_profile.getUpperBoundOfIndepVar();
    
    if( pz_max > pz_table_max )
      pz_max = pz_table_max;

    // Sample an electron momentum projection
    double pz = compton_profile.sampleInSubrange( pz_max );
    
    if( d_half_profiles )
    {
      if( Utility::RandomNumberGenerator::getRandomNumber<double>() <= 0.5 )
	pz *= -1.0;
    }

    bool energetically_possible;

    outgoing_energy = calculateDopplerBroadenedEnergy(pz,
						      incoming_energy,
						      scattering_angle_cosine,
						      energetically_possible );
    
    if( !energetically_possible || outgoing_energy < 0.0 )
    {
      valid_doppler_broadening = false;

      ++trials;

      break;
    }
    else
    {
      if( outgoing_energy == 0.0 )
	outgoing_energy = std::numeric_limits<double>::min();
      
      valid_doppler_broadening = true;
      
      ++trials;

      break;
    }
  }

  // reset the outgoing energy to the Compton line energy
  if( !valid_doppler_broadening ) 
  {   
    outgoing_energy = calculateComptonLineEnergy( incoming_energy,
						  scattering_angle_cosine );
  }

  // The ENDF subshell is not sampled in this procedure
  unsigned shell_index;
  
  this->sampleENDFInteractionSubshell( shell_of_interaction,
				       shell_index );

  // Make sure the outgoing energy is valid
  testPostcondition( outgoing_energy <= incoming_energy );
  testPostcondition( outgoing_energy > 0.0 );
  // Make sure that the sampled subshell is valid
  testPostcondition( shell_of_interaction != UNKNOWN_SUBSHELL );
  testPostcondition( shell_of_interaction != INVALID_SUBSHELL );
}

// Sample the old subshell that is interacted with
void DecoupledCompleteDopplerBroadenedPhotonEnergyDistribution::sampleOldInteractionSubshell( 
				    unsigned& old_shell_of_interaction,
				    double& old_subshell_binding_energy ) const
{
  d_old_subshell_occupancy_distribution->sampleAndRecordBinIndex( 
						    old_shell_of_interaction );

  // Get the binding energy
  old_subshell_binding_energy = 
    d_old_subshell_binding_energy[old_shell_of_interaction];
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_DecoupledCompleteDopplerBroadenedPhotonEnergyDistribution.cpp
//---------------------------------------------------------------------------//
