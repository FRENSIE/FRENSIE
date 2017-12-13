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
#include "Utility_TwoDInterpolationPolicy.hpp"

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
template<typename TwoDInterpPolicy, typename Distribution>
class UnitAwareInterpolatedTabularBasicBivariateDistributionImplBase : public Distribution
{

  // Typedef for this type
  typedef UnitAwareInterpolatedTabularBasicBivariateDistributionImplBase<Distribution> ThisType;
  
protected:
  
  // The parent distribution type
  typedef Distribution BaseType;

  // The base univariate distribution type
  typedef typename BaseType::BaseUnivariateDistributionType BaseUnivariateDistributionType;

  // Typedef for QuantityTrais<double>
  typedef typename BaseType::QT QT;

  // Typedef for QuantityTraits<PrimaryIndepQuantity>
  typedef typename BaseType::PIQT PIQT;

  // Typddef for QuantityTraits<SecondaryIndepQuantity>
  typedef typename BaseType::SIQT SIQT;

  // Typedef for QuantityTriats<InverseSecondaryIndepQuantity>
  typedef typename BaseType::ISIQT ISIQT;

  // Typedef for QuantityTraits<DepQuantity>
  typedef typename BaseType::DQT DQT;

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
     secondary_distributions );

  //! Destructor
  virtual ~UnitAwareInterpolatedTabularBasicBivariateDistributionImplBase()
  { /* ... */ }

  //! Evaluate the distribution
  DepQuantity evaluate(
       const PrimaryIndepQuantity primary_indep_var_value,
       const SecondaryIndepQuantity secondary_indep_var_value ) const override;

  //! Evaluate the secondary conditional PDF
  InverseSecondaryIndepQuantity evaluateSecondaryConditionalPDF(
       const PrimaryIndepQuantity primary_indep_var_value,
       const SecondaryIndepQuantity secondary_indep_var_value ) const override;

  //! Return a random sample from the secondary conditional PDF
  SecondaryIndepQuantity sampleSecondaryConditional(
           const PrimaryIndepQuantity primary_indep_var_value ) const override;

  //! Return a random sample and record the number of trials
  SecondaryIndepQuantity sampleSecondaryConditionalAndRecordTrials(
                          const PrimaryIndepQuantity primary_indep_var_value,
                          DistributionTraits::Counter& trials ) const override;

  //! Return the upper bound of the conditional distribution
  SecondaryIndepQuantity getUpperBoundOfSecondaryConditionalIndepVar(
           const PrimaryIndepQuantity primary_indep_var_value ) const override;

  //! Return the lower bound of the conditional distribution
  SecondaryIndepQuantity getLowerBoundOfSecondaryConditionalIndepVar(
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

  // Verify that the distribution data is valid
  static void verifyValidData(
     const std::vector<PrimaryIndepQuantity>& primary_indep_grid,
     const std::vector<std::shared_ptr<const BaseUnivariateDistributionType> >&
     secondary_distributions );

  // Save the distribution to an archive
  template<typename Archive>
  void save( Archive& ar, const unsigned version ) const;

  // Load the distribution from an archive
  template<typename Archive>
  void load( Archive& ar, const unsigned version );

  BOOST_SERIALIZATION_SPLIT_MEMBER();

  // Declare the boost serialization access object as a friend
  friend class boost::serialization::access;
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
