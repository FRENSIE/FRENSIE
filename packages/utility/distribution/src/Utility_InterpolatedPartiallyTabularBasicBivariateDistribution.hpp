//---------------------------------------------------------------------------//
//!
//! \file   Utility_InterpolatedPartiallyTabularBivariateDistribution.hpp
//! \author Alex Robinson
//! \brief  The interpolated partially tabular two-d dist. class decl.
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_INTERPOLATED_PARTIALLY_TABULAR_TWO_D_DISTRIBUTION_HPP
#define UTILITY_INTERPOLATED_PARTIALLY_TABULAR_TWO_D_DISTRIBUTION_HPP

// FRENSIE Includes
#include "Utility_InterpolatedTabularBivariateDistributionImplBase.hpp"

namespace Utility{

/*! The unit-aware interpolated partially tabular two_dimensional distribution
 * \ingroup bivariate_distributions
 */
template<typename TwoDInterpPolicy,
         typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit>
class UnitAwareInterpolatedPartiallyTabularBivariateDistribution : public UnitAwareInterpolatedTabularBivariateDistributionImplBase<TwoDInterpPolicy,UnitAwarePartiallyTabularBivariateDistribution<PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit> >
{

private:

  // The parent distribution type
  typedef UnitAwareInterpolatedTabularBivariateDistributionImplBase<TwoDInterpPolicy,UnitAwarePartiallyTabularBivariateDistribution<PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit> > ParentType;
  
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
  UnitAwareInterpolatedPartiallyTabularBivariateDistribution(
                                         const DistributionType& distribution )
    : ParentType( distribution )
  { /* ... */ }

  //! Constructor
  template<template<typename T, typename... Args> class ArrayA,
           template<typename T, typename... Args> class ArrayB>
  UnitAwareInterpolatedPartiallyTabularBivariateDistribution(
                   const ArrayA<PrimaryIndepQuantity>& primary_indep_grid,
                   const ArrayB<std::shared_ptr<const UnitAwareUnivariateDistribution<SecondaryIndependentUnit,DependentUnit> > >& secondary_distributions )
    : ParentType( primary_indep_grid, secondary_distributions )
  { /* ... */ }

  //! Destructor
  ~UnitAwareInterpolatedPartiallyTabularBivariateDistribution()
  { /* ... */ }
};

/*! \brief The interpolated partially tabular bivariate distribution 
 * (unit-agnostic)
 * \ingroup bivariate_distributions
 */
template<typename TwoDInterpPolicy> using InterpolatedPartiallyTabularBivariateDistribution =
  UnitAwareInterpolatedPartiallyTabularBivariateDistribution<TwoDInterpPolicy,void,void,void>;
  
} // end Utility namespace

#endif // end UTILITY_INTERPOLATED_PARTIALLY_TABULAR_TWO_D_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end Utility_InterpolatedPartiallyTabularBivariateDistribution.hpp
//---------------------------------------------------------------------------//
