//---------------------------------------------------------------------------//
//!
//! \file   Utility_FullyTabularBasicBivariateDistribution.hpp
//! \author Alex Robinson
//! \brief  The fully tabular basic bivariate distribution class declaration
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_FULLY_TABULAR_BASIC_BIVARIATE_DISTRIBUTION_HPP
#define UTILITY_FULLY_TABULAR_BASIC_BIVARIATE_DISTRIBUTION_HPP

// FRENSIE Includes
#include "Utility_TabularBasicBivariateDistribution.hpp"
#include "Utility_TabularUnivariateDistribution.hpp"

namespace Utility{

/*! The unit-aware fully tabular bivariate distribution
 * \ingroup bivariate_distributions
 */
template<typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit>
class UnitAwareFullyTabularBasicBivariateDistribution : public UnitAwareTabularBasicBivariateDistribution<PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit,UnitAwareTabularUnivariateDistribution>
{

  // Typedef for this type
  typedef UnitAwareFullyTabularBasicBivariateDistribution<PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit> ThisType;

protected:

  //! The parent distribution type
  typedef UnitAwareTabularBasicBivariateDistribution<PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit,UnitAwareTabularUnivariateDistribution> BaseType;

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
  UnitAwareFullyTabularBasicBivariateDistribution(
     const std::vector<PrimaryIndepQuantity>& primary_indep_grid,
     const std::vector<std::shared_ptr<const BaseUnivariateDistributionType> >&
     secondary_distributions );

  //! Destructor
  virtual ~UnitAwareFullyTabularBasicBivariateDistribution()
  { /* ... */ }

  //! Evaluate the distribution
  virtual DepQuantity evaluate(
            const PrimaryIndepQuantity primary_indep_var_value,
            const SecondaryIndepQuantity secondary_indep_var_value,
            const std::function<SecondaryIndepQuantity(PrimaryIndepQuantity)>&
              min_secondary_indep_var_functor,
            const std::function<SecondaryIndepQuantity(PrimaryIndepQuantity)>&
              max_secondary_indep_var_functor ) const;

  //! Evaluate the secondary conditional PDF
  virtual InverseSecondaryIndepQuantity evaluateSecondaryConditionalPDF(
            const PrimaryIndepQuantity primary_indep_var_value,
            const SecondaryIndepQuantity secondary_indep_var_value,
            const std::function<SecondaryIndepQuantity(PrimaryIndepQuantity)>&
              min_secondary_indep_var_functor,
            const std::function<SecondaryIndepQuantity(PrimaryIndepQuantity)>&
              max_secondary_indep_var_functor ) const;

  //! Evaluate the secondary conditional CDF
  virtual double evaluateSecondaryConditionalCDF(
            const PrimaryIndepQuantity primary_indep_var_value,
            const SecondaryIndepQuantity secondary_indep_var_value ) const = 0;

  //! Evaluate the secondary conditional CDF
  virtual double evaluateSecondaryConditionalCDF(
            const PrimaryIndepQuantity primary_indep_var_value,
            const SecondaryIndepQuantity secondary_indep_var_value,
            const std::function<SecondaryIndepQuantity(PrimaryIndepQuantity)>&
              min_secondary_indep_var_functor,
            const std::function<SecondaryIndepQuantity(PrimaryIndepQuantity)>&
              max_secondary_indep_var_functor ) const;

  //! Return a random sample from the secondary conditional PDF
  virtual SecondaryIndepQuantity sampleSecondaryConditional(
            const PrimaryIndepQuantity primary_indep_var_value,
            const std::function<SecondaryIndepQuantity(PrimaryIndepQuantity)>&
              min_secondary_indep_var_functor,
            const std::function<SecondaryIndepQuantity(PrimaryIndepQuantity)>&
              max_secondary_indep_var_functor ) const;

  using BaseType::evaluate;
  using BaseType::evaluateSecondaryConditionalPDF;
  using BaseType::sampleSecondaryConditional;

  //! Return a random sample from the secondary conditional PDF and the index
  virtual SecondaryIndepQuantity sampleSecondaryConditionalAndRecordBinIndices(
                            const PrimaryIndepQuantity primary_indep_var_value,
                            size_t& primary_bin_index,
                            size_t& secondary_bin_index ) const = 0;

