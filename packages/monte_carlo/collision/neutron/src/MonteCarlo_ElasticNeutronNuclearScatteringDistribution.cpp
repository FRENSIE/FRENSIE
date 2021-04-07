//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ElasticNeutronNuclearScatteringDistribution_def.hpp
//! \author Alex Robinson
//! \brief  The elastic scattering distribution class definition
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <math.h>

// FRENSIE Includes
#include "MonteCarlo_ElasticNeutronNuclearScatteringDistribution.hpp"
#include "MonteCarlo_SimulationNeutronProperties.hpp"
#include "MonteCarlo_KinematicHelpers.hpp"
#include "Utility_3DCartesianVectorHelpers.hpp"
#include "Utility_DesignByContract.hpp"
#include "Utility_SortAlgorithms.hpp"
#include "Utility_PhysicalConstants.hpp"

namespace MonteCarlo{

// Constructor
ElasticNeutronNuclearScatteringDistribution::ElasticNeutronNuclearScatteringDistribution(
             const double atomic_weight_ratio,
             const double free_gas_threshold,
	     const std::shared_ptr<const NuclearScatteringAngularDistribution>&
             angular_scattering_distribution )
  : NuclearScatteringDistribution( atomic_weight_ratio ),
    d_free_gas_threshold( free_gas_threshold ),
    d_angular_scattering_distribution( angular_scattering_distribution )
{
  // Make sure the atomic weight ratio is valid
  testPrecondition( atomic_weight_ratio > 0.0 );
  // Make sure the free gas threshold is valid
  testPrecondition( free_gas_threshold > 0.0 );
  // Make sure the angular distribution pointer is valid
  testPrecondition( angular_scattering_distribution.get() );
}

// Randomly scatter the nuclear
/*! \details The energy of the nuclear in the lab frame is used to sample
 * a center-of-mass scattering angle cosine (this is also done in openMC). It
 * may be more appropriate to instead use the energy of the nuclear in the
 * target-at-rest frame as recommended in the MCNP manual.
 */
void ElasticNeutronNuclearScatteringDistribution::scatterParticle(
				        const NeutronState& incoming_neutron,
					NeutronState& outgoing_neutron,
					const double temperature ) const
{
  // Use the target-at-rest kinematics
  if( incoming_neutron.getEnergy() > d_free_gas_threshold*temperature &&
      this->getAtomicWeightRatio() > 1.0 )
  {
    double A = this->getAtomicWeightRatio();

    // Sample the CM scattering angle cosine
    double cm_scattering_angle_cosine =
      d_angular_scattering_distribution->sampleAngleCosine(
					       incoming_neutron.getEnergy() );
    double outgoing_neutron_energy = incoming_neutron.getEnergy()*
      (2*A*cm_scattering_angle_cosine + 1 + A*A)/((A+1)*(A+1));
    double lab_scattering_angle_cosine = (A*cm_scattering_angle_cosine + 1)/
      sqrt(2*A*cm_scattering_angle_cosine + 1 + A*A);

    double outgoing_neutron_direction[3];

    Utility::rotateUnitVectorThroughPolarAndAzimuthalAngle(
					       lab_scattering_angle_cosine,
                                               sampleAzimuthalAngle(),
					       incoming_neutron.getDirection(),
                                               outgoing_neutron_direction);

    // Make sure the lab scattering angle cosine is in [-1,1]
    testPostcondition( lab_scattering_angle_cosine >= -1.0 );
    testPostcondition( lab_scattering_angle_cosine <= 1.0 );

    outgoing_neutron.setEnergy( outgoing_neutron_energy );

    outgoing_neutron.setDirection( outgoing_neutron_direction );
  }
  // Use the free gas thermal model
 else
 {
   // NOTE: A relativistic treatment is used to convert the neutron energy
   // to a speed and vice versa. To be consistent with the above treatment of
   // elastic scattering, a classical treatment must be used in the free gas
   // model.

   // Calculate the neutron velocity (classical)
   double incoming_neutron_speed = MonteCarlo::calculateSpeed(
			  Utility::PhysicalConstants::neutron_rest_mass_energy,
			  incoming_neutron.getEnergy() );

   double neutron_velocity[3] =
     {incoming_neutron.getXDirection()*incoming_neutron_speed,
      incoming_neutron.getYDirection()*incoming_neutron_speed,
      incoming_neutron.getZDirection()*incoming_neutron_speed};

   // Sample the target velocity
   double target_velocity[3];

   this->sampleTargetVelocity( incoming_neutron,
                               temperature,
                               target_velocity );

   // Calculate the center-of-mass velocity
   double center_of_mass_velocity[3];

   this->calculateCenterOfMassVelocity( neutron_velocity,
                                        target_velocity,
                                        center_of_mass_velocity );

   // Transform the neutron velocity to the center-of-mass frame
   this->transformVelocityToCenterOfMassFrame( center_of_mass_velocity,
                                               neutron_velocity );

   // Calculate the neutron speed in the center-of-mass
   double cm_neutron_speed = Utility::vectorMagnitude( neutron_velocity );

   // Calculate the neutron direction in the center-of-mass frame
   double cm_neutron_direction[3] = {neutron_velocity[0]/cm_neutron_speed,
				     neutron_velocity[1]/cm_neutron_speed,
				     neutron_velocity[2]/cm_neutron_speed};

   // Eliminate roundoff errors from the previous division operation
   Utility::normalizeVector( cm_neutron_direction );

   // Sample the CM scattering angle cosine
   double cm_scattering_angle_cosine =
     d_angular_scattering_distribution->sampleAngleCosine(
					       incoming_neutron.getEnergy() );

   // Rotate the neutron velocity vector to the new angle
   // Note: The speed of the neutron does not change in the center-of-mass
   double cm_outgoing_neutron_direction[3];

   Utility::rotateUnitVectorThroughPolarAndAzimuthalAngle(
						cm_scattering_angle_cosine,
						sampleAzimuthalAngle(),
						cm_neutron_direction,
						cm_outgoing_neutron_direction);

   neutron_velocity[0] = cm_neutron_speed*cm_outgoing_neutron_direction[0];
   neutron_velocity[1] = cm_neutron_speed*cm_outgoing_neutron_direction[1];
   neutron_velocity[2] = cm_neutron_speed*cm_outgoing_neutron_direction[2];

   // Transform back to the lab frame
   this->transformVelocityToLabFrame( center_of_mass_velocity,
                                      neutron_velocity );

   // Calculate the outgoing neutron speed
   double outgoing_neutron_speed =
     Utility::vectorMagnitude( neutron_velocity );

   // Calculate and set the outgoing neutron energy (classical)
   double outgoing_neutron_energy =
     MonteCarlo::calculateKineticEnergy(
			  Utility::PhysicalConstants::neutron_rest_mass_energy,
			  outgoing_neutron_speed );

   // Set the new neutron direction
   outgoing_neutron.setDirection( neutron_velocity[0]/outgoing_neutron_speed,
                                  neutron_velocity[1]/outgoing_neutron_speed,
                                  neutron_velocity[2]/outgoing_neutron_speed);

   outgoing_neutron.setEnergy( outgoing_neutron_energy );
 }
}

// Sample the velocity of the target nucleus
/*! \details the temperature should be in units of MeV (kT)
 */
void ElasticNeutronNuclearScatteringDistribution::sampleTargetVelocity(
					      const ParticleState& neutron,
					      const double temperature,
				        double target_velocity[3] ) const
{
  // Check if the energy is above the free gas thermal treatment threshold
  double target_speed, mu_target;

  double neutron_speed = neutron.getSpeed();

  while( true )
  {
    // Sample the target speed
    target_speed = sampleTargetSpeed( neutron, temperature );

    // Sample the cosine of the angle between the neutron and target velocity
    mu_target =
      2*Utility::RandomNumberGenerator::getRandomNumber<double>() - 1.0;

    // Calculate the acceptance probability
    double acceptance_probability =
      sqrt( neutron_speed*neutron_speed + target_speed*target_speed -
	    2*neutron_speed*target_speed*mu_target)/
      (neutron_speed+target_speed);

    if( Utility::RandomNumberGenerator::getRandomNumber<double>() <
	acceptance_probability )
      break;
  }

  // Calculate the velocity of the target nucleus
  if( target_speed > 0.0 )
  {
    Utility::rotateUnitVectorThroughPolarAndAzimuthalAngle(
							mu_target,
						        sampleAzimuthalAngle(),
							neutron.getDirection(),
							target_velocity );
  }

  target_velocity[0] *= target_speed;
  target_velocity[1] *= target_speed;
  target_velocity[2] *= target_speed;
}

// Sample the speed of the target nucleus
/*! \details the temperature should be in units of MeV (kT)
 */
double ElasticNeutronNuclearScatteringDistribution::sampleTargetSpeed(
					      const ParticleState& neutron,
					      const double temperature ) const
{
  double target_speed;

  // Calculate beta [=] s/cm
  double beta =
    sqrt(this->getAtomicWeightRatio()*
	 Utility::PhysicalConstants::neutron_rest_mass_energy/
	 (2*temperature))/Utility::PhysicalConstants::speed_of_light;

  // The sampling scheme branching probability (alpha)
  double alpha = 1.0/(1.0 + sqrt(Utility::PhysicalConstants::pi)*beta*
		      neutron.getSpeed()/2);

  // Sample two random numbers
  double random_number_1 =
    Utility::RandomNumberGenerator::getRandomNumber<double>();
  double random_number_2 =
    Utility::RandomNumberGenerator::getRandomNumber<double>();

  // The value sampled from the transformed distributions
  double y;

  // With probability alpha, sample from p(y) = y*exp(-y) => C45 from MC Samp
  if( Utility::RandomNumberGenerator::getRandomNumber<double>() < alpha )
  {
    y = -log(random_number_1*random_number_2);

    target_speed = sqrt(y)/beta;
  }

  // With probability 1-alpha, sample from p(y) = y^2*exp(-y^2) => C61
  else
  {
    double tau =
      cos(Utility::PhysicalConstants::pi/2*
	  Utility::RandomNumberGenerator::getRandomNumber<double>());
    y = sqrt(-log(random_number_1) - log(random_number_2)*tau*tau);

    target_speed = y/beta;
  }

  // Make sure the target speed is valid
  testPostcondition( target_speed >= 0.0 );
  testPostcondition( target_speed < std::numeric_limits<double>::infinity());

  return target_speed;
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_ElasticNeutronNuclearScatteringDistribution_def.hpp
//---------------------------------------------------------------------------//
