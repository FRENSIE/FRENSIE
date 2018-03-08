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
  : BaseType( incoming_energy_grid,
              cross_section,
              threshold_energy_index ),
    d_interaction_subshell( interaction_subshell ),
    d_electroionization_subshell_distribution( electroionization_subshell_distribution ),
    d_reaction_type( convertSubshellEnumToElectroionizationElectroatomicReactionEnum(
                                                        interaction_subshell ) )
{
  // Make sure the interaction subshell is valid
  testPrecondition( interaction_subshell != Data::INVALID_SUBSHELL );
  testPrecondition( interaction_subshell !=Data::UNKNOWN_SUBSHELL );

  // Make sure the distribution data is valid
  testPrecondition( electroionization_subshell_distribution.use_count() > 0 );

  // Make sure the threshold energy isn't less than the binding energy
  testPrecondition( incoming_energy_grid[threshold_energy_index] >=
                    d_electroionization_subshell_distribution->getBindingEnergy() );
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
  : BaseType( incoming_energy_grid,
              cross_section,
              threshold_energy_index,
              grid_searcher ),
    d_interaction_subshell( interaction_subshell ),
    d_electroionization_subshell_distribution(
            electroionization_subshell_distribution ),
    d_reaction_type( convertSubshellEnumToElectroionizationElectroatomicReactionEnum(
            interaction_subshell ) )
{
  // Make sure the interaction subshell is valid
  testPrecondition( interaction_subshell != Data::INVALID_SUBSHELL );
  testPrecondition( interaction_subshell !=Data::UNKNOWN_SUBSHELL );

  // Make sure the distribution data is valid
  testPrecondition( electroionization_subshell_distribution.use_count() > 0 );

  // Make sure the threshold energy isn't less than the binding energy
  testPrecondition( incoming_energy_grid[threshold_energy_index] >=
                    d_electroionization_subshell_distribution->getBindingEnergy() );
}

// Return the number of photons emitted from the rxn at the given energy
//! \details This does not include photons from atomic relaxation.
template<typename InterpPolicy, bool processed_cross_section>
unsigned ElectroionizationSubshellElectroatomicReaction<InterpPolicy,processed_cross_section>::getNumberOfEmittedPhotons( const double energy ) const
{
  return 0u;
}

// Return the number of electrons emitted from the rxn at the given energy
template<typename InterpPolicy, bool processed_cross_section>
unsigned ElectroionizationSubshellElectroatomicReaction<InterpPolicy,processed_cross_section>::getNumberOfEmittedElectrons( const double energy ) const
{
  if( energy >= this->getThresholdEnergy() )
    return 1u;
  else
    return 0u;
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

  // Sample the pdf using the energy of the knock-on electron
  double pdf = d_electroionization_subshell_distribution->evaluatePDF(
          incoming_energy,
          outgoing_energy );

  return forward_cs*pdf;
}

// Simulate the reaction
template<typename InterpPolicy, bool processed_cross_section>
void ElectroionizationSubshellElectroatomicReaction<InterpPolicy,processed_cross_section>::react(
     ElectronState& electron,
     ParticleBank& bank,
     Data::SubshellType& shell_of_interaction ) const
{
  // Make sure the electron energy isn't less than the binding energy
  testPrecondition( electron.getEnergy() >=
                    d_electroionization_subshell_distribution->getBindingEnergy() );

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
