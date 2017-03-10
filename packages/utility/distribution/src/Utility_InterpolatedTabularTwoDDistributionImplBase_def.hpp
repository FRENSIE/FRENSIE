//---------------------------------------------------------------------------//
//!
//! \file   Utility_InterpolatedTabularTwoDDistributionImplBase_def.hpp
//! \author Alex Robinson
//! \brief  The interpolated tabular two-dimensional dist. helper class defs.
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_INTERPOLATED_TABULAR_TWO_D_DISTRIBUTION_IMPL_BASE_DEF_HPP
#define UTILITY_INTERPOLATED_TABULAR_TWO_D_DISTRIBUTION_IMPL_BASE_DEF_HPP

// FRENSIE Includes
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_ContractException.hpp"

namespace Utility{

// Constructor
template<typename TwoDInterpPolicy, typename Distribution>
UnitAwareInterpolatedTabularTwoDDistributionImplBase<TwoDInterpPolicy,Distribution>::UnitAwareInterpolatedTabularTwoDDistributionImplBase(
                                         const DistributionType& distribution,
                                         const double fuzzy_boundary_tol )
    : ParentType( distribution ),
      d_fuzzy_boundary_tol( fuzzy_boundary_tol )
{
  // Make sure the distributions are continuous
  testPrecondition( this->areSecondaryDistributionsContinuous() );
  // Make sure the distributions are compatible with the requested interp
  testPrecondition( this->areSecondaryDistsCompatibleWithInterpType( distribution ) );
  // Make sure the fuzzy boundary tolerance is valid
  testPrecondition( d_fuzzy_boundary_tol >= 0.0 )
  testPrecondition( d_fuzzy_boundary_tol < 1.0 )
}

// Constructor
template<typename TwoDInterpPolicy, typename Distribution>
template<template<typename T, typename... Args> class ArrayA,
         template<typename T, typename... Args> class ArrayB>
UnitAwareInterpolatedTabularTwoDDistributionImplBase<TwoDInterpPolicy,Distribution>::UnitAwareInterpolatedTabularTwoDDistributionImplBase(
                const ArrayA<PrimaryIndepQuantity>& primary_indep_grid,
                const ArrayB<std::shared_ptr<const BaseOneDDistributionType> >&
                secondary_distributions,
                const double fuzzy_boundary_tol )
  : ParentType( primary_indep_grid, secondary_distributions ),
    d_fuzzy_boundary_tol( fuzzy_boundary_tol )
{
  // Make sure the distributions are continuous
  testPrecondition( this->areSecondaryDistributionsContinuous() );
  // Make sure the distributions are compatible with the requested interp
  testPrecondition( this->areSecondaryDistsCompatibleWithInterpType( secondary_distributions ) );
  // Make sure the fuzzy boundary tolerance is valid
  testPrecondition( d_fuzzy_boundary_tol >= 0.0 )
  testPrecondition( d_fuzzy_boundary_tol < 1.0 )
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

// Return the upper bound of the distribution secondary independent variable using interpolation
template<typename TwoDInterpPolicy, typename Distribution>
auto UnitAwareInterpolatedTabularTwoDDistributionImplBase<TwoDInterpPolicy,Distribution>::getUpperInterpolatedBoundOfSecondaryIndepVar(
                const PrimaryIndepQuantity primary_indep_var_value ) const
  -> SecondaryIndepQuantity
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
      return lower_bin_boundary->second->getUpperBoundOfIndepVar();
    else 
      return QuantityTraits<SecondaryIndepQuantity>::zero();
  }
  else if( lower_bin_boundary->first == primary_indep_var_value )
  {
    return lower_bin_boundary->second->getUpperBoundOfIndepVar();
  }
  else if( upper_bin_boundary->first == primary_indep_var_value )
  {
    return upper_bin_boundary->second->getUpperBoundOfIndepVar();
  }
  else
  {
    return this->getUpperInterpolatedBoundOfSecondaryIndepVar(
                      primary_indep_var_value,
                      lower_bin_boundary,
                      upper_bin_boundary );
  }
}

