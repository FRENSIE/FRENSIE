//---------------------------------------------------------------------------//
//! 
//! \file   Facemc_NeutronScatteringEnergyDistributionFactory.hpp
//! \author Alex Robinson, Alex Bennett
//! \brief  Neutron scattering energy distribution factory class declaration
//!
//---------------------------------------------------------------------------//

#ifndef FACEMC_NEUTRON_SCATTERING_ENERGY_DISTRIBUTION_FACTORY
#define FACEMC_NEUTRON_SCATTERING_ENERGY_DISTRIBUTION_FACTORY

// Trilinos Includes
#include <Teuchos_RCP.hpp>
#include <Teuchos_Array.hpp>

// FRENSIE Includes
#include "Facemc_NeutronScatteringEnergyDistribution.hpp"
#include "Facemc_NeutronScatteringDistribution.hpp"
#include "Facemc_NuclearReactionType.hpp"

namespace Facemc{

//! The scattering angular distribution factory class
class NeutronScatteringEnergyDistributionFactory
{

public:

  //! Create the energy distribution
  static void createDistribution( 
	    const Teuchos::ArrayView<const double>& dlw_block_array,
	    const unsigned dlw_block_array_start_index,
	    const std::string& table_name,
	    const NuclearReactionType reaction,
            Teuchos::RCP<NeutronScatteringEnergyDistribution>& distribution );

  //! Create the ENDF law 44 coupled energy-angle distribution
  static void createCoupledDistribution(
	           const Teuchos::ArrayView<const double>& dlw_block_array,
		   const unsigned dlw_block_array_start_index,
		   const std::string& table_name,
		   const NuclearReactionType reaction,
                   Teuchos::RCP<NeutronScatteringDistribution>& distribution );

private:

  //! Constructor
  NeutronScatteringEnergyDistributionFactory();

};

} // end Facemc namespace

#endif // end FACEMC_NEUTRON_SCATTERING_ENERGY_DISTRIBUTION_FACTORY

//---------------------------------------------------------------------------//
// end Facemc_NeutronScatteringEnergyDistributionFactory.hpp
//---------------------------------------------------------------------------//
