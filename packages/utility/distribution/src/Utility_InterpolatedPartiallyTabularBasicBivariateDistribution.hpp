//---------------------------------------------------------------------------//
//!
//! \file   Utility_InterpolatedPartiallyTabularBasicBivariateDistribution.hpp
//! \author Alex Robinson
//! \brief  The interpolated partially tabular basic bivariate dist. class
//!         declaration
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_INTERPOLATED_PARTIALLY_TABULAR_BASIC_BIVARIATE_DISTRIBUTION_HPP
#define UTILITY_INTERPOLATED_PARTIALLY_TABULAR_BASIC_BIVARIATE_DISTRIBUTION_HPP

// FRENSIE Includes
#include "Utility_InterpolatedTabularBasicBivariateDistributionImplBase.hpp"

namespace Utility{

/*! The unit-aware interpolated partially tabular bivariate distribution
 * \ingroup bivariate_distributions
 */
template<typename TwoDGridPolicy,
         typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit>
class UnitAwareInterpolatedPartiallyTabularBasicBivariateDistribution : public UnitAwareInterpolatedTabularBasicBivariateDistributionImplBase<TwoDGridPolicy,UnitAwarePartiallyTabularBasicBivariateDistribution<PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit> >
{
  // The parent distribution type
  typedef UnitAwareInterpolatedTabularBasicBivariateDistributionImplBase<TwoDGridPolicy,UnitAwarePartiallyTabularBasicBivariateDistribution<PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit> > BaseType;
  
public:

  //! This type
  typedef UnitAwareInterpolatedPartiallyTabularBasicBivariateDistribution<TwoDGridPolicy,PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit> ThisType;
  
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

  // Default constructor
  UnitAwareInterpolatedPartiallyTabularBasicBivariateDistribution();
  
  //! Constructor
  UnitAwareInterpolatedPartiallyTabularBasicBivariateDistribution(
     const std::vector<PrimaryIndepQuantity>& primary_indep_grid,
     const std::vector<std::shared_ptr<const BaseUnivariateDistributionType> >&
     secondary_distributions,
     const double fuzzy_boundary_tol = 1e-3,
     const double relative_error_tol = 1e-7,
     const double error_tol = 1e-16 );

  //! Destructor
  ~UnitAwareInterpolatedPartiallyTabularBasicBivariateDistribution()
  { /* ... */ }

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

/*! \brief The interpolated partially tabular bivariate distribution 
 * (unit-agnostic)
 * \ingroup bivariate_distributions
 */
template<typename TwoDGridPolicy> using InterpolatedPartiallyTabularBasicBivariateDistribution =
UnitAwareInterpolatedPartiallyTabularBasicBivariateDistribution<TwoDGridPolicy,void,void,void>;
  
} // end Utility namespace

BOOST_SERIALIZATION_DISTRIBUTION4_VERSION( UnitAwareInterpolatedPartiallyTabularBasicBivariateDistribution, 0 );

#define BOOST_SERIALIZATION_INTERPOLATED_PARTIALLY_TABULAR_BASIC_BIVARIATE_DISTRIBUTION_EXPORT_STANDARD_KEY() \
  BOOST_SERIALIZATION_CLASS4_EXPORT_STANDARD_KEY( UnitAwareInterpolatedPartiallyTabularBasicBivariateDistribution, Utility ) \
  BOOST_SERIALIZATION_TEMPLATE_CLASS_EXPORT_KEY_IMPL(                   \
    UnitAwareInterpolatedPartiallyTabularBasicBivariateDistribution, Utility, \
    __BOOST_SERIALIZATION_FORWARD_AS_SINGLE_ARG__( std::string( "InterpolatedPartiallyTabularBasicBivariateDistribution<" ) + Utility::typeName<GridPolicy>() + ">" ), \
    __BOOST_SERIALIZATION_FORWARD_AS_SINGLE_ARG__( typename GridPolicy ), \
    __BOOST_SERIALIZATION_FORWARD_AS_SINGLE_ARG__( GridPolicy, void, void, void ) )

BOOST_SERIALIZATION_INTERPOLATED_PARTIALLY_TABULAR_BASIC_BIVARIATE_DISTRIBUTION_EXPORT_STANDARD_KEY();

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "Utility_InterpolatedPartiallyTabularBasicBivariateDistribution_def.hpp"

//---------------------------------------------------------------------------//

#endif // end UTILITY_INTERPOLATED_PARTIALLY_TABULAR_BASIC_BIVARIATE_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end Utility_InterpolatedPartiallyTabularBasicBivariateDistribution.hpp
//---------------------------------------------------------------------------//
