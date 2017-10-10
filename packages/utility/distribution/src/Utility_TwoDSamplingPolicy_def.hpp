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


// Return the lower bound of the conditional distribution
template<typename TwoDInterpPolicy,
         typename XIndepType,
         typename YIndepType,
         typename YZIterator>
inline YIndepType
SamplingPolicyHelpers<TwoDInterpPolicy,XIndepType,YIndepType,YZIterator>::getLowerBoundOfConditionalIndepVar(
                    const XIndepType& x_indep_value,
                    const YZIterator& lower_bin_boundary,
                    const YZIterator& upper_bin_boundary )
{
  return TwoDInterpPolicy::calculateIntermediateGridLimit(
                       lower_bin_boundary->first,
                       upper_bin_boundary->first,
                       x_indep_value,
                       lower_bin_boundary->second->getLowerBoundOfIndepVar(),
                       upper_bin_boundary->second->getLowerBoundOfIndepVar() );
}

// Return the upper bound of the conditional distribution
template<typename TwoDInterpPolicy,
         typename XIndepType,
         typename YIndepType,
         typename YZIterator>
inline YIndepType
SamplingPolicyHelpers<TwoDInterpPolicy,XIndepType,YIndepType,YZIterator>::getUpperBoundOfConditionalIndepVar(
                    const XIndepType& x_indep_value,
                    const YZIterator& lower_bin_boundary,
                    const YZIterator& upper_bin_boundary )
{
  return TwoDInterpPolicy::calculateIntermediateGridLimit(
                       lower_bin_boundary->first,
                       upper_bin_boundary->first,
                       x_indep_value,
                       lower_bin_boundary->second->getUpperBoundOfIndepVar(),
                       upper_bin_boundary->second->getUpperBoundOfIndepVar() );
}

// Sample between bin boundaries using the desired sampling functor
template<typename TwoDInterpPolicy,
         typename XIndepType,
         typename YIndepType,
         typename YZIterator,
         typename SampleFunctor>
YIndepType Stochastic::sample(
            SampleFunctor sample_functor,
            const YZIterator& lower_bin_boundary,
            const YZIterator& upper_bin_boundary,
            const XIndepType& x_indep_value )
{
  // Dummy variables
  YIndepType dummy_raw_sample;
  YZIterator dummy_sampled_bin_boundary;

  return Stochastic::sampleDetailed<TwoDInterpPolicy,XIndepType,YIndepType,YZIterator,SampleFunctor>(
            sample_functor,
            dummy_raw_sample,
            dummy_sampled_bin_boundary,
            lower_bin_boundary,
            upper_bin_boundary,
            x_indep_value );
}

// Sample between bin boundaries using the desired sampling functor
template<typename TwoDInterpPolicy,
         typename XIndepType,
         typename YIndepType,
         typename YZIterator,
         typename SampleFunctor>
YIndepType Stochastic::sample(
            SampleFunctor sample_functor,
            const YZIterator& lower_bin_boundary,
            const YZIterator& upper_bin_boundary,
            const XIndepType& x_indep_value,
            const YIndepType& min_y_indep_value,
            const YIndepType& max_y_indep_value )
{
  // Dummy variables
  YIndepType dummy_raw_sample;
  YZIterator dummy_sampled_bin_boundary;

  return Stochastic::sampleDetailed<TwoDInterpPolicy,XIndepType,YIndepType,YZIterator,SampleFunctor>(
            sample_functor,
            dummy_raw_sample,
            dummy_sampled_bin_boundary,
            lower_bin_boundary,
            upper_bin_boundary,
            x_indep_value,
            min_y_indep_value,
            max_y_indep_value );
}

// Sample between bin boundaries using the desired sampling functor
template<typename TwoDInterpPolicy,
         typename XIndepType,
         typename YIndepType,
         typename YZIterator,
         typename SampleFunctor>
