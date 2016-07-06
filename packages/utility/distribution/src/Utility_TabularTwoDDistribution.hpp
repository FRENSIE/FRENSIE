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
 * \details The interpolation specified will determine the 
 * Dependent-PrimaryIndepedent interpolation scheme that will be used. Note
 * that unit-base interpolation will always be used so providing secondary
 * distributions with different grid bounds is acceptable. 
 * \ingroup two_d_distributions
 */
template<typename InterpolationPolicy,
         typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit>
class UnitAwareTabularTwoDDistribution : public UnitAwareTwoDDistribution<PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>
{

private:

  // The base TwoDDistribution type
  typedef UnitAwareTwoDDistribution<PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit> BaseType;

  // Typedef for QuantityTraits<double>
  typedef QuantityTraits<double> QT;

  // Typedef for QuantityTraits<PrimaryIndepQuantity>
  typedef QuantityTraits<typename BaseType::PrimaryIndepQuantity> PIQT;

  // Typddef for QuantityTraits<SecondaryIndepQuantity>
  typedef QuantityTraits<typename BaseType::SecondaryIndepQuantity> SIQT;

  // Typedef for QuantityTraits<InversePrimaryIndepQuantity>
  typedef QuantityTraits<typename BaseType::InversePrimaryIndepQuantity> IPIQT;

  // Typedef for QuantityTriats<InverseSecondaryIndepQuantity>
  typedef QuantityTraits<typename BaseType::InverseSecondaryIndepQuantity> ISIQT;

  // Typedef for QuantityTraits<InverseIndepQuantity>
  typedef QuantityTraits<typename BaseType::InverseIndepQuantity> IIQT;

  // Typedef for QuantityTraits<DepQuantity>
  typedef QuantityTraits<typename BaseType::DepQuantity> DQT;

public:

  //! The dependent unit type
  typedef typename BaseType::DepUnit DepUnit;

  //! The primary independent quantity type
  typedef typename BaseType::PrimaryIndepQuantity PrimaryIndepQuantity;

  //! The secondary independent quantity type
  typedef typename BaseType::SecondaryIndepQuantity SecondaryIndepQuantity;

  //! The inverse primary independent quantity type
  typedef typename BaseType::InversePrimaryIndepQuantity InversePrimaryIndepQuantity;

  //! The inverse secondary independent quantity type
  typedef typename BaseType::InverseSecondaryIndepQuantity InverseSecondaryIndepQuantity

  //! The inverse independent quantity type
  typedef typename BaseType::InverseIndepQuantity InverseIndepQuantity;

  //! The dependent quantity type
  typedef typename BaseType::DepQuantity DepQuantity;

  //! Constructor
  template<template<typename T, typename... Args> class Array>
  UnitAwareTabularTwoDDistribution( const Array<std::pair<PrimaryIndepQuantity,std::shared_ptr<const UnitAwareOneDDistribution<SecondaryIndependentUnit,DependentUnit> > > >& distribution );

  //! Constructor
  template<template<typename T, typename... Args> class ArrayA,
           template<typename T, typename... Args> class ArrayB>
  UnitAwareTabularTwoDDistribution(
                   const ArrayA<PrimaryIndepQuantity>& primary_indep_grid,
                   const ArrayB<std::shared_ptr<const UnitAwareOneDDistribution<SecondaryIndependentUnit,DependentUnit> > >& secondary_distributions );

  //! Destructor
  ~UnitAwareTabularTwoDDistribution()
  { /* ... */ }

  //! Evaluate the distribution
  DepQuantity evaluate(
                const PrimaryIndepQuantity primary_indep_var_value,
                const SecondaryIndepQuantity secondary_indep_var_value ) const;

  //! Evaluate the joint PDF
  InverseIndepQuantity evaluateJointPDF(
                const PrimaryIndepQuantity primary_indep_var_value,
                const SecondaryIndepQuantity secondary_indep_var_value ) const;

