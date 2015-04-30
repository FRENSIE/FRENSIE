//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ThompsonPhotonScatteringDistribution.cpp
//! \author Alex Robinson
//! \brief  The Thompson photon scattering distribution class definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_ThompsonPhotonScatteringDistribution.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Default constructor
ThompsonPhotonScatteringDistribution::ThompsonPhotonScatteringDistribution()
{ /* ... */ }

// Evaluate the distribution
double ThompsonPhotonScatteringDistribution::evaluate( 
				   const double incoming_energy,
				   const double scattering_angle_cosine ) const
{
  // Make sure the incoming energy is valid
  testPrecondition( incoming_energy > 0.0 );
  // Make sure the scattering angle cosine is valid
  testPrecondition( scattering_angle_cosine >= -1.0 );
  testPrecondition( scattering_angle_cosine <= 1.0 );

  const double mult = Utility::PhysicalConstants::pi*
    Utility::PhysicalConstants::classical_electron_radius*
    Utility::PhysicalConstants::classical_electron_radius;

  return mult*(1.0 + scattering_angle_cosine*scattering_angle_cosine);
}

// Evaluate the PDF
double ThompsonPhotonScatteringDistribution::evaluatePDF( 
				   const double incoming_energy,
				   const double scattering_angle_cosine ) const
{
  // Make sure the incoming energy is valid
  testPrecondition( incoming_energy > 0.0 );
  // Make sure the scattering angle cosine is valid
  testPrecondition( scattering_angle_cosine >= -1.0 );
  testPrecondition( scattering_angle_cosine <= 1.0 );

  return this->evaluate( incoming_energy, scattering_angle_cosine )/
    this->evaluateIntegratedCrossSection( incoming_energy, 1e-6 );
}

// Evaluate the integrated cross section (cm^2)
double ThompsonPhotonScatteringDistribution::evaluateIntegratedCrossSection(
						 const double incoming_energy,
						 const double precision ) const
{
  // Make sure the incoming energy is valid
  testPrecondition( incoming_energy > 0.0 );

  return (8.0/3.0)*Utility::PhysicalConstants::pi*
    Utility::PhysicalConstants::classical_electron_radius*
    Utility::PhysicalConstants::classical_electron_radius;
}

// Sample an outgoing energy and direction from the distribution
void ThompsonPhotonScatteringDistribution::sample( 
				     const double incoming_energy,
				     double& outgoing_energy,
				     double& scattering_angle_cosine,
				     SubshellType& shell_of_interaction ) const
{
  // Make sure the incoming energy is valid
  testPrecondition( incoming_energy > 0.0 );

  unsigned trial_dummy;

  this->sampleAndRecordTrials( incoming_energy,
			       outgoing_energy,
			       scattering_angle_cosine,
			       shell_of_interaction,
			       trial_dummy );
}

// Sample an outgoing energy and direction and record the number of trials
void ThompsonPhotonScatteringDistribution::sampleAndRecordTrials( 
					    const double incoming_energy,
					    double& outgoing_energy,
					    double& scattering_angle_cosine,
					    SubshellType& shell_of_interaction,
					    unsigned& trials ) const
{
  // Make sure the incoming energy is valid
  testPrecondition( incoming_energy > 0.0 );

  // Increment the number of trials
  ++trials;

  // Use the probability mixing technique to sample an outgoing angle
  double random_number_1 = 
    Utility::RandomNumberGenerator::getRandomNumber<double>();
  double random_number_2 = 
    Utility::RandomNumberGenerator::getRandomNumber<double>();
    
  if( random_number_1 <= 0.75 )
    scattering_angle_cosine = 2*random_number_2 - 1.0;
  else
  {
    scattering_angle_cosine = pow( fabs(2*random_number_2 - 1.0), 1.0/3.0 );

    if( random_number_2 < 0.5 )
      scattering_angle_cosine *= -1.0;
  }

  // Check for roundoff error
  if( fabs( scattering_angle_cosine ) > 1.0 )
    scattering_angle_cosine = copysign( 1.0, scattering_angle_cosine );

  // There is no change in energy for Thompson scattering
  outgoing_energy = incoming_energy;
  
  // The shell is not relevant for free electron scattering
  shell_of_interaction = UNKNOWN_SUBSHELL;

  // Make sure the outgoing energy is valid
  testPostcondition( outgoing_energy == incoming_energy );
  // Make sure the scattering angle cosine is valid
  testPostcondition( scattering_angle_cosine >= -1.0 );
  testPostcondition( scattering_angle_cosine <= 1.0 );
}

// Randomly scatter the photon
void ThompsonPhotonScatteringDistribution::scatterPhoton( 
				     PhotonState& photon,
				     ParticleBank& bank,
				     SubshellType& shell_of_interaction ) const
{
  double outgoing_energy, scattering_angle_cosine;

  this->sample( photon.getEnergy(),
		outgoing_energy,
		scattering_angle_cosine,
		shell_of_interaction );

  photon.rotateDirection( scattering_angle_cosine,
			  this->sampleAzimuthalAngle() );
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_ThompsonPhotonScatteringDistribution.cpp
//---------------------------------------------------------------------------//