// Return the lower bound of the distribution secondary independent variable using interpolation
template<typename TwoDInterpPolicy, typename Distribution>
auto UnitAwareInterpolatedTabularTwoDDistributionImplBase<TwoDInterpPolicy,Distribution>::getLowerInterpolatedBoundOfSecondaryIndepVar(
                const PrimaryIndepQuantity primary_indep_var_value ) const
  -> SecondaryIndepQuantity
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
      return lower_bin_boundary->second->getLowerBoundOfIndepVar();
    else 
      return QuantityTraits<SecondaryIndepQuantity>::zero();
  }
  else if( lower_bin_boundary->first == primary_indep_var_value )
  {
    return lower_bin_boundary->second->getLowerBoundOfIndepVar();
  }
  else if( upper_bin_boundary->first == primary_indep_var_value )
  {
    return upper_bin_boundary->second->getLowerBoundOfIndepVar();
  }
  else
  {
    return this->getLowerInterpolatedBoundOfSecondaryIndepVar(
                      primary_indep_var_value,
                      lower_bin_boundary,
                      upper_bin_boundary );
  }
}

// Return the upper bound of the distribution secondary independent variable using interpolation
template<typename TwoDInterpPolicy, typename Distribution>
auto UnitAwareInterpolatedTabularTwoDDistributionImplBase<TwoDInterpPolicy,Distribution>::getUpperInterpolatedBoundOfSecondaryIndepVar(
        const PrimaryIndepQuantity primary_indep_var_value,
        const typename DistributionType::const_iterator lower_bin_boundary,
        const typename DistributionType::const_iterator upper_bin_boundary ) const
  -> SecondaryIndepQuantity
{
    return TwoDInterpPolicy::ZXInterpPolicy::interpolate(
                      lower_bin_boundary->first,
                      upper_bin_boundary->first,
                      primary_indep_var_value,
                      lower_bin_boundary->second->getUpperBoundOfIndepVar(),
                      upper_bin_boundary->second->getUpperBoundOfIndepVar() );
}

// Return the lower bound of the distribution secondary independent variable using interpolation
template<typename TwoDInterpPolicy, typename Distribution>
auto UnitAwareInterpolatedTabularTwoDDistributionImplBase<TwoDInterpPolicy,Distribution>::getLowerInterpolatedBoundOfSecondaryIndepVar(
        const PrimaryIndepQuantity primary_indep_var_value,
        const typename DistributionType::const_iterator lower_bin_boundary,
        const typename DistributionType::const_iterator upper_bin_boundary ) const
  -> SecondaryIndepQuantity
{
    return  TwoDInterpPolicy::ZXInterpPolicy::interpolate(
                      lower_bin_boundary->first,
                      upper_bin_boundary->first,
                      primary_indep_var_value,
                      lower_bin_boundary->second->getLowerBoundOfIndepVar(),
                      upper_bin_boundary->second->getLowerBoundOfIndepVar() );
}

// Evaluate the distribution using unit based interpolation
template<typename TwoDInterpPolicy, typename Distribution>
auto UnitAwareInterpolatedTabularTwoDDistributionImplBase<TwoDInterpPolicy,Distribution>::evaluate(
                const PrimaryIndepQuantity primary_indep_var_value,
                const SecondaryIndepQuantity secondary_indep_var_value ) const
  -> DepQuantity
{
  return this->evaluateImpl<TwoDInterpPolicy,DepQuantity>(
                                          primary_indep_var_value,
                                          secondary_indep_var_value,
                                          &BaseOneDDistributionType::evaluate );
}

//// Evaluate the distribution
//template<typename TwoDInterpPolicy, typename Distribution>
//auto UnitAwareInterpolatedTabularTwoDDistributionImplBase<TwoDInterpPolicy,Distribution>::evaluateExact(
//                 const PrimaryIndepQuantity primary_indep_var_value,
//                 const SecondaryIndepQuantity secondary_indep_var_value ) const
//  -> DepQuantity
//{
//  return this->evaluateExactImpl<TwoDInterpPolicy,DepQuantity>(
//                                          primary_indep_var_value,
//                                          secondary_indep_var_value,
//                                          &BaseOneDDistributionType::evaluate );
//}

