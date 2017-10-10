//---------------------------------------------------------------------------//
//!
//! \file   Utility_TwoDSamplingPolicy.hpp
//! \author Luke Kersting
//! \brief  Policy struct declarations for sampling on 2D grids
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_TWO_D_SAMPLING_POLICY_HPP
#define UTILITY_TWO_D_SAMPLING_POLICY_HPP

// Std Lib Includes
#include <iterator>

// FRENSIE Includes
#include "Utility_TwoDInterpolationPolicy.hpp"
#include "Utility_Tuple.hpp"
#include "Utility_TupleMemberTraits.hpp"
#include "Utility_QuantityTraits.hpp"

namespace Utility{

//! Helper class used by sampling policy methods
template<typename TwoDInterpPolicy,
          typename XIndepType,
          typename YIndepType,
          typename YZIterator>
struct SamplingPolicyHelpers
{
  // Return the lower bound of the conditional distribution
  static YIndepType getLowerBoundOfConditionalIndepVar(
                    const XIndepType& x_indep_value,
                    const YZIterator& lower_bin_boundary,
                    const YZIterator& upper_bin_boundary );

  // Return the upper bound of the conditional distribution
  static YIndepType getUpperBoundOfConditionalIndepVar(
                    const XIndepType& x_indep_value,
                    const YZIterator& lower_bin_boundary,
                    const YZIterator& upper_bin_boundary );

};

/*! \brief Policy struct for sampling 2D tables ( stochastic unit base sampling
 * is performed ).
 */
struct Stochastic
{
public:

  //! Sample between bin boundaries using the desired sampling functor
  template<typename TwoDInterpPolicy,
          typename XIndepType,
          typename YIndepType,
          typename YZIterator,
          typename SampleFunctor>
  static YIndepType sample(
              SampleFunctor sample_functor,
              const YZIterator& lower_bin_boundary,
              const YZIterator& upper_bin_boundary,
              const XIndepType& x_indep_value );

  //! Sample between bin boundaries using the desired sampling functor
  template<typename TwoDInterpPolicy,
          typename XIndepType,
          typename YIndepType,
          typename YZIterator,
          typename SampleFunctor>
  static YIndepType sample(
              SampleFunctor sample_functor,
              const YZIterator& lower_bin_boundary,
              const YZIterator& upper_bin_boundary,
              const XIndepType& x_indep_value,
              const YIndepType& min_y_indep_value,
              const YIndepType& max_y_indep_value );

  //! Sample between bin boundaries using the desired sampling functor
  template<typename TwoDInterpPolicy,
           typename XIndepType,
           typename YIndepType,
           typename YZIterator,
           typename SampleFunctor>
  static YIndepType sampleDetailed(
            SampleFunctor sample_functor,
            YIndepType& raw_sample,
            YZIterator& sampled_bin_boundary,
            const YZIterator& lower_bin_boundary,
            const YZIterator& upper_bin_boundary,
            const XIndepType& x_indep_value );

  //! Sample between bin boundaries using the desired sampling functor
  template<typename TwoDInterpPolicy,
           typename XIndepType,
           typename YIndepType,
           typename YZIterator,
           typename SampleFunctor>
  static YIndepType sampleDetailed(
            SampleFunctor sample_functor,
            YIndepType& raw_sample,
            YZIterator& sampled_bin_boundary,
            const YZIterator& lower_bin_boundary,
            const YZIterator& upper_bin_boundary,
            const XIndepType& x_indep_value,
            const YIndepType& min_y_indep_value,
            const YIndepType& max_y_indep_value );

  //! The name of the policy
  static const std::string name();

private:

  //! Sample the bin boundary that will be used for stochastic sampling
  template<typename TwoDInterpPolicy,
           typename XIndepType,
           typename YZIterator>
  static YZIterator sampleBinBoundary(
    const XIndepType& x_indep_value,
    const YZIterator& lower_bin_boundary,
    const YZIterator& upper_bin_boundary );
};

/*! \brief Policy struct for sampling 2D tables ( correlated exact sampling
 * is performed ).
 */
struct Exact
{
public:

  //! Sample between bin boundaries using the desired sampling functor
  template<typename TwoDInterpPolicy,
          typename XIndepType,
          typename YIndepType,
          typename YZIterator,
          typename SampleFunctor>
  static YIndepType sample(
              SampleFunctor sample_functor,
              const YZIterator& lower_bin_boundary,
              const YZIterator& upper_bin_boundary,
              const XIndepType& x_indep_value );

