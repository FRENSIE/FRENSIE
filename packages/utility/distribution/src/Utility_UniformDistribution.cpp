//---------------------------------------------------------------------------//
//!
//! \file   Utility_UniformDistribution.cpp
//! \author Alex Robinson
//! \brief  Uniform distribution class declaration.
//!
//---------------------------------------------------------------------------//

// FRNECS Includes
#include "Utility_UniformDistribution.hpp"
#include "Utility_RandomNumberGenerator.hpp"

namespace Utility{

// Constructor
UniformDistribution::UniformDistribution( const double min_independent_value, 
					  const double max_independent_value,
					  const double dependent_value )
  : d_min_independent_value( min_independent_value ),
    d_max_independent_value( max_independent_value ),
    d_dependent_value( dependent_value ),
    d_pdf_value( 1.0/(max_independent_value - min_independent_value) )
{
  // Make sure that the values are valid
  testPrecondition( !ST::isnaninf( min_independent_value ) );
  testPrecondition( !ST::isnaninf( max_independent_value ) );
  testPrecondition( !ST::isnaninf( dependent_value ) );
  // Make sure that the max value is greater than the min value
  testPrecondition( max_independent_value > min_independent_value );
}

// Evaluate the distribution
double UniformDistribution::evaluate( const double indep_var_value ) const
{
  if( indep_var_value >= d_min_independent_value && 
      indep_var_value <= d_max_independent_value )
    return d_dependent_value;
  else
    return 0.0;
}

// Evaluate the PDF
double UniformDistribution::evaluatePDF( const double indep_var_value ) const
{
  if( indep_var_value >= d_min_independent_value &&
      indep_var_value <= d_max_independent_value )
    return d_pdf_value;
  else
    return 0.0;
}

// Return a random sample from the distribution
double UniformDistribution::sample()
{
  return (const_cast<const UniformDistribution*>(this))->sample();
}

// Return a random sample from the distribution
double UniformDistribution::sample() const
{
  double random_number = RandomNumberGenerator::getRandomNumber<double>();

  return random_number*(d_max_independent_value - d_min_independent_value) +
    d_min_independent_value;
}

// Return the sampling efficiency from the distribution
double UniformDistribution::getSamplingEfficiency() const
{
  return 1.0;
}

// Return the upper bound of the distribution independent variable
double UniformDistribution::getUpperBoundOfIndepVar() const
{
  return d_max_independent_value;
}

// Return the lower bound of the distribution independent variable
double UniformDistribution::getLowerBoundOfIndepVar() const
{
  return d_min_independent_value;
}

// Return the distribution type
OneDDistributionType UniformDistribution::getDistributionType() const
{
  return UniformDistribution::distribution_type;
}

} // end Utility namespace

//---------------------------------------------------------------------------//
// end Utility_UniformDistribution.cpp
//---------------------------------------------------------------------------//
