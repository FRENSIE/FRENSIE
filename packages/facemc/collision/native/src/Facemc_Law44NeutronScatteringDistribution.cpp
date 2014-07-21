//---------------------------------------------------------------------------//
//!
//! \file   Facemc_Law44NeutronScatteringDistribution.cpp
//! \author Alex Bennett
//! \brief  The law 44 scattering distribution class definition
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <math.h>

// FRENSIE Includes
#include "Facemc_Law44NeutronScatteringDistribution.hpp"
#include "Facemc_NeutronScatteringEnergyDistribution.hpp"
#include "Utility_DirectionHelpers.hpp"
#include "Utility_ContractException.hpp"
#include "Utility_RandomNumberGenerator.hpp"

namespace Facemc{

// Constructor
Law44NeutronScatteringDistribution::Law44NeutronScatteringDistribution( 
                      const double atomic_weight_ratio,
		      const Teuchos::RCP<NeutronScatteringEnergyDistribution>& 
		      energy_scattering_distribution,
		      const Teuchos::Array<Teuchos::RCP<Law44ARDistribution> >&
		      ar_distributions )
   : NeutronScatteringDistribution( atomic_weight_ratio ),
     d_energy_scattering_distribution( energy_scattering_distribution ),
     d_ar_distributions( ar_distributions )
{
  // Make sure the energy distribution pointer is valid
  testPrecondition( !energy_scattering_distribution.is_null() );
  // Make sure the energy distribution is not in the CM
  testPrecondition( !energy_scattering_distribution->isCMDistribution() );
  // Make sure the energy scattering distribution and the ar distribution have
  // the same size
  testPrecondition( energy_scattering_distribution.size() ==
		    ar_distributions.size() );
}

// Randomly scatter the neutron
void Law44NeutronScatteringDistribution::scatterNeutron(
					       NeutronState& neutron,
                                               const double ) const
{
  unsigned outgoing_bin_index, incoming_bin_index;

  double energy_prime;

  // Sample the energy of the neutron
  double energy = 
    d_energy_scattering_distribution->sampleEnergy( neutron.getEnergy(),
						    incoming_bin_index,
						    outgoing_bin_index,
						    energy_prime );
  
  double a, r;
  
  d_ar_distribution[incoming_energy_bin]->sampleAR( outgoing_index,
						    energy_prime,
						    a, 
						    r );

  double random_num = 
    Utility::RandomNumberGenerator::getRandomNumber<double>();

  double scattering_angle;

  if( Utility::RandomNumberGenerator::getRandomNumber<double>() > r )
  {
    double t = (2 * random_num - 1) * sinh(a);

    scattering_angle = log(t + sqrt(t * t + 1) ) / a;
  }
  else
  {
    scattering_angle = log(random_num * exp(a) + (1 - random_num) * exp(-a))/a;
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
