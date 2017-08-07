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

  //! Constructor
template<typename TwoDInterpPolicy,
         typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit>
UnitAwareAnalogElasticTwoDDistribution<TwoDInterpPolicy,PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>::UnitAwareAnalogElasticTwoDDistribution(
                            const DistributionType& distribution,
                            const double fuzzy_boundary_tol,
                            const double evaluate_relative_error_tol,
                            const double evaluate_error_tol )
    : ParentType( distribution,
                  fuzzy_boundary_tol,
                  evaluate_relative_error_tol,
                  evaluate_error_tol ),
      d_relative_error_tol( evaluate_relative_error_tol ),
      d_error_tol( evaluate_error_tol ),
      d_upper_bound_conditional_indep_var( 1.0*SIQT::one() ),
      d_lower_bound_conditional_indep_var( -1.0*SIQT::one() ),
      d_upper_bound_processed_indep_var(),
      d_lower_bound_processed_indep_var(),
      d_grid_length()
{
  // Calculate the unit based grid length
  this->calculateUnitBaseGridLength();
}

  //! Constructor
template<typename TwoDInterpPolicy,
         typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit>
template<template<typename T, typename... Args> class ArrayA,
         template<typename T, typename... Args> class ArrayB>
UnitAwareAnalogElasticTwoDDistribution<TwoDInterpPolicy,PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>::UnitAwareAnalogElasticTwoDDistribution(
                   const ArrayA<PrimaryIndepQuantity>& primary_indep_grid,
                   const ArrayB<std::shared_ptr<const UnitAwareTabularOneDDistribution<SecondaryIndependentUnit,DependentUnit> > >& secondary_distributions,
                   const double fuzzy_boundary_tol,
                   const double evaluate_relative_error_tol,
                   const double evaluate_error_tol )
    : ParentType( primary_indep_grid,
                  secondary_distributions,
                  fuzzy_boundary_tol,
                  evaluate_relative_error_tol,
                  evaluate_error_tol ),
      d_relative_error_tol( evaluate_relative_error_tol ),
      d_error_tol( evaluate_error_tol ),
      d_upper_bound_conditional_indep_var( 1.0*SIQT::one() ),
      d_lower_bound_conditional_indep_var( -1.0*SIQT::one() ),
      d_upper_bound_processed_indep_var(),
      d_lower_bound_processed_indep_var(),
      d_grid_length()
{
  // Calculate the unit based grid length
  this->calculateUnitBaseGridLength();
}


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
/*! \details This method performs a type of binary search using a unit based
 *  correlated sampling to estimate the CDF to a relative error tolerance in
 *  order to find the proper interpolation. The result is consistent with the
 *  correlatedSampleSecondaryConditional methods.
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
/*! \details This method performs a type of binary search using a unit based
 *  correlated sampling to estimate the CDF to a relative error tolerance in
 *  order to find the proper interpolation. The result is consistent with the
 *  correlatedSampleSecondaryConditional methods.
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
/*! \details This method performs a type of binary search using a unit based
 *  correlated sampling to estimate the CDF to a relative error tolerance. The
 *  result is consistent with the correlatedSampleSecondaryConditional methods.
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
/*! \details A sample is made using a correlated sampling technique.
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
/*! \details A sample is made using a unit based correlated sampling technique.
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



////---------------------------------------------------------------------------//
//// EVALUATING METHODS
////---------------------------------------------------------------------------//

//// Correlated evaluate the distribution (unit based)
///*! \details This method performs a type of binary search using a unit based
// *  correlated sampling to estimate the CDF to a relative error tolerance in
// *  order to find the proper interpolation. The result is consistent with the
// *  correlatedSampleSecondaryConditional methods.
// */
//template<typename TwoDInterpPolicy,
//         typename PrimaryIndependentUnit,
//         typename SecondaryIndependentUnit,
//         typename DependentUnit>
//auto UnitAwareAnalogElasticTwoDDistribution<TwoDInterpPolicy,PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>::correlatedEvaluateInBoundaries(
//                const PrimaryIndepQuantity incoming_energy,
//                const SecondaryIndepQuantity angle_cosine,
//                const SecondaryIndepQuantity min_secondary_indep_var,
//                const SecondaryIndepQuantity max_secondary_indep_var ) const
//  -> DepQuantity
//{
//  return this->template correlatedEvaluateImpl<TwoDInterpPolicy,DepQuantity>(
//                                          incoming_energy,
//                                          angle_cosine,
//                                          min_secondary_indep_var,
//                                          max_secondary_indep_var,
//                                          &BaseOneDDistributionType::evaluate );
//}

