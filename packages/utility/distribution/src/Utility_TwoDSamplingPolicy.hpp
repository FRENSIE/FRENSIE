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

  // //! Sample between bin boundaries using the desired sampling functor
  // template<typename TwoDInterpPolicy,
  //          typename XIndepType,
  //          typename YIndepType,
  //          typename YZIterator,
  //          typename SampleFunctor>
  // static YIndepType sample( const SampleFunctor& sample_functor,
  //                           const XIndepType& x_indep_value,
  //                           const YZIterator& lower_bin_boundary,
  //                           const YZIterator& upper_bin_boundary,
  //                           const YIndepType& min_y_indep_value,
  //                           const YIndepType& max_y_indep_value );

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

  // //! Sample between bin boundaries using the desired sampling functor
  // template<typename TwoDInterpPolicy,
  //          typename XIndepType,
  //          typename YIndepType,
  //          typename YZIterator,
  //          typename SampleFunctor>
  // static YIndepType sampleDetailed( const SampleFunctor& sample_functor,
  //                                   const XIndepType& x_indep_value,
  //                                   const YZIterator& lower_bin_boundary,
  //                                   const YZIterator& upper_bin_boundary,
  //                                   const YIndepType& min_y_indep_value,
  //                                   const YIndepType& max_y_indep_value,
  //                                   YZIterator& sampled_bin_boundary,
  //                                   YIndepType& raw_sample );

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

  // //! Sample between bin boundaries using the desired sampling functor
  // template<typename TwoDInterpPolicy,
  //          typename XIndepType,
  //          typename YIndepType,
  //          typename YZIterator,
  //          typename SampleFunctor>
  // static YIndepType sample( const SampleFunctor& sample_functor,
  //                           const XIndepType& x_indep_value,
  //                           const YZIterator& lower_bin_boundary,
  //                           const YZIterator& upper_bin_boundary,
  //                           const YIndepType& min_y_indep_value,
  //                           const YIndepType& max_y_indep_value );

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

  // //! Sample between bin boundaries using the desired sampling functor
  // template<typename TwoDInterpPolicy,
  //          typename XIndepType,
  //          typename YIndepType,
  //          typename YZIterator,
  //          typename SampleFunctor>
  // static YIndepType sampleDetailed( const SampleFunctor& sample_functor,
  //                                   const XIndepType& x_indep_value,
  //                                   const YZIterator& lower_bin_boundary,
  //                                   const YZIterator& upper_bin_boundary,
  //                                   const YIndepType& min_y_indep_value,
  //                                   const YIndepType& max_y_indep_value,
  //                                   YZIterator& sampled_bin_boundary,
  //                                   YIndepType& raw_sample );

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

  // //! Sample between bin boundaries using the desired sampling functor
  // template<typename TwoDInterpPolicy,
  //          typename XIndepType,
  //          typename YIndepType,
  //          typename YZIterator,
  //          typename SampleFunctor>
  // static YIndepType sample( const SampleFunctor& sample_functor,
  //                           const XIndepType& x_indep_value,
  //                           const YZIterator& lower_bin_boundary,
  //                           const YZIterator& upper_bin_boundary,
  //                           const YIndepType& min_y_indep_value,
  //                           const YIndepType& max_y_indep_value );

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

  // //! Sample between bin boundaries using the desired sampling functor
  // template<typename TwoDInterpPolicy,
  //          typename XIndepType,
  //          typename YIndepType,
  //          typename YZIterator,
  //          typename SampleFunctor>
  // static YIndepType sampleDetailed( const SampleFunctor& sample_functor,
  //                                   const XIndepType& x_indep_value,
  //                                   const YZIterator& lower_bin_boundary,
  //                                   const YZIterator& upper_bin_boundary,
  //                                   const YIndepType& min_y_indep_value,
  //                                   const YIndepType& max_y_indep_value,
  //                                   YZIterator& sampled_bin_boundary,
  //                                   YIndepType& raw_sample );

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
