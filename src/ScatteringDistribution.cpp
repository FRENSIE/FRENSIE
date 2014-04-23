//---------------------------------------------------------------------------//
//!
//! \file   ScatteringDistribution.cpp
//! \author Alex Robinson
//! \brief  The scattering distribution base class definition
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <limits>

// Trilinos Includes
#include <Teuchos_ScalarTraits.hpp>

// FACEMC Includes
#include "ScatteringDistribution.hpp"
#include "DirectionHelpers.hpp"
#include "ContractException.hpp"

namespace FACEMC{

// Initialize the static member data
unsigned ScatteringDistribution::free_gas_threshold = 400u;

// Constructor
ScatteringDistribution::ScatteringDistribution( 
					     const double atomic_weight_ratio )
  : d_atomic_weight_ratio( atomic_weight_ratio )
{
  // Make sure the atomic weight ratio is valid
  testPrecondition( atomic_weight_ratio > 0.0 );
  testPrecondition( atomic_weight_ratio < 
		    std::numeric_limits<double>::infinity() );
}

// Set the free gas thermal treatment temperature threshold
/*! \details The value given is the number of times above the material 
 * temperature that the energy of a neutron can be before the free gas
 * thermal treatment is not used anymore.
 */
void ScatteringDistribution::setFreeGasThermalTreatmentTemperatureThreshold(
					   const double temperature_threshold )
{
  ScatteringDistribution::free_gas_threshold = temperature_threshold;
}

// Sample the velociy of the target nucleus
/*! \details the temperature should be in units of MeV (kT)
 */ 
void ScatteringDistribution::sampleTargetVelocity(
					      BasicParticleState& particle,
					      const double temperature,
				              double target_velocity[3] ) const
{
  // Check if the energy is above the free gas thermal treatment threshold
  if( particle.getEnergy() > 
      ScatteringDistribution::free_gas_threshold*temperature &&
      d_atomic_weight_ratio > 1.0 )
  {
    target_velocity[0] = 0.0;
    target_velocity[1] = 0.0;
    target_velocity[2] = 0.0;
  }
  else
  {
    double target_speed, mu_target;
    
    double neutron_speed = particle.getSpeed();
    
    while( true )
    {
      // Sample the target speed
      target_speed = sampleTargetSpeed( particle, temperature );
      
      // Sample the cosine of the angle between the neutron and target velocity
      mu_target = 2*RandomNumberGenerator::getRandomNumber<double>() - 1.0;
      
      // Calculate the acceptance probability
      double acceptance_probability = 
	sqrt( neutron_speed*neutron_speed + target_speed*target_speed - 
	      2*neutron_speed*target_speed*mu_target)/
	(neutron_speed+target_speed);
      
      if( RandomNumberGenerator::getRandomNumber<double>() < 
	  acceptance_probability )
	break;
    }
    
    // Calculate the velocity of the target nucleus
    if( target_speed > 0.0 )
    {
      rotateDirectionThroughPolarAndAzimuthalAngle( mu_target,
						    sampleAzimuthalAngle(),
						    particle.getDirection(),
						    target_velocity );
    }
    
    target_velocity[0] *= target_speed;
    target_velocity[1] *= target_speed;
    target_velocity[2] *= target_speed;
  }
}

// Sample the speed of the target nucleus
/*! \details the temperature should be in units of MeV (kT)
 */
double ScatteringDistribution::sampleTargetSpeed( 
					      BasicParticleState& particle,
					      const double temperature ) const
{
  double target_speed;
  
  // Calculate beta [=] s/cm
  double beta = sqrt(d_atomic_weight_ratio*
		     PhysicalConstants::neutron_rest_mass_energy*
		     particle.getEnergy()/temperature)/
    PhysicalConstants::speed_of_light;
  
  // The sampling scheme branching probability (alpha)
  double alpha = 1.0/(1.0 + sqrt(PhysicalConstants::pi)*beta*
		      particle.getSpeed()/2);
  
  // Sample two random numbers
  double random_number_1 = RandomNumberGenerator::getRandomNumber<double>();
  double random_number_2 = RandomNumberGenerator::getRandomNumber<double>();
  
  // The value sampled from the transformed distributions
  double y;
  
  // With probability alpha, sample from p(y) = y*exp(-y) => C45 from MC Samp
  if( RandomNumberGenerator::getRandomNumber<double>() < alpha )
  {
    y = -log(random_number_1*random_number_2);
    
    target_speed = sqrt(y)/beta;
  }
  
  // With probability 1-alpha, sample from p(y) = y^2*exp(-y^2) => C61
  else
  {
    double tau = cos(PhysicalConstants::pi/2*
		     RandomNumberGenerator::getRandomNumber<double>());
    y = sqrt(-log(random_number_1) - log(random_number_2)*tau*tau);
    
    target_speed = y/beta;
  }
  
  // Make sure the target speed is valid
  testPostcondition( target_speed >= 0.0 );
  testPostcondition( target_speed < std::numeric_limits<double>::infinity());
  
  return target_speed;
}

} // end FACEMC namespace

//---------------------------------------------------------------------------//
// end ScatteringDistribution.cpp
//---------------------------------------------------------------------------//
