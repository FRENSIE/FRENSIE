//---------------------------------------------------------------------------//
//!
//! \file   Utility_TwoDGridPolicy.hpp
//! \author Luke Kersting
//! \brief  Policy struct declarations for sampling on 2D grids
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_TWO_D_GRID_POLICY_HPP
#define UTILITY_TWO_D_GRID_POLICY_HPP

// Std Lib Includes
#include <iterator>

// FRENSIE Includes
#include "Utility_TwoDInterpolationPolicy.hpp"
#include "Utility_Tuple.hpp"
#include "Utility_QuantityTraits.hpp"
#include "Utility_TypeNameTraits.hpp"

namespace Utility{

/*! \brief Policy struct for evaluting and sampling 2D tables. A direct (a.k.a.
 * cartesian) interpolation method is used in evaluating the distribution and
 * the direct statistical method in sampling the distribution. If the sample
 * range varies between distribution (e.g. energy loss) direct interpolation
 * will often give non-physical values. Unless specifically specified direct
 * interpolation should only be used when the sampled range does not change
 * between distributions (e.g. cosines).
 */
template<typename _TwoDInterpPolicy>
struct Direct
{
  //! The two-dimensional interpolation policy
  typedef _TwoDInterpPolicy TwoDInterpPolicy;

  //! Calculate the Y independent lower bound between bin boundaries
  template<typename YIndepType,
           typename XIndepType,
           typename YZIterator>
  static YIndepType calculateLowerBound(
                      const XIndepType& x_indep_value,
                      const YZIterator& lower_bin_boundary,
                      const YZIterator& upper_bin_boundary );

  //! Calculate the Y independent upper bound between bin boundaries
  template<typename YIndepType,
           typename XIndepType,
           typename YZIterator>
  static YIndepType calculateUpperBound(
                      const XIndepType& x_indep_value,
                      const YZIterator& lower_bin_boundary,
                      const YZIterator& upper_bin_boundary );

  //! Evaluate the PDF between bin boundaries using the desired evaluation method
  template<typename BaseUnivariateDistributionType,
           typename XIndepType,
           typename YIndepType,
           typename ReturnType,
           typename YZIterator,
           typename EvaluationMethod,
           typename YBoundsFunctor>
  static ReturnType evaluatePDFCos(
                      const XIndepType& x_indep_value,
                      const YIndepType& y_indep_value,
                      const YBoundsFunctor& min_y_indep_functor,
                      const YBoundsFunctor& max_y_indep_functor,
                      const EvaluationMethod& evaluate,
                      const YZIterator& lower_bin_boundary,
                      const YZIterator& upper_bin_boundary,
                      const double fuzzy_boundary_tol = 1e-3,
                      const double rel_error_tol = 1e-7,
                      const double error_tol = 1e-15,
                      unsigned max_number_of_iterations = 500u );

  //! Evaluate the PDF between bin boundaries using the desired evaluation method
  template<typename BaseUnivariateDistributionType,
           typename XIndepType,
           typename YIndepType,
           typename ReturnType,
           typename YZIterator,
           typename EvaluationMethod,
           typename YBoundsFunctor>
  static ReturnType evaluatePDF(
              const XIndepType& x_indep_value,
              const YIndepType& y_indep_value,
              const YBoundsFunctor& min_y_indep_functor,
              const YBoundsFunctor& max_y_indep_functor,
              const EvaluationMethod& evaluate,
              const YZIterator& lower_bin_boundary,
              const YZIterator& upper_bin_boundary,
              const double fuzzy_boundary_tol = 1e-3,
              const double rel_error_tol = 1e-7,
              const double error_tol = 1e-15,
              unsigned max_number_of_iterations = 500u );

