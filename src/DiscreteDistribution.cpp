//---------------------------------------------------------------------------//
//!
//! \file   DiscreteDistribution.cpp
//! \author Alex Robinson
//! \brief  Discrete distribution class definition.
//!
//---------------------------------------------------------------------------//

// FACEMC Includes
#include "DiscreteDistribution.hpp"
#include "DataProcessor.hpp"
#include "RandomNumberGenerator.hpp"

namespace FACEMC{

// Constructor
DiscreteDistribution::DiscreteDistribution( 
			         const Teuchos::Array<double>& discrete_values,
				 const Teuchos::Array<double>& probabilities )
  : d_distribution( discrete_values.size() )
{
  // Make sure that every value has a probability assigned
  testPrecondition( discrete_values.size() == probabilities.size() );

  // Assign the raw distribution data
  for( unsigned i = 0; i < discrete_values.size(); ++i )
  {
    d_distribution[i].first = discrete_values[i];

    d_distribution[i].second = probabilities[i];
  }

  // Create a CDF from the raw distribution data
  DataProcessor::calculateDiscreteCDF<SECOND,SECOND>( d_distribution );
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
    Search::binarySearchDiscreteData<SECOND>( d_distribution.begin(),
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

} // end FACEMC namespace

//---------------------------------------------------------------------------//
// end DiscreteDistribution.cpp
//---------------------------------------------------------------------------//
