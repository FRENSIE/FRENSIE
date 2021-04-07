//---------------------------------------------------------------------------//
//!
//! \file   Utility_DeltaDistribution.hpp
//! \author Alex Robinson
//! \brief  Delta distribution class declaration.
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_DELTA_DISTRIBUTION_HPP
#define UTILITY_DELTA_DISTRIBUTION_HPP

// FRENSIE Includes
#include "Utility_TabularUnivariateDistribution.hpp"
#include "Utility_QuantityTraits.hpp"
#include "Utility_UnitTraits.hpp"

namespace Utility{

/*! The unit-aware delta distribution class
 * \ingroup univariate_distributions
 */
template<typename IndependentUnit, typename DependentUnit>
class UnitAwareDeltaDistribution : public UnitAwareTabularUnivariateDistribution<IndependentUnit,DependentUnit>
{
  // Typedef for base type
  typedef UnitAwareTabularUnivariateDistribution<IndependentUnit,DependentUnit> BaseType;

  // Typedef for QuantityTraits<double>
  typedef QuantityTraits<double> QT;

  // Typedef for QuantityTraits<IndepQuantity>
  typedef QuantityTraits<typename BaseType::IndepQuantity> IQT;

  // Typedef for QuantityTraits<InverseIndepQuantity>
  typedef QuantityTraits<typename BaseType::InverseIndepQuantity> IIQT;

  // Typedef for QuantityTraits<DepQuantity>
  typedef QuantityTraits<typename BaseType::DepQuantity> DQT;

public:

  //! This distribution type
  typedef UnitAwareDeltaDistribution<IndependentUnit,DependentUnit> ThisType;

  //! The independent quantity type
  typedef typename BaseType::IndepQuantity IndepQuantity;

  //! The inverse independent quantity type
  typedef typename BaseType::InverseIndepQuantity InverseIndepQuantity;

  //! The dependent quantity type
  typedef typename BaseType::DepQuantity DepQuantity;

  //! Constructor
  template<typename InputIndepQuantity = IndepQuantity,
           typename InputDepQuantity = DepQuantity>
  UnitAwareDeltaDistribution(
                          const InputIndepQuantity location =
                          ThisType::getDefaultLocation<InputIndepQuantity>(),
                          const InputDepQuantity multiplier =
                          ThisType::getDefaultMultiplier<InputDepQuantity>() );

  //! Copy constructor
  template<typename InputIndepUnit, typename InputDepUnit, typename Dummy=void>
  UnitAwareDeltaDistribution( const UnitAwareDeltaDistribution<InputIndepUnit,InputDepUnit>& dist_instance );

  //! Construct distribution from a unitless dist. (potentially dangerous)
  static UnitAwareDeltaDistribution fromUnitlessDistribution( const UnitAwareDeltaDistribution<void,void>& unitless_distribution );

  //! Assignment operator
  UnitAwareDeltaDistribution& operator=( const UnitAwareDeltaDistribution& dist_instance );

  //! Destructor
  ~UnitAwareDeltaDistribution()
  { /* ... */ }

  //! Evaluate the distribution
  DepQuantity evaluate( const IndepQuantity indep_var_value ) const override;

  //! Evaluate the PDF
  InverseIndepQuantity evaluatePDF( const IndepQuantity indep_var_value ) const override;

  //! Evaluate the CDF
  double evaluateCDF( const IndepQuantity indep_var_value ) const override;

  //! Return a random sample from the corresponding CDF
  IndepQuantity sample() const override;

  //! Return a random sample from the corresponding CDF and record the number of trials
  IndepQuantity sampleAndRecordTrials( DistributionTraits::Counter& trials ) const override;

  //! Return a random sample from the distribution and the sampled index
  IndepQuantity sampleAndRecordBinIndex( size_t& sampled_bin_index ) const override;

  //! Return a random sample from the distribution at the given CDF value
  IndepQuantity sampleWithRandomNumber( const double random_number ) const override;

  //! Return a random sample from the distribution in a subrange
  IndepQuantity sampleInSubrange( const IndepQuantity max_indep_var ) const override;

  //! Return a random sample from the distribution at the given CDF value in a subrange
  IndepQuantity sampleWithRandomNumberInSubrange(
				     const double random_number,
				     const IndepQuantity max_indep_var ) const override;

  //! Return the upper bound of the distribution independent variable
  IndepQuantity getUpperBoundOfIndepVar() const override;

  //! Return the lower bound of the distribution independent variable
  IndepQuantity getLowerBoundOfIndepVar() const override;

  //! Return the distribution type
  UnivariateDistributionType getDistributionType() const override;

  //! Test if the distribution is continuous
  bool isContinuous() const override;

  //! Method for placing the object in an output stream
  void toStream( std::ostream& os ) const override;

  //! Equality comparison operator
  bool operator==( const UnitAwareDeltaDistribution& other ) const;

  //! Inequality comparison operator
  bool operator!=( const UnitAwareDeltaDistribution& other ) const;

protected:

  //! Copy constructor (copying from unitless distribution only)
  UnitAwareDeltaDistribution( const UnitAwareDeltaDistribution<void,void>& unitless_dist_instance, int );

  //! Test if the dependent variable can be zero within the indep bounds
  bool canDepVarBeZeroInIndepBounds() const override;

  //! Get the default location
  template<typename InputIndepQuantity>
  static InputIndepQuantity getDefaultLocation()
  { return QuantityTraits<InputIndepQuantity>::zero(); }

  //! Get the default constant multiplier
  template<typename InputDepQuantity>
  static InputDepQuantity getDefaultMultiplier()
  { return QuantityTraits<InputDepQuantity>::one(); }

private:

  // Verify that the shape parameters are valid
  static void verifyValidShapeParameters( const IndepQuantity& location,
                                          const DepQuantity& multiplier );

  // Save the distribution to an archive
  template<typename Archive>
  void save( Archive& ar, const unsigned version ) const;

  // Load the distribution from an archive
  template<typename Archive>
  void load( Archive& ar, const unsigned version );

  BOOST_SERIALIZATION_SPLIT_MEMBER();

  // Declare the boost serialization access object as a friend
  friend class boost::serialization::access;

  // All possible instantiations are friends
  template<typename FriendIndepUnit, typename FriendDepUnit>
  friend class UnitAwareDeltaDistribution;

  // The distribution type
  static const UnivariateDistributionType distribution_type = DELTA_DISTRIBUTION;

  // The location of the delta distribution
  IndepQuantity d_location;

  // The multiplier
  DepQuantity d_multiplier;
};

/*! The delta distribution (unit-agnostic)
 * \ingroup univariate_distributions
 */
typedef UnitAwareDeltaDistribution<void,void> DeltaDistribution;

} // end Utility namespace

BOOST_SERIALIZATION_DISTRIBUTION2_VERSION( UnitAwareDeltaDistribution, 0 );
BOOST_SERIALIZATION_DISTRIBUTION2_EXPORT_STANDARD_KEY( DeltaDistribution );

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "Utility_DeltaDistribution_def.hpp"

//---------------------------------------------------------------------------//

#endif // end UTILITY_DELTA_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end Utility_DeltaDistribution.hpp
//---------------------------------------------------------------------------//
