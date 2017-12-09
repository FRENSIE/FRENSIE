//---------------------------------------------------------------------------//
//!
//! \file   Utility_PartiallyTabularBivariateDistribution.hpp
//! \author Alex Robinson
//! \brief  The partially tabular bivariate distribution class decl.
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_PARTIALLY_TABULAR_TWO_D_DISTRIBUTION_HPP
#define UTILITY_PARTIALLY_TABULAR_TWO_D_DISTRIBUTION_HPP

// FRENSIE Includes
#include "Utility_TabularBivariateDistribution.hpp"
#include "Utility_UnivariateDistribution.hpp"

namespace Utility{

/*! The unit-aware partially tabular bivariate distribution
 * \ingroup two_d_distribution
 */
template<typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit>
class UnitAwarePartiallyTabularBivariateDistribution : public UnitAwareTabularBivariateDistribution<PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit,UnitAwareUnivariateDistribution>
{

protected:

  //! The parent distribution type
  typedef UnitAwareTabularBivariateDistribution<PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit,UnitAwareUnivariateDistribution> ParentType;

  //! The base univariate distribution type
  typedef typename ParentType::BaseUnivariateDistributionType BaseUnivariateDistributionType;

  //! Typedef for QuantityTraits<double>
  typedef QuantityTraits<double> QT;

  //! Typedef for QuantityTraits<PrimaryIndepQuantity>
  typedef QuantityTraits<typename ParentType::PrimaryIndepQuantity> PIQT;

  //! Typddef for QuantityTraits<SecondaryIndepQuantity>
  typedef QuantityTraits<typename ParentType::SecondaryIndepQuantity> SIQT;

  //! Typedef for QuantityTriats<InverseSecondaryIndepQuantity>
  typedef QuantityTraits<typename ParentType::InverseSecondaryIndepQuantity> ISIQT;

  //! Typedef for QuantityTraits<DepQuantity>
  typedef QuantityTraits<typename ParentType::DepQuantity> DQT;

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
  UnitAwarePartiallyTabularBivariateDistribution(
                                         const DistributionType& distribution )
    : ParentType( distribution )
  { /* .... */ }

  //! Constructor
  template<template<typename T, typename... Args> class ArrayA,
           template<typename T, typename... Args> class ArrayB>
  UnitAwarePartiallyTabularBivariateDistribution(
                const ArrayA<PrimaryIndepQuantity>& primary_indep_grid,
                const ArrayB<std::shared_ptr<const BaseUnivariateDistributionType> >&
                secondary_distributions )
    : ParentType( primary_indep_grid, secondary_distributions )
  { /* ... */ }

  //! Destructor
  virtual ~UnitAwarePartiallyTabularBivariateDistribution()
  { /* ... */ }
};

/*! The partially tabular bivariate distribution (unit-agnostic)
 * \ingroup bivariate_distributions
 */
typedef UnitAwarePartiallyTabularBivariateDistribution<void,void,void> PartiallyTabularBivariateDistribution;
  
} // end Utility namespace

#endif // end UTILITY_PARTIALLY_TABULAR_TWO_D_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end Utility_PartiallyTabularBivariateDistribution.hpp
//---------------------------------------------------------------------------//
