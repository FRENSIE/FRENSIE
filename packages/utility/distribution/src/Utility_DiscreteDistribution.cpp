//---------------------------------------------------------------------------//
//!
//! \file   Utility_DiscreteDistribution.cpp
//! \author Alex Robinson
//! \brief  Discrete distribution class definition.
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <stdexcept>

// FRENSIE Includes
#include "Utility_DiscreteDistribution.hpp"
#include "Utility_DataProcessor.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_ExceptionTestMacros.hpp"

namespace Utility{

// Default Constructor
DiscreteDistribution::DiscreteDistribution()
{ /* ... */ }

// Constructor
DiscreteDistribution::DiscreteDistribution( 
			      const Teuchos::Array<double>& independent_values,
			      const Teuchos::Array<double>& dependent_values )
  : d_distribution( independent_values.size() )
{
  initializeDistribution( independent_values, dependent_values );
}

// Copy constructor
DiscreteDistribution::DiscreteDistribution( 
			    const DiscreteDistribution& dist_instance )
  : d_distribution( dist_instance.d_distribution ),
    d_norm_constant( dist_instance.d_norm_constant )
{
  // Make sure that the distribution is valid
  testPrecondition( d_distribution.size() > 0 );
}

// Assignment operator
DiscreteDistribution& DiscreteDistribution::operator=( 
				    const DiscreteDistribution& dist_instance )
{
  // Make sure that the distribution is valid
  testPrecondition( dist_instance.d_distribution.size() > 0 );
  
  if( this != &dist_instance )
  {
    d_distribution = dist_instance.d_distribution;
    d_norm_constant = dist_instance.d_norm_constant;
  }

  return *this;
}

// Evaluate the distribution
/*! \details The discrete distribution can be expressed as a sum of delta
 * functions. Therefore, the discrete distribution can only take on two
 * values: 0.0 and infinity.
 */
double DiscreteDistribution::evaluate( const double indep_var_value ) const 
{
  for( unsigned i = 0; i < d_distribution.size(); ++i )
  {
    if( indep_var_value == d_distribution[i].first )
      return std::numeric_limits<double>::infinity();
  }

  return 0.0;
}

// Evaluate the PDF
double DiscreteDistribution::evaluatePDF( const double indep_var_value ) const
{
  for( unsigned i = 0; i < d_distribution.size(); ++i )
  {
    if( indep_var_value == d_distribution[i].first )
    {
      if( i == 0 )
	return d_distribution[i].second;
      else
	return d_distribution[i].second - d_distribution[i-1].second;
    }
  }
  
  return 0.0;
}

// Return a random sample from the distribution
double DiscreteDistribution::sample()
{
  return (const_cast<const DiscreteDistribution*>(this))->sample();
}

// Return a random sample from the distribution
double DiscreteDistribution::sample() const
{
  double random_number = RandomNumberGenerator::getRandomNumber<double>();
  
  Teuchos::Array<Pair<double,double> >::const_iterator sample = 
    Search::binaryUpperBound<SECOND>( d_distribution.begin(),
				      d_distribution.end(),
				      random_number );

  return sample->first;
}

// Return the sampling efficiency from the distribution
double DiscreteDistribution::getSamplingEfficiency() const
{
  return 1.0;
}

// Return the upper bound of the distribution independent variable
double DiscreteDistribution::getUpperBoundOfIndepVar() const
{
  double max_value = -std::numeric_limits<double>::infinity();
  
  // Find the max value
  for( unsigned i = 0; i < d_distribution.size(); ++i )
  {
    if( d_distribution[i].first > max_value )
      max_value = d_distribution[i].first;
  }
      
  return max_value;
}

// Return the lower bound of the independent variable
double DiscreteDistribution::getLowerBoundOfIndepVar() const
{
  double min_value = std::numeric_limits<double>::infinity();

  // Find the min value
  for( unsigned i = 0; i < d_distribution.size(); ++i )
  {
    if( d_distribution[i].first < min_value )
      min_value = d_distribution[i].first;
  }
  
  return min_value;
}

// Return the distribution type
OneDDistributionType DiscreteDistribution::getDistributionType() const
{
  return DiscreteDistribution::distribution_type;
}

// Method for placing the object in an output stream
void DiscreteDistribution::toStream( std::ostream& os ) const
{
  Teuchos::Array<double> independent_values( d_distribution.size() );
  Teuchos::Array<double> dependent_values( d_distribution.size() );

  independent_values[0] = d_distribution[0].first;
  dependent_values[0] = d_distribution[0].second*d_norm_constant;

  for( unsigned i = 1u; i < d_distribution.size(); ++i )
  {
    independent_values[i] = d_distribution[i].first;
    dependent_values[i] = 
      (d_distribution[i].second-d_distribution[i-1].second)*d_norm_constant;
  }

  os << "{" << independent_values << "," << dependent_values << "}";
}

// Method for initializing the object from an input stream
void DiscreteDistribution::fromStream( std::istream& is )
{
  // Read the initial '{'
  std::string start_bracket;
  std::getline( is, start_bracket, '{' );
  start_bracket = Teuchos::Utils::trimWhiteSpace( start_bracket );
  
  TEST_FOR_EXCEPTION( start_bracket.size() != 0, 
		      InvalidDistributionStringRepresentation, 
		      "Error: the input stream is not a valid discrete "
		      "distribution representation!" );

  std::string independent_values_rep;
  std::getline( is, independent_values_rep, '}' );
  independent_values_rep += "}";
  
  Teuchos::Array<double> independent_values;
  try{
    independent_values = 
      Teuchos::fromStringToArray<double>( independent_values_rep );
  }
  catch( Teuchos::InvalidArrayStringRepresentation& error )
  {
    std::string message( "Error: the discrete distribution cannot be "
			 "constructed because the independent values are "
			 "not valid (see details below)!\n" );
    message += error.what();
    
    throw InvalidDistributionStringRepresentation( message );
  }
  
  // Read the ","
  std::string separator;
  std::getline( is, separator, ',' );
  
  std::string dependent_values_rep;
  std::getline( is, dependent_values_rep, '}' );
  dependent_values_rep += "}";
  
  Teuchos::Array<double> dependent_values;
  try{
    dependent_values = 
      Teuchos::fromStringToArray<double>( dependent_values_rep );
  }
  catch( Teuchos::InvalidArrayStringRepresentation& error )
  {
    std::string message( "Error: the discrete distribution cannot be "
			 "constructed because the dependent values are "
			 "not valid (see details below)!\n" );
    message += error.what();
    
    throw InvalidDistributionStringRepresentation( message );
  }

  TEST_FOR_EXCEPTION( independent_values.size() != dependent_values.size(),
		      InvalidDistributionStringRepresentation, 
		      "Error: the discrete distribution "
		      "{" << independent_values_rep << "},{"
		      << dependent_values_rep << "} "
		      "cannot be constructed because the number of "
		      "independent values does not match the number of "
		      " dependent values!" );
  
  initializeDistribution( independent_values, dependent_values );
}

// Method for testing if two objects are equivalent
bool DiscreteDistribution::isEqual( const DiscreteDistribution& other ) const
{
  return d_distribution == other.d_distribution && 
    d_norm_constant == other.d_norm_constant;
}

// Initialize the distribution
void DiscreteDistribution::initializeDistribution( 
			      const Teuchos::Array<double>& independent_values,
			      const Teuchos::Array<double>& dependent_values )
{
  // Make sure that every value has a probability assigned
  testPrecondition( independent_values.size() == dependent_values.size() );
  
  // resize the distribution array
  d_distribution.resize( independent_values.size() );
  
  // reset the normalization constant
  d_norm_constant = 0.0;
  
  // Assign the raw distribution data
  for( unsigned i = 0; i < independent_values.size(); ++i )
  {
    d_distribution[i].first = independent_values[i];

    d_distribution[i].second = dependent_values[i];

    d_norm_constant += dependent_values[i];
  }

  // Create a CDF from the raw distribution data
  DataProcessor::calculateDiscreteCDF<SECOND,SECOND>( d_distribution );
}

} // end Utility namespace

//---------------------------------------------------------------------------//
// end Utility_DiscreteDistribution.cpp
//---------------------------------------------------------------------------//
