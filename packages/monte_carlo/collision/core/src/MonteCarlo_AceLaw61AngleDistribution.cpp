//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_AceLaw61AngleDistribution.cpp
//! \author Eli Moll
//! \brief  The law 61 angle distribution class definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_AceLaw61AngleDistribution.hpp"

namespace MonteCarlo{

// Constructor
AceLaw61AngleDistribution::AceLaw61AngleDistribution( 
    const Utility::ArrayView<const double>& outgoing_energy_grid,
    const std::vector<std::shared_ptr<const Utility::UnivariateDistribution> >&
    cosine_distributions )
  : d_outgoing_energy_grid( outgoing_energy_grid.begin(),
                            outgoing_energy_grid.end() ),
    d_cosine_distributions( cosine_distributions )
{
  // Make sure the arrays have the same size
  testPrecondition( outgoing_energy_grid.size() > 0 );
  testPrecondition( outgoing_energy_grid.size() == cosine_distributions.size() );
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_AceLaw61AngleDistribution.cpp
//---------------------------------------------------------------------------//
