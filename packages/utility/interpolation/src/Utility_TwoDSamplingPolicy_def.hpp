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

// Sample from the distribution using the desired sampling functor
template<typename TwoDInterpPolicy,
         typename FirstIndepType,
         typename SecondIndepType,
         typename YZIterator,
         typename SampleFunctor>
SecondIndepType Stochastic::sample(
            SampleFunctor sample_functor,
            const FirstIndepType primary_indep_var_value,
            const SecondIndepType min_secondary_indep_var_value,
            const SecondIndepType max_secondary_indep_var_value,
            const YZIterator& lower_bin_boundary,
            const YZIterator& upper_bin_boundary )
{
  YZIterator sampled_bin_boundary =
    Stochastic::sampleBinBoundary<FirstIndepType,YZIterator>(
                            primary_indep_var_value,
                            lower_bin_boundary,
                            upper_bin_boundary );

  // Create the raw sample
  SecondIndepType raw_sample = sample_functor( *sampled_bin_boundary->second );

  // Calculate the intermediate grid limits
  typename QuantityTraits<SecondIndepType>::RawType
    intermediate_grid_length =
    TwoDInterpPolicy::SecondaryBasePolicy::calculateUnitBaseGridLength(
                min_secondary_indep_var_value, max_secondary_indep_var_value );
  
  // Calculate the unit base variable on the bin boundary corresponding to the
  // raw sample
  typename QuantityTraits<SecondIndepType>::RawType eta;

  {
    typename QuantityTraits<SecondIndepType>::RawType grid_length =
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
                eta, min_secondary_indep_var_value, intermediate_grid_length );
}


// Sample the bin boundary that will be used for stochastic sampling
/*! \details This method will throw an exception if the primary independent
 * value is outside of the primary grid limits and the primary grid has not
 * been extended.
 */
template<typename TwoDInterpPolicy,
         typename FirstIndepType,
         typename YZIterator>
YZIterator Stochastic::sampleBinBoundary(
    const FirstIndepType primary_indep_var_value,
    const YZIterator lower_bin_boundary,
    const YZIterator upper_bin_boundary )
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

// The name of the policy
inline const std::string Stochastic::name()
{
  return "Stochastic";
}

} // end Utility namespace

#endif // end UTILITY_TWO_D_SAMPLING_POLICY_DEF_HPP

//---------------------------------------------------------------------------//
// end Utility_TwoDSamplingPolicy_def.hpp
//---------------------------------------------------------------------------//
