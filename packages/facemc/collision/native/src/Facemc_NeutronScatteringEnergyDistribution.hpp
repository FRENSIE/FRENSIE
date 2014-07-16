//---------------------------------------------------------------------------//
//!
//! \file   Facemc_NeutronScatteringEnergyDistribution.hpp
//! \author Alex Robinson, Alex Bennett
//! \brief  The neutron scattering energy distribution base class declaration
//!
//---------------------------------------------------------------------------//

#ifndef FACEMC_NEUTRON_SCATTERING_ENERGY_DISTRIBUTION
#define FACEMC_NEUTRON_SCATTERING_ENERGY_DISTRIBUTION

// Trilinos Includes
#include <Teuchos_Array.hpp>

// FRENSIE Includes
#include "Facemc_NeutronState.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_OneDDistribution.hpp"

namespace Facemc{

//! The energy scattering distribution base class
class NeutronScatteringEnergyDistribution
{

public:

  //! Constructor
  NeutronScatteringEnergyDistribution()
  { /* ... */ }

  //! Destructor
  virtual ~NeutronScatteringEnergyDistribution()
  { /* ... */ }

  //! Sample a scattering energy
  virtual double sampleEnergy( const double energy ) const = 0;

};

} // end Facemc namespace

#endif // end FACEMC_NEUTRON_SCATTERING_ENERGY_DISTRIBUTION

//---------------------------------------------------------------------------//
// end Facemc_NeutronScatteringEnergyDistribution.hpp
//---------------------------------------------------------------------------//