//// Correlated evaluate the distribution (unit based)
///*! \details This method performs a type of binary search using a unit based
// *  correlated sampling to estimate the CDF to a relative error tolerance in
// *  order to find the proper interpolation. The result is consistent with the
// *  correlatedSampleSecondaryConditional methods.
// *  The lower and upper conditional boundaries will be use as the min and max
// *  secondary independent variable values.
// */
//template<typename TwoDInterpPolicy,
//         typename PrimaryIndependentUnit,
//         typename SecondaryIndependentUnit,
//         typename DependentUnit>
//auto UnitAwareAnalogElasticTwoDDistribution<TwoDInterpPolicy,PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>::correlatedEvaluate(
//                const PrimaryIndepQuantity incoming_energy,
//                const SecondaryIndepQuantity angle_cosine ) const
//  -> DepQuantity
//{
//  return this->correlatedEvaluateInBoundaries( incoming_energy,
//                                               angle_cosine );
//}

//// Evaluate the distribution
///*! \details This method performs a type of binary search using a unit based
// *  correlated sampling to estimate the CDF to a relative error tolerance in
// *  order to find the proper interpolation. The result is consistent with the
// *  sampleSecondaryConditionalExact methods.
// */
//template<typename TwoDInterpPolicy,
//         typename PrimaryIndependentUnit,
//         typename SecondaryIndependentUnit,
//         typename DependentUnit>
//auto UnitAwareAnalogElasticTwoDDistribution<TwoDInterpPolicy,PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>::evaluateExact(
//                 const PrimaryIndepQuantity incoming_energy,
//                 const SecondaryIndepQuantity angle_cosine ) const
//  -> DepQuantity
//{
//  return this->template evaluateExactImpl<TwoDInterpPolicy,DepQuantity>(
//                                          incoming_energy,
//                                          angle_cosine,
//                                          &BaseOneDDistributionType::evaluate );
//}

//// Correlated evaluate the secondary conditional PDF
///*! \details This method performs a type of binary search using a unit based
// *  correlated sampling to estimate the CDF to a relative error tolerance in
// *  order to find the proper interpolation. The result is consistent with the
// *  correlatedSampleSecondaryConditional methods.
// */
//template<typename TwoDInterpPolicy,
//         typename PrimaryIndependentUnit,
//         typename SecondaryIndependentUnit,
//         typename DependentUnit>
//auto UnitAwareAnalogElasticTwoDDistribution<TwoDInterpPolicy,PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>::correlatedEvaluateSecondaryConditionalPDFInBoundaries(
//                const PrimaryIndepQuantity incoming_energy,
//                const SecondaryIndepQuantity angle_cosine,
//                const SecondaryIndepQuantity min_secondary_indep_var,
//                const SecondaryIndepQuantity max_secondary_indep_var ) const
//  ->  InverseSecondaryIndepQuantity
//{
//  return this->template correlatedEvaluateImpl<TwoDInterpPolicy,InverseSecondaryIndepQuantity>(
//                                    incoming_energy,
//                                    angle_cosine,
//                                    min_secondary_indep_var,
//                                    max_secondary_indep_var,
//                                    &BaseOneDDistributionType::evaluatePDF );
//}

//// Correlated evaluate the secondary conditional PDF
///*! \details This method performs a type of binary search using a unit based
// *  correlated sampling to estimate the CDF to a relative error tolerance in
// *  order to find the proper interpolation. The result is consistent with the
// *  correlatedSampleSecondaryConditional methods.
// *  The lower and upper conditional boundaries will be use as the min and max
// *  secondary independent variable values.
// */
//template<typename TwoDInterpPolicy,
//         typename PrimaryIndependentUnit,
//         typename SecondaryIndependentUnit,
//         typename DependentUnit>
//auto UnitAwareAnalogElasticTwoDDistribution<TwoDInterpPolicy,PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>::correlatedEvaluateSecondaryConditionalPDF(
//                const PrimaryIndepQuantity incoming_energy,
//                const SecondaryIndepQuantity angle_cosine ) const
//  ->  InverseSecondaryIndepQuantity
//{
//  return this->correlatedEvaluateSecondaryConditionalPDFInBoundaries(
//                                                    incoming_energy,
//                                                    angle_cosine );
//}

