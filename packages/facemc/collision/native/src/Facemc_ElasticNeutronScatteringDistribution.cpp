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
#include "Utility_DirectionHelpers.hpp"
#include "Utility_ContractException.hpp"
#include "Utility_SearchAlgorithms.hpp"
#include "Utility_SortAlgorithms.hpp"

namespace Facemc{

// Constructor
ElasticNeutronScatteringDistribution::ElasticNeutronScatteringDistribution(
                                              const double atomic_weight_ratio,
					      const Teuchos::Array<Utility::Pair<double,Teuchos::RCP<Utility::OneDDistribution> > >& angular_scattering_distribution )
  : NeutronScatteringDistribution( atomic_weight_ratio ),
    d_angular_scattering_distribution( angular_scattering_distribution )
{ 
  // Make sure the array has at least one value
  testPrecondition( angular_scattering_distribution.size() > 0 );
  // Make sure that the array is sorted
  testPrecondition( Utility::Sort::isSortedAscending<Utility::FIRST>( 
				     angular_scattering_distribution.begin(),
				     angular_scattering_distribution.end() ) );
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
  // Calculate the neutron velocity
  double neutron_velocity[3] = {neutron.getXDirection()*neutron.getSpeed(),
				neutron.getYDirection()*neutron.getSpeed(),
				neutron.getZDirection()*neutron.getSpeed()};
    
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

  // Sample the scattering angle 
  double cm_scattering_angle_cosine = 
    sampleCMScatteringAngleCosine( neutron.getEnergy() );

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
  double outgoing_neutron_speed = Utility::vectorMagnitude( neutron_velocity );

  // Set the new neutron direction
  neutron.setDirection( neutron_velocity[0]/outgoing_neutron_speed,
			neutron_velocity[1]/outgoing_neutron_speed,
			neutron_velocity[2]/outgoing_neutron_speed );

  // Calculate and set the outgoing neutron energy  
  neutron.setSpeed( outgoing_neutron_speed );
}

// Sample a center-of-mass scattering angle cosine
double ElasticNeutronScatteringDistribution::sampleCMScatteringAngleCosine(
						    const double energy ) const
{
  double cm_scattering_angle_cosine;

  if( energy < d_angular_scattering_distribution.front().first )
  {
    cm_scattering_angle_cosine = 
      d_angular_scattering_distribution.front().second->sample();
  }
  else if( energy >= d_angular_scattering_distribution.back().first )
  {
    cm_scattering_angle_cosine = 
      d_angular_scattering_distribution.back().second->sample();
  }
  else
  {
    Teuchos::Array<Utility::Pair<double,Teuchos::RCP<Utility::OneDDistribution> > >::const_iterator
      lower_bin_boundary, upper_bin_boundary;
    
    lower_bin_boundary = d_angular_scattering_distribution.begin();
    upper_bin_boundary = d_angular_scattering_distribution.end();
    
    lower_bin_boundary = Utility::Search::binaryLowerBound<Utility::FIRST>( 
							  lower_bin_boundary,
							  upper_bin_boundary,
							  energy );

    upper_bin_boundary = lower_bin_boundary;
    ++upper_bin_boundary;
    
    double lower_bin_boundary_probability = 
      (upper_bin_boundary->first - energy)/
      (upper_bin_boundary->first - lower_bin_boundary->first);
    
    if( Utility::RandomNumberGenerator::getRandomNumber<double>() < 
	lower_bin_boundary_probability )
      cm_scattering_angle_cosine = lower_bin_boundary->second->sample();
    else
      cm_scattering_angle_cosine = upper_bin_boundary->second->sample();
  }

  // Due to floating-point roundoff, it is possible for the scattering angle
  // cosine to be outside [-1,1]. When this occurs, manually set to -1 or 1.
  if(Teuchos::ScalarTraits<double>::magnitude(cm_scattering_angle_cosine) >1.0)
    cm_scattering_angle_cosine = copysign( 1.0, cm_scattering_angle_cosine );

  // Make sure that the scattering angle cosine is valid
  testPrecondition( cm_scattering_angle_cosine >= -1.0 );
  testPrecondition( cm_scattering_angle_cosine <= 1.0 );

  return cm_scattering_angle_cosine;
}								    

} // end Facemc namespace

//---------------------------------------------------------------------------//
// end Facemc_ElasticNeutronScatteringDistribution.cpp
//---------------------------------------------------------------------------//
