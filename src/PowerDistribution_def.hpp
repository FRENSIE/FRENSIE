//---------------------------------------------------------------------------//
//!
//! \file   PowerDistribution_def.hpp
//! \author Alex Robinson
//! \brief  Power distribution class definition (N>2).
//!
//---------------------------------------------------------------------------//

// FACEMC Includes
#include "ContractException.hpp"
#include "ExponentiationAlgorithms.hpp"
#include "RandomNumberGenerator.hpp"

namespace FACEMC{

// Constructor
template<unsigned N>
PowerDistribution<N>::PowerDistribution( const double constant_multiplier,
					 const double min_indep_limit,
					 const double max_indep_limit )
  : d_constant_multiplier( constant_multiplier ),
    d_min_indep_limit( min_indep_limit ),
    d_min_indep_limit_to_power_Np1( min_indep_limit ),
    d_max_indep_limit( max_indep_limit ),
    d_max_indep_limit_to_power_Np1( max_indep_limit )
{
  // Make sure the exponent is valid
  testStaticPrecondition( N > 0 );
  // Make sure that the values are valid
  testPrecondition( !ST::isnaninf( constant_multiplier ) );
  testPrecondition( !ST::isnaninf( min_indep_limit ) );
  testPrecondition( !ST::isnaninf( max_indep_limit ) );
  // Make sure that the min value is greater than or equal to zero
  testPrecondition( min_indep_limit >= 0.0 );
  // Make sure that the max value is greater than the min value
  testPrecondition( max_indep_limit > min_indep_limit );

  // Take the limits to the power N
  d_min_indep_limit_to_power_Np1 = 
    Exponentiation::recursive( d_min_indep_limit, N+1u );
  
  d_max_indep_limit_to_power_Np1 = 
    Exponentiation::recursive( d_max_indep_limit, N+1u );
}

// Evaluate the distribution
template<unsigned N>
double PowerDistribution<N>::evaluate( const double indep_var_value ) const
{
  if( indep_var_value < d_min_indep_limit )
    return 0.0;
  else if( indep_var_value > d_max_indep_limit )
    return 0.0;
  else
    return d_constant_multiplier*Exponentiation::recursive(indep_var_value, N);
}

// Evaluate the PDF
template<unsigned N>
double PowerDistribution<N>::evaluatePDF( const double indep_var_value ) const
{
  if( indep_var_value < d_min_indep_limit )
    return 0.0;
  else if( indep_var_value > d_max_indep_limit )
    return 0.0;
  else
  {
    return (N+1u)*Exponentiation::recursive( indep_var_value, N )/
      (d_max_indep_limit_to_power_Np1 - d_min_indep_limit_to_power_Np1 );
  }
}

// Return a random sample from the distribution
template<unsigned N>
double PowerDistribution<N>::sample()
{
  return (const_cast<const PowerDistribution<N>*>(this))->sample();
}

// Return a random sample from the distribution
template<unsigned N>
double PowerDistribution<N>::sample() const
{
  double random_number = RandomNumberGenerator::getRandomNumber<double>();
  
  double argument = random_number*
    (d_max_indep_limit_to_power_Np1 - d_min_indep_limit_to_power_Np1 ) +
    d_min_indep_limit_to_power_Np1;
  
  return pow( argument, 1.0/(N+1u) );
}

// Return the sampling efficiency from the distribution
template<unsigned N>
double PowerDistribution<N>::getSamplingEfficiency() const
{
  return 1.0;
}

// Return the upper bound of the distribution independent variable
template<unsigned N>
double PowerDistribution<N>::getUpperBoundOfIndepVar() const
{
  return d_max_indep_limit;
}

// Return the lower bound of the distribution independent variable
template<unsigned N>
double PowerDistribution<N>::getLowerBoundOfIndepVar() const 
{
  return d_min_indep_limit;
}

// Return the distribution type
template<unsigned N>
OneDDistributionType PowerDistribution<N>::getDistributionType() const
{
  return PowerDistribution<N>::distribution_type;
}

} // end FACEMC namespace

//---------------------------------------------------------------------------//
// end PowerDistribution_def.hpp
//---------------------------------------------------------------------------//