  //! Evaluate the CDF between bin boundaries using the desired evaluation method
  template<typename BaseUnivariateDistributionType,
           typename XIndepType,
           typename YIndepType,
           typename YZIterator,
           typename EvaluationMethod,
           typename YBoundsFunctor>
  static double evaluateCDFCos(
              const XIndepType& x_indep_value,
              const YIndepType& y_indep_value,
              const YBoundsFunctor& min_y_indep_functor,
              const YBoundsFunctor& max_y_indep_functor,
              const EvaluationMethod& evaluate,
              const YZIterator& lower_bin_boundary,
              const YZIterator& upper_bin_boundary,
              const double fuzzy_boundary_tol = 1e-3,
              const double rel_error_tol = 1e-7,
              const double error_tol = 1e-15,
              unsigned max_number_of_iterations = 500u );

  //! Evaluate the CDF between bin boundaries using the desired evaluation method
  template<typename BaseUnivariateDistributionType,
           typename XIndepType,
           typename YIndepType,
           typename YZIterator,
           typename EvaluationMethod,
           typename YBoundsFunctor>
  static double evaluateCDF(
              const XIndepType& x_indep_value,
              const YIndepType& y_indep_value,
              const YBoundsFunctor& min_y_indep_functor,
              const YBoundsFunctor& max_y_indep_functor,
              const EvaluationMethod& evaluate,
              const YZIterator& lower_bin_boundary,
              const YZIterator& upper_bin_boundary,
              const double fuzzy_boundary_tol = 1e-3,
              const double rel_error_tol = 1e-7,
              const double error_tol = 1e-15,
              unsigned max_number_of_iterations = 500u );

  //! Sample between bin boundaries using the desired sampling functor
  template<typename XIndepType,
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
  template<typename XIndepType,
           typename YIndepType,
           typename YZIterator,
           typename SampleFunctor>
  static YIndepType sampleCos( const SampleFunctor& sample_functor,
                               const XIndepType& x_indep_value,
                               const YZIterator& lower_bin_boundary,
                               const YZIterator& upper_bin_boundary );

  //! Sample between bin boundaries using the desired subrange sampling functor
  template<typename XIndepType,
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
  template<typename XIndepType,
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
  template<typename XIndepType,
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

  //! Sample the bin boundary that will be used for statistical sampling
  template<typename XIndepType,
           typename YZIterator>
  static YZIterator sampleBinBoundary(
    const XIndepType& x_indep_value,
    const YZIterator& lower_bin_boundary,
    const YZIterator& upper_bin_boundary );
};

/*! \brief Policy struct for evaluting and sampling 2D tables. A unit-base
 * interpolation method is used in evaluating the distribution and the unit-base
 * statistical method in sampling the distribution.
 */
template<typename _TwoDInterpPolicy>
struct UnitBase
{
  //! The two-dimensional interpolation policy
  typedef _TwoDInterpPolicy TwoDInterpPolicy;

  //! Calculate the Y independent lower bound between bin boundaries
  template<typename YIndepType,
           typename XIndepType,
           typename YZIterator>
  static YIndepType calculateLowerBound(
                      const XIndepType& x_indep_value,
                      const YZIterator& lower_bin_boundary,
                      const YZIterator& upper_bin_boundary );

  //! Calculate the Y independent upper bound between bin boundaries
  template<typename YIndepType,
           typename XIndepType,
           typename YZIterator>
  static YIndepType calculateUpperBound(
                      const XIndepType& x_indep_value,
                      const YZIterator& lower_bin_boundary,
                      const YZIterator& upper_bin_boundary );

  //! Evaluate the PDF between bin boundaries using the desired evaluation method
  template<typename BaseUnivariateDistributionType,
           typename XIndepType,
           typename YIndepType,
           typename ReturnType,
           typename YZIterator,
           typename EvaluationMethod,
           typename YBoundsFunctor>
  static ReturnType evaluatePDFCos(
                      const XIndepType& x_indep_value,
                      const YIndepType& y_indep_value,
                      const YBoundsFunctor& min_y_indep_functor,
                      const YBoundsFunctor& max_y_indep_functor,
                      const EvaluationMethod& evaluate,
                      const YZIterator& lower_bin_boundary,
                      const YZIterator& upper_bin_boundary,
                      const double fuzzy_boundary_tol = 1e-3,
                      const double rel_error_tol = 1e-7,
                      const double error_tol = 1e-15,
                      unsigned max_number_of_iterations = 500u );

