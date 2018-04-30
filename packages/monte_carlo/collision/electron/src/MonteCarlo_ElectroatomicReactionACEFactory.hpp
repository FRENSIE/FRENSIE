//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ElectroatomicReactionACEFactory.hpp
//! \author Luke Kersting
//! \brief  The electroatomic reaction ACE data factory declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_ELECTROATOMIC_REACTION_ACE_FACTORY_HPP
#define MONTE_CARLO_ELECTROATOMIC_REACTION_ACE_FACTORY_HPP

// Std Lib Includes
#include <memory>

// FRENSIE Includes
#include "MonteCarlo_ElectroatomicReaction.hpp"
#include "MonteCarlo_BremsstrahlungAngularDistributionType.hpp"
#include "Data_XSSEPRDataExtractor.hpp"
#include "Utility_HashBasedGridSearcher.hpp"
#include "Utility_ArrayView.hpp"
#include "Utility_Vector.hpp"

namespace MonteCarlo{

//! The electroatomic reaction factory class that uses ACE data
class ElectroatomicReactionACEFactory
{

public:

  //! Create a Decoupled elastic scattering electroatomic reaction
  static void createDecoupledElasticReaction(
      const Data::XSSEPRDataExtractor& raw_electroatom_data,
      const std::shared_ptr<const std::vector<double> >& energy_grid,
      const std::shared_ptr<const Utility::HashBasedGridSearcher<double>>& grid_searcher,
      std::shared_ptr<const ElectroatomicReaction>& elastic_reaction );

  //! Create an cutoff elastic scattering electroatomic reaction
  static void createCutoffElasticReaction(
      const Data::XSSEPRDataExtractor& raw_electroatom_data,
      const std::shared_ptr<const std::vector<double> >& energy_grid,
      const std::shared_ptr<const Utility::HashBasedGridSearcher<double>>& grid_searcher,
      std::shared_ptr<const ElectroatomicReaction>& elastic_reaction );

  //! Create a screened Rutherford elastic scattering electroatomic reaction
  static void createScreenedRutherfordElasticReaction(
      const Data::XSSEPRDataExtractor& raw_electroatom_data,
      const std::shared_ptr<const std::vector<double> >& energy_grid,
      const std::shared_ptr<const Utility::HashBasedGridSearcher<double>>& grid_searcher,
      std::shared_ptr<const ElectroatomicReaction>& elastic_reaction );

  //! Create an atomic excitation scattering electroatomic reaction
  static void createAtomicExcitationReaction(
      const Data::XSSEPRDataExtractor& raw_electroatom_data,
      const std::shared_ptr<const std::vector<double> >& energy_grid,
      const std::shared_ptr<const Utility::HashBasedGridSearcher<double>>& grid_searcher,
      std::shared_ptr<const ElectroatomicReaction>& atomic_excitation_reaction );

  //! Create the total electroionization electroatomic reaction
  static void createTotalElectroionizationReaction(
      const Data::XSSEPRDataExtractor& raw_electroatom_data,
      const std::shared_ptr<const std::vector<double> >& energy_grid,
      const std::shared_ptr<const Utility::HashBasedGridSearcher<double>>& grid_searcher,
      std::shared_ptr<const ElectroatomicReaction>& electroionization_reaction );

  //! Create the subshell electroionization electroatomic reaction
  static void createSubshellElectroionizationReaction(
      const Data::XSSEPRDataExtractor& raw_electroatom_data,
      const std::shared_ptr<const std::vector<double> >& energy_grid,
      const std::shared_ptr<const Utility::HashBasedGridSearcher<double>>& grid_searcher,
      std::shared_ptr<const ElectroatomicReaction>& electroionization_subshell_reaction,
      const unsigned endf_subshell_designator );

  //! Create the subshell electroionization electroatomic reactions
  static void createSubshellElectroionizationReactions(
      const Data::XSSEPRDataExtractor& raw_electroatom_data,
      const std::shared_ptr<const std::vector<double> >& energy_grid,
      const std::shared_ptr<const Utility::HashBasedGridSearcher<double>>& grid_searcher,
      std::vector<std::shared_ptr<const ElectroatomicReaction> >&
        electroionization_subshell_reactions );

  //! Create the bremsstrahlung electroatomic reaction
  static void createBremsstrahlungReaction(
      const Data::XSSEPRDataExtractor& raw_electroatom_data,
      const std::shared_ptr<const std::vector<double> >& energy_grid,
      const std::shared_ptr<const Utility::HashBasedGridSearcher<double>>& grid_searcher,
      std::shared_ptr<const ElectroatomicReaction>& bremsstrahlung_reaction,
      BremsstrahlungAngularDistributionType photon_distribution_function );

  //! Create a void absorption electroatomic reaction
  static void createVoidAbsorptionReaction(
      std::shared_ptr<const ElectroatomicReaction>& void_absorption_reaction );

//protected:

  //! Remove the zeros from a cross section
  static void removeZerosFromCrossSection(
      const std::vector<double>& energy_grid,
      const Utility::ArrayView<const double>& raw_cross_section,
      std::vector<double>& cross_section,
      size_t& threshold_energy_index );

  //! Remove the zeros from a cross section
  static void removeZerosFromCrossSection(
      const std::vector<double>& energy_grid,
      const std::vector<double>& raw_cross_section,
      std::vector<double>& cross_section,
      size_t& threshold_energy_index );

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
