//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_CoupledCompleteDopplerBroadenedPhotonEnergyDistribution.cpp
//! \author Alex Robinson
//! \brief  The coupled complete Doppler broadened photon energy dist. def.
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_CoupledCompleteDopplerBroadenedPhotonEnergyDistribution.hpp"
#include "MonteCarlo_PhotonKinematicsHelpers.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Constructor
/*! \details The Compton profile grids must be in me*c units (not atomic 
 * units). The Compton profiles must be in inverse me*c units (not inverse 
 * atomic units). Only half profiles should be provided (grid ranges from 0.0 
 * to 1.0).
 */
CoupledCompleteDopplerBroadenedPhotonEnergyDistribution::CoupledCompleteDopplerBroadenedPhotonEnergyDistribution(
                const Teuchos::Array<double>& subshell_binding_energies,
                const Teuchos::Array<double>& subshell_occupancies,
                const Teuchos::Array<SubshellType>& subshell_order,
                const std::shared_ptr<const ComptonProfileSubshellConverter>&
                subshell_converter,
                const ElectronMomentumDistArray& electron_momentum_dist_array )
  : CompleteDopplerBroadenedPhotonEnergyDistribution( subshell_occupancies,
						      subshell_order ),
    d_subshell_converter( subshell_converter ),
    d_subshell_binding_energies( subshell_binding_energies ),
    d_half_profiles( true ),
    d_electron_momentum_distribution( electron_momentum_dist_array )
{
  // Make sure the shell interaction data is valid
  testPrecondition( subshell_occupancies.size() > 0 );
  testPrecondition( subshell_order.size() == 
		    subshell_occupancies.size() );
  testPrecondition( subshell_binding_energies.size() ==
		    subshell_occupancies.size() );
  // Make sure the comptron profile array is valid
  testPrecondition( electron_momentum_dist_array.size() > 0 );

  // Check if a half (standard) or full profile is being used.
  if( electron_momentum_dist_array.front()->getLowerBoundOfMomentum() < 
      0.0*Utility::Units::mec_momentum )
    d_half_profiles = false;
  else
    d_half_profiles = true;
}

// Evaluate the distribution
double CoupledCompleteDopplerBroadenedPhotonEnergyDistribution::evaluate( 
				   const double incoming_energy,
				   const double outgoing_energy,
				   const double scattering_angle_cosine ) const
{
  return 0.0;
}
    
// Evaluate the subshell distribution
double CoupledCompleteDopplerBroadenedPhotonEnergyDistribution::evaluateSubshell( 
				          const double incoming_energy,
					  const double outgoing_energy,
				          const double scattering_angle_cosine,
					  const SubshellType subshell ) const
{
  return 0.0;
}

// Evaluate the PDF
double CoupledCompleteDopplerBroadenedPhotonEnergyDistribution::evaluatePDF( 
				   const double incoming_energy,
				   const double outgoing_energy,
				   const double scattering_angle_cosine ) const
{
  return 0.0;
}

// Evaluate the PDF
double CoupledCompleteDopplerBroadenedPhotonEnergyDistribution::evaluateSubshellPDF( 
					  const double incoming_energy,
					  const double outgoing_energy,
				          const double scattering_angle_cosine,
					  const SubshellType subshell ) const
{
  return 0.0;
}

// Evaluate the integrated cross section (b/mu)
double CoupledCompleteDopplerBroadenedPhotonEnergyDistribution::evaluateIntegratedCrossSection( 
					  const double incoming_energy,
					  const double scattering_angle_cosine,
					  const double precision ) const
{
  return 0.0;
}

// Evaluate the integrated cross section (b/mu)
double CoupledCompleteDopplerBroadenedPhotonEnergyDistribution::evaluateSubshellIntegratedCrossSection( 
				          const double incoming_energy,
					  const double scattering_angle_cosine,
					  const SubshellType subshell,
					  const double precision ) const
{
  return 0.0;
}

// Sample an outgoing energy from the distribution
void CoupledCompleteDopplerBroadenedPhotonEnergyDistribution::sample( 
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
 * are coupled in this procedure.
 */
void CoupledCompleteDopplerBroadenedPhotonEnergyDistribution::sampleAndRecordTrials( 
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

  const double compton_line_energy = calculateComptonLineEnergy( 
						     incoming_energy,
						     scattering_angle_cosine );

  // Record if a valid Doppler broadening energy is calculated
  bool valid_doppler_broadening = false;

  // Record the number of iterations
  unsigned iterations = 0u;

  while( iterations < 1000 )
  {
    ++iterations;
    
    // Sample the shell that is interacted with
    unsigned shell_index;

    this->sampleENDFInteractionSubshell( shell_of_interaction,
					 shell_index );

    double subshell_binding_energy = d_subshell_binding_energies[shell_index];

    unsigned compton_shell_index = 
      d_subshell_converter->convertSubshellToIndex( shell_of_interaction );

    // Get the Compton profile for the sampled subshell
    const ComptonProfile& compton_profile = 
      *d_electron_momentum_distribution[compton_shell_index];

    // Calculate the maximum outgoing photon energy
    double energy_max = incoming_energy - subshell_binding_energy;

    // Compton scattering can only occur if there is enough energy to release
    // the electron from its shell
    if( energy_max <= 0.0 )
      continue;

    // Calculate the maximum electron momentum projection
    ComptonProfile::MomentumQuantity pz_max = Utility::Units::mec_momentum* 
      calculateMaxElectronMomentumProjection( incoming_energy,
					      subshell_binding_energy,
					      scattering_angle_cosine );

    // If using a half profile, make sure the maximum electron momentum 
    // projection is positive (why? - pz_max >= -1.0 is acceptable...)
    if( pz_max < compton_profile.getLowerBoundOfMomentum() )
      continue;

    ComptonProfile::MomentumQuantity pz_table_max = 
      compton_profile.getUpperBoundOfMomentum();
    
    if( pz_max > pz_table_max )
      pz_max = pz_table_max;
    
    // Sample an electron momentum projection
    ComptonProfile::MomentumQuantity pz = 
      compton_profile.sampleInSubrange( pz_max );
    
    if( d_half_profiles )
    {
      if( Utility::RandomNumberGenerator::getRandomNumber<double>() <= 0.5 )
      	pz *= -1.0;
    }
    
    bool energetically_possible;

    outgoing_energy = calculateDopplerBroadenedEnergy(pz.value(),
						      incoming_energy,
						      scattering_angle_cosine,
						      energetically_possible );
    
    if( !energetically_possible || outgoing_energy < 0.0 )
      continue;
    else
    {
      if( outgoing_energy == 0.0 )
	outgoing_energy = std::numeric_limits<double>::min();
      
      valid_doppler_broadening = true;

      break;
    }
  }

  // Increment the number of trials
  trials += iterations;

  if( !valid_doppler_broadening )
  {
    // Should the interaction shell be reset?
    // shell_of_interaction = UNKNOWN_SUBSHELL;
    
    // reset the outgoing energy
    outgoing_energy = compton_line_energy;
  }

  // Make sure the outgoing energy is valid
  testPostcondition( outgoing_energy <= incoming_energy );
  testPostcondition( outgoing_energy > 0.0 );
  // Make sure the interaction subshell is valid
  testPostcondition( shell_of_interaction != UNKNOWN_SUBSHELL );
  testPostcondition( shell_of_interaction != INVALID_SUBSHELL );
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_CoupledCompleteDopplerBroadenedPhotonEnergyDistribution.cpp
//---------------------------------------------------------------------------//
