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

  //! Create the Ace law 44 coupled energy-angle distribution
  static void createAceLaw44Distribution(
                   const double atomic_weight_ratio,
	           const Teuchos::ArrayView<const double>& dlw_block_array,
		   const unsigned dlw_block_array_start_index,
		   const std::string& table_name,
		   const NuclearReactionType reaction,
		   const bool is_cm_distribution,
                   Teuchos::RCP<NeutronScatteringDistribution>& distribution );

private:

  // Create a Ace Law 1 energy distribution
  static void createAceLaw1EnergyDistribution( 
	     const Teuchos::ArrayView<const double>& dlw_block_array,
	     const unsigned dlw_block_array_start_index,
	     const std::string& table_name,
	     const NuclearReactionType reaction,
	     Teuchos::RCP<NeutronScatteringEnergyDistribution>& distribution );

  // Create a Law 3 energy distribution
  static void createAceLaw3EnergyDistribution(
	     const Teuchos::ArrayView<const double>& dlw_block_array,
	     const unsigned dlw_block_array_start_index,
	     const std::string& table_name,
	     const NuclearReactionType reaction,
	     Teuchos::RCP<NeutronScatteringEnergyDistribution>& distribution );

  // Create a Law 4 energy distribution
  static void createAceLaw4EnergyDistribution(
	     const Teuchos::ArrayView<const double>& dlw_block_array,
	     const unsigned dlw_block_array_start_index,
	     const std::string& table_name,
	     const NuclearReactionType reaction,
	     Teuchos::RCP<NeutronScatteringEnergyDistribution>& distribution );

  // Constructor
  NeutronScatteringEnergyDistributionFactory();

};

} // end Facemc namespace

#endif // end FACEMC_NEUTRON_SCATTERING_ENERGY_DISTRIBUTION_FACTORY

//---------------------------------------------------------------------------//
// end Facemc_NeutronScatteringEnergyDistributionFactory.hpp
//---------------------------------------------------------------------------//
