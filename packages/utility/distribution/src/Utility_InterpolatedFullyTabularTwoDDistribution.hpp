//---------------------------------------------------------------------------//
//!
//! \file   Utility_InterpolatedFullyTabularTwoDDistribution.hpp
//! \author Alex Robinson
//! \brief  The interpolated fully tabular two-dimensional dist. class decl.
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_INTERPOLATED_FULLY_TABULAR_TWO_D_DISTRIBUTION_HPP
#define UTILITY_INTERPOLATED_FULLY_TABULAR_TWO_D_DISTRIBUTION_HPP

// FRENSIE Includes
#include "Utility_InterpolatedTabularTwoDDistributionHelpers.hpp"

namespace Utility{

/*! The unit-aware inteprolated fully tabular two-dimensional distribution
 * \ingroup two_d_distribution
 */
template<typename TwoDInterpPolicy,
         typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit>
class UnitAwareInterpolatedFullyTabularTwoDDistribution : public UnitAwareInterpolatedTabularTwoDDistributionImpl<TwoDInterpPolicy,PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit,true>
{

private:

  // The parent distribution type
  typedef UnitAwareHistogramTabularTwoDDistributionImpl<PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit,true> ParentType;
  
public:
  
  //! The primary independent quantity type
  typedef typename ParentType::PrimaryIndepQuantity PrimaryIndepQuantity;

  //! The secondary independent quantity type
  typedef typename ParentType::SecondaryIndepQuantity SecondaryIndepQuantity;

  //! The inverse secondary independent quantity type
  typedef typename ParentType::InverseSecondaryIndepQuantity InverseSecondaryIndepQuantity;

  //! The dependent quantity type
  typedef typename ParentType::DepQuantity DepQuantity;

  //! The distribution type
  typedef typename ParentType::DistributionType DistributionType;

  //! Constructor
  UnitAwareInterpolatedFullyTabularTwoDDistribution(
                                         const DistributionType& distribution )
    : ParentType( distribution )
  { /* ... */ }

  //! Constructor
  template<template<typename T, typename... Args> class ArrayA,
           template<typename T, typename... Args> class ArrayB>
  UnitAwareInterpolatedFullyTabularTwoDDistribution(
                   const ArrayA<PrimaryIndepQuantity>& primary_indep_grid,
                   const ArrayB<std::shared_ptr<const UnitAwareTabularOneDDistribution<SecondaryIndependentUnit,DependentUnit> > >& secondary_distributions )
    : ParentType( primary_indep_grid, secondary_distributions )
  { /* ... */ }

  //! Raw constructor
  template<template<typename T, typename... Args> class ArrayA,
           template<typename T, typename... Args> class ArrayB,
           template<typename T, typename... Args> class SubarrayB,
           template<typename T, typename... Args> class ArrayC,
           template<typename T, typename... Args> class SubarrayC>
  UnitAwareInterpolatedFullyTabularTwoDDistribution(
       const ArrayA<PrimaryIndepQuantity>& primary_indep_grid,
       const ArrayB<SubarrayB<SecondaryIndepQuantity> >& secondary_indep_grids,
       const ArrayC<SubarrayC<DepQuantity> >& dependent_values )
    : ParentType( primary_indep_grid, secondary_indep_grids, dependent_values )
  { /* ... */ }

  //! Destructor
  ~UnitAwareInterpolatedFullyTabularTwoDDistribution()
  { /* ... */ }
};

/*! \brief The interpolated fully tabular two-dimensional distribution 
 * (unit-agnostic)
 * \ingroup two_d_distributions
 */
template<typename TwoDInterpPolicy> using InterpolatedFullyTabularTwoDDistribution =
  UnitAwareInterpolatedFullyTabularTwoDDistribution<TwoDInterpPolicy,void,void,void>;
  
} // end Utility namespace


#endif // end UTILITY_INTERPOLATED_FULLY_TABULAR_TWO_D_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end Utility_InterpolatedFullyTabularTwoDDistribution.hpp
//---------------------------------------------------------------------------//
