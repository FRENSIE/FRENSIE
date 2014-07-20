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
					                const bool is_cm_dist )
  : d_is_cm_dist( is_cm_dist )
{ /* ... */ }

} // end Facemc namespace

//---------------------------------------------------------------------------//
// end Facemc_NeutronScatteringEnergyDistribution.cpp
//---------------------------------------------------------------------------//
