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
#include "Utility_RandomNumberGenerator.hpp"

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
  typedef UnitAwareTabularTwoDDistribution<PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit,UnitAwareTabularOneDDistribution> ParentType;

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
  typedef typename ParentType::InverseSecondaryIndepQuantity InverseSecondaryIndepQuantity;

  //! The dependent quantity type
  typedef typename ParentType::DepQuantity DepQuantity;

  //! The distribution type
  typedef typename ParentType::DistributionType DistributionType;

  //! Constructor
  UnitAwareFullyTabularTwoDDistribution( const DistributionType& distribution )
    : ParentType( distribution )
  { /* ... */ }

  //! Constructor
  template<template<typename T, typename... Args> class ArrayA,
           template<typename T, typename... Args> class ArrayB>
  UnitAwareFullyTabularTwoDDistribution(
                const ArrayA<PrimaryIndepQuantity>& primary_indep_grid,
                const ArrayB<std::shared_ptr<const BaseOneDDistributionType> >&
                secondary_distributions )
    : ParentType( primary_indep_grid, secondary_distributions )
  { /* ... */ }

  //! Destructor
  virtual ~UnitAwareFullyTabularTwoDDistribution()
  { /* ... */ }

 //! Correlated evaluate the distribution (Unit Based)
  virtual DepQuantity correlatedEvaluate(
        const PrimaryIndepQuantity primary_indep_var_value,
        const SecondaryIndepQuantity secondary_indep_var_value,
        const SecondaryIndepQuantity min_secondary_indep_var_value,
        const SecondaryIndepQuantity max_secondary_indep_var_value ) const = 0;

  //! Evaluate the distribution
  virtual DepQuantity evaluateExact(
        const PrimaryIndepQuantity primary_indep_var_value,
        const SecondaryIndepQuantity secondary_indep_var_value ) const = 0;

  //! Correlated evaluate the secondary conditional PDF (Unit Based)
  virtual InverseSecondaryIndepQuantity correlatedEvaluateSecondaryConditionalPDF(
        const PrimaryIndepQuantity primary_indep_var_value,
        const SecondaryIndepQuantity secondary_indep_var_value,
        const SecondaryIndepQuantity min_secondary_indep_var_value,
        const SecondaryIndepQuantity max_secondary_indep_var_value ) const = 0;

  //! Evaluate the secondary conditional PDF
  virtual InverseSecondaryIndepQuantity evaluateSecondaryConditionalPDFExact(
        const PrimaryIndepQuantity primary_indep_var_value,
        const SecondaryIndepQuantity secondary_indep_var_value ) const = 0;

  //! Evaluate the secondary conditional CDF
  virtual double evaluateSecondaryConditionalCDF(
        const PrimaryIndepQuantity primary_indep_var_value,
        const SecondaryIndepQuantity secondary_indep_var_value ) const = 0;

  //! Correlated evaluate the secondary conditional CDF
  virtual double correlatedEvaluateSecondaryConditionalCDF(
        const PrimaryIndepQuantity primary_indep_var_value,
        const SecondaryIndepQuantity secondary_indep_var_value,
        const SecondaryIndepQuantity min_secondary_indep_var_value,
        const SecondaryIndepQuantity max_secondary_indep_var_value ) const = 0;

  //! Evaluate the secondary conditional CDF
  virtual double evaluateSecondaryConditionalCDFExact(
        const PrimaryIndepQuantity primary_indep_var_value,
        const SecondaryIndepQuantity secondary_indep_var_value ) const = 0;

  //! Return a random correlated sample from the secondary conditional PDF
  virtual SecondaryIndepQuantity correlatedSampleSecondaryConditional(
        const PrimaryIndepQuantity primary_indep_var_value,
        const SecondaryIndepQuantity min_secondary_indep_var_value,
        const SecondaryIndepQuantity max_secondary_indep_var_value ) const;

  //! Return a random sample from the secondary conditional PDF
  virtual SecondaryIndepQuantity sampleSecondaryConditionalExact(
        const PrimaryIndepQuantity primary_indep_var_value ) const;

  //! Return a random sample from the secondary conditional PDF at the CDF val
  virtual SecondaryIndepQuantity sampleSecondaryConditionalWithRandomNumber(
                    const PrimaryIndepQuantity primary_indep_var_value,
                    const double random_number ) const = 0;

  //! Return a random correlated sample from the secondary conditional PDF at the CDF val
  virtual SecondaryIndepQuantity correlatedSampleSecondaryConditionalWithRandomNumber(
                    const PrimaryIndepQuantity primary_indep_var_value,
                    const SecondaryIndepQuantity min_secondary_indep_var_value,
                    const SecondaryIndepQuantity max_secondary_indep_var_value,
                    const double random_number ) const;

  //! Return a random sample from the secondary conditional PDF at the CDF val
  virtual SecondaryIndepQuantity sampleSecondaryConditionalExactWithRandomNumber(
                    const PrimaryIndepQuantity primary_indep_var_value,
                    const double random_number ) const;

  //! Return a random sample from the secondary conditional PDF in the subrange
  virtual SecondaryIndepQuantity sampleSecondaryConditionalInSubrange(
        const PrimaryIndepQuantity primary_indep_var_value,
        const SecondaryIndepQuantity max_secondary_indep_var_value ) const = 0;

  //! Return a random correlated sample from the secondary conditional PDF in the subrange
  virtual SecondaryIndepQuantity correlatedSampleSecondaryConditionalInSubrange(
        const PrimaryIndepQuantity primary_indep_var_value,
        const SecondaryIndepQuantity min_secondary_indep_var_value,
        const SecondaryIndepQuantity max_secondary_indep_var_value ) const;

  //! Return a random sample from the secondary conditional PDF in the subrange
  virtual SecondaryIndepQuantity sampleSecondaryConditionalExactInSubrange(
        const PrimaryIndepQuantity primary_indep_var_value,
        const SecondaryIndepQuantity max_secondary_indep_var_value ) const;

  //! Return a random sample from the secondary conditional PDF in the subrange
  virtual SecondaryIndepQuantity sampleSecondaryConditionalWithRandomNumberInSubrange(
        const PrimaryIndepQuantity primary_indep_var_value,
        const double random_number,
        const SecondaryIndepQuantity max_secondary_indep_var_value ) const = 0;

  //! Return a random correlated sample from the secondary conditional PDF in the subrange
  virtual SecondaryIndepQuantity correlatedSampleSecondaryConditionalWithRandomNumberInSubrange(
        const PrimaryIndepQuantity primary_indep_var_value,
        const double random_number,
        const SecondaryIndepQuantity min_secondary_indep_var_value,
        const SecondaryIndepQuantity max_secondary_indep_var_value ) const;

  //! Return a random sample from the secondary conditional PDF in the subrange
  virtual SecondaryIndepQuantity sampleSecondaryConditionalExactWithRandomNumberInSubrange(
        const PrimaryIndepQuantity primary_indep_var_value,
        const double random_number,
        const SecondaryIndepQuantity max_secondary_indep_var_value ) const;

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