  //! Evaluate the PDF between bin boundaries using the desired evaluation method
  template<typename BaseUnivariateDistributionType,
           typename XIndepType,
           typename YIndepType,
           typename ReturnType,
           typename YZIterator,
           typename EvaluationMethod,
           typename YBoundsFunctor>
  static ReturnType evaluatePDF(
              const XIndepType& x_indep_value,
              const YIndepType& y_indep_value,
              const YBoundsFunctor& min_y_indep_functor,
              const YBoundsFunctor& max_y_indep_functor,
              const EvaluationMethod& evaluate,
              const YZIterator& lower_bin_boundary,
              const YZIterator& upper_bin_boundary,
              const double fuzzy_boundary_tol = 1e-3,
              const double rel_error_tol = 1e-7,
              const double error_tol = 1e-15,
              unsigned max_number_of_iterations = 500u );

  //! Evaluate the CDF between bin boundaries using the desired evaluation method
  template<typename BaseUnivariateDistributionType,
           typename XIndepType,
           typename YIndepType,
           typename YZIterator,
           typename EvaluationMethod,
           typename YBoundsFunctor>
  static double evaluateCDFCos(
              const XIndepType& x_indep_value,
              const YIndepType& y_indep_value,
              const YBoundsFunctor& min_y_indep_functor,
              const YBoundsFunctor& max_y_indep_functor,
              const EvaluationMethod& evaluate,
              const YZIterator& lower_bin_boundary,
              const YZIterator& upper_bin_boundary,
              const double fuzzy_boundary_tol = 1e-3,
              const double rel_error_tol = 1e-7,
              const double error_tol = 1e-15,
              unsigned max_number_of_iterations = 500u );

  //! Evaluate the CDF between bin boundaries using the desired evaluation method
  template<typename BaseUnivariateDistributionType,
           typename XIndepType,
           typename YIndepType,
           typename YZIterator,
           typename EvaluationMethod,
           typename YBoundsFunctor>
  static double evaluateCDF(
              const XIndepType& x_indep_value,
              const YIndepType& y_indep_value,
              const YBoundsFunctor& min_y_indep_functor,
              const YBoundsFunctor& max_y_indep_functor,
              const EvaluationMethod& evaluate,
              const YZIterator& lower_bin_boundary,
              const YZIterator& upper_bin_boundary,
              const double fuzzy_boundary_tol = 1e-3,
              const double rel_error_tol = 1e-7,
              const double error_tol = 1e-15,
              unsigned max_number_of_iterations = 500u );

  //! Sample between bin boundaries using the desired sampling functor
  template<typename XIndepType,
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
  template<typename XIndepType,
           typename YIndepType,
           typename YZIterator,
           typename SampleFunctor>
  static YIndepType sampleCos( const SampleFunctor& sample_functor,
                               const XIndepType& x_indep_value,
                               const YZIterator& lower_bin_boundary,
                               const YZIterator& upper_bin_boundary );

  //! Sample between bin boundaries using the desired subrange sampling functor
  template<typename XIndepType,
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
  template<typename XIndepType,
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
  template<typename XIndepType,
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

  //! Sample the bin boundary that will be used for statistical sampling
  template<typename XIndepType,
           typename YZIterator>
  static YZIterator sampleBinBoundary(
    const XIndepType& x_indep_value,
    const YZIterator& lower_bin_boundary,
    const YZIterator& upper_bin_boundary );
};

/*! \brief Policy struct for evaluting and sampling 2D tables. A cumulative
 * points interpolation method is used in evaluating the distribution and the
 * cumulative points statistical method in sampling the distribution.
 */
template<typename _TwoDInterpPolicy>
struct CumulativePoints
{
  //! The two-dimensional interpolation policy
  typedef _TwoDInterpPolicy TwoDInterpPolicy;

