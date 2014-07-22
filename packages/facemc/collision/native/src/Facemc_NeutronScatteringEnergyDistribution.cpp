//---------------------------------------------------------------------------//
//!
//! \file   Facemc_NeutronScatteringEnergyDistribution.cpp
//! \author Alex Robinson, Alex Bennett
//! \brief  The neutron scattering energy distribution base class declaration
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "Facemc_NeutronScatteringEnergyDistribution.hpp"

namespace Facemc{

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

} // end Facemc namespace

//---------------------------------------------------------------------------//
// end Facemc_NeutronScatteringEnergyDistribution.cpp
//---------------------------------------------------------------------------//