//// Evaluate the secondary conditional PDF
///*! \details This method performs a type of binary search using a unit based
// *  correlated sampling to estimate the CDF to a relative error tolerance in
// *  order to find the proper interpolation. The result is consistent with the
// *  sampleSecondaryConditionalExact methods.
// */
//template<typename TwoDInterpPolicy,
//         typename PrimaryIndependentUnit,
//         typename SecondaryIndependentUnit,
//         typename DependentUnit>
//auto UnitAwareAnalogElasticTwoDDistribution<TwoDInterpPolicy,PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>::evaluateSecondaryConditionalPDFExact(
//                 const PrimaryIndepQuantity incoming_energy,
//                 const SecondaryIndepQuantity angle_cosine ) const
//  -> InverseSecondaryIndepQuantity
//{
//  return this->template evaluateExactImpl<TwoDInterpPolicy,InverseSecondaryIndepQuantity>(
//                                      incoming_energy,
//                                      angle_cosine,
//                                      &BaseOneDDistributionType::evaluatePDF );
//}

//// Evaluate the secondary conditional CDF
//template<typename TwoDInterpPolicy,
//         typename PrimaryIndependentUnit,
//         typename SecondaryIndependentUnit,
//         typename DependentUnit>
//double UnitAwareAnalogElasticTwoDDistribution<TwoDInterpPolicy,PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>::evaluateSecondaryConditionalCDF(
//                 const PrimaryIndepQuantity incoming_energy,
//                 const SecondaryIndepQuantity angle_cosine ) const
//{
//  return this->template evaluateImpl<CDFInterpPolicy,double>(
//                                      incoming_energy,
//                                      angle_cosine,
//                                      &BaseOneDDistributionType::evaluateCDF,
//                                      0.0,
//                                      1.0 );
//}

//// Correlated evaluate the secondary conditional CDF
///*! \details This method performs a type of binary search using a unit based
// *  correlated sampling to estimate the CDF to a relative error tolerance. The
// *  result is consistent with the correlatedSampleSecondaryConditional methods.
// */
//template<typename TwoDInterpPolicy,
//         typename PrimaryIndependentUnit,
//         typename SecondaryIndependentUnit,
//         typename DependentUnit>
//double UnitAwareAnalogElasticTwoDDistribution<TwoDInterpPolicy,PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>::correlatedEvaluateSecondaryConditionalCDFInBoundaries(
//                const PrimaryIndepQuantity incoming_energy,
//                const SecondaryIndepQuantity angle_cosine,
//                const SecondaryIndepQuantity min_secondary_indep_var,
//                const SecondaryIndepQuantity max_secondary_indep_var ) const
//{
//  return this->template correlatedEvaluateImpl<TwoDInterpPolicy,double>(
//                                      incoming_energy,
//                                      angle_cosine,
//                                      min_secondary_indep_var,
//                                      max_secondary_indep_var,
//                                      &BaseOneDDistributionType::evaluateCDF,
//                                      0.0,
//                                      1.0 );
//}

//// Correlated evaluate the secondary conditional CDF
///*! \details This method performs a type of binary search using a unit based
// *  correlated sampling to estimate the CDF to a relative error tolerance. The
// *  result is consistent with the correlatedSampleSecondaryConditional methods.
// *  The lower and upper conditional boundaries will be use as the min and max
// *  secondary independent variable values.
// */
//template<typename TwoDInterpPolicy,
//         typename PrimaryIndependentUnit,
//         typename SecondaryIndependentUnit,
//         typename DependentUnit>
//double UnitAwareAnalogElasticTwoDDistribution<TwoDInterpPolicy,PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>::correlatedEvaluateSecondaryConditionalCDF(
//                const PrimaryIndepQuantity incoming_energy,
//                const SecondaryIndepQuantity angle_cosine ) const
//{
//  return this->correlatedEvaluateSecondaryConditionalCDFInBoundaries(
//                                                    incoming_energy,
//                                                    angle_cosine );
//}

