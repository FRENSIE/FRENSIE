//---------------------------------------------------------------------------//
//!
//! \file   Utility_ElasticBasicBivariateDistribution.hpp
//! \author Luke Kersting
//! \brief  The elastic basic bivariate dist. class decl.
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_ELASTIC_BASIC_BIVARIATE_DISTRIBUTION_HPP
#define UTILITY_ELASTIC_BASIC_BIVARIATE_DISTRIBUTION_HPP

// Boost Includes
#include <boost/units/physical_dimensions/energy.hpp>

// FRENSIE Includes
#include "Utility_InterpolatedFullyTabularBasicBivariateDistribution.hpp"

namespace Utility{

/*! The unit-aware interpolated fully tabular two-dimensional distribution
 * \ingroup two_d_distribution
 */
template<typename TwoDInterpPolicy,
         typename TwoDSamplePolicy,
         typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit>
class UnitAwareElasticBasicBivariateDistribution : public UnitAwareInterpolatedFullyTabularBasicBivariateDistribution<TwoDInterpPolicy,TwoDSamplePolicy,PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>
{

  // Only allow construction when the primary independent unit corresponds to energy
  RESTRICT_UNIT_TO_BOOST_DIMENSION( PrimaryIndependentUnit, energy_dimension );

  // The typedef for this type
  typedef UnitAwareElasticBasicBivariateDistribution<TwoDInterpPolicy,TwoDSamplePolicy,PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit> ThisType;

  // The parent distribution type
  typedef UnitAwareInterpolatedFullyTabularBasicBivariateDistribution<TwoDInterpPolicy,TwoDSamplePolicy,PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit> BaseType;

  // The base one-dimensional distribution type (UnitAwareTabularUnivariateDist)
  typedef typename BaseType::BaseUnivariateDistributionType BaseUnivariateDistributionType;

  // Typedef for QuantityTraits<double>
  typedef typename BaseType::QT QT;

  // Typedef for QuantityTraits<PrimaryIndepQuantity>
  typedef typename BaseType::PIQT PIQT;

  // Typedef for QuantityTraits<SecondaryIndepQuantity>
  typedef typename BaseType::SIQT SIQT;

  // Typedef for QuantityTriats<InverseSecondaryIndepQuantity>
  typedef typename BaseType::ISIQT ISIQT;

  // Typedef for QuantityTraits<DepQuantity>
  typedef typename BaseType::DQT DQT;

  //! The primary independent variable processing tag
  typedef typename TwoDInterpPolicy::FirstIndepVarProcessingTag FirstIndepVarProcessingTag;

  //! The secondary independent quantity type
  typedef typename TwoDInterpPolicy::SecondIndepVarProcessingTag SecondIndepVarProcessingTag;

public:
  
  //! The primary independent quantity type
  typedef typename BaseType::PrimaryIndepQuantity PrimaryIndepQuantity;

  //! The secondary independent quantity type
  typedef typename BaseType::SecondaryIndepQuantity SecondaryIndepQuantity;

  //! The inverse secondary independent quantity type
  typedef typename BaseType::InverseSecondaryIndepQuantity InverseSecondaryIndepQuantity;

  //! The dependent quantity type
  typedef typename BaseType::DepQuantity DepQuantity;

  //! The distribution type
  typedef typename BaseType::DistributionType DistributionType;

  //! Constructor
  UnitAwareElasticBasicBivariateDistribution(
        const std::vector<PrimaryIndepQuantity>& primary_indep_grid,
        const std::vector<std::shared_ptr<const UnitAwareTabularUnivariateDistribution<SecondaryIndependentUnit,DependentUnit> > >& secondary_distributions,
        const SecondaryIndepQuantity upper_bound_conditional_indep_var = SIQT::one(),
        const double fuzzy_boundary_tol = 1e-7,
        const double evaluate_relative_error_tol = 1e-7,
        const double evaluate_error_tol = 1e-12 );

  //! Destructor
  ~UnitAwareElasticBasicBivariateDistribution()
  { /* ... */ }

  //! Evaluate the distribution
  DepQuantity evaluate(
       const PrimaryIndepQuantity primary_indep_var_value,
       const SecondaryIndepQuantity secondary_indep_var_value ) const override;

  //! Evaluate the secondary conditional PDF
  InverseSecondaryIndepQuantity evaluateSecondaryConditionalPDF(
       const PrimaryIndepQuantity primary_indep_var_value,
       const SecondaryIndepQuantity secondary_indep_var_value ) const override;