  //! Calculate the Y independent lower bound between bin boundaries
  template<typename YIndepType,
           typename XIndepType,
           typename YZIterator>
  static YIndepType calculateLowerBound(
                      const XIndepType& x_indep_value,
                      const YZIterator& lower_bin_boundary,
                      const YZIterator& upper_bin_boundary );

  //! Calculate the Y independent upper bound between bin boundaries
  template<typename TwoDInterpPolicy,
           typename YIndepType,
           typename XIndepType,
           typename YZIterator>
  static YIndepType calculateUpperBound(
                      const XIndepType& x_indep_value,
                      const YZIterator& lower_bin_boundary,
                      const YZIterator& upper_bin_boundary );

  //! Evaluate the PDF between bin boundaries using the desired evaluation method
  template<typename BaseUnivariateDistributionType,
           typename XIndepType,
           typename YIndepType,
           typename ReturnType,
           typename YZIterator,
           typename EvaluationMethod,
           typename YBoundsFunctor>
  static ReturnType evaluatePDFCos(
                      const XIndepType& x_indep_value,
                      const YIndepType& y_indep_value,
                      const YBoundsFunctor& min_y_indep_functor,
                      const YBoundsFunctor& max_y_indep_functor,
                      const EvaluationMethod& evaluate,
                      const YZIterator& lower_bin_boundary,
                      const YZIterator& upper_bin_boundary,
                      const double fuzzy_boundary_tol = 1e-3,
                      const double rel_error_tol = 1e-7,
                      const double error_tol = 1e-15,
                      unsigned max_number_of_iterations = 500u );

  //! Evaluate the PDF between bin boundaries using the desired evaluation method
  template<typename BaseUnivariateDistributionType,
           typename XIndepType,
           typename YIndepType,
           typename ReturnType,
           typename YZIterator,
           typename EvaluationMethod,
           typename YBoundsFunctor>
  static ReturnType evaluatePDF(
              const XIndepType& x_indep_value,
              const YIndepType& y_indep_value,
              const YBoundsFunctor& min_y_indep_functor,
              const YBoundsFunctor& max_y_indep_functor,
              const EvaluationMethod& evaluate,
              const YZIterator& lower_bin_boundary,
              const YZIterator& upper_bin_boundary,
              const double fuzzy_boundary_tol = 1e-3,
              const double rel_error_tol = 1e-7,
              const double error_tol = 1e-15,
              unsigned max_number_of_iterations = 500u );

  //! Evaluate the CDF between bin boundaries using the desired evaluation method
  template<typename BaseUnivariateDistributionType,
           typename XIndepType,
           typename YIndepType,
           typename YZIterator,
           typename EvaluationMethod,
           typename YBoundsFunctor>
  static double evaluateCDFCos(
              const XIndepType& x_indep_value,
              const YIndepType& y_indep_value,
              const YBoundsFunctor& min_y_indep_functor,
              const YBoundsFunctor& max_y_indep_functor,
              const EvaluationMethod& evaluate,
              const YZIterator& lower_bin_boundary,
              const YZIterator& upper_bin_boundary,
              const double fuzzy_boundary_tol = 1e-3,
              const double rel_error_tol = 1e-7,
              const double error_tol = 1e-15,
              unsigned max_number_of_iterations = 500u );

  //! Evaluate the CDF between bin boundaries using the desired evaluation method
  template<typename BaseUnivariateDistributionType,
           typename XIndepType,
           typename YIndepType,
           typename YZIterator,
           typename EvaluationMethod,
           typename YBoundsFunctor>
  static double evaluateCDF(
              const XIndepType& x_indep_value,
              const YIndepType& y_indep_value,
              const YBoundsFunctor& min_y_indep_functor,
              const YBoundsFunctor& max_y_indep_functor,
              const EvaluationMethod& evaluate,
              const YZIterator& lower_bin_boundary,
              const YZIterator& upper_bin_boundary,
              const double fuzzy_boundary_tol = 1e-3,
              const double rel_error_tol = 1e-7,
              const double error_tol = 1e-15,
              unsigned max_number_of_iterations = 500u );

