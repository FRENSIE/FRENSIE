//---------------------------------------------------------------------------//
//!
//! \file   Utility_HistogramPartiallyTabularBasicBivariateDistribution.hpp
//! \author Alex Robinson
//! \brief  The histogram partially tabular basic bivariate dist. class decl.
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_HISTOGRAM_PARTIALLY_TABULAR_BASIC_BIVARIATE_DISTRIBUTION_HPP
#define UTILITY_HISTOGRAM_PARTIALLY_TABULAR_BASIC_BIVARIATE_DISTRIBUTION_HPP

// FRENSIE Includes
#include "Utility_HistogramTabularBasicBivariateDistributionImplBase.hpp"

namespace Utility{

/*! The unit-aware histogram partially tabular basic bivariate distribution
 * \ingroup bivariate_distributions
 */
template<typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit>
class UnitAwareHistogramPartiallyTabularBasicBivariateDistribution : public UnitAwareHistogramTabularBasicBivariateDistributionImplBase<UnitAwarePartiallyTabularBasicBivariateDistribution<PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit> >
{
  // The parent distribution type
  typedef UnitAwareHistogramTabularBasicBivariateDistributionImplBase<UnitAwarePartiallyTabularBasicBivariateDistribution<PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit> > BaseType;
  
public:

  //! This type
  typedef UnitAwareHistogramPartiallyTabularBasicBivariateDistribution<PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit> ThisType;
  
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
  UnitAwareHistogramPartiallyTabularBasicBivariateDistribution(
     const std::vector<PrimaryIndepQuantity>& primary_indep_grid,
     const std::vector<std::shared_ptr<const BaseUnivariateDistributionType> >&
     secondary_distributions );

  //! Destructor
  ~UnitAwareHistogramPartiallyTabularBasicBivariateDistribution()
  { /* ... */ }

  //! Method for placing the object in an output stream
  void toStream( std::ostream& os ) const override;

private:

  // Default constructor
  UnitAwareHistogramPartiallyTabularBasicBivariateDistribution();

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

/*! The histogram tabular bivariate distribution (unit-agnostic)
 * \ingroup bivariate_distributions
 */
typedef UnitAwareHistogramPartiallyTabularBasicBivariateDistribution<void,void,void> HistogramPartiallyTabularBasicBivariateDistribution;
  
} // end Utility namespace

BOOST_SERIALIZATION_DISTRIBUTION3_VERSION( UnitAwareHistogramPartiallyTabularBasicBivariateDistribution, 0 );
BOOST_SERIALIZATION_DISTRIBUTION3_EXPORT_STANDARD_KEY( HistogramPartiallyTabularBasicBivariateDistribution );

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "Utility_HistogramPartiallyTabularBasicBivariateDistribution_def.hpp"

#endif // end UTILITY_HISTOGRAM_PARTIALLY_TABULAR_BASIC_BIVARIATE_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end Utility_HistogramPartiallyTabularBasicBivariateDistribution.hpp
//---------------------------------------------------------------------------//
