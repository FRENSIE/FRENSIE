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
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_ContractException.hpp"

namespace Utility{

// Constructor
template<typename TwoDInterpPolicy, typename Distribution>
UnitAwareInterpolatedTabularTwoDDistributionImplBase<TwoDInterpPolicy,Distribution>::UnitAwareInterpolatedTabularTwoDDistributionImplBase(
                                         const DistributionType& distribution )
    : ParentType( distribution )
{
  // Make sure the distributions are compatible with the requested interp
  testPrecondition( this->areSecondaryDistsCompatibleWithInterpType( distribution ) );
}

// Constructor
template<typename TwoDInterpPolicy, typename Distribution>
template<template<typename T, typename... Args> class ArrayA,
         template<typename T, typename... Args> class ArrayB>
UnitAwareInterpolatedTabularTwoDDistributionImplBase<TwoDInterpPolicy,Distribution>::UnitAwareInterpolatedTabularTwoDDistributionImplBase(
                const ArrayA<PrimaryIndepQuantity>& primary_indep_grid,
                const ArrayB<std::shared_ptr<const BaseOneDDistributionType> >&
                secondary_distributions )
  : ParentType( primary_indep_grid, secondary_distributions )
{
  // Make sure the distributions are compatible with the requested interp
  testPrecondition( this->areSecondaryDistsCompatibleWithInterpType( secondary_distributions ) );
}

// Check that the secondary dists are compatible with the requested interp
template<typename TwoDInterpPolicy, typename Distribution>
bool UnitAwareInterpolatedTabularTwoDDistributionImplBase<TwoDInterpPolicy,Distribution>::areSecondaryDistsCompatibleWithInterpType(
                                   const DistributionType& distribution ) const
{
  bool compatible = true;
  
  for( size_t i = 0; i < distribution.size(); ++i )
  {
    if( !distribution[i].second->template isCompatibleWithInterpType<typename TwoDInterpPolicy::SecondaryBasePolicy>() )
    {
      compatible = false;

      break;
    }
  }

  return compatible;
}

// Check that the secondary dists are compatible with the requested interp
template<typename TwoDInterpPolicy, typename Distribution>
template<template<typename T, typename... Args> class Array>
bool UnitAwareInterpolatedTabularTwoDDistributionImplBase<TwoDInterpPolicy,Distribution>::areSecondaryDistsCompatibleWithInterpType(
                 const Array<std::shared_ptr<const BaseOneDDistributionType> >&
                 secondary_distributions ) const
{
  bool compatible = true;
  
  for( size_t i = 0; i < secondary_distributions.size(); ++i )
  {
    if( !secondary_distributions[i]->template isCompatibleWithInterpType<typename TwoDInterpPolicy::SecondaryBasePolicy>() )
    {
      compatible = false;

      break;
    }
  }

  return compatible;
}
 
// Evaluate the distribution
template<typename TwoDInterpPolicy, typename Distribution>
auto UnitAwareInterpolatedTabularTwoDDistributionImplBase<TwoDInterpPolicy,Distribution>::evaluate(
                 const PrimaryIndepQuantity primary_indep_var_value,
                 const SecondaryIndepQuantity secondary_indep_var_value ) const
  -> DepQuantity
{
  return this->evaluateImpl<TwoDInterpPolicy,DepQuantity>(
                                          primary_indep_var_value,
                                          secondary_indep_var_value,
                                          &BaseOneDDistributionType::evaluate);
}

// Evaluate the secondary conditional PDF
template<typename TwoDInterpPolicy, typename Distribution>
auto UnitAwareInterpolatedTabularTwoDDistributionImplBase<TwoDInterpPolicy,Distribution>::evaluateSecondaryConditionalPDF(
                 const PrimaryIndepQuantity primary_indep_var_value,
                 const SecondaryIndepQuantity secondary_indep_var_value ) const
  -> InverseSecondaryIndepQuantity
{
  return this->evaluateImpl<TwoDInterpPolicy,InverseSecondaryIndepQuantity>(
                                      primary_indep_var_value,
                                      secondary_indep_var_value,
                                      &BaseOneDDistributionType::evaluatePDF );
}

// Evaluate the distribution using the desired evaluation method
template<typename TwoDInterpPolicy, typename Distribution>
template<typename LocalTwoDInterpPolicy,
         typename ReturnType,
         typename EvaluationMethod>
inline ReturnType UnitAwareInterpolatedTabularTwoDDistributionImplBase<TwoDInterpPolicy,Distribution>::evaluateImpl(
                        const PrimaryIndepQuantity primary_indep_var_value,
                        const SecondaryIndepQuantity secondary_indep_var_value,
                        EvaluationMethod evaluate,
                        const ReturnType below_lower_bound_return,
                        const ReturnType above_upper_bound_return ) const
{
  // Find the bin boundaries
  typename DistributionType::const_iterator lower_bin_boundary, upper_bin_boundary;
  
  this->findBinBoundaries( primary_indep_var_value,
                           lower_bin_boundary,
                           upper_bin_boundary );
  
  // Check for a primary value outside of the primary grid limits
  if( lower_bin_boundary == upper_bin_boundary )
  {
    if( this->arePrimaryLimitsExtended() )
      return ((*lower_bin_boundary->second).*evaluate)(secondary_indep_var_value);
    else 
      return QuantityTraits<ReturnType>::zero();
  }
  else
  {
    // Create the grid evaluation functors
    std::function<ReturnType(const SecondaryIndepQuantity)>
      evaluate_grid_0_functor =
      std::bind<ReturnType>( evaluate,
                             std::cref( *lower_bin_boundary->second ),
                             std::placeholders::_1 );
  
    std::function<ReturnType(const SecondaryIndepQuantity)>
      evaluate_grid_1_functor =
      std::bind<ReturnType>( evaluate,
                             std::cref( *upper_bin_boundary->second ),
                             std::placeholders::_1 );
  
    return LocalTwoDInterpPolicy::interpolateUnitBase(
                         lower_bin_boundary->first,
                         upper_bin_boundary->first,
                         primary_indep_var_value,
                         secondary_indep_var_value,
                         lower_bin_boundary->second->getLowerBoundOfIndepVar(),
                         lower_bin_boundary->second->getUpperBoundOfIndepVar(),
                         upper_bin_boundary->second->getLowerBoundOfIndepVar(),
                         upper_bin_boundary->second->getUpperBoundOfIndepVar(),
                         evaluate_grid_0_functor,
                         evaluate_grid_1_functor,
                         below_lower_bound_return,
                         above_upper_bound_return );
  }
}

// Return a random sample from the secondary conditional PDF
/*! \details A stochastic sampling procedure is used. If the primary value
 * provided is outside of the primary grid limits the appropriate limiting
 * secondary distribution will be used to create the sample. The alternative
 * to this behavior is to throw an exception unless the distribution has 
 * been extended by calling the extendBeyondPrimaryIndepLimits method. Since
 * this is a performance critical method we decided against this behavior.
 */
template<typename TwoDInterpPolicy, typename Distribution>
auto UnitAwareInterpolatedTabularTwoDDistributionImplBase<TwoDInterpPolicy,Distribution>::sampleSecondaryConditional(
                     const PrimaryIndepQuantity primary_indep_var_value ) const
  -> SecondaryIndepQuantity
{
  // Create the sampling functor
  std::function<SecondaryIndepQuantity(const BaseOneDDistributionType&)>
    sampling_functor = std::bind<SecondaryIndepQuantity>(
                                             &BaseOneDDistributionType::sample,
                                             std::placeholders::_1 );

  return this->sampleImpl( primary_indep_var_value, sampling_functor );
}

// Return a random sample and record the number of trials
/*! \details A stochastic sampling procedure is used. If the primary value
 * provided is outside of the primary grid limits the appropriate limiting
 * secondary distribution will be used to create the sample. The alternative
 * to this behavior is to throw an exception unless the distribution has 
 * been extended by calling the extendBeyondPrimaryIndepLimits method. Since
 * this is a performance critical method we decided against this behavior.
 */
template<typename TwoDInterpPolicy, typename Distribution>
auto UnitAwareInterpolatedTabularTwoDDistributionImplBase<TwoDInterpPolicy,Distribution>::sampleSecondaryConditionalAndRecordTrials(
                            const PrimaryIndepQuantity primary_indep_var_value,
                            unsigned& trials ) const
  -> SecondaryIndepQuantity
{
  // Create the sampling functor
  std::function<SecondaryIndepQuantity(const BaseOneDDistributionType&)>
    sampling_functor = std::bind<SecondaryIndepQuantity>(
                              &BaseOneDDistributionType::sampleAndRecordTrials,
                              std::placeholders::_1,
                              std::ref( trials ) );

  return this->sampleImpl( primary_indep_var_value, sampling_functor );
}

// Sample from the distribution using the desired sampling functor
template<typename TwoDInterpPolicy, typename Distribution>
template<typename SampleFunctor>
auto UnitAwareInterpolatedTabularTwoDDistributionImplBase<TwoDInterpPolicy,Distribution>::sampleImpl(
                            const PrimaryIndepQuantity primary_indep_var_value,
                            SampleFunctor sample_functor ) const
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

