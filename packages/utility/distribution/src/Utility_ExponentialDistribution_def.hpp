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
#include "Utility_ExplicitTemplateInstantiationMacros.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_ExceptionCatchMacros.hpp"
#include "Utility_ContractException.hpp"

BOOST_DISTRIBUTION_CLASS_EXPORT_IMPLEMENT( UnitAwareExponentialDistribution );

namespace Utility{

// The constant multiplier value key (used in property trees)
template<typename IndependentUnit, typename DependentUnit>
const std::string UnitAwareExponentialDistribution<IndependentUnit,DependentUnit>::s_const_multiplier_value_key( "multiplier" );

// The constant multiplier min match string (used in property trees)
template<typename IndependentUnit, typename DependentUnit>
const std::string UnitAwareExponentialDistribution<IndependentUnit,DependentUnit>::s_const_multiplier_value_min_match_string( "mult" );

// The exponent multiplier value key (used in property trees)
template<typename IndependentUnit, typename DependentUnit>
const std::string UnitAwareExponentialDistribution<IndependentUnit,DependentUnit>::s_exponent_multiplier_value_key( "exponent" );

// The exponent multiplier min match string (used in property trees)
template<typename IndependentUnit, typename DependentUnit>
const std::string UnitAwareExponentialDistribution<IndependentUnit,DependentUnit>::s_exponent_multiplier_value_min_match_string( "exp" );

// The lower limit value key (used in property trees)
template<typename IndependentUnit, typename DependentUnit>
const std::string UnitAwareExponentialDistribution<IndependentUnit,DependentUnit>::s_lower_limit_value_key( "lower boundary" );

// The lower limit min match string (used in property trees)
template<typename IndependentUnit, typename DependentUnit>  
const std::string UnitAwareExponentialDistribution<IndependentUnit,DependentUnit>::s_lower_limit_value_min_match_string( "lower" );

// The upper limit value key (used in property trees)
template<typename IndependentUnit, typename DependentUnit>
const std::string UnitAwareExponentialDistribution<IndependentUnit,DependentUnit>::s_upper_limit_value_key( "upper boundary" );

// The upper limit min match string (used in property trees)
template<typename IndependentUnit, typename DependentUnit>
const std::string UnitAwareExponentialDistribution<IndependentUnit,DependentUnit>::s_upper_limit_value_min_match_string( "upper" );

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

  BOOST_DISTRIBUTION_CLASS_EXPORT_IMPLEMENT_FINALIZE( ThisType );
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

  BOOST_DISTRIBUTION_CLASS_EXPORT_IMPLEMENT_FINALIZE( ThisType );
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

