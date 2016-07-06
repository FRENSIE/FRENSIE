//---------------------------------------------------------------------------//
//!
//! \file   Utility_GeneralTabularTwoDDistribution.hpp
//! \author Alex Robinson
//! \brief  The general tabular two-dimensional distribution class declaration
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_GENERAL_TABULAR_TWO_D_DISTRIBUTION_HPP
#define UTILITY_GENERAL_TABULAR_TWO_D_DISTRIBUTION_HPP

// FRENSIE Includes
#include "Utility_TabularTwoDDistribution.hpp"
#include "Utility_OneDDistribution.hpp"

namespace Utility{

/*! The unit-aware general tabular two-dimensional distribution
 * \ingroup two_d_distribution
 */
template<typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit>
class UnitAwareGeneralTabularTwoDDistribution : public UnitAwareTabularTwoDDistribution<PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit,UnitAwareOneDDistribution>
{

protected:

  //! The parent distribution type
  typedef UnitAwareTabularTwoDDistribution<PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit> ParentType;

  //! The base one-dimensional distribution type
  typedef typename ParentType::BaseOneDDistributionType BaseOneDDistributionType;

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
  typedef typename ParentType::InverseSecondaryIndepQuantity InverseSecondaryIndepQuantity

  //! The dependent quantity type
  typedef typename ParentType::DepQuantity DepQuantity;

  //! Constructor
  template<template<typename T, typename... Args> class Array>
  UnitAwareGeneralTabularTwoDDistribution( const Array<std::pair<PrimaryIndepQuantity,std::shared_ptr<const BaseOneDDistributionType> > >& distribution );

  //! Constructor
  template<template<typename T, typename... Args> class ArrayA,
           template<typename T, typename... Args> class ArrayB>
  UnitAwareGeneralTabularTwoDDistribution(
                const ArrayA<PrimaryIndepQuantity>& primary_indep_grid,
                const ArrayB<std::shared_ptr<const BaseOneDDistributionType> >&
                secondary_distributions );

  //! Destructor
  virtual ~UnitAwareGeneralTabularTwoDDistribution()
  { /* ... */ }
};

/*! The general tabular two-dimensional distribution (unit-agnostic)
 * \ingroup two_d_distributions
 */
typedef UnitAwareGeneralTabularTwoDDistribution<void,void,void> GeneralTabularTwoDDistribution;
  
} // end Utility namespace

#endif // end UTILITY_GENERAL_TABULAR_TWO_D_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end Utility_GeneralTabularTwoDDistribution.hpp
//---------------------------------------------------------------------------//
