//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_DetailedResponseFunction.cpp
//! \author Alex Robinson
//! \brief  Detailed response function class definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_DetailedResponseFunction.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Constructor
DetailedResponseFunction::DetailedResponseFunction(
             const std::shared_ptr<const ParticleDistribution>& particle_dist )
  : d_particle_dist( particle_dist )
{
  // Make sure that the particle distribution pointer is valid
  testPrecondition( particle_dist.get() );
}

// Evaluate the response function at the desired phase space point
double DetailedResponseFunction::evaluate( const ParticleState& particle ) const
{
  return d_particle_dist->evaluate( particle );
}

// Check if the response function is spatially uniform
bool DetailedResponseFunction::isSpatiallyUniform() const
{
  return d_particle_dist->isSpatiallyUniform();
}  
  
} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_DetailedResponseFunction.cpp
//---------------------------------------------------------------------------//
