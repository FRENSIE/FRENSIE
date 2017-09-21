//---------------------------------------------------------------------------//
//!
//! \file   Utility_InterpolatedFullyTabularTwoDDistribution_def.hpp
//! \author Alex Robinson
//! \brief  The interpolated fully tabular two-dimensional dist. class def.
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_INTERPOLATED_FULLY_TABULAR_TWO_D_DISTRIBUTION_DEF_HPP
#define UTILITY_INTERPOLATED_FULLY_TABULAR_TWO_D_DISTRIBUTION_DEF_HPP

// FRENSIE Includes
#include "Utility_TabularDistribution.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_SortAlgorithms.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_ContractException.hpp"

namespace Utility{

// Constructor
template<typename TwoDInterpPolicy,
         typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit>
template<template<typename T, typename... Args> class ArrayA,
         template<typename T, typename... Args> class ArrayB,
         template<typename T, typename... Args> class SubarrayB,
         template<typename T, typename... Args> class ArrayC,
         template<typename T, typename... Args> class SubarrayC>
UnitAwareInterpolatedFullyTabularTwoDDistribution<TwoDInterpPolicy,PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>::UnitAwareInterpolatedFullyTabularTwoDDistribution(
        const ArrayA<PrimaryIndepQuantity>& primary_indep_grid,
        const ArrayB<SubarrayB<SecondaryIndepQuantity> >& secondary_indep_grids,
        const ArrayC<SubarrayC<DepQuantity> >& dependent_values,
        const double fuzzy_boundary_tol,
        const double evaluate_relative_error_tol,
        const double evaluate_error_tol )
  : d_relative_error_tol( evaluate_relative_error_tol ),
    d_error_tol( evaluate_error_tol )
{
  // Make sure the grids are valid
  testPrecondition( Sort::isSortedAscending( primary_indep_grid.begin(),
                                             primary_indep_grid.end() ) );
  testPrecondition( primary_indep_grid.size() > 1 );
  testPrecondition( primary_indep_grid.size() == secondary_indep_grids.size());
  testPrecondition( primary_indep_grid.size() == dependent_values.size() );

  // Construct the 2D distribution
  DistributionType distribution( primary_indep_grid.size() );
  
  for( size_t i = 0; i < primary_indep_grid.size(); ++i )
  {
    distribution[i].first = primary_indep_grid[i];
    distribution[i].second.reset(
          new UnitAwareTabularDistribution<typename TwoDInterpPolicy::SecondaryBasePolicy,SecondaryIndependentUnit,DependentUnit>(
                                                      secondary_indep_grids[i],
                                                      dependent_values[i] ) );
  }

  // Set the 2D distribution
  this->setDistribution( distribution );
}

//---------------------------------------------------------------------------//
// EVALUATING METHODS
//---------------------------------------------------------------------------//

// Correlated evaluate the distribution (unit based)
/*! \details This method performs a type of binary search using a unit based
 *  correlated sampling to estimate the CDF to a relative error tolerance in
 *  order to find the proper interpolation. The result is consistent with the
 *  correlatedSampleSecondaryConditional methods.
 */
template<typename TwoDInterpPolicy,
         typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit>
auto UnitAwareInterpolatedFullyTabularTwoDDistribution<TwoDInterpPolicy,PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>::correlatedEvaluateInBoundaries(
                const PrimaryIndepQuantity primary_indep_var_value,
                const SecondaryIndepQuantity secondary_indep_var_value,
                const SecondaryIndepQuantity min_secondary_indep_var,
                const SecondaryIndepQuantity max_secondary_indep_var ) const
  -> DepQuantity
{
  return this->template correlatedEvaluateImpl<TwoDInterpPolicy,DepQuantity>(
                                          primary_indep_var_value,
                                          secondary_indep_var_value,
                                          min_secondary_indep_var,
                                          max_secondary_indep_var,
                                          &BaseOneDDistributionType::evaluate );
}

// Correlated evaluate the distribution (unit based)
/*! \details This method performs a type of binary search using a unit based
 *  correlated sampling to estimate the CDF to a relative error tolerance in
 *  order to find the proper interpolation. The result is consistent with the
 *  correlatedSampleSecondaryConditional methods.
 *  The lower and upper conditional boundaries will be use as the min and max
 *  secondary independent variable values.
 */
template<typename TwoDInterpPolicy,
         typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit>
auto UnitAwareInterpolatedFullyTabularTwoDDistribution<TwoDInterpPolicy,PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>::correlatedEvaluate(
                const PrimaryIndepQuantity primary_indep_var_value,
                const SecondaryIndepQuantity secondary_indep_var_value ) const
  -> DepQuantity
{
  // Get the min and max secondary independent variable values
  SecondaryIndepQuantity min_secondary_indep_var =
    this->getLowerBoundOfConditionalIndepVar( primary_indep_var_value );
  SecondaryIndepQuantity max_secondary_indep_var =
    this->getUpperBoundOfConditionalIndepVar( primary_indep_var_value );

  return this->correlatedEvaluateInBoundaries( primary_indep_var_value,
                                               secondary_indep_var_value,
                                               min_secondary_indep_var,
                                               max_secondary_indep_var );
}

// Evaluate the distribution
/*! \details This method performs a type of binary search using a unit based
 *  correlated sampling to estimate the CDF to a relative error tolerance in
 *  order to find the proper interpolation. The result is consistent with the
 *  sampleSecondaryConditionalExact methods.
 */
template<typename TwoDInterpPolicy,
         typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit>
auto UnitAwareInterpolatedFullyTabularTwoDDistribution<TwoDInterpPolicy,PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>::evaluateExact(
                 const PrimaryIndepQuantity primary_indep_var_value,
                 const SecondaryIndepQuantity secondary_indep_var_value ) const
  -> DepQuantity
{
  return this->template evaluateExactImpl<TwoDInterpPolicy,DepQuantity>(
                                          primary_indep_var_value,
                                          secondary_indep_var_value,
                                          &BaseOneDDistributionType::evaluate );
}

// Correlated evaluate the secondary conditional PDF
/*! \details This method performs a type of binary search using a unit based
 *  correlated sampling to estimate the CDF to a relative error tolerance in
 *  order to find the proper interpolation. The result is consistent with the
 *  correlatedSampleSecondaryConditional methods.
 */
template<typename TwoDInterpPolicy,
         typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit>
auto UnitAwareInterpolatedFullyTabularTwoDDistribution<TwoDInterpPolicy,PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>::correlatedEvaluateSecondaryConditionalPDFInBoundaries(
                const PrimaryIndepQuantity primary_indep_var_value,
                const SecondaryIndepQuantity secondary_indep_var_value,
                const SecondaryIndepQuantity min_secondary_indep_var,
                const SecondaryIndepQuantity max_secondary_indep_var ) const
  ->  InverseSecondaryIndepQuantity
{
  return this->template correlatedEvaluateImpl<TwoDInterpPolicy,InverseSecondaryIndepQuantity>(
                                    primary_indep_var_value,
                                    secondary_indep_var_value,
                                    min_secondary_indep_var,
                                    max_secondary_indep_var,
                                    &BaseOneDDistributionType::evaluatePDF );
}

// Correlated evaluate the secondary conditional PDF
/*! \details This method performs a type of binary search using a unit based
 *  correlated sampling to estimate the CDF to a relative error tolerance in
 *  order to find the proper interpolation. The result is consistent with the
 *  correlatedSampleSecondaryConditional methods.
 *  The lower and upper conditional boundaries will be use as the min and max
 *  secondary independent variable values.
 */
template<typename TwoDInterpPolicy,
         typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit>
auto UnitAwareInterpolatedFullyTabularTwoDDistribution<TwoDInterpPolicy,PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>::correlatedEvaluateSecondaryConditionalPDF(
                const PrimaryIndepQuantity primary_indep_var_value,
                const SecondaryIndepQuantity secondary_indep_var_value ) const
  ->  InverseSecondaryIndepQuantity
{
  // Get the min and max secondary independent variable values
  SecondaryIndepQuantity min_secondary_indep_var =
    this->getLowerBoundOfConditionalIndepVar( primary_indep_var_value );
  SecondaryIndepQuantity max_secondary_indep_var =
    this->getUpperBoundOfConditionalIndepVar( primary_indep_var_value );

  return this->correlatedEvaluateSecondaryConditionalPDFInBoundaries(
                                                    primary_indep_var_value,
                                                    secondary_indep_var_value,
                                                    min_secondary_indep_var,
                                                    max_secondary_indep_var );
}

// Evaluate the secondary conditional PDF
/*! \details This method performs a type of binary search using a unit based
 *  correlated sampling to estimate the CDF to a relative error tolerance in
 *  order to find the proper interpolation. The result is consistent with the
 *  sampleSecondaryConditionalExact methods.
 */
template<typename TwoDInterpPolicy,
         typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit>
auto UnitAwareInterpolatedFullyTabularTwoDDistribution<TwoDInterpPolicy,PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>::evaluateSecondaryConditionalPDFExact(
                 const PrimaryIndepQuantity primary_indep_var_value,
                 const SecondaryIndepQuantity secondary_indep_var_value ) const
  -> InverseSecondaryIndepQuantity
{
  return this->template evaluateExactImpl<TwoDInterpPolicy,InverseSecondaryIndepQuantity>(
                                      primary_indep_var_value,
                                      secondary_indep_var_value,
                                      &BaseOneDDistributionType::evaluatePDF );
}

// Evaluate the secondary conditional CDF
template<typename TwoDInterpPolicy,
         typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit>
double UnitAwareInterpolatedFullyTabularTwoDDistribution<TwoDInterpPolicy,PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>::evaluateSecondaryConditionalCDF(
                 const PrimaryIndepQuantity primary_indep_var_value,
                 const SecondaryIndepQuantity secondary_indep_var_value ) const
{
  return this->template evaluateImpl<CDFInterpPolicy,double>(
                                      primary_indep_var_value,
                                      secondary_indep_var_value,
                                      &BaseOneDDistributionType::evaluateCDF,
                                      0.0,
                                      1.0 );
}

// Correlated evaluate the secondary conditional CDF
/*! \details This method performs a type of binary search using a unit based
 *  correlated sampling to estimate the CDF to a relative error tolerance. The
 *  result is consistent with the correlatedSampleSecondaryConditional methods.
 */
template<typename TwoDInterpPolicy,
         typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit>
double UnitAwareInterpolatedFullyTabularTwoDDistribution<TwoDInterpPolicy,PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>::correlatedEvaluateSecondaryConditionalCDFInBoundaries(
                const PrimaryIndepQuantity primary_indep_var_value,
                const SecondaryIndepQuantity secondary_indep_var_value,
                const SecondaryIndepQuantity min_secondary_indep_var,
                const SecondaryIndepQuantity max_secondary_indep_var ) const
{
  return this->template correlatedEvaluateImpl<TwoDInterpPolicy,double>(
                                      primary_indep_var_value,
                                      secondary_indep_var_value,
                                      min_secondary_indep_var,
                                      max_secondary_indep_var,
                                      &BaseOneDDistributionType::evaluateCDF,
                                      0.0,
                                      1.0 );
}

// Correlated evaluate the secondary conditional CDF
/*! \details This method performs a type of binary search using a unit based
 *  correlated sampling to estimate the CDF to a relative error tolerance. The
 *  result is consistent with the correlatedSampleSecondaryConditional methods.
 *  The lower and upper conditional boundaries will be use as the min and max
 *  secondary independent variable values.
 */
template<typename TwoDInterpPolicy,
         typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit>
double UnitAwareInterpolatedFullyTabularTwoDDistribution<TwoDInterpPolicy,PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>::correlatedEvaluateSecondaryConditionalCDF(
                const PrimaryIndepQuantity primary_indep_var_value,
                const SecondaryIndepQuantity secondary_indep_var_value ) const
{
  // Get the min and max secondary independent variable values
  SecondaryIndepQuantity min_secondary_indep_var =
    this->getLowerBoundOfConditionalIndepVar( primary_indep_var_value );
  SecondaryIndepQuantity max_secondary_indep_var =
    this->getUpperBoundOfConditionalIndepVar( primary_indep_var_value );

  return this->correlatedEvaluateSecondaryConditionalCDFInBoundaries(
                                                    primary_indep_var_value,
                                                    secondary_indep_var_value,
                                                    min_secondary_indep_var,
                                                    max_secondary_indep_var );
}

// Evaluate the secondary conditional CDF
/*! \details This method performs a type of binary search using a unit based
 *  correlated sampling to estimate the CDF to a relative error tolerance.
 *  The result is consistent with the sampleSecondaryConditionalExact methods.
 */
template<typename TwoDInterpPolicy,
         typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit>
double UnitAwareInterpolatedFullyTabularTwoDDistribution<TwoDInterpPolicy,PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>::evaluateSecondaryConditionalCDFExact(
                 const PrimaryIndepQuantity primary_indep_var_value,
                 const SecondaryIndepQuantity secondary_indep_var_value ) const
{
  return this->template evaluateExactImpl<CDFInterpPolicy,double>(
                                      primary_indep_var_value,
                                      secondary_indep_var_value,
                                      &BaseOneDDistributionType::evaluateCDF,
                                      0.0,
                                      1.0 );
}

// Evaluate the distribution using the desired evaluation method
/*! \details This method performs a type of binary search using an exact
 *  correlated sampling to estimate the CDF to a relative error tolerance to
 *  find the proper interpolation for the evaluation method. If the realtive
 *  error tolerance is not met after the max number of iterations but the error
 *  tolerance is met then the estimated value will be returned, otherwise an
 *  error message will be thrown. The estimated result is consistent with the
 *  sampleSecondaryConditionalExact methods.
 */
template<typename TwoDInterpPolicy,
         typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit>
template<typename LocalTwoDInterpPolicy,
         typename ReturnType,
         typename EvaluationMethod>
inline ReturnType UnitAwareInterpolatedFullyTabularTwoDDistribution<TwoDInterpPolicy,PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>::evaluateExactImpl(
                        const PrimaryIndepQuantity primary_indep_var_value,
                        const SecondaryIndepQuantity secondary_indep_var_value,
                        EvaluationMethod evaluate,
                        const ReturnType below_lower_bound_return,
                        const ReturnType above_upper_bound_return,
                        unsigned max_number_of_iterations ) const
{
  // Find the bin boundaries
  typename DistributionType::const_iterator lower_bin_boundary, upper_bin_boundary;

  this->findBinBoundaries( primary_indep_var_value,
                           lower_bin_boundary,
                           upper_bin_boundary );

  // Check for a primary value outside of the primary grid limits
  if( lower_bin_boundary == upper_bin_boundary )
  {
    if( this->arePrimaryLimitsExtended() )
      return ((*lower_bin_boundary->second).*evaluate)(secondary_indep_var_value);
    else
      return QuantityTraits<ReturnType>::zero();
  }
  else if( lower_bin_boundary->first == primary_indep_var_value )
  {
    return ((*lower_bin_boundary->second).*evaluate)(secondary_indep_var_value);
  }
  else if( upper_bin_boundary->first == primary_indep_var_value )
  {
    return ((*upper_bin_boundary->second).*evaluate)(secondary_indep_var_value);
  }
  else
  {
    // Calculate the bin length of the first indep variable
    const typename QuantityTraits<PrimaryIndepQuantity>::RawType primary_bin_length =
      TwoDInterpPolicy::PrimaryBasePolicy::calculateUnitBaseGridLength(
                                                    lower_bin_boundary->first,
                                                    upper_bin_boundary->first );

    // Calculate the first indep variable bin ratio (beta)
    const typename QuantityTraits<PrimaryIndepQuantity>::RawType beta =
      TwoDInterpPolicy::PrimaryBasePolicy::calculateUnitBaseIndepVar(
                                                    primary_indep_var_value,
                                                    lower_bin_boundary->first,
                                                    primary_bin_length );

    // Get the lower secondary indep grid limits at the primary value
    SecondaryIndepQuantity lower_sec_indep_var_bound =
      TwoDInterpPolicy::ZXInterpPolicy::interpolate(
                      beta,
                      lower_bin_boundary->second->getLowerBoundOfIndepVar(),
                      upper_bin_boundary->second->getLowerBoundOfIndepVar() );

    // Get the upper secondary indep grid limits at the primary value
    SecondaryIndepQuantity upper_sec_indep_var_bound =
      TwoDInterpPolicy::ZXInterpPolicy::interpolate(
                      beta,
                      lower_bin_boundary->second->getUpperBoundOfIndepVar(),
                      upper_bin_boundary->second->getUpperBoundOfIndepVar() );

    // Check for a seconday indep value outside of the secondary indep grid limits
    if ( secondary_indep_var_value < lower_sec_indep_var_bound )
      return below_lower_bound_return;
    else if ( secondary_indep_var_value > upper_sec_indep_var_bound )
      return above_upper_bound_return;
    else if ( secondary_indep_var_value == lower_sec_indep_var_bound )
    {
      return TwoDInterpPolicy::ZXInterpPolicy::interpolate(
                beta,
                ((*lower_bin_boundary->second).*evaluate)(lower_bin_boundary->second->getLowerBoundOfIndepVar()),
                ((*upper_bin_boundary->second).*evaluate)(upper_bin_boundary->second->getLowerBoundOfIndepVar()) );
    }
    else if ( secondary_indep_var_value == upper_sec_indep_var_bound )
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
          ((*lower_bin_boundary->second).*&BaseOneDDistributionType::evaluateCDF)( secondary_indep_var_value );
        double bin_eval_1 =
          ((*upper_bin_boundary->second).*&BaseOneDDistributionType::evaluateCDF)( secondary_indep_var_value );

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
      SecondaryIndepQuantity lower_bin_sample, upper_bin_sample;
      double rel_error = 1.0;
      SecondaryIndepQuantity error_norm_constant = secondary_indep_var_value;
      double tolerance = d_relative_error_tol;

      /*! \detials If the secondary indep var value is zero the relative error
       *  will always zero or inf. When this is the case the error tolerance will
       *  be used instead of the relative error tolerance.
       */
       if ( secondary_indep_var_value == SIQT::zero() )
       {
          error_norm_constant = SIQT::one();
          tolerance = d_error_tol;
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

        // Interpolate using the templated TwoDInterpPolicy::ZXInterpPolicy
        SecondaryIndepQuantity est_secondary_indep_var_value =
          TwoDInterpPolicy::ZXInterpPolicy::interpolate( beta,
                                                         lower_bin_sample,
                                                         upper_bin_sample );

        if ( secondary_indep_var_value == est_secondary_indep_var_value )
          break;

        // Calculate the relative error between the secondary_indep_var_value and the estimate
        rel_error = (secondary_indep_var_value - est_secondary_indep_var_value )/
                                                            error_norm_constant;

        // Make sure the relative error is positive
        rel_error = rel_error < 0 ? -rel_error : rel_error;

        // Update the number of iterations
        ++number_of_iterations;

        // If tolerance is met exit loop
        if ( rel_error <= tolerance )
          break;

        // Update the estimated_cdf estimate
        if ( est_secondary_indep_var_value < secondary_indep_var_value )
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
            (secondary_indep_var_value - est_secondary_indep_var_value )/SIQT::one();
          error = error < 0 ? -error : error;

          // If error meets error tolerance accept estimate
          if ( error < d_error_tol )
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
                             << d_relative_error_tol
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
                  primary_indep_var_value,
                  lower_eval,
                  upper_eval );
    }
  }
}

