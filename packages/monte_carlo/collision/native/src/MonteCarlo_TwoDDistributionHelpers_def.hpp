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
template<typename DependentTwoDDistribution, typename InterpolationPolicy>
void findLowerAndUpperBinBoundary(
    const double independent_variable,
	const DependentTwoDDistribution& dependent_distribution,
    typename DependentTwoDDistribution::const_iterator& lower_bin_boundary,
    typename DependentTwoDDistribution::const_iterator& upper_bin_boundary )
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
  }
}

// Find the lower and upper bin boundary
template<typename DependentTwoDDistribution, typename InterpolationPolicy>
void findLowerAndUpperBinBoundary(
    const double independent_variable,
	const DependentTwoDDistribution& dependent_distribution,
    typename DependentTwoDDistribution::const_iterator& lower_bin_boundary,
    typename DependentTwoDDistribution::const_iterator& upper_bin_boundary,
    double& interpolation_fraction )
{

    findLowerAndUpperBinBoundary(
        independent_variable,
        dependent_distribution,
        lower_bin_boundary,
        upper_bin_boundary );

  if( independent_variable < dependent_distribution.front().first )
  {
    interpolation_fraction = 0.0;
  }
  else if( independent_variable >= dependent_distribution.back().first )
  {
    interpolation_fraction = 0.0;
  }
  else
  {
    // Calculate the interpolation fraction
    interpolation_fraction =
      (independent_variable - lower_bin_boundary->first)/
      (upper_bin_boundary->first - lower_bin_boundary->first);
  }
}

// Sample a two dimensional ditribution with a random number
template<typename DependentTwoDDistribution, typename InterpolationPolicy>
double sampleTwoDDistributionCorrelatedWithRandomNumber(
   const double independent_variable,
   const DependentTwoDDistribution& dependent_distribution,
   const double random_number )
{
  typename DependentTwoDDistribution::const_iterator lower_bin_boundary,
                                                     upper_bin_boundary;

  findLowerAndUpperBinBoundary<DependentTwoDDistribution, InterpolationPolicy>(
        independent_variable,
        dependent_distribution,
        lower_bin_boundary,
        upper_bin_boundary );

  if( lower_bin_boundary != upper_bin_boundary )
  {
    return InterpolationPolicy::interpolate(
        lower_bin_boundary->first,
        upper_bin_boundary->first,
        independent_variable,
        lower_bin_boundary->second->sampleWithRandomNumber( random_number ),
        upper_bin_boundary->second->sampleWithRandomNumber( random_number ) );
  }
  else
    return lower_bin_boundary->second->sampleWithRandomNumber( random_number );
}

template<typename DependentTwoDDistribution, typename InterpolationPolicy>
double sampleTwoDDistributionCorrelatedInSubrange(
    const double independent_variable,
    const DependentTwoDDistribution& dependent_distribution,
    const double max_indep_var )
{
  double random_number =
      Utility::RandomNumberGenerator::getRandomNumber<double>();

  typename DependentTwoDDistribution::const_iterator lower_bin_boundary,
                                                     upper_bin_boundary;

  findLowerAndUpperBinBoundary<DependentTwoDDistribution, InterpolationPolicy>(
        independent_variable,
        dependent_distribution,
        lower_bin_boundary,
        upper_bin_boundary);

  if( lower_bin_boundary != upper_bin_boundary )
  {
  return InterpolationPolicy::interpolate(
    lower_bin_boundary->first,
    upper_bin_boundary->first,
    independent_variable,
    lower_bin_boundary->second->sampleWithRandomNumberInSubrange( random_number, max_indep_var ),
    upper_bin_boundary->second->sampleWithRandomNumberInSubrange( random_number, max_indep_var ) );
  }
  else
  {
    return upper_bin_boundary->second->sampleInSubrange( max_indep_var );
  }
}


// Sample a two dimensional ditribution
template<typename DependentTwoDDistribution, typename InterpolationPolicy>
double sampleTwoDDistributionCorrelated(
   const double independent_variable,
   const DependentTwoDDistribution& dependent_distribution )
{
  double random_number =
      Utility::RandomNumberGenerator::getRandomNumber<double>();

  return sampleTwoDDistributionCorrelatedWithRandomNumber<DependentTwoDDistribution,InterpolationPolicy>(
            independent_variable,
            dependent_distribution,
            random_number );
}


