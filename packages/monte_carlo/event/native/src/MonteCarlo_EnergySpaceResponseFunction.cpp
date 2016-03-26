//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_EnergySpaceResponseFunction.cpp
//! \author Alex Robinson
//! \brief  Energy space dependent (only) response function definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_EnergySpaceResponseFunction.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Constructor
EnergySpaceResponseFunction::EnergySpaceResponseFunction(
	 const unsigned id,
         const std::string& name,
	 const std::shared_ptr<Utility::OneDDistribution> energy_distribution )
  : ResponseFunction( id, name ),
    d_energy_distribution( energy_distribution )
{
  // Make sure the energy distribution is valid
  testPrecondition( energy_distribution.get() );
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

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_EnergySpaceResponseFunction.cpp
//---------------------------------------------------------------------------//
