//---------------------------------------------------------------------------//
//!
//! \file   Facemc_NeutronScatteringEnergyDistribution.cpp
//! \author Alex Robinson, Alex Bennett
//! \brief  The neutron scattering energy distribution base class definition
//!
//---------------------------------------------------------------------------//

// Trilinos Includes
#include <Teuchos_ScalarTraits.hpp>

// FRENSIE Includes
#include "Facemc_NeutronScatteringEnergyDistribution.hpp"
#include "Utility_SearchAlgorithms.hpp"
#include "Utility_SortAlgorithms.hpp"
#include "Utility_ContractException.hpp"

namespace Facemc{

// Constructor
//NeutronScatteringEnergyDistribution::NeutronScatteringEnergyDistribution(
//            const NeutronScatteringEnergyDistribution::EnergyDistribution& dist )
//  : d_energy_distribution( dist )
//{
//  // Make sure the array ahs at least one value
//  testPrecondition( dist.size() > 0 );
//}
//
//// Sample a scattering energy
//double NeutronScatteringEnergyDistribution::sampleEnergy( const double energy) const
//{
//
//
//
//
//
//}

} // end Facemc namespace

//---------------------------------------------------------------------------//
// end Facemc_NeutronScatteringEnergyDistribution.cpp
//---------------------------------------------------------------------------//