// Evaluate the distribution using the desired evaluation method
/*! \details This method performs a type of binary search using a unit based
 *  correlated sampling to estimate the CDF to a relative error tolerance to
 *  find the proper interpolation for the evaluation method. If the realtive
 *  error tolerance is not met after the max number of iterations but the error
 *  tolerance is met then the estimated value will be returned, otherwise an
 *  error message will be thrown. The estimated result is consistent with the
 *  sampleSecondaryConditionalExact methods.
 */
template<typename TwoDInterpPolicy,
         typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit>
template<typename LocalTwoDInterpPolicy,
         typename ReturnType,
         typename EvaluationMethod>
inline ReturnType UnitAwareInterpolatedFullyTabularTwoDDistribution<TwoDInterpPolicy,PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>::correlatedEvaluateImpl(
                        const PrimaryIndepQuantity primary_indep_var_value,
                        const SecondaryIndepQuantity secondary_indep_var_value,
                        const SecondaryIndepQuantity min_secondary_indep_var,
                        const SecondaryIndepQuantity max_secondary_indep_var,
                        EvaluationMethod evaluate,
                        const ReturnType below_lower_bound_return,
                        const ReturnType above_upper_bound_return,
                        unsigned max_number_of_iterations ) const
{
  // Find the bin boundaries
  typename DistributionType::const_iterator lower_bin_boundary, upper_bin_boundary;

  this->findBinBoundaries( primary_indep_var_value,
                           lower_bin_boundary,
                           upper_bin_boundary );

  // Check for a primary value outside of the primary grid limits
  if( lower_bin_boundary == upper_bin_boundary )
  {
    if( this->arePrimaryLimitsExtended() )
      return ((*lower_bin_boundary->second).*evaluate)(secondary_indep_var_value);
    else 
      return QuantityTraits<ReturnType>::zero();
  }
  else if( lower_bin_boundary->first == primary_indep_var_value )
  {
    return ((*lower_bin_boundary->second).*evaluate)(secondary_indep_var_value);
  }
  else if( upper_bin_boundary->first == primary_indep_var_value )
  {
    return ((*upper_bin_boundary->second).*evaluate)(secondary_indep_var_value);
  }
  else
  {
    // Calculate the bin length of the first indep variable
    const typename QuantityTraits<PrimaryIndepQuantity>::RawType primary_bin_length =
      TwoDInterpPolicy::PrimaryBasePolicy::calculateUnitBaseGridLength(
                                                    lower_bin_boundary->first,
                                                    upper_bin_boundary->first );

    // Calculate the first indep variable bin ratio (beta)
    const typename QuantityTraits<PrimaryIndepQuantity>::RawType beta =
      TwoDInterpPolicy::PrimaryBasePolicy::calculateUnitBaseIndepVar(
                                                    primary_indep_var_value,
                                                    lower_bin_boundary->first,
                                                    primary_bin_length );

    // Check for a seconday indep value outside of the secondary indep grid limits
    if ( secondary_indep_var_value < min_secondary_indep_var )
      return below_lower_bound_return;
    else if ( secondary_indep_var_value > max_secondary_indep_var )
      return above_upper_bound_return;
    else if ( secondary_indep_var_value == min_secondary_indep_var )
    {
      return TwoDInterpPolicy::SecondaryBasePolicy::interpolate(
                beta,
                ((*lower_bin_boundary->second).*evaluate)(lower_bin_boundary->second->getLowerBoundOfIndepVar()),
                ((*upper_bin_boundary->second).*evaluate)(upper_bin_boundary->second->getLowerBoundOfIndepVar()) );
    }
    else if ( secondary_indep_var_value == max_secondary_indep_var )
    {
      return TwoDInterpPolicy::SecondaryBasePolicy::interpolate(
                beta,
                ((*lower_bin_boundary->second).*evaluate)(lower_bin_boundary->second->getUpperBoundOfIndepVar()),
                ((*upper_bin_boundary->second).*evaluate)(upper_bin_boundary->second->getUpperBoundOfIndepVar()) );
    }
    else
    {
      // Get the intermediate grid lengths for the indep value and the upper and lower bin boundary
      typename QuantityTraits<SecondaryIndepQuantity>::RawType grid_length_0 =
            TwoDInterpPolicy::SecondaryBasePolicy::calculateUnitBaseGridLength(
                        lower_bin_boundary->second->getLowerBoundOfIndepVar(),
                        lower_bin_boundary->second->getUpperBoundOfIndepVar() );

      typename QuantityTraits<SecondaryIndepQuantity>::RawType grid_length_1 =
            TwoDInterpPolicy::SecondaryBasePolicy::calculateUnitBaseGridLength(
                        upper_bin_boundary->second->getLowerBoundOfIndepVar(),
                        upper_bin_boundary->second->getUpperBoundOfIndepVar() );

      typename QuantityTraits<SecondaryIndepQuantity>::RawType
      intermediate_grid_length =
            TwoDInterpPolicy::SecondaryBasePolicy::calculateUnitBaseGridLength(
                        min_secondary_indep_var,
                        max_secondary_indep_var );

      // Get the lower and upper boundaries of the evaluated cdf
      double lower_cdf_bound, upper_cdf_bound;
      {

        SecondaryIndepQuantity min_secondary_indep_var_with_tol =
            TwoDInterpPolicy::SecondaryBasePolicy::calculateFuzzyLowerBound(
                        min_secondary_indep_var );

        SecondaryIndepQuantity max_secondary_indep_var_with_tol =
            TwoDInterpPolicy::SecondaryBasePolicy::calculateFuzzyUpperBound(
                        max_secondary_indep_var );

        // Calculate the unit base variable on the intermediate grid
        typename QuantityTraits<SecondaryIndepQuantity>::RawType eta =
            TwoDInterpPolicy::SecondaryBasePolicy::calculateUnitBaseIndepVar(
                secondary_indep_var_value,
                min_secondary_indep_var,
                intermediate_grid_length );

        // Get the secondary indep var value for the upper and lower bin boundaries
        SecondaryIndepQuantity secondary_indep_var_value_0 =
            TwoDInterpPolicy::SecondaryBasePolicy::calculateIndepVar(
                        eta,
                        lower_bin_boundary->second->getLowerBoundOfIndepVar(),
                        grid_length_0 );

        SecondaryIndepQuantity secondary_indep_var_value_1 =
            TwoDInterpPolicy::SecondaryBasePolicy::calculateIndepVar(
                        eta,
                        upper_bin_boundary->second->getLowerBoundOfIndepVar(),
                        grid_length_1 );

        // Evaluate the cdf at the upper and lower bin boundaries
        double bin_eval_0 =
          ((*lower_bin_boundary->second).*&BaseOneDDistributionType::evaluateCDF)( secondary_indep_var_value_0 );
        double bin_eval_1 =
          ((*upper_bin_boundary->second).*&BaseOneDDistributionType::evaluateCDF)( secondary_indep_var_value_1 );

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
    SecondaryIndepQuantity lower_bin_sample, upper_bin_sample;
    double rel_error = 1.0;
    SecondaryIndepQuantity error_norm_constant = secondary_indep_var_value;
    double tolerance = d_relative_error_tol;

    /*! \detials If the secondary indep var value is zero the relative error
     *  will always zero or inf. When this is the case the error tolerance will
     *  be used instead of the relative error tolerance.
     */
     if ( secondary_indep_var_value ==
                                QuantityTraits<SecondaryIndepQuantity>::zero() )
     {
        error_norm_constant = QuantityTraits<SecondaryIndepQuantity>::one();
        tolerance = d_error_tol;
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
      typename QuantityTraits<SecondaryIndepQuantity>::RawType
        eta_estimate, eta_0, eta_1;

      eta_0 =
        TwoDInterpPolicy::SecondaryBasePolicy::calculateUnitBaseIndepVar(
            lower_bin_sample,
            lower_bin_boundary->second->getLowerBoundOfIndepVar(),
            grid_length_0 );

      eta_1 =
        TwoDInterpPolicy::SecondaryBasePolicy::calculateUnitBaseIndepVar(
            upper_bin_sample,
            upper_bin_boundary->second->getLowerBoundOfIndepVar(),
            grid_length_1 );

      // Interpolate using the templated TwoDInterpPolicy::PrimaryBasePolicy
      eta_estimate =
        TwoDInterpPolicy::PrimaryBasePolicy::interpolate( beta, eta_0, eta_1 );

      // Scale the sample so that it preserves the intermediate limits.
      SecondaryIndepQuantity est_secondary_indep_var_value =
        TwoDInterpPolicy::SecondaryBasePolicy::calculateIndepVar(
            eta_estimate,
            min_secondary_indep_var,
            intermediate_grid_length );

      // Update the number of iterations
      ++number_of_iterations;

      if ( secondary_indep_var_value == est_secondary_indep_var_value )
        break;

      // Calculate the relative error between the secondary_indep_var_value and the estimate
      rel_error = (secondary_indep_var_value - est_secondary_indep_var_value )/
                                                            error_norm_constant;

      // Make sure the relative error is positive
      rel_error = rel_error < 0 ? -rel_error : rel_error;

      // If tolerance is met exit loop
      if ( rel_error <= tolerance )
        break;

      // Update the estimated_cdf estimate
      if ( est_secondary_indep_var_value < secondary_indep_var_value )
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
            (secondary_indep_var_value - est_secondary_indep_var_value )/
                                QuantityTraits<SecondaryIndepQuantity>::one();
        error = error < 0 ? -error : error;

        // If error meets error tolerance accept estimate
        if ( error < d_error_tol )
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
                       << d_relative_error_tol
                       << ")." );
        }
      }
    }
    // Return the interpolated evaluation
    return TwoDInterpPolicy::PrimaryBasePolicy::interpolate(
                lower_bin_boundary->first,
                upper_bin_boundary->first,
                primary_indep_var_value,
                ((*lower_bin_boundary->second).*evaluate)(lower_bin_sample),
                ((*upper_bin_boundary->second).*evaluate)(upper_bin_sample) );
    }
  }
}

