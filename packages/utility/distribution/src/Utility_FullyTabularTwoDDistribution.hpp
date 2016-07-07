//---------------------------------------------------------------------------//
//!
//! \file   Utility_FullyTabularTwoDDistribution.hpp
//! \author Alex Robinson
//! \brief  The fully tabular two-dimensional distribution class declaration
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_FULLY_TABULAR_TWO_D_DISTRIBUTION_HPP
#define UTILITY_FULLY_TABULAR_TWO_D_DISTRIBUTION_HPP

// FRENSIE Includes
#include "Utility_TabularTwoDDistribution.hpp"
#include "Utility_TabularOneDDistribution.hpp"

namespace Utility{

/*! The unit-aware fully tabular two-dimensional distribution
 * \ingroup two_d_distributions
 */
template<typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit>
class UnitAwareFullyTabularTwoDDistribution : public UnitAwareTabularTwoDDistribution<PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit,UnitAwareTabularOneDDistribution>
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
  UnitAwareFullyTabularTwoDDistribution( const Array<std::pair<PrimaryIndepQuantity,std::shared_ptr<const BaseOneDDistributionType> > >& distribution );

  //! Constructor
  template<template<typename T, typename... Args> class ArrayA,
           template<typename T, typename... Args> class ArrayB>
  UnitAwareFullyTabularTwoDDistribution(
                const ArrayA<PrimaryIndepQuantity>& primary_indep_grid,
                const ArrayB<std::shared_ptr<const BaseOneDDistributionType> >&
                secondary_distributions );

  //! Destructor
  virtual ~UnitAwareFullyTabularTwoDDistribution()
  { /* ... */ }

  //! Evaluate the secondary conditional CDF
  virtual double evaluateSecondaryConditionalCDF(
            const PrimaryIndepQuantity primary_indep_var_value,
            const SecondaryIndepQuantity secondary_indep_var_value ) const = 0;

  //! Return a random sample from the secondary conditional PDF and the index
  virtual SecondaryIndepQuantity sampleSecondaryConditionalAndRecordBinIndex(
                                       unsigned& sampled_bin_index ) const = 0;

  //! Return a random sample from the secondary conditional PDF at the CDF val
  virtual SecondaryIndepQuantity sampleSecondaryConditionalWithRandomNumber(
                                        const double random_number ) const = 0;

  //! Return a random sample from the secondary conditional PDF in the subrange
  virtual SecondaryIndepQuantity sampleSecondaryConditionalInSubrange(
        const SecondaryIndepQuantity max_secondary_indep_var_value ) const = 0;

  //! Return a random sample from the secondary conditional PDF in the subrange
  virtual SecondaryIndepQuantity sampleSecondaryConditionalWithRandomNumberInSubrange(
        const double random_number,
        const SecondaryIndepQuantity max_secondary_indep_var_value ) const = 0;
};

/*! The fully tabular two-dimensional distribution (unit-agnostic)
 * \ingroup two_d_distributions
 */
typedef UnitAwareFullyTabularTwoDDistribution<void,void,void> FullyTabularTwoDDistribution;
  
} // end utility namespace

#endif // end UTILITY_FULLY_TABULAR_TWO_D_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end Utility_FullyTabularTwoDDistribution.hpp
//---------------------------------------------------------------------------//