//// Evaluate the distribution using normalized interpolation
//template<typename TwoDInterpPolicy, typename Distribution>
//auto UnitAwareInterpolatedTabularTwoDDistributionImplBase<TwoDInterpPolicy,Distribution>::evaluateNormalized(
//                 const PrimaryIndepQuantity primary_indep_var_value,
//                 const double normalized_secondary_indep_var_value ) const
//  -> DepQuantity
//{
//  return this->evaluateNormalizedImpl<TwoDInterpPolicy,DepQuantity>(
//                                          primary_indep_var_value,
//                                          normalized_secondary_indep_var_value,
//                                          &BaseOneDDistributionType::evaluate );
//}


// Evaluate the secondary conditional PDF using unit based interpolation
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

//// Evaluate the secondary conditional PDF
//template<typename TwoDInterpPolicy, typename Distribution>
//auto UnitAwareInterpolatedTabularTwoDDistributionImplBase<TwoDInterpPolicy,Distribution>::evaluateSecondaryConditionalPDFExact(
//                 const PrimaryIndepQuantity primary_indep_var_value,
//                 const SecondaryIndepQuantity secondary_indep_var_value ) const
//  -> InverseSecondaryIndepQuantity
//{
//  return this->evaluateExactImpl<TwoDInterpPolicy,InverseSecondaryIndepQuantity>(
//                                      primary_indep_var_value,
//                                      secondary_indep_var_value,
//                                      &BaseOneDDistributionType::evaluatePDF );
//}

//// Evaluate the secondary conditional PDF using normalized interpolation
//template<typename TwoDInterpPolicy, typename Distribution>
//auto UnitAwareInterpolatedTabularTwoDDistributionImplBase<TwoDInterpPolicy,Distribution>::evaluateSecondaryConditionalPDFNormalized(
//                 const PrimaryIndepQuantity primary_indep_var_value,
//                 const double normalized_secondary_indep_var_value ) const
//  ->  InverseSecondaryIndepQuantity
//{
//  return this->evaluateNormalizedImpl<TwoDInterpPolicy,InverseSecondaryIndepQuantity>(
//                                          primary_indep_var_value,
//                                          normalized_secondary_indep_var_value,
//                                          &BaseOneDDistributionType::evaluatePDF );
//}

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
                         above_upper_bound_return,
                         d_fuzzy_boundary_tol );
  }
}

// Evaluate the distribution using the desired evaluation method
template<typename TwoDInterpPolicy, typename Distribution>
template<typename LocalTwoDInterpPolicy,
         typename ReturnType,
         typename EvaluationMethod>
inline ReturnType UnitAwareInterpolatedTabularTwoDDistributionImplBase<TwoDInterpPolicy,Distribution>::evaluateExactImpl(
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
    // Check for a primary value at the primary grid upper limit
    if( primary_indep_var_value == upper_bin_boundary->first )
    {
      return ((*upper_bin_boundary->second).*evaluate)(secondary_indep_var_value);
    }
    else if( primary_indep_var_value == lower_bin_boundary->first )
    {
      return ((*lower_bin_boundary->second).*evaluate)(secondary_indep_var_value);
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

      return LocalTwoDInterpPolicy::interpolate(
                           lower_bin_boundary->first,
                           upper_bin_boundary->first,
                           primary_indep_var_value,
                           secondary_indep_var_value,
                           evaluate_grid_0_functor,
                           evaluate_grid_1_functor );
    }
  }
}

// Evaluate the distribution using the desired evaluation method and the ratio of the secondary indep variable
/*! \details The distribution is evaluated with a correlated routine that
 * evaluates the upper and lower distributions using the secondary indepent
 * variable normalized by the max secondary independent variable.
 * This allows the upper and lower distributions with different max secondary
 * indepent variables to be sampled to sampled correctly.
 */
template<typename TwoDInterpPolicy, typename Distribution>
template<typename LocalTwoDInterpPolicy,
         typename ReturnType,
         typename EvaluationMethod>
