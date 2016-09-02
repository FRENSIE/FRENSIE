//---------------------------------------------------------------------------//
//!
//! \file   Utility_TabularTwoDDistribution_def.hpp
//! \author Alex Robinson
//! \brief  The tabular two-dimensional distribution class definition
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
         template<typename T, typename U> class BaseOneDDistribution>
UnitAwareTabularTwoDDistribution<PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit,BaseOneDDistribution>::UnitAwareTabularTwoDDistribution( const DistributionType& distribution )
  : d_distribution( distribution.begin(), distribution.end() )
{
  // Make sure the distribution is valid
  testPrecondition( Sort::isSortedAscending<FIRST>( distribution.begin(),
                                                    distribution.end() ) );
}

// Constructor
template<typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit,
         template<typename T, typename U> class BaseOneDDistribution>
template<template<typename T, typename... Args> class ArrayA,
         template<typename T, typename... Args> class ArrayB>
UnitAwareTabularTwoDDistribution<PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit,BaseOneDDistribution>::UnitAwareTabularTwoDDistribution(
                const ArrayA<PrimaryIndepQuantity>& primary_indep_grid,
                const ArrayB<std::shared_ptr<const BaseOneDDistributionType> >&
                secondary_distributions )
  : d_distribution( primary_indep_grid.size() )
{
  // Make sure the independent grid is valid
  testPrecondition( Sort::isSortedAscending( primary_indep_grid.begin(),
                                             primary_indep_grid.end() ) );
  testPrecondition( primary_indep_grid.size() ==
                    secondary_distributions.size() );

  // Set the distribution
  for( unsigned i = 0u; i < primary_indep_grid.size(); ++i )
  {
    d_distribution[i].first = primary_indep_grid[i];
    d_distribution[i].second = secondary_distributions[i];
  }
}

// Return the upper bound of the distribution primary independent variable
template<typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit,
         template<typename T, typename U> class BaseOneDDistribution>
auto UnitAwareTabularTwoDDistribution<PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit,BaseOneDDistribution>::getUpperBoundOfPrimaryIndepVar() const -> PrimaryIndepQuantity
{
  return d_distribution.back().first;
}

// Return the lower bound of the distribution primary independent variable
template<typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit,
         template<typename T, typename U> class BaseOneDDistribution>
auto UnitAwareTabularTwoDDistribution<PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit,BaseOneDDistribution>::getLowerBoundOfPrimaryIndepVar() const -> PrimaryIndepQuantity
{
  return d_distribution.front().first;
}

// Test if the distribution is tabular in the primary dimension
template<typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit,
         template<typename T, typename U> class BaseOneDDistribution>
bool UnitAwareTabularTwoDDistribution<PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit,BaseOneDDistribution>::isPrimaryDimensionTabular() const
{
  return true;
}

// Set the distribution
template<typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit,
         template<typename T, typename U> class BaseOneDDistribution>
void UnitAwareTabularTwoDDistribution<PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit,BaseOneDDistribution>::setDistribution( const DistributionType distribution )
{
  // Make sure the distribution is valid
  testPrecondition( Sort::isSortedAscending<FIRST>( distribution.begin(),
                                                    distribution.end() ) );

  d_distribution = distribution;
}

// Find the bin boundaries
template<typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit,
         template<typename T, typename U> class BaseOneDDistribution>
inline void UnitAwareTabularTwoDDistribution<PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit,BaseOneDDistribution>::findBinBoundaries(
          const PrimaryIndepQuantity primary_independent_var_value,
          typename DistributionType::const_iterator& lower_bin_boundary,
          typename DistributionType::const_iterator& upper_bin_boundary ) const
{
  if( primary_independent_var_value < d_distribution.front().first )
  {
    lower_bin_boundary = d_distribution.begin();
    upper_bin_boundary = lower_bin_boundary;
  }
  else if( primary_independent_var_value >= d_distribution.back().first )
  {
    lower_bin_boundary = d_distribution.end();
    --lower_bin_boundary;
    upper_bin_boundary = lower_bin_boundary;
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

// Calculate the interpolation fraction
template<typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit,
         template<typename T, typename U> class BaseOneDDistribution>
inline double UnitAwareTabularTwoDDistribution<PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit,BaseOneDDistribution>::calculateInterpolationFraction(
    const PrimaryIndepQuantity primary_indep_var_value,
    const typename DistributionType::const_iterator& lower_bin_boundary,
    const typename DistributionType::const_iterator& upper_bin_boundary ) const
{
  return (primary_indep_var_value - lower_bin_boundary->first)/
    (upper_bin_boundary->first - lower_bin_boundary->first);
}

} // end Utility namespace

#endif // end UTILITY_TABULAR_TWO_D_DISTRIBUTION_DEF_HPP 
  
//---------------------------------------------------------------------------//
// end Utility_TabularTwoDDistribution_def.hpp
//---------------------------------------------------------------------------//
