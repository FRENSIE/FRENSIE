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

/*! \brief Policy struct for sampling 2D tables ( stochastic unit base sampling
 * is performed ).
 */
struct Stochastic
{
public:

  //! Evaluate between bin boundaries using the desired evaluation method
  template<typename TwoDInterpPolicy,
           typename BaseOneDDistributionType,
           typename XIndepType,
           typename YIndepType,
           typename ReturnType,
           typename YZIterator,
           typename EvaluationMethod,
           typename YBoundsFunctor>
  static ReturnType evaluateCosSampleBased(
                      const XIndepType& x_indep_value,
                      const YIndepType& y_indep_value,
                      const YBoundsFunctor& min_y_indep_functor,
                      const YBoundsFunctor& max_y_indep_functor,
                      const EvaluationMethod& evaluate,
                      const YZIterator& lower_bin_boundary,
                      const YZIterator& upper_bin_boundary,
                      const double rel_error_tol = 1e-7,
                      const double error_tol = 1e-15,
                      unsigned max_number_of_iterations = 500u );

  //! Evaluate between bin boundaries using the desired evaluation method
  template<typename TwoDInterpPolicy,
           typename BaseOneDDistributionType,
           typename XIndepType,
           typename YIndepType,
           typename ReturnType,
           typename YZIterator,
           typename EvaluationMethod,
           typename YBoundsFunctor>
  static ReturnType evaluateSampleBased(
              const XIndepType& x_indep_value,
              const YIndepType& y_indep_value,
              const YBoundsFunctor& min_y_indep_functor,
              const YBoundsFunctor& max_y_indep_functor,
              const EvaluationMethod& evaluate,
              const YZIterator& lower_bin_boundary,
              const YZIterator& upper_bin_boundary,
              const ReturnType& below_lower_bound_return =
                Utility::QuantityTraits<ReturnType>::zero(),
              const ReturnType& above_upper_bound_return =
                Utility::QuantityTraits<ReturnType>::zero(),
              const double fuzzy_boundary_tol = 1e-3,
              const double rel_error_tol = 1e-7,
              const double error_tol = 1e-15,
              unsigned max_number_of_iterations = 500u );

  //! Evaluate between bin boundaries using the desired evaluation method
  template<typename TwoDInterpPolicy,
           typename BaseOneDDistributionType,
           typename XIndepType,
           typename YIndepType,
           typename ReturnType,
           typename YZIterator,
           typename EvaluationMethod,
           typename YBoundsFunctor>
  static ReturnType evaluateDirect(
              const XIndepType& x_indep_value,
              const YIndepType& y_indep_value,
              const YBoundsFunctor& min_y_indep_functor,
              const YBoundsFunctor& max_y_indep_functor,
              const EvaluationMethod& evaluate,
              const YZIterator& lower_bin_boundary,
              const YZIterator& upper_bin_boundary,
              const ReturnType& below_lower_bound_return =
                Utility::QuantityTraits<ReturnType>::zero(),
              const ReturnType& above_upper_bound_return =
                Utility::QuantityTraits<ReturnType>::zero(),
              const double fuzzy_boundary_tol = 1e-3 );

  //! Sample between bin boundaries using the desired sampling functor
  template<typename TwoDInterpPolicy,
           typename XIndepType,
           typename YIndepType,
           typename YZIterator,
           typename SampleFunctor,
           typename YBoundsFunctor>
  static YIndepType sample( const SampleFunctor& sample_functor,
                            const YBoundsFunctor& min_y_indep_functor,
                            const YBoundsFunctor& max_y_indep_functor,
                            const XIndepType& x_indep_value,
                            const YZIterator& lower_bin_boundary,
                            const YZIterator& upper_bin_boundary );

  //! Sample between bin boundaries using the desired sampling functor
  template<typename TwoDInterpPolicy,
           typename XIndepType,
           typename YIndepType,
           typename YZIterator,
           typename SampleFunctor>
  static YIndepType sampleCos( const SampleFunctor& sample_functor,
                               const XIndepType& x_indep_value,
                               const YZIterator& lower_bin_boundary,
                               const YZIterator& upper_bin_boundary );

  //! Sample between bin boundaries using the desired subrange sampling functor
  template<typename TwoDInterpPolicy,
           typename XIndepType,
           typename YIndepType,
           typename YZIterator,
           typename SampleFunctor,
           typename YBoundsFunctor>
  static YIndepType sampleInSubrange(
            const SampleFunctor& subrange_sample_functor,
            const YBoundsFunctor& min_y_indep_functor,
            const YBoundsFunctor& max_y_indep_functor,
            const XIndepType& x_indep_value,
            const YZIterator& lower_bin_boundary,
            const YZIterator& upper_bin_boundary,
            const YIndepType& max_y_indep_value );

