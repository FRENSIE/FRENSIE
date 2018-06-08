//---------------------------------------------------------------------------//
//!
//! \file   Utility_TabularBasicBivariateDistribution.hpp
//! \author Alex Robinson
//! \brief  The tabular bivariate distribution class declaration
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_TABULAR_BASIC_BIVARIATE_DISTRIBUTION_HPP
#define UTILITY_TABULAR_BASIC_BIVARIATE_DISTRIBUTION_HPP

// Std Lib Includes
#include <memory>

// FRENSIE Includes
#include "Utility_BasicBivariateDistribution.hpp"
#include "Utility_UnivariateDistribution.hpp"
#include "Utility_TabularUnivariateDistribution.hpp"
#include "Utility_QuantityTraits.hpp"
#include "Utility_Vector.hpp"
#include "Utility_Tuple.hpp"

namespace Utility{

/*! The unit-aware tabular bivariate distribution
 * \ingroup bivariate_distributions
 */
template<typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit,
         template<typename...> class BaseUnivariateDistribution>
class UnitAwareTabularBasicBivariateDistribution : public UnitAwareBasicBivariateDistribution<PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>
{

  // Typedef for this type
  typedef UnitAwareTabularBasicBivariateDistribution<PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit,BaseUnivariateDistribution> ThisType;

  //! The parent distribution type
  typedef UnitAwareBasicBivariateDistribution<PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit> BaseType;

  // The distribution data type
  typedef std::vector<std::pair<typename BaseType::PrimaryIndepQuantity,std::shared_ptr<const BaseUnivariateDistribution<SecondaryIndependentUnit,DependentUnit> > > > DistributionDataType;

protected:

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
  typedef typename DistributionDataType::const_iterator DistributionDataConstIterator;

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
  typedef BaseUnivariateDistribution<SecondaryIndependentUnit,DependentUnit> BaseUnivariateDistributionType;

  //! Constructor
  UnitAwareTabularBasicBivariateDistribution(
     const std::vector<PrimaryIndepQuantity>& primary_indep_grid,
     const std::vector<std::shared_ptr<const BaseUnivariateDistributionType> >&
     secondary_distributions );

  //! Destructor
  virtual ~UnitAwareTabularBasicBivariateDistribution()
  { /* ... */ }

  //! Extend the distribution beyond the primary independent variable limits
  void extendBeyondPrimaryIndepLimits();

  //! Limit the distribution to the primary independent variable limits
  void limitToPrimaryIndepLimits();

  //! Check if the distribution is being extended beyond the primary limits
  bool arePrimaryLimitsExtended() const;

  //! Return the upper bound of the distribution primary independent variable
  PrimaryIndepQuantity getUpperBoundOfPrimaryIndepVar() const override;

  //! Return the lower bound of the distribution primary independent variable
  PrimaryIndepQuantity getLowerBoundOfPrimaryIndepVar() const override;

  //! Test if the distribution is tabular in the primary dimension
  bool isPrimaryDimensionTabular() const override;

protected:

  //! Default constructor
  UnitAwareTabularBasicBivariateDistribution()
  { /* ... */ }

  //! Set the distribution
  virtual void setDistribution(
     const std::vector<PrimaryIndepQuantity>& primary_indep_grid,
     const std::vector<std::shared_ptr<const BaseUnivariateDistributionType> >&
     secondary_distributions );

  //! Find the bin boundaries
  void findBinBoundaries(
            const PrimaryIndepQuantity primary_indep_var_value,
            DistributionDataConstIterator& lower_bin_boundary,
            DistributionDataConstIterator& upper_bin_boundary ) const;

  //! Calculate the index of the desired bin
  size_t calculateBinIndex( const DistributionDataConstIterator& bin_boundary ) const;

  // Check that all secondary distributions are continuous
  bool areSecondaryDistributionsContinuous() const;

  //! Add tabular distribution data to the stream
  template<typename... Types>
  void toStreamTabularDistImpl( std::ostream& os,
                                const std::string& name,
                                const Types&... data ) const;

private:

  // Initialize the distribution
  void initialize(
     const std::vector<PrimaryIndepQuantity>& primary_indep_grid,
     const std::vector<std::shared_ptr<const BaseUnivariateDistributionType> >&
     secondary_distributions );

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

  // The distribution
  DistributionDataType d_distribution;

  // Extend beyond primary limits
  bool d_extend_beyond_primary_limits;
};

} // end Utility namespace

#if !defined SWIG

#define BOOST_SERIALIZATION_TABULAR_BASIC_BIVARIATE_DISTRIBUTION_ASSUME_ABSTRACT() \
  BOOST_SERIALIZATION_ASSUME_ABSTRACT_TEMPLATE_CLASS_IMPL(              \
    UnitAwareTabularBasicBivariateDistribution, Utility,                  \
    __BOOST_SERIALIZATION_FORWARD_AS_SINGLE_ARG__( typename T, typename U, typename V, template<typename,typename> class W ), \
    __BOOST_SERIALIZATION_FORWARD_AS_SINGLE_ARG__( T, U, V, W ) )

BOOST_SERIALIZATION_TABULAR_BASIC_BIVARIATE_DISTRIBUTION_ASSUME_ABSTRACT()

#define BOOST_SERIALIZATION_TABULAR_BASIC_BIVARIATE_DISTRIBUTION_VERSION( Version ) \
  BOOST_SERIALIZATION_TEMPLATE_CLASS_VERSION_IMPL(                      \
    UnitAwareTabularBasicBivariateDistribution, Utility, Version,         \
    __BOOST_SERIALIZATION_FORWARD_AS_SINGLE_ARG__( typename T, typename U, typename V, template<typename,typename> class W ), \
    __BOOST_SERIALIZATION_FORWARD_AS_SINGLE_ARG__( T, U, V, W ) )

//---------------------------------------------------------------------------//
// Update the version number here
//---------------------------------------------------------------------------//
BOOST_SERIALIZATION_TABULAR_BASIC_BIVARIATE_DISTRIBUTION_VERSION( 0 );

#endif // end !defined SWIG

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "Utility_TabularBasicBivariateDistribution_def.hpp"

//---------------------------------------------------------------------------//

#endif // end UTILITY_TABULAR_BASIC_BIVARIATE_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end Utility_TabularBasicBivariateDistribution.hpp
//---------------------------------------------------------------------------//
