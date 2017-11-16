//---------------------------------------------------------------------------//
//!
//! \file   Utility_PowerDistribution_def.hpp
//! \author Alex Robinson
//! \brief  Power distribution class definition.
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_POWER_DISTRIBUTION_DEF_HPP
#define UTILITY_POWER_DISTRIBUTION_DEF_HPP

// FRENSIE Includes
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_ExponentiationAlgorithms.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_ExceptionCatchMacros.hpp"
#include "Utility_ContractException.hpp"

BOOST_DISTRIBUTION_CLASS_EXPORT_IMPLEMENT_EXTRA( UnitAwarePowerDistribution, size_t, N );

namespace Utility{

// Initialize static member data
template<size_t N, typename IndependentUnit, typename DependentUnit>
const std::string UnitAwarePowerDistribution<N,IndependentUnit,DependentUnit>::s_const_multiplier_value_key( "multiplier" );
  
template<size_t N, typename IndependentUnit, typename DependentUnit>
const std::string UnitAwarePowerDistribution<N,IndependentUnit,DependentUnit>::s_const_multiplier_value_min_match_string( "mult" );

template<size_t N, typename IndependentUnit, typename DependentUnit>
const std::string UnitAwarePowerDistribution<N,IndependentUnit,DependentUnit>::s_lower_limit_value_key( "lower boundary" );

template<size_t N, typename IndependentUnit, typename DependentUnit>
const std::string UnitAwarePowerDistribution<N,IndependentUnit,DependentUnit>::s_lower_limit_value_min_match_string( "lower" );

template<size_t N, typename IndependentUnit, typename DependentUnit>
const std::string UnitAwarePowerDistribution<N,IndependentUnit,DependentUnit>::s_upper_limit_value_key( "upper boundary" );

template<size_t N, typename IndependentUnit, typename DependentUnit>
const std::string UnitAwarePowerDistribution<N,IndependentUnit,DependentUnit>::s_upper_limit_value_min_match_string( "upper" );

namespace Details{

/*! Power distribution traits struct for power N
 * \ingroup one_d_distributions
 * \ingroup traits
 */
template<size_t N>
struct PowerDistributionTraits
{
  //! The distribution type
  static const OneDDistributionType distribution_type = POWER_N_DISTRIBUTION;

  //! The N+1 root function
  template<typename Np1Quantity>
  static inline typename QuantityTraits<Np1Quantity>::template GetQuantityToPowerType<1,N+1>::type np1Root( const Np1Quantity& quantity )
  { return rpow<1,N+1>( quantity ); }

  //! The pow N function
  template<typename Quantity>
  static inline typename QuantityTraits<Quantity>::template GetQuantityToPowerType<N>::type powN( const Quantity& quantity )
  {
    return QuantityTraits<typename QuantityTraits<Quantity>::template GetQuantityToPowerType<N>::type>::initializeQuantity( Exponentiation::recursive( getRawQuantity( quantity ), N ) );
  }

  //! The pow Np1 function
  template<typename Quantity>
  static inline typename QuantityTraits<Quantity>::template GetQuantityToPowerType<N+1>::type powNp1( const Quantity& quantity )
  {
    return QuantityTraits<typename QuantityTraits<Quantity>::template GetQuantityToPowerType<N+1>::type>::initializeQuantity( Exponentiation::recursive( getRawQuantity( quantity ), N+1 ) );
  }
};

/*! Power distribution traits struct for power 2
 * \ingroup one_d_distributions
 * \ingroup traits
 */
template<>
struct PowerDistributionTraits<2>
{
  //! The distribution type
  static const OneDDistributionType distribution_type = POWER_2_DISTRIBUTION;

  //! The N+1 root function
  template<typename CubedQuantity>
  static inline typename QuantityTraits<CubedQuantity>::template GetQuantityToPowerType<1,3>::type np1Root( const CubedQuantity& quantity )
  { return rpow<1,3>( quantity ); }

  //! The pow N function
  template<typename Quantity>
  static inline typename QuantityTraits<Quantity>::template GetQuantityToPowerType<2>::type powN( const Quantity& quantity )
  {
    return quantity*quantity;
  }

