//---------------------------------------------------------------------------//
//!
//! \file   Utility_TwoDGridPolicy_def.hpp
//! \author Luke Kersting
//! \brief  Policy struct declarations for sampling on 2D grids
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_TWO_D_GRID_POLICY_DEF_HPP
#define UTILITY_TWO_D_GRID_POLICY_DEF_HPP

// Std Lib Includes
#include <functional>

// FRENSIE Includes
#include "Utility_SortAlgorithms.hpp"
#include "Utility_SearchAlgorithms.hpp"
#include "Utility_DesignByContract.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_TabularUnivariateDistribution.hpp"

namespace Utility{

// Calculate the Y independent lower bound between bin boundaries
/*! \details The lower bound will be the minimum of the two boundary
 * lower bounds.
 */
template<typename _TwoDInterpPolicy>
template<typename YIndepType,
         typename XIndepType,
         typename YZIterator>
auto Direct<_TwoDInterpPolicy>::calculateLowerBound(
                      const XIndepType& x_indep_value,
                      const YZIterator& lower_bin_boundary,
                      const YZIterator& upper_bin_boundary ) -> YIndepType
{
  if ( x_indep_value == lower_bin_boundary->first )
  {
    return lower_bin_boundary->second->getLowerBoundOfIndepVar();
  }
  else if ( x_indep_value == upper_bin_boundary->first )
  {
    return upper_bin_boundary->second->getLowerBoundOfIndepVar();
  }
  else
  {
    return std::min( lower_bin_boundary->second->getLowerBoundOfIndepVar(),
                     upper_bin_boundary->second->getLowerBoundOfIndepVar() );
  }
}

// Calculate the Y independent upper bound between bin boundaries
/*! \details The upper bound will be the maximum of the two boundary
 * upper bounds.
 */
template<typename _TwoDInterpPolicy>
template<typename YIndepType,
         typename XIndepType,
         typename YZIterator>
auto Direct<_TwoDInterpPolicy>::calculateUpperBound(
                      const XIndepType& x_indep_value,
                      const YZIterator& lower_bin_boundary,
                      const YZIterator& upper_bin_boundary ) -> YIndepType
{
  if ( x_indep_value == lower_bin_boundary->first )
  {
    return lower_bin_boundary->second->getUpperBoundOfIndepVar();
  }
  else if ( x_indep_value == upper_bin_boundary->first )
  {
    return upper_bin_boundary->second->getUpperBoundOfIndepVar();
  }
  else
  {
    return std::max( lower_bin_boundary->second->getUpperBoundOfIndepVar(),
                     upper_bin_boundary->second->getUpperBoundOfIndepVar() );
  }
}

// Evaluate the PDF between bin boundaries using the desired evaluation method
//! \details The EvaluationMethod must evalute using a Cosine variable.
template<typename _TwoDInterpPolicy>
template<typename BaseUnivariateDistributionType,
         typename XIndepType,
         typename YIndepType,
         typename ReturnType,
         typename YZIterator,
         typename EvaluationMethod,
         typename YBoundsFunctor>
ReturnType Direct<_TwoDInterpPolicy>::evaluatePDFCos(
                                  const XIndepType& x_indep_value,
                                  const YIndepType& y_indep_value,
                                  const YBoundsFunctor& min_y_indep_functor,
                                  const YBoundsFunctor& max_y_indep_functor,
                                  const EvaluationMethod& evaluate,
                                  const YZIterator& lower_bin_boundary,
                                  const YZIterator& upper_bin_boundary,
                                  const double fuzzy_boundary_tol,
                                  const double rel_error_tol,
                                  const double error_tol,
                                  unsigned max_number_of_iterations )
{
  return Direct<TwoDInterpPolicy>::evaluatePDF<BaseUnivariateDistributionType,
                                               XIndepType, YIndepType,
                                               ReturnType, YZIterator, EvaluationMethod,
                                               YBoundsFunctor>(
                                    x_indep_value,
                                    y_indep_value,
                                    min_y_indep_functor,
                                    max_y_indep_functor,
                                    evaluate,
                                    lower_bin_boundary,
                                    upper_bin_boundary,
                                    fuzzy_boundary_tol,
                                    rel_error_tol,
                                    error_tol,
                                    max_number_of_iterations );
}

// Evaluate the PDF between bin boundaries using the desired evaluation method
/*! \details Direct interpolation is used to evaluate the probability density
 *  function.
 */
template<typename _TwoDInterpPolicy>
template<typename BaseUnivariateDistributionType,
         typename XIndepType,
         typename YIndepType,
         typename ReturnType,
         typename YZIterator,
         typename EvaluationMethod,
         typename YBoundsFunctor>
ReturnType Direct<_TwoDInterpPolicy>::evaluatePDF(
                                  const XIndepType& x_indep_value,
                                  const YIndepType& y_indep_value,
                                  const YBoundsFunctor& min_y_indep_functor,
                                  const YBoundsFunctor& max_y_indep_functor,
                                  const EvaluationMethod& evaluate,
                                  const YZIterator& lower_bin_boundary,
                                  const YZIterator& upper_bin_boundary,
                                  const double fuzzy_boundary_tol,
                                  const double rel_error_tol,
                                  const double error_tol,
                                  unsigned max_number_of_iterations )
{
  if( lower_bin_boundary->first == x_indep_value )
  {
    return ((*lower_bin_boundary->second).*evaluate)(y_indep_value);
  }
  else if( upper_bin_boundary->first == x_indep_value )
  {
    return ((*upper_bin_boundary->second).*evaluate)(y_indep_value);
  }
  else
  {
    // Get the evaluation at the lower and upper bin boundaries
    ReturnType bin_eval_0 = ((*lower_bin_boundary->second).*evaluate)(y_indep_value);
    ReturnType bin_eval_1 = ((*upper_bin_boundary->second).*evaluate)(y_indep_value);

    if ( getRawQuantity( bin_eval_0*bin_eval_1 ) > 0.0 )
    {
      // Return the interpolated evaluation
      return TwoDInterpPolicy::ZXInterpPolicy::interpolate(
              lower_bin_boundary->first,
              upper_bin_boundary->first,
              x_indep_value,
              bin_eval_0,
              bin_eval_1 );
    }
    else
    {
      // Return the interpolated evaluation using LinLin interpolation
      return LinLin::interpolate(
              lower_bin_boundary->first,
              upper_bin_boundary->first,
              x_indep_value,
              bin_eval_0,
              bin_eval_1 );
    }
  }
}

// Evaluate the CDF between bin boundaries using the desired evaluation method
//! \details The EvaluationMethod must evalute using a Cosine variable.
template<typename _TwoDInterpPolicy>
template<typename BaseUnivariateDistributionType,
         typename XIndepType,
         typename YIndepType,
         typename YZIterator,
         typename EvaluationMethod,
         typename YBoundsFunctor>
double Direct<_TwoDInterpPolicy>::evaluateCDFCos(
                                  const XIndepType& x_indep_value,
                                  const YIndepType& y_indep_value,
                                  const YBoundsFunctor& min_y_indep_functor,
                                  const YBoundsFunctor& max_y_indep_functor,
                                  const EvaluationMethod& evaluate,
                                  const YZIterator& lower_bin_boundary,
                                  const YZIterator& upper_bin_boundary,
                                  const double fuzzy_boundary_tol,
                                  const double rel_error_tol,
                                  const double error_tol,
                                  unsigned max_number_of_iterations )
{
  return Direct<TwoDInterpPolicy>::evaluateCDF<BaseUnivariateDistributionType,
                                               XIndepType, YIndepType, YZIterator,
                                               EvaluationMethod, YBoundsFunctor>(
                                              x_indep_value,
                                              y_indep_value,
                                              min_y_indep_functor,
                                              max_y_indep_functor,
                                              evaluate,
                                              lower_bin_boundary,
                                              upper_bin_boundary,
                                              fuzzy_boundary_tol,
                                              rel_error_tol,
                                              error_tol,
                                              max_number_of_iterations );
}

// Evaluate the CDF between bin boundaries using the desired evaluation method
/*! \details The CDF is evaluated from a direct interpolation of the PDF.
 */
template<typename _TwoDInterpPolicy>
template<typename BaseUnivariateDistributionType,
         typename XIndepType,
         typename YIndepType,
         typename YZIterator,
         typename EvaluationMethod,
         typename YBoundsFunctor>
double Direct<_TwoDInterpPolicy>::evaluateCDF(
                                  const XIndepType& x_indep_value,
                                  const YIndepType& y_indep_value,
                                  const YBoundsFunctor& min_y_indep_functor,
                                  const YBoundsFunctor& max_y_indep_functor,
                                  const EvaluationMethod& evaluate,
                                  const YZIterator& lower_bin_boundary,
                                  const YZIterator& upper_bin_boundary,
                                  const double fuzzy_boundary_tol,
                                  const double rel_error_tol,
                                  const double error_tol,
                                  unsigned max_number_of_iterations )
{
  return Direct<TwoDInterpPolicy>::evaluatePDF<BaseUnivariateDistributionType,
                                               XIndepType, YIndepType,
                                               double, YZIterator, EvaluationMethod,
                                               YBoundsFunctor>(
                                    x_indep_value,
                                    y_indep_value,
                                    min_y_indep_functor,
                                    max_y_indep_functor,
                                    evaluate,
                                    lower_bin_boundary,
                                    upper_bin_boundary,
                                    fuzzy_boundary_tol,
                                    rel_error_tol,
                                    error_tol,
                                    max_number_of_iterations );
}

// Sample between bin boundaries using the desired sampling functor
/*! \details A direct statistical sampling procedure is used which samples
 * from one of the distributions on the bin boundaries.
 * Statistical sampling does not sample the true intermediate distribution and
 * will not match the direct evaluated PDF and CDF distributions. The
 * expected value of a sample, however, will be a sample from the true
 * distribution.
 */
template<typename _TwoDInterpPolicy>
template<typename XIndepType,
         typename YIndepType,
         typename YZIterator,
         typename SampleFunctor,
         typename YBoundsFunctor>
YIndepType Direct<_TwoDInterpPolicy>::sample(
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

  return Direct<TwoDInterpPolicy>::sampleDetailed<XIndepType,YIndepType,YZIterator,SampleFunctor>(
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
/* \details The SampleFunctor must sample a Cosine variable.
 * A direct statistical sampling procedure is used which samples
 * from one of the distributions on the bin boundaries.
 * Statistical sampling does not sample the true intermediate distribution and
 * will not match the direct evaluated PDF and CDF distributions. The
 * expected value of a sample, however, will be a sample from the true
 * distribution.
 */
template<typename _TwoDInterpPolicy>
template<typename XIndepType,
         typename YIndepType,
         typename YZIterator,
         typename SampleFunctor>
YIndepType Direct<_TwoDInterpPolicy>::sampleCos(
                                   const SampleFunctor& sample_functor,
                                   const XIndepType& x_indep_value,
                                   const YZIterator& lower_bin_boundary,
                                   const YZIterator& upper_bin_boundary )
{
  // Dummy variables
  YIndepType dummy_raw_sample;
  YZIterator dummy_sampled_bin_boundary;

  return Direct<TwoDInterpPolicy>::sampleCosDetailed<XIndepType,YIndepType,YZIterator,SampleFunctor>(
            sample_functor,
            x_indep_value,
            lower_bin_boundary,
            upper_bin_boundary,
            dummy_sampled_bin_boundary,
            dummy_raw_sample );
}

// Sample between bin boundaries using the desired subrange sampling functor
/* \details The SampleFunctor must be of the form that it takes a subrange
 * sampling function from a UnivariateDistribution and the max indep variable.
 * A direct statistical sampling procedure is used which samples
 * from one of the distributions on the bin boundaries.
 * Statistical sampling does not sample the true intermediate distribution and
 * will not match the direct evaluated PDF and CDF distributions. The
 * expected value of a sample, however, will be a sample from the true
 * distribution.
 */
template<typename _TwoDInterpPolicy>
template<typename XIndepType,
         typename YIndepType,
         typename YZIterator,
         typename SampleFunctor,
         typename YBoundsFunctor>
YIndepType Direct<_TwoDInterpPolicy>::sampleInSubrange(
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
    Direct<TwoDInterpPolicy>::sampleBinBoundary<XIndepType,YZIterator>(
                              x_indep_value,
                              lower_bin_boundary,
                              upper_bin_boundary );

  // Make sure subrange max value is below the max value of the sampled bin
  YIndepType max_y_indep_value_bin_bound =
        std::min( subrange_max_y_indep_value,
                  sampled_bin_boundary->second->getUpperBoundOfIndepVar() );

  // Sample in the bin's subrange
  YIndepType raw_sample =
    subrange_sample_functor( *sampled_bin_boundary->second,
                              max_y_indep_value_bin_bound );

  return raw_sample;
}

// Sample between bin boundaries using the desired sampling functor
/*! \details A direct statistical sampling procedure is used which samples
 * from one of the distributions on the bin boundaries.
 * Statistical sampling does not sample the true intermediate distribution and
 * will not match the direct evaluated PDF and CDF distributions. The
 * expected value of a sample, however, will be a sample from the true
 * distribution.
 */
template<typename _TwoDInterpPolicy>
template<typename XIndepType,
         typename YIndepType,
         typename YZIterator,
         typename SampleFunctor,
         typename YBoundsFunctor>
YIndepType Direct<_TwoDInterpPolicy>::sampleDetailed(
            const SampleFunctor& sample_functor,
            const YBoundsFunctor& min_y_indep_functor,
            const YBoundsFunctor& max_y_indep_functor,
            const XIndepType& x_indep_value,
            const YZIterator& lower_bin_boundary,
            const YZIterator& upper_bin_boundary,
            YZIterator& sampled_bin_boundary,
            YIndepType& raw_sample )
{
  // Get the sampled bin boundary
  sampled_bin_boundary =
    Direct<TwoDInterpPolicy>::sampleBinBoundary<XIndepType,YZIterator>(
                            x_indep_value,
                            lower_bin_boundary,
                            upper_bin_boundary );

  // Create the raw sample
  raw_sample = sample_functor( *sampled_bin_boundary->second );

  // Note: This is a stochastic procedure. The intermediate distribution that
  //       has been sampled is not the true distribution. The expected value
  //       of a sample will be a sample from the true distribution though.
  return raw_sample;
}

// Sample between bin boundaries using the desired sampling functor
template<typename _TwoDInterpPolicy>
template<typename XIndepType,
         typename YIndepType,
         typename YZIterator,
         typename SampleFunctor>
YIndepType Direct<_TwoDInterpPolicy>::sampleCosDetailed(
            const SampleFunctor& sample_functor,
            const XIndepType& x_indep_value,
            const YZIterator& lower_bin_boundary,
            const YZIterator& upper_bin_boundary,
            YZIterator& sampled_bin_boundary,
            YIndepType& raw_sample )
{

  std::function<YIndepType(const XIndepType)> dummy_functor =
    [](XIndepType x){return QuantityTraits<YIndepType>::zero();};

  return Direct<TwoDInterpPolicy>::sampleDetailed<XIndepType, YIndepType, YZIterator, SampleFunctor>(
              sample_functor,
              dummy_functor,
              dummy_functor,
              x_indep_value,
              lower_bin_boundary,
              upper_bin_boundary,
              sampled_bin_boundary,
              raw_sample );
}

// Sample the bin boundary that will be used for statistical sampling
/*! \details This method will throw an exception if the primary independent
 * value is outside of the primary grid limits and the primary grid has not
 * been extended.
 */
template<typename _TwoDInterpPolicy>
template<typename XIndepType,
         typename YZIterator>
YZIterator Direct<_TwoDInterpPolicy>::sampleBinBoundary(
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
template<typename _TwoDInterpPolicy>
inline const std::string Direct<_TwoDInterpPolicy>::name()
{
  return "Direct";
}

// Calculate the Y independent lower bound between bin boundaries
template<typename _TwoDInterpPolicy>
template<typename YIndepType,
         typename XIndepType,
         typename YZIterator>
auto UnitBase<_TwoDInterpPolicy>::calculateLowerBound(
                      const XIndepType& x_indep_value,
                      const YZIterator& lower_bin_boundary,
                      const YZIterator& upper_bin_boundary ) -> YIndepType
{
  return TwoDInterpPolicy::calculateIntermediateGridLimit(
                       lower_bin_boundary->first,
                       upper_bin_boundary->first,
                       x_indep_value,
                       lower_bin_boundary->second->getLowerBoundOfIndepVar(),
                       upper_bin_boundary->second->getLowerBoundOfIndepVar() );
}

// Calculate the Y independent upper bound between bin boundaries
template<typename _TwoDInterpPolicy>
template<typename YIndepType,
         typename XIndepType,
         typename YZIterator>
auto UnitBase<_TwoDInterpPolicy>::calculateUpperBound(
                      const XIndepType& x_indep_value,
                      const YZIterator& lower_bin_boundary,
                      const YZIterator& upper_bin_boundary ) -> YIndepType
{
  return TwoDInterpPolicy::calculateIntermediateGridLimit(
                       lower_bin_boundary->first,
                       upper_bin_boundary->first,
                       x_indep_value,
                       lower_bin_boundary->second->getUpperBoundOfIndepVar(),
                       upper_bin_boundary->second->getUpperBoundOfIndepVar() );
}

// Evaluate the PDF between bin boundaries using the desired evaluation method
//! \details The EvaluationMethod must evalute using a Cosine variable.
template<typename _TwoDInterpPolicy>
template<typename BaseUnivariateDistributionType,
         typename XIndepType,
         typename YIndepType,
         typename ReturnType,
         typename YZIterator,
         typename EvaluationMethod,
         typename YBoundsFunctor>
ReturnType UnitBase<_TwoDInterpPolicy>::evaluatePDFCos(
                                  const XIndepType& x_indep_value,
                                  const YIndepType& y_indep_value,
                                  const YBoundsFunctor& min_y_indep_functor,
                                  const YBoundsFunctor& max_y_indep_functor,
                                  const EvaluationMethod& evaluate,
                                  const YZIterator& lower_bin_boundary,
                                  const YZIterator& upper_bin_boundary,
                                  const double fuzzy_boundary_tol,
                                  const double rel_error_tol,
                                  const double error_tol,
                                  unsigned max_number_of_iterations )
{
  return Direct<TwoDInterpPolicy>::template evaluatePDF<BaseUnivariateDistributionType,
                                                        XIndepType, YIndepType,
                                                        ReturnType, YZIterator,
                                                        EvaluationMethod,
                                                        YBoundsFunctor>(
                                    x_indep_value,
                                    y_indep_value,
                                    min_y_indep_functor,
                                    max_y_indep_functor,
                                    evaluate,
                                    lower_bin_boundary,
                                    upper_bin_boundary,
                                    fuzzy_boundary_tol,
                                    rel_error_tol,
                                    error_tol,
                                    max_number_of_iterations );
}

// Evaluate the PDF between bin boundaries using the desired evaluation method
/*! \details Unit-base interpolation is used to evaluate the probability density
 *  function.
 */
template<typename _TwoDInterpPolicy>
template<typename BaseUnivariateDistributionType,
         typename XIndepType,
         typename YIndepType,
         typename ReturnType,
         typename YZIterator,
         typename EvaluationMethod,
         typename YBoundsFunctor>
ReturnType UnitBase<_TwoDInterpPolicy>::evaluatePDF(
                                  const XIndepType& x_indep_value,
                                  const YIndepType& y_indep_value,
                                  const YBoundsFunctor& min_y_indep_functor,
                                  const YBoundsFunctor& max_y_indep_functor,
                                  const EvaluationMethod& evaluate,
                                  const YZIterator& lower_bin_boundary,
                                  const YZIterator& upper_bin_boundary,
                                  const double fuzzy_boundary_tol,
                                  const double rel_error_tol,
                                  const double error_tol,
                                  unsigned max_number_of_iterations )
{
  if( lower_bin_boundary->first == x_indep_value ||
      upper_bin_boundary->first == x_indep_value )
  {
    // Get the min and max y indep values
    YIndepType min_y_indep_value = min_y_indep_functor( x_indep_value );
    YIndepType max_y_indep_value = max_y_indep_functor( x_indep_value );

    // Calculate the intermediate y min with fuzzy tol
    YIndepType min_y_indep_value_with_tol =
     TwoDInterpPolicy::ZYInterpPolicy::calculateFuzzyLowerBound(
        min_y_indep_value, fuzzy_boundary_tol );

    // Calculate the intermediate y max with fuzzy tol
    YIndepType max_y_indep_value_with_tol =
      TwoDInterpPolicy::ZYInterpPolicy::calculateFuzzyUpperBound(
          max_y_indep_value, fuzzy_boundary_tol );

    // Check if the secondary indep value is in the intermediate grid
    if( y_indep_value >= min_y_indep_value_with_tol && y_indep_value <= max_y_indep_value_with_tol )
    {
      // Calculate the unit base independent variable
      typename QuantityTraits<YIndepType>::RawType eta;

      if( y_indep_value > min_y_indep_value && y_indep_value < max_y_indep_value )
      {
        typename QuantityTraits<YIndepType>::RawType
        intermediate_grid_length =
              TwoDInterpPolicy::ZYInterpPolicy::calculateUnitBaseGridLength(
                          min_y_indep_value,
                          max_y_indep_value );

        eta = TwoDInterpPolicy::ZYInterpPolicy::calculateUnitBaseIndepVar(
                      y_indep_value, min_y_indep_value, intermediate_grid_length );
      }
      else if( y_indep_value <= min_y_indep_value && y_indep_value >= min_y_indep_value_with_tol )
        eta = 0.0;
      else // y_indep_value >= max_y_indep_value && y_indep_value <= max_y_indep_value_with_tol
        eta = 1.0;

      typename QuantityTraits<YIndepType>::RawType grid_length;
      if( lower_bin_boundary->first == x_indep_value )
      {
        // Get the intermediate grid lengths for the indep value and the lower bin boundary
        typename QuantityTraits<YIndepType>::RawType grid_length_0 =
            TwoDInterpPolicy::ZYInterpPolicy::calculateUnitBaseGridLength(
                        lower_bin_boundary->second->getLowerBoundOfIndepVar(),
                        lower_bin_boundary->second->getUpperBoundOfIndepVar() );

        YIndepType norm_y_value = std::min(
          TwoDInterpPolicy::ZYInterpPolicy::calculateIndepVar(
              eta,
              lower_bin_boundary->second->getLowerBoundOfIndepVar(),
              grid_length_0 ),
                lower_bin_boundary->second->getUpperBoundOfIndepVar() );

        return ((*lower_bin_boundary->second).*evaluate)(norm_y_value);
      }
      else if( upper_bin_boundary->first == x_indep_value )
      {
        // Get the intermediate grid lengths for the indep value and the upper bin boundary
        typename QuantityTraits<YIndepType>::RawType grid_length_1 =
              TwoDInterpPolicy::ZYInterpPolicy::calculateUnitBaseGridLength(
                          upper_bin_boundary->second->getLowerBoundOfIndepVar(),
                          upper_bin_boundary->second->getUpperBoundOfIndepVar() );

        YIndepType norm_y_value = std::min(
          TwoDInterpPolicy::ZYInterpPolicy::calculateIndepVar(
              eta,
              upper_bin_boundary->second->getLowerBoundOfIndepVar(),
              grid_length_1 ),
                upper_bin_boundary->second->getUpperBoundOfIndepVar() );

        return ((*upper_bin_boundary->second).*evaluate)(norm_y_value);
      }
    }
    else
    {
      return QuantityTraits<ReturnType>::zero();
    }
  }
  else
  {
    // Create the grid evaluation functors
    std::function<ReturnType(const YIndepType)>
      evaluate_grid_0_functor =
      std::bind<ReturnType>( evaluate,
                            std::cref( *lower_bin_boundary->second ),
                            std::placeholders::_1 );

    std::function<ReturnType(const YIndepType)>
      evaluate_grid_1_functor =
      std::bind<ReturnType>( evaluate,
                            std::cref( *upper_bin_boundary->second ),
                            std::placeholders::_1 );

    return TwoDInterpPolicy::interpolateUnitBase(
                          lower_bin_boundary->first,
                          upper_bin_boundary->first,
                          x_indep_value,
                          y_indep_value,
                          min_y_indep_functor(x_indep_value),
                          max_y_indep_functor(x_indep_value),
                          lower_bin_boundary->second->getLowerBoundOfIndepVar(),
                          lower_bin_boundary->second->getUpperBoundOfIndepVar(),
                          upper_bin_boundary->second->getLowerBoundOfIndepVar(),
                          upper_bin_boundary->second->getUpperBoundOfIndepVar(),
                          evaluate_grid_0_functor,
                          evaluate_grid_1_functor,
                          QuantityTraits<ReturnType>::zero(),
                          QuantityTraits<ReturnType>::zero(),
                          fuzzy_boundary_tol );
  }
}

// Evaluate the CDF between bin boundaries using the desired evaluation method
//! \details The EvaluationMethod must evalute using a Cosine variable.
template<typename _TwoDInterpPolicy>
template<typename BaseUnivariateDistributionType,
         typename XIndepType,
         typename YIndepType,
         typename YZIterator,
         typename EvaluationMethod,
         typename YBoundsFunctor>
double UnitBase<_TwoDInterpPolicy>::evaluateCDFCos(
                                  const XIndepType& x_indep_value,
                                  const YIndepType& y_indep_value,
                                  const YBoundsFunctor& min_y_indep_functor,
                                  const YBoundsFunctor& max_y_indep_functor,
                                  const EvaluationMethod& evaluate,
                                  const YZIterator& lower_bin_boundary,
                                  const YZIterator& upper_bin_boundary,
                                  const double fuzzy_boundary_tol,
                                  const double rel_error_tol,
                                  const double error_tol,
                                  unsigned max_number_of_iterations )
{
  return Direct<TwoDInterpPolicy>::template evaluateCDF<BaseUnivariateDistributionType,
                                                        XIndepType, YIndepType, YZIterator,
                                                        EvaluationMethod, YBoundsFunctor>(
                                              x_indep_value,
                                              y_indep_value,
                                              min_y_indep_functor,
                                              max_y_indep_functor,
                                              evaluate,
                                              lower_bin_boundary,
                                              upper_bin_boundary,
                                              fuzzy_boundary_tol,
                                              rel_error_tol,
                                              error_tol,
                                              max_number_of_iterations );
}

// Evaluate the CDF between bin boundaries using the desired evaluation method
/*! \details The CDF is evaluated from a unit-base interpolation of the PDF.
 */
template<typename _TwoDInterpPolicy>
template<typename BaseUnivariateDistributionType,
         typename XIndepType,
         typename YIndepType,
         typename YZIterator,
         typename EvaluationMethod,
         typename YBoundsFunctor>
double UnitBase<_TwoDInterpPolicy>::evaluateCDF(
                                  const XIndepType& x_indep_value,
                                  const YIndepType& y_indep_value,
                                  const YBoundsFunctor& min_y_indep_functor,
                                  const YBoundsFunctor& max_y_indep_functor,
                                  const EvaluationMethod& evaluate,
                                  const YZIterator& lower_bin_boundary,
                                  const YZIterator& upper_bin_boundary,
                                  const double fuzzy_boundary_tol,
                                  const double rel_error_tol,
                                  const double error_tol,
                                  unsigned max_number_of_iterations )
{
  if( lower_bin_boundary->first == x_indep_value ||
      upper_bin_boundary->first == x_indep_value )
  {
    // Get the min and max y indep values
    YIndepType min_y_indep_value = min_y_indep_functor( x_indep_value );
    YIndepType max_y_indep_value = max_y_indep_functor( x_indep_value );

    // Calculate the intermediate y min with fuzzy tol
    YIndepType min_y_indep_value_with_tol =
     TwoDInterpPolicy::ZYInterpPolicy::calculateFuzzyLowerBound(
        min_y_indep_value, fuzzy_boundary_tol );

    // Calculate the intermediate y max with fuzzy tol
    YIndepType max_y_indep_value_with_tol =
      TwoDInterpPolicy::ZYInterpPolicy::calculateFuzzyUpperBound(
          max_y_indep_value, fuzzy_boundary_tol );

    // Check if the secondary indep value is in the intermediate grid
    if( y_indep_value >= min_y_indep_value_with_tol && y_indep_value <= max_y_indep_value_with_tol )
    {
      // Calculate the unit base independent variable
      typename QuantityTraits<YIndepType>::RawType eta;

      if( y_indep_value > min_y_indep_value && y_indep_value < max_y_indep_value )
      {
        typename QuantityTraits<YIndepType>::RawType
        intermediate_grid_length =
              TwoDInterpPolicy::ZYInterpPolicy::calculateUnitBaseGridLength(
                          min_y_indep_value,
                          max_y_indep_value );

        eta = TwoDInterpPolicy::ZYInterpPolicy::calculateUnitBaseIndepVar(
                      y_indep_value, min_y_indep_value, intermediate_grid_length );
      }
      else if( y_indep_value <= min_y_indep_value && y_indep_value >= min_y_indep_value_with_tol )
        eta = 0.0;
      else // y_indep_value >= max_y_indep_value && y_indep_value <= max_y_indep_value_with_tol
        eta = 1.0;

      typename QuantityTraits<YIndepType>::RawType grid_length;
      if( lower_bin_boundary->first == x_indep_value )
      {
        // Get the intermediate grid lengths for the indep value and the lower bin boundary
        typename QuantityTraits<YIndepType>::RawType grid_length_0 =
            TwoDInterpPolicy::ZYInterpPolicy::calculateUnitBaseGridLength(
                        lower_bin_boundary->second->getLowerBoundOfIndepVar(),
                        lower_bin_boundary->second->getUpperBoundOfIndepVar() );

        YIndepType norm_y_value = std::min(
          TwoDInterpPolicy::ZYInterpPolicy::calculateIndepVar(
              eta,
              lower_bin_boundary->second->getLowerBoundOfIndepVar(),
              grid_length_0 ),
                lower_bin_boundary->second->getUpperBoundOfIndepVar() );

        return ((*lower_bin_boundary->second).*evaluate)(norm_y_value);
      }
      else if( upper_bin_boundary->first == x_indep_value )
      {
        // Get the intermediate grid lengths for the indep value and the upper bin boundary
        typename QuantityTraits<YIndepType>::RawType grid_length_1 =
              TwoDInterpPolicy::ZYInterpPolicy::calculateUnitBaseGridLength(
                          upper_bin_boundary->second->getLowerBoundOfIndepVar(),
                          upper_bin_boundary->second->getUpperBoundOfIndepVar() );

        YIndepType norm_y_value = std::min(
          TwoDInterpPolicy::ZYInterpPolicy::calculateIndepVar(
              eta,
              upper_bin_boundary->second->getLowerBoundOfIndepVar(),
              grid_length_1 ),
                upper_bin_boundary->second->getUpperBoundOfIndepVar() );

        return ((*upper_bin_boundary->second).*evaluate)(norm_y_value);
      }
    }
    else if ( y_indep_value > max_y_indep_value_with_tol )
      return 1.0;
    else
      return 0.0;
  }
  else
  {
    // Calculate the lower bin grid length
    typename QuantityTraits<YIndepType>::RawType
      grid_length_0 =
        TwoDInterpPolicy::ZYInterpPolicy::calculateUnitBaseGridLength(
            lower_bin_boundary->second->getLowerBoundOfIndepVar(),
            lower_bin_boundary->second->getUpperBoundOfIndepVar() );

    // Calculate the upper bin grid length
    typename QuantityTraits<YIndepType>::RawType
      grid_length_1 =
        TwoDInterpPolicy::ZYInterpPolicy::calculateUnitBaseGridLength(
            upper_bin_boundary->second->getLowerBoundOfIndepVar(),
            upper_bin_boundary->second->getUpperBoundOfIndepVar() );

    // Calculate the intermediate grid limits
    YIndepType min_y_indep_value = min_y_indep_functor( x_indep_value );
    YIndepType max_y_indep_value = max_y_indep_functor( x_indep_value );

    typename QuantityTraits<YIndepType>::RawType
      intermediate_grid_length =
        TwoDInterpPolicy::ZYInterpPolicy::calculateUnitBaseGridLength(
                min_y_indep_value,
                max_y_indep_value );

    // Calculate the tol to the intermediate grid limits
    YIndepType min_y_indep_value_with_tol =
      TwoDInterpPolicy::ZYInterpPolicy::calculateFuzzyLowerBound(
                                                      min_y_indep_value,
                                                      fuzzy_boundary_tol );
    YIndepType max_y_indep_value_with_tol =
      TwoDInterpPolicy::ZYInterpPolicy::calculateFuzzyUpperBound(
                                                      max_y_indep_value,
                                                      fuzzy_boundary_tol );

    // Check if the secondary indep value is in the intermediate grid
    if( y_indep_value >= min_y_indep_value_with_tol &&
        y_indep_value <= max_y_indep_value_with_tol )
    {
      // Calculate the unit base independent variable
      typename QuantityTraits<YIndepType>::RawType eta;

      if( y_indep_value > min_y_indep_value && y_indep_value < max_y_indep_value )
      {
        eta = TwoDInterpPolicy::ZYInterpPolicy::calculateUnitBaseIndepVar(
                                          y_indep_value,
                                          min_y_indep_value,
                                          intermediate_grid_length );
      }
      else if( y_indep_value <= min_y_indep_value &&
               y_indep_value >= min_y_indep_value_with_tol )
        eta = 0.0;
      else // y_indep_value >= max_y_indep_value && y_indep_value <= max_y_indep_value_with_tol
        eta = 1.0;

      // Scale eta to the lower bin grid length
      YIndepType y_indep_value_0 =
        TwoDInterpPolicy::ZYInterpPolicy::calculateIndepVar(
                          eta,
                          lower_bin_boundary->second->getLowerBoundOfIndepVar(),
                          grid_length_0,
                          fuzzy_boundary_tol );

      // Scale eta to the upper bin grid length
      YIndepType y_indep_value_1 =
        TwoDInterpPolicy::ZYInterpPolicy::calculateIndepVar(
                          eta,
                          upper_bin_boundary->second->getLowerBoundOfIndepVar(),
                          grid_length_1,
                          fuzzy_boundary_tol );

      // Get the evaluation at the lower and upper bin boundaries
      double bin_eval_0 = ((*lower_bin_boundary->second).*evaluate)(y_indep_value_0);
      double bin_eval_1 = ((*upper_bin_boundary->second).*evaluate)(y_indep_value_1);

      if ( bin_eval_0 == bin_eval_1 )
        return bin_eval_0;
      else
      {
        // Return the interpolated evaluation
        return TwoDInterpPolicy::ZXInterpPolicy::interpolate(
                lower_bin_boundary->first,
                upper_bin_boundary->first,
                x_indep_value,
                bin_eval_0,
                bin_eval_1 );
      }
    }
    else // y_indep_value < min_y_indep_value || y_indep_value > max_y_indep_value
    {
      if( y_indep_value < min_y_indep_value_with_tol )
        return 0.0;
      else // y_indep_value > max_y_indep_value_with_tol
        return 1.0;
    }
  }
}

// Sample between bin boundaries using the desired sampling functor
/*! \details A unit-base statistical sampling procedure is used which samples
 * from one of the distributions on the bin boundaries and then scales the
 * sample so that it preserves intermediate grid limits. Certain methods require
 * the unscaled (or raw) sample, which can be acquired with this method.
 * Statistical sampling does not sample the true intermediate distribution and
 * will not match the unit-base evaluated PDF and CDF distributions. The
 * expected value of a sample, however, will be a sample from the true
 * distribution.
 */
template<typename _TwoDInterpPolicy>
template<typename XIndepType,
         typename YIndepType,
         typename YZIterator,
         typename SampleFunctor,
         typename YBoundsFunctor>
YIndepType UnitBase<_TwoDInterpPolicy>::sample(
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

  return UnitBase<TwoDInterpPolicy>::sampleDetailed<XIndepType,YIndepType,YZIterator,SampleFunctor>(
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
/* \details The SampleFunctor must sample a Cosine variable.
 * A unit-base statistical sampling procedure is used which samples
 * from one of the distributions on the bin boundaries and then scales the
 * sample so that it preserves intermediate grid limits. Certain methods require
 * the unscaled (or raw) sample, which can be acquired with this method.
 * Statistical sampling does not sample the true intermediate distribution and
 * will not match the unit-base evaluated PDF and CDF distributions. The
 * expected value of a sample, however, will be a sample from the true
 * distribution.
 */
template<typename _TwoDInterpPolicy>
template<typename XIndepType,
         typename YIndepType,
         typename YZIterator,
         typename SampleFunctor>
YIndepType UnitBase<_TwoDInterpPolicy>::sampleCos(
                                   const SampleFunctor& sample_functor,
                                   const XIndepType& x_indep_value,
                                   const YZIterator& lower_bin_boundary,
                                   const YZIterator& upper_bin_boundary )
{
  // Dummy variables
  YIndepType dummy_raw_sample;
  YZIterator dummy_sampled_bin_boundary;

  return UnitBase<TwoDInterpPolicy>::sampleCosDetailed<XIndepType,YIndepType,YZIterator,SampleFunctor>(
            sample_functor,
            x_indep_value,
            lower_bin_boundary,
            upper_bin_boundary,
            dummy_sampled_bin_boundary,
            dummy_raw_sample );
}

// Sample between bin boundaries using the desired subrange sampling functor
/* \details The SampleFunctor must be of the form that it takes a subrange
 * sampling function from a UnivariateDistribution and the max indep variable.
 * A unit-base statistical sampling procedure is used which samples
 * from one of the distributions on the bin boundaries and then scales the
 * sample so that it preserves intermediate grid limits. Certain methods require
 * the unscaled (or raw) sample, which can be acquired with this method.
 * Statistical sampling does not sample the true intermediate distribution and
 * will not match the unit-base evaluated PDF and CDF distributions. The
 * expected value of a sample, however, will be a sample from the true
 * distribution.
 */
template<typename _TwoDInterpPolicy>
template<typename XIndepType,
         typename YIndepType,
         typename YZIterator,
         typename SampleFunctor,
         typename YBoundsFunctor>
YIndepType UnitBase<_TwoDInterpPolicy>::sampleInSubrange(
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
    UnitBase<TwoDInterpPolicy>::sampleBinBoundary<XIndepType,YZIterator>(
                              x_indep_value,
                              lower_bin_boundary,
                              upper_bin_boundary );

  // Calculate the intermediate grid limits
  typename QuantityTraits<YIndepType>::RawType
      intermediate_grid_length =
        TwoDInterpPolicy::ZYInterpPolicy::calculateUnitBaseGridLength(
                                                  min_y_indep_value,
                                                  max_y_indep_value );

  // Calculate the unit base variable on the sampled bin boundary
  typename QuantityTraits<YIndepType>::RawType eta;

  {
    // Calculate the limit on the sampled bin boundary
    typename QuantityTraits<YIndepType>::RawType grid_length =
      TwoDInterpPolicy::ZYInterpPolicy::calculateUnitBaseGridLength(
                      sampled_bin_boundary->second->getLowerBoundOfIndepVar(),
                      sampled_bin_boundary->second->getUpperBoundOfIndepVar() );

    YIndepType raw_sample;
    if( subrange_max_y_indep_value < max_y_indep_value )
    {
      typename QuantityTraits<YIndepType>::RawType subrange_eta_max =
        TwoDInterpPolicy::ZYInterpPolicy::calculateUnitBaseIndepVar(
                                                    subrange_max_y_indep_value,
                                                    min_y_indep_value,
                                                    intermediate_grid_length );

      YIndepType max_y_indep_value_bin_bound =
        TwoDInterpPolicy::ZYInterpPolicy::calculateIndepVar(
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
    eta = TwoDInterpPolicy::ZYInterpPolicy::calculateUnitBaseIndepVar(
                        raw_sample,
                        sampled_bin_boundary->second->getLowerBoundOfIndepVar(),
                        grid_length );
  }

  return TwoDInterpPolicy::ZYInterpPolicy::calculateIndepVar(
                                                eta,
                                                min_y_indep_value,
                                                intermediate_grid_length );
}

// Sample between bin boundaries using the desired sampling functor
/*! \details A unit-base statistical sampling procedure is used which samples
 * from one of the distributions on the bin boundaries and then scales the
 * sample so that it preserves intermediate grid limits. Certain methods require
 * the unscaled (or raw) sample, which can be acquired with this method.
 * Statistical sampling does not sample the true intermediate distribution and
 * will not match the unit-base evaluated PDF and CDF distributions. The
 * expected value of a sample, however, will be a sample from the true
 * distribution. This method is an implementation of ACE law 4.
 */
template<typename _TwoDInterpPolicy>
template<typename XIndepType,
         typename YIndepType,
         typename YZIterator,
         typename SampleFunctor,
         typename YBoundsFunctor>
YIndepType UnitBase<_TwoDInterpPolicy>::sampleDetailed(
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
    UnitBase<_TwoDInterpPolicy>::sampleBinBoundary<XIndepType,YZIterator>(
                            x_indep_value,
                            lower_bin_boundary,
                            upper_bin_boundary );

  // Calculate the intermediate grid limits
  typename QuantityTraits<YIndepType>::RawType
    intermediate_grid_length =
    TwoDInterpPolicy::ZYInterpPolicy::calculateUnitBaseGridLength(
                min_y_indep_value, max_y_indep_value );

  // Calculate the unit base variable on the bin boundary corresponding to the
  // raw sample
  typename QuantityTraits<YIndepType>::RawType eta;

  {
    // Calculate the limit on the sampled bin boundary
    typename QuantityTraits<YIndepType>::RawType grid_length =
      TwoDInterpPolicy::ZYInterpPolicy::calculateUnitBaseGridLength(
                      sampled_bin_boundary->second->getLowerBoundOfIndepVar(),
                      sampled_bin_boundary->second->getUpperBoundOfIndepVar());

    // Create the raw sample
    raw_sample = sample_functor( *sampled_bin_boundary->second );

    eta = TwoDInterpPolicy::ZYInterpPolicy::calculateUnitBaseIndepVar(
                       raw_sample,
                       sampled_bin_boundary->second->getLowerBoundOfIndepVar(),
                       grid_length );
  }
  // Scale the sample so that it preserves the intermediate limits.
  // Note: This is a stochastic procedure. The intermediate distribution that
  //       has been sampled is not the true distribution. The expected value
  //       of a sample will be a sample from the true distribution though.
  return TwoDInterpPolicy::ZYInterpPolicy::calculateIndepVar(
                eta, min_y_indep_value, intermediate_grid_length );
}

// Sample between bin boundaries using the desired sampling functor
template<typename _TwoDInterpPolicy>
template<typename XIndepType,
         typename YIndepType,
         typename YZIterator,
         typename SampleFunctor>
YIndepType UnitBase<_TwoDInterpPolicy>::sampleCosDetailed(
            const SampleFunctor& sample_functor,
            const XIndepType& x_indep_value,
            const YZIterator& lower_bin_boundary,
            const YZIterator& upper_bin_boundary,
            YZIterator& sampled_bin_boundary,
            YIndepType& raw_sample )
{
  // Get the sampled bin boundary
  sampled_bin_boundary =
    UnitBase<_TwoDInterpPolicy>::sampleBinBoundary<XIndepType,YZIterator>(
                            x_indep_value,
                            lower_bin_boundary,
                            upper_bin_boundary );

  // Create the raw sample
  raw_sample = sample_functor( *sampled_bin_boundary->second );

  return raw_sample;
}

// Sample the bin boundary that will be used for statistical sampling
/*! \details This method will throw an exception if the primary independent
 * value is outside of the primary grid limits and the primary grid has not
 * been extended.
 */
template<typename _TwoDInterpPolicy>
template<typename XIndepType,
         typename YZIterator>
YZIterator UnitBase<_TwoDInterpPolicy>::sampleBinBoundary(
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
template<typename _TwoDInterpPolicy>
inline const std::string UnitBase<_TwoDInterpPolicy>::name()
{
  return "Unit-base";
}

// Calculate the Y independent lower bound between bin boundaries
template<typename _TwoDInterpPolicy>
template<typename YIndepType,
         typename XIndepType,
         typename YZIterator>
auto Correlated<_TwoDInterpPolicy>::calculateLowerBound(
                      const XIndepType& x_indep_value,
                      const YZIterator& lower_bin_boundary,
                      const YZIterator& upper_bin_boundary ) -> YIndepType
{
  return UnitBase<_TwoDInterpPolicy>::template calculateLowerBound<YIndepType, XIndepType, YZIterator>(
                        x_indep_value,
                        lower_bin_boundary,
                        upper_bin_boundary );
}

// Calculate the Y independent upper bound between bin boundaries
template<typename _TwoDInterpPolicy>
template<typename YIndepType,
         typename XIndepType,
         typename YZIterator>
auto Correlated<_TwoDInterpPolicy>::calculateUpperBound(
                      const XIndepType& x_indep_value,
                      const YZIterator& lower_bin_boundary,
                      const YZIterator& upper_bin_boundary ) -> YIndepType
{
  return UnitBase<_TwoDInterpPolicy>::template calculateUpperBound<YIndepType, XIndepType, YZIterator>(
                        x_indep_value,
                        lower_bin_boundary,
                        upper_bin_boundary );
}

namespace Details{

/*! The helper struct used to calculate the secondary independent value
 *
 * Specialization of this class for different UnivariateDistribution classes is
 * required. Using a UnivariateDistribution class that does not have a specialization
 * (and is therefore assumed to be unsupported) will result in the following
 * compile time error message: "...::thisInterpPolicyIsNotSupported()".
 */
template<typename BaseUnivariateDistributionType>
struct CorrelatedEvaluatePDFSecondaryIndepHelper
{
  //! Typedef for this type
  typedef CorrelatedEvaluatePDFSecondaryIndepHelper<BaseUnivariateDistributionType> ThisType;

  //! Calculate the secondary independent values
  template<typename TwoDInterpPolicy,
           typename YIndepType,
           typename YZIterator,
           typename EvaluationMethod,
           typename T>
  static void calculateSecondaryIndepValues( const EvaluationMethod& evaluate,
                                             const YIndepType& y_indep_value,
                                             const YZIterator& lower_bin_boundary,
                                             const YZIterator& upper_bin_boundary,
                                             const T& beta,
                                             const double fuzzy_boundary_tol,
                                             const double rel_error_tol,
                                             const double error_tol,
                                             const unsigned max_number_of_iterations,
                                             YIndepType& lower_y_value,
                                             YIndepType& upper_y_value )
  { BaseUnivariateDistributionType::thisDistTypeIsNotCompatibleWithCorrelatedEvaluation(); }

  // Estimate the interpolated CDF and the corresponding lower and upper y
  // indep values
  template<typename TwoDInterpPolicy,
           typename YIndepType,
           typename YZIterator,
           typename T>
  static double estimateCDF(
              double& lower_cdf_est,
              double& upper_cdf_est,
              YIndepType& y_indep_value_0,
              YIndepType& y_indep_value_1,
              const T& beta,
              const YIndepType& y_indep_value,
              const YZIterator& lower_bin_boundary,
              const YZIterator& upper_bin_boundary,
              const double rel_error_tol = 1e-7,
              const double error_tol = 1e-15,
              unsigned max_number_of_iterations = 500u )
  { BaseUnivariateDistributionType::thisDistTypeIsNotCompatibleWithCorrelatedEvaluation(); }

  // Evaluate the interpolated y at the CDF value
  template<typename TwoDInterpPolicy,
           typename YIndepType,
           typename YZIterator,
           typename T>
  static YIndepType evaluateY(
             double& cdf,
             const T& beta,
             const YZIterator& lower_bin_boundary,
             const YZIterator& upper_bin_boundary,
             YIndepType& y_indep_value_0,
             YIndepType& y_indep_value_1 )
  {
BaseUnivariateDistributionType::thisDistTypeIsNotCompatibleWithCorrelatedEvaluation(); }
};

/*! \brief Partial specialization of the
 * Utility::Details::CorrelatedEvaluatePDFSecondaryIndepHelper class for
 * Utility::UnitAwareTabularUnivariateDistribution
 */
template<typename _T, typename _U>
struct CorrelatedEvaluatePDFSecondaryIndepHelper<Utility::UnitAwareTabularUnivariateDistribution<_T,_U> >
{
  //! Typdef for this type
  typedef CorrelatedEvaluatePDFSecondaryIndepHelper<Utility::UnitAwareTabularUnivariateDistribution<_T,_U> > ThisType;

  //! Calculate the secondary independent values
  template<typename TwoDInterpPolicy,
           typename YIndepType,
           typename YZIterator,
           typename EvaluationMethod,
           typename T>
  static void calculateSecondaryIndepValues( const EvaluationMethod& evaluate,
                                             const YIndepType& y_indep_value,
                                             const YZIterator& lower_bin_boundary,
                                             const YZIterator& upper_bin_boundary,
                                             const T& beta,
                                             const double fuzzy_boundary_tol,
                                             const double rel_error_tol,
                                             const double error_tol,
                                             const unsigned max_number_of_iterations,
                                             YIndepType& lower_y_value,
                                             YIndepType& upper_y_value );

  // Estimate the interpolated CDF and the corresponding lower and upper y
  // indep values
  template<typename TwoDInterpPolicy,
           typename YIndepType,
           typename YZIterator,
           typename T>
  static double estimateCDF(
              double& lower_cdf_est,
              double& upper_cdf_est,
              YIndepType& y_indep_value_0,
              YIndepType& y_indep_value_1,
              const T& beta,
              const YIndepType& y_indep_value,
              const YZIterator& lower_bin_boundary,
              const YZIterator& upper_bin_boundary,
              const double rel_error_tol = 1e-7,
              const double error_tol = 1e-15,
              unsigned max_number_of_iterations = 500u );

  // Evaluate the interpolated y at the CDF value
  template<typename TwoDInterpPolicy,
           typename YIndepType,
           typename YZIterator,
           typename T>
  static YIndepType evaluateY(
             double& cdf,
             const T& beta,
             const YZIterator& lower_bin_boundary,
             const YZIterator& upper_bin_boundary,
             YIndepType& y_indep_value_0,
             YIndepType& y_indep_value_1 );
};

// Calculate the secondary independent values
template<typename _T, typename _U>
template<typename TwoDInterpPolicy,
         typename YIndepType,
         typename YZIterator,
         typename EvaluationMethod,
         typename T>
void CorrelatedEvaluatePDFSecondaryIndepHelper<Utility::UnitAwareTabularUnivariateDistribution<_T,_U> >::calculateSecondaryIndepValues(
                                       const EvaluationMethod& evaluate,
                                       const YIndepType& y_indep_value,
                                       const YZIterator& lower_bin_boundary,
                                       const YZIterator& upper_bin_boundary,
                                       const T& beta,
                                       const double fuzzy_boundary_tol,
                                       const double rel_error_tol,
                                       const double error_tol,
                                       const unsigned max_number_of_iterations,
                                       YIndepType& lower_y_value,
                                       YIndepType& upper_y_value )
{
  // Get the lower and upper boundaries of the evaluated cdf
  double lower_cdf_bound, upper_cdf_bound;
  {
    // Evaluate the cdf at the upper and lower bin boundaries
    double bin_eval_0 =
      ((*lower_bin_boundary->second).*&Utility::UnitAwareTabularUnivariateDistribution<_T,_U>::evaluateCDF)( y_indep_value );
    double bin_eval_1 =
      ((*upper_bin_boundary->second).*&Utility::UnitAwareTabularUnivariateDistribution<_T,_U>::evaluateCDF)( y_indep_value );

    if ( bin_eval_0 <= bin_eval_1 )
    {
      lower_cdf_bound = bin_eval_0;
      upper_cdf_bound = bin_eval_1;
    }
    else
    {
      lower_cdf_bound = bin_eval_1;
      upper_cdf_bound = bin_eval_0;
    }

    // Make sure the estimates are valid
    YIndepType dummy_y0, dummy_y1;
    YIndepType lower_y_estimate = ThisType::evaluateY<TwoDInterpPolicy>(
                                                      lower_cdf_bound,
                                                      beta,
                                                      lower_bin_boundary,
                                                      upper_bin_boundary,
                                                      dummy_y0,
                                                      dummy_y1 );

    YIndepType upper_y_estimate = ThisType::evaluateY<TwoDInterpPolicy>(
                                                      upper_cdf_bound,
                                                      beta,
                                                      lower_bin_boundary,
                                                      upper_bin_boundary,
                                                      dummy_y0,
                                                      dummy_y1 );

    while( lower_y_estimate > y_indep_value )
    {
      upper_cdf_bound = lower_cdf_bound;
      lower_cdf_bound *= 0.9;

      if( lower_cdf_bound == 0.0 )
        break;

      lower_y_estimate =
        ThisType::evaluateY<TwoDInterpPolicy>( lower_cdf_bound,
                                               beta,
                                               lower_bin_boundary,
                                               upper_bin_boundary,
                                               dummy_y0,
                                               dummy_y1 );
    }

    while( upper_y_estimate < y_indep_value )
    {
      lower_cdf_bound = upper_cdf_bound;
      upper_cdf_bound *= 1.1;

      if( upper_cdf_bound >= 1.0 )
      {
        upper_cdf_bound = 1.0;
        break;
      }

      upper_y_estimate =
        ThisType::evaluateY<TwoDInterpPolicy>( upper_cdf_bound,
                                               beta,
                                               lower_bin_boundary,
                                               upper_bin_boundary,
                                               dummy_y0,
                                               dummy_y1 );
    }
  }

  double est_cdf = ThisType::estimateCDF<TwoDInterpPolicy>(
                                                    lower_cdf_bound,
                                                    upper_cdf_bound,
                                                    lower_y_value,
                                                    upper_y_value,
                                                    beta,
                                                    y_indep_value,
                                                    lower_bin_boundary,
                                                    upper_bin_boundary,
                                                    rel_error_tol,
                                                    error_tol,
                                                    max_number_of_iterations );
}


// Estimate the interpolated CDF and the corresponding lower and upper y indep
// values
template<typename _T, typename _U>
template<typename TwoDInterpPolicy,
         typename YIndepType,
         typename YZIterator,
         typename T>
double CorrelatedEvaluatePDFSecondaryIndepHelper<Utility::UnitAwareTabularUnivariateDistribution<_T,_U> >::estimateCDF(
                                          double& lower_cdf_est,
                                          double& upper_cdf_est,
                                          YIndepType& y_indep_value_0,
                                          YIndepType& y_indep_value_1,
                                          const T& beta,
                                          const YIndepType& y_indep_value,
                                          const YZIterator& lower_bin_boundary,
                                          const YZIterator& upper_bin_boundary,
                                          const double rel_error_tol,
                                          const double error_tol,
                                          unsigned max_number_of_iterations )
{
  unsigned number_of_iterations = 0;
  double rel_error = 1.0;
  YIndepType error_norm_constant = y_indep_value;
  double tolerance = rel_error_tol;

  /*! \detials If the secondary indep var value is zero the relative error
   *  will always zero or inf. When this is the case the error tolerance will
   *  be used instead of the relative error tolerance.
   */
  if ( y_indep_value == QuantityTraits<YIndepType>::zero() )
  {
    error_norm_constant = QuantityTraits<YIndepType>::one();
    tolerance = error_tol;
  }

  // Refine the estimated cdf value until it meet the tolerance
  double estimated_cdf = 0.0;
  while ( rel_error > tolerance )
  {
    // Estimate the cdf as the midpoint of the lower and upper boundaries
    estimated_cdf = 0.5*( lower_cdf_est + upper_cdf_est );

    YIndepType est_y_indep_value =
      ThisType::evaluateY<TwoDInterpPolicy>( estimated_cdf,
                                             beta,
                                             lower_bin_boundary,
                                             upper_bin_boundary,
                                             y_indep_value_0,
                                             y_indep_value_1 );

    if ( y_indep_value == est_y_indep_value )
      break;

    // Calculate the relative error between the y_indep_value and the estimate
    rel_error = (y_indep_value - est_y_indep_value )/ error_norm_constant;

    // Make sure the relative error is positive
    rel_error = rel_error < 0 ? -rel_error : rel_error;

    // Update the number of iterations
    ++number_of_iterations;

    // If tolerance is met exit loop
    if ( rel_error <= tolerance )
      break;

    // Update the estimated_cdf estimate
    if ( est_y_indep_value < y_indep_value )
    {
      // Old estimated_cdf estimate is new lower cdf boundary
      lower_cdf_est = estimated_cdf;
    }
    else
    {
      // Old estimated_cdf estimate is new upper cdf boundary
      upper_cdf_est = estimated_cdf;
    }

    // Check for the max number of iterations
    if ( number_of_iterations > max_number_of_iterations )
    {
      // Get error in estimate
      double error =
        (y_indep_value - est_y_indep_value )/QuantityTraits<YIndepType>::one();
      error = error < 0 ? -error : error;

      // If error meets error tolerance accept estimate
      if ( error < error_tol )
        break;
      else
      {
        THROW_EXCEPTION( std::logic_error,
                         "Error: The evaluation could not be completed. "
                         "The max number of iterations ("
                         << max_number_of_iterations
                         << ") was reached before the relative error ("
                         << rel_error
                         << ") reached the evaluation tolerance ("
                         << tolerance
                         << ")"
                         << " or the error ("
                         << error
                         << ") reached the error tolerance ("
                         << error_tol
                         << ")." );
      }
    }
  }

  return estimated_cdf;
}





// Evaluate the interpolated y at the CDF value
template<typename _T, typename _U>
template<typename TwoDInterpPolicy,
         typename YIndepType,
         typename YZIterator,
         typename T>
YIndepType CorrelatedEvaluatePDFSecondaryIndepHelper<Utility::UnitAwareTabularUnivariateDistribution<_T,_U> >::evaluateY(
             double& cdf,
             const T& beta,
             const YZIterator& lower_bin_boundary,
             const YZIterator& upper_bin_boundary,
             YIndepType& y_indep_value_0,
             YIndepType& y_indep_value_1 )
{
  // Get the sampled values at the upper and lower bin for the estimated_cdf
  y_indep_value_0 =
    ((*lower_bin_boundary->second).*&Utility::UnitAwareTabularUnivariateDistribution<_T,_U>::sampleWithRandomNumber)( cdf );
  y_indep_value_1 =
    ((*upper_bin_boundary->second).*&Utility::UnitAwareTabularUnivariateDistribution<_T,_U>::sampleWithRandomNumber)( cdf );

  // Interpolate using the templated TwoDInterpPolicy::YXInterpPolicy
  return TwoDInterpPolicy::YXInterpPolicy::interpolate( beta,
                                                        y_indep_value_0,
                                                        y_indep_value_1 );
}




/*! \brief Base helper struct for calculating the PDF of a bivariate
 * distribution assuming linear interpolation with the secondary indep grid
 * The PDF for lin-lin interpolation is defined as:
 * f(x,y) = ( f_0( y_0 ) * f_1( y_1 ) )/
 *          ( f_1(y_1) + ( f_0(y_0) - f_1(y_1) )* beta )
 */
struct CorrelatedEvaluatePDFCosHelperLinBase
{
  template<typename YIndepType,
           typename ReturnType,
           typename T>
  static inline ReturnType evaluate( const YIndepType y_indep_value,
                                     const YIndepType lower_y_value,
                                     const ReturnType lower_eval,
                                     const YIndepType upper_y_value,
                                     const ReturnType upper_eval,
                                     const T beta )
  {
    return lower_eval*upper_eval/
      Utility::LinLin::interpolate( beta, upper_eval, lower_eval );
  }
};

/*! \brief Base helper struct for calculating the PDF of a bivariate
 * distribution assuming log-cos interpolation with the secondary indep grid
 *
 * The PDF for log-log interpolation is defined as:
 * f(x,y) = (1/y)*( y_0*f_0( y_0 ) * y_1*f_1( y_1 ) )/
 *          ( y_1*f_1(y_1)+( (y_0*f_0(y_0)) - (y_1*f_1(y_1)) )*beta )
 */
struct CorrelatedEvaluatePDFCosHelperLogCosBase
{
  template<typename YIndepType,
           typename ReturnType,
           typename T>
  static inline ReturnType evaluate( const YIndepType y_indep_value,
                                     const YIndepType lower_y_value,
                                     const ReturnType lower_eval,
                                     const YIndepType upper_y_value,
                                     const ReturnType upper_eval,
                                     const T beta )
  {
    auto lower_product = lower_eval*Utility::CosNudgeHelper<false>::convertFromCosineVar(lower_y_value);
    auto upper_product = upper_eval*Utility::CosNudgeHelper<false>::convertFromCosineVar(upper_y_value);

    return (lower_product*upper_product)/
      (Utility::LinLin::interpolate( beta, upper_product, lower_product )*
        Utility::CosNudgeHelper<false>::convertFromCosineVar(y_indep_value) );
  }
};

/*! \brief Base helper struct for calculating the PDF of a bivariate
 * distribution assuming log-cos (with nudge factor) interpolation with the
 * secondary indep grid
 *
 * The PDF for log-log interpolation is defined as: f(x,y) = (1/y)*( y_0*f_0(
 * y_0 ) * y_1*f_1( y_1 ) )/ ( y_1*f_1(y_1)+( (y_0*f_0(y_0)) - (y_1*f_1(y_1))
 * )*beta )
 */
struct CorrelatedEvaluatePDFCosHelperLogCosBaseWithNudge
{
  template<typename YIndepType,
           typename ReturnType,
           typename T>
  static inline ReturnType evaluate( const YIndepType y_indep_value,
                                     const YIndepType lower_y_value,
                                     const ReturnType lower_eval,
                                     const YIndepType upper_y_value,
                                     const ReturnType upper_eval,
                                     const T beta )
  {
    auto lower_product = lower_eval*Utility::CosNudgeHelper<true>::convertFromCosineVar(lower_y_value);
    auto upper_product = upper_eval*Utility::CosNudgeHelper<true>::convertFromCosineVar(upper_y_value);

    return (lower_product*upper_product)/
      (Utility::LinLin::interpolate( beta, upper_product, lower_product )*
        Utility::CosNudgeHelper<true>::convertFromCosineVar(y_indep_value) );
  }
};

/*! \brief Helper struct for calculating the PDF of a bivariate distribution
 *
 * Specialization of this struct for the different interpolation types is
 * required.
 */
template<typename YXInterpPolicy>
struct CorrelatedEvaluatePDFCosHelper
{
  template<typename YIndepType,
           typename ReturnType,
           typename T>
  static inline ReturnType evaluate( const YIndepType y_indep_value,
                                     const YIndepType lower_y_value,
                                     const ReturnType lower_eval,
                                     const YIndepType upper_y_value,
                                     const ReturnType upper_eval,
                                     const T beta )
  {
    THROW_EXCEPTION( std::runtime_error,
                     "Interpolation type " << YXInterpPolicy::name() <<
                     " is not currently supported!\n" );
  }
};

/*! \brief Specialization of Utility::Details::CorrelatedEvaluatePDFCosHelper
 * for Utility::LinLin.
 */
template<>
struct CorrelatedEvaluatePDFCosHelper<Utility::LinLin> : public CorrelatedEvaluatePDFCosHelperLinBase
{ /* ... */ };

/*! \brief Specialization of Utility::Details::CorrelatedEvaluatePDFCosHelper
 * for Utility::LinLog.
 */
template<>
struct CorrelatedEvaluatePDFCosHelper<Utility::LinLog> : public CorrelatedEvaluatePDFCosHelperLinBase
{ /* ... */ };

/*! \brief Specialization of Utility::Details::CorrelatedEvaluatePDFCosHelper
 * for Utility::LogCosLin.
 */
template<>
struct CorrelatedEvaluatePDFCosHelper<Utility::LogCosLin > : public CorrelatedEvaluatePDFCosHelperLogCosBase
{ /* ... */ };

/*! \brief Specialization of Utility::Details::CorrelatedEvaluatePDFCosHelper
 * for Utility::LogCosLin.
 */
template<>
struct CorrelatedEvaluatePDFCosHelper<Utility::NudgedLogCosLin > : public CorrelatedEvaluatePDFCosHelperLogCosBaseWithNudge
{ /* ... */ };

/*! \brief Specialization of Utility::Details::CorrelatedEvaluatePDFCosHelper
 * for Utility::LogCosLog.
 */
template<>
struct CorrelatedEvaluatePDFCosHelper<Utility::LogCosLog > : public CorrelatedEvaluatePDFCosHelperLogCosBase
{ /* ... */ };

/*! \brief Specialization of Utility::Details::CorrelatedEvaluatePDFCosHelper
 * for Utility::LogCosLog.
 */
template<>
struct CorrelatedEvaluatePDFCosHelper<Utility::NudgedLogCosLog > : public CorrelatedEvaluatePDFCosHelperLogCosBaseWithNudge
{ /* ... */ };

} // end Details namespace

// Evaluate the PDF between bin boundaries using the desired evaluation method
/*! \details The EvaluationMethod must evalute using a Cosine variable. The edge
 *  case of no scattering (i.e. y = 1 ) is must be specially handled with
 *  LogCosLog interpolation in order to avoid a ln(1). This method uses an
 *  iterative method to estimate the CDF for correlated sampling to a relative
 *  error tolerance in order to get the proper interpolation parameters.
 */
template<typename _TwoDInterpPolicy>
template<typename BaseUnivariateDistributionType,
         typename XIndepType,
         typename YIndepType,
         typename ReturnType,
         typename YZIterator,
         typename EvaluationMethod,
         typename YBoundsFunctor>
ReturnType Correlated<_TwoDInterpPolicy>::evaluatePDFCos(
                                  const XIndepType& x_indep_value,
                                  const YIndepType& y_indep_value,
                                  const YBoundsFunctor& min_y_indep_functor,
                                  const YBoundsFunctor& max_y_indep_functor,
                                  const EvaluationMethod& evaluate,
                                  const YZIterator& lower_bin_boundary,
                                  const YZIterator& upper_bin_boundary,
                                  const double fuzzy_boundary_tol,
                                  const double rel_error_tol,
                                  const double error_tol,
                                  unsigned max_number_of_iterations )
{
  // Check to see if the x indep value is on the grid limits
  if( lower_bin_boundary->first == x_indep_value )
  {
    return ((*lower_bin_boundary->second).*evaluate)(y_indep_value);
  }
  else if( upper_bin_boundary->first == x_indep_value )
  {
    return ((*upper_bin_boundary->second).*evaluate)(y_indep_value);
  }
  else // x indep value is in between the grid limits
  {
    // Calculate the bin length of the x variable
    const typename QuantityTraits<XIndepType>::RawType x_bin_length =
      TwoDInterpPolicy::ZXInterpPolicy::calculateUnitBaseGridLength(
                                                    lower_bin_boundary->first,
                                                    upper_bin_boundary->first );

      // Calculate the x variable bin ratio (beta)
    const typename QuantityTraits<XIndepType>::RawType beta =
      TwoDInterpPolicy::ZXInterpPolicy::calculateUnitBaseIndepVar(
                                                    x_indep_value,
                                                    lower_bin_boundary->first,
                                                    x_bin_length );

    // Get the min and max y value at the given x value
    YIndepType min_y_indep_value = min_y_indep_functor( x_indep_value );
    YIndepType max_y_indep_value = max_y_indep_functor( x_indep_value );

    // Calculate the correlated y value at the lower and upper bin boundary
    YIndepType lower_y_value, upper_y_value;

    // Check for a secondary indep value outside of the secondary indep grid limits
    if ( y_indep_value < min_y_indep_value || y_indep_value > max_y_indep_value )
      return QuantityTraits<ReturnType>::zero();
    else if ( y_indep_value == min_y_indep_value ) // At min y value
    {
      lower_y_value = min_y_indep_value;
      upper_y_value = min_y_indep_value;
    }
    else if ( y_indep_value == max_y_indep_value ) // At max y value
    {
      lower_y_value = max_y_indep_value;
      upper_y_value = max_y_indep_value;
    }
    else // Between min and max y values
    {
      Details::CorrelatedEvaluatePDFSecondaryIndepHelper<BaseUnivariateDistributionType>::template calculateSecondaryIndepValues<TwoDInterpPolicy>(
                                                      evaluate,
                                                      y_indep_value,
                                                      lower_bin_boundary,
                                                      upper_bin_boundary,
                                                      beta,
                                                      fuzzy_boundary_tol,
                                                      rel_error_tol,
                                                      error_tol,
                                                      max_number_of_iterations,
                                                      lower_y_value,
                                                      upper_y_value );
    }

    // Interpolate using the correlated upper and lower y values
    ReturnType lower_eval = ((*lower_bin_boundary->second).*evaluate)(lower_y_value);
    ReturnType upper_eval = ((*upper_bin_boundary->second).*evaluate)(upper_y_value);

    if( lower_eval == upper_eval )
      return lower_eval;
    else
    {
      return Details::CorrelatedEvaluatePDFCosHelper<typename TwoDInterpPolicy::YXInterpPolicy>::evaluate(
                                                                 y_indep_value,
                                                                 lower_y_value,
                                                                 lower_eval,
                                                                 upper_y_value,
                                                                 upper_eval,
                                                                 beta );
    }
  }
}

namespace Details{

/*! \brief Base helper struct for calculating the PDF of a bivariate
 * distribution assuming linear interpolation with the secondary indep grid
 * The PDF for lin-lin interpolation is defined as:
 * f(x,y) = ( f_0( y_0 ) * f_1( y_1 ) )/
 *          ( f_1(y_1) + ( f_0(y_0) - f_1(y_1) )* beta )
 */
struct CorrelatedEvaluatePDFHelperLinBase : public CorrelatedEvaluatePDFCosHelperLinBase
{ /* ... */ };

/*! \brief Base helper struct for calculating the PDF of a bivariate
 * distribution assuming log interpolation with the secondary indep grid
 *
 * The PDF for log-log interpolation is defined as:
 * f(x,y) = (1/y)*( y_0*f_0( y_0 ) * y_1*f_1( y_1 ) )/
 *          ( y_1*f_1(y_1)+( (y_0*f_0(y_0)) - (y_1*f_1(y_1)) )*beta )
 */
struct CorrelatedEvaluatePDFHelperLogBase
{
  template<typename YIndepType,
           typename ReturnType,
           typename T>
  static inline ReturnType evaluate( const YIndepType y_indep_value,
                                     const YIndepType lower_y_value,
                                     const ReturnType lower_eval,
                                     const YIndepType upper_y_value,
                                     const ReturnType upper_eval,
                                     const T beta )
  {
    auto lower_product = lower_eval*lower_y_value;
    auto upper_product = upper_eval*upper_y_value;

    return (lower_product*upper_product)/
      (Utility::LinLin::interpolate( beta, upper_product, lower_product )*
       y_indep_value);
  }
};

/*! \brief Helper struct for calculating the PDF of a bivariate distribution
 *
 * Specialization of this struct for the different interpolation types is
 * required.
 */
template<typename YXInterpPolicy>
struct CorrelatedEvaluatePDFHelper
{
  template<typename YIndepType,
           typename ReturnType,
           typename T>
  static inline ReturnType evaluate( const YIndepType y_indep_value,
                                     const YIndepType lower_y_value,
                                     const ReturnType lower_eval,
                                     const YIndepType upper_y_value,
                                     const ReturnType upper_eval,
                                     const T beta )
  {
    THROW_EXCEPTION( std::runtime_error,
                     "Interpolation type " << YXInterpPolicy::name() <<
                     " is not currently supported!\n" );
  }
};

/*! \brief Specialization of Utility::Details::CorrelatedEvaluatePDFHelper for
 * Utility::LinLin
 */
template<>
struct CorrelatedEvaluatePDFHelper<Utility::LinLin> : public CorrelatedEvaluatePDFHelperLinBase
{ /* ... */ };

/*! \brief Specialization of Utility::Details::CorrelatedEvaluatePDFHelper for
 * Utility::LinLog
 */
template<>
struct CorrelatedEvaluatePDFHelper<Utility::LinLog> : public CorrelatedEvaluatePDFHelperLinBase
{ /* ... */ };

/*! \brief Specialization of Utility::Details::CorrelatedEvaluatePDFHelper for
 * Utility::LogLog
 */
template<>
struct CorrelatedEvaluatePDFHelper<Utility::LogLog> : public CorrelatedEvaluatePDFHelperLogBase
{ /* ... */ };

/*! \brief Specialization of Utility::Details::CorrelatedEvaluatePDFHelper for
 * Utility::LogCosLog
 */
template<>
struct CorrelatedEvaluatePDFHelper<Utility::LogCosLog > : public CorrelatedEvaluatePDFHelperLogBase
{ /* ... */ };

/*! \brief Specialization of Utility::Details::CorrelatedEvaluatePDFHelper for
 * Utility::LogCosLog
 */
template<>
struct CorrelatedEvaluatePDFHelper<Utility::NudgedLogCosLog > : public CorrelatedEvaluatePDFHelperLogBase
{ /* ... */ };

/*! \brief Specialization of Utility::Details::CorrelatedEvaluatePDFHelper for
 * Utility::LogLin
 */
template<>
struct CorrelatedEvaluatePDFHelper<Utility::LogLin> : public CorrelatedEvaluatePDFHelperLogBase
{ /* ... */ };

/*! \brief Specialization of Utility::Details::CorrelatedEvaluatePDFHelper for
 * Utility::LogCosLin
 */
template<>
struct CorrelatedEvaluatePDFHelper<Utility::LogCosLin > : public CorrelatedEvaluatePDFHelperLogBase
{ /* ... */ };

/*! \brief Specialization of Utility::Details::CorrelatedEvaluatePDFHelper for
 * Utility::LogCosLin
 */
template<>
struct CorrelatedEvaluatePDFHelper<Utility::NudgedLogCosLin > : public CorrelatedEvaluatePDFHelperLogBase
{ /* ... */ };

} // end Details namespace

// Evaluate the PDF between bin boundaries using the desired evaluation method
/*! \details This function uses an iterative method to estimate the CDF for
 *  correlated sampling to a relative error tolerance in order to get the proper
 *  interpolation parameters.
 */
template<typename _TwoDInterpPolicy>
template<typename BaseUnivariateDistributionType,
         typename XIndepType,
         typename YIndepType,
         typename ReturnType,
         typename YZIterator,
         typename EvaluationMethod,
         typename YBoundsFunctor>
ReturnType Correlated<_TwoDInterpPolicy>::evaluatePDF(
                                  const XIndepType& x_indep_value,
                                  const YIndepType& y_indep_value,
                                  const YBoundsFunctor& min_y_indep_functor,
                                  const YBoundsFunctor& max_y_indep_functor,
                                  const EvaluationMethod& evaluate,
                                  const YZIterator& lower_bin_boundary,
                                  const YZIterator& upper_bin_boundary,
                                  const double fuzzy_boundary_tol,
                                  const double rel_error_tol,
                                  const double error_tol,
                                  unsigned max_number_of_iterations )
{
  // Check to see if the x indep value is on the bin limits
  if( lower_bin_boundary->first == x_indep_value )
  {
    return ((*lower_bin_boundary->second).*evaluate)(y_indep_value);
  }
  else if( upper_bin_boundary->first == x_indep_value )
  {
    return ((*upper_bin_boundary->second).*evaluate)(y_indep_value);
  }
  else
  {
    // Calculate the bin length of the x variable
    const typename QuantityTraits<XIndepType>::RawType x_bin_length =
      TwoDInterpPolicy::ZXInterpPolicy::calculateUnitBaseGridLength(
                                                    lower_bin_boundary->first,
                                                    upper_bin_boundary->first );

      // Calculate the x variable bin ratio (beta)
    const typename QuantityTraits<XIndepType>::RawType beta =
      TwoDInterpPolicy::ZXInterpPolicy::calculateUnitBaseIndepVar(
                                                    x_indep_value,
                                                    lower_bin_boundary->first,
                                                    x_bin_length );

    // Get the lower secondary indep grid limits at the primary value
    YIndepType min_y_indep_value =
      TwoDInterpPolicy::YXInterpPolicy::interpolate(
                      beta,
                      lower_bin_boundary->second->getLowerBoundOfIndepVar(),
                      upper_bin_boundary->second->getLowerBoundOfIndepVar() );

    // Get the upper secondary indep grid limits at the primary value
    YIndepType max_y_indep_value =
      TwoDInterpPolicy::YXInterpPolicy::interpolate(
                      beta,
                      lower_bin_boundary->second->getUpperBoundOfIndepVar(),
                      upper_bin_boundary->second->getUpperBoundOfIndepVar() );

    // Calculate the correlated y value at the lower and upper bin boundary
    YIndepType lower_y_value, upper_y_value;

    YIndepType min_y_indep_value_with_tol =
      TwoDInterpPolicy::ZYInterpPolicy::calculateFuzzyLowerBound(
                        min_y_indep_value,
                        fuzzy_boundary_tol );

    YIndepType max_y_indep_value_with_tol =
      TwoDInterpPolicy::ZYInterpPolicy::calculateFuzzyUpperBound(
                        max_y_indep_value,
                        fuzzy_boundary_tol );

    // Check for a secondary indep value outside of the secondary indep grid limits
    if ( y_indep_value < min_y_indep_value_with_tol || y_indep_value > max_y_indep_value_with_tol )
      return QuantityTraits<ReturnType>::zero();
    else if ( y_indep_value <= min_y_indep_value && y_indep_value >= min_y_indep_value_with_tol ) // At min y value
    {
      lower_y_value = lower_bin_boundary->second->getLowerBoundOfIndepVar();
      upper_y_value = upper_bin_boundary->second->getLowerBoundOfIndepVar();
    }
    else if ( y_indep_value >= max_y_indep_value && y_indep_value <= max_y_indep_value_with_tol ) // At max y value
    {
      lower_y_value = lower_bin_boundary->second->getUpperBoundOfIndepVar();
      upper_y_value = upper_bin_boundary->second->getUpperBoundOfIndepVar();
    }
    else // Between min and max y values
    {
      Details::CorrelatedEvaluatePDFSecondaryIndepHelper<BaseUnivariateDistributionType>::template calculateSecondaryIndepValues<TwoDInterpPolicy>(
                                                      evaluate,
                                                      y_indep_value,
                                                      lower_bin_boundary,
                                                      upper_bin_boundary,
                                                      beta,
                                                      fuzzy_boundary_tol,
                                                      rel_error_tol,
                                                      error_tol,
                                                      max_number_of_iterations,
                                                      lower_y_value,
                                                      upper_y_value );
    }

    ReturnType lower_eval = ((*lower_bin_boundary->second).*evaluate)(lower_y_value);
    ReturnType upper_eval = ((*upper_bin_boundary->second).*evaluate)(upper_y_value);

    if( lower_eval == upper_eval )
      return lower_eval;
    else
    {
      return Details::CorrelatedEvaluatePDFHelper<typename TwoDInterpPolicy::YXInterpPolicy>::evaluate(
                                                          y_indep_value,
                                                          lower_y_value,
                                                          lower_eval,
                                                          upper_y_value,
                                                          upper_eval,
                                                          beta );
    }
  }
}

// Evaluate the CDF between bin boundaries using the desired evaluation method
/*! \details The EvaluationMethod must evalute using a Cosine variable. This
 *  function uses an iterative method to estimate the CDF for correlated sampling
 *  to a relative error tolerance in order to get the proper interpolation
 *  parameters.
 */
template<typename _TwoDInterpPolicy>
template<typename BaseUnivariateDistributionType,
         typename XIndepType,
         typename YIndepType,
         typename YZIterator,
         typename EvaluationMethod,
         typename YBoundsFunctor>
double Correlated<_TwoDInterpPolicy>::evaluateCDFCos(
                                  const XIndepType& x_indep_value,
                                  const YIndepType& y_indep_value,
                                  const YBoundsFunctor& min_y_indep_functor,
                                  const YBoundsFunctor& max_y_indep_functor,
                                  const EvaluationMethod& evaluate,
                                  const YZIterator& lower_bin_boundary,
                                  const YZIterator& upper_bin_boundary,
                                  const double fuzzy_boundary_tol,
                                  const double rel_error_tol,
                                  const double error_tol,
                                  unsigned max_number_of_iterations )
{
  // Check to see if the x indep value is on the grid limits
  if( lower_bin_boundary->first == x_indep_value )
  {
    return ((*lower_bin_boundary->second).*evaluate)(y_indep_value);
  }
  else if( upper_bin_boundary->first == x_indep_value )
  {
    return ((*upper_bin_boundary->second).*evaluate)(y_indep_value);
  }
  else // x indep value is in between the grid limits
  {
    // Get the min and max y value at the given x value
    YIndepType min_y_indep_value = min_y_indep_functor( x_indep_value );
    YIndepType max_y_indep_value = max_y_indep_functor( x_indep_value );

    // Calculate the CDF value
    if ( y_indep_value <= min_y_indep_value )
      return 0.0;
    else if ( y_indep_value >= max_y_indep_value )
      return 1.0;
    else
    {
      // Calculate the bin length of the x variable
      const typename QuantityTraits<XIndepType>::RawType x_bin_length =
        TwoDInterpPolicy::ZXInterpPolicy::calculateUnitBaseGridLength(
                                                      lower_bin_boundary->first,
                                                      upper_bin_boundary->first );

        // Calculate the x variable bin ratio (beta)
      const typename QuantityTraits<XIndepType>::RawType beta =
        TwoDInterpPolicy::ZXInterpPolicy::calculateUnitBaseIndepVar(
                                                      x_indep_value,
                                                      lower_bin_boundary->first,
                                                      x_bin_length );

      // Get the lower and upper boundaries of the evaluated cdf
      double lower_cdf_bound, upper_cdf_bound;
      {
        // Evaluate the cdf at the upper and lower bin boundaries
        double bin_eval_0 =
          ((*lower_bin_boundary->second).*&BaseUnivariateDistributionType::evaluateCDF)( y_indep_value );
        double bin_eval_1 =
          ((*upper_bin_boundary->second).*&BaseUnivariateDistributionType::evaluateCDF)( y_indep_value );

        if ( bin_eval_0 <= bin_eval_1 )
        {
          lower_cdf_bound = bin_eval_0;
          upper_cdf_bound = bin_eval_1;
        }
        else
        {
          lower_cdf_bound = bin_eval_1;
          upper_cdf_bound = bin_eval_0;
        }
      }

      YIndepType lower_y_value, upper_y_value;

      double est_cdf =
        Details::CorrelatedEvaluatePDFSecondaryIndepHelper<BaseUnivariateDistributionType>::template estimateCDF<TwoDInterpPolicy>(
                                        lower_cdf_bound,
                                        upper_cdf_bound,
                                        lower_y_value,
                                        upper_y_value,
                                        beta,
                                        y_indep_value,
                                        lower_bin_boundary,
                                        upper_bin_boundary,
                                        rel_error_tol,
                                        error_tol,
                                        max_number_of_iterations );

      return est_cdf;
    }
  }
}

// Evaluate the CDF between bin boundaries using the desired evaluation method
/*! \details This function uses an iterative method to estimate the CDF for
 *  correlated sampling to a relative error tolerance in order to get the proper
 *  interpolation parameters.
 */
template<typename _TwoDInterpPolicy>
template<typename BaseUnivariateDistributionType,
         typename XIndepType,
         typename YIndepType,
         typename YZIterator,
         typename EvaluationMethod,
         typename YBoundsFunctor>
double Correlated<_TwoDInterpPolicy>::evaluateCDF(
                                const XIndepType& x_indep_value,
                                const YIndepType& y_indep_value,
                                const YBoundsFunctor& min_y_indep_functor,
                                const YBoundsFunctor& max_y_indep_functor,
                                const EvaluationMethod& evaluate,
                                const YZIterator& lower_bin_boundary,
                                const YZIterator& upper_bin_boundary,
                                const double fuzzy_boundary_tol,
                                const double rel_error_tol,
                                const double error_tol,
                                unsigned max_number_of_iterations )
{
  // Check to see if the x indep value is on the bin limits
  if( lower_bin_boundary->first == x_indep_value )
  {
    return ((*lower_bin_boundary->second).*evaluate)(y_indep_value);
  }
  else if( upper_bin_boundary->first == x_indep_value )
  {
    return ((*upper_bin_boundary->second).*evaluate)(y_indep_value);
  }
  else // x indep value is in between the grid limits
  {
    // Calculate the bin length of the x variable
    const typename QuantityTraits<XIndepType>::RawType x_bin_length =
      TwoDInterpPolicy::ZXInterpPolicy::calculateUnitBaseGridLength(
                                                    lower_bin_boundary->first,
                                                    upper_bin_boundary->first );

      // Calculate the x variable bin ratio (beta)
    const typename QuantityTraits<XIndepType>::RawType beta =
      TwoDInterpPolicy::ZXInterpPolicy::calculateUnitBaseIndepVar(
                                                    x_indep_value,
                                                    lower_bin_boundary->first,
                                                    x_bin_length );

    // Get the lower secondary indep grid limits at the primary value
    YIndepType min_y_indep_value =
      TwoDInterpPolicy::YXInterpPolicy::interpolate(
                      beta,
                      lower_bin_boundary->second->getLowerBoundOfIndepVar(),
                      upper_bin_boundary->second->getLowerBoundOfIndepVar() );

    // Get the upper secondary indep grid limits at the primary value
    YIndepType max_y_indep_value =
      TwoDInterpPolicy::YXInterpPolicy::interpolate(
                      beta,
                      lower_bin_boundary->second->getUpperBoundOfIndepVar(),
                      upper_bin_boundary->second->getUpperBoundOfIndepVar() );

    // Calculate the CDF value
    if ( y_indep_value <= min_y_indep_value )
      return 0.0;
    else if ( y_indep_value >= max_y_indep_value )
      return 1.0;
    else
    {
      // Get the lower and upper boundaries of the evaluated cdf
      double lower_cdf_bound, upper_cdf_bound;
      {
        // Evaluate the cdf at the upper and lower bin boundaries
        double bin_eval_0 =
          ((*lower_bin_boundary->second).*&BaseUnivariateDistributionType::evaluateCDF)( y_indep_value );
        double bin_eval_1 =
          ((*upper_bin_boundary->second).*&BaseUnivariateDistributionType::evaluateCDF)( y_indep_value );

        if ( bin_eval_0 <= bin_eval_1 )
        {
          lower_cdf_bound = bin_eval_0;
          upper_cdf_bound = bin_eval_1;
        }
        else
        {
          lower_cdf_bound = bin_eval_1;
          upper_cdf_bound = bin_eval_0;
        }
      }

      YIndepType lower_y_value, upper_y_value;
      double est_cdf =
        Details::CorrelatedEvaluatePDFSecondaryIndepHelper<BaseUnivariateDistributionType>::template estimateCDF<TwoDInterpPolicy>(
                                        lower_cdf_bound,
                                        upper_cdf_bound,
                                        lower_y_value,
                                        upper_y_value,
                                        beta,
                                        y_indep_value,
                                        lower_bin_boundary,
                                        upper_bin_boundary,
                                        rel_error_tol,
                                        error_tol,
                                        max_number_of_iterations );

      return est_cdf;
    }
  }
}

// Sample between bin boundaries using the desired sampling functor
/*! \details A direct correlated routine is used to sample the distribution.
 * In order for this method to calculate a sample accurately the same random
 * number must be used to sample from the distribution on the lower and upper
 * bounds. The sample functor must therefore wrap the
 * Utility::TabularUnivariateDist::sampleWithRandomNumber routine or one of the
 * similar methods that takes a random number.
 */
template<typename _TwoDInterpPolicy>
template<typename XIndepType,
         typename YIndepType,
         typename YZIterator,
         typename SampleFunctor,
         typename YBoundsFunctor>
YIndepType Correlated<_TwoDInterpPolicy>::sample(
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

  return Correlated<TwoDInterpPolicy>::sampleDetailed<XIndepType,YIndepType,YZIterator,SampleFunctor>(
            sample_functor,
            min_y_indep_functor,
            max_y_indep_functor,
            x_indep_value,
            lower_bin_boundary,
            upper_bin_boundary,
            dummy_sampled_bin_boundary,
            dummy_raw_sample );
}

// Sample between bin boundaries using the desired sampling functor
/*! \details The SampleFunctor must return a Cosine variable.
 * A direct correlated routine is used to sample the distribution.
 * In order for this method to calculate a sample accurately the same random
 * number must be used to sample from the distribution on the lower and upper
 * bounds. The sample functor must therefore wrap the
 * Utility::TabularUnivariateDist::sampleWithRandomNumber routine or one of the
 * similar methods that takes a random number.
 */
template<typename _TwoDInterpPolicy>
template<typename XIndepType,
         typename YIndepType,
         typename YZIterator,
         typename SampleFunctor>
YIndepType Correlated<_TwoDInterpPolicy>::sampleCos(
                             const SampleFunctor& sample_functor,
                             const XIndepType& x_indep_value,
                             const YZIterator& lower_bin_boundary,
                             const YZIterator& upper_bin_boundary )
{
  // Dummy variables
  YIndepType dummy_raw_sample;
  YZIterator dummy_sampled_bin_boundary;

  return Correlated<TwoDInterpPolicy>::sampleCosDetailed<XIndepType,YIndepType,YZIterator,SampleFunctor>(
            sample_functor,
            x_indep_value,
            lower_bin_boundary,
            upper_bin_boundary,
            dummy_sampled_bin_boundary,
            dummy_raw_sample );
}

// Sample between bin boundaries using the desired subrange sampling functor
/* \details A direct correlated routine is used to sample the distribution.
 * In order for this method to calculate a sample accurately the same random
 * number must be used to sample from the distribution on the lower and upper
 * bounds. The sample functor must therefore wrap the
 * Utility::TabularUnivariateDist::sampleWithRandomNumberInSubrange routine.
 */
template<typename _TwoDInterpPolicy>
template<typename XIndepType,
         typename YIndepType,
         typename YZIterator,
         typename SampleFunctor,
         typename YBoundsFunctor>
YIndepType Correlated<_TwoDInterpPolicy>::sampleInSubrange(
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
  YIndepType max_y_indep_value_0 =
    lower_bin_boundary->second->getUpperBoundOfIndepVar();

  // Only set the subrange if it is below the max y indep value
  if( subrange_max_y_indep_value < max_y_indep_value_0 )
    max_y_indep_value_0 = subrange_max_y_indep_value;

  // Get the max y indep value at the upper bin boundary
  YIndepType max_y_indep_value_1 =
    upper_bin_boundary->second->getUpperBoundOfIndepVar();

  // Only set the subrange if it is below the max y indep value
  if( subrange_max_y_indep_value < max_y_indep_value_1 )
    max_y_indep_value_1 = subrange_max_y_indep_value;

  // Check for a primary value at the primary grid upper limit
  if( x_indep_value == upper_bin_boundary->first )
  {
    return subrange_sample_functor( *upper_bin_boundary->second,
                                    max_y_indep_value_0 );
  }
  // Check for a primary value at the primary grid lower limit
  else if( x_indep_value == lower_bin_boundary->first )
  {
    return subrange_sample_functor( *lower_bin_boundary->second,
                                    max_y_indep_value_1 );
  }
  else
  {
    YIndepType lower_sample =
      subrange_sample_functor( *lower_bin_boundary->second,
                               max_y_indep_value_0 );
    YIndepType upper_sample =
      subrange_sample_functor( *upper_bin_boundary->second,
                               max_y_indep_value_1 );

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
/*! \details A direct correlated routine is used to sample the distribution.
 * In order for this method to calculate a sample accurately the same random
 * number must be used to sample from the distribution on the lower and upper
 * bounds. The sample functor must therefore wrap the
 * Utility::TabularUnivariateDist::sampleWithRandomNumber routine or one of the
 * similar methods that takes a random number.
 */
template<typename _TwoDInterpPolicy>
template<typename XIndepType,
         typename YIndepType,
         typename YZIterator,
         typename SampleFunctor,
         typename YBoundsFunctor>
YIndepType Correlated<_TwoDInterpPolicy>::sampleDetailed(
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
/*! \details The SampleFunctor must return a Cosine variable.
 * A direct correlated routine is used to sample the distribution.
 * In order for this method to calculate a sample accurately the same random
 * number must be used to sample from the distribution on the lower and upper
 * bounds. The sample functor must therefore wrap the
 * Utility::TabularUnivariateDist::sampleWithRandomNumber routine or one of the
 * similar methods that takes a random number.
 */
template<typename _TwoDInterpPolicy>
template<typename XIndepType,
         typename YIndepType,
         typename YZIterator,
         typename SampleFunctor>
YIndepType Correlated<_TwoDInterpPolicy>::sampleCosDetailed(
            const SampleFunctor& sample_functor,
            const XIndepType& x_indep_value,
            const YZIterator& lower_bin_boundary,
            const YZIterator& upper_bin_boundary,
            YZIterator& sampled_bin_boundary,
            YIndepType& raw_sample )
{
  // Dummy variables
  double dummy_functor;

  return Correlated<TwoDInterpPolicy>::sampleDetailed<XIndepType,YIndepType,YZIterator,SampleFunctor>(
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
template<typename _TwoDInterpPolicy>
inline const std::string Correlated<_TwoDInterpPolicy>::name()
{
  return "Correlated";
}

// Calculate the Y independent lower bound between bin boundaries
template<typename _TwoDInterpPolicy>
template<typename YIndepType,
         typename XIndepType,
         typename YZIterator>
auto UnitBaseCorrelated<_TwoDInterpPolicy>::calculateLowerBound(
                      const XIndepType& x_indep_value,
                      const YZIterator& lower_bin_boundary,
                      const YZIterator& upper_bin_boundary ) -> YIndepType
{
  return UnitBase<TwoDInterpPolicy>::template calculateLowerBound<YIndepType, XIndepType, YZIterator>(
                        x_indep_value,
                        lower_bin_boundary,
                        upper_bin_boundary );
}

// Calculate the Y independent upper bound between bin boundaries
template<typename _TwoDInterpPolicy>
template<typename YIndepType,
         typename XIndepType,
         typename YZIterator>
auto UnitBaseCorrelated<_TwoDInterpPolicy>::calculateUpperBound(
                      const XIndepType& x_indep_value,
                      const YZIterator& lower_bin_boundary,
                      const YZIterator& upper_bin_boundary ) -> YIndepType
{
  return UnitBase<TwoDInterpPolicy>::template calculateUpperBound<YIndepType, XIndepType, YZIterator>(
                        x_indep_value,
                        lower_bin_boundary,
                        upper_bin_boundary );
}

// Evaluate the PDF between bin boundaries using the desired evaluation method
/*! \details The EvaluationMethod must evalute using a Cosine variable. This
 *  method uses an iterative method to estimate the CDF for unit-base correlated
 *  sampling to a relative error tolerance in order to get the proper
 *  interpolation parameters. The lower and upper bounds of the secondary
 *  independent variable (cosine) are fixed (-1 <= cosine <= 1). Therefore a
 *  unit base method is not necessary and the direct correlated method is used
 *  to evaluate instead.
 */
template<typename _TwoDInterpPolicy>
template<typename BaseUnivariateDistributionType,
         typename XIndepType,
         typename YIndepType,
         typename ReturnType,
         typename YZIterator,
         typename EvaluationMethod,
         typename YBoundsFunctor>
ReturnType UnitBaseCorrelated<_TwoDInterpPolicy>::evaluatePDFCos(
                                  const XIndepType& x_indep_value,
                                  const YIndepType& y_indep_value,
                                  const YBoundsFunctor& min_y_indep_functor,
                                  const YBoundsFunctor& max_y_indep_functor,
                                  const EvaluationMethod& evaluate,
                                  const YZIterator& lower_bin_boundary,
                                  const YZIterator& upper_bin_boundary,
                                  const double fuzzy_boundary_tol,
                                  const double rel_error_tol,
                                  const double error_tol,
                                  unsigned max_number_of_iterations )
{
  return Correlated<TwoDInterpPolicy>::template evaluatePDFCos<
                                                      BaseUnivariateDistributionType,
                                                      XIndepType,
                                                      YIndepType,
                                                      ReturnType,
                                                      YZIterator,
                                                      EvaluationMethod,
                                                      YBoundsFunctor>(
                                                    x_indep_value,
                                                    y_indep_value,
                                                    min_y_indep_functor,
                                                    max_y_indep_functor,
                                                    evaluate,
                                                    lower_bin_boundary,
                                                    upper_bin_boundary,
                                                    fuzzy_boundary_tol,
                                                    rel_error_tol,
                                                    error_tol,
                                                    max_number_of_iterations );
}

namespace Details{

/*! The helper struct used to calculate the secondary independent value
 *
 * Specialization of this class for different UnivariateDistribution classes is
 * required.
 */
template<typename BaseUnivariateDistributionType>
struct UnitBaseCorrelatedEvaluatePDFSecondaryIndepHelper
{
  //! Typdef for this type
  typedef UnitBaseCorrelatedEvaluatePDFSecondaryIndepHelper<BaseUnivariateDistributionType> ThisType;

  //! Calculate the secondary independent values
  template<typename TwoDInterpPolicy,
           typename YIndepType,
           typename YZIterator,
           typename EvaluationMethod,
           typename T>
  static void calculateSecondaryIndepValues(
             const EvaluationMethod& evaluate,
             const YIndepType& min_y_indep_value,
             const YIndepType& max_y_indep_value,
             const YIndepType& y_indep_value,
             const T& beta,
             const typename QuantityTraits<YIndepType>::RawType& grid_length_0,
             const typename QuantityTraits<YIndepType>::RawType& grid_length_1,
             const typename QuantityTraits<YIndepType>::RawType& intermediate_grid_length,
             const YZIterator& lower_bin_boundary,
             const YZIterator& upper_bin_boundary,
             const double fuzzy_boundary_tol,
             const double rel_error_tol,
             const double error_tol,
             const unsigned max_number_of_iterations,
             YIndepType& lower_y_value,
             YIndepType& upper_y_value )
  {
    BaseUnivariateDistributionType::thisDistTypeIsNotCompatibleWithUnitBaseCorrelatedEvaluation();
  }

  // Estimate the interpolated CDF and the corresponding lower and upper y
  // indep values
  template<typename TwoDInterpPolicy,
           typename YIndepType,
           typename YZIterator,
           typename T>
  static double estimateCDF(
             double& lower_cdf_est,
             double& upper_cdf_est,
             YIndepType& y_indep_value_0,
             YIndepType& y_indep_value_1,
             const T& beta,
             const typename QuantityTraits<YIndepType>::RawType& grid_length_0,
             const typename QuantityTraits<YIndepType>::RawType& grid_length_1,
             const typename QuantityTraits<YIndepType>::RawType& eta,
             const YZIterator& lower_bin_boundary,
             const YZIterator& upper_bin_boundary,
             const double rel_error_tol = 1e-7,
             const double error_tol = 1e-15,
             unsigned max_number_of_iterations = 500u )
  {
    BaseUnivariateDistributionType::thisDistTypeIsNotCompatibleWithUnitBaseCorrelatedEvaluation();
  }

  // Evaluate the interpolated eta at the CDF value
  template<typename TwoDInterpPolicy,
           typename YIndepType,
           typename YZIterator,
           typename T>
  static double evaluateEta(
             double& cdf,
             const T& beta,
             const typename QuantityTraits<YIndepType>::RawType& grid_length_0,
             const typename QuantityTraits<YIndepType>::RawType& grid_length_1,
             const YZIterator& lower_bin_boundary,
             const YZIterator& upper_bin_boundary,
             YIndepType& y_indep_value_0,
             YIndepType& y_indep_value_1 )
  {
    BaseUnivariateDistributionType::thisDistTypeIsNotCompatibleWithUnitBaseCorrelatedEvaluation();
  }
};

/*! \brief Partial specialization of the
 * Utility::Details::UnitBaseCorrelatedEvaluatePDFSecondaryIndepHelper class
 * for Utility::UnitAwareTabularUnivariateDistribution
 */
template<typename _T, typename _U>
struct UnitBaseCorrelatedEvaluatePDFSecondaryIndepHelper<Utility::UnitAwareTabularUnivariateDistribution<_T,_U> >
{
  //! Typdef for this type
  typedef UnitBaseCorrelatedEvaluatePDFSecondaryIndepHelper<Utility::UnitAwareTabularUnivariateDistribution<_T,_U> > ThisType;

  //! Calculate the secondary independent values
  template<typename TwoDInterpPolicy,
           typename YIndepType,
           typename YZIterator,
           typename EvaluationMethod,
           typename T>
  static void calculateSecondaryIndepValues(
             const EvaluationMethod& evaluate,
             const YIndepType& min_y_indep_value,
             const YIndepType& max_y_indep_value,
             const YIndepType& y_indep_value,
             const T& beta,
             const typename QuantityTraits<YIndepType>::RawType& grid_length_0,
             const typename QuantityTraits<YIndepType>::RawType& grid_length_1,
             const typename QuantityTraits<YIndepType>::RawType& intermediate_grid_length,
             const YZIterator& lower_bin_boundary,
             const YZIterator& upper_bin_boundary,
             const double fuzzy_boundary_tol,
             const double rel_error_tol,
             const double error_tol,
             const unsigned max_number_of_iterations,
             YIndepType& lower_y_value,
             YIndepType& upper_y_value );

  // Estimate the interpolated CDF and the corresponding lower and upper y
  // indep values
  template<typename TwoDInterpPolicy,
           typename YIndepType,
           typename YZIterator,
           typename T>
  static double estimateCDF(
             double& lower_cdf_est,
             double& upper_cdf_est,
             YIndepType& y_indep_value_0,
             YIndepType& y_indep_value_1,
             const T& beta,
             const typename QuantityTraits<YIndepType>::RawType& grid_length_0,
             const typename QuantityTraits<YIndepType>::RawType& grid_length_1,
             const typename QuantityTraits<YIndepType>::RawType& eta,
             const YZIterator& lower_bin_boundary,
             const YZIterator& upper_bin_boundary,
             const double rel_error_tol = 1e-7,
             const double error_tol = 1e-15,
             unsigned max_number_of_iterations = 500u );

  // Evaluate the interpolated eta at the CDF value
  template<typename TwoDInterpPolicy,
           typename YIndepType,
           typename YZIterator,
           typename T>
  static double evaluateEta(
             double& cdf,
             const T& beta,
             const typename QuantityTraits<YIndepType>::RawType& grid_length_0,
             const typename QuantityTraits<YIndepType>::RawType& grid_length_1,
             const YZIterator& lower_bin_boundary,
             const YZIterator& upper_bin_boundary,
             YIndepType& y_indep_value_0,
             YIndepType& y_indep_value_1 );
};

// Calculate the secondary independent values
template<typename _T, typename _U>
template<typename TwoDInterpPolicy,
         typename YIndepType,
         typename YZIterator,
         typename EvaluationMethod,
         typename T>
void UnitBaseCorrelatedEvaluatePDFSecondaryIndepHelper<Utility::UnitAwareTabularUnivariateDistribution<_T,_U> >::calculateSecondaryIndepValues(
             const EvaluationMethod& evaluate,
             const YIndepType& min_y_indep_value,
             const YIndepType& max_y_indep_value,
             const YIndepType& y_indep_value,
             const T& beta,
             const typename QuantityTraits<YIndepType>::RawType& grid_length_0,
             const typename QuantityTraits<YIndepType>::RawType& grid_length_1,
             const typename QuantityTraits<YIndepType>::RawType& intermediate_grid_length,
             const YZIterator& lower_bin_boundary,
             const YZIterator& upper_bin_boundary,
             const double fuzzy_boundary_tol,
             const double rel_error_tol,
             const double error_tol,
             const unsigned max_number_of_iterations,
             YIndepType& lower_y_value,
             YIndepType& upper_y_value )
{
  // Get the lower and upper boundaries of the evaluated cdf
  double lower_cdf_bound, upper_cdf_bound;
  typename QuantityTraits<YIndepType>::RawType eta;

  {
    YIndepType min_y_indep_value_with_tol =
      TwoDInterpPolicy::ZYInterpPolicy::calculateFuzzyLowerBound(
                        min_y_indep_value,
                        fuzzy_boundary_tol );

    YIndepType max_y_indep_value_with_tol =
      TwoDInterpPolicy::ZYInterpPolicy::calculateFuzzyUpperBound(
                        max_y_indep_value,
                        fuzzy_boundary_tol );

    // Calculate the unit base variable on the intermediate grid
    eta = TwoDInterpPolicy::ZYInterpPolicy::calculateUnitBaseIndepVar(
                y_indep_value,
                min_y_indep_value,
                intermediate_grid_length,
                fuzzy_boundary_tol );

    // Get the y indep var value for the upper and lower bin boundaries
    YIndepType y_indep_value_0 =
      TwoDInterpPolicy::ZYInterpPolicy::calculateIndepVar(
                        eta,
                        lower_bin_boundary->second->getLowerBoundOfIndepVar(),
                        grid_length_0,
                        fuzzy_boundary_tol );

    YIndepType y_indep_value_1 =
      TwoDInterpPolicy::ZYInterpPolicy::calculateIndepVar(
                        eta,
                        upper_bin_boundary->second->getLowerBoundOfIndepVar(),
                        grid_length_1,
                        fuzzy_boundary_tol );

    // Evaluate the cdf at the upper and lower bin boundaries
    double bin_eval_0 =
      ((*lower_bin_boundary->second).*&Utility::UnitAwareTabularUnivariateDistribution<_T,_U>::evaluateCDF)( y_indep_value_0 );
    double bin_eval_1 =
      ((*upper_bin_boundary->second).*&Utility::UnitAwareTabularUnivariateDistribution<_T,_U>::evaluateCDF)( y_indep_value_1 );

    if ( bin_eval_0 <= bin_eval_1 )
    {
      lower_cdf_bound = bin_eval_0;
      upper_cdf_bound = bin_eval_1;
    }
    else
    {
      lower_cdf_bound = bin_eval_1;
      upper_cdf_bound = bin_eval_0;
    }

    // Make sure the estimates are valid
    YIndepType dummy_y0, dummy_y1;
    typename QuantityTraits<YIndepType>::RawType lower_eta_estimate, upper_eta_estimate;

    lower_eta_estimate =
      ThisType::evaluateEta<TwoDInterpPolicy>(
          lower_cdf_bound,
          beta,
          grid_length_0,
          grid_length_1,
          lower_bin_boundary,
          upper_bin_boundary,
          dummy_y0,
          dummy_y1 );

    upper_eta_estimate =
      ThisType::evaluateEta<TwoDInterpPolicy>(
          upper_cdf_bound,
          beta,
          grid_length_0,
          grid_length_1,
          lower_bin_boundary,
          upper_bin_boundary,
          dummy_y0,
          dummy_y1 );

    while( lower_eta_estimate > eta )
    {
      upper_cdf_bound = lower_cdf_bound;
      lower_cdf_bound *= 0.99;

      if( lower_cdf_bound == 0.0 )
        break;

      lower_eta_estimate = ThisType::evaluateEta<TwoDInterpPolicy>(
            lower_cdf_bound,
            beta,
            grid_length_0,
            grid_length_1,
            lower_bin_boundary,
            upper_bin_boundary,
            dummy_y0,
            dummy_y1 );
    }

    while( upper_eta_estimate < eta )
    {
      lower_cdf_bound = upper_cdf_bound;
      upper_cdf_bound *= 1.01;

      if( upper_cdf_bound >= 1.0 )
      {
        upper_cdf_bound = 1.0;
        break;
      }

      upper_eta_estimate = ThisType::evaluateEta<TwoDInterpPolicy>(
            upper_cdf_bound,
            beta,
            grid_length_0,
            grid_length_1,
            lower_bin_boundary,
            upper_bin_boundary,
            dummy_y0,
            dummy_y1 );
    }
  }

  ThisType::estimateCDF<TwoDInterpPolicy>( lower_cdf_bound,
                                           upper_cdf_bound,
                                           lower_y_value,
                                           upper_y_value,
                                           beta,
                                           grid_length_0,
                                           grid_length_1,
                                           eta,
                                           lower_bin_boundary,
                                           upper_bin_boundary,
                                           rel_error_tol,
                                           error_tol,
                                           max_number_of_iterations );
}

// Estimate the interpolated CDF and the corresponding lower and upper y
// indep values
template<typename _T, typename _U>
template<typename TwoDInterpPolicy,
         typename YIndepType,
         typename YZIterator,
         typename T>
double UnitBaseCorrelatedEvaluatePDFSecondaryIndepHelper<Utility::UnitAwareTabularUnivariateDistribution<_T,_U> >::estimateCDF(
             double& lower_cdf_est,
             double& upper_cdf_est,
             YIndepType& y_indep_value_0,
             YIndepType& y_indep_value_1,
             const T& beta,
             const typename QuantityTraits<YIndepType>::RawType& grid_length_0,
             const typename QuantityTraits<YIndepType>::RawType& grid_length_1,
             const typename QuantityTraits<YIndepType>::RawType& eta,
             const YZIterator& lower_bin_boundary,
             const YZIterator& upper_bin_boundary,
             const double rel_error_tol,
             const double error_tol,
             unsigned max_number_of_iterations )
{
  unsigned number_of_iterations = 0;
  double rel_error = 1.0;
  typename QuantityTraits<YIndepType>::RawType error_norm_constant = eta;
  double tolerance = rel_error_tol;

  /*! \detials If the y indep var value is zero the relative error
    *  will always zero or inf. When this is the case the error tolerance will
    *  be used instead of the relative error tolerance.
    */
    if ( eta == 0.0 )
    {
      error_norm_constant = 1.0;
      tolerance = error_tol;
    }

  // Refine the estimated cdf value until it meet the tolerance
  double estimated_cdf = 0.0;
  while ( rel_error > tolerance )
  {
    // Estimate the cdf as the midpoint of the lower and upper boundaries
    estimated_cdf = 0.5*( lower_cdf_est + upper_cdf_est );

    auto&& eta_estimate =
        ThisType::evaluateEta<TwoDInterpPolicy>( estimated_cdf,
                                                 beta,
                                                 grid_length_0,
                                                 grid_length_1,
                                                 lower_bin_boundary,
                                                 upper_bin_boundary,
                                                 y_indep_value_0,
                                                 y_indep_value_1 );

    // Update the number of iterations
    ++number_of_iterations;

    if ( eta == eta_estimate )
      break;

    // Calculate the relative error between eta and the estimate
    rel_error = ( eta - eta_estimate )/error_norm_constant;

    // Make sure the relative error is positive
    rel_error = rel_error < 0 ? -rel_error : rel_error;

    // If tolerance is met exit loop
    if ( rel_error <= tolerance )
      break;

    // Update the estimated_cdf estimate
    if ( eta_estimate < eta )
    {
      // Old estimated_cdf estimate is new lower cdf boundary
      lower_cdf_est = estimated_cdf;
    }
    else
    {
      // Old estimated_cdf estimate is new upper cdf boundary
      upper_cdf_est = estimated_cdf;
    }

    // Check for the max number of iterations
    if ( number_of_iterations > max_number_of_iterations )
    {
      // Get error in estimate
      double error = ( eta - eta_estimate );
      error = error < 0 ? -error : error;

      // If error meets error tolerance accept estimate
      if ( error < error_tol )
          break;
      else
      {
        std::ostringstream oss;
        oss.precision( 18 );
        oss << "max number of iterations (" << max_number_of_iterations
            << ") hit before convergence (" << rel_error_tol << ")- "
            << "(y0,y1) = (" << y_indep_value_0 << "," << y_indep_value_1
            << "), (cdf_0,cdf_1) = (" << lower_cdf_est << "," << upper_cdf_est
            << "), relError(eta,eta_exact) = relError(" << eta_estimate
            << "," << eta << ") = " << rel_error;


        THROW_EXCEPTION( std::runtime_error, oss.str() );
      }
    }
  }

  return estimated_cdf;
}


// Evaluate the interpolated eta at the CDF value
template<typename _T, typename _U>
template<typename TwoDInterpPolicy,
         typename YIndepType,
         typename YZIterator,
         typename T>
  double UnitBaseCorrelatedEvaluatePDFSecondaryIndepHelper<Utility::UnitAwareTabularUnivariateDistribution<_T,_U> >::evaluateEta(
             double& cdf,
             const T& beta,
             const typename QuantityTraits<YIndepType>::RawType& grid_length_0,
             const typename QuantityTraits<YIndepType>::RawType& grid_length_1,
             const YZIterator& lower_bin_boundary,
             const YZIterator& upper_bin_boundary,
             YIndepType& y_indep_value_0,
             YIndepType& y_indep_value_1 )
  {
    // Get the sampled values at the upper and lower bin for the cdf
    y_indep_value_0 =
      ((*lower_bin_boundary->second).*&Utility::UnitAwareTabularUnivariateDistribution<_T,_U>::sampleWithRandomNumber)( cdf );
    y_indep_value_1 =
      ((*upper_bin_boundary->second).*&Utility::UnitAwareTabularUnivariateDistribution<_T,_U>::sampleWithRandomNumber)( cdf );

    // Calculate the unit base variable on the intermediate grid corresponding to the
    // raw samples on the lower and upper boundaries
    typename QuantityTraits<YIndepType>::RawType eta_0, eta_1;

    eta_0 =
      TwoDInterpPolicy::ZYInterpPolicy::calculateUnitBaseIndepVar(
          y_indep_value_0,
          lower_bin_boundary->second->getLowerBoundOfIndepVar(),
          grid_length_0 );

    eta_1 =
      TwoDInterpPolicy::ZYInterpPolicy::calculateUnitBaseIndepVar(
          y_indep_value_1,
          upper_bin_boundary->second->getLowerBoundOfIndepVar(),
          grid_length_1 );

    // Interpolate using the templated TwoDInterpPolicy::YXInterpPolicy
    return TwoDInterpPolicy::YXInterpPolicy::interpolate( beta, eta_0, eta_1 );
  }

/*! \brief Base helper struct for calculating the PDF of a bivariate
 * distribution assuming linear interpolation with the secondary indep grid
 * The PDF for lin-lin interpolation is defined as:
 * f(x,y) = 1/L * ( L_0f_0( y_0 ) * L_1f_1( y_1 ) )/
 *          ( L_1f_1(y_1) + ( L_0f_0(y_0) - L_1f_1(y_1) )* beta )
 */
struct UnitBaseCorrelatedEvaluatePDFHelperLinBase
{
  template<typename YIndepType,
           typename ReturnType,
           typename T>
  static inline ReturnType evaluate(
   const YIndepType y_indep_value,
   const YIndepType y_min_indep_value,
   const typename QuantityTraits<YIndepType>::RawType intermediate_grid_length,
   const YIndepType lower_y_indep_value,
   const YIndepType lower_y_min_indep_value,
   const typename QuantityTraits<YIndepType>::RawType lower_grid_length,
   const ReturnType lower_eval,
   const YIndepType upper_y_indep_value,
   const YIndepType upper_y_min_indep_value,
   const typename QuantityTraits<YIndepType>::RawType upper_grid_length,
   const ReturnType upper_eval,
   const T eta,
   const T beta )
  {
    auto lower_product = lower_eval*lower_grid_length;
    auto upper_product = upper_eval*upper_grid_length;

    return (lower_product*upper_product)/LinLin::interpolate( beta, upper_product, lower_product )/intermediate_grid_length;
  }
};

/*! \brief Base helper struct for calculating the PDF of a bivariate
 * distribution assuming log interpolation with the secondary indep grid
 *
 * The PDF for log-log interpolation is defined as:
 * f(x,y) = 1/(eta*L)*( eta_0*L_0*f_0( y_0 ) * eta_1*L_1*f_1( y_1 ) )/
 * ( eta_1*L_1*f_1(y_1) + ( (eta_0*L_0*f_0(y_0)) - (eta_1*L_1*f_1(y_1)) )*beta )
 */
struct UnitBaseCorrelatedEvaluatePDFHelperLogBase
{
  template<typename YIndepType,
           typename ReturnType,
           typename T>
  static inline ReturnType evaluate(
   const YIndepType y_indep_value,
   const YIndepType y_min_indep_value,
   const typename QuantityTraits<YIndepType>::RawType intermediate_grid_length,
   const YIndepType lower_y_indep_value,
   const YIndepType lower_y_min_indep_value,
   const typename QuantityTraits<YIndepType>::RawType lower_grid_length,
   const ReturnType lower_eval,
   const YIndepType upper_y_indep_value,
   const YIndepType upper_y_min_indep_value,
   const typename QuantityTraits<YIndepType>::RawType upper_grid_length,
   const ReturnType upper_eval,
   const T eta,
   const T beta )
  {
    if( eta == Utility::QuantityTraits<T>::zero() )
    {
      return UnitBaseCorrelatedEvaluatePDFHelperLinBase::evaluate(
                                                      y_indep_value,
                                                      y_min_indep_value,
                                                      intermediate_grid_length,
                                                      lower_y_indep_value,
                                                      lower_y_min_indep_value,
                                                      lower_grid_length,
                                                      lower_eval,
                                                      upper_y_indep_value,
                                                      upper_y_min_indep_value,
                                                      upper_grid_length,
                                                      upper_eval,
                                                      eta,
                                                      beta );
    }

    auto lower_product =
      lower_eval*std::log( lower_y_indep_value/lower_y_min_indep_value );

    auto upper_product =
      upper_eval*std::log( upper_y_indep_value/upper_y_min_indep_value );

    return (lower_product*upper_product)/LinLin::interpolate( beta, upper_product, lower_product )/std::log(y_indep_value/y_min_indep_value);
  }
};

/*! \brief Helper struct for calculating the PDF of a bivariate distribution
 *
 * Specialization of this struct for the different interpolation types is
 * required.
 */
template<typename YXInterpPolicy>
struct UnitBaseCorrelatedEvaluatePDFHelper
{
  template<typename YIndepType,
           typename ReturnType,
           typename T>
  static inline ReturnType evaluate( const YIndepType y_indep_value,
   const YIndepType y_min_indep_value,
   const typename QuantityTraits<YIndepType>::RawType intermediate_grid_length,
   const YIndepType lower_y_indep_value,
   const YIndepType lower_y_min_indep_value,
   const typename QuantityTraits<YIndepType>::RawType lower_grid_length,
   const ReturnType lower_eval,
   const YIndepType upper_y_indep_value,
   const YIndepType upper_y_min_indep_value,
   const typename QuantityTraits<YIndepType>::RawType upper_grid_length,
   const ReturnType upper_eval,
   const T eta,
   const T beta )
  {
    THROW_EXCEPTION( std::runtime_error,
                     "Interpolation type " << YXInterpPolicy::name() <<
                     " is not currently supported!\n" );
  }
};

/*! \brief Specialization of
 * Utility::Details::UnitBaseCorrelatedEvaluatePDFHelper for Utility::LinLin
 */
template<>
struct UnitBaseCorrelatedEvaluatePDFHelper<Utility::LinLin> : public UnitBaseCorrelatedEvaluatePDFHelperLinBase
{ /* ... */ };

/*! \brief Specialization of
 * Utility::Details::UnitBaseCorrelatedEvaluatePDFHelper for Utility::LinLog
 */
template<>
struct UnitBaseCorrelatedEvaluatePDFHelper<Utility::LinLog> : public UnitBaseCorrelatedEvaluatePDFHelperLinBase
{ /* ... */ };

/*! \brief Specialization of
 * Utility::Details::UnitBaseCorrelatedEvaluatePDFHelper for Utility::LogLog
 */
template<>
struct UnitBaseCorrelatedEvaluatePDFHelper<Utility::LogLog> : public UnitBaseCorrelatedEvaluatePDFHelperLogBase
{ /* ... */ };

/*! \brief Specialization of
 * Utility::Details::UnitBaseCorrelatedEvaluatePDFHelper for Utility::LogCosLog
 */
template<>
struct UnitBaseCorrelatedEvaluatePDFHelper<Utility::LogCosLog > : public UnitBaseCorrelatedEvaluatePDFHelperLogBase
{ /* ... */ };

/*! \brief Specialization of
 * Utility::Details::UnitBaseCorrelatedEvaluatePDFHelper for Utility::LogCosLog
 */
template<>
struct UnitBaseCorrelatedEvaluatePDFHelper<Utility::NudgedLogCosLog > : public UnitBaseCorrelatedEvaluatePDFHelperLogBase
{ /* ... */ };

/*! \brief Specialization of
 * Utility::Details::UnitBaseCorrelatedEvaluatePDFHelper for Utility::LogLin
 */
template<>
struct UnitBaseCorrelatedEvaluatePDFHelper<Utility::LogLin> : public UnitBaseCorrelatedEvaluatePDFHelperLogBase
{ /* ... */ };

/*! \brief Specialization of
 * Utility::Details::UnitBaseCorrelatedEvaluatePDFHelper for Utility::LogCosLin
 */
template<>
struct UnitBaseCorrelatedEvaluatePDFHelper<Utility::LogCosLin > : public UnitBaseCorrelatedEvaluatePDFHelperLogBase
{ /* ... */ };

/*! \brief Specialization of
 * Utility::Details::UnitBaseCorrelatedEvaluatePDFHelper for Utility::LogCosLin
 */
template<>
struct UnitBaseCorrelatedEvaluatePDFHelper<Utility::NudgedLogCosLin > : public UnitBaseCorrelatedEvaluatePDFHelperLogBase
{ /* ... */ };

} // end Details namespace

// Evaluate the PDF between bin boundaries using the desired evaluation method
/*! \details This method uses an iterative method to estimate the CDF for
 *  unit-base correlated sampling to a relative error tolerance in order to get
 *  the proper interpolation parameters.
 */
template<typename _TwoDInterpPolicy>
template<typename BaseUnivariateDistributionType,
         typename XIndepType,
         typename YIndepType,
         typename ReturnType,
         typename YZIterator,
         typename EvaluationMethod,
         typename YBoundsFunctor>
ReturnType UnitBaseCorrelated<_TwoDInterpPolicy>::evaluatePDF(
                                  const XIndepType& x_indep_value,
                                  const YIndepType& y_indep_value,
                                  const YBoundsFunctor& min_y_indep_functor,
                                  const YBoundsFunctor& max_y_indep_functor,
                                  const EvaluationMethod& evaluate,
                                  const YZIterator& lower_bin_boundary,
                                  const YZIterator& upper_bin_boundary,
                                  const double fuzzy_boundary_tol,
                                  const double rel_error_tol,
                                  const double error_tol,
                                  unsigned max_number_of_iterations )
{
  // Get the min and max y indep values
  YIndepType min_y_indep_value = min_y_indep_functor( x_indep_value );
  YIndepType max_y_indep_value = max_y_indep_functor( x_indep_value );

  // Get the intermediate grid lengths for the indep value and the upper and lower bin boundary
  typename QuantityTraits<YIndepType>::RawType grid_length_0 =
        TwoDInterpPolicy::ZYInterpPolicy::calculateUnitBaseGridLength(
                    lower_bin_boundary->second->getLowerBoundOfIndepVar(),
                    lower_bin_boundary->second->getUpperBoundOfIndepVar() );

  typename QuantityTraits<YIndepType>::RawType grid_length_1 =
        TwoDInterpPolicy::ZYInterpPolicy::calculateUnitBaseGridLength(
                    upper_bin_boundary->second->getLowerBoundOfIndepVar(),
                    upper_bin_boundary->second->getUpperBoundOfIndepVar() );

  typename QuantityTraits<YIndepType>::RawType
  intermediate_grid_length =
        TwoDInterpPolicy::ZYInterpPolicy::calculateUnitBaseGridLength(
                    min_y_indep_value,
                    max_y_indep_value );



  if( lower_bin_boundary->first == x_indep_value ||
      upper_bin_boundary->first == x_indep_value )
  {
    // Calculate the intermediate y min with fuzzy tol
    YIndepType min_y_indep_value_with_tol =
     TwoDInterpPolicy::ZYInterpPolicy::calculateFuzzyLowerBound(
        min_y_indep_value, fuzzy_boundary_tol );

    // Calculate the intermediate y max with fuzzy tol
    YIndepType max_y_indep_value_with_tol =
      TwoDInterpPolicy::ZYInterpPolicy::calculateFuzzyUpperBound(
          max_y_indep_value, fuzzy_boundary_tol );

    // Check if the secondary indep value is in the intermediate grid
    if( y_indep_value >= min_y_indep_value_with_tol && y_indep_value <= max_y_indep_value_with_tol )
    {
      // Calculate the unit base independent variable
      typename QuantityTraits<YIndepType>::RawType eta;

      if( y_indep_value > min_y_indep_value && y_indep_value < max_y_indep_value )
      {
        typename QuantityTraits<YIndepType>::RawType
        intermediate_grid_length =
              TwoDInterpPolicy::ZYInterpPolicy::calculateUnitBaseGridLength(
                          min_y_indep_value,
                          max_y_indep_value );

        eta = TwoDInterpPolicy::ZYInterpPolicy::calculateUnitBaseIndepVar(
                      y_indep_value, min_y_indep_value, intermediate_grid_length );
      }
      else if( y_indep_value <= min_y_indep_value && y_indep_value >= min_y_indep_value_with_tol )
        eta = 0.0;
      else // y_indep_value >= max_y_indep_value && y_indep_value <= max_y_indep_value_with_tol
        eta = 1.0;

      typename QuantityTraits<YIndepType>::RawType grid_length;
      if( lower_bin_boundary->first == x_indep_value )
      {
        YIndepType norm_y_value = std::min(
          TwoDInterpPolicy::ZYInterpPolicy::calculateIndepVar(
              eta,
              lower_bin_boundary->second->getLowerBoundOfIndepVar(),
              grid_length_0 ),
                lower_bin_boundary->second->getUpperBoundOfIndepVar() );

        return ((*lower_bin_boundary->second).*evaluate)(norm_y_value);
      }
      else if( upper_bin_boundary->first == x_indep_value )
      {
        YIndepType norm_y_value = std::min(
          TwoDInterpPolicy::ZYInterpPolicy::calculateIndepVar(
              eta,
              upper_bin_boundary->second->getLowerBoundOfIndepVar(),
              grid_length_1 ),
                upper_bin_boundary->second->getUpperBoundOfIndepVar() );

        return ((*upper_bin_boundary->second).*evaluate)(norm_y_value);
      }
    }
    else
    {
      return QuantityTraits<ReturnType>::zero();
    }
  }
  else
  {
    // Calculate the bin length of the x variable
    const typename QuantityTraits<XIndepType>::RawType x_bin_length =
      TwoDInterpPolicy::ZXInterpPolicy::calculateUnitBaseGridLength(
                                                    lower_bin_boundary->first,
                                                    upper_bin_boundary->first );

    // Calculate the x variable bin ratio (beta)
    const typename QuantityTraits<XIndepType>::RawType beta =
      TwoDInterpPolicy::ZXInterpPolicy::calculateUnitBaseIndepVar(
                                                    x_indep_value,
                                                    lower_bin_boundary->first,
                                                    x_bin_length,
                                                    fuzzy_boundary_tol );

    // Calculate the correlated y value at the lower and upper bin boundary
    YIndepType lower_y_value, upper_y_value;
    typename QuantityTraits<YIndepType>::RawType eta;

    // Check for a y indep value outside of the y indep grid limits
    if ( y_indep_value < min_y_indep_value || y_indep_value > max_y_indep_value )
      return QuantityTraits<ReturnType>::zero();
    else if ( y_indep_value == min_y_indep_value ) // At min y value
    {
      lower_y_value = lower_bin_boundary->second->getLowerBoundOfIndepVar();
      upper_y_value = upper_bin_boundary->second->getLowerBoundOfIndepVar();
      eta = 0.0;
    }
    else if ( y_indep_value == max_y_indep_value ) // At max y value
    {
      lower_y_value = lower_bin_boundary->second->getUpperBoundOfIndepVar();
      upper_y_value = upper_bin_boundary->second->getUpperBoundOfIndepVar();
      eta = 1.0;
    }
    else // Between min and max y values
    {
      Details::UnitBaseCorrelatedEvaluatePDFSecondaryIndepHelper<BaseUnivariateDistributionType>::template calculateSecondaryIndepValues<TwoDInterpPolicy>(
                                                      evaluate,
                                                      min_y_indep_value,
                                                      max_y_indep_value,
                                                      y_indep_value,
                                                      beta,
                                                      grid_length_0,
                                                      grid_length_1,
                                                      intermediate_grid_length,
                                                      lower_bin_boundary,
                                                      upper_bin_boundary,
                                                      fuzzy_boundary_tol,
                                                      rel_error_tol,
                                                      error_tol,
                                                      max_number_of_iterations,
                                                      lower_y_value,
                                                      upper_y_value );
    }

    ReturnType lower_eval = ((*lower_bin_boundary->second).*evaluate)(lower_y_value);
    ReturnType upper_eval = ((*upper_bin_boundary->second).*evaluate)(upper_y_value);

    if( lower_eval == upper_eval )
      return lower_eval;
    else
    {
      return Details::UnitBaseCorrelatedEvaluatePDFHelper<typename TwoDInterpPolicy::YXInterpPolicy>::evaluate(
                         y_indep_value,
                         min_y_indep_value,
                         intermediate_grid_length,
                         lower_y_value,
                         lower_bin_boundary->second->getLowerBoundOfIndepVar(),
                         grid_length_0,
                         lower_eval,
                         upper_y_value,
                         upper_bin_boundary->second->getLowerBoundOfIndepVar(),
                         grid_length_1,
                         upper_eval,
                         eta,
                         beta );
    }
  }
}

// Evaluate the CDF between bin boundaries using the desired evaluation method
/*! \details The EvaluationMethod must evalute using a Cosine variable. This
 *  method uses an iterative method to estimate the CDF for unit-base correlated
 *  sampling to a relative error tolerance in order to get the proper
 *  interpolation parameters. The lower and upper bounds of the secondary
 *  independent variable (cosine) are fixed (-1 <= cosine <= 1). Therefore a
 *  unit base method is not necessary and the direct correlated method is used
 *  to evaluate instead.
 */
template<typename _TwoDInterpPolicy>
template<typename BaseUnivariateDistributionType,
         typename XIndepType,
         typename YIndepType,
         typename YZIterator,
         typename EvaluationMethod,
         typename YBoundsFunctor>
double UnitBaseCorrelated<_TwoDInterpPolicy>::evaluateCDFCos(
                                  const XIndepType& x_indep_value,
                                  const YIndepType& y_indep_value,
                                  const YBoundsFunctor& min_y_indep_functor,
                                  const YBoundsFunctor& max_y_indep_functor,
                                  const EvaluationMethod& evaluate,
                                  const YZIterator& lower_bin_boundary,
                                  const YZIterator& upper_bin_boundary,
                                  const double fuzzy_boundary_tol,
                                  const double rel_error_tol,
                                  const double error_tol,
                                  unsigned max_number_of_iterations )
{
  return Correlated<TwoDInterpPolicy>::template evaluateCDFCos<BaseUnivariateDistributionType,
                                                               XIndepType,
                                                               YIndepType,
                                                               YZIterator,
                                                               EvaluationMethod,
                                                               YBoundsFunctor>(
                                                    x_indep_value,
                                                    y_indep_value,
                                                    min_y_indep_functor,
                                                    max_y_indep_functor,
                                                    evaluate,
                                                    lower_bin_boundary,
                                                    upper_bin_boundary,
                                                    fuzzy_boundary_tol,
                                                    rel_error_tol,
                                                    error_tol,
                                                    max_number_of_iterations );
}

// Evaluate the CDF between bin boundaries using the desired evaluation method
/*! \details This method uses an iterative method to estimate the CDF for
 *  unit-base correlated sampling to a relative error tolerance in order to get
 *  the proper interpolation parameters.
 */
template<typename _TwoDInterpPolicy>
template<typename BaseUnivariateDistributionType,
         typename XIndepType,
         typename YIndepType,
         typename YZIterator,
         typename EvaluationMethod,
         typename YBoundsFunctor>
double UnitBaseCorrelated<_TwoDInterpPolicy>::evaluateCDF(
                                  const XIndepType& x_indep_value,
                                  const YIndepType& y_indep_value,
                                  const YBoundsFunctor& min_y_indep_functor,
                                  const YBoundsFunctor& max_y_indep_functor,
                                  const EvaluationMethod& evaluate,
                                  const YZIterator& lower_bin_boundary,
                                  const YZIterator& upper_bin_boundary,
                                  const double fuzzy_boundary_tol,
                                  const double rel_error_tol,
                                  const double error_tol,
                                  unsigned max_number_of_iterations )
{
  // Get the min and max y indep values
  YIndepType min_y_indep_value = min_y_indep_functor( x_indep_value );
  YIndepType max_y_indep_value = max_y_indep_functor( x_indep_value );

  // Get the intermediate grid lengths for the indep value and the upper and lower bin boundary
  typename QuantityTraits<YIndepType>::RawType grid_length_0 =
        TwoDInterpPolicy::ZYInterpPolicy::calculateUnitBaseGridLength(
                    lower_bin_boundary->second->getLowerBoundOfIndepVar(),
                    lower_bin_boundary->second->getUpperBoundOfIndepVar() );

  typename QuantityTraits<YIndepType>::RawType grid_length_1 =
        TwoDInterpPolicy::ZYInterpPolicy::calculateUnitBaseGridLength(
                    upper_bin_boundary->second->getLowerBoundOfIndepVar(),
                    upper_bin_boundary->second->getUpperBoundOfIndepVar() );

  typename QuantityTraits<YIndepType>::RawType
  intermediate_grid_length =
        TwoDInterpPolicy::ZYInterpPolicy::calculateUnitBaseGridLength(
                    min_y_indep_value,
                    max_y_indep_value );



  if( lower_bin_boundary->first == x_indep_value ||
      upper_bin_boundary->first == x_indep_value )
  {
    // Calculate the intermediate y min with fuzzy tol
    YIndepType min_y_indep_value_with_tol =
     TwoDInterpPolicy::ZYInterpPolicy::calculateFuzzyLowerBound(
        min_y_indep_value, fuzzy_boundary_tol );

    // Calculate the intermediate y max with fuzzy tol
    YIndepType max_y_indep_value_with_tol =
      TwoDInterpPolicy::ZYInterpPolicy::calculateFuzzyUpperBound(
          max_y_indep_value, fuzzy_boundary_tol );

    // Check if the secondary indep value is in the intermediate grid
    if( y_indep_value >= min_y_indep_value_with_tol && y_indep_value <= max_y_indep_value_with_tol )
    {
      // Calculate the unit base independent variable
      typename QuantityTraits<YIndepType>::RawType eta;

      if( y_indep_value > min_y_indep_value && y_indep_value < max_y_indep_value )
      {
        typename QuantityTraits<YIndepType>::RawType
        intermediate_grid_length =
              TwoDInterpPolicy::ZYInterpPolicy::calculateUnitBaseGridLength(
                          min_y_indep_value,
                          max_y_indep_value );

        eta = TwoDInterpPolicy::ZYInterpPolicy::calculateUnitBaseIndepVar(
                      y_indep_value, min_y_indep_value, intermediate_grid_length );
      }
      else if( y_indep_value <= min_y_indep_value && y_indep_value >= min_y_indep_value_with_tol )
        eta = 0.0;
      else // y_indep_value >= max_y_indep_value && y_indep_value <= max_y_indep_value_with_tol
        eta = 1.0;

      typename QuantityTraits<YIndepType>::RawType grid_length;
      if( lower_bin_boundary->first == x_indep_value )
      {
        YIndepType norm_y_value = std::min(
          TwoDInterpPolicy::ZYInterpPolicy::calculateIndepVar(
              eta,
              lower_bin_boundary->second->getLowerBoundOfIndepVar(),
              grid_length_0 ),
                lower_bin_boundary->second->getUpperBoundOfIndepVar() );

        return ((*lower_bin_boundary->second).*evaluate)(norm_y_value);
      }
      else if( upper_bin_boundary->first == x_indep_value )
      {
        YIndepType norm_y_value = std::min(
          TwoDInterpPolicy::ZYInterpPolicy::calculateIndepVar(
              eta,
              upper_bin_boundary->second->getLowerBoundOfIndepVar(),
              grid_length_1 ),
                upper_bin_boundary->second->getUpperBoundOfIndepVar() );

        return ((*upper_bin_boundary->second).*evaluate)(norm_y_value);
      }
    }
    else if ( y_indep_value > max_y_indep_value_with_tol )
      return 1.0;
    else
      return 0.0;
  }
  else
  {
    // Calculate the bin length of the x variable
    const typename QuantityTraits<XIndepType>::RawType x_bin_length =
      TwoDInterpPolicy::ZXInterpPolicy::calculateUnitBaseGridLength(
                                                    lower_bin_boundary->first,
                                                    upper_bin_boundary->first );

    // Calculate the x variable bin ratio (beta)
    const typename QuantityTraits<XIndepType>::RawType beta =
      TwoDInterpPolicy::ZXInterpPolicy::calculateUnitBaseIndepVar(
                                                    x_indep_value,
                                                    lower_bin_boundary->first,
                                                    x_bin_length );

    // Get the min and max y indep values
    YIndepType min_y_indep_value = min_y_indep_functor( x_indep_value );
    YIndepType max_y_indep_value = max_y_indep_functor( x_indep_value );

    // Get the intermediate grid lengths for the indep value and the upper and lower bin boundary
    typename QuantityTraits<YIndepType>::RawType grid_length_0 =
          TwoDInterpPolicy::ZYInterpPolicy::calculateUnitBaseGridLength(
                      lower_bin_boundary->second->getLowerBoundOfIndepVar(),
                      lower_bin_boundary->second->getUpperBoundOfIndepVar() );

    typename QuantityTraits<YIndepType>::RawType grid_length_1 =
          TwoDInterpPolicy::ZYInterpPolicy::calculateUnitBaseGridLength(
                      upper_bin_boundary->second->getLowerBoundOfIndepVar(),
                      upper_bin_boundary->second->getUpperBoundOfIndepVar() );

    typename QuantityTraits<YIndepType>::RawType
    intermediate_grid_length =
          TwoDInterpPolicy::ZYInterpPolicy::calculateUnitBaseGridLength(
                      min_y_indep_value,
                      max_y_indep_value );

    // Check for a y indep value outside of the y indep grid limits
    if ( y_indep_value <= min_y_indep_value )
      return 0.0;
    else if ( y_indep_value >= max_y_indep_value )
      return 1.0;
    else
    {
      // Get the lower and upper boundaries of the evaluated cdf
      double lower_cdf_bound, upper_cdf_bound;
      typename QuantityTraits<YIndepType>::RawType eta;
      {

        YIndepType min_y_indep_value_with_tol =
            TwoDInterpPolicy::ZYInterpPolicy::calculateFuzzyLowerBound(
                        min_y_indep_value );

        YIndepType max_y_indep_value_with_tol =
            TwoDInterpPolicy::ZYInterpPolicy::calculateFuzzyUpperBound(
                        max_y_indep_value );

        // Calculate the unit base variable on the intermediate grid
        eta = TwoDInterpPolicy::ZYInterpPolicy::calculateUnitBaseIndepVar(
                y_indep_value,
                min_y_indep_value,
                intermediate_grid_length );

        // Get the y indep var value for the upper and lower bin boundaries
        YIndepType y_indep_value_0 =
            TwoDInterpPolicy::ZYInterpPolicy::calculateIndepVar(
                        eta,
                        lower_bin_boundary->second->getLowerBoundOfIndepVar(),
                        grid_length_0 );

        YIndepType y_indep_value_1 =
            TwoDInterpPolicy::ZYInterpPolicy::calculateIndepVar(
                        eta,
                        upper_bin_boundary->second->getLowerBoundOfIndepVar(),
                        grid_length_1 );

        // Evaluate the cdf at the upper and lower bin boundaries
        double bin_eval_0 =
          ((*lower_bin_boundary->second).*&BaseUnivariateDistributionType::evaluateCDF)( y_indep_value_0 );
        double bin_eval_1 =
          ((*upper_bin_boundary->second).*&BaseUnivariateDistributionType::evaluateCDF)( y_indep_value_1 );

        if ( bin_eval_0 <= bin_eval_1 )
        {
          lower_cdf_bound = bin_eval_0;
          upper_cdf_bound = bin_eval_1;
        }
        else
        {
          lower_cdf_bound = bin_eval_1;
          upper_cdf_bound = bin_eval_0;
        }
      }

      YIndepType lower_y_value, upper_y_value;

      return Details::UnitBaseCorrelatedEvaluatePDFSecondaryIndepHelper<BaseUnivariateDistributionType>::template estimateCDF<TwoDInterpPolicy>(
                                                    lower_cdf_bound,
                                                    upper_cdf_bound,
                                                    lower_y_value,
                                                    upper_y_value,
                                                    beta,
                                                    grid_length_0,
                                                    grid_length_1,
                                                    eta,
                                                    lower_bin_boundary,
                                                    upper_bin_boundary,
                                                    rel_error_tol,
                                                    error_tol,
                                                    max_number_of_iterations );
    }
  }
}

// Sample between bin boundaries using the desired sampling functor
/*! \details In order for this method to calculate a sample accurately the same
 * random number must be used to sample from the distribution on the lower and
 * upper bounds. The sample functor must therefore wrap the
 * Utility::TabularUnivariateDist::sampleWithRandomNumber routine or one of the
 * similar methods that takes a random number.
 */
template<typename _TwoDInterpPolicy>
template<typename XIndepType,
         typename YIndepType,
         typename YZIterator,
         typename SampleFunctor,
         typename YBoundsFunctor>
YIndepType UnitBaseCorrelated<_TwoDInterpPolicy>::sample(
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

  return UnitBaseCorrelated<_TwoDInterpPolicy>::sampleDetailed<XIndepType,YIndepType,YZIterator,SampleFunctor>(
            sample_functor,
            min_y_indep_functor,
            max_y_indep_functor,
            x_indep_value,
            lower_bin_boundary,
            upper_bin_boundary,
            dummy_sampled_bin_boundary,
            dummy_raw_sample );
}

// Sample between bin boundaries using the desired sampling functor
/*! \details In order for this method to calculate a sample accurately the same
 * random number must be used to sample from the distribution on the lower and
 * upper bounds. The sample functor must therefore wrap the
 * Utility::TabularUnivariateDist::sampleWithRandomNumber routine or one of the
 * similar methods that takes a random number.
 */
template<typename _TwoDInterpPolicy>
template<typename XIndepType,
         typename YIndepType,
         typename YZIterator,
         typename SampleFunctor>
YIndepType UnitBaseCorrelated<_TwoDInterpPolicy>::sampleCos(
                                  const SampleFunctor& sample_functor,
                                  const XIndepType& x_indep_value,
                                  const YZIterator& lower_bin_boundary,
                                  const YZIterator& upper_bin_boundary )
{
  // Dummy variables
  YIndepType dummy_raw_sample;
  YZIterator dummy_sampled_bin_boundary;

  return UnitBaseCorrelated<_TwoDInterpPolicy>::sampleCosDetailed<XIndepType,YIndepType,YZIterator,SampleFunctor>(
            sample_functor,
            x_indep_value,
            lower_bin_boundary,
            upper_bin_boundary,
            dummy_sampled_bin_boundary,
            dummy_raw_sample );
}

// Sample between bin boundaries using the desired subrange sampling functor
/* \details A direct correlated routine is used to sample the distribution.
 * In order for this method to calculate a sample accurately the same random
 * number must be used to sample from the distribution on the lower and upper
 * bounds. The sample functor must therefore wrap the
 * Utility::TabularUnivariateDist::sampleWithRandomNumberInSubrange routine.
 */
template<typename _TwoDInterpPolicy>
template<typename XIndepType,
         typename YIndepType,
         typename YZIterator,
         typename SampleFunctor,
         typename YBoundsFunctor>
YIndepType UnitBaseCorrelated<_TwoDInterpPolicy>::sampleInSubrange(
          const SampleFunctor& subrange_sample_functor,
          const YBoundsFunctor& min_y_indep_functor,
          const YBoundsFunctor& max_y_indep_functor,
          const XIndepType& x_indep_value,
          const YZIterator& lower_bin_boundary,
          const YZIterator& upper_bin_boundary,
          const YIndepType& subrange_max_y_indep_value )
{
  // Get the min y indep var values for the x_indep_value
  YIndepType min_y_indep_value = min_y_indep_functor( x_indep_value );

  // Get the max y indep var values for the x_indep_value
  YIndepType max_y_indep_value;
  if( subrange_max_y_indep_value > max_y_indep_functor( x_indep_value ) )
    max_y_indep_value = max_y_indep_functor( x_indep_value );
  else
    max_y_indep_value = subrange_max_y_indep_value;

  // Check for a x value at a grid limit
  if( x_indep_value == upper_bin_boundary->first )
    return subrange_sample_functor( *upper_bin_boundary->second, max_y_indep_value );
  else if( x_indep_value == lower_bin_boundary->first )
    return subrange_sample_functor( *lower_bin_boundary->second, max_y_indep_value );
  else
  {
    typename QuantityTraits<YIndepType>::RawType
    intermediate_grid_length =
      TwoDInterpPolicy::ZYInterpPolicy::calculateUnitBaseGridLength(
                  min_y_indep_value, max_y_indep_value );

    // Calculate the unit base variable on the intermediate grid corresponding to the
    // raw samples on the lower and upper boundaries
    typename QuantityTraits<YIndepType>::RawType eta, eta_0, eta_1;

    {
      // Get the max y indep value at the lower bin boundary
      YIndepType max_y_indep_value_0 =
        lower_bin_boundary->second->getUpperBoundOfIndepVar();

      // Only set the subrange if it is below the max y indep value
      if( subrange_max_y_indep_value < max_y_indep_value_0 )
        max_y_indep_value_0 = subrange_max_y_indep_value;

      // Calculate the unit base variable on the lower grid corresponding to the
      // lower raw sample
      typename QuantityTraits<YIndepType>::RawType grid_length_0 =
        TwoDInterpPolicy::ZYInterpPolicy::calculateUnitBaseGridLength(
                    lower_bin_boundary->second->getLowerBoundOfIndepVar(),
                    max_y_indep_value_0 );

      eta_0 = TwoDInterpPolicy::ZYInterpPolicy::calculateUnitBaseIndepVar(
            subrange_sample_functor( *lower_bin_boundary->second, max_y_indep_value_0 ),
            lower_bin_boundary->second->getLowerBoundOfIndepVar(),
            grid_length_0 );


      // Get the max y indep value at the upper bin boundary
      YIndepType max_y_indep_value_1 =
        upper_bin_boundary->second->getUpperBoundOfIndepVar();

      // Only set the subrange if it is below the max y indep value
      if( subrange_max_y_indep_value < max_y_indep_value_1 )
        max_y_indep_value_1 = subrange_max_y_indep_value;

      // Calculate the unit base variable on the upper grid corresponding to the
      // upper raw sample
      typename QuantityTraits<YIndepType>::RawType grid_length_1 =
        TwoDInterpPolicy::ZYInterpPolicy::calculateUnitBaseGridLength(
                    upper_bin_boundary->second->getLowerBoundOfIndepVar(),
                    max_y_indep_value_1 );

      eta_1 = TwoDInterpPolicy::ZYInterpPolicy::calculateUnitBaseIndepVar(
            subrange_sample_functor( *upper_bin_boundary->second, max_y_indep_value_1 ),
            upper_bin_boundary->second->getLowerBoundOfIndepVar(),
            grid_length_1 );

      // Interpolate between the lower and upper unit base variables
      eta = TwoDInterpPolicy::YXInterpPolicy::interpolate(
                                                  lower_bin_boundary->first,
                                                  upper_bin_boundary->first,
                                                  x_indep_value,
                                                  eta_0,
                                                  eta_1 );
    }

    // Scale the sample so that it preserves the intermediate limits.
    return TwoDInterpPolicy::ZYInterpPolicy::calculateIndepVar(
              eta, min_y_indep_value, intermediate_grid_length );
  }
}

// Sample between bin boundaries using the desired sampling functor
/*! \details In order for this method to calculate a sample accurately the same
 * random number must be used to sample from the distribution on the lower and
 * upper bounds. The sample functor must therefore wrap the
 * Utility::TabularUnivariateDist::sampleWithRandomNumber routine or one of the
 * similar methods that takes a random number.
 */
template<typename _TwoDInterpPolicy>
template<typename XIndepType,
         typename YIndepType,
         typename YZIterator,
         typename SampleFunctor,
         typename YBoundsFunctor>
YIndepType UnitBaseCorrelated<_TwoDInterpPolicy>::sampleDetailed(
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
        TwoDInterpPolicy::ZYInterpPolicy::calculateUnitBaseGridLength(
                            min_y_indep_value, max_y_indep_value );

      // Calculate the unit base variable on the intermediate grid corresponding to the
      // raw samples on the lower and upper boundaries
      typename QuantityTraits<YIndepType>::RawType eta, eta_0, eta_1;

      {
        // Calculate the unit base variable on the lower grid corresponding to the
        // lower raw sample
        typename QuantityTraits<YIndepType>::RawType grid_length_0 =
          TwoDInterpPolicy::ZYInterpPolicy::calculateUnitBaseGridLength(
                      lower_bin_boundary->second->getLowerBoundOfIndepVar(),
                      lower_bin_boundary->second->getUpperBoundOfIndepVar());

        eta_0 = TwoDInterpPolicy::ZYInterpPolicy::calculateUnitBaseIndepVar(
                        sample_functor( *lower_bin_boundary->second ),
                        lower_bin_boundary->second->getLowerBoundOfIndepVar(),
                        grid_length_0 );

        // Calculate the unit base variable on the upper grid corresponding to the
        // upper raw sample
        typename QuantityTraits<YIndepType>::RawType grid_length_1 =
          TwoDInterpPolicy::ZYInterpPolicy::calculateUnitBaseGridLength(
                      upper_bin_boundary->second->getLowerBoundOfIndepVar(),
                      upper_bin_boundary->second->getUpperBoundOfIndepVar());

        eta_1 = TwoDInterpPolicy::ZYInterpPolicy::calculateUnitBaseIndepVar(
                        sample_functor( *upper_bin_boundary->second ),
                        upper_bin_boundary->second->getLowerBoundOfIndepVar(),
                        grid_length_1 );

        // Take into account special case where both eta values equal zero
        // (e.g. random number of zero)
        if( eta_0 == eta_1)
          eta = eta_0;
        else
        {
          // Interpolate between the lower and upper unit base variables
          eta = TwoDInterpPolicy::YXInterpPolicy::interpolate(
                                                  lower_bin_boundary->first,
                                                  upper_bin_boundary->first,
                                                  x_indep_value,
                                                  eta_0,
                                                  eta_1 );
        }
      }
    // Scale the sample so that it preserves the intermediate limits.
    raw_sample = TwoDInterpPolicy::ZYInterpPolicy::calculateIndepVar(
                  eta, min_y_indep_value, intermediate_grid_length );
    sampled_bin_boundary = lower_bin_boundary;
    }
  }
  return raw_sample;
}

// Sample between bin boundaries using the desired sampling functor
/*! \details In order for this method to calculate a sample accurately the same
 * random number must be used to sample from the distribution on the lower and
 * upper bounds. The sample functor must therefore wrap the
 * Utility::TabularUnivariateDist::sampleWithRandomNumber routine or one of the
 * similar methods that takes a random number.
 */
template<typename _TwoDInterpPolicy>
template<typename XIndepType,
         typename YIndepType,
         typename YZIterator,
         typename SampleFunctor>
YIndepType UnitBaseCorrelated<_TwoDInterpPolicy>::sampleCosDetailed(
            const SampleFunctor& sample_functor,
            const XIndepType& x_indep_value,
            const YZIterator& lower_bin_boundary,
            const YZIterator& upper_bin_boundary,
            YZIterator& sampled_bin_boundary,
            YIndepType& raw_sample )
{
  return Correlated<_TwoDInterpPolicy>::template sampleCosDetailed<XIndepType,YIndepType,YZIterator,SampleFunctor>(
            sample_functor,
            x_indep_value,
            lower_bin_boundary,
            upper_bin_boundary,
            sampled_bin_boundary,
            raw_sample );
}

// The name of the policy
template<typename _TwoDInterpPolicy>
inline const std::string UnitBaseCorrelated<_TwoDInterpPolicy>::name()
{
  return "Unit-base Correlated";
}

TWO_D_GRID_POLICY_TYPE_NAME_TRAITS_QUICK_DECL( Direct );
TWO_D_GRID_POLICY_TYPE_NAME_TRAITS_QUICK_DECL( UnitBase );
TWO_D_GRID_POLICY_TYPE_NAME_TRAITS_QUICK_DECL( CumulativePoints );
TWO_D_GRID_POLICY_TYPE_NAME_TRAITS_QUICK_DECL( Correlated );
TWO_D_GRID_POLICY_TYPE_NAME_TRAITS_QUICK_DECL( UnitBaseCorrelated );

} // end Utility namespace

#endif // end UTILITY_TWO_D_GRID_POLICY_DEF_HPP

//---------------------------------------------------------------------------//
// end Utility_TwoDGridPolicy_def.hpp
//---------------------------------------------------------------------------//
