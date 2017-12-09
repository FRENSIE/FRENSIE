//---------------------------------------------------------------------------//
//!
//! \file   Utility_HistogramFullyTabularBivariateDistribution.hpp
//! \author Alex Robinson
//! \brief  The histogram fully tabular two-dimensional dist. class decl.
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_HISTOGRAM_FULLY_TABULAR_TWO_D_DISTRIBUTION_HPP
#define UTILITY_HISTOGRAM_FULLY_TABULAR_TWO_D_DISTRIBUTION_HPP

// FRENSIE Includes
#include "Utility_HistogramTabularBivariateDistributionImplBase.hpp"

namespace Utility{

/*! The unit-aware histogram fully tabular bivariate distribution
 * \ingroup bivariate_distributions
 */
template<typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit>
class UnitAwareHistogramFullyTabularBivariateDistribution : public UnitAwareHistogramTabularBivariateDistributionImplBase<UnitAwareFullyTabularBivariateDistribution<PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit> >
{

private:

  // The parent distribution type
  typedef UnitAwareHistogramTabularBivariateDistributionImplBase<UnitAwareFullyTabularBivariateDistribution<PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit> > ParentType;

  // The base univariate distribution type
  typedef typename ParentType::BaseUnivariateDistributionType BaseUnivariateDistributionType;

  // Typedef for QuantityTraits<double>
  typedef typename ParentType::QT QT;

  // Typedef for QuantityTraits<PrimaryIndepQuantity>
  typedef typename ParentType::PIQT PIQT;

  // Typddef for QuantityTraits<SecondaryIndepQuantity>
  typedef typename ParentType::SIQT SIQT;

  // Typedef for QuantityTriats<InverseSecondaryIndepQuantity>
  typedef typename ParentType::ISIQT ISIQT;

  // Typedef for QuantityTraits<DepQuantity>
  typedef typename ParentType::DQT DQT;
  
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
  UnitAwareHistogramFullyTabularBivariateDistribution(
                                         const DistributionType& distribution )
    : ParentType( distribution )
  { /* ... */ }

  //! Constructor
  template<template<typename T, typename... Args> class ArrayA,
           template<typename T, typename... Args> class ArrayB>
  UnitAwareHistogramFullyTabularBivariateDistribution(
                   const ArrayA<PrimaryIndepQuantity>& primary_indep_grid,
                   const ArrayB<std::shared_ptr<const UnitAwareTabularUnivariateDistribution<SecondaryIndependentUnit,DependentUnit> > >& secondary_distributions )
    : ParentType( primary_indep_grid, secondary_distributions )
  { /* ... */ }

  //! Destructor
  ~UnitAwareHistogramFullyTabularBivariateDistribution()
  { /* ... */ }

  //! Evaluate the secondary conditional CDF
  double evaluateSecondaryConditionalCDF(
                const PrimaryIndepQuantity primary_indep_var_value,
                const SecondaryIndepQuantity secondary_indep_var_value ) const;

  //! Return a random sample from the secondary conditional PDF and the index
  SecondaryIndepQuantity sampleSecondaryConditionalAndRecordBinIndices(
                            const PrimaryIndepQuantity primary_indep_var_value,
                            unsigned& primary_bin_index,
                            unsigned& secondary_bin_index ) const;

  //! Return a random sample from the secondary conditional PDF at the CDF val
  SecondaryIndepQuantity sampleSecondaryConditionalWithRandomNumber(
                            const PrimaryIndepQuantity primary_indep_var_value,
                            const double random_number ) const;

  //! Return a random sample from the secondary conditional PDF in the subrange
  SecondaryIndepQuantity sampleSecondaryConditionalInSubrange(
            const PrimaryIndepQuantity primary_indep_var_value,
            const SecondaryIndepQuantity max_secondary_indep_var_value ) const;

  //! Return a random sample from the secondary conditional PDF in the subrange
  SecondaryIndepQuantity sampleSecondaryConditionalWithRandomNumberInSubrange(
            const PrimaryIndepQuantity primary_indep_var_value,
            const double random_number,
            const SecondaryIndepQuantity max_secondary_indep_var_value ) const;
};

/*! The histogram fully tabular bivariate distribution (unit-agnostic)
 * \ingroup bivariate_distributions
 */
typedef UnitAwareHistogramFullyTabularBivariateDistribution<void,void,void> HistogramFullyTabularBivariateDistribution;
  
} // end Utility namespace

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "Utility_HistogramFullyTabularBivariateDistribution_def.hpp"

//---------------------------------------------------------------------------//

#endif // end UTILITY_HISTOGRAM_FULLY_TABULAR_TWO_D_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end Utility_HistogramFullyTabularBivariateDistribution.hpp
//---------------------------------------------------------------------------//
