//---------------------------------------------------------------------------//
//!
//! \file   Utility_FullyTabularBivariateDistribution.hpp
//! \author Alex Robinson
//! \brief  The fully tabular bivariate distribution class declaration
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_FULLY_TABULAR_TWO_D_DISTRIBUTION_HPP
#define UTILITY_FULLY_TABULAR_TWO_D_DISTRIBUTION_HPP

// FRENSIE Includes
#include "Utility_TabularBivariateDistribution.hpp"
#include "Utility_TabularUnivariateDistribution.hpp"

namespace Utility{

/*! The unit-aware fully tabular bivariate distribution
 * \ingroup bivariate_distributions
 */
template<typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit>
class UnitAwareFullyTabularBivariateDistribution : public UnitAwareTabularBivariateDistribution<PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit,UnitAwareTabularUnivariateDistribution>
{

protected:

  //! The parent distribution type
  typedef UnitAwareTabularBivariateDistribution<PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit,UnitAwareTabularUnivariateDistribution> ParentType;

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
  UnitAwareFullyTabularBivariateDistribution( const DistributionType& distribution )
    : ParentType( distribution )
  { /* ... */ }

  //! Constructor
  template<template<typename T, typename... Args> class ArrayA,
           template<typename T, typename... Args> class ArrayB>
  UnitAwareFullyTabularBivariateDistribution(
                const ArrayA<PrimaryIndepQuantity>& primary_indep_grid,
                const ArrayB<std::shared_ptr<const BaseUnivariateDistributionType> >&
                secondary_distributions )
    : ParentType( primary_indep_grid, secondary_distributions )
  { /* ... */ }

  //! Destructor
  virtual ~UnitAwareFullyTabularBivariateDistribution()
  { /* ... */ }

  //! Evaluate the secondary conditional CDF
  virtual double evaluateSecondaryConditionalCDF(
            const PrimaryIndepQuantity primary_indep_var_value,
            const SecondaryIndepQuantity secondary_indep_var_value ) const = 0;

  //! Return a random sample from the secondary conditional PDF 
  virtual SecondaryIndepQuantity sampleSecondaryConditionalExact(
                    const PrimaryIndepQuantity primary_indep_var_value ) const;

  //! Return a random sample from the secondary conditional PDF and the index
  virtual SecondaryIndepQuantity sampleSecondaryConditionalAndRecordBinIndices(
                            const PrimaryIndepQuantity primary_indep_var_value,
                            unsigned& primary_bin_index,
                            unsigned& secondary_bin_index ) const = 0;

  //! Return a random sample from the secondary conditional PDF and the index
  virtual SecondaryIndepQuantity sampleSecondaryConditionalAndRecordBinIndices(
                            const PrimaryIndepQuantity primary_indep_var_value,
                            SecondaryIndepQuantity& raw_sample,
                            unsigned& primary_bin_index,
                            unsigned& secondary_bin_index ) const;

  //! Return a random sample from the secondary conditional PDF at the CDF val
  virtual SecondaryIndepQuantity sampleSecondaryConditionalWithRandomNumber(
                            const PrimaryIndepQuantity primary_indep_var_value,
                            const double random_number ) const = 0;

  //! Return a random sample from the secondary conditional PDF at the CDF val
  virtual SecondaryIndepQuantity sampleSecondaryConditionalExactWithRandomNumber(
                            const PrimaryIndepQuantity primary_indep_var_value,
                            const double random_number ) const;

  //! Return a random sample from the secondary conditional PDF in the subrange
  virtual SecondaryIndepQuantity sampleSecondaryConditionalInSubrange(
        const PrimaryIndepQuantity primary_indep_var_value,
        const SecondaryIndepQuantity max_secondary_indep_var_value ) const = 0;

  //! Return a random sample from the secondary conditional PDF in the subrange
  virtual SecondaryIndepQuantity sampleSecondaryConditionalExactInSubrange(
            const PrimaryIndepQuantity primary_indep_var_value,
            const SecondaryIndepQuantity max_secondary_indep_var_value ) const;

  //! Return a random sample from the secondary conditional PDF in the subrange
  virtual SecondaryIndepQuantity sampleSecondaryConditionalWithRandomNumberInSubrange(
        const PrimaryIndepQuantity primary_indep_var_value,
        const double random_number,
        const SecondaryIndepQuantity max_secondary_indep_var_value ) const = 0;

