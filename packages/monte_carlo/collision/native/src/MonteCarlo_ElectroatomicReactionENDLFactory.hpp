//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ElectroatomicReactionENDLFactory.hpp
//! \author Luke Kersting
//! \brief  The electroatomic reaction ENDL data factory declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_PHOTOATOMIC_REACTION_ENDL_FACTORY_HPP
#define MONTE_CARLO_PHOTOATOMIC_REACTION_ENDL_FACTORY_HPP

// FRENSIE Includes
#include "MonteCarlo_ElectroatomicReaction.hpp"
#include "MonteCarlo_BremsstrahlungElectroatomicReaction.hpp"
#include "MonteCarlo_ElectroionizationSubshellElectroatomicReaction.hpp"
#include "Data_ENDLDataContainer.hpp"
#include "Utility_StandardHashBasedGridSearcher.hpp"
#include "MonteCarlo_BremsstrahlungAngularDistributionType.hpp"

namespace MonteCarlo{

//! The electroatomic reaction factory class that uses ENDL data
class ElectroatomicReactionENDLFactory
{

public:

  typedef ElectroionizationSubshellElectroatomicReaction<Utility::LinLin>
    ElectroionizationReaction;

  typedef BremsstrahlungElectroatomicReaction<Utility::LinLin>
    BremsstrahlungReaction;

/*
  //! Create an analog elastic scattering electroatomic reaction
  static void createAnalogElasticReaction(
    const Data::ENDLDataContainer& raw_electroatom_data,
    std::shared_ptr<ElectroatomicReaction>& elastic_reaction );

  //! Create a hybrid elastic scattering electroatomic reaction
  static void createHybridElasticReaction(
    const Data::ENDLDataContainer& raw_electroatom_data,
    std::shared_ptr<ElectroatomicReaction>& elastic_reaction,
    const double cutoff_angle_cosine = 0.9 );

  //! Create an cutoff elastic scattering electroatomic reaction
  static void createCutoffElasticReaction(
    const Data::ENDLDataContainer& raw_electroatom_data,
    std::shared_ptr<ElectroatomicReaction>& elastic_reaction,
    const double cutoff_angle_cosine = 1.0 );

  //! Create a screened Rutherford elastic scattering electroatomic reaction
  static void createScreenedRutherfordElasticReaction(
    const Data::ENDLDataContainer& raw_electroatom_data,
    std::shared_ptr<ElectroatomicReaction>& elastic_reaction,
    const double cutoff_angle_cosine = 1.0 );

  //! Create the moment preserving elastic scattering electroatomic reaction
  static void createMomentPreservingElasticReaction(
    const Data::ENDLDataContainer& raw_electroatom_data,
    std::shared_ptr<ElectroatomicReaction>& elastic_reaction,
    const double cutoff_angle_cosine = 0.9 );

  //! Create an atomic excitation scattering electroatomic reaction
  static void createAtomicExcitationReaction(
	const Data::ENDLDataContainer& raw_electroatom_data,
	std::shared_ptr<ElectroatomicReaction>& atomic_excitation_reaction );
*/

  //! Create the subshell electroionization electroatomic reaction
  static void createSubshellElectroionizationReaction(
    const Data::ENDLDataContainer& raw_electroatom_data,
    const std::vector<double>& ionization_recoil_energy_grid,
    const unsigned shell,
    std::shared_ptr<ElectroionizationReaction>& electroionization_subshell_reaction );

  //! Create the subshell electroionization electroatomic reactions
  static void createSubshellElectroionizationReactions(
    const Data::ENDLDataContainer& raw_electroatom_data,
    const std::map<unsigned, std::vector<double> >& ionization_recoil_energy_grids,
    std::vector<std::shared_ptr<ElectroionizationReaction> >&
        electroionization_subshell_reactions );

  //! Create the bremsstrahlung electroatomic reaction
  static void createBremsstrahlungReaction(
    const Data::ENDLDataContainer& raw_electroatom_data,
    const std::vector<double>& bremsstrahlung_photon_energy_grid,
	std::shared_ptr<BremsstrahlungReaction>&
        bremsstrahlung_reaction,
	BremsstrahlungAngularDistributionType photon_distribution_function );
/*
  //! Create a void absorption electroatomic reaction
  static void createVoidAbsorptionReaction(
    std::shared_ptr<ElectroatomicReaction>& void_absorption_reaction );
*/
private:

  // Check if a value is not equal to zero
  static bool notEqualZero( double value );

  // Constructor
  ElectroatomicReactionENDLFactory();
};

// Check if a value is not equal to zero
inline bool ElectroatomicReactionENDLFactory::notEqualZero( double value )
{
  return value != 0.0;
}

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_PHOTOATOMIC_REACTION_ENDL_FACTORY_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ElectroatomicReactionENDLFactory.hpp
//---------------------------------------------------------------------------//
