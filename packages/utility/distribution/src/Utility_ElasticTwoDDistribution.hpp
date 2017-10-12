//---------------------------------------------------------------------------//
//!
//! \file   Utility_ElasticTwoDDistribution.hpp
//! \author Luke Kersting
//! \brief  The elastic two-dimensional dist. class decl.
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_ELASTIC_TWO_D_DISTRIBUTION_HPP
#define UTILITY_ELASTIC_TWO_D_DISTRIBUTION_HPP

// Boost Includes
#include <boost/units/physical_dimensions/energy.hpp>

// FRENSIE Includes
#include "Utility_InterpolatedFullyTabularTwoDDistribution.hpp"

namespace Utility{

/*! The unit-aware inteprolated fully tabular two-dimensional distribution
 * \ingroup two_d_distribution
 */
template<typename TwoDInterpPolicy,
         typename TwoDSamplePolicy,
         typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit>
class UnitAwareElasticTwoDDistribution : public UnitAwareInterpolatedFullyTabularTwoDDistribution<TwoDInterpPolicy,TwoDSamplePolicy,PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>
{

  // Only allow construction when the primary independent unit corresponds to energy
  RESTRICT_UNIT_TO_BOOST_DIMENSION( PrimaryIndependentUnit, energy_dimension );

private:

  // The typedef for this type
  typedef UnitAwareElasticTwoDDistribution<TwoDInterpPolicy,TwoDSamplePolicy,PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit> ThisType;

  // The parent distribution type
  typedef UnitAwareInterpolatedFullyTabularTwoDDistribution<TwoDInterpPolicy,TwoDSamplePolicy,PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit> ParentType;

  // The base one-dimensional distribution type (UnitAwareTabularOneDDist)
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

  //! The primary independent variable processing tag
  typedef typename TwoDInterpPolicy::FirstIndepVarProcessingTag FirstIndepVarProcessingTag;

  //! The secondary independent quantity type
  typedef typename TwoDInterpPolicy::SecondIndepVarProcessingTag SecondIndepVarProcessingTag;

  // The CDF interpolation policy
  typedef typename ParentType::CDFInterpPolicy CDFInterpPolicy;
  
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
  UnitAwareElasticTwoDDistribution(
        const DistributionType& distribution,
        const SecondaryIndepQuantity upper_bound_conditional_indep_var = SIQT::one(),
        const double fuzzy_boundary_tol = 1e-7,
        const double evaluate_relative_error_tol = 1e-7,
        const double evaluate_error_tol = 1e-12 );

  //! Constructor
  template<template<typename T, typename... Args> class ArrayA,
           template<typename T, typename... Args> class ArrayB>
  UnitAwareElasticTwoDDistribution(
        const ArrayA<PrimaryIndepQuantity>& primary_indep_grid,
        const ArrayB<std::shared_ptr<const UnitAwareTabularOneDDistribution<SecondaryIndependentUnit,DependentUnit> > >& secondary_distributions,
        const SecondaryIndepQuantity upper_bound_conditional_indep_var = SIQT::one(),
        const double fuzzy_boundary_tol = 1e-7,
        const double evaluate_relative_error_tol = 1e-7,
        const double evaluate_error_tol = 1e-12 );

  //! Destructor
  ~UnitAwareElasticTwoDDistribution()
  { /* ... */ }

  //! Evaluate the distribution
  DepQuantity evaluate(
            const PrimaryIndepQuantity primary_indep_var_value,
            const SecondaryIndepQuantity secondary_indep_var_value ) const;

  //! Evaluate the distribution
  DepQuantity evaluateExact(
            const PrimaryIndepQuantity primary_indep_var_value,
            const SecondaryIndepQuantity secondary_indep_var_value ) const;

  //! Evaluate the secondary conditional PDF
  InverseSecondaryIndepQuantity evaluateSecondaryConditionalPDF(
            const PrimaryIndepQuantity primary_indep_var_value,
            const SecondaryIndepQuantity secondary_indep_var_value ) const;

