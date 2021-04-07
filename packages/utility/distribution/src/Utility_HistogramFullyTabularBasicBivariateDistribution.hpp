//---------------------------------------------------------------------------//
//!
//! \file   Utility_HistogramFullyTabularBasicBivariateDistribution.hpp
//! \author Alex Robinson
//! \brief  The histogram fully tabular two-dimensional dist. class decl.
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_HISTOGRAM_FULLY_TABULAR_BASIC_BIVARIATE_DISTRIBUTION_HPP
#define UTILITY_HISTOGRAM_FULLY_TABULAR_BASIC_BIVARIATE_DISTRIBUTION_HPP

// FRENSIE Includes
#include "Utility_HistogramTabularBasicBivariateDistributionImplBase.hpp"

namespace Utility{

/*! The unit-aware histogram fully tabular basic bivariate distribution
 * \ingroup bivariate_distributions
 */
template<typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit>
class UnitAwareHistogramFullyTabularBasicBivariateDistribution : public UnitAwareHistogramTabularBasicBivariateDistributionImplBase<UnitAwareFullyTabularBasicBivariateDistribution<PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit> >
{
  // The parent distribution type
  typedef UnitAwareHistogramTabularBasicBivariateDistributionImplBase<UnitAwareFullyTabularBasicBivariateDistribution<PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit> > BaseType;

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

public:

  //! This type
  typedef UnitAwareHistogramFullyTabularBasicBivariateDistribution<PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit> ThisType;

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
  UnitAwareHistogramFullyTabularBasicBivariateDistribution(
     const std::vector<PrimaryIndepQuantity>& primary_indep_grid,
     const std::vector<std::shared_ptr<const BaseUnivariateDistributionType> >&
     secondary_distributions );

  //! Destructor
  ~UnitAwareHistogramFullyTabularBasicBivariateDistribution()
  { /* ... */ }

  //! Evaluate the secondary conditional CDF
  double evaluateSecondaryConditionalCDF(
       const PrimaryIndepQuantity primary_indep_var_value,
       const SecondaryIndepQuantity secondary_indep_var_value ) const override;

  //! Return a random sample from the secondary conditional PDF and the index
  SecondaryIndepQuantity sampleSecondaryConditionalAndRecordBinIndices(
                            const PrimaryIndepQuantity primary_indep_var_value,
                            size_t& primary_bin_index,
                            size_t& secondary_bin_index ) const override;

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

  //! Method for placing the object in an output stream
  void toStream( std::ostream& os ) const override;

private:

  // Default constructor
  UnitAwareHistogramFullyTabularBasicBivariateDistribution();

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

/*! The histogram fully tabular bivariate distribution (unit-agnostic)
 * \ingroup bivariate_distributions
 */
typedef UnitAwareHistogramFullyTabularBasicBivariateDistribution<void,void,void> HistogramFullyTabularBasicBivariateDistribution;

} // end Utility namespace

BOOST_SERIALIZATION_DISTRIBUTION3_VERSION( UnitAwareHistogramFullyTabularBasicBivariateDistribution, 0 );
BOOST_SERIALIZATION_DISTRIBUTION3_EXPORT_STANDARD_KEY( HistogramFullyTabularBasicBivariateDistribution );

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "Utility_HistogramFullyTabularBasicBivariateDistribution_def.hpp"

//---------------------------------------------------------------------------//

#endif // end UTILITY_HISTOGRAM_FULLY_TABULAR_BASIC_BIVARIATE_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end Utility_HistogramFullyTabularBasicBivariateDistribution.hpp
//---------------------------------------------------------------------------//
