//---------------------------------------------------------------------------//
//!
//! \file   EnergySpaceResponseFunction.cpp
//! \author Alex Robinson
//! \brief  Energy space dependent (only) response function definition
//!
//---------------------------------------------------------------------------//

// FACEMC Includes
#include "EnergySpaceResponseFunction.hpp"
#include "ContractException.hpp"

namespace FACEMC{

// Constructor
EnergySpaceResponseFunction::EnergySpaceResponseFunction(
		     const std::string& name,
		     const Teuchos::RCP<OneDDistribution> energy_distribution )
  : ReponseFunction( name ),
    d_energy_distribution( energy_distribution )
{
  // Make sure the energy distribution is valid
  testPrecondition( !energy_distribution.is_null() );
}

// Evaluate the response function at the desired energy
double EnergySpaceResponseFunction::evaluate( 
				     const BasicParticleState& particle ) const
{
  return energy_distribution->evaluate( particle.getEnergy() );
}

// Check if the response function is spacially uniform
bool EnergySpaceResponseFunction::isSpatiallyUniform() const
{
  return true;
}

} // end FACEMC namespace

//---------------------------------------------------------------------------//
// end EnergySpaceResponseFunction.cpp
//---------------------------------------------------------------------------//
