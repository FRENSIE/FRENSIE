//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_NuclearScatteringEnergyDistribution.cpp
//! \author Alex Robinson, Alex Bennett
//! \brief  The neutron scattering energy distribution base class declaration
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_NuclearScatteringEnergyDistribution.hpp"

namespace MonteCarlo{

// Constructor
NuclearScatteringEnergyDistribution::NuclearScatteringEnergyDistribution(
						      const unsigned law )
  : d_law( law )
{ /* ... */ }

// Return the scattering law
unsigned NuclearScatteringEnergyDistribution::getLaw() const
{
  return d_law;
}

void NuclearScatteringEnergyDistribution::getDistribution()
{
  
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_NuclearScatteringEnergyDistribution.cpp
//---------------------------------------------------------------------------//
