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

// Evaluate the dimension distribution at the desired phase space point
/*! \details The evaluation process will cascade to all of the dependent
 * dimensions as well (the results are then multiplied).
 */
double ParticleSourceDimension::evaluateDistribution(
                 const ParticleSourcePhaseSpacePoint& phase_space_point ) const
{
  // Evaluate this dimension distribution only
  const double local_value =
    this->evaluateDistributionWithoutCascade( phase_space_point );

  return local_value*this->evaluateDependentDistributions( phase_space_point );
}

// Evaluate the dependent dimension dists. at the desired phase space point
double ParticleSourceDimension::evaluateDependentDistributions(
                 const ParticleSourcePhaseSpacePoint& phase_space_point ) const
{
  double dependent_value = 1.0;
  
  for( size_t i = 0; i < d_dependent_dimensions.size(); ++i )
  {
    dependent_value *=
      d_dependent_dimensions[i]->evaluateDistribution( phase_space_point );
  }

  return dependent_value;
}

// Sample from the dimension distribution
/*! \details The sampling process will cascade to all of the dependent
 * dimensions as well (they will use the value sampled for this dimension).
 */
void ParticleSourceDimension::sampleFromDistribution(
                      ParticleSourcePhaseSpacePoint& phase_space_sample ) const
{
  // Sample a value for this dimension
  this->sampleFromDistributionWithoutCascade( phase_space_sample );

  // Sample values for all dependent dimensions
  this->sampleFromDependentDimensionDistributions( phase_space_sample );
}

// Sample from all of the dependent dimensions with the value from this dim.
void ParticleSourceDimension::sampleFromDependentDimensionDistributions(
                      ParticleSourcePhaseSpacePoint& phase_space_sample ) const
{
  for( size_t i = 0; i < d_dependent_dimensions.size(); ++i )
    d_dependent_dimensions[i]->sampleFromDistribution( phase_space_sample );
}

// Set the dimension value and weight appropriately
/*! \details To ensure that the dependent dimension values are valid, they
 * will be resampled after the dimension value is set.
 */
void ParticleSourceDimension::setDimensionValueAndCalculateWeight(
                             ParticleSourcePhaseSpacePoint& phase_space_sample,
                             const double dimension_value ) const
{
  // Set the dimension value
  this->setDimensionValueAndCalculateWeightWithoutCascade(
                                         phase_space_sample, dimension_value );

  // Sample values for all dependent dimensions
  this->sampleFromDependentDimensionDistributions( phase_space_sample );
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
