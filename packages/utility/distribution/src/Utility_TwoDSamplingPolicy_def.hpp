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

// Evaluate between bin boundaries using the desired evaluation method
template<typename TwoDInterpPolicy,
         typename BaseOneDDistributionType,
         typename XIndepType,
         typename YIndepType,
         typename ReturnType,
         typename YZIterator,
         typename EvaluationMethod,
         typename YBoundsFunctor>
ReturnType Stochastic::evaluateCosSampleBased(
                                  const XIndepType& x_indep_value,
                                  const YIndepType& y_indep_value,
                                  const YBoundsFunctor& min_y_indep_functor,
                                  const YBoundsFunctor& max_y_indep_functor,
                                  const EvaluationMethod& evaluate,
                                  const YZIterator& lower_bin_boundary,
                                  const YZIterator& upper_bin_boundary,
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
    ReturnType min_eval_0 = ((*lower_bin_boundary->second).*evaluate)(y_indep_value);
    ReturnType min_eval_1 = ((*upper_bin_boundary->second).*evaluate)(y_indep_value);

    if ( min_eval_0 == min_eval_1 )
      return min_eval_0;
    else
    {
      // Return the interpolated evaluation
      return TwoDInterpPolicy::ZXInterpPolicy::interpolate(
              lower_bin_boundary->first,
              upper_bin_boundary->first,
              x_indep_value,
              min_eval_0,
              min_eval_1 );
    }
  }
}

// Evaluate between bin boundaries using the desired evaluation method
/*! \details Because stochastic sampling does not sample on the true
 *  intermediate grid a sample base evaluation scheme would give the incorrect
 *  evaluation. Therefore, the direct evaluation scheme will always be used.
 */
template<typename TwoDInterpPolicy,
         typename BaseOneDDistributionType,
         typename XIndepType,
         typename YIndepType,
         typename ReturnType,
         typename YZIterator,
         typename EvaluationMethod,
         typename YBoundsFunctor>
ReturnType Stochastic::evaluateSampleBased(
                                  const XIndepType& x_indep_value,
                                  const YIndepType& y_indep_value,
                                  const YBoundsFunctor& min_y_indep_functor,
                                  const YBoundsFunctor& max_y_indep_functor,
                                  const EvaluationMethod& evaluate,
                                  const YZIterator& lower_bin_boundary,
                                  const YZIterator& upper_bin_boundary,
                                  const ReturnType& below_lower_bound_return,
                                  const ReturnType& above_upper_bound_return,
                                  const double fuzzy_boundary_tol,
                                  const double rel_error_tol,
                                  const double error_tol,
                                  unsigned max_number_of_iterations )
{
  return Stochastic::evaluateDirect<TwoDInterpPolicy,
                                    BaseOneDDistributionType,
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
                                        below_lower_bound_return,
                                        above_upper_bound_return,
                                        fuzzy_boundary_tol );
}

// Evaluate between bin boundaries using the desired evaluation method
template<typename TwoDInterpPolicy,
         typename BaseOneDDistributionType,
         typename XIndepType,
         typename YIndepType,
         typename ReturnType,
         typename YZIterator,
         typename EvaluationMethod,
         typename YBoundsFunctor>
ReturnType Stochastic::evaluateDirect(
                                  const XIndepType& x_indep_value,
                                  const YIndepType& y_indep_value,
                                  const YBoundsFunctor& min_y_indep_functor,
                                  const YBoundsFunctor& max_y_indep_functor,
                                  const EvaluationMethod& evaluate,
                                  const YZIterator& lower_bin_boundary,
                                  const YZIterator& upper_bin_boundary,
                                  const ReturnType& below_lower_bound_return,
                                  const ReturnType& above_upper_bound_return,
                                  const double fuzzy_boundary_tol )
{
  return Correlated::evaluateDirect<TwoDInterpPolicy,
                                    BaseOneDDistributionType,
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
                                        below_lower_bound_return,
                                        above_upper_bound_return,
                                        fuzzy_boundary_tol );
}

// Sample between bin boundaries using the desired sampling functor
//! \details A correlated stochastic sampling procedure is used.
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

