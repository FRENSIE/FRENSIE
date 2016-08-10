//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ElectroatomicReactionACEFactory.hpp
//! \author Luke Kersting
//! \brief  The electroatomic reaction ACE data factory declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_ELECTROATOMIC_REACTION_ACE_FACTORY_HPP
#define MONTE_CARLO_ELECTROATOMIC_REACTION_ACE_FACTORY_HPP

// FRENSIE Includes
#include "MonteCarlo_ElectroatomicReaction.hpp"
#include "Data_XSSEPRDataExtractor.hpp"
#include "Utility_HashBasedGridSearcher.hpp"
#include "MonteCarlo_BremsstrahlungAngularDistributionType.hpp"

namespace MonteCarlo{

//! The electroatomic reaction factory class that uses ACE data
class ElectroatomicReactionACEFactory
{

public:

  //! Create an cutoff elastic scattering electroatomic reaction
  static void createCutoffElasticReaction(
        const Data::XSSEPRDataExtractor& raw_electroatom_data,
        const Teuchos::ArrayRCP<const double>& energy_grid,
        const Teuchos::RCP<const Utility::HashBasedGridSearcher>& grid_searcher,
        std::shared_ptr<ElectroatomicReaction>& elastic_reaction,
        const double lower_cutoff_angle_cosine = 1.0 );

  //! Create an atomic excitation scattering electroatomic reaction
  static void createAtomicExcitationReaction(
	const Data::XSSEPRDataExtractor& raw_electroatom_data,
	const Teuchos::ArrayRCP<const double>& energy_grid,
    const Teuchos::RCP<const Utility::HashBasedGridSearcher>& grid_searcher,
	std::shared_ptr<ElectroatomicReaction>& atomic_excitation_reaction );

  //! Create the total electroionization electroatomic reaction
  static void createTotalElectroionizationReaction(
	const Data::XSSEPRDataExtractor& raw_electroatom_data,
	const Teuchos::ArrayRCP<const double>& energy_grid,
    const Teuchos::RCP<const Utility::HashBasedGridSearcher>& grid_searcher,
	std::shared_ptr<ElectroatomicReaction>& electroionization_reaction );

  //! Create the subshell electroionization electroatomic reactions
  static void createSubshellElectroionizationReactions(
        const Data::XSSEPRDataExtractor& raw_electroatom_data,
        const Teuchos::ArrayRCP<const double>& energy_grid,
        const Teuchos::RCP<const Utility::HashBasedGridSearcher>& grid_searcher,
        std::vector<std::shared_ptr<ElectroatomicReaction> >&
        electroionization_subshell_reactions );

  //! Create the bremsstrahlung electroatomic reaction
  static void createBremsstrahlungReaction(
	const Data::XSSEPRDataExtractor& raw_electroatom_data,
	const Teuchos::ArrayRCP<const double>& energy_grid,
    const Teuchos::RCP<const Utility::HashBasedGridSearcher>& grid_searcher,
	std::shared_ptr<ElectroatomicReaction>& bremsstrahlung_reactions,
	BremsstrahlungAngularDistributionType photon_distribution_function );

  //! Create a void absorption electroatomic reaction
  static void createVoidAbsorptionReaction(
        std::shared_ptr<ElectroatomicReaction>& void_absorption_reaction );

//protected:

  //! Remove the zeros from a cross section
  static void removeZerosFromCrossSection(
        const Teuchos::ArrayRCP<const double>& energy_grid,
        const Teuchos::ArrayView<const double>& raw_cross_section,
        Teuchos::ArrayRCP<double>& cross_section,
        unsigned& threshold_energy_index );

private:

  // Check if a value is not equal to zero
  static bool notEqualZero( double value );

  // Constructor
  ElectroatomicReactionACEFactory();
};

// Check if a value is not equal to zero
inline bool ElectroatomicReactionACEFactory::notEqualZero( double value )
{
  return value != 0.0;
}

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_ELECTROATOMIC_REACTION_ACE_FACTORY_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ElectroatomicReactionACEFactory.hpp
//---------------------------------------------------------------------------//
