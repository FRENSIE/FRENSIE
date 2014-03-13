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
#include "PhysicalConstants.hpp"
#include "ContractException.hpp"

namespace FACEMC{

// Initialize the constant multiplier
const double NormalDistribution::constant_multiplier = 
  1.0/sqrt( 2*PhysicalConstants::pi );

// Constructor
NormalDistribution::NormalDistribution( const double mean,
					const double standard_deviation,
					const double min_independent_value,
					const double max_independent_value )
  : d_mean( mean ),
    d_standard_deviation( standard_deviation ),
    d_min_independent_value( min_independent_value ),
    d_max_independent_value( max_independent_value ),
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
  if( indep_var_value < d_min_independent_value )
    return 0.0;
  else if( indep_var_value > d_max_independent_value )
    return 0.0;
  else
  {
    double argument = -(indep_var_value-d_mean)*(indep_var_value-d_mean)/
      (2*d_standard_deviation*d_standard_deviation);
  
    return NormalDistribution::constant_multiplier*exp( argument );
  }
}

// Return a sample from the distribution
double NormalDistribution::sample()
{
  double random_number_1, random_number_2;
  double x, y, sample;
  
  while( true )
  {
    // Use the rejection sampling technique outlined by Kahn in "Applications 
    // of Mone Carlo" (1954)
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

    // stretch and shift the sampled value
    sample = d_standard_deviation*x+d_mean;

    if( sample >= d_min_independent_value && 
	sample <= d_max_independent_value )
      break;
  }
  
  return sample;
}

// Return the sampling efficiency from the distribution
double NormalDistribution::getSamplingEfficiency() const
{
  if( d_trials > 0 )
    return static_cast<double>(d_samples)/d_trials;
  else
    return 0.0;
}

// Return the upper bound of the distribution independent variable
double NormalDistribution::getUpperBoundOfIndepVar() const
{
  return d_max_independent_value;
}

// Return the lower bound of the distribution independent variable
double NormalDistribution::getLowerBoundOfIndepVar() const
{
  return d_min_independent_value;
}

// Return the distribution type
OneDDistributionType NormalDistribution::getDistributionType() const
{
  return NormalDistribution::distribution_type;
}

} // end FACEMC namespace

//---------------------------------------------------------------------------//
// end NormalDistribution.cpp
//---------------------------------------------------------------------------//
