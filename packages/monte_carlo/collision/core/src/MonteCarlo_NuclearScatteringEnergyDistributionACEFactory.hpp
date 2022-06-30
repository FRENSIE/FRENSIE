//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_NuclearScatteringEnergyDistributionACEFactory.hpp
//! \author Alex Robinson, Alex Bennett, Eli Moll
//! \brief  Nuclear scattering energy distribution factory class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_NUCLEAR_SCATTERING_ENERGY_DISTRIBUTION_ACE_FACTORY
#define MONTE_CARLO_NUCLEAR_SCATTERING_ENERGY_DISTRIBUTION_ACE_FACTORY

// Std Lib Includes
#include <memory>

// FRENSIE Includes
#include "MonteCarlo_NuclearScatteringEnergyDistribution.hpp"
#include "MonteCarlo_NuclearScatteringDistribution.hpp"
#include "Utility_UniformDistribution.hpp"
#include "Utility_Vector.hpp"
#include "Utility_ArrayView.hpp"

namespace MonteCarlo{

//! The scattering angular distribution factory class
class NuclearScatteringEnergyDistributionACEFactory
{

public:

  //! Create the energy distribution
  static void createDistribution(
                    const Utility::ArrayView<const double>& dlw_block_array,
                    const unsigned dlw_block_array_start_index,
                    const std::string& table_name,
                    const unsigned reaction,
                    std::shared_ptr<const NuclearScatteringEnergyDistribution>&
                    distribution,
                    const double atomic_weight_ratio = 0.0 );

  //! Create the Ace law 44 coupled energy-angle distribution
  template<typename ScatteringDistribution>
  static void createAceLaw44Distribution(
                       const double atomic_weight_ratio,
                       const Utility::ArrayView<const double>& dlw_block_array,
                       const unsigned dlw_block_array_start_index,
                       const std::string& table_name,
                       const unsigned reaction,
                       const bool is_cm_distribution,
                       std::shared_ptr<const ScatteringDistribution>&
                       distribution );

  //! Create the Ace law 61 coupled energy-angle distribution
  template<typename ScatteringDistribution>
  static void createAceLaw61Distribution(
                       const double atomic_weight_ratio,
                       const Utility::ArrayView<const double>& dlw_block_array,
                       const unsigned dlw_block_array_start_index,
                       const std::string& table_name,
                       const unsigned reaction,
                       const bool is_cm_distribution,
                       std::shared_ptr<const ScatteringDistribution>&
                       distribution );

  //! Create the SAlphaBeta Inelastic distribution
  template <typename ScatteringDistribution>
  static void createSAlphaBetaInelasticDistribution(
      const double atomic_weight_ratio,
      const Utility::ArrayView<const double>& incoming_energies,
      const Utility::ArrayView<const double>& inelastic_locations,
      const Utility::ArrayView<const double>& outgoing_energies,
      const Utility::ArrayView<const double>& itxe_block_array,
      const bool is_continuous_energy,
      const std::string& table_name,
      const unsigned reaction,
      const bool is_cm_distribution,
      std::shared_ptr<ScatteringDistribution>& distribution);
      
  //! Determine the coupled energy-angle distribution
  static unsigned determineCoupledDistribution(
    const double atomic_weight_ratio,
		const Utility::ArrayView<const double>& dlw_block_array,
		const unsigned dlw_block_array_start_index,
		const std::string& table_name );

private:

  // Create an Ace Law 1 energy distribution
  static void createAceLaw1EnergyDistribution(
                    const Utility::ArrayView<const double>& dlw_block_array,
                    const unsigned dlw_block_array_start_index,
                    const std::string& table_name,
                    const unsigned reaction,
	            std::shared_ptr<const NuclearScatteringEnergyDistribution>&
                    distribution );

  // Create an Ace Law 2 energy distribution
  static void createAceLaw2EnergyDistribution(
                    const Utility::ArrayView<const double>& dlw_block_array,
                    const unsigned dlw_block_array_start_index,
                    const std::string& table_name,
                    const unsigned reaction,
	            std::shared_ptr<const NuclearScatteringEnergyDistribution>&
                    distribution,
                    const double atomic_weight_ratio );

  // Create an Law 3 energy distribution
  static void createAceLaw3EnergyDistribution(
                    const Utility::ArrayView<const double>& dlw_block_array,
                    const unsigned dlw_block_array_start_index,
                    const std::string& table_name,
                    const unsigned reaction,
                    std::shared_ptr<const NuclearScatteringEnergyDistribution>&
                    distribution );

  // Create an Law 4 energy distribution
  static void createAceLaw4EnergyDistribution(
                    const Utility::ArrayView<const double>& dlw_block_array,
                    const unsigned dlw_block_array_start_index,
                    const std::string& table_name,
                    const unsigned reaction,
	            std::shared_ptr<const NuclearScatteringEnergyDistribution>&
                    distribution );

  // Create an Law 5 energy distribution
  static void createAceLaw5EnergyDistribution(
                    const Utility::ArrayView<const double>& dlw_block_array,
                    const unsigned dlw_block_array_start_index,
                    const std::string& table_name,
                    const unsigned reaction,
	            std::shared_ptr<const NuclearScatteringEnergyDistribution>&
                    distribution );

  // Create an Law 7 energy distribution
  static void createAceLaw7EnergyDistribution(
                    const Utility::ArrayView<const double>& dlw_block_array,
                    const unsigned dlw_block_array_start_index,
                    const std::string& table_name,
                    const unsigned reaction,
	            std::shared_ptr<const NuclearScatteringEnergyDistribution>&
                    distribution );

  // Create an Law 9 energy distribution
  static void createAceLaw9EnergyDistribution(
                    const Utility::ArrayView<const double>& dlw_block_array,
                    const unsigned dlw_block_array_start_index,
                    const std::string& table_name,
                    const unsigned reaction,
	            std::shared_ptr<const NuclearScatteringEnergyDistribution>&
                    distribution );

  // Create an Law 11 energy distribution
  static void createAceLaw11EnergyDistribution(
                    const Utility::ArrayView<const double>& dlw_block_array,
                    const unsigned dlw_block_array_start_index,
                    const std::string& table_name,
                    const unsigned reaction,
	            std::shared_ptr<const NuclearScatteringEnergyDistribution>&
                    distribution );

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
