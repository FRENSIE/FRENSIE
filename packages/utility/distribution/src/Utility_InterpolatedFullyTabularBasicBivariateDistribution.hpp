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
         typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit>
class UnitAwareInterpolatedFullyTabularBasicBivariateDistribution : public UnitAwareInterpolatedTabularBasicBivariateDistributionImplBase<TwoDInterpPolicy,UnitAwareFullyTabularBasicBivariateDistribution<PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit> >
{
  // The parent distribution type
  typedef UnitAwareInterpolatedTabularBasicBivariateDistributionImplBase<TwoDInterpPolicy,UnitAwareFullyTabularBasicBivariateDistribution<PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit> > BaseType;

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
  
public:

  //! This type
  typedef UnitAwareInterpolatedFullyTabularBasicBivariateDistribution<TwoDInterpPolicy,PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit> ThisType;
  
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

  //! The base univariate distribution type
  typedef typename BaseType::BaseUnivariateDistributionType BaseUnivariateDistributionType;

  //! Constructor
  UnitAwareInterpolatedFullyTabularBasicBivariateDistribution(
     const std::vector<PrimaryIndepQuantity>& primary_indep_grid,
     const std::vector<std::shared_ptr<const BaseUnivariateDistributionType> >&
     secondary_distributions );

  //! Grid constructor
  UnitAwareInterpolatedFullyTabularBasicBivariateDistribution(
              const std::vector<PrimaryIndepQuantity>& primary_indep_grid,
              const std::vector<std::vector<SecondaryIndepQuantity> >& secondary_indep_grids,
              const std::vector<std::vector<DepQuantity> >& dependent_values );

  //! Destructor
  ~UnitAwareInterpolatedFullyTabularBasicBivariateDistribution()
  { /* ... */ }

  //! Evaluate the secondary conditional CDF
  double evaluateSecondaryConditionalCDF(
       const PrimaryIndepQuantity primary_indep_var_value,
       const SecondaryIndepQuantity secondary_indep_var_value ) const override;

  //! Return a random sample from the secondary conditional PDF and the index
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
                            const double random_number ) const;

  //! Return a random sample from the secondary conditional PDF in the subrange
  SecondaryIndepQuantity sampleSecondaryConditionalInSubrange(
   const PrimaryIndepQuantity primary_indep_var_value,
   const SecondaryIndepQuantity max_secondary_indep_var_value ) const override;

  //! Return a random sample from the secondary conditional PDF in the subrange
  SecondaryIndepQuantity sampleSecondaryConditionalWithRandomNumberInSubrange(
   const PrimaryIndepQuantity primary_indep_var_value,
   const double random_number,
   const SecondaryIndepQuantity max_secondary_indep_var_value ) const override;

  //! Return a random sample from the secondary conditional PDF 
  SecondaryIndepQuantity sampleSecondaryConditionalExact(
           const PrimaryIndepQuantity primary_indep_var_value ) const override;

  //! Return a random sample from the secondary conditional PDF at the CDF val
  SecondaryIndepQuantity sampleSecondaryConditionalExactWithRandomNumber(
                            const PrimaryIndepQuantity primary_indep_var_value,
                            const double random_number ) const override;

  //! Return a random sample from the secondary conditional PDF in the subrange
  SecondaryIndepQuantity sampleSecondaryConditionalExactInSubrange(
   const PrimaryIndepQuantity primary_indep_var_value,
   const SecondaryIndepQuantity max_secondary_indep_var_value ) const override;

  //! Return a random sample from the secondary conditional PDF in the subrange
  SecondaryIndepQuantity sampleSecondaryConditionalExactWithRandomNumberInSubrange(
   const PrimaryIndepQuantity primary_indep_var_value,
   const double random_number,
   const SecondaryIndepQuantity max_secondary_indep_var_value ) const override;

  //! Method for placing the object in an output stream
  void toStream( std::ostream& os ) const override;

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

/*! \brief The interpolated fully tabular bivariate distribution 
 * (unit-agnostic)
 * \ingroup bivariate_distributions
 */
template<typename TwoDInterpPolicy> using InterpolatedFullyTabularBasicBivariateDistribution =
  UnitAwareInterpolatedFullyTabularBasicBivariateDistribution<TwoDInterpPolicy,void,void,void>;
  
} // end Utility namespace

BOOST_SERIALIZATION_DISTRIBUTION4_VERSION( UnitAwareInterpolatedFullyTabularBasicBivariateDistribution, 0 );

#define BOOST_SERIALIZATION_INTERPOLATED_FULLY_TABULAR_BASIC_BIVARIATE_DISTRIBUTION_EXPORT_STANDARD_KEY() \
  BOOST_SERIALIZATION_CLASS4_EXPORT_STANDARD_KEY( UnitAwareInterpolatedFullyTabularBasicBivariateDistribution, Utility ) \
  BOOST_SERIALIZATION_TEMPLATE_CLASS_EXPORT_KEY_IMPL(                   \
    UnitAwareInterpolatedFullyTabularBasicBivariateDistribution, Utility, \
    __BOOST_SERIALIZATION_FORWARD_AS_SINGLE_ARG__( std::string( "InterpolatedFullyTabularBasicBivariateDistribution<" ) + Utility::typeName<InterpPolicy> + ">" ), \
    __BOOST_SERIALIZATION_FORWARD_AS_SINGLE_ARG__( typename InterpPolicy ), \
    __BOOST_SERIALIZATION_FORWARD_AS_SINGLE_ARG__( InterpPolicy, void, void ) )

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
