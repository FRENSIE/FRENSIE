//---------------------------------------------------------------------------//
//!
//! \file   Utility_PartiallyTabularBasicBivariateDistribution.hpp
//! \author Alex Robinson
//! \brief  The partially tabular basic bivariate distribution class decl.
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_PARTIALLY_TABULAR_BASIC_BIVARIATE_DISTRIBUTION_HPP
#define UTILITY_PARTIALLY_TABULAR_BASIC_BIVARIATE_DISTRIBUTION_HPP

// FRENSIE Includes
#include "Utility_TabularBasicBivariateDistribution.hpp"
#include "Utility_UnivariateDistribution.hpp"

namespace Utility{

/*! The unit-aware partially tabular bivariate distribution
 * \ingroup two_d_distribution
 */
template<typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit>
class UnitAwarePartiallyTabularBasicBivariateDistribution : public UnitAwareTabularBasicBivariateDistribution<PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit,UnitAwareUnivariateDistribution>
{

  // Typedef for this type
  typedef UnitAwarePartiallyTabularBasicBivariateDistribution<PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit> ThisType;

protected:

  //! The parent distribution type
  typedef UnitAwareTabularBasicBivariateDistribution<PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit,UnitAwareUnivariateDistribution> BaseType;

  //! Typedef for QuantityTraits<double>
  typedef QuantityTraits<double> QT;

  //! Typedef for QuantityTraits<PrimaryIndepQuantity>
  typedef QuantityTraits<typename BaseType::PrimaryIndepQuantity> PIQT;

  //! Typedef for QuantityTraits<SecondaryIndepQuantity>
  typedef QuantityTraits<typename BaseType::SecondaryIndepQuantity> SIQT;

  //! Typedef for QuantityTriats<InverseSecondaryIndepQuantity>
  typedef QuantityTraits<typename BaseType::InverseSecondaryIndepQuantity> ISIQT;

  //! Typedef for QuantityTraits<DepQuantity>
  typedef QuantityTraits<typename BaseType::DepQuantity> DQT;

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
  UnitAwarePartiallyTabularBasicBivariateDistribution(
     const std::vector<PrimaryIndepQuantity>& primary_indep_grid,
     const std::vector<std::shared_ptr<const BaseUnivariateDistributionType> >&
     secondary_distributions )
    : BaseType( primary_indep_grid, secondary_distributions )
  { /* ... */ }

  //! Destructor
  virtual ~UnitAwarePartiallyTabularBasicBivariateDistribution()
  { /* ... */ }

protected:

  //! Default constructor
  UnitAwarePartiallyTabularBasicBivariateDistribution()
  { /* ... */ }

private:

  // Save the distribution to an archive
  template<typename Archive>
  void save( Archive& ar, const unsigned version ) const
  { ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( BaseType ); }

  // Load the distribution from an archive
  template<typename Archive>
  void load( Archive& ar, const unsigned version )
  { ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( BaseType ); }

  BOOST_SERIALIZATION_SPLIT_MEMBER();

  // Declare the boost serialization access object as a friend
  friend class boost::serialization::access;
};

/*! The partially tabular bivariate distribution (unit-agnostic)
 * \ingroup bivariate_distributions
 */
typedef UnitAwarePartiallyTabularBasicBivariateDistribution<void,void,void> PartiallyTabularBasicBivariateDistribution;

} // end Utility namespace

BOOST_SERIALIZATION_ASSUME_ABSTRACT_DISTRIBUTION3( UnitAwarePartiallyTabularBasicBivariateDistribution );
BOOST_SERIALIZATION_DISTRIBUTION3_VERSION( UnitAwarePartiallyTabularBasicBivariateDistribution, 0 );

EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( Utility::UnitAwarePartiallyTabularBasicBivariateDistribution<void,void,void> );
EXTERN_EXPLICIT_CLASS_SAVE_LOAD_INST( Utility, UnitAwarePartiallyTabularBasicBivariateDistribution<void,void,void> );

#endif // end UTILITY_PARTIALLY_TABULAR_BASIC_BIVARIATE_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end Utility_PartiallyTabularBasicBivariateDistribution.hpp
//---------------------------------------------------------------------------//