  //! Sample between bin boundaries using the desired sampling functor
  template<typename TwoDInterpPolicy,
           typename XIndepType,
           typename YIndepType,
           typename YZIterator,
           typename SampleFunctor,
           typename YBoundsFunctor>
  static YIndepType sampleDetailed( const SampleFunctor& sample_functor,
                                    const YBoundsFunctor& min_y_indep_functor,
                                    const YBoundsFunctor& max_y_indep_functor,
                                    const XIndepType& x_indep_value,
                                    const YZIterator& lower_bin_boundary,
                                    const YZIterator& upper_bin_boundary,
                                    YZIterator& sampled_bin_boundary,
                                    YIndepType& raw_sample );

 //! Sample between bin boundaries using the desired sampling functor
  template<typename TwoDInterpPolicy,
           typename XIndepType,
           typename YIndepType,
           typename YZIterator,
           typename SampleFunctor>
  static YIndepType sampleCosDetailed( const SampleFunctor& sample_functor,
                                       const XIndepType& x_indep_value,
                                       const YZIterator& lower_bin_boundary,
                                       const YZIterator& upper_bin_boundary,
                                       YZIterator& sampled_bin_boundary,
                                       YIndepType& raw_sample );

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

  //! Evaluate between bin boundaries using the desired evaluation method
  template<typename TwoDInterpPolicy,
           typename BaseOneDDistributionType,
           typename XIndepType,
           typename YIndepType,
           typename ReturnType,
           typename YZIterator,
           typename EvaluationMethod,
           typename YBoundsFunctor>
  static ReturnType evaluateCosSampleBased(
                      const XIndepType& x_indep_value,
                      const YIndepType& y_indep_value,
                      const YBoundsFunctor& min_y_indep_functor,
                      const YBoundsFunctor& max_y_indep_functor,
                      const EvaluationMethod& evaluate,
                      const YZIterator& lower_bin_boundary,
                      const YZIterator& upper_bin_boundary,
                      const double rel_error_tol = 1e-7,
                      const double error_tol = 1e-15,
                      unsigned max_number_of_iterations = 500u );

  //! Evaluate between bin boundaries using the desired evaluation method
  template<typename TwoDInterpPolicy,
           typename BaseOneDDistributionType,
           typename XIndepType,
           typename YIndepType,
           typename ReturnType,
           typename YZIterator,
           typename EvaluationMethod,
           typename YBoundsFunctor>
  static ReturnType evaluateSampleBased(
              const XIndepType& x_indep_value,
              const YIndepType& y_indep_value,
              const YBoundsFunctor& min_y_indep_functor,
              const YBoundsFunctor& max_y_indep_functor,
              const EvaluationMethod& evaluate,
              const YZIterator& lower_bin_boundary,
              const YZIterator& upper_bin_boundary,
              const ReturnType& below_lower_bound_return =
                Utility::QuantityTraits<ReturnType>::zero(),
              const ReturnType& above_upper_bound_return =
                Utility::QuantityTraits<ReturnType>::zero(),
              const double fuzzy_boundary_tol = 1e-3,
              const double rel_error_tol = 1e-7,
              const double error_tol = 1e-15,
              unsigned max_number_of_iterations = 500u );


  //! Evaluate between bin boundaries using the desired evaluation method
  template<typename TwoDInterpPolicy,
           typename BaseOneDDistributionType,
           typename XIndepType,
           typename YIndepType,
           typename ReturnType,
           typename YZIterator,
           typename EvaluationMethod,
           typename YBoundsFunctor>
  static ReturnType evaluateDirect(
              const XIndepType& x_indep_value,
              const YIndepType& y_indep_value,
              const YBoundsFunctor& min_y_indep_functor,
              const YBoundsFunctor& max_y_indep_functor,
              const EvaluationMethod& evaluate,
              const YZIterator& lower_bin_boundary,
              const YZIterator& upper_bin_boundary,
              const ReturnType& below_lower_bound_return =
                Utility::QuantityTraits<ReturnType>::zero(),
              const ReturnType& above_upper_bound_return =
                Utility::QuantityTraits<ReturnType>::zero(),
              const double fuzzy_boundary_tol = 1e-3 );