YIndepType Stochastic::sampleDetailed(
            SampleFunctor sample_functor,
            YIndepType& raw_sample,
            YZIterator& sampled_bin_boundary,
            const YZIterator& lower_bin_boundary,
            const YZIterator& upper_bin_boundary,
            const XIndepType& x_indep_value )
{
  // Get lower y indep value at the x indep value
  YIndepType min_y_indep_value =
   SamplingPolicyHelpers<TwoDInterpPolicy,XIndepType,YIndepType,YZIterator>::getLowerBoundOfConditionalIndepVar(
                      x_indep_value,
                      lower_bin_boundary,
                      upper_bin_boundary );

  // Get upper y indep value at the x indep value
  YIndepType max_y_indep_value =
   SamplingPolicyHelpers<TwoDInterpPolicy,XIndepType,YIndepType,YZIterator>::getUpperBoundOfConditionalIndepVar(
                      x_indep_value,
                      lower_bin_boundary,
                      upper_bin_boundary );

  return Stochastic::sampleDetailed<TwoDInterpPolicy,XIndepType,YIndepType,YZIterator,SampleFunctor>(
            sample_functor,
            raw_sample,
            sampled_bin_boundary,
            lower_bin_boundary,
            upper_bin_boundary,
            x_indep_value,
            min_y_indep_value,
            max_y_indep_value );
}

  //! Sample between bin boundaries using the desired sampling functor
  template<typename TwoDInterpPolicy,
           typename XIndepType,
           typename YIndepType,
           typename YZIterator,
           typename SampleFunctor>
  YIndepType Stochastic::sampleDetailed(
            SampleFunctor sample_functor,
            YIndepType& raw_sample,
            YZIterator& sampled_bin_boundary,
            const YZIterator& lower_bin_boundary,
            const YZIterator& upper_bin_boundary,
            const XIndepType& x_indep_value,
            const YIndepType& min_y_indep_value,
            const YIndepType& max_y_indep_value )
{
  // Make sure the y limits is valid
  testPrecondition( max_y_indep_value >= min_y_indep_value );

  // Get the sampled bin boundary
  sampled_bin_boundary =
    Stochastic::sampleBinBoundary<TwoDInterpPolicy,XIndepType,YZIterator>(
                            x_indep_value,
                            lower_bin_boundary,
                            upper_bin_boundary );

  // Create the raw sample
  raw_sample = sample_functor( *sampled_bin_boundary->second );

  // Calculate the intermediate grid limits
  typename QuantityTraits<YIndepType>::RawType
    intermediate_grid_length =
    TwoDInterpPolicy::SecondaryBasePolicy::calculateUnitBaseGridLength(
                min_y_indep_value, max_y_indep_value );
  
  // Calculate the unit base variable on the bin boundary corresponding to the
  // raw sample
  typename QuantityTraits<YIndepType>::RawType eta;

  {
    typename QuantityTraits<YIndepType>::RawType grid_length =
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
                eta, min_y_indep_value, intermediate_grid_length );
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
         typename SampleFunctor>
YIndepType Exact::sample(
            SampleFunctor sample_functor,
            const YZIterator& lower_bin_boundary,
            const YZIterator& upper_bin_boundary,
            const XIndepType& x_indep_value )
{
  // Dummy variables
  YIndepType dummy_raw_sample;
  YZIterator dummy_sampled_bin_boundary;

  return Exact::sampleDetailed<TwoDInterpPolicy,XIndepType,YIndepType,YZIterator,SampleFunctor>(
            sample_functor,
            dummy_raw_sample,
            dummy_sampled_bin_boundary,
            lower_bin_boundary,
            upper_bin_boundary,
            x_indep_value );
}

// Sample between bin boundaries using the desired sampling functor
template<typename TwoDInterpPolicy,
         typename XIndepType,
         typename YIndepType,
         typename YZIterator,
         typename SampleFunctor>
YIndepType Exact::sample(
            SampleFunctor sample_functor,
            const YZIterator& lower_bin_boundary,
            const YZIterator& upper_bin_boundary,
            const XIndepType& x_indep_value,
            const YIndepType& min_y_indep_value,
            const YIndepType& max_y_indep_value )
{
  // Dummy variables
  YIndepType dummy_raw_sample;
  YZIterator dummy_sampled_bin_boundary;

  return Exact::sampleDetailed<TwoDInterpPolicy,XIndepType,YIndepType,YZIterator,SampleFunctor>(
            sample_functor,
            dummy_raw_sample,
            dummy_sampled_bin_boundary,
            lower_bin_boundary,
            upper_bin_boundary,
            x_indep_value,
            min_y_indep_value,
            max_y_indep_value );
}

// Sample between bin boundaries using the desired sampling functor
template<typename TwoDInterpPolicy,
         typename XIndepType,
         typename YIndepType,
         typename YZIterator,
         typename SampleFunctor>
YIndepType Exact::sampleDetailed(
            SampleFunctor sample_functor,
            YIndepType& raw_sample,
            YZIterator& sampled_bin_boundary,
            const YZIterator& lower_bin_boundary,
            const YZIterator& upper_bin_boundary,
            const XIndepType& x_indep_value )
{
  // Get lower y indep value at the x indep value
  YIndepType min_y_indep_value =
   SamplingPolicyHelpers<TwoDInterpPolicy,XIndepType,YIndepType,YZIterator>::getLowerBoundOfConditionalIndepVar(
                      x_indep_value,
                      lower_bin_boundary,
                      upper_bin_boundary );

  // Get upper y indep value at the x indep value
  YIndepType max_y_indep_value =
   SamplingPolicyHelpers<TwoDInterpPolicy,XIndepType,YIndepType,YZIterator>::getUpperBoundOfConditionalIndepVar(
                      x_indep_value,
                      lower_bin_boundary,
                      upper_bin_boundary );

  return Exact::sampleDetailed<TwoDInterpPolicy,XIndepType,YIndepType,YZIterator,SampleFunctor>(
            sample_functor,
            raw_sample,
            sampled_bin_boundary,
            lower_bin_boundary,
            upper_bin_boundary,
            x_indep_value,
            min_y_indep_value,
            max_y_indep_value );
}

  //! Sample between bin boundaries using the desired sampling functor
  template<typename TwoDInterpPolicy,
           typename XIndepType,
           typename YIndepType,
           typename YZIterator,
           typename SampleFunctor>
  YIndepType Exact::sampleDetailed(
            SampleFunctor sample_functor,
            YIndepType& raw_sample,
            YZIterator& sampled_bin_boundary,
            const YZIterator& lower_bin_boundary,
            const YZIterator& upper_bin_boundary,
            const XIndepType& x_indep_value,
            const YIndepType& min_y_indep_value,
            const YIndepType& max_y_indep_value )
{
  // Make sure the y limits is valid
  testPrecondition( max_y_indep_value >= min_y_indep_value );

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
    raw_sample = TwoDInterpPolicy::ZXInterpPolicy::interpolate(
                          lower_bin_boundary->first,
                          upper_bin_boundary->first,
                          x_indep_value,
                          sample_functor( *lower_bin_boundary->second ),
                          sample_functor( *upper_bin_boundary->second ) );

    sampled_bin_boundary = lower_bin_boundary;
  }
  return raw_sample;
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
         typename SampleFunctor>
YIndepType Correlated::sample(
            SampleFunctor sample_functor,
            const YZIterator& lower_bin_boundary,
            const YZIterator& upper_bin_boundary,
            const XIndepType& x_indep_value )
{
  // Dummy variables
  YIndepType dummy_raw_sample;
  YZIterator dummy_sampled_bin_boundary;

  return Correlated::sampleDetailed<TwoDInterpPolicy,XIndepType,YIndepType,YZIterator,SampleFunctor>(
            sample_functor,
            dummy_raw_sample,
            dummy_sampled_bin_boundary,
            lower_bin_boundary,
            upper_bin_boundary,
            x_indep_value );
}

// Sample between bin boundaries using the desired sampling functor
template<typename TwoDInterpPolicy,
         typename XIndepType,
         typename YIndepType,
         typename YZIterator,
         typename SampleFunctor>
YIndepType Correlated::sample(
            SampleFunctor sample_functor,
            const YZIterator& lower_bin_boundary,
            const YZIterator& upper_bin_boundary,
            const XIndepType& x_indep_value,
            const YIndepType& min_y_indep_value,
            const YIndepType& max_y_indep_value )
{
  // Dummy variables
  YIndepType dummy_raw_sample;
  YZIterator dummy_sampled_bin_boundary;

  return Correlated::sampleDetailed<TwoDInterpPolicy,XIndepType,YIndepType,YZIterator,SampleFunctor>(
            sample_functor,
            dummy_raw_sample,
            dummy_sampled_bin_boundary,
            lower_bin_boundary,
            upper_bin_boundary,
            x_indep_value,
            min_y_indep_value,
            max_y_indep_value );
}

// Sample between bin boundaries using the desired sampling functor
template<typename TwoDInterpPolicy,
         typename XIndepType,
         typename YIndepType,
         typename YZIterator,
         typename SampleFunctor>
YIndepType Correlated::sampleDetailed(
            SampleFunctor sample_functor,
            YIndepType& raw_sample,
            YZIterator& sampled_bin_boundary,
            const YZIterator& lower_bin_boundary,
            const YZIterator& upper_bin_boundary,
            const XIndepType& x_indep_value )
{
  // Get lower y indep value at the x indep value
  YIndepType min_y_indep_value =
   SamplingPolicyHelpers<TwoDInterpPolicy,XIndepType,YIndepType,YZIterator>::getLowerBoundOfConditionalIndepVar(
                      x_indep_value,
                      lower_bin_boundary,
                      upper_bin_boundary );

  // Get upper y indep value at the x indep value
  YIndepType max_y_indep_value =
   SamplingPolicyHelpers<TwoDInterpPolicy,XIndepType,YIndepType,YZIterator>::getUpperBoundOfConditionalIndepVar(
                      x_indep_value,
                      lower_bin_boundary,
                      upper_bin_boundary );

  return Correlated::sampleDetailed<TwoDInterpPolicy,XIndepType,YIndepType,YZIterator,SampleFunctor>(
            sample_functor,
            raw_sample,
            sampled_bin_boundary,
            lower_bin_boundary,
            upper_bin_boundary,
            x_indep_value,
            min_y_indep_value,
            max_y_indep_value );
}

  //! Sample between bin boundaries using the desired sampling functor
  template<typename TwoDInterpPolicy,
           typename XIndepType,
           typename YIndepType,
           typename YZIterator,
           typename SampleFunctor>
  YIndepType Correlated::sampleDetailed(
            SampleFunctor sample_functor,
            YIndepType& raw_sample,
            YZIterator& sampled_bin_boundary,
            const YZIterator& lower_bin_boundary,
            const YZIterator& upper_bin_boundary,
            const XIndepType& x_indep_value,
            const YIndepType& min_y_indep_value,
            const YIndepType& max_y_indep_value )
{
  // Make sure the y limits is valid
  testPrecondition( max_y_indep_value >= min_y_indep_value );

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
  else if( min_y_indep_value == max_y_indep_value )
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
      eta = TwoDInterpPolicy::ZXInterpPolicy::interpolate(
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
  return raw_sample;
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
