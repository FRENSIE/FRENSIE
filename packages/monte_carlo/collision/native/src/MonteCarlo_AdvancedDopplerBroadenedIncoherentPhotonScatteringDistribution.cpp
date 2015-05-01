//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_AdvancedDopplerBroadenedIncoherentPhotonScatteringDistribution.cpp
//! \author Alex Robinson
//! \brief  THe advanced Doppler broadened incoherent photon scattering dist decl.
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_AdvancedDopplerBroadenedIncoherentPhotonScatteringDistribution.hpp"
#include "MonteCarlo_ComptonProfileHelpers.hpp"

namespace MonteCarlo{

// Constructor
/*! \details The Compton profile grids must be in me*c units (not atomic 
 * units). The Compton profiles must be in inverse me*c units (not inverse 
 * atomic units). Only half profiles should be provided (grid ranges from 0.0 
 * to 1.0).
 */
AdvancedDopplerBroadenedIncoherentPhotonScatteringDistribution::AdvancedDopplerBroadenedIncoherentPhotonScatteringDistribution(
     const Teuchos::RCP<const Utility::OneDDistribution>& scattering_function,
     const Teuchos::Array<double>& subshell_binding_energies,
     const Teuchos::Array<double>& subshell_occupancies,
     const Teuchos::Array<SubshellType>& subshell_order,
     const Teuchos::RCP<ComptonProfileSubshellConverter>& subshell_converter,
     const ElectronMomentumDistArray& electron_momentum_dist_array,
     const double kahn_sampling_cutoff_energy )
  : DopplerBroadenedIncoherentPhotonScatteringDistribution( 
						 scattering_function,
						 subshell_binding_energies,
						 subshell_occupancies,
						 subshell_order,
						 subshell_converter,
						 kahn_sampling_cutoff_energy ),
    d_electron_momentum_distribution( electron_momentum_dist_array )
{
  // Make sure the scattering function is valid
  testPrecondition( !scattering_function.is_null() );
  // Make sure the shell interaction data is valid
  testPrecondition( subshell_binding_energies.size() > 0 );
  testPrecondition( subshell_occupancies.size() ==
		    subshell_binding_energies.size() );
  testPrecondition( subshell_order.size() == 
		    subshell_binding_energies.size() );
  // Make sure the comptron profile array is valid
  testPrecondition( electron_momentum_dist_array.size() > 0 );
  testPrecondition( electron_momentum_dist_array.front()->getLowerBoundOfIndepVar() == 0.0 );
  testPrecondition( electron_momentum_dist_array.back()->getLowerBoundOfIndepVar() == 0.0 );
  testPrecondition( electron_momentum_dist_array.front()->getUpperBoundOfIndepVar() <= 1.0 );
  testPrecondition( electron_momentum_dist_array.back()->getUpperBoundOfIndepVar() <= 1.0 );
}

// Doppler broaden a compton line energy
/*! \details This is the procedure outlined in many papers, which recommend
 * the use of only 1/2 of the Compton profile (0 to 100 in 
 * atomic momentum units). The validity of this approach seems questionable
 * so use the revised version when possible.
 */
double AdvancedDopplerBroadenedIncoherentPhotonScatteringDistribution::sampleDopplerBroadenedComptonLineEnergy( 
				     const double incoming_energy,
				     const double scattering_angle_cosine,
				     SubshellType& shell_of_interaction ) const
{
  // Make sure the incoming energy is valid
  testPrecondition( incoming_energy > 0.0 );
  // Make sure the scattering angle cosine is valid
  testPrecondition( scattering_angle_cosine >= -1.0 );
  testPrecondition( scattering_angle_cosine <= 1.0 );
  
  const double compton_line_energy = 
    this->calculateComptonLineEnergy( incoming_energy,
				      scattering_angle_cosine );

  double outgoing_energy;
  
  // Record if a valid Doppler broadening energy is calculated
  bool valid_doppler_broadening = true;

  while( true )
  {
    // Sample the shell that is interacted with
    double subshell_binding_energy;
    unsigned compton_shell_index;

    this->sampleSubshell( shell_of_interaction,
			  subshell_binding_energy,
			  compton_shell_index );

    // Calculate the maximum outgoing photon energy
    double energy_max = incoming_energy - subshell_binding_energy;

    // Compton scattering can only occur if there is enough energy to release
    // the electron from its shell
    if( energy_max <= 0.0 )
    {
      valid_doppler_broadening = false;
      break;
    }

    // Calculate the maximum electron momentum projection
    double pz_max = calculateMaxElectronMomentumProjection( 
						     incoming_energy,
						     subshell_binding_energy,
						     scattering_angle_cosine );

    // Make sure the maximum electron momentum projection is physical (>-1.0)
    if( pz_max < d_electron_momentum_distribution[compton_shell_index]->getLowerBoundOfIndepVar() )
    {
      valid_doppler_broadening = false;

      break;
    }
    
    double pz_table_max = 
      d_electron_momentum_distribution[compton_shell_index]->getUpperBoundOfIndepVar();
    
    if( pz_max > pz_table_max )
      pz_max = pz_table_max;
    
    // Sample an electron momentum projection
    double pz = 
      d_electron_momentum_distribution[compton_shell_index]->sampleInSubrange( 
								      pz_max );
    
    // Calculate the doppler broadened energy
    bool energetically_possible;

    outgoing_energy = calculateDopplerBroadenedEnergy(pz,
						      incoming_energy,
						      scattering_angle_cosine,
						      energetically_possible );

    if( !energetically_possible || outgoing_energy == 0.0 )
    {
      valid_doppler_broadening = false;
	
      break;
    }
    else
    {
      valid_doppler_broadening = true;

      break;
    }
  }

  if( !valid_doppler_broadening )
  {
    // reset the shell of interaction
    shell_of_interaction = UNKNOWN_SUBSHELL;
    
    // reset the outgoing energy
    outgoing_energy = compton_line_energy;
  }

  // Make sure the outgoing energy is valid
  testPostcondition( outgoing_energy <= incoming_energy );
  testPostcondition( outgoing_energy > 0.0 );

  return outgoing_energy;
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_AdvancedDopplerBroadenedIncoherentPhotonScatteringDistribution.cpp
//---------------------------------------------------------------------------//