protected:

  //! Default constructor
  UnitAwareFullyTabularTwoDDistribution()
  { /* ... */ }
};

// Return a random correlated sample from the secondary conditional PDF
/*! \details There are often multiple ways to sample from two-dimensional
 * distributions (e.g. stochastic and correlated sampling). A correlated unit
 * based sampling is performed.
 */
template<typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit>
inline auto UnitAwareFullyTabularTwoDDistribution<PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>::correlatedSampleSecondaryConditional(
        const PrimaryIndepQuantity primary_indep_var_value,
        const SecondaryIndepQuantity min_secondary_indep_var_value,
        const SecondaryIndepQuantity max_secondary_indep_var_value ) const
  -> SecondaryIndepQuantity
{
  double random_number = RandomNumberGenerator::getRandomNumber<double>();

  return this->correlatedSampleSecondaryConditionalWithRandomNumber(
                                                primary_indep_var_value,
                                                min_secondary_indep_var_value,
                                                max_secondary_indep_var_value,
                                                random_number );
}

// Return a random sample from the secondary conditional PDF
/*! \details There are often multiple ways to sample from two-dimensional
 * distributions (e.g. stochastic and correlated sampling). Ideally the
 * "non-exact" method will be faster and stochastically correct.
 */
template<typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit>
inline auto UnitAwareFullyTabularTwoDDistribution<PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>::sampleSecondaryConditionalExact(
                     const PrimaryIndepQuantity primary_indep_var_value ) const
  -> SecondaryIndepQuantity
{
  return this->sampleSecondaryConditional( primary_indep_var_value );
}