  //! Evaluate the secondary conditional PDF
  InverseSecondaryIndepQuantity evaluateSecondaryConditionalPDFExact(
            const PrimaryIndepQuantity primary_indep_var_value,
            const SecondaryIndepQuantity secondary_indep_var_value ) const;

  //! Evaluate the secondary conditional CDF
  double evaluateSecondaryConditionalCDF(
            const PrimaryIndepQuantity primary_indep_var_value,
            const SecondaryIndepQuantity secondary_indep_var_value ) const;

  //! Evaluate the secondary conditional CDF
  double evaluateSecondaryConditionalCDFExact(
            const PrimaryIndepQuantity primary_indep_var_value,
            const SecondaryIndepQuantity secondary_indep_var_value ) const;

  //! Return a random sample from the secondary conditional PDF
  SecondaryIndepQuantity sampleSecondaryConditional(
            const PrimaryIndepQuantity primary_indep_var_value ) const;

  //! Return a random sample and record the number of trials
  SecondaryIndepQuantity sampleSecondaryConditionalAndRecordTrials(
            const PrimaryIndepQuantity primary_indep_var_value,
            unsigned& trials ) const;

// Return a random sample from the secondary conditional PDF and the index
  SecondaryIndepQuantity sampleSecondaryConditionalAndRecordBinIndices(
            const PrimaryIndepQuantity primary_indep_var_value,
            unsigned& primary_bin_index,
            unsigned& secondary_bin_index ) const;

  //! Return a random sample from the secondary conditional PDF and the index
  SecondaryIndepQuantity sampleSecondaryConditionalAndRecordBinIndices(
            const PrimaryIndepQuantity primary_indep_var_value,
            SecondaryIndepQuantity& raw_sample,
            unsigned& primary_bin_index,
            unsigned& secondary_bin_index ) const;

  //! Return a random sample from the secondary conditional PDF at the CDF val
  SecondaryIndepQuantity sampleSecondaryConditionalWithRandomNumber(
                const PrimaryIndepQuantity primary_indep_var_value,
                const double random_number ) const;

  //! Return a random sample from the secondary conditional PDF at the CDF val
  SecondaryIndepQuantity sampleSecondaryConditionalExactWithRandomNumber(
            const PrimaryIndepQuantity primary_indep_var_value,
            const double random_number ) const;

  //! Return a random sample from the secondary conditional PDF in the subrange
  SecondaryIndepQuantity sampleSecondaryConditionalWithRandomNumberInSubrange(
            const PrimaryIndepQuantity primary_indep_var_value,
            const double random_number,
            const SecondaryIndepQuantity max_secondary_indep_var_value ) const;

  //! Return a random sample from the secondary conditional PDF in the subrange
  SecondaryIndepQuantity sampleSecondaryConditionalExactWithRandomNumberInSubrange(
            const PrimaryIndepQuantity primary_indep_var_value,
            const double random_number,
            const SecondaryIndepQuantity max_secondary_indep_var_value ) const;

  //! Return the lower bound of the conditional distribution
  SecondaryIndepQuantity getLowerBoundOfConditionalIndepVar(
                    const PrimaryIndepQuantity primary_indep_var_value ) const;

  //! Return the upper bound of the conditional distribution
  SecondaryIndepQuantity getUpperBoundOfConditionalIndepVar(
                    const PrimaryIndepQuantity primary_indep_var_value ) const;

private:

  //! Correlated evaluate the distribution (unit based)
  DepQuantity correlatedEvaluateInBoundaries(
            const PrimaryIndepQuantity primary_indep_var_value,
            const SecondaryIndepQuantity secondary_indep_var_value,
            const SecondaryIndepQuantity min_secondary_indep_var_value,
            const SecondaryIndepQuantity max_secondary_indep_var_value ) const;

  //! Correlated evaluate the secondary conditional PDF (unit based)
  InverseSecondaryIndepQuantity correlatedEvaluateSecondaryConditionalPDFInBoundaries(
            const PrimaryIndepQuantity primary_indep_var_value,
            const SecondaryIndepQuantity secondary_indep_var_value,
            const SecondaryIndepQuantity min_secondary_indep_var_value,
            const SecondaryIndepQuantity max_secondary_indep_var_value ) const;

