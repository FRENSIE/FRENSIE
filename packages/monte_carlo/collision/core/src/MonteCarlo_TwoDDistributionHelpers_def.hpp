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

// Return the primary grid values of the 2-D distribution
template<typename DependentTwoDDistribution>
void getPrimaryGrid(
	const DependentTwoDDistribution& dependent_distribution,
  std::vector<double>& primary_grid )
{
  primary_grid.resize( dependent_distribution.size() );

  for ( unsigned i = 0; i < dependent_distribution.size(); ++i )
  {
    primary_grid[i] = Utility::get<0>( dependent_distribution[i] );
  }
}

// Find the lower and upper bin boundary
template<typename DependentTwoDDistribution>
void findLowerAndUpperBinIndex(
    const double independent_variable,
	const DependentTwoDDistribution& dependent_distribution,
    unsigned& lower_bin_index,
    unsigned& upper_bin_index )
{
  if( independent_variable < Utility::get<0>( dependent_distribution.front() ))
  {
    lower_bin_index = 0;
    upper_bin_index = lower_bin_index;
  }
  else if( independent_variable >= Utility::get<0>( dependent_distribution.back() ) )
  {
    lower_bin_index = dependent_distribution.size();
    --lower_bin_index;
    upper_bin_index = lower_bin_index;
  }
  else
  {
    typename DependentTwoDDistribution::const_iterator
        lower_bin_boundary, upper_bin_boundary;
    lower_bin_boundary = dependent_distribution.begin();
    upper_bin_boundary = dependent_distribution.end();

    lower_bin_index = Utility::Search::binaryLowerBoundIndex<Utility::FIRST>(
							lower_bin_boundary,
							upper_bin_boundary,
							independent_variable );
    upper_bin_index = lower_bin_index;
    
    if( Utility::get<0>( dependent_distribution[lower_bin_index] ) != independent_variable )
      ++upper_bin_index;
  }
}

// Find the lower and upper bin boundary
template<typename DependentTwoDDistribution>
void findLowerAndUpperBinBoundary(
    const double independent_variable,
	const DependentTwoDDistribution& dependent_distribution,
    typename DependentTwoDDistribution::const_iterator& lower_bin_boundary,
    typename DependentTwoDDistribution::const_iterator& upper_bin_boundary )
{
  if( independent_variable < Utility::get<0>( dependent_distribution.front() ) )
  {
    lower_bin_boundary = dependent_distribution.begin();
    upper_bin_boundary = lower_bin_boundary;
  }
  else if( independent_variable >= Utility::get<0>( dependent_distribution.back() ) )
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
    
    if ( Utility::get<0>( *lower_bin_boundary ) != independent_variable )
      ++upper_bin_boundary;
  }
}

// Find the lower and upper bin boundary
template<typename DependentTwoDDistribution>
void findLowerAndUpperBinBoundary(
    const double independent_variable,
	const DependentTwoDDistribution& dependent_distribution,
    typename DependentTwoDDistribution::const_iterator& lower_bin_boundary,
    typename DependentTwoDDistribution::const_iterator& upper_bin_boundary,
    double& interpolation_fraction )
{

  findLowerAndUpperBinBoundary( independent_variable,
                                dependent_distribution,
                                lower_bin_boundary,
                                upper_bin_boundary );
  
  if( independent_variable < Utility::get<0>( dependent_distribution.front() ) )
  {
    interpolation_fraction = 0.0;
  }
  else if( independent_variable >= Utility::get<0>( dependent_distribution.back() ) )
  {
    interpolation_fraction = 0.0;
  }
  else
  {
    // Calculate the interpolation fraction
    interpolation_fraction =
      (independent_variable - Utility::get<0>( *lower_bin_boundary ))/
      (Utility::get<0>( *upper_bin_boundary ) - Utility::get<0>( *lower_bin_boundary));
  }
}

