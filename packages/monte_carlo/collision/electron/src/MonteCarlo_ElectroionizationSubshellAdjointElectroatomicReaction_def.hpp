//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ElectroionizationSubshellAdjointElectroatomicReaction_def.hpp
//! \author Luke Kersting
//! \brief  The electroionization subshell adjoint electroatomic reaction class definition
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_ELECTROIONIZATION_SUBSHELL_ADJOINT_ELECTROATOMIC_REACTION_DEF_HPP
#define MONTE_CARLO_ELECTROIONIZATION_SUBSHELL_ADJOINT_ELECTROATOMIC_REACTION_DEF_HPP

// Boost Includes
#include <boost/function.hpp>
#include <boost/bind.hpp>

// FRENSIE Includes
#include "MonteCarlo_ElectroionizationAdjointElectroatomicReaction.hpp"
#include "MonteCarlo_AdjointElectroatomicReactionType.hpp"
#include "Utility_DesignByContract.hpp"

namespace MonteCarlo{

// Basic Constructor
/*! \details If the last couple of cross section values are zero the max energy
 *  index will be set to the last non-zero cross section value. All energies
 *  above the max energy index will return a cross section of zero.
 */
template<typename InterpPolicy, bool processed_cross_section>
ElectroionizationSubshellAdjointElectroatomicReaction<InterpPolicy,processed_cross_section>::ElectroionizationSubshellAdjointElectroatomicReaction(
    const std::shared_ptr<const std::vector<double> >& incoming_energy_grid,
    const std::shared_ptr<const std::vector<double> >& cross_section,
    const size_t threshold_energy_index,
    const Data::SubshellType interaction_subshell,
    const std::shared_ptr<ElectroionizationSubshellAdjointElectronScatteringDistribution>&
            electroionization_subshell_distribution )
  : BaseType( incoming_energy_grid,
              cross_section,
              threshold_energy_index ),
    d_interaction_subshell( interaction_subshell ),
    d_electroionization_subshell_distribution( electroionization_subshell_distribution ),
    d_reaction_type( convertSubshellEnumToElectroionizationAdjointElectroatomicReactionEnum(
                                                        interaction_subshell ) )
{
  // Make sure the interaction subshell is valid
  testPrecondition( interaction_subshell != Data::INVALID_SUBSHELL );
  testPrecondition( interaction_subshell !=Data::UNKNOWN_SUBSHELL );

  // Make sure the distribution data is valid
  testPrecondition( electroionization_subshell_distribution.use_count() > 0 );

  // Set the max energy index
  size_t max_energy_index = incoming_energy_grid->size() - threshold_energy_index - 1;

  while( cross_section->at(max_energy_index) == 0.0 )
    --max_energy_index;

  this->setMaxEnergyIndex( max_energy_index );
}


// Constructor
/*! \details If the last couple of cross section values are zero the max energy
 *  index will be set to the last non-zero cross section value. All energies
 *  above the max energy index will return a cross section of zero.
 */
template<typename InterpPolicy, bool processed_cross_section>
ElectroionizationSubshellAdjointElectroatomicReaction<InterpPolicy,processed_cross_section>::ElectroionizationSubshellAdjointElectroatomicReaction(
    const std::shared_ptr<const std::vector<double> >& incoming_energy_grid,
    const std::shared_ptr<const std::vector<double> >& cross_section,
    const size_t threshold_energy_index,
    const std::shared_ptr<const Utility::HashBasedGridSearcher<double>>& grid_searcher,
    const Data::SubshellType interaction_subshell,
    const std::shared_ptr<ElectroionizationSubshellAdjointElectronScatteringDistribution>&
            electroionization_subshell_distribution )
  : BaseType( incoming_energy_grid,
              cross_section,
              threshold_energy_index,
              grid_searcher ),
    d_interaction_subshell( interaction_subshell ),
    d_electroionization_subshell_distribution(
            electroionization_subshell_distribution ),
    d_reaction_type( convertSubshellEnumToElectroionizationAdjointElectroatomicReactionEnum(
            interaction_subshell ) )
{
  // Make sure the interaction subshell is valid
  testPrecondition( interaction_subshell != Data::INVALID_SUBSHELL );
  testPrecondition( interaction_subshell !=Data::UNKNOWN_SUBSHELL );

  // Make sure the distribution data is valid
  testPrecondition( electroionization_subshell_distribution.use_count() > 0 );

  // Set the max energy index
  size_t max_energy_index = incoming_energy_grid->size() - threshold_energy_index - 1;

  while( cross_section->at(max_energy_index) == 0.0 )
    --max_energy_index;

  this->setMaxEnergyIndex( max_energy_index );
}

// Set the critical line energies
template<typename InterpPolicy, bool processed_cross_section>
void ElectroionizationSubshellAdjointElectroatomicReaction<InterpPolicy,processed_cross_section>::setCriticalLineEnergies(
                const std::shared_ptr<const std::vector<double> >& critical_line_energies )
{
  d_electroionization_subshell_distribution->setCriticalLineEnergies( critical_line_energies );
}

// Get the critical line energies
template<typename InterpPolicy, bool processed_cross_section>
const std::vector<double>&
ElectroionizationSubshellAdjointElectroatomicReaction<InterpPolicy,processed_cross_section>::getCriticalLineEnergies() const
{
  return d_electroionization_subshell_distribution->getCriticalLineEnergies();
}

// Simulate the reaction
template<typename InterpPolicy, bool processed_cross_section>
void ElectroionizationSubshellAdjointElectroatomicReaction<InterpPolicy,processed_cross_section>::react(
     AdjointElectronState& electron,
     ParticleBank& bank,
     Data::SubshellType& shell_of_interaction ) const
{
  d_electroionization_subshell_distribution->scatterAdjointElectron(
                                               electron,
                                               bank,
                                               shell_of_interaction);

  electron.incrementCollisionNumber();

  shell_of_interaction = d_interaction_subshell;
}

// Return the reaction type
template<typename InterpPolicy, bool processed_cross_section>
AdjointElectroatomicReactionType ElectroionizationSubshellAdjointElectroatomicReaction<InterpPolicy,processed_cross_section>::getReactionType() const
{
  return d_reaction_type;
}

// Get the interaction subshell (non-standard interface)
template<typename InterpPolicy, bool processed_cross_section>
unsigned ElectroionizationSubshellAdjointElectroatomicReaction<InterpPolicy,processed_cross_section>::getSubshell() const
{
  return d_interaction_subshell;
}

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_ELECTROIONIZATION_SUBSHELL_ADJOINT_ELECTROATOMIC_REACTION_DEF_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ElectroionizationSubshellAdjointElectroatomicReaction_def.hpp
//---------------------------------------------------------------------------//
