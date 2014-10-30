//---------------------------------------------------------------------------//
//!
//! \file   Utility_NormalDistribution.cpp
//! \author Alex Robinson
//! \brief  Normal distribution class declaration.
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "Utility_NormalDistribution.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_ContractException.hpp"

namespace Utility{

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
    d_trials( 0u ),
    d_samples( 0u )
{
  // Make sure that the values are valid
  testPrecondition( !ST::isnaninf( mean ) );
  testPrecondition( !ST::isnaninf( standard_deviation ) );
  // Make sure that the standard deviation is positive
  testPrecondition( standard_deviation > 0.0 );
  // Make sure that the min indep value is < the max indep value
  testPrecondition( min_independent_value < max_independent_value );
}

// Copy constructor
NormalDistribution::NormalDistribution( 
				      const NormalDistribution& dist_instance )
  : d_mean( dist_instance.d_mean ),
    d_standard_deviation( dist_instance.d_standard_deviation ),
    d_min_independent_value( dist_instance.d_min_independent_value ),
    d_max_independent_value( dist_instance.d_max_independent_value ),
    d_trials( dist_instance.d_trials ),
    d_samples( dist_instance.d_samples )
{
  // Make sure that the values are valid
  testPrecondition( !ST::isnaninf( dist_instance.d_mean ) );
  testPrecondition( !ST::isnaninf( dist_instance.d_standard_deviation ) );
  // Make sure that the standard deviation is positive
  testPrecondition( dist_instance.d_standard_deviation > 0.0 );
}

// Assignment operator
NormalDistribution& NormalDistribution::operator=(
				      const NormalDistribution& dist_instance )
{
  if( this != &dist_instance )
  {
    d_mean = dist_instance.d_mean;
    d_standard_deviation = dist_instance.d_standard_deviation;
    d_min_independent_value = dist_instance.d_min_independent_value;
    d_max_independent_value = dist_instance.d_max_independent_value;
    d_trials = dist_instance.d_trials;
    d_samples = dist_instance.d_samples;
  }

  return *this;
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
  
    return NormalDistribution::constant_multiplier*exp( argument )/
      d_standard_deviation;
  }
}

// Return a sample from the distribution
double NormalDistribution::sample()
{
  unsigned number_of_trials;

  double normal_sample = sample( number_of_trials );

  // Update the efficiency counters
  d_trials += number_of_trials;
  ++d_samples;

  return normal_sample;
}

// Return a random sample from the distribution
double NormalDistribution::sample() const
{
  unsigned number_of_trials;

  return sample( number_of_trials );
}

