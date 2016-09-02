//---------------------------------------------------------------------------//
//!
//! \file   Utility_InterpolatedTabularTwoDDistributionHelpers_def.hpp
//! \author Alex Robinson
//! \brief  The interpolated tabular two-dimensional dist. helper class defs.
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_INTERPOLATED_TABULAR_TWO_D_DISTRIBUTION_HELPERS_DEF_HPP
#define UTILITY_INTERPOLATED_TABULAR_TWO_D_DISTRIBUTION_HELPERS_DEF_HPP

// FRENSIE Includes
#include "Utility_TabularDistribution.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_ContractException.hpp"

namespace Utility{
 
// Evaluate the distribution
template<typename TwoDInterpPolicy, typename Distribution>
auto UnitAwareInterpolatedTabularTwoDDistributionImplBase<TwoDInterpPolicy,Distribution>::evaluate(
                 const PrimaryIndepQuantity primary_indep_var_value,
                 const SecondaryIndepQuantity secondary_indep_var_value ) const
  -> DepQuantity
{
  // Find the bin boundaries
  typename DistributionType::const_iterator lower_bin_boundary, upper_bin_boundary;
  
  this->findBinBoundaries( primary_indep_var_value,
                           lower_bin_boundary,
                           upper_bin_boundary );

  // Calculate the length of the lower secondary grid
  const typename QuantityTraits<SecondaryIndepQuantity>::RawType L0 =
    TwoDInterpPolicy::calculateGridLength(
                       lower_bin_boundary->second->getLowerBoundOfIndepVar(),
                       lower_bin_boundary->second->getUpperBoundOfIndepVar() );

  // Calculate the length of the upper secondary grid
  const typename QuantityTraits<SecondaryIndepQuantity>::RawType L1 =
    TwoDInterpPolicy::calculateGridLength(
                       upper_bin_boundary->second->getLowerBoundOfIndepVar(),
                       upper_bin_boundary->second->getUpperBoundOfIndepVar() );

  // Create the grid evaluation functors
  std::function<DepQuantity(const SecondaryIndepQuantity)> evaluate_grid_0_functor =
    std::bind<DepQuantity>( &BaseOneDDistributionType::evaluate,
                            std::cref( *lower_bin_boundary->second ),
                            std::placeholders::_1 );

  std::function<DepQuantity(const SecondaryIndepQuantity)> evaluate_grid_1_functor =
    std::bind<DepQuantity>( &BaseOneDDistributionType::evaluate,
                            std::cref( *upper_bin_boundary->second ),
                            std::placeholders::_1 );
  
  return TwoDInterpPolicy::interpolateUnitBase(
                         lower_bin_boundary->first,
                         upper_bin_boundary->first,
                         primary_indep_var_value,
                         secondary_indep_var_value,
                         lower_bin_boundary->second->getLowerBoundOfIndepVar(),
                         upper_bin_boundary->second->getLowerBoundOfIndepVar(),
                         L0,
                         L1,
                         evaluate_grid_0_functor,
                         evaluate_grid_1_functor );
}

// Evaluate the secondary conditional PDF
template<typename TwoDInterpPolicy, typename Distribution>
auto UnitAwareInterpolatedTabularTwoDDistributionImplBase<TwoDInterpPolicy,Distribution>::evaluateSecondaryConditionalPDF(
                 const PrimaryIndepQuantity primary_indep_var_value,
                 const SecondaryIndepQuantity secondary_indep_var_value ) const
  -> InverseSecondaryIndepQuantity
{
  // Find the bin boundaries
  typename DistributionType::const_iterator lower_bin_boundary, upper_bin_boundary;
  
  this->findBinBoundaries( primary_indep_var_value,
                           lower_bin_boundary,
                           upper_bin_boundary );

  // Calculate the length of the lower secondary grid
  const typename QuantityTraits<SecondaryIndepQuantity>::RawType L0 =
    TwoDInterpPolicy::calculateGridLength(
                       lower_bin_boundary->second->getLowerBoundOfIndepVar(),
                       lower_bin_boundary->second->getUpperBoundOfIndepVar() );

  // Calculate the length of the upper secondary grid
  const typename QuantityTraits<SecondaryIndepQuantity>::RawType L1 =
    TwoDInterpPolicy::calculateGridLength(
                       upper_bin_boundary->second->getLowerBoundOfIndepVar(),
                       upper_bin_boundary->second->getUpperBoundOfIndepVar() );

  // Create the grid evaluation functors
  std::function<InverseSecondaryIndepQuantity(const SecondaryIndepQuantity)> evaluate_grid_0_functor =
    std::bind<InverseSecondaryIndepQuantity>(
                                      &BaseOneDDistributionType::evaluatePDF,
                                      std::cref( *lower_bin_boundary->second ),
                                      std::placeholders::_1 );

  std::function<InverseSecondaryIndepQuantity(const SecondaryIndepQuantity)> evaluate_grid_1_functor =
    std::bind<InverseSecondaryIndepQuantity>(
                                      &BaseOneDDistributionType::evaluatePDF,
                                      std::cref( *upper_bin_boundary->second ),
                                      std::placeholders::_1 );
  
  return TwoDInterpPolicy::interpolateUnitBase(
                         lower_bin_boundary->first,
                         upper_bin_boundary->first,
                         primary_indep_var_value,
                         secondary_indep_var_value,
                         lower_bin_boundary->second->getLowerBoundOfIndepVar(),
                         upper_bin_boundary->second->getLowerBoundOfIndepVar(),
                         L0,
                         L1,
                         evaluate_grid_0_functor,
                         evaluate_grid_1_functor );
}

// Return a random sample from the secondary conditional PDF
/*! \details A stochastic sampling procedure is used.
 */
template<typename TwoDInterpPolicy, typename Distribution>
auto UnitAwareInterpolatedTabularTwoDDistributionImplBase<TwoDInterpPolicy,Distribution>::sampleSecondaryConditional(
                     const PrimaryIndepQuantity primary_indep_var_value ) const
  -> SecondaryIndepQuantity
{
  // Find the bin boundaries
  typename DistributionType::const_iterator lower_bin_boundary, upper_bin_boundary;
  
  this->findBinBoundaries( primary_indep_var_value,
                           lower_bin_boundary,
                           upper_bin_boundary );

  typename DistributionType::const_iterator sampled_bin_boundary =
    this->sampleBinBoundary( primary_indep_var_value,
                             lower_bin_boundary,
                             upper_bin_boundary );

  return sampled_bin_boundary->second->sample();
}

// Return a random sample and record the number of trials
/*! \details A stochastic sampling procedure is used.
 */
template<typename TwoDInterpPolicy, typename Distribution>
auto UnitAwareInterpolatedTabularTwoDDistributionImplBase<TwoDInterpPolicy,Distribution>::sampleSecondaryConditionalAndRecordTrials(
                            const PrimaryIndepQuantity primary_indep_var_value,
                            unsigned& trials ) const
  -> SecondaryIndepQuantity
{
  // Find the bin boundaries
  typename DistributionType::const_iterator lower_bin_boundary, upper_bin_boundary;
  
  this->findBinBoundaries( primary_indep_var_value,
                           lower_bin_boundary,
                           upper_bin_boundary );

  typename DistributionType::const_iterator sampled_bin_boundary =
    this->sampleBinBoundary( primary_indep_var_value,
                             lower_bin_boundary,
                             upper_bin_boundary );

  return sampled_bin_boundary->second->sampleAndRecordTrials( trials );
}

// Sample the bin boundary that will be used for stochastic sampling
template<typename TwoDInterpPolicy, typename Distribution>
auto
UnitAwareInterpolatedTabularTwoDDistributionImplBase<TwoDInterpPolicy,Distribution>::sampleBinBoundary(
    const PrimaryIndepQuantity primary_indep_var_value,
    const typename DistributionType::const_iterator lower_bin_boundary,
    const typename DistributionType::const_iterator upper_bin_boundary ) const
  -> typename DistributionType::const_iterator
{
  if( lower_bin_boundary != upper_bin_boundary )
  {
    // Calculate the interpolation fraction
    double interpolation_fraction =
      this->calculateInterpolationFraction( primary_indep_var_value,
                                            lower_bin_boundary,
                                            upper_bin_boundary );
    

    // Sample to determine the distribution that will be used
    double random_number =
      Utility::RandomNumberGenerator::getRandomNumber<double>();

    if( random_number < interpolation_fraction )
      return upper_bin_boundary;
    else
      return lower_bin_boundary;
  }
  else
    return lower_bin_boundary;
}

// Return the upper bound of the conditional distribution
template<typename TwoDInterpPolicy, typename Distribution>
auto UnitAwareInterpolatedTabularTwoDDistributionImplBase<TwoDInterpPolicy,Distribution>::getUpperBoundOfConditionalIndepVar(
                     const PrimaryIndepQuantity primary_indep_var_value ) const
  -> SecondaryIndepQuantity
{
  typename DistributionType::const_iterator lower_bin_boundary, upper_bin_boundary;
  
  this->findBinBoundaries( primary_indep_var_value,
                           lower_bin_boundary,
                           upper_bin_boundary );
  
  return TwoDInterpPolicy::calculateIntermediateGridLimit(
                       lower_bin_boundary->first,
                       upper_bin_boundary->first,
                       primary_indep_var_value,
                       lower_bin_boundary->second->getUpperBoundOfIndepVar(),
                       upper_bin_boundary->second->getUpperBoundOfIndepVar() );
}

// Return the lower bound of the conditional distribution
template<typename TwoDInterpPolicy, typename Distribution>
auto UnitAwareInterpolatedTabularTwoDDistributionImplBase<TwoDInterpPolicy,Distribution>::getLowerBoundOfConditionalIndepVar(
                     const PrimaryIndepQuantity primary_indep_var_value ) const
  -> SecondaryIndepQuantity
{
  typename DistributionType::const_iterator lower_bin_boundary, upper_bin_boundary;
  
  this->findBinBoundaries( primary_indep_var_value,
                           lower_bin_boundary,
                           upper_bin_boundary );
  
  return TwoDInterpPolicy::calculateIntermediateGridLimit(
                       lower_bin_boundary->first,
                       upper_bin_boundary->first,
                       primary_indep_var_value,
                       lower_bin_boundary->second->getLowerBoundOfIndepVar(),
                       upper_bin_boundary->second->getLowerBoundOfIndepVar() );
}

// Test if the distribution is continuous in the primary dimension
template<typename TwoDInterpPolicy, typename Distribution>
bool UnitAwareInterpolatedTabularTwoDDistributionImplBase<TwoDInterpPolicy,Distribution>::isPrimaryDimensionContinuous() const
{
  return true;
}

// Raw Constructor
template<typename TwoDInterpPolicy,
         typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit,
         bool FullyTabular>
template<template<typename T, typename... Args> class ArrayA,
         template<typename T, typename... Args> class ArrayB,
         template<typename T, typename... Args> class SubarrayB,
         template<typename T, typename... Args> class ArrayC,
         template<typename T, typename... Args> class SubarrayC>
UnitAwareInterpolatedTabularTwoDDistributionImpl<TwoDInterpPolicy,PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit,FullyTabular>::UnitAwareInterpolatedTabularTwoDDistributionImpl(
       const ArrayA<PrimaryIndepQuantity>& primary_indep_grid,
       const ArrayB<SubarrayB<SecondaryIndepQuantity> >& secondary_indep_grids,
       const ArrayC<SubarrayC<DepQuantity> >& dependent_values )
{
  // Make sure the grids are valid
  testPrecondition( Sort::isSortedAscending( primary_indep_grid.begin(),
                                             primary_indep_grid.end() ) );
  testPrecondition( primary_indep_grid.size() > 1 );
  testPrecondition( primary_indep_grid.size() == secondary_indep_grids.size());
  testPrecondition( primary_indep_grid.size() == dependent_values.size() );
  
  // Construct the 2D distribution
  DistributionType distribution( primary_indep_grid.size() );
  
  for( size_t i = 0; i < primary_indep_grid.size(); ++i )
  {
    distribution[i].first = primary_indep_grid;
    distribution[i].second.reset(
          new UnitAwareTabularDistribution<typename TwoDInterpPolicy::SecondaryBasePolicy,SecondaryIndependentUnit,DependentUnit>(
                                                      secondary_indep_grids[i],
                                                      dependent_values[i] ) );
  }

  this->setDistribution( distribution );
}

// Evaluate the secondary conditional CDF
template<typename TwoDInterpPolicy,
         typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit,
         bool FullyTabular>
double UnitAwareInterpolatedTabularTwoDDistributionImpl<TwoDInterpPolicy,PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit,FullyTabular>::evaluateSecondaryConditionalCDF(
                 const PrimaryIndepQuantity primary_indep_var_value,
                 const SecondaryIndepQuantity secondary_indep_var_value ) const
{
  // Find the bin boundaries
  typename DistributionType::const_iterator lower_bin_boundary, upper_bin_boundary;
  
  this->findBinBoundaries( primary_indep_var_value,
                           lower_bin_boundary,
                           upper_bin_boundary );

  // Calculate the length of the lower secondary grid
  const typename QuantityTraits<SecondaryIndepQuantity>::RawType L0 =
    TwoDInterpPolicy::calculateGridLength(
                       lower_bin_boundary->second->getLowerBoundOfIndepVar(),
                       lower_bin_boundary->second->getUpperBoundOfIndepVar() );

  // Calculate the length of the upper secondary grid
  const typename QuantityTraits<SecondaryIndepQuantity>::RawType L1 =
    TwoDInterpPolicy::calculateGridLength(
                       upper_bin_boundary->second->getLowerBoundOfIndepVar(),
                       upper_bin_boundary->second->getUpperBoundOfIndepVar() );

  // Create the grid evaluation functors
  std::function<double(const SecondaryIndepQuantity)> evaluate_grid_0_functor =
    std::bind<double>( &BaseOneDDistributionType::evaluateCDF,
                            std::cref( lower_bin_boundary->second ),
                            std::placeholders::_1 );

  std::function<double(const SecondaryIndepQuantity)> evaluate_grid_1_functor =
    std::bind<double>( &BaseOneDDistributionType::evaluateCDF,
                            std::cref( upper_bin_boundary->second ),
                            std::placeholders::_1 );
  
  return TwoDInterpPolicy::interpolateUnitBase(
                         lower_bin_boundary->first,
                         upper_bin_boundary->first,
                         primary_indep_var_value,
                         secondary_indep_var_value,
                         lower_bin_boundary->second->getLowerBoundOfIndepVar(),
                         upper_bin_boundary->second->getLowerBoundOfIndepVar(),
                         L0,
                         L1,
                         evaluate_grid_0_functor,
                         evaluate_grid_1_functor );
}

// Return a random sample from the secondary conditional PDF
template<typename TwoDInterpPolicy,
         typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit,
         bool FullyTabular>
auto UnitAwareInterpolatedTabularTwoDDistributionImpl<TwoDInterpPolicy,PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit,FullyTabular>::sampleSecondaryConditionalExact(
                     const PrimaryIndepQuantity primary_indep_var_value ) const
  -> SecondaryIndepQuantity
{
  // Use this random number to do create the correlated sample
  const double random_number =
    Utility::RandomNumberGenerator::getRandomNumber<double>();

  return this->sampleSecondaryConditionalExactWithRandomNumber( random_number );
}

// Return a random sample from the secondary conditional PDF and the index
template<typename TwoDInterpPolicy,
         typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit,
         bool FullyTabular>
auto UnitAwareInterpolatedTabularTwoDDistributionImpl<TwoDInterpPolicy,PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit,FullyTabular>::sampleSecondaryConditionalAndRecordBinIndex(
                            const PrimaryIndepQuantity primary_indep_var_value,
                            unsigned& sampled_bin_index ) const
  -> SecondaryIndepQuantity
{
  // Find the bin boundaries
  typename DistributionType::const_iterator lower_bin_boundary, upper_bin_boundary;
  
  this->findBinBoundaries( primary_indep_var_value,
                           lower_bin_boundary,
                           upper_bin_boundary );

  typename DistributionType::const_iterator sampled_bin_boundary =
    this->sampleBinBoundary( primary_indep_var_value,
                             lower_bin_boundary,
                             upper_bin_boundary );

  return sampled_bin_boundary->second->sampleAndRecordBinIndex( sampled_bin_index );
}

// Return a random sample from the secondary conditional PDF at the CDF val
template<typename TwoDInterpPolicy,
         typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit,
         bool FullyTabular>
auto UnitAwareInterpolatedTabularTwoDDistributionImpl<TwoDInterpPolicy,PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit,FullyTabular>::sampleSecondaryConditionalWithRandomNumber(
                            const PrimaryIndepQuantity primary_indep_var_value,
                            const double random_number ) const
  -> SecondaryIndepQuantity
{
  // Find the bin boundaries
  typename DistributionType::const_iterator lower_bin_boundary, upper_bin_boundary;
  
  this->findBinBoundaries( primary_indep_var_value,
                           lower_bin_boundary,
                           upper_bin_boundary );

  typename DistributionType::const_iterator sampled_bin_boundary =
    this->sampleBinBoundary( primary_indep_var_value,
                             lower_bin_boundary,
                             upper_bin_boundary );

  return sampled_bin_boundary->second->sampleWithRandomNumber( random_number );
}

// Return a random sample from the secondary conditional PDF at the CDF val
template<typename TwoDInterpPolicy,
         typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit,
         bool FullyTabular>
auto UnitAwareInterpolatedTabularTwoDDistributionImpl<TwoDInterpPolicy,PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit,FullyTabular>::sampleSecondaryConditionalExactWithRandomNumber(
                            const PrimaryIndepQuantity primary_indep_var_value,
                            const double random_number ) const
  -> SecondaryIndepQuantity
{
  // Find the bin boundaries
  typename DistributionType::const_iterator lower_bin_boundary, upper_bin_boundary;
  
  this->findBinBoundaries( primary_indep_var_value,
                           lower_bin_boundary,
                           upper_bin_boundary );

  if( lower_bin_boundary != upper_bin_boundary )
  {
    return TwoDInterpPolicy::PrimaryBasePolicy::interpolate(
         lower_bin_boundary->first,
         upper_bin_boundary->first,
         primary_indep_var_value,
         lower_bin_boundary->second->sampleWithRandomNumber( random_number ),
         upper_bin_boundary->second->sampleWithRandomNumber( random_number ) );
  }
  else
    return lower_bin_boundary->second->sampleWithRandomNumber( random_number );
}

// Return a random sample from the secondary conditional PDF in the subrange
template<typename TwoDInterpPolicy,
         typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit,
         bool FullyTabular>
auto UnitAwareInterpolatedTabularTwoDDistributionImpl<TwoDInterpPolicy,PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit,FullyTabular>::sampleSecondaryConditionalInSubrange(
             const PrimaryIndepQuantity primary_indep_var_value,
             const SecondaryIndepQuantity max_secondary_indep_var_value ) const
  -> SecondaryIndepQuantity
{
  const double random_number =
    Utility::RandomNumberGenerator::getRandomNumber<double>();
  
  return this->sampleSecondaryConditionalWithRandomNumberInSubrange(
                                               primary_indep_var_value,
                                               random_number,
                                               max_secondary_indep_var_value );
}

// Return a random sample from the secondary conditional PDF in the subrange
template<typename TwoDInterpPolicy,
         typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit,
         bool FullyTabular>
auto UnitAwareInterpolatedTabularTwoDDistributionImpl<TwoDInterpPolicy,PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit,FullyTabular>::sampleSecondaryConditionalExactInSubrange(
             const PrimaryIndepQuantity primary_indep_var_value,
             const SecondaryIndepQuantity max_secondary_indep_var_value ) const
  -> SecondaryIndepQuantity
{
  // Use this random number to do create the correlated sample
  const double random_number =
    Utility::RandomNumberGenerator::getRandomNumber<double>();

  return this->sampleSecondaryConditionalExactWithRandomNumberInSubrange(
                                               primary_indep_var_value,
                                               random_number,
                                               max_secondary_indep_var_value );
}

// Return a random sample from the secondary conditional PDF in the subrange
template<typename TwoDInterpPolicy,
         typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit,
         bool FullyTabular>
auto UnitAwareInterpolatedTabularTwoDDistributionImpl<TwoDInterpPolicy,PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit,FullyTabular>::sampleSecondaryConditionalWithRandomNumberInSubrange(
             const PrimaryIndepQuantity primary_indep_var_value,
             const double random_number,
             const SecondaryIndepQuantity max_secondary_indep_var_value ) const
  -> SecondaryIndepQuantity
{
  // Find the bin boundaries
  typename DistributionType::const_iterator lower_bin_boundary, upper_bin_boundary;
  
  this->findBinBoundaries( primary_indep_var_value,
                           lower_bin_boundary,
                           upper_bin_boundary );

  typename DistributionType::const_iterator sampled_bin_boundary =
    this->sampleBinBoundary( primary_indep_var_value,
                             lower_bin_boundary,
                             upper_bin_boundary );

  return sampled_bin_boundary->second->sampleWithRandomNumberInSubrange(
                                random_number, max_secondary_indep_var_value );
}

// Return a random sample from the secondary conditional PDF in the subrange
template<typename TwoDInterpPolicy,
         typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit,
         bool FullyTabular>
auto UnitAwareInterpolatedTabularTwoDDistributionImpl<TwoDInterpPolicy,PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit,FullyTabular>::sampleSecondaryConditionalExactWithRandomNumberInSubrange(
             const PrimaryIndepQuantity primary_indep_var_value,
             const double random_number,
             const SecondaryIndepQuantity max_secondary_indep_var_value ) const
  -> SecondaryIndepQuantity
{
  // Find the bin boundaries
  typename DistributionType::const_iterator lower_bin_boundary, upper_bin_boundary;
  
  this->findBinBoundaries( primary_indep_var_value,
                           lower_bin_boundary,
                           upper_bin_boundary );

  if( lower_bin_boundary != upper_bin_boundary )
  {
    return TwoDInterpPolicy::PrimaryBasePolicy::interpolate(
         lower_bin_boundary->first,
         upper_bin_boundary->first,
         primary_indep_var_value,
         lower_bin_boundary->second->sampleWithRandomNumberInSubrange( random_number, max_secondary_indep_var_value ),
         upper_bin_boundary->second->sampleWithRandomNumberInSubrange( random_number, max_secondary_indep_var_value ) );
  }
  else
    return lower_bin_boundary->second->sampleWithRandomNumberInSubrange( random_number, max_secondary_indep_var_value );
}

} // end Utility namespace

#endif // end UTILITY_INTERPOLATED_TABULAR_TWO_D_DISTRIBUTION_HELPERS_DEF_HPP

//---------------------------------------------------------------------------//
// end Utility_InterpolatedTabularTwoDDistributionHelpers_def.hpp
//---------------------------------------------------------------------------//