// Sample a two dimensional distribution
template<typename DependentTwoDDistribution, typename InterpolationPolicy>
double sampleTwoDDistributionIndependent(
    const double independent_variable,
    const DependentTwoDDistribution& dependent_distribution )
{
  typename DependentTwoDDistribution::const_iterator lower_bin_boundary,
                                                     upper_bin_boundary;
  double interpolation_fraction;

  findLowerAndUpperBinBoundary<DependentTwoDDistribution,InterpolationPolicy>(
        independent_variable,
        dependent_distribution,
        lower_bin_boundary,
        upper_bin_boundary,
        interpolation_fraction );

  double random_number =
    Utility::RandomNumberGenerator::getRandomNumber<double>();

  if( lower_bin_boundary != upper_bin_boundary && random_number < interpolation_fraction )
  {
    return upper_bin_boundary->second->sample();
  }
  else
    return lower_bin_boundary->second->sample();
}


// Evaluate a correlated value from a two dimensional distribution
template<typename DependentTwoDDistribution, typename InterpolationPolicy>
double evaluateTwoDDistributionCorrelated(
    const double independent_variable,
    const double dependent_variable,
    const DependentTwoDDistribution& dependent_distribution )
{
  typename DependentTwoDDistribution::const_iterator lower_bin_boundary,
                                                     upper_bin_boundary;

  findLowerAndUpperBinBoundary<DependentTwoDDistribution,InterpolationPolicy>(
        independent_variable,
        dependent_distribution,
        lower_bin_boundary,
        upper_bin_boundary );

  if( lower_bin_boundary != upper_bin_boundary )
  {
    return InterpolationPolicy::interpolate(
            lower_bin_boundary->first,
            upper_bin_boundary->first,
            independent_variable,
            lower_bin_boundary->second->evaluate( dependent_variable ),
            upper_bin_boundary->second->evaluate( dependent_variable ) );
  }
  else
    return lower_bin_boundary->second->evaluate( dependent_variable );
}


// Evaluate a correlated PDF from a two dimensional distribution
template<typename DependentTwoDDistribution, typename InterpolationPolicy>
double evaluateTwoDDistributionCorrelatedPDF(
    const double independent_variable,
    const double dependent_variable,
    const DependentTwoDDistribution& dependent_distribution )
{
  typename DependentTwoDDistribution::const_iterator lower_bin_boundary,
                                                     upper_bin_boundary;

  findLowerAndUpperBinBoundary<DependentTwoDDistribution, InterpolationPolicy>(
        independent_variable,
        dependent_distribution,
        lower_bin_boundary,
        upper_bin_boundary );

  if( lower_bin_boundary != upper_bin_boundary )
  {
    return InterpolationPolicy::interpolate(
            lower_bin_boundary->first,
            upper_bin_boundary->first,
            independent_variable,
            lower_bin_boundary->second->evaluatePDF( dependent_variable ),
            upper_bin_boundary->second->evaluatePDF( dependent_variable ) );
  }
  else
    return lower_bin_boundary->second->evaluatePDF( dependent_variable );
}


// Evaluate a correlated CDF from a two dimensional distribution
template<typename DependentTwoDDistribution, typename InterpolationPolicy>
double evaluateTwoDDistributionCorrelatedCDF(
    const double independent_variable,
    const double dependent_variable,
    const DependentTwoDDistribution& dependent_distribution )
{
  typename DependentTwoDDistribution::const_iterator lower_bin_boundary,
                                                     upper_bin_boundary;

  findLowerAndUpperBinBoundary<DependentTwoDDistribution, InterpolationPolicy>(
        independent_variable,
        dependent_distribution,
        lower_bin_boundary,
        upper_bin_boundary );

  if( lower_bin_boundary != upper_bin_boundary )
  {
    return InterpolationPolicy::interpolate(
            lower_bin_boundary->first,
            upper_bin_boundary->first,
            independent_variable,
            lower_bin_boundary->second->evaluateCDF( dependent_variable ),
            upper_bin_boundary->second->evaluateCDF( dependent_variable ) );
  }
  else
    return lower_bin_boundary->second->evaluateCDF( dependent_variable );
}

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_TWO_D_DISTRIBUTION_HELPERS_DEF_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_TwoDDistributionHelpers_def.hpp
//---------------------------------------------------------------------------//
