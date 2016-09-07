//---------------------------------------------------------------------------//
//!
//! \file   Utility_HistogramTabularTwoDDistributionHelpers_def.hpp
//! \author Alex Robinson
//! \brief  The histogram tabular two-dimensional dist. helper class def.
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_HISTOGRAM_TABULAR_TWO_D_DISTRIBUTION_HELPERS_DEF_HPP
#define UTILITY_HISTOGRAM_TABULAR_TWO_D_DISTRIBUTION_HELPERS_DEF_HPP

// FRENSIE Includes
#include "Utility_ContractException.hpp"

namespace Utility{

// Evaluate the distribution
template<typename Distribution>
auto UnitAwareHistogramTabularTwoDDistributionImplBase<Distribution>::evaluate(
  const PrimaryIndepQuantity primary_indep_var_value,
  const SecondaryIndepQuantity secondary_indep_var_value ) const -> DepQuantity
{
  return this->evaluateImpl<DepQuantity>( primary_indep_var_value,
                                          secondary_indep_var_value,
                                          &BaseOneDDistributionType::evaluate);
}

// Evaluate the secondary conditional PDF
template<typename Distribution>
auto UnitAwareHistogramTabularTwoDDistributionImplBase<Distribution>::evaluateSecondaryConditionalPDF(
                 const PrimaryIndepQuantity primary_indep_var_value,
                 const SecondaryIndepQuantity secondary_indep_var_value ) const
  -> InverseSecondaryIndepQuantity
{
  return this->evaluateImpl<InverseSecondaryIndepQuantity>(
                                      primary_indep_var_value,
                                      secondary_indep_var_value,
                                      &BaseOneDDistributionType::evaluatePDF );
}

// Evaluate the distribution using the desired evaluation method
template<typename Distribution>
template<typename ReturnType, typename EvaluationMethod>
inline ReturnType UnitAwareHistogramTabularTwoDDistributionImplBase<Distribution>::evaluateImpl(
                        const PrimaryIndepQuantity primary_indep_var_value,
                        const SecondaryIndepQuantity secondary_indep_var_value,
                        EvaluationMethod evaluate ) const
{
  typename DistributionType::const_iterator lower_bin_boundary, upper_bin_boundary;
  
  this->findBinBoundaries( primary_indep_var_value,
                           lower_bin_boundary,
                           upper_bin_boundary );

  // Check for a primary value outside of the primary grid limits
  if( lower_bin_boundary == upper_bin_boundary )
  {
    if( this->arePrimaryLimitsExtended() )
      return ((*lower_bin_boundary->second).*evaluate)( secondary_indep_var_value );
    else
      return QuantityTraits<ReturnType>::zero();
  }
  else
    return ((*lower_bin_boundary->second).*evaluate)( secondary_indep_var_value );
}

// Return a random sample from the secondary conditional PDF
template<typename Distribution>
auto UnitAwareHistogramTabularTwoDDistributionImplBase<Distribution>::sampleSecondaryConditional(
                     const PrimaryIndepQuantity primary_indep_var_value ) const
  -> SecondaryIndepQuantity
{
  typename DistributionType::const_iterator lower_bin_boundary, upper_bin_boundary;
  
  this->findBinBoundaries( primary_indep_var_value,
                           lower_bin_boundary,
                           upper_bin_boundary );

  return lower_bin_boundary->second->sample();
}

// Return a random sample and record the number of trials
template<typename Distribution>
auto UnitAwareHistogramTabularTwoDDistributionImplBase<Distribution>::sampleSecondaryConditionalAndRecordTrials(
                            const PrimaryIndepQuantity primary_indep_var_value,
                            unsigned& trials ) const -> SecondaryIndepQuantity
{
  typename DistributionType::const_iterator lower_bin_boundary, upper_bin_boundary;
  
  this->findBinBoundaries( primary_indep_var_value,
                           lower_bin_boundary,
                           upper_bin_boundary );

  return lower_bin_boundary->second->sampleAndRecordTrials( trials );
}

// Return the upper bound of the conditional distribution
template<typename Distribution>
auto UnitAwareHistogramTabularTwoDDistributionImplBase<Distribution>::getUpperBoundOfConditionalIndepVar(
                     const PrimaryIndepQuantity primary_indep_var_value ) const
  -> SecondaryIndepQuantity
{
  typename DistributionType::const_iterator lower_bin_boundary, upper_bin_boundary;
  
  this->findBinBoundaries( primary_indep_var_value,
                           lower_bin_boundary,
                           upper_bin_boundary );

  return lower_bin_boundary->second->getUpperBoundOfIndepVar();
}

// Return the lower bound of the conditional distribution
template<typename Distribution>
auto UnitAwareHistogramTabularTwoDDistributionImplBase<Distribution>::getLowerBoundOfConditionalIndepVar(
                     const PrimaryIndepQuantity primary_indep_var_value ) const
  -> SecondaryIndepQuantity
{
  typename DistributionType::const_iterator lower_bin_boundary, upper_bin_boundary;
  
  this->findBinBoundaries( primary_indep_var_value,
                           lower_bin_boundary,
                           upper_bin_boundary );

  return lower_bin_boundary->second->getLowerBoundOfIndepVar();
}

// Test if the distribution is continuous in the primary dimension
template<typename Distribution>
bool UnitAwareHistogramTabularTwoDDistributionImplBase<Distribution>::isPrimaryDimensionContinuous() const
{
  return true;
}

// Evaluate the secondary conditional CDF
template<typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit,
         bool FullyTabular>
double UnitAwareHistogramTabularTwoDDistributionImpl<PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit,FullyTabular>::evaluateSecondaryConditionalCDF(
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
         typename DependentUnit,
         bool FullyTabular>
auto UnitAwareHistogramTabularTwoDDistributionImpl<PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit,FullyTabular>::sampleSecondaryConditionalAndRecordBinIndex(
                  const PrimaryIndepQuantity primary_indep_var_value,
                  unsigned& sampled_bin_index ) const -> SecondaryIndepQuantity
{
  typename DistributionType::const_iterator lower_bin_boundary, upper_bin_boundary;
  
  this->findBinBoundaries( primary_indep_var_value,
                           lower_bin_boundary,
                           upper_bin_boundary );

  return lower_bin_boundary->second->sampleAndRecordBinIndex( sampled_bin_index );
}

// Return a random sample from the secondary conditional PDF at the CDF val
template<typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit,
         bool FullyTabular>
auto UnitAwareHistogramTabularTwoDDistributionImpl<PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit,FullyTabular>::sampleSecondaryConditionalWithRandomNumber(
                   const PrimaryIndepQuantity primary_indep_var_value,
                   const double random_number ) const -> SecondaryIndepQuantity
{
  typename DistributionType::const_iterator lower_bin_boundary, upper_bin_boundary;
  
  this->findBinBoundaries( primary_indep_var_value,
                           lower_bin_boundary,
                           upper_bin_boundary );

  return lower_bin_boundary->second->sampleWithRandomNumber( random_number );
}

// Return a random sample from the secondary conditional PDF in the subrange
template<typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit,
         bool FullyTabular>
auto UnitAwareHistogramTabularTwoDDistributionImpl<PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit,FullyTabular>::sampleSecondaryConditionalInSubrange(
             const PrimaryIndepQuantity primary_indep_var_value,
             const SecondaryIndepQuantity max_secondary_indep_var_value ) const
  -> SecondaryIndepQuantity
{
  typename DistributionType::const_iterator lower_bin_boundary, upper_bin_boundary;
  
  this->findBinBoundaries( primary_indep_var_value,
                           lower_bin_boundary,
                           upper_bin_boundary );

  return lower_bin_boundary->second->sampleInSubrange( max_secondary_indep_var_value );
}

// Return a random sample from the secondary conditional PDF in the subrange
template<typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit,
         bool FullyTabular>
auto UnitAwareHistogramTabularTwoDDistributionImpl<PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit,FullyTabular>::sampleSecondaryConditionalWithRandomNumberInSubrange(
             const PrimaryIndepQuantity primary_indep_var_value,
             const double random_number,
             const SecondaryIndepQuantity max_secondary_indep_var_value ) const
  -> SecondaryIndepQuantity
{
  typename DistributionType::const_iterator lower_bin_boundary, upper_bin_boundary;
 
  this->findBinBoundaries( primary_indep_var_value,
                           lower_bin_boundary,
                           upper_bin_boundary );

  return lower_bin_boundary->second->sampleWithRandomNumberInSubrange(
                                               random_number,
                                               max_secondary_indep_var_value );
}
  
} // end Utility namespace

#endif // end UTILITY_HISTOGRAM_TABULAR_TWO_D_DISTRIBUTION_HELPERS_DEF_HPP

//---------------------------------------------------------------------------//
// end Utility_HistogramTabularTwoDDistributionHelpers_def.hpp
//---------------------------------------------------------------------------//
