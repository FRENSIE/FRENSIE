//---------------------------------------------------------------------------//
//!
//! \file   Utility_HistogramFullyTabularTwoDDistribution.hpp
//! \author Alex Robinson
//! \brief  The histogram fully tabular two-dimensional dist. class decl.
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_HISTOGRAM_FULLY_TABULAR_TWO_D_DISTRIBUTION_HPP
#define UTILITY_HISTOGRAM_FULLY_TABULAR_TWO_D_DISTRIBUTION_HPP

// FRENSIE Includes
#include "Utility_HistogramFullyTabularTwoDDistribution.hpp"

namespace Utility{

/*! The unit-aware histogram fully tabular two-dimensional distribution
 * \ingroup two_d_distributions
 */
template<typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit>
class UnitAwareHistogramFullyTabularTwoDDistribution : public UnitAwareHistogramTabularTwoDDistributionImpl<PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit,true>
{
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
  UnitAwareHistogramFullyTabularTwoDDistribution( const Array<std::pair<PrimaryIndepQuantity,std::shared_ptr<const UnitAwareTabularOneDDistribution<SecondaryIndependentUnit,DependentUnit> > > >& distribution )
    : UnitAwareHistogramTabularTwoDDistributionImpl<PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit,true>( distribution )
  { /* ... */ }

  //! Constructor
  template<template<typename T, typename... Args> class ArrayA,
           template<typename T, typename... Args> class ArrayB>
  UnitAwareHistogramFullyTabularTwoDDistribution(
                   const ArrayA<PrimaryIndepQuantity>& primary_indep_grid,
                   const ArrayB<std::shared_ptr<const UnitAwareTabularOneDDistribution<SecondaryIndependentUnit,DependentUnit> > >& secondary_distributions )
    : UnitAwareHistogramTabularTwoDDistributionImpl<PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit,true>( primary_indep_grid, secondary_distributions )
  { /* ... */ }

  //! Destructor
  ~UnitAwareHistogramFullyTabularTwoDDistribution()
  { /* ... */ }
};

/*! The histogram tabular two-dimensional distribution (unit-agnostic)
 * \ingroup two_d_distributions
 */
typedef UnitAwareHistogramFullyTabularTwoDDistribution<void,void,void> HistogramFullyTabularTwoDDistribution;
  
} // end Utility namespace

#endif // end UTILITY_HISTOGRAM_FULLY_TABULAR_TWO_D_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end Utility_HistogramFullyTabularTwoDDistribution.hpp
//---------------------------------------------------------------------------//
