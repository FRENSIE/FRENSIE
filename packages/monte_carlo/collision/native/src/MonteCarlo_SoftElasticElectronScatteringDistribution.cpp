//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_SoftElasticElectronScatteringDistribution.cpp
//! \author Luke Kersting
//! \brief  The soft electron elastic scattering distribution definition
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <limits>

// Trilinos Includes
#include <Teuchos_Array.hpp>

// FRENSIE Includes
#include "MonteCarlo_SoftElasticElectronScatteringDistribution.hpp"
#include "MonteCarlo_TwoDDistributionHelpers.hpp"
#include "Utility_DiscreteDistribution.hpp"

namespace MonteCarlo{

// Constructor
SoftElasticElectronScatteringDistribution::SoftElasticElectronScatteringDistribution(
    const int atomic_number,
    const double mu_cutoff,
    const ElasticDistribution& discrete_scattering_distribution )
  : d_discrete_scattering_distribution( discrete_scattering_distribution )
{
  // Make sure the array is valid
  testPrecondition( d_discrete_scattering_distribution.size() > 0 );
}

// Sample an outgoing energy and direction from the distribution
void SoftElasticElectronScatteringDistribution::sample( 
               const double incoming_energy,
               double& outgoing_energy,
               double& scattering_angle_cosine ) const
{
  // The outgoing energy is always equal to the incoming energy
  outgoing_energy = incoming_energy;

  unsigned trial_dummy;

  // Sample an outgoing direction
  this->sampleAndRecordTrialsImpl( incoming_energy,
				                   scattering_angle_cosine,
				                   trial_dummy );
}

// Sample an outgoing energy and direction and record the number of trials
void SoftElasticElectronScatteringDistribution::sampleAndRecordTrials( 
                const double incoming_energy,
                double& outgoing_energy,
                double& scattering_angle_cosine,
                unsigned& trials ) const
{
  // The outgoing energy is always equal to the incoming energy
  outgoing_energy = incoming_energy;
  
  // Sample an outgoing direction
  this->sampleAndRecordTrialsImpl( incoming_energy,
				                   scattering_angle_cosine,
				                   trials );
}

// Randomly scatter the electron
void SoftElasticElectronScatteringDistribution::scatterElectron( 
                ElectronState& electron,
                ParticleBank& bank,
                SubshellType& shell_of_interaction ) const
{
  double scattering_angle_cosine;

  unsigned trial_dummy;

  // Sample an outgoing direction
  this->sampleAndRecordTrialsImpl( electron.getEnergy(),
				                   scattering_angle_cosine,
				                   trial_dummy );

  shell_of_interaction = UNKNOWN_SUBSHELL;

  // Set the new direction
  electron.rotateDirection( scattering_angle_cosine, 
			                this->sampleAzimuthalAngle() );
}
                        
// Randomly scatter the adjoint electron
void SoftElasticElectronScatteringDistribution::scatterAdjointElectron( 
                AdjointElectronState& adjoint_electron,
                ParticleBank& bank,
                SubshellType& shell_of_interaction ) const
{
  double scattering_angle_cosine;

  unsigned trial_dummy;

  // Sample an outgoing direction
  this->sampleAndRecordTrialsImpl( adjoint_electron.getEnergy(),
				                   scattering_angle_cosine,
				                   trial_dummy );
  
  shell_of_interaction = UNKNOWN_SUBSHELL;

  // Set the new direction
  adjoint_electron.rotateDirection( scattering_angle_cosine, 
				                    this->sampleAzimuthalAngle() );
}

// Sample an outgoing direction from the distribution
void SoftElasticElectronScatteringDistribution::sampleAndRecordTrialsImpl( 
                const double incoming_energy,
                double& scattering_angle_cosine,
                unsigned& trials ) const
{
  // Make sure the incoming energy is valid
  testPrecondition( incoming_energy > 0.0 );

  // Increment the number of trials
  ++trials;

  scattering_angle_cosine = MonteCarlo::sampleTwoDDistributionCorrelated(
                                incoming_energy,
                                d_discrete_scattering_distribution );

  // Make sure the scattering angle cosine is valid
  testPostcondition( scattering_angle_cosine >= -1.0 );
  testPostcondition( scattering_angle_cosine <= 1.0 );
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_ElasticElectronScatteringDistribution.hpp
//---------------------------------------------------------------------------//
