//---------------------------------------------------------------------------//
//!
//! \file   Facemc_ElasticNeutronScatteringDistribution.cpp
//! \author Alex Robinson
//! \brief  The elastic scattering distribution class definition
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <math.h>

// FRENSIE Includes
#include "Facemc_ElasticNeutronScatteringDistribution.hpp"
#include "Facemc_SimulationProperties.hpp"
#include "Utility_DirectionHelpers.hpp"
#include "Utility_ContractException.hpp"
#include "Utility_SortAlgorithms.hpp"
#include "Utility_PhysicalConstants.hpp"

namespace Facemc{

// Constructor
ElasticNeutronScatteringDistribution::ElasticNeutronScatteringDistribution(
		      const double atomic_weight_ratio,
		      const Teuchos::RCP<NeutronScatteringAngularDistribution>&
		      angular_scattering_distribution )
  : NeutronScatteringDistribution( atomic_weight_ratio ),
    d_angular_scattering_distribution( angular_scattering_distribution )
{ 
  // Make sure the atomic weight ratio is valid
  testPrecondition( atomic_weight_ratio > 0.0 );
  // Make sure the angular distribution pointer is valid
  testPrecondition( !angular_scattering_distribution.is_null() );
}

// Randomly scatter the neutron
/*! \details The energy of the neutron in the lab frame is used to sample
 * a center-of-mass scattering angle cosine (this is also done in openmc). It
 * may be more appropriate to instead use the energy of the neutron in the
 * target-at-rest frame as recommended in the MCNP manual.
 */ 
void ElasticNeutronScatteringDistribution::scatterNeutron( 
					      NeutronState& neutron,
					      const double temperature ) const
{
  // Use the target-at-rest kinematics
  if( neutron.getEnergy() > 
      SimulationProperties::getFreeGasThreshold()*temperature &&
      this->getAtomicWeightRatio() > 1.0 )
  {
    double A = this->getAtomicWeightRatio();
    
    // Sample the CM scattering angle cosine
    double cm_scattering_angle_cosine = 
      d_angular_scattering_distribution->sampleAngleCosine( 
							 neutron.getEnergy() );
    double outgoing_neutron_energy = neutron.getEnergy()*
      (2*A*cm_scattering_angle_cosine + 1 + A*A)/((A+1)*(A+1));
    double lab_scattering_angle_cosine = (A*cm_scattering_angle_cosine + 1)/
      sqrt(2*A*cm_scattering_angle_cosine + 1 + A*A);
    
    double outgoing_neutron_direction[3];
    
    Utility::rotateDirectionThroughPolarAndAzimuthalAngle( 
						lab_scattering_angle_cosine,
						sampleAzimuthalAngle(),
						neutron.getDirection(),
						outgoing_neutron_direction);

    // Make sure the lab scattering angle cosine is in [-1,1]
    testPostcondition( lab_scattering_angle_cosine >= -1.0 );
    testPostcondition( lab_scattering_angle_cosine <= 1.0 );
    
    neutron.setEnergy( outgoing_neutron_energy );
    
    neutron.setDirection( outgoing_neutron_direction );
  }
  // Use the free gas thermal model
 else
 {
   // NOTE: A relativistic treatment is used to convert the particle energy
   // to a speed and vice versa. To be consistent with the above treatment of
   // elastic scattering, a classical treatment must be used in the free gas
   // model.
   
   // Calculate the neutron velocity (classical)
   double incoming_neutron_speed = 
      Utility::PhysicalConstants::speed_of_light*
      sqrt(2*neutron.getEnergy()/
    	   Utility::PhysicalConstants::neutron_rest_mass_energy);
  
   double neutron_velocity[3] = 
     {neutron.getXDirection()*incoming_neutron_speed,
      neutron.getYDirection()*incoming_neutron_speed,
      neutron.getZDirection()*incoming_neutron_speed};

   // Sample the target velocity
   double target_velocity[3];
   
   sampleTargetVelocity( neutron, temperature, target_velocity );
   
   // Calculate the center-of-mass velocity
   double center_of_mass_velocity[3];
    
   calculateCenterOfMassVelocity( neutron_velocity,
				  target_velocity,
				  center_of_mass_velocity );
    
   // Transform the neutron velocity to the center-of-mass frame
   transformVelocityToCenterOfMassFrame( center_of_mass_velocity, 
					 neutron_velocity );
   
   // Calculate the neutron speed in the center-of-mass
   double cm_neutron_speed = Utility::vectorMagnitude( neutron_velocity );
    
   // Calculate the neutron direction in the center-of-mass frame
   double cm_neutron_direction[3] = {neutron_velocity[0]/cm_neutron_speed,
				     neutron_velocity[1]/cm_neutron_speed,
				     neutron_velocity[2]/cm_neutron_speed};

   // Sample the CM scattering angle cosine
   double cm_scattering_angle_cosine = 
     d_angular_scattering_distribution->sampleAngleCosine( 
							 neutron.getEnergy() );
   
   // Rotate the neutron velocity vector to the new angle
   // Note: The speed of the neutron does not change in the center-of-mass
   double cm_outgoing_neutron_direction[3];
    
   Utility::rotateDirectionThroughPolarAndAzimuthalAngle( 
						cm_scattering_angle_cosine,
						sampleAzimuthalAngle(),
						cm_neutron_direction,
						cm_outgoing_neutron_direction);

   neutron_velocity[0] = cm_neutron_speed*cm_outgoing_neutron_direction[0];
   neutron_velocity[1] = cm_neutron_speed*cm_outgoing_neutron_direction[1];
   neutron_velocity[2] = cm_neutron_speed*cm_outgoing_neutron_direction[2];

   // Transform back to the lab frame
   transformVelocityToLabFrame( center_of_mass_velocity, neutron_velocity );
   
   // Calculate the outgoing neutron speed
   double outgoing_neutron_speed = 
     Utility::vectorMagnitude( neutron_velocity );
   
   // Calculate and set the outgoing neutron energy
   double outgoing_neutron_energy = 
     0.5*Utility::PhysicalConstants::neutron_rest_mass_energy*
     outgoing_neutron_speed*outgoing_neutron_speed/
     (Utility::PhysicalConstants::speed_of_light*
      Utility::PhysicalConstants::speed_of_light);

   // Set the new neutron direction
   neutron.setDirection( neutron_velocity[0]/outgoing_neutron_speed,
			 neutron_velocity[1]/outgoing_neutron_speed,
			 neutron_velocity[2]/outgoing_neutron_speed );
   
   neutron.setEnergy( outgoing_neutron_energy );
 }
}

} // end Facemc namespace

//---------------------------------------------------------------------------//
// end Facemc_ElasticNeutronScatteringDistribution.cpp
//---------------------------------------------------------------------------//
