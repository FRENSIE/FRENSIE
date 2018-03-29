//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_CoherentScatteringDistributionFactory.cpp
//! \author Alex Robinson
//! \brief  The coherent scattering distribution factory base class def.
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_CoherentScatteringDistributionFactory.hpp"
#include "MonteCarlo_ThompsonScatteringDistribution.hpp"

namespace MonteCarlo{

// Initialize the static member data
std::shared_ptr<const CoherentScatteringDistribution>
CoherentScatteringDistributionFactory::s_thompson_distribution(
				        new ThompsonScatteringDistribution() );

// Create a Thompson distribution
void CoherentScatteringDistributionFactory::createThompsonDistribution(
                         std::shared_ptr<const CoherentScatteringDistribution>&
                         coherent_distribution )
{
  coherent_distribution = s_thompson_distribution;
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_CoherentScatteringDistributionFactory.cpp
//---------------------------------------------------------------------------//