inline ReturnType UnitAwareInterpolatedTabularTwoDDistributionImplBase<TwoDInterpPolicy,Distribution>::evaluateNormalizedImpl(
                        const PrimaryIndepQuantity primary_indep_var_value,
                        const SecondaryIndepQuantity secondary_indep_var_value,
                        const SecondaryIndepQuantity min_secondary_indep_var,
                        const SecondaryIndepQuantity max_secondary_indep_var,
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
    {
      return ((*lower_bin_boundary->second).*evaluate)(secondary_indep_var_value);
    }
    else
      return QuantityTraits<ReturnType>::zero();
  }
  else
  {
    // Check for a primary value at the primary grid upper limit
    if( primary_indep_var_value == upper_bin_boundary->first )
    {
      return ((*upper_bin_boundary->second).*evaluate)(secondary_indep_var_value);
    }
    else if( primary_indep_var_value == lower_bin_boundary->first )
    {
      return ((*lower_bin_boundary->second).*evaluate)(secondary_indep_var_value);
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

      double normalized_secondary_indep_var_value =
            secondary_indep_var_value/max_secondary_indep_var;

      return LocalTwoDInterpPolicy::interpolateWeighted(
                           lower_bin_boundary->first,
                           upper_bin_boundary->first,
                           primary_indep_var_value,
                           normalized_secondary_indep_var_value,
                           evaluate_grid_0_functor,
                           evaluate_grid_1_functor,
                           lower_bin_boundary->second->getUpperBoundOfIndepVar(),
                           upper_bin_boundary->second->getUpperBoundOfIndepVar() );
    }
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

// Return a random sample from the secondary conditional PDF
/*! \details A stochastic exact sampling procedure is used. If the primary value
 * provided is outside of the primary grid limits the appropriate limiting
 * secondary distribution will be used to create the sample. The alternative
 * to this behavior is to throw an exception unless the distribution has 
 * been extended by calling the extendBeyondPrimaryIndepLimits method. Since
 * this is a performance critical method we decided against this behavior.
 */
template<typename TwoDInterpPolicy, typename Distribution>
auto UnitAwareInterpolatedTabularTwoDDistributionImplBase<TwoDInterpPolicy,Distribution>::sampleSecondaryConditionalExact(
                     const PrimaryIndepQuantity primary_indep_var_value ) const
  -> SecondaryIndepQuantity
{
  // Create the sampling functor
  std::function<SecondaryIndepQuantity(const BaseOneDDistributionType&)>
    sampling_functor = std::bind<SecondaryIndepQuantity>(
                             &BaseOneDDistributionType::sample,
                             std::placeholders::_1 );

  return this->sampleExactImpl( primary_indep_var_value, sampling_functor );
}


// Return a random sample from the secondary conditional PDF using a normalized interpolation
/*! \details A stochastic normalized sampling procedure is used. If the primary
 * value provided is outside of the primary grid limits the appropriate limiting
 * secondary distribution will be used to create the sample. The alternative
 * to this behavior is to throw an exception unless the distribution has
 * been extended by calling the extendBeyondPrimaryIndepLimits method. Since
 * this is a performance critical method we decided against this behavior.
 */
template<typename TwoDInterpPolicy, typename Distribution>
auto UnitAwareInterpolatedTabularTwoDDistributionImplBase<TwoDInterpPolicy,Distribution>::sampleSecondaryConditionalNormalized(
        const PrimaryIndepQuantity primary_indep_var_value,
        const SecondaryIndepQuantity min_secondary_indep_var,
        const SecondaryIndepQuantity max_secondary_indep_var ) const
  -> SecondaryIndepQuantity
{
  // Create the sampling functor
  std::function<SecondaryIndepQuantity(const BaseOneDDistributionType&)>
    sampling_functor = std::bind<SecondaryIndepQuantity>(
                             &BaseOneDDistributionType::sample,
                             std::placeholders::_1 );

  return this->sampleNormalizedImpl( primary_indep_var_value,
                                     min_secondary_indep_var,
                                     max_secondary_indep_var,
                                     sampling_functor );
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
inline auto UnitAwareInterpolatedTabularTwoDDistributionImplBase<TwoDInterpPolicy,Distribution>::sampleDetailedImpl(
                            const PrimaryIndepQuantity primary_indep_var_value,
                            SampleFunctor sample_functor,
                            SecondaryIndepQuantity& raw_sample,
                            unsigned& primary_bin_index ) const
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

  // Calculate the index of the primary bin boundary that will be used to
  // create the secondary conditional sample
  primary_bin_index = this->calculateBinIndex( sampled_bin_boundary );

  // Create the raw sample
  raw_sample = sample_functor( *sampled_bin_boundary->second );

  // Calculate the intermediate grid limits
  SecondaryIndepQuantity y_x_min = this->getLowerBoundOfConditionalIndepVar(
                                                     primary_indep_var_value );

  SecondaryIndepQuantity y_x_max = this->getUpperBoundOfConditionalIndepVar(
                                                     primary_indep_var_value );

  typename QuantityTraits<SecondaryIndepQuantity>::RawType
    intermediate_grid_length =
    TwoDInterpPolicy::SecondaryBasePolicy::calculateUnitBaseGridLength(
                                                            y_x_min, y_x_max );
  
  // Calculate the unit base variable on the bin boundary corresponding to the
  // raw sample
  typename QuantityTraits<SecondaryIndepQuantity>::RawType eta;

  {
    typename QuantityTraits<SecondaryIndepQuantity>::RawType grid_length =
      TwoDInterpPolicy::SecondaryBasePolicy::calculateUnitBaseGridLength(
                      sampled_bin_boundary->second->getLowerBoundOfIndepVar(),
                      sampled_bin_boundary->second->getUpperBoundOfIndepVar());
    
    eta = TwoDInterpPolicy::SecondaryBasePolicy::calculateUnitBaseIndepVar(
                       raw_sample,
                       sampled_bin_boundary->second->getLowerBoundOfIndepVar(),
                       grid_length );
  }
  
  // Scale the sample so that it preserves the intermediate limits.
  // Note: This is a stochastic procedure. The intermediate distribution that
  //       has been sampled is not the true distribution. The expected value
  //       of a sample will be a sample from the true distribution though.
  return TwoDInterpPolicy::SecondaryBasePolicy::calculateIndepVar(
                                      eta, y_x_min, intermediate_grid_length );
}

// Sample from the distribution using the desired sampling functor and a correlated routine
template<typename TwoDInterpPolicy, typename Distribution>
template<typename SampleFunctor>
inline auto UnitAwareInterpolatedTabularTwoDDistributionImplBase<TwoDInterpPolicy,Distribution>::sampleExactDetailedImpl(
                const PrimaryIndepQuantity primary_indep_var_value,
                SampleFunctor sample_functor,
                SecondaryIndepQuantity& raw_sample,
                unsigned& primary_bin_index ) const
  -> SecondaryIndepQuantity
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
    {
      // Create the raw sample
      raw_sample = sample_functor( *lower_bin_boundary->second );

      return raw_sample;
    }
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
  else
  {
    // Check for a primary value at the primary grid upper limit
    if( primary_indep_var_value == upper_bin_boundary->first )
    {
      // Create the raw sample
      raw_sample = sample_functor( *upper_bin_boundary->second );

      return raw_sample;
    }
    else if( primary_indep_var_value == lower_bin_boundary->first )
    {
      // Create the raw sample
      raw_sample = sample_functor( *lower_bin_boundary->second );

      return raw_sample;
    }
    else
    {
      raw_sample = TwoDInterpPolicy::ZXInterpPolicy::interpolate(
                           lower_bin_boundary->first,
                           upper_bin_boundary->first,
                           primary_indep_var_value,
                           sample_functor( *lower_bin_boundary->second ),
                           sample_functor( *upper_bin_boundary->second ) );

      return raw_sample;
    }
  }
}

