//---------------------------------------------------------------------------//
//!
//! \file   Utility_InterpolatedFullyTabularBasicBivariateDistribution.hpp
//! \author Alex Robinson
//! \brief  The interpolated fully tabular basic bivariate dist. class decl.
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_INTERPOLATED_FULLY_TABULAR_BASIC_BIVARIATE_DISTRIBUTION_HPP
#define UTILITY_INTERPOLATED_FULLY_TABULAR_BASIC_BIVARIATE_DISTRIBUTION_HPP

// FRENSIE Includes
#include "Utility_InterpolatedTabularBasicBivariateDistributionImplBase.hpp"

namespace Utility{

/*! The unit-aware inteprolated fully tabular bivariate distribution
 * \ingroup bivariate_distributions
 */
template<typename TwoDInterpPolicy,
         typename TwoDSamplePolicy,
         typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit>
class UnitAwareInterpolatedFullyTabularBasicBivariateDistribution : public UnitAwareInterpolatedTabularBasicBivariateDistributionImplBase<TwoDInterpPolicy,UnitAwareFullyTabularBasicBivariateDistribution<PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit> >
{
  // The parent distribution type
  typedef UnitAwareInterpolatedTabularBasicBivariateDistributionImplBase<TwoDInterpPolicy,TwoDSamplePolicy,UnitAwareFullyTabularBasicBivariateDistribution<PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit> > BaseType;

  // Typedef for QuantityTraits<double>
  typedef typename BaseType::QT QT;

  // Typedef for QuantityTraits<PrimaryIndepQuantity>
  typedef typename BaseType::PIQT PIQT;

  // Typddef for QuantityTraits<SecondaryIndepQuantity>
  typedef typename BaseType::SIQT SIQT;

  // Typedef for QuantityTriats<InverseSecondaryIndepQuantity>
  typedef typename BaseType::ISIQT ISIQT;

  // Typedef for QuantityTraits<DepQuantity>
  typedef typename BaseType::DQT DQT;

  //! The distribution data const iterator
  typedef typename BaseType::DistributionDataConstIterator DistributionDataConstIterator;
  
public:

  //! This type
  typedef UnitAwareInterpolatedFullyTabularBasicBivariateDistribution<TwoDInterpPolicy,TwoDSamplePolicy,PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit> ThisType;
  
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
  UnitAwareInterpolatedFullyTabularBasicBivariateDistribution(
     const std::vector<PrimaryIndepQuantity>& primary_indep_grid,
     const std::vector<std::shared_ptr<const BaseUnivariateDistributionType> >&
     secondary_distributions,
     const double fuzzy_boundary_tol = 1e-3,
     const double evaluate_relative_error_tol = 1e-7,
     const double evaluate_error_tol = 1e-16 );

  //! Grid constructor
  UnitAwareInterpolatedFullyTabularBasicBivariateDistribution(
              const std::vector<PrimaryIndepQuantity>& primary_indep_grid,
              const std::vector<std::vector<SecondaryIndepQuantity> >& secondary_indep_grids,
              const std::vector<std::vector<DepQuantity> >& dependent_values,
              const double fuzzy_boundary_tol = 1e-3,
              const double evaluate_relative_error_tol = 1e-7,
              const double evaluate_error_tol = 1e-16 );

  //! Destructor
  virtual ~UnitAwareInterpolatedFullyTabularBasicBivariateDistribution()
  { /* ... */ }

  using ParentType::sampleSecondaryConditional;
  using ParentType::evaluateSecondaryConditionalPDF;
  using ParentType::ParentType::sampleSecondaryConditionalWithRandomNumber;
  using ParentType::ParentType::sampleSecondaryConditionalInSubrange;
  using ParentType::ParentType::sampleSecondaryConditionalWithRandomNumberInSubrange;

  //! Evaluate the secondary conditional CDF
  virtual double evaluateSecondaryConditionalCDF(
       const PrimaryIndepQuantity primary_indep_var_value,
       const SecondaryIndepQuantity secondary_indep_var_value ) const override;

  //! Evaluate the secondary conditional CDF
  double evaluateSecondaryConditionalCDF(
            const PrimaryIndepQuantity primary_indep_var_value,
            const SecondaryIndepQuantity secondary_indep_var_value,
            const std::function<SecondaryIndepQuantity(PrimaryIndepQuantity)>&
              min_secondary_indep_var_functor,
            const std::function<SecondaryIndepQuantity(PrimaryIndepQuantity)>&
              max_secondary_indep_var_functor ) const override;

  //! Return a random sample from the secondary conditional PDF and the index
  virtual SecondaryIndepQuantity sampleSecondaryConditionalAndRecordBinIndices(
                            const PrimaryIndepQuantity primary_indep_var_value,
                            size_t& primary_bin_index,
                            size_t& secondary_bin_index ) const override;

  //! Return a random sample from the secondary conditional PDF and the index
  virtual SecondaryIndepQuantity sampleSecondaryConditionalAndRecordBinIndices(
                            const PrimaryIndepQuantity primary_indep_var_value,
                            SecondaryIndepQuantity& raw_sample,
                            size_t& primary_bin_index,
                            size_t& secondary_bin_index ) const override;

  //! Return a random sample from the secondary conditional PDF at the CDF val
  virtual SecondaryIndepQuantity sampleSecondaryConditionalWithRandomNumber(
                            const PrimaryIndepQuantity primary_indep_var_value,
                            const double random_number ) const override;