// Evaluate between bin boundaries using the desired evaluation method
/*! \details This method performs a type of binary search using an exact
 *  correlated sampling to estimate the CDF to a relative error tolerance in
 *  order to find the proper interpolation. The result is consistent with the
 *  exact sampling methods.
 */
template<typename TwoDInterpPolicy,
         typename BaseOneDDistributionType,
         typename XIndepType,
         typename YIndepType,
         typename ReturnType,
         typename YZIterator,
         typename EvaluationMethod,
         typename YBoundsFunctor>
ReturnType Exact::evaluateCosSampleBased(
                                  const XIndepType& x_indep_value,
                                  const YIndepType& y_indep_value,
                                  const YBoundsFunctor& min_y_indep_functor,
                                  const YBoundsFunctor& max_y_indep_functor,
                                  const EvaluationMethod& evaluate,
                                  const YZIterator& lower_bin_boundary,
                                  const YZIterator& upper_bin_boundary,
                                  const double rel_error_tol,
                                  const double error_tol,
                                  unsigned max_number_of_iterations )
{
  YIndepType min_y_indep_value = min_y_indep_functor( x_indep_value );
  YIndepType max_y_indep_value = max_y_indep_functor( x_indep_value );

  if( lower_bin_boundary->first == x_indep_value )
  {
    return ((*lower_bin_boundary->second).*evaluate)(y_indep_value);
  }
  else if( upper_bin_boundary->first == x_indep_value )
  {
    return ((*upper_bin_boundary->second).*evaluate)(y_indep_value);
  }
  else if ( y_indep_value == min_y_indep_value )
  {
    ReturnType min_eval_0 =
      ((*lower_bin_boundary->second).*evaluate)(min_y_indep_value);
    ReturnType min_eval_1 =
      ((*upper_bin_boundary->second).*evaluate)(min_y_indep_value);

    if ( min_eval_0 == min_eval_1 )
      return min_eval_0;
    else
    {
      return TwoDInterpPolicy::ZXInterpPolicy::interpolate(
                lower_bin_boundary->first,
                upper_bin_boundary->first,
                x_indep_value,
                min_eval_0,
                min_eval_1 );
    }
  }
  else if ( y_indep_value == max_y_indep_value )
  {
    return TwoDInterpPolicy::ZXInterpPolicy::interpolate(
                lower_bin_boundary->first,
                upper_bin_boundary->first,
                x_indep_value,
                ((*lower_bin_boundary->second).*evaluate)(max_y_indep_value),
                ((*upper_bin_boundary->second).*evaluate)(max_y_indep_value) );
  }
  else
  {
    // Get the lower and upper boundaries of the evaluated cdf
    double lower_cdf_bound, upper_cdf_bound;
    {
      // Evaluate the cdf at the upper and lower bin boundaries
      double bin_eval_0 =
        ((*lower_bin_boundary->second).*&BaseOneDDistributionType::evaluateCDF)( y_indep_value );
      double bin_eval_1 =
        ((*upper_bin_boundary->second).*&BaseOneDDistributionType::evaluateCDF)( y_indep_value );

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

    unsigned number_of_iterations = 0;
    YIndepType lower_bin_sample, upper_bin_sample;
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

    // Calculate the bin length of the first indep variable
    const typename QuantityTraits<XIndepType>::RawType x_bin_length =
      TwoDInterpPolicy::ZXInterpPolicy::calculateUnitBaseGridLength(
                                                    lower_bin_boundary->first,
                                                    upper_bin_boundary->first );

    // Calculate the first indep variable bin ratio (beta)
    const typename QuantityTraits<XIndepType>::RawType beta =
      TwoDInterpPolicy::ZXInterpPolicy::calculateUnitBaseIndepVar(
                                                    x_indep_value,
                                                    lower_bin_boundary->first,
                                                    x_bin_length );

    // Refine the estimated cdf value until it meet the tolerance
    while ( rel_error > tolerance )
    {
      // Estimate the cdf as the midpoint of the lower and upper boundaries
      double estimated_cdf = 0.5*( lower_cdf_bound + upper_cdf_bound );

      // Get the sampled values at the upper and lower bin for the estimated_cdf
      lower_bin_sample =
        ((*lower_bin_boundary->second).*&BaseOneDDistributionType::sampleWithRandomNumber)( estimated_cdf );
      upper_bin_sample =
        ((*upper_bin_boundary->second).*&BaseOneDDistributionType::sampleWithRandomNumber)( estimated_cdf );

      // Interpolate using the templated TwoDInterpPolicy::YXInterpPolicy
      YIndepType est_y_indep_value =
       TwoDInterpPolicy::YXInterpPolicy::interpolate(
            beta,
            lower_bin_sample,
            upper_bin_sample );

      if ( y_indep_value == est_y_indep_value )
        break;

      // Calculate the relative error between the y_indep_value and the estimate
      rel_error = (y_indep_value - est_y_indep_value )/error_norm_constant;

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
        lower_cdf_bound = estimated_cdf;
      }
      else
      {
        // Old estimated_cdf estimate is new upper cdf boundary
        upper_cdf_bound = estimated_cdf;
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

    ReturnType lower_eval =
                  ((*lower_bin_boundary->second).*evaluate)(lower_bin_sample);
    ReturnType upper_eval =
                  ((*upper_bin_boundary->second).*evaluate)(upper_bin_sample);

    if( lower_eval == upper_eval )
      return lower_eval;
    else
    {
      // Return the interpolated evaluation
      return TwoDInterpPolicy::ZXInterpPolicy::interpolate(
                beta, lower_eval, upper_eval );
    }
  }
}

// Evaluate between bin boundaries using the desired evaluation method
/*! \details This method performs a type of binary search using an exact
 *  correlated sampling to estimate the CDF to a relative error tolerance in
 *  order to find the proper interpolation. The result is consistent with the
 *  exact sampling methods.
 */
template<typename TwoDInterpPolicy,
         typename BaseOneDDistributionType,
         typename XIndepType,
         typename YIndepType,
         typename ReturnType,
         typename YZIterator,
         typename EvaluationMethod,
         typename YBoundsFunctor>
ReturnType Exact::evaluateSampleBased(
                                  const XIndepType& x_indep_value,
                                  const YIndepType& y_indep_value,
                                  const YBoundsFunctor& min_y_indep_functor,
                                  const YBoundsFunctor& max_y_indep_functor,
                                  const EvaluationMethod& evaluate,
                                  const YZIterator& lower_bin_boundary,
                                  const YZIterator& upper_bin_boundary,
                                  const ReturnType& below_lower_bound_return,
                                  const ReturnType& above_upper_bound_return,
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
    // Calculate the bin length of the first indep variable
    const typename QuantityTraits<XIndepType>::RawType x_bin_length =
      TwoDInterpPolicy::ZXInterpPolicy::calculateUnitBaseGridLength(
                                                    lower_bin_boundary->first,
                                                    upper_bin_boundary->first );

    // Calculate the first indep variable bin ratio (beta)
    const typename QuantityTraits<XIndepType>::RawType beta =
      TwoDInterpPolicy::ZXInterpPolicy::calculateUnitBaseIndepVar(
                                                    x_indep_value,
                                                    lower_bin_boundary->first,
                                                    x_bin_length );

    // Get the lower secondary indep grid limits at the primary value
    YIndepType lower_sec_indep_var_bound =
      TwoDInterpPolicy::YXInterpPolicy::interpolate(
                      beta,
                      lower_bin_boundary->second->getLowerBoundOfIndepVar(),
                      upper_bin_boundary->second->getLowerBoundOfIndepVar() );

    // Get the upper secondary indep grid limits at the primary value
    YIndepType upper_sec_indep_var_bound =
      TwoDInterpPolicy::YXInterpPolicy::interpolate(
                      beta,
                      lower_bin_boundary->second->getUpperBoundOfIndepVar(),
                      upper_bin_boundary->second->getUpperBoundOfIndepVar() );

    // Get the min and max y indep values
    YIndepType min_y_indep_var = min_y_indep_functor( x_indep_value);
    YIndepType max_y_indep_var = max_y_indep_functor( x_indep_value);

    // Check for a seconday indep value outside of the secondary indep grid limits
    if ( y_indep_value < lower_sec_indep_var_bound )
      return below_lower_bound_return;
    else if ( y_indep_value > upper_sec_indep_var_bound )
      return above_upper_bound_return;
    else if ( y_indep_value == lower_sec_indep_var_bound )
    {
      return TwoDInterpPolicy::ZXInterpPolicy::interpolate(
                beta,
                ((*lower_bin_boundary->second).*evaluate)(lower_bin_boundary->second->getLowerBoundOfIndepVar()),
                ((*upper_bin_boundary->second).*evaluate)(upper_bin_boundary->second->getLowerBoundOfIndepVar()) );
    }
    else if ( y_indep_value == upper_sec_indep_var_bound )
    {
      return TwoDInterpPolicy::ZXInterpPolicy::interpolate(
                beta,
                ((*lower_bin_boundary->second).*evaluate)(lower_bin_boundary->second->getUpperBoundOfIndepVar()),
                ((*upper_bin_boundary->second).*evaluate)(upper_bin_boundary->second->getUpperBoundOfIndepVar()) );
    }
    else
    {
      // Get the lower and upper boundaries of the evaluated cdf
      double lower_cdf_bound, upper_cdf_bound;
      {
        // Evaluate the cdf at the upper and lower bin boundaries
        double bin_eval_0 =
          ((*lower_bin_boundary->second).*&BaseOneDDistributionType::evaluateCDF)( y_indep_value );
        double bin_eval_1 =
          ((*upper_bin_boundary->second).*&BaseOneDDistributionType::evaluateCDF)( y_indep_value );

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

      unsigned number_of_iterations = 0;
      YIndepType lower_bin_sample, upper_bin_sample;
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
      while ( rel_error > tolerance )
      {
        // Estimate the cdf as the midpoint of the lower and upper boundaries
        double estimated_cdf = 0.5*( lower_cdf_bound + upper_cdf_bound );

        // Get the sampled values at the upper and lower bin for the estimated_cdf
        lower_bin_sample =
          ((*lower_bin_boundary->second).*&BaseOneDDistributionType::sampleWithRandomNumber)( estimated_cdf );
        upper_bin_sample =
          ((*upper_bin_boundary->second).*&BaseOneDDistributionType::sampleWithRandomNumber)( estimated_cdf );

        // Interpolate using the templated TwoDInterpPolicy::YXInterpPolicy
        YIndepType est_y_indep_value =
          TwoDInterpPolicy::YXInterpPolicy::interpolate( beta,
                                                         lower_bin_sample,
                                                         upper_bin_sample );

        if ( y_indep_value == est_y_indep_value )
          break;

        // Calculate the relative error between the y_indep_value and the estimate
        rel_error = (y_indep_value - est_y_indep_value )/
                                                            error_norm_constant;

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
          lower_cdf_bound = estimated_cdf;
        }
        else
        {
          // Old estimated_cdf estimate is new upper cdf boundary
          upper_cdf_bound = estimated_cdf;
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
                              << rel_error_tol
                              << ")." );
          }
        }
      }

      ReturnType lower_eval =
                  ((*lower_bin_boundary->second).*evaluate)(lower_bin_sample);
      ReturnType upper_eval =
                  ((*upper_bin_boundary->second).*evaluate)(upper_bin_sample);

      if( lower_eval == upper_eval )
        return lower_eval;

      // Return the interpolated evaluation
      return TwoDInterpPolicy::ZXInterpPolicy::interpolate(
                  lower_bin_boundary->first,
                  upper_bin_boundary->first,
                  x_indep_value,
                  lower_eval,
                  upper_eval );
    }
  }
}

