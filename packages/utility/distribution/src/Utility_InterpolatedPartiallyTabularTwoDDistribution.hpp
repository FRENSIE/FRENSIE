//---------------------------------------------------------------------------//
//!
//! \file   Utility_InterpolatedPartiallyTabularTwoDDistribution.hpp
//! \author Alex Robinson
//! \brief  The interpolated partially tabular two-d dist. class decl.
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_INTERPOLATED_PARTIALLY_TABULAR_TWO_D_DISTRIBUTION_HPP
#define UTILITY_INTERPOLATED_PARTIALLY_TABULAR_TWO_D_DISTRIBUTION_HPP

// FRENSIE Includes
#include "Utility_InterpolatedTabularTwoDDistributionImplBase.hpp"

namespace Utility{

/*! The unit-aware interpolated partially tabular two_dimensional distribution
 * \ingroup two_d_distributions
 */
template<typename TwoDGridPolicy,
         typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit>
class UnitAwareInterpolatedPartiallyTabularTwoDDistribution : public UnitAwareInterpolatedTabularTwoDDistributionImplBase<TwoDGridPolicy,UnitAwarePartiallyTabularTwoDDistribution<PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit> >
{

private:

  // The parent distribution type
  typedef UnitAwareInterpolatedTabularTwoDDistributionImplBase<TwoDGridPolicy,UnitAwarePartiallyTabularTwoDDistribution<PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit> > ParentType;
  
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
  UnitAwareInterpolatedPartiallyTabularTwoDDistribution(
                                         const DistributionType& distribution )
    : ParentType( distribution )
  { /* ... */ }

  //! Constructor
  template<template<typename T, typename... Args> class ArrayA,
           template<typename T, typename... Args> class ArrayB>
  UnitAwareInterpolatedPartiallyTabularTwoDDistribution(
                   const ArrayA<PrimaryIndepQuantity>& primary_indep_grid,
                   const ArrayB<std::shared_ptr<const UnitAwareOneDDistribution<SecondaryIndependentUnit,DependentUnit> > >& secondary_distributions )
    : ParentType( primary_indep_grid, secondary_distributions )
  { /* ... */ }

  //! Destructor
  ~UnitAwareInterpolatedPartiallyTabularTwoDDistribution()
  { /* ... */ }
};

/*! \brief The interpolated partially tabular two-dimensional distribution
 * (unit-agnostic)
 * \ingroup two_d_distributions
 */
template<typename TwoDGridPolicy> using InterpolatedPartiallyTabularTwoDDistribution =
  UnitAwareInterpolatedPartiallyTabularTwoDDistribution<TwoDGridPolicy,void,void,void>;
  
} // end Utility namespace

#endif // end UTILITY_INTERPOLATED_PARTIALLY_TABULAR_TWO_D_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end Utility_InterpolatedPartiallyTabularTwoDDistribution.hpp
//---------------------------------------------------------------------------//
