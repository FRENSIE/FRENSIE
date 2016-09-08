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
#include "Utility_ArrayString.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_ExceptionCatchMacros.hpp"
#include "Utility_ContractException.hpp"

namespace Utility{

// Default constructor
template<typename IndependentUnit, typename DependentUnit>
UnitAwarePolynomialDistribution<IndependentUnit,DependentUnit>::UnitAwarePolynomialDistribution()
{ /* ... */ }

// Constructor
/*! \details This constructor will explicitly cast the input quantities to
 * the distribution quantity (which includes any unit-conversion). The
 * dimension type must match and there must be a unit-conversion defined using
 * the boost methodology.
 */
template<typename IndependentUnit, typename DependentUnit>
template<typename InputIndepQuantity>
UnitAwarePolynomialDistribution<IndependentUnit,DependentUnit>::UnitAwarePolynomialDistribution(
			            const Teuchos::Array<double>& coefficients,
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
  testPrecondition( !QT::isnaninf( dist_instance.d_indep_limits_to_series_powers_p1.front().first ) );
  testPrecondition( !QT::isnaninf( dist_instance.d_indep_limits_to_series_powers_p1.front().second ) );

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
	    dist_instance.d_indep_limits_to_series_powers_p1.front().first ) );

  IndepQuantity max_indep_limit(
    QuantityTraits<InputIndepQuantity>::initializeQuantity(
	   dist_instance.d_indep_limits_to_series_powers_p1.front().second ) );

  this->initializeDistribution( min_indep_limit, max_indep_limit );
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
  testPrecondition( !QT::isnaninf( dist_instance.d_indep_limits_to_series_powers_p1.front().first ) );
  testPrecondition( !QT::isnaninf( dist_instance.d_indep_limits_to_series_powers_p1.front().second ) );
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
  testPrecondition( !QT::isnaninf( dist_instance.d_indep_limits_to_series_powers_p1.front().first ) );
  testPrecondition( !QT::isnaninf( dist_instance.d_indep_limits_to_series_powers_p1.front().second ) );

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

  if( raw_indep_var_value < d_indep_limits_to_series_powers_p1.front().first )
    return DQT::zero();
  else if( raw_indep_var_value >
	   d_indep_limits_to_series_powers_p1.front().second )
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
    (d_indep_limits_to_series_powers_p1[sampled_term].second -
     d_indep_limits_to_series_powers_p1[sampled_term].first) +
    d_indep_limits_to_series_powers_p1[sampled_term].first;

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
UnitAwarePolynomialDistribution<IndependentUnit,DependentUnit>::sampleAndRecordTrials( unsigned& trials ) const
{
  ++trials;

  return this->sample();
}

// Return the upper bound of the distribution independent variable
template<typename IndependentUnit, typename DependentUnit>
typename UnitAwarePolynomialDistribution<IndependentUnit,DependentUnit>::IndepQuantity
UnitAwarePolynomialDistribution<IndependentUnit,DependentUnit>::getUpperBoundOfIndepVar() const
{
  return IQT::initializeQuantity( d_indep_limits_to_series_powers_p1.front().second );
}

// Return the lower bound of the distribution independent variable
template<typename IndependentUnit, typename DependentUnit>
typename UnitAwarePolynomialDistribution<IndependentUnit,DependentUnit>::IndepQuantity
UnitAwarePolynomialDistribution<IndependentUnit,DependentUnit>::getLowerBoundOfIndepVar() const
{
  return IQT::initializeQuantity( d_indep_limits_to_series_powers_p1.front().first );
}

// Return the distribution type
template<typename IndependentUnit, typename DependentUnit>
OneDDistributionType
UnitAwarePolynomialDistribution<IndependentUnit,DependentUnit>::getDistributionType() const
{
  return UnitAwarePolynomialDistribution::distribution_type;
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
  os << "{" << d_coefficients
     << "," << d_indep_limits_to_series_powers_p1.front().first
     << "," << d_indep_limits_to_series_powers_p1.front().second
     << "}";
}

