//---------------------------------------------------------------------------//
//! 
//! \file   Utility_PowerDistribution.cpp
//! \author Alex Robinson
//! \brief  Power distribution class definition (N=1,N=2)
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "Utility_PowerDistribution.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_ArrayString.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_ExceptionCatchMacros.hpp"
#include "Utility_ContractException.hpp"

namespace Utility{

// Default constructor
PowerDistribution<2u>::PowerDistribution()
{ /* ... */ }

// Default constructor
PowerDistribution<1u>::PowerDistribution()
{ /* ... */ }

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

// Copy constructor
PowerDistribution<2u>::PowerDistribution( 
				   const PowerDistribution<2u>& dist_instance )
  : d_constant_multiplier( dist_instance.d_constant_multiplier ),
    d_min_indep_limit( dist_instance.d_min_indep_limit ),
    d_min_indep_limit_cubed( dist_instance.d_min_indep_limit_cubed ),
    d_max_indep_limit( dist_instance.d_max_indep_limit ),
    d_max_indep_limit_cubed( dist_instance.d_max_indep_limit_cubed )
{
  // Make sure that the values are valid
  testPrecondition( !ST::isnaninf( dist_instance.d_constant_multiplier ) );
  testPrecondition( !ST::isnaninf( dist_instance.d_min_indep_limit ) );
  testPrecondition( !ST::isnaninf( dist_instance.d_max_indep_limit ) );
  // Make sure that the min value is greater than or equal to zero
  testPrecondition( dist_instance.d_min_indep_limit >= 0.0 );
  // Make sure that the max value is greater than the min value
  testPrecondition( dist_instance.d_max_indep_limit > 
		    dist_instance.d_min_indep_limit ); 
}

// Copy constructor
PowerDistribution<1u>::PowerDistribution(
				   const PowerDistribution<1u>& dist_instance )
  : d_constant_multiplier( dist_instance.d_constant_multiplier ),
    d_min_indep_limit( dist_instance.d_min_indep_limit ),
    d_min_indep_limit_squared( dist_instance.d_min_indep_limit_squared ),
    d_max_indep_limit( dist_instance.d_max_indep_limit ),
    d_max_indep_limit_squared( dist_instance.d_max_indep_limit_squared )
{
  // Make sure that the values are valid
  testPrecondition( !ST::isnaninf( dist_instance.d_constant_multiplier ) );
  testPrecondition( !ST::isnaninf( dist_instance.d_min_indep_limit ) );
  testPrecondition( !ST::isnaninf( dist_instance.d_max_indep_limit ) );
  // Make sure that the min value is greater than or equal to zero
  testPrecondition( dist_instance.d_min_indep_limit >= 0.0 );
  // Make sure that the max value is greater than the min value
  testPrecondition( dist_instance.d_max_indep_limit > 
		    dist_instance.d_min_indep_limit ); 
}

// Assignment operator
PowerDistribution<2u>& PowerDistribution<2u>::operator=(
				   const PowerDistribution<2u>& dist_instance )
{
  // Make sure the distribution is valid
  testPrecondition( dist_instance.d_min_indep_limit >= 0.0 );
  testPrecondition( dist_instance.d_max_indep_limit > 
		    dist_instance.d_min_indep_limit );

  if( this != &dist_instance )
  {
    d_constant_multiplier = dist_instance.d_constant_multiplier;
    d_min_indep_limit = dist_instance.d_min_indep_limit;
    d_min_indep_limit_cubed = dist_instance.d_min_indep_limit_cubed;
    d_max_indep_limit = dist_instance.d_max_indep_limit;
    d_max_indep_limit_cubed = dist_instance.d_max_indep_limit_cubed;
  }

  return *this;
}

// Assignment operator
PowerDistribution<1u>& PowerDistribution<1u>::operator=(
				   const PowerDistribution<1u>& dist_instance )
{
  // Make sure the distribution is valid
  testPrecondition( dist_instance.d_min_indep_limit >= 0.0 );
  testPrecondition( dist_instance.d_max_indep_limit > 
		    dist_instance.d_min_indep_limit );

  if( this != &dist_instance )
  {
    d_constant_multiplier = dist_instance.d_constant_multiplier;
    d_min_indep_limit = dist_instance.d_min_indep_limit;
    d_min_indep_limit_squared = dist_instance.d_min_indep_limit_squared;
    d_max_indep_limit = dist_instance.d_max_indep_limit;
    d_max_indep_limit_squared = dist_instance.d_max_indep_limit_squared;
  }

  return *this;
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

// Return a random sample and record the number of trials
double PowerDistribution<2u>::sampleAndRecordTrials( unsigned& trials ) const
{
  ++trials;

  return this->sample();
}

// Return a random sample and record the number of trials
double PowerDistribution<1u>::sampleAndRecordTrials( unsigned& trials ) const
{
  ++trials;
  
  return this->sample();
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

//! Test if the distribution is continuous
bool PowerDistribution<2u>::isContinuous() const
{
  return true;
}

//! Test if the distribution is continuous
bool PowerDistribution<1u>::isContinuous() const
{
  return true;
}

// Method for placing the object in an output stream
void PowerDistribution<2u>::toStream( std::ostream& os ) const
{
  os << "{" << d_constant_multiplier 
     << "," << d_min_indep_limit
     << "," << d_max_indep_limit
     << "}";
}

// Method for placing the object in an output stream
void PowerDistribution<1u>::toStream( std::ostream& os ) const
{
  os << "{" << d_constant_multiplier 
     << "," << d_min_indep_limit
     << "," << d_max_indep_limit
     << "}";
}

// Method for initializing the object from an input stream
void PowerDistribution<2u>::fromStream( std::istream& is )
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
			      "Error: the power 2 distribution cannot be "
			      "constructed because the representation is not "
			      "valid (see details below)!\n" );

  Teuchos::Array<double> distribution;
  try{
    distribution = Teuchos::fromStringToArray<double>( dist_rep );
  }
  EXCEPTION_CATCH_RETHROW_AS( Teuchos::InvalidArrayStringRepresentation,
			      InvalidDistributionStringRepresentation,
			      "Error: the power 2 distribution cannot be "
			      "constructed because the representation is not "
			      "valid (see details below)!\n" );
  
  TEST_FOR_EXCEPTION( distribution.size() < 2 || distribution.size() > 3,
		      InvalidDistributionStringRepresentation,
		      "Error: the power 2 distribution cannot be constructed "
		      "because the representation is not valid "
		      "(either 2 or 3 values may be specified)!" );

  // Set the constant multiplier
  if( distribution.size() == 3 )
    d_constant_multiplier = distribution[0];
  else
    d_constant_multiplier = 1.0;
  
  TEST_FOR_EXCEPTION( ST::isnaninf( d_constant_multiplier ),
		      InvalidDistributionStringRepresentation,
		      "Error: the power 2 distribution cannot be "
		      "constructed because the constant multiplier is not "
		      "valid!" );
  
  // Set the min independent limit
  if( distribution.size() == 3 )
    d_min_indep_limit = distribution[1];
  else
    d_min_indep_limit = distribution[0];
  
  TEST_FOR_EXCEPTION( ST::isnaninf( d_min_indep_limit ),
		      InvalidDistributionStringRepresentation,
		      "Error: the power 2 distribution cannot be "
		      "constructed because the min independent limit is not "
		      "valid!" );

  TEST_FOR_EXCEPTION( d_min_indep_limit < 0,
		      InvalidDistributionStringRepresentation,
		      "Error: the power 2 distribution cannot be "
		      "constructed because the min independent limit is not "
		      "valid!" );

  d_min_indep_limit_cubed = 
    d_min_indep_limit*d_min_indep_limit*d_min_indep_limit;

  // Set the max independent limit
  if( distribution.size() == 3 )
    d_max_indep_limit = distribution[2];
  else
    d_max_indep_limit = distribution[1];

  TEST_FOR_EXCEPTION( ST::isnaninf( d_max_indep_limit ),
		      InvalidDistributionStringRepresentation,
		      "Error: the power 2 distribution cannot be "
		      "constructed because the max independent limit is not "
		      "valid!" );

  TEST_FOR_EXCEPTION( d_max_indep_limit <= d_min_indep_limit,
		      InvalidDistributionStringRepresentation,
		      "Error: the power 2 distribution cannot be "
		      "constructed because the max independent limit is not "
		      "valid!" );

  d_max_indep_limit_cubed = 
    d_max_indep_limit*d_max_indep_limit*d_max_indep_limit;
}

// Method for initializing the object from an input stream
void PowerDistribution<1u>::fromStream( std::istream& is )
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
			      "Error: the power 1 distribution cannot be "
			      "constructed because the representation is not "
			      "valid (see details below)!\n" );

  Teuchos::Array<double> distribution;
  try{
    distribution = Teuchos::fromStringToArray<double>( dist_rep );
  }
  EXCEPTION_CATCH_RETHROW_AS( Teuchos::InvalidArrayStringRepresentation,
			      InvalidDistributionStringRepresentation,
			      "Error: the power 1 distribution cannot be "
			      "constructed because the representation is not "
			      "valid (see details below)!\n" );
  
  TEST_FOR_EXCEPTION( distribution.size() < 2 || distribution.size() > 3,
		      InvalidDistributionStringRepresentation,
		      "Error: the power 1 distribution cannot be constructed "
		      "because the representation is not valid "
		      "(either 2 or 3 values may be specified)!" );

  // Set the constant multiplier
  if( distribution.size() == 3 )
    d_constant_multiplier = distribution[0];
  else
    d_constant_multiplier = 1.0;
  
  TEST_FOR_EXCEPTION( ST::isnaninf( d_constant_multiplier ),
		      InvalidDistributionStringRepresentation,
		      "Error: the power 1 distribution cannot be "
		      "constructed because the constant multiplier is not "
		      "valid!" );
  
  // Read the min independent limit
  if( distribution.size() == 3 )
    d_min_indep_limit = distribution[1];
  else
    d_min_indep_limit = distribution[0];

  TEST_FOR_EXCEPTION( ST::isnaninf( d_min_indep_limit ),
		      InvalidDistributionStringRepresentation,
		      "Error: the power 1 distribution cannot be "
		      "constructed because the min independent limit is not "
		      "valid!" );

  TEST_FOR_EXCEPTION( d_min_indep_limit < 0,
		      InvalidDistributionStringRepresentation,
		      "Error: the power 1 distribution cannot be "
		      "constructed because the min independent limit is not "
		      "valid!" );

  d_min_indep_limit_squared = d_min_indep_limit*d_min_indep_limit;

  // Read the max independent limit
  if( distribution.size() == 3 )
    d_max_indep_limit = distribution[2];
  else
    d_max_indep_limit = distribution[1];
  
  TEST_FOR_EXCEPTION( ST::isnaninf( d_max_indep_limit ),
		      InvalidDistributionStringRepresentation,
		      "Error: the power 1 distribution cannot be "
		      "constructed because the max independent limit is not "
		      "valid!" );

  TEST_FOR_EXCEPTION( d_max_indep_limit <= d_min_indep_limit,
		      InvalidDistributionStringRepresentation,
		      "Error: the power 1 distribution cannot be "
		      "constructed because the max independent limit is not "
		      "valid!" );

  d_max_indep_limit_squared = d_max_indep_limit*d_max_indep_limit;
}

// Method for testing if two objects are equivalent
bool PowerDistribution<2u>::isEqual( const PowerDistribution<2u>& other ) const
{
  return d_constant_multiplier == other.d_constant_multiplier &&
    d_min_indep_limit == other.d_min_indep_limit &&
    d_min_indep_limit_cubed == other.d_min_indep_limit_cubed &&
    d_max_indep_limit == other.d_max_indep_limit &&
    d_max_indep_limit_cubed == other.d_max_indep_limit_cubed;
}

// Method for testing if two objects are equivalent
bool PowerDistribution<1u>::isEqual( const PowerDistribution<1u>& other ) const
{
  return d_constant_multiplier == other.d_constant_multiplier &&
    d_min_indep_limit == other.d_min_indep_limit &&
    d_min_indep_limit_squared == other.d_min_indep_limit_squared &&
    d_max_indep_limit == other.d_max_indep_limit &&
    d_max_indep_limit_squared == other.d_max_indep_limit_squared;
}

} // end Utility namespace

//---------------------------------------------------------------------------//
// end Utility_PowerDistribution.cpp
//---------------------------------------------------------------------------//
