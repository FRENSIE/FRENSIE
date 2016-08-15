//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ElectroionizationSubshellElectroatomicReaction_def.hpp
//! \author Luke Kersting
//! \brief  The electroionization subshell electroatomic reaction class definition
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_ELECTROIONIZATION_SUBSHELL_ELECTROATOMIC_REACTION_DEF_HPP
#define MONTE_CARLO_ELECTROIONIZATION_SUBSHELL_ELECTROATOMIC_REACTION_DEF_HPP

// Boost Includes
#include <boost/function.hpp>
#include <boost/bind.hpp>

// FRENSIE Includes
#include "MonteCarlo_ElectroionizationElectroatomicReaction.hpp"
#include "MonteCarlo_ElectroatomicReactionType.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Basic Constructor
template<typename InterpPolicy, bool processed_cross_section>
ElectroionizationSubshellElectroatomicReaction<InterpPolicy,processed_cross_section>::ElectroionizationSubshellElectroatomicReaction(
    const Teuchos::ArrayRCP<const double>& incoming_energy_grid,
    const Teuchos::ArrayRCP<const double>& cross_section,
    const unsigned threshold_energy_index,
    const Data::SubshellType interaction_subshell,
    const std::shared_ptr<const ElectroionizationSubshellElectronScatteringDistribution>&
            electroionization_subshell_distribution )
  : ElectroionizationElectroatomicReaction<InterpPolicy,processed_cross_section>(
                                                       incoming_energy_grid,
                                                       cross_section,
                                                       threshold_energy_index ),
    d_interaction_subshell( interaction_subshell ),
    d_electroionization_subshell_distribution( electroionization_subshell_distribution ),
    d_reaction_type( convertSubshellEnumToElectroatomicReactionEnum(
                                                        interaction_subshell ) )
{
  // Make sure the interaction subshell is valid
  testPrecondition( interaction_subshell != Data::INVALID_SUBSHELL );
  testPrecondition( interaction_subshell !=Data::UNKNOWN_SUBSHELL );

  // Make sure the distribution data is valid
  testPrecondition( electroionization_subshell_distribution.use_count() > 0 );
}


// Constructor
template<typename InterpPolicy, bool processed_cross_section>
ElectroionizationSubshellElectroatomicReaction<InterpPolicy,processed_cross_section>::ElectroionizationSubshellElectroatomicReaction(
    const Teuchos::ArrayRCP<const double>& incoming_energy_grid,
    const Teuchos::ArrayRCP<const double>& cross_section,
    const unsigned threshold_energy_index,
    const Teuchos::RCP<const Utility::HashBasedGridSearcher>& grid_searcher,
    const Data::SubshellType interaction_subshell,
    const std::shared_ptr<const ElectroionizationSubshellElectronScatteringDistribution>&
            electroionization_subshell_distribution )
  : ElectroionizationElectroatomicReaction<InterpPolicy,processed_cross_section>(
            incoming_energy_grid,
            cross_section,
            threshold_energy_index,
            grid_searcher ),
    d_interaction_subshell( interaction_subshell ),
    d_electroionization_subshell_distribution(
            electroionization_subshell_distribution ),
    d_reaction_type( convertSubshellEnumToElectroatomicReactionEnum(
            interaction_subshell ) )
{
  // Make sure the interaction subshell is valid
  testPrecondition( interaction_subshell != Data::INVALID_SUBSHELL );
  testPrecondition( interaction_subshell !=Data::UNKNOWN_SUBSHELL );

  // Make sure the distribution data is valid
  testPrecondition( electroionization_subshell_distribution.use_count() > 0 );
}