  return sample_functor( *sampled_bin_boundary->second );
}

// Sample the bin boundary that will be used for stochastic sampling
/*! \details This method will throw an exception if the primary independent
 * value is outside of the primary grid limits and the primary grid has not
 * been extended.
 */
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
    double interpolation_fraction;

    {
      const double processed_lower_bin_boundary = 
        TwoDInterpPolicy::processFirstIndepVar( lower_bin_boundary->first );

      interpolation_fraction =
        (TwoDInterpPolicy::processFirstIndepVar( primary_indep_var_value ) -
         processed_lower_bin_boundary)/
        (TwoDInterpPolicy::processFirstIndepVar( upper_bin_boundary->first ) -
         processed_lower_bin_boundary );
    }

    // Sample to determine the distribution that will be used
    double random_number =
      Utility::RandomNumberGenerator::getRandomNumber<double>();

    if( random_number < interpolation_fraction )
      return upper_bin_boundary;
    else
      return lower_bin_boundary;
  }
  else
  {
    if( this->arePrimaryLimitsExtended() )
      return lower_bin_boundary;
    else
    {
      THROW_EXCEPTION( std::logic_error,
                       "Error: Sampling beyond the primary grid boundaries "
                       "cannot be done unless the grid has been extended ("
                       << primary_indep_var_value << " not in ["
                       << this->getLowerBoundOfPrimaryIndepVar() << ","
                       << this->getUpperBoundOfPrimaryIndepVar() << "])!" );
    }
  }
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

  // Check for a primary value outside of the primary grid limits
  if( lower_bin_boundary == upper_bin_boundary )
  {
    if( this->arePrimaryLimitsExtended() )
      return lower_bin_boundary->second->getUpperBoundOfIndepVar();
    else
      return QuantityTraits<SecondaryIndepQuantity>::zero();
  }
  else
  {
    return TwoDInterpPolicy::calculateIntermediateGridLimit(
                       lower_bin_boundary->first,
                       upper_bin_boundary->first,
                       primary_indep_var_value,
                       lower_bin_boundary->second->getUpperBoundOfIndepVar(),
                       upper_bin_boundary->second->getUpperBoundOfIndepVar() );
  }
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

  // Check for a primary value outside of the primary grid limits
  if( lower_bin_boundary == upper_bin_boundary )
  {
    if( this->arePrimaryLimitsExtended() )
      return lower_bin_boundary->second->getLowerBoundOfIndepVar();
    else
      return QuantityTraits<SecondaryIndepQuantity>::zero();
  }
  else
  {
    return TwoDInterpPolicy::calculateIntermediateGridLimit(
                       lower_bin_boundary->first,
                       upper_bin_boundary->first,
                       primary_indep_var_value,
                       lower_bin_boundary->second->getLowerBoundOfIndepVar(),
                       upper_bin_boundary->second->getLowerBoundOfIndepVar() );
  }
}

