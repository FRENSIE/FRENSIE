//---------------------------------------------------------------------------//
//!
//! \file   Utility_PowerDistribution.hpp
//! \author Alex Robinson
//! \brief  Power distribution class declaration
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_POWER_DISTRIBUTION_HPP
#define UTILITY_POWER_DISTRIBUTION_HPP

// FRENSIE Includes
#include "Utility_UnivariateDistribution.hpp"

namespace Utility{

/*! Power distribution class
 * \ingroup univariate_distributions
 */
template<size_t N, typename IndependentUnit, typename DependentUnit = void>
class UnitAwarePowerDistribution : public UnitAwareUnivariateDistribution<IndependentUnit,DependentUnit>
{
  // Typedef for base type
  typedef UnitAwareUnivariateDistribution<IndependentUnit,DependentUnit> BaseType;

  // The independent unit to power N+1
  typedef UnitTraits<typename UnitTraits<IndependentUnit>::template GetUnitToPowerType<N+1>::type> IndepUnitTraitsNp1;

  // The independent unit to power N+1 quantity type
  typedef typename IndepUnitTraitsNp1::template GetQuantityType<double>::type IndepQuantityNp1;

  // The distribution multiplier unit traits
  typedef UnitTraits<typename UnitTraits<DependentUnit>::template GetMultipliedUnitType<typename UnitTraits<IndependentUnit>::template GetUnitToPowerType<N,-1>::type>::type> DistMultiplierUnitTraits;

  // The distribution multiplier quantity type
  typedef typename DistMultiplierUnitTraits::template GetQuantityType<double>::type DistMultiplierQuantity;

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

  // Typedef for QuantityTraits<DistMultiplierQuantity>
  typedef QuantityTraits<DistMultiplierQuantity> DMQT;

public:

  //! This distribution type
  typedef UnitAwarePowerDistribution<N,IndependentUnit,DependentUnit> ThisType;

  //! The independent quantity type
  typedef typename BaseType::IndepQuantity IndepQuantity;

  //! The inverse independent quantity type
  typedef typename BaseType::InverseIndepQuantity InverseIndepQuantity;

  //! The dependent quantity type
  typedef typename BaseType::DepQuantity DepQuantity;

  //! Constructor ( A*x^N : x in (a,b) )
  template<typename InputIndepQuantity = IndepQuantity>
  UnitAwarePowerDistribution(
                        const double constant_multiplier =
                        ThisType::getDefaultConstMultiplier<double>(),
                        const InputIndepQuantity min_indep_limit =
                        ThisType::getDefaultLowerLimit<InputIndepQuantity>(),
                        const InputIndepQuantity max_indep_limit =
                        ThisType::getDefaultUpperLimit<InputIndepQuantity>() );

  //! Copy constructor
  template<typename InputIndepUnit, typename InputDepUnit>
  UnitAwarePowerDistribution( const UnitAwarePowerDistribution<N,InputIndepUnit,InputDepUnit>& dist_instance );

  //! Construct distribution from a unitless dist. (potentially dangerous)
  static UnitAwarePowerDistribution fromUnitlessDistribution( const UnitAwarePowerDistribution<N,void,void>& unitless_distribution );

  //! Assignment operator
  UnitAwarePowerDistribution& operator=( const UnitAwarePowerDistribution& dist_instance );

  //! Destructor (virtual for python interface extenstions)
  virtual ~UnitAwarePowerDistribution()
  { /* ... */ }

  //! Evaluate the distribution
  DepQuantity evaluate( const IndepQuantity indep_var_value ) const override;

  //! Evaluate the PDF
  InverseIndepQuantity evaluatePDF( const IndepQuantity indep_var_value) const override;

  //! Return a random sample from the distribution
  IndepQuantity sample() const override;

  //! Return a random sample from the distribution
  static IndepQuantity sample( const IndepQuantity min_independent_value,
			       const IndepQuantity max_independent_value );

  //! Return a random sample and record the number of trials
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
  bool operator==( const UnitAwarePowerDistribution& other ) const;

  //! Inequality comparison operator
  bool operator!=( const UnitAwarePowerDistribution& other ) const;

protected:

  //! Copy constructor (copying from unitless distribution only)
  UnitAwarePowerDistribution( const UnitAwarePowerDistribution<N,void,void>& unitless_dist_instance, int );

  //! Test if the dependent variable can be zero within the indep bounds
  bool canDepVarBeZeroInIndepBounds() const;

