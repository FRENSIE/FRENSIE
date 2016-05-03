//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_TwoDDistributionHelpers_def.hpp
//! \author Luke Kersting
//! \brief  Two dimensional distribution helpers declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_TWO_D_DISTRIBUTION_HELPERS_DEF_HPP
#define MONTE_CARLO_TWO_D_DISTRIBUTION_HELPERS_DEF_HPP

// FRENSIE Includes
#include "Utility_SearchAlgorithms.hpp"

namespace MonteCarlo{

// Find the lower and upper bin boundary
template<typename DependentTwoDDistribution>
void findLowerAndUpperBinBoundary( 
    const double independent_variable,
	const DependentTwoDDistribution& dependent_distribution,
    typename DependentTwoDDistribution::const_iterator& lower_bin_boundary,
    typename DependentTwoDDistribution::const_iterator& upper_bin_boundary,
    double& interpolation_fraction )
{
  if( independent_variable < dependent_distribution.front().first )
  {
    lower_bin_boundary = dependent_distribution.begin();
    upper_bin_boundary = lower_bin_boundary;
  }
  else if( independent_variable >= dependent_distribution.back().first )
  {
    lower_bin_boundary = dependent_distribution.end();
    --lower_bin_boundary;
    upper_bin_boundary = lower_bin_boundary;
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

// Sample a two dimensional ditribution with a random number
/*! \details This function is designed for lin-lin unit base interpolation 
 * data.
 */  
template<typename DependentTwoDDistribution>
double sampleTwoDDistributionCorrelatedWithRandomNumber(
   const double independent_variable,
   const DependentTwoDDistribution& dependent_distribution,
   const double random_number )
{
  typename DependentTwoDDistribution::const_iterator lower_bin_boundary, 
                                                     upper_bin_boundary;
  double interpolation_fraction;

  findLowerAndUpperBinBoundary( independent_variable,
                                dependent_distribution,
                                lower_bin_boundary,
                                upper_bin_boundary,
                                interpolation_fraction );

  if( lower_bin_boundary != upper_bin_boundary )
  {
    return correlatedSampleWithRandomNumber( upper_bin_boundary->second,
                                             lower_bin_boundary->second,
                                             interpolation_fraction,
                                             random_number );
  }
  else
    return lower_bin_boundary->second->sampleWithRandomNumber( random_number );
}


// Sample a two dimensional ditribution
/*! \details This function is designed for lin-lin unit base interpolation 
 * data.
 */  
template<typename DependentTwoDDistribution>
double sampleTwoDDistributionCorrelated(
   const double independent_variable,
   const DependentTwoDDistribution& dependent_distribution )
{
  double random_number = 
      Utility::RandomNumberGenerator::getRandomNumber<double>();

  return sampleTwoDDistributionCorrelatedWithRandomNumber<DependentTwoDDistribution>(
            independent_variable,
            dependent_distribution,
            random_number );
}


// Sample a two dimensional distribution
/*! \details This function is designed for lin-lin unit base interpolation 
 * data.
 */
template<typename DependentTwoDDistribution>
double sampleTwoDDistributionIndependent(
    const double independent_variable,
    const DependentTwoDDistribution& dependent_distribution )
{
  typename DependentTwoDDistribution::const_iterator lower_bin_boundary, 
                                                     upper_bin_boundary;
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


// Evaluate a correlated value from a two dimensional distribution
template<typename DependentTwoDDistribution>
double evaluateTwoDDistributionCorrelated( 
    const double independent_variable,
    const double dependent_variable,
    const DependentTwoDDistribution& dependent_distribution )
{
  typename DependentTwoDDistribution::const_iterator lower_bin_boundary, 
                                                     upper_bin_boundary;
  double interpolation_fraction;

  findLowerAndUpperBinBoundary( independent_variable,
				dependent_distribution,
				lower_bin_boundary,
				upper_bin_boundary,
				interpolation_fraction );
  
  if( lower_bin_boundary != upper_bin_boundary )
  {
    return evaluateCorrelated( upper_bin_boundary->second,
                               lower_bin_boundary->second,
                               interpolation_fraction,
                               dependent_variable );
  }
  else
    return lower_bin_boundary->second->evaluate( dependent_variable );
}


// Evaluate a correlated PDF from a two dimensional distribution
template<typename DependentTwoDDistribution>
double evaluateTwoDDistributionCorrelatedPDF( 
    const double independent_variable,
    const double dependent_variable,
    const DependentTwoDDistribution& dependent_distribution )
{
  typename DependentTwoDDistribution::const_iterator lower_bin_boundary, 
                                                     upper_bin_boundary;
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


// Evaluate a correlated CDF from a two dimensional distribution
template<typename DependentTwoDDistribution>
double evaluateTwoDDistributionCorrelatedCDF( 
    const double independent_variable,
    const double dependent_variable,
    const DependentTwoDDistribution& dependent_distribution )
{
  typename DependentTwoDDistribution::const_iterator lower_bin_boundary, 
                                                     upper_bin_boundary;
  double interpolation_fraction;

  findLowerAndUpperBinBoundary( independent_variable,
				dependent_distribution,
				lower_bin_boundary,
				upper_bin_boundary,
				interpolation_fraction );
  
  if( lower_bin_boundary != upper_bin_boundary )
  {
    return evaluateCorrelatedCDF( upper_bin_boundary->second,
                                  lower_bin_boundary->second,
                                  interpolation_fraction,
                                  dependent_variable );
  }
  else
    return lower_bin_boundary->second->evaluateCDF( dependent_variable );
}


// Sample an upper and lower distribution using a common given random variable
template<typename DependentDistribution>
double correlatedSampleWithRandomNumber(
    const Teuchos::RCP<const DependentDistribution>& upper_distribution,
    const Teuchos::RCP<const DependentDistribution>& lower_distribution,
    const double interpolation_fraction,
    const double random_number )
{  
  double upper_dist_dependent_variable = 
                   upper_distribution->sampleWithRandomNumber( random_number );

  double lower_dist_dependent_variable = 
                   lower_distribution->sampleWithRandomNumber( random_number );

  // Linearly interpolate between the upper and lower distributions
  return lower_dist_dependent_variable + interpolation_fraction*
    (upper_dist_dependent_variable - lower_dist_dependent_variable);
}


// Sample an upper and lower distribution using a common random variable
template<typename DependentDistribution>
double correlatedSample(
    const Teuchos::RCP<const DependentDistribution>& upper_distribution,
    const Teuchos::RCP<const DependentDistribution>& lower_distribution,
    const double interpolation_fraction )
{  
  double random_number = 
      Utility::RandomNumberGenerator::getRandomNumber<double>();
    
  return correlatedSampleWithRandomNumber(
                    upper_distribution, 
                    lower_distribution, 
                    interpolation_fraction,
                    random_number );
}


// Sample an upper and lower distribution using a common random variable in a subrange
template<typename DependentDistribution>
double correlatedSampleInSubrange(
    const Teuchos::RCP<const DependentDistribution>& upper_distribution,
	const Teuchos::RCP<const DependentDistribution>& lower_distribution,
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
template<typename DependentDistribution>
double evaluateCorrelatedCDF(
    const Teuchos::RCP<const DependentDistribution>& upper_distribution,
	const Teuchos::RCP<const DependentDistribution>& lower_distribution,
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
template<typename DependentDistribution>
double evaluateCorrelatedPDF(
    const Teuchos::RCP<const DependentDistribution>& upper_distribution,
    const Teuchos::RCP<const DependentDistribution>& lower_distribution,
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


// Evaluate a correlated value
template<typename DependentDistribution>
double evaluateCorrelated(
    const Teuchos::RCP<const DependentDistribution>& upper_distribution,
    const Teuchos::RCP<const DependentDistribution>& lower_distribution,
    const double interpolation_fraction,
    const double independent_value )
{
  double upper_pdf = 
    upper_distribution->evaluate( independent_value );

  double lower_pdf = 
    lower_distribution->evaluate( independent_value );

  // Linearly interpolate between the upper and lower pdf values
  return interpolation_fraction*(upper_pdf - lower_pdf) + lower_pdf;
}


// Sample from either the lower or upper distribution depending on interp frac
template<typename DependentDistribution>
double independentSample(
    const Teuchos::RCP<const DependentDistribution>& upper_distribution,
	const Teuchos::RCP<const DependentDistribution>& lower_distribution,
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

#endif // end MONTE_CARLO_TWO_D_DISTRIBUTION_HELPERS_DEF_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_TwoDDistributionHelpers_def.hpp
//---------------------------------------------------------------------------//
