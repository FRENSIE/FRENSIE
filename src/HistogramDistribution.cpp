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
  : d_distribution( bin_boundaries.size() )
{
  // Make sure that for n bin boundaries there are n-1 bin values
  testPrecondition( bin_boundaries.size()-1 == bin_values.size() );

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
    Teuchos::Array<Trip<double,double,double> >::const_iterator bin = 
      Search::binarySearchContinuousData<FIRST>( d_distribution.begin(),
						 d_distribution.end(),
						 indep_var_value );
    return bin->second;
  }
} 

// Return a random sample from the distribution
double HistogramDistribution::sample() 
{
  return (const_cast<const HistogramDistribution*>(this))->sample();
}

// Return a random sample from the distribution
double HistogramDistribution::sample() const
{
  // Sample the bin
  double random_number = RandomNumberGenerator::getRandomNumber<double>();
  
  Teuchos::Array<Trip<double,double,double> >::const_iterator bin = 
    Search::binarySearchContinuousData<THIRD>( d_distribution.begin(),
						d_distribution.end(),
						random_number );

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

} // end FACEMC namespace

//---------------------------------------------------------------------------//
// end HistogramDistribution.cpp
//---------------------------------------------------------------------------//