  //! Correlated evaluate the secondary conditional CDF (unit based)
  double correlatedEvaluateSecondaryConditionalCDFInBoundaries(
            const PrimaryIndepQuantity primary_indep_var_value,
            const SecondaryIndepQuantity secondary_indep_var_value,
            const SecondaryIndepQuantity min_secondary_indep_var_value,
            const SecondaryIndepQuantity max_secondary_indep_var_value ) const;

  //! Return a random correlated sample from the secondary conditional PDF
  SecondaryIndepQuantity correlatedSampleSecondaryConditionalWithRandomNumberInBoundaries(
            const PrimaryIndepQuantity primary_indep_var_value,
            const double random_number,
            const SecondaryIndepQuantity min_secondary_indep_var_value,
            const SecondaryIndepQuantity max_secondary_indep_var_value ) const;

  //! Return a random correlated sample from the secondary conditional PDF in the subrange
  SecondaryIndepQuantity correlatedSampleSecondaryConditionalWithRandomNumberInSubrangeInBoundaries(
            const PrimaryIndepQuantity primary_indep_var_value,
            const double random_number,
            const SecondaryIndepQuantity min_secondary_indep_var_value,
            const SecondaryIndepQuantity max_secondary_indep_var_value ) const;

  //! Evaluate the distribution using the desired evaluation method
  template<typename ReturnType,
           typename EvaluationMethod>
  ReturnType evaluateImpl(
                    const PrimaryIndepQuantity incoming_energy,
                    const SecondaryIndepQuantity angle_cosine,
                    EvaluationMethod evaluate ) const;

  //! Evaluate the distribution using the desired evaluation method
  template<typename ReturnType,
           typename EvaluationMethod>
  ReturnType evaluateExactInSubrangeImpl(
                    const PrimaryIndepQuantity incoming_energy,
                    const SecondaryIndepQuantity angle_cosine,
                    const SecondaryIndepQuantity max_angle_cosine,
                    EvaluationMethod evaluate,
                    ReturnType above_max_angle_cosine_return =
                        QuantityTraits<ReturnType>::zero(),
                    unsigned max_number_of_iterations = 500 ) const;

  //! Evaluate the distribution using the desired evaluation method
  template<typename ReturnType,
           typename EvaluationMethod>
  ReturnType evaluateExactImpl(
                    const PrimaryIndepQuantity incoming_energy,
                    const SecondaryIndepQuantity angle_cosine,
                    EvaluationMethod evaluate,
                    unsigned max_number_of_iterations = 500 ) const;

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

  //! Test if the second independent variable is compatible with Cosine processing
  bool isSecondIndepVarCompatibleWithCosineProcessingType() const;

  // The max upper bound of the conditional distribution ( 1.0 )
  SecondaryIndepQuantity d_max_upper_bound_conditional_indep_var;

  // The upper bound of the conditional distribution ( -1.0 < mu_cut <= 1.0 )
  SecondaryIndepQuantity d_upper_bound_conditional_indep_var;

  // The lower bound of the conditional distribution ( -1.0 )
  SecondaryIndepQuantity d_lower_bound_conditional_indep_var;

  // The relative error tolerance for the evaluate impl schemes
  double d_relative_error_tol;

  // The error tolerance for the evaluate impl schemes
  double d_error_tol;
};

/*! \brief The interpolated fully tabular two-dimensional distribution 
 * (unit-agnostic)
 * \ingroup two_d_distributions
 */
template<typename TwoDInterpPolicy,typename TwoDSamplePolicy> using ElasticTwoDDistribution =
  UnitAwareElasticTwoDDistribution<TwoDInterpPolicy,TwoDSamplePolicy,void,void,void>;
  
} // end Utility namespace

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "Utility_ElasticTwoDDistribution_def.hpp"

//---------------------------------------------------------------------------//

#endif // end UTILITY_ELASTIC_TWO_D_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end Utility_ElasticTwoDDistribution.hpp
//---------------------------------------------------------------------------//
