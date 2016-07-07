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

// Constructor
template<typename Distribution>
template<template<typename T, typename... Args> class Array>
UnitAwareHistogramTabularTwoDDistributionImplBase<Distribution>::UnitAwareHistogramTabularTwoDDistributionImplBase( const Array<std::pair<PrimaryIndepQuantity,std::shared_ptr<const BaseOneDDistributionType> > >& distribution )
  : Distribution( distribution )
{ /* ... */ }

// Constructor
template<typename Distribution>
template<template<typename T, typename... Args> class ArrayA,
         template<typename T, typename... Args> class ArrayB>
UnitAwareHistogramTabularTwoDDistributionImplBase<Distribution>::UnitAwareHistogramTabularTwoDDistributionImplBase(
                const ArrayA<PrimaryIndepQuantity>& primary_indep_grid,
                const ArrayB<std::shared_ptr<const BaseOneDDistributionType> >&
                secondary_distributions )
  : Distribution( primary_indep_grid, secondary_distributions )
{ /* ... */ }

// Evaluate the distribution
template<typename Distribution>
DepQuantity UnitAwareHistogramTabularTwoDDistributionImplBase<Distribution>::evaluate(
                 const PrimaryIndepQuantity primary_indep_var_value,
                 const SecondaryIndepQuantity secondary_indep_var_value ) const
{
  DistributionType::const_iterator lower_bin_boundary, upper_bin_boundary;
  
  this->findBinBoundaries( primary_indep_var_value,
                           lower_bin_boundary,
                           upper_bin_boundary );

  lower_bin_boundary->evaluate( secondary_indep_var_value );
}

// Evaluate the secondary conditional PDF
template<typename Distribution>
InverseSecondaryIndepQuantity UnitAwareHistogramTabularTwoDDistributionImplBase<Distribution>::evaluateSecondaryConditionalPDF(
                 const PrimaryIndepQuantity primary_indep_var_value,
                 const SecondaryIndepQuantity secondary_indep_var_value ) const
{
  DistributionType::const_iterator lower_bin_boundary, upper_bin_boundary;
  
  this->findBinBoundaries( primary_indep_var_value,
                           lower_bin_boundary,
                           upper_bin_boundary );

  return lower_bin_boundary->evaluatePDF( secondary_indep_var_value );
}

// Return a random sample from the secondary conditional PDF
template<typename Distribution>
SecondaryIndepQuantity UnitAwareHistogramTabularTwoDDistributionImplBase<Distribution>::sampleSecondaryConditional(
                     const PrimaryIndepQuantity primary_indep_var_value ) const
{
  DistributionType::const_iterator lower_bin_boundary, upper_bin_boundary;
  
  this->findBinBoundaries( primary_indep_var_value,
                           lower_bin_boundary,
                           upper_bin_boundary );

  return lower_bin_boundary->sample( primary_indep_var_value );
}

// Return a random sample and record the number of trials
template<typename Distribution>
SecondaryIndepQuantity UnitAwareHistogramTabularTwoDDistributionImplBase<Distribution>::sampleSecondaryConditionalAndRecordTrials(
                            const PrimaryIndepQuantity primary_indep_var_value,
                            unsigned& trials ) const
{
  DistributionType::const_iterator lower_bin_boundary, upper_bin_boundary;
  
  this->findBinBoundaries( primary_indep_var_value,
                           lower_bin_boundary,
                           upper_bin_boundary );

  return lower_bin_boundary->sampleAndRecordTrials( trials );
}

// Return the upper bound of the conditional distribution
template<typename Distribution>
SecondaryIndepQuantity UnitAwareHistogramTabularTwoDDistributionImplBase<Distribution>::getUpperBoundOfConditionalIndepVar(
                     const PrimaryIndepQuantity primary_indep_var_value ) const
{
  DistributionType::const_iterator lower_bin_boundary, upper_bin_boundary;
  
  this->findBinBoundaries( primary_indep_var_value,
                           lower_bin_boundary,
                           upper_bin_boundary );

  return lower_bin_boundary->getUpperBoundOfIndepVar();
}

