//---------------------------------------------------------------------------//
//!
//! \file   Facemc_IndependentEnergyAngleNeutronScatteringDistribution_def.hpp
//! \author Alex Robinson, Alex Bennett
//! \brief  The independent energy-angle scattering distribution class def.
//!
//---------------------------------------------------------------------------//

#ifndef FACEMC_INDEPENDENT_ENERGY_ANGLE_NEUTRON_SCATTERING_DISTRIBUTION_DEF_HPP
#define FACEMC_INDEPENDENT_ENERGY_ANGLE_NEUTRON_SCATTERING_DISTRIBUTION_DEF_HPP

// FRENSIE Includes
#include "Utility_DirectionHelpers.hpp"
#include "Utility_ContractException.hpp"

namespace Facemc{

// Constructor
template<typename SystemConversionPolicy>
IndependentEnergyAngleNeutronScatteringDistribution<SystemConversionPolicy>::IndependentEnergyAngleNeutronScatteringDistribution( 
		      const double atomic_weight_ratio,
		      const Teuchos::RCP<NeutronScatteringEnergyDistribution>&
		      energy_scattering_distribution,
		      const Teuchos::RCP<NeutronScatteringAngularDistribution>&
		      angular_scattering_distribution )
  : NeutronScatteringDistribution( atomic_weight_ratio ),
    d_energy_scattering_distribution( energy_scattering_distribution ),
    d_angular_scattering_distribution( angular_scattering_distribution )
{
  // Check to make sure the energy distribution pointer is valid
  testPrecondition( !energy_scattering_distribution.is_null() );
    // Check to make sure the angular distribution pointer is valid
  testPrecondition( !angular_scattering_distribution.is_null() );
}

// Randomly scatter the neutron
template<typename SystemConversionPolicy>
void 
IndependentEnergyAngleNeutronScatteringDistribution<SystemConversionPolicy>::scatterNeutron(
					                 NeutronState& neutron,
							 const double ) const
{
  double outgoing_sys_energy = 
    d_energy_scattering_distribution->sampleEnergy( neutron.getEnergy() );

  double sys_scattering_angle_cosine = 
    d_angular_scattering_distribution->sampleAngleCosine( neutron.getEnergy());

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

  double outgoing_neutron_direction[3];

  Utility::rotateDirectionThroughPolarAndAzimuthalAngle(
						  scattering_angle_cosine,
						  sampleAzimuthalAngle(),
						  neutron.getDirection(),
						  outgoing_neutron_direction );

  // Set the new energy
  neutron.setEnergy( outgoing_energy );

  // Set the new direction
  neutron.setDirection( outgoing_neutron_direction );
}

} // end Facemc namespace

#endif // end FACEMC_INDEPENDENT_ENERGY_ANGLE_NEUTRON_SCATTERING_DISTRIBUTION_DEF_HPP

//---------------------------------------------------------------------------//
// end Facemc_IndependentEnergyAngleNeutronScatteringDistribution_def.hpp
//---------------------------------------------------------------------------//
