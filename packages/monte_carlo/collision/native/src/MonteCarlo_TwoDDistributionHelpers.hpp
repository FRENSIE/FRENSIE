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


  /*! Sample a two dimensional ditribution consisting of an array pair of double 
   *  and OneDDistribution
   */ 
double sampleTwoDDistribution( const double independent_variable,
    const Teuchos::Array<Utility::Pair<double,
    Teuchos::RCP<Utility::OneDDistribution> > >& dependent_distribution );



} // end MonteCarlo namespace

#endif // end MONTE_CARLO_TWO_D_DISTRIBUTION_HELPERS

//---------------------------------------------------------------------------//
// end MonteCarlo_TwoDDistributionHelpers.hpp
//---------------------------------------------------------------------------//
