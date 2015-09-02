//---------------------------------------------------------------------------//
//!
//! \file   Utility_PolynomialDistribution.cpp
//! \author Alex Robinson
//! \brief  Polynomial distribution class definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "Utility_PolynomialDistribution.hpp"
#include "Utility_ExponentiationAlgorithms.hpp"
#include "Utility_ArrayString.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_ExceptionCatchMacros.hpp"
#include "Utility_ContractException.hpp"

namespace Utility{

// Default constructor
PolynomialDistribution::PolynomialDistribution()
{ /* ... */ }

// Constructor
PolynomialDistribution::PolynomialDistribution(
			            const Teuchos::Array<double>& coefficients,
				    const double min_indep_limit,
				    const double max_indep_limit )
  : d_coefficients( coefficients ),
    d_term_sampling_cdf( coefficients.size() ),
    d_indep_limits_to_series_powers_p1( coefficients.size() ),
    d_norm_constant( 1.0 )
{
  // Make sure the polynomial is valid
  testPrecondition( coefficients.size() > 0 );
  // Make sure the values are valid
  testPrecondition( !ST::isnaninf( min_indep_limit ) );
  testPrecondition( !ST::isnaninf( max_indep_limit ) );

  initializeDistribution( min_indep_limit, max_indep_limit );
}

// Copy constructor
PolynomialDistribution::PolynomialDistribution(
				  const PolynomialDistribution& dist_instance )
  : d_coefficients( dist_instance.d_coefficients ),
    d_term_sampling_cdf( dist_instance.d_term_sampling_cdf ),
    d_indep_limits_to_series_powers_p1(
			    dist_instance.d_indep_limits_to_series_powers_p1 ),
    d_norm_constant( dist_instance.d_norm_constant )
{
  // Make sure the polynomial is valid
  testPrecondition( dist_instance.d_coefficients.size() > 0 );
  // Make sure the values are valid
  testPrecondition( !ST::isnaninf( dist_instance.d_indep_limits_to_series_powers_p1.front().first ) );
  testPrecondition( !ST::isnaninf( dist_instance.d_indep_limits_to_series_powers_p1.front().second ) );
}

// Assignment operator
PolynomialDistribution& PolynomialDistribution::operator=( 
				  const PolynomialDistribution& dist_instance )
{
  // Make sure the polynomial is valid
  testPrecondition( dist_instance.d_coefficients.size() > 0 );
  // Make sure the values are valid
  testPrecondition( !ST::isnaninf( dist_instance.d_indep_limits_to_series_powers_p1.front().first ) );
  testPrecondition( !ST::isnaninf( dist_instance.d_indep_limits_to_series_powers_p1.front().second ) );

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
double PolynomialDistribution::evaluate( const double indep_var_value ) const
{
  if( indep_var_value < d_indep_limits_to_series_powers_p1.front().first )
    return 0.0;
  else if( indep_var_value > d_indep_limits_to_series_powers_p1.front().second)
    return 0.0;
  else
  {
    double dep_value = 0.0;
    double indep_var_to_series_power = 1.0;

    for( unsigned i = 0; i < d_coefficients.size(); ++i )
    {
      dep_value += d_coefficients[i]*indep_var_to_series_power;

      indep_var_to_series_power *= indep_var_value;
    }

    return dep_value;
  }
}

// Evaluate the PDF
double PolynomialDistribution::evaluatePDF( const double indep_var_value) const
{
  return evaluate( indep_var_value )*d_norm_constant;
}

// Return a random sample from the distribution
/*! \details The probability mixing technique is used to sample from the
 * polynomial exactly.
 */
double PolynomialDistribution::sample() const
{
  double random_number_1 = RandomNumberGenerator::getRandomNumber<double>();

  unsigned sampled_term;
  
  // Sample which term of the series will be used to sample from
  for( unsigned i = 0; i < d_term_sampling_cdf.size(); ++i )
  {
    if( random_number_1 < d_term_sampling_cdf[i] )
    {
      sampled_term = i;

      break;
    }
  }

  double argument = RandomNumberGenerator::getRandomNumber<double>()*
    (d_indep_limits_to_series_powers_p1[sampled_term].second - 
     d_indep_limits_to_series_powers_p1[sampled_term].first) +
    d_indep_limits_to_series_powers_p1[sampled_term].first;

  if( sampled_term == 0u )
    return argument;
  else if( sampled_term == 1u )
    return sqrt( argument );
  else
    return pow( argument, 1.0/(sampled_term+1u) );
}

//! Return a random sample and record the number of trials
double PolynomialDistribution::sampleAndRecordTrials( unsigned& trials ) const
{
  ++trials;

  return this->sample();
}

// Return the upper bound of the distribution independent variable
double PolynomialDistribution::getUpperBoundOfIndepVar() const
{
  return d_indep_limits_to_series_powers_p1.front().second;
}

// Return the lower bound of the distribution independent variable
double PolynomialDistribution::getLowerBoundOfIndepVar() const
{
  return d_indep_limits_to_series_powers_p1.front().first;
}

// Return the distribution type
OneDDistributionType PolynomialDistribution::getDistributionType() const
{
  return PolynomialDistribution::distribution_type;
}

// Test if the distribution is continuous
bool PolynomialDistribution::isContinuous() const
{
  return true;
}

// Method for placing the object in an output stream
void PolynomialDistribution::toStream( std::ostream& os ) const
{
  os << "{" << d_coefficients
     << "," << d_indep_limits_to_series_powers_p1.front().first
     << "," << d_indep_limits_to_series_powers_p1.front().second
     << "}";
}

// Method for initializing the object from an input stream
void PolynomialDistribution::fromStream( std::istream& is )
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

  initializeDistribution( independent_limits[0], independent_limits[1] );

  // Make sure the distribution is valid for sampling
  TEST_FOR_EXCEPTION( !isValidSamplingDistribution(),
		      InvalidDistributionStringRepresentation,
		      "Error: each term of the polynomial distribution is not "
		      "a positive functions and can therefor not be used for "
		      "sampling!" );
}

// Method for testing if two objects are equivalent
bool PolynomialDistribution::isEqual( const PolynomialDistribution& other ) const
{
  return d_coefficients == other.d_coefficients &&
    d_indep_limits_to_series_powers_p1.front().first ==
    other.d_indep_limits_to_series_powers_p1.front().first &&
    d_indep_limits_to_series_powers_p1.front().second ==
    other.d_indep_limits_to_series_powers_p1.front().second;
}

// Initialize the distribution
void PolynomialDistribution::initializeDistribution(		            
						 const double min_indep_limit,
						 const double max_indep_limit )
{
  d_indep_limits_to_series_powers_p1.resize( d_coefficients.size() );
  double min_indep_limit_to_term_power_p1 = min_indep_limit;
  double max_indep_limit_to_term_power_p2 = max_indep_limit;

  for( unsigned i = 0; i < d_coefficients.size(); ++i )
  {
    d_indep_limits_to_series_powers_p1[i].first = 
      min_indep_limit_to_term_power_p1;
    d_indep_limits_to_series_powers_p1[i].second = 
      max_indep_limit_to_term_power_p2;

    min_indep_limit_to_term_power_p1 *= max_indep_limit;
    max_indep_limit_to_term_power_p2 *= max_indep_limit;
  }

  // Calculate the norm constant
  d_norm_constant = 0.0;
  
  for( unsigned i = 0; i < d_coefficients.size(); ++i )
  {
    d_norm_constant += d_coefficients[i]/(i+1u)*
      (d_indep_limits_to_series_powers_p1[i].second -
       d_indep_limits_to_series_powers_p1[i].first);
  }

  d_norm_constant = 1.0/d_norm_constant;

  // Calculate the term sampling cdf
  d_term_sampling_cdf.resize( d_coefficients.size() );

  for( unsigned i = 0; i < d_coefficients.size(); ++i )
  {
    d_term_sampling_cdf[i] = d_coefficients[i]/(i+1u)*d_norm_constant*
      (d_indep_limits_to_series_powers_p1[i].second -
       d_indep_limits_to_series_powers_p1[i].first);

    if( i > 0 )
      d_term_sampling_cdf[i] += d_term_sampling_cdf[i-1];
  }
  
  // Make sure the term sampling cdf has been constructed correctly
  testPostcondition( d_term_sampling_cdf.back() == 1.0 );
}

// Test if the distribution can be used for sampling (each term must be a
// positive function
bool PolynomialDistribution::isValidSamplingDistribution()
{
  if( d_indep_limits_to_series_powers_p1.front().first < 0.0 &&
      d_indep_limits_to_series_powers_p1.front().second > 0.0 )
    return false;
  else if( d_indep_limits_to_series_powers_p1.front().first  < 0.0 &&  
	   d_indep_limits_to_series_powers_p1.front().second <= 0.0 )
  {
    for( unsigned i = 0; i < d_coefficients.size(); ++i )
    {
      if( d_coefficients[i] > 0.0 )
	return false;
    }
    return true;
  }
  else if( d_indep_limits_to_series_powers_p1.front().first  >= 0.0 &&  
	   d_indep_limits_to_series_powers_p1.front().second > 0.0 )
  {
    for( unsigned i = 0; i < d_coefficients.size(); ++i )
    {
      if( d_coefficients[i] < 0.0 )
	return false;
    }
    return true;
  }
  else
    return false;
}

} // end Utility namespace

//---------------------------------------------------------------------------//
// end Utility_PolynomialDistribution.cpp
//---------------------------------------------------------------------------//