  //! Sample between bin boundaries using the desired sampling functor
  template<typename TwoDInterpPolicy,
           typename XIndepType,
           typename YIndepType,
           typename YZIterator,
           typename SampleFunctor,
           typename YBoundsFunctor>
  static YIndepType sample( const SampleFunctor& sample_functor,
                            const YBoundsFunctor& min_y_indep_functor,
                            const YBoundsFunctor& max_y_indep_functor,
                            const XIndepType& x_indep_value,
                            const YZIterator& lower_bin_boundary,
                            const YZIterator& upper_bin_boundary );

  //! Sample between bin boundaries using the desired sampling functor
  template<typename TwoDInterpPolicy,
           typename XIndepType,
           typename YIndepType,
           typename YZIterator,
           typename SampleFunctor>
  static YIndepType sampleCos( const SampleFunctor& sample_functor,
                               const XIndepType& x_indep_value,
                               const YZIterator& lower_bin_boundary,
                               const YZIterator& upper_bin_boundary );

  //! Sample between bin boundaries using the desired subrange sampling functor
  template<typename TwoDInterpPolicy,
           typename XIndepType,
           typename YIndepType,
           typename YZIterator,
           typename SampleFunctor,
           typename YBoundsFunctor>
  static YIndepType sampleInSubrange(
            const SampleFunctor& subrange_sample_functor,
            const YBoundsFunctor& min_y_indep_functor,
            const YBoundsFunctor& max_y_indep_functor,
            const XIndepType& x_indep_value,
            const YZIterator& lower_bin_boundary,
            const YZIterator& upper_bin_boundary,
            const YIndepType& max_y_indep_value );

  //! Sample between bin boundaries using the desired sampling functor
  template<typename TwoDInterpPolicy,
           typename XIndepType,
           typename YIndepType,
           typename YZIterator,
           typename SampleFunctor,
           typename YBoundsFunctor>
  static YIndepType sampleDetailed( const SampleFunctor& sample_functor,
                                    const YBoundsFunctor& min_y_indep_functor,
                                    const YBoundsFunctor& max_y_indep_functor,
                                    const XIndepType& x_indep_value,
                                    const YZIterator& lower_bin_boundary,
                                    const YZIterator& upper_bin_boundary,
                                    YZIterator& sampled_bin_boundary,
                                    YIndepType& raw_sample );

 //! Sample between bin boundaries using the desired sampling functor
  template<typename TwoDInterpPolicy,
           typename XIndepType,
           typename YIndepType,
           typename YZIterator,
           typename SampleFunctor>
  static YIndepType sampleCosDetailed( const SampleFunctor& sample_functor,
                                       const XIndepType& x_indep_value,
                                       const YZIterator& lower_bin_boundary,
                                       const YZIterator& upper_bin_boundary,
                                       YZIterator& sampled_bin_boundary,
                                       YIndepType& raw_sample );

  //! The name of the policy
  static const std::string name();
};

/*! \brief Policy struct for sampling 2D tables ( correlated unit base sampling
 * is performed ).
 */
struct Correlated
{
public:

  //! Evaluate between bin boundaries using the desired evaluation method
  template<typename TwoDInterpPolicy,
           typename BaseOneDDistributionType,
           typename XIndepType,
           typename YIndepType,
           typename ReturnType,
           typename YZIterator,
           typename EvaluationMethod,
           typename YBoundsFunctor>
  static ReturnType evaluateCosSampleBased(
                      const XIndepType& x_indep_value,
                      const YIndepType& y_indep_value,
                      const YBoundsFunctor& min_y_indep_functor,
                      const YBoundsFunctor& max_y_indep_functor,
                      const EvaluationMethod& evaluate,
                      const YZIterator& lower_bin_boundary,
                      const YZIterator& upper_bin_boundary,
                      const double rel_error_tol = 1e-7,
                      const double error_tol = 1e-15,
                      unsigned max_number_of_iterations = 500u );

