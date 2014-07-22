//---------------------------------------------------------------------------//
//! 
//! \file   Facemc_AceLaw1NeutronScatteringEnergyDistribution.hpp
//! \author Alex Bennett
//! \brief  The neutron equiprobable bin scattering energy distribution class
//!
//---------------------------------------------------------------------------//

#ifndef FACEMC_ACE_LAW_1_NEUTRON_SCATTERING_ENERGY_DISTRIBUTION_HPP
#define FACEMC_ACE_LAW_1_NEUTRON_SCATTERING_ENERGY_DISTRIBUTION_HPP

// Trilinos Includes
#include <Teuchos_Array.hpp>

// FRENSIE Includes
#include "Facemc_NeutronScatteringEnergyDistribution.hpp"
#include "Utility_ContractException.hpp"
#include "Utility_Tuple.hpp"

namespace Facemc{

//! The inelastic equiprobable energy bins scattering eneryg distribution class (ENDF Law 1)
class AceLaw1NeutronScatteringEnergyDistribution : public NeutronScatteringEnergyDistribution
{

public:

  typedef Teuchos::Array<Utility::Pair<double,Teuchos::Array<double> > >
  EnergyDistArray;

  //! Constructor
  AceLaw1NeutronScatteringEnergyDistribution(EnergyDistArray& energy_grid);

  //! Destructor
  ~AceLaw1NeutronScatteringEnergyDistribution()
  { /* ... */ }

  //! Sample a scattering energy
  double sampleEnergy( const double energy ) const;

private:

  EnergyDistArray d_energy_grid;

};

} // end Facemc namespace

#endif // end FACEMC_ACE_LAW_1_NEUTRON_SCATTERING_ENERGY_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end Facemc_AceLaw1NeutronScatteringEnergyDistribution.hpp
//---------------------------------------------------------------------------//

