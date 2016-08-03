//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ElectroatomicReactionNativeFactory.hpp
//! \author Luke Kersting
//! \brief  The electroatomic reaction Native data factory declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_PHOTOATOMIC_REACTION_NATIVE_FACTORY_HPP
#define MONTE_CARLO_PHOTOATOMIC_REACTION_NATIVE_FACTORY_HPP

// Trilinos Includes
#include <Teuchos_Array.hpp>

// FRENSIE Includes
#include "MonteCarlo_ElectroatomicReaction.hpp"
#include "Data_ElectronPhotonRelaxationDataContainer.hpp"
#include "Utility_StandardHashBasedGridSearcher.hpp"
#include "MonteCarlo_BremsstrahlungAngularDistributionType.hpp"

namespace MonteCarlo{

//! The electroatomic reaction factory class that uses Native data
class ElectroatomicReactionNativeFactory
{

public:

  //! Create an analog elastic scattering electroatomic reaction
  static void createAnalogElasticReaction(
    const Data::ElectronPhotonRelaxationDataContainer& raw_electroatom_data,
    const Teuchos::ArrayRCP<const double>& energy_grid,
    const Teuchos::RCP<Utility::HashBasedGridSearcher>& grid_searcher,
    Teuchos::RCP<ElectroatomicReaction>& elastic_reaction );

  //! Create a hybrid elastic scattering electroatomic reaction
  static void createHybridElasticReaction(
    const Data::ElectronPhotonRelaxationDataContainer& raw_electroatom_data,
    const Teuchos::ArrayRCP<const double>& energy_grid,
    const Teuchos::RCP<Utility::HashBasedGridSearcher>& grid_searcher,
    Teuchos::RCP<ElectroatomicReaction>& elastic_reaction,
    const double cutoff_angle_cosine = 0.9 );

  //! Create an cutoff elastic scattering electroatomic reaction
  static void createCutoffElasticReaction(
    const Data::ElectronPhotonRelaxationDataContainer& raw_electroatom_data,
    const Teuchos::ArrayRCP<const double>& energy_grid,
    const Teuchos::RCP<Utility::HashBasedGridSearcher>& grid_searcher,
    Teuchos::RCP<ElectroatomicReaction>& elastic_reaction,
    const double cutoff_angle_cosine = 1.0 );

  //! Create a screened Rutherford elastic scattering electroatomic reaction
  static void createScreenedRutherfordElasticReaction(
    const Data::ElectronPhotonRelaxationDataContainer& raw_electroatom_data,
    const Teuchos::ArrayRCP<const double>& energy_grid,
    const Teuchos::RCP<Utility::HashBasedGridSearcher>& grid_searcher,
    Teuchos::RCP<ElectroatomicReaction>& elastic_reaction,
    const double cutoff_angle_cosine = 1.0 );

  //! Create the moment preserving elastic scattering electroatomic reaction
  static void createMomentPreservingElasticReaction(
    const Data::ElectronPhotonRelaxationDataContainer& raw_electroatom_data,
    const Teuchos::ArrayRCP<const double>& energy_grid,
    const Teuchos::RCP<Utility::HashBasedGridSearcher>& grid_searcher,
    Teuchos::RCP<ElectroatomicReaction>& elastic_reaction,
    const double cutoff_angle_cosine = 0.9 );

  //! Create an atomic excitation scattering electroatomic reaction
  static void createAtomicExcitationReaction(
	const Data::ElectronPhotonRelaxationDataContainer& raw_electroatom_data,
	const Teuchos::ArrayRCP<const double>& energy_grid,
    const Teuchos::RCP<Utility::HashBasedGridSearcher>& grid_searcher,
	Teuchos::RCP<ElectroatomicReaction>& atomic_excitation_reaction );

  //! Create the subshell electroionization electroatomic reactions
  static void createSubshellElectroionizationReactions(
    const Data::ElectronPhotonRelaxationDataContainer& raw_electroatom_data,
    const Teuchos::ArrayRCP<const double>& energy_grid,
    const Teuchos::RCP<Utility::HashBasedGridSearcher>& grid_searcher,
    Teuchos::Array<Teuchos::RCP<ElectroatomicReaction> >&
        electroionization_subshell_reactions );

  //! Create the bremsstrahlung electroatomic reaction
  static void createBremsstrahlungReaction(
	const Data::ElectronPhotonRelaxationDataContainer& raw_electroatom_data,
	const Teuchos::ArrayRCP<const double>& energy_grid,
    const Teuchos::RCP<Utility::HashBasedGridSearcher>& grid_searcher,
	Teuchos::RCP<ElectroatomicReaction>& bremsstrahlung_reactions,
	BremsstrahlungAngularDistributionType photon_distribution_function );

  //! Create a void absorption electroatomic reaction
  static void createVoidAbsorptionReaction(
    Teuchos::RCP<ElectroatomicReaction>& void_absorption_reaction );

private:

  // Check if a value is not equal to zero
  static bool notEqualZero( double value );

  // Constructor
  ElectroatomicReactionNativeFactory();
};

// Check if a value is not equal to zero
inline bool ElectroatomicReactionNativeFactory::notEqualZero( double value )
{
  return value != 0.0;
}

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_PHOTOATOMIC_REACTION_NATIVE_FACTORY_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ElectroatomicReactionNativeFactory.hpp
//---------------------------------------------------------------------------//
