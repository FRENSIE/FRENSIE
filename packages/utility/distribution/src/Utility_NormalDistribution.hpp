//---------------------------------------------------------------------------//
//!
//! \file   Utility_NormalDistribution.hpp
//! \author Alex Robinson
//! \brief  Normal distribution class declaration.
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_NORMAL_DISTRIBUTION_HPP
#define UTILITY_NORMAL_DISTRIBUTION_HPP

// FRENSIE Includes
#include "Utility_UnivariateDistribution.hpp"

namespace Utility{

//! Normal distribution class
template<typename IndependentUnit, typename DependentUnit = void>
class UnitAwareNormalDistribution : public UnitAwareUnivariateDistribution<IndependentUnit,DependentUnit>
{
  // Typedef for base type
  typedef UnitAwareUnivariateDistribution<IndependentUnit,DependentUnit> BaseType;

  // The distribution normalization quantity type
  typedef typename BaseType::DistNormQuantity DistNormQuantity;

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
  typedef UnitAwareNormalDistribution<IndependentUnit,DependentUnit> ThisType;

  //! The independent quantity type
  typedef typename BaseType::IndepQuantity IndepQuantity;

  //! The inverse independent quantity type
  typedef typename BaseType::InverseIndepQuantity InverseIndepQuantity;

  //! The dependent quantity type
  typedef typename BaseType::DepQuantity DepQuantity;

  //! Constructor ( a*exp(-[x-mean]^2/[2*sigma]^2), x E (b,c) )
  template<typename InputDepQuantity = DepQuantity,
	   typename InputIndepQuantityA = IndepQuantity,
	   typename InputIndepQuantityB = IndepQuantity,
	   typename InputIndepQuantityC = IndepQuantity>
  UnitAwareNormalDistribution(
                  const InputIndepQuantityA mean =
                  ThisType::getDefaultMean<InputIndepQuantityA>(),
                  const InputIndepQuantityB standard_deviation =
                  ThisType::getDefaultStandardDeviation<InputIndepQuantityB>(),
                  const InputDepQuantity constant_multiplier =
                  ThisType::getDefaultConstMultiplier<InputDepQuantity>(),
                  const InputIndepQuantityC min_independent_value =
                  ThisType::getDefaultLowerLimit<InputIndepQuantityC>(),
                  const InputIndepQuantityC max_independent_value =
                  ThisType::getDefaultUpperLimit<InputIndepQuantityC>() );


  //! Copy constructor
  template<typename InputIndepUnit, typename InputDepUnit>
  UnitAwareNormalDistribution( const UnitAwareNormalDistribution<InputIndepUnit,InputDepUnit>& dist_instance );

  //! Construct distribution from a unitless dist. (potentially dangerous)
  static UnitAwareNormalDistribution fromUnitlessDistribution( const UnitAwareNormalDistribution<void,void>& unitless_distribution );

  //! Assignment operator
  UnitAwareNormalDistribution& operator=( const UnitAwareNormalDistribution& dist_instance );

  //! Destructor
  ~UnitAwareNormalDistribution()
  { /* ... */ }

  //! Evaluate the distribution
  DepQuantity evaluate( const IndepQuantity indep_var_value ) const override;

  //! Evaluate the PDF
  InverseIndepQuantity evaluatePDF( const IndepQuantity indep_var_value ) const override;

  //! Return a random sample from the distribution
  static IndepQuantity sample(
                             const IndepQuantity mean,
                             const IndepQuantity standard_deviation,
                             const IndepQuantity min_independent_value =
                             ThisType::getDefaultLowerLimit<IndepQuantity>(),
                             const IndepQuantity max_independent_value =
			     ThisType::getDefaultUpperLimit<IndepQuantity>() );

  //! Return a random sample from the distribution and record the trials
  static IndepQuantity sampleAndRecordTrials(
			     DistributionTraits::Counter& trials,
                             const IndepQuantity mean,
                             const IndepQuantity standard_deviation,
                             const IndepQuantity min_independent_value =
                             ThisType::getDefaultLowerLimit<IndepQuantity>(),
                             const IndepQuantity max_independent_value =
			     ThisType::getDefaultUpperLimit<IndepQuantity>() );

  //! Return a random sample from the distribution
  IndepQuantity sample() const override;

  //! Return a random sample from the distribution and record the trials
  IndepQuantity sampleAndRecordTrials( DistributionTraits::Counter& trials ) const override;

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
  bool operator==( const UnitAwareNormalDistribution& other ) const;

  //! Inequality comparison operator
  bool operator!=( const UnitAwareNormalDistribution& other ) const;
  
protected:

  //! Copy constructor (copying from unitless distribution only)
  UnitAwareNormalDistribution( const UnitAwareNormalDistribution<void,void>& unitless_dist_instance, int );

  //! Test if the dependent variable can be zero within the indep bounds
  bool canDepVarBeZeroInIndepBounds() const override;

  //! Get the default mean
  template<typename InputIndepQuantity>
  static InputIndepQuantity getDefaultMean()
  { return QuantityTraits<InputIndepQuantity>::zero(); }

  //! Get the default std deviation
  template<typename InputIndepQuantity>
  static InputIndepQuantity getDefaultStandardDeviation()
  { return QuantityTraits<InputIndepQuantity>::one(); }

  //! Get the default constant multiplier
  template<typename InputDepQuantity>
  static InputDepQuantity getDefaultConstMultiplier()
  { return QuantityTraits<InputDepQuantity>::one(); }

  //! Get the default lower limit
  template<typename InputIndepQuantity>
  static InputIndepQuantity getDefaultLowerLimit()
  { return -QuantityTraits<InputIndepQuantity>::inf(); }

  //! Get the default upper limit
  template<typename InputIndepQuantity>
  static InputIndepQuantity getDefaultUpperLimit()
  { return QuantityTraits<InputIndepQuantity>::inf(); }

private:
  
  // Verify that the shape parameters are valid
  static void verifyValidShapeParameters(
                                  const DepQuantity& const_multiplier,
                                  const IndepQuantity& mean,
                                  const IndepQuantity& standard_deviation,
                                  const IndepQuantity& min_independent_value,
                                  const IndepQuantity& max_independent_value );

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
  friend class UnitAwareNormalDistribution;

  // The distribution type
  static const UnivariateDistributionType distribution_type = NORMAL_DISTRIBUTION;

  // Constant normalization factor (1/sqrt(2*pi))
  static const double constant_norm_factor;

  // The constant multiplier
  DepQuantity d_constant_multiplier;

  // The mean of the distribution
  IndepQuantity d_mean;

  // The standard deviation of the distribution
  IndepQuantity d_standard_deviation;

  // The min independent value
  IndepQuantity d_min_independent_value;

  // The max independent value
  IndepQuantity d_max_independent_value;
};

/*! The normal distribution (unit-agnostic)
 * \ingroup univariate_distributions
 */
typedef UnitAwareNormalDistribution<void,void> NormalDistribution;

} // end Utility namespace

BOOST_SERIALIZATION_DISTRIBUTION2_VERSION( UnitAwareNormalDistribution, 0 );
BOOST_SERIALIZATION_DISTRIBUTION2_EXPORT_STANDARD_KEY( NormalDistribution );

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "Utility_NormalDistribution_def.hpp"

//---------------------------------------------------------------------------//

#endif // end UTILITY_NORMAL_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end Utility_NormalDistribution.hpp
//---------------------------------------------------------------------------//
