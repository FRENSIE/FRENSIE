//---------------------------------------------------------------------------//
//!
//! \file   DiscreteDistribution.cpp
//! \author Alex Robinson
//! \brief  Discrete distribution class definition.
//!
//---------------------------------------------------------------------------//

// FACEMC Includes
#include "DiscreteDistribution.hpp"
#include "RandomNumberGenerator.hpp"
#include "SearchAlgorithms.hpp"
#include "ContractException.hpp"

namespace FACEMC{

// Constructor
DiscreteDistribution::DiscreteDistribution( 
			         const Teuchos::Array<double>& discrete_values,
				 const Teuchos::Array<double>& probabilities )
{
  // Make sure that every value has a probability assigned
  testPrecondition( discrete_values.size() == probabilities.size() );

  // Construct the distribution( discrete values, CDF )
  for( unsigned i = 0; i < discrete_values.size(); ++i )
  {
    d_distribution[i].first = discrete_values[i];

    d_distribution[i].second = probalities[i];
    
    if( i > 0 )
      d_distribution[i].second += d_distribution[i-1].second;
  }

  // Normalize the CDF
  for( unsigned i = 0; i < d_distribution.size(); ++i )
    d_distribution[i].second /= d_distrubiton.back().second;

  // Make sure that the CDF has been constructed correctly
  testPostcondition( ST::magnitude( d_distribution.back().second - 1.0 ) <
		     ST::prec() );
}

// Evaluate the distribution
/*! \details The discrete distribution can be expressed as a sum of delta
 * functions. Therefore, the discrete distribution can only take on two
 * values: 0.0 and infinity.
 */
double evaluate( const double indep_var_value ) const 
{
  for( unsigned i = 0; i < d_distribution.size(); ++i )
  {
    if( indep_var_value == d_distribution[i] )
      return std::numeric_limits<double>::infinity();
  }

  return 0.0;
}

// Return a random sample from the distribution
double DiscreteDistribution::sample()
{
  double random_number = RandomNumberGenerator<double>::getRandomNumber();

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
  return d_distribution.front().first;
}

// Return the lower bound of the independent variable
double DiscreteDistribution::getLowerBoundOfIndepVar() const
{
  return d_distribution.back().first;
}

} // end FACEMC namespace

//---------------------------------------------------------------------------//
// end DiscreteDistribution.cpp
//---------------------------------------------------------------------------//
