//---------------------------------------------------------------------------//
//!
//! \file   Facemc_EnergySpaceResponseFunction.cpp
//! \author Alex Robinson
//! \brief  Energy space dependent (only) response function definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "Facemc_EnergySpaceResponseFunction.hpp"
#include "Utility_ContractException.hpp"

namespace Facemc{

// Constructor
EnergySpaceResponseFunction::EnergySpaceResponseFunction(
	    const std::string& name,
	    const Teuchos::RCP<Utility::OneDDistribution> energy_distribution )
  : ResponseFunction( name ),
    d_energy_distribution( energy_distribution )
{
  // Make sure the energy distribution is valid
  testPrecondition( !energy_distribution.is_null() );
}

// Evaluate the response function at the desired energy
double EnergySpaceResponseFunction::evaluate( 
				          const ParticleState& particle ) const
{
  return d_energy_distribution->evaluate( particle.getEnergy() );
}

// Check if the response function is spacially uniform
bool EnergySpaceResponseFunction::isSpatiallyUniform() const
{
  return true;
}

} // end Facemc namespace

//---------------------------------------------------------------------------//
// end Facemc_EnergySpaceResponseFunction.cpp
//---------------------------------------------------------------------------//
