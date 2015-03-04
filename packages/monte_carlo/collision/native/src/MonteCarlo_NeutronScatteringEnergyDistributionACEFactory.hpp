//---------------------------------------------------------------------------//
//! 
//! \file   MonteCarlo_NeutronScatteringEnergyDistributionACEFactory.hpp
//! \author Alex Robinson, Alex Bennett
//! \brief  Neutron scattering energy distribution factory class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_NEUTRON_SCATTERING_ENERGY_DISTRIBUTION_ACE_FACTORY
#define MONTE_CARLO_NEUTRON_SCATTERING_ENERGY_DISTRIBUTION_ACE_FACTORY

// Trilinos Includes
#include <Teuchos_RCP.hpp>
#include <Teuchos_Array.hpp>

// FRENSIE Includes
#include "MonteCarlo_ParticleScatteringEnergyDistribution.hpp"
#include "MonteCarlo_NeutronScatteringDistribution.hpp"
#include "MonteCarlo_NuclearReactionType.hpp"

namespace MonteCarlo{

//! The scattering angular distribution factory class
class NeutronScatteringEnergyDistributionACEFactory
{

public:

  //! Create the energy distribution
  static void createDistribution( 
	    const Teuchos::ArrayView<const double>& dlw_block_array,
	    const unsigned dlw_block_array_start_index,
	    const std::string& table_name,
	    const NuclearReactionType reaction,
            Teuchos::RCP<ParticleScatteringEnergyDistribution>& distribution );

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
	    Teuchos::RCP<ParticleScatteringEnergyDistribution>& distribution );

  // Create a Law 3 energy distribution
  static void createAceLaw3EnergyDistribution(
	    const Teuchos::ArrayView<const double>& dlw_block_array,
	    const unsigned dlw_block_array_start_index,
	    const std::string& table_name,
	    const NuclearReactionType reaction,
	    Teuchos::RCP<ParticleScatteringEnergyDistribution>& distribution );

  // Create a Law 4 energy distribution
  static void createAceLaw4EnergyDistribution(
	    const Teuchos::ArrayView<const double>& dlw_block_array,
	    const unsigned dlw_block_array_start_index,
	    const std::string& table_name,
	    const NuclearReactionType reaction,
	    Teuchos::RCP<ParticleScatteringEnergyDistribution>& distribution );

  // Constructor
  NeutronScatteringEnergyDistributionACEFactory();

};

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_NEUTRON_SCATTERING_ENERGY_DISTRIBUTION_ACE_FACTORY

//---------------------------------------------------------------------------//
// end MonteCarlo_NeutronScatteringEnergyDistributionACEFactory.hpp
//---------------------------------------------------------------------------//
