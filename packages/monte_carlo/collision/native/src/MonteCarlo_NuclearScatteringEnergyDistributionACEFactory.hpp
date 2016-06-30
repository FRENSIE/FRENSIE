//---------------------------------------------------------------------------//
//! 
//! \file   MonteCarlo_NuclearScatteringEnergyDistributionACEFactory.hpp
//! \author Alex Robinson, Alex Bennett, Eli Moll
//! \brief  Nuclear scattering energy distribution factory class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_NUCLEAR_SCATTERING_ENERGY_DISTRIBUTION_ACE_FACTORY
#define MONTE_CARLO_NUCLEAR_SCATTERING_ENERGY_DISTRIBUTION_ACE_FACTORY

// Trilinos Includes
#include <Teuchos_RCP.hpp>
#include <Teuchos_Array.hpp>

// FRENSIE Includes
#include "MonteCarlo_NuclearScatteringEnergyDistribution.hpp"
#include "MonteCarlo_NuclearScatteringDistribution.hpp"
#include "MonteCarlo_NuclearReactionType.hpp"
#include "Utility_UniformDistribution.hpp"

namespace MonteCarlo{

//! The scattering angular distribution factory class
class NuclearScatteringEnergyDistributionACEFactory
{

public:

  //! Create the energy distribution
  static void createDistribution( 
	  const Teuchos::ArrayView<const double>& dlw_block_array,
	  const unsigned dlw_block_array_start_index,
	  const std::string& table_name,
	  const unsigned reaction,
      Teuchos::RCP<NuclearScatteringEnergyDistribution>& distribution,
      const double atomic_weight_ratio = 0.0 );

  //! Create the Ace law 44 coupled energy-angle distribution
  template<typename ScatteringDistributionBaseType>
  static void createAceLaw44Distribution(
                  const double atomic_weight_ratio,
		const Teuchos::ArrayView<const double>& dlw_block_array,
		const unsigned dlw_block_array_start_index,
		const std::string& table_name,
		const unsigned reaction,
		const bool is_cm_distribution,
                  Teuchos::RCP<ScatteringDistributionBaseType>& distribution );

  //! Create the Ace law 61 coupled energy-angle distribution
  template<typename ScatteringDistributionBaseType>
  static void createAceLaw61Distribution(
    const double atomic_weight_ratio,
		const Teuchos::ArrayView<const double>& dlw_block_array,
		const unsigned dlw_block_array_start_index,
		const std::string& table_name,
		const unsigned reaction,
		const bool is_cm_distribution,
                  Teuchos::RCP<ScatteringDistributionBaseType>& distribution );
                  
  //! Create the S(alpha,beta) coupled energy-angle inelastic distribution
  template<typename ScatteringDistributionBaseType>
  static void createSAlphaBetaInelasticDistribution(
    const double atomic_weight_ratio,
    const Teuchos::ArrayView<const double>& incoming_energies,
    const Teuchos::ArrayView<const double>& inelastic_locations,
    const Teuchos::ArrayView<const double>& outgoing_energies,
		const Teuchos::ArrayView<const double>& itxe_block_array,
		const std::string& table_name,
		const unsigned reaction,
		const bool is_cm_distribution,
    Teuchos::RCP<ScatteringDistributionBaseType>& distribution );
    
  //! Create the S(alpha,beta) coupled energy-angle inelastic distribution
  template<typename ScatteringDistributionBaseType>
  static void createSAlphaBetaElasticDistribution(
    const double atomic_weight_ratio,
    const Teuchos::ArrayView<const double>& incoming_energies,
    const Teuchos::ArrayView<const double>& itce_block_array,
		const Teuchos::ArrayView<const double>& itca_block_array,
		const std::string& table_name,
		const unsigned reaction,
		const bool is_cm_distribution,
    Teuchos::RCP<ScatteringDistributionBaseType>& distribution );

  //! Determine the coupled energy-angle distribution
  static unsigned determineCoupledDistribution(
    const double atomic_weight_ratio,
		const Teuchos::ArrayView<const double>& dlw_block_array,
		const unsigned dlw_block_array_start_index,
		const std::string& table_name );

private:

  // Create an Ace Law 1 energy distribution
  static void createAceLaw1EnergyDistribution( 
	  const Teuchos::ArrayView<const double>& dlw_block_array,
	  const unsigned dlw_block_array_start_index,
	  const std::string& table_name,
	  const unsigned reaction,
	  Teuchos::RCP<NuclearScatteringEnergyDistribution>& distribution );

  // Create an Ace Law 2 energy distribution
  static void createAceLaw2EnergyDistribution( 
	  const Teuchos::ArrayView<const double>& dlw_block_array,
	  const unsigned dlw_block_array_start_index,
	  const std::string& table_name,
	  const unsigned reaction,
	  Teuchos::RCP<NuclearScatteringEnergyDistribution>& distribution,
	  const double atomic_weight_ratio );

  // Create an Law 3 energy distribution
  static void createAceLaw3EnergyDistribution(
	  const Teuchos::ArrayView<const double>& dlw_block_array,
	  const unsigned dlw_block_array_start_index,
	  const std::string& table_name,
	  const unsigned reaction,
	  Teuchos::RCP<NuclearScatteringEnergyDistribution>& distribution );

  // Create an Law 4 energy distribution
  static void createAceLaw4EnergyDistribution(
	  const Teuchos::ArrayView<const double>& dlw_block_array,
	  const unsigned dlw_block_array_start_index,
	  const std::string& table_name,
	  const unsigned reaction,
	  Teuchos::RCP<NuclearScatteringEnergyDistribution>& distribution );

  // Create an Law 5 energy distribution
  static void createAceLaw5EnergyDistribution(
	  const Teuchos::ArrayView<const double>& dlw_block_array,
	  const unsigned dlw_block_array_start_index,
	  const std::string& table_name,
	  const unsigned reaction,
	  Teuchos::RCP<NuclearScatteringEnergyDistribution>& distribution );

  // Create an Law 7 energy distribution
  static void createAceLaw7EnergyDistribution(
	  const Teuchos::ArrayView<const double>& dlw_block_array,
	  const unsigned dlw_block_array_start_index,
	  const std::string& table_name,
	  const unsigned reaction,
	  Teuchos::RCP<NuclearScatteringEnergyDistribution>& distribution );

  // Create an Law 9 energy distribution
  static void createAceLaw9EnergyDistribution(
	  const Teuchos::ArrayView<const double>& dlw_block_array,
	  const unsigned dlw_block_array_start_index,
	  const std::string& table_name,
	  const unsigned reaction,
	  Teuchos::RCP<NuclearScatteringEnergyDistribution>& distribution );

  // Create an Law 11 energy distribution
  static void createAceLaw11EnergyDistribution(
	  const Teuchos::ArrayView<const double>& dlw_block_array,
	  const unsigned dlw_block_array_start_index,
	  const std::string& table_name,
	  const unsigned reaction,
	  Teuchos::RCP<NuclearScatteringEnergyDistribution>& distribution );

  // Constructor
  NuclearScatteringEnergyDistributionACEFactory();

};

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "MonteCarlo_NuclearScatteringEnergyDistributionACEFactory_def.hpp"

//---------------------------------------------------------------------------//

#endif // end MONTE_CARLO_NUCLEAR_SCATTERING_ENERGY_DISTRIBUTION_ACE_FACTORY

//---------------------------------------------------------------------------//
// end MonteCarlo_NuclearScatteringEnergyDistributionACEFactory.hpp
//---------------------------------------------------------------------------//