// Return the lower bound of the conditional distribution
template<typename Distribution>
SecondaryIndepQuantity UnitAwareHistogramTabularTwoDDistributionImplBase<Distribution>::getLowerBoundOfConditionalIndepVar(
                     const PrimaryIndepQuantity primary_indep_var_value ) const
{
  DistributionType::const_iterator lower_bin_boundary, upper_bin_boundary;
  
  this->findBinBoundaries( primary_indep_var_value,
                           lower_bin_boundary,
                           upper_bin_boundary );

  return lower_bin_boundary->getLowerBoundOfIndepVar();
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
         typename DependentUnit
         bool FullyTabular>
double UnitAwareHistogramTabularTwoDDistributionImpl<PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>::evaluateSecondaryConditionalCDF(
                 const PrimaryIndepQuantity primary_indep_var_value,
                 const SecondaryIndepQuantity secondary_indep_var_value ) const
{
  DistributionType::const_iterator lower_bin_boundary, upper_bin_boundary;
  
  this->findBinBoundaries( primary_indep_var_value,
                           lower_bin_boundary,
                           upper_bin_boundary );

  return lower_bin_boundary->evaluateCDF( primary_indep_var_value );
}

// Return a random sample from the secondary conditional PDF and the index
template<typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit
         bool FullyTabular>
SecondaryIndepQuantity UnitAwareHistogramTabularTwoDDistributionImpl<PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>::sampleSecondaryConditionalAndRecordBinIndex(
                                            unsigned& sampled_bin_index ) const
{
  DistributionType::const_iterator lower_bin_boundary, upper_bin_boundary;
  
  this->findBinBoundaries( primary_indep_var_value,
                           lower_bin_boundary,
                           upper_bin_boundary );

  return lower_bin_boundary->sampleAndRecordBinIndex( sampled_bin_index );
}

// Return a random sample from the secondary conditional PDF at the CDF val
template<typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit
         bool FullyTabular>
SecondaryIndepQuantity UnitAwareHistogramTabularTwoDDistributionImpl<PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>::sampleSecondaryConditionalWithRandomNumber(
                                             const double random_number ) const
{
  DistributionType::const_iterator lower_bin_boundary, upper_bin_boundary;
  
  this->findBinBoundaries( primary_indep_var_value,
                           lower_bin_boundary,
                           upper_bin_boundary );

  return lower_bin_boundary->sampleWithRandomNumber( random_number );
}

// Return a random sample from the secondary conditional PDF in the subrange
template<typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit
         bool FullyTabular>
SecondaryIndepQuantity UnitAwareHistogramTabularTwoDDistributionImpl<PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>::sampleSecondaryConditionalInSubrange(
             const SecondaryIndepQuantity max_secondary_indep_var_value ) const
{
  DistributionType::const_iterator lower_bin_boundary, upper_bin_boundary;
  
  this->findBinBoundaries( primary_indep_var_value,
                           lower_bin_boundary,
                           upper_bin_boundary );

  return lower_bin_boundary->sampleInSubrange( max_secondary_indep_var_value );
}

// Return a random sample from the secondary conditional PDF in the subrange
template<typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit
         bool FullyTabular>
SecondaryIndepQuantity UnitAwareHistogramTabularTwoDDistributionImpl<PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>::sampleSeconaryConditionalWithRandomNumberInSubrange(
             const double random_number,
             const SecondaryIndepQuantity max_secondary_indep_var_value ) const
{
  DistributionType::const_iterator lower_bin_boundary, upper_bin_boundary;
 
  this->findBinBoundaries( primary_indep_var_value,
                           lower_bin_boundary,
                           upper_bin_boundary );

  return lower_bin_boundary->sampleWithRandomNumberInSubrange(
                                               random_number,
                                               max_secondary_indep_var_value );
}
  
} // end Utility namespace

#endif // end UTILITY_HISTOGRAM_TABULAR_TWO_D_DISTRIBUTION_HELPERS_DEF_HPP

//---------------------------------------------------------------------------//
// end Utility_HistogramTabularTwoDDistributionHelpers_def.hpp
//---------------------------------------------------------------------------//
