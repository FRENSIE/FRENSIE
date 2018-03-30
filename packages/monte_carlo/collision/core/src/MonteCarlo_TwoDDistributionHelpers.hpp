//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_TwoDDistributionHelpers.hpp
//! \author Luke Kersting
//! \brief  Two dimensional distribution helpers base declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_TWO_D_DISTRIBUTION_HELPERS
#define MONTE_CARLO_TWO_D_DISTRIBUTION_HELPERS

// FRENSIE Includes
#include "Utility_TabularUnivariateDistribution.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_InterpolationPolicy.hpp"
#include "Utility_Tuple.hpp"

namespace MonteCarlo{

//! Typedef for a 2-D distribution
typedef std::vector<std::pair<double,std::shared_ptr<const Utility::TabularUnivariateDistribution> > >
TwoDDistribution;

//! Return the primary grid values of the 2-D distribution
template<typename DependentTwoDDistribution>
void getPrimaryGrid(
	const DependentTwoDDistribution& dependent_distribution,
  std::vector<double>& primary_grid );

//! Find the lower and upper bin boundary
template<typename DependentTwoDDistribution>
void findLowerAndUpperBinIndex(
    const double independent_variable,
	const DependentTwoDDistribution& dependent_distribution,
    unsigned& lower_bin_index,
    unsigned& upper_bin_index );

//! Find the lower and upper bin boundary
template<typename DependentTwoDDistribution>
void findLowerAndUpperBinBoundary(
	const double independent_variable,
	const DependentTwoDDistribution& dependent_distribution,
	typename DependentTwoDDistribution::const_iterator& lower_bin_boundary,
	typename DependentTwoDDistribution::const_iterator& upper_bin_boundary,
	double& interpolation_fraction );

//! Find the lower and upper bin boundary
template<typename DependentTwoDDistribution>
void findLowerAndUpperBinBoundary(
	const double independent_variable,
	const DependentTwoDDistribution& dependent_distribution,
	typename DependentTwoDDistribution::const_iterator& lower_bin_boundary,
	typename DependentTwoDDistribution::const_iterator& upper_bin_boundary );

//! Sample a two dimensional distribution using correlated sampling
template<typename DependentTwoDDistribution,
         typename InterpolationPolicy = Utility::LinLin>
double sampleTwoDDistributionCorrelated(
    const double independent_variable,
    const DependentTwoDDistribution& dependent_distribution );

//! Sample a two dimensional distribution with a random number using correlated sampling
template<typename DependentTwoDDistribution,
         typename InterpolationPolicy = Utility::LinLin>
double sampleTwoDDistributionCorrelatedWithRandomNumber(
    const double independent_variable,
    const DependentTwoDDistribution& dependent_distribution,
    const double random_number );

//! Sample a two dimensional distribution in a subrange using correlated sampling
template<typename DependentTwoDDistribution,
         typename InterpolationPolicy = Utility::LinLin>
double sampleTwoDDistributionCorrelatedInSubrange(
    const double independent_variable,
    const DependentTwoDDistribution& dependent_distribution,
	const double max_indep_var );

//! Sample a two dimensional distribution using independent sampling
template<typename DependentTwoDDistribution,
         typename InterpolationPolicy = Utility::LinLin>
double sampleTwoDDistributionIndependent(
    const double independent_variable,
    const DependentTwoDDistribution& dependent_distribution );

//! Sample continuously across multiple two dimensional distribution bins
template<typename DependentTwoDDistributionA, typename DependentTwoDDistributionB>
double sampleContinuouslyAcrossDistributions(
    const typename DependentTwoDDistributionA::const_iterator& distribution_a_bin,
    const typename DependentTwoDDistributionB::const_iterator& distribution_b_bin,
    const double& cross_section_a,
    const double& cross_section_b,
    const double& random_number,
    double& scattering_angle_cosine );

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
    double& scattering_angle_cosine );

//! Evaluate a correlated value from a two dimensional distribution
template<typename DependentTwoDDistribution,
         typename InterpolationPolicy = Utility::LinLin>
double evaluateTwoDDistributionCorrelated(
    const double independent_variable,
    const double dependent_variable,
    const DependentTwoDDistribution& dependent_distribution );

//! Evaluate a correlated from a two dimensional distribution
template<typename DependentTwoDDistribution,
         typename InterpolationPolicy = Utility::LinLin>
double evaluateTwoDDistributionCorrelated(
    const unsigned lower_bin_index,
    const double independent_variable,
    const double dependent_variable,
    const DependentTwoDDistribution& dependent_distribution );

//! Evaluate a correlated value from a two dimensional distribution with a fractionally weighted dependent variable
template<typename DependentTwoDDistribution,
         typename InterpolationPolicy = Utility::LinLin>
double evaluateTwoDDistributionCorrelatedWithWeightedVariable(
    const double independent_variable,
    const double dependent_variable,
    const DependentTwoDDistribution& dependent_distribution );

//! Evaluate a correlated from a two dimensional distribution with a fractionally weighted dependent variable
template<typename DependentTwoDDistribution,
         typename InterpolationPolicy = Utility::LinLin>
double evaluateTwoDDistributionCorrelatedWithWeightedVariable(
    const unsigned lower_bin_index,
    const double independent_variable,
    const double dependent_variable,
    const DependentTwoDDistribution& dependent_distribution );

//! Evaluate a correlated PDF from a two dimensional distribution
template<typename DependentTwoDDistribution,
         typename InterpolationPolicy = Utility::LinLin>
double evaluateTwoDDistributionCorrelatedPDF(
    const double independent_variable,
    const double dependent_variable,
    const DependentTwoDDistribution& dependent_distribution );

//! Evaluate a correlated PDF from a two dimensional distribution
template<typename DependentTwoDDistribution,
         typename InterpolationPolicy = Utility::LinLin>
double evaluateTwoDDistributionCorrelatedPDF(
    const unsigned lower_bin_index,
    const double independent_variable,
    const double dependent_variable,
    const DependentTwoDDistribution& dependent_distribution );

//! Evaluate a correlated PDF from a two dimensional distribution with a fractionally weighted dependent variable
template<typename DependentTwoDDistribution,
         typename InterpolationPolicy = Utility::LinLin>
double evaluateTwoDDistributionCorrelatedPDFWithWeightedVariable(
    const double independent_variable,
    const double weighted_dependent_variable,
    const DependentTwoDDistribution& dependent_distribution );

//! Evaluate a correlated PDF from a two dimensional distribution with a fractionally weighted dependent variable
template<typename DependentTwoDDistribution,
         typename InterpolationPolicy = Utility::LinLin>
double evaluateTwoDDistributionCorrelatedPDFWithWeightedVariable(
    const unsigned lower_bin_index,
    const double independent_variable,
    const double weighted_dependent_variable,
    const DependentTwoDDistribution& dependent_distribution );

//! Evaluate a correlated CDF from a two dimensional distribution
template<typename DependentTwoDDistribution,
         typename InterpolationPolicy = Utility::LinLin>
double evaluateTwoDDistributionCorrelatedCDF(
    const double independent_variable,
    const double dependent_variable,
    const DependentTwoDDistribution& dependent_distribution );

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// Template includes.
//---------------------------------------------------------------------------//

#include "MonteCarlo_TwoDDistributionHelpers_def.hpp"

//---------------------------------------------------------------------------//

#endif // end MONTE_CARLO_TWO_D_DISTRIBUTION_HELPERS

//---------------------------------------------------------------------------//
// end MonteCarlo_TwoDDistributionHelpers.hpp
//---------------------------------------------------------------------------//