// Sample a two dimensional distribution with a random number
template<typename DependentTwoDDistribution, typename InterpolationPolicy>
double sampleTwoDDistributionCorrelatedWithRandomNumber(
   const double independent_variable,
   const DependentTwoDDistribution& dependent_distribution,
   const double random_number )
{
  typename DependentTwoDDistribution::const_iterator lower_bin_boundary,
                                                     upper_bin_boundary;

  findLowerAndUpperBinBoundary<DependentTwoDDistribution>(
        independent_variable,
        dependent_distribution,
        lower_bin_boundary,
        upper_bin_boundary );

  if( lower_bin_boundary != upper_bin_boundary )
  {
    return InterpolationPolicy::interpolate(
        Utility::get<0>( *lower_bin_boundary ),
        Utility::get<0>( *upper_bin_boundary ),
        independent_variable,
        Utility::get<1>( *lower_bin_boundary )->sampleWithRandomNumber( random_number ),
        Utility::get<1>( *upper_bin_boundary )->sampleWithRandomNumber( random_number ) );
  }
  else
    return Utility::get<1>( *lower_bin_boundary )->sampleWithRandomNumber( random_number );
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

  findLowerAndUpperBinBoundary<DependentTwoDDistribution>(
        independent_variable,
        dependent_distribution,
        lower_bin_boundary,
        upper_bin_boundary);

  if( lower_bin_boundary != upper_bin_boundary )
  {
    return InterpolationPolicy::interpolate(
              Utility::get<0>( *lower_bin_boundary ),
              Utility::get<0>( *upper_bin_boundary ),
              independent_variable,
              Utility::get<1>( *lower_bin_boundary )->sampleWithRandomNumberInSubrange( random_number, max_indep_var ),
              Utility::get<1>( *upper_bin_boundary )->sampleWithRandomNumberInSubrange( random_number, max_indep_var ) );
  }
  else
  {
    return Utility::get<1>( *upper_bin_boundary )->sampleInSubrange( max_indep_var );
  }
}


// Sample a two dimensional distribution
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

  findLowerAndUpperBinBoundary<DependentTwoDDistribution>(
        independent_variable,
        dependent_distribution,
        lower_bin_boundary,
        upper_bin_boundary,
        interpolation_fraction );

  double random_number =
    Utility::RandomNumberGenerator::getRandomNumber<double>();

  if( lower_bin_boundary != upper_bin_boundary && random_number < interpolation_fraction )
  {
    return Utility::get<1>( *upper_bin_boundary )->sample();
  }
  else
    return Utility::get<1>( *lower_bin_boundary )->sample();
}

//! Sample continuously across multiple two dimensional distribution bins
template<typename DependentTwoDDistributionA, typename DependentTwoDDistributionB >
double sampleContinuouslyAcrossDistributions(
    const typename DependentTwoDDistributionA::const_iterator& distribution_a_bin,
    const typename DependentTwoDDistributionB::const_iterator& distribution_b_bin,
    const double& cross_section_a,
    const double& cross_section_b,
    const double& random_number,
    double& scattering_angle_cosine )
{
  // Get the total cross section
  double total_cross_section =
     cross_section_a + cross_section_b;

  // Scale the random number
  double scaled_random_number = total_cross_section*random_number;

  if ( scaled_random_number < cross_section_a )
  {
    scaled_random_number /= cross_section_a;

    scattering_angle_cosine =
      Utility::get<1>( *distribution_a_bin )->sampleWithRandomNumber(
                                                        scaled_random_number );
  }
  else
  {
    scaled_random_number =
        ( scaled_random_number - cross_section_a )/cross_section_b;

    scattering_angle_cosine =
      Utility::get<1>( *distribution_b_bin )->sampleWithRandomNumber(
                                                        scaled_random_number );
  }
}

//! Sample continuously across multiple two dimensional distribution using correlated sampling
template<typename DependentTwoDDistributionA,
         typename DependentTwoDDistributionB,
         typename InterpolationPolicy >
