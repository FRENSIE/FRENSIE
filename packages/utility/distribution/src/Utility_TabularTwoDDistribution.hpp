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
#include <vector>
#include <utility>

// FRENSIE Includes
#include "Utility_TwoDDistribution.hpp"
#include "Utility_OneDDistribution.hpp"
#include "Utility_QuantityTraits.hpp"

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

  //! The base one-dimensional distribution type
  typedef BaseOneDDistribution<SecondaryIndependentUnit,DependentUnit> BaseOneDDistributionType;

  //! The secondary distribution type
  typedef std::pair<PrimaryIndepQuantity,std::shared_ptr<const BaseOneDDistributionType> > PrimaryGridPointAndSecondaryDistPair;

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
  UnitAwareTabularTwoDDistribution( const Array<std::pair<PrimaryIndepQuantity,std::shared_ptr<const BaseOneDDistributionType> > >& distribution );

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

private:

  // The distribution type
  typedef std::vector<PrimaryGridPointAndSecondaryDistPair> DistributionType;

  // Find the bin boundaries
  void findBinBoundaries(
            const PrimaryIndepQuantity independent_var_value,
            PrimaryGridPointAndSecondaryDistPair& lower_bin_boundary,
            PrimaryGridPointAndSecondaryDistPair& upper_bin_boundary,
            double& interpolation_fraction ) const;

  // The distribution
  DistributionType d_distribution;
};
  
} // end Utility namespace

#endif // end UTILITY_TABULAR_TWO_D_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end Utility_TabularTwoDimensionalDistribution.hpp
//---------------------------------------------------------------------------//