// Sample from the distribution using the desired sampling functor and a normalized interpolation
/*! \details This function uses a normalized interpolation and returns the sampled
 * value normalized by the given secondary independent weighting factor.
 */
template<typename TwoDInterpPolicy, typename Distribution>
template<typename SampleFunctor>
inline auto UnitAwareInterpolatedTabularTwoDDistributionImplBase<TwoDInterpPolicy,Distribution>::sampleNormalizedDetailedImpl(
                const PrimaryIndepQuantity primary_indep_var_value,
                const SecondaryIndepQuantity min_secondary_indep_var,
                const SecondaryIndepQuantity max_secondary_indep_var,
                SampleFunctor sample_functor,
                SecondaryIndepQuantity& raw_sample,
                unsigned& primary_bin_index ) const
  -> SecondaryIndepQuantity
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
    {
      // Create the raw sample
      raw_sample = sample_functor( *lower_bin_boundary->second );

      return raw_sample;
    }
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
  else
  {
    // Check for a primary value at the primary grid upper limit
    if( primary_indep_var_value == upper_bin_boundary->first )
    {
      // Create the raw sample
      raw_sample = sample_functor( *upper_bin_boundary->second );

      return raw_sample;
    }
    else if( primary_indep_var_value == lower_bin_boundary->first )
    {
      // Create the raw sample
      raw_sample = sample_functor( *lower_bin_boundary->second );

      return raw_sample;
    }
    else
    {
      // sample the lower and upper distributions
      double raw_sample_0 =
        ( sample_functor( *lower_bin_boundary->second ) -
                    lower_bin_boundary->second->getLowerBoundOfIndepVar() )/
        ( lower_bin_boundary->second->getUpperBoundOfIndepVar() -
                    lower_bin_boundary->second->getLowerBoundOfIndepVar() );

      double raw_sample_1 =
        ( sample_functor( *upper_bin_boundary->second ) -
                    upper_bin_boundary->second->getLowerBoundOfIndepVar() )/
        ( upper_bin_boundary->second->getUpperBoundOfIndepVar() -
                    upper_bin_boundary->second->getLowerBoundOfIndepVar() );

      double norm_sample = TwoDInterpPolicy::ZXInterpPolicy::interpolate(
                                           lower_bin_boundary->first,
                                           upper_bin_boundary->first,
                                           primary_indep_var_value,
                                           raw_sample_0,
                                           raw_sample_1 );

      raw_sample = (max_secondary_indep_var - min_secondary_indep_var)*
                                        norm_sample + min_secondary_indep_var;

      return raw_sample;
    }
  }
}

