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
template<typename TwoDInterpPolicy, typename TwoDSamplePolicy, typename Distribution>
UnitAwareInterpolatedTabularTwoDDistributionImplBase<TwoDInterpPolicy,TwoDSamplePolicy,Distribution>::UnitAwareInterpolatedTabularTwoDDistributionImplBase(
                                         const DistributionType& distribution,
                                         const double fuzzy_boundary_tol )
  : ParentType( distribution ),
    d_fuzzy_boundary_tol( fuzzy_boundary_tol ),
    d_relative_error_tol( 1e-7 ),
    d_error_tol( 1e-16 )
{
  // Make sure the distributions are continuous
  testPrecondition( this->areSecondaryDistributionsContinuous() );
  // Make sure the distributions are compatible with the requested interp
  //testPrecondition( this->areSecondaryDistsCompatibleWithInterpType( distribution ) );
  // Make sure the fuzzy boundary tolerance is valid
  testPrecondition( d_fuzzy_boundary_tol >= 0.0 )
  testPrecondition( d_fuzzy_boundary_tol < 1.0 )
}

// Constructor
template<typename TwoDInterpPolicy, typename TwoDSamplePolicy, typename Distribution>
template<template<typename T, typename... Args> class ArrayA,
         template<typename T, typename... Args> class ArrayB>
UnitAwareInterpolatedTabularTwoDDistributionImplBase<TwoDInterpPolicy,TwoDSamplePolicy,Distribution>::UnitAwareInterpolatedTabularTwoDDistributionImplBase(
                const ArrayA<PrimaryIndepQuantity>& primary_indep_grid,
                const ArrayB<std::shared_ptr<const BaseOneDDistributionType> >&
                secondary_distributions,
                const double fuzzy_boundary_tol )
  : ParentType( primary_indep_grid, secondary_distributions ),
    d_fuzzy_boundary_tol( fuzzy_boundary_tol ),
    d_relative_error_tol( 1e-7 ),
    d_error_tol( 1e-16 )
{
  // Make sure the distributions are continuous
  testPrecondition( this->areSecondaryDistributionsContinuous() );
  /*! \todo The compatibility of secondary with the requested interpolation
      method needs to be investigated further. There are cases where the
      2-D interpolation mathod should be agnostic to the 1-D interpolation
      method such that you could perform a Lin-Lin (y-z) interpolation in the
      OneDDistribution and a Log-Log-Log (ie: Log-Log x-z and Log-Log y-z)
      interpolation in the TwoDDistribution. For now this precondition test will
      be commented out. */
  // Make sure the distributions are compatible with the requested interp
  //testPrecondition( this->areSecondaryDistsCompatibleWithInterpType( secondary_distributions ) );
  // Make sure the fuzzy boundary tolerance is valid
  testPrecondition( d_fuzzy_boundary_tol >= 0.0 )
  testPrecondition( d_fuzzy_boundary_tol < 1.0 )
}

// Set the evaluation tolerances
template<typename TwoDInterpPolicy, typename TwoDSamplePolicy, typename Distribution>
void UnitAwareInterpolatedTabularTwoDDistributionImplBase<TwoDInterpPolicy,TwoDSamplePolicy,Distribution>::setEvaluationTolerances(
                                const double& fuzzy_boundary_tol,
                                const double& relative_error_tol,
                                const double& error_tol )
{
  // Make sure the fuzzy boundary tolerance is valid
  testPrecondition( fuzzy_boundary_tol >= 0.0 );
  testPrecondition( fuzzy_boundary_tol < 1.0 );
  // Make sure the relative error tolerance is valid
  testPrecondition( relative_error_tol >= 0.0 );
  testPrecondition( relative_error_tol < 1.0 );
  // Make sure the error tolerance is valid
  testPrecondition( error_tol >= 0.0 );
  testPrecondition( error_tol < 1.0 );

  d_fuzzy_boundary_tol = fuzzy_boundary_tol;
  d_relative_error_tol = relative_error_tol;
  d_error_tol = error_tol;
}

// Return the fuzzy bound tolerance
template<typename TwoDInterpPolicy, typename TwoDSamplePolicy, typename Distribution>
double UnitAwareInterpolatedTabularTwoDDistributionImplBase<TwoDInterpPolicy,TwoDSamplePolicy,Distribution>::getFuzzyBoundTolerance() const
{
  return d_fuzzy_boundary_tol;
}

