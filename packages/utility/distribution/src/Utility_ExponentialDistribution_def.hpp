//---------------------------------------------------------------------------//
//!
//! \file   Utility_ExponentialDistribution.cpp
//! \author Alex Robinson
//! \brief  Exponential distribution class definition.
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_EXPONENTIAL_DISTRIBUTION_DEF_HPP
#define UTILITY_EXPONENTIAL_DISTRIBUTION_DEF_HPP

// Std Lib Includes
#include <limits>

// Trilinos Includes
#include <Teuchos_Utils.hpp>

// FRENSIE Includes
#include "Utility_ExponentialDistribution.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_ArrayString.hpp"
#include "Utility_ExplicitTemplateInstantiationMacros.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_ExceptionCatchMacros.hpp"

namespace Utility{

// Explicit instantiation (extern declaration)
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( UnitAwareExponentialDistribution<void,void> );

// Default constructor
template<typename IndependentUnit, typename DependentUnit>
UnitAwareExponentialDistribution<IndependentUnit,DependentUnit>::UnitAwareExponentialDistribution()
{ /* ... */ }

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
  // Make sure the multipliers are valid
  remember( typedef QuantityTraits<InputIndepQuantity> InputIQT );
  remember( typedef QuantityTraits<InputInverseIndepQuantity> InputIIQT );
  remember( typedef QuantityTraits<InputDepQuantity> InputDQT );
  testPrecondition( !InputDQT::isnaninf( constant_multiplier ) );
  testPrecondition( !InputIIQT::isnaninf( exponent_multiplier ) );
  // Make sure that the exponent multiplier is positive
  testPrecondition( exponent_multiplier > InputIIQT::zero() );
  // Make sure the limits are valid
  testPrecondition( lower_limit >= InputIQT::zero() );
  testPrecondition( upper_limit > lower_limit );

  // Initialize the distribution
  this->initialize();
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
  remember( typedef QuantityTraits<typename UnitAwareExponentialDistribution<InputIndepUnit,InputDepUnit>::IndepQuantity> InputIQT );
  remember( typedef QuantityTraits<typename UnitAwareExponentialDistribution<InputIndepUnit,InputDepUnit>::InverseIndepQuantity> InputIIQT );
  remember( typedef QuantityTraits<typename UnitAwareExponentialDistribution<InputIndepUnit,InputDepUnit>::DepQuantity> InputDQT );
  // Make sure the multipliers are valid
  testPrecondition( !InputDQT::isnaninf(dist_instance.d_constant_multiplier) );
  testPrecondition( !InputIIQT::isnaninf(dist_instance.d_exponent_multiplier));
  // Make sure that the exponent multiplier is positive
  testPrecondition( dist_instance.d_exponent_multiplier > InputIIQT::zero() );
  // Make sure the limits are valid
  testPrecondition( dist_instance.d_lower_limit >= InputIQT::zero() );
  testPrecondition( dist_instance.d_upper_limit >
		    dist_instance.d_lower_limit );

  // Initialize the distribution
  this->initialize();
}

// Copy constructor (copying from unitless distribution only)
template<typename IndependentUnit, typename DependentUnit>
UnitAwareExponentialDistribution<IndependentUnit,DependentUnit>::UnitAwareExponentialDistribution( const UnitAwareExponentialDistribution<void,void>& unitless_dist_instance, int )
  : d_constant_multiplier( DQT::initializeQuantity( unitless_dist_instance.d_constant_multiplier ) ),
    d_exponent_multiplier( IIQT::initializeQuantity( unitless_dist_instance.d_exponent_multiplier ) ),
    d_lower_limit( IQT::initializeQuantity( unitless_dist_instance.d_lower_limit ) ),
    d_upper_limit( IQT::initializeQuantity( unitless_dist_instance.d_upper_limit ) )
{
  // Make sure the multipliers are valid
  testPrecondition( !QT::isnaninf(
			      unitless_dist_instance.d_constant_multiplier ) );
  testPrecondition( !QT::isnaninf(
			      unitless_dist_instance.d_exponent_multiplier ) );
  // Make sure that the exponent multiplier is positive
  testPrecondition( unitless_dist_instance.d_exponent_multiplier > QT::zero());
  // Make sure the limits are valid
  testPrecondition( unitless_dist_instance.d_lower_limit >= QT::zero() );
  testPrecondition( unitless_dist_instance.d_upper_limit >
		    unitless_dist_instance.d_lower_limit );

  // Initialize the distribution
  this->initialize();
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
  // Make sure the multipliers are valid
  testPrecondition( !DQT::isnaninf(dist_instance.d_constant_multiplier) );
  testPrecondition( !IIQT::isnaninf(dist_instance.d_exponent_multiplier));
  // Make sure that the exponent multiplier is positive
  testPrecondition( dist_instance.d_exponent_multiplier > IIQT::zero() );
  // Make sure the limits are valid
  testPrecondition( dist_instance.d_lower_limit >= IQT::zero() );
  testPrecondition( dist_instance.d_upper_limit >
		    dist_instance.d_lower_limit );

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
OneDDistributionType
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
  os << "{" << getRawQuantity( d_exponent_multiplier )
     << "," << getRawQuantity( d_constant_multiplier )
     << "," << getRawQuantity( d_lower_limit )
     << ",";

  if( d_upper_limit < IQT::inf() )
    os << getRawQuantity( d_upper_limit );
  else
    os << "inf";

  os << "}";
}