// Sample from the distribution using the desired sampling functor
template<typename TwoDInterpPolicy, typename Distribution>
template<typename SampleFunctor>
inline auto UnitAwareInterpolatedTabularTwoDDistributionImplBase<TwoDInterpPolicy,Distribution>::sampleImpl(
                            const PrimaryIndepQuantity primary_indep_var_value,
                            SampleFunctor sample_functor ) const
  -> SecondaryIndepQuantity
{
  // Dummy variables
  SecondaryIndepQuantity dummy_raw_sample;
  unsigned dummy_primary_bin_index;

  return this->sampleDetailedImpl( primary_indep_var_value,
                                   sample_functor,
                                   dummy_raw_sample,
                                   dummy_primary_bin_index );
}

// Sample from the distribution using the desired sampling functor
template<typename TwoDInterpPolicy, typename Distribution>
template<typename SampleFunctor>
inline auto UnitAwareInterpolatedTabularTwoDDistributionImplBase<TwoDInterpPolicy,Distribution>::sampleExactImpl(
                            const PrimaryIndepQuantity primary_indep_var_value,
                            SampleFunctor sample_functor ) const
  -> SecondaryIndepQuantity
{
  // Dummy variables
  SecondaryIndepQuantity dummy_raw_sample;
  unsigned dummy_primary_bin_index;

  return this->sampleExactDetailedImpl( primary_indep_var_value,
                                        sample_functor,
                                        dummy_raw_sample,
                                        dummy_primary_bin_index );
}

  //! Sample from the distribution using the desired sampling functor and a normalized interpolation