  //! Sample between bin boundaries using the desired sampling functor
  template<typename XIndepType,
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
  template<typename XIndepType,
           typename YIndepType,
           typename YZIterator,
           typename SampleFunctor>
  static YIndepType sampleCos( const SampleFunctor& sample_functor,
                               const XIndepType& x_indep_value,
                               const YZIterator& lower_bin_boundary,
                               const YZIterator& upper_bin_boundary );

  //! Sample between bin boundaries using the desired subrange sampling functor
  template<typename XIndepType,
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
  template<typename XIndepType,
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
  template<typename XIndepType,
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

  //! Sample the bin boundary that will be used for statistical sampling
  template<typename XIndepType,
           typename YZIterator>
  static YZIterator sampleBinBoundary(
    const XIndepType& x_indep_value,
    const YZIterator& lower_bin_boundary,
    const YZIterator& upper_bin_boundary );
};

/*! \brief Policy struct for evaluting and sampling 2D tables. A correlated
 * sampling method is used in sampling the distribution. The correlated sampling
 * routine is equivalent to interpolating by corresponding energies as the
 * number of bins goes to infinity. Evaluating the PDF and CDF requires using an
 * iterative method of estimating the CDF and comparing it to the sampling
 * routine.
 */
template<typename _TwoDInterpPolicy>
struct Correlated
{
  //! The two-dimensional interpolation policy
  typedef _TwoDInterpPolicy TwoDInterpPolicy;

  //! Calculate the Y independent lower bound between bin boundaries
  template<typename YIndepType,
           typename XIndepType,
           typename YZIterator>
  static YIndepType calculateLowerBound(
                      const XIndepType& x_indep_value,
                      const YZIterator& lower_bin_boundary,
                      const YZIterator& upper_bin_boundary );

  //! Calculate the Y independent upper bound between bin boundaries
  template<typename YIndepType,
           typename XIndepType,
           typename YZIterator>
  static YIndepType calculateUpperBound(
                      const XIndepType& x_indep_value,
                      const YZIterator& lower_bin_boundary,
                      const YZIterator& upper_bin_boundary );

  //! Evaluate the PDF between bin boundaries using the desired evaluation method
  template<typename BaseUnivariateDistributionType,
           typename XIndepType,
           typename YIndepType,
           typename ReturnType,
           typename YZIterator,
           typename EvaluationMethod,
           typename YBoundsFunctor>
  static ReturnType evaluatePDFCos(
                      const XIndepType& x_indep_value,
                      const YIndepType& y_indep_value,
                      const YBoundsFunctor& min_y_indep_functor,
                      const YBoundsFunctor& max_y_indep_functor,
                      const EvaluationMethod& evaluate,
                      const YZIterator& lower_bin_boundary,
                      const YZIterator& upper_bin_boundary,
                      const double fuzzy_boundary_tol = 1e-3,
                      const double rel_error_tol = 1e-7,
                      const double error_tol = 1e-15,
                      unsigned max_number_of_iterations = 500u );

  //! Evaluate the PDF between bin boundaries using the desired evaluation method
  template<typename BaseUnivariateDistributionType,
           typename XIndepType,
           typename YIndepType,
           typename ReturnType,
           typename YZIterator,
           typename EvaluationMethod,
           typename YBoundsFunctor>
  static ReturnType evaluatePDF(
              const XIndepType& x_indep_value,
              const YIndepType& y_indep_value,
              const YBoundsFunctor& min_y_indep_functor,
              const YBoundsFunctor& max_y_indep_functor,
              const EvaluationMethod& evaluate,
              const YZIterator& lower_bin_boundary,
              const YZIterator& upper_bin_boundary,
              const double fuzzy_boundary_tol = 1e-3,
              const double rel_error_tol = 1e-7,
              const double error_tol = 1e-15,
              unsigned max_number_of_iterations = 500u );

