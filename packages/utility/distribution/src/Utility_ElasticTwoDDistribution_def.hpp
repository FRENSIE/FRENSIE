//---------------------------------------------------------------------------//
//!
//! \file   Utility_ElasticTwoDDistribution_def.hpp
//! \author Luke Kersting
//! \brief  The elastic two-dimensional dist. class def.
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_ELASTIC_TWO_D_DISTRIBUTION_DEF_HPP
#define UTILITY_ELASTIC_TWO_D_DISTRIBUTION_DEF_HPP

// FRENSIE Includes
#include "Utility_TabularDistribution.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_SortAlgorithms.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_ContractException.hpp"

namespace Utility{

// Constructor
template<typename TwoDInterpPolicy,
         typename TwoDSamplePolicy,
         typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit>
UnitAwareElasticTwoDDistribution<TwoDInterpPolicy,TwoDSamplePolicy,PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>::UnitAwareElasticTwoDDistribution(
      const DistributionType& distribution,
      const SecondaryIndepQuantity upper_bound_conditional_indep_var,
      const double fuzzy_boundary_tol,
      const double evaluate_relative_error_tol,
      const double evaluate_error_tol )
  : ParentType( distribution,
                fuzzy_boundary_tol,
                evaluate_relative_error_tol,
                evaluate_error_tol ),
    d_upper_bound_conditional_indep_var( upper_bound_conditional_indep_var ),
    d_max_upper_bound_conditional_indep_var( SIQT::one() ),
    d_lower_bound_conditional_indep_var( -1.0*SIQT::one() )
{
  testPrecondition( this->isSecondIndepVarCompatibleWithCosineProcessingType() );
}

// Constructor
template<typename TwoDInterpPolicy,
         typename TwoDSamplePolicy,
         typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit>
template<template<typename T, typename... Args> class ArrayA,
          template<typename T, typename... Args> class ArrayB>
UnitAwareElasticTwoDDistribution<TwoDInterpPolicy,TwoDSamplePolicy,PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>::UnitAwareElasticTwoDDistribution(
      const ArrayA<PrimaryIndepQuantity>& primary_indep_grid,
      const ArrayB<std::shared_ptr<const UnitAwareTabularOneDDistribution<SecondaryIndependentUnit,DependentUnit> > >& secondary_distributions,
      const SecondaryIndepQuantity upper_bound_conditional_indep_var,
      const double fuzzy_boundary_tol,
      const double evaluate_relative_error_tol,
      const double evaluate_error_tol )
  : ParentType( primary_indep_grid,
                secondary_distributions,
                fuzzy_boundary_tol,
                evaluate_relative_error_tol,
                evaluate_error_tol ),
    d_upper_bound_conditional_indep_var( upper_bound_conditional_indep_var ),
    d_max_upper_bound_conditional_indep_var( SIQT::one() ),
    d_lower_bound_conditional_indep_var( -1.0*SIQT::one() )
{
  testPrecondition( this->isSecondIndepVarCompatibleWithCosineProcessingType() );
}

////---------------------------------------------------------------------------//
//// EVALUATING METHODS
////---------------------------------------------------------------------------//

// Evaluate the distribution
template<typename TwoDInterpPolicy,
         typename TwoDSamplePolicy,
         typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit>
auto UnitAwareElasticTwoDDistribution<TwoDInterpPolicy,TwoDSamplePolicy,PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>::evaluate(
                const PrimaryIndepQuantity primary_indep_var_value,
                const SecondaryIndepQuantity secondary_indep_var_value,
                const bool use_direct_eval_method ) const
  -> DepQuantity
{
  return this->evaluateImpl<TwoDInterpPolicy,DepQuantity>(
                                      primary_indep_var_value,
                                      secondary_indep_var_value,
                                      &BaseOneDDistributionType::evaluate,
                                      use_direct_eval_method );
}

// Evaluate the secondary conditional PDF
template<typename TwoDInterpPolicy,
         typename TwoDSamplePolicy,
         typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit>
auto UnitAwareElasticTwoDDistribution<TwoDInterpPolicy,TwoDSamplePolicy,PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>::evaluateSecondaryConditionalPDF(
                const PrimaryIndepQuantity primary_indep_var_value,
                const SecondaryIndepQuantity secondary_indep_var_value,
                const bool use_direct_eval_method ) const
  -> InverseSecondaryIndepQuantity
{
  return this->evaluateImpl<TwoDInterpPolicy,InverseSecondaryIndepQuantity>(
                                      primary_indep_var_value,
                                      secondary_indep_var_value,
                                      &BaseOneDDistributionType::evaluatePDF,
                                      use_direct_eval_method );
}

// Evaluate the secondary conditional PDF
template<typename TwoDInterpPolicy,
         typename TwoDSamplePolicy,
         typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit>
auto UnitAwareElasticTwoDDistribution<TwoDInterpPolicy,TwoDSamplePolicy,PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>::evaluateSecondaryConditionalPDF(
            const PrimaryIndepQuantity primary_indep_var_value,
            const SecondaryIndepQuantity secondary_indep_var_value,
            const std::function<SecondaryIndepQuantity(PrimaryIndepQuantity)>&
              min_secondary_indep_var_functor,
            const std::function<SecondaryIndepQuantity(PrimaryIndepQuantity)>&
              max_secondary_indep_var_functor,
            const bool use_direct_eval_method ) const
  -> InverseSecondaryIndepQuantity
{
  return this->evaluateImpl<TwoDInterpPolicy,InverseSecondaryIndepQuantity>(
                                      primary_indep_var_value,
                                      secondary_indep_var_value,
                                      min_secondary_indep_var_functor,
                                      max_secondary_indep_var_functor,
                                      &BaseOneDDistributionType::evaluatePDF,
                                      use_direct_eval_method );
}

// Evaluate the secondary conditional CDF
template<typename TwoDInterpPolicy,
         typename TwoDSamplePolicy,
         typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit>
double UnitAwareElasticTwoDDistribution<TwoDInterpPolicy,TwoDSamplePolicy,PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>::evaluateSecondaryConditionalCDF(
                const PrimaryIndepQuantity primary_indep_var_value,
                const SecondaryIndepQuantity secondary_indep_var_value,
                const bool use_direct_eval_method ) const
{
  if ( TwoDSamplePolicy::name() == "Exact" )
  {
    return this->evaluateImpl<TwoDInterpPolicy,double>(
                                      primary_indep_var_value,
                                      secondary_indep_var_value,
                                      &BaseOneDDistributionType::evaluateCDF,
                                      use_direct_eval_method );
  }
  else
  {
    return this->evaluateImpl<CDFInterpPolicy,double>(
                                      primary_indep_var_value,
                                      secondary_indep_var_value,
                                      &BaseOneDDistributionType::evaluateCDF,
                                      use_direct_eval_method );
  }
}

// Evaluate the distribution using the desired evaluation method
template<typename TwoDInterpPolicy,
         typename TwoDSamplePolicy,
         typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit>
template<typename LocalTwoDInterpPolicy,
         typename ReturnType,
         typename EvaluationMethod>
inline ReturnType UnitAwareElasticTwoDDistribution<TwoDInterpPolicy,TwoDSamplePolicy,PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>::evaluateImpl(
                        const PrimaryIndepQuantity incoming_energy,
                        const SecondaryIndepQuantity angle_cosine,
                        EvaluationMethod evaluate,
                        const bool use_direct_eval_method ) const
{
  // Make sure the angle cosine is valid
  testPrecondition( angle_cosine >= d_lower_bound_conditional_indep_var );
  testPrecondition( angle_cosine <= d_max_upper_bound_conditional_indep_var );

  // Find the bin boundaries
  typename DistributionType::const_iterator lower_bin_boundary, upper_bin_boundary;

  this->findBinBoundaries( incoming_energy,
                           lower_bin_boundary,
                           upper_bin_boundary );

  if( lower_bin_boundary != upper_bin_boundary )
  {
    // Create the lower bound functor
    std::function<SecondaryIndepQuantity(const PrimaryIndepQuantity)>
      min_secondary_indep_var_functor =
        [this](const PrimaryIndepQuantity x){
          return d_lower_bound_conditional_indep_var;
        };

    // Create the upper bound functor
    std::function<SecondaryIndepQuantity(const PrimaryIndepQuantity)>
      max_secondary_indep_var_functor =
        [this](const PrimaryIndepQuantity x){
          return d_upper_bound_conditional_indep_var;
        };

    if ( use_direct_eval_method )
    {
      return Stochastic::evaluateCosSampleBased<TwoDInterpPolicy,BaseOneDDistributionType,PrimaryIndepQuantity,SecondaryIndepQuantity,ReturnType>(
          incoming_energy,
          angle_cosine,
          min_secondary_indep_var_functor,
          max_secondary_indep_var_functor,
          evaluate,
          lower_bin_boundary,
          upper_bin_boundary,
          this->getRelativeErrorTolerance(),
          this->getErrorTolerance(),
          500 );
    }
    else
    {
      return TwoDSamplePolicy::template evaluateCosSampleBased<TwoDInterpPolicy,BaseOneDDistributionType,PrimaryIndepQuantity,SecondaryIndepQuantity,ReturnType>(
          incoming_energy,
          angle_cosine,
          min_secondary_indep_var_functor,
          max_secondary_indep_var_functor,
          evaluate,
          lower_bin_boundary,
          upper_bin_boundary,
          this->getRelativeErrorTolerance(),
          this->getErrorTolerance(),
          500 );
    }
  }
  // Check for a primary value outside of the primary grid limits
  else
  {
    if( this->arePrimaryLimitsExtended() )
      return ((*lower_bin_boundary->second).*evaluate)(angle_cosine);
    else
      return QuantityTraits<ReturnType>::zero();
  }
  // else if( lower_bin_boundary->first == primary_indep_var_value )
  // {
  //   return ((*lower_bin_boundary->second).*evaluate)(angle_cosine);
  // }
  // else if( upper_bin_boundary->first == primary_indep_var_value )
  // {
  //   return ((*upper_bin_boundary->second).*evaluate)(angle_cosine);
  // }
  // else
  // {
  //   // Get the evaluation at the lower and upper bin boundaries
  //   ReturnType min_eval_0 = ((*lower_bin_boundary->second).*evaluate)(angle_cosine);
  //   ReturnType min_eval_1 = ((*upper_bin_boundary->second).*evaluate)(angle_cosine);

  //   if ( min_eval_0 == min_eval_1 )
  //     return min_eval_0;
  //   else
  //   {
  //     // Return the interpolated evaluation
  //     return TwoDInterpPolicy::ZXInterpPolicy::interpolate(
  //             lower_bin_boundary->first,
  //             upper_bin_boundary->first,
  //             primary_indep_var_value,
  //             min_eval_0,
  //             min_eval_1 );
  //   }
  // }
}

// Evaluate the distribution using the desired evaluation method
template<typename TwoDInterpPolicy,
         typename TwoDSamplePolicy,
         typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit>
template<typename LocalTwoDInterpPolicy,
         typename ReturnType,
         typename EvaluationMethod>
inline ReturnType UnitAwareElasticTwoDDistribution<TwoDInterpPolicy,TwoDSamplePolicy,PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>::evaluateImpl(
            const PrimaryIndepQuantity incoming_energy,
            const SecondaryIndepQuantity angle_cosine,
            const std::function<SecondaryIndepQuantity(PrimaryIndepQuantity)>&
              min_secondary_indep_var_functor,
            const std::function<SecondaryIndepQuantity(PrimaryIndepQuantity)>&
              max_secondary_indep_var_functor,
            EvaluationMethod evaluate,
            const bool use_direct_eval_method,
            const ReturnType below_lower_bound_return,
            const ReturnType above_upper_bound_return,
            unsigned max_number_of_iterations ) const
{
  // Make sure the angle cosine is valid
  testPrecondition( angle_cosine >= d_lower_bound_conditional_indep_var );
  testPrecondition( angle_cosine <= d_max_upper_bound_conditional_indep_var );

  // Find the bin boundaries
  typename DistributionType::const_iterator lower_bin_boundary, upper_bin_boundary;

  this->findBinBoundaries( incoming_energy,
                           lower_bin_boundary,
                           upper_bin_boundary );

  if( lower_bin_boundary != upper_bin_boundary )
  {
    if ( use_direct_eval_method )
    {
      return Stochastic::evaluateCosSampleBased<TwoDInterpPolicy,BaseOneDDistributionType,PrimaryIndepQuantity,SecondaryIndepQuantity,ReturnType>(
          incoming_energy,
          angle_cosine,
          min_secondary_indep_var_functor,
          max_secondary_indep_var_functor,
          evaluate,
          lower_bin_boundary,
          upper_bin_boundary,
          this->getRelativeErrorTolerance(),
          this->getErrorTolerance(),
          500 );
    }
    else
    {
      return TwoDSamplePolicy::template evaluateCosSampleBased<TwoDInterpPolicy,BaseOneDDistributionType,PrimaryIndepQuantity,SecondaryIndepQuantity,ReturnType>(
          incoming_energy,
          angle_cosine,
          min_secondary_indep_var_functor,
          max_secondary_indep_var_functor,
          evaluate,
          lower_bin_boundary,
          upper_bin_boundary,
          this->getRelativeErrorTolerance(),
          this->getErrorTolerance(),
          500 );
    }
  }
  // Check for a primary value outside of the primary grid limits
  else
  {
    if( this->arePrimaryLimitsExtended() )
      return ((*lower_bin_boundary->second).*evaluate)(angle_cosine);
    else
      return QuantityTraits<ReturnType>::zero();
  }
}

////---------------------------------------------------------------------------//
//// SAMPLING METHODS
////---------------------------------------------------------------------------//

// Return a random sample from the secondary conditional PDF
template<typename TwoDInterpPolicy,
         typename TwoDSamplePolicy,
         typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit>
auto UnitAwareElasticTwoDDistribution<TwoDInterpPolicy,TwoDSamplePolicy,PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>::sampleSecondaryConditional(
                     const PrimaryIndepQuantity primary_indep_var_value ) const
  -> SecondaryIndepQuantity
{
  // Use this random number to sample
  const double random_number =
    Utility::RandomNumberGenerator::getRandomNumber<double>();

  // Create the sampling functor
  std::function<SecondaryIndepQuantity(const BaseOneDDistributionType&)>
    sampling_functor = std::bind<SecondaryIndepQuantity>(
                             &BaseOneDDistributionType::sampleWithRandomNumber,
                             std::placeholders::_1,
                             random_number );

  return this->sampleImpl( primary_indep_var_value, sampling_functor );
}


// Return a random sample from the secondary conditional PDF
template<typename TwoDInterpPolicy,
         typename TwoDSamplePolicy,
         typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit>
auto UnitAwareElasticTwoDDistribution<TwoDInterpPolicy,TwoDSamplePolicy,PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>::sampleSecondaryConditional(
    const PrimaryIndepQuantity primary_indep_var_value,
    const std::function<SecondaryIndepQuantity(PrimaryIndepQuantity)>& min_secondary_indep_var_functor,
    const std::function<SecondaryIndepQuantity(PrimaryIndepQuantity)>& max_secondary_indep_var_functor ) const
  -> SecondaryIndepQuantity
{
  return this->sampleSecondaryConditional( primary_indep_var_value );
}

// Return a random sample and record the number of trials
template<typename TwoDInterpPolicy,
         typename TwoDSamplePolicy,
         typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit>
auto UnitAwareElasticTwoDDistribution<TwoDInterpPolicy,TwoDSamplePolicy,PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>::sampleSecondaryConditionalAndRecordTrials(
                            const PrimaryIndepQuantity primary_indep_var_value,
                            unsigned& trials ) const
  -> SecondaryIndepQuantity
{
  ++trials;
  return this->sampleSecondaryConditional( primary_indep_var_value );
}

// Return a random sample from the secondary conditional PDF and the index
/*! \details The primary_bin_index stores the index of the bin boundary that
 * was used to generate the sample.
 */
template<typename TwoDInterpPolicy,
         typename TwoDSamplePolicy,
         typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit>
auto UnitAwareElasticTwoDDistribution<TwoDInterpPolicy,TwoDSamplePolicy,PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>::sampleSecondaryConditionalAndRecordBinIndices(
                            const PrimaryIndepQuantity primary_indep_var_value,
                            unsigned& primary_bin_index,
                            unsigned& secondary_bin_index ) const
  -> SecondaryIndepQuantity
{
  // Dummy variable
  SecondaryIndepQuantity dummy_raw_sample;
  
  // Create the sampling functor
  std::function<SecondaryIndepQuantity(const BaseOneDDistributionType&)>
    sampling_functor = std::bind<SecondaryIndepQuantity>(
                            &BaseOneDDistributionType::sampleAndRecordBinIndex,
                            std::placeholders::_1,
                            std::ref( secondary_bin_index ) );

  return this->sampleDetailedImpl( primary_indep_var_value,
                                   sampling_functor,
                                   dummy_raw_sample,
                                   primary_bin_index );
}

// Return a random sample from the secondary conditional PDF and the index
/*! \details The primary_bin_index stores the index of the bin boundary that
 * was used to generate the raw_sample. The raw_sample is the original sample
 * that was made before the scaling operation was done.
 */
template<typename TwoDInterpPolicy,
         typename TwoDSamplePolicy,
         typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit>
auto UnitAwareElasticTwoDDistribution<TwoDInterpPolicy,TwoDSamplePolicy,PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>::sampleSecondaryConditionalAndRecordBinIndices(
                            const PrimaryIndepQuantity primary_indep_var_value,
                            SecondaryIndepQuantity& raw_sample,
                            unsigned& primary_bin_index,
                            unsigned& secondary_bin_index ) const
  -> SecondaryIndepQuantity
{
  // Create the sampling functor
  std::function<SecondaryIndepQuantity(const BaseOneDDistributionType&)>
    sampling_functor = std::bind<SecondaryIndepQuantity>(
                            &BaseOneDDistributionType::sampleAndRecordBinIndex,
                            std::placeholders::_1,
                            std::ref( secondary_bin_index ) );

  return this->sampleDetailedImpl( primary_indep_var_value,
                                   sampling_functor,
                                   raw_sample,
                                   primary_bin_index );
}

// Return a random sample from the secondary conditional PDF at the CDF val
template<typename TwoDInterpPolicy,
         typename TwoDSamplePolicy,
         typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit>
auto UnitAwareElasticTwoDDistribution<TwoDInterpPolicy,TwoDSamplePolicy,PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>::sampleSecondaryConditionalWithRandomNumber(
                            const PrimaryIndepQuantity primary_indep_var_value,
                            const double random_number ) const
  -> SecondaryIndepQuantity
{
  // Make sure the random number is valid
  testPrecondition( random_number >= 0.0 );
  testPrecondition( random_number <= 1.0 );
  
  // Create the sampling functor
  std::function<SecondaryIndepQuantity(const BaseOneDDistributionType&)>
    sampling_functor = std::bind<SecondaryIndepQuantity>(
                             &BaseOneDDistributionType::sampleWithRandomNumber,
                             std::placeholders::_1,
                             random_number );

  return this->sampleImpl( primary_indep_var_value, sampling_functor );
}

// Return a random sample from the secondary conditional PDF in the subrange
template<typename TwoDInterpPolicy,
         typename TwoDSamplePolicy,
         typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit>
auto UnitAwareElasticTwoDDistribution<TwoDInterpPolicy,TwoDSamplePolicy,PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>::sampleSecondaryConditionalInSubrange(
             const PrimaryIndepQuantity primary_indep_var_value,
             const SecondaryIndepQuantity max_secondary_indep_var_value ) const
  -> SecondaryIndepQuantity
{
  // Use this random number to do create the sample functor
  const double random_number =
    Utility::RandomNumberGenerator::getRandomNumber<double>();

  return this->sampleSecondaryConditionalWithRandomNumberInSubrange(
                                               primary_indep_var_value,
                                               random_number,
                                               max_secondary_indep_var_value );
}
// Return a random sample from the secondary conditional PDF in the subrange
template<typename TwoDInterpPolicy,
         typename TwoDSamplePolicy,
         typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit>
auto UnitAwareElasticTwoDDistribution<TwoDInterpPolicy,TwoDSamplePolicy,PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>::sampleSecondaryConditionalWithRandomNumberInSubrange(
             const PrimaryIndepQuantity primary_indep_var_value,
             const double random_number,
             const SecondaryIndepQuantity max_secondary_indep_var_value ) const
  -> SecondaryIndepQuantity
{
  // Make sure the random number is valid
  testPrecondition( random_number >= 0.0 );
  testPrecondition( random_number <= 1.0 );
  // Make sure the secondary limit is valid
  testPrecondition( max_secondary_indep_var_value >
                    d_lower_bound_conditional_indep_var );

  std::function<SecondaryIndepQuantity(const BaseOneDDistributionType&)>
      sampling_functor;

  // Check if the max_secondary_indep_var_value is greater than the max indep value at the energy
  if ( max_secondary_indep_var_value >
       d_upper_bound_conditional_indep_var )
  {
    // Create the sampling functor
    sampling_functor = std::bind<SecondaryIndepQuantity>(
                             &BaseOneDDistributionType::sampleWithRandomNumberInSubrange,
                             std::placeholders::_1,
                             random_number,
                             d_upper_bound_conditional_indep_var );
  }
  else
  {
    // Create the sampling functor
    sampling_functor = std::bind<SecondaryIndepQuantity>(
                             &BaseOneDDistributionType::sampleWithRandomNumberInSubrange,
                             std::placeholders::_1,
                             random_number,
                             max_secondary_indep_var_value );
  }

  return this->sampleImpl( primary_indep_var_value, sampling_functor );
}

// Sample from the distribution using the desired sampling functor
template<typename TwoDInterpPolicy,
         typename TwoDSamplePolicy,
         typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit>
template<typename SampleFunctor>
inline auto UnitAwareElasticTwoDDistribution<TwoDInterpPolicy,TwoDSamplePolicy,PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>::sampleImpl(
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
template<typename TwoDInterpPolicy,
         typename TwoDSamplePolicy,
         typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit>
template<typename SampleFunctor>
inline auto UnitAwareElasticTwoDDistribution<TwoDInterpPolicy,TwoDSamplePolicy,PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>::sampleDetailedImpl(
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

  SecondaryIndepQuantity sample;
  if( lower_bin_boundary != upper_bin_boundary )
  {
    typename DistributionType::const_iterator sampled_bin_boundary;
    sample =
      TwoDSamplePolicy::template sampleCosDetailed<TwoDInterpPolicy,PrimaryIndepQuantity,SecondaryIndepQuantity>(
          sample_functor,
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

////---------------------------------------------------------------------------//
//// MISC. FUNCTIONS
////---------------------------------------------------------------------------//

// Return the lower bound of the conditional distribution
template<typename TwoDInterpPolicy,
         typename TwoDSamplePolicy,
         typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit>
auto UnitAwareElasticTwoDDistribution<TwoDInterpPolicy,TwoDSamplePolicy,PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>::getLowerBoundOfConditionalIndepVar(
                     const PrimaryIndepQuantity primary_indep_var_value ) const
  -> SecondaryIndepQuantity
{
  // Check for a primary value outside of the primary grid limits
  if( primary_indep_var_value < this->getLowerBoundOfPrimaryIndepVar() ||
      primary_indep_var_value > this->getUpperBoundOfPrimaryIndepVar() )
  {
    if( this->arePrimaryLimitsExtended() )
      return d_lower_bound_conditional_indep_var;
    else
      return SIQT::zero();
  }
  else
    return d_lower_bound_conditional_indep_var;
}

// Return the upper bound of the conditional distribution
template<typename TwoDInterpPolicy,
         typename TwoDSamplePolicy,
         typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit>
auto UnitAwareElasticTwoDDistribution<TwoDInterpPolicy,TwoDSamplePolicy,PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>::getUpperBoundOfConditionalIndepVar(
                     const PrimaryIndepQuantity primary_indep_var_value ) const
  -> SecondaryIndepQuantity
{
  // Check for a primary value outside of the primary grid limits
  if( primary_indep_var_value < this->getLowerBoundOfPrimaryIndepVar() ||
      primary_indep_var_value > this->getUpperBoundOfPrimaryIndepVar() )
  {
    if( this->arePrimaryLimitsExtended() )
      return d_upper_bound_conditional_indep_var;
    else
      return SIQT::zero();
  }
  else
    return d_upper_bound_conditional_indep_var;
}

// Test if the second independent variable is compatible with Cosine processing
template<typename TwoDInterpPolicy,
         typename TwoDSamplePolicy,
         typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit>
bool UnitAwareElasticTwoDDistribution<TwoDInterpPolicy,TwoDSamplePolicy,PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>::isSecondIndepVarCompatibleWithCosineProcessingType() const
{
  if( boost::is_same<typename TwoDInterpPolicy::SecondIndepVarProcessingTag,LogCosIndepVarProcessingTag>::value ||
      boost::is_same<typename TwoDInterpPolicy::SecondIndepVarProcessingTag,LinIndepVarProcessingTag>::value )
    return true;
  else
    return false;
}

} // end Utility namespace

#endif // UTILITY_ELASTIC_TWO_D_DISTRIBUTION_DEF_HPP

//---------------------------------------------------------------------------//
// end Utility_ElasticTwoDDistribution_def.hpp
//---------------------------------------------------------------------------//