  //! Return a random sample from the secondary conditional PDF at the CDF val
  SecondaryIndepQuantity sampleSecondaryConditionalWithRandomNumber(
            const PrimaryIndepQuantity primary_indep_var_value,
            const double random_number,
            const std::function<SecondaryIndepQuantity(PrimaryIndepQuantity)>&
            min_secondary_indep_var_functor,
            const std::function<SecondaryIndepQuantity(PrimaryIndepQuantity)>&
            max_secondary_indep_var_functor ) const override;

  //! Return a random sample from the secondary conditional PDF in the subrange
  virtual SecondaryIndepQuantity sampleSecondaryConditionalInSubrange(
   const PrimaryIndepQuantity primary_indep_var_value,
   const SecondaryIndepQuantity max_secondary_indep_var_value ) const override;

  //! Return a random sample from the secondary conditional PDF in the subrange
  SecondaryIndepQuantity sampleSecondaryConditionalInSubrange(
   const PrimaryIndepQuantity primary_indep_var_value,
   const std::function<SecondaryIndepQuantity(PrimaryIndepQuantity)>&
   min_secondary_indep_var_functor,
   const std::function<SecondaryIndepQuantity(PrimaryIndepQuantity)>&
   max_secondary_indep_var_functor,
   const SecondaryIndepQuantity max_secondary_indep_var_value ) const override;

  //! Return a random sample from the secondary conditional PDF in the subrange
  virtual SecondaryIndepQuantity sampleSecondaryConditionalWithRandomNumberInSubrange(
   const PrimaryIndepQuantity primary_indep_var_value,
   const double random_number,
   const SecondaryIndepQuantity max_secondary_indep_var_value ) const override;

  //! Return a random sample from the secondary conditional PDF in the subrange
  SecondaryIndepQuantity sampleSecondaryConditionalWithRandomNumberInSubrange(
    const PrimaryIndepQuantity primary_indep_var_value,
    const double random_number,
    const std::function<SecondaryIndepQuantity(PrimaryIndepQuantity)>&
    min_secondary_indep_var_functor,
    const std::function<SecondaryIndepQuantity(PrimaryIndepQuantity)>&
    max_secondary_indep_var_functor,
    const SecondaryIndepQuantity max_secondary_indep_var_value ) const override

  //! Method for placing the object in an output stream
  void toStream( std::ostream& os ) const override;

private:

  // Default constructor
  UnitAwareInterpolatedFullyTabularBasicBivariateDistribution();

  //! Evaluate the distribution using the desired CDF evaluation method
  template<typename LocalTwoDInterpPolicy, typename EvaluationMethod>
  double evaluateCDFImpl(
                        const PrimaryIndepQuantity primary_indep_var_value,
                        const SecondaryIndepQuantity secondary_indep_var_value,
                        EvaluationMethod evaluateCDF ) const;

  //! Evaluate the distribution using the desired CDF evaluation method
  template<typename LocalTwoDInterpPolicy, typename EvaluationMethod>
  double evaluateCDFImpl(
             const PrimaryIndepQuantity primary_indep_var_value,
             const SecondaryIndepQuantity secondary_indep_var_value,
             const std::function<SecondaryIndepQuantity(PrimaryIndepQuantity)>&
             min_secondary_indep_var_functor,
             const std::function<SecondaryIndepQuantity(PrimaryIndepQuantity)>&
             max_secondary_indep_var_functor,
             EvaluationMethod evaluateCDF,
             unsigned max_number_of_iterations = 500 ) const;

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

/*! \brief The interpolated fully tabular bivariate distribution 
 * (unit-agnostic)
 * \ingroup bivariate_distributions
 */
template<typename TwoDInterpPolicy> using InterpolatedFullyTabularBasicBivariateDistribution =
  UnitAwareInterpolatedFullyTabularBasicBivariateDistribution<TwoDInterpPolicy,void,void,void>;
  
} // end Utility namespace

BOOST_SERIALIZATION_DISTRIBUTION5_VERSION( UnitAwareInterpolatedFullyTabularBasicBivariateDistribution, 0 );

#define BOOST_SERIALIZATION_INTERPOLATED_FULLY_TABULAR_BASIC_BIVARIATE_DISTRIBUTION_EXPORT_STANDARD_KEY() \
  BOOST_SERIALIZATION_CLASS5_EXPORT_STANDARD_KEY( UnitAwareInterpolatedFullyTabularBasicBivariateDistribution, Utility ) \
  BOOST_SERIALIZATION_TEMPLATE_CLASS_EXPORT_KEY_IMPL(                   \
    UnitAwareInterpolatedFullyTabularBasicBivariateDistribution, Utility, \
    __BOOST_SERIALIZATION_FORWARD_AS_SINGLE_ARG__( std::string( "InterpolatedFullyTabularBasicBivariateDistribution<" ) + Utility::typeName<InterpPolicy>() + "," + Utility::typeName<SamplePolicy>() + ">" ), \
    __BOOST_SERIALIZATION_FORWARD_AS_SINGLE_ARG__( typename InterpPolicy, typename SamplePolicy ), \
    __BOOST_SERIALIZATION_FORWARD_AS_SINGLE_ARG__( InterpPolicy, SamplePolicy, void, void, void ) )

BOOST_SERIALIZATION_INTERPOLATED_FULLY_TABULAR_BASIC_BIVARIATE_DISTRIBUTION_EXPORT_STANDARD_KEY();

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "Utility_InterpolatedFullyTabularBasicBivariateDistribution_def.hpp"

//---------------------------------------------------------------------------//

#endif // end UTILITY_INTERPOLATED_FULLY_TABULAR_BASIC_BIVARIATE_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end Utility_InterpolatedFullyTabularBasicBivariateDistribution.hpp
//---------------------------------------------------------------------------//