  //! Return a random sample from the secondary conditional PDF and the index
  virtual SecondaryIndepQuantity sampleSecondaryConditionalAndRecordBinIndices(
                        const PrimaryIndepQuantity primary_indep_var_value,
                        SecondaryIndepQuantity& raw_sample,
                        size_t& primary_bin_index,
                        size_t& secondary_bin_index ) const;

  //! Return a random sample from the secondary conditional PDF at the CDF val
  virtual SecondaryIndepQuantity sampleSecondaryConditionalWithRandomNumber(
                            const PrimaryIndepQuantity primary_indep_var_value,
                            const double random_number ) const = 0;

  //! Return a random sample from the secondary conditional PDF at the CDF val
  virtual SecondaryIndepQuantity sampleSecondaryConditionalWithRandomNumber(
            const PrimaryIndepQuantity primary_indep_var_value,
            const double random_number,
            const std::function<SecondaryIndepQuantity(PrimaryIndepQuantity)>&
              min_secondary_indep_var_functor,
            const std::function<SecondaryIndepQuantity(PrimaryIndepQuantity)>&
              max_secondary_indep_var_functor ) const;

  //! Return a random sample from the secondary conditional PDF in the subrange
  virtual SecondaryIndepQuantity sampleSecondaryConditionalInSubrange(
        const PrimaryIndepQuantity primary_indep_var_value,
        const SecondaryIndepQuantity max_secondary_indep_var_value ) const = 0;

  //! Return a random sample from the secondary conditional PDF in the subrange
  virtual SecondaryIndepQuantity sampleSecondaryConditionalInSubrange(
            const PrimaryIndepQuantity primary_indep_var_value,
            const std::function<SecondaryIndepQuantity(PrimaryIndepQuantity)>&
              min_secondary_indep_var_functor,
            const std::function<SecondaryIndepQuantity(PrimaryIndepQuantity)>&
              max_secondary_indep_var_functor,
            const SecondaryIndepQuantity max_secondary_indep_var_value ) const;

  //! Return a random sample from the secondary conditional PDF in the subrange
  virtual SecondaryIndepQuantity sampleSecondaryConditionalWithRandomNumberInSubrange(
        const PrimaryIndepQuantity primary_indep_var_value,
        const double random_number,
        const SecondaryIndepQuantity max_secondary_indep_var_value ) const = 0;

  //! Return a random sample from the secondary conditional PDF in the subrange
  virtual SecondaryIndepQuantity sampleSecondaryConditionalWithRandomNumberInSubrange(
            const PrimaryIndepQuantity primary_indep_var_value,
            const double random_number,
            const std::function<SecondaryIndepQuantity(PrimaryIndepQuantity)>&
              min_secondary_indep_var_functor,
            const std::function<SecondaryIndepQuantity(PrimaryIndepQuantity)>&
              max_secondary_indep_var_functor,
            const SecondaryIndepQuantity max_secondary_indep_var_value ) const;

protected:

  //! Default constructor
  UnitAwareFullyTabularBasicBivariateDistribution()
  { /* ... */ }

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

/*! The fully tabular bivariate distribution (unit-agnostic)
 * \ingroup bivariate_distributions
 */
typedef UnitAwareFullyTabularBasicBivariateDistribution<void,void,void> FullyTabularBasicBivariateDistribution;

} // end utility namespace

BOOST_SERIALIZATION_ASSUME_ABSTRACT_DISTRIBUTION3( UnitAwareFullyTabularBasicBivariateDistribution );
BOOST_SERIALIZATION_DISTRIBUTION3_VERSION( UnitAwareFullyTabularBasicBivariateDistribution, 0 );

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "Utility_FullyTabularBasicBivariateDistribution_def.hpp"

//---------------------------------------------------------------------------//

#endif // end UTILITY_FULLY_TABULAR_BASIC_BIVARIATE_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end Utility_FullyTabularBasicBivariateDistribution.hpp
//---------------------------------------------------------------------------//