//// Evaluate the secondary conditional CDF
///*! \details This method performs a type of binary search using a unit based
// *  correlated sampling to estimate the CDF to a relative error tolerance.
// *  The result is consistent with the sampleSecondaryConditionalExact methods.
// */
//template<typename TwoDInterpPolicy,
//         typename PrimaryIndependentUnit,
//         typename SecondaryIndependentUnit,
//         typename DependentUnit>
//double UnitAwareAnalogElasticTwoDDistribution<TwoDInterpPolicy,PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>::evaluateSecondaryConditionalCDFExact(
//                 const PrimaryIndepQuantity incoming_energy,
//                 const SecondaryIndepQuantity angle_cosine ) const
//{
//  return this->template evaluateExactImpl<CDFInterpPolicy,double>(
//                                      incoming_energy,
//                                      angle_cosine,
//                                      &BaseOneDDistributionType::evaluateCDF,
//                                      0.0,
//                                      1.0 );
//}

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
    if ( angle_cosine == QuantityTraits<SecondaryIndepQuantity>::zero() )
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
        break;

      // Calculate the relative error between the angle_cosine and the estimate
      rel_error = (angle_cosine - est_angle_cosine )/error_norm_constant;

      // Make sure the relative error is positive
      rel_error = rel_error < 0 ? -rel_error : rel_error;

      // Update the number of iterations
      ++number_of_iterations;

      // If tolerance is met exit loop
      if ( rel_error <= tolerance )
        break;

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
            (angle_cosine - est_angle_cosine )/
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
    // Return the interpolated evaluation
    return TwoDInterpPolicy::ZXInterpPolicy::interpolate(
              lower_bin_boundary->first,
              upper_bin_boundary->first,
              primary_indep_var_value,
              ((*lower_bin_boundary->second).*evaluate)(angle_cosine),
              ((*upper_bin_boundary->second).*evaluate)(angle_cosine) );
  }
}

////---------------------------------------------------------------------------//
//// SAMPLING METHODS
////---------------------------------------------------------------------------//

//// Return a random sample from the secondary conditional PDF
///*! \details A sample is made using a unit based correlated sampling technique.
// */
//template<typename TwoDInterpPolicy,
//         typename PrimaryIndependentUnit,
//         typename SecondaryIndependentUnit,
//         typename DependentUnit>
//auto UnitAwareAnalogElasticTwoDDistribution<TwoDInterpPolicy,PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>::correlatedSampleSecondaryConditionalInCutoff(
//             const PrimaryIndepQuantity incoming_energy ) const
//  -> SecondaryIndepQuantity
//{
//  // Make sure the secondary limit is valid
//  testPrecondition( max_angle_cosine > d_lower_bound_conditional_indep_var );

//  // Use this random number to do create the correlated sample
//  const double random_number =
//    Utility::RandomNumberGenerator::getRandomNumber<double>();

//  return this->correlatedSampleSecondaryConditionalWithRandomNumberInBoundaries(
//                                            incoming_energy,
//                                            random_number );
//}

//// Return a random sample from the secondary conditional PDF
///*! \details A sample is made using a unit based correlated sampling technique.
// *  The lower and upper conditional boundaries will be use as the min and max
// *  secondary independent variable values.
// */
//template<typename TwoDInterpPolicy,
//         typename PrimaryIndependentUnit,
//         typename SecondaryIndependentUnit,
//         typename DependentUnit>
//auto UnitAwareAnalogElasticTwoDDistribution<TwoDInterpPolicy,PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>::correlatedSampleSecondaryConditional(
//             const PrimaryIndepQuantity incoming_energy ) const
//  -> SecondaryIndepQuantity
//{
//  return this->correlatedSampleSecondaryConditionalInBoundaries(
//                                            incoming_energy );
//}

//// Return a random sample from the secondary conditional PDF
///*! \details A sample is made using a correlated sampling technique.
// */
//template<typename TwoDInterpPolicy,
//         typename PrimaryIndependentUnit,
//         typename SecondaryIndependentUnit,
//         typename DependentUnit>
//auto UnitAwareAnalogElasticTwoDDistribution<TwoDInterpPolicy,PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>::sampleSecondaryConditionalExact(
//                     const PrimaryIndepQuantity incoming_energy ) const
//  -> SecondaryIndepQuantity
//{
//  // Use this random number to do create the correlated sample
//  const double random_number =
//    Utility::RandomNumberGenerator::getRandomNumber<double>();

//  return this->sampleSecondaryConditionalExactWithRandomNumber(
//                                      incoming_energy, random_number );
//}

//// Return a random sample from the secondary conditional PDF at the CDF val
//template<typename TwoDInterpPolicy,
//         typename PrimaryIndependentUnit,
//         typename SecondaryIndependentUnit,
//         typename DependentUnit>
//auto UnitAwareAnalogElasticTwoDDistribution<TwoDInterpPolicy,PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>::sampleSecondaryConditionalWithRandomNumber(
//                            const PrimaryIndepQuantity incoming_energy,
//                            const double random_number ) const
//  -> SecondaryIndepQuantity
//{
//  // Make sure the random number is valid
//  testPrecondition( random_number >= 0.0 );
//  testPrecondition( random_number <= 1.0 );
//  
//  // Create the sampling functor
//  std::function<SecondaryIndepQuantity(const BaseOneDDistributionType&)>
//    sampling_functor = std::bind<SecondaryIndepQuantity>(
//                             &BaseOneDDistributionType::sampleWithRandomNumber,
//                             std::placeholders::_1,
//                             random_number );

