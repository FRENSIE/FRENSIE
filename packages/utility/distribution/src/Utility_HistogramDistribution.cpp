//---------------------------------------------------------------------------//
//!
//! \file   Utility_HistogramDistribution.cpp
//! \author Alex Robinson
//! \brief  Histogram distribution class definition.
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <limits>

// FRENSIE Includes
#include "Utility_HistogramDistribution.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_SortAlgorithms.hpp"
#include "Utility_ExceptionTestMacros.hpp"

namespace Utility{

// Default constructor
HistogramDistribution::HistogramDistribution()
{ /* ... */ }

// Constructor
HistogramDistribution::HistogramDistribution( 
				  const Teuchos::Array<double>& bin_boundaries,
				  const Teuchos::Array<double>& bin_values )
  : d_distribution( bin_boundaries.size() )
{
  initializeDistribution( bin_boundaries, bin_values );
}

// Copy constructor
HistogramDistribution::HistogramDistribution(
				   const HistogramDistribution& dist_instance )
  : d_distribution( dist_instance.d_distribution ),
    d_norm_constant( dist_instance.d_norm_constant )
{
  // Make sure that the distribution is valid
  testPrecondition( dist_instance.d_distribution.size() > 0 );
}

// Assignment operator
HistogramDistribution& HistogramDistribution::operator=(
				   const HistogramDistribution& dist_instance )
{
  if( this != &dist_instance )
  {
    d_distribution = dist_instance.d_distribution;
    d_norm_constant = dist_instance.d_norm_constant;
  }

  return *this;
}

// Evaluate the distribution
double HistogramDistribution::evaluate( const double indep_var_value ) const
{
  return evaluatePDF( indep_var_value )*d_norm_constant;
}

// Evaluate the PDF
double HistogramDistribution::evaluatePDF( const double indep_var_value ) const
{
  if( indep_var_value < d_distribution.front().first )
    return 0.0;
  else if( indep_var_value > d_distribution.back().first )
    return 0.0;
  else
  {
    Teuchos::Array<Trip<double,double,double> >::const_iterator bin = 
      Search::binaryLowerBound<FIRST>( d_distribution.begin(),
				       d_distribution.end(),
				       indep_var_value );
    
    return bin->second;
  }
} 

// Return a random sample and bin index from the distribution
double HistogramDistribution::sample( unsigned& sampled_bin_index ) const
{
  // Sample the bin
  double random_number = RandomNumberGenerator::getRandomNumber<double>();
  
  Teuchos::Array<Trip<double,double,double> >::const_iterator bin = 
    Search::binaryLowerBound<THIRD>( d_distribution.begin(),
				     d_distribution.end(),
				     random_number );

  sampled_bin_index = std::distance( d_distribution.begin(), bin );

  return bin->first + (random_number - bin->third)/bin->second;
}

// Return the sampling efficiency from the distribution
double HistogramDistribution::getSamplingEfficiency() const
{
  return 1.0;
}

// Return the upper bound of the distribution independent variable
double HistogramDistribution::getUpperBoundOfIndepVar() const
{
  return d_distribution.back().first;
}

// Return the lower bound of the distribution independent variable
double HistogramDistribution::getLowerBoundOfIndepVar() const
{
  return d_distribution.front().first;
}

// Return the distribution type
OneDDistributionType HistogramDistribution::getDistributionType() const
{
  return HistogramDistribution::distribution_type;
}

// Method for placing the object in an output stream
void HistogramDistribution::toStream( std::ostream& os ) const
{
  Teuchos::Array<double> bin_boundaries( d_distribution.size() );
  Teuchos::Array<double> bin_values( d_distribution.size() - 1 );

  bin_boundaries.back() = d_distribution.back().first;
  
  for( unsigned i = 0u; i < d_distribution.size() - 1; ++i )
  {
    bin_boundaries[i] = d_distribution[i].first;
    
    bin_values[i] = d_distribution[i].second*d_norm_constant;
  }

  os << "{" << bin_boundaries << "," << bin_values << "}";
}

// Method for initializing the object from an input stream
void HistogramDistribution::fromStream( std::istream& is )
{
  // Read the initial '{'
  std::string start_bracket;
  std::getline( is, start_bracket, '{' );
  start_bracket = Teuchos::Utils::trimWhiteSpace( start_bracket );
  
  TEST_FOR_EXCEPTION( start_bracket.size() != 0, 
		      InvalidDistributionStringRepresentation, 
		      "Error: the input stream is not a valid histogram "
		      "distribution representation!" );

  std::string bin_boundaries_rep;
  std::getline( is, bin_boundaries_rep, '}' );
  bin_boundaries_rep += "}";
  
  Teuchos::Array<double> bin_boundaries;
  try{
    bin_boundaries = Teuchos::fromStringToArray<double>( bin_boundaries_rep );
  }
  catch( Teuchos::InvalidArrayStringRepresentation& error )
  {
    std::string message( "Error: the histogram distribution cannot be "
			 "constructed because the representation is not valid "
			 "(see details below)!\n" );
    message += error.what();

    throw InvalidDistributionStringRepresentation( message );
  }

  TEST_FOR_EXCEPTION( !Sort::isSortedAscending( bin_boundaries.begin(),
						bin_boundaries.end() ),
		      InvalidDistributionStringRepresentation,
		      "Error: the histogram distribution cannot be "
		      "constructed because the bin boundaries "
		      << bin_boundaries_rep << " are not sorted!" );
  
  // Read the ","
  std::string separator;
  std::getline( is, separator, ',' );

  std::string bin_values_rep;
  std::getline( is, bin_values_rep, '}' );
  bin_values_rep += "}";
  
  Teuchos::Array<double> bin_values;
  try{
    bin_values = Teuchos::fromStringToArray<double>( bin_values_rep );
  }
  catch( Teuchos::InvalidArrayStringRepresentation& error )
  {
    std::string message( "Error: the histogram distribution cannot be "
			 "constructed because the representation is not valid "
			 "(see details below)!\n" );
    message += error.what();

    throw InvalidDistributionStringRepresentation( message );
  }

  TEST_FOR_EXCEPTION( bin_boundaries.size()-1 != bin_values.size(),
		      InvalidDistributionStringRepresentation, 
		      "Error: the histogram distribution "
		      "{" << bin_boundaries_rep << "},{"
		      << bin_values_rep << "} "
		      "cannot be constructed because the number of bin values "
		      "does not equal the number of bin boundaries - 1!" );
		        
  initializeDistribution( bin_boundaries, bin_values );
}

// Method for testing if two objects are equivalent
bool HistogramDistribution::isEqual( const HistogramDistribution& other ) const
{
  return d_distribution == other.d_distribution && 
    d_norm_constant == other.d_norm_constant;
}

// Initialize the distribution
void HistogramDistribution::initializeDistribution( 
				  const Teuchos::Array<double>& bin_boundaries,
				  const Teuchos::Array<double>& bin_values )
{
  // Make sure that the bin boundaries are sorted
  testPrecondition( Sort::isSortedAscending( bin_boundaries.begin(), 
					     bin_boundaries.end() ) );
  // Make sure that for n bin boundaries there are n-1 bin values
  testPrecondition( bin_boundaries.size()-1 == bin_values.size() );

  // Resize the distribution
  d_distribution.resize( bin_boundaries.size() );

  // Construct the distribution
  for( unsigned i = 0; i < bin_boundaries.size(); ++i )
  {
    // Assign the min and max bin boundaries (respectively)
    d_distribution[i].first = bin_boundaries[i];

    // Assign the bin PDF value
    if( i < bin_boundaries.size() - 1 )
      d_distribution[i].second = bin_values[i];
    else 
      d_distribution[i].second = bin_values[i-1];
    
    // Assign the discrete CDF value
    if( i > 0 )
    {
      d_distribution[i].third = d_distribution[i-1].third;
      
      d_distribution[i].third += bin_values[i-1]*
      (d_distribution[i].first - d_distribution[i-1].first);
    }
    else
      d_distribution[i].third = 0.0;
  }

  // Assign the normalization constant
  d_norm_constant = d_distribution.back().third;

  // Normalize the PDF and CDF
  for( unsigned i = 0; i < d_distribution.size(); ++i )
  {
    d_distribution[i].second /= d_norm_constant;
    d_distribution[i].third /= d_norm_constant;
  }

  // Make sure that the CDF has been constructed correctly
  testPostcondition( ST::magnitude( d_distribution.back().third - 1.0 ) <
		     ST::prec() );
}

} // end Utility namespace

//---------------------------------------------------------------------------//
// end Utility_HistogramDistribution.cpp
//---------------------------------------------------------------------------//
