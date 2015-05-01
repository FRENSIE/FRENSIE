//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_KleinNishinaPhotonScatteringDistribution.cpp
//! \author Alex Robinson
//! \brief  The Klein-Nishina photon scattering distribution definition
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <limits>

// FRENSIE Includes
#include "MonteCarlo_KleinNishinaPhotonScatteringDistribution.hpp"
#include "Utility_UniformDistribution.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Default Constructor
KleinNishinaPhotonScatteringDistribution::KleinNishinaPhotonScatteringDistribution()
  : IncoherentPhotonScatteringDistribution( Teuchos::RCP<const Utility::OneDDistribution>( new Utility::UniformDistribution( 0.0, std::numeric_limits<double>::max(), 1.0 ) ), 3.0 )
{ /* ... */ }

// Constructor
/*! Above the cutoff energy Koblinger's direct sampling method will be used. 
 * Koblinger's method can only be used when the particle energy is above
 * (1 + sqrt(3))*me.
 */
KleinNishinaPhotonScatteringDistribution::KleinNishinaPhotonScatteringDistribution(
				     const double kahn_sampling_cutoff_energy )
  : IncoherentPhotonScatteringDistribution( Teuchos::RCP<const Utility::OneDDistribution>( new Utility::UniformDistribution( 0.0, std::numeric_limits<double>::max(), 1.0 ) ), 3.0 )
{
  
}

// Evaluate the integrated cross section (cm^2)
double 
KleinNishinaPhotonScatteringDistribution::evaluateIntegratedCrossSection(
						const double incoming_energy,
						const double precision ) const
{
  // Make sure the energy is valid
  testPrecondition( incoming_energy > 0.0 );
  
  const double alpha = 
    incoming_energy/Utility::PhysicalConstants::electron_rest_mass_energy;
  
  const double arg = 1.0 + 2.0*alpha;

  const double term_1 = (1.0 + alpha)/(alpha*alpha)*
    ((1.0 + arg)/arg - log(arg)/alpha);

  const double term_2 = log(arg)/(2.0*alpha);
  
  const double term_3 = -(arg + alpha)/(arg*arg);

  const double cross_section = 2.0*Utility::PhysicalConstants::pi*
    Utility::PhysicalConstants::classical_electron_radius*
    Utility::PhysicalConstants::classical_electron_radius*
    (term_1 + term_2 + term_3);

  // Make sure the cross section is valid
  testPostcondition( cross_section > 0.0 );

  return cross_section;
}

// Sample an outgoing energy and direction from the distribution
void KleinNishinaPhotonScatteringDistribution::sample( 
				     const double incoming_energy,
				     double& outgoing_energy,
				     double& scattering_angle_cosine,
				     SubshellType& shell_of_interaction ) const
{
  // Make sure the energy is valid
  testPrecondition( incoming_energy > 0.0 );
  
  unsigned trial_dummy;

  this->sampleAndRecordTrials( incoming_energy,
			       outgoing_energy,
			       scattering_angle_cosine,
			       shell_of_interaction,
			       trial_dummy );
}

