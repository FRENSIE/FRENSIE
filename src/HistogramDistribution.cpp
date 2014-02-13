//---------------------------------------------------------------------------//
//!
//! \file   HistogramDistribution.cpp
//! \author Alex Robinson
//! \brief  Histogram distribution class definition.
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <limits>

// FACEMC Includes
#include "HistogramDistribution.hpp"
#include "RandomNumberGenerator.hpp"

namespace FACEMC{

// Constructor
HistogramDistribution::HistogramDistribution( 
				  const Teuchos::Array<double>& bin_boundaries,
				  const Teuchos::Array<double>& bin_values )
  : d_distribution( bin_values.size() )
{
  // Make sure that for n bin boundaries there are n-1 bin values
  testPrecondition( bin_boundaries.size()-1 == bin_values.size() );

  // Construct the distribution
  for( unsigned i = 0; i < bin_values.size(); ++i )
  {
    // Assign the min and max bin boundaries (respectively)
    d_distribution[i].first = bin_boundaries[i];
    d_distribution[i].second = bin_boundaries[i+1];

    // Assign the bin PDF value
    d_distribution[i].third = bin_values[i];
    
    // Assign the discrete CDF value
    d_distribution[i].fourth = bin_values[i]*
      (d_distribution[i].second - d_distribution[i].first);

    if( i > 0 )
      d_distribution[i].fourth += d_distribution[i-1].fourth;
  }

  // Assign the normalization constant
  d_norm_constant = d_distribution.back().fourth;

  // Normalize the PDF and CDF
  for( unsigned i = 0; i < d_distribution.size(); ++i )
  {
    d_distribution[i].third /= d_distribution.back().fourth;
    d_distribution[i].fourth /= d_distribution.back().fourth;
  }

  // Make sure that the CDF has been constructed correctly
  testPostcondition( ST::magnitude( d_distribution.back().fourth - 1.0 ) <
		     ST::prec() );
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
  else if( indep_var_value > d_distribution.back().second )
    return 0.0;
  else
  {
    Teuchos::Array<Quad<double,double,double,double> >::const_iterator bin = 
      Search::binarySearchDiscreteData<SECOND>( d_distribution.begin(),
						d_distribution.end(),
						indep_var_value );
    return bin->third;
  }
} 

// Return a random sample from the distribution
double HistogramDistribution::sample()
{
  double random_number_1 = RandomNumberGenerator::getRandomNumber<double>();
  double random_number_2 = RandomNumberGenerator::getRandomNumber<double>();

  return sample( random_number_1, random_number_2 );
}

// Return the sampling efficiency from the distribution
double HistogramDistribution::getSamplingEfficiency() const
{
  return 1.0;
}

// Return the upper bound of the distribution independent variable
double HistogramDistribution::getUpperBoundOfIndepVar() const
{
  return d_distribution.back().second;
}

// Return the lower bound of the distribution independent variable
double HistogramDistribution::getLowerBoundOfIndepVar() const
{
  return d_distribution.front().first;
}

} // end FACEMC namespace

//---------------------------------------------------------------------------//
// end HistogramDistribution.cpp
//---------------------------------------------------------------------------//