  //! Sample between bin boundaries using the desired sampling functor
  template<typename TwoDInterpPolicy,
          typename XIndepType,
          typename YIndepType,
          typename YZIterator,
          typename SampleFunctor>
  static YIndepType sample(
              SampleFunctor sample_functor,
              const YZIterator& lower_bin_boundary,
              const YZIterator& upper_bin_boundary,
              const XIndepType& x_indep_value,
              const YIndepType& min_y_indep_value,
              const YIndepType& max_y_indep_value );

  //! Sample between bin boundaries using the desired sampling functor
  template<typename TwoDInterpPolicy,
           typename XIndepType,
           typename YIndepType,
           typename YZIterator,
           typename SampleFunctor>
  static YIndepType sampleDetailed(
            SampleFunctor sample_functor,
            YIndepType& raw_sample,
            YZIterator& sampled_bin_boundary,
            const YZIterator& lower_bin_boundary,
            const YZIterator& upper_bin_boundary,
            const XIndepType& x_indep_value );

  //! Sample between bin boundaries using the desired sampling functor
  template<typename TwoDInterpPolicy,
           typename XIndepType,
           typename YIndepType,
           typename YZIterator,
           typename SampleFunctor>
  static YIndepType sampleDetailed(
            SampleFunctor sample_functor,
            YIndepType& raw_sample,
            YZIterator& sampled_bin_boundary,
            const YZIterator& lower_bin_boundary,
            const YZIterator& upper_bin_boundary,
            const XIndepType& x_indep_value,
            const YIndepType& min_y_indep_value,
            const YIndepType& max_y_indep_value );

  //! The name of the policy
  static const std::string name();
};

/*! \brief Policy struct for sampling 2D tables ( correlated unit base sampling
 * is performed ).
 */
struct Correlated
{
public:

  //! Sample between bin boundaries using the desired sampling functor
  template<typename TwoDInterpPolicy,
          typename XIndepType,
          typename YIndepType,
          typename YZIterator,
          typename SampleFunctor>
  static YIndepType sample(
              SampleFunctor sample_functor,
              const YZIterator& lower_bin_boundary,
              const YZIterator& upper_bin_boundary,
              const XIndepType& x_indep_value );

  //! Sample between bin boundaries using the desired sampling functor
  template<typename TwoDInterpPolicy,
          typename XIndepType,
          typename YIndepType,
          typename YZIterator,
          typename SampleFunctor>
  static YIndepType sample(
              SampleFunctor sample_functor,
              const YZIterator& lower_bin_boundary,
              const YZIterator& upper_bin_boundary,
              const XIndepType& x_indep_value,
              const YIndepType& min_y_indep_value,
              const YIndepType& max_y_indep_value );

  //! Sample between bin boundaries using the desired sampling functor
  template<typename TwoDInterpPolicy,
           typename XIndepType,
           typename YIndepType,
           typename YZIterator,
           typename SampleFunctor>
  static YIndepType sampleDetailed(
            SampleFunctor sample_functor,
            YIndepType& raw_sample,
            YZIterator& sampled_bin_boundary,
            const YZIterator& lower_bin_boundary,
            const YZIterator& upper_bin_boundary,
            const XIndepType& x_indep_value );

  //! Sample between bin boundaries using the desired sampling functor
  template<typename TwoDInterpPolicy,
           typename XIndepType,
           typename YIndepType,
           typename YZIterator,
           typename SampleFunctor>
  static YIndepType sampleDetailed(
            SampleFunctor sample_functor,
            YIndepType& raw_sample,
            YZIterator& sampled_bin_boundary,
            const YZIterator& lower_bin_boundary,
            const YZIterator& upper_bin_boundary,
            const XIndepType& x_indep_value,
            const YIndepType& min_y_indep_value,
            const YIndepType& max_y_indep_value );

  //! The name of the policy
  static const std::string name();
};

} // end Utility namespace

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "Utility_TwoDSamplingPolicy_def.hpp"

//---------------------------------------------------------------------------//

#endif // end UTILITY_TWO_D_SAMPLING_POLICY_HPP

//---------------------------------------------------------------------------//
// end Utility_TwoDSamplingPolicy.hpp
//---------------------------------------------------------------------------//
