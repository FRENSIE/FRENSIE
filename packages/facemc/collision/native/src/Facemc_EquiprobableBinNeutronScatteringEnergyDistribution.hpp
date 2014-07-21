//---------------------------------------------------------------------------//
//! 
//! \file   Facemc_EquiprobableBinNeutronScatteringEnergyDistribution.hpp
//! \author Alex Bennett
//! \brief  The neutron equiprobable bin scattering energy distribution class
//!
//---------------------------------------------------------------------------//

#ifndef FACEMC_EQUIPROBABLE_BIN_NEUTRON_SCATTERING_ENERGY_DISTRIBUTION
#define FACEMC_EQUIPROBABLE_BIN_NEUTRON_SCATTERING_ENERGY_DISTRIBUTION

// Trilinos Includes
#include <Teuchos_Array.hpp>

// FRENSIE Includes
#include "Facemc_NeutronScatteringEnergyDistribution.hpp"
#include "Utility_ContractException.hpp"
#include "Utility_Tuple.hpp"

namespace Facemc{

//! The inelastic equiprobable energy bins scattering eneryg distribution class (ENDF Law 1)
class EquiprobableBinNeutronScatteringEnergyDistribution : public NeutronScatteringEnergyDistribution
{

public:

  typedef Teuchos::Array<Utility::Pair<double,Teuchos::Array<double> > > EnergyDistArray;

  //! Constructor
  EquiprobableBinNeutronScatteringEnergyDistribution(EnergyDistArray& energy_grid);

  //! Destructor
  ~EquiprobableBinNeutronScatteringEnergyDistribution()
  { /* ... */ }

  //! Sample a scattering energy
  double sampleEnergy( const double energy ) const;

private:

  EnergyDistArray d_energy_grid;

};

} // end Facemc namespace

#endif // end FACEMC_EQUIPROBABLE_BIN_NEUTRON_SCATTERING_ENERGY_DISTRIBUTION

//---------------------------------------------------------------------------//
// end Facemc_EquiprobableBinNeutronScatteringEnergyDistribution.hpp
//---------------------------------------------------------------------------//

