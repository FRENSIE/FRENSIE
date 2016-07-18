//---------------------------------------------------------------------------//
//!
//! \file   Utility_InterpolatedTabularTwoDDistributionHelpers_def.hpp
//! \author Alex Robinson
//! \brief  The interpolated tabular two-dimensional dist. helper class defs.
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_INTERPOLATED_TABULAR_TWO_D_DISTRIBUTION_HELPERS_DEF_HPP
#define UTILITY_INTERPOLATED_TABULAR_TWO_D_DISTRIBUTION_HELPERS_DEF_HPP

// FRENSIE Includes
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_ContractException.hpp"

namespace Utility{

// Constructor
template<typename TwoDInterpPolicy, typename Distribution>
UnitAwareInterpolatedTabularTwoDDistributionImplBase<TwoDInterpPolicy,Distribution>::UnitAwareInterpolatedTabularTwoDDistributionImplBase(
                                         const DistributionType& distribution )
  : ParentType( distribution )
{

}

// Constructor
template<typename TwoDInterpPolicy, typename Distribution>
template<template<typename T, typename... Args> class ArrayA,
         template<typename T, typename... Args> class ArrayB>
UnitAwareInterpolatedTabularTwoDDistributionImplBase(
                const ArrayA<PrimaryIndepQuantity>& primary_indep_grid,
                const ArrayB<std::shared_ptr<const BaseOneDDistributionType> >&
                secondary_distributions )
    : ParentType( primary_indep_grid, secondary_distributions )
{

}
 
// Evaluate the distribution
template<typename TwoDInterpPolicy, typename Distribution>
auto UnitAwareInterpolatedTabularTwoDDistributionImplBase<TwoDInterpPolicy,Distribution>::evaluate(
                 const PrimaryIndepQuantity primary_indep_var_value,
                 const SecondaryIndepQuantity secondary_indep_var_value ) const
  -> DepQuantity
{
  // Find the bin boundaries
  typename DistributionType::const_iterator lower_bin_boundary, upper_bin_boundary;
  
  this->findBinBoundaries( primary_indep_var_value,
                           lower_bin_boundary,
                           upper_bin_boundary );

  // Calculate the length of the lower secondary grid
  const typename QuantityTraits<SecondaryIndepQuantity>::RawType L0 =
    TwoDInterpPolicy::calculateLength(
                       lower_bin_boundary->second->getLowerBoundOfIndepVar(),
                       lower_bin_boundary->second->getUpperBoundOfIndepVar() );

  // Calculate the length of the upper secondary grid
  const typename QuantityTraits<SecondaryIndepQuantity>::RawType L1 =
    TwoDInterpPolicy::calculateLength(
                       upper_bin_boundary->second->getLowerBoundOfIndepVar(),
                       upper_bin_boundary->second->getUpperBoundOfIndepVar() );

  // Calculate the length of the intermediate grid
  const typename QuantityTraits<SecondaryIndepQuantity>::RawType L_mid =
    TwoDInterpPolicy::calculateIntermediateGridLength(
                                                     lower_bin_boundary->first,
                                                     upper_bin_boundary->first,
                                                     primary_indep_var_value,
                                                     L0,
                                                     L1 );

  // Calculate the intermediate secondary indep lower bound
  const typename QuantityTraits<SecondaryIndepQuantity>::RawType
    secondary_indep_lower_bound_value_mid =
    TwoDInterpPolicy::calculateIntermediateGridLimit(
                       lower_bin_boundary->first,
                       upper_bin_boundary->first,
                       primary_indep_var_value,
                       lower_bin_boundary->second->getLowerBoundOfIndepVar(),
                       upper_bin_boundary->second->getLowerBoundOfIndepVar() );

  // Calculate the unit base independent variable
  const typename QuantityTraits<SecondaryIndepQuantity>::RawType eta =
    TwoDInterpPolicy::ZYInterpPolicy::calculateUnitBaseIndepVar(
                                         secondary_indep_var_value,
                                         secondary_indep_lower_bound_value_mid,
                                         L_mid );

  // Calculate the secondary independent value on the first grid
  const typename QuantityTraits<SecondaryIndepQuantity>::RawType
    lower_secondary_indep_var_value =
    TwoDInterpPolicy::ZYInterpPolicy::calculateIndepVar(
                         eta,
                         lower_bin_boundary->second->getLowerBoundOfIndepVar(),
                         L0 );

  // Evaluate the lower distribution
  DepQuantity lower_dep_var_value =
    lower_bin_boundary->second->evaluate( lower_secondary_indep_var_value  );

  const typename QuantityTraits<DepQuantity>::RawType
    processed_lower_dep_var_value =
    TwoDInterpPolicy::ZYInterpPolicy::processDepVar( lower_dep_var_value );

  // Calculate the secondary independent value on the second grid
  const typename QuantityTraits<SecondaryIndepQuantity>::RawType
    upper_secondary_indep_var_value =
    TwoDInterpPolicy::ZYInterpPolicy::calculateIndepVar(
                         eta,
                         lower_bin_boundary->second->getLowerBoundOfIndepVar(),
                         L0 );

  // Evaluate the upper distribution
  DepQuantity upper_dep_var_value =
    upper_bin_boundary->second->evaluate( upper_secondary_indep_var_value );

  const typename QuantityTraits<DepQuantity>::RawType
    processed_upper_dep_var_value =
    TwoDInterpPolicy::ZYInterpPolicy::processDepVar( upper_dep_var_value );

  // Conduct the primary-dependent interpolation
  const typename QuantityTraits<PrimaryIndepQuantity>::RawType
    processed_lower_primary_indep_var_value =
    TwoDInterpPolicy::ZXInterpPolicy::processIndepVar( lower_bin_boundary->first );

  const typename QuantityTraits<PrimaryIndepQuantity>::RawType
    processed_upper_primary_indep_var_value =
    TwoDInterpPolicy::ZXInterpPolicy::processIndepVar( upper_bin_boundary->first );

  const typename QuantityTraitss<PrimaryIndepQuantity>::RawType
    processed_primary_indep_var_value =
    TwoDInterpPolicy::ZXInterpPolicy::processIndepVar( primary_indep_var_value );

  const typename QuantityTraitss<PrimaryIndepQuantity>::RawType
    processed_slope =
    (processed_upper_dep_var_value*L1 - processed_lower_dep_var_value*L0)/
    (processed_upper_primary_indep_var_value -
     processed_lower_primary_indep_var_value);
  
  const typename QuantityTraits<SecondaryIndepQuantity>::RawType
    processed_dep_var_value =
    TwoDInterpPolicy::ZXInterpPolicy::interpolateAndProcess(
                                        procesed_lower_primary_indep_var_value,
                                        processed_primary_indep_var_value,
                                        processed_lower_dep_var_value*L0,
                                        processed_slope )/L_mid;
  
  return QuantityTraits<DepQuantity>::initializeQuantity(
                      TwoDInterpPolicy::ZXInterpPolicy::recoverProcessedDepVar(
                                                   processed_dep_var_value ) );
}

// Evaluate the secondary conditional PDF
template<typename TwoDInterpPolicy, typename Distribution>
InverseSecondaryIndepQuantity UnitAwareInterpolatedTabularTwoDDistributionImplBase<TwoDInterpPolicy,Distribution>::evaluateSecondaryConditionalPDF(
                 const PrimaryIndepQuantity primary_indep_var_value,
                 const SecondaryIndepQuantity secondary_indep_var_value ) const
{

}

// Return a random sample from the secondary conditional PDF
/*! \details A stochastic sampling procedure is used.
 */
template<typename TwoDInterpPolicy, typename Distribution>
auto UnitAwareInterpolatedTabularTwoDDistributionImplBase<TwoDInterpPolicy,Distribution>::sampleSecondaryConditional(
                     const PrimaryIndepQuantity primary_indep_var_value ) const
  -> SecondaryIndepQuantity
{
  // Find the bin boundaries
  typename DistributionType::const_iterator lower_bin_boundary, upper_bin_boundary;
  
  this->findBinBoundaries( primary_indep_var_value,
                           lower_bin_boundary,
                           upper_bin_boundary );

  // Calculate the interpolation fraction
  double interpolation_fraction = 
      (primary_indep_var_value - lower_bin_boundary->first)/
      (upper_bin_boundary->first - lower_bin_boundary->first);

  // Sample to determine the distribution that will be used
  double random_number =
    Utility::RandomNumberGenerator::getRandomNumber<double>();

  if( random_number < interpolation_fraction )
    return upper_bin_boundary->second->sample();
  else
    return lower_bin_boundary->second->sample();
}

// Return a random sample and record the number of trials
/*! \details A stochastic sampling procedure is used.
 */
template<typename TwoDInterpPolicy, typename Distribution>
SecondaryIndepQuantity UnitAwareInterpolatedTabularTwoDDistributionImplBase<TwoDInterpPolicy,Distribution>::sampleSecondaryConditionalAndRecordTrials(
                            const PrimaryIndepQuantity primary_indep_var_value,
                            unsigned& trials ) const
{
  // Find the bin boundaries
  typename DistributionType::const_iterator lower_bin_boundary, upper_bin_boundary;
  
  this->findBinBoundaries( primary_indep_var_value,
                           lower_bin_boundary,
                           upper_bin_boundary );

  // Calculate the interpolation fraction
  double interpolation_fraction = 
      (primary_indep_var_value - lower_bin_boundary->first)/
      (upper_bin_boundary->first - lower_bin_boundary->first);

  // Sample to determine the distribution that will be used
  double random_number =
    Utility::RandomNumberGenerator::getRandomNumber<double>();

  if( random_number < interpolation_fraction )
    return upper_bin_boundary->second->sampleAndRecordTrials( trials );
  else
    return lower_bin_boundary->second->sampleAndRecordTrials( trials );
}

// Return the upper bound of the conditional distribution
template<typename TwoDInterpPolicy, typename Distribution>
auto UnitAwareInterpolatedTabularTwoDDistributionImplBase<TwoDInterpPolicy,Distribution>::getUpperBoundOfConditionalIndepVar(
                     const PrimaryIndepQuantity primary_indep_var_value ) const
  -> SecondaryIndepQuantity
{
  typename DistributionType::const_interator lower_bin_bounary, upper_bin_boundary;
  
  this->findBinBoundaries( primary_indep_var_value,
                           lower_bin_boundary,
                           upper_bin_boundary );
  
  return TwoDInterpPolicy::calculateIntermediateGridLimit(
                       lower_bin_boundary->first,
                       lower_bin_boundary->second,
                       primary_indep_var_value,
                       lower_bin_boundary->second->getUpperBoundOfIndepVar(),
                       upper_bin_boundary->second->getUpperBoundOfIndepVar() );
}

// Return the lower bound of the conditional distribution
template<typename TwoDInterpPolicy, typename Distribution>
auto UnitAwareInterpolatedTabularTwoDDistributionImplBase<TwoDInterpPolicy,Distribution>::getLowerBoundOfConditionalIndepVar(
                     const PrimaryIndepQuantity primary_indep_var_value ) const
  -> SecondaryIndepQuantity
{
  typename DistributionType::const_interator lower_bin_bounary, upper_bin_boundary;
  
  this->findBinBoundaries( primary_indep_var_value,
                           lower_bin_boundary,
                           upper_bin_boundary );
  
  return TwoDInterpPolicy::calculateIntermediateGridLimit(
                       lower_bin_boundary->first,
                       lower_bin_boundary->second,
                       primary_indep_var_value,
                       lower_bin_boundary->second->getLowerBoundOfIndepVar(),
                       upper_bin_boundary->second->getLowerBoundOfIndepVar() );
}

// Test if the distribution is continuous in the primary dimension
template<typename TwoDInterpPolicy, typename Distribution>
bool UnitAwareInterpolatedTabularTwoDDistributionImplBase<TwoDInterpPolicy,Distribution>::isPrimaryDimensionContinuous() const
{
  return true;
}

} // end Utility namespace

#endif // end UTILITY_INTERPOLATED_TABULAR_TWO_D_DISTRIBUTION_HELPERS_DEF_HPP

//---------------------------------------------------------------------------//
// end Utility_InterpolatedTabularTwoDDistributionHelpers_def.hpp
//---------------------------------------------------------------------------//
