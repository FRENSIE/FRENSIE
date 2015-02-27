//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_TwoDDistributionHelpers.cpp
//! \author Luke Kersting
//! \brief  Two dimensional distribution helpers base class definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_TwoDDistributionHelpers.hpp"
#include "Utility_SearchAlgorithms.hpp"

namespace MonteCarlo{


// Sample a two dimensional ditribution
/*! \details This function is designed for lin-lin base interpolation data and 
 *  is not appropriate for unit base interpolations
 */  
double sampleTwoDDistribution(
   const double independent_variable,
   const TwoDDistribution& dependent_distribution )
{

  if( independent_variable < dependent_distribution.front().first )
  {
    return dependent_distribution.front().second->sample();
  }
  else if( independent_variable >= dependent_distribution.back().first )
  {
    return dependent_distribution.back().second->sample();
  }
  else
  {
    TwoDDistribution::const_iterator
      lower_dist_boundary, upper_dist_boundary;
    
    lower_dist_boundary = dependent_distribution.begin();
    upper_dist_boundary = dependent_distribution.end();
    
    lower_dist_boundary = Utility::Search::binaryLowerBound<Utility::FIRST>( 
							  lower_dist_boundary,
							  upper_dist_boundary,
							  independent_variable );

    upper_dist_boundary = lower_dist_boundary;
    ++upper_dist_boundary;

    // Calculate the interpolation fraction
    double interpolation_fraction = ( independent_variable - lower_dist_boundary->first )/
      (upper_dist_boundary->first - lower_dist_boundary->first);

    return correlatedSample( upper_dist_boundary->second,
                             lower_dist_boundary->second,
                             interpolation_fraction );
  }
}

// Sample an upper and lower distribution using a common random variable
double correlatedSample(
   const Teuchos::RCP<const Utility::OneDDistribution>& upper_distribution,
   const Teuchos::RCP<const Utility::OneDDistribution>& lower_distribution,
   const double interpolation_fraction )
{  
  double random_number = 
      Utility::RandomNumberGenerator::getRandomNumber<double>();
    
  double upper_dist_dependent_variable = 
                   upper_distribution->sampleWithValue( random_number );

  double lower_dist_dependent_variable = 
                   lower_distribution->sampleWithValue( random_number );

  // Linearly interpolate between the upper and lower distributions
  return lower_dist_dependent_variable + interpolation_fraction*
                (upper_dist_dependent_variable - lower_dist_dependent_variable);
}

// Sample an upper and lower distribution using a common random variable in a subrange
double correlatedSample(
   const Teuchos::RCP<const Utility::OneDDistribution>& upper_distribution,
   const Teuchos::RCP<const Utility::OneDDistribution>& lower_distribution,
   const double interpolation_fraction,
   const double max_indep_var )
{  
    // Sample the upper and lower distributions using the same random number
    double random_number = 
      Utility::RandomNumberGenerator::getRandomNumber<double>();
    
    double upper_dist_dependent_variable = 
                     upper_distribution->sampleWithValue( random_number,
                                                          max_indep_var );

    double lower_dist_dependent_variable = 
                     lower_distribution->sampleWithValue( random_number,
                                                          max_indep_var );

    // Linearly interpolate between the upper and lower distributions
    return lower_dist_dependent_variable + interpolation_fraction*
                (upper_dist_dependent_variable - lower_dist_dependent_variable);
}

// Evaluate a correlated cdf value
double evaluateCorrelatedCDF(
    const Teuchos::RCP<const Utility::OneDDistribution>& upper_distribution,
    const Teuchos::RCP<const Utility::OneDDistribution>& lower_distribution,
    const double interpolation_fraction,
    const double independent_value )
{
  double upper_cdf = 
    upper_distribution->evaluateCDF( independent_value );

  double lower_cdf = 
    lower_distribution->evaluateCDF( independent_value );

  // Linearly interpolate between the upper and lower cdf values
  return interpolation_fraction*(upper_cdf - lower_cdf) + lower_cdf;
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_TwoDDistributionHelpers.cpp
//---------------------------------------------------------------------------//
