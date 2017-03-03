//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_PhaseSpaceDimensionDistribution.cpp
//! \author Alex Robinson
//! \brief  Phase space dimension distribution class definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_PhaseSpaceDimensionDistribution.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Constructor
PhaseSpaceDimensionDistribution::PhaseSpaceDimensionDistribution()
  : d_dependent_dimension_distributions()
{ /* ... */ }

// Check if the dimension distribution is uniform (somewhere)
/*! \details The default implementation of this method is simply uses
 * the hasForm method with the Utility::UNIFORM_DISTRIBUTION value.
 */
bool PhaseSpaceDimensionDistribution::isUniform() const
{
  return this->hasForm( Utility::UNIFORM_DISTRIBUTION );
}

// Evaluate the dimension distribution with a cascade to the dependent dists
/*! \details The evaluation process will cascade to all of the dependent
 * dimensions as well (the results are then multiplied).
 */
double PhaseSpaceDimensionDistribution::evaluateWithCascade(
                               const PhaseSpacePoint& phase_space_point ) const
{
  // Evaluate this dimension distribution only
  const double local_value =
    this->evaluateWithoutCascade( phase_space_point );

  // Evaluate the dependent distributions
  return local_value*this->evaluateDependentDistributions( phase_space_point );
}

// Evaluate the dependent dimension dists. at the desired phase space point
double PhaseSpaceDimensionDistribution::evaluateDependentDistributions(
                               const PhaseSpacePoint& phase_space_point ) const
{
  double dependent_value = 1.0;

  DimensionDependentDistributionMap::const_iterator dimension_dep_dist_it =
    d_dependent_dimension_distributions.begin();

  while( dimension_dep_dist_it != d_dependent_dimension_distributions.end() )
  {
    dependent_value *=
      dimension_dep_dist_it->second->evaluateWithCascade( phase_space_point );

    ++dimension_dep_dist_it;
  }

  return dependent_value;
}

// Sample a dimension value and cascade to the dependent distributions.
/*! \details The sampling process will cascade to all of the dependent
 * dimensions as well (they will use the value sampled for this dimension).
 */
void PhaseSpaceDimensionDistribution::sampleWithCascade(
                                    PhaseSpacePoint& phase_space_sample ) const
{
  // Sample a value for this dimension
  this->sampleWithoutCascade( phase_space_sample );

  // Sample values for all dependent dimesions
  this->sampleFromDependentDistributions( phase_space_sample );
}

// Sample from all of the dependent dimensions using this dimension value
void PhaseSpaceDimensionDistribution::sampleFromDependentDistributions(
                                    PhaseSpacePoint& phase_space_sample ) const
{
  DimensionDependentDistributionMap::const_iterator dimension_dep_dist_it =
    d_dependent_dimension_distributions.begin();

  while( dimension_dep_dist_it != d_dependent_dimension_distributions.end() )
  {
    dimension_dep_dist_it->second->sampleWithCascade( phase_space_sample );

    ++dimension_dep_dist_it;
  }
}

// Sample a dimension value and cascade to the dependent distributions 
/*! \details The sampling process will cascade to all of the dependent
 * dimensions as well (they will use the value sampled for this dimension).
 */
void PhaseSpaceDimensionDistribution::sampleAndRecordTrialsWithCascade(
                                           PhaseSpacePoint& phase_space_sample,
                                           DimensionCounterMap& trials ) const
{
  // Make sure the trial counter map is valid
  testPrecondition( trials.count( this->getDimension() ) );
  
  // Sample a value for this dimension only
  this->sampleAndRecordTrialsWithoutCascade(
             phase_space_sample, trials.find( this->getDimension() )->second );
  
  // Sample values for all dependent dimensions
  this->sampleFromDependentDistributionsAndRecordTrials(
                                                  phase_space_sample, trials );
}

// Sample from all of the dependent dimensions and record trials
void PhaseSpaceDimensionDistribution::sampleFromDependentDistributionsAndRecordTrials(
                                           PhaseSpacePoint& phase_space_sample,
                                           DimensionCounterMap& trials ) const
{
  DimensionDependentDistributionMap::const_iterator dimension_dep_dist_it =
    d_dependent_dimension_distributions.begin();

  while( dimension_dep_dist_it != d_dependent_dimension_distributions.end() )
  {
    dimension_dep_dist_it->second->sampleAndRecordTrialsWithCascade(
                                                  phase_space_sample, trials );

    ++dimension_dep_dist_it;
  }
}