//  return this->sampleImpl( incoming_energy, sampling_functor );
//}

//// Return a random correlated sample from the secondary conditional PDF at the CDF val
///*! \details A sample is made using a unit based correlated sampling technique.
// *  The lower and upper conditional boundaries will be use as the min and max
// *  secondary independent variable values.
// */
//template<typename TwoDInterpPolicy,
//         typename PrimaryIndependentUnit,
//         typename SecondaryIndependentUnit,
//         typename DependentUnit>
//auto UnitAwareAnalogElasticTwoDDistribution<TwoDInterpPolicy,PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>::correlatedSampleSecondaryConditionalWithRandomNumber(
//                    const PrimaryIndepQuantity incoming_energy,
//                    const double random_number ) const
//  -> SecondaryIndepQuantity
//{
//  // Make sure the random number is valid
//  testPrecondition( random_number >= 0.0 );
//  testPrecondition( random_number <= 1.0 );

//  // Create the sampling functor
//  std::function<SecondaryIndepQuantity(const BaseOneDDistributionType&)>
//    sampling_functor = std::bind<SecondaryIndepQuantity>(
//                             &BaseOneDDistributionType::sampleWithRandomNumber,
//                             std::placeholders::_1,
//                             random_number );

//  return this->correlatedSampleImpl(
//            incoming_energy,
//            d_lower_bound_conditional_indep_var,
//            d_upper_bound_conditional_indep_var,
//            sampling_functor );
//}

//// Return a random sample from the secondary conditional PDF at the CDF val
///*! \details A sample is made using an exact correlated sampling technique.
// */
//template<typename TwoDInterpPolicy,
//         typename PrimaryIndependentUnit,
//         typename SecondaryIndependentUnit,
//         typename DependentUnit>
//auto UnitAwareAnalogElasticTwoDDistribution<TwoDInterpPolicy,PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>::sampleSecondaryConditionalExactWithRandomNumber(
//                            const PrimaryIndepQuantity incoming_energy,
//                            const double random_number ) const
//  -> SecondaryIndepQuantity
//{
//  // Make sure the random number is valid
//  testPrecondition( random_number >= 0.0 );
//  testPrecondition( random_number <= 1.0 );
//  
//  // Create the sampling functor
//  std::function<SecondaryIndepQuantity(const BaseOneDDistributionType&)>
//    sampling_functor = std::bind<SecondaryIndepQuantity>(
//                             &BaseOneDDistributionType::sampleWithRandomNumber,
//                             std::placeholders::_1,
//                             random_number );

//  return this->sampleExactImpl( incoming_energy, sampling_functor );
//}

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

// Calculate the unit based grid length
template<typename TwoDInterpPolicy,
         typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit>
void UnitAwareAnalogElasticTwoDDistribution<TwoDInterpPolicy,PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>::calculateUnitBaseGridLength()
{
  // Process the lower and upper bounds of the conditional indep var
  SecondaryIndepQuantity processed_min =
    CosineProcessor::processCosineVar( d_lower_bound_conditional_indep_var );

  SecondaryIndepQuantity processed_max =
    CosineProcessor::processCosineVar( d_upper_bound_conditional_indep_var );

  // Find the lower and upper bounds of the processed conditional indep var
  if( processed_min < processed_max )
  {
    d_lower_bound_processed_indep_var = processed_min;
    d_upper_bound_processed_indep_var = processed_max;
  }
  else
  {
    d_lower_bound_processed_indep_var = 1e-6*SIQT::one();//processed_max;
    d_upper_bound_processed_indep_var = 2.0*SIQT::one();//processed_min;
  }

  // Calculate and set the grid length
  d_grid_length =
    TwoDInterpPolicy::SecondaryBasePolicy::calculateUnitBaseGridLength(
                        d_lower_bound_processed_indep_var,
                        d_upper_bound_processed_indep_var );
}

} // end Utility namespace

#endif // UTILITY_ANALOG_ELASTIC_TWO_D_DISTRIBUTION_DEF_HPP

//---------------------------------------------------------------------------//
// end Utility_AnalogElasticTwoDDistribution_def.hpp
//---------------------------------------------------------------------------//
