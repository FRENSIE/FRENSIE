//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_TwoDDistributionHelpers.hpp
//! \author Luke Kersting
//! \brief  Two dimensional distribution helpers base class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_TWO_D_DISTRIBUTION_HELPERS
#define MONTE_CARLO_TWO_D_DISTRIBUTION_HELPERS

// Trilinos Includse
#include <Teuchos_Array.hpp>

// FRENSIE Includes
#include "Utility_OneDDistribution.hpp"
#include "Utility_RandomNumberGenerator.hpp"

namespace MonteCarlo{

//! Typedef for the  bremsstrahlung distribution
typedef Teuchos::Array<Utility::Pair<double,
                       Teuchos::RCP<const Utility::OneDDistribution> > >
TwoDDistribution;

//! Sample a two dimensional distribution using correlated sampling 
double sampleTwoDDistributionCorrelated( 
    const double independent_variable,
    const TwoDDistribution& dependent_distribution );

//! Sample a two dimensional distribution using independent sampling
double sampleTwoDDistributionIndependent(
    const double independent_variable,
    const TwoDDistribution& dependent_distribution );

//! Sample an upper and lower distribution using a common random variable
double correlatedSample(
   const Teuchos::RCP<const Utility::OneDDistribution>& upper_distribution,
   const Teuchos::RCP<const Utility::OneDDistribution>& lower_distribution,
   const double interpolation_fraction );

//! Sample an upper and lower distribution using a common random variable in a subrange
double correlatedSample(
   const Teuchos::RCP<const Utility::OneDDistribution>& upper_distribution,
   const Teuchos::RCP<const Utility::OneDDistribution>& lower_distribution,
   const double interpolation_fraction,
   const double max_indep_var );

//! Evaluate a correlated cdf value
double evaluateCorrelatedCDF(
   const Teuchos::RCP<const Utility::OneDDistribution>& upper_distribution,
   const Teuchos::RCP<const Utility::OneDDistribution>& lower_distribution,
   const double interpolation_fraction,
   const double independent_value );

//! Sample from either the lower or upper distribution depending on interp frac
double independentSample(
   const Teuchos::RCP<const Utility::OneDDistribution>& upper_distribution,
   const Teuchos::RCP<const Utility::OneDDistribution>& lower_distribution,
   const double interpolation_fraction );

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_TWO_D_DISTRIBUTION_HELPERS

//---------------------------------------------------------------------------//
// end MonteCarlo_TwoDDistributionHelpers.hpp
//---------------------------------------------------------------------------//
