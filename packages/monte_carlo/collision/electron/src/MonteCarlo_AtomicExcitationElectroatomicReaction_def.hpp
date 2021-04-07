//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_AtomicExcitationElectroatomicReaction_def.hpp
//! \author Luke Kersting
//! \brief  The atomic excitation electroatomic reaction class definition
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_ATOMIC_EXCITATION_ELECTROATOMIC_REACTION_DEF_HPP
#define MONTE_CARLO_ATOMIC_EXCITATION_ELECTROATOMIC_REACTION_DEF_HPP

// FRENSIE Includes
#include "Utility_3DCartesianVectorHelpers.hpp"
#include "Utility_ExplicitTemplateInstantiationMacros.hpp"
#include "Utility_DesignByContract.hpp"

namespace MonteCarlo{

// Basic Constructor
template<typename InterpPolicy, bool processed_cross_section>
AtomicExcitationElectroatomicReaction<InterpPolicy,processed_cross_section>::AtomicExcitationElectroatomicReaction(
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
AtomicExcitationElectroatomicReaction<InterpPolicy,processed_cross_section>::AtomicExcitationElectroatomicReaction(
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
unsigned AtomicExcitationElectroatomicReaction<InterpPolicy,processed_cross_section>::getNumberOfEmittedPhotons( const double energy ) const
{
  return 0u;
}

// Return the number of electrons emitted from the rxn at the given energy
template<typename InterpPolicy, bool processed_cross_section>
unsigned AtomicExcitationElectroatomicReaction<InterpPolicy,processed_cross_section>::getNumberOfEmittedElectrons( const double energy ) const
{
  return 1u;
}

// Return the number of positrons emitted from the rxn at the given energy
template<typename InterpPolicy, bool processed_cross_section>
unsigned AtomicExcitationElectroatomicReaction<InterpPolicy,processed_cross_section>::getNumberOfEmittedPositrons( const double energy ) const
{
  return 0u;
}

// Return the differential cross section
template<typename InterpPolicy, bool processed_cross_section>
double AtomicExcitationElectroatomicReaction<InterpPolicy,processed_cross_section>::getDifferentialCrossSection(
                                const double incoming_energy,
                                const double outgoing_energy ) const
{
  return this->getCrossSection( incoming_energy );
}

// Return the reaction type
template<typename InterpPolicy, bool processed_cross_section>
ElectroatomicReactionType AtomicExcitationElectroatomicReaction<InterpPolicy,processed_cross_section>::getReactionType() const
{
  return ATOMIC_EXCITATION_ELECTROATOMIC_REACTION;
}

// Simulate the reaction
template<typename InterpPolicy, bool processed_cross_section>
void AtomicExcitationElectroatomicReaction<InterpPolicy,processed_cross_section>::react(
                             ElectronState& electron,
                             ParticleBank& bank,
                             Data::SubshellType& shell_of_interaction ) const
{
  d_energy_loss_distribution->scatterElectron( electron,
                                               bank,
                                               shell_of_interaction);

  electron.incrementCollisionNumber();

  // The shell of interaction is currently ignored
  shell_of_interaction =Data::UNKNOWN_SUBSHELL;
}

EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( AtomicExcitationElectroatomicReaction<Utility::LinLin,false> );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( AtomicExcitationElectroatomicReaction<Utility::LinLin,true> );

EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( AtomicExcitationElectroatomicReaction<Utility::LinLog,false> );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( AtomicExcitationElectroatomicReaction<Utility::LinLog,true> );

EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( AtomicExcitationElectroatomicReaction<Utility::LogLin,false> );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( AtomicExcitationElectroatomicReaction<Utility::LogLin,true> );

EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( AtomicExcitationElectroatomicReaction<Utility::LogLog,false> );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( AtomicExcitationElectroatomicReaction<Utility::LogLog,true> );

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_ATOMIC_EXCITATION_ELECTROATOMIC_REACTION_DEF_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_AtomicExcitationElectroatomicReaction_def.hpp
//---------------------------------------------------------------------------//
