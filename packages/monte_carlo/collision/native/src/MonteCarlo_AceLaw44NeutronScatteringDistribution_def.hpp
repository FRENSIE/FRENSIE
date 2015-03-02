//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_AceLaw44NeutronScatteringDistribution_def.hpp
//! \author Alex Bennett
//! \brief  The law 44 scattering distribution class definition
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_ACE_LAW_44_NEUTRON_SCATTERING_DISTRIBUTION_DEF_HPP
#define MONTE_CARLO_ACE_LAW_44_NEUTRON_SCATTERING_DISTRIBUTION_DEF_HPP

// Std Lib Includes
#include <math.h>

// FRENSIE Includes
#include "MonteCarlo_AceLaw44NeutronScatteringDistribution.hpp"
#include "MonteCarlo_NeutronScatteringEnergyDistribution.hpp"
#include "Utility_DirectionHelpers.hpp"
#include "Utility_ContractException.hpp"
#include "Utility_RandomNumberGenerator.hpp"

namespace MonteCarlo{

// Constructor
template<typename SystemConversionPolicy>
AceLaw44NeutronScatteringDistribution<SystemConversionPolicy>::AceLaw44NeutronScatteringDistribution( 
                      const double atomic_weight_ratio,
		      const Teuchos::RCP<NeutronScatteringEnergyDistribution>& 
		      energy_scattering_distribution,
		      const Teuchos::Array<Teuchos::RCP<AceLaw44ARDistribution> >&
		      ar_distributions )
   : NeutronScatteringDistribution( atomic_weight_ratio ),
     d_energy_scattering_distribution( energy_scattering_distribution ),
     d_ar_distributions( ar_distributions )
{
  // Make sure the energy distribution pointer is valid
  testPrecondition( !energy_scattering_distribution.is_null() );
}

// Randomly scatter the neutron
template<typename SystemConversionPolicy>
void AceLaw44NeutronScatteringDistribution<SystemConversionPolicy>::scatterNeutron(
					       NeutronState& neutron,
                                               const double ) const
{
  unsigned outgoing_bin_index, incoming_bin_index;

  double energy_prime;

  // Sample the energy of the neutron
  double outgoing_sys_energy = 
    d_energy_scattering_distribution->sampleEnergy( neutron.getEnergy(),
						    incoming_bin_index,
						    outgoing_bin_index,
						    energy_prime );
 
  double a, r;
 
  d_ar_distributions[incoming_bin_index]->sampleAR( outgoing_bin_index,
						    energy_prime,
						    a, 
						    r );

  double random_num = 
    Utility::RandomNumberGenerator::getRandomNumber<double>();

  double sys_scattering_angle_cosine;

  if( Utility::RandomNumberGenerator::getRandomNumber<double>() > r )
  {
    double t = (2 * random_num - 1) * sinh(a);

    sys_scattering_angle_cosine = log(t + sqrt(t * t + 1) ) / a;
  }
  else
  {
    sys_scattering_angle_cosine = 
      log(random_num * exp(a) + (1 - random_num) * exp(-a))/a;
  }

  // convert the outgoing energy from this system to the lab system
  double outgoing_energy = 
    SystemConversionPolicy::convertToLabEnergy( neutron.getEnergy(),
						outgoing_sys_energy,
						sys_scattering_angle_cosine,
						this->getAtomicWeightRatio() );

  // convert the scattering angle cosine from this system to the lab system
  double scattering_angle_cosine = 
    SystemConversionPolicy::convertToLabAngleCosine( 
						neutron.getEnergy(),
						outgoing_sys_energy,
						outgoing_energy,
						sys_scattering_angle_cosine,
						this->getAtomicWeightRatio() );

  // Make sure the scattering angle cosine is valid
  testPostcondition( scattering_angle_cosine >= -1.0 );
  testPostcondition( scattering_angle_cosine <= 1.0 );

  // Set the new energy
  neutron.setEnergy( outgoing_energy );
  
  // Set the new direction
  neutron.rotateDirection( scattering_angle_cosine, sampleAzimuthalAngle() );
}

} // End MonteCarlo namespace

#endif // end MONTE_CARLO_ACE_LAW_44_NEUTRON_SCATTERING_DISTRIBUTION_DEF_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_AceLaw44NeutronScatteringDistribution_def.hpp
//---------------------------------------------------------------------------//
