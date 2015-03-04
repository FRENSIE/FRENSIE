//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ParticleScatteringEnergyDistribution.cpp
//! \author Alex Robinson, Alex Bennett
//! \brief  The neutron scattering energy distribution base class declaration
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_ParticleScatteringEnergyDistribution.hpp"

namespace MonteCarlo{

// Constructor
ParticleScatteringEnergyDistribution::ParticleScatteringEnergyDistribution( 
						      const unsigned law )
  : d_law( law )
{ /* ... */ }

// Return the scattering law
unsigned ParticleScatteringEnergyDistribution::getLaw() const
{
  return d_law;
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_ParticleScatteringEnergyDistribution.cpp
//---------------------------------------------------------------------------//
