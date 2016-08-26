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
/*! \details Electroionization produces a secondary electron (knock-on) that is
 * indistinguishable from the primary scattered electron. The convention is to
 * treat the outgoing electron with the lower energy as the knock-on electron.
 * outgoing_energy_1 can be either the primary or secondary scattered electron.
 */
template<typename InterpPolicy, bool processed_cross_section>
double ElectroionizationSubshellElectroatomicReaction<InterpPolicy,processed_cross_section>::getDifferentialCrossSection(
    const double incoming_energy,
    const double outgoing_energy_1 ) const
{
  // Make sure the energies are valid
  testPrecondition( incoming_energy > 0.0 );
  testPrecondition( outgoing_energy_1 >= 0.0 );
  testPrecondition( outgoing_energy_1 <= incoming_energy );

  if ( !this->isEnergyWithinEnergyGrid( incoming_energy ) )
    return 0.0;

  // Evaluate the forward cross section at the incoming energy
  double forward_cs = this->getCrossSection( incoming_energy );

  // calcualte the energy of the second outgoing electron
  double outgoing_energy_2 = incoming_energy - outgoing_energy_1 -
    d_electroionization_subshell_distribution->getBindingEnergy();

  // If reaction is energetically impossible return zero
  if ( outgoing_energy_2 <= 0.0 )
    return 0.0;

  // Assume the lower of the two outgoing energies is the knock-on electron
  double knock_on_energy = std::min( outgoing_energy_1, outgoing_energy_2 );

  // The max tabulated knock-on energy for the incoming energy
  double max_knock_on_energy = 
    d_electroionization_subshell_distribution->getMaxSecondaryEnergyAtIncomingEnergy( incoming_energy );

  /* Due to roundoff errors in the tabulated data the physically allowable max
   * knock-on energy can be slightly higher than the max tabulated/interpolated
   * knock-on energy. In this case the max tabulated/interpolated knock-on
   * energy will be used instead, to ensure that a non-zero pdf is returned.
   */
  if ( knock_on_energy > max_knock_on_energy );
  {
    knock_on_energy = max_knock_on_energy;
  }

  // Sample the pdf using the energy of the knock-on electron
  double pdf = d_electroionization_subshell_distribution->evaluatePDF(
          incoming_energy,
          knock_on_energy );

if ( pdf <= 0.0 )
{
std::cout << std::setprecision(20) << "binding energy = " << d_electroionization_subshell_distribution->getBindingEnergy()
                                 << "\tknock_on_energy = " << knock_on_energy
                                 << "\tforward_cs = " << forward_cs << std::endl;

std::cout << std::setprecision(20) << "incoming_energy = " << incoming_energy
                                 << "\toutgoing_energy_1 = " << outgoing_energy_1
                                 << "\toutgoing_energy_2 = " << outgoing_energy_2 
                                 << "\tpdf = " << pdf << std::endl;
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
