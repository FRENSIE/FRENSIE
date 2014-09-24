//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_NeutronScatteringEnergyDistribution.cpp
//! \author Alex Robinson, Alex Bennett
//! \brief  The neutron scattering energy distribution base class declaration
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_NeutronScatteringEnergyDistribution.hpp"

namespace MonteCarlo{

// Constructor
NeutronScatteringEnergyDistribution::NeutronScatteringEnergyDistribution( 
						      const unsigned law )
  : d_law( law )
{ /* ... */ }

// Return the scattering law
unsigned NeutronScatteringEnergyDistribution::getLaw() const
{
  return d_law;
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_NeutronScatteringEnergyDistribution.cpp
//---------------------------------------------------------------------------//
