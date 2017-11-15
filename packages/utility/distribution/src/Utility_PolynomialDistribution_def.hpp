//---------------------------------------------------------------------------//
//!
//! \file   Utility_PolynomialDistribution_def.hpp
//! \author Alex Robinson
//! \brief  Polynomial distribution class definition
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_POLYNOMIAL_DISTRIBUTION_DEF_HPP
#define UTILITY_POLYNOMIAL_DISTRIBUTION_DEF_HPP

// FRENSIE Includes
#include "Utility_ExponentiationAlgorithms.hpp"
#include "Utility_SearchAlgorithms.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_ExceptionCatchMacros.hpp"
#include "Utility_ContractException.hpp"

BOOST_DISTRIBUTION_CLASS_EXPORT_IMPLEMENT( UnitAwarePolynomialDistribution );

namespace Utility{

// Initialize static member data
template<typename IndependentUnit, typename DependentUnit>
const std::string UnitAwarePolynomialDistribution<IndependentUnit,DependentUnit>::s_coefficient_values_key( "coefficients" );

template<typename IndependentUnit, typename DependentUnit>
const std::string UnitAwarePolynomialDistribution<IndependentUnit,DependentUnit>::s_coefficient_values_min_match_string( "coeff" );

template<typename IndependentUnit, typename DependentUnit>
const std::string UnitAwarePolynomialDistribution<IndependentUnit,DependentUnit>::s_lower_limit_value_key( "lower boundary" );

template<typename IndependentUnit, typename DependentUnit>
const std::string UnitAwarePolynomialDistribution<IndependentUnit,DependentUnit>::s_lower_limit_value_min_match_string( "lower" );

template<typename IndependentUnit, typename DependentUnit>
const std::string UnitAwarePolynomialDistribution<IndependentUnit,DependentUnit>::s_upper_limit_value_key( "upper boundary" );

template<typename IndependentUnit, typename DependentUnit>
const std::string UnitAwarePolynomialDistribution<IndependentUnit,DependentUnit>::s_upper_limit_value_min_match_string( "upper" );

// Default constructor
template<typename IndependentUnit, typename DependentUnit>
UnitAwarePolynomialDistribution<IndependentUnit,DependentUnit>::UnitAwarePolynomialDistribution()
  : d_coefficients(),
    d_term_sampling_cdf(),
    d_indep_limits_to_series_powers_p1( {std::make_tuple( 0.0, 1.0 )} ),
    d_norm_constant()
{ 
  BOOST_DISTRIBUTION_CLASS_EXPORT_IMPLEMENT_FINALIZE( UnitAwarePolynomialDistribution<IndependentUnit,DependentUnit> );
}

// Constructor
/*! \details This constructor will explicitly cast the input quantities to
 * the distribution quantity (which includes any unit-conversion). The
 * dimension type must match and there must be a unit-conversion defined using
 * the boost methodology.
 */
template<typename IndependentUnit, typename DependentUnit>
template<typename InputIndepQuantity>
UnitAwarePolynomialDistribution<IndependentUnit,DependentUnit>::UnitAwarePolynomialDistribution(
			            const std::vector<double>& coefficients,
				    const InputIndepQuantity min_indep_limit,
				    const InputIndepQuantity max_indep_limit )
  : d_coefficients( coefficients ),
    d_term_sampling_cdf( coefficients.size() ),
    d_indep_limits_to_series_powers_p1( coefficients.size() ),
    d_norm_constant( DNQT::one() )
{
  // Make sure there is at least one term
  testPrecondition( coefficients.size() > 0 );
  // Make sure the limits are valid
  testPrecondition( !QuantityTraits<InputIndepQuantity>::isnaninf( min_indep_limit ) );
  testPrecondition( !QuantityTraits<InputIndepQuantity>::isnaninf( max_indep_limit ) );
  // Make sure the polynomial can be used for sampling
  testPrecondition( ThisType::isValidSamplingDistribution(
					  coefficients,
					  IndepQuantity( min_indep_limit ),
					  IndepQuantity( max_indep_limit ) ) );

  this->initializeDistribution( IndepQuantity( min_indep_limit ),
				IndepQuantity( max_indep_limit ) );

  BOOST_DISTRIBUTION_CLASS_EXPORT_IMPLEMENT_FINALIZE( UnitAwarePolynomialDistribution<IndependentUnit,DependentUnit> );
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
UnitAwarePolynomialDistribution<IndependentUnit,DependentUnit>::UnitAwarePolynomialDistribution(
 const UnitAwarePolynomialDistribution<InputIndepUnit,InputDepUnit>& dist_instance )
  : d_coefficients( dist_instance.d_coefficients.size() ),
    d_term_sampling_cdf( dist_instance.d_term_sampling_cdf.size() ),
    d_indep_limits_to_series_powers_p1(
		     dist_instance.d_indep_limits_to_series_powers_p1.size() ),
    d_norm_constant()
{
  // Make sure there is at least on term
  testPrecondition( dist_instance.d_coefficients.size() > 0 );
  // Make sure the limits are valid
  testPrecondition( !QT::isnaninf( Utility::get<0>(dist_instance.d_indep_limits_to_series_powers_p1.front()) ) );
  testPrecondition( !QT::isnaninf( Utility::get<1>(dist_instance.d_indep_limits_to_series_powers_p1.front()) ) );

  typedef typename UnitAwarePolynomialDistribution<InputIndepUnit,InputDepUnit>::DepQuantity InputDepQuantity;

  typedef typename UnitAwarePolynomialDistribution<InputIndepUnit,InputDepUnit>::IndepQuantity InputIndepQuantity;

  double coeff_scale_factor =
    getRawQuantity( DepQuantity( QuantityTraits<InputDepQuantity>::one() ) );

  // Scale the coefficients
  for( unsigned i = 0u; i < d_coefficients.size(); ++i )
  {
    d_coefficients[i] = dist_instance.d_coefficients[i]*coeff_scale_factor;

    coeff_scale_factor /=
      getRawQuantity(IndepQuantity(QuantityTraits<InputIndepQuantity>::one()));
  }

  IndepQuantity min_indep_limit(
    QuantityTraits<InputIndepQuantity>::initializeQuantity(
          Utility::get<0>(dist_instance.d_indep_limits_to_series_powers_p1.front()) ) );

  IndepQuantity max_indep_limit(
    QuantityTraits<InputIndepQuantity>::initializeQuantity(
          Utility::get<1>(dist_instance.d_indep_limits_to_series_powers_p1.front()) ) );

  this->initializeDistribution( min_indep_limit, max_indep_limit );

  BOOST_DISTRIBUTION_CLASS_EXPORT_IMPLEMENT_FINALIZE( UnitAwarePolynomialDistribution<IndependentUnit,DependentUnit> );
}

// Copy constructor (copying from unitless distribution only)
template<typename IndependentUnit, typename DependentUnit>
UnitAwarePolynomialDistribution<IndependentUnit,DependentUnit>::UnitAwarePolynomialDistribution(
	       const UnitAwarePolynomialDistribution<void,void>& dist_instance,
	       int )
  : d_coefficients( dist_instance.d_coefficients ),
    d_term_sampling_cdf( dist_instance.d_term_sampling_cdf ),
    d_indep_limits_to_series_powers_p1(
		            dist_instance.d_indep_limits_to_series_powers_p1 ),
    d_norm_constant( DNQT::initializeQuantity(dist_instance.d_norm_constant) )
{
  // Make sure there is at least one term
  testPrecondition( dist_instance.d_coefficients.size() > 0 );
  // Make sure the limits are valid
  testPrecondition( !QT::isnaninf( Utility::get<0>( dist_instance.d_indep_limits_to_series_powers_p1.front() ) ) );
  testPrecondition( !QT::isnaninf( Utility::get<1>( dist_instance.d_indep_limits_to_series_powers_p1.front() ) ) );

  BOOST_DISTRIBUTION_CLASS_EXPORT_IMPLEMENT_FINALIZE( UnitAwarePolynomialDistribution<IndependentUnit,DependentUnit> );
}

// Construct distribution from a unitless dist. (potentially dangerous)
/*! \details Constructing a unit-aware distribution from a unitless
 * distribution is potentially dangerous. By forcing users to construct objects
 * using this method instead of a standard constructor we are trying to make
 * sure users are aware of the danger. This is designed to mimic the interface
 * of the boost::units::quantity, which also has to deal with this issue.
 */
template<typename IndependentUnit, typename DependentUnit>
UnitAwarePolynomialDistribution<IndependentUnit,DependentUnit>
UnitAwarePolynomialDistribution<IndependentUnit,DependentUnit>::fromUnitlessDistribution(
      const UnitAwarePolynomialDistribution<void,void>& unitless_distribution )
{
  return ThisType( unitless_distribution, 0 );
}

// Assignment operator
template<typename IndependentUnit, typename DependentUnit>
UnitAwarePolynomialDistribution<IndependentUnit,DependentUnit>&
UnitAwarePolynomialDistribution<IndependentUnit,DependentUnit>::operator=(
  const UnitAwarePolynomialDistribution<IndependentUnit,DependentUnit>& dist_instance )
{
  // Make sure there is at least one term
  testPrecondition( dist_instance.d_coefficients.size() > 0 );
  // Make sure the values are valid
  testPrecondition( !QT::isnaninf( Utility::get<0>(dist_instance.d_indep_limits_to_series_powers_p1.front()) ) );
  testPrecondition( !QT::isnaninf( Utility::get<1>(dist_instance.d_indep_limits_to_series_powers_p1.front()) ) );

  if( this != &dist_instance )
  {
    d_coefficients = dist_instance.d_coefficients;
    d_term_sampling_cdf = dist_instance.d_term_sampling_cdf;
    d_indep_limits_to_series_powers_p1 =
			      dist_instance.d_indep_limits_to_series_powers_p1;
    d_norm_constant = dist_instance.d_norm_constant;
  }

  return *this;
}

// Evaluate the distribution
template<typename IndependentUnit, typename DependentUnit>
typename UnitAwarePolynomialDistribution<IndependentUnit,DependentUnit>::DepQuantity
UnitAwarePolynomialDistribution<IndependentUnit,DependentUnit>::evaluate(
const typename UnitAwarePolynomialDistribution<IndependentUnit,DependentUnit>::IndepQuantity indep_var_value ) const
{
  double raw_indep_var_value = getRawQuantity( indep_var_value );

  if( raw_indep_var_value <
      Utility::get<0>( d_indep_limits_to_series_powers_p1.front() ) )
    return DQT::zero();
  else if( raw_indep_var_value >
	   Utility::get<1>( d_indep_limits_to_series_powers_p1.front() ) )
    return DQT::zero();
  else
  {
    double dep_value = 0.0;
    double indep_var_to_series_power = 1.0;

    for( unsigned i = 0; i < d_coefficients.size(); ++i )
    {
      dep_value += d_coefficients[i]*indep_var_to_series_power;

      indep_var_to_series_power *= raw_indep_var_value;
    }

    return DQT::initializeQuantity( dep_value );
  }
}

// Evaluate the PDF
template<typename IndependentUnit, typename DependentUnit>
typename UnitAwarePolynomialDistribution<IndependentUnit,DependentUnit>::InverseIndepQuantity
UnitAwarePolynomialDistribution<IndependentUnit,DependentUnit>::evaluatePDF(
 const typename UnitAwarePolynomialDistribution<IndependentUnit,DependentUnit>::IndepQuantity indep_var_value) const
{
  return this->evaluate( indep_var_value )*d_norm_constant;
}

// Return a random sample from the distribution
/*! \details The probability mixing technique is used to sample from the
 * polynomial exactly (as long as all coefficients have the same sign).
 */
template<typename IndependentUnit, typename DependentUnit>
typename UnitAwarePolynomialDistribution<IndependentUnit,DependentUnit>::IndepQuantity
UnitAwarePolynomialDistribution<IndependentUnit,DependentUnit>::sample() const
{
  double random_number_1 = RandomNumberGenerator::getRandomNumber<double>();

  unsigned sampled_term =
    Search::binaryUpperBoundIndex( d_term_sampling_cdf.begin(),
				   d_term_sampling_cdf.end(),
				   random_number_1 );

  double argument = RandomNumberGenerator::getRandomNumber<double>()*
    (Utility::get<1>(d_indep_limits_to_series_powers_p1[sampled_term]) -
     Utility::get<0>(d_indep_limits_to_series_powers_p1[sampled_term]) ) +
    Utility::get<0>(d_indep_limits_to_series_powers_p1[sampled_term]);

  double sample;

  if( sampled_term == 0u )
    sample = argument;
  else if( sampled_term == 1u )
    sample = sqrt( argument );
  else
    sample = pow( argument, 1.0/(sampled_term+1u) );

  return IQT::initializeQuantity( sample );
}

//! Return a random sample and record the number of trials
template<typename IndependentUnit, typename DependentUnit>
typename UnitAwarePolynomialDistribution<IndependentUnit,DependentUnit>::IndepQuantity
UnitAwarePolynomialDistribution<IndependentUnit,DependentUnit>::sampleAndRecordTrials( DistributionTraits::Counter& trials ) const
{
  ++trials;

  return this->sample();
}

// Return the upper bound of the distribution independent variable
template<typename IndependentUnit, typename DependentUnit>
typename UnitAwarePolynomialDistribution<IndependentUnit,DependentUnit>::IndepQuantity
UnitAwarePolynomialDistribution<IndependentUnit,DependentUnit>::getUpperBoundOfIndepVar() const
{
  return IQT::initializeQuantity( Utility::get<1>(d_indep_limits_to_series_powers_p1.front()) );
}

// Return the lower bound of the distribution independent variable
template<typename IndependentUnit, typename DependentUnit>
typename UnitAwarePolynomialDistribution<IndependentUnit,DependentUnit>::IndepQuantity
UnitAwarePolynomialDistribution<IndependentUnit,DependentUnit>::getLowerBoundOfIndepVar() const
{
  return IQT::initializeQuantity( Utility::get<0>(d_indep_limits_to_series_powers_p1.front()) );
}

// Return the distribution type
template<typename IndependentUnit, typename DependentUnit>
OneDDistributionType
UnitAwarePolynomialDistribution<IndependentUnit,DependentUnit>::getDistributionType() const
{
  return UnitAwarePolynomialDistribution::distribution_type;
}

// Return the distribution type name
template<typename IndependentUnit, typename DependentUnit>
std::string UnitAwarePolynomialDistribution<IndependentUnit,DependentUnit>::typeName(
                                                const bool verbose_name,
                                                const bool use_template_params,
                                                const std::string& delim )
{
  return BaseType::typeNameImpl( "Polynomial",
                                 verbose_name,
                                 use_template_params,
                                 delim );
}

// Return the distribution type name
template<typename IndependentUnit, typename DependentUnit>
std::string UnitAwarePolynomialDistribution<IndependentUnit,DependentUnit>::getDistributionTypeName(
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
bool UnitAwarePolynomialDistribution<IndependentUnit,DependentUnit>::isContinuous() const
{
  return true;
}

// Method for placing the object in an output stream
template<typename IndependentUnit, typename DependentUnit>
void UnitAwarePolynomialDistribution<IndependentUnit,DependentUnit>::toStream( std::ostream& os ) const
{
  this->toStreamImpl( os,
                      d_coefficients,
                      Utility::get<0>(d_indep_limits_to_series_powers_p1.front()),
                      Utility::get<1>(d_indep_limits_to_series_powers_p1.front()) );
}

// Method for initializing the object from an input stream
template<typename IndependentUnit, typename DependentUnit>
void UnitAwarePolynomialDistribution<IndependentUnit,DependentUnit>::fromStream( std::istream& is, const std::string& )
{
  VariantList distribution_data;

  this->fromStreamImpl( is, distribution_data );

  // Extract the coefficients
  TEST_FOR_EXCEPTION( distribution_data.empty(),
                      Utility::StringConversionException,
                      "The " << this->getDistributionTypeName( true, false ) <<
                      " could not be constructed because no coefficients "
                      "are specified!" );

  this->extractCoefficients( distribution_data.front(), d_coefficients );

  distribution_data.pop_front();
  
  // Extract the lower limit
  TEST_FOR_EXCEPTION( distribution_data.empty(),
                      Utility::StringConversionException,
                      "The " << this->getDistributionTypeName( true, false ) <<
                      " could not be constructed because the lower limit "
                      "was not specified!" );

  IndepQuantity lower_limit;
  this->extractLimit( distribution_data.front(), lower_limit );
  
  distribution_data.pop_front();

  // Extract the upper limit
  TEST_FOR_EXCEPTION( distribution_data.empty(),
                      Utility::StringConversionException,
                      "The " << this->getDistributionTypeName( true, false ) <<
                      " could not be constructed because the upper limit "
                      "was not specified!" );

  IndepQuantity upper_limit;
  this->extractLimit( distribution_data.front(), upper_limit );

  distribution_data.pop_front();

  // Verify that the values are valid
  this->verifyValidDistributionData( d_coefficients, lower_limit, upper_limit );

  // Initialize the distribution
  this->initializeDistribution( lower_limit, upper_limit );

  // Check if there is any superfluous data
  this->checkForUnusedStreamData( distribution_data );
}

// Method for converting the type to a property tree
template<typename IndependentUnit, typename DependentUnit>
Utility::PropertyTree UnitAwarePolynomialDistribution<IndependentUnit,DependentUnit>::toPropertyTree(
                                                 const bool inline_data ) const
{
  if( inline_data )
    return this->toInlinedPropertyTreeImpl();
  else
  {
    return this->toPropertyTreeImpl(
                          std::tie( s_coefficient_values_key, d_coefficients ),
                          std::tie( s_lower_limit_value_key, Utility::get<0>(d_indep_limits_to_series_powers_p1.front()) ),
                          std::tie( s_upper_limit_value_key, Utility::get<1>(d_indep_limits_to_series_powers_p1.front()) ) );
  }
}

// Method for initializing the object from a property tree node
template<typename IndependentUnit, typename DependentUnit>
void UnitAwarePolynomialDistribution<IndependentUnit,DependentUnit>::fromPropertyTree(
                                    const Utility::PropertyTree& node,
                                    std::vector<std::string>& unused_children )
{
  // Initialize from inline data
  if( node.size() == 0 )
    this->fromInlinedPropertyTreeImpl( node );
  
  // Initialize from child nodes
  else
  {
    IndepQuantity lower_limit, upper_limit;
    
    typename BaseType::DataExtractorMap data_extractors;

    data_extractors.insert(
     std::make_pair( s_coefficient_values_key,
      std::make_tuple( s_coefficient_values_min_match_string, true,
                       std::bind<void>(&ThisType::extractCoefficientsFromNode,
                                       std::placeholders::_1,
                                       std::ref(d_coefficients) ) ) ) );
    data_extractors.insert(
     std::make_pair( s_lower_limit_value_key,
      std::make_tuple( s_lower_limit_value_min_match_string, true,
       std::bind<void>(&ThisType::extractLimitFromNode<IndepQuantity>,
                       std::placeholders::_1,
                       std::ref(lower_limit) ) ) ) );
    data_extractors.insert(
     std::make_pair( s_upper_limit_value_key,
      std::make_tuple( s_upper_limit_value_min_match_string, true,
       std::bind<void>(&ThisType::extractLimitFromNode<IndepQuantity>,
                       std::placeholders::_1,
                       std::ref(upper_limit) ) ) ) );

    this->fromPropertyTreeImpl( node, unused_children, data_extractors );

    // Verify that the values are valid
    try{
      this->verifyValidDistributionData( d_coefficients, lower_limit, upper_limit );
    }
    EXCEPTION_CATCH_RETHROW_AS( Utility::StringConversionException,
                                Utility::PropertyTreeConversionException,
                                "Invalid parameter(s) detected!" );

    // Initialize the distribution
    this->initializeDistribution( lower_limit, upper_limit );
  }
}

// Save the distribution to an archive
template<typename IndependentUnit, typename DependentUnit>
template<typename Archive>
void UnitAwarePolynomialDistribution<IndependentUnit,DependentUnit>::save( Archive& ar, const unsigned version ) const
{
  // Save the base class first
  ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( BaseType );

  // Save the local member data
  ar & BOOST_SERIALIZATION_NVP( d_coefficients );
  ar & BOOST_SERIALIZATION_NVP( d_term_sampling_cdf );
  ar & BOOST_SERIALIZATION_NVP( d_indep_limits_to_series_powers_p1 );
  ar & BOOST_SERIALIZATION_NVP( d_norm_constant );
}

// Load the distribution from an archive
template<typename IndependentUnit, typename DependentUnit>
template<typename Archive>
void UnitAwarePolynomialDistribution<IndependentUnit,DependentUnit>::load( Archive& ar, const unsigned version )
{
  // Load the base class first
  ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( BaseType );

  // Load the local member data
  ar & BOOST_SERIALIZATION_NVP( d_coefficients );
  ar & BOOST_SERIALIZATION_NVP( d_term_sampling_cdf );
  ar & BOOST_SERIALIZATION_NVP( d_indep_limits_to_series_powers_p1 );
  ar & BOOST_SERIALIZATION_NVP( d_norm_constant );
}

// Method for testing if two objects are equivalent
template<typename IndependentUnit, typename DependentUnit>
bool UnitAwarePolynomialDistribution<IndependentUnit,DependentUnit>::operator==(
                           const UnitAwarePolynomialDistribution& other ) const
{
  return d_coefficients == other.d_coefficients &&
    Utility::get<0>(d_indep_limits_to_series_powers_p1.front()) ==
    Utility::get<0>(other.d_indep_limits_to_series_powers_p1.front()) &&
    Utility::get<1>(d_indep_limits_to_series_powers_p1.front()) ==
    Utility::get<1>(other.d_indep_limits_to_series_powers_p1.front());
}

// Method for testing if two objects are equivalent
template<typename IndependentUnit, typename DependentUnit>
bool UnitAwarePolynomialDistribution<IndependentUnit,DependentUnit>::operator!=(
                           const UnitAwarePolynomialDistribution& other ) const
{
  return d_coefficients != other.d_coefficients ||
    Utility::get<0>(d_indep_limits_to_series_powers_p1.front()) !=
    Utility::get<0>(other.d_indep_limits_to_series_powers_p1.front()) ||
    Utility::get<1>(d_indep_limits_to_series_powers_p1.front()) !=
    Utility::get<1>(other.d_indep_limits_to_series_powers_p1.front());
}

// Initialize the distribution
template<typename IndependentUnit, typename DependentUnit>
void UnitAwarePolynomialDistribution<IndependentUnit,DependentUnit>::initializeDistribution(
 const typename UnitAwarePolynomialDistribution<IndependentUnit,DependentUnit>::IndepQuantity min_indep_limit,
 const typename UnitAwarePolynomialDistribution<IndependentUnit,DependentUnit>::IndepQuantity max_indep_limit )
{
  d_indep_limits_to_series_powers_p1.resize( d_coefficients.size() );
  double min_indep_limit_to_term_power_p1 = getRawQuantity( min_indep_limit );
  double max_indep_limit_to_term_power_p2 = getRawQuantity( max_indep_limit );

  for( unsigned i = 0; i < d_coefficients.size(); ++i )
  {
    Utility::get<0>(d_indep_limits_to_series_powers_p1[i]) =
      min_indep_limit_to_term_power_p1;
    Utility::get<1>(d_indep_limits_to_series_powers_p1[i]) =
      max_indep_limit_to_term_power_p2;

    min_indep_limit_to_term_power_p1 *= getRawQuantity( max_indep_limit );
    max_indep_limit_to_term_power_p2 *= getRawQuantity( max_indep_limit );
  }

  // Calculate the norm constant and the term sampling cdf
  d_term_sampling_cdf.resize( d_coefficients.size() );

  for( unsigned i = 0; i < d_coefficients.size(); ++i )
  {
    d_term_sampling_cdf[i] = d_coefficients[i]/(i+1u)*
      (Utility::get<1>(d_indep_limits_to_series_powers_p1[i]) -
       Utility::get<0>(d_indep_limits_to_series_powers_p1[i]));

    if( i > 0 )
      d_term_sampling_cdf[i] += d_term_sampling_cdf[i-1];
  }

  double raw_norm_constant = 1.0/d_term_sampling_cdf.back();

  d_norm_constant = DNQT::initializeQuantity( raw_norm_constant );

  // Normalize the term sampling cdf
  for( unsigned i = 0; i < d_term_sampling_cdf.size(); ++i )
    d_term_sampling_cdf[i] *= raw_norm_constant;

  // Check for round-off error
  if( fabs( d_term_sampling_cdf.back() - 1.0 ) < 1e-9 )
    d_term_sampling_cdf.back() = 1.0;

  // Make sure the term sampling cdf has been constructed correctly
  testPostcondition( d_term_sampling_cdf.back() == 1.0 );
}

// Test if the dependent variable can be zero within the indep bounds
template<typename IndependentUnit, typename DependentUnit>
bool UnitAwarePolynomialDistribution<IndependentUnit,DependentUnit>::canDepVarBeZeroInIndepBounds() const
{
  if( d_coefficients[0] == 0 )
  {
    if( Utility::get<0>(d_indep_limits_to_series_powers_p1.front()) == 0.0 )
      return true;
    else if( Utility::get<1>(d_indep_limits_to_series_powers_p1.front()) == 0.0 )
      return true;
    else
      return false;
  }
  else
    return false;
}

// Extract coefficients from a node
template<typename IndependentUnit, typename DependentUnit>
void UnitAwarePolynomialDistribution<IndependentUnit,DependentUnit>::extractCoefficientsFromNode(
                                 const Utility::PropertyTree& coefficient_data,
                                 std::vector<double>& coefficients )
{
  // Inline array
  if( coefficient_data.size() == 0 )
    ThisType::extractCoefficients( coefficient_data.data(), coefficients );

  // JSON array
  else
  {
    try{
      coefficients = Utility::fromPropertyTree<std::vector<double> >( coefficient_data );
    }
    EXCEPTION_CATCH_RETHROW( Utility::PropertyTreeConversionException,
                             "The polynomial distribution cannot be "
                             "constructed because the coefficients are not "
                             "valid!" );
  }
}

// Extract coefficients
template<typename IndependentUnit, typename DependentUnit>
void UnitAwarePolynomialDistribution<IndependentUnit,DependentUnit>::extractCoefficients(
                                      const Utility::Variant& coefficient_data,
                                      std::vector<double>& coefficients )
{
  try{
    coefficients = Utility::variant_cast<std::vector<double> >( coefficient_data );
  }
  EXCEPTION_CATCH_RETHROW( Utility::StringConversionException,
                           "The polynomial distribution cannot be "
                           "constructed because the coefficients are "
                           "not valid!" );
}

// Extract a limit from a node
template<typename IndependentUnit, typename DependentUnit>
template<typename QuantityType>
void UnitAwarePolynomialDistribution<IndependentUnit,DependentUnit>::extractLimitFromNode(
                                       const Utility::PropertyTree& limit_data,
                                       QuantityType& limit )
{
  // The data must be inlined in the node
  TEST_FOR_EXCEPTION( limit_data.size() != 0,
                      Utility::PropertyTreeConversionException,
                      "Could not extract the limit value!" );

  ThisType::extractLimit( limit_data.data(), limit );
}

// Extract a limit
template<typename IndependentUnit, typename DependentUnit>
template<typename QuantityType>
void UnitAwarePolynomialDistribution<IndependentUnit,DependentUnit>::extractLimit(
                                            const Utility::Variant& limit_data,
                                            QuantityType& limit )
{
  double raw_limit;
  
  try{
    raw_limit = Utility::variant_cast<double>( limit_data );
  }
  EXCEPTION_CATCH_RETHROW( Utility::StringConversionException,
                           "The polynomial distribution cannot be "
                           "constructed because a limit is not "
                           "valid!" );

  Utility::setQuantity( limit, raw_limit );
}

// Verify that the distribution data is valid
template<typename IndependentUnit, typename DependentUnit>
void UnitAwarePolynomialDistribution<IndependentUnit,DependentUnit>::verifyValidDistributionData(
                                       const std::vector<double>& coefficients,
                                       const IndepQuantity min_indep_limit,
                                       const IndepQuantity max_indep_limit )
{
  TEST_FOR_EXCEPTION( coefficients.size() == 0,
                      Utility::StringConversionException,
                      "The polynomial distribution cannot be constructed "
                      "because there are no coefficients specified!" );

  std::vector<double>::const_iterator non_zero_coefficient =
    std::find_if( coefficients.begin(),
                  coefficients.end(),
                  []( double coeff ){ return coeff != 0.0; } );

  TEST_FOR_EXCEPTION( non_zero_coefficient == coefficients.end(),
                      Utility::StringConversionException,
                      "The polynomial distribution cannot be constructed "
                      "because all coeffients are zero!" );

  std::vector<double>::const_iterator bad_coefficient =
    std::find_if( coefficients.begin(),
                  coefficients.end(),
                  []( double coeff ){ return coeff < 0.0 || Utility::isnaninf( coeff ); } );

  TEST_FOR_EXCEPTION( bad_coefficient != coefficients.end(),
                      Utility::StringConversionException,
                      "The polynomial distribution cannot be constructed "
                      "because an invalid (negative or inf) coefficient ("
                      << *bad_coefficient << ") "
                      "was encountered at index "
                      << std::distance(coefficients.begin(), bad_coefficient)<<
                      "!" );

  TEST_FOR_EXCEPTION( min_indep_limit < IQT::zero(),
                      Utility::StringConversionException,
                      "The polynomial distribution cannot be constructed "
                      "because the lower limits is negative!" );
  
  TEST_FOR_EXCEPTION( max_indep_limit <= min_indep_limit,
                      Utility::StringConversionException,
                      "The polynomial distribution cannot be constructed "
                      "because the limits are invalid!" );
}

// Test if the distribution can be used for sampling (each term must be a
// positive function
template<typename IndependentUnit, typename DependentUnit>
bool UnitAwarePolynomialDistribution<IndependentUnit,DependentUnit>::isValidSamplingDistribution(
                                    const std::vector<double>& coefficients,
                                    const IndepQuantity min_indep_limit,
                                    const IndepQuantity max_indep_limit )
{
  bool valid = true;
  
  try{
    ThisType::verifyValidDistributionData( coefficients, min_indep_limit, max_indep_limit );
  }
  catch( ... )
  { valid = false; }

  return valid;
}

} // end Utility namespace

EXTERN_EXPLICIT_DISTRIBUTION_INST( UnitAwarePolynomialDistribution<void,void> );

#endif // end UTILITY_POLYNOMIAL_DISTRIBUTION_DEF_HPP

//---------------------------------------------------------------------------//
// end Utility_UnitAwarePolynomialDistribution_def.hpp
//---------------------------------------------------------------------------//
