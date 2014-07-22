//---------------------------------------------------------------------------//
//! 
//! \file   Facemc_Law4NeutronScatteringEnergyDistribution.hpp
//! \author Alex Bennett
//! \brief  The law 4 scattering energy distribution class
//!
//---------------------------------------------------------------------------//

#ifndef FACEMC_LAW_4_NEUTRON_SCATTERING_ENERGY_DISTRIBUTION
#define FACEMC_LAW_4_NEUTRON_SCATTERING_ENERGY_DISTRIBUTION

// Trilinos Includes
#include <Teuchos_Array.hpp>
#include <Teuchos_ArrayRCP.hpp>

// FRENSIE Includes
#include "Facemc_NeutronScatteringEnergyDistribution.hpp"
#include "Utility_ContractException.hpp"
#include "Utility_Tuple.hpp"

namespace Facemc{

//! The law 4 scattering eneryg distribution class (ENDF Law 4)
class Law4NeutronScatteringEnergyDistribution : public NeutronScatteringEnergyDistribution
{

public:

  //! Typedef for the energy distribution
  typedef Teuchos::Array<Utility::Pair<double,Teuchos::RCP<Utility::OneDDistribution> > >
                                                        EnergyDistribution;
  //! Constructor
  Law4NeutronScatteringEnergyDistribution(EnergyDistribution& energy_distribution);

  //! Destructor
  ~Law4NeutronScatteringEnergyDistribution()
  { /* ... */ }

  //! Sample a scattering energy
  double sampleEnergy( const double energy ) const;

  //! Sample a scattering energy
  double sampleEnergy( const double energy, 
                       unsigned& incoming_index, 
                       unsigned& outgoing_index,
                       double& energy_prime ) const;

private:

  EnergyDistribution d_energy_distribution;

};

} // end Facemc namespace

#endif // end FACEMC_LAW_4_NEUTRON_SCATTERING_ENERGY_DISTRIBUTION

//---------------------------------------------------------------------------//
// end Facemc_Law4NeutronScatteringEnergyDistribution.hpp
//---------------------------------------------------------------------------//