// Sample a dimension value and cascade to the dependent distributions
void PhaseSpaceDimensionDistribution::sampleWithCascadeUsingDimensionValue(
                                        PhaseSpacePoint& phase_space_sample,
                                        const PhaseSpaceDimension dimension,
                                        const double dimension_value ) const
{
  // Check if this is the dimension that should use the specified value instead
  // of sampling (a weight will be calculated and applied if so)
  if( this->getDimension() == dimension )
  {
    this->setDimensionValueAndApplyWeight( phase_space_sample,
                                           dimension_value );

    this->sampleFromDependentDistributions( phase_space_sample );
  }
  else
  {
    this->sampleWithoutCascade( phase_space_sample );

    this->sampleFromDependentDistributionsUsingDimensionValue(
                                                            phase_space_sample,
                                                            dimension,
                                                            dimension_value );
  } 
}

// Sample from all of the dependent dimensions using the dimension value
void PhaseSpaceDimensionDistribution::sampleFromDependentDistributionsUsingDimensionValue(
                                           PhaseSpacePoint& phase_space_sample,
                                           const PhaseSpaceDimension dimension,
                                           const double dimension_value ) const
{
  DimensionDependentDistributionMap::const_iterator dependent_dim_dist_it =
    d_dependent_dimension_distributions.begin();

  while( dependent_dim_dist_it != d_dependent_dimension_distributions.end() )
  {
    dependent_dim_dist_it->second->sampleWithCascadeUsingDimensionValue(
                                                            phase_space_sample,
                                                            dimension,
                                                            dimension_value );
    
    ++dependent_dim_dist_it;
  }
}

// Set the dimension value, weight appropriately and record the trials
void PhaseSpaceDimensionDistribution::sampleAndRecordTrialsWithCascadeUsingDimensionValue(
                                           PhaseSpacePoint& phase_space_sample,
                                           DimensionCounterMap& trials,
                                           const PhaseSpaceDimension dimension,
                                           const double dimension_value ) const
{
  // Make sure the trial counter map is valid
  testPrecondition( trials.count( this->getDimension() ) );
  
  // Check if this is the dimension that should use the specified value instead
  // of sampling (a weight will be calculated and applied if so)
  if( this->getDimension() == dimension )
  {
    this->setDimensionValueAndApplyWeight( phase_space_sample,
                                           dimension_value );

    this->sampleFromDependentDistributionsAndRecordTrials( phase_space_sample,
                                                           trials );
  }
  else
  {
    this->sampleAndRecordTrialsWithoutCascade(
               phase_space_sample, trials.find(this->getDimension())->second );

    this->sampleFromDependentDistributionsAndRecordTrialsUsingDimensionValue(
                                                            phase_space_sample,
                                                            trials,
                                                            dimension,
                                                            dimension_value );
  } 
}

// Sample from all of the dependent dims. and record trials using dim. value
void PhaseSpaceDimensionDistribution::sampleFromDependentDistributionsAndRecordTrialsUsingDimensionValue(
                                           PhaseSpacePoint& phase_space_sample,
                                           DimensionCounterMap& trials,
                                           const PhaseSpaceDimension dimension,
                                           const double dimension_value ) const
{
  DimensionDependentDistributionMap::const_iterator dependent_dim_dist_it =
    d_dependent_dimension_distributions.begin();

  while( dependent_dim_dist_it != d_dependent_dimension_distributions.end() )
  {
    dependent_dim_dist_it->second->sampleAndRecordTrialsWithCascadeUsingDimensionValue(
                                                            phase_space_sample,
                                                            trials,
                                                            dimension,
                                                            dimension_value );
    
    ++dependent_dim_dist_it;
  }
}

// Add a dependent dimension
void PhaseSpaceDimensionDistribution::addDependentDimension(
                  const std::shared_ptr<const PhaseSpaceDimensionDistribution>&
                  dependent_dimension )
{
  // Make sure that the dependent dimension is actually dependent on this dim.
  testPrecondition( dependent_dimension->isDependentOnDimension( this->getDimension() ) );
  // Make sure that the dependent dimension is unique
  testPrecondition( this->getDimension() != dependent_dimension->getDimension() );
  testPrecondition( !d_dependent_dimension_distributions.count( dependent_dimension->getDimension() ) );

  // Add the dependent distribution to the map
  d_dependent_dimension_distributions[dependent_dimension->getDimension()] =
    dependent_dimension;
}
  
} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_PhaseSpaceDimensionDistribution.cpp
//---------------------------------------------------------------------------//
