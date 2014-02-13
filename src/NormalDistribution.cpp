//---------------------------------------------------------------------------//
//!
//! \file   NormalDistribution.cpp
//! \author Alex Robinson
//! \brief  Normal distribution class declaration.
//!
//---------------------------------------------------------------------------//

// FACEMC Includes
#include "NormalDistribution.hpp"
#include "RandomNumberGenerator.hpp"
#include "ContractException.hpp"

namespace FACEMC{

// Initialize the constant multiplier
const double NormalDistribution::constant_multiplier = 
  1.0/sqrt( 2*acos( -1.0 ) );

// Constructor
NormalDistribution::NormalDistribution( const double mean,
					const double standard_deviation )
  : d_mean( mean ),
    d_standard_deviation( standard_deviation ),
    d_trials( 0 ),
    d_samples( 0 )
{
  // Make sure that the values are valid
  testPrecondition( !ST::isnaninf( mean ) );
  testPrecondition( !ST::isnaninf( standard_deviation ) );
  // Make sure that the standard deviation is positive
  testPrecondition( standard_deviation > 0.0 );
}

// Evaluate the distribution
double NormalDistribution::evaluate( const double indep_var_value ) const
{
  return evaluatePDF( indep_var_value );
}

// Evaluate the PDF
double NormalDistribution::evaluatePDF( const double indep_var_value ) const
{
  double argument = -(indep_var_value-d_mean)*(indep_var_value-d_mean)/
    (2*d_standard_deviation*d_standard_deviation);
  
  return NormalDistribution::constant_multiplier*exp( argument );
}

// Return a sample from the distribution
double NormalDistribution::sample()
{
  double random_number_1, random_number_2;
  double x, y;
  
  while( true )
  {
    random_number_1 = RandomNumberGenerator::getRandomNumber<double>();
    random_number_2 = RandomNumberGenerator::getRandomNumber<double>();
    
    x = -log( random_number_1 );
    y = -log( random_number_2 );
    
    if( 0.5*(x - 1)*(x - 1) <= y )
    {
      ++d_samples;
      ++d_trials;
      break;
    }
    else
      ++d_trials;
  }

  if( RandomNumberGenerator::getRandomNumber<double>() < 0.5 )
    x *= -1.0;

  return x;
}

// Return the sampling efficiency from the distribution
double NormalDistribution::getSamplingEfficiency() const
{
  return static_cast<double>(d_samples)/d_trials;
}

// Return the upper bound of the distribution independent variable
double NormalDistribution::getUpperBoundOfIndepVar() const
{
  return std::numeric_limits<double>::infinity();
}

// Return the lower bound of the distribution independent variable
double NormalDistribution::getLowerBoundOfIndepVar() const
{
  return -std::numeric_limits<double>::infinity();
}

} // end FACEMC namespace

//---------------------------------------------------------------------------//
// end NormalDistribution.cpp
//---------------------------------------------------------------------------//
