//---------------------------------------------------------------------------//
//!
//! \file   Utility_PowerDistribution_def.hpp
//! \author Alex Robinson
//! \brief  Power distribution class definition (N>2).
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "Utility_ContractException.hpp"
#include "Utility_ExponentiationAlgorithms.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_ArrayString.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_ExceptionCatchMacros.hpp"

namespace Utility{

// Default constructor
template<unsigned N>
PowerDistribution<N>::PowerDistribution()
{ 
  // Make sure the exponent is valid
  testStaticPrecondition( N > 0 );
}

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

  initializeDistribution();
}

// Copy constructor
template<unsigned N>
PowerDistribution<N>::PowerDistribution( 
				    const PowerDistribution<N>& dist_instance )
  : d_constant_multiplier( dist_instance.d_constant_multiplier ),
    d_min_indep_limit( dist_instance.d_min_indep_limit ),
    d_min_indep_limit_to_power_Np1( 
				dist_instance.d_min_indep_limit_to_power_Np1 ),
    d_max_indep_limit( dist_instance.d_max_indep_limit ),
    d_max_indep_limit_to_power_Np1( 
				 dist_instance.d_max_indep_limit_to_power_Np1 )
{
  // Make sure the exponent is valid
  testStaticPrecondition( N > 0 );
  // Make sure that the values are valid
  testPrecondition( !ST::isnaninf( dist_instance.d_constant_multiplier ) );
  testPrecondition( !ST::isnaninf( dist_instance.d_min_indep_limit ) );
  testPrecondition( !ST::isnaninf( dist_instance.d_max_indep_limit ) );
  testPrecondition( !ST::isnaninf( 
			      dist_instance.d_min_indep_limit_to_power_Np1 ) );
  testPrecondition( !ST::isnaninf( 
			      dist_instance.d_max_indep_limit_to_power_Np1 ) );
  // Make sure that the min value is greater than or equal to zero
  testPrecondition( dist_instance.d_min_indep_limit >= 0.0 );
  // Make sure that the max value is greater than the min value
  testPrecondition( dist_instance.d_max_indep_limit > 
		    dist_instance.d_min_indep_limit );
}

// Assignment operator
template<unsigned N>
PowerDistribution<N>& PowerDistribution<N>::operator=( 
				    const PowerDistribution<N>& dist_instance )
{
  // Make sure the distribution is valid
  testPrecondition( dist_instance.d_min_indep_limit >= 0.0 );
  testPrecondition( dist_instance.d_max_indep_limit > 
		    dist_instance.d_min_indep_limit );
  
  if( this != &dist_instance )
  {
    d_constant_multiplier = dist_instance.d_constant_multiplier;
    d_min_indep_limit = dist_instance.d_min_indep_limit;
    d_min_indep_limit_to_power_Np1 = 
      dist_instance.d_min_indep_limit_to_power_Np1;
    d_max_indep_limit = dist_instance.d_max_indep_limit;
    d_max_indep_limit_to_power_Np1 = 
      dist_instance.d_max_indep_limit_to_power_Np1;
  }
  
  return *this;
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

// Method for placing the object in an output stream
template<unsigned N>
void PowerDistribution<N>::toStream( std::ostream& os ) const
{
  os << "{" << d_constant_multiplier 
     << "," << d_min_indep_limit
     << "," << d_max_indep_limit
     << "}";
}

// Method for initializing the object from an input stream
template<unsigned N>
void PowerDistribution<N>::fromStream( std::istream& is )
{
  // Read in the distribution representation
  std::string dist_rep;
  std::getline( is, dist_rep, '}' );
  dist_rep += '}';

  // Parse special characters
  try{
    ArrayString::locateAndReplacePi( dist_rep );
  }
  EXCEPTION_CATCH_RETHROW_AS( std::runtime_error,
			      InvalidDistributionStringRepresentation,
			      "Error: the power " << N << " distribution "
			      "cannot be constructed because the "
			      "representation is not valid (see details "
			      "below)!\n" );

  Teuchos::Array<double> distribution;
  try{
    distribution = Teuchos::fromStringToArray<double>( dist_rep );
  }
  EXCEPTION_CATCH_RETHROW_AS( Teuchos::InvalidArrayStringRepresentation,
			      InvalidDistributionStringRepresentation,
			      "Error: the power " << N << " distribution "
			      "cannot be constructed because the "
			      "representation is not valid (see details "
			      "below)!\n" );
  
  TEST_FOR_EXCEPTION( distribution.size() < 2 || distribution.size() > 3,
		      InvalidDistributionStringRepresentation,
		      "Error: the power " << N << " distribution cannot be "
		      "constructed because the representation is not valid "
		      "(only 3 values may be specified)!" );

  // Set the constant multiplier
  if( distribution.size() == 3 )
    d_constant_multiplier = distribution[0];
  else
    d_constant_multiplier = 1.0;
  
  TEST_FOR_EXCEPTION( ST::isnaninf( d_constant_multiplier ),
		      InvalidDistributionStringRepresentation,
		      "Error: the power " << N << " distribution cannot be "
		      "constructed because the constant multiplier is not "
		      "valid!" );
  
  // Read the min independent limit
  if( distribution.size() == 3 )
    d_min_indep_limit = distribution[1];
  else
    d_min_indep_limit = distribution[0];

  TEST_FOR_EXCEPTION( ST::isnaninf( d_min_indep_limit ),
		      InvalidDistributionStringRepresentation,
		      "Error: the power " << N << " distribution cannot be "
		      "constructed because the min independent limit is not "
		      "valid!" );

  TEST_FOR_EXCEPTION( d_min_indep_limit < 0,
		      InvalidDistributionStringRepresentation,
		      "Error: the power " << N << " distribution cannot be "
		      "constructed because the min independent limit is not "
		      "valid!" );

  // Read the max independent limit
  if( distribution.size() == 3 )
    d_max_indep_limit = distribution[2];
  else
    d_max_indep_limit = distribution[1];

  TEST_FOR_EXCEPTION( ST::isnaninf( d_max_indep_limit ),
		      InvalidDistributionStringRepresentation,
		      "Error: the power " << N << " distribution cannot be "
		      "constructed because the max independent limit is not "
		      "valid!" );

  TEST_FOR_EXCEPTION( d_max_indep_limit <= d_min_indep_limit,
		      InvalidDistributionStringRepresentation,
		      "Error: the power " << N << " distribution cannot be "
		      "constructed because the max independent limit is not "
		      "valid!" );

  initializeDistribution();	      
}

// Method for testing if two objects are equivalent
template<unsigned N>
bool PowerDistribution<N>::isEqual( const PowerDistribution<N>& other ) const
{
  return d_constant_multiplier == other.d_constant_multiplier &&
    d_min_indep_limit == other.d_min_indep_limit &&
    d_min_indep_limit_to_power_Np1 == other.d_min_indep_limit_to_power_Np1 &&
    d_max_indep_limit == other.d_max_indep_limit &&
    d_max_indep_limit_to_power_Np1 == other.d_max_indep_limit_to_power_Np1;
}

// Initialize the distribution
template<unsigned N>
void PowerDistribution<N>::initializeDistribution()
{
  // Take the limits to the power N
  d_min_indep_limit_to_power_Np1 = 
    Exponentiation::recursive( d_min_indep_limit, N+1u );
  
  d_max_indep_limit_to_power_Np1 = 
    Exponentiation::recursive( d_max_indep_limit, N+1u );
}

} // end Utility namespace

//---------------------------------------------------------------------------//
// end Utility_PowerDistribution_def.hpp
//---------------------------------------------------------------------------//
