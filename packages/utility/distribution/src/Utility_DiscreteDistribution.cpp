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
#include "Utility_ArrayString.hpp"
#include "Utility_SortAlgorithms.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_ExceptionCatchMacros.hpp"

namespace Utility{

// Default Constructor
DiscreteDistribution::DiscreteDistribution()
{ /* ... */ }

// Constructor 
/*! \details A precalculated CDF can be passed as the dependent values as
 * long as the interpret_dependent_values_as_cdf argument is true.
 */ 
DiscreteDistribution::DiscreteDistribution( 
			      const Teuchos::Array<double>& independent_values,
			      const Teuchos::Array<double>& dependent_values,
			      const bool interpret_dependent_values_as_cdf )
  : d_distribution( independent_values.size() ),
    d_norm_constant( 1.0 )
{
  if( interpret_dependent_values_as_cdf )
  {
    // Make sure that every value has a probability assigned
    testPrecondition( independent_values.size() == dependent_values.size() );
    // Make sure that the bins are sorted
    testPrecondition( Sort::isSortedAscending( independent_values.begin(),
					       independent_values.end() ) );
    // Make sure that the bin values are sorted
    testPrecondition( Sort::isSortedAscending( dependent_values.begin(), 
					       dependent_values.end() ) );
    
    // Assign the distribution
    for( unsigned i = 0; i < independent_values.size(); ++i )
    {
      d_distribution[i].first = independent_values[i];
      d_distribution[i].second = dependent_values[i];
    }
    
    // Verify that the CDF is normalized (in event of round-off errors)
    if( dependent_values.back() != 1.0 )
    {
      for( unsigned i = 0; i < d_distribution.size(); ++i )
	d_distribution[i].second /= d_distribution.back().second;
    }
  }
  else
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
  double value = this->evaluatePDF( indep_var_value );

  if( value != 0.0 )
    value = std::numeric_limits<double>::infinity();

  return value;
}

// Evaluate the PDF
double DiscreteDistribution::evaluatePDF( const double indep_var_value ) const
{
  double pdf = 0.0;

  if( indep_var_value >= d_distribution.front().first &&
      indep_var_value <= d_distribution.back().first )
  {
    Teuchos::Array<Pair<double,double> >::const_iterator bin = 
      Search::binaryLowerBound<FIRST>( d_distribution.begin(),
				       d_distribution.end(),
				       indep_var_value );

    Teuchos::Array<Pair<double,double> >::const_iterator prev_bin = bin;
    --prev_bin;
    
    // The same independent variable may appear multiple times
    while( bin->first == indep_var_value )
    {
      if( bin != d_distribution.begin() )
      {
	pdf += bin->second - prev_bin->second;
	
	--bin;
	--prev_bin;
      }
      else
      {
	pdf += bin->second;
	
	break;
      }
    }
  }
  else
    pdf = 0.0;
  
  return pdf;
}

// Evaluate the CDF
double DiscreteDistribution::evaluateCDF( const double indep_var_value ) const
{
  double cdf = 0.0;

  if( indep_var_value >= d_distribution.front().first &&
      indep_var_value <= d_distribution.back().first )
  {
    Teuchos::Array<Pair<double,double> >::const_iterator bin = 
      Search::binaryLowerBound<FIRST>( d_distribution.begin(),
				       d_distribution.end(),
				       indep_var_value );

    // The same independent variable may appear multiple times
    cdf = bin->second;
  }
  else if( indep_var_value < d_distribution.front().first )
    cdf = 0.0;
  else
    cdf = 1.0;
  
  return cdf;
}


// Return a random sample from the distribution
double DiscreteDistribution::sample() const
{
  double random_number = RandomNumberGenerator::getRandomNumber<double>();
  
  unsigned dummy_index;

  return this->sampleImplementation( random_number, dummy_index );
}

// Return a random sample and record the number of trials
double DiscreteDistribution::sampleAndRecordTrials( unsigned& trials ) const
{
  ++trials;

  return this->sample();
}

// Return a random sample and sampled index from the corresponding CDF
double DiscreteDistribution::sampleAndRecordBinIndex( 
					    unsigned& sampled_bin_index ) const
{
  double random_number = RandomNumberGenerator::getRandomNumber<double>();
  
  return this->sampleImplementation( random_number, sampled_bin_index );
}

// Return a random sample and sampled index from the corresponding CDF
double DiscreteDistribution::sampleWithRandomNumber( 
					     const double random_number ) const
{
  unsigned dummy_index;
  
  return this->sampleImplementation( random_number, dummy_index );
}

// Return a random sample from the corresponding CDF in a subrange
double DiscreteDistribution::sampleInSubrange( 
					     const double max_indep_var ) const
{
  // Make sure the max independent variable is valid
  testPrecondition( max_indep_var >= d_distribution.front().first );
  
  double random_number = RandomNumberGenerator::getRandomNumber<double>();

  return this->sampleWithRandomNumberInSubrange( random_number,
						 max_indep_var );
}

// Return the upper bound of the distribution independent variable
double DiscreteDistribution::getUpperBoundOfIndepVar() const
{
  return d_distribution.back().first;
}

// Return the lower bound of the independent variable
double DiscreteDistribution::getLowerBoundOfIndepVar() const
{
  return d_distribution.front().first;
}

// Return the distribution type
OneDDistributionType DiscreteDistribution::getDistributionType() const
{
  return DiscreteDistribution::distribution_type;
}

// Test if the distribution is continuous
bool DiscreteDistribution::isContinuous() const
{
  return false;
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

  // Parse special charaters
  try{
    ArrayString::locateAndReplacePi( independent_values_rep );
    ArrayString::locateAndReplaceIntervalOperator( independent_values_rep );
  }
  EXCEPTION_CATCH_RETHROW_AS( std::runtime_error,
			      InvalidDistributionStringRepresentation,
			      "Error: the discrete distribution cannot be "
			      "constructed because the independent values are "
			      "not valid (see details below)!\n" );
  
  Teuchos::Array<double> independent_values;
  try{
    independent_values = 
      Teuchos::fromStringToArray<double>( independent_values_rep );
  }
  EXCEPTION_CATCH_RETHROW_AS( Teuchos::InvalidArrayStringRepresentation,
			      InvalidDistributionStringRepresentation,
			      "Error: the discrete distribution cannot be "
			      "constructed because the independent values are "
			      "not valid (see details below)!\n" );

  TEST_FOR_EXCEPTION( !Sort::isSortedAscending( independent_values.begin(),
						independent_values.end() ),
		      InvalidDistributionStringRepresentation,
		      "Error: the discrete distribution cannot be constructed "
		      "because the bin boundaries "
		      << independent_values_rep << " are not sorted!" );
    
  // Read the ","
  std::string separator;
  std::getline( is, separator, ',' );
  
  std::string dependent_values_rep;
  std::getline( is, dependent_values_rep, '}' );
  dependent_values_rep += "}";

  // Parse special charaters
  try{
    ArrayString::locateAndReplacePi( dependent_values_rep );
    ArrayString::locateAndReplaceIntervalOperator( dependent_values_rep );
  }
  EXCEPTION_CATCH_RETHROW_AS( std::runtime_error,
			      InvalidDistributionStringRepresentation,
			      "Error: the discrete distribution cannot be "
			      "constructed because the dependent values are "
			      "not valid (see details below)!\n" );
  
  Teuchos::Array<double> dependent_values;
  try{
    dependent_values = 
      Teuchos::fromStringToArray<double>( dependent_values_rep );
  }
  EXCEPTION_CATCH_RETHROW_AS( Teuchos::InvalidArrayStringRepresentation,
			      InvalidDistributionStringRepresentation,
			      "Error: the discrete distribution cannot be "
			      "constructed because the dependent values are "
			      "not valid (see details below)!\n" );
  
  TEST_FOR_EXCEPTION( independent_values.size() != dependent_values.size(),
		      InvalidDistributionStringRepresentation, 
		      "Error: the discrete distribution "
		      "{" << independent_values_rep << "},{"
		      << dependent_values_rep << "} "
		      "cannot be constructed because the number of "
		      "independent values does not match the number of "
		      "dependent values!" );
  
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
  // Make sure that the bins are sorted
  testPrecondition( Sort::isSortedAscending( independent_values.begin(),
					     independent_values.end() ) );
  
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