  BOOST_DISTRIBUTION_CLASS_EXPORT_IMPLEMENT_FINALIZE( ThisType );
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

// Return the distribution type name
template<typename IndependentUnit, typename DependentUnit>
std::string UnitAwareExponentialDistribution<IndependentUnit,DependentUnit>::typeName(
                                                const bool verbose_name,
                                                const bool use_template_params,
                                                const std::string& delim )
{
  return BaseType::typeNameImpl( "Exponential",
                                 verbose_name,
                                 use_template_params,
                                 delim );
}

// Return the distribution type name
template<typename IndependentUnit, typename DependentUnit>
std::string UnitAwareExponentialDistribution<IndependentUnit,DependentUnit>::getTypeNameImpl(
                                                const bool verbose_name ) const
{
  return this->typeName( verbose_name, false, " " );
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
  this->toStreamImpl( os,
                      Utility::getRawQuantity( d_exponent_multiplier ),
                      Utility::getRawQuantity( d_constant_multiplier ),
                      Utility::getRawQuantity( d_lower_limit ),
                      Utility::getRawQuantity( d_upper_limit ) );
}

// Method for initializing the object from an input stream
template<typename IndependentUnit, typename DependentUnit>
void UnitAwareExponentialDistribution<IndependentUnit,DependentUnit>::fromStreamImpl(
                                               VariantList& distribution_data )
{
  // Set the exponent multiplier
  if( !distribution_data.empty() )
  {
    this->extractShapeParameter( distribution_data.front(),
                                 d_exponent_multiplier );
    distribution_data.pop_front();
  }
  else
  {
    d_exponent_multiplier =
      ThisType::getDefaultExponentMultiplier<InverseIndepQuantity>();
  }

  // Set the constant multiplier
  if( !distribution_data.empty() )
  {
    this->extractShapeParameter( distribution_data.front(),
                                 d_constant_multiplier );
    distribution_data.pop_front();
  }
  else
  {
    d_constant_multiplier =
      ThisType::getDefaultConstMultiplier<DepQuantity>();
  }

  // Set the lower boundary of the distribution
  if( !distribution_data.empty() )
  {
    this->extractShapeParameter( distribution_data.front(),
                                 d_lower_limit );
    distribution_data.pop_front();
  }
  else
    d_lower_limit = ThisType::getDefaultLowerLimit<IndepQuantity>();

  // Set the upper boundary of the distribution
  if( !distribution_data.empty() )
  {
    this->extractShapeParameter( distribution_data.front(),
                                 d_upper_limit );
    distribution_data.pop_front();
  }
  else
    d_upper_limit = ThisType::getDefaultUpperLimit<IndepQuantity>();

  // Verify that the shape parameters are valid
  this->verifyValidShapeParameters( d_constant_multiplier,
                                    d_exponent_multiplier,
                                    d_lower_limit,
                                    d_upper_limit );
  
  // Initialize the distribution
  this->initialize();
}

// Method for converting the type to a property tree
template<typename IndependentUnit, typename DependentUnit>
Utility::PropertyTree UnitAwareExponentialDistribution<IndependentUnit,DependentUnit>::toPropertyTree( const bool inline_data ) const
{
  if( inline_data )
    return this->toInlinedPropertyTreeImpl();
  else
  {
    return this->toPropertyTreeImpl(
     std::tie(s_const_multiplier_value_key, Utility::getRawQuantity(d_constant_multiplier)),
     std::tie(s_exponent_multiplier_value_key, Utility::getRawQuantity(d_exponent_multiplier)),
     std::tie(s_lower_limit_value_key, Utility::getRawQuantity(d_lower_limit)),
     std::tie(s_upper_limit_value_key, Utility::getRawQuantity(d_upper_limit)) );
  }
}

// Method for initializing the object from a property tree
template<typename IndependentUnit, typename DependentUnit>
void UnitAwareExponentialDistribution<IndependentUnit,DependentUnit>::fromPropertyTree(
                                    const Utility::PropertyTree& node,
                                    std::vector<std::string>& unused_children )
{
  if( node.size() == 0 )
    this->fromInlinedPropertyTreeImpl( node );

  // Initialize from child nodes
  else
  {
    // Initialize the member data to default values
    d_constant_multiplier = ThisType::getDefaultConstMultiplier<DepQuantity>();
    d_exponent_multiplier = ThisType::getDefaultExponentMultiplier<InverseIndepQuantity>();
    d_lower_limit = ThisType::getDefaultLowerLimit<IndepQuantity>();
    d_upper_limit = ThisType::getDefaultUpperLimit<IndepQuantity>();

    std::string type_name = this->getTypeName( true, true );

    // Create the data extractor map
    typename BaseType::DataExtractorMap data_extractors;

    data_extractors.insert(
     std::make_pair( s_const_multiplier_value_key,
      std::make_tuple( s_const_multiplier_value_min_match_string, BaseType::OPTIONAL_DATA,
         std::bind<void>(&ThisType::extractShapeParameterFromNode<DepQuantity>,
                         std::placeholders::_1,
                         std::ref(d_constant_multiplier)) )));
    data_extractors.insert(
     std::make_pair( s_exponent_multiplier_value_key,
      std::make_tuple( s_exponent_multiplier_value_min_match_string, BaseType::OPTIONAL_DATA,
       std::bind<void>(&BaseType::template extractValueFromNode<InverseIndepQuantity>,
                       std::placeholders::_1,
                       std::ref(d_exponent_multiplier),
                       std::cref(type_name)) )));
    data_extractors.insert(
     std::make_pair( s_lower_limit_value_key,
      std::make_tuple( s_lower_limit_value_min_match_string, BaseType::OPTIONAL_DATA,
       std::bind<void>(&BaseType::template extractValueFromNode<IndepQuantity>,
                       std::placeholders::_1,
                       std::ref(d_lower_limit),
                       std::cref(type_name)) )));
    data_extractors.insert(
     std::make_pair( s_upper_limit_value_key,
      std::make_tuple( s_upper_limit_value_min_match_string, BaseType::OPTIONAL_DATA,
       std::bind<void>(&BaseType::template extractValueFromNode<IndepQuantity>,
                       std::placeholders::_1,
                       std::ref(d_upper_limit),
                       std::cref(type_name)) )));

    this->fromPropertyTreeImpl( node, unused_children, data_extractors );

    // Verify that the shape parameters are valid
    try{
      this->verifyValidShapeParameters( d_constant_multiplier,
                                        d_exponent_multiplier,
                                        d_lower_limit,
                                        d_upper_limit );
    }
    EXCEPTION_CATCH_RETHROW_AS( Utility::StringConversionException,
                                Utility::PropertyTreeConversionException,
                                "Invalid shape parameter detected!" );

    // Initialize the distribution
    this->initialize();
  }
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
  ar & BOOST_SERIALIZATION_NVP( d_upper_limit );
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
  ar & BOOST_SERIALIZATION_NVP( d_upper_limit );
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
void UnitAwareExponentialDistribution<IndependentUnit,DependentUnit>::verifyValidShapeParameters(
                               const DepQuantity& const_multiplier,
                               const InverseIndepQuantity& exponent_multiplier,
                               const IndepQuantity& lower_limit,
                               const IndepQuantity& upper_limit )
{
  TEST_FOR_EXCEPTION( DQT::isnaninf( const_multiplier ),
                      Utility::StringConversionException,
                      "The exponential distribution cannot be "
                      "constructed because the multiplier is invalid!" );

  TEST_FOR_EXCEPTION( const_multiplier == DQT::zero(),
                      Utility::StringConversionException,
                      "The exponential distribution cannot be "
                      "constructed because the multiplier is invalid!" );
  
  TEST_FOR_EXCEPTION( IIQT::isnaninf( exponent_multiplier ),
                      Utility::StringConversionException,
                      "The exponential distribution cannot be "
                      "constructed because the exponent multiplier is "
                      "invalid!" );
  
  TEST_FOR_EXCEPTION( exponent_multiplier <= IIQT::zero(),
                      Utility::StringConversionException,
                      "The exponential distribution cannot be "
                      "constructed because the exponent multiplier is "
                      "invalid!" );

  TEST_FOR_EXCEPTION( lower_limit < IQT::zero(),
                      Utility::StringConversionException,
                      "The exponential distribution cannot be "
                      "constructed because the lower limit is invalid!" );

  TEST_FOR_EXCEPTION( upper_limit <= lower_limit,
                      Utility::StringConversionException,
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

EXTERN_EXPLICIT_DISTRIBUTION_INST( UnitAwareExponentialDistribution<void,void> );

#endif // end UTILITY_EXPONENTIAL_DISTRIBUTION_DEF_HPP

//---------------------------------------------------------------------------//
// end Utility_ExponentialDistribution_def.hpp
//---------------------------------------------------------------------------//