// Method for initializing the object from an input stream
template<typename IndependentUnit, typename DependentUnit>
void UnitAwarePolynomialDistribution<IndependentUnit,DependentUnit>::fromStream( std::istream& is )
{
  // Read the initial '{'
  std::string start_bracket;
  std::getline( is, start_bracket, '{' );
  start_bracket = Teuchos::Utils::trimWhiteSpace( start_bracket );

  TEST_FOR_EXCEPTION( start_bracket.size() != 0,
		      InvalidDistributionStringRepresentation,
		      "Error: the input stream is not a valid polynomial "
		      "distribution representation!" );

  std::string coeffs_rep;
  std::getline( is, coeffs_rep, '}' );
  coeffs_rep += '}';

  // Parse special characters
  try{
    ArrayString::locateAndReplacePi( coeffs_rep );
    ArrayString::locateAndReplaceIntervalOperator( coeffs_rep );
  }
  EXCEPTION_CATCH_RETHROW_AS( std::runtime_error,
			      InvalidDistributionStringRepresentation,
			      "Error: the polynomial distribution cannot be "
			      "constructed because the representation is not "
			      "valid (see details below)!\n" );

  d_coefficients.clear();
  try{
    d_coefficients = Teuchos::fromStringToArray<double>( coeffs_rep );
  }
  EXCEPTION_CATCH_RETHROW_AS( Teuchos::InvalidArrayStringRepresentation,
			      InvalidDistributionStringRepresentation,
			      "Error: the polynomial distribution cannot be "
			      "constructed because the representation is not "
			      "valid (see details below)!\n" );

  // Read the ","
  std::string separator;
  std::getline( is, separator, ',' );

  // Read the rest of the values
  std::string limits_rep( "{" );
  std::string raw_limits_rep;
  std::getline( is, raw_limits_rep, '}' );
  raw_limits_rep += '}';

  limits_rep += raw_limits_rep;

  try{
    ArrayString::locateAndReplacePi( limits_rep );
  }
  EXCEPTION_CATCH_RETHROW_AS( std::runtime_error,
			      InvalidDistributionStringRepresentation,
			      "Error: the polynomial distribution cannot be "
			      "constructed because the representation is not "
			      "valid (see details below)!\n" );

  Teuchos::Array<double> independent_limits;
  try{
    independent_limits =
      Teuchos::fromStringToArray<double>( limits_rep );
  }
  EXCEPTION_CATCH_RETHROW_AS( Teuchos::InvalidArrayStringRepresentation,
			      InvalidDistributionStringRepresentation,
			      "Error: the polynomial distribution cannot be "
			      "constructed because the representation is not "
			      "valid (see details below)!\n" );

  TEST_FOR_EXCEPTION( independent_limits.size() != 2,
		      InvalidDistributionStringRepresentation,
		      "Error: the polynomial distribution cannot be "
		      "constructed because a lower and upper limit were not "
		      "given - "
		      << independent_limits.size() << " limits were given "
		      << independent_limits << "!" );

  TEST_FOR_EXCEPTION( independent_limits[0] >= independent_limits[1],
		      InvalidDistributionStringRepresentation,
		      "Error: the polynomial distribution cannot be "
		      "constructed because the lower limit is not less than "
		      " the upper limit (" << independent_limits[0] << ","
		      << independent_limits[1] << ")!" );

  // Make sure the distribution is valid for sampling
  TEST_FOR_EXCEPTION( !ThisType::isValidSamplingDistribution(
			    d_coefficients,
			    IQT::initializeQuantity( independent_limits[0] ),
			    IQT::initializeQuantity( independent_limits[1] ) ),
		      InvalidDistributionStringRepresentation,
		      "Error: each term of the polynomial distribution is not "
		      "a positive functions and can therefor not be used for "
		      "sampling!" );

  this->initializeDistribution(
			    IQT::initializeQuantity( independent_limits[0] ),
			    IQT::initializeQuantity( independent_limits[1] ) );
}

// Method for testing if two objects are equivalent
template<typename IndependentUnit, typename DependentUnit>
bool UnitAwarePolynomialDistribution<IndependentUnit,DependentUnit>::isEqual(
 const UnitAwarePolynomialDistribution<IndependentUnit,DependentUnit>& other ) const
{
  return d_coefficients == other.d_coefficients &&
    d_indep_limits_to_series_powers_p1.front().first ==
    other.d_indep_limits_to_series_powers_p1.front().first &&
    d_indep_limits_to_series_powers_p1.front().second ==
    other.d_indep_limits_to_series_powers_p1.front().second;
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
    d_indep_limits_to_series_powers_p1[i].first =
      min_indep_limit_to_term_power_p1;
    d_indep_limits_to_series_powers_p1[i].second =
      max_indep_limit_to_term_power_p2;

    min_indep_limit_to_term_power_p1 *= getRawQuantity( max_indep_limit );
    max_indep_limit_to_term_power_p2 *= getRawQuantity( max_indep_limit );
  }

  // Calculate the norm constant and the term sampling cdf
  d_term_sampling_cdf.resize( d_coefficients.size() );

  for( unsigned i = 0; i < d_coefficients.size(); ++i )
  {
    d_term_sampling_cdf[i] = d_coefficients[i]/(i+1u)*
      (d_indep_limits_to_series_powers_p1[i].second -
       d_indep_limits_to_series_powers_p1[i].first);

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

// Test if the distribution can be used for sampling (each term must be a
// positive function
template<typename IndependentUnit, typename DependentUnit>
bool UnitAwarePolynomialDistribution<IndependentUnit,DependentUnit>::isValidSamplingDistribution(
  const Teuchos::Array<double>& coefficients,
  const typename UnitAwarePolynomialDistribution<IndependentUnit,DependentUnit>::IndepQuantity min_indep_limit,
  const typename UnitAwarePolynomialDistribution<IndependentUnit,DependentUnit>::IndepQuantity max_indep_limit )
{
  bool valid = true;

  // There must be at least one term
  if( coefficients.size() == 0 )
    valid = false;

  // There must be at least one non-zero term
  Teuchos::Array<double>::const_iterator element, end;
  element = coefficients.begin();
  end = coefficients.end();

  while( element != end )
  {
    if( *element != 0.0 )
      break;

    ++element;
  }

  // All terms are zero
  if( element == end )
    valid = false;

  // The term coefficients must all have the same sign (sign of limits)
  if( min_indep_limit < IQT::zero() &&
      max_indep_limit > IQT::zero() )
    valid = false;
  else if( min_indep_limit < IQT::zero() &&
	   max_indep_limit <= IQT::zero() )
  {
    for( unsigned i = 0; i < coefficients.size(); ++i )
    {
      if( coefficients[i] > 0.0 )
	valid = false;
    }
    valid = true;
  }
  else if( min_indep_limit >= IQT::zero() &&
	   max_indep_limit > IQT::zero() )
  {
    for( unsigned i = 0; i < coefficients.size(); ++i )
    {
      if( coefficients[i] < 0.0 )
	valid = false;
    }
    valid = true;
  }
  // The limits cannot be equal
  else
    valid = false;

  return valid;
}

} // end Utility namespace

#endif // end UTILITY_POLYNOMIAL_DISTRIBUTION_DEF_HPP

//---------------------------------------------------------------------------//
// end Utility_UnitAwarePolynomialDistribution_def.hpp
//---------------------------------------------------------------------------//