// Return the evaluation relative error tolerance
template<typename TwoDInterpPolicy, typename TwoDSamplePolicy, typename Distribution>
double UnitAwareInterpolatedTabularTwoDDistributionImplBase<TwoDInterpPolicy,TwoDSamplePolicy,Distribution>::getRelativeErrorTolerance() const
{
  return d_relative_error_tol;
}

// Return the evaluation error tolerance
template<typename TwoDInterpPolicy, typename TwoDSamplePolicy, typename Distribution>
double UnitAwareInterpolatedTabularTwoDDistributionImplBase<TwoDInterpPolicy,TwoDSamplePolicy,Distribution>::getErrorTolerance() const
{
  return d_error_tol;
}

// Check that the secondary dists are compatible with the requested interp
template<typename TwoDInterpPolicy, typename TwoDSamplePolicy, typename Distribution>
bool UnitAwareInterpolatedTabularTwoDDistributionImplBase<TwoDInterpPolicy,TwoDSamplePolicy,Distribution>::areSecondaryDistsCompatibleWithInterpType(
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
template<typename TwoDInterpPolicy, typename TwoDSamplePolicy, typename Distribution>
template<template<typename T, typename... Args> class Array>
bool UnitAwareInterpolatedTabularTwoDDistributionImplBase<TwoDInterpPolicy,TwoDSamplePolicy,Distribution>::areSecondaryDistsCompatibleWithInterpType(
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

// Evaluate the distribution using
template<typename TwoDInterpPolicy, typename TwoDSamplePolicy, typename Distribution>
auto UnitAwareInterpolatedTabularTwoDDistributionImplBase<TwoDInterpPolicy,TwoDSamplePolicy,Distribution>::evaluate(
            const PrimaryIndepQuantity primary_indep_var_value,
            const SecondaryIndepQuantity secondary_indep_var_value ) const
  -> DepQuantity
{
  return this->evaluateImpl<TwoDInterpPolicy,DepQuantity>(
                                          primary_indep_var_value,
                                          secondary_indep_var_value,
                                          &BaseOneDDistributionType::evaluate );
}

// Evaluate the distribution using
template<typename TwoDInterpPolicy, typename TwoDSamplePolicy, typename Distribution>
auto UnitAwareInterpolatedTabularTwoDDistributionImplBase<TwoDInterpPolicy,TwoDSamplePolicy,Distribution>::evaluate(
            const PrimaryIndepQuantity primary_indep_var_value,
            const SecondaryIndepQuantity secondary_indep_var_value,
            const std::function<SecondaryIndepQuantity(PrimaryIndepQuantity)>&
              min_secondary_indep_var_functor,
            const std::function<SecondaryIndepQuantity(PrimaryIndepQuantity)>&
              max_secondary_indep_var_functor ) const
  -> DepQuantity
{
  return this->evaluateImpl<TwoDInterpPolicy,DepQuantity>(
                                          primary_indep_var_value,
                                          secondary_indep_var_value,
                                          min_secondary_indep_var_functor,
                                          max_secondary_indep_var_functor,
                                          &BaseOneDDistributionType::evaluate );
}

// Evaluate the secondary conditional PDF
template<typename TwoDInterpPolicy, typename TwoDSamplePolicy, typename Distribution>
auto UnitAwareInterpolatedTabularTwoDDistributionImplBase<TwoDInterpPolicy,TwoDSamplePolicy,Distribution>::evaluateSecondaryConditionalPDF(
            const PrimaryIndepQuantity primary_indep_var_value,
            const SecondaryIndepQuantity secondary_indep_var_value ) const
  -> InverseSecondaryIndepQuantity
{
  return this->evaluateImpl<TwoDInterpPolicy,InverseSecondaryIndepQuantity>(
                                      primary_indep_var_value,
                                      secondary_indep_var_value,
                                      &BaseOneDDistributionType::evaluatePDF );
}

// Evaluate the secondary conditional PDF
template<typename TwoDInterpPolicy, typename TwoDSamplePolicy, typename Distribution>
auto UnitAwareInterpolatedTabularTwoDDistributionImplBase<TwoDInterpPolicy,TwoDSamplePolicy,Distribution>::evaluateSecondaryConditionalPDF(
            const PrimaryIndepQuantity primary_indep_var_value,
            const SecondaryIndepQuantity secondary_indep_var_value,
            const std::function<SecondaryIndepQuantity(PrimaryIndepQuantity)>&
              min_secondary_indep_var_functor,
            const std::function<SecondaryIndepQuantity(PrimaryIndepQuantity)>&
              max_secondary_indep_var_functor ) const
  -> InverseSecondaryIndepQuantity
{
  return this->evaluateImpl<TwoDInterpPolicy,InverseSecondaryIndepQuantity>(
                                      primary_indep_var_value,
                                      secondary_indep_var_value,
                                      min_secondary_indep_var_functor,
                                      max_secondary_indep_var_functor,
                                      &BaseOneDDistributionType::evaluatePDF );
}

// Evaluate the distribution using the desired evaluation method
template<typename TwoDInterpPolicy, typename TwoDSamplePolicy, typename Distribution>
template<typename LocalTwoDInterpPolicy,
         typename ReturnType,
         typename EvaluationMethod>
inline ReturnType UnitAwareInterpolatedTabularTwoDDistributionImplBase<TwoDInterpPolicy,TwoDSamplePolicy,Distribution>::evaluateImpl(
            const PrimaryIndepQuantity primary_indep_var_value,
            const SecondaryIndepQuantity secondary_indep_var_value,
            const std::function<SecondaryIndepQuantity(PrimaryIndepQuantity)>&
              min_secondary_indep_var_functor,
            const std::function<SecondaryIndepQuantity(PrimaryIndepQuantity)>&
              max_secondary_indep_var_functor,
            EvaluationMethod evaluate,
            unsigned max_number_of_iterations ) const
{
  // Find the bin boundaries
  typename DistributionType::const_iterator lower_bin_boundary, upper_bin_boundary;

  this->findBinBoundaries( primary_indep_var_value,
                           lower_bin_boundary,
                           upper_bin_boundary );

  if( lower_bin_boundary != upper_bin_boundary )
  {
    return TwoDSamplePolicy::template evaluatePDF<LocalTwoDInterpPolicy,BaseOneDDistributionType,PrimaryIndepQuantity,SecondaryIndepQuantity,ReturnType>(
        primary_indep_var_value,
        secondary_indep_var_value,
        min_secondary_indep_var_functor,
        max_secondary_indep_var_functor,
        evaluate,
        lower_bin_boundary,
        upper_bin_boundary,
        d_fuzzy_boundary_tol,
        d_relative_error_tol,
        d_error_tol,
        max_number_of_iterations );
  }
  // Primary value is outside of the primary grid limits
  else
  {
    if( this->arePrimaryLimitsExtended() )
    {
      return ((*lower_bin_boundary->second).*evaluate)(secondary_indep_var_value);
    }
    else 
      return QuantityTraits<ReturnType>::zero();
  }
}

// Evaluate the distribution using the desired evaluation method
template<typename TwoDInterpPolicy, typename TwoDSamplePolicy, typename Distribution>
template<typename LocalTwoDInterpPolicy,
         typename ReturnType,
         typename EvaluationMethod>
inline ReturnType UnitAwareInterpolatedTabularTwoDDistributionImplBase<TwoDInterpPolicy,TwoDSamplePolicy,Distribution>::evaluateImpl(
            const PrimaryIndepQuantity primary_indep_var_value,
            const SecondaryIndepQuantity secondary_indep_var_value,
            EvaluationMethod evaluate ) const
{
    // Create the lower bound functor
    std::function<SecondaryIndepQuantity(const PrimaryIndepQuantity)>
      min_secondary_indep_var_functor = std::bind<SecondaryIndepQuantity>(
                                &ThisType::getLowerBoundOfConditionalIndepVar,
                                std::cref( *this ),
                                std::placeholders::_1 );

    // Create the upper bound functor
    std::function<SecondaryIndepQuantity(const PrimaryIndepQuantity)>
      max_secondary_indep_var_functor = std::bind<SecondaryIndepQuantity>(
                                &ThisType::getUpperBoundOfConditionalIndepVar,
                                std::cref( *this ),
                                std::placeholders::_1 );

  return this->evaluateImpl<LocalTwoDInterpPolicy,ReturnType,EvaluationMethod>(
              primary_indep_var_value,
              secondary_indep_var_value,
              min_secondary_indep_var_functor,
              max_secondary_indep_var_functor,
              evaluate );
}

// Evaluate the distribution using the desired CDF evaluation method
template<typename TwoDInterpPolicy, typename TwoDSamplePolicy, typename Distribution>
template<typename LocalTwoDInterpPolicy,
         typename EvaluationMethod>
inline double UnitAwareInterpolatedTabularTwoDDistributionImplBase<TwoDInterpPolicy,TwoDSamplePolicy,Distribution>::evaluateCDFImpl(
            const PrimaryIndepQuantity primary_indep_var_value,
            const SecondaryIndepQuantity secondary_indep_var_value,
            const std::function<SecondaryIndepQuantity(PrimaryIndepQuantity)>&
              min_secondary_indep_var_functor,
            const std::function<SecondaryIndepQuantity(PrimaryIndepQuantity)>&
              max_secondary_indep_var_functor,
            EvaluationMethod evaluateCDF,
            unsigned max_number_of_iterations ) const
{
  // Find the bin boundaries
  typename DistributionType::const_iterator lower_bin_boundary, upper_bin_boundary;

  this->findBinBoundaries( primary_indep_var_value,
                           lower_bin_boundary,
                           upper_bin_boundary );

  if( lower_bin_boundary != upper_bin_boundary )
  {
    return TwoDSamplePolicy::template evaluateCDF<LocalTwoDInterpPolicy,BaseOneDDistributionType,PrimaryIndepQuantity,SecondaryIndepQuantity>(
        primary_indep_var_value,
        secondary_indep_var_value,
        min_secondary_indep_var_functor,
        max_secondary_indep_var_functor,
        evaluateCDF,
        lower_bin_boundary,
        upper_bin_boundary,
        d_fuzzy_boundary_tol,
        d_relative_error_tol,
        d_error_tol,
        max_number_of_iterations );
  }
  // Primary value is outside of the primary grid limits
  else
  {
    if( this->arePrimaryLimitsExtended() )
    {
      return ((*lower_bin_boundary->second).*evaluateCDF)(secondary_indep_var_value);
    }
    else 
      return 0.0;
  }
}

// Evaluate the distribution using the desired CDF evaluation method
template<typename TwoDInterpPolicy, typename TwoDSamplePolicy, typename Distribution>
template<typename LocalTwoDInterpPolicy,
         typename EvaluationMethod>
inline double UnitAwareInterpolatedTabularTwoDDistributionImplBase<TwoDInterpPolicy,TwoDSamplePolicy,Distribution>::evaluateCDFImpl(
            const PrimaryIndepQuantity primary_indep_var_value,
            const SecondaryIndepQuantity secondary_indep_var_value,
            EvaluationMethod evaluateCDF ) const
{
    // Create the lower bound functor
    std::function<SecondaryIndepQuantity(const PrimaryIndepQuantity)>
      min_secondary_indep_var_functor = std::bind<SecondaryIndepQuantity>(
                                &ThisType::getLowerBoundOfConditionalIndepVar,
                                std::cref( *this ),
                                std::placeholders::_1 );

    // Create the upper bound functor
    std::function<SecondaryIndepQuantity(const PrimaryIndepQuantity)>
      max_secondary_indep_var_functor = std::bind<SecondaryIndepQuantity>(
                                &ThisType::getUpperBoundOfConditionalIndepVar,
                                std::cref( *this ),
                                std::placeholders::_1 );

  return this->evaluateCDFImpl<LocalTwoDInterpPolicy,EvaluationMethod>(
              primary_indep_var_value,
              secondary_indep_var_value,
              min_secondary_indep_var_functor,
              max_secondary_indep_var_functor,
              evaluateCDF );
}

// Return a random sample from the secondary conditional PDF
/*! \details If the primary value provided is outside of the primary grid limits
 * the appropriate limiting secondary distribution will be used to create the
 * sample. The alternative to this behavior is to throw an exception unless the
 * distribution has been extended by calling the extendBeyondPrimaryIndepLimits
 * method. Since this is a performance critical method we decided against this
 * behavior.
 */
template<typename TwoDInterpPolicy, typename TwoDSamplePolicy, typename Distribution>
auto UnitAwareInterpolatedTabularTwoDDistributionImplBase<TwoDInterpPolicy,TwoDSamplePolicy,Distribution>::sampleSecondaryConditional(
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
/*! \details If the primary value provided is outside of the primary grid limits
 * the appropriate limiting secondary distribution will be used to create the
 * sample. The alternative to this behavior is to throw an exception unless the
 * distribution has been extended by calling the extendBeyondPrimaryIndepLimits
 * method. Since this is a performance critical method we decided against this
 * behavior.
 */
template<typename TwoDInterpPolicy, typename TwoDSamplePolicy, typename Distribution>
auto UnitAwareInterpolatedTabularTwoDDistributionImplBase<TwoDInterpPolicy,TwoDSamplePolicy,Distribution>::sampleSecondaryConditional(
            const PrimaryIndepQuantity primary_indep_var_value,
            const std::function<SecondaryIndepQuantity(PrimaryIndepQuantity)>&
              min_secondary_indep_var_functor,
            const std::function<SecondaryIndepQuantity(PrimaryIndepQuantity)>&
              max_secondary_indep_var_functor ) const
  -> SecondaryIndepQuantity
{
  // Create the sampling functor
  std::function<SecondaryIndepQuantity(const BaseOneDDistributionType&)>
    sampling_functor = std::bind<SecondaryIndepQuantity>(
                                             &BaseOneDDistributionType::sample,
                                             std::placeholders::_1 );

  return this->sampleImpl( primary_indep_var_value,
                           sampling_functor,
                           min_secondary_indep_var_functor,
                           max_secondary_indep_var_functor );
}

// Return a random sample and record the number of trials
/*! \details If the primary value provided is outside of the primary grid limits
 * the appropriate limiting secondary distribution will be used to create the
 * sample. The alternative to this behavior is to throw an exception unless the
 * distribution has been extended by calling the extendBeyondPrimaryIndepLimits
 * method. Since this is a performance critical method we decided against this
 * behavior.
 */
template<typename TwoDInterpPolicy, typename TwoDSamplePolicy, typename Distribution>
auto UnitAwareInterpolatedTabularTwoDDistributionImplBase<TwoDInterpPolicy,TwoDSamplePolicy,Distribution>::sampleSecondaryConditionalAndRecordTrials(
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
template<typename TwoDInterpPolicy, typename TwoDSamplePolicy, typename Distribution>
template<typename SampleFunctor>
inline auto UnitAwareInterpolatedTabularTwoDDistributionImplBase<TwoDInterpPolicy,TwoDSamplePolicy,Distribution>::sampleDetailedImpl(
                            const PrimaryIndepQuantity primary_indep_var_value,
                            SampleFunctor sample_functor,
                            SecondaryIndepQuantity& raw_sample,
                            unsigned& primary_bin_index ) const
  -> SecondaryIndepQuantity
{
  // Create the lower bound functor
  std::function<SecondaryIndepQuantity(const PrimaryIndepQuantity)>
    lower_bound_functor = std::bind<SecondaryIndepQuantity>(
                              &ThisType::getLowerBoundOfConditionalIndepVar,
                              std::cref( *this ),
                              std::placeholders::_1 );

  // Create the upper bound functor
  std::function<SecondaryIndepQuantity(const PrimaryIndepQuantity)>
    upper_bound_functor = std::bind<SecondaryIndepQuantity>(
                              &ThisType::getUpperBoundOfConditionalIndepVar,
                              std::cref( *this ),
                              std::placeholders::_1 );

  return this->sampleDetailedImpl( primary_indep_var_value,
                                   sample_functor,
                                   raw_sample,
                                   primary_bin_index,
                                   lower_bound_functor,
                                   upper_bound_functor );
}

// Sample from the distribution using the desired sampling functor
template<typename TwoDInterpPolicy, typename TwoDSamplePolicy, typename Distribution>
template<typename SampleFunctor>
inline auto UnitAwareInterpolatedTabularTwoDDistributionImplBase<TwoDInterpPolicy,TwoDSamplePolicy,Distribution>::sampleDetailedImpl(
            const PrimaryIndepQuantity primary_indep_var_value,
            SampleFunctor sample_functor,
            SecondaryIndepQuantity& raw_sample,
            unsigned& primary_bin_index,
            const std::function<SecondaryIndepQuantity(PrimaryIndepQuantity)>&
              min_secondary_indep_var_functor,
            const std::function<SecondaryIndepQuantity(PrimaryIndepQuantity)>&
              max_secondary_indep_var_functor ) const
  -> SecondaryIndepQuantity
{
  // Find the bin boundaries
  typename DistributionType::const_iterator lower_bin_boundary, upper_bin_boundary;

  this->findBinBoundaries( primary_indep_var_value,
                           lower_bin_boundary,
                           upper_bin_boundary );

  SecondaryIndepQuantity sample;
  if( lower_bin_boundary != upper_bin_boundary )
  {
    typename DistributionType::const_iterator sampled_bin_boundary;
    sample =
      TwoDSamplePolicy::template sampleDetailed<TwoDInterpPolicy,PrimaryIndepQuantity,SecondaryIndepQuantity>(
          sample_functor,
          min_secondary_indep_var_functor,
          max_secondary_indep_var_functor,
          primary_indep_var_value,
          lower_bin_boundary,
          upper_bin_boundary,
          sampled_bin_boundary,
          raw_sample );

    // Calculate the index of the primary bin boundary that will be used to
    // create the secondary conditional sample
    primary_bin_index = this->calculateBinIndex( sampled_bin_boundary );
  }
  else
  {
    if( this->arePrimaryLimitsExtended() )
    {
      raw_sample = sample_functor( *lower_bin_boundary->second );
      sample = raw_sample;

      // Calculate the index of the primary bin boundary that will be used to
      // create the secondary conditional sample
      primary_bin_index = this->calculateBinIndex( lower_bin_boundary );
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
  return sample;
}

// Sample from the distribution using the desired sampling functor
template<typename TwoDInterpPolicy, typename TwoDSamplePolicy, typename Distribution>
template<typename SampleFunctor>
inline auto UnitAwareInterpolatedTabularTwoDDistributionImplBase<TwoDInterpPolicy,TwoDSamplePolicy,Distribution>::sampleImpl(
                            const PrimaryIndepQuantity primary_indep_var_value,
                            SampleFunctor sample_functor ) const
  -> SecondaryIndepQuantity
{
  SecondaryIndepQuantity dummy_raw_sample;
  unsigned dummy_primary_bin_index;

  return this->sampleDetailedImpl( primary_indep_var_value,
                                   sample_functor,
                                   dummy_raw_sample,
                                   dummy_primary_bin_index );
}

// Sample from the distribution using the desired sampling functor
template<typename TwoDInterpPolicy, typename TwoDSamplePolicy, typename Distribution>
template<typename SampleFunctor>
inline auto UnitAwareInterpolatedTabularTwoDDistributionImplBase<TwoDInterpPolicy,TwoDSamplePolicy,Distribution>::sampleImpl(
            const PrimaryIndepQuantity primary_indep_var_value,
            SampleFunctor sample_functor,
            const std::function<SecondaryIndepQuantity(PrimaryIndepQuantity)>&
              min_secondary_indep_var_functor,
            const std::function<SecondaryIndepQuantity(PrimaryIndepQuantity)>&
              max_secondary_indep_var_functor ) const
  -> SecondaryIndepQuantity
{
  SecondaryIndepQuantity dummy_raw_sample;
  unsigned dummy_primary_bin_index;

  return this->sampleDetailedImpl( primary_indep_var_value,
                                   sample_functor,
                                   dummy_raw_sample,
                                   dummy_primary_bin_index,
                                   min_secondary_indep_var_functor,
                                   max_secondary_indep_var_functor );
}

// Return the upper bound of the conditional distribution
template<typename TwoDInterpPolicy, typename TwoDSamplePolicy, typename Distribution>
auto UnitAwareInterpolatedTabularTwoDDistributionImplBase<TwoDInterpPolicy,TwoDSamplePolicy,Distribution>::getUpperBoundOfConditionalIndepVar(
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
    return TwoDSamplePolicy::template calculateUpperBound<TwoDInterpPolicy,SecondaryIndepQuantity>(
                       primary_indep_var_value,
                       lower_bin_boundary,
                       upper_bin_boundary );
  }
}

// Return the lower bound of the conditional distribution
template<typename TwoDInterpPolicy, typename TwoDSamplePolicy, typename Distribution>
auto UnitAwareInterpolatedTabularTwoDDistributionImplBase<TwoDInterpPolicy,TwoDSamplePolicy,Distribution>::getLowerBoundOfConditionalIndepVar(
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
    return TwoDSamplePolicy::template calculateLowerBound<TwoDInterpPolicy,SecondaryIndepQuantity>(
                       primary_indep_var_value,
                       lower_bin_boundary,
                       upper_bin_boundary );
  }
}

// Test if the distribution is continuous in the primary dimension
template<typename TwoDInterpPolicy, typename TwoDSamplePolicy, typename Distribution>
bool UnitAwareInterpolatedTabularTwoDDistributionImplBase<TwoDInterpPolicy,TwoDSamplePolicy,Distribution>::isPrimaryDimensionContinuous() const
{
  return true;
}

} // end Utility namespace

#endif // end UTILITY_INTERPOLATED_TABULAR_TWO_D_DISTRIBUTION_IMPL_BASE_DEF_HPP

//---------------------------------------------------------------------------//
// end Utility_InterpolatedTabularTwoDDistributionImplBase_def.hpp
//---------------------------------------------------------------------------//
