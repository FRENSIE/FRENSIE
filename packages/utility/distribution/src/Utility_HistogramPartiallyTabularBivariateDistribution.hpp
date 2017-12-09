//---------------------------------------------------------------------------//
//!
//! \file   Utility_HistogramPartiallyTabularBivariateDistribution.hpp
//! \author Alex Robinson
//! \brief  The histogram partially tabular two-dimensional dist. class decl.
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_HISTOGRAM_PARTIALLY_TABULAR_TWO_D_DISTRIBUTION_HPP
#define UTILITY_HISTOGRAM_PARTIALLY_TABULAR_TWO_D_DISTRIBUTION_HPP

// FRENSIE Includes
#include "Utility_HistogramTabularBivariateDistributionImplBase.hpp"

namespace Utility{

/*! The unit-aware histogram partially tabular bivariate distribution
 * \ingroup bivariate_distributions
 */
template<typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit>
class UnitAwareHistogramPartiallyTabularBivariateDistribution : public UnitAwareHistogramTabularBivariateDistributionImplBase<UnitAwarePartiallyTabularBivariateDistribution<PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit> >
{
private:

  // The parent distribution type
  typedef UnitAwareHistogramTabularBivariateDistributionImplBase<UnitAwarePartiallyTabularBivariateDistribution<PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit> > ParentType;
  
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
  UnitAwareHistogramPartiallyTabularBivariateDistribution(
                                         const DistributionType& distribution )
    : ParentType( distribution )
  { /* ... */ }

  //! Constructor
  template<template<typename T, typename... Args> class ArrayA,
           template<typename T, typename... Args> class ArrayB>
  UnitAwareHistogramPartiallyTabularBivariateDistribution(
                   const ArrayA<PrimaryIndepQuantity>& primary_indep_grid,
                   const ArrayB<std::shared_ptr<const UnitAwareUnivariateDistribution<SecondaryIndependentUnit,DependentUnit> > >& secondary_distributions )
    : ParentType( primary_indep_grid, secondary_distributions )
  { /* ... */ }

  //! Destructor
  ~UnitAwareHistogramPartiallyTabularBivariateDistribution()
  { /* ... */ }
};

/*! The histogram tabular bivariate distribution (unit-agnostic)
 * \ingroup bivariate_distributions
 */
typedef UnitAwareHistogramPartiallyTabularBivariateDistribution<void,void,void> HistogramPartiallyTabularBivariateDistribution;
  
} // end Utility namespace

#endif // end UTILITY_HISTOGRAM_PARTIALLY_TABULAR_TWO_D_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end Utility_HistogramPartiallyTabularBivariateDistribution.hpp
//---------------------------------------------------------------------------//