//---------------------------------------------------------------------------//
// SAMPLING METHODS
//---------------------------------------------------------------------------//

// Return a random sample from the secondary conditional PDF
/*! \details A sample is made using a unit based correlated sampling technique.
 */
template<typename TwoDInterpPolicy,
         typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit>
auto UnitAwareInterpolatedFullyTabularTwoDDistribution<TwoDInterpPolicy,PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>::correlatedSampleSecondaryConditionalInBoundaries(
             const PrimaryIndepQuantity primary_indep_var_value,
             const SecondaryIndepQuantity min_secondary_indep_var_value,
             const SecondaryIndepQuantity max_secondary_indep_var_value ) const
  -> SecondaryIndepQuantity
{
  // Make sure the secondary limit is valid
  testPrecondition( max_secondary_indep_var_value >=
                    min_secondary_indep_var_value );

  // Use this random number to do create the correlated sample
  const double random_number =
    Utility::RandomNumberGenerator::getRandomNumber<double>();

  return this->correlatedSampleSecondaryConditionalWithRandomNumberInBoundaries(
                                            primary_indep_var_value,
                                            random_number,
                                            min_secondary_indep_var_value,
                                            max_secondary_indep_var_value );
}

// Return a random sample from the secondary conditional PDF
/*! \details A sample is made using a unit based correlated sampling technique.
 *  The lower and upper conditional boundaries will be use as the min and max
 *  secondary independent variable values.
 */
