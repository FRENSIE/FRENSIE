//---------------------------------------------------------------------------//
//!
//! \file   Utility_TabularBivariateDistribution_def.hpp
//! \author Alex Robinson
//! \brief  The tabular bivariate distribution class definition
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_TABULAR_TWO_D_DISTRIBUTION_DEF_HPP 
#define UTILITY_TABULAR_TWO_D_DISTRIBUTION_DEF_HPP

// FRENSIE Includes
#include "Utility_SortAlgorithms.hpp"
#include "Utility_SearchAlgorithms.hpp"
#include "Utility_ContractException.hpp"

namespace Utility{

// Constructor
/*! \details The independent values must be sorted in ascending order
 */
template<typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit,
         template<typename T, typename U> class BaseUnivariateDistribution>
UnitAwareTabularBivariateDistribution<PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit,BaseUnivariateDistribution>::UnitAwareTabularBivariateDistribution( const DistributionType& distribution )
  : d_distribution( distribution.begin(), distribution.end() ),
    d_extend_beyond_primary_limits( false )
{
  // Make sure the distribution is valid
  testPrecondition( Sort::isSortedAscending<FIRST>( distribution.begin(),
                                                    distribution.end() ) );
}

// Constructor
template<typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit,
         template<typename T, typename U> class BaseUnivariateDistribution>
template<template<typename T, typename... Args> class ArrayA,
         template<typename T, typename... Args> class ArrayB>
UnitAwareTabularBivariateDistribution<PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit,BaseUnivariateDistribution>::UnitAwareTabularBivariateDistribution(
                const ArrayA<PrimaryIndepQuantity>& primary_indep_grid,
                const ArrayB<std::shared_ptr<const BaseUnivariateDistributionType> >&
                secondary_distributions )
  : d_distribution( primary_indep_grid.size() ),
    d_extend_beyond_primary_limits( false )
{
  // Make sure the independent grid is valid
  testPrecondition( Sort::isSortedAscending( primary_indep_grid.begin(),
                                             primary_indep_grid.end() ) );
  testPrecondition( primary_indep_grid.size() ==
                    secondary_distributions.size() );

  // Set the distribution
  for( unsigned i = 0u; i < primary_indep_grid.size(); ++i )
  {
    Utility::get<0>( d_distribution[i] ) = primary_indep_grid[i];
    Utility::get<1>( d_distribution[i] ) = secondary_distributions[i];
  }
}

// Extend the distribution beyond the primary independent variable limits
/*! \details The default behavior of this class when evaluating the
 * the distribution outside of the primary independent variable limits is
 * to return zero. After calling this function that behavior will instead
 * be to use the appropriate limiting secondary distribution for all 
 * primary values beyond the defined primary limits.
 */
template<typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit,
         template<typename T, typename U> class BaseUnivariateDistribution>
void UnitAwareTabularBivariateDistribution<PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit,BaseUnivariateDistribution>::extendBeyondPrimaryIndepLimits()
{
  d_extend_beyond_primary_limits = true;
}

// Limit the distribution to the primary independent variable limits
/*! \details The default behavior of this class when evaluating the
 * the distribution outside of the primary independent variable limits is
 * to return zero. This method does not need to be called unless
 * the extendDistributionBeyondPrimaryIndepLimits method has been called
 * (this method will restore the default behavior).
 */
template<typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit,
         template<typename T, typename U> class BaseUnivariateDistribution>
void UnitAwareTabularBivariateDistribution<PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit,BaseUnivariateDistribution>::limitToPrimaryIndepLimits()
{
  d_extend_beyond_primary_limits = false;
}

// Check if the distribution is being extended beyond the primary limits
/*! \details The default behavior of this class when evaluating the
 * the distribution outside of the primary independent variable limits is
 * to return zero. When the limits have been extended that behavior will 
 * instead be to use the appropriate limiting secondary distribution for all 
 * primary values beyond the defined primary limits.
 */
template<typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit,
         template<typename T, typename U> class BaseUnivariateDistribution>
bool UnitAwareTabularBivariateDistribution<PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit,BaseUnivariateDistribution>::arePrimaryLimitsExtended() const
{
  return d_extend_beyond_primary_limits;
}

// Return the upper bound of the distribution primary independent variable
template<typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit,
         template<typename T, typename U> class BaseUnivariateDistribution>
auto UnitAwareTabularBivariateDistribution<PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit,BaseUnivariateDistribution>::getUpperBoundOfPrimaryIndepVar() const -> PrimaryIndepQuantity
{
  return Utility::get<0>(d_distribution.back());
}

// Return the lower bound of the distribution primary independent variable
template<typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit,
         template<typename T, typename U> class BaseUnivariateDistribution>
auto UnitAwareTabularBivariateDistribution<PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit,BaseUnivariateDistribution>::getLowerBoundOfPrimaryIndepVar() const -> PrimaryIndepQuantity
{
  return Utility::get<0>(d_distribution.front());
}

// Test if the distribution is tabular in the primary dimension
template<typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit,
         template<typename T, typename U> class BaseUnivariateDistribution>
bool UnitAwareTabularBivariateDistribution<PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit,BaseUnivariateDistribution>::isPrimaryDimensionTabular() const
{
  return true;
}

// Set the distribution
template<typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit,
         template<typename T, typename U> class BaseUnivariateDistribution>
void UnitAwareTabularBivariateDistribution<PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit,BaseUnivariateDistribution>::setDistribution( const DistributionType distribution )
{
  // Make sure the distribution is valid
  testPrecondition( Sort::isSortedAscending<FIRST>( distribution.begin(),
                                                    distribution.end() ) );

  d_distribution = distribution;
}

// Find the bin boundaries
/*! \details The lower and upper boundary will only be equal when the 
 * primary_independent_var_value is outside of the primary grid limits.
 */
template<typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit,
         template<typename T, typename U> class BaseUnivariateDistribution>
inline void UnitAwareTabularBivariateDistribution<PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit,BaseUnivariateDistribution>::findBinBoundaries(
          const PrimaryIndepQuantity primary_independent_var_value,
          typename DistributionType::const_iterator& lower_bin_boundary,
          typename DistributionType::const_iterator& upper_bin_boundary ) const
{
  if( primary_independent_var_value < Utility::get<0>(d_distribution.front()) )
  {
    lower_bin_boundary = d_distribution.begin();
    upper_bin_boundary = lower_bin_boundary;
  }
  else if( primary_independent_var_value > Utility::get<0>(d_distribution.back()) )
  {
    lower_bin_boundary = d_distribution.end();
    --lower_bin_boundary;
    upper_bin_boundary = lower_bin_boundary;
  }
  else if( primary_independent_var_value == Utility::get<0>(d_distribution.back()) )
  {
    lower_bin_boundary = d_distribution.end();
    --lower_bin_boundary;
    upper_bin_boundary = lower_bin_boundary;

    --lower_bin_boundary;
  }
  else
  {
    lower_bin_boundary = d_distribution.begin();
    upper_bin_boundary = d_distribution.end();
    
    lower_bin_boundary = Utility::Search::binaryLowerBound<Utility::FIRST>( 
					       lower_bin_boundary,
                                               upper_bin_boundary,
					       primary_independent_var_value );
    upper_bin_boundary = lower_bin_boundary;
    ++upper_bin_boundary;
  }
}

// Calculate the index of the desired bin
template<typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit,
         template<typename T, typename U> class BaseUnivariateDistribution>
size_t UnitAwareTabularBivariateDistribution<PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit,BaseUnivariateDistribution>::calculateBinIndex(
                typename DistributionType::const_iterator& bin_boundary ) const
{
  return std::distance( d_distribution.begin(), bin_boundary );
}

// Check that all secondary distributions are continuous
template<typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit,
         template<typename T, typename U> class BaseUnivariateDistribution>
bool UnitAwareTabularBivariateDistribution<PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit,BaseUnivariateDistribution>::areSecondaryDistributionsContinuous() const
{
  bool all_continuous = true;
  
  for( size_t i = 0; i < d_distribution.size(); ++i )
  {
    if( !Utility::get<1>(d_distribution[i])->isContinuous() )
    {
      all_continuous = false;

      break;
    }
  }

  return all_continuous;
}

} // end Utility namespace

#endif // end UTILITY_TABULAR_TWO_D_DISTRIBUTION_DEF_HPP 
  
//---------------------------------------------------------------------------//
// end Utility_TabularBivariateDistribution_def.hpp
//---------------------------------------------------------------------------//