// Sample a value from the distribution, count the number of trials
double NormalDistribution::sample( unsigned& number_of_trials ) const
{
  double random_number_1, random_number_2;
  double x, y, sample;
  
  // Set the number of trials to zero
  number_of_trials = 0u;
  
  while( true )
  {
    // Use the rejection sampling technique outlined by Kahn in "Applications 
    // of Monte Carlo" (1954)
    while( true )
    {
      random_number_1 = RandomNumberGenerator::getRandomNumber<double>();
      random_number_2 = RandomNumberGenerator::getRandomNumber<double>();
      
      x = -log( random_number_1 );
      y = -log( random_number_2 );
      
      if( 0.5*(x - 1)*(x - 1) <= y )
      {
	++number_of_trials;
	break;
      }
      else
	++number_of_trials;
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
/*! \details The sampling efficiency will only be correct if the non-const 
 * sample member function is called exclusively.
 */ 
double NormalDistribution::getSamplingEfficiency() const
{
  if( d_trials > 0u )
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

// Method for placing the object in an output stream
void NormalDistribution::toStream( std::ostream& os ) const
{
  os << "{" << d_mean << "," << d_standard_deviation << ","
     << d_min_independent_value << "," << d_max_independent_value << "}";
}

// Method for initializing the object from an input stream
void NormalDistribution::fromStream( std::istream& is )
{
  // Read in the distribution representation
  std::string dist_rep;
  std::getline( is, dist_rep, '}' );
  dist_rep += '}';

  Teuchos::Array<std::string> distribution;
  try{
    distribution = Teuchos::fromStringToArray<std::string>( dist_rep );
  }
  catch( Teuchos::InvalidArrayStringRepresentation& error )
  {
    std::string message( "Error: the normal distribution cannot be "
			 "constructed because the representation is not valid "
			 "(see details below)!\n" );
    message += error.what();

    throw InvalidDistributionStringRepresentation( message );
  }

  TEST_FOR_EXCEPTION( distribution.size() < 2 || distribution.size() > 4,
		      InvalidDistributionStringRepresentation,
		      "Error: the normal distribution cannot be constructed "
		      "because the representation is not valid "
		      "(only 2, 3, or 4 values may be specified)!" );

  // Set the mean
  TEST_FOR_EXCEPTION( distribution[0].find_first_not_of( " -0123456789.e" ) <
		      distribution[0].size(),
		      InvalidDistributionStringRepresentation,
		      "Error: the normal distribution cannot be "
		      "constructed because of an invalid mean "
		      << distribution[0] );
  {
    std::istringstream iss( distribution[0] );
    Teuchos::extractDataFromISS( iss, d_mean );
  }
  
  TEST_FOR_EXCEPTION( ST::isnaninf( d_mean ),
		      InvalidDistributionStringRepresentation,
		      "Error: the normal distribution cannot be constructed "
		      "because of an invalid mean " << d_mean );
  
  // Set the standard deviation
  TEST_FOR_EXCEPTION( distribution[1].find_first_not_of( " 0123456789.e" ) <
		      distribution[1].size(),
		      InvalidDistributionStringRepresentation,
		      "Error: the normal distribution cannot be "
		      "constructed because of an invalid standard deviation "
		      << distribution[1] );
  {
    std::istringstream iss( distribution[1] );
    Teuchos::extractDataFromISS( iss, d_standard_deviation );
  }

  TEST_FOR_EXCEPTION( ST::isnaninf( d_standard_deviation ),
		      InvalidDistributionStringRepresentation,
		      "Error: the normal distribution cannot be constructed "
		      "because of an invalid standard deviation "
		      << d_standard_deviation );

  TEST_FOR_EXCEPTION( d_standard_deviation < 0.0,
		      InvalidDistributionStringRepresentation,
		      "Error: the normal distribution cannot be constructed "
		      "because of an invalid standard deviation "
		      << d_standard_deviation );

  // Set the min independent value
  if( distribution.size() > 2 )
  {
    if( distribution[2].compare( "-inf" ) == 0 )
      d_min_independent_value = -std::numeric_limits<double>::infinity();
    else
    {
      TEST_FOR_EXCEPTION( distribution[2].find_first_not_of( " -0123456789.e")<
			  distribution[2].size(),
			  InvalidDistributionStringRepresentation,
			  "Error: the normal distribution cannot be "
			  "constructed because of an invalid min independent "
			  " value " << distribution[2] );
      std::istringstream entry_iss( distribution[2] );
      
      Teuchos::extractDataFromISS( entry_iss, d_min_independent_value );
    }
  }
  else
    d_min_independent_value = -std::numeric_limits<double>::infinity();

  // Set the max independent value
  if( distribution.size() > 3 )
  {
    if( distribution[3].compare( "inf" ) == 0 )
      d_max_independent_value = std::numeric_limits<double>::infinity();
    else
    {
      TEST_FOR_EXCEPTION( distribution[3].find_first_not_of( " -0123456789.e")<
			  distribution[3].size(),
			  InvalidDistributionStringRepresentation,
			  "Error: the normal distribution cannot be "
			  "constructed because of an invalid max independent "
			  " value " << distribution[3] );
      std::istringstream entry_iss( distribution[3] );
      
      Teuchos::extractDataFromISS( entry_iss, d_max_independent_value );
    }
  }
  else
    d_max_independent_value = std::numeric_limits<double>::infinity();

  TEST_FOR_EXCEPTION( d_max_independent_value <= d_min_independent_value,
		      InvalidDistributionStringRepresentation,
		      "Error: the normal distribution cannot be "
		      "constructed because the max independent value is not "
		      "greater than the min independent value!" );
}

// Method for testing if two objects are equivalent
bool NormalDistribution::isEqual( const NormalDistribution& other ) const
{
  return d_mean == other.d_mean && 
    d_standard_deviation == other.d_standard_deviation &&
    d_min_independent_value == other.d_min_independent_value &&
    d_max_independent_value == other.d_max_independent_value;
}

} // end Utility namespace

//---------------------------------------------------------------------------//
// end Utility_NormalDistribution.cpp
//---------------------------------------------------------------------------//