template<typename TwoDInterpPolicy, typename Distribution>
template<typename SampleFunctor>
inline auto UnitAwareInterpolatedTabularTwoDDistributionImplBase<TwoDInterpPolicy,Distribution>::sampleNormalizedImpl(
                const PrimaryIndepQuantity primary_indep_var_value,
                const SecondaryIndepQuantity min_secondary_indep_var,
                const SecondaryIndepQuantity max_secondary_indep_var,
                SampleFunctor sample_functor ) const
  -> SecondaryIndepQuantity
{
  // Dummy variables
  SecondaryIndepQuantity dummy_raw_sample;
  unsigned dummy_primary_bin_index;

  return this->sampleNormalizedDetailedImpl( primary_indep_var_value,
                                             min_secondary_indep_var,
                                             max_secondary_indep_var,
                                             sample_functor,
                                             dummy_raw_sample,
                                             dummy_primary_bin_index );
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

// Estimate the secondary conditional CDF
/*! \details This method performs a type of binary search using an exact
 *  correlated sampling to estimate the CDF to a relative error tolerance.
 */
template<typename TwoDInterpPolicy, typename Distribution>
void UnitAwareInterpolatedTabularTwoDDistributionImplBase<TwoDInterpPolicy,Distribution>::evaluateSecondaryConditionalCDFExactImpl(
        const PrimaryIndepQuantity primary_indep_var_value,
        const SecondaryIndepQuantity secondary_indep_var_value,
        const typename DistributionType::const_iterator lower_bin_boundary,
        const typename DistributionType::const_iterator upper_bin_boundary,
        double& evaluated_cdf ) const
{
  // Evaluate the cdf at the upper and lower bin boundaries
  double lower_bin_eval =
    lower_bin_boundary->second.evaluateCDF( secondary_indep_var_value );
  double upper_bin_eval =
    upper_bin_boundary->second.evaluateCDF( secondary_indep_var_value );

  // Get the lower and upper boundaries of the evaluated cdf
  double lower_cdf_bound, upper_cdf_bound;
  if ( lower_bin_eval <= upper_bin_eval )
  {
    lower_cdf_bound = lower_bin_eval;
    upper_cdf_bound = upper_bin_eval;
  }
  else
  {
    lower_cdf_bound = upper_bin_eval;
    upper_cdf_bound = lower_bin_eval;
  }

  // Set the tol
  double relative_error_tol = 1e-6;
  double rel_error = 1.0;

  // Estimate the cdf as the midpoint of the lower and upper boundaries
  evaluated_cdf = 0.5*( lower_cdf_bound + upper_cdf_bound );

  // Refine the mid_point cdf value until it meet the tolerance
  while ( rel_error > relative_error_tol )
  {
//    // Create the sampling functor
//    std::function<SecondaryIndepQuantity(const BaseOneDDistributionType&)>
//      sampling_functor = std::bind<SecondaryIndepQuantity>(
//                             &BaseOneDDistributionType::sampleWithRandomNumber,
//                             std::placeholders::_1,
//                             mid_point );
//    SecondaryIndepQuantity est_secondary_indep_var_value =
//      this->sampleExactImpl( primary_indep_var_value, sampling_functor );

    // Interpolate using the templated TwoDInterpPolicy::ZXInterpPolicy
    SecondaryIndepQuantity est_secondary_indep_var_value =
      TwoDInterpPolicy::ZXInterpPolicy::interpolate(
            lower_bin_boundary->first,
            upper_bin_boundary->first,
            primary_indep_var_value,
            lower_bin_boundary->second.sampleWithRandomNumber( evaluated_cdf ),
            upper_bin_boundary->second.sampleWithRandomNumber( evaluated_cdf ) );

    // Calculate the relative error between the secondary_indep_var_value and the estimate
    rel_error =
        std::abs( est_secondary_indep_var_value - secondary_indep_var_value )/
                                                    secondary_indep_var_value;

    // If tolerance is met exit loop
    if ( rel_error <= relative_error_tol )
        break;

    // Update the evaluated_cdf estimate
    if ( est_secondary_indep_var_value < secondary_indep_var_value )
    {
        // Old evaluated_cdf estimate is new lower cdf boundary
        evaluated_cdf = 0.5*( evaluated_cdf + upper_cdf_bound );
    }
    else
    {
        // Old evaluated_cdf estimate is new upper cdf boundary
        evaluated_cdf = 0.5*( lower_cdf_bound + evaluated_cdf );
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

} // end Utility namespace

#endif // end UTILITY_INTERPOLATED_TABULAR_TWO_D_DISTRIBUTION_IMPL_BASE_DEF_HPP

//---------------------------------------------------------------------------//
// end Utility_InterpolatedTabularTwoDDistributionImplBase_def.hpp
//---------------------------------------------------------------------------//
