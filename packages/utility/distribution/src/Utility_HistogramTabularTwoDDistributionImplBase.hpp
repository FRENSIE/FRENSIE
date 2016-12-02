//---------------------------------------------------------------------------//
//!
//! \file   Utility_HistogramTabularTwoDDistributionImplBase.hpp
//! \author Alex Robinson
//! \brief  The histogram tabular two-dimensional dist. helper class decl.
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_HISTOGRAM_TABULAR_TWO_D_DISTRIBUTION_IMPL_BASE_HPP
#define UTILITY_HISTOGRAM_TABULAR_TWO_D_DISTRIBUTION_IMPL_BASE_HPP

// FRENSIE Includes
#include "Utility_PartiallyTabularTwoDDistribution.hpp"
#include "Utility_FullyTabularTwoDDistribution.hpp"

namespace Utility{

//! The histogram tabular two-dimensional dist. base implementation class
template<typename Distribution>
class UnitAwareHistogramTabularTwoDDistributionImplBase : public Distribution
{
  
protected:

  // The parent distribution type
  typedef Distribution ParentType;

  // The base one-dimensional distribution type
  typedef typename ParentType::BaseOneDDistributionType BaseOneDDistributionType;

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
  UnitAwareHistogramTabularTwoDDistributionImplBase(
                                         const DistributionType& distribution )
    : ParentType( distribution )
  { /* ... */ }

  //! Constructor
  template<template<typename T, typename... Args> class ArrayA,
           template<typename T, typename... Args> class ArrayB>
  UnitAwareHistogramTabularTwoDDistributionImplBase(
                const ArrayA<PrimaryIndepQuantity>& primary_indep_grid,
                const ArrayB<std::shared_ptr<const BaseOneDDistributionType> >&
                secondary_distributions )
    : ParentType( primary_indep_grid, secondary_distributions )
  { /* ... */ }

  //! Destructor
  virtual ~UnitAwareHistogramTabularTwoDDistributionImplBase()
  { /* ... */ }

  //! Evaluate the distribution
  DepQuantity evaluate(
                const PrimaryIndepQuantity primary_indep_var_value,
                const SecondaryIndepQuantity secondary_indep_var_value ) const;

  //! Evaluate the distribution
  DepQuantity evaluateExact(
                const PrimaryIndepQuantity primary_indep_var_value,
                const SecondaryIndepQuantity secondary_indep_var_value ) const;

  //! Evaluate the distribution using a weighted interpolation scheme
  DepQuantity evaluateWeighted(
                const PrimaryIndepQuantity primary_indep_var_value,
                const double weighted_secondary_indep_var_value ) const;

  //! Evaluate the secondary conditional PDF
  InverseSecondaryIndepQuantity evaluateSecondaryConditionalPDF(
                const PrimaryIndepQuantity primary_indep_var_value,
                const SecondaryIndepQuantity secondary_indep_var_value ) const;

  //! Evaluate the secondary conditional PDF
  InverseSecondaryIndepQuantity evaluateSecondaryConditionalPDFExact(
                const PrimaryIndepQuantity primary_indep_var_value,
                const SecondaryIndepQuantity secondary_indep_var_value ) const;

  //! Evaluate the secondary conditional PDF using a weighted interpolation scheme
  InverseSecondaryIndepQuantity evaluateSecondaryConditionalPDFWeighted(
                const PrimaryIndepQuantity primary_indep_var_value,
                const double weighted_secondary_indep_var_value ) const;

  //! Evaluate the secondary conditional CDF
  double evaluateSecondaryConditionalCDFExact(
                const PrimaryIndepQuantity primary_indep_var_value,
                const SecondaryIndepQuantity secondary_indep_var_value ) const;

  //! Evaluate the secondary conditional CDF using weighted interpolation
  double evaluateSecondaryConditionalCDFWeighted(
                const PrimaryIndepQuantity primary_indep_var_value,
                const double weighted_secondary_indep_var_value ) const;

  //! Return a random sample from the secondary conditional PDF
  SecondaryIndepQuantity sampleSecondaryConditional(
                    const PrimaryIndepQuantity primary_indep_var_value ) const;

  //! Return a random sample from the secondary conditional PDF using a weighted interpolation
  SecondaryIndepQuantity sampleSecondaryConditionalWeighted(
        const PrimaryIndepQuantity primary_indep_var_value,
        const SecondaryIndepQuantity secondary_indep_weighting_factor ) const;

  //! Return a random sample and record the number of trials
  SecondaryIndepQuantity sampleSecondaryConditionalAndRecordTrials(
                            const PrimaryIndepQuantity primary_indep_var_value,
                            unsigned& trials ) const;

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
  UnitAwareHistogramTabularTwoDDistributionImplBase()
  { /* ... */ }

  //! Evaluate the distribution using the desired evaluation method
  template<typename ReturnType, typename EvaluationMethod>
  ReturnType evaluateImpl(
                        const PrimaryIndepQuantity primary_indep_var_value,
                        const SecondaryIndepQuantity secondary_indep_var_value,
                        EvaluationMethod evaluate ) const;

  //! Evaluate the distribution using the desired evaluation method
  template<typename ReturnType, typename EvaluationMethod>
  ReturnType evaluateWeightedImpl(
                        const PrimaryIndepQuantity primary_indep_var_value,
                        const double weighted_secondary_indep_var_value,
                        EvaluationMethod evaluate ) const;

  //! Sample from the distribution using the desired sampling functor
  template<typename SampleFunctor>
  SecondaryIndepQuantity sampleDetailedImpl(
                            const PrimaryIndepQuantity primary_indep_var_value,
                            SampleFunctor sample_functor,
                            unsigned& primary_bin_index ) const;

  //! Sample from the distribution using the desired sampling functor
  template<typename SampleFunctor>
  SecondaryIndepQuantity sampleImpl(
                            const PrimaryIndepQuantity primary_indep_var_value,
                            SampleFunctor sample_functor ) const;  
};
  
} // end Utility namespace

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "Utility_HistogramTabularTwoDDistributionImplBase_def.hpp"

//---------------------------------------------------------------------------//

#endif // end UTILITY_HISTOGRAM_TABULAR_TWO_D_DISTRIBUTION_IMPL_BASE_HPP

//---------------------------------------------------------------------------//
// end Utility_HistogramTabularTwoDDistributionImplBase.hpp
//---------------------------------------------------------------------------//
