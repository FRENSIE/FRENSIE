//---------------------------------------------------------------------------//
//!
//! \file   Utility_InterpolatedTabularTwoDDistributionImplBase.hpp
//! \author Alex Robinson
//! \brief  The interpolated tabular two-dimensional dist. helper class decl.
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_INTERPOLATED_TABULAR_TWO_D_DISTRIBUTION_IMPL_BASE_HPP
#define UTILITY_INTERPOLATED_TABULAR_TWO_D_DISTRIBUTION_IMPL_BASE_HPP

// FRENSIE Includes
#include "Utility_PartiallyTabularTwoDDistribution.hpp"
#include "Utility_FullyTabularTwoDDistribution.hpp"
#include "Utility_TwoDInterpolationPolicy.hpp"

namespace Utility{

/*! The interpolated tabular two-dimensional dist. base implementation class
 * \details Distribution must be either the PartiallyTabularTwoDDistribution
 * or the FullyTabularTwoDDistribution. This intermediate base class implements
 * methods that are required by both the branches of the inheritance tree
 * and differ only in the OneDDistribution base class that they operate on
 * (either the OneDDistribution or the TabularOneDDistribution respectively).
 */
template<typename TwoDInterpPolicy, typename Distribution>
class UnitAwareInterpolatedTabularTwoDDistributionImplBase : public Distribution{

protected:

  // The parent distribution type
  typedef Distribution ParentType;

  // The base one-dimensional distribution type
  typedef typename ParentType::BaseOneDDistributionType BaseOneDDistributionType;

  // Typedef for QuantityTrais<double>
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
  UnitAwareInterpolatedTabularTwoDDistributionImplBase(
                                        const DistributionType& distribution );
  
  //! Constructor
  template<template<typename T, typename... Args> class ArrayA,
           template<typename T, typename... Args> class ArrayB>
  UnitAwareInterpolatedTabularTwoDDistributionImplBase(
                const ArrayA<PrimaryIndepQuantity>& primary_indep_grid,
                const ArrayB<std::shared_ptr<const BaseOneDDistributionType> >&
                secondary_distributions );

  //! Destructor
  virtual ~UnitAwareInterpolatedTabularTwoDDistributionImplBase()
  { /* ... */ }

  //! Evaluate the distribution
  DepQuantity evaluate(
                const PrimaryIndepQuantity primary_indep_var_value,
                const SecondaryIndepQuantity secondary_indep_var_value ) const;

  //! Evaluate the secondary conditional PDF
  InverseSecondaryIndepQuantity evaluateSecondaryConditionalPDF(
                const PrimaryIndepQuantity primary_indep_var_value,
                const SecondaryIndepQuantity secondary_indep_var_value ) const;

  //! Return a random sample from the secondary conditional PDF
  SecondaryIndepQuantity sampleSecondaryConditional(
                    const PrimaryIndepQuantity primary_indep_var_value ) const;

  //! Return a random sample and record the number of trials
  SecondaryIndepQuantity sampleSecondaryConditionalAndRecordTrials(
                            const PrimaryIndepQuantity primary_indep_var_value,
                            DistributionTraits::Counter& trials ) const;

  //! Return the upper bound of the conditional distribution
  SecondaryIndepQuantity getUpperBoundOfConditionalIndepVar(
                    const PrimaryIndepQuantity primary_indep_var_value ) const;

  //! Return the lower bound of the conditional distribution
  SecondaryIndepQuantity getLowerBoundOfConditionalIndepVar(
                    const PrimaryIndepQuantity primary_indep_var_value ) const;

  //! Test if the distribution is continuous in the primary dimension
  bool isPrimaryDimensionContinuous() const;

protected:

  //! Default constructor
  UnitAwareInterpolatedTabularTwoDDistributionImplBase()
  { /* ... */ }

  //! Evaluate the distribution using the desired evaluation method
  template<typename LocalTwoDInterpPolicy,
           typename ReturnType,
           typename EvaluationMethod>
  ReturnType evaluateImpl(
                        const PrimaryIndepQuantity primary_indep_var_value,
                        const SecondaryIndepQuantity secondary_indep_var_value,
                        EvaluationMethod evaluate,
                        const ReturnType below_lower_bound_return =
                        QuantityTraits<ReturnType>::zero(),
                        const ReturnType above_upper_bound_return =
                        QuantityTraits<ReturnType>::zero() ) const;

  //! Sample from the distribution using the desired sampling functor
  template<typename SampleFunctor>
  SecondaryIndepQuantity sampleDetailedImpl(
                            const PrimaryIndepQuantity primary_indep_var_value,
                            SampleFunctor sample_functor,
                            SecondaryIndepQuantity& raw_sample,
                            unsigned& primary_bin_index ) const;

  //! Sample from the distribution using the desired sampling functor
  template<typename SampleFunctor>
  SecondaryIndepQuantity sampleImpl(
                            const PrimaryIndepQuantity primary_indep_var_value,
                            SampleFunctor sample_functor ) const;

  //! Sample the bin boundary that will be used for stochastic sampling
  typename DistributionType::const_iterator
  sampleBinBoundary(
    const PrimaryIndepQuantity primary_indep_var_value,
    const typename DistributionType::const_iterator lower_bin_boundary,
    const typename DistributionType::const_iterator upper_bin_boundary ) const;

private:

  // Check that the secondary dists are compatible with the requested interp
  bool areSecondaryDistsCompatibleWithInterpType(
                                  const DistributionType& distribution ) const;

  // Check that the secondary dists are compatible with the requested interp
  template<template<typename T, typename... Args> class Array>
  bool areSecondaryDistsCompatibleWithInterpType(
                 const Array<std::shared_ptr<const BaseOneDDistributionType> >&
                 secondary_distributions ) const;
};
  
} // end Utility namespace

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "Utility_InterpolatedTabularTwoDDistributionImplBase_def.hpp"

//---------------------------------------------------------------------------//

#endif // end UTILITY_INTERPOLATED_TABULAR_TWO_D_DISTRIBUTION_IMPL_BASE_HPP

//---------------------------------------------------------------------------//
// end Utility_InterpolatedTabularTwoDDistributionImplBase.hpp
//---------------------------------------------------------------------------//
