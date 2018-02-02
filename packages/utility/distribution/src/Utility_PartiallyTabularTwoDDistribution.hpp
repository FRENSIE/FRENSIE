//---------------------------------------------------------------------------//
//!
//! \file   Utility_PartiallyTabularTwoDDistribution.hpp
//! \author Alex Robinson
//! \brief  The partially tabular two-dimensional distribution class decl.
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_PARTIALLY_TABULAR_TWO_D_DISTRIBUTION_HPP
#define UTILITY_PARTIALLY_TABULAR_TWO_D_DISTRIBUTION_HPP

// FRENSIE Includes
#include "Utility_TabularTwoDDistribution.hpp"
#include "Utility_OneDDistribution.hpp"

namespace Utility{

/*! The unit-aware partially tabular two-dimensional distribution
 * \ingroup two_d_distribution
 */
template<typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit>
class UnitAwarePartiallyTabularTwoDDistribution : public UnitAwareTabularTwoDDistribution<PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit,UnitAwareOneDDistribution>
{

protected:

  //! The parent distribution type
  typedef UnitAwareTabularTwoDDistribution<PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit,UnitAwareOneDDistribution> ParentType;

  //! The base one-dimensional distribution type
  typedef typename ParentType::BaseOneDDistributionType BaseOneDDistributionType;

  //! Typedef for QuantityTraits<double>
  typedef QuantityTraits<double> QT;

  //! Typedef for QuantityTraits<PrimaryIndepQuantity>
  typedef QuantityTraits<typename ParentType::PrimaryIndepQuantity> PIQT;

  //! Typedef for QuantityTraits<SecondaryIndepQuantity>
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
  UnitAwarePartiallyTabularTwoDDistribution(
                                         const DistributionType& distribution )
    : ParentType( distribution )
  { /* .... */ }

  //! Constructor
  template<template<typename T, typename... Args> class ArrayA,
           template<typename T, typename... Args> class ArrayB>
  UnitAwarePartiallyTabularTwoDDistribution(
                const ArrayA<PrimaryIndepQuantity>& primary_indep_grid,
                const ArrayB<std::shared_ptr<const BaseOneDDistributionType> >&
                secondary_distributions )
    : ParentType( primary_indep_grid, secondary_distributions )
  { /* ... */ }

  //! Destructor
  virtual ~UnitAwarePartiallyTabularTwoDDistribution()
  { /* ... */ }
};

/*! The partially tabular two-dimensional distribution (unit-agnostic)
 * \ingroup two_d_distributions
 */
typedef UnitAwarePartiallyTabularTwoDDistribution<void,void,void> PartiallyTabularTwoDDistribution;

} // end Utility namespace

#endif // end UTILITY_PARTIALLY_TABULAR_TWO_D_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end Utility_PartiallyTabularTwoDDistribution.hpp
//---------------------------------------------------------------------------//