// Return the differential cross section
template<typename InterpPolicy, bool processed_cross_section>
double ElectroionizationSubshellElectroatomicReaction<InterpPolicy,processed_cross_section>::getDifferentialCrossSection(
    const double incoming_energy,
    const double outgoing_energy ) const
{
  // Make sure the energies are valid
  testPrecondition( incoming_energy > 0.0 );
  testPrecondition( outgoing_energy >= 0.0 );
  testPrecondition( outgoing_energy <= incoming_energy );

  if ( !this->isEnergyWithinEnergyGrid( incoming_energy ) )
    return 0.0;

  // Evaluate the forward cross section at the incoming energy
  double forward_cs = this->getCrossSection( incoming_energy );
  double pdf;

  // If reaction is energetically impossible return zero
  if ( incoming_energy - outgoing_energy <=
       d_electroionization_subshell_distribution->getBindingEnergy() )
    return 0.0;

  if ( outgoing_energy < incoming_energy*0.5 )
  {
    // Take the outgoing energy as the energy of the knock-on electron
    pdf =
      d_electroionization_subshell_distribution->evaluatePDF( incoming_energy,
                                                              outgoing_energy );
  }
  else
  {
  /* Calculate the energy of a knock on electron from a primary electron with
     outgoing energy = outgoing_energy */
  double knock_on_energy = incoming_energy - outgoing_energy -
    d_electroionization_subshell_distribution->getBindingEnergy();

  // Get the pdf for the incoming_energy and knock_on_energy
  pdf =
    d_electroionization_subshell_distribution->evaluatePDF( incoming_energy,
                                                            knock_on_energy );
  }
  return forward_cs*pdf;
}

// Return the differential cross section (efficient)
template<typename InterpPolicy, bool processed_cross_section>
double ElectroionizationSubshellElectroatomicReaction<InterpPolicy,processed_cross_section>::getDifferentialCrossSection(
    const unsigned incoming_energy_bin,
    const double incoming_energy,
    const double outgoing_energy ) const
{
  // Make sure the energies are valid
  testPrecondition( incoming_energy_bin >= 0 );
  testPrecondition( incoming_energy > 0.0 );
  testPrecondition( outgoing_energy >= 0.0 );
  testPrecondition( outgoing_energy <= incoming_energy );

  if ( !this->isEnergyWithinEnergyGrid( incoming_energy ) )
    return 0.0;

  // Evaluate the forward cross section at the incoming energy
  double forward_cs = this->getCrossSection( incoming_energy );

  double pdf;

  // If reaction is energetically impossible return zero
  if ( incoming_energy - outgoing_energy <=
       d_electroionization_subshell_distribution->getBindingEnergy() )
    return 0.0;

  if ( outgoing_energy < incoming_energy*0.5 )
  {
    // Take the outgoing energy as the energy of the knock-on electron
    pdf =
      d_electroionization_subshell_distribution->evaluatePDF( incoming_energy_bin,
                                                              incoming_energy,
                                                              outgoing_energy );
  }
  else
  {
  /* Calculate the energy of a knock on electron from a primary electron with
     outgoing energy = outgoing_energy */
  double knock_on_energy = incoming_energy - outgoing_energy -
    d_electroionization_subshell_distribution->getBindingEnergy();

  // Get the pdf for the incoming_energy and knock_on_energy
  pdf =
      d_electroionization_subshell_distribution->evaluatePDF( incoming_energy_bin,
                                                              incoming_energy,
                                                              knock_on_energy );
  }

  return forward_cs*pdf;
}

// Simulate the reaction
template<typename InterpPolicy, bool processed_cross_section>
void ElectroionizationSubshellElectroatomicReaction<InterpPolicy,processed_cross_section>::react(
				     ElectronState& electron,
				     ParticleBank& bank,
				     Data::SubshellType& shell_of_interaction ) const
{
  d_electroionization_subshell_distribution->scatterElectron(
                                               electron,
                                               bank,
                                               shell_of_interaction);

  electron.incrementCollisionNumber();

  shell_of_interaction = d_interaction_subshell;
}

// Return the reaction type
template<typename InterpPolicy, bool processed_cross_section>
ElectroatomicReactionType ElectroionizationSubshellElectroatomicReaction<InterpPolicy,processed_cross_section>::getReactionType() const
{
  return d_reaction_type;
}

// Get the interaction subshell (non-standard interface)
template<typename InterpPolicy, bool processed_cross_section>
unsigned ElectroionizationSubshellElectroatomicReaction<InterpPolicy,processed_cross_section>::getSubshell() const
{
  return d_interaction_subshell;
}

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_ELECTROIONIZATION_SUBSHELL_ELECTROATOMIC_REACTION_DEF_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ElectroionizationSubshellElectroatomicReaction_def.hpp
//---------------------------------------------------------------------------//
