//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_DetailedWHIncoherentPhotonScatteringDistribution.cpp
//! \author Alex Robinson
//! \brief  The detailed Waller-Hartree incoherent photon scattering dist. def.
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_DetailedWHIncoherentPhotonScatteringDistribution.hpp"
#include "Utility_DiscreteDistribution.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Constructor
DetailedWHIncoherentPhotonScatteringDistribution::DetailedWHIncoherentPhotonScatteringDistribution(
   const std::shared_ptr<const ScatteringFunction>& scattering_function,
   const Teuchos::Array<double>& subshell_occupancies,
   const Teuchos::Array<SubshellType>& subshell_order,
   const double kahn_sampling_cutoff_energy )
  : WHIncoherentPhotonScatteringDistribution( scattering_function,
					      kahn_sampling_cutoff_energy ),
    d_subshell_occupancy_distribution(),
    d_subshell_order( subshell_order )
{
  // Make sure the scattering function is valid
  testPrecondition( scattering_function.get() );
  // Make sure the shell interaction data is valid
  testPrecondition( subshell_occupancies.size() > 0 );
  testPrecondition( subshell_occupancies.size() ==
		    subshell_order.size() );

  // Create the shell interaction data distribution
  Teuchos::Array<double> dummy_indep_vals( subshell_occupancies.size() );
  
  d_subshell_occupancy_distribution.reset(
	           new Utility::DiscreteDistribution( dummy_indep_vals,
						      subshell_occupancies ) );
}

// Randomly scatter the photon and return the shell that was interacted with
/*! \details The particle bank is used to store the electron that is emitted
 * from the collision. The energy and direction of the outgoing electron is 
 * calculated as if it were at rest initially (feel free to update this 
 * model!).
 */ 
void DetailedWHIncoherentPhotonScatteringDistribution::scatterPhoton( 
				     PhotonState& photon,
				     ParticleBank& bank,
				     SubshellType& shell_of_interaction ) const
{
  double outgoing_energy, scattering_angle_cosine;

  // Sample an outgoing energy and direction
  this->sample( photon.getEnergy(),
		outgoing_energy,
		scattering_angle_cosine );

  // Sample the approximate subshell that is interacted with
  this->sampleInteractionSubshell( shell_of_interaction );

  // Sample the azimuthal angle of the outgoing photon
  const double azimuthal_angle = this->sampleAzimuthalAngle();

  // Create the ejectected electron 
  this->createEjectedElectron( photon, 
			       scattering_angle_cosine, 
			       azimuthal_angle,
			       bank );
  
  // Set the new energy
  photon.setEnergy( outgoing_energy );

  // Set the new direction
  photon.rotateDirection( scattering_angle_cosine, azimuthal_angle );
}

// Sample the subshell that is interacted with
void DetailedWHIncoherentPhotonScatteringDistribution::sampleInteractionSubshell(
				     SubshellType& shell_of_interaction ) const
{
  // Sample the shell that is interacted with
  unsigned shell_index;

  d_subshell_occupancy_distribution->sampleAndRecordBinIndex( shell_index );

  shell_of_interaction = d_subshell_order[shell_index];
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_DetailedWHIncoherentPhotonScatteringDistribution.cpp
//---------------------------------------------------------------------------//