// Return a random sample from the secondary conditional PDF at the CDF val
/*! \details There are often multiple ways to sample from two-dimensional
 * distributions (e.g. stochastic and correlated sampling). Ideally the
 * "non-exact" method will be faster and stochastically correct.
 */
template<typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit>
inline auto UnitAwareFullyTabularTwoDDistribution<PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>::correlatedSampleSecondaryConditionalWithRandomNumber(
        const PrimaryIndepQuantity primary_indep_var_value,
        const SecondaryIndepQuantity min_secondary_indep_var_value,
        const SecondaryIndepQuantity max_secondary_indep_var_value,
        const double random_number ) const
  -> SecondaryIndepQuantity
{
  return this->sampleSecondaryConditionalWithRandomNumber(
                                      primary_indep_var_value, random_number );
}

// Return a random sample from the secondary conditional PDF at the CDF val
/*! \details There are often multiple ways to sample from two-dimensional
 * distributions (e.g. stochastic and correlated sampling). Ideally the
 * "non-exact" method will be faster and stochastically correct.
 */
template<typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit>
inline auto UnitAwareFullyTabularTwoDDistribution<PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>::sampleSecondaryConditionalExactWithRandomNumber(
                            const PrimaryIndepQuantity primary_indep_var_value,
                            const double random_number ) const
  -> SecondaryIndepQuantity
{
  return this->sampleSecondaryConditionalWithRandomNumber(
                                      primary_indep_var_value, random_number );
}

// Return a random correlated sample from the secondary conditional PDF in the subrange
/*! \details There are often multiple ways to sample from two-dimensional
 * distributions (e.g. stochastic and correlated sampling). A correlated unit
 * based sampling is performed in a subrange.
 */
template<typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit>
inline auto UnitAwareFullyTabularTwoDDistribution<PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>::correlatedSampleSecondaryConditionalInSubrange(
        const PrimaryIndepQuantity primary_indep_var_value,
        const SecondaryIndepQuantity min_secondary_indep_var_value,
        const SecondaryIndepQuantity max_secondary_indep_var_value ) const
  -> SecondaryIndepQuantity
{
  double random_number = RandomNumberGenerator::getRandomNumber<double>();

  return this->correlatedSampleSecondaryConditionalWithRandomNumberInSubrange(
                                                primary_indep_var_value,
                                                random_number,
                                                min_secondary_indep_var_value,
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
inline auto UnitAwareFullyTabularTwoDDistribution<PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>::sampleSecondaryConditionalExactInSubrange(
            const PrimaryIndepQuantity primary_indep_var_value,
            const SecondaryIndepQuantity max_secondary_indep_var_value ) const
  -> SecondaryIndepQuantity
{
  return this->sampleSecondaryConditionalInSubrange(
                                               primary_indep_var_value,
                                               max_secondary_indep_var_value );
}

// Return a correlated random sample from the secondary conditional PDF in the subrange
/*! \details There are often multiple ways to sample from two-dimensional
 * distributions (e.g. stochastic and correlated sampling). Ideally the
 * "non-exact" method will be faster and stochastically correct.
 */
template<typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit>
inline auto UnitAwareFullyTabularTwoDDistribution<PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>::correlatedSampleSecondaryConditionalWithRandomNumberInSubrange(
        const PrimaryIndepQuantity primary_indep_var_value,
        const double random_number,
        const SecondaryIndepQuantity min_secondary_indep_var_value,
        const SecondaryIndepQuantity max_secondary_indep_var_value ) const
  -> SecondaryIndepQuantity
{
  return this->sampleSecondaryConditionalWithRandomNumberInSubrange(
                                               primary_indep_var_value,
                                               random_number,
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
inline auto UnitAwareFullyTabularTwoDDistribution<PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>::sampleSecondaryConditionalExactWithRandomNumberInSubrange(
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
inline auto UnitAwareFullyTabularTwoDDistribution<PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>::sampleSecondaryConditionalAndRecordBinIndices(
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

/*! The fully tabular two-dimensional distribution (unit-agnostic)
 * \ingroup two_d_distributions
 */
typedef UnitAwareFullyTabularTwoDDistribution<void,void,void> FullyTabularTwoDDistribution;
  
} // end utility namespace

#endif // end UTILITY_FULLY_TABULAR_TWO_D_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end Utility_FullyTabularTwoDDistribution.hpp
//---------------------------------------------------------------------------//
