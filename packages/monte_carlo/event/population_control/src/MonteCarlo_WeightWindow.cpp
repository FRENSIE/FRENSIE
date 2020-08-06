//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_WeightWindowMesh.cpp
//! \author Philip Britt
//! \brief  Weight window mesh class definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_WeightWindow.hpp"
#include "Utility_ExceptionTestMacros.hpp"

namespace MonteCarlo{

// Update the particle state and bank
void WeightWindow::checkParticleWithPopulationController( ParticleState& particle,
                                                          ParticleBank& bank ) const
{
  double weight = particle.getWeight();
}


} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_WeightWindowMesh.cpp
//---------------------------------------------------------------------------//