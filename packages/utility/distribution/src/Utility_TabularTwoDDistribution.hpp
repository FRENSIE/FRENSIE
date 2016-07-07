//---------------------------------------------------------------------------//
//!
//! \file   Utility_TabularTwoDDistribution.hpp
//! \author Alex Robinson
//! \brief  The tabular two-dimensional distribution class declaration
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_TABULAR_TWO_D_DISTRIBUTION_HPP
#define UTILITY_TABULAR_TWO_D_DISTRIBUTION_HPP

// Std Lib Includes
#include <memory>

// Trilinos Includes
#include <Teuchos_Array.hpp>

// FRENSIE Includes
#include "Utility_TwoDDistribution.hpp"
#include "Utility_OneDDistribution.hpp"
#include "Utility_QuantityTraits.hpp"
#include "Utility_Tuple.hpp"

namespace Utility{

/*! The unit-aware tabular two-dimensional distribution
 * \ingroup two_d_distributions
 */
template<typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit,
         template<typename T, typename U> class BaseOneDDistribution>
class UnitAwareTabularTwoDDistribution : public UnitAwareTwoDDistribution<PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>
{

protected:

  //! The parent distribution type
  typedef UnitAwareTwoDDistribution<PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit> ParentType;

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

  //! The base one-dimensional distribution type
  typedef BaseOneDDistribution<SecondaryIndependentUnit,DependentUnit> BaseOneDDistributionType;

  //! The secondary distribution type
  typedef Utility::Pair<PrimaryIndepQuantity,std::shared_ptr<const BaseOneDDistributionType> > PrimaryGridPointAndSecondaryDistPair;

  //! The distribution type
  typedef Teuchos::Array<PrimaryGridPointAndSecondaryDistPair> DistributionType;

  //! Constructor
  UnitAwareTabularTwoDDistribution( const DistributionType& distribution );

  //! Constructor
  template<template<typename T, typename... Args> class ArrayA,
           template<typename T, typename... Args> class ArrayB>
  UnitAwareTabularTwoDDistribution(
                const ArrayA<PrimaryIndepQuantity>& primary_indep_grid,
                const ArrayB<std::shared_ptr<const BaseOneDDistributionType> >&
                secondary_distributions );

  //! Destructor
  virtual ~UnitAwareTabularTwoDDistribution()
  { /* ... */ }

  //! Return the upper bound of the distribution primary independent variable
  PrimaryIndepQuantity getUpperBoundOfPrimaryIndepVar() const;

  //! Return the lower bound of the distribution primary independent variable
  PrimaryIndepQuantity getLowerBoundOfPrimaryIndepVar() const;

  //! Test if the distribution is tabular in the primary dimension
  bool isPrimaryDimensionTabular() const;

protected:

  // Find the bin boundaries
  void findBinBoundaries(
         const PrimaryIndepQuantity primary_indep_var_value,
         typename DistributionType::const_iterator& lower_bin_boundary,
         typename DistributionType::const_iterator& upper_bin_boundary ) const;

  // Calculate the interpolation fraction
  double calculateInterpolationFraction(
   const PrimaryIndepQuantity primary_indep_var_value,
   const typename DistributionType::const_iterator& lower_bin_boundary,
   const typename DistributionType::const_iterator& upper_bin_boundary ) const;

private:

  // The distribution
  DistributionType d_distribution;
};
  
} // end Utility namespace

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "Utility_TabularTwoDDistribution_def.hpp"

//---------------------------------------------------------------------------//

#endif // end UTILITY_TABULAR_TWO_D_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end Utility_TabularTwoDimensionalDistribution.hpp
//---------------------------------------------------------------------------//