double sampleContinuouslyAcrossDistributions(
    const typename DependentTwoDDistributionA::const_iterator& distribution_a_lower_bin,
    const typename DependentTwoDDistributionA::const_iterator& distribution_a_upper_bin,
    const typename DependentTwoDDistributionB::const_iterator& distribution_b_lower_bin,
    const typename DependentTwoDDistributionB::const_iterator& distribution_b_upper_bin,
    const double& lower_cross_section_a,
    const double& upper_cross_section_a,
    const double& lower_cross_section_b,
    const double& upper_cross_section_b,
    const double& independent_variable,
    double& scattering_angle_cosine )
{
  double lower_angle_cosine, upper_angle_cosine;

  double random_number =
    Utility::RandomNumberGenerator::getRandomNumber<double>();

  // sample lower bins
  sampleContinuouslyAcrossDistributions<DependentTwoDDistributionA, DependentTwoDDistributionB >(
    distribution_a_lower_bin,
    distribution_b_lower_bin,
    lower_cross_section_a,
    lower_cross_section_b,
    random_number,
    lower_angle_cosine );

  // sample upper bins
  sampleContinuouslyAcrossDistributions<DependentTwoDDistributionA, DependentTwoDDistributionB >(
    distribution_a_upper_bin,
    distribution_b_upper_bin,
    upper_cross_section_a,
    upper_cross_section_b,
    random_number,
    upper_angle_cosine );

    return InterpolationPolicy::interpolate(
                                  Utility::get<0>( *distribution_a_lower_bin ),
                                  Utility::get<0>( *distribution_a_upper_bin ),
                                  independent_variable,
                                  lower_angle_cosine,
                                  upper_angle_cosine );

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

  findLowerAndUpperBinBoundary<DependentTwoDDistribution>(
        independent_variable,
        dependent_distribution,
        lower_bin_boundary,
        upper_bin_boundary );

  if( lower_bin_boundary != upper_bin_boundary )
  {
    return InterpolationPolicy::interpolate(
        Utility::get<0>( *lower_bin_boundary ),
        Utility::get<0>( *upper_bin_boundary ),
        independent_variable,
        Utility::get<1>( *lower_bin_boundary )->evaluate( dependent_variable ),
        Utility::get<1>( *upper_bin_boundary )->evaluate( dependent_variable ) );
  }
  else
    return Utility::get<1>( *lower_bin_boundary )->evaluate( dependent_variable );
}

// Evaluate a correlated value from a two dimensional distribution
template<typename DependentTwoDDistribution, typename InterpolationPolicy>
double evaluateTwoDDistributionCorrelated(
    const unsigned lower_bin_index,
    const double independent_variable,
    const double dependent_variable,
    const DependentTwoDDistribution& dependent_distribution )
{
  // Make sure the lower_bin_index is valid
  testPrecondition( lower_bin_index >= 0 );
  testPrecondition( lower_bin_index < dependent_distribution.size() );

  if( dependent_distribution[lower_bin_index].first != independent_variable )
  {
    return InterpolationPolicy::interpolate(
            dependent_distribution[lower_bin_index].first,
            dependent_distribution[lower_bin_index+1].first,
            independent_variable,
            dependent_distribution[lower_bin_index].second->evaluate( dependent_variable ),
            dependent_distribution[lower_bin_index+1].second->evaluate( dependent_variable ) );
  }
  else
    return dependent_distribution[lower_bin_index].second->evaluate( dependent_variable );
}

// Evaluate a correlated value from a two dimensional distribution
template<typename DependentTwoDDistribution, typename InterpolationPolicy>
double evaluateTwoDDistributionCorrelatedWithWeightedVariable(
    const double independent_variable,
    const double weighted_dependent_variable,
    const DependentTwoDDistribution& dependent_distribution )
{
  typename DependentTwoDDistribution::const_iterator lower_bin_boundary,
                                                     upper_bin_boundary;

  findLowerAndUpperBinBoundary<DependentTwoDDistribution>(
        independent_variable,
        dependent_distribution,
        lower_bin_boundary,
        upper_bin_boundary );

  double lower_dependent_variable = weighted_dependent_variable*
      lower_bin_boundary->second->getUpperBoundOfIndepVar();

  if( lower_bin_boundary != upper_bin_boundary )
  {
    double upper_dependent_variable = weighted_dependent_variable*
      upper_bin_boundary->second->getUpperBoundOfIndepVar();

    return InterpolationPolicy::interpolate(
            lower_bin_boundary->first,
            upper_bin_boundary->first,
            independent_variable,
            lower_bin_boundary->second->evaluate( lower_dependent_variable ),
            upper_bin_boundary->second->evaluate( upper_dependent_variable ) );
  }
  else
    return lower_bin_boundary->second->evaluate( lower_dependent_variable );
}