  //! Get the default constant multiplier
  template<typename InputDepQuantity>
  static InputDepQuantity getDefaultConstMultiplier()
  { return QuantityTraits<InputDepQuantity>::one(); }

  //! Get the default lower limit
  template<typename InputIndepQuantity>
  static InputIndepQuantity getDefaultLowerLimit()
  { return QuantityTraits<InputIndepQuantity>::zero(); }

  //! Get the default upper limit
  template<typename InputIndepQuantity>
  static InputIndepQuantity getDefaultUpperLimit()
  { return QuantityTraits<InputIndepQuantity>::one(); }

private:

  // Initialize the distribution
  void initializeDistribution();

  // Verify that the shape parameters are valid
  static void verifyValidShapeParameters(
                                const DistMultiplierQuantity& const_multiplier,
                                const IndepQuantity& lower_limit,
                                const IndepQuantity& upper_limit );

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
  template<size_t M, typename FriendIndepUnit, typename FriendDepUnit>
  friend class UnitAwarePowerDistribution;

  // The distribution type
  static const UnivariateDistributionType distribution_type = POWER_DISTRIBUTION;

  // The multiplier
  DistMultiplierQuantity d_multiplier;

  // The min independent variable limit
  IndepQuantity d_min_indep_limit;

  // The min independent variable limit to the power N+1
  IndepQuantityNp1 d_min_indep_limit_to_power_Np1;

  // The max independent variable limit
  IndepQuantity d_max_indep_limit;

  // The max independent variable limit to the power N+1
  IndepQuantityNp1 d_max_indep_limit_to_power_Np1;

  // The normalization constant
  DistNormQuantity d_norm_constant;
};

/*! The power distribution (unit-agnostic)
 * \ingroup univariate_distributions
 */
template<unsigned N> using PowerDistribution =
  UnitAwarePowerDistribution<N,void,void>;

} // end Utility namespace

#define BOOST_SERIALIZATION_POWER_DISTRIBUTION_VERSION( VERSION )       \
  BOOST_SERIALIZATION_TEMPLATE_CLASS_VERSION_IMPL(                      \
    UnitAwarePowerDistribution, Utility, VERSION,                         \
    __BOOST_SERIALIZATION_FORWARD_AS_SINGLE_ARG__( size_t N, typename T, typename U ), \
    __BOOST_SERIALIZATION_FORWARD_AS_SINGLE_ARG__( N, T, U ) )

//---------------------------------------------------------------------------//
// Update the version number here
//---------------------------------------------------------------------------//

BOOST_SERIALIZATION_POWER_DISTRIBUTION_VERSION( 0 );

//---------------------------------------------------------------------------//

#define BOOST_SERIALIZATION_POWER_DISTRIBUTION_EXPORT_STANDARD_KEY()    \
  BOOST_SERIALIZATION_TEMPLATE_CLASS_EXPORT_KEY_IMPL( \
    UnitAwarePowerDistribution, Utility, \
    __BOOST_SERIALIZATION_FORWARD_AS_SINGLE_ARG__( std::string( "UnitAwarePowerDistribution<" ) + Utility::toString( N ) + "," + Utility::typeName<T,U>() + ">" ), \
    __BOOST_SERIALIZATION_FORWARD_AS_SINGLE_ARG__( size_t N, typename T, typename U ),  \
    __BOOST_SERIALIZATION_FORWARD_AS_SINGLE_ARG__( N, T, U ) )          \
                                                                        \
  BOOST_SERIALIZATION_TEMPLATE_CLASS_EXPORT_KEY_IMPL(                   \
    UnitAwarePowerDistribution, Utility, \
    __BOOST_SERIALIZATION_FORWARD_AS_SINGLE_ARG__( std::string( "PowerDistribution<" ) + Utility::toString( N ) + ">" ), \
    __BOOST_SERIALIZATION_FORWARD_AS_SINGLE_ARG__( size_t N ),  \
    __BOOST_SERIALIZATION_FORWARD_AS_SINGLE_ARG__( N, void, void ) )

BOOST_SERIALIZATION_POWER_DISTRIBUTION_EXPORT_STANDARD_KEY()

//---------------------------------------------------------------------------//
// Template includes
//---------------------------------------------------------------------------//

#include "Utility_PowerDistribution_def.hpp"

//---------------------------------------------------------------------------//

#endif // end UTILITY_POWER_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end Utility_PowerDistribution.hpp
//---------------------------------------------------------------------------//
