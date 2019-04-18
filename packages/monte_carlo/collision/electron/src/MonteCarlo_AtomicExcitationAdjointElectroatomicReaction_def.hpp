//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_AtomicExcitationAdjointElectroatomicReaction_def.hpp
//! \author Luke Kersting
//! \brief  The atomic excitation adjoint electroatomic reaction class definition
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_ATOMIC_EXCITATION_ADJOINT_ELECTROATOMIC_REACTION_DEF_HPP
#define MONTE_CARLO_ATOMIC_EXCITATION_ADJOINT_ELECTROATOMIC_REACTION_DEF_HPP

// FRENSIE Includes
#include "Utility_ExplicitTemplateInstantiationMacros.hpp"
#include "Utility_DesignByContract.hpp"

namespace MonteCarlo{

// Basic Constructor
template<typename InterpPolicy, bool processed_cross_section>
AtomicExcitationAdjointElectroatomicReaction<InterpPolicy,processed_cross_section>::AtomicExcitationAdjointElectroatomicReaction(
    const std::shared_ptr<const std::vector<double> >& incoming_energy_grid,
    const std::shared_ptr<const std::vector<double> >& cross_section,
    const size_t threshold_energy_index,
    const std::shared_ptr<const AtomicExcitationAdjointElectronScatteringDistribution>&
            energy_gain_distribution )
  : BaseType( incoming_energy_grid,
              cross_section,
              threshold_energy_index ),
    d_energy_gain_distribution( energy_gain_distribution )
{
  // Make sure the energy gain distribution data is valid
  testPrecondition( energy_gain_distribution.use_count() > 0 );

  // Set the max energy index
  size_t max_energy_index = incoming_energy_grid->size() - threshold_energy_index - 1;

  // Check if the cross section at max_energy_index is zero
  while( cross_section->at(max_energy_index) == 0.0 )
    --max_energy_index;

  this->setMaxEnergyIndex( max_energy_index );
}

// Constructor
template<typename InterpPolicy, bool processed_cross_section>
AtomicExcitationAdjointElectroatomicReaction<InterpPolicy,processed_cross_section>::AtomicExcitationAdjointElectroatomicReaction(
       const std::shared_ptr<const std::vector<double> >& incoming_energy_grid,
       const std::shared_ptr<const std::vector<double> >& cross_section,
       const size_t threshold_energy_index,
       const std::shared_ptr<const Utility::HashBasedGridSearcher<double>>& grid_searcher,
       const std::shared_ptr<const AtomicExcitationAdjointElectronScatteringDistribution>&
            energy_gain_distribution )
  : BaseType( incoming_energy_grid,
              cross_section,
              threshold_energy_index,
              grid_searcher ),
    d_energy_gain_distribution( energy_gain_distribution )
{
  // Make sure the energy gain distribution data is valid
  testPrecondition( energy_gain_distribution.use_count() > 0 );

  // Set the max energy index
  size_t max_energy_index = incoming_energy_grid->size() - threshold_energy_index - 1;

  // Check if the cross section at max_energy_index is zero
  while( cross_section->at(max_energy_index) == 0.0 )
    --max_energy_index;

  this->setMaxEnergyIndex( max_energy_index );
}

// Return the number of adjoint photons emitted from the rxn at the given energy
template<typename InterpPolicy, bool processed_cross_section>
unsigned AtomicExcitationAdjointElectroatomicReaction<InterpPolicy,processed_cross_section>::getNumberOfEmittedAdjointPhotons( const double energy ) const
{
  return 0u;
}

// Return the number of adjoint electrons emitted from the rxn at the given energy
template<typename InterpPolicy, bool processed_cross_section>
unsigned AtomicExcitationAdjointElectroatomicReaction<InterpPolicy,processed_cross_section>::getNumberOfEmittedAdjointElectrons( const double energy ) const
{
  return 1u;
}

// Return the number of adjoint positrons emitted from the rxn at the given energy
template<typename InterpPolicy, bool processed_cross_section>
unsigned AtomicExcitationAdjointElectroatomicReaction<InterpPolicy,processed_cross_section>::getNumberOfEmittedAdjointPositrons( const double energy ) const
{
  return 0u;
}

// Return the reaction type
template<typename InterpPolicy, bool processed_cross_section>
AdjointElectroatomicReactionType AtomicExcitationAdjointElectroatomicReaction<InterpPolicy,processed_cross_section>::getReactionType() const
{
  return ATOMIC_EXCITATION_ADJOINT_ELECTROATOMIC_REACTION;
}

// Simulate the reaction
template<typename InterpPolicy, bool processed_cross_section>
void AtomicExcitationAdjointElectroatomicReaction<InterpPolicy,processed_cross_section>::react(
                             AdjointElectronState& electron,
                             ParticleBank& bank,
                             Data::SubshellType& shell_of_interaction ) const
{
  d_energy_gain_distribution->scatterAdjointElectron( electron,
                                                      bank,
                                                      shell_of_interaction);

  electron.incrementCollisionNumber();

  // The shell of interaction is currently ignored
  shell_of_interaction =Data::UNKNOWN_SUBSHELL;
}

EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( AtomicExcitationAdjointElectroatomicReaction<Utility::LinLin,false> );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( AtomicExcitationAdjointElectroatomicReaction<Utility::LinLin,true> );

EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( AtomicExcitationAdjointElectroatomicReaction<Utility::LogLog,false> );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( AtomicExcitationAdjointElectroatomicReaction<Utility::LogLog,true> );

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_ATOMIC_EXCITATION_ADJOINT_ELECTROATOMIC_REACTION_DEF_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_AtomicExcitationAdjointElectroatomicReaction_def.hpp
//---------------------------------------------------------------------------//
