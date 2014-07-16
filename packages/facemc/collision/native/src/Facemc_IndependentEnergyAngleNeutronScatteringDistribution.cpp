//---------------------------------------------------------------------------//
//!
//! \file   Facemc_IndependentEnergyAngleNeutronScatteringDistribution.cpp
//! \author Alex Robinson, Alex Bennett
//! \brief  The independent energy-angle scattering distribution class def.
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "Facemc_IndependentEnergyAngleNeutronScatteringDistribution.hpp"
#include "Utility_DirectionHelpers.hpp"
#include "Utility_ContractException.hpp"

namespace Facemc{

// Constructor
IndependentEnergyAngleNeutronScatteringDistribution::IndependentEnergyAngleNeutronScatteringDistribution( 
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
  // Make sure the energy distribution is in the Lab
  testPrecondition( !energy_scattering_distribution->isCMDistribution() );
  // Check to make sure the angular distribution pointer is valid
  testPrecondition( !angular_scattering_distribution.is_null() );
  // Make sure the angular distribution is in the Lab
  testPrecondition( !angular_scattering_distribution->isCMDistribution() );    
}

// Randomly scatter the neutron
void IndependentEnergyAngleNeutronScatteringDistribution::scatterNeutron(
					       NeutronState& neutron,
                                               const double ) const
{
  double outgoing_energy = 
    d_energy_scattering_distribution->sampleEnergy( neutron.getEnergy() );

  double scattering_angle_cosine = 
    d_angular_scattering_distribution->sampleAngleCosine( neutron.getEnergy());

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

//---------------------------------------------------------------------------//
// end Facemc_IndependentEnergyAngleNeutronScatteringDistribution.cpp
//---------------------------------------------------------------------------//
