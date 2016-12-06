//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ParticleSourceDimension.cpp
//! \author Alex Robinson
//! \brief  Particle source dimension class definition.
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_ParticleSourceDimension.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Constructor
ParticleSourceDimension::ParticleSourceDimension()
  : d_dependent_dimensions()
{ /* ... */ }

// Return the dimension class type
ParticleSourceDimensionClassType
ParticleSourceDimension::getDimensionClassType() const
{
  return getClassOfParticleSourceDimensionType( this->getDimensionType() );
}

// Sample from the dimension distribution (and all dependent dim. dists.)
void ParticleSourceDimension::sample(
                      ParticleSourcePhaseSpacePoint& phase_space_sample ) const
{
  // Sample a value for this dimension
  this->sampleDimension( phase_space_sample );

  // Sample values for all dependent dimensions
  this->sampleDependentDimensions( phase_space_sample );
}

// Sample from all of the dependent dimensions with the value from this dim.
void ParticleSourceDimension::sampleDependentDimensions(
                      ParticleSourcePhaseSpacePoint& phase_space_sample ) const
{
  for( size_t i = 0; i < d_dependent_dimensions.size(); ++i )
    d_dependent_dimensions[i]->sampleDimension( phase_space_sample );
}

// Add a dependent dimension
void ParticleSourceDimension::addDependentDimension(
                          const std::shared_ptr<const ParticleSourceDimension>&
                          dependent_dimension )
{
  // Make sure the dependent dimension is actually dependent on this dimension
  testPrecondition( dependent_dimension->isDependentOnDimension( this->getDimensionType() ) );

  d_dependent_dimensions.push_back( dependent_dimension );
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_ParticleSourceDimension.cpp
//---------------------------------------------------------------------------//
