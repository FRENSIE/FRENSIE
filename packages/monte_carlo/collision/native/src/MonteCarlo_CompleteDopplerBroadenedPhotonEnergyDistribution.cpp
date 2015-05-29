//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_CompleteDopplerBroadenedPhotonEnergyDistribution.cpp
//! \author Alex Robinson
//! \brief  The complete Doppler broadened photon energy distribution def.
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_CompleteDopplerBroadenedPhotonEnergyDistribution.hpp"
#include "Utility_DiscreteDistribution.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Constructor
CompleteDopplerBroadenedPhotonEnergyDistribution::CompleteDopplerBroadenedPhotonEnergyDistribution(
		      const Teuchos::Array<double>& endf_subshell_occupancies,
		      const Teuchos::Array<SubshellType>& endf_subshell_order )
  : d_endf_subshell_occupancy_distribution(),
    d_endf_subshell_order( endf_subshell_order )
{
  // Make sure the shell interaction data is valid
  testPrecondition( endf_subshell_occupancies.size() > 0 );
  testPrecondition( endf_subshell_order.size() == 
		    endf_subshell_occupancies.size() );
  
  // Create the ENDF subshell interaction distribution
  Teuchos::Array<double> dummy_indep_vals( endf_subshell_occupancies.size() );

  d_endf_subshell_occupancy_distribution.reset(
	      new Utility::DiscreteDistribution( dummy_indep_vals,
						 endf_subshell_occupancies ) );
}


// Sample an ENDF subshell
void CompleteDopplerBroadenedPhotonEnergyDistribution::sampleENDFInteractionSubshell( 
					    SubshellType& shell_of_interaction,
					    unsigned& shell_index ) const
{
  d_endf_subshell_occupancy_distribution->sampleAndRecordBinIndex(shell_index);
								  
  shell_of_interaction = d_endf_subshell_order[shell_index];
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_CompleteDopplerBroadenedPhotonEnergyDistribution.cpp
//---------------------------------------------------------------------------//
