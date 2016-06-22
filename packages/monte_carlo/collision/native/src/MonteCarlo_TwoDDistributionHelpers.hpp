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
#include "Utility_TabularOneDDistribution.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_InterpolationPolicy.hpp"

namespace MonteCarlo{

//! Typedef for the  bremsstrahlung distribution 
typedef Teuchos::Array<Utility::Pair<double, 
                       Teuchos::RCP<const Utility::TabularOneDDistribution> > > 
TwoDDistribution; 


//! Find the lower and upper bin boundary
template<typename DependentTwoDDistribution,
         typename InterpolationPolicy = Utility::LinLin>
void findLowerAndUpperBinBoundary(
	const double independent_variable,
	const DependentTwoDDistribution& dependent_distribution,
	typename DependentTwoDDistribution::const_iterator& lower_bin_boundary,
	typename DependentTwoDDistribution::const_iterator& upper_bin_boundary,
	double& interpolation_fraction );

//! Find the lower and upper bin boundary
template<typename DependentTwoDDistribution,
         typename InterpolationPolicy = Utility::LinLin>
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

//! Evaluate a correlated value from a two dimensional distribution
template<typename DependentTwoDDistribution,
         typename InterpolationPolicy = Utility::LinLin>
double evaluateTwoDDistributionCorrelated(
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

//! Evaluate a correlated CDF from a two dimensional distribution
template<typename DependentTwoDDistribution,
         typename InterpolationPolicy = Utility::LinLin>
double evaluateTwoDDistributionCorrelatedCDF(
    const double independent_variable,
    const double dependent_variable,
    const DependentTwoDDistribution& dependent_distribution );

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// Template inludes.
//---------------------------------------------------------------------------//

#include "MonteCarlo_TwoDDistributionHelpers_def.hpp"

//---------------------------------------------------------------------------//

#endif // end MONTE_CARLO_TWO_D_DISTRIBUTION_HELPERS

//---------------------------------------------------------------------------//
// end MonteCarlo_TwoDDistributionHelpers.hpp
//---------------------------------------------------------------------------//
