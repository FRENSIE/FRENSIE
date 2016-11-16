//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_AdjointElectroatomicReactionNativeFactory.hpp
//! \author Luke Kersting
//! \brief  The adjoint electroatomic reaction Native data factory declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_ADJOINT_ELECTROATOMIC_REACTION_NATIVE_FACTORY_HPP
#define MONTE_CARLO_ADJOINT_ELECTROATOMIC_REACTION_NATIVE_FACTORY_HPP

// Trilinos Includes
#include <Teuchos_RCP.hpp>
#include <Teuchos_Array.hpp>

// FRENSIE Includes
#include "MonteCarlo_AdjointElectroatomicReaction.hpp"
#include "MonteCarlo_BremsstrahlungAngularDistributionType.hpp"
#include "Data_AdjointElectronPhotonRelaxationDataContainer.hpp"
#include "Utility_HashBasedGridSearcher.hpp"

namespace MonteCarlo{

//! The adjoint electroatomic reaction factory class that uses Native data
class AdjointElectroatomicReactionNativeFactory
{

public:

  //! Create an analog elastic scattering adjoint electroatomic reaction
  static void createAnalogElasticReaction(
    const Data::AdjointElectronPhotonRelaxationDataContainer&
        raw_adjoint_electroatom_data,
    const Teuchos::ArrayRCP<const double>& energy_grid,
    const Teuchos::RCP<Utility::HashBasedGridSearcher>& grid_searcher,
    std::shared_ptr<AdjointElectroatomicReaction>& elastic_reaction );

  //! Create a hybrid elastic scattering adjoint electroatomic reaction
  static void createHybridElasticReaction(
    const Data::AdjointElectronPhotonRelaxationDataContainer&
        raw_adjoint_electroatom_data,
    const Teuchos::ArrayRCP<const double>& energy_grid,
    const Teuchos::RCP<Utility::HashBasedGridSearcher>& grid_searcher,
    std::shared_ptr<AdjointElectroatomicReaction>& elastic_reaction,
    const double cutoff_angle_cosine = 0.9 );

  //! Create an cutoff elastic scattering adjoint electroatomic reaction
  static void createCutoffElasticReaction(
    const Data::AdjointElectronPhotonRelaxationDataContainer&
        raw_adjoint_electroatom_data,
    const Teuchos::ArrayRCP<const double>& energy_grid,
    const Teuchos::RCP<Utility::HashBasedGridSearcher>& grid_searcher,
    std::shared_ptr<AdjointElectroatomicReaction>& elastic_reaction,
    const double cutoff_angle_cosine = 1.0 );

  //! Create a screened Rutherford elastic scattering adjoint electroatomic reaction
  static void createScreenedRutherfordElasticReaction(
    const Data::AdjointElectronPhotonRelaxationDataContainer&
        raw_adjoint_electroatom_data,
    const Teuchos::ArrayRCP<const double>& energy_grid,
    const Teuchos::RCP<Utility::HashBasedGridSearcher>& grid_searcher,
    std::shared_ptr<AdjointElectroatomicReaction>& elastic_reaction,
    const double cutoff_angle_cosine = 1.0 );

  //! Create the moment preserving elastic scattering adjoint electroatomic reaction
  static void createMomentPreservingElasticReaction(
    const Data::AdjointElectronPhotonRelaxationDataContainer&
        raw_adjoint_electroatom_data,
    const Teuchos::ArrayRCP<const double>& energy_grid,
    const Teuchos::RCP<Utility::HashBasedGridSearcher>& grid_searcher,
    std::shared_ptr<AdjointElectroatomicReaction>& elastic_reaction,
    const double cutoff_angle_cosine = 0.9 );

  //! Create an atomic excitation scattering adjoint electroatomic reaction
  static void createAtomicExcitationReaction(
    const Data::AdjointElectronPhotonRelaxationDataContainer&
        raw_adjoint_electroatom_data,
    const Teuchos::ArrayRCP<const double>& energy_grid,
    const Teuchos::RCP<Utility::HashBasedGridSearcher>& grid_searcher,
    std::shared_ptr<AdjointElectroatomicReaction>& atomic_excitation_reaction );

  //! Create the subshell electroionization adjoint electroatomic reaction
  static void createSubshellElectroionizationReaction(
    const Data::AdjointElectronPhotonRelaxationDataContainer&
        raw_adjoint_electroatom_data,
    const Teuchos::ArrayRCP<const double>& energy_grid,
    const Teuchos::RCP<Utility::HashBasedGridSearcher>& grid_searcher,
    const unsigned subshell,
    std::shared_ptr<AdjointElectroatomicReaction>& electroionization_subshell_reaction );

  //! Create the subshell electroionization adjoint electroatomic reactions
  static void createSubshellElectroionizationReactions(
    const Data::AdjointElectronPhotonRelaxationDataContainer&
        raw_adjoint_electroatom_data,
    const Teuchos::ArrayRCP<const double>& energy_grid,
    const Teuchos::RCP<Utility::HashBasedGridSearcher>& grid_searcher,
    std::vector<std::shared_ptr<AdjointElectroatomicReaction> >&
        electroionization_subshell_reactions );

  //! Create the bremsstrahlung adjoint electroatomic reaction
  static void createBremsstrahlungReaction(
    const Data::AdjointElectronPhotonRelaxationDataContainer&
        raw_adjoint_electroatom_data,
    const Teuchos::ArrayRCP<const double>& energy_grid,
    const Teuchos::RCP<Utility::HashBasedGridSearcher>& grid_searcher,
    std::shared_ptr<AdjointElectroatomicReaction>& bremsstrahlung_reaction,
    BremsstrahlungAngularDistributionType photon_distribution_function );

  //! Create a void absorption adjoint electroatomic reaction
  static void createVoidAbsorptionReaction(
    std::shared_ptr<AdjointElectroatomicReaction>& void_absorption_reaction );
};

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_ADJOINT_ELECTROATOMIC_REACTION_NATIVE_FACTORY_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_AdjointElectroatomicReactionNativeFactory.hpp
//---------------------------------------------------------------------------//