  //! Evaluate the secondary conditional PDF
  InverseSecondaryIndepQuantity evaluateSecondaryConditionalPDF(
            const PrimaryIndepQuantity primary_indep_var_value,
            const SecondaryIndepQuantity secondary_indep_var_value,
            const std::function<SecondaryIndepQuantity(PrimaryIndepQuantity)>&
            min_secondary_indep_var_functor,
            const std::function<SecondaryIndepQuantity(PrimaryIndepQuantity)>&
            max_secondary_indep_var_functor ) const override;

  //! Evaluate the secondary conditional CDF
  double evaluateSecondaryConditionalCDF(
       const PrimaryIndepQuantity primary_indep_var_value,
       const SecondaryIndepQuantity secondary_indep_var_value ) const override;

  //! Return a random sample from the secondary conditional PDF
  SecondaryIndepQuantity sampleSecondaryConditional(
           const PrimaryIndepQuantity primary_indep_var_value ) const override;

  //! Return a random sample from the secondary conditional PDF
  SecondaryIndepQuantity sampleSecondaryConditional(
            const PrimaryIndepQuantity primary_indep_var_value,
            const std::function<SecondaryIndepQuantity(PrimaryIndepQuantity)>&
            min_secondary_indep_var_functor,
            const std::function<SecondaryIndepQuantity(PrimaryIndepQuantity)>&
            max_secondary_indep_var_functor ) const override;

  //! Return a random sample and record the number of trials
  SecondaryIndepQuantity sampleSecondaryConditionalAndRecordTrials(
            const PrimaryIndepQuantity primary_indep_var_value,
            unsigned& trials ) const override;

// Return a random sample from the secondary conditional PDF and the index
  SecondaryIndepQuantity sampleSecondaryConditionalAndRecordBinIndices(
            const PrimaryIndepQuantity primary_indep_var_value,
            unsigned& primary_bin_index,
            unsigned& secondary_bin_index ) const override;

  //! Return a random sample from the secondary conditional PDF and the index
  SecondaryIndepQuantity sampleSecondaryConditionalAndRecordBinIndices(
            const PrimaryIndepQuantity primary_indep_var_value,
            SecondaryIndepQuantity& raw_sample,
            unsigned& primary_bin_index,
            unsigned& secondary_bin_index ) const override;

  //! Return a random sample from the secondary conditional PDF at the CDF val
  SecondaryIndepQuantity sampleSecondaryConditionalWithRandomNumber(
                const PrimaryIndepQuantity primary_indep_var_value,
                const double random_number ) const override;

  //! Return a random sample from the secondary conditional PDF in the subrange
  SecondaryIndepQuantity sampleSecondaryConditionalInSubrange(
   const PrimaryIndepQuantity primary_indep_var_value,
   const SecondaryIndepQuantity max_secondary_indep_var_value ) const override;

  //! Return a random sample from the secondary conditional PDF in the subrange
  SecondaryIndepQuantity sampleSecondaryConditionalWithRandomNumberInSubrange(
   const PrimaryIndepQuantity primary_indep_var_value,
   const double random_number,
   const SecondaryIndepQuantity max_secondary_indep_var_value ) const override;

  //! Return the lower bound of the conditional distribution
  SecondaryIndepQuantity getLowerBoundOfConditionalIndepVar(
           const PrimaryIndepQuantity primary_indep_var_value ) const override;

  //! Return the upper bound of the conditional distribution
  SecondaryIndepQuantity getUpperBoundOfConditionalIndepVar(
           const PrimaryIndepQuantity primary_indep_var_value ) const override;

private:

  //! Evaluate the distribution using the desired evaluation method
  template<typename LocalTwoDInterpPolicy,
           typename ReturnType,
           typename EvaluationMethod>
  ReturnType evaluateImpl(
                    const PrimaryIndepQuantity incoming_energy,
                    const SecondaryIndepQuantity angle_cosine,
                    EvaluationMethod evaluate ) const;

