//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_KleinNishinaAdjointPhotonScatteringDistribution.cpp
//! \author Alex Robinson
//! \brief  The Klein-Nishina adjoint photon scattering distribution def.
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_KleinNishinaAdjointPhotonScatteringDistribution.hpp"
#include "MonteCarlo_AdjointPhotonKinematicsHelpers.hpp"
#include "MonteCarlo_AdjointPhotonProbeState.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Constructor
KleinNishinaAdjointPhotonScatteringDistribution::KleinNishinaAdjointPhotonScatteringDistribution(
	        const double max_energy,
	        const Teuchos::ArrayRCP<const double>& critical_line_energies )
  : IncoherentAdjointPhotonScatteringDistribution( max_energy,
						   critical_line_energies )
{ /* ... */ }

// Evaluate the distribution
double KleinNishinaAdjointPhotonScatteringDistribution::evaluate( 
				   const double incoming_energy,
				   const double scattering_angle_cosine ) const
{
  // Make sure the incoming energy is valid
  testPrecondition( incoming_energy > 0.0 );
  testPrecondition( incoming_energy <= d_max_energy );
  // Make sure the scattering angle cosine is valid
  testPrecondition( scattering_angle_cosine >= 
		    calculateMinScatteringAngleCosine( incoming_energy,
						       this->getMaxEnergy() ));
  testPrecondition( scattering_angle_cosine <= 1.0 );

  return this->evaluateAdjointKleinNishinaDist( incoming_energy,
						scattering_angle_cosine );
}
  
// Evaluate the integrated cross section (cm^2)
double KleinNishinaAdjointPhotonScatteringDistribution::evaluateIntegratedCrossSection( 
					         const double incoming_energy,
					         const double precision ) const
{
  // Make sure the energy is valid
  testPrecondition( incoming_energy > 0.0 );
  testPrecondition( incoming_energy <= this->getMaxEnergy() );

  const double alpha = 
    incoming_energy/Utility::PhysicalConstants::electron_rest_mass_energy;

  const double alpha_sqr = alpha*alpha;
  
  const double x_min = 
    calculateMinInverseEnergyGainRatio( incoming_energy, this->getMaxEnergy());

  const double x_min_sqr = x_min*x_min;

  const double term_1 = (1.0 - x_min_sqr*x_min)/(3.0*alpha_sqr);
  
  const double term_2 = 0.5*(1.0 + 2*(alpha-1.0)/alpha_sqr)*(1.0-x_min_sqr);

  const double term_3 = (1.0 - 2*alpha)*(1-x_min)/alpha_sqr;

  const double term_4 = -log(x_min);

  const double cross_section = 1e24*Utility::PhysicalConstants::pi*
    Utility::PhysicalConstants::classical_electron_radius*
    Utility::PhysicalConstants::classical_electron_radius*
    (term_1 + term_2 + term_3 + term_4);

  // Make sure the cross section is valid
  testPostcondition( cross_section > 0.0 );

  return cross_section;
}
  
// Sample an outgoing energy and direction from the distribution
void KleinNishinaAdjointPhotonScatteringDistribution::sample( 
					const double incoming_energy,
					double& outgoing_energy,
					double& scattering_angle_cosine ) const
{
  // Make sure the energy is valid
  testPrecondition( incoming_energy > 0.0 );
  testPrecondition( incoming_energy <= this->getMaxEnergy() );

  unsigned trial_dummy;

  this->sampleAndRecordTrialsAdjointKleinNishina( incoming_energy,
						  outgoing_energy,
						  scattering_angle_cosine,
						  trial_dummy );	 
}
  
// Sample an outgoing energy and direction and record the number of trials
void KleinNishinaAdjointPhotonScatteringDistribution::sampleAndRecordTrials( 
					       const double incoming_energy,
					       double& outgoing_energy,
					       double& scattering_angle_cosine,
					       unsigned& trials ) const
{
  // Make sure the energy is valid
  testPrecondition( incoming_energy > 0.0 );
  testPrecondition( incoming_energy <= this->getMaxEnergy() );

  this->sampleAndRecordTrialsAdjointKleinNishina( incoming_energy,
						  outgoing_energy,
						  scattering_angle_cosine,
						  trials );
}
  
// Randomly scatter the photon and return the shell that was interacted with
void KleinNishinaAdjointPhotonScatteringDistribution::scatterAdjointPhoton( 
				     AdjointPhotonState& adjoint_photon,
				     ParticleBank& bank,
				     SubshellType& shell_of_interaction ) const
{
  double outgoing_energy, scattering_angle_cosine;
  
  this->sample( adjoint_photon.getEnergy(),
		outgoing_energy,
		scattering_angle_cosine );

  shell_of_interaction = UNKNOWN_SUBSHELL;

  adjoint_photon.setEnergy( outgoing_energy );

  adjoint_photon.rotateDirection( scattering_angle_cosine,
				  this->sampleAzimuthalAngle() );
}
  
// Create a probe particle
void KleinNishinaAdjointPhotonScatteringDistribution::createProbeParticle( 
				      const double energy_of_interest, 
				      const AdjointPhotonState& adjoint_photon,
				      ParticleBank& bank ) const
{
  // Make sure the energy of interest is in the scattering window
  testPrecondition( this->isEnergyInScatteringWindow( 
						energy_of_interest,
						adjoint_photon.getEnergy() ) );

  // Only generate the probe if the energy is in the scattering window
  if( this->isEnergyInScatteringWindow( energy_of_interest,
					adjoint_photon.getEnergy() ) )
  {
    const double scattering_angle_cosine = 
      calculateScatteringAngleCosineAdjoint( adjoint_photon.getEnergy(),
					     energy_of_interest );
    
    const double pdf_conversion = 
      Utility::PhysicalConstants::electron_rest_mass_energy/
      (adjoint_photon.getEnergy()*adjoint_photon.getEnergy());

    const double weight_mult = 
      this->evaluatePDF( adjoint_photon.getEnergy(), scattering_angle_cosine )*
      pdf_conversion;

    // Create the probe with the desired energy and modified weight
    Teuchos::RCP<AdjointPhotonProbeState> probe( 
			       new AdjointPhotonProbeState( adjoint_photon ) );
    
    probe->setEnergy( energy_of_interest );
    probe->rotateDirection( scattering_angle_cosine, 
			    this->sampleAzimuthalAngle() );
    probe->multiplyWeight( weight_mult );
    probe->activate();

    // Add the probe to the bank
    bank.push( probe );
  }
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_KleinNishinaAdjointPhotonScatteringDistribution.cpp
//---------------------------------------------------------------------------//