// Evaluate between bin boundaries using the desired evaluation method
template<typename TwoDInterpPolicy,
         typename BaseOneDDistributionType,
         typename XIndepType,
         typename YIndepType,
         typename ReturnType,
         typename YZIterator,
         typename EvaluationMethod,
         typename YBoundsFunctor>
ReturnType Exact::evaluateDirect(
                                  const XIndepType& x_indep_value,
                                  const YIndepType& y_indep_value,
                                  const YBoundsFunctor& min_y_indep_functor,
                                  const YBoundsFunctor& max_y_indep_functor,
                                  const EvaluationMethod& evaluate,
                                  const YZIterator& lower_bin_boundary,
                                  const YZIterator& upper_bin_boundary,
                                  const ReturnType& below_lower_bound_return,
                                  const ReturnType& above_upper_bound_return,
                                  const double fuzzy_boundary_tol )
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
    ReturnType min_eval_0 = ((*lower_bin_boundary->second).*evaluate)(y_indep_value);
    ReturnType min_eval_1 = ((*upper_bin_boundary->second).*evaluate)(y_indep_value);

    if ( min_eval_0 == min_eval_1 )
      return min_eval_0;
    else
    {
      // Return the interpolated evaluation
      return TwoDInterpPolicy::ZXInterpPolicy::interpolate(
              lower_bin_boundary->first,
              upper_bin_boundary->first,
              x_indep_value,
              min_eval_0,
              min_eval_1 );
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

// Evaluate between bin boundaries using the desired evaluation method
/*! \details This method performs a type of binary search using sampling to
 *  estimate the CDF to a relative error tolerance to find the interpolation.
 *  The lower and upper bounds of the secondary independent variable
 *  (cosine) are fixed (-1 <= cosine <= 1). Therefore a unit base method is not
 *  necessary and an exact method is used to evaluate instead.
 */
template<typename TwoDInterpPolicy,
         typename BaseOneDDistributionType,
         typename XIndepType,
         typename YIndepType,
         typename ReturnType,
         typename YZIterator,
         typename EvaluationMethod,
         typename YBoundsFunctor>
ReturnType Correlated::evaluateCosSampleBased(
                                  const XIndepType& x_indep_value,
                                  const YIndepType& y_indep_value,
                                  const YBoundsFunctor& min_y_indep_functor,
                                  const YBoundsFunctor& max_y_indep_functor,
                                  const EvaluationMethod& evaluate,
                                  const YZIterator& lower_bin_boundary,
                                  const YZIterator& upper_bin_boundary,
                                  const double rel_error_tol,
                                  const double error_tol,
                                  unsigned max_number_of_iterations )
{
  return Exact::evaluateCosSampleBased<TwoDInterpPolicy,
                                       BaseOneDDistributionType,
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
                                                    rel_error_tol,
                                                    error_tol,
                                                    max_number_of_iterations );
}

