//---------------------------------------------------------------------------//
//!
//! \file   Utility_InterpolatedTabularBivariateDistributionImplBase.hpp
//! \author Alex Robinson
//! \brief  The interpolated tabular two-dimensional dist. helper class decl.
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_INTERPOLATED_TABULAR_BASIC_BIVARIATE_DISTRIBUTION_IMPL_BASE_HPP
#define UTILITY_INTERPOLATED_TABULAR_BASIC_BIVARIATE_DISTRIBUTION_IMPL_BASE_HPP

// FRENSIE Includes
#include "Utility_TwoDGridPolicy.hpp"
#include "Utility_TabularBasicBivariateDistribution.hpp"

namespace Utility{

/*! The interpolated tabular bivariate dist. base implementation class
 *
 * Distribution must be either the
 * Utility::PartiallyTabularBasicBivariateDistribution
 * or the Utility::FullyTabularBasicBivariateDistribution. This intermediate
 * base class implements methods that are required by both the branches of the
 * inheritance tree and differ only in the UnivariateDistribution base class
 * that they operate on (either the Utility::UnivariateDistribution or the
 * Utility::TabularUnivariateDistribution respectively).
 */
template<typename TwoDGridPolicy,
         typename Distribution>
class UnitAwareInterpolatedTabularBasicBivariateDistributionImplBase : public Distribution
{

  // Typedef for this type
  typedef UnitAwareInterpolatedTabularBasicBivariateDistributionImplBase<TwoDGridPolicy,Distribution> ThisType;

protected:

  //! The parent distribution type
  typedef Distribution BaseType;

  //! Typedef for QuantityTraits<double>
  typedef typename BaseType::QT QT;

  //! Typedef for QuantityTraits<PrimaryIndepQuantity>
  typedef typename BaseType::PIQT PIQT;

  //! Typedef for QuantityTraits<SecondaryIndepQuantity>
  typedef typename BaseType::SIQT SIQT;

  //! Typedef for QuantityTriats<InverseSecondaryIndepQuantity>
  typedef typename BaseType::ISIQT ISIQT;

  //! Typedef for QuantityTraits<DepQuantity>
  typedef typename BaseType::DQT DQT;

  //! The distribution data const iterator
  typedef typename BaseType::DistributionDataConstIterator DistributionDataConstIterator;

public:

  //! The primary independent quantity type
  typedef typename BaseType::PrimaryIndepQuantity PrimaryIndepQuantity;

  //! The secondary independent quantity type
  typedef typename BaseType::SecondaryIndepQuantity SecondaryIndepQuantity;

  //! The inverse secondary independent quantity type
  typedef typename BaseType::InverseSecondaryIndepQuantity InverseSecondaryIndepQuantity;

  //! The dependent quantity type
  typedef typename BaseType::DepQuantity DepQuantity;

  //! The base univariate distribution type
  typedef typename BaseType::BaseUnivariateDistributionType BaseUnivariateDistributionType;

  //! Constructor
  UnitAwareInterpolatedTabularBasicBivariateDistributionImplBase(
     const std::vector<PrimaryIndepQuantity>& primary_indep_grid,
     const std::vector<std::shared_ptr<const BaseUnivariateDistributionType> >&
     secondary_distributions,
     const double fuzzy_boundary_tol = 1e-3,
     const double relative_error_tol = 1e-7,
     const double error_tol = 1e-16,
     const unsigned max_number_of_iterations = 500 );

  //! Destructor
  virtual ~UnitAwareInterpolatedTabularBasicBivariateDistributionImplBase()
  { /* ... */ }

  //! Return the evaluation fuzzy bound tolerance
  double getFuzzyBoundTolerance() const;

  //! Return the evaluation relative error tolerance
  double getRelativeErrorTolerance() const;

  //! Return the evaluation error tolerance
  double getErrorTolerance() const;

  //! Return the evaluation max number of iterations
  unsigned getMaxNumberOfIterations() const;

  //! Evaluate the distribution
  virtual DepQuantity evaluate(
       const PrimaryIndepQuantity primary_indep_var_value,
       const SecondaryIndepQuantity secondary_indep_var_value ) const override;

  //! Evaluate the secondary conditional PDF
  virtual InverseSecondaryIndepQuantity evaluateSecondaryConditionalPDF(
       const PrimaryIndepQuantity primary_indep_var_value,
       const SecondaryIndepQuantity secondary_indep_var_value ) const override;

  //! Return a random sample from the secondary conditional PDF
  virtual SecondaryIndepQuantity sampleSecondaryConditional(
           const PrimaryIndepQuantity primary_indep_var_value ) const override;

  //! Return a random sample and record the number of trials
  virtual SecondaryIndepQuantity sampleSecondaryConditionalAndRecordTrials(
                          const PrimaryIndepQuantity primary_indep_var_value,
                          DistributionTraits::Counter& trials ) const override;

  //! Return the upper bound of the conditional distribution
  virtual SecondaryIndepQuantity getUpperBoundOfSecondaryConditionalIndepVar(
           const PrimaryIndepQuantity primary_indep_var_value ) const override;

  //! Return the lower bound of the conditional distribution
  virtual SecondaryIndepQuantity getLowerBoundOfSecondaryConditionalIndepVar(
           const PrimaryIndepQuantity primary_indep_var_value ) const override;