template<typename TwoDInterpPolicy,
         typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit>
auto UnitAwareInterpolatedFullyTabularTwoDDistribution<TwoDInterpPolicy,PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>::correlatedSampleSecondaryConditional(
             const PrimaryIndepQuantity primary_indep_var_value ) const
  -> SecondaryIndepQuantity
{
  // Get the min and max secondary independent variable values
  SecondaryIndepQuantity min_secondary_indep_var_value =
    this->getLowerBoundOfConditionalIndepVar( primary_indep_var_value );
  SecondaryIndepQuantity max_secondary_indep_var_value =
    this->getUpperBoundOfConditionalIndepVar( primary_indep_var_value );

  return this->correlatedSampleSecondaryConditionalInBoundaries(
                                            primary_indep_var_value,
                                            min_secondary_indep_var_value,
                                            max_secondary_indep_var_value );
}

// Return a random sample from the secondary conditional PDF
/*! \details A sample is made using a correlated sampling technique.
 */
template<typename TwoDInterpPolicy,
         typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit>
auto UnitAwareInterpolatedFullyTabularTwoDDistribution<TwoDInterpPolicy,PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>::sampleSecondaryConditionalExact(
                     const PrimaryIndepQuantity primary_indep_var_value ) const
  -> SecondaryIndepQuantity
{
  // Use this random number to do create the correlated sample
  const double random_number =
    Utility::RandomNumberGenerator::getRandomNumber<double>();

  return this->sampleSecondaryConditionalExactWithRandomNumber(
                                      primary_indep_var_value, random_number );
}

