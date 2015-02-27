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

/*! Sample a two dimensional ditribution consisting of an array pair of double 
 *  and OneDDistribution
 */ 
double sampleTwoDDistribution( 
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
   const double cutoff_cdf );

//! Evaluate a correlated cdf value
double evaluateCorrelatedCDF(
 			   const Teuchos::RCP<const Utility::OneDDistribution>&
			     upper_elastic_scattering_distribution,
 			   const Teuchos::RCP<const Utility::OneDDistribution>&
			     lower_elastic_scattering_distribution,
			   const double interpolation_fraction,
               const double independent_value );

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_TWO_D_DISTRIBUTION_HELPERS

//---------------------------------------------------------------------------//
// end MonteCarlo_TwoDDistributionHelpers.hpp
//---------------------------------------------------------------------------//