  //! Test if the distribution is continuous in the primary dimension
  bool isPrimaryDimensionContinuous() const;

protected:

  //! Default constructor
  UnitAwareInterpolatedTabularBasicBivariateDistributionImplBase()
  { /* ... */ }

  //! Set the distribution
  void setDistribution(
     const std::vector<PrimaryIndepQuantity>& primary_indep_grid,
     const std::vector<std::shared_ptr<const BaseUnivariateDistributionType> >&
     secondary_distributions ) override;

  //! Set the evaluation tolerances
  void setEvaluationTolerances( const double fuzzy_boundary_tol,
                                const double relative_error_tol,
                                const double error_tol,
                                const unsigned max_number_of_iterations = 500 );

  //! Evaluate the distribution using the desired evaluation method
  template<typename ReturnType, typename EvaluationMethod>
  ReturnType evaluateImpl(
                        const PrimaryIndepQuantity primary_indep_var_value,
                        const SecondaryIndepQuantity secondary_indep_var_value,
                        EvaluationMethod evaluate ) const;

  //! Evaluate the distribution using the desired evaluation method
  template<typename ReturnType, typename EvaluationMethod>
  ReturnType evaluateImpl(
             const PrimaryIndepQuantity primary_indep_var_value,
             const SecondaryIndepQuantity secondary_indep_var_value,
             const std::function<SecondaryIndepQuantity(PrimaryIndepQuantity)>&
             min_secondary_indep_var_functor,
             const std::function<SecondaryIndepQuantity(PrimaryIndepQuantity)>&
             max_secondary_indep_var_functor,
             EvaluationMethod evaluate ) const;

  //! Sample from the distribution using the desired sampling functor
  template<typename SampleFunctor>
  SecondaryIndepQuantity sampleDetailedImpl(
                            const PrimaryIndepQuantity primary_indep_var_value,
                            SampleFunctor sample_functor,
                            SecondaryIndepQuantity& raw_sample,
                            size_t& primary_bin_index ) const;

  //! Sample from the distribution using the desired sampling functor
  template<typename SampleFunctor>
  SecondaryIndepQuantity sampleDetailedImpl(
            const PrimaryIndepQuantity primary_indep_var_value,
            SampleFunctor sample_functor,
            SecondaryIndepQuantity& raw_sample,
            size_t& primary_bin_index,
            const std::function<SecondaryIndepQuantity(PrimaryIndepQuantity)>&
              min_secondary_indep_var_functor,
            const std::function<SecondaryIndepQuantity(PrimaryIndepQuantity)>&
              max_secondary_indep_var_functor ) const;

  //! Sample from the distribution using the desired sampling functor
  template<typename SampleFunctor>
  SecondaryIndepQuantity sampleImpl(
                            const PrimaryIndepQuantity primary_indep_var_value,
                            SampleFunctor sample_functor ) const;

  //! Sample from the distribution using the desired sampling functor
  template<typename SampleFunctor>
  SecondaryIndepQuantity sampleImpl(
            const PrimaryIndepQuantity primary_indep_var_value,
            SampleFunctor sample_functor,
            const std::function<SecondaryIndepQuantity(PrimaryIndepQuantity)>&
              min_secondary_indep_var_functor,
            const std::function<SecondaryIndepQuantity(PrimaryIndepQuantity)>&
              max_secondary_indep_var_functor ) const;

private:

  // Verify that the distribution data is valid
  static void verifyValidData(
     const std::vector<PrimaryIndepQuantity>& primary_indep_grid,
     const std::vector<std::shared_ptr<const BaseUnivariateDistributionType> >&
     secondary_distributions );

  // Verify that the tolerances are valid
  static void verifyValidTolerances( const double fuzzy_boundary_tol,
                                     const double relative_error_tol,
                                     const double error_tol );

  // Save the distribution to an archive
  template<typename Archive>
  void save( Archive& ar, const unsigned version ) const;

  // Load the distribution from an archive
  template<typename Archive>
  void load( Archive& ar, const unsigned version );

  BOOST_SERIALIZATION_SPLIT_MEMBER();

  // Declare the boost serialization access object as a friend
  friend class boost::serialization::access;

  // The evaluation fuzzy boundary tol
  double d_fuzzy_boundary_tol;

  // The evaluation relative error tol
  double d_relative_error_tol;

  // The evaluation error tol
  double d_error_tol;

  // The evaluation max number of iterations
  unsigned d_max_number_of_iterations;
};

} // end Utility namespace

BOOST_SERIALIZATION_ASSUME_ABSTRACT_CLASS2( UnitAwareInterpolatedTabularBasicBivariateDistributionImplBase, Utility );
BOOST_SERIALIZATION_CLASS2_VERSION( UnitAwareInterpolatedTabularBasicBivariateDistributionImplBase, Utility, 0 );

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "Utility_InterpolatedTabularBasicBivariateDistributionImplBase_def.hpp"

//---------------------------------------------------------------------------//

#endif // end UTILITY_INTERPOLATED_TABULAR_BASIC_BIVARIATE_DISTRIBUTION_IMPL_BASE_HPP

//---------------------------------------------------------------------------//
// end Utility_InterpolatedTabularBasicBivariateDistributionImplBase.hpp
//---------------------------------------------------------------------------//
