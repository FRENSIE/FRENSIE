//---------------------------------------------------------------------------//
//!
//! \file   Utility_TwoDSamplingPolicy_def.hpp
//! \author Luke Kersting
//! \brief  Policy struct declarations for sampling on 2D grids
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_TWO_D_SAMPLING_POLICY_DEF_HPP
#define UTILITY_TWO_D_SAMPLING_POLICY_DEF_HPP

// Std Lib Includes
#include <functional>

// FRENSIE Includes
#include "Utility_SortAlgorithms.hpp"
#include "Utility_SearchAlgorithms.hpp"
#include "Utility_ContractException.hpp"
#include "Utility_RandomNumberGenerator.hpp"

namespace Utility{

// Sample between bin boundaries using the desired sampling functor
template<typename TwoDInterpPolicy,
         typename XIndepType,
         typename YIndepType,
         typename YZIterator,
         typename SampleFunctor,
         typename YBoundsFunctor>
YIndepType Stochastic::sample(
          const SampleFunctor& sample_functor,
          const YBoundsFunctor& min_y_indep_functor,
          const YBoundsFunctor& max_y_indep_functor,
          const XIndepType& x_indep_value,
          const YZIterator& lower_bin_boundary,
          const YZIterator& upper_bin_boundary )
{
  // Dummy variables
  YIndepType dummy_raw_sample;
  YZIterator dummy_sampled_bin_boundary;

  return Stochastic::sampleDetailed<TwoDInterpPolicy,XIndepType,YIndepType,YZIterator,SampleFunctor>(
            sample_functor,
            min_y_indep_functor,
            max_y_indep_functor,
            x_indep_value,
            lower_bin_boundary,
            upper_bin_boundary,
            dummy_sampled_bin_boundary,
            dummy_raw_sample );
}

//! Sample between bin boundaries using the desired sampling functor
template<typename TwoDInterpPolicy,
         typename XIndepType,
         typename YIndepType,
         typename YZIterator,
         typename SampleFunctor>
YIndepType Stochastic::sampleCos( const SampleFunctor& sample_functor,
                             const XIndepType& x_indep_value,
                             const YZIterator& lower_bin_boundary,
                             const YZIterator& upper_bin_boundary )
{
  // Dummy variables
  YIndepType dummy_raw_sample;
  YZIterator dummy_sampled_bin_boundary;

  return Stochastic::sampleCosDetailed<TwoDInterpPolicy,XIndepType,YIndepType,YZIterator,SampleFunctor>(
            sample_functor,
            x_indep_value,
            lower_bin_boundary,
            upper_bin_boundary,
            dummy_sampled_bin_boundary,
            dummy_raw_sample );
}

// Sample between bin boundaries using the desired subrange sampling functor
/* \details The SampleFunctor must be of the form that it takes a subrange
 * sampling function from a OneDDistribution and the max indep variable.
 */
template<typename TwoDInterpPolicy,
         typename XIndepType,
         typename YIndepType,
         typename YZIterator,
         typename SampleFunctor,
         typename YBoundsFunctor>
YIndepType Stochastic::sampleInSubrange(
          const SampleFunctor& subrange_sample_functor,
          const YBoundsFunctor& min_y_indep_functor,
          const YBoundsFunctor& max_y_indep_functor,
          const XIndepType& x_indep_value,
          const YZIterator& lower_bin_boundary,
          const YZIterator& upper_bin_boundary,
          const YIndepType& subrange_max_y_indep_value )
{
  YIndepType max_y_indep_value = max_y_indep_functor( x_indep_value );
  YIndepType min_y_indep_value = min_y_indep_functor( x_indep_value );

  // Make sure the y subrange limit is valid
  testPrecondition( subrange_max_y_indep_value >= min_y_indep_value )
  // Make sure the y limits is valid
  testPrecondition( max_y_indep_value >= min_y_indep_value );

  // Get the sampled bin boundary
  YZIterator sampled_bin_boundary =
    Stochastic::sampleBinBoundary<TwoDInterpPolicy,XIndepType,YZIterator>(
                              x_indep_value,
                              lower_bin_boundary,
                              upper_bin_boundary );

  // Calculate the intermediate grid limits
  typename QuantityTraits<YIndepType>::RawType
      intermediate_grid_length =
        TwoDInterpPolicy::SecondaryBasePolicy::calculateUnitBaseGridLength(
                                                  min_y_indep_value,
                                                  max_y_indep_value );

  // Calculate the unit base variable on the sampled bin boundary
  typename QuantityTraits<YIndepType>::RawType eta;

  {
    // Calculate the limit on the sampled bin boundary
    typename QuantityTraits<YIndepType>::RawType grid_length =
      TwoDInterpPolicy::SecondaryBasePolicy::calculateUnitBaseGridLength(
                      sampled_bin_boundary->second->getLowerBoundOfIndepVar(),
                      sampled_bin_boundary->second->getUpperBoundOfIndepVar() );

    YIndepType raw_sample;
    if( subrange_max_y_indep_value < max_y_indep_value )
    {
      typename QuantityTraits<YIndepType>::RawType subrange_eta_max =
        TwoDInterpPolicy::SecondaryBasePolicy::calculateUnitBaseIndepVar(
                                                    subrange_max_y_indep_value,
                                                    min_y_indep_value,
                                                    intermediate_grid_length );

      YIndepType max_y_indep_value_bin_bound =
        TwoDInterpPolicy::SecondaryBasePolicy::calculateIndepVar(
                          subrange_eta_max,
                          sampled_bin_boundary->second->getLowerBoundOfIndepVar(),
                          grid_length );

      // Sample in the bin's subrange
      raw_sample =
        subrange_sample_functor( *sampled_bin_boundary->second,
                                  max_y_indep_value_bin_bound );
    }
    else
    {
      raw_sample =
        subrange_sample_functor( *sampled_bin_boundary->second,
                                 sampled_bin_boundary->second->getUpperBoundOfIndepVar() );
    }

    // Scale the sample
    eta = TwoDInterpPolicy::SecondaryBasePolicy::calculateUnitBaseIndepVar(
                        raw_sample,
                        sampled_bin_boundary->second->getLowerBoundOfIndepVar(),
                        grid_length );
  }

  return TwoDInterpPolicy::SecondaryBasePolicy::calculateIndepVar(
                                                eta,
                                                min_y_indep_value,
                                                intermediate_grid_length );
}

// Sample between bin boundaries using the desired sampling functor
template<typename TwoDInterpPolicy,
         typename XIndepType,
         typename YIndepType,
         typename YZIterator,
         typename SampleFunctor,
         typename YBoundsFunctor>
YIndepType Stochastic::sampleDetailed(
            const SampleFunctor& sample_functor,
            const YBoundsFunctor& min_y_indep_functor,
            const YBoundsFunctor& max_y_indep_functor,
            const XIndepType& x_indep_value,
            const YZIterator& lower_bin_boundary,
            const YZIterator& upper_bin_boundary,
            YZIterator& sampled_bin_boundary,
            YIndepType& raw_sample )
{
  YIndepType min_y_indep_value = min_y_indep_functor(x_indep_value);
  YIndepType max_y_indep_value = max_y_indep_functor(x_indep_value);

  // Make sure the y limits is valid
  testPrecondition( max_y_indep_value >= min_y_indep_value );

  // Get the sampled bin boundary
  sampled_bin_boundary =
    Stochastic::sampleBinBoundary<TwoDInterpPolicy,XIndepType,YZIterator>(
                            x_indep_value,
                            lower_bin_boundary,
                            upper_bin_boundary );

  // Calculate the intermediate grid limits
  typename QuantityTraits<YIndepType>::RawType
    intermediate_grid_length =
    TwoDInterpPolicy::SecondaryBasePolicy::calculateUnitBaseGridLength(
                min_y_indep_value, max_y_indep_value );
  
  // Calculate the unit base variable on the bin boundary corresponding to the
  // raw sample
  typename QuantityTraits<YIndepType>::RawType eta;

  {
    // Calculate the limit on the sampled bin boundary
    typename QuantityTraits<YIndepType>::RawType grid_length =
      TwoDInterpPolicy::SecondaryBasePolicy::calculateUnitBaseGridLength(
                      sampled_bin_boundary->second->getLowerBoundOfIndepVar(),
                      sampled_bin_boundary->second->getUpperBoundOfIndepVar());

    // Create the raw sample
    raw_sample = sample_functor( *sampled_bin_boundary->second );

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
                eta, min_y_indep_value, intermediate_grid_length );
}

// Sample between bin boundaries using the desired sampling functor
template<typename TwoDInterpPolicy,
         typename XIndepType,
         typename YIndepType,
         typename YZIterator,
         typename SampleFunctor>
YIndepType Stochastic::sampleCosDetailed(
            const SampleFunctor& sample_functor,
            const XIndepType& x_indep_value,
            const YZIterator& lower_bin_boundary,
            const YZIterator& upper_bin_boundary,
            YZIterator& sampled_bin_boundary,
            YIndepType& raw_sample )
{
  // Get the sampled bin boundary
  sampled_bin_boundary =
    Stochastic::sampleBinBoundary<TwoDInterpPolicy,XIndepType,YZIterator>(
                            x_indep_value,
                            lower_bin_boundary,
                            upper_bin_boundary );

  // Create the raw sample
  raw_sample = sample_functor( *sampled_bin_boundary->second );

  return raw_sample;
}

// Sample the bin boundary that will be used for stochastic sampling
/*! \details This method will throw an exception if the primary independent
 * value is outside of the primary grid limits and the primary grid has not
 * been extended.
 */
template<typename TwoDInterpPolicy,
         typename XIndepType,
         typename YZIterator>
YZIterator Stochastic::sampleBinBoundary(
    const XIndepType& x_indep_value,
    const YZIterator& lower_bin_boundary,
    const YZIterator& upper_bin_boundary )
{
  // Calculate the interpolation fraction
  double interpolation_fraction;

  {
    const double processed_lower_bin_boundary = 
      TwoDInterpPolicy::processFirstIndepVar( lower_bin_boundary->first );

    interpolation_fraction =
      (TwoDInterpPolicy::processFirstIndepVar( x_indep_value ) -
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

// The name of the policy
inline const std::string Stochastic::name()
{
  return "Stochastic";
}

// Sample between bin boundaries using the desired sampling functor
template<typename TwoDInterpPolicy,
         typename XIndepType,
         typename YIndepType,
         typename YZIterator,
         typename SampleFunctor,
         typename YBoundsFunctor>
YIndepType Exact::sample(
          const SampleFunctor& sample_functor,
          const YBoundsFunctor& min_y_indep_functor,
          const YBoundsFunctor& max_y_indep_functor,
          const XIndepType& x_indep_value,
          const YZIterator& lower_bin_boundary,
          const YZIterator& upper_bin_boundary )
{
  // Dummy variables
  YIndepType dummy_raw_sample;
  YZIterator dummy_sampled_bin_boundary;

  return Exact::sampleDetailed<TwoDInterpPolicy,XIndepType,YIndepType,YZIterator,SampleFunctor>(
            sample_functor,
            min_y_indep_functor,
            max_y_indep_functor,
            x_indep_value,
            lower_bin_boundary,
            upper_bin_boundary,
            dummy_sampled_bin_boundary,
            dummy_raw_sample );
}

//! Sample between bin boundaries using the desired sampling functor
template<typename TwoDInterpPolicy,
         typename XIndepType,
         typename YIndepType,
         typename YZIterator,
         typename SampleFunctor>
YIndepType Exact::sampleCos( const SampleFunctor& sample_functor,
                             const XIndepType& x_indep_value,
                             const YZIterator& lower_bin_boundary,
                             const YZIterator& upper_bin_boundary )
{
  // Dummy variables
  YIndepType dummy_raw_sample;
  YZIterator dummy_sampled_bin_boundary;

  return Exact::sampleCosDetailed<TwoDInterpPolicy,XIndepType,YIndepType,YZIterator,SampleFunctor>(
            sample_functor,
            x_indep_value,
            lower_bin_boundary,
            upper_bin_boundary,
            dummy_sampled_bin_boundary,
            dummy_raw_sample );
}

// Sample between bin boundaries using the desired subrange sampling functor
/* \details The SampleFunctor must be of the form that it takes a subrange
 * sampling function from a OneDDistribution and the max indep variable.
 */
template<typename TwoDInterpPolicy,
         typename XIndepType,
         typename YIndepType,
         typename YZIterator,
         typename SampleFunctor,
         typename YBoundsFunctor>
YIndepType Exact::sampleInSubrange(
          const SampleFunctor& subrange_sample_functor,
          const YBoundsFunctor& min_y_indep_functor,
          const YBoundsFunctor& max_y_indep_functor,
          const XIndepType& x_indep_value,
          const YZIterator& lower_bin_boundary,
          const YZIterator& upper_bin_boundary,
          const YIndepType& subrange_max_y_indep_value )
{
  // Make sure the max y independent variable is above the lower bound of the
  // conditional independent variable
  testPrecondition( subrange_max_y_indep_value >
                    min_y_indep_functor( x_indep_value ) );

  // Get the max y indep value at the lower bin boundary
  YIndepType max_y_indep_var_0 =
    lower_bin_boundary->second->getUpperBoundOfIndepVar();

  // Only set the subrange if it is below the max y indep value
  if( subrange_max_y_indep_value < max_y_indep_var_0 )
    max_y_indep_var_0 = subrange_max_y_indep_value;

  // Get the max y indep value at the upper bin boundary
  YIndepType max_y_indep_var_1 =
    upper_bin_boundary->second->getUpperBoundOfIndepVar();

  // Only set the subrange if it is below the max y indep value
  if( subrange_max_y_indep_value < max_y_indep_var_1 )
    max_y_indep_var_1 = subrange_max_y_indep_value;

  // Check for a primary value at the primary grid upper limit
  if( x_indep_value == upper_bin_boundary->first )
  {
    return subrange_sample_functor( *upper_bin_boundary->second,
                                    max_y_indep_var_0 );
  }
  // Check for a primary value at the primary grid lower limit
  else if( x_indep_value == lower_bin_boundary->first )
  {
    return subrange_sample_functor( *lower_bin_boundary->second,
                                    max_y_indep_var_1 );
  }
  else
  {
    YIndepType lower_sample =
      subrange_sample_functor( *lower_bin_boundary->second,
                               max_y_indep_var_0 );
    YIndepType upper_sample =
      subrange_sample_functor( *upper_bin_boundary->second,
                               max_y_indep_var_1 );

    // Check if the samples are equal
    /*! \details Special cases can arise where the min/max of a secondary
     * distribution is zero. If the min/max is sampled both the upper and lower
     * samples will be zero.
     * In order to avoid log interpolation errors no interpolation is performed.
     */
    if( lower_sample == upper_sample )
      return lower_sample;
    else
    {
      return TwoDInterpPolicy::YXInterpPolicy::interpolate(
                            lower_bin_boundary->first,
                            upper_bin_boundary->first,
                            x_indep_value,
                            lower_sample,
                            upper_sample );
    }
  }
}

// Sample between bin boundaries using the desired sampling functor
template<typename TwoDInterpPolicy,
         typename XIndepType,
         typename YIndepType,
         typename YZIterator,
         typename SampleFunctor,
         typename YBoundsFunctor>
YIndepType Exact::sampleDetailed(
            const SampleFunctor& sample_functor,
            const YBoundsFunctor& min_y_indep_functor,
            const YBoundsFunctor& max_y_indep_functor,
            const XIndepType& x_indep_value,
            const YZIterator& lower_bin_boundary,
            const YZIterator& upper_bin_boundary,
            YZIterator& sampled_bin_boundary,
            YIndepType& raw_sample )
{
  // Check for a primary value at the primary grid upper limit
  if( x_indep_value == upper_bin_boundary->first )
  {
    raw_sample = sample_functor( *upper_bin_boundary->second );
    sampled_bin_boundary = upper_bin_boundary;
  }
  else if( x_indep_value == lower_bin_boundary->first )
  {
    raw_sample = sample_functor( *lower_bin_boundary->second );
    sampled_bin_boundary = lower_bin_boundary;
  }
  else
  {
    YIndepType lower_sample = sample_functor( *lower_bin_boundary->second );
    YIndepType upper_sample = sample_functor( *upper_bin_boundary->second );

    // Check if the samples are equal
    /*! \details Special cases can arise where the min/max of a secondary
     * distribution is zero. If the min/max is sampled both the upper and lower
     * samples will be zero.
     * In order to avoid log interpolation errors no interpolation is performed.
     */
    if( lower_sample == upper_sample )
    {
      raw_sample = lower_sample;
      sampled_bin_boundary = lower_bin_boundary;
    }
    else
    {
      raw_sample = TwoDInterpPolicy::YXInterpPolicy::interpolate(
                            lower_bin_boundary->first,
                            upper_bin_boundary->first,
                            x_indep_value,
                            lower_sample,
                            upper_sample );

      sampled_bin_boundary = lower_bin_boundary;
    }
  }
  return raw_sample;
}

// Sample between bin boundaries using the desired sampling functor
template<typename TwoDInterpPolicy,
         typename XIndepType,
         typename YIndepType,
         typename YZIterator,
         typename SampleFunctor>
YIndepType Exact::sampleCosDetailed(
            const SampleFunctor& sample_functor,
            const XIndepType& x_indep_value,
            const YZIterator& lower_bin_boundary,
            const YZIterator& upper_bin_boundary,
            YZIterator& sampled_bin_boundary,
            YIndepType& raw_sample )
{
  // Dummy variables
  double dummy_functor;

  return Exact::sampleDetailed<TwoDInterpPolicy,XIndepType,YIndepType,YZIterator,SampleFunctor>(
            sample_functor,
            dummy_functor,
            dummy_functor,
            x_indep_value,
            lower_bin_boundary,
            upper_bin_boundary,
            sampled_bin_boundary,
            raw_sample );
}

// The name of the policy
inline const std::string Exact::name()
{
  return "Exact";
}

// Sample between bin boundaries using the desired sampling functor
template<typename TwoDInterpPolicy,
         typename XIndepType,
         typename YIndepType,
         typename YZIterator,
         typename SampleFunctor,
         typename YBoundsFunctor>
YIndepType Correlated::sample(
          const SampleFunctor& sample_functor,
          const YBoundsFunctor& min_y_indep_functor,
          const YBoundsFunctor& max_y_indep_functor,
          const XIndepType& x_indep_value,
          const YZIterator& lower_bin_boundary,
          const YZIterator& upper_bin_boundary )
{
  // Dummy variables
  YIndepType dummy_raw_sample;
  YZIterator dummy_sampled_bin_boundary;

  return Correlated::sampleDetailed<TwoDInterpPolicy,XIndepType,YIndepType,YZIterator,SampleFunctor>(
            sample_functor,
            min_y_indep_functor,
            max_y_indep_functor,
            x_indep_value,
            lower_bin_boundary,
            upper_bin_boundary,
            dummy_sampled_bin_boundary,
            dummy_raw_sample );
}

//! Sample between bin boundaries using the desired sampling functor
template<typename TwoDInterpPolicy,
         typename XIndepType,
         typename YIndepType,
         typename YZIterator,
         typename SampleFunctor>
YIndepType Correlated::sampleCos( const SampleFunctor& sample_functor,
                                  const XIndepType& x_indep_value,
                                  const YZIterator& lower_bin_boundary,
                                  const YZIterator& upper_bin_boundary )
{
  // Dummy variables
  YIndepType dummy_raw_sample;
  YZIterator dummy_sampled_bin_boundary;

  return Correlated::sampleCosDetailed<TwoDInterpPolicy,XIndepType,YIndepType,YZIterator,SampleFunctor>(
            sample_functor,
            x_indep_value,
            lower_bin_boundary,
            upper_bin_boundary,
            dummy_sampled_bin_boundary,
            dummy_raw_sample );
}

// Sample between bin boundaries using the desired subrange sampling functor
/* \details The SampleFunctor must be of the form that it takes a subrange
 * sampling function from a OneDDistribution and the max indep variable.
 */
template<typename TwoDInterpPolicy,
         typename XIndepType,
         typename YIndepType,
         typename YZIterator,
         typename SampleFunctor,
         typename YBoundsFunctor>
YIndepType Correlated::sampleInSubrange(
          const SampleFunctor& subrange_sample_functor,
          const YBoundsFunctor& min_y_indep_functor,
          const YBoundsFunctor& max_y_indep_functor,
          const XIndepType& x_indep_value,
          const YZIterator& lower_bin_boundary,
          const YZIterator& upper_bin_boundary,
          const YIndepType& subrange_max_y_indep_value )
{
  // Get the min y indep var values for the x_indep_value
  YIndepType min_y_indep_var = min_y_indep_functor( x_indep_value );

  // Get the max y indep var values for the x_indep_value
  YIndepType max_y_indep_var;
  if( subrange_max_y_indep_value > max_y_indep_functor( x_indep_value ) )
    max_y_indep_var = max_y_indep_functor( x_indep_value );
  else
    max_y_indep_var = subrange_max_y_indep_value;

  // Check for a x value at a grid limit
  if( x_indep_value == upper_bin_boundary->first )
    return subrange_sample_functor( *upper_bin_boundary->second, max_y_indep_var );
  else if( x_indep_value == lower_bin_boundary->first )
    return subrange_sample_functor( *lower_bin_boundary->second, max_y_indep_var );
  else
  {
    typename QuantityTraits<YIndepType>::RawType
    intermediate_grid_length =
      TwoDInterpPolicy::SecondaryBasePolicy::calculateUnitBaseGridLength(
                  min_y_indep_var, max_y_indep_var );

    // Calculate the unit base variable on the intermediate grid corresponding to the
    // raw samples on the lower and upper boundaries
    typename QuantityTraits<YIndepType>::RawType eta, eta_0, eta_1;

    {
      // Get the max y indep value at the lower bin boundary
      YIndepType max_y_indep_var_0 =
        lower_bin_boundary->second->getUpperBoundOfIndepVar();

      // Only set the subrange if it is below the max y indep value
      if( subrange_max_y_indep_value < max_y_indep_var_0 )
        max_y_indep_var_0 = subrange_max_y_indep_value;

      // Calculate the unit base variable on the lower grid corresponding to the
      // lower raw sample
      typename QuantityTraits<YIndepType>::RawType grid_length_0 =
        TwoDInterpPolicy::SecondaryBasePolicy::calculateUnitBaseGridLength(
                    lower_bin_boundary->second->getLowerBoundOfIndepVar(),
                    max_y_indep_var_0 );

      eta_0 = TwoDInterpPolicy::ZYInterpPolicy::calculateUnitBaseIndepVar(
            subrange_sample_functor( *lower_bin_boundary->second, max_y_indep_var_0 ),
            lower_bin_boundary->second->getLowerBoundOfIndepVar(),
            grid_length_0 );


      // Get the max y indep value at the upper bin boundary
      YIndepType max_y_indep_var_1 =
        upper_bin_boundary->second->getUpperBoundOfIndepVar();

      // Only set the subrange if it is below the max y indep value
      if( subrange_max_y_indep_value < max_y_indep_var_1 )
        max_y_indep_var_1 = subrange_max_y_indep_value;

      // Calculate the unit base variable on the upper grid corresponding to the
      // upper raw sample
      typename QuantityTraits<YIndepType>::RawType grid_length_1 =
        TwoDInterpPolicy::SecondaryBasePolicy::calculateUnitBaseGridLength(
                    upper_bin_boundary->second->getLowerBoundOfIndepVar(),
                    max_y_indep_var_1 );

      eta_1 = TwoDInterpPolicy::ZYInterpPolicy::calculateUnitBaseIndepVar(
            subrange_sample_functor( *upper_bin_boundary->second, max_y_indep_var_1 ),
            upper_bin_boundary->second->getLowerBoundOfIndepVar(),
            grid_length_1 );

      // Interpolate between the lower and upper unit based variables
      eta = TwoDInterpPolicy::ZXInterpPolicy::interpolate(
                                                  lower_bin_boundary->first,
                                                  upper_bin_boundary->first,
                                                  x_indep_value,
                                                  eta_0,
                                                  eta_1 );
    }

    // Scale the sample so that it preserves the intermediate limits.
    return TwoDInterpPolicy::SecondaryBasePolicy::calculateIndepVar(
              eta, min_y_indep_var, intermediate_grid_length );
  }
}

// Sample between bin boundaries using the desired sampling functor
template<typename TwoDInterpPolicy,
         typename XIndepType,
         typename YIndepType,
         typename YZIterator,
         typename SampleFunctor,
         typename YBoundsFunctor>
YIndepType Correlated::sampleDetailed(
            const SampleFunctor& sample_functor,
            const YBoundsFunctor& min_y_indep_functor,
            const YBoundsFunctor& max_y_indep_functor,
            const XIndepType& x_indep_value,
            const YZIterator& lower_bin_boundary,
            const YZIterator& upper_bin_boundary,
            YZIterator& sampled_bin_boundary,
            YIndepType& raw_sample )
{
  // Check for a primary value at the primary grid upper limit
  if( x_indep_value == upper_bin_boundary->first )
  {
    raw_sample = sample_functor( *upper_bin_boundary->second );
    sampled_bin_boundary = upper_bin_boundary;
  }
  else if( x_indep_value == lower_bin_boundary->first )
  {
    raw_sample = sample_functor( *lower_bin_boundary->second );
    sampled_bin_boundary = lower_bin_boundary;
  }
  else
  {
    YIndepType min_y_indep_value = min_y_indep_functor(x_indep_value);
    YIndepType max_y_indep_value = max_y_indep_functor(x_indep_value);

    // Make sure the y limits is valid
    testPrecondition( max_y_indep_value >= min_y_indep_value );

    if( min_y_indep_value == max_y_indep_value )
    {
      // The min equals the max
      raw_sample = min_y_indep_value;
      sampled_bin_boundary = lower_bin_boundary;
    }
    else
    {
      typename QuantityTraits<YIndepType>::RawType
      intermediate_grid_length =
        TwoDInterpPolicy::SecondaryBasePolicy::calculateUnitBaseGridLength(
                            min_y_indep_value, max_y_indep_value );

      // Calculate the unit base variable on the intermediate grid corresponding to the
      // raw samples on the lower and upper boundaries
      typename QuantityTraits<YIndepType>::RawType eta, eta_0, eta_1;

      {
        // Calculate the unit base variable on the lower grid corresponding to the
        // lower raw sample
        typename QuantityTraits<YIndepType>::RawType grid_length_0 =
          TwoDInterpPolicy::SecondaryBasePolicy::calculateUnitBaseGridLength(
                      lower_bin_boundary->second->getLowerBoundOfIndepVar(),
                      lower_bin_boundary->second->getUpperBoundOfIndepVar());

        eta_0 = TwoDInterpPolicy::SecondaryBasePolicy::calculateUnitBaseIndepVar(
                        sample_functor( *lower_bin_boundary->second ),
                        lower_bin_boundary->second->getLowerBoundOfIndepVar(),
                        grid_length_0 );

        // Calculate the unit base variable on the upper grid corresponding to the
        // upper raw sample
        typename QuantityTraits<YIndepType>::RawType grid_length_1 =
          TwoDInterpPolicy::SecondaryBasePolicy::calculateUnitBaseGridLength(
                      upper_bin_boundary->second->getLowerBoundOfIndepVar(),
                      upper_bin_boundary->second->getUpperBoundOfIndepVar());

        eta_1 = TwoDInterpPolicy::SecondaryBasePolicy::calculateUnitBaseIndepVar(
                        sample_functor( *upper_bin_boundary->second ),
                        upper_bin_boundary->second->getLowerBoundOfIndepVar(),
                        grid_length_1 );

        // Interpolate between the lower and upper unit based variables
        eta = TwoDInterpPolicy::YXInterpPolicy::interpolate(
                                                  lower_bin_boundary->first,
                                                  upper_bin_boundary->first,
                                                  x_indep_value,
                                                  eta_0,
                                                  eta_1 );
      }
    // Scale the sample so that it preserves the intermediate limits.
    raw_sample = TwoDInterpPolicy::SecondaryBasePolicy::calculateIndepVar(
                  eta, min_y_indep_value, intermediate_grid_length );
    sampled_bin_boundary = lower_bin_boundary;
    }
  }
  return raw_sample;
}

// Sample between bin boundaries using the desired sampling functor
template<typename TwoDInterpPolicy,
         typename XIndepType,
         typename YIndepType,
         typename YZIterator,
         typename SampleFunctor>
YIndepType Correlated::sampleCosDetailed(
            const SampleFunctor& sample_functor,
            const XIndepType& x_indep_value,
            const YZIterator& lower_bin_boundary,
            const YZIterator& upper_bin_boundary,
            YZIterator& sampled_bin_boundary,
            YIndepType& raw_sample )
{
  return Exact::sampleCosDetailed<TwoDInterpPolicy,XIndepType,YIndepType,YZIterator,SampleFunctor>(
            sample_functor,
            x_indep_value,
            lower_bin_boundary,
            upper_bin_boundary,
            sampled_bin_boundary,
            raw_sample );
}

// The name of the policy
inline const std::string Correlated::name()
{
  return "Correlated";
}

} // end Utility namespace

#endif // end UTILITY_TWO_D_SAMPLING_POLICY_DEF_HPP

//---------------------------------------------------------------------------//
// end Utility_TwoDSamplingPolicy_def.hpp
//---------------------------------------------------------------------------//
