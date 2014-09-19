//---------------------------------------------------------------------------//
//! 
//! \file   MonteCarlo_AceLaw1NeutronScatteringEnergyDistribution.hpp
//! \author Alex Bennett
//! \brief  The neutron equiprobable bin scattering energy distribution class
//!
//---------------------------------------------------------------------------//

#ifndef FACEMC_ACE_LAW_1_NEUTRON_SCATTERING_ENERGY_DISTRIBUTION_HPP
#define FACEMC_ACE_LAW_1_NEUTRON_SCATTERING_ENERGY_DISTRIBUTION_HPP

// Trilinos Includes
#include <Teuchos_Array.hpp>

// FRENSIE Includes
#include "MonteCarlo_NeutronScatteringEnergyDistribution.hpp"
#include "Utility_ContractException.hpp"
#include "Utility_Tuple.hpp"

namespace MonteCarlo{

/*! \brief The inelastic equiprobable energy bins scattering enery 
 * distribution class (ENDF Law 1)
 * \ingroup ace_laws
 */
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

} // end MonteCarlo namespace

#endif // end FACEMC_ACE_LAW_1_NEUTRON_SCATTERING_ENERGY_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_AceLaw1NeutronScatteringEnergyDistribution.hpp
//---------------------------------------------------------------------------//