// Method for initializing the object from an input stream
template<typename IndependentUnit, typename DependentUnit>
void UnitAwareExponentialDistribution<IndependentUnit,DependentUnit>::fromStream( std::istream& is )
{
  // Read in the distribution representation
  std::string dist_rep;
  std::getline( is, dist_rep, '}' );
  dist_rep += '}';

  // Parse special characters
  try{
    ArrayString::locateAndReplacePi( dist_rep );
  }
  EXCEPTION_CATCH_RETHROW_AS( std::runtime_error,
			      InvalidDistributionStringRepresentation,
			      "Error: the exponential distribution cannot be "
			      "constructed because the representation is not "
			      "valid (see details below)!\n" );

  Teuchos::Array<std::string> distribution;
  try{
    distribution = Teuchos::fromStringToArray<std::string>( dist_rep );
  }
  EXCEPTION_CATCH_RETHROW_AS( Teuchos::InvalidArrayStringRepresentation,
			      InvalidDistributionStringRepresentation,
			      "Error: the exponential distribution cannot be "
			      "constructed because the representation is not "
			      "valid (see details below)!\n" );

  TEST_FOR_EXCEPTION( distribution.size() < 1 || distribution.size() > 4,
		      InvalidDistributionStringRepresentation,
		      "Error: the exponential distribution cannot be "
		      "constructed because the representation is not valid "
		      "(either two, three or four values may be specified)!" );

  // Extract the exponent multiplier
  {
    std::istringstream iss( distribution[0] );
    double raw_exponent_multiplier;

    Teuchos::extractDataFromISS( iss, raw_exponent_multiplier );

    d_exponent_multiplier = IIQT::initializeQuantity( raw_exponent_multiplier);

    TEST_FOR_EXCEPTION( IIQT::isnaninf( d_exponent_multiplier ),
			InvalidDistributionStringRepresentation,
			"Error: the exponential distribution cannot be "
			"constructed because of an invalid exponent "
			"multiplier " << d_exponent_multiplier );
  }

  // Extract the constant multiplier
  if( distribution.size() > 1 )
  {
    std::istringstream iss( distribution[1] );
    double raw_constant_multiplier;

    Teuchos::extractDataFromISS( iss, raw_constant_multiplier );

    d_constant_multiplier = DQT::initializeQuantity( raw_constant_multiplier );

    TEST_FOR_EXCEPTION( DQT::isnaninf( d_constant_multiplier ),
			InvalidDistributionStringRepresentation,
			"Error: the exponential distribution cannot be "
			"constructed because of an invalid constant "
			"multiplier " << d_constant_multiplier );
  }
  else
    d_constant_multiplier = DQT::one();

  // Extract the lower limit
  if( distribution.size() > 2 )
  {
    std::istringstream iss( distribution[2] );
    double raw_lower_limit;

    Teuchos::extractDataFromISS( iss, raw_lower_limit );

    d_lower_limit = IQT::initializeQuantity( raw_lower_limit );

    TEST_FOR_EXCEPTION( d_lower_limit < IQT::zero(),
			InvalidDistributionStringRepresentation,
			"Error: The exponential distribution cannot be "
			"constructed because of an invalid lower limit "
			<< d_lower_limit );
  }
  else
    d_lower_limit = IQT::zero();

  // Extract the upper limit
  if( distribution.size() > 3 )
  {
    if( distribution[3].compare( "inf" ) == 0 )
      d_upper_limit = IQT::inf();
    else
    {
      TEST_FOR_EXCEPTION( distribution[3].find_first_not_of( "0123456789.e" )<
			  distribution[3].size(),
			  InvalidDistributionStringRepresentation,
			  "Error: the exponential distribution cannot be "
			  "constructed because of an invalid max independent "
			  " value " << distribution[3] );

      std::istringstream iss( distribution[3] );
      double raw_upper_limit;

      Teuchos::extractDataFromISS( iss, raw_upper_limit );

      d_upper_limit = IQT::initializeQuantity( raw_upper_limit );

      TEST_FOR_EXCEPTION( d_upper_limit <= d_lower_limit,
			  InvalidDistributionStringRepresentation,
			  "Error: The exponential distribution cannot be "
			  "constructed because of an invalid upper limit "
			  << d_upper_limit << " <= " << d_lower_limit );
    }
  }
  else
    d_upper_limit = IQT::inf();

  // Initialize the distribution
  this->initialize();
}

// Method for testing if two objects are equivalent
template<typename IndependentUnit, typename DependentUnit>
bool UnitAwareExponentialDistribution<IndependentUnit,DependentUnit>::isEqual(
 const UnitAwareExponentialDistribution<IndependentUnit,DependentUnit>& other ) const
{
  return d_constant_multiplier == other.d_constant_multiplier &&
    d_exponent_multiplier == other.d_exponent_multiplier &&
    d_lower_limit == other.d_lower_limit &&
    d_upper_limit == other.d_upper_limit;
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

#endif // end UTILITY_EXPONENTIAL_DISTRIBUTION_DEF_HPP

//---------------------------------------------------------------------------//
// end Utility_ExponentialDistribution_def.hpp
//---------------------------------------------------------------------------//
