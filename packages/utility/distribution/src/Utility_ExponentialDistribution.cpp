//---------------------------------------------------------------------------//
//!
//! \file   Utility_ExponentialDistribution.cpp
//! \author Alex Robinson
//! \brief  Exponential distribution class definition.
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <limits>

// Trilinos Includes
#include <Teuchos_Utils.hpp>

// FRENSIE Includes
#include "Utility_ExponentialDistribution.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_ExceptionTestMacros.hpp"

namespace Utility{

// Default constructor
ExponentialDistribution::ExponentialDistribution()
{ /* ... */ }

// Constructor
ExponentialDistribution::ExponentialDistribution( 
					     const double constant_multiplier,
					     const double exponent_multiplier )
  : d_constant_multiplier( constant_multiplier ),
    d_exponent_multiplier( exponent_multiplier )
{
  // Make sure the multipliers are valid
  testPrecondition( !ST::isnaninf( constant_multiplier ) );
  testPrecondition( !ST::isnaninf( exponent_multiplier ) );
  // Make sure that the exponent multiplier is positive
  testPrecondition( exponent_multiplier > 0.0 );
}

// Copy constructor
ExponentialDistribution::ExponentialDistribution( 
				 const ExponentialDistribution& dist_instance )
  : d_constant_multiplier( dist_instance.d_constant_multiplier ),
    d_exponent_multiplier( dist_instance.d_exponent_multiplier )
{
  // Make sure the multipliers are valid
  testPrecondition( !ST::isnaninf( dist_instance.d_constant_multiplier ) );
  testPrecondition( !ST::isnaninf( dist_instance.d_exponent_multiplier ) );
  // Make sure that the exponent multiplier is positive
  testPrecondition( dist_instance.d_exponent_multiplier > 0.0 );
}

// Assignment operator
ExponentialDistribution& ExponentialDistribution::operator=( 
				 const ExponentialDistribution& dist_instance )
{
  // Make sure the distribution is valid
  testPrecondition( !ST::isnaninf( dist_instance.d_constant_multiplier ) );
  testPrecondition( !ST::isnaninf( dist_instance.d_exponent_multiplier ) );
  testPrecondition( dist_instance.d_exponent_multiplier > 0.0 );

  if( this != &dist_instance )
  {
    d_constant_multiplier = dist_instance.d_constant_multiplier;
    d_exponent_multiplier = dist_instance.d_exponent_multiplier;
  }
  
  return *this;
}

// Evaluate the distribution
double ExponentialDistribution::evaluate( const double indep_var_value ) const
{
  if( indep_var_value < 0.0 )
    return 0.0;
  else
    return d_constant_multiplier*evaluateExponential( indep_var_value );
}

// Evaluate the PDF
/*! \details PDF(x) = m*exp(-m*x) if x >= 0, = 0 if x < 0
 */ 
double ExponentialDistribution::evaluatePDF( 
					   const double indep_var_value ) const
{
  if( indep_var_value < 0.0 )
    return 0.0;
  else
    return d_exponent_multiplier*evaluateExponential( indep_var_value );
}

// Return a sample from the distribution
/*! \details x = -ln(rnd)/m
 */
double ExponentialDistribution::sample()
{
  return (const_cast<const ExponentialDistribution*>(this))->sample();
}

// Return a sample from the distribution
/*! \details x = -ln(rnd)/m
 */
double ExponentialDistribution::sample() const
{
  double random_number = RandomNumberGenerator::getRandomNumber<double>();

  return -log( random_number )/d_exponent_multiplier;
}

// Return the sampling efficiency
double ExponentialDistribution::getSamplingEfficiency() const
{
  return 1.0;
}

// Return the upper bound of the distribution independent variable
double ExponentialDistribution::getUpperBoundOfIndepVar() const
{
  return std::numeric_limits<double>::infinity();
}

// Return the lower bound of the distribution independent variable
double ExponentialDistribution::getLowerBoundOfIndepVar() const
{
  return 0.0;
}

// Evaluate the exponential
double ExponentialDistribution::evaluateExponential( 
					   const double indep_var_value ) const
{
  return exp( -d_exponent_multiplier*indep_var_value );
}

// Return the distribution type
OneDDistributionType ExponentialDistribution::getDistributionType() const
{
  return ExponentialDistribution::distribution_type;
}

// Method for placing the object in an output stream
void ExponentialDistribution::toStream( std::ostream& os ) const
{
  os << "{" << d_constant_multiplier << "," << d_exponent_multiplier << "}";
}

// Method for initializing the object from an input stream
void ExponentialDistribution::fromStream( std::istream& is )
{
  // Read in the distribution representation
  std::string dist_rep;
  std::getline( is, dist_rep, '}' );
  dist_rep += '}';

  Teuchos::Array<double> distribution;
  try{
    distribution = Teuchos::fromStringToArray<double>( dist_rep );
  }
  catch( Teuchos::InvalidArrayStringRepresentation& error )
  {
    std::string message( "Error: the exponential distribution cannot be "
			 "constructed because the representation is not valid "
			 "(see details below)!\n" );
    message += error.what();

    throw InvalidDistributionStringRepresentation( message );
  }

  TEST_FOR_EXCEPTION( distribution.size() != 2,
		      InvalidDistributionStringRepresentation,
		      "Error: the exponential distribution cannot be "
		      "constructed because the representation is not valid "
		      "(only two values may be specified)!" );

  d_constant_multiplier = distribution[0];

  TEST_FOR_EXCEPTION( ST::isnaninf( d_constant_multiplier ),
		      InvalidDistributionStringRepresentation,
		      "Error: the exponential distribution cannot be "
		      "constructed because of an invalid constant "
		      "multiplier " << d_constant_multiplier );

  d_exponent_multiplier = distribution[1];

  TEST_FOR_EXCEPTION( ST::isnaninf( d_exponent_multiplier ),
		      InvalidDistributionStringRepresentation,
		      "Error: the exponential distribution cannot be "
		      "constructed because of an invalid exponent "
		      "multiplier " << d_exponent_multiplier );
}

// Method for testing if two objects are equivalent
bool ExponentialDistribution::isEqual( 
				   const ExponentialDistribution& other ) const
{
  return d_constant_multiplier == other.d_constant_multiplier &&
    d_exponent_multiplier == other.d_exponent_multiplier;
}

} // end Utility namespace

//---------------------------------------------------------------------------//
// end Utility_ExponentialDistribution.cpp
//---------------------------------------------------------------------------//