// Test if the distribution is continuous in the primary dimension
template<typename TwoDInterpPolicy, typename Distribution>
bool UnitAwareInterpolatedTabularTwoDDistributionImplBase<TwoDInterpPolicy,Distribution>::isPrimaryDimensionContinuous() const
{
  return true;
}

// Constructor
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
    distribution[i].first = primary_indep_grid[i];
    distribution[i].second.reset(
          new UnitAwareTabularDistribution<typename TwoDInterpPolicy::SecondaryBasePolicy,SecondaryIndependentUnit,DependentUnit>(
                                                      secondary_indep_grids[i],
                                                      dependent_values[i] ) );
  }

  // Set the 2D distribution
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
  return this->template evaluateImpl<CDFInterpPolicy,double>(
                                      primary_indep_var_value,
                                      secondary_indep_var_value,
                                      &BaseOneDDistributionType::evaluateCDF,
                                      0.0,
                                      1.0 );
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

  return this->sampleSecondaryConditionalExactWithRandomNumber(
                                      primary_indep_var_value, random_number );
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
  // Create the sampling functor
  std::function<SecondaryIndepQuantity(const BaseOneDDistributionType&)>
    sampling_functor = std::bind<SecondaryIndepQuantity>(
                            &BaseOneDDistributionType::sampleAndRecordBinIndex,
                            std::placeholders::_1,
                            std::ref( sampled_bin_index ) );

  return this->sampleImpl( primary_indep_var_value, sampling_functor );
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
  // Create the sampling functor
  std::function<SecondaryIndepQuantity(const BaseOneDDistributionType&)>
    sampling_functor = std::bind<SecondaryIndepQuantity>(
                             &BaseOneDDistributionType::sampleWithRandomNumber,
                             std::placeholders::_1,
                             random_number );

  return this->sampleImpl( primary_indep_var_value, sampling_functor );
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
  // Create the sampling functor
  std::function<SecondaryIndepQuantity(const BaseOneDDistributionType&)>
    sampling_functor = std::bind<SecondaryIndepQuantity>(
                                   &BaseOneDDistributionType::sampleInSubrange,
                                   std::placeholders::_1,
                                   max_secondary_indep_var_value );
    
  return this->sampleImpl( primary_indep_var_value, sampling_functor );
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
  // Create the sampling functor
  std::function<SecondaryIndepQuantity(const BaseOneDDistributionType&)>
    sampling_functor = std::bind<SecondaryIndepQuantity>(
                   &BaseOneDDistributionType::sampleWithRandomNumberInSubrange,
                   std::placeholders::_1,
                   random_number,
                   max_secondary_indep_var_value );

  return this->sampleImpl( primary_indep_var_value, sampling_functor );
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
