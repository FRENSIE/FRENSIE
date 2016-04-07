//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_IncoherentPhotonScatteringDistribution.cpp
//! \author Alex Robinson, Luke Kersting
//! \brief  The incoherent photon scattering distribution definition.
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <limits>

// FRENSIE Includes
#include "MonteCarlo_IncoherentPhotonScatteringDistribution.hpp"
#include "MonteCarlo_PhotonKinematicsHelpers.hpp"
#include "MonteCarlo_ElectronState.hpp"
#include "MonteCarlo_PhotonKinematicsHelpers.hpp"
#include "MonteCarlo_SimulationPhotonProperties.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_GaussKronrodIntegrator.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Constructor without doppler broadening
/*! \details The recoil electron momentum (scattering function independent 
 * variable) should have units of 1/cm.
 */ 
IncoherentPhotonScatteringDistribution::IncoherentPhotonScatteringDistribution(
				     const double kahn_sampling_cutoff_energy )
  : d_kahn_sampling_cutoff_energy( kahn_sampling_cutoff_energy )
{
  // Make sure the cutoff energy is valid
  testPrecondition( kahn_sampling_cutoff_energy >= 
		    SimulationPhotonProperties::getAbsoluteMinKahnSamplingCutoffEnergy() );
}

// Evaluate the PDF
double IncoherentPhotonScatteringDistribution::evaluatePDF( 
				   const double incoming_energy,
				   const double scattering_angle_cosine ) const
{
  // Make sure the incoming energy is valid
  testPrecondition( incoming_energy > 0.0 );
  // Make sure the scattering angle cosine is valid
  testPrecondition( scattering_angle_cosine >= -1.0 );
  testPrecondition( scattering_angle_cosine <= 1.0 );

  return this->evaluate( incoming_energy, scattering_angle_cosine )/
    this->evaluateIntegratedCrossSection( incoming_energy, 1e-3 );
}

// Evaluate the Klein-Nishina distribution
/*! The Klein-Nishina cross section (b) differential in the scattering angle 
 * cosine is returned from this function.
 */
double IncoherentPhotonScatteringDistribution::evaluateKleinNishinaDist( 
				   const double incoming_energy,
				   const double scattering_angle_cosine ) const
{
  // Make sure the energy is valid
  testPrecondition( incoming_energy > 0.0 );
  // Make sure the scattering angle cosine is valid
  testPrecondition( scattering_angle_cosine >= -1.0 );
  testPrecondition( scattering_angle_cosine <= 1.0 );
  
  const double mult = Utility::PhysicalConstants::pi*
    Utility::PhysicalConstants::classical_electron_radius*
    Utility::PhysicalConstants::classical_electron_radius;

  const double outgoing_energy = 
    calculateComptonLineEnergy( incoming_energy, scattering_angle_cosine );

  return mult*1e24*((outgoing_energy*outgoing_energy)/
	    (incoming_energy*incoming_energy))*
    (outgoing_energy/incoming_energy + incoming_energy/outgoing_energy - 1.0 +
     scattering_angle_cosine*scattering_angle_cosine);
}

// Klein-Nishina sampling implementation
void IncoherentPhotonScatteringDistribution::sampleAndRecordTrialsKleinNishina(
					    const double incoming_energy,
					    double& outgoing_energy,
					    double& scattering_angle_cosine,
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

// Create ejected electron
void IncoherentPhotonScatteringDistribution::createEjectedElectron( 
					  const PhotonState& photon,
				          const double scattering_angle_cosine,
					  const double azimuthal_angle,
					  ParticleBank& bank ) const
{
  // Make sure the incoming energy is valid
  testPrecondition( photon.getEnergy() > 0.0 );
  // Make sure the scattering angle cosine is valid
  testPrecondition( scattering_angle_cosine >= -1.0 );
  testPrecondition( scattering_angle_cosine <= 1.0 );
  // Make sure the azimuthal angle is valid
  testPrecondition( azimuthal_angle >= 0.0 );
  testPrecondition( azimuthal_angle <= 2*Utility::PhysicalConstants::pi );
  
  // Calculate the compton line energy
  const double compton_line_energy = 
    calculateComptonLineEnergy( photon.getEnergy(), 
				scattering_angle_cosine );
    
  double electron_energy = photon.getEnergy() - compton_line_energy;

  double electron_scattering_angle_cosine = 
    (photon.getEnergy() - compton_line_energy*scattering_angle_cosine)/
    sqrt(electron_energy*electron_energy + 2*electron_energy*
	 Utility::PhysicalConstants::electron_rest_mass_energy );

  // Due to floating-point roundoff, it is possible for the scattering angle
  // cosine to be outside [-1,1]. When this occurs, manually set to -1 or 1.
  if( fabs( electron_scattering_angle_cosine ) > 1.0 )
  {
    electron_scattering_angle_cosine = 
      copysign( 1.0, electron_scattering_angle_cosine );
  }
  
  // Create the new electron
  if( electron_energy > 0.0 )
  {
    Teuchos::RCP<ParticleState> electron( 
				     new ElectronState( photon, true, true ) );

    electron->setEnergy( electron_energy );
    
    double electron_azimuthal_angle = azimuthal_angle;
    
    if( azimuthal_angle <= Utility::PhysicalConstants::pi )
      electron_azimuthal_angle += Utility::PhysicalConstants::pi;
    else
      electron_azimuthal_angle -= Utility::PhysicalConstants::pi;

    electron->rotateDirection( electron_scattering_angle_cosine,
			       electron_azimuthal_angle );

    bank.push( electron );
  }

  // Make sure the electron energy is valid
  testPostcondition( fabs(electron_energy + compton_line_energy - photon.getEnergy()) < 1e-12 );
  // Make sure the electron scattering angle cosine is valid
  testPostcondition( electron_scattering_angle_cosine >= -1.0 );
  testPostcondition( electron_scattering_angle_cosine <= 1.0 );
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_IncoherentPhotonScatteringDistribution.cpp
//---------------------------------------------------------------------------//