// Evaluate a correlated value from a two dimensional distribution
template<typename DependentTwoDDistribution, typename InterpolationPolicy>
double evaluateTwoDDistributionCorrelatedWithWeightedVariable(
    const unsigned lower_bin_index,
    const double independent_variable,
    const double weighted_dependent_variable,
    const DependentTwoDDistribution& dependent_distribution )
{
  // Make sure the lower_bin_index is valid
  testPrecondition( lower_bin_index >= 0 );
  testPrecondition( lower_bin_index < dependent_distribution.size() );

  double lower_dependent_variable = weighted_dependent_variable*
      dependent_distribution[lower_bin_index].second->getUpperBoundOfIndepVar();

  if( dependent_distribution[lower_bin_index].first != independent_variable )
  {
    double upper_dependent_variable = weighted_dependent_variable*
      dependent_distribution[lower_bin_index+1].second->getUpperBoundOfIndepVar();

    return InterpolationPolicy::interpolate(
            dependent_distribution[lower_bin_index].first,
            dependent_distribution[lower_bin_index+1].first,
            independent_variable,
            dependent_distribution[lower_bin_index].second->evaluate( lower_dependent_variable ),
            dependent_distribution[lower_bin_index+1].second->evaluate( upper_dependent_variable ) );
  }
  else
    return dependent_distribution[lower_bin_index].second->evaluate( lower_dependent_variable );
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

  findLowerAndUpperBinBoundary<DependentTwoDDistribution>(
        independent_variable,
        dependent_distribution,
        lower_bin_boundary,
        upper_bin_boundary );

  if( lower_bin_boundary != upper_bin_boundary )
  {
    return InterpolationPolicy::interpolate(
     Utility::get<0>( *lower_bin_boundary ),
     Utility::get<0>( *upper_bin_boundary ),
     independent_variable,
     Utility::get<1>( *lower_bin_boundary )->evaluatePDF( dependent_variable ),
     Utility::get<1>( *upper_bin_boundary )->evaluatePDF( dependent_variable ) );
  }
  else
    return Utility::get<1>( *lower_bin_boundary )->evaluatePDF( dependent_variable );
}

// Evaluate a correlated PDF from a two dimensional distribution
template<typename DependentTwoDDistribution, typename InterpolationPolicy>
double evaluateTwoDDistributionCorrelatedPDF(
    const unsigned lower_bin_index,
    const double independent_variable,
    const double dependent_variable,
    const DependentTwoDDistribution& dependent_distribution )
{
  // Make sure the lower_bin_index is valid
  testPrecondition( lower_bin_index >= 0 );
  testPrecondition( lower_bin_index < dependent_distribution.size() );

  if( Utility::get<0>( dependent_distribution[lower_bin_index] ) != independent_variable )
  {
    return InterpolationPolicy::interpolate(
              Utility::get<0>( dependent_distribution[lower_bin_index] ),
              Utility::get<0>( dependent_distribution[lower_bin_index+1] ),
              independent_variable,
              Utility::get<1>( dependent_distribution[lower_bin_index] )->evaluatePDF( dependent_variable ),
              Utility::get<1>( dependent_distribution[lower_bin_index+1] )->evaluatePDF( dependent_variable ) );
  }
  else
    return Utility::get<1>( dependent_distribution[lower_bin_index] )->evaluatePDF( dependent_variable );
}

