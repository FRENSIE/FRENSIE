//---------------------------------------------------------------------------//
//!
//! \file   Utility_TabularBivariateDistribution.hpp
//! \author Alex Robinson
//! \brief  The tabular bivariate distribution class declaration
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_TABULAR_TWO_D_DISTRIBUTION_HPP
#define UTILITY_TABULAR_TWO_D_DISTRIBUTION_HPP

// Std Lib Includes
#include <memory>

// Trilinos Includes
#include <Teuchos_Array.hpp>

// FRENSIE Includes
#include "Utility_BivariateDistribution.hpp"
#include "Utility_UnivariateDistribution.hpp"
#include "Utility_QuantityTraits.hpp"
#include "Utility_Tuple.hpp"

namespace Utility{

/*! The unit-aware tabular bivariate distribution
 * \ingroup bivariate_distributions
 */
template<typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit,
         template<typename T, typename U> class BaseUnivariateDistribution>
class UnitAwareTabularBivariateDistribution : public UnitAwareBivariateDistribution<PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>
{

protected:

  //! The parent distribution type
  typedef UnitAwareBivariateDistribution<PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit> ParentType;

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

  //! The base univariate distribution type
  typedef BaseUnivariateDistribution<SecondaryIndependentUnit,DependentUnit> BaseUnivariateDistributionType;

  //! The secondary distribution type
  typedef Utility::Pair<PrimaryIndepQuantity,std::shared_ptr<const BaseUnivariateDistributionType> > PrimaryGridPointAndSecondaryDistPair;

  //! The distribution type
  typedef Teuchos::Array<PrimaryGridPointAndSecondaryDistPair> DistributionType;

  //! Constructor
  UnitAwareTabularBivariateDistribution( const DistributionType& distribution );

  //! Constructor
  template<template<typename T, typename... Args> class ArrayA,
           template<typename T, typename... Args> class ArrayB>
  UnitAwareTabularBivariateDistribution(
                const ArrayA<PrimaryIndepQuantity>& primary_indep_grid,
                const ArrayB<std::shared_ptr<const BaseUnivariateDistributionType> >&
                secondary_distributions );

  //! Destructor
  virtual ~UnitAwareTabularBivariateDistribution()
  { /* ... */ }

  //! Extend the distribution beyond the primary independent variable limits
  void extendBeyondPrimaryIndepLimits();

  //! Limit the distribution to the primary independent variable limits
  void limitToPrimaryIndepLimits();

  //! Check if the distribution is being extended beyond the primary limits
  bool arePrimaryLimitsExtended() const;

  //! Return the upper bound of the distribution primary independent variable
  PrimaryIndepQuantity getUpperBoundOfPrimaryIndepVar() const;

  //! Return the lower bound of the distribution primary independent variable
  PrimaryIndepQuantity getLowerBoundOfPrimaryIndepVar() const;

  //! Test if the distribution is tabular in the primary dimension
  bool isPrimaryDimensionTabular() const;

protected:

  //! Default constructor
  UnitAwareTabularBivariateDistribution()
  { /* ... */ }

  //! Set the distribution
  void setDistribution( const DistributionType distribution );

  //! Find the bin boundaries
  void findBinBoundaries(
         const PrimaryIndepQuantity primary_indep_var_value,
         typename DistributionType::const_iterator& lower_bin_boundary,
         typename DistributionType::const_iterator& upper_bin_boundary ) const;

  //! Calculate the index of the desired bin
  size_t calculateBinIndex(
               typename DistributionType::const_iterator& bin_boundary ) const;

  // Check that all secondary distributions are continuous
  bool areSecondaryDistributionsContinuous() const;

private:

  // The distribution
  DistributionType d_distribution;

  // Extend beyond primary limits
  bool d_extend_beyond_primary_limits;
};
  
} // end Utility namespace

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "Utility_TabularBivariateDistribution_def.hpp"

//---------------------------------------------------------------------------//

#endif // end UTILITY_TABULAR_TWO_D_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end Utility_TabularTwoDimensionalDistribution.hpp
//---------------------------------------------------------------------------//
