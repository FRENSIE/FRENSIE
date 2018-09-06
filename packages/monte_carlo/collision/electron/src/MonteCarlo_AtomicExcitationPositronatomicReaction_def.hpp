//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_AtomicExcitationPositronatomicReaction_def.hpp
//! \author Luke Kersting
//! \brief  The atomic excitation positronatomic reaction class definition
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_ATOMIC_EXCITATION_POSITRONATOMIC_REACTION_DEF_HPP
#define MONTE_CARLO_ATOMIC_EXCITATION_POSITRONATOMIC_REACTION_DEF_HPP

// FRENSIE Includes
#include "Utility_ExplicitTemplateInstantiationMacros.hpp"
#include "Utility_DesignByContract.hpp"

namespace MonteCarlo{

// Basic Constructor
template<typename InterpPolicy, bool processed_cross_section>
AtomicExcitationPositronatomicReaction<InterpPolicy,processed_cross_section>::AtomicExcitationPositronatomicReaction(
       const std::shared_ptr<const std::vector<double> >& incoming_energy_grid,
       const std::shared_ptr<const std::vector<double> >& cross_section,
       const size_t threshold_energy_index,
       const std::shared_ptr<const AtomicExcitationElectronScatteringDistribution>&
            energy_loss_distribution )
  : BaseType( incoming_energy_grid,
              cross_section,
              threshold_energy_index ),
    d_energy_loss_distribution( energy_loss_distribution )
{
  // Make sure the energy loss distribution data is valid
  testPrecondition( energy_loss_distribution.use_count() > 0 );
}

// Constructor
template<typename InterpPolicy, bool processed_cross_section>
AtomicExcitationPositronatomicReaction<InterpPolicy,processed_cross_section>::AtomicExcitationPositronatomicReaction(
       const std::shared_ptr<const std::vector<double> >& incoming_energy_grid,
       const std::shared_ptr<const std::vector<double> >& cross_section,
       const size_t threshold_energy_index,
       const std::shared_ptr<const Utility::HashBasedGridSearcher<double>>& grid_searcher,
       const std::shared_ptr<const AtomicExcitationElectronScatteringDistribution>&
            energy_loss_distribution )
  : BaseType( incoming_energy_grid,
              cross_section,
              threshold_energy_index,
              grid_searcher ),
    d_energy_loss_distribution( energy_loss_distribution )
{
  // Make sure the energy loss distribution data is valid
  testPrecondition( energy_loss_distribution.use_count() > 0 );
}

// Return the number of photons emitted from the rxn at the given energy
template<typename InterpPolicy, bool processed_cross_section>
unsigned AtomicExcitationPositronatomicReaction<InterpPolicy,processed_cross_section>::getNumberOfEmittedPhotons( const double energy ) const
{
  return 0u;
}

// Return the number of electrons emitted from the rxn at the given energy
template<typename InterpPolicy, bool processed_cross_section>
unsigned AtomicExcitationPositronatomicReaction<InterpPolicy,processed_cross_section>::getNumberOfEmittedElectrons( const double energy ) const
{
  return 0u;
}

// Return the number of positrons emitted from the rxn at the given energy
template<typename InterpPolicy, bool processed_cross_section>
unsigned AtomicExcitationPositronatomicReaction<InterpPolicy,processed_cross_section>::getNumberOfEmittedPositrons( const double energy ) const
{
  return 1u;
}

// Return the differential cross section
template<typename InterpPolicy, bool processed_cross_section>
double AtomicExcitationPositronatomicReaction<InterpPolicy,processed_cross_section>::getDifferentialCrossSection(
                                const double incoming_energy,
                                const double outgoing_energy ) const
{
  return this->getCrossSection( incoming_energy );
}

// Return the reaction type
template<typename InterpPolicy, bool processed_cross_section>
PositronatomicReactionType AtomicExcitationPositronatomicReaction<InterpPolicy,processed_cross_section>::getReactionType() const
{
  return ATOMIC_EXCITATION_POSITRONATOMIC_REACTION;
}

// Simulate the reaction
template<typename InterpPolicy, bool processed_cross_section>
void AtomicExcitationPositronatomicReaction<InterpPolicy,processed_cross_section>::react(
                             PositronState& positron,
                             ParticleBank& bank,
                             Data::SubshellType& shell_of_interaction ) const
{
  d_energy_loss_distribution->scatterPositron( positron,
                                               bank,
                                               shell_of_interaction);

  positron.incrementCollisionNumber();

  // The shell of interaction is currently ignored
  shell_of_interaction =Data::UNKNOWN_SUBSHELL;
}

EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( AtomicExcitationPositronatomicReaction<Utility::LinLin,false> );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( AtomicExcitationPositronatomicReaction<Utility::LinLin,true> );

EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( AtomicExcitationPositronatomicReaction<Utility::LinLog,false> );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( AtomicExcitationPositronatomicReaction<Utility::LinLog,true> );

EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( AtomicExcitationPositronatomicReaction<Utility::LogLin,false> );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( AtomicExcitationPositronatomicReaction<Utility::LogLin,true> );

EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( AtomicExcitationPositronatomicReaction<Utility::LogLog,false> );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( AtomicExcitationPositronatomicReaction<Utility::LogLog,true> );

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_ATOMIC_EXCITATION_POSITRONATOMIC_REACTION_DEF_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_AtomicExcitationPositronatomicReaction_def.hpp
//---------------------------------------------------------------------------//
