//---------------------------------------------------------------------------//
//!
//! \file   Facemc_Law44NeutronScatteringDistribution_def.hpp
//! \author Alex Bennett
//! \brief  The law 44 scattering distribution class definition
//!
//---------------------------------------------------------------------------//

#ifndef FACEMC_LAW_44_NEUTRON_SCATTERING_DISTRIBUTION_DEF
#define FACEMC_LAW_44_NEUTRON_SCATTERING_DISTRIBUTION_DEF

// Trilinos Includes
#include <Teuchos_RCPDecl.hpp>

// Std Lib Includes
#include <math.h>

// FRENSIE Includes
#include "Facemc_Law44NeutronScatteringDistribution.hpp"
#include "Facemc_NeutronScatteringEnergyDistribution.hpp"
#include "Utility_DirectionHelpers.hpp"
#include "Utility_ContractException.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_Tuple.hpp"

namespace Facemc{

// Constructor
template<typename Law44InterpolationPolicy>
Law44NeutronScatteringDistribution<Law44InterpolationPolicy>::Law44NeutronScatteringDistribution( 
                      const double atomic_weight_ratio,
		      const Teuchos::RCP<NeutronScatteringEnergyDistribution>& energy_scattering_distribution,
		      Law44NeutronScatteringDistribution::ScatteringDistribution& scattering_distribution)
   : NeutronScatteringDistribution( atomic_weight_ratio ),
     d_energy_scattering_distribution( energy_scattering_distribution ),
     d_scattering_distribution( scattering_distribution )
{
  // Check to make sure the energy distribution pointer is valid
  testPrecondition( !energy_scattering_distribution.is_null() );
  // Make sure the energy distribution is not in the CM
  testPrecondition( !energy_scattering_distribution->isCMDistribution() );
}

// Randomly scatter the neutron
template<typename Law44InterpolationPolicy>
void Law44NeutronScatteringDistribution<Law44InterpolationPolicy>::scatterNeutron(
					       NeutronState& neutron,
                                               const double ) const
{
  unsigned sampled_bin_index, incoming_bin_index;

  double energy_prime;

  // Sample the energy of the neutron
  double energy = d_energy_scattering_distribution->sampleEnergy( neutron.getEnergy(),
                                                                  sampled_bin_index,
                                                                  incoming_bin_index,
                                                                  energy_prime );

   

  double interpolated_r = Law44InterpolationPolicy::interpolate(energy_prime,
                                                   d_scattering_distribution[incoming_bin_index].second[sampled_bin_index],
                                                   d_scattering_distribution[incoming_bin_index].second[sampled_bin_index+1],
                                                   d_scattering_distribution[incoming_bin_index].third[sampled_bin_index],
                                                   d_scattering_distribution[incoming_bin_index].third[sampled_bin_index+1] );

  double interpolated_a = Law44InterpolationPolicy::interpolate(energy_prime,
                                                   d_scattering_distribution[incoming_bin_index].second[sampled_bin_index],
                                                   d_scattering_distribution[incoming_bin_index].second[sampled_bin_index+1],
                                                   d_scattering_distribution[incoming_bin_index].fourth[sampled_bin_index],
                                                   d_scattering_distribution[incoming_bin_index].fourth[sampled_bin_index+1] );


  double random_num = Utility::RandomNumberGenerator::getRandomNumber<double>();

  double scattering_angle;

  if( Utility::RandomNumberGenerator::getRandomNumber<double>() > interpolated_r )
  {
    double t = (2 * random_num - 1) * sinh(interpolated_a);

    scattering_angle = log(t + sqrt(t * t + 1) ) / interpolated_a;
  }
  else
  {
    scattering_angle = log(random_num * exp(interpolated_a) + (1 - random_num) * exp(-interpolated_a)) / interpolated_a; 
  }

  // Rotate the neutron to the new angle
  double outgoing_neutron_direction[3];
  
  Utility::rotateDirectionThroughPolarAndAzimuthalAngle(
						  scattering_angle,
						  sampleAzimuthalAngle(),
						  neutron.getDirection(),
						  outgoing_neutron_direction );

  // Set the new energy
  neutron.setEnergy( energy );
  
  // Set the new direction
  neutron.setDirection( outgoing_neutron_direction );
}

} // End Facemc namespace

#endif // end FACEMC_LAW_44_NEUTRON_SCATTERING_DISTRIBUTION_DEF

//---------------------------------------------------------------------------//
// end Facemc_Law44NeutronScatteringDistribution_def.hpp
//---------------------------------------------------------------------------//