  //! Evaluate the primary marginal PDF
  InversePrimaryIndepQuantity evaluatePrimaryMarginalPDF(
                    const PrimaryIndepQuantity primary_indep_var_value ) const;

  //! Evaluate the secondary marginal PDF
  InverseSecondaryIndepQuantity evaluateSecondaryMarginalPDF(
                const SecondaryIndepQuantity secondary_indep_var_value ) const;

  //! Evaluate the primary conditional PDF
  InversePrimaryIndepQuantity evaluatePrimaryConditionalPDF(
                const PrimaryIndepQuantity primary_indep_var_value,
                const SecondaryIndepQuantity secondary_indep_var_value ) const;

  //! Evaluate the secondary conditional PDF
  InverseSecondaryIndepQuantity evaluateSecondaryConditionalPDF(
                const PrimaryIndepQuantity primary_indep_var_value,
                const SecondaryIndepQuantity secondary_indep_var_value ) const;

  //! Return a random sample from the primary marginal PDF
  PrimaryIndepQuantity samplePrimaryMarginal() const;

  //! Return a random sample from the secondary marginal PDF
  SecondarIndepQuantity sampleSecondaryMarginal() const;

  //! Return a random sample from the primary conditional PDF
  PrimaryIndepQuantity samplePrimaryConditional(
                const SecondaryIndepQuantity secondary_indep_var_value ) const;

  //! Return a random sample and record the number of trials
  PrimaryIndepQuantity samplePrimaryConditionalAndRecordTrials(
                        const SecondaryIndepQuantity secondary_indep_var_value,
                        unsigned& trials ) const;

  //! Return a random sample from the secondary conditional PDF
  SecondaryIndepQuantity sampleSecondaryConditional(
                    const PrimaryIndepQuantity primary_indep_var_value ) const;

  //! Return a random sample and record the number of trials
  SecondaryIndepQuantity sampleSecondaryConditionalAndRecordTrials(
                            const PrimaryIndepQuantity primary_indep_var_value,
                            unsigned& trials ) const;

  //! Return the upper bound of the distribution primary independent variable
  PrimaryIndepQuantity getUpperBoundOfPrimaryIndepVar() const;

  //! Return the lower bound of the distribution primary independent variable
  PrimaryIndepQuantity getLowerBoundOfPrimaryIndepVar() const;

  //! Return the upper bound of the distribution secondary independent variable
  SecondaryIndepQuantity getUpperBoundOfSecondaryIndepVar() const;

  //! Return the lower bound of the distribution secondary independent variable
  SecondaryIndepQuantity getLowerBoundOfSecondaryIndepVar() const;

  //! Return the upper bound of the conditional distribution
  SecondaryIndepQuantity getUpperBoundOfConditionalIndepVar(
                    const PrimaryIndepQuantity primary_indep_var_value ) const;

  //! Return the lower bound of the conditional distribution
  SecondaryIndepQuantity getLowerBoundOfConditionalIndepVar(
                    const PrimaryIndepQuantity primary_indep_var_value ) const;

  //! Test if the distribution is tabular in the primary dimension
  bool isPrimaryDimensionTabular() const;

  //! Test if the distribution is condinuous in the primary dimension
  bool isPrimaryDimensionContinuous() const;

private:

  // The distribution
  std::vector<std::pair<PrimaryIndepQuantity,std::shared_ptr<const UnitAwareOneDDistribution<SecondaryIndependentUnit,DependentUnit> > > > d_distribution;
};

/*! The tabular two-dimensional distribution (unit-agnostic)
 * \ingroup two_d_distributions
 */
template<typename InterpolationPolicy> using TabularTwoDDistribution =
  UnitAwareTabularTwoDDistribution<InterpolationPolicy,void,void,void>;
  
} // end Utility namespace

#endif // end UTILITY_TABULAR_TWO_D_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end Utility_TabularTwoDimensionalDistribution.hpp
//---------------------------------------------------------------------------//