// Evaluate between bin boundaries using the desired evaluation method
/*! \details This method performs a type of binary search using a unit base
 *  correlated sampling to estimate the CDF to a relative error tolerance in
 *  order to find the proper interpolation. The result is consistent with the
 *  correlated sampling methods.
 */
template<typename TwoDInterpPolicy,
         typename BaseOneDDistributionType,
         typename XIndepType,
         typename YIndepType,
         typename ReturnType,
         typename YZIterator,
         typename EvaluationMethod,
         typename YBoundsFunctor>
ReturnType Correlated::evaluateSampleBased(
                                  const XIndepType& x_indep_value,
                                  const YIndepType& y_indep_value,
                                  const YBoundsFunctor& min_y_indep_functor,
                                  const YBoundsFunctor& max_y_indep_functor,
                                  const EvaluationMethod& evaluate,
                                  const YZIterator& lower_bin_boundary,
                                  const YZIterator& upper_bin_boundary,
                                  const ReturnType& below_lower_bound_return,
                                  const ReturnType& above_upper_bound_return,
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
    YIndepType min_y_indep_var = min_y_indep_functor( x_indep_value );
    YIndepType max_y_indep_var = max_y_indep_functor( x_indep_value );

    // Check for a y indep value outside of the y indep grid limits
    if ( y_indep_value < min_y_indep_var )
      return below_lower_bound_return;
    else if ( y_indep_value > max_y_indep_var )
      return above_upper_bound_return;
    else if ( y_indep_value == min_y_indep_var )
    {
      return TwoDInterpPolicy::ZXInterpPolicy::interpolate(
                beta,
                ((*lower_bin_boundary->second).*evaluate)(lower_bin_boundary->second->getLowerBoundOfIndepVar()),
                ((*upper_bin_boundary->second).*evaluate)(upper_bin_boundary->second->getLowerBoundOfIndepVar()) );
    }
    else if ( y_indep_value == max_y_indep_var )
    {
      return TwoDInterpPolicy::ZXInterpPolicy::interpolate(
                beta,
                ((*lower_bin_boundary->second).*evaluate)(lower_bin_boundary->second->getUpperBoundOfIndepVar()),
                ((*upper_bin_boundary->second).*evaluate)(upper_bin_boundary->second->getUpperBoundOfIndepVar()) );
    }
    else
    {
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
                        min_y_indep_var,
                        max_y_indep_var );

      // Get the lower and upper boundaries of the evaluated cdf
      double lower_cdf_bound, upper_cdf_bound;
      {

        YIndepType min_y_indep_var_with_tol =
            TwoDInterpPolicy::ZYInterpPolicy::calculateFuzzyLowerBound(
                        min_y_indep_var );

        YIndepType max_y_indep_var_with_tol =
            TwoDInterpPolicy::ZYInterpPolicy::calculateFuzzyUpperBound(
                        max_y_indep_var );

        // Calculate the unit base variable on the intermediate grid
        typename QuantityTraits<YIndepType>::RawType eta =
            TwoDInterpPolicy::ZYInterpPolicy::calculateUnitBaseIndepVar(
                y_indep_value,
                min_y_indep_var,
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
          ((*lower_bin_boundary->second).*&BaseOneDDistributionType::evaluateCDF)( y_indep_value_0 );
        double bin_eval_1 =
          ((*upper_bin_boundary->second).*&BaseOneDDistributionType::evaluateCDF)( y_indep_value_1 );

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

    unsigned number_of_iterations = 0;
    YIndepType lower_bin_sample, upper_bin_sample;
    double rel_error = 1.0;
    YIndepType error_norm_constant = y_indep_value;
    double tolerance = rel_error_tol;

    /*! \detials If the y indep var value is zero the relative error
     *  will always zero or inf. When this is the case the error tolerance will
     *  be used instead of the relative error tolerance.
     */
     if ( y_indep_value == QuantityTraits<YIndepType>::zero() )
     {
        error_norm_constant = QuantityTraits<YIndepType>::one();
        tolerance = error_tol;
     }

    // Refine the estimated cdf value until it meet the tolerance
    while ( rel_error > tolerance )
    {
      // Estimate the cdf as the midpoint of the lower and upper boundaries
      double estimated_cdf = 0.5*( lower_cdf_bound + upper_cdf_bound );

      // Get the sampled values at the upper and lower bin for the estimated_cdf
      lower_bin_sample =
        ((*lower_bin_boundary->second).*&BaseOneDDistributionType::sampleWithRandomNumber)( estimated_cdf );
      upper_bin_sample =
        ((*upper_bin_boundary->second).*&BaseOneDDistributionType::sampleWithRandomNumber)( estimated_cdf );

      // Calculate the unit base variable on the intermediate grid corresponding to the
      // raw samples on the lower and upper boundaries
      typename QuantityTraits<YIndepType>::RawType
        eta_estimate, eta_0, eta_1;

      eta_0 =
        TwoDInterpPolicy::ZYInterpPolicy::calculateUnitBaseIndepVar(
            lower_bin_sample,
            lower_bin_boundary->second->getLowerBoundOfIndepVar(),
            grid_length_0 );

      eta_1 =
        TwoDInterpPolicy::ZYInterpPolicy::calculateUnitBaseIndepVar(
            upper_bin_sample,
            upper_bin_boundary->second->getLowerBoundOfIndepVar(),
            grid_length_1 );

      // Interpolate using the templated TwoDInterpPolicy::YXInterpPolicy
      eta_estimate =
        TwoDInterpPolicy::YXInterpPolicy::interpolate( beta, eta_0, eta_1 );

      // Scale the sample so that it preserves the intermediate limits.
      YIndepType est_y_indep_value =
        TwoDInterpPolicy::ZYInterpPolicy::calculateIndepVar(
            eta_estimate,
            min_y_indep_var,
            intermediate_grid_length );

      // Update the number of iterations
      ++number_of_iterations;

      if ( y_indep_value == est_y_indep_value )
        break;

      // Calculate the relative error between the y_indep_value and the estimate
      rel_error = (y_indep_value - est_y_indep_value )/error_norm_constant;

      // Make sure the relative error is positive
      rel_error = rel_error < 0 ? -rel_error : rel_error;

      // If tolerance is met exit loop
      if ( rel_error <= tolerance )
        break;

      // Update the estimated_cdf estimate
      if ( est_y_indep_value < y_indep_value )
      {
        // Old estimated_cdf estimate is new lower cdf boundary
        lower_cdf_bound = estimated_cdf;
      }
      else
      {
        // Old estimated_cdf estimate is new upper cdf boundary
        upper_cdf_bound = estimated_cdf;
      }

      // Check for the max number of iterations
      if ( number_of_iterations > max_number_of_iterations )
      {
        // Get error in estimate
        double error =
            (y_indep_value - est_y_indep_value )/
                                QuantityTraits<YIndepType>::one();
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
                       << rel_error_tol
                       << ")." );
        }
      }
    }

    // Return the interpolated evaluation
    return TwoDInterpPolicy::ZXInterpPolicy::interpolate(
                lower_bin_boundary->first,
                upper_bin_boundary->first,
                x_indep_value,
                ((*lower_bin_boundary->second).*evaluate)(lower_bin_sample),
                ((*upper_bin_boundary->second).*evaluate)(upper_bin_sample) );
    }
  }
}

