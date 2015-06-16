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

namespace {

// Find the lower and upper bin boundary
void findLowerAndUpperBinBoundary( 
	      const double independent_variable,
	      const MonteCarlo::TwoDDistribution& dependent_distribution,
	      MonteCarlo::TwoDDistribution::const_iterator& lower_bin_boundary,
	      MonteCarlo::TwoDDistribution::const_iterator& upper_bin_boundary,
	      double& interpolation_fraction )
{
  if( independent_variable < dependent_distribution.front().first )
  {
    lower_bin_boundary = dependent_distribution.begin();
    upper_bin_boundary = lower_bin_boundary;
    //return dependent_distribution.front().second->sample();
  }
  else if( independent_variable >= dependent_distribution.back().first )
  {
    lower_bin_boundary = dependent_distribution.end();
    --lower_bin_boundary;
    upper_bin_boundary = lower_bin_boundary;
    //return dependent_distribution.back().second->sample();
  }
  else
  {
    lower_bin_boundary = dependent_distribution.begin();
    upper_bin_boundary = dependent_distribution.end();
    
    lower_bin_boundary = Utility::Search::binaryLowerBound<Utility::FIRST>( 
							lower_bin_boundary,
							upper_bin_boundary,
							independent_variable );
    upper_bin_boundary = lower_bin_boundary;
    ++upper_bin_boundary;

    // Calculate the interpolation fraction
    interpolation_fraction = 
      (independent_variable - lower_bin_boundary->first)/
      (upper_bin_boundary->first - lower_bin_boundary->first);
  }
}

} // end Anonymous namespace

namespace MonteCarlo{

// Sample a two dimensional ditribution
/*! \details This function is designed for lin-lin unit base interpolation 
 * data.
 */  
double sampleTwoDDistributionCorrelated(
   const double independent_variable,
   const TwoDDistribution& dependent_distribution )
{
  TwoDDistribution::const_iterator lower_bin_boundary, upper_bin_boundary;
  double interpolation_fraction;

  findLowerAndUpperBinBoundary( independent_variable,
				dependent_distribution,
				lower_bin_boundary,
				upper_bin_boundary,
				interpolation_fraction );
  
  if( lower_bin_boundary != upper_bin_boundary )
  {
    return correlatedSample( upper_bin_boundary->second,
			     lower_bin_boundary->second,
			     interpolation_fraction );
  }
  else
    return lower_bin_boundary->second->sample();
}

// Sample a two dimensional distribution
/*! \details This function is designed for lin-lin unit base interpolation 
 * data.
 */
double sampleTwoDDistributionIndependent(
    const double independent_variable,
    const TwoDDistribution& dependent_distribution )
{
  TwoDDistribution::const_iterator lower_bin_boundary, upper_bin_boundary;
  double interpolation_fraction;

  findLowerAndUpperBinBoundary( independent_variable,
				dependent_distribution,
				lower_bin_boundary,
				upper_bin_boundary,
				interpolation_fraction );
  
  if( lower_bin_boundary != upper_bin_boundary )
  {
    return independentSample( upper_bin_boundary->second,
			      lower_bin_boundary->second,
			      interpolation_fraction );
  }
  else
    return lower_bin_boundary->second->sample();
}

// Evaluate a correlated PDF from a two dimensional distribution
double evaluateTwoDDistributionCorrelatedPDF( 
    const double independent_variable,
    const double dependent_variable,
    const TwoDDistribution& dependent_distribution )
{
  TwoDDistribution::const_iterator lower_bin_boundary, upper_bin_boundary;
  double interpolation_fraction;

  findLowerAndUpperBinBoundary( independent_variable,
				dependent_distribution,
				lower_bin_boundary,
				upper_bin_boundary,
				interpolation_fraction );
  
  if( lower_bin_boundary != upper_bin_boundary )
  {
    return evaluateCorrelatedPDF( upper_bin_boundary->second,
			          lower_bin_boundary->second,
			          interpolation_fraction,
                                  dependent_variable );
  }
  else
    return lower_bin_boundary->second->evaluatePDF( dependent_variable );
}

// Sample an upper and lower distribution using a common random variable
double correlatedSample(
                    const Teuchos::RCP<const Utility::TabularOneDDistribution>&
		    upper_distribution,
		    const Teuchos::RCP<const Utility::TabularOneDDistribution>&
		    lower_distribution,
		    const double interpolation_fraction )
{  
  double random_number = 
      Utility::RandomNumberGenerator::getRandomNumber<double>();
    
  double upper_dist_dependent_variable = 
                   upper_distribution->sampleWithRandomNumber( random_number );

  double lower_dist_dependent_variable = 
                   lower_distribution->sampleWithRandomNumber( random_number );

  // Linearly interpolate between the upper and lower distributions
  return lower_dist_dependent_variable + interpolation_fraction*
    (upper_dist_dependent_variable - lower_dist_dependent_variable);
}

// Sample an upper and lower distribution using a common random variable in a subrange
double correlatedSample(
                    const Teuchos::RCP<const Utility::TabularOneDDistribution>&
		    upper_distribution,
		    const Teuchos::RCP<const Utility::TabularOneDDistribution>&
		    lower_distribution,
		    const double interpolation_fraction,
		    const double max_indep_var )
{  
  // Sample the upper and lower distributions using the same random number
  double random_number = 
    Utility::RandomNumberGenerator::getRandomNumber<double>();
  
  double upper_dist_dependent_variable = 
    upper_distribution->sampleWithRandomNumberInSubrange( random_number,
							  max_indep_var );

  double lower_dist_dependent_variable = 
    lower_distribution->sampleWithRandomNumberInSubrange( random_number,
							  max_indep_var );

  // Linearly interpolate between the upper and lower distributions
  return lower_dist_dependent_variable + interpolation_fraction*
    (upper_dist_dependent_variable - lower_dist_dependent_variable);
}

// Evaluate a correlated cdf value
double evaluateCorrelatedCDF(
                    const Teuchos::RCP<const Utility::TabularOneDDistribution>&
		    upper_distribution,
		    const Teuchos::RCP<const Utility::TabularOneDDistribution>&
		    lower_distribution,
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

// Evaluate a correlated pdf value
double evaluateCorrelatedPDF(
    const Teuchos::RCP<const Utility::OneDDistribution>& upper_distribution,
    const Teuchos::RCP<const Utility::OneDDistribution>& lower_distribution,
    const double interpolation_fraction,
    const double independent_value )
{
  double upper_pdf = 
    upper_distribution->evaluatePDF( independent_value );

  double lower_pdf = 
    lower_distribution->evaluatePDF( independent_value );

  // Linearly interpolate between the upper and lower cdf values
  return interpolation_fraction*(upper_pdf - lower_pdf) + lower_pdf;
}

// Sample from either the lower or upper distribution depending on interp frac
double independentSample(
                    const Teuchos::RCP<const Utility::TabularOneDDistribution>&
		    upper_distribution,
		    const Teuchos::RCP<const Utility::TabularOneDDistribution>&
		    lower_distribution,
		    const double interpolation_fraction )
{
  double random_number = 
    Utility::RandomNumberGenerator::getRandomNumber<double>();

  if( random_number < interpolation_fraction )
    return upper_distribution->sample();
  else
    return lower_distribution->sample();
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_TwoDDistributionHelpers.cpp
//---------------------------------------------------------------------------//
