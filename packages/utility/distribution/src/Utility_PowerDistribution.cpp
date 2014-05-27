//---------------------------------------------------------------------------//
//! 
//! \file   Utility_PowerDistribution.cpp
//! \author Alex Robinson
//! \brief  Power distribution class definition (N=1,N=2)
//!
//---------------------------------------------------------------------------//

// FRNECS Includes
#include "Utility_PowerDistribution.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_ContractException.hpp"

namespace Utility{

// Constructor
PowerDistribution<2u>::PowerDistribution( const double constant_multiplier,
					  const double min_indep_limit,
					  const double max_indep_limit )
  : d_constant_multiplier( constant_multiplier ),
    d_min_indep_limit( min_indep_limit ),
    d_min_indep_limit_cubed( min_indep_limit*min_indep_limit*min_indep_limit ),
    d_max_indep_limit( max_indep_limit ),
    d_max_indep_limit_cubed( max_indep_limit*max_indep_limit*max_indep_limit )
{
  // Make sure that the values are valid
  testPrecondition( !ST::isnaninf( constant_multiplier ) );
  testPrecondition( !ST::isnaninf( min_indep_limit ) );
  testPrecondition( !ST::isnaninf( max_indep_limit ) );
  // Make sure that the min value is greater than or equal to zero
  testPrecondition( min_indep_limit >= 0.0 );
  // Make sure that the max value is greater than the min value
  testPrecondition( max_indep_limit > min_indep_limit ); 
}

// Constructor
PowerDistribution<1u>::PowerDistribution( const double constant_multiplier,
					  const double min_indep_limit,
					  const double max_indep_limit )
  : d_constant_multiplier( constant_multiplier ),
    d_min_indep_limit( min_indep_limit ),
    d_min_indep_limit_squared( min_indep_limit*min_indep_limit ),
    d_max_indep_limit( max_indep_limit ),
    d_max_indep_limit_squared( max_indep_limit*max_indep_limit )
{
  // Make sure that the values are valid
  testPrecondition( !ST::isnaninf( constant_multiplier ) );
  testPrecondition( !ST::isnaninf( min_indep_limit ) );
  testPrecondition( !ST::isnaninf( max_indep_limit ) );
  // Make sure that the min value is greater than or equal to zero
  testPrecondition( min_indep_limit >= 0.0 );
  // Make sure that the max value is greater than the min value
  testPrecondition( max_indep_limit > min_indep_limit ); 
}

// Evaluate the distribution
double PowerDistribution<2u>::evaluate( const double indep_var_value ) const
{
  if( indep_var_value < d_min_indep_limit )
    return 0.0;
  else if( indep_var_value > d_max_indep_limit )
    return 0.0;
  else
    return d_constant_multiplier*indep_var_value*indep_var_value;
}

// Evaluate the distribution
double PowerDistribution<1u>::evaluate( const double indep_var_value ) const
{
  if( indep_var_value < d_min_indep_limit )
    return 0.0;
  else if( indep_var_value > d_max_indep_limit )
    return 0.0;
  else
    return d_constant_multiplier*indep_var_value;
}

// Evaluate the PDF
double PowerDistribution<2u>::evaluatePDF( const double indep_var_value ) const
{
  if( indep_var_value < d_min_indep_limit )
    return 0.0;
  else if( indep_var_value > d_max_indep_limit )
    return 0.0;
  else
  {
    return 3*indep_var_value*indep_var_value/
      (d_max_indep_limit_cubed - d_min_indep_limit_cubed );
  }
}

// Evaluate the PDF
double PowerDistribution<1u>::evaluatePDF( const double indep_var_value ) const
{
  if( indep_var_value < d_min_indep_limit )
    return 0.0;
  else if( indep_var_value > d_max_indep_limit )
    return 0.0;
  else
  {
    return 2*indep_var_value/
      (d_max_indep_limit_squared - d_min_indep_limit_squared );
  }
}

// Return a random sample from the distribution
double PowerDistribution<2u>::sample()
{
  return (const_cast<const PowerDistribution<2u>*>(this))->sample();
}

// Return a random sample from the distribution
double PowerDistribution<1u>::sample()
{
  return (const_cast<const PowerDistribution<1u>*>(this))->sample();
}

// Return a random sample from the distribution
double PowerDistribution<2u>::sample() const
{
  double random_number = RandomNumberGenerator::getRandomNumber<double>();
  
  double argument = random_number*
    (d_max_indep_limit_cubed - d_min_indep_limit_cubed) + 
    d_min_indep_limit_cubed;

  return pow( argument, 1.0/3.0 );
}

// Return a random sample from the distribution
double PowerDistribution<1u>::sample() const
{
  double random_number = RandomNumberGenerator::getRandomNumber<double>();
  
  double argument = random_number*
    (d_max_indep_limit_squared - d_min_indep_limit_squared) + 
    d_min_indep_limit_squared;

  return sqrt( argument );
}

// Return the sampling efficiency from the distribution
double PowerDistribution<2u>::getSamplingEfficiency() const
{
  return 1.0;
}

// Return the sampling efficiency from the distribution
double PowerDistribution<1u>::getSamplingEfficiency() const
{
  return 1.0;
}

// Return the upper bound of the distribution independent variable
double PowerDistribution<2u>::getUpperBoundOfIndepVar() const
{
  return d_max_indep_limit;
}

// Return the upper bound of the distribution independent variable
double PowerDistribution<1u>::getUpperBoundOfIndepVar() const
{
  return d_max_indep_limit;
}

// Return the lower bound of the distribution independent variable
double PowerDistribution<2u>::getLowerBoundOfIndepVar() const 
{
  return d_min_indep_limit;
}

// Return the lower bound of the distribution independent variable
double PowerDistribution<1u>::getLowerBoundOfIndepVar() const 
{
  return d_min_indep_limit;
}

// Return the distribution type
OneDDistributionType PowerDistribution<2u>::getDistributionType() const
{
  return PowerDistribution<2u>::distribution_type;
}

// Return the distribution type
OneDDistributionType PowerDistribution<1u>::getDistributionType() const
{
  return PowerDistribution<1u>::distribution_type;
}

} // end Utility namespace

//---------------------------------------------------------------------------//
// end Utility_PowerDistribution.cpp
//---------------------------------------------------------------------------//
