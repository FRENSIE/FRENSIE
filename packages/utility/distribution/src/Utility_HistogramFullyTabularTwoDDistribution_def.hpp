//---------------------------------------------------------------------------//
//!
//! \file   Utility_HistogramFullyTabularTwoDDistribution.hpp
//! \author Alex Robinson
//! \brief  The histogram fully tabular two-dimensional dist. class definition
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_HISTOGRAM_FULLY_TABULAR_TWO_D_DISTRIBUTION_DEF_HPP
#define UTILITY_HISTOGRAM_FULLY_TABULAR_TWO_D_DISTRIBUTION_DEF_HPP

// FRENSIE Includes
#include "Utility_TabularDistribution.hpp"
#include "Utility_SortAlgorithms.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_ContractException.hpp"

namespace Utility{

// Evaluate the secondary conditional CDF
template<typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit>
double UnitAwareHistogramFullyTabularTwoDDistribution<PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>::evaluateSecondaryConditionalCDF(
                 const PrimaryIndepQuantity primary_indep_var_value,
                 const SecondaryIndepQuantity secondary_indep_var_value ) const
{
  return this->template evaluateImpl<double>(
                                      primary_indep_var_value,
                                      secondary_indep_var_value,
                                      &BaseOneDDistributionType::evaluateCDF );
}

// Return a random sample from the secondary conditional PDF and the index
template<typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit>
auto UnitAwareHistogramFullyTabularTwoDDistribution<PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>::sampleSecondaryConditionalAndRecordBinIndex(
                const PrimaryIndepQuantity primary_indep_var_value,
                unsigned& primary_bin_index,
                unsigned& secondary_bin_index ) const -> SecondaryIndepQuantity
{
  // Create the sampling functor
  std::function<SecondaryIndepQuantity(const BaseOneDDistributionType&)>
    sampling_functor = std::bind<SecondaryIndepQuantity>(
                            &BaseOneDDistributionType::sampleAndRecordBinIndex,
                            std::placeholders::_1,
                            std::ref( secondary_bin_index ) );

  return this->sampleDetailedImpl( primary_indep_var_value,
                                   sampling_functor,
                                   primary_bin_index );
}

// Return a random sample from the secondary conditional PDF at the CDF val
template<typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit>
auto UnitAwareHistogramFullyTabularTwoDDistribution<PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>::sampleSecondaryConditionalWithRandomNumber(
                   const PrimaryIndepQuantity primary_indep_var_value,
                   const double random_number ) const -> SecondaryIndepQuantity
{
  // Make sure the random number is valid
  testPrecondition( random_number >= 0.0 );
  testPrecondition( random_number <= 1.0 );

  // Create the sampling functor
  std::function<SecondaryIndepQuantity(const BaseOneDDistribution&)>
    sampling_functor = std::bind<SecondaryIndepQuantity>(
                             &BaseOneDDistributionType::sampleWithRandomNumber,
                             std::placeholders::_1,
                             random_number );

  return this->sampleImpl( primary_indep_var_value, sampling_functor );
}

// Return a random sample from the secondary conditional PDF in the subrange
template<typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit>
auto UnitAwareHistogramFullyTabularTwoDDistribution<PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>::sampleSecondaryConditionalInSubrange(
             const PrimaryIndepQuantity primary_indep_var_value,
             const SecondaryIndepQuantity max_secondary_indep_var_value ) const
  -> SecondaryIndepQuantity
{
  // Make sure the max secondary independent variable is above the lower
  // bound of the conditional independent variable
  testPrecondition( max_secondary_indep_var_value >
                    this->getLowerBoundOfConditionalIndepVar( primary_indep_var_value ) );

  // Create the sampling functor
  std::function<SecondaryIndepQuantity(const BaseOneDDistribution&)>
    sampling_functor = std::bind<SecondaryIndepQuantity>(
                                   &BaseOneDDistributionType::sampleInSubrange,
                                   std::placeholders::_1,
                                   max_secondary_indep_var_value );
                                                         

  return this->sampleImpl( primary_indep_var_value, sampling_functor );
}

// Return a random sample from the secondary conditional PDF in the subrange
template<typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit>
auto UnitAwareHistogramFullyTabularTwoDDistribution<PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>::sampleSecondaryConditionalWithRandomNumberInSubrange(
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

  // Create the sampling functor
  std::function<SecondaryIndepQuantity(const BaseOneDDistribution&)>
    sampling_functor = std::bind<SecondaryIndepQuantity>(
                   &BaseOneDDistributionType::sampleWithRandomNumberInSubrange,
                   std::placeholders::_1,
                   random_number,
                   max_secondary_indep_var_value );

  return this->sampleImpl( primary_indep_var_value, sampling_functor );
}
  
} // end Utility namespace

#endif // end UTILITY_HISTOGRAM_FULLY_TABULAR_TWO_D_DISTRIBUTION_DEF_HPP

//---------------------------------------------------------------------------//
// end Utility_HistogramFullyTabularTwoDDistribution_def.hpp
//---------------------------------------------------------------------------//
