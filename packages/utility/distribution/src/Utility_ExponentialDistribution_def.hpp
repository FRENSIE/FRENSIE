//---------------------------------------------------------------------------//
//!
//! \file   Utility_ExponentialDistribution.cpp
//! \author Alex Robinson
//! \brief  Exponential distribution class definition.
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_EXPONENTIAL_DISTRIBUTION_DEF_HPP
#define UTILITY_EXPONENTIAL_DISTRIBUTION_DEF_HPP

// FRENSIE Includes
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_ExceptionCatchMacros.hpp"
#include "Utility_DesignByContract.hpp"

BOOST_SERIALIZATION_DISTRIBUTION2_EXPORT_IMPLEMENT( UnitAwareExponentialDistribution );

namespace Utility{

// Constructor
/*! \details This constructor will explicitly cast the input quantities to
 * the distribution quantity (which includes any unit-conversion). The
 * dimension type must match and there must be a unit-conversion defined using
 * the boost methodology.
 */
template<typename IndependentUnit, typename DependentUnit>
template<typename InputDepQuantity,
	 typename InputInverseIndepQuantity,
         typename InputIndepQuantity>
UnitAwareExponentialDistribution<IndependentUnit,DependentUnit>::UnitAwareExponentialDistribution(
			 const InputDepQuantity constant_multiplier,
			 const InputInverseIndepQuantity exponent_multiplier,
			 const InputIndepQuantity lower_limit,
			 const InputIndepQuantity upper_limit )
  : d_constant_multiplier( constant_multiplier ),
    d_exponent_multiplier( exponent_multiplier ),
    d_lower_limit( lower_limit ),
    d_upper_limit( upper_limit )
{
  // Verify that the shape parameters are valid
  this->verifyValidShapeParameters( d_constant_multiplier,
                                    d_exponent_multiplier,
                                    d_lower_limit,
                                    d_upper_limit );
  
  // Initialize the distribution
  this->initialize();

  BOOST_SERIALIZATION_CLASS_EXPORT_IMPLEMENT_FINALIZE( ThisType );
}

// Copy constructor
/*! \details Just like boost::units::quantity objects, the unit-aware
 * distribution can be explicitly cast to a distribution with compatible
 * units. If the units are not compatible, this function will not compile. Note
 * that this allows distributions to be scaled safely (unit conversions
 * are completely taken care of by boost::units)!
 */
template<typename IndependentUnit, typename DependentUnit>
template<typename InputIndepUnit, typename InputDepUnit>
UnitAwareExponentialDistribution<IndependentUnit,DependentUnit>::UnitAwareExponentialDistribution( const UnitAwareExponentialDistribution<InputIndepUnit,InputDepUnit>& dist_instance )
  : d_constant_multiplier( dist_instance.d_constant_multiplier ),
    d_exponent_multiplier( dist_instance.d_exponent_multiplier ),
    d_lower_limit( dist_instance.d_lower_limit ),
    d_upper_limit( dist_instance.d_upper_limit )
{
  // Initialize the distribution
  this->initialize();

  BOOST_SERIALIZATION_CLASS_EXPORT_IMPLEMENT_FINALIZE( ThisType );
}

// Copy constructor (copying from unitless distribution only)
template<typename IndependentUnit, typename DependentUnit>
UnitAwareExponentialDistribution<IndependentUnit,DependentUnit>::UnitAwareExponentialDistribution( const UnitAwareExponentialDistribution<void,void>& unitless_dist_instance, int )
  : d_constant_multiplier( DQT::initializeQuantity( unitless_dist_instance.d_constant_multiplier ) ),
    d_exponent_multiplier( IIQT::initializeQuantity( unitless_dist_instance.d_exponent_multiplier ) ),
    d_lower_limit( IQT::initializeQuantity( unitless_dist_instance.d_lower_limit ) ),
    d_upper_limit( IQT::initializeQuantity( unitless_dist_instance.d_upper_limit ) )
{
  // Initialize the distribution
  this->initialize();

  BOOST_SERIALIZATION_CLASS_EXPORT_IMPLEMENT_FINALIZE( ThisType );
}

// Construct distribution from a unitless dist. (potentially dangerous)
/*! \details Constructing a unit-aware distribution from a unitless
 * distribution is potentially dangerous. By forcing users to construct objects
 * using this method instead of a standard constructor we are trying to make
 * sure users are aware of the danger. This is designed to mimic the interface
 * of the boost::units::quantity, which also has to deal with this issue.
 */
template<typename IndependentUnit, typename DependentUnit>
UnitAwareExponentialDistribution<IndependentUnit,DependentUnit>
UnitAwareExponentialDistribution<IndependentUnit,DependentUnit>::fromUnitlessDistribution( const UnitAwareExponentialDistribution<void,void>& unitless_distribution )
{
  return ThisType( unitless_distribution, 0 );
}

// Assignment operator
template<typename IndependentUnit, typename DependentUnit>
UnitAwareExponentialDistribution<IndependentUnit,DependentUnit>&
UnitAwareExponentialDistribution<IndependentUnit,DependentUnit>::operator=(
 const UnitAwareExponentialDistribution<IndependentUnit,DependentUnit>& dist_instance )
{
  if( this != &dist_instance )
  {
    d_constant_multiplier = dist_instance.d_constant_multiplier;
    d_exponent_multiplier = dist_instance.d_exponent_multiplier;
    d_lower_limit = dist_instance.d_lower_limit;
    d_upper_limit = dist_instance.d_upper_limit;
    d_exp_lower_limit = dist_instance.d_exp_lower_limit;
    d_exp_upper_limit = dist_instance.d_exp_upper_limit;
  }

  return *this;
}

// Evaluate the distribution
template<typename IndependentUnit, typename DependentUnit>
typename UnitAwareExponentialDistribution<IndependentUnit,DependentUnit>::DepQuantity
UnitAwareExponentialDistribution<IndependentUnit,DependentUnit>::evaluate(
 const typename UnitAwareExponentialDistribution<IndependentUnit,DependentUnit>::IndepQuantity indep_var_value ) const
{
  if( indep_var_value < d_lower_limit )
    return DQT::zero();
  else if( indep_var_value > d_upper_limit )
    return DQT::zero();
  else
    return d_constant_multiplier*exp( -d_exponent_multiplier*indep_var_value );
}

// Evaluate the PDF
/*! \details PDF(x) = m*exp(-m*x) if x >= 0, = 0 if x < 0
 */
template<typename IndependentUnit, typename DependentUnit>
typename UnitAwareExponentialDistribution<IndependentUnit,DependentUnit>::InverseIndepQuantity
UnitAwareExponentialDistribution<IndependentUnit,DependentUnit>::evaluatePDF(
 const typename UnitAwareExponentialDistribution<IndependentUnit,DependentUnit>::IndepQuantity indep_var_value ) const
{
  if( indep_var_value < d_lower_limit )
    return IIQT::zero();
  else if( indep_var_value > d_upper_limit )
    return IIQT::zero();
  else
    return d_exponent_multiplier*exp( -d_exponent_multiplier*indep_var_value )/
      (d_exp_lower_limit - d_exp_upper_limit);
}

// Return a sample from the distribution
/* \details x = -ln(rnd)/m
 */
template<typename IndependentUnit, typename DependentUnit>
typename UnitAwareExponentialDistribution<IndependentUnit,DependentUnit>::IndepQuantity
UnitAwareExponentialDistribution<IndependentUnit,DependentUnit>::sample(
  const typename UnitAwareExponentialDistribution<IndependentUnit,DependentUnit>::InverseIndepQuantity exponent_multiplier )
{
  // Make sure that the exponent multiplier is positive
  testPrecondition( exponent_multiplier > IIQT::zero() );

  return -log( 1.0 - RandomNumberGenerator::getRandomNumber<double>() )/
    exponent_multiplier;
}

// Return a sample from the distribution
/* \details x = -ln(exp(-m*lb) - rnd*[exp(-m*lb)-exp(-m*ub)])/m
 */
template<typename IndependentUnit, typename DependentUnit>
typename UnitAwareExponentialDistribution<IndependentUnit,DependentUnit>::IndepQuantity
UnitAwareExponentialDistribution<IndependentUnit,DependentUnit>::sample(
  const typename UnitAwareExponentialDistribution<IndependentUnit,DependentUnit>::InverseIndepQuantity exponent_multiplier,
  const typename UnitAwareExponentialDistribution<IndependentUnit,DependentUnit>::IndepQuantity lower_limit,
  const typename UnitAwareExponentialDistribution<IndependentUnit,DependentUnit>::IndepQuantity upper_limit )
{
  // Make sure that the exponent multiplier is positive
  testPrecondition( exponent_multiplier > IIQT::zero() );
  // Make sure the limits are valid
  testPrecondition( lower_limit >= IQT::zero() );
  testPrecondition( upper_limit > lower_limit );

  double exp_upper_limit;

  if( upper_limit < IQT::inf() )
    exp_upper_limit = exp( -exponent_multiplier*upper_limit );
  else
    exp_upper_limit = 0.0;

  double exp_lower_limit;

  if( lower_limit > IQT::zero() )
    exp_lower_limit = exp( -exponent_multiplier*lower_limit );
  else
    exp_lower_limit = 1.0;

  double random_number = RandomNumberGenerator::getRandomNumber<double>();

  return -log( exp_lower_limit -
               random_number*(exp_lower_limit - exp_upper_limit) )/
    exponent_multiplier;
}

// Return a sample from the distribution
/*! \details x = -ln(exp(-m*lb) - rnd*[exp(-m*lb)-exp(-m*ub)])/m
 */
template<typename IndependentUnit, typename DependentUnit>
typename UnitAwareExponentialDistribution<IndependentUnit,DependentUnit>::IndepQuantity
UnitAwareExponentialDistribution<IndependentUnit,DependentUnit>::sample() const
{
  double random_number = RandomNumberGenerator::getRandomNumber<double>();

  return -log( d_exp_lower_limit -
               random_number*(d_exp_lower_limit-d_exp_upper_limit) )/
    d_exponent_multiplier;
}

// Return a random sample and record the number of trials
template<typename IndependentUnit, typename DependentUnit>
typename UnitAwareExponentialDistribution<IndependentUnit,DependentUnit>::IndepQuantity
UnitAwareExponentialDistribution<IndependentUnit,DependentUnit>::sampleAndRecordTrials( DistributionTraits::Counter& trials ) const
{
  ++trials;

  return this->sample();
}

// Return the upper bound of the distribution independent variable
template<typename IndependentUnit, typename DependentUnit>
typename UnitAwareExponentialDistribution<IndependentUnit,DependentUnit>::IndepQuantity
UnitAwareExponentialDistribution<IndependentUnit,DependentUnit>::getUpperBoundOfIndepVar() const
{
  return d_upper_limit;
}

// Return the lower bound of the distribution independent variable
template<typename IndependentUnit, typename DependentUnit>
typename UnitAwareExponentialDistribution<IndependentUnit,DependentUnit>::IndepQuantity
UnitAwareExponentialDistribution<IndependentUnit,DependentUnit>::getLowerBoundOfIndepVar() const
{
  return d_lower_limit;
}

// Return the distribution type
template<typename IndependentUnit, typename DependentUnit>
UnivariateDistributionType
UnitAwareExponentialDistribution<IndependentUnit,DependentUnit>::getDistributionType() const
{
  return ThisType::distribution_type;
}

// Test if the distribution is continuous
template<typename IndependentUnit, typename DependentUnit>
bool
UnitAwareExponentialDistribution<IndependentUnit,DependentUnit>::isContinuous() const
{
  return true;
}

// Method for placing the object in an output stream
template<typename IndependentUnit, typename DependentUnit>
void
UnitAwareExponentialDistribution<IndependentUnit,DependentUnit>::toStream( std::ostream& os ) const
{
  this->toStreamWithLimitsDistImpl( os,
                                    std::make_pair( "exponent multiplier", d_exponent_multiplier ),
                                    std::make_pair( "multiplier", d_constant_multiplier ) );
}

// Save the distribution to an archive
template<typename IndependentUnit, typename DependentUnit>
template<typename Archive>
void UnitAwareExponentialDistribution<IndependentUnit,DependentUnit>::save( Archive& ar, const unsigned version ) const
{
  // Save the base class first
  ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( BaseType );

  // Save the local member data
  ar & BOOST_SERIALIZATION_NVP( d_constant_multiplier );
  ar & BOOST_SERIALIZATION_NVP( d_exponent_multiplier );
  ar & BOOST_SERIALIZATION_NVP( d_lower_limit );

  // We cannot safely serialize inf to all archive types - create flag that
  // records if the upper limit is inf
  const bool __upper_limit_is_inf__ = (d_upper_limit == IQT::inf());
  
  ar & BOOST_SERIALIZATION_NVP( __upper_limit_is_inf__ );
  
  if( __upper_limit_is_inf__ )
  {
    IndepQuantity tmp_upper_limit = IQT::max();
    ar & boost::serialization::make_nvp( "d_upper_limit", tmp_upper_limit );
  }
  else
  {
    ar & BOOST_SERIALIZATION_NVP( d_upper_limit );
  }
}

// Load the distribution from an archive
template<typename IndependentUnit, typename DependentUnit>
template<typename Archive>
void UnitAwareExponentialDistribution<IndependentUnit,DependentUnit>::load( Archive& ar, const unsigned version )
{
  // Load the base class first
  ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( BaseType );

  // Load the local member data
  ar & BOOST_SERIALIZATION_NVP( d_constant_multiplier );
  ar & BOOST_SERIALIZATION_NVP( d_exponent_multiplier );
  ar & BOOST_SERIALIZATION_NVP( d_lower_limit );

  // Load the upper limit inf flag
  bool __upper_limit_is_inf__;
  ar & BOOST_SERIALIZATION_NVP( __upper_limit_is_inf__ );
  
  ar & BOOST_SERIALIZATION_NVP( d_upper_limit );

  // Restore the inf value of the upper limit
  if( __upper_limit_is_inf__ )
    d_upper_limit = IQT::inf();

  this->initialize();
}

// Method for testing if two objects are equivalent
template<typename IndependentUnit, typename DependentUnit>
bool UnitAwareExponentialDistribution<IndependentUnit,DependentUnit>::operator==(
                          const UnitAwareExponentialDistribution& other ) const
{
  return d_constant_multiplier == other.d_constant_multiplier &&
    d_exponent_multiplier == other.d_exponent_multiplier &&
    d_lower_limit == other.d_lower_limit &&
    d_upper_limit == other.d_upper_limit;
}

// Method for testing if two objects are equivalent
template<typename IndependentUnit, typename DependentUnit>
bool UnitAwareExponentialDistribution<IndependentUnit,DependentUnit>::operator!=(
                          const UnitAwareExponentialDistribution& other ) const
{
  return d_constant_multiplier != other.d_constant_multiplier ||
    d_exponent_multiplier != other.d_exponent_multiplier ||
    d_lower_limit != other.d_lower_limit ||
    d_upper_limit != other.d_upper_limit;
}

// Initialize the distribution
template<typename IndependentUnit, typename DependentUnit>
void UnitAwareExponentialDistribution<IndependentUnit,DependentUnit>::initialize()
{
  // Calculate the exponential of the lower and upper bounds
  if( d_upper_limit < IQT::inf() )
    d_exp_upper_limit = exp( -d_exponent_multiplier*d_upper_limit );
  else
    d_exp_upper_limit = 0.0;

  if( d_lower_limit > IQT::zero() )
    d_exp_lower_limit = exp( -d_exponent_multiplier*d_lower_limit );
  else
    d_exp_lower_limit = 1.0;
}

// Verify that the shape parameters are valid
template<typename IndependentUnit, typename DependentUnit>
template<typename InputIndepQuantity,
         typename InputInverseIndepQuantity,
         typename InputDepQuantity>
void UnitAwareExponentialDistribution<IndependentUnit,DependentUnit>::verifyValidShapeParameters(
                          const InputDepQuantity& const_multiplier,
                          const InputInverseIndepQuantity& exponent_multiplier,
                          const InputIndepQuantity& lower_limit,
                          const InputIndepQuantity& upper_limit )
{
  typedef Utility::QuantityTraits<InputDepQuantity> InputDQT;
  
  TEST_FOR_EXCEPTION( InputDQT::isnaninf( const_multiplier ),
                      Utility::BadUnivariateDistributionParameter,
                      "The exponential distribution cannot be "
                      "constructed because the multiplier is invalid!" );

  TEST_FOR_EXCEPTION( const_multiplier == InputDQT::zero(),
                      Utility::BadUnivariateDistributionParameter,
                      "The exponential distribution cannot be "
                      "constructed because the multiplier is invalid!" );

  typedef Utility::QuantityTraits<InputInverseIndepQuantity> InputIIQT;
  
  TEST_FOR_EXCEPTION( InputIIQT::isnaninf( exponent_multiplier ),
                      Utility::BadUnivariateDistributionParameter,
                      "The exponential distribution cannot be "
                      "constructed because the exponent multiplier is "
                      "invalid!" );
  
  TEST_FOR_EXCEPTION( exponent_multiplier <= InputIIQT::zero(),
                      Utility::BadUnivariateDistributionParameter,
                      "The exponential distribution cannot be "
                      "constructed because the exponent multiplier is "
                      "invalid!" );

  typedef Utility::QuantityTraits<InputIndepQuantity> InputIQT;

  TEST_FOR_EXCEPTION( lower_limit < InputIQT::zero(),
                      Utility::BadUnivariateDistributionParameter,
                      "The exponential distribution cannot be "
                      "constructed because the lower limit is invalid!" );

  TEST_FOR_EXCEPTION( upper_limit <= lower_limit,
                      Utility::BadUnivariateDistributionParameter,
                      "The exponential distribution cannot be "
                      "constructed because the upper limit is invalid!" );
}

// Test if the dependent variable can be zero within the indep bounds
/*! \details If the upper limit is Inf then it is possible for the 
 * distribution to return 0.0 from one of the evaluate methods. However, 
 * the 0.0 value will only occur if the distribution is evaluated at Inf,
 * which should never actually be done in practice, so we will return
 * false from this method.
 */
template<typename IndependentUnit, typename DependentUnit>
bool UnitAwareExponentialDistribution<IndependentUnit,DependentUnit>::canDepVarBeZeroInIndepBounds() const
{
  return false;
}

} // end Utility namespace

EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( Utility::UnitAwareExponentialDistribution<void,void> );
EXTERN_EXPLICIT_CLASS_SAVE_LOAD_INST( Utility, UnitAwareExponentialDistribution<void,void> );

#endif // end UTILITY_EXPONENTIAL_DISTRIBUTION_DEF_HPP

//---------------------------------------------------------------------------//
// end Utility_ExponentialDistribution_def.hpp
//---------------------------------------------------------------------------//