// Evaluate a correlated PDF from a two dimensional distribution
template<typename DependentTwoDDistribution, typename InterpolationPolicy>
double evaluateTwoDDistributionCorrelatedPDFWithWeightedVariable(
    const double independent_variable,
    const double weighted_dependent_variable,
    const DependentTwoDDistribution& dependent_distribution )
{
  // Make sure the weighted dependent variable is valid
  testPrecondition( weighted_dependent_variable <= 1.0 );

  typename DependentTwoDDistribution::const_iterator lower_bin_boundary,
                                                     upper_bin_boundary;

  findLowerAndUpperBinBoundary<DependentTwoDDistribution>(
        independent_variable,
        dependent_distribution,
        lower_bin_boundary,
        upper_bin_boundary );

  double lower_dependent_variable = weighted_dependent_variable*
      lower_bin_boundary->second->getUpperBoundOfIndepVar();

  if( lower_bin_boundary != upper_bin_boundary )
  {
    double upper_dependent_variable = weighted_dependent_variable*
      upper_bin_boundary->second->getUpperBoundOfIndepVar();

    return InterpolationPolicy::interpolate(
            lower_bin_boundary->first,
            upper_bin_boundary->first,
            independent_variable,
            lower_bin_boundary->second->evaluatePDF( lower_dependent_variable ),
            upper_bin_boundary->second->evaluatePDF( upper_dependent_variable ) );
  }
  else
    return lower_bin_boundary->second->evaluatePDF( lower_dependent_variable );
}

// Evaluate a correlated PDF from a two dimensional distribution
template<typename DependentTwoDDistribution, typename InterpolationPolicy>
double evaluateTwoDDistributionCorrelatedPDFWithWeightedVariable(
    const unsigned lower_bin_index,
    const double independent_variable,
    const double weighted_dependent_variable,
    const DependentTwoDDistribution& dependent_distribution )
{
  // Make sure the lower_bin_index is valid
  testPrecondition( lower_bin_index >= 0 );
  testPrecondition( lower_bin_index < dependent_distribution.size() );
  // Make sure the weighted dependent variable is valid
  testPrecondition( weighted_dependent_variable <= 1.0 );

  double lower_dependent_variable = weighted_dependent_variable*
      dependent_distribution[lower_bin_index].second->getUpperBoundOfIndepVar();

  if( dependent_distribution[lower_bin_index].first != independent_variable )
  {
    double upper_dependent_variable = weighted_dependent_variable*
      dependent_distribution[lower_bin_index+1].second->getUpperBoundOfIndepVar();

    return InterpolationPolicy::interpolate(
            dependent_distribution[lower_bin_index].first,
            dependent_distribution[lower_bin_index+1].first,
            independent_variable,
            dependent_distribution[lower_bin_index].second->evaluatePDF( lower_dependent_variable ),
            dependent_distribution[lower_bin_index+1].second->evaluatePDF( upper_dependent_variable ) );
  }
  else
    return dependent_distribution[lower_bin_index].second->evaluatePDF( lower_dependent_variable );
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

  findLowerAndUpperBinBoundary<DependentTwoDDistribution>(
        independent_variable,
        dependent_distribution,
        lower_bin_boundary,
        upper_bin_boundary );

  if( lower_bin_boundary != upper_bin_boundary )
  {
    return InterpolationPolicy::interpolate(
     Utility::get<0>( *lower_bin_boundary ),
     Utility::get<0>( *upper_bin_boundary ),
     independent_variable,
     Utility::get<1>( *lower_bin_boundary )->evaluateCDF( dependent_variable ),
     Utility::get<1>( *upper_bin_boundary )->evaluateCDF( dependent_variable ) );
  }
  else
    return Utility::get<1>( *lower_bin_boundary )->evaluateCDF( dependent_variable );
}

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_TWO_D_DISTRIBUTION_HELPERS_DEF_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_TwoDDistributionHelpers_def.hpp
//---------------------------------------------------------------------------//
