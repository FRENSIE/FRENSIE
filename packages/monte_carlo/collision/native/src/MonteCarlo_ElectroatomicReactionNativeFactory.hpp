//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ElectroatomicReactionNativeFactory.hpp
//! \author Luke Kersting
//! \brief  The electroatomic reaction Native data factory declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_ELECTROATOMIC_REACTION_NATIVE_FACTORY_HPP
#define MONTE_CARLO_ELECTROATOMIC_REACTION_NATIVE_FACTORY_HPP

// Trilinos Includes
#include <Teuchos_RCP.hpp>
#include <Teuchos_ArrayRCP.hpp>

// FRENSIE Includes
#include "MonteCarlo_ElectroatomicReaction.hpp"
#include "MonteCarlo_BremsstrahlungAngularDistributionType.hpp"
#include "Data_ElectronPhotonRelaxationDataContainer.hpp"
#include "Utility_HashBasedGridSearcher.hpp"
#include "Utility_TwoDInterpolationPolicy.hpp"

namespace MonteCarlo{

//! The electroatomic reaction factory class that uses Native data
class ElectroatomicReactionNativeFactory
{

public:

  //! Create an analog elastic scattering electroatomic reaction
  template< typename TwoDInterpPolicy = Utility::LinLinLog>
  static void createAnalogElasticReaction(
    const Data::ElectronPhotonRelaxationDataContainer& raw_electroatom_data,
    const Teuchos::ArrayRCP<const double>& energy_grid,
    const Teuchos::RCP<Utility::HashBasedGridSearcher>& grid_searcher,
    std::shared_ptr<ElectroatomicReaction>& elastic_reaction,
    const bool correlated_sampling_mode_on,
    const double evaluation_tol );

  //! Create a hybrid elastic scattering electroatomic reaction
  template< typename TwoDInterpPolicy = Utility::LinLinLog>
  static void createHybridElasticReaction(
    const Data::ElectronPhotonRelaxationDataContainer& raw_electroatom_data,
    const Teuchos::ArrayRCP<const double>& energy_grid,
    const Teuchos::RCP<Utility::HashBasedGridSearcher>& grid_searcher,
    std::shared_ptr<ElectroatomicReaction>& elastic_reaction,
    const double cutoff_angle_cosine,
    const bool correlated_sampling_mode_on,
    const double evaluation_tol );

  //! Create an cutoff elastic scattering electroatomic reaction
  template< typename TwoDInterpPolicy = Utility::LinLinLog>
  static void createCutoffElasticReaction(
    const Data::ElectronPhotonRelaxationDataContainer& raw_electroatom_data,
    const Teuchos::ArrayRCP<const double>& energy_grid,
    const Teuchos::RCP<Utility::HashBasedGridSearcher>& grid_searcher,
    std::shared_ptr<ElectroatomicReaction>& elastic_reaction,
    const double cutoff_angle_cosine,
    const bool correlated_sampling_mode_on,
    const double evaluation_tol );

  //! Create a screened Rutherford elastic scattering electroatomic reaction
  template< typename TwoDInterpPolicy = Utility::LinLinLog>
  static void createScreenedRutherfordElasticReaction(
    const Data::ElectronPhotonRelaxationDataContainer& raw_electroatom_data,
    const Teuchos::ArrayRCP<const double>& energy_grid,
    const Teuchos::RCP<Utility::HashBasedGridSearcher>& grid_searcher,
    std::shared_ptr<ElectroatomicReaction>& elastic_reaction,
    const double cutoff_angle_cosine,
    const bool correlated_sampling_mode_on,
    const double evaluation_tol );

  //! Create the moment preserving elastic scattering electroatomic reaction
  template< typename TwoDInterpPolicy = Utility::LinLinLog>
  static void createMomentPreservingElasticReaction(
    const Data::ElectronPhotonRelaxationDataContainer& raw_electroatom_data,
    const Teuchos::ArrayRCP<const double>& energy_grid,
    const Teuchos::RCP<Utility::HashBasedGridSearcher>& grid_searcher,
    std::shared_ptr<ElectroatomicReaction>& elastic_reaction,
    const double cutoff_angle_cosine ,
    const bool correlated_sampling_mode_on,
    const double evaluation_tol );

  //! Create an atomic excitation scattering electroatomic reaction
  static void createAtomicExcitationReaction(
    const Data::ElectronPhotonRelaxationDataContainer& raw_electroatom_data,
    const Teuchos::ArrayRCP<const double>& energy_grid,
    const Teuchos::RCP<Utility::HashBasedGridSearcher>& grid_searcher,
    std::shared_ptr<ElectroatomicReaction>& atomic_excitation_reaction );

  //! Create the subshell electroionization electroatomic reaction
  template< typename ReactionType = ElectroatomicReaction,
            typename TwoDInterpPolicy = Utility::LinLinLog>
  static void createSubshellElectroionizationReaction(
    const Data::ElectronPhotonRelaxationDataContainer& raw_electroatom_data,
    const Teuchos::ArrayRCP<const double>& energy_grid,
    const Teuchos::RCP<Utility::HashBasedGridSearcher>& grid_searcher,
    const unsigned subshell,
    std::shared_ptr<ReactionType>& electroionization_subshell_reaction,
    const bool correlated_sampling_mode_on,
    const bool unit_based_interpolation_mode_on,
    const double evaluation_tol );

  //! Create the subshell electroionization electroatomic reactions
  template< typename ReactionType = ElectroatomicReaction,
            typename TwoDInterpPolicy = Utility::LinLinLog>
  static void createSubshellElectroionizationReactions(
    const Data::ElectronPhotonRelaxationDataContainer& raw_electroatom_data,
    const Teuchos::ArrayRCP<const double>& energy_grid,
    const Teuchos::RCP<Utility::HashBasedGridSearcher>& grid_searcher,
    std::vector<std::shared_ptr<ReactionType> >&
        electroionization_subshell_reactions,
    const bool correlated_sampling_mode_on,
    const bool unit_based_interpolation_mode_on,
    const double evaluation_tol );

  //! Create the bremsstrahlung electroatomic reaction
  template< typename ReactionType = ElectroatomicReaction,
            typename TwoDInterpPolicy = Utility::LinLinLog>
  static void createBremsstrahlungReaction(
    const Data::ElectronPhotonRelaxationDataContainer& raw_electroatom_data,
    const Teuchos::ArrayRCP<const double>& energy_grid,
    const Teuchos::RCP<Utility::HashBasedGridSearcher>& grid_searcher,
    std::shared_ptr<ReactionType>& bremsstrahlung_reaction,
    BremsstrahlungAngularDistributionType photon_distribution_function,
    const bool correlated_sampling_mode_on,
    const bool unit_based_interpolation_mode_on,
    const double evaluation_tol );

  //! Create a void absorption electroatomic reaction
  static void createVoidAbsorptionReaction(
    std::shared_ptr<ElectroatomicReaction>& void_absorption_reaction );

private:

  // Constructor
  ElectroatomicReactionNativeFactory();
};

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "MonteCarlo_ElectroatomicReactionNativeFactory_def.hpp"

//---------------------------------------------------------------------------//

#endif // end MONTE_CARLO_ELECTROATOMIC_REACTION_NATIVE_FACTORY_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ElectroatomicReactionNativeFactory.hpp
//---------------------------------------------------------------------------//