  //! Evaluate the CDF between bin boundaries using the desired evaluation method
  template<typename BaseUnivariateDistributionType,
           typename XIndepType,
           typename YIndepType,
           typename YZIterator,
           typename EvaluationMethod,
           typename YBoundsFunctor>
  static double evaluateCDFCos(
              const XIndepType& x_indep_value,
              const YIndepType& y_indep_value,
              const YBoundsFunctor& min_y_indep_functor,
              const YBoundsFunctor& max_y_indep_functor,
              const EvaluationMethod& evaluate,
              const YZIterator& lower_bin_boundary,
              const YZIterator& upper_bin_boundary,
              const double fuzzy_boundary_tol = 1e-3,
              const double rel_error_tol = 1e-7,
              const double error_tol = 1e-15,
              unsigned max_number_of_iterations = 500u );

  //! Evaluate the CDF between bin boundaries using the desired evaluation method
  template<typename BaseUnivariateDistributionType,
           typename XIndepType,
           typename YIndepType,
           typename YZIterator,
           typename EvaluationMethod,
           typename YBoundsFunctor>
  static double evaluateCDF(
              const XIndepType& x_indep_value,
              const YIndepType& y_indep_value,
              const YBoundsFunctor& min_y_indep_functor,
              const YBoundsFunctor& max_y_indep_functor,
              const EvaluationMethod& evaluate,
              const YZIterator& lower_bin_boundary,
              const YZIterator& upper_bin_boundary,
              const double fuzzy_boundary_tol = 1e-3,
              const double rel_error_tol = 1e-7,
              const double error_tol = 1e-15,
              unsigned max_number_of_iterations = 500u );

  //! Sample between bin boundaries using the desired sampling functor
  template<typename XIndepType,
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
  template<typename XIndepType,
           typename YIndepType,
           typename YZIterator,
           typename SampleFunctor>
  static YIndepType sampleCos( const SampleFunctor& sample_functor,
                               const XIndepType& x_indep_value,
                               const YZIterator& lower_bin_boundary,
                               const YZIterator& upper_bin_boundary );

  //! Sample between bin boundaries using the desired subrange sampling functor
  template<typename XIndepType,
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
  template<typename XIndepType,
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
  template<typename XIndepType,
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

/*! \brief Policy struct for evaluting and sampling 2D tables. A unit-base
 * correlated sampling method is used in sampling the distribution. Evaluating
 * the PDF and CDF requires using an iterative method of estimating the CDF and
 * comparing it to the sampling routine.
 */
template<typename _TwoDInterpPolicy>
struct UnitBaseCorrelated
{
  //! The two-dimensional interpolation policy
  typedef _TwoDInterpPolicy TwoDInterpPolicy;

  //! Calculate the Y independent lower bound between bin boundaries
  template<typename YIndepType,
           typename XIndepType,
           typename YZIterator>
  static YIndepType calculateLowerBound(
                      const XIndepType& x_indep_value,
                      const YZIterator& lower_bin_boundary,
                      const YZIterator& upper_bin_boundary );

  //! Calculate the Y independent upper bound between bin boundaries
  template<typename YIndepType,
           typename XIndepType,
           typename YZIterator>
  static YIndepType calculateUpperBound(
                      const XIndepType& x_indep_value,
                      const YZIterator& lower_bin_boundary,
                      const YZIterator& upper_bin_boundary );

  //! Evaluate the PDF between bin boundaries using the desired evaluation method
  template<typename BaseUnivariateDistributionType,
           typename XIndepType,
           typename YIndepType,
           typename ReturnType,
           typename YZIterator,
           typename EvaluationMethod,
           typename YBoundsFunctor>
  static ReturnType evaluatePDFCos(
                      const XIndepType& x_indep_value,
                      const YIndepType& y_indep_value,
                      const YBoundsFunctor& min_y_indep_functor,
                      const YBoundsFunctor& max_y_indep_functor,
                      const EvaluationMethod& evaluate,
                      const YZIterator& lower_bin_boundary,
                      const YZIterator& upper_bin_boundary,
                      const double fuzzy_boundary_tol = 1e-3,
                      const double rel_error_tol = 1e-7,
                      const double error_tol = 1e-15,
                      unsigned max_number_of_iterations = 500u );