  //! Evaluate the distribution using the desired evaluation method
  template<typename LocalTwoDInterpPolicy,
           typename ReturnType,
           typename EvaluationMethod>
  ReturnType evaluateImpl(
    const PrimaryIndepQuantity incoming_energy,
    const SecondaryIndepQuantity angle_cosine,
    const std::function<SecondaryIndepQuantity(PrimaryIndepQuantity)>&
      min_secondary_indep_var_functor,
    const std::function<SecondaryIndepQuantity(PrimaryIndepQuantity)>&
      max_secondary_indep_var_functor,
    EvaluationMethod evaluate,
    unsigned max_number_of_iterations = 500 ) const;

  //! Evaluate the distribution using the desired evaluation method
  template<typename LocalTwoDInterpPolicy,
           typename EvaluationMethod>
  double evaluateCDFImpl(
                    const PrimaryIndepQuantity incoming_energy,
                    const SecondaryIndepQuantity angle_cosine,
                    EvaluationMethod evaluateCDF ) const;

  //! Evaluate the distribution using the desired evaluation method
  template<typename LocalTwoDInterpPolicy,
           typename EvaluationMethod>
  double evaluateCDFImpl(
    const PrimaryIndepQuantity incoming_energy,
    const SecondaryIndepQuantity angle_cosine,
    const std::function<SecondaryIndepQuantity(PrimaryIndepQuantity)>&
      min_secondary_indep_var_functor,
    const std::function<SecondaryIndepQuantity(PrimaryIndepQuantity)>&
      max_secondary_indep_var_functor,
    EvaluationMethod evaluateCDF,
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

  //! Verify that the second independent variable processing type is compatible with Cosine processing
  bool verifyValidSecondIndepVarProcessingType() const;

  // Save the distribution to an archive
  template<typename Archive>
  void save( Archive& ar, const unsigned version ) const;

  // Load the distribution from an archive
  template<typename Archive>
  void load( Archive& ar, const unsigned version );

  BOOST_SERIALIZATION_SPLIT_MEMBER();

  // Declare the boost serialization access object as a friend
  friend class boost::serialization::access;

  // The max upper bound of the conditional distribution ( 1.0 )
  SecondaryIndepQuantity d_max_upper_bound_conditional_indep_var;

  // The upper bound of the conditional distribution ( -1.0 < mu_cut <= 1.0 )
  SecondaryIndepQuantity d_upper_bound_conditional_indep_var;

  // The lower bound of the conditional distribution ( -1.0 )
  SecondaryIndepQuantity d_lower_bound_conditional_indep_var;
};

/*! \brief The interpolated fully tabular two-dimensional distribution 
 * (unit-agnostic)
 * \ingroup two_d_distributions
 */
template<typename TwoDInterpPolicy,typename TwoDSamplePolicy> using ElasticBasicBivariateDistribution =
  UnitAwareElasticBasicBivariateDistribution<TwoDInterpPolicy,TwoDSamplePolicy,void,void,void>;
  
} // end Utility namespace

BOOST_SERIALIZATION_DISTRIBUTION5_VERSION( UnitAwareElasticBasicBivariateDistribution, 0 );

#define BOOST_SERIALIZATION_ELASTIC_BASIC_BIVARIATE_DISTRIBUTION_EXPORT_STANDARD_KEY() \
  BOOST_SERIALIZATION_CLASS5_EXPORT_STANDARD_KEY( UnitAwareElasticBasicBivariateDistribution, Utility ) \
  BOOST_SERIALIZATION_TEMPLATE_CLASS_EXPORT_KEY_IMPL(                   \
    UnitAwareElasticBasicBivariateDistribution, Utility, \
    __BOOST_SERIALIZATION_FORWARD_AS_SINGLE_ARG__( std::string( "ElasticBasicBivariateDistribution<" ) + Utility::typeName<InterpPolicy>() + "," + Utility::typeName<SamplePolicy>() + ">" ), \
    __BOOST_SERIALIZATION_FORWARD_AS_SINGLE_ARG__( typename InterpPolicy, typename SamplePolicy ), \
    __BOOST_SERIALIZATION_FORWARD_AS_SINGLE_ARG__( InterpPolicy, SamplePolicy, void, void, void ) )

BOOST_SERIALIZATION_ELASTIC_BASIC_BIVARIATE_DISTRIBUTION_EXPORT_STANDARD_KEY();

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "Utility_ElasticBivariateDistribution_def.hpp"

//---------------------------------------------------------------------------//

#endif // end UTILITY_ELASTIC_BASIC_BIVARIATE_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end Utility_ElasticBivariateDistribution.hpp
//---------------------------------------------------------------------------//
