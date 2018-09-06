//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_PhaseSpaceDimensionDistribution.cpp
//! \author Alex Robinson
//! \brief  Phase space dimension distribution class definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "FRENSIE_Archives.hpp"
#include "MonteCarlo_PhaseSpaceDimensionDistribution.hpp"
#include "Utility_LoggingMacros.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_DesignByContract.hpp"

namespace MonteCarlo{

// Constructor
PhaseSpaceDimensionDistribution::PhaseSpaceDimensionDistribution()
  : d_parent_distribution(),
    d_dependent_dimension_distributions()
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
  // Make sure that the trials map is valid
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

// Check if the distribution has a parent
bool PhaseSpaceDimensionDistribution::hasParentDistribution() const
{
  return d_parent_distribution.use_count() > 0;
}

// Get the parent distribution
const PhaseSpaceDimensionDistribution& PhaseSpaceDimensionDistribution::getParentDistribution() const
{
  // Make sure that there is a parent distribution
  testPrecondition( this->hasParentDistribution() );
  
  return *d_parent_distribution.lock();
}

// Add a dependent distribution
void PhaseSpaceDimensionDistribution::addDependentDistribution(
                       const std::shared_ptr<PhaseSpaceDimensionDistribution>&
                       dependent_dimension )
{
  // Make sure that the dependent dimension is actually dependent on this dim.
  TEST_FOR_EXCEPTION( !dependent_dimension->isDependentOnDimension( this->getDimension() ),
                      std::runtime_error,
                      "The dependent distribution cannot be set because its "
                      "parent dimension does not match the parent "
                      "distribution's dimension!" );

  // Make sure that the dependent dimension is unique
  TEST_FOR_EXCEPTION( this->getDimension() == dependent_dimension->getDimension(),
                      std::runtime_error,
                      "The dependent distribution cannot be set because its "
                      "dimension is the same the same as the parent "
                      "distribution's dimension!" );

  TEST_FOR_EXCEPTION( d_dependent_dimension_distributions.count( dependent_dimension->getDimension() ),
                      std::runtime_error,
                      "The dependent distribution cannot be set because a "
                      "dependent distribution with the same dimension has "
                      "already been set in the parent distribution!" );
                                        

  // Add the dependent distribution to the map
  d_dependent_dimension_distributions[dependent_dimension->getDimension()] =
    dependent_dimension;

  // Set this distribution as the parent of the dependent distribution
  dependent_dimension->d_parent_distribution = shared_from_this();
}

// Remove dependent distributions
void PhaseSpaceDimensionDistribution::removeDependentDistributions()
{
  DimensionDependentDistributionMap::iterator dep_dist_it =
    d_dependent_dimension_distributions.begin();

  DimensionDependentDistributionMap::iterator dep_dist_end =
    d_dependent_dimension_distributions.end();

  while( dep_dist_it != dep_dist_end )
  {
    // This distribution will no longer be the parent of the stored dists.
    dep_dist_it->second->d_parent_distribution =
      std::weak_ptr<const PhaseSpaceDimensionDistribution>();
    
    ++dep_dist_it;
  }

  d_dependent_dimension_distributions.clear();
}

// Get the dependent dimensions
void PhaseSpaceDimensionDistribution::getDependentDimensions(
                            DependentDimensionSet& dependent_dimensions ) const
{
  DimensionDependentDistributionMap::const_iterator dimension_it =
    d_dependent_dimension_distributions.begin();

  DimensionDependentDistributionMap::const_iterator dimension_end =
    d_dependent_dimension_distributions.end();

  while( dimension_it != dimension_end )
  {
    dependent_dimensions.insert( dimension_it->first );

    ++dimension_it;
  }
}

EXPLICIT_CLASS_SAVE_LOAD_INST( PhaseSpaceDimensionDistribution  );
  
} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_PhaseSpaceDimensionDistribution.cpp
//---------------------------------------------------------------------------//