// Evaluate between bin boundaries using the desired evaluation method
template<typename TwoDInterpPolicy,
         typename BaseOneDDistributionType,
         typename XIndepType,
         typename YIndepType,
         typename ReturnType,
         typename YZIterator,
         typename EvaluationMethod,
         typename YBoundsFunctor>
ReturnType Correlated::evaluateDirect(
                                  const XIndepType& x_indep_value,
                                  const YIndepType& y_indep_value,
                                  const YBoundsFunctor& min_y_indep_functor,
                                  const YBoundsFunctor& max_y_indep_functor,
                                  const EvaluationMethod& evaluate,
                                  const YZIterator& lower_bin_boundary,
                                  const YZIterator& upper_bin_boundary,
                                  const ReturnType& below_lower_bound_return,
                                  const ReturnType& above_upper_bound_return,
                                  const double fuzzy_boundary_tol )
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
                        lower_bin_boundary->second->getLowerBoundOfIndepVar(),
                        lower_bin_boundary->second->getUpperBoundOfIndepVar(),
                        upper_bin_boundary->second->getLowerBoundOfIndepVar(),
                        upper_bin_boundary->second->getUpperBoundOfIndepVar(),
                        evaluate_grid_0_functor,
                        evaluate_grid_1_functor,
                        below_lower_bound_return,
                        above_upper_bound_return,
                        fuzzy_boundary_tol );
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
      TwoDInterpPolicy::ZYInterpPolicy::calculateUnitBaseGridLength(
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
        TwoDInterpPolicy::ZYInterpPolicy::calculateUnitBaseGridLength(
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
        TwoDInterpPolicy::ZYInterpPolicy::calculateUnitBaseGridLength(
                    upper_bin_boundary->second->getLowerBoundOfIndepVar(),
                    max_y_indep_var_1 );

      eta_1 = TwoDInterpPolicy::ZYInterpPolicy::calculateUnitBaseIndepVar(
            subrange_sample_functor( *upper_bin_boundary->second, max_y_indep_var_1 ),
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

        // Interpolate between the lower and upper unit base variables
        eta = TwoDInterpPolicy::YXInterpPolicy::interpolate(
                                                  lower_bin_boundary->first,
                                                  upper_bin_boundary->first,
                                                  x_indep_value,
                                                  eta_0,
                                                  eta_1 );
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
