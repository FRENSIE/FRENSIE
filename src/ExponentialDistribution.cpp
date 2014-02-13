//---------------------------------------------------------------------------//
//!
//! \file   ExponentialDistribution.cpp
//! \author Alex Robinson
//! \brief  Exponential distribution class definition.
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <limits>

// FACEMC Includes
#include "ExponentialDistribution.hpp"
#include "RandomNumberGenerator.hpp"

namespace FACEMC{

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
  double random_number = RandomNumberGenerator::getRandomNumber<double>();

  return sample( random_number );
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

} // end FACEMC namespace

//---------------------------------------------------------------------------//
// end ExponentialDistribution.cpp
//---------------------------------------------------------------------------//