  //! Return a random sample from the secondary conditional PDF in the subrange
  virtual SecondaryIndepQuantity sampleSecondaryConditionalExactWithRandomNumberInSubrange(
            const PrimaryIndepQuantity primary_indep_var_value,
            const double random_number,
            const SecondaryIndepQuantity max_secondary_indep_var_value ) const;

protected:

  //! Default constructor
  UnitAwareFullyTabularBivariateDistribution()
  { /* ... */ }
};

// Return a random sample from the secondary conditional PDF
/*! \details There are often multiple ways to sample from two-dimensional
 * distributions (e.g. stochastic and correlated sampling). Ideally the 
 * "non-exact" method will be faster and stochastically correct.
 */
template<typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit>
inline auto UnitAwareFullyTabularBivariateDistribution<PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>::sampleSecondaryConditionalExact(
                     const PrimaryIndepQuantity primary_indep_var_value ) const
  -> SecondaryIndepQuantity
{
  return this->sampleSecondaryConditional( primary_indep_var_value );
}

// Return a random sample from the secondary conditional PDF and the index
/*! \details When the secondary conditional sampling method is stochastic it
 * is common to sample from one of the distributions on the bin boundaries
 * and then to scale the sample so that it preserves intermediate grid limits.
 * Certain methods require the unscaled (or raw) sample, which can be 
 * acquired with this method.
 */
template<typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit>
inline auto UnitAwareFullyTabularBivariateDistribution<PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>::sampleSecondaryConditionalAndRecordBinIndices(
                            const PrimaryIndepQuantity primary_indep_var_value,
                            SecondaryIndepQuantity& raw_sample,
                            unsigned& primary_bin_index,
                            unsigned& secondary_bin_index ) const
  -> SecondaryIndepQuantity
{
  raw_sample = this->sampleSecondaryConditionalAndRecordBinIndices(
                                                       primary_indep_var_value,
                                                       primary_bin_index,
                                                       secondary_bin_index );

  return raw_sample;
}

// Return a random sample from the secondary conditional PDF at the CDF val
/*! \details There are often multiple ways to sample from two-dimensional
 * distributions (e.g. stochastic and correlated sampling). Ideally the 
 * "non-exact" method will be faster and stochastically correct.
 */
template<typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit>
inline auto UnitAwareFullyTabularBivariateDistribution<PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>::sampleSecondaryConditionalExactWithRandomNumber(
                            const PrimaryIndepQuantity primary_indep_var_value,
                            const double random_number ) const
  -> SecondaryIndepQuantity
{
  return this->sampleSecondaryConditionalWithRandomNumber(
                                      primary_indep_var_value, random_number );
}

// Return a random sample from the secondary conditional PDF in the subrange
/*! \details There are often multiple ways to sample from two-dimensional
 * distributions (e.g. stochastic and correlated sampling). Ideally the 
 * "non-exact" method will be faster and stochastically correct.
 */
template<typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit>
inline auto UnitAwareFullyTabularBivariateDistribution<PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>::sampleSecondaryConditionalExactInSubrange(
            const PrimaryIndepQuantity primary_indep_var_value,
            const SecondaryIndepQuantity max_secondary_indep_var_value ) const
  -> SecondaryIndepQuantity
{
  return this->sampleSecondaryConditionalInSubrange(
                                               primary_indep_var_value,
                                               max_secondary_indep_var_value );
}

// Return a random sample from the secondary conditional PDF in the subrange
/*! \details There are often multiple ways to sample from two-dimensional
 * distributions (e.g. stochastic and correlated sampling). Ideally the 
 * "non-exact" method will be faster and stochastically correct.
 */
template<typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit>
inline auto UnitAwareFullyTabularBivariateDistribution<PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>::sampleSecondaryConditionalExactWithRandomNumberInSubrange(
            const PrimaryIndepQuantity primary_indep_var_value,
            const double random_number,
            const SecondaryIndepQuantity max_secondary_indep_var_value ) const
  -> SecondaryIndepQuantity
{
  return this->sampleSecondaryConditionalWithRandomNumberInSubrange(
                                               primary_indep_var_value,
                                               random_number,
                                               max_secondary_indep_var_value );
}

/*! The fully tabular bivariate distribution (unit-agnostic)
 * \ingroup bivariate_distributions
 */
typedef UnitAwareFullyTabularBivariateDistribution<void,void,void> FullyTabularBivariateDistribution;
  
} // end utility namespace

#endif // end UTILITY_FULLY_TABULAR_TWO_D_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end Utility_FullyTabularBivariateDistribution.hpp
//---------------------------------------------------------------------------//
