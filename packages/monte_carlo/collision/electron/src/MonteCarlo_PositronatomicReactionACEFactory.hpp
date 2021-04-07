//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_PositronatomicReactionACEFactory.hpp
//! \author Luke Kersting
//! \brief  The positron-atomic reaction ACE data factory declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_POSITRONATOMIC_REACTION_ACE_FACTORY_HPP
#define MONTE_CARLO_POSITRONATOMIC_REACTION_ACE_FACTORY_HPP

// FRENSIE Includes
#include "MonteCarlo_PositronatomicReaction.hpp"
#include "Data_XSSEPRDataExtractor.hpp"
#include "Utility_HashBasedGridSearcher.hpp"
#include "MonteCarlo_BremsstrahlungAngularDistributionType.hpp"

namespace MonteCarlo{

//! The positron-atomic reaction factory class that uses ACE data
class PositronatomicReactionACEFactory
{

public:

  //! Create a Decoupled elastic scattering positron-atomic reaction
  static void createDecoupledElasticReaction(
      const Data::XSSEPRDataExtractor& raw_positronatom_data,
      const std::shared_ptr<const std::vector<double> >& energy_grid,
      const std::shared_ptr<const Utility::HashBasedGridSearcher<double>>& grid_searcher,
      std::shared_ptr<const PositronatomicReaction>& elastic_reaction );

  //! Create an cutoff elastic scattering positron-atomic reaction
  static void createCutoffElasticReaction(
      const Data::XSSEPRDataExtractor& raw_positronatom_data,
      const std::shared_ptr<const std::vector<double> >& energy_grid,
      const std::shared_ptr<const Utility::HashBasedGridSearcher<double>>& grid_searcher,
      std::shared_ptr<const PositronatomicReaction>& elastic_reaction );

  //! Create a screened Rutherford elastic scattering positron-atomic reaction
  static void createScreenedRutherfordElasticReaction(
      const Data::XSSEPRDataExtractor& raw_positronatom_data,
      const std::shared_ptr<const std::vector<double> >& energy_grid,
      const std::shared_ptr<const Utility::HashBasedGridSearcher<double>>& grid_searcher,
      std::shared_ptr<const PositronatomicReaction>& elastic_reaction );

  //! Create an atomic excitation scattering positron-atomic reaction
  static void createAtomicExcitationReaction(
      const Data::XSSEPRDataExtractor& raw_positronatom_data,
      const std::shared_ptr<const std::vector<double> >& energy_grid,
      const std::shared_ptr<const Utility::HashBasedGridSearcher<double>>& grid_searcher,
      std::shared_ptr<const PositronatomicReaction>& atomic_excitation_reaction );

  //! Create the total electroionization positron-atomic reaction
  static void createTotalPositronionizationReaction(
      const Data::XSSEPRDataExtractor& raw_positronatom_data,
      const std::shared_ptr<const std::vector<double> >& energy_grid,
      const std::shared_ptr<const Utility::HashBasedGridSearcher<double>>& grid_searcher,
      std::shared_ptr<const PositronatomicReaction>& electroionization_reaction );

  //! Create the subshell electroionization positron-atomic reaction
  static void createSubshellPositronionizationReaction(
      const Data::XSSEPRDataExtractor& raw_positronatom_data,
      const std::shared_ptr<const std::vector<double> >& energy_grid,
      const std::shared_ptr<const Utility::HashBasedGridSearcher<double>>& grid_searcher,
      std::shared_ptr<const PositronatomicReaction>& electroionization_subshell_reaction,
      const unsigned endf_subshell_designator );

  //! Create the subshell electroionization positron-atomic reactions
  static void createSubshellPositronionizationReactions(
      const Data::XSSEPRDataExtractor& raw_positronatom_data,
      const std::shared_ptr<const std::vector<double> >& energy_grid,
      const std::shared_ptr<const Utility::HashBasedGridSearcher<double>>& grid_searcher,
      std::vector<std::shared_ptr<const PositronatomicReaction> >&
        electroionization_subshell_reactions );

  //! Create the bremsstrahlung positron-atomic reaction
  static void createBremsstrahlungReaction(
      const Data::XSSEPRDataExtractor& raw_positronatom_data,
      const std::shared_ptr<const std::vector<double> >& energy_grid,
      const std::shared_ptr<const Utility::HashBasedGridSearcher<double>>& grid_searcher,
      std::shared_ptr<const PositronatomicReaction>& bremsstrahlung_reaction,
      BremsstrahlungAngularDistributionType photon_distribution_function );

  //! Create a void absorption positron-atomic reaction
  static void createVoidAbsorptionReaction(
      std::shared_ptr<const PositronatomicReaction>& void_absorption_reaction );

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
  PositronatomicReactionACEFactory();
};

// Check if a value is not equal to zero
inline bool PositronatomicReactionACEFactory::notEqualZero( double value )
{
  return value != 0.0;
}

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_POSITRONATOMIC_REACTION_ACE_FACTORY_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_PositronatomicReactionACEFactory.hpp
//---------------------------------------------------------------------------//