  //! The pow N+1 function
  template<typename Quantity>
  static inline typename QuantityTraits<Quantity>::template GetQuantityToPowerType<3>::type powNp1( const Quantity& quantity )
  {
    return quantity*quantity*quantity;
  }
};

/*! Power distribution traits struct for power 1
 * \ingroup one_d_distributions
 * \ingroup traits
 */
template<>
struct PowerDistributionTraits<1>
{
  //! The distribution type
  static const OneDDistributionType distribution_type = POWER_1_DISTRIBUTION;

  //! The N+1 root function
  template<typename SquaredQuantity>
  static inline typename QuantityTraits<SquaredQuantity>::template GetQuantityToPowerType<1,2>::type np1Root( const SquaredQuantity& quantity )
  { return Utility::sqrt( quantity ); }

  //! The pow N function
  template<typename Quantity>
  static inline Quantity powN( const Quantity& quantity )
  {
    return quantity;
  }

  //! The pow N+1 function
  template<typename Quantity>
  static inline typename QuantityTraits<Quantity>::template GetQuantityToPowerType<2>::type powNp1( const Quantity& quantity )
  {
    return quantity*quantity;
  }
};
  
} // end Details namespace

// Constructor
/*! \details This constructor will explicitly cast the input quantities to
 * the distribution quantity (which includes any unit-conversion). The
 * dimension type must match and there must be a unit-conversion defined using
 * the boost methodology.
 */
template<size_t N, typename IndependentUnit, typename DependentUnit>
template<typename InputIndepQuantity>
UnitAwarePowerDistribution<N,IndependentUnit,DependentUnit>::UnitAwarePowerDistribution(
				     const double constant_multiplier,
				     const InputIndepQuantity min_indep_limit,
				     const InputIndepQuantity max_indep_limit )
  : d_multiplier( DMQT::initializeQuantity( constant_multiplier ) ),
    d_min_indep_limit( min_indep_limit ),
    d_min_indep_limit_to_power_Np1(),
    d_max_indep_limit( max_indep_limit ),
    d_max_indep_limit_to_power_Np1(),
    d_norm_constant()
{
  // Make sure the exponent is valid
  testStaticPrecondition( N > 0 );
  // Make sure that the values are valid
  testPrecondition( !QT::isnaninf( constant_multiplier ) );
  testPrecondition( !QuantityTraits<InputIndepQuantity>::isnaninf( min_indep_limit ) );
  testPrecondition( !QuantityTraits<InputIndepQuantity>::isnaninf( max_indep_limit ) );
  // Make sure that the min value is greater than or equal to zero
  testPrecondition( min_indep_limit >=
		    QuantityTraits<InputIndepQuantity>::zero() );
  // Make sure that the max value is greater than the min value
  testPrecondition( max_indep_limit > min_indep_limit );

  this->initializeDistribution();

  BOOST_DISTRIBUTION_CLASS_EXPORT_IMPLEMENT_FINALIZE( ThisType );
}

// Copy constructor
/*! \details Just like boost::units::quantity objects, the unit-aware
 * distribution can be explicitly cast to a distribution with compatible
 * units. If the units are not compatible, this function will not compile. Note
 * that this allows distributions to be scaled safely (unit conversions
 * are completely taken care of by boost::units)!
 */
template<size_t N, typename IndependentUnit, typename DependentUnit>
template<typename InputIndepUnit, typename InputDepUnit>
UnitAwarePowerDistribution<N,IndependentUnit,DependentUnit>::UnitAwarePowerDistribution(
 const UnitAwarePowerDistribution<N,InputIndepUnit,InputDepUnit>& dist_instance )
  : d_multiplier(),
    d_min_indep_limit( dist_instance.d_min_indep_limit ),
    d_min_indep_limit_to_power_Np1(),
    d_max_indep_limit( dist_instance.d_max_indep_limit ),
    d_max_indep_limit_to_power_Np1(),
    d_norm_constant()
{
  // Make sure the exponent is valid
  testStaticPrecondition( N > 0 );
  // Make sure that the values are valid
  remember( typedef QuantityTraits<typename UnitAwarePowerDistribution<N,InputIndepUnit,InputDepUnit>::IndepQuantity> InputIQT );
  testPrecondition( !InputIQT::isnaninf( dist_instance.d_min_indep_limit ) );
  testPrecondition( !InputIQT::isnaninf( dist_instance.d_max_indep_limit ) );
  // Make sure that the min value is greater than or equal to zero
  testPrecondition( dist_instance.d_min_indep_limit >= InputIQT::zero() );
  // Make sure that the max value is greater than the min value
  testPrecondition( dist_instance.d_max_indep_limit >
		    dist_instance.d_min_indep_limit );

  typedef typename UnitAwarePowerDistribution<N,InputIndepUnit,InputDepUnit>::DepQuantity InputDepQuantity;

  typedef typename UnitAwarePowerDistribution<N,InputIndepUnit,InputDepUnit>::IndepQuantity InputIndepQuantity;

  // Calculate the scaled multiplier (for complex units, boost::units has
  // problems doing the conversion so we will do it manually)
  d_multiplier = getRawQuantity( dist_instance.d_multiplier )*
    DepQuantity( QuantityTraits<InputDepQuantity>::one() )/
    Details::PowerDistributionTraits<N>::powN(
		  IndepQuantity( QuantityTraits<InputIndepQuantity>::one() ) );

  this->initializeDistribution();

  BOOST_DISTRIBUTION_CLASS_EXPORT_IMPLEMENT_FINALIZE( ThisType );
}

// Copy constructor (copying from unitless distribution only)
template<size_t N, typename IndependentUnit, typename DependentUnit>
UnitAwarePowerDistribution<N,IndependentUnit,DependentUnit>::UnitAwarePowerDistribution( const UnitAwarePowerDistribution<N,void,void>& unitless_dist_instance, int )
  : d_multiplier( DMQT::initializeQuantity( unitless_dist_instance.d_multiplier ) ),
    d_min_indep_limit( IQT::initializeQuantity( unitless_dist_instance.d_min_indep_limit ) ),
    d_min_indep_limit_to_power_Np1(),
    d_max_indep_limit( IQT::initializeQuantity( unitless_dist_instance.d_max_indep_limit ) ),
    d_max_indep_limit_to_power_Np1(),
    d_norm_constant()
{
  // Make sure the exponent is valid
  testStaticPrecondition( N > 0 );
  // Make sure that the values are valid
  testPrecondition( !QT::isnaninf( unitless_dist_instance.d_multiplier ) );
  testPrecondition( !QT::isnaninf( unitless_dist_instance.d_min_indep_limit ));
  testPrecondition( !QT::isnaninf( unitless_dist_instance.d_max_indep_limit ));
  // Make sure that the min value is greater than or equal to zero
  testPrecondition( unitless_dist_instance.d_min_indep_limit >= QT::zero() );
  // Make sure that the max value is greater than the min value
  testPrecondition( unitless_dist_instance.d_max_indep_limit >
		    unitless_dist_instance.d_min_indep_limit );

  this->initializeDistribution();

  BOOST_DISTRIBUTION_CLASS_EXPORT_IMPLEMENT_FINALIZE( ThisType );
}

// Construct distribution from a unitless dist. (potentially dangerous)
/*! \details Constructing a unit-aware distribution from a unitless
 * distribution is potentially dangerous. By forcing users to construct objects
 * using this method instead of a standard constructor we are trying to make
 * sure users are aware of the danger. This is designed to mimic the interface
 * of the boost::units::quantity, which also has to deal with this issue.
 */
template<size_t N, typename IndependentUnit, typename DependentUnit>
UnitAwarePowerDistribution<N,IndependentUnit,DependentUnit>
UnitAwarePowerDistribution<N,IndependentUnit,DependentUnit>::fromUnitlessDistribution( const UnitAwarePowerDistribution<N,void,void>& unitless_distribution )
{
  return ThisType( unitless_distribution, 0 );
}

// Assignment operator
template<size_t N, typename IndependentUnit, typename DependentUnit>
UnitAwarePowerDistribution<N,IndependentUnit,DependentUnit>&
UnitAwarePowerDistribution<N,IndependentUnit,DependentUnit>::operator=(
                              const UnitAwarePowerDistribution& dist_instance )
{
  // Make sure the distribution is valid
  testPrecondition( dist_instance.d_min_indep_limit >= IQT::zero() );
  testPrecondition( dist_instance.d_max_indep_limit >
		    dist_instance.d_min_indep_limit );

  if( this != &dist_instance )
  {
    d_multiplier = dist_instance.d_multiplier;

    d_min_indep_limit = dist_instance.d_min_indep_limit;

    d_min_indep_limit_to_power_Np1 =
      dist_instance.d_min_indep_limit_to_power_Np1;

    d_max_indep_limit = dist_instance.d_max_indep_limit;

    d_max_indep_limit_to_power_Np1 =
      dist_instance.d_max_indep_limit_to_power_Np1;

    d_norm_constant = dist_instance.d_norm_constant;
  }

  return *this;
}

// Evaluate the distribution
template<size_t N, typename IndependentUnit, typename DependentUnit>
auto UnitAwarePowerDistribution<N,IndependentUnit,DependentUnit>::evaluate(
                     const IndepQuantity indep_var_value ) const -> DepQuantity
{
  if( indep_var_value < d_min_indep_limit )
    return DQT::zero();
  else if( indep_var_value > d_max_indep_limit )
    return DQT::zero();
  else
    return d_multiplier*Details::PowerDistributionTraits<N>::powN( indep_var_value );
}

// Evaluate the PDF
template<size_t N, typename IndependentUnit, typename DependentUnit>
auto UnitAwarePowerDistribution<N,IndependentUnit,DependentUnit>::evaluatePDF(
            const IndepQuantity indep_var_value ) const -> InverseIndepQuantity
{
  return evaluate( indep_var_value )*d_norm_constant;
}

// Return a random sample from the distribution
template<size_t N, typename IndependentUnit, typename DependentUnit>
auto UnitAwarePowerDistribution<N,IndependentUnit,DependentUnit>::sample() const -> IndepQuantity
{
  IndepQuantityNp1 argument = RandomNumberGenerator::getRandomNumber<double>()*
    (d_max_indep_limit_to_power_Np1 - d_min_indep_limit_to_power_Np1 ) +
    d_min_indep_limit_to_power_Np1;

  return Details::PowerDistributionTraits<N>::np1Root( argument );
}

// Return a random sample from the distribution
template<size_t N, typename IndependentUnit, typename DependentUnit>
auto UnitAwarePowerDistribution<N,IndependentUnit,DependentUnit>::sample(
  const UnitAwarePowerDistribution<N,IndependentUnit,DependentUnit>::IndepQuantity min_independent_value,
  const UnitAwarePowerDistribution<N,IndependentUnit,DependentUnit>::IndepQuantity max_independent_value ) -> IndepQuantity
{
  // Make sure that the values are valid
  testPrecondition( !IQT::isnaninf( min_independent_value ) );
  testPrecondition( !IQT::isnaninf( max_independent_value ) );
  // Make sure that the min value is greater than or equal to zero
  testPrecondition( min_independent_value >= IQT::zero() );
  // Make sure that the max value is greater than the min value
  testPrecondition( max_independent_value > min_independent_value );

  IndepQuantityNp1 min_indep_limit_to_power_np1 =
    Details::PowerDistributionTraits<N>::powNp1( min_independent_value );

  IndepQuantityNp1 argument = RandomNumberGenerator::getRandomNumber<double>()*
    (Details::PowerDistributionTraits<N>::powNp1( max_independent_value ) -
     min_indep_limit_to_power_np1) + min_indep_limit_to_power_np1;

  return Details::PowerDistributionTraits<N>::np1Root( argument );
}

// Return a random sample and record the number of trials
template<size_t N, typename IndependentUnit, typename DependentUnit>
typename UnitAwarePowerDistribution<N,IndependentUnit,DependentUnit>::IndepQuantity
UnitAwarePowerDistribution<N,IndependentUnit,DependentUnit>::sampleAndRecordTrials( DistributionTraits::Counter& trials ) const
{
  ++trials;

  return this->sample();
}

// Return the upper bound of the distribution independent variable
template<size_t N, typename IndependentUnit, typename DependentUnit>
typename UnitAwarePowerDistribution<N,IndependentUnit,DependentUnit>::IndepQuantity
UnitAwarePowerDistribution<N,IndependentUnit,DependentUnit>::getUpperBoundOfIndepVar() const
{
  return d_max_indep_limit;
}

// Return the lower bound of the distribution independent variable
template<size_t N, typename IndependentUnit, typename DependentUnit>
typename UnitAwarePowerDistribution<N,IndependentUnit,DependentUnit>::IndepQuantity
UnitAwarePowerDistribution<N,IndependentUnit,DependentUnit>::getLowerBoundOfIndepVar() const
{
  return d_min_indep_limit;
}

// Return the distribution type
template<size_t N, typename IndependentUnit, typename DependentUnit>
OneDDistributionType
UnitAwarePowerDistribution<N,IndependentUnit,DependentUnit>::getDistributionType() const
{
  return Details::PowerDistributionTraits<N>::distribution_type;
}

// Return the distribution type name
template<size_t N, typename IndependentUnit, typename DependentUnit>
std::string UnitAwarePowerDistribution<N,IndependentUnit,DependentUnit>::typeName(
                                                const bool verbose_name,
                                                const bool use_template_params,
                                                const std::string& delim )
{
  return BaseType::typeNameImpl( {"Power", Utility::toString(N)},
                                 verbose_name,
                                 use_template_params,
                                 delim );
}

// Return the distribution type name
template<size_t N, typename IndependentUnit, typename DependentUnit>
std::string UnitAwarePowerDistribution<N,IndependentUnit,DependentUnit>::getDistributionTypeName(
                                                   const bool verbose_name,
                                                   const bool lowercase ) const
{
  std::string name = this->typeName( verbose_name, false, " " );

  if( lowercase )
    boost::algorithm::to_lower( name );

  return name;
}

// Test if the distribution is continuous
template<size_t N, typename IndependentUnit, typename DependentUnit>
bool
UnitAwarePowerDistribution<N,IndependentUnit,DependentUnit>::isContinuous() const
{
  return true;
}

// Method for placing the object in an output stream
template<size_t N, typename IndependentUnit, typename DependentUnit>
void UnitAwarePowerDistribution<N,IndependentUnit,DependentUnit>::toStream(
						       std::ostream& os ) const
{
  this->toStreamImpl( os,
                      Utility::getRawQuantity( d_min_indep_limit ),
                      Utility::getRawQuantity( d_max_indep_limit ),
                      Utility::getRawQuantity( d_multiplier ) );
}

// Method for initializing the object from an input stream
template<size_t N, typename IndependentUnit, typename DependentUnit>
void UnitAwarePowerDistribution<N,IndependentUnit,DependentUnit>::fromStream(
                                         std::istream& is, const std::string& )
{
  VariantList distribution_data;

  this->fromStreamImpl( is, distribution_data );

  // Set the lower boundary of the distribution
  if( !distribution_data.empty() )
  {
    this->extractShapeParameter( distribution_data.front(),
                                 d_min_indep_limit );
    
    distribution_data.pop_front();
  }
  else
    d_min_indep_limit = ThisType::getDefaultLowerLimit<IndepQuantity>();

  // Set the upper boundary of the distribution
  if( !distribution_data.empty() )
  {
    this->extractShapeParameter( distribution_data.front(),
                                 d_max_indep_limit );
    
    distribution_data.pop_front();
  }
  else
    d_max_indep_limit = ThisType::getDefaultUpperLimit<IndepQuantity>();

  // Set the multiplier
  if( !distribution_data.empty() )
  {
    this->extractShapeParameter( distribution_data.front(), d_multiplier );

    distribution_data.pop_front();
  }
  else
  {
    d_multiplier =
      ThisType::getDefaultConstMultiplier<DistMultiplierQuantity>();
  }

  // Verify that the shape parameters are valid
  this->verifyValidShapeParameters( d_multiplier,
                                    d_min_indep_limit,
                                    d_max_indep_limit );

  // Check if there is any superfluous data
  this->checkForUnusedStreamData( distribution_data );

  // Initialize the distribution
  this->initializeDistribution();
}

// Method for placing the object in an output stream
template<size_t N, typename IndependentUnit, typename DependentUnit>
Utility::PropertyTree UnitAwarePowerDistribution<N,IndependentUnit,DependentUnit>::toPropertyTree( const bool inline_data ) const
{
  if( inline_data )
    return this->toInlinedPropertyTreeImpl();
  else
  {
    return this->toPropertyTreeImpl(
       std::tie(s_const_multiplier_value_key, Utility::getRawQuantity( d_multiplier )),
       std::tie(s_lower_limit_value_key, Utility::getRawQuantity(d_min_indep_limit)),
       std::tie(s_upper_limit_value_key, Utility::getRawQuantity(d_max_indep_limit)) );
  }
}

// Method for initializing the object from a property tree
template<size_t N, typename IndependentUnit, typename DependentUnit>
void UnitAwarePowerDistribution<N,IndependentUnit,DependentUnit>::fromPropertyTree( 
                                    const Utility::PropertyTree& node,
                                    std::vector<std::string>& unused_children )
{
  if( node.size() == 0 )
    this->fromInlinedPropertyTreeImpl( node );

  // Initialize from child nodes
  else
  {
    // Initialize the member data to default values
    d_multiplier =
      ThisType::getDefaultConstMultiplier<DistMultiplierQuantity>();
    d_min_indep_limit = ThisType::getDefaultLowerLimit<IndepQuantity>();
    d_max_indep_limit = ThisType::getDefaultUpperLimit<IndepQuantity>();

    // Create the data extractor map
    typename BaseType::DataExtractorMap data_extractors;

    data_extractors.insert(
     std::make_pair( s_const_multiplier_value_key,
      std::make_tuple( s_const_multiplier_value_min_match_string, false,
       std::bind<void>(&ThisType::extractShapeParameterFromNode<DistMultiplierQuantity>,
                       std::placeholders::_1,
                       std::ref(d_multiplier)) )));
    data_extractors.insert(
     std::make_pair( s_lower_limit_value_key,
      std::make_tuple( s_lower_limit_value_min_match_string, false,
       std::bind<void>(&ThisType::extractShapeParameterFromNode<IndepQuantity>,
                       std::placeholders::_1,
                       std::ref(d_min_indep_limit)) )));
    data_extractors.insert(
     std::make_pair( s_upper_limit_value_key,
      std::make_tuple( s_upper_limit_value_min_match_string, false,
       std::bind<void>(&ThisType::extractShapeParameterFromNode<IndepQuantity>,
                       std::placeholders::_1,
                       std::ref(d_max_indep_limit)) )));

    this->fromPropertyTreeImpl( node, unused_children, data_extractors );

    // Verify that the shape parameters are valid
    try{
      this->verifyValidShapeParameters( d_multiplier,
                                        d_min_indep_limit,
                                        d_max_indep_limit );
    }
    EXCEPTION_CATCH_RETHROW_AS( Utility::StringConversionException,
                                Utility::PropertyTreeConversionException,
                                "Invalid shape parameter detected!" );

    // Initialize the distribution
    this->initializeDistribution();
  }
}

// Save the distribution to an archive
template<size_t N, typename IndependentUnit, typename DependentUnit>
template<typename Archive>
void UnitAwarePowerDistribution<N,IndependentUnit,DependentUnit>::save( Archive& ar, const unsigned version ) const
{
  // Save the base class first
  ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( BaseType );

  // Save the local member data
  ar & BOOST_SERIALIZATION_NVP( d_multiplier );
  ar & BOOST_SERIALIZATION_NVP( d_min_indep_limit );
  ar & BOOST_SERIALIZATION_NVP( d_min_indep_limit_to_power_Np1 );
  ar & BOOST_SERIALIZATION_NVP( d_max_indep_limit );
  ar & BOOST_SERIALIZATION_NVP( d_max_indep_limit_to_power_Np1 );
  ar & BOOST_SERIALIZATION_NVP( d_norm_constant );
}

// Load the distribution from an archive
template<size_t N, typename IndependentUnit, typename DependentUnit>
template<typename Archive>
void UnitAwarePowerDistribution<N,IndependentUnit,DependentUnit>::load( Archive& ar, const unsigned version )
{
  // Load the base class first
  ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( BaseType );

  // Load the local member data
  ar & BOOST_SERIALIZATION_NVP( d_multiplier );
  ar & BOOST_SERIALIZATION_NVP( d_min_indep_limit );
  ar & BOOST_SERIALIZATION_NVP( d_min_indep_limit_to_power_Np1 );
  ar & BOOST_SERIALIZATION_NVP( d_max_indep_limit );
  ar & BOOST_SERIALIZATION_NVP( d_max_indep_limit_to_power_Np1 );
  ar & BOOST_SERIALIZATION_NVP( d_norm_constant );
}

// Method for testing if two objects are equivalent
template<size_t N, typename IndependentUnit, typename DependentUnit>
bool UnitAwarePowerDistribution<N,IndependentUnit,DependentUnit>::operator==( const UnitAwarePowerDistribution& other ) const
{
  return d_multiplier == other.d_multiplier &&
    d_min_indep_limit == other.d_min_indep_limit &&
    d_max_indep_limit == other.d_max_indep_limit;
}

// Method for testing if two objects are different
template<size_t N, typename IndependentUnit, typename DependentUnit>
bool UnitAwarePowerDistribution<N,IndependentUnit,DependentUnit>::operator!=( const UnitAwarePowerDistribution& other ) const
{
  return d_multiplier != other.d_multiplier ||
    d_min_indep_limit != other.d_min_indep_limit ||
    d_max_indep_limit != other.d_max_indep_limit;
}

// Initialize the distribution
template<size_t N, typename IndependentUnit, typename DependentUnit>
void UnitAwarePowerDistribution<N,IndependentUnit,DependentUnit>::initializeDistribution()
{
  // Take the limits to the power N+1
  d_min_indep_limit_to_power_Np1 =
    Details::PowerDistributionTraits<N>::powNp1( d_min_indep_limit );

  d_max_indep_limit_to_power_Np1 =
    Details::PowerDistributionTraits<N>::powNp1( d_max_indep_limit );

  // Calculate the normalization constant
  d_norm_constant = (N+1.0)/
    (d_multiplier*(d_max_indep_limit_to_power_Np1 -
  		   d_min_indep_limit_to_power_Np1 ));
}

// Test if the dependent variable can be zero within the indep bounds
template<size_t N, typename IndependentUnit, typename DependentUnit>
bool UnitAwarePowerDistribution<N,IndependentUnit,DependentUnit>::canDepVarBeZeroInIndepBounds() const
{
  if( d_min_indep_limit == IQT::zero() )
    return true;
  else
    return false;
}

// Extract a shape parameter from a node
template<size_t N, typename IndependentUnit, typename DependentUnit>
template<typename QuantityType>
void UnitAwarePowerDistribution<N,IndependentUnit,DependentUnit>::extractShapeParameterFromNode(
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
template<size_t N, typename IndependentUnit, typename DependentUnit>
template<typename QuantityType>
void UnitAwarePowerDistribution<N,IndependentUnit,DependentUnit>::extractShapeParameter(
                                  const Utility::Variant& shape_parameter_data,
                                  QuantityType& shape_parameter )
{
  double raw_shape_parameter;

  try{
    raw_shape_parameter =
      Utility::variant_cast<double>( shape_parameter_data );
  }
  EXCEPTION_CATCH_RETHROW( Utility::StringConversionException,
                           "The power distribution cannot be "
                           "constructed because a shape parameter is not "
                           "valid!" );

  Utility::setQuantity( shape_parameter, raw_shape_parameter );
}

// Verify that the shape parameters are valid
template<size_t N, typename IndependentUnit, typename DependentUnit>
void UnitAwarePowerDistribution<N,IndependentUnit,DependentUnit>::verifyValidShapeParameters(
                                const DistMultiplierQuantity& const_multiplier,
                                const IndepQuantity& lower_limit,
                                const IndepQuantity& upper_limit )
{
  TEST_FOR_EXCEPTION( DMQT::isnaninf( const_multiplier ),
		      Utility::StringConversionException,
                      "The power distribution cannot be constructed because "
                      "the multiplier is invalid!" );
  
  TEST_FOR_EXCEPTION( const_multiplier == DMQT::zero(),
                      Utility::StringConversionException,
                      "The power distribution cannot be constructed because "
                      "the multiplier is invalid!" );

  TEST_FOR_EXCEPTION( IQT::isnaninf( lower_limit ),
		      Utility::StringConversionException,
                      "The power distribution cannot be constructed because "
                      "the lower limit is invalid!" );

  TEST_FOR_EXCEPTION( lower_limit < IQT::zero(),
		      Utility::StringConversionException,
                      "The power distribution cannot be constructed because "
                      "the lower limit is invalid!" );

  TEST_FOR_EXCEPTION( IQT::isnaninf( upper_limit ),
                      Utility::StringConversionException,
                      "The power distribution cannot be constructed because "
                      "the upper limit is invalid!" );

  TEST_FOR_EXCEPTION( upper_limit <= lower_limit,
		      Utility::StringConversionException,
		      "The power distribution cannot be constructed because "
                      "the upper limit is invalid!" );
}

} // end Utility namespace

EXTERN_EXPLICIT_DISTRIBUTION_INST( UnitAwarePowerDistribution<1,void,void> );
EXTERN_EXPLICIT_DISTRIBUTION_INST( UnitAwarePowerDistribution<2,void,void> );

#endif // end UTILITY_POWER_DISTRIBUTION_DEF_HPP

//---------------------------------------------------------------------------//
// end Utility_PowerDistribution_def.hpp
//---------------------------------------------------------------------------//
