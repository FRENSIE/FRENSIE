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
    TwoDInterpPolicy::calculateGridLength(
                       lower_bin_boundary->second->getLowerBoundOfIndepVar(),
                       lower_bin_boundary->second->getUpperBoundOfIndepVar() );

  // Calculate the length of the upper secondary grid
  const typename QuantityTraits<SecondaryIndepQuantity>::RawType L1 =
    TwoDInterpPolicy::calculateGridLength(
                       upper_bin_boundary->second->getLowerBoundOfIndepVar(),
                       upper_bin_boundary->second->getUpperBoundOfIndepVar() );

  // Create the grid evaluation functors
  std::function<DepQuantity(IndepQuantity)> evaluate_grid_0_functor =
    std::bind<DepQuantity>( &BaseOneDDistributionType::evaluate,
                            std::cref( lower_bin_boundary->second ),
                            std::placeholders::_1 );

  std::function<DepQuantity(IndepQuantity)> evaluate_grid_1_functor =
    std::bind<DepQuantity>( &BaseOneDDistributionType::evaluate,
                            std::cref( upper_bin_boundary->second ),
                            std::placeholders::_1 );
  
  return TwoDInterpPolicy::interpolateUnitBase(
                         lower_bin_boundary->first,
                         upper_bin_boundary->first,
                         primary_indep_var_value,
                         secondary_indep_var_value,
                         lower_bin_boundary->second->getLowerBoundOfIndepVar(),
                         upper_bin_boundary->second->getLowerBoundOfIndepVar(),
                         L0,
                         L1,
                         evaluate_grid_0_functor,
                         evaluate_grid_1_functor );
}

// Evaluate the secondary conditional PDF
template<typename TwoDInterpPolicy, typename Distribution>
InverseSecondaryIndepQuantity UnitAwareInterpolatedTabularTwoDDistributionImplBase<TwoDInterpPolicy,Distribution>::evaluateSecondaryConditionalPDF(
                 const PrimaryIndepQuantity primary_indep_var_value,
                 const SecondaryIndepQuantity secondary_indep_var_value ) const
{
  // Find the bin boundaries
  typename DistributionType::const_iterator lower_bin_boundary, upper_bin_boundary;
  
  this->findBinBoundaries( primary_indep_var_value,
                           lower_bin_boundary,
                           upper_bin_boundary );

  // Calculate the length of the lower secondary grid
  const typename QuantityTraits<SecondaryIndepQuantity>::RawType L0 =
    TwoDInterpPolicy::calculateGridLength(
                       lower_bin_boundary->second->getLowerBoundOfIndepVar(),
                       lower_bin_boundary->second->getUpperBoundOfIndepVar() );

  // Calculate the length of the upper secondary grid
  const typename QuantityTraits<SecondaryIndepQuantity>::RawType L1 =
    TwoDInterpPolicy::calculateGridLength(
                       upper_bin_boundary->second->getLowerBoundOfIndepVar(),
                       upper_bin_boundary->second->getUpperBoundOfIndepVar() );

  // Create the grid evaluation functors
  std::function<DepQuantity(IndepQuantity)> evaluate_grid_0_functor =
    std::bind<DepQuantity>( &BaseOneDDistributionType::evaluatePDF,
                            std::cref( lower_bin_boundary->second ),
                            std::placeholders::_1 );

  std::function<DepQuantity(IndepQuantity)> evaluate_grid_1_functor =
    std::bind<DepQuantity>( &BaseOneDDistributionType::evaluatePDF,
                            std::cref( upper_bin_boundary->second ),
                            std::placeholders::_1 );
  
  return TwoDInterpPolicy::interpolateUnitBase(
                         lower_bin_boundary->first,
                         upper_bin_boundary->first,
                         primary_indep_var_value,
                         secondary_indep_var_value,
                         lower_bin_boundary->second->getLowerBoundOfIndepVar(),
                         upper_bin_boundary->second->getLowerBoundOfIndepVar(),
                         L0,
                         L1,
                         evaluate_grid_0_functor,
                         evaluate_grid_1_functor );
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
