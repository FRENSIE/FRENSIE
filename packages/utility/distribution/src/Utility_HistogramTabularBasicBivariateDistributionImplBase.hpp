//---------------------------------------------------------------------------//
//!
//! \file   Utility_HistogramTabularBasicBivariateDistributionImplBase.hpp
//! \author Alex Robinson
//! \brief  The histogram tabular basic bivariate dist. helper class decl.
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_HISTOGRAM_TABULAR_BASIC_BIVARIATE_DISTRIBUTION_IMPL_BASE_HPP
#define UTILITY_HISTOGRAM_TABULAR_BASIC_BIVARIATE_DISTRIBUTION_IMPL_BASE_HPP

// FRENSIE Includes
#include "Utility_TabularBasicBivariateDistribution.hpp"

namespace Utility{

/*! The histogram tabular bivariate dist. base implementation class
 * \ingroup bivariate_distributions
 */
template<typename Distribution>
class UnitAwareHistogramTabularBasicBivariateDistributionImplBase : public Distribution
{

  // Typedef for this type
  typedef UnitAwareHistogramTabularBasicBivariateDistributionImplBase<Distribution> ThisType;

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
  UnitAwareHistogramTabularBasicBivariateDistributionImplBase(
     const std::vector<PrimaryIndepQuantity>& primary_indep_grid,
     const std::vector<std::shared_ptr<const BaseUnivariateDistributionType> >&
     secondary_distributions );

  //! Destructor
  virtual ~UnitAwareHistogramTabularBasicBivariateDistributionImplBase()
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
  bool isPrimaryDimensionContinuous() const override;

protected:

  //! Default constructor
  UnitAwareHistogramTabularBasicBivariateDistributionImplBase()
  { /* ... */ }

  //! Evaluate the distribution using the desired evaluation method
  template<typename ReturnType, typename EvaluationMethod>
  ReturnType evaluateImpl(
                        const PrimaryIndepQuantity primary_indep_var_value,
                        const SecondaryIndepQuantity secondary_indep_var_value,
                        EvaluationMethod evaluate ) const;

  //! Sample from the distribution using the desired sampling functor
  template<typename SampleFunctor>
  SecondaryIndepQuantity sampleDetailedImpl(
                            const PrimaryIndepQuantity primary_indep_var_value,
                            SampleFunctor sample_functor,
                            size_t& primary_bin_index ) const;

  //! Sample from the distribution using the desired sampling functor
  template<typename SampleFunctor>
  SecondaryIndepQuantity sampleImpl(
                            const PrimaryIndepQuantity primary_indep_var_value,
                            SampleFunctor sample_functor ) const;

private:

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

BOOST_SERIALIZATION_ASSUME_ABSTRACT_CLASS1( UnitAwareHistogramTabularBasicBivariateDistributionImplBase, Utility );
BOOST_SERIALIZATION_CLASS1_VERSION( UnitAwareHistogramTabularBasicBivariateDistributionImplBase, Utility, 0 );

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "Utility_HistogramTabularBasicBivariateDistributionImplBase_def.hpp"

//---------------------------------------------------------------------------//

#endif // end UTILITY_HISTOGRAM_TABULAR_BASIC_BIVARIATE_DISTRIBUTION_IMPL_BASE_HPP

//---------------------------------------------------------------------------//
// end Utility_HistogramTabularBasicBivariateDistributionImplBase.hpp
//---------------------------------------------------------------------------//
