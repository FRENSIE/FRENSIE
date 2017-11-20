//---------------------------------------------------------------------------//
//!
//! \file   Utility_NormalDistribution_def.hpp
//! \author Alex Robinson
//! \brief  Normal distribution class declaration.
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_NORMAL_DISTRIBUTION_DEF_HPP
#define UTILITY_NORMAL_DISTRIBUTION_DEF_HPP

// FRENSIE Includes
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_ExceptionCatchMacros.hpp"
#include "Utility_ExplicitTemplateInstantiationMacros.hpp"
#include "Utility_ContractException.hpp"

BOOST_DISTRIBUTION_CLASS_EXPORT_IMPLEMENT( UnitAwareNormalDistribution );

namespace Utility{

// Initialize property tree keys and match strings
template<typename IndependentUnit, typename DependentUnit>
const std::string UnitAwareNormalDistribution<IndependentUnit,DependentUnit>::s_const_multiplier_value_key( "multiplier" );

template<typename IndependentUnit, typename DependentUnit>
const std::string UnitAwareNormalDistribution<IndependentUnit,DependentUnit>::s_const_multiplier_value_min_match_string( "mult" );

template<typename IndependentUnit, typename DependentUnit>
const std::string UnitAwareNormalDistribution<IndependentUnit,DependentUnit>::s_mean_value_key( "mean" );

template<typename IndependentUnit, typename DependentUnit>
const std::string UnitAwareNormalDistribution<IndependentUnit,DependentUnit>::s_mean_value_min_match_string( "mean" );

template<typename IndependentUnit, typename DependentUnit>
const std::string UnitAwareNormalDistribution<IndependentUnit,DependentUnit>::s_standard_deviation_value_key( "standard deviation" );

template<typename IndependentUnit, typename DependentUnit>
const std::string UnitAwareNormalDistribution<IndependentUnit,DependentUnit>::s_standard_deviation_value_min_match_string( "dev" );

template<typename IndependentUnit, typename DependentUnit>
const std::string UnitAwareNormalDistribution<IndependentUnit,DependentUnit>::s_lower_limit_value_key( "lower boundary" );

template<typename IndependentUnit, typename DependentUnit>
const std::string UnitAwareNormalDistribution<IndependentUnit,DependentUnit>::s_lower_limit_value_min_match_string( "lower" );

template<typename IndependentUnit, typename DependentUnit>
const std::string UnitAwareNormalDistribution<IndependentUnit,DependentUnit>::s_upper_limit_value_key( "upper boundary" );

template<typename IndependentUnit, typename DependentUnit>
const std::string UnitAwareNormalDistribution<IndependentUnit,DependentUnit>::s_upper_limit_value_min_match_string( "upper" );

// Initialize the constant norm factor
template<typename IndependentUnit, typename DependentUnit>
const double UnitAwareNormalDistribution<IndependentUnit,DependentUnit>::constant_norm_factor = 1.0/sqrt( 2*PhysicalConstants::pi );

// Constructor
/*! \details This constructor will explicitly cast the input quantities to
 * the distribution quantity (which includes any unit-conversion). The
 * dimension type must match and there must be a unit-conversion defined using
 * the boost methodology.
 */
template<typename IndependentUnit, typename DependentUnit>
template<typename InputDepQuantity,
	 typename InputIndepQuantityA,
	 typename InputIndepQuantityB,
	 typename InputIndepQuantityC>
UnitAwareNormalDistribution<IndependentUnit,DependentUnit>::UnitAwareNormalDistribution(
			      const InputIndepQuantityA mean,
			      const InputIndepQuantityB standard_deviation,
                              const InputDepQuantity constant_multiplier,
			      const InputIndepQuantityC min_independent_value,
			      const InputIndepQuantityC max_independent_value )
  : d_constant_multiplier( constant_multiplier ),
    d_mean( mean ),
    d_standard_deviation( standard_deviation ),
    d_min_independent_value( min_independent_value ),
    d_max_independent_value( max_independent_value )
{
  // Make sure that the values are valid
  testPrecondition( !QuantityTraits<InputDepQuantity>::isnaninf( constant_multiplier ) );
  testPrecondition( constant_multiplier !=
		    QuantityTraits<InputDepQuantity>::zero() );
  testPrecondition( !QuantityTraits<InputIndepQuantityA>::isnaninf( mean ) );
  testPrecondition( !QuantityTraits<InputIndepQuantityB>::isnaninf( standard_deviation ) );
  // Make sure that the standard deviation is positive
  testPrecondition( standard_deviation >
		    QuantityTraits<InputIndepQuantityB>::zero() );
  // Make sure that the min indep value is < the max indep value
  testPrecondition( min_independent_value < max_independent_value );

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
UnitAwareNormalDistribution<IndependentUnit,DependentUnit>::UnitAwareNormalDistribution(
  const UnitAwareNormalDistribution<InputIndepUnit,InputDepUnit>& dist_instance )
  : d_constant_multiplier( dist_instance.d_constant_multiplier ),
    d_mean( dist_instance.d_mean ),
    d_standard_deviation( dist_instance.d_standard_deviation ),
    d_min_independent_value( dist_instance.d_min_independent_value ),
    d_max_independent_value( dist_instance.d_max_independent_value )
{
  remember( typedef QuantityTraits<typename UnitAwareNormalDistribution<InputIndepUnit,InputDepUnit>::IndepQuantity> InputIQT );
  remember( typedef QuantityTraits<typename UnitAwareNormalDistribution<InputIndepUnit,InputDepUnit>::DepQuantity> InputDQT );
  // Make sure that the values are valid
  testPrecondition( !InputDQT::isnaninf( dist_instance.d_constant_multiplier ) );
  testPrecondition( dist_instance.d_constant_multiplier != InputDQT::zero() );
  testPrecondition( !InputIQT::isnaninf( dist_instance.d_mean ) );
  testPrecondition( !InputIQT::isnaninf( dist_instance.d_standard_deviation ) );
  // Make sure that the standard deviation is positive
  testPrecondition( dist_instance.d_standard_deviation > InputIQT::zero() );

  BOOST_DISTRIBUTION_CLASS_EXPORT_IMPLEMENT_FINALIZE( ThisType );
}

// Copy constructor (copying from unitless distribution only)
template<typename IndependentUnit, typename DependentUnit>
UnitAwareNormalDistribution<IndependentUnit,DependentUnit>::UnitAwareNormalDistribution( const UnitAwareNormalDistribution<void,void>& unitless_dist_instance, int )
  : d_constant_multiplier( DQT::initializeQuantity( unitless_dist_instance.d_constant_multiplier ) ),
    d_mean( IQT::initializeQuantity( unitless_dist_instance.d_mean ) ),
    d_standard_deviation( IQT::initializeQuantity( unitless_dist_instance.d_standard_deviation ) ),
    d_min_independent_value( IQT::initializeQuantity( unitless_dist_instance.d_min_independent_value ) ),
    d_max_independent_value( IQT::initializeQuantity( unitless_dist_instance.d_max_independent_value ) )
{
  // Make sure that the values are valid
  testPrecondition( !QT::isnaninf( unitless_dist_instance.d_constant_multiplier ) );
  testPrecondition( unitless_dist_instance.d_constant_multiplier != 0.0 );
  testPrecondition( !QT::isnaninf( unitless_dist_instance.d_mean ) );
  testPrecondition( !QT::isnaninf( unitless_dist_instance.d_standard_deviation ) );
  // Make sure that the standard deviation is positive
  testPrecondition( unitless_dist_instance.d_standard_deviation > 0.0 );

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
UnitAwareNormalDistribution<IndependentUnit,DependentUnit>
UnitAwareNormalDistribution<IndependentUnit,DependentUnit>::fromUnitlessDistribution( const UnitAwareNormalDistribution<void,void>& unitless_distribution )
{
  return ThisType( unitless_distribution, 0 );
}

// Assignment operator
template<typename IndependentUnit, typename DependentUnit>
UnitAwareNormalDistribution<IndependentUnit,DependentUnit>&
UnitAwareNormalDistribution<IndependentUnit,DependentUnit>::operator=(
  const UnitAwareNormalDistribution<IndependentUnit,DependentUnit>& dist_instance )
{
  // Make sure that the values are valid
  testPrecondition( !DQT::isnaninf( dist_instance.d_constant_multiplier ) );
  testPrecondition( dist_instance.d_constant_multiplier != DQT::zero() );
  testPrecondition( !IQT::isnaninf( dist_instance.d_mean ) );
  testPrecondition( !IQT::isnaninf( dist_instance.d_standard_deviation ) );
  // Make sure that the standard deviation is positive
  testPrecondition( dist_instance.d_standard_deviation > IQT::zero() );

  if( this != &dist_instance )
  {
    d_constant_multiplier = dist_instance.d_constant_multiplier;
    d_mean = dist_instance.d_mean;
    d_standard_deviation = dist_instance.d_standard_deviation;
    d_min_independent_value = dist_instance.d_min_independent_value;
    d_max_independent_value = dist_instance.d_max_independent_value;
  }

  return *this;
}

// Evaluate the distribution
template<typename IndependentUnit, typename DependentUnit>
typename UnitAwareNormalDistribution<IndependentUnit,DependentUnit>::DepQuantity
UnitAwareNormalDistribution<IndependentUnit,DependentUnit>::evaluate( const UnitAwareNormalDistribution<IndependentUnit,DependentUnit>::IndepQuantity indep_var_value ) const
{
  if( indep_var_value < d_min_independent_value )
    return DQT::zero();
  else if( indep_var_value > d_max_independent_value )
    return DQT::zero();
  else
  {
    double argument = -(indep_var_value-d_mean)*(indep_var_value-d_mean)/
      (2.0*d_standard_deviation*d_standard_deviation);

    return d_constant_multiplier*exp( argument );
  }
}

// Evaluate the PDF
template<typename IndependentUnit, typename DependentUnit>
typename UnitAwareNormalDistribution<IndependentUnit,DependentUnit>::InverseIndepQuantity
UnitAwareNormalDistribution<IndependentUnit,DependentUnit>::evaluatePDF( const UnitAwareNormalDistribution<IndependentUnit,DependentUnit>::IndepQuantity indep_var_value ) const
{
  if( indep_var_value < d_min_independent_value )
    return IIQT::zero();
  else if( indep_var_value > d_max_independent_value )
    return IIQT::zero();
  else
  {
    double argument = -(indep_var_value-d_mean)*(indep_var_value-d_mean)/
      (2.0*d_standard_deviation*d_standard_deviation);

    return UnitAwareNormalDistribution::constant_norm_factor*exp( argument )/
      d_standard_deviation;
  }
}

// Return a random sample from the distribution
template<typename IndependentUnit, typename DependentUnit>
inline typename UnitAwareNormalDistribution<IndependentUnit,DependentUnit>::IndepQuantity
UnitAwareNormalDistribution<IndependentUnit,DependentUnit>::sample(
			            const IndepQuantity mean,
				    const IndepQuantity standard_deviation,
				    const IndepQuantity min_independent_value,
			            const IndepQuantity max_independent_value )
{
  DistributionTraits::Counter number_of_trials;

  return ThisType::sampleAndRecordTrials( number_of_trials,
					  mean,
					  standard_deviation,
					  min_independent_value,
					  max_independent_value );
}

// Return a random sample from the distribution
template<typename IndependentUnit, typename DependentUnit>
typename UnitAwareNormalDistribution<IndependentUnit,DependentUnit>::IndepQuantity
UnitAwareNormalDistribution<IndependentUnit,DependentUnit>::sample() const
{
  return ThisType::sample( d_mean,
			   d_standard_deviation,
			   d_min_independent_value,
			   d_max_independent_value );
}

// Return a random sample from the distribution
template<typename IndependentUnit, typename DependentUnit>
inline typename UnitAwareNormalDistribution<IndependentUnit,DependentUnit>::IndepQuantity
UnitAwareNormalDistribution<IndependentUnit,DependentUnit>::sampleAndRecordTrials(
				    DistributionTraits::Counter& trials,
			            const IndepQuantity mean,
				    const IndepQuantity standard_deviation,
				    const IndepQuantity min_independent_value,
			            const IndepQuantity max_independent_value )
{
  double random_number_1, random_number_2;
  double x, y;
  IndepQuantity sample;

  while( true )
  {
    // Use the rejection sampling technique outlined by Kahn in "Applications
    // of Monte Carlo" (1954)
    while( true )
    {
      ++trials;

      random_number_1 = RandomNumberGenerator::getRandomNumber<double>();
      random_number_2 = RandomNumberGenerator::getRandomNumber<double>();

      x = -log( random_number_1 );
      y = -log( random_number_2 );

      if( 0.5*(x - 1)*(x - 1) <= y )
      	break;
    }

    if( RandomNumberGenerator::getRandomNumber<double>() < 0.5 )
      x *= -1.0;

    // stretch and shift the sampled value
    sample = standard_deviation*x+mean;

    if( sample >= min_independent_value &&
	sample <= max_independent_value )
      break;
  }

  return sample;
}

// Return a random sample from the corresponding CDF and record the number of trials
template<typename IndependentUnit, typename DependentUnit>
typename UnitAwareNormalDistribution<IndependentUnit,DependentUnit>::IndepQuantity
UnitAwareNormalDistribution<IndependentUnit,DependentUnit>::sampleAndRecordTrials( DistributionTraits::Counter& trials ) const
{
  return ThisType::sampleAndRecordTrials( trials,
					  d_mean,
					  d_standard_deviation,
					  d_min_independent_value,
					  d_max_independent_value );
}

// Return the upper bound of the distribution independent variable
template<typename IndependentUnit, typename DependentUnit>
typename UnitAwareNormalDistribution<IndependentUnit,DependentUnit>::IndepQuantity
UnitAwareNormalDistribution<IndependentUnit,DependentUnit>::getUpperBoundOfIndepVar() const
{
  return d_max_independent_value;
}

// Return the lower bound of the distribution independent variable
template<typename IndependentUnit, typename DependentUnit>
typename UnitAwareNormalDistribution<IndependentUnit,DependentUnit>::IndepQuantity
UnitAwareNormalDistribution<IndependentUnit,DependentUnit>::getLowerBoundOfIndepVar() const
{
  return d_min_independent_value;
}

// Return the distribution type
template<typename IndependentUnit, typename DependentUnit>
OneDDistributionType
UnitAwareNormalDistribution<IndependentUnit,DependentUnit>::getDistributionType() const
{
  return ThisType::distribution_type;
}

// Return the distribution type name
template<typename IndependentUnit, typename DependentUnit>
std::string UnitAwareNormalDistribution<IndependentUnit,DependentUnit>::typeName(
                                                const bool verbose_name,
                                                const bool use_template_params,
                                                const std::string& delim )
{
  return BaseType::typeNameImpl( "Normal",
                                 verbose_name,
                                 use_template_params,
                                 delim );
}

// Return the distribution type name
template<typename IndependentUnit, typename DependentUnit>
std::string UnitAwareNormalDistribution<IndependentUnit,DependentUnit>::getDistributionTypeName(
                                                   const bool verbose_name,
                                                   const bool lowercase ) const
{
  std::string name = this->typeName( verbose_name, false, " " );

  if( lowercase )
    boost::algorithm::to_lower( name );

  return name;
}

// Test if the distribution is continuous
template<typename IndependentUnit, typename DependentUnit>
bool UnitAwareNormalDistribution<IndependentUnit,DependentUnit>::isContinuous() const
{
  return true;
}

// Method for placing the object in an output stream
template<typename IndependentUnit, typename DependentUnit>
void UnitAwareNormalDistribution<IndependentUnit,DependentUnit>::toStream( std::ostream& os ) const
{
  this->toStreamImpl( os,
                      Utility::getRawQuantity( d_mean ),
                      Utility::getRawQuantity( d_standard_deviation ),
                      Utility::getRawQuantity( d_min_independent_value ),
                      Utility::getRawQuantity( d_max_independent_value ),
                      Utility::getRawQuantity( d_constant_multiplier ) );
}

// Method for initializing the object from an input stream
template<typename IndependentUnit, typename DependentUnit>
void UnitAwareNormalDistribution<IndependentUnit,DependentUnit>::fromStream( std::istream& is, const std::string& )
{
  VariantList distribution_data;

  this->fromStreamImpl( is, distribution_data );

  // Set the mean
  if( !distribution_data.empty() )
  {
    this->extractShapeParameter( distribution_data.front(), d_mean );

    distribution_data.pop_front();
  }
  else
    d_mean = ThisType::getDefaultMean<IndepQuantity>();

  // Set the standard deviation
  if( !distribution_data.empty() )
  {
    this->extractShapeParameter( distribution_data.front(),
                                 d_standard_deviation );

    distribution_data.pop_front();
  }
  else
  {
    d_standard_deviation =
      ThisType::getDefaultStandardDeviation<IndepQuantity>();
  }

  // Set the lower boundary of the distribution
  if( !distribution_data.empty() )
  {
    this->extractShapeParameter( distribution_data.front(),
                                 d_min_independent_value );

    distribution_data.pop_front();
  }
  else
    d_min_independent_value = ThisType::getDefaultLowerLimit<IndepQuantity>();

  // Set the upper boundary of the distribution
  if( !distribution_data.empty() )
  {
    this->extractShapeParameter( distribution_data.front(),
                                 d_max_independent_value );

    distribution_data.pop_front();
  }
  else
    d_max_independent_value = ThisType::getDefaultUpperLimit<IndepQuantity>();

  // Set the constant multiplier
  if( !distribution_data.empty() )
  {
    this->extractShapeParameter( distribution_data.front(),
                                 d_constant_multiplier );

    distribution_data.pop_front();
  }
  else
    d_constant_multiplier = ThisType::getDefaultConstMultiplier<DepQuantity>();

  // Verify that the shape parameters are valid
  this->verifyValidShapeParameters( d_constant_multiplier,
                                    d_mean,
                                    d_standard_deviation,
                                    d_min_independent_value,
                                    d_max_independent_value );
  
  // Check if there is any superfluous data
  this->checkForUnusedStreamData( distribution_data );
}

// Method for converting the type to a property tree
template<typename IndependentUnit, typename DependentUnit>
Utility::PropertyTree UnitAwareNormalDistribution<IndependentUnit,DependentUnit>::toPropertyTree( const bool inline_data ) const
{
  if( inline_data )
    return this->toInlinedPropertyTreeImpl();
  else
  {
    return this->toPropertyTreeImpl(
     std::tie(s_const_multiplier_value_key, Utility::getRawQuantity(d_constant_multiplier)),
     std::tie(s_mean_value_key, Utility::getRawQuantity(d_mean)),
     std::tie(s_standard_deviation_value_key, Utility::getRawQuantity(d_standard_deviation)),
     std::tie(s_lower_limit_value_key, Utility::getRawQuantity(d_min_independent_value)),
     std::tie(s_upper_limit_value_key, Utility::getRawQuantity(d_max_independent_value)) );
  }
}

// Method for initializing the object from a property tree
template<typename IndependentUnit, typename DependentUnit>
void UnitAwareNormalDistribution<IndependentUnit,DependentUnit>::fromPropertyTree(
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
    d_mean = ThisType::getDefaultMean<IndepQuantity>();
    d_standard_deviation =
      ThisType::getDefaultStandardDeviation<IndepQuantity>();
    d_min_independent_value = ThisType::getDefaultLowerLimit<IndepQuantity>();
    d_max_independent_value = ThisType::getDefaultUpperLimit<IndepQuantity>();

    // Create the data extractor map
    typename BaseType::DataExtractorMap data_extractors;

    data_extractors.insert(
     std::make_pair( s_const_multiplier_value_key,
      std::make_tuple( s_const_multiplier_value_min_match_string, OPTIONAL_DATA,
         std::bind<void>(&ThisType::extractShapeParameterFromNode<DepQuantity>,
                         std::placeholders::_1,
                         std::ref(d_constant_multiplier)) )));
    data_extractors.insert(
     std::make_pair( s_mean_value_key,
      std::make_tuple( s_mean_value_min_match_string, OPTIONAL_DATA,
         std::bind<void>(&ThisType::extractShapeParameterFromNode<IndepQuantity>,
                         std::placeholders::_1,
                         std::ref(d_mean)) )));
    data_extractors.insert(
     std::make_pair( s_standard_deviation_value_key,
      std::make_tuple( s_standard_deviation_value_min_match_string, OPTIONAL_DATA,
       std::bind<void>(&ThisType::extractShapeParameterFromNode<IndepQuantity>,
                       std::placeholders::_1,
                       std::ref(d_standard_deviation)) )));
    data_extractors.insert(
     std::make_pair( s_lower_limit_value_key,
      std::make_tuple( s_lower_limit_value_min_match_string, OPTIONAL_DATA,
       std::bind<void>(&ThisType::extractShapeParameterFromNode<IndepQuantity>,
                       std::placeholders::_1,
                       std::ref(d_min_independent_value)) )));
    data_extractors.insert(
     std::make_pair( s_upper_limit_value_key,
      std::make_tuple( s_upper_limit_value_min_match_string, OPTIONAL_DATA,
       std::bind<void>(&ThisType::extractShapeParameterFromNode<IndepQuantity>,
                       std::placeholders::_1,
                       std::ref(d_max_independent_value)) )));

    this->fromPropertyTreeImpl( node, unused_children, data_extractors );

    // Verify that the shape parameters are valid
    try{
      this->verifyValidShapeParameters( d_constant_multiplier,
                                        d_mean,
                                        d_standard_deviation,
                                        d_min_independent_value,
                                        d_max_independent_value );
    }
    EXCEPTION_CATCH_RETHROW_AS( Utility::StringConversionException,
                                Utility::PropertyTreeConversionException,
                                "Invalid shape parameter detected!" );
  }
}

// Save the distribution to an archive
template<typename IndependentUnit, typename DependentUnit>
template<typename Archive>
void UnitAwareNormalDistribution<IndependentUnit,DependentUnit>::save( Archive& ar, const unsigned version ) const
{
  // Save the base class first
  ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( BaseType );

  // Save the local member data
  ar & BOOST_SERIALIZATION_NVP( d_constant_multiplier );
  ar & BOOST_SERIALIZATION_NVP( d_mean );
  ar & BOOST_SERIALIZATION_NVP( d_standard_deviation );
  ar & BOOST_SERIALIZATION_NVP( d_min_independent_value );
  ar & BOOST_SERIALIZATION_NVP( d_max_independent_value );
}

// Load the distribution from an archive
template<typename IndependentUnit, typename DependentUnit>
template<typename Archive>
void UnitAwareNormalDistribution<IndependentUnit,DependentUnit>::load( Archive& ar, const unsigned version )
{
  // Load the base class first
  ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( BaseType );

  // Load the local member data
  ar & BOOST_SERIALIZATION_NVP( d_constant_multiplier );
  ar & BOOST_SERIALIZATION_NVP( d_mean );
  ar & BOOST_SERIALIZATION_NVP( d_standard_deviation );
  ar & BOOST_SERIALIZATION_NVP( d_min_independent_value );
  ar & BOOST_SERIALIZATION_NVP( d_max_independent_value );
}

// Method for testing if two objects are equivalent
template<typename IndependentUnit, typename DependentUnit>
bool UnitAwareNormalDistribution<IndependentUnit,DependentUnit>::operator==( const UnitAwareNormalDistribution& other ) const
{
  return d_constant_multiplier == other.d_constant_multiplier &&
    d_mean == other.d_mean &&
    d_standard_deviation == other.d_standard_deviation &&
    d_min_independent_value == other.d_min_independent_value &&
    d_max_independent_value == other.d_max_independent_value;
}

// Method for testing if two objects are different
template<typename IndependentUnit, typename DependentUnit>
bool UnitAwareNormalDistribution<IndependentUnit,DependentUnit>::operator!=( const UnitAwareNormalDistribution& other ) const
{
  return d_constant_multiplier != other.d_constant_multiplier ||
    d_mean != other.d_mean ||
    d_standard_deviation != other.d_standard_deviation ||
    d_min_independent_value != other.d_min_independent_value ||
    d_max_independent_value != other.d_max_independent_value;
}

// Test if the dependent variable can be zero within the indep bounds
/*! \details If the absolute value of the lower or upper limit is Inf then it 
 * is possible for the distribution to return 0.0 from one of the evaluate 
 * methods. However, the 0.0 value will only occur if the distribution is 
 * evaluated at +/- Inf, which should never actually be done in practice, so we
 *  will return false from this method.
 */
template<typename IndependentUnit, typename DependentUnit>
bool UnitAwareNormalDistribution<IndependentUnit,DependentUnit>::canDepVarBeZeroInIndepBounds() const
{
  return false;
}

// Extract a shape parameter from a node
template<typename IndependentUnit, typename DependentUnit>
template<typename QuantityType>
void UnitAwareNormalDistribution<IndependentUnit,DependentUnit>::extractShapeParameterFromNode(
                             const Utility::PropertyTree& shape_parameter_data,
                             QuantityType& shape_parameter )
{
  // The data must be inlined in the node
  TEST_FOR_EXCEPTION( shape_parameter_data.size() != 0,
                      Utility::PropertyTreeConversionException,
                      "Could not extract the shape parameter value!" );

  ThisType::extractShapeParameter( shape_parameter_data.data(),
                                   shape_parameter );
}

// Extract a shape parameter
template<typename IndependentUnit, typename DependentUnit>
template<typename QuantityType>
void UnitAwareNormalDistribution<IndependentUnit,DependentUnit>::extractShapeParameter(
                                  const Utility::Variant& shape_parameter_data,
                                  QuantityType& shape_parameter )
{
  double raw_shape_parameter;

  try{
    raw_shape_parameter =
      Utility::variant_cast<double>( shape_parameter_data );
  }
  EXCEPTION_CATCH_RETHROW( Utility::StringConversionException,
                           "The normal distribution cannot be "
                           "constructed because a shape parameter is not "
                           "valid!" );

  Utility::setQuantity( shape_parameter, raw_shape_parameter );
}

// Verify that the shape parameters are valid
template<typename IndependentUnit, typename DependentUnit>
void UnitAwareNormalDistribution<IndependentUnit,DependentUnit>::verifyValidShapeParameters(
                                   const DepQuantity& const_multiplier,
                                   const IndepQuantity& mean,
                                   const IndepQuantity& standard_deviation,
                                   const IndepQuantity& min_independent_value,
                                   const IndepQuantity& max_independent_value )
{
  TEST_FOR_EXCEPTION( DQT::isnaninf( const_multiplier ),
		      Utility::StringConversionException,
		      "The normal distribution cannot be constructed "
		      "because of the multiplier is invalid!" );
  
  TEST_FOR_EXCEPTION( const_multiplier == DQT::zero(),
		      Utility::StringConversionException,
		      "The normal distribution cannot be constructed "
		      "because of the multiplier is invalid!" );
  
  TEST_FOR_EXCEPTION( IQT::isnaninf( mean ),
		      Utility::StringConversionException,
		      "The normal distribution cannot be constructed "
		      "because the mean is invalid!" );

  TEST_FOR_EXCEPTION( IQT::isnaninf( standard_deviation ),
		      Utility::StringConversionException,
		      "The normal distribution cannot be constructed "
		      "because the standard deviation is invalid!" );

  TEST_FOR_EXCEPTION( standard_deviation <= IQT::zero(),
		      Utility::StringConversionException,
		      "The normal distribution cannot be constructed "
		      "because the standard deviation is invalid!" );

  TEST_FOR_EXCEPTION( max_independent_value <= min_independent_value,
		      Utility::StringConversionException,
		      "The normal distribution cannot be constructed because "
                      "the upper limit is invalid!" );
}

} // end Utility namespace

EXTERN_EXPLICIT_DISTRIBUTION_INST( UnitAwareNormalDistribution<void,void> );

#endif // end UTILITY_NORMAL_DISTRIBUTION_DEF_HPP

//---------------------------------------------------------------------------//
// end Utility_NormalDistribution_def.hpp
//---------------------------------------------------------------------------//