  //! Evaluate between bin boundaries using the desired evaluation method
  template<typename TwoDInterpPolicy,
           typename BaseOneDDistributionType,
           typename XIndepType,
           typename YIndepType,
           typename ReturnType,
           typename YZIterator,
           typename EvaluationMethod,
           typename YBoundsFunctor>
  static ReturnType evaluateSampleBased(
              const XIndepType& x_indep_value,
              const YIndepType& y_indep_value,
              const YBoundsFunctor& min_y_indep_functor,
              const YBoundsFunctor& max_y_indep_functor,
              const EvaluationMethod& evaluate,
              const YZIterator& lower_bin_boundary,
              const YZIterator& upper_bin_boundary,
              const ReturnType& below_lower_bound_return =
                Utility::QuantityTraits<ReturnType>::zero(),
              const ReturnType& above_upper_bound_return =
                Utility::QuantityTraits<ReturnType>::zero(),
              const double fuzzy_boundary_tol = 1e-3,
              const double rel_error_tol = 1e-7,
              const double error_tol = 1e-15,
              unsigned max_number_of_iterations = 500u );


  //! Evaluate between bin boundaries using the desired evaluation method
  template<typename TwoDInterpPolicy,
           typename BaseOneDDistributionType,
           typename XIndepType,
           typename YIndepType,
           typename ReturnType,
           typename YZIterator,
           typename EvaluationMethod,
           typename YBoundsFunctor>
static ReturnType evaluateDirect(
              const XIndepType& x_indep_value,
              const YIndepType& y_indep_value,
              const YBoundsFunctor& min_y_indep_functor,
              const YBoundsFunctor& max_y_indep_functor,
              const EvaluationMethod& evaluate,
              const YZIterator& lower_bin_boundary,
              const YZIterator& upper_bin_boundary,
              const ReturnType& below_lower_bound_return =
                Utility::QuantityTraits<ReturnType>::zero(),
              const ReturnType& above_upper_bound_return =
                Utility::QuantityTraits<ReturnType>::zero(),
              const double fuzzy_boundary_tol = 1e-3 );

  //! Sample between bin boundaries using the desired sampling functor
  template<typename TwoDInterpPolicy,
           typename XIndepType,
           typename YIndepType,
           typename YZIterator,
           typename SampleFunctor,
           typename YBoundsFunctor>
  static YIndepType sample( const SampleFunctor& sample_functor,
                            const YBoundsFunctor& min_y_indep_functor,
                            const YBoundsFunctor& max_y_indep_functor,
                            const XIndepType& x_indep_value,
                            const YZIterator& lower_bin_boundary,
                            const YZIterator& upper_bin_boundary );

  //! Sample between bin boundaries using the desired sampling functor
  template<typename TwoDInterpPolicy,
           typename XIndepType,
           typename YIndepType,
           typename YZIterator,
           typename SampleFunctor>
  static YIndepType sampleCos( const SampleFunctor& sample_functor,
                               const XIndepType& x_indep_value,
                               const YZIterator& lower_bin_boundary,
                               const YZIterator& upper_bin_boundary );

  //! Sample between bin boundaries using the desired subrange sampling functor
  template<typename TwoDInterpPolicy,
           typename XIndepType,
           typename YIndepType,
           typename YZIterator,
           typename SampleFunctor,
           typename YBoundsFunctor>
  static YIndepType sampleInSubrange(
            const SampleFunctor& subrange_sample_functor,
            const YBoundsFunctor& min_y_indep_functor,
            const YBoundsFunctor& max_y_indep_functor,
            const XIndepType& x_indep_value,
            const YZIterator& lower_bin_boundary,
            const YZIterator& upper_bin_boundary,
            const YIndepType& max_y_indep_value );

  //! Sample between bin boundaries using the desired sampling functor
  template<typename TwoDInterpPolicy,
           typename XIndepType,
           typename YIndepType,
           typename YZIterator,
           typename SampleFunctor,
           typename YBoundsFunctor>
  static YIndepType sampleDetailed( const SampleFunctor& sample_functor,
                                    const YBoundsFunctor& min_y_indep_functor,
                                    const YBoundsFunctor& max_y_indep_functor,
                                    const XIndepType& x_indep_value,
                                    const YZIterator& lower_bin_boundary,
                                    const YZIterator& upper_bin_boundary,
                                    YZIterator& sampled_bin_boundary,
                                    YIndepType& raw_sample );

 //! Sample between bin boundaries using the desired sampling functor
  template<typename TwoDInterpPolicy,
           typename XIndepType,
           typename YIndepType,
           typename YZIterator,
           typename SampleFunctor>
  static YIndepType sampleCosDetailed( const SampleFunctor& sample_functor,
                                       const XIndepType& x_indep_value,
                                       const YZIterator& lower_bin_boundary,
                                       const YZIterator& upper_bin_boundary,
                                       YZIterator& sampled_bin_boundary,
                                       YIndepType& raw_sample );

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
