//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_TwoDDistributionHelpers.hpp
//! \author Luke Kersting
//! \brief  Two dimensional distribution helpers base declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_TWO_D_DISTRIBUTION_HELPERS
#define MONTE_CARLO_TWO_D_DISTRIBUTION_HELPERS

// Trilinos Includse
#include <Teuchos_Array.hpp>

// FRENSIE Includes
#include "Utility_TabularOneDDistribution.hpp"
#include "Utility_RandomNumberGenerator.hpp"

namespace MonteCarlo{

//! Typedef for the two dimensional distribution
typedef Teuchos::Array<Utility::Pair<double,
                       Teuchos::RCP<const Utility::TabularOneDDistribution> > >
    TwoDDistribution;

//! Find the lower and upper bin boundary
template<typename DependentTwoDDistribution>
void findLowerAndUpperBinBoundary(
	const double independent_variable,
	const DependentTwoDDistribution& dependent_distribution,
	typename DependentTwoDDistribution::const_iterator& lower_bin_boundary,
	typename DependentTwoDDistribution::const_iterator& upper_bin_boundary,
	double& interpolation_fraction );

//! Sample a two dimensional distribution using correlated sampling
template<typename DependentTwoDDistribution>
double sampleTwoDDistributionCorrelated(
    const double independent_variable,
    const DependentTwoDDistribution& dependent_distribution );

//! Sample a two dimensional distribution with a random number using correlated sampling
template<typename DependentTwoDDistribution>
double sampleTwoDDistributionCorrelatedWithRandomNumber(
    const double independent_variable,
    const DependentTwoDDistribution& dependent_distribution,
    const double random_number );
/*
//! Sample a two dimensional distribution with a random number using correlated sampling
double sampleTwoDDistributionCorrelatedWithRandomNumber(
    const double independent_variable,
    const TwoDDistribution& dependent_distribution,
    const double random_number );
*/
//! Sample a two dimensional distribution using independent sampling
template<typename DependentTwoDDistribution>
double sampleTwoDDistributionIndependent(
    const double independent_variable,
    const DependentTwoDDistribution& dependent_distribution );

//! Evaluate a correlated value from a two dimensional distribution
template<typename DependentTwoDDistribution>
double evaluateTwoDDistributionCorrelated(
    const double independent_variable,
    const double dependent_variable,
    const DependentTwoDDistribution& dependent_distribution );

//! Evaluate a correlated PDF from a two dimensional distribution
template<typename DependentTwoDDistribution>
double evaluateTwoDDistributionCorrelatedPDF(
    const double independent_variable,
    const double dependent_variable,
    const DependentTwoDDistribution& dependent_distribution );

//! Evaluate a correlated CDF from a two dimensional distribution
template<typename DependentTwoDDistribution>
double evaluateTwoDDistributionCorrelatedCDF(
    const double independent_variable,
    const double dependent_variable,
    const DependentTwoDDistribution& dependent_distribution );
/*
//! Evaluate a correlated value from a two dimensional distribution
double evaluateTwoDDistributionCorrelated(
    const double independent_variable,
    const double dependent_variable,
    const TwoDDistribution& dependent_distribution );

//! Evaluate a correlated PDF from a two dimensional distribution
double evaluateTwoDDistributionCorrelatedPDF(
    const double independent_variable,
    const double dependent_variable,
    const TwoDDistribution& dependent_distribution );

//! Evaluate a correlated CDF from a two dimensional distribution
double evaluateTwoDDistributionCorrelatedCDF(
    const double independent_variable,
    const double dependent_variable,
    const TwoDDistribution& dependent_distribution );
*/
//! Sample an upper and lower distribution using a common random variable
template<typename DependentDistribution>
double correlatedSample(
    const Teuchos::RCP<const DependentDistribution>& upper_distribution,
	const Teuchos::RCP<const DependentDistribution>& lower_distribution,
	const double interpolation_fraction );


//! Sample an upper and lower distribution using a common given random variable
template<typename DependentDistribution>
double correlatedSampleWithRandomNumber(
    const Teuchos::RCP<const DependentDistribution>& upper_distribution,
	const Teuchos::RCP<const DependentDistribution>& lower_distribution,
	const double interpolation_fraction,
	const double random_number );
/*
//! Sample an upper and lower distribution using a common given random variable
double correlatedSampleWithRandomNumber(
            const Teuchos::RCP<const Utility::TabularOneDDistribution>&
		    upper_distribution,
		    const Teuchos::RCP<const Utility::TabularOneDDistribution>&
		    lower_distribution,
		    const double interpolation_fraction,
		    const double random_number );
*/
//! Sample an upper and lower distribution using a common random variable in a subrange
template<typename DependentDistribution>
double correlatedSampleInSubrange(
    const Teuchos::RCP<const DependentDistribution>& upper_distribution,
	const Teuchos::RCP<const DependentDistribution>& lower_distribution,
	const double interpolation_fraction,
	const double max_indep_var );

//! Evaluate a correlated value
template<typename DependentDistribution>
double evaluateCorrelated(
   const Teuchos::RCP<const DependentDistribution>& upper_distribution,
   const Teuchos::RCP<const DependentDistribution>& lower_distribution,
   const double interpolation_fraction,
   const double independent_value );

//! Evaluate a correlated pdf value
template<typename DependentDistribution>
double evaluateCorrelatedPDF(
    const Teuchos::RCP<const DependentDistribution>& upper_distribution,
    const Teuchos::RCP<const DependentDistribution>& lower_distribution,
    const double interpolation_fraction,
    const double independent_value );

//! Evaluate a correlated cdf value
template<typename DependentDistribution>
double evaluateCorrelatedCDF(
	const Teuchos::RCP<const DependentDistribution>& upper_distribution,
	const Teuchos::RCP<const DependentDistribution>& lower_distribution,
	const double interpolation_fraction,
	const double independent_value );
/*
//! Evaluate a correlated value
double evaluateCorrelated(
   const Teuchos::RCP<const Utility::OneDDistribution>& upper_distribution,
   const Teuchos::RCP<const Utility::OneDDistribution>& lower_distribution,
   const double interpolation_fraction,
   const double independent_value );
*/
//! Sample from either the lower or upper distribution depending on interp frac
template<typename DependentDistribution>
double independentSample(
    const Teuchos::RCP<const DependentDistribution>& upper_distribution,
    const Teuchos::RCP<const DependentDistribution>& lower_distribution,
	const double interpolation_fraction );

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