  //! Evaluate the PDF between bin boundaries using the desired evaluation method
  template<typename BaseUnivariateDistributionType,
           typename XIndepType,
           typename YIndepType,
           typename ReturnType,
           typename YZIterator,
           typename EvaluationMethod,
           typename YBoundsFunctor>
  static ReturnType evaluatePDF(
              const XIndepType& x_indep_value,
              const YIndepType& y_indep_value,
              const YBoundsFunctor& min_y_indep_functor,
              const YBoundsFunctor& max_y_indep_functor,
              const EvaluationMethod& evaluate,
              const YZIterator& lower_bin_boundary,
              const YZIterator& upper_bin_boundary,
              const double fuzzy_boundary_tol = 1e-3,
              const double rel_error_tol = 1e-7,
              const double error_tol = 1e-15,
              unsigned max_number_of_iterations = 500u );

  //! Evaluate the CDF between bin boundaries using the desired evaluation method
  template<typename BaseUnivariateDistributionType,
           typename XIndepType,
           typename YIndepType,
           typename YZIterator,
           typename EvaluationMethod,
           typename YBoundsFunctor>
  static double evaluateCDFCos(
              const XIndepType& x_indep_value,
              const YIndepType& y_indep_value,
              const YBoundsFunctor& min_y_indep_functor,
              const YBoundsFunctor& max_y_indep_functor,
              const EvaluationMethod& evaluate,
              const YZIterator& lower_bin_boundary,
              const YZIterator& upper_bin_boundary,
              const double fuzzy_boundary_tol = 1e-3,
              const double rel_error_tol = 1e-7,
              const double error_tol = 1e-15,
              unsigned max_number_of_iterations = 500u );

  //! Evaluate the CDF between bin boundaries using the desired evaluation method
  template<typename BaseUnivariateDistributionType,
           typename XIndepType,
           typename YIndepType,
           typename YZIterator,
           typename EvaluationMethod,
           typename YBoundsFunctor>
  static double evaluateCDF(
              const XIndepType& x_indep_value,
              const YIndepType& y_indep_value,
              const YBoundsFunctor& min_y_indep_functor,
              const YBoundsFunctor& max_y_indep_functor,
              const EvaluationMethod& evaluate,
              const YZIterator& lower_bin_boundary,
              const YZIterator& upper_bin_boundary,
              const double fuzzy_boundary_tol = 1e-3,
              const double rel_error_tol = 1e-7,
              const double error_tol = 1e-15,
              unsigned max_number_of_iterations = 500u );

  //! Sample between bin boundaries using the desired sampling functor
  template<typename XIndepType,
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
  template<typename XIndepType,
           typename YIndepType,
           typename YZIterator,
           typename SampleFunctor>
  static YIndepType sampleCos( const SampleFunctor& sample_functor,
                               const XIndepType& x_indep_value,
                               const YZIterator& lower_bin_boundary,
                               const YZIterator& upper_bin_boundary );

  //! Sample between bin boundaries using the desired subrange sampling functor
  template<typename XIndepType,
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
  template<typename XIndepType,
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
  template<typename XIndepType,
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

/*! Partial specialization of Utility::TypeNameTraits for Utility::Direct
 * \ingroup type_name_traits
 */
#define TWO_D_GRID_POLICY_TYPE_NAME_TRAITS_QUICK_DECL( GridPolicy ) \
  template<typename _TwoDInterpPolicy>                              \
  struct TypeNameTraits<GridPolicy<_TwoDInterpPolicy> >             \
  {                                                                 \
    typedef std::true_type IsSpecialized;                           \
                                                                    \
    static inline std::string name()                                \
    {                                                               \
      return std::string(#GridPolicy) + "<" +                       \
        Utility::typeName<_TwoDInterpPolicy>() + ">";               \
    }                                                               \
  }

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "Utility_TwoDGridPolicy_def.hpp"

//---------------------------------------------------------------------------//

#endif // end UTILITY_TWO_D_GRID_POLICY_HPP

//---------------------------------------------------------------------------//
// end Utility_TwoDGridPolicy.hpp
//---------------------------------------------------------------------------//