// Return a random sample from the secondary conditional PDF at the CDF val
template<typename TwoDInterpPolicy,
         typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit>
auto UnitAwareInterpolatedFullyTabularTwoDDistribution<TwoDInterpPolicy,PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>::sampleSecondaryConditionalWithRandomNumber(
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

// Return a random correlated sample from the secondary conditional PDF at the CDF val
/*! \details A sample is made using a unit based correlated sampling technique.
 */
template<typename TwoDInterpPolicy,
         typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit>
auto UnitAwareInterpolatedFullyTabularTwoDDistribution<TwoDInterpPolicy,PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>::correlatedSampleSecondaryConditionalWithRandomNumberInBoundaries(
                    const PrimaryIndepQuantity primary_indep_var_value,
                    const double random_number,
                    const SecondaryIndepQuantity min_secondary_indep_var_value,
                    const SecondaryIndepQuantity max_secondary_indep_var_value ) const
  -> SecondaryIndepQuantity
{
  // Make sure the random number is valid
  testPrecondition( random_number >= 0.0 );
  testPrecondition( random_number <= 1.0 );
  // Make sure the secondary limit is valid
  testPrecondition( max_secondary_indep_var_value >= min_secondary_indep_var_value );

  // Create the sampling functor
  std::function<SecondaryIndepQuantity(const BaseOneDDistributionType&)>
    sampling_functor = std::bind<SecondaryIndepQuantity>(
                             &BaseOneDDistributionType::sampleWithRandomNumber,
                             std::placeholders::_1,
                             random_number );

  if ( random_number == 0.0 )
  {
    // Check for a primary value outside of the primary grid limits
    if( primary_indep_var_value < this->getLowerBoundOfPrimaryIndepVar() ||
        primary_indep_var_value > this->getUpperBoundOfPrimaryIndepVar() )
    {
      if( this->arePrimaryLimitsExtended() )
        return min_secondary_indep_var_value;
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
    else
      return min_secondary_indep_var_value;
  }
  else
    return this->correlatedSampleImpl( primary_indep_var_value,
                                       min_secondary_indep_var_value,
                                       max_secondary_indep_var_value,
                                       sampling_functor );
}

// Return a random correlated sample from the secondary conditional PDF at the CDF val
/*! \details A sample is made using a unit based correlated sampling technique.
 *  The lower and upper conditional boundaries will be use as the min and max
 *  secondary independent variable values.
 */
template<typename TwoDInterpPolicy,
         typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit>
auto UnitAwareInterpolatedFullyTabularTwoDDistribution<TwoDInterpPolicy,PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>::correlatedSampleSecondaryConditionalWithRandomNumber(
                    const PrimaryIndepQuantity primary_indep_var_value,
                    const double random_number ) const
  -> SecondaryIndepQuantity
{
  // Make sure the random number is valid
  testPrecondition( random_number >= 0.0 );
  testPrecondition( random_number <= 1.0 );

  // Get the min and max secondary independent variable values
  SecondaryIndepQuantity min_secondary_indep_var_value =
    this->getLowerBoundOfConditionalIndepVar( primary_indep_var_value );
  SecondaryIndepQuantity max_secondary_indep_var_value =
    this->getUpperBoundOfConditionalIndepVar( primary_indep_var_value );

  return this->correlatedSampleSecondaryConditionalWithRandomNumberInBoundaries(
                                    primary_indep_var_value,
                                    random_number,
                                    min_secondary_indep_var_value,
                                    max_secondary_indep_var_value );
}

// Return a random sample from the secondary conditional PDF at the CDF val
/*! \details A sample is made using an exact correlated sampling technique.
 */
template<typename TwoDInterpPolicy,
         typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit>
auto UnitAwareInterpolatedFullyTabularTwoDDistribution<TwoDInterpPolicy,PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>::sampleSecondaryConditionalExactWithRandomNumber(
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

  return this->sampleExactImpl( primary_indep_var_value, sampling_functor );
}

// Return a random sample from the secondary conditional PDF in the subrange
template<typename TwoDInterpPolicy,
         typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit>
auto UnitAwareInterpolatedFullyTabularTwoDDistribution<TwoDInterpPolicy,PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>::sampleSecondaryConditionalInSubrange(
             const PrimaryIndepQuantity primary_indep_var_value,
             const SecondaryIndepQuantity max_secondary_indep_var_value ) const
  -> SecondaryIndepQuantity
{
  // Make sure the max secondary independent variable is above the lower
  // bound of the conditional independent variable
  testPrecondition( max_secondary_indep_var_value >
                    this->getLowerBoundOfConditionalIndepVar( primary_indep_var_value ) );
  
  // Generate a random number
  double random_number =
    Utility::RandomNumberGenerator::getRandomNumber<double>();

  return this->sampleSecondaryConditionalWithRandomNumberInSubrange(
                                               primary_indep_var_value,
                                               random_number,
                                               max_secondary_indep_var_value );
}

// Return a random sample from the secondary conditional PDF in the subrange
/*! \details A sample is made using a unit based correlated sampling technique.
 */
template<typename TwoDInterpPolicy,
         typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit>
auto UnitAwareInterpolatedFullyTabularTwoDDistribution<TwoDInterpPolicy,PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>::correlatedSampleSecondaryConditionalInSubrangeInBoundaries(
             const PrimaryIndepQuantity primary_indep_var_value,
             const SecondaryIndepQuantity min_secondary_indep_var_value,
             const SecondaryIndepQuantity max_secondary_indep_var_value ) const
  -> SecondaryIndepQuantity
{
  // Make sure the secondary limit is valid
  testPrecondition( max_secondary_indep_var_value >
                    this->getLowerBoundOfConditionalIndepVar( primary_indep_var_value ) );

  // Use this random number to do create the correlated sample
  const double random_number =
    Utility::RandomNumberGenerator::getRandomNumber<double>();

  return this->correlatedSampleSecondaryConditionalWithRandomNumberInSubrangeInBoundaries(
                                                primary_indep_var_value,
                                                random_number,
                                                min_secondary_indep_var_value,
                                                max_secondary_indep_var_value );
}

// Return a random sample from the secondary conditional PDF in the subrange
/*! \details A sample is made using a unit based correlated sampling technique.
 *  The lower and upper conditional boundaries will be use as the min and max
 *  secondary independent variable values.
 */
template<typename TwoDInterpPolicy,
         typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit>
auto UnitAwareInterpolatedFullyTabularTwoDDistribution<TwoDInterpPolicy,PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>::correlatedSampleSecondaryConditionalInSubrange(
             const PrimaryIndepQuantity primary_indep_var_value,
             const SecondaryIndepQuantity max_secondary_indep_var_value ) const
  -> SecondaryIndepQuantity
{
  // Make sure the secondary limit is valid
  testPrecondition( max_secondary_indep_var_value >
                    this->getLowerBoundOfConditionalIndepVar( primary_indep_var_value ) );

  // Get the min secondary independent variable value
  SecondaryIndepQuantity min_secondary_indep_var_value =
    this->getLowerBoundOfConditionalIndepVar( primary_indep_var_value );

  return this->correlatedSampleSecondaryConditionalInSubrangeInBoundaries(
                                                primary_indep_var_value,
                                                min_secondary_indep_var_value,
                                                max_secondary_indep_var_value );
}

// Return a random sample from the secondary conditional PDF in the subrange
/*! \details A sample is made using an exact correlated sampling technique.
 */
template<typename TwoDInterpPolicy,
         typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit>
auto UnitAwareInterpolatedFullyTabularTwoDDistribution<TwoDInterpPolicy,PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>::sampleSecondaryConditionalExactInSubrange(
             const PrimaryIndepQuantity primary_indep_var_value,
             const SecondaryIndepQuantity max_secondary_indep_var_value ) const
  -> SecondaryIndepQuantity
{
  // Use this random number to do create the correlated sample
  const double random_number =
    Utility::RandomNumberGenerator::getRandomNumber<double>();

  return this->sampleSecondaryConditionalExactWithRandomNumberInSubrange(
                                               primary_indep_var_value,
                                               random_number,
                                               max_secondary_indep_var_value );
}

// Return a random sample from the secondary conditional PDF in the subrange
template<typename TwoDInterpPolicy,
         typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit>
auto UnitAwareInterpolatedFullyTabularTwoDDistribution<TwoDInterpPolicy,PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>::sampleSecondaryConditionalWithRandomNumberInSubrange(
             const PrimaryIndepQuantity primary_indep_var_value,
             const double random_number,
             const SecondaryIndepQuantity max_secondary_indep_var_value ) const
  -> SecondaryIndepQuantity
{
  // Make sure the max secondary independent variable is above the lower
  // bound of the conditional independent variable
  testPrecondition( max_secondary_indep_var_value >
                    this->getLowerBoundOfConditionalIndepVar( primary_indep_var_value ) );
  // Make sure the random number is valid
  testPrecondition( random_number >= 0.0 );
  testPrecondition( random_number <= 1.0 );

  SecondaryIndepQuantity intermediate_grid_upper_bound =
    this->getUpperBoundOfConditionalIndepVar( primary_indep_var_value );

  // Generate a sample in the subrange
  if( max_secondary_indep_var_value < intermediate_grid_upper_bound )
  {
    // Find the bin boundaries
    typename DistributionType::const_iterator lower_bin_boundary, upper_bin_boundary;

    this->findBinBoundaries( primary_indep_var_value,
                             lower_bin_boundary,
                             upper_bin_boundary );

    typename DistributionType::const_iterator sampled_bin_boundary =
      this->sampleBinBoundary( primary_indep_var_value,
                               lower_bin_boundary,
                               upper_bin_boundary );

    // Calculate the limit on the sampled bin boundary
    typename QuantityTraits<SecondaryIndepQuantity>::RawType grid_length =
      TwoDInterpPolicy::SecondaryBasePolicy::calculateUnitBaseGridLength(
                     sampled_bin_boundary->second->getLowerBoundOfIndepVar(),
                     sampled_bin_boundary->second->getUpperBoundOfIndepVar() );

    SecondaryIndepQuantity intermediate_grid_lower_bound =
    this->getLowerBoundOfConditionalIndepVar( primary_indep_var_value );

    typename QuantityTraits<SecondaryIndepQuantity>::RawType
      intermediate_grid_length =
      TwoDInterpPolicy::SecondaryBasePolicy::calculateUnitBaseGridLength(
                                               intermediate_grid_lower_bound,
                                               intermediate_grid_upper_bound );

    typename QuantityTraits<SecondaryIndepQuantity>::RawType eta =
      TwoDInterpPolicy::SecondaryBasePolicy::calculateUnitBaseIndepVar(
                                                 max_secondary_indep_var_value,
                                                 intermediate_grid_lower_bound,
                                                 intermediate_grid_length );

    SecondaryIndepQuantity max_secondary_indep_var_value_bin_bound =
      TwoDInterpPolicy::SecondaryBasePolicy::calculateIndepVar(
                       eta,
                       sampled_bin_boundary->second->getLowerBoundOfIndepVar(),
                       grid_length );

    // Sample in the bin's subrange
    SecondaryIndepQuantity raw_sample =
      sampled_bin_boundary->second->sampleWithRandomNumberInSubrange(
                                     random_number,
                                     max_secondary_indep_var_value_bin_bound );

    // Scale the sample
    eta = TwoDInterpPolicy::SecondaryBasePolicy::calculateUnitBaseIndepVar(
                       raw_sample,
                       sampled_bin_boundary->second->getLowerBoundOfIndepVar(),
                       grid_length );

    return TwoDInterpPolicy::SecondaryBasePolicy::calculateIndepVar(
                                                 eta,
                                                 intermediate_grid_lower_bound,
                                                 intermediate_grid_length );
  }
  // Generate a sample in the full range
  else
  {
    return this->sampleSecondaryConditionalWithRandomNumber(
                                      primary_indep_var_value, random_number );
  }
}

// Return a random sample from the secondary conditional PDF in the subrange
/*! \details A sample is made using a unit based correlated sampling technique.
 */
template<typename TwoDInterpPolicy,
         typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit>
auto UnitAwareInterpolatedFullyTabularTwoDDistribution<TwoDInterpPolicy,PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>::correlatedSampleSecondaryConditionalWithRandomNumberInSubrangeInBoundaries(
             const PrimaryIndepQuantity primary_indep_var_value,
             const double random_number,
             const SecondaryIndepQuantity min_secondary_indep_var_value,
             const SecondaryIndepQuantity max_secondary_indep_var_value ) const
  -> SecondaryIndepQuantity
{
  // Make sure the random number is valid
  testPrecondition( random_number >= 0.0 );
  testPrecondition( random_number <= 1.0 );

  // Find the bin boundaries
  typename DistributionType::const_iterator lower_bin_boundary, upper_bin_boundary;

  this->findBinBoundaries( primary_indep_var_value,
                           lower_bin_boundary,
                           upper_bin_boundary );

  // Check for a primary value outside of the primary grid limits
  if( lower_bin_boundary == upper_bin_boundary )
  {
    if( this->arePrimaryLimitsExtended() )
    {
      // Get the sample functor and max secondary indep var values for the lower_bin_boundary
      std::function<SecondaryIndepQuantity(const BaseOneDDistributionType&)>
        sample_functor;
      SecondaryIndepQuantity max_secondary_indep_var;

      this->getCorrelatedSampleInSubrangeFunctor( lower_bin_boundary,
                                                  max_secondary_indep_var_value,
                                                  random_number,
                                                  sample_functor,
                                                  max_secondary_indep_var );

      return sample_functor( *lower_bin_boundary->second );
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
  else
  {
    // Get the sample functor and max secondary indep var values for the primary_indep_var_value
    std::function<SecondaryIndepQuantity(const BaseOneDDistributionType&)>
        sample_functor;
    SecondaryIndepQuantity max_secondary_indep_var;

    // Check if the max_secondary_indep_var_value is greater than the max secondary indep value at the primary_indep_var_value
    if( max_secondary_indep_var_value >
           this->getUpperBoundOfConditionalIndepVar( primary_indep_var_value ) )
    {
      max_secondary_indep_var =
            this->getUpperBoundOfConditionalIndepVar( primary_indep_var_value );

      // Create the sampling functor
      sample_functor = std::bind<SecondaryIndepQuantity>(
                            &BaseOneDDistributionType::sampleWithRandomNumber,
                            std::placeholders::_1,
                            random_number );
    }
    else
    {
      max_secondary_indep_var = max_secondary_indep_var_value;

      // Create the sampling functor
      sample_functor = std::bind<SecondaryIndepQuantity>(
                &BaseOneDDistributionType::sampleWithRandomNumberInSubrange,
                std::placeholders::_1,
                random_number,
                max_secondary_indep_var );
    }

    // Check for a primary value at the primary grid upper limit
    if( primary_indep_var_value == upper_bin_boundary->first )
      return sample_functor( *upper_bin_boundary->second );
    else if( primary_indep_var_value == lower_bin_boundary->first )
      return sample_functor( *lower_bin_boundary->second );
    else
    {
      typename QuantityTraits<SecondaryIndepQuantity>::RawType
      intermediate_grid_length =
        TwoDInterpPolicy::SecondaryBasePolicy::calculateUnitBaseGridLength(
                    min_secondary_indep_var_value, max_secondary_indep_var );

      // Calculate the unit base variable on the intermediate grid corresponding to the
      // raw samples on the lower and upper boundaries
      typename QuantityTraits<SecondaryIndepQuantity>::RawType eta, eta_0, eta_1;

      {
        // Get the sample functor and max secondary indep var values for the upper_bin_boundary
        std::function<SecondaryIndepQuantity(const BaseOneDDistributionType&)>
          sample_functor_0;
        SecondaryIndepQuantity max_secondary_indep_var_0;

        this->getCorrelatedSampleInSubrangeFunctor(
                                                lower_bin_boundary,
                                                max_secondary_indep_var_value,
                                                random_number,
                                                sample_functor_0,
                                                max_secondary_indep_var_0 );

        // Calculate the unit base variable on the lower grid corresponding to the
        // lower raw sample
        typename QuantityTraits<SecondaryIndepQuantity>::RawType grid_length_0 =
          TwoDInterpPolicy::SecondaryBasePolicy::calculateUnitBaseGridLength(
                      lower_bin_boundary->second->getLowerBoundOfIndepVar(),
                      max_secondary_indep_var_0 );

        eta_0 = TwoDInterpPolicy::ZYInterpPolicy::calculateUnitBaseIndepVar(
                        sample_functor_0( *lower_bin_boundary->second ),
                        lower_bin_boundary->second->getLowerBoundOfIndepVar(),
                        grid_length_0 );


        // Get the sample functor and max secondary indep var values for the upper_bin_boundary
        std::function<SecondaryIndepQuantity(const BaseOneDDistributionType&)>
          sample_functor_1;
        SecondaryIndepQuantity max_secondary_indep_var_1;

        this->getCorrelatedSampleInSubrangeFunctor(
                                                lower_bin_boundary,
                                                max_secondary_indep_var_value,
                                                random_number,
                                                sample_functor_1,
                                                max_secondary_indep_var_1 );

        // Calculate the unit base variable on the upper grid corresponding to the
        // upper raw sample
        typename QuantityTraits<SecondaryIndepQuantity>::RawType grid_length_1 =
          TwoDInterpPolicy::SecondaryBasePolicy::calculateUnitBaseGridLength(
                      upper_bin_boundary->second->getLowerBoundOfIndepVar(),
                      max_secondary_indep_var_1 );

        eta_1 = TwoDInterpPolicy::ZYInterpPolicy::calculateUnitBaseIndepVar(
                        sample_functor_1( *upper_bin_boundary->second ),
                        upper_bin_boundary->second->getLowerBoundOfIndepVar(),
                        grid_length_1 );

        // Interpolate between the lower and upper unit based variables
        eta = TwoDInterpPolicy::ZXInterpPolicy::interpolate(
                                                   lower_bin_boundary->first,
                                                   upper_bin_boundary->first,
                                                   primary_indep_var_value,
                                                   eta_0,
                                                   eta_1 );
      }

      // Scale the sample so that it preserves the intermediate limits.
      return TwoDInterpPolicy::SecondaryBasePolicy::calculateIndepVar(
                eta, min_secondary_indep_var_value, intermediate_grid_length );
    }
  }
}

// Return a random sample from the secondary conditional PDF in the subrange
/*! \details A sample is made using a unit based correlated sampling technique.
 *  The lower and upper conditional boundaries will be use as the min and max
 *  secondary independent variable values.
 */
template<typename TwoDInterpPolicy,
         typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit>
auto UnitAwareInterpolatedFullyTabularTwoDDistribution<TwoDInterpPolicy,PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>::correlatedSampleSecondaryConditionalWithRandomNumberInSubrange(
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
                    this->getLowerBoundOfConditionalIndepVar( primary_indep_var_value ) );

  // Get the min secondary independent variable value
  SecondaryIndepQuantity min_secondary_indep_var_value =
    this->getLowerBoundOfConditionalIndepVar( primary_indep_var_value );

  return this->correlatedSampleSecondaryConditionalWithRandomNumberInSubrangeInBoundaries(
                                        primary_indep_var_value,
                                        random_number,
                                        min_secondary_indep_var_value,
                                        max_secondary_indep_var_value );
}

// Return a random sample from the secondary conditional PDF in the subrange
/*! \details A sample is made using a correlated sampling technique.
 */
template<typename TwoDInterpPolicy,
         typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit>
auto UnitAwareInterpolatedFullyTabularTwoDDistribution<TwoDInterpPolicy,PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>::sampleSecondaryConditionalExactWithRandomNumberInSubrange(
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
                    this->getLowerBoundOfConditionalIndepVar( primary_indep_var_value ) );

  std::function<SecondaryIndepQuantity(const BaseOneDDistributionType&)>
      sampling_functor;

  // Check if the max_secondary_indep_var_value is greater than the max indep value at the energy
  if ( max_secondary_indep_var_value >
       this->getUpperBoundOfConditionalIndepVar( primary_indep_var_value ) )
  {
    // Create the sampling functor
    sampling_functor = std::bind<SecondaryIndepQuantity>(
                             &BaseOneDDistributionType::sampleWithRandomNumberInSubrange,
                             std::placeholders::_1,
                             random_number,
                             this->getUpperBoundOfConditionalIndepVar( primary_indep_var_value ) );
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

  return this->sampleExactImpl( primary_indep_var_value, sampling_functor );
}

// Return a random sample from the secondary conditional PDF and the index
/*! \details The primary_bin_index stores the index of the bin boundary that
 * was used to generate the sample.
 */
template<typename TwoDInterpPolicy,
         typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit>
auto UnitAwareInterpolatedFullyTabularTwoDDistribution<TwoDInterpPolicy,PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>::sampleSecondaryConditionalAndRecordBinIndices(
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
         typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit>
auto UnitAwareInterpolatedFullyTabularTwoDDistribution<TwoDInterpPolicy,PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>::sampleSecondaryConditionalAndRecordBinIndices(
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

// Correlated sample from the distribution using the desired sampling functor
template<typename TwoDInterpPolicy,
         typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit>
template<typename SampleFunctor>
inline auto UnitAwareInterpolatedFullyTabularTwoDDistribution<TwoDInterpPolicy,PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>::correlatedSampleImpl(
                const PrimaryIndepQuantity primary_indep_var_value,
                const SecondaryIndepQuantity min_secondary_indep_var,
                const SecondaryIndepQuantity max_secondary_indep_var,
                SampleFunctor sample_functor ) const
  -> SecondaryIndepQuantity
{
  // Make sure the secondary limit is valid
  testPrecondition( max_secondary_indep_var >= min_secondary_indep_var );

  // Find the bin boundaries
  typename DistributionType::const_iterator lower_bin_boundary, upper_bin_boundary;

  this->findBinBoundaries( primary_indep_var_value,
                           lower_bin_boundary,
                           upper_bin_boundary );

  // Check for a primary value outside of the primary grid limits
  if( lower_bin_boundary == upper_bin_boundary )
  {
    if( this->arePrimaryLimitsExtended() )
      return sample_functor( *lower_bin_boundary->second );
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
  else
  {
    // Check for a primary value at the primary grid upper limit
    if( primary_indep_var_value == upper_bin_boundary->first )
      return sample_functor( *upper_bin_boundary->second );
    else if( primary_indep_var_value == lower_bin_boundary->first )
      return sample_functor( *lower_bin_boundary->second );
    else
    {
      // Check to see if the min equals the max
      if( min_secondary_indep_var == max_secondary_indep_var )
        return min_secondary_indep_var;

      typename QuantityTraits<SecondaryIndepQuantity>::RawType
      intermediate_grid_length =
        TwoDInterpPolicy::SecondaryBasePolicy::calculateUnitBaseGridLength(
                            min_secondary_indep_var, max_secondary_indep_var );

      // Calculate the unit base variable on the intermediate grid corresponding to the
      // raw samples on the lower and upper boundaries
      typename QuantityTraits<SecondaryIndepQuantity>::RawType eta, eta_0, eta_1;

      {
        // Calculate the unit base variable on the lower grid corresponding to the
        // lower raw sample
        typename QuantityTraits<SecondaryIndepQuantity>::RawType grid_length_0 =
          TwoDInterpPolicy::SecondaryBasePolicy::calculateUnitBaseGridLength(
                      lower_bin_boundary->second->getLowerBoundOfIndepVar(),
                      lower_bin_boundary->second->getUpperBoundOfIndepVar());

        eta_0 = TwoDInterpPolicy::SecondaryBasePolicy::calculateUnitBaseIndepVar(
                        sample_functor( *lower_bin_boundary->second ),
                        lower_bin_boundary->second->getLowerBoundOfIndepVar(),
                        grid_length_0 );

        // Calculate the unit base variable on the upper grid corresponding to the
        // upper raw sample
        typename QuantityTraits<SecondaryIndepQuantity>::RawType grid_length_1 =
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
                                                   primary_indep_var_value,
                                                   eta_0,
                                                   eta_1 );
      }

      // Scale the sample so that it preserves the intermediate limits.
      return TwoDInterpPolicy::SecondaryBasePolicy::calculateIndepVar(
                    eta, min_secondary_indep_var, intermediate_grid_length );
    }
  }
}

// Sample from the distribution using the desired sampling functor
template<typename TwoDInterpPolicy,
         typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit>
template<typename SampleFunctor>
inline auto UnitAwareInterpolatedFullyTabularTwoDDistribution<TwoDInterpPolicy,PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>::sampleExactImpl(
                            const PrimaryIndepQuantity primary_indep_var_value,
                            SampleFunctor sample_functor ) const
  -> SecondaryIndepQuantity
{
  // Find the bin boundaries
  typename DistributionType::const_iterator lower_bin_boundary, upper_bin_boundary;

  this->findBinBoundaries( primary_indep_var_value,
                           lower_bin_boundary,
                           upper_bin_boundary );

  // Check for a primary value outside of the primary grid limits
  if( lower_bin_boundary == upper_bin_boundary )
  {
    if( this->arePrimaryLimitsExtended() )
      return sample_functor( *lower_bin_boundary->second );
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
  else
  {
    // Check for a primary value at the primary grid upper limit
    if( primary_indep_var_value == upper_bin_boundary->first )
      return sample_functor( *upper_bin_boundary->second );
    else if( primary_indep_var_value == lower_bin_boundary->first )
      return sample_functor( *lower_bin_boundary->second );
    else
    {
      return TwoDInterpPolicy::ZXInterpPolicy::interpolate(
                           lower_bin_boundary->first,
                           upper_bin_boundary->first,
                           primary_indep_var_value,
                           sample_functor( *lower_bin_boundary->second ),
                           sample_functor( *upper_bin_boundary->second ) );
    }
  }
}

// Return the correlated sampling functor for the desired bin boundary
template<typename TwoDInterpPolicy,
         typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit>
template<typename SampleFunctor>
inline void UnitAwareInterpolatedFullyTabularTwoDDistribution<TwoDInterpPolicy,PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>::getCorrelatedSampleInSubrangeFunctor(
                    typename DistributionType::const_iterator bin_boundary,
                    const SecondaryIndepQuantity max_secondary_indep_var_value,
                    const double random_number,
                    SampleFunctor& sample_functor,
                    SecondaryIndepQuantity& bin_boundary_max_value ) const
{
  // Check if the max_secondary_indep_var_value is greater than the max secondary indep value at the bin_boundary
  if ( max_secondary_indep_var_value >
                        bin_boundary->second->getUpperBoundOfIndepVar() )
  {
    bin_boundary_max_value = bin_boundary->second->getUpperBoundOfIndepVar();

    // Create the sampling functor
    sample_functor = std::bind<SecondaryIndepQuantity>(
                             &BaseOneDDistributionType::sampleWithRandomNumber,
                             std::placeholders::_1,
                             random_number );
  }
  else
  {
    bin_boundary_max_value = max_secondary_indep_var_value;

    // Create the sampling functor
    sample_functor = std::bind<SecondaryIndepQuantity>(
             &BaseOneDDistributionType::sampleWithRandomNumberInSubrange,
             std::placeholders::_1,
             random_number,
             bin_boundary_max_value );
  }
}


} // end Utility namespace

#endif // UTILITY_INTERPOLATED_FULLY_TABULAR_TWO_D_DISTRIBUTION_DEF_HPP

//---------------------------------------------------------------------------//
// end Utility_InterpolatedFullyTabularTwoDDistribution_def.hpp
//---------------------------------------------------------------------------//