// Sample an outgoing energy and direction and record the number of trials
void KleinNishinaPhotonScatteringDistribution::sampleAndRecordTrials( 
					    const double incoming_energy,
					    double& outgoing_energy,
					    double& scattering_angle_cosine,
					    SubshellType& shell_of_interaction,
					    unsigned& trials ) const
{
  // Make sure the incoming energy is valid
  testPrecondition( incoming_energy > 0.0 );

  // The unitless incoming energy
  const double alpha = 
      incoming_energy/Utility::PhysicalConstants::electron_rest_mass_energy;

  // The argument used by both sampling schemes
  const double arg = 1.0 + 2.0*alpha;
  
  // The sampled inverse energy loss ratio
  double x;

  // Use Kahn's rejection scheme
  if( incoming_energy < d_kahn_sampling_cutoff_energy )
  {
    const double branching_ratio = arg/(8.0 + arg);

    // Three random numbers are required by the rejection scheme
    double random_number_1, random_number_2, random_number_3;

    while( true )
    {
      // Generate new random numbers
      random_number_1 =
	Utility::RandomNumberGenerator::getRandomNumber<double>();
      random_number_2 =
	Utility::RandomNumberGenerator::getRandomNumber<double>();
      random_number_3 = 
	Utility::RandomNumberGenerator::getRandomNumber<double>();
      
      // Increment the number of trials
      ++trials;
      
      // Take the first branch
      if( random_number_1 <= branching_ratio )
      {
	x = 1.0 + 2.0*random_number_2*alpha;
	
	if( random_number_3 <= 4.0*(1.0/x - 1.0/(x*x)) )
	  break;
      }
      // Take the second branch
      else
      {
	x = (arg)/(1.0 + 2.0*random_number_2*alpha);
	
	double branch_arg = (1.0 - x)/alpha + 1.0;
	
	if( 2*random_number_3 <= branch_arg*branch_arg + 1.0/x )
	  break;
      }
    }
  }
  // Use Koblinger's direct sampling scheme
  else
  {
    // Increment the number of trials
    ++trials;

    // The mixing probabilities
    double p1 = 2.0/alpha;
    double p2 = (1.0 - (1.0 + arg)/(alpha*alpha))*log(arg);
    double p3 = p1;
    double p4 = 0.5*(1.0 - 1.0/(arg*arg));

    const double norm = p1+p2+p3+p4;

    p1 /= norm;
    p2 /= norm;
    p3 /= norm;
    p4 /= norm;
    
    // Sample from the individual pdfs
    double random_number_1 = 
      Utility::RandomNumberGenerator::getRandomNumber<double>();
    double random_number_2 = 
      Utility::RandomNumberGenerator::getRandomNumber<double>();
    
    if( random_number_1 <= p1 )
      x = 1.0 + 2.0*alpha*random_number_2;
    else if( random_number_1 <= p1+p2 )
      x = pow( arg, random_number_2 );
    else if( random_number_1 <= p1+p2+p3 )
      x = arg/(1.0 + 2.0*alpha*random_number_2 );
    else
      x = 1.0/sqrt(1.0 - random_number_2*(1.0 - 1.0/(arg*arg)));
  }

  // Calculate the outgoing energy
  outgoing_energy = incoming_energy/x;
  
  // Calculate the outgoing scattering angle cosine
  scattering_angle_cosine = 1.0 - (x - 1.0)/alpha;
  
  // Check for roundoff error
  if( fabs( scattering_angle_cosine ) > 1.0 )
    scattering_angle_cosine = copysign( 1.0, scattering_angle_cosine );

  // The shell is not relevant for free electron scattering
  shell_of_interaction = UNKNOWN_SUBSHELL;
  
  // Make sure the sampled inverse energy loss ratio is valid
  testPostcondition( x >= 1.0 );
  testPostcondition( x <= 1.0 + 2.0*alpha );
  // Make sure the compton line energy is valid
  testPostcondition( outgoing_energy <= incoming_energy );
  testPostcondition( outgoing_energy >= incoming_energy/(1+2*alpha) );
  // Make sure the scattering angle cosine is valid
  testPostcondition( scattering_angle_cosine >= -1.0 );
  testPostcondition( scattering_angle_cosine <= 1.0 );
}

// Randomly scatter the photon and return the shell that was interacted with
void KleinNishinaPhotonScatteringDistribution::scatterPhoton( 
				     PhotonState& photon,
				     ParticleBank& bank,
				     SubshellType& shell_of_interaction ) const
{
  double outgoing_energy, scattering_angle_cosine;

  this->sample( photon.getEnergy(),
		outgoing_energy,
		scattering_angle_cosine,
		shell_of_interaction );

  photon.setEnergy( outgoing_energy );

  photon.rotateDirection( scattering_angle_cosine, 
			  this->sampleAzimuthalAngle() );
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_KleinNishinaPhotonScatteringDistribution.cpp
//---------------------------------------------------------------------------//
