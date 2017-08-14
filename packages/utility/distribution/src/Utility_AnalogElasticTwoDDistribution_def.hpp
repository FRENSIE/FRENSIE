//---------------------------------------------------------------------------//
//!
//! \file   Utility_AnalogElasticTwoDDistribution_def.hpp
//! \author Luke Kersting
//! \brief  The interpolated fully tabular two-dimensional dist. class def.
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_ANALOG_ELASTIC_TWO_D_DISTRIBUTION_DEF_HPP
#define UTILITY_ANALOG_ELASTIC_TWO_D_DISTRIBUTION_DEF_HPP

// FRENSIE Includes
#include "Utility_TabularDistribution.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_SortAlgorithms.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_ContractException.hpp"

namespace Utility{

////---------------------------------------------------------------------------//
//// EVALUATING METHODS
////---------------------------------------------------------------------------//

// Evaluate the distribution using unit based interpolation
template<typename TwoDInterpPolicy,
         typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit>
auto UnitAwareAnalogElasticTwoDDistribution<TwoDInterpPolicy,PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>::evaluate(
                const PrimaryIndepQuantity primary_indep_var_value,
                const SecondaryIndepQuantity secondary_indep_var_value ) const
  -> DepQuantity
{
  return this->template evaluateImpl<TwoDInterpPolicy,DepQuantity>(
                                          primary_indep_var_value,
                                          secondary_indep_var_value,
                                          &BaseOneDDistributionType::evaluate );
}

// Correlated evaluate the distribution (unit based)
/*! \details This method performs a type of binary search using sampling to
 *  estimate the CDF to a relative error tolerance to find the interpolation.
 * The lower and upper bounds of the secondary independent variable
 *  (cosine) are fixed (-1 <= cosine <= 1). Therefore a unit based method is not
 *  necessary and an exact method is used to evaluate instead.
 */
template<typename TwoDInterpPolicy,
         typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit>
auto UnitAwareAnalogElasticTwoDDistribution<TwoDInterpPolicy,PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>::correlatedEvaluateInBoundaries(
                const PrimaryIndepQuantity primary_indep_var_value,
                const SecondaryIndepQuantity secondary_indep_var_value,
                const SecondaryIndepQuantity min_secondary_indep_var,
                const SecondaryIndepQuantity max_secondary_indep_var ) const
  -> DepQuantity
{
  return this->template evaluateExactImpl<TwoDInterpPolicy,DepQuantity>(
                                          primary_indep_var_value,
                                          secondary_indep_var_value,
                                          &BaseOneDDistributionType::evaluate );
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
auto UnitAwareAnalogElasticTwoDDistribution<TwoDInterpPolicy,PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>::evaluateExact(
                 const PrimaryIndepQuantity primary_indep_var_value,
                 const SecondaryIndepQuantity secondary_indep_var_value ) const
  -> DepQuantity
{
  return this->template evaluateExactImpl<TwoDInterpPolicy,DepQuantity>(
                                          primary_indep_var_value,
                                          secondary_indep_var_value,
                                          &BaseOneDDistributionType::evaluate );
}

// Evaluate the secondary conditional PDF using unit based interpolation
template<typename TwoDInterpPolicy,
         typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit>
auto UnitAwareAnalogElasticTwoDDistribution<TwoDInterpPolicy,PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>::evaluateSecondaryConditionalPDF(
                 const PrimaryIndepQuantity primary_indep_var_value,
                 const SecondaryIndepQuantity secondary_indep_var_value ) const
  -> InverseSecondaryIndepQuantity
{
  return this->template evaluateImpl<TwoDInterpPolicy,InverseSecondaryIndepQuantity>(
                                      primary_indep_var_value,
                                      secondary_indep_var_value,
                                      &BaseOneDDistributionType::evaluatePDF );
}

// Correlated evaluate the secondary conditional PDF
/*! \details This method performs a type of binary search using sampling to
 *  estimate the CDF to a relative error tolerance to find the interpolation.
 * The lower and upper bounds of the secondary independent variable
 *  (cosine) are fixed (-1 <= cosine <= 1). Therefore a unit based method is not
 *  necessary and an exact method is used to evaluate instead.
 */
template<typename TwoDInterpPolicy,
         typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit>
auto UnitAwareAnalogElasticTwoDDistribution<TwoDInterpPolicy,PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>::correlatedEvaluateSecondaryConditionalPDFInBoundaries(
                const PrimaryIndepQuantity primary_indep_var_value,
                const SecondaryIndepQuantity secondary_indep_var_value,
                const SecondaryIndepQuantity min_secondary_indep_var,
                const SecondaryIndepQuantity max_secondary_indep_var ) const
  ->  InverseSecondaryIndepQuantity
{
  return this->template evaluateExactImpl<TwoDInterpPolicy,InverseSecondaryIndepQuantity>(
                                    primary_indep_var_value,
                                    secondary_indep_var_value,
                                    &BaseOneDDistributionType::evaluatePDF );
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
auto UnitAwareAnalogElasticTwoDDistribution<TwoDInterpPolicy,PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>::evaluateSecondaryConditionalPDFExact(
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
double UnitAwareAnalogElasticTwoDDistribution<TwoDInterpPolicy,PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>::evaluateSecondaryConditionalCDF(
                 const PrimaryIndepQuantity primary_indep_var_value,
                 const SecondaryIndepQuantity secondary_indep_var_value ) const
{
  return this->template evaluateImpl<CDFInterpPolicy,double>(
                                      primary_indep_var_value,
                                      secondary_indep_var_value,
                                      &BaseOneDDistributionType::evaluateCDF );
}

// Correlated evaluate the secondary conditional CDF
/*! \details This method performs a type of binary search using sampling to
 *  estimate the CDF to a relative error tolerance.
 * The lower and upper bounds of the secondary independent variable
 *  (cosine) are fixed (-1 <= cosine <= 1). Therefore a unit based method is not
 *  necessary and an exact method is used to evaluate instead.
 */
template<typename TwoDInterpPolicy,
         typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit>
double UnitAwareAnalogElasticTwoDDistribution<TwoDInterpPolicy,PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>::correlatedEvaluateSecondaryConditionalCDFInBoundaries(
                const PrimaryIndepQuantity primary_indep_var_value,
                const SecondaryIndepQuantity secondary_indep_var_value,
                const SecondaryIndepQuantity min_secondary_indep_var,
                const SecondaryIndepQuantity max_secondary_indep_var ) const
{
  return this->template evaluateExactImpl<TwoDInterpPolicy,double>(
                                      primary_indep_var_value,
                                      secondary_indep_var_value,
                                      &BaseOneDDistributionType::evaluateCDF );
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
double UnitAwareAnalogElasticTwoDDistribution<TwoDInterpPolicy,PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>::evaluateSecondaryConditionalCDFExact(
                 const PrimaryIndepQuantity primary_indep_var_value,
                 const SecondaryIndepQuantity secondary_indep_var_value ) const
{
  return this->template evaluateExactImpl<CDFInterpPolicy,double>(
                                      primary_indep_var_value,
                                      secondary_indep_var_value,
                                      &BaseOneDDistributionType::evaluateCDF );
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
inline ReturnType UnitAwareAnalogElasticTwoDDistribution<TwoDInterpPolicy,PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>::evaluateExactImpl(
                        const PrimaryIndepQuantity incoming_energy,
                        const SecondaryIndepQuantity angle_cosine,
                        EvaluationMethod evaluate,
                        unsigned max_number_of_iterations ) const
{
  // Make sure the angle cosine is valid
  testPrecondition( angle_cosine >= d_lower_bound_conditional_indep_var );
  testPrecondition( angle_cosine <= d_upper_bound_conditional_indep_var );

  // Find the bin boundaries
  typename DistributionType::const_iterator lower_bin_boundary, upper_bin_boundary;

  this->findBinBoundaries( incoming_energy,
                           lower_bin_boundary,
                           upper_bin_boundary );

  // Check for a primary value outside of the primary grid limits
  if( lower_bin_boundary == upper_bin_boundary )
  {
    if( this->arePrimaryLimitsExtended() )
      return ((*lower_bin_boundary->second).*evaluate)(angle_cosine);
    else 
      return QuantityTraits<ReturnType>::zero();
  }
  else if( lower_bin_boundary->first == incoming_energy )
  {
    return ((*lower_bin_boundary->second).*evaluate)(angle_cosine);
  }
  else if( upper_bin_boundary->first == incoming_energy )
  {
    return ((*upper_bin_boundary->second).*evaluate)(angle_cosine);
  }
  else if ( angle_cosine == d_lower_bound_conditional_indep_var )
  {
    ReturnType min_eval_0 =
      ((*lower_bin_boundary->second).*evaluate)(d_lower_bound_conditional_indep_var);
    ReturnType min_eval_1 =
      ((*upper_bin_boundary->second).*evaluate)(d_lower_bound_conditional_indep_var);

    if ( min_eval_0 == min_eval_1 )
      return min_eval_0;
    else
    {
      return TwoDInterpPolicy::ZXInterpPolicy::interpolate(
                lower_bin_boundary->first,
                upper_bin_boundary->first,
                incoming_energy,
                min_eval_0,
                min_eval_1 );
    }
  }
  else if ( angle_cosine == d_upper_bound_conditional_indep_var )
  {
    return TwoDInterpPolicy::ZXInterpPolicy::interpolate(
                lower_bin_boundary->first,
                upper_bin_boundary->first,
                incoming_energy,
                ((*lower_bin_boundary->second).*evaluate)(d_upper_bound_conditional_indep_var),
                ((*upper_bin_boundary->second).*evaluate)(d_upper_bound_conditional_indep_var) );
  }
  else
  {
    // Get the lower and upper boundaries of the evaluated cdf
    double lower_cdf_bound, upper_cdf_bound;
    {
      // Evaluate the cdf at the upper and lower bin boundaries
      double bin_eval_0 =
        ((*lower_bin_boundary->second).*&BaseOneDDistributionType::evaluateCDF)( angle_cosine );
      double bin_eval_1 =
        ((*upper_bin_boundary->second).*&BaseOneDDistributionType::evaluateCDF)( angle_cosine );

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
    SecondaryIndepQuantity error_norm_constant = angle_cosine;
    double tolerance = d_relative_error_tol;

    /*! \detials If the secondary indep var value is zero the relative error
     *  will always zero or inf. When this is the case the error tolerance will
     *  be used instead of the relative error tolerance.
     */
    if ( angle_cosine == SIQT::zero() )
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
      SecondaryIndepQuantity est_angle_cosine =
       CosineProcessor::processCosineVar(
         TwoDInterpPolicy::ZXInterpPolicy::interpolate(
            lower_bin_boundary->first,
            upper_bin_boundary->first,
            incoming_energy,
            CosineProcessor::processCosineVar( lower_bin_sample ),
            CosineProcessor::processCosineVar( upper_bin_sample ) ) );

      if ( angle_cosine == est_angle_cosine )
      {
        break;
      }

      // Calculate the relative error between the angle_cosine and the estimate
      rel_error = (angle_cosine - est_angle_cosine )/error_norm_constant;

      // Make sure the relative error is positive
      rel_error = rel_error < 0 ? -rel_error : rel_error;

      // Update the number of iterations
      ++number_of_iterations;

      // If tolerance is met exit loop
      if ( rel_error <= tolerance )
      {
        break;
      }

      // Update the estimated_cdf estimate
      if ( est_angle_cosine < angle_cosine )
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
            (angle_cosine - est_angle_cosine )/SIQT::one();
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
                           << tolerance
                           << ")."
                           << "or the error ("
                           << error
                           << ") reached the error tolerance ("
                           << d_error_tol
                           << ")." );
        }
      }
    }

    // Return the interpolated evaluation
    return TwoDInterpPolicy::ZXInterpPolicy::interpolate(
              lower_bin_boundary->first,
              upper_bin_boundary->first,
              incoming_energy,
              ((*lower_bin_boundary->second).*evaluate)(lower_bin_sample),
              ((*upper_bin_boundary->second).*evaluate)(upper_bin_sample) );
  }
}

// Evaluate the distribution using the desired evaluation method
template<typename TwoDInterpPolicy,
         typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit>
template<typename LocalTwoDInterpPolicy,
         typename ReturnType,
         typename EvaluationMethod>
inline ReturnType UnitAwareAnalogElasticTwoDDistribution<TwoDInterpPolicy,PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>::evaluateImpl(
                        const PrimaryIndepQuantity primary_indep_var_value,
                        const SecondaryIndepQuantity angle_cosine,
                        EvaluationMethod evaluate ) const
{
  // Make sure the angle cosine is valid
  testPrecondition( angle_cosine >= d_lower_bound_conditional_indep_var );
  testPrecondition( angle_cosine <= d_upper_bound_conditional_indep_var );

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
      return ((*lower_bin_boundary->second).*evaluate)(angle_cosine);
    }
    else 
      return QuantityTraits<ReturnType>::zero();
  }
  else
  {
    // Get the evaluation at the lower and upper bin boundaries
    ReturnType min_eval_0 = ((*lower_bin_boundary->second).*evaluate)(angle_cosine);
    ReturnType min_eval_1 = ((*upper_bin_boundary->second).*evaluate)(angle_cosine);

    if ( min_eval_0 == min_eval_1 )
      return min_eval_0;
    else
    {
      // Return the interpolated evaluation
      return TwoDInterpPolicy::ZXInterpPolicy::interpolate(
              lower_bin_boundary->first,
              upper_bin_boundary->first,
              primary_indep_var_value,
              min_eval_0,
              min_eval_1 );
    }
  }
}

////---------------------------------------------------------------------------//
//// SAMPLING METHODS
////---------------------------------------------------------------------------//

// Return a random sample from the secondary conditional PDF
/*! \details A stochastic sampling procedure is used. If the primary value
 * provided is outside of the primary grid limits the appropriate limiting
 * secondary distribution will be used to create the sample. The alternative
 * to this behavior is to throw an exception unless the distribution has 
 * been extended by calling the extendBeyondPrimaryIndepLimits method. Since
 * this is a performance critical method we decided against this behavior.
 */
template<typename TwoDInterpPolicy,
         typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit>
auto UnitAwareAnalogElasticTwoDDistribution<TwoDInterpPolicy,PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>::sampleSecondaryConditional(
                     const PrimaryIndepQuantity primary_indep_var_value ) const
  -> SecondaryIndepQuantity
{
  // Create the sampling functor
  std::function<SecondaryIndepQuantity(const BaseOneDDistributionType&)>
    sampling_functor = std::bind<SecondaryIndepQuantity>(
                                             &BaseOneDDistributionType::sample,
                                             std::placeholders::_1 );

  return this->sampleImpl( primary_indep_var_value, sampling_functor );
}

// Return a random sample and record the number of trials
/*! \details A stochastic sampling procedure is used. If the primary value
 * provided is outside of the primary grid limits the appropriate limiting
 * secondary distribution will be used to create the sample. The alternative
 * to this behavior is to throw an exception unless the distribution has 
 * been extended by calling the extendBeyondPrimaryIndepLimits method. Since
 * this is a performance critical method we decided against this behavior.
 */
template<typename TwoDInterpPolicy,
         typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit>
auto UnitAwareAnalogElasticTwoDDistribution<TwoDInterpPolicy,PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>::sampleSecondaryConditionalAndRecordTrials(
                            const PrimaryIndepQuantity primary_indep_var_value,
                            unsigned& trials ) const
  -> SecondaryIndepQuantity
{
  // Create the sampling functor
  std::function<SecondaryIndepQuantity(const BaseOneDDistributionType&)>
    sampling_functor = std::bind<SecondaryIndepQuantity>(
                              &BaseOneDDistributionType::sampleAndRecordTrials,
                              std::placeholders::_1,
                              std::ref( trials ) );

  return this->sampleImpl( primary_indep_var_value, sampling_functor );
}

// Return a random sample from the secondary conditional PDF and the index
/*! \details The primary_bin_index stores the index of the bin boundary that
 * was used to generate the sample.
 */
template<typename TwoDInterpPolicy,
         typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit>
auto UnitAwareAnalogElasticTwoDDistribution<TwoDInterpPolicy,PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>::sampleSecondaryConditionalAndRecordBinIndices(
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
auto UnitAwareAnalogElasticTwoDDistribution<TwoDInterpPolicy,PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>::sampleSecondaryConditionalAndRecordBinIndices(
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

// Return a random sample from the secondary conditional PDF at the CDF val
template<typename TwoDInterpPolicy,
         typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit>
auto UnitAwareAnalogElasticTwoDDistribution<TwoDInterpPolicy,PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>::sampleSecondaryConditionalWithRandomNumber(
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

// Return a random sample from the secondary conditional PDF at the CDF val
/*! \details A sample is made using an exact correlated sampling technique.
 */
template<typename TwoDInterpPolicy,
         typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit>
auto UnitAwareAnalogElasticTwoDDistribution<TwoDInterpPolicy,PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>::sampleSecondaryConditionalExactWithRandomNumber(
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
auto UnitAwareAnalogElasticTwoDDistribution<TwoDInterpPolicy,PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>::sampleSecondaryConditionalWithRandomNumberInSubrange(
             const PrimaryIndepQuantity primary_indep_var_value,
             const double random_number,
             const SecondaryIndepQuantity max_secondary_indep_var_value ) const
  -> SecondaryIndepQuantity
{
  // Make sure the max secondary independent variable is above the lower
  // bound of the conditional independent variable
  testPrecondition( max_secondary_indep_var_value >
                    d_lower_bound_conditional_indep_var );
  // Make sure the random number is valid
  testPrecondition( random_number >= 0.0 );
  testPrecondition( random_number <= 1.0 );

  // Generate a sample in the subrange
  if( max_secondary_indep_var_value < d_upper_bound_conditional_indep_var )
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

    // Sample in the bin's subrange
    return sampled_bin_boundary->second->sampleWithRandomNumberInSubrange(
                                     random_number,
                                     max_secondary_indep_var_value );
  }
  // Generate a sample in the full range
  else
  {
    return this->sampleSecondaryConditionalWithRandomNumber(
                                      primary_indep_var_value, random_number );
  }
}


// Return a random sample from the secondary conditional PDF in the subrange
/*! \details A sample is made using an exact correlated sampling technique.
 */
template<typename TwoDInterpPolicy,
         typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit>
auto UnitAwareAnalogElasticTwoDDistribution<TwoDInterpPolicy,PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>::sampleSecondaryConditionalExactWithRandomNumberInSubrange(
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

// Return a random correlated sample from the secondary conditional PDF at the CDF val
/*! \details The lower and upper bounds of the secondary independent variable
 *  (cosine) are fixed (-1 <= cosine <= 1). Therefore a unit based method is not
 *  necessary and an exact method is used to sample instead.
 */
template<typename TwoDInterpPolicy,
         typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit>
auto UnitAwareAnalogElasticTwoDDistribution<TwoDInterpPolicy,PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>::correlatedSampleSecondaryConditionalWithRandomNumberInBoundaries(
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
  testPrecondition( max_secondary_indep_var_value >
                    this->getLowerBoundOfConditionalIndepVar( primary_indep_var_value ) );
  
  // Create the sampling functor
  std::function<SecondaryIndepQuantity(const BaseOneDDistributionType&)>
    sampling_functor = std::bind<SecondaryIndepQuantity>(
                             &BaseOneDDistributionType::sampleWithRandomNumber,
                             std::placeholders::_1,
                             random_number );

  return this->sampleExactImpl( primary_indep_var_value,
                                     sampling_functor );
}

// Return a random sample from the secondary conditional PDF in the subrange
/*! \details The lower and upper bounds of the secondary independent variable
 *  (cosine) are fixed (-1 <= cosine <= 1). Therefore a unit based method is not
 *  necessary and an exact method is used to sample instead.
 */
template<typename TwoDInterpPolicy,
         typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit>
auto UnitAwareAnalogElasticTwoDDistribution<TwoDInterpPolicy,PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>::correlatedSampleSecondaryConditionalWithRandomNumberInSubrangeInBoundaries(
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
  testPrecondition( max_secondary_indep_var_value >
                    this->getLowerBoundOfConditionalIndepVar( primary_indep_var_value ) );


  return this->sampleSecondaryConditionalExactWithRandomNumberInSubrange(
             primary_indep_var_value,
             random_number,
             max_secondary_indep_var_value );
}

// Sample from the distribution using the desired sampling functor
template<typename TwoDInterpPolicy,
         typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit>
template<typename SampleFunctor>
inline auto UnitAwareAnalogElasticTwoDDistribution<TwoDInterpPolicy,PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>::sampleImpl(
                            const PrimaryIndepQuantity primary_indep_var_value,
                            SampleFunctor sample_functor ) const
  -> SecondaryIndepQuantity
{
  // Dummy variables
  SecondaryIndepQuantity dummy_raw_sample;
  unsigned dummy_primary_bin_index;

  return this->sampleDetailedImpl( primary_indep_var_value,
                                   sample_functor,
                                   dummy_raw_sample,
                                   dummy_primary_bin_index );
}

// Sample from the distribution using the desired sampling functor
template<typename TwoDInterpPolicy,
         typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit>
template<typename SampleFunctor>
inline auto UnitAwareAnalogElasticTwoDDistribution<TwoDInterpPolicy,PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>::sampleDetailedImpl(
                            const PrimaryIndepQuantity primary_indep_var_value,
                            SampleFunctor sample_functor,
                            SecondaryIndepQuantity& raw_sample,
                            unsigned& primary_bin_index ) const
  -> SecondaryIndepQuantity
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

  // Calculate the index of the primary bin boundary that will be used to
  // create the secondary conditional sample
  primary_bin_index = this->calculateBinIndex( sampled_bin_boundary );

  // Create the raw sample
  raw_sample = sample_functor( *sampled_bin_boundary->second );

  // Return the raw sample
  return raw_sample;
}

// Sample from the distribution using the desired sampling functor
template<typename TwoDInterpPolicy,
         typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit>
template<typename SampleFunctor>
inline auto UnitAwareAnalogElasticTwoDDistribution<TwoDInterpPolicy,PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>::sampleExactImpl(
                            const PrimaryIndepQuantity incoming_energy,
                            SampleFunctor sample_functor ) const
  -> SecondaryIndepQuantity
{
  // Find the bin boundaries
  typename DistributionType::const_iterator lower_bin_boundary, upper_bin_boundary;

  this->findBinBoundaries( incoming_energy,
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
                       << incoming_energy << " not in ["
                       << this->getLowerBoundOfPrimaryIndepVar() << ","
                       << this->getUpperBoundOfPrimaryIndepVar() << "])!" );
    }
  }
  else
  {
    // Check for a primary value at the primary grid upper limit
    if( incoming_energy == upper_bin_boundary->first )
      return sample_functor( *upper_bin_boundary->second );
    else if( incoming_energy == lower_bin_boundary->first )
      return sample_functor( *lower_bin_boundary->second );
    else
    {
      SecondaryIndepQuantity sampled_value_0 =
        sample_functor( *lower_bin_boundary->second );
      SecondaryIndepQuantity sampled_value_1 =
        sample_functor( *upper_bin_boundary->second );

      if ( sampled_value_0 == sampled_value_1 )
        return sampled_value_0;
      else
      {
        return CosineProcessor::processCosineVar(
                 TwoDInterpPolicy::ZXInterpPolicy::interpolate(
                   lower_bin_boundary->first,
                   upper_bin_boundary->first,
                   incoming_energy,
                   CosineProcessor::processCosineVar( sampled_value_0 ),
                   CosineProcessor::processCosineVar( sampled_value_1 ) ) );
      }
    }
  }
}

////---------------------------------------------------------------------------//
//// MISC. FUNCTIONS
////---------------------------------------------------------------------------//

// Return the lower bound of the conditional distribution
template<typename TwoDInterpPolicy,
         typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit>
auto UnitAwareAnalogElasticTwoDDistribution<TwoDInterpPolicy,PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>::getLowerBoundOfConditionalIndepVar(
                     const PrimaryIndepQuantity primary_indep_var_value ) const
  -> SecondaryIndepQuantity
{
  // Check for a primary value outside of the primary grid limits
  if( primary_indep_var_value < this->getLowerBoundOfPrimaryIndepVar() ||
      primary_indep_var_value > this->getUpperBoundOfPrimaryIndepVar() )
  {
    if( this->arePrimaryLimitsExtended() )
      return -1.0*SIQT::one();
    else
      return SIQT::zero();
  }
  else
    return -1.0*SIQT::one();
}

// Return the cutoff bound of the conditional distribution
template<typename TwoDInterpPolicy,
         typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit>
auto UnitAwareAnalogElasticTwoDDistribution<TwoDInterpPolicy,PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>::getCutoffBoundOfConditionalIndepVar(
                     const PrimaryIndepQuantity primary_indep_var_value ) const
  -> SecondaryIndepQuantity
{
  // Check for a primary value outside of the primary grid limits
  if( primary_indep_var_value < this->getLowerBoundOfPrimaryIndepVar() ||
      primary_indep_var_value > this->getUpperBoundOfPrimaryIndepVar() )
  {
    if( this->arePrimaryLimitsExtended() )
      return -0.999999*SIQT::one();
    else
      return SIQT::zero();
  }
  else
    return 0.999999*SIQT::one();
}

// Return the upper bound of the conditional distribution
template<typename TwoDInterpPolicy,
         typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit>
auto UnitAwareAnalogElasticTwoDDistribution<TwoDInterpPolicy,PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>::getUpperBoundOfConditionalIndepVar(
                     const PrimaryIndepQuantity primary_indep_var_value ) const
  -> SecondaryIndepQuantity
{
  // Check for a primary value outside of the primary grid limits
  if( primary_indep_var_value < this->getLowerBoundOfPrimaryIndepVar() ||
      primary_indep_var_value > this->getUpperBoundOfPrimaryIndepVar() )
  {
    if( this->arePrimaryLimitsExtended() )
      return SIQT::one();
    else
      return SIQT::zero();
  }
  else
    return SIQT::one();
}

} // end Utility namespace

#endif // UTILITY_ANALOG_ELASTIC_TWO_D_DISTRIBUTION_DEF_HPP

//---------------------------------------------------------------------------//
// end Utility_AnalogElasticTwoDDistribution_def.hpp
//---------------------------------------------------------------------------//
