//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_StandardResponseFunction.cpp
//! \author Alex Robinson
//! \brief  Standard response function class definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_StandardResponseFunction.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Constructor
StandardResponseFunction::StandardResponseFunction(
                            const ParticleDistributionPointer& particle_dist )
  : d_particle_dist( particle_dist )
{
  // Make sure that the particle distribution pointer is valid
  testPrecondition( particle_dist.get() );
}

// Return the id
ModuleTraits::InternalROIHandle StandardResponseFunction::getId() const
{
  return d_particle_dist->getId();
}

// Return the name of the response function
const std::string& StandardResponseFunction::getName() const
{
  return d_particle_dist->getName();
}

// Evaluate the response function at the desired phase space point
double StandardResponseFunction::evaluate( const ParticleState& particle ) const
{
  return d_particle_dist->evaluate( particle );
}

// Check if the response function is spatially uniform
bool StandardResponseFunction::isSpatiallyUniform() const
{
  return d_particle_dist->isSpatiallyUniform();
}  
  
} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_StandardResponseFunction.cpp
//---------------------------------------------------------------------------//
