//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_BremsstrahlungAdjointElectroatomicReaction_def.hpp
//! \author Luke Kersting
//! \brief  The bremsstrahlung adjoint electroatomic reaction class definition
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_BREMSSTRAHLUNG_ADJOINT_ELECTROATOMIC_REACTION_DEF_HPP
#define MONTE_CARLO_BREMSSTRAHLUNG_ADJOINT_ELECTROATOMIC_REACTION_DEF_HPP

// FRENSIE Includes
#include "Utility_ExplicitTemplateInstantiationMacros.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Basic Constructor
template<typename InterpPolicy, bool processed_cross_section>
BremsstrahlungAdjointElectroatomicReaction<InterpPolicy,processed_cross_section>::BremsstrahlungAdjointElectroatomicReaction(
    const std::shared_ptr<const std::vector<double> >& incoming_energy_grid,
    const std::shared_ptr<const std::vector<double> >& cross_section,
    const size_t threshold_energy_index,
    const std::shared_ptr<const BremsstrahlungAdjointElectronScatteringDistribution>&
            bremsstrahlung_distribution )
  : BaseType( incoming_energy_grid,
              cross_section,
              threshold_energy_index ),
    d_bremsstrahlung_distribution( bremsstrahlung_distribution )
{
  // Make sure the energy gain distribution data is valid
  testPrecondition( bremsstrahlung_distribution.use_count() > 0 );
}

// Constructor
template<typename InterpPolicy, bool processed_cross_section>
BremsstrahlungAdjointElectroatomicReaction<InterpPolicy,processed_cross_section>::BremsstrahlungAdjointElectroatomicReaction(
       const std::shared_ptr<const std::vector<double> >& incoming_energy_grid,
       const std::shared_ptr<const std::vector<double> >& cross_section,
       const size_t threshold_energy_index,
       const std::shared_ptr<const Utility::HashBasedGridSearcher<double>>& grid_searcher,
       const std::shared_ptr<const BremsstrahlungAdjointElectronScatteringDistribution>&
            bremsstrahlung_distribution )
  : BaseType( incoming_energy_grid,
              cross_section,
              threshold_energy_index,
              grid_searcher ),
    d_bremsstrahlung_distribution( bremsstrahlung_distribution )
{
  // Make sure the energy gain distribution data is valid
  testPrecondition( bremsstrahlung_distribution.use_count() > 0 );
}

// Return the number of photons emitted from the rxn at the given energy
/*! \details This does not include photons from atomic relaxation.
 */
template<typename InterpPolicy, bool processed_cross_section>
unsigned BremsstrahlungAdjointElectroatomicReaction<InterpPolicy,processed_cross_section>::getNumberOfEmittedPhotons( const double energy ) const
{
  return 0u;
}

// Return the number of electrons emitted from the rxn at the given energy
template<typename InterpPolicy, bool processed_cross_section>
unsigned BremsstrahlungAdjointElectroatomicReaction<InterpPolicy,processed_cross_section>::getNumberOfEmittedElectrons( const double energy ) const
{
  return 1u;
}

// Return the reaction type
template<typename InterpPolicy, bool processed_cross_section>
AdjointElectroatomicReactionType BremsstrahlungAdjointElectroatomicReaction<InterpPolicy,processed_cross_section>::getReactionType() const
{
  return BREMSSTRAHLUNG_ADJOINT_ELECTROATOMIC_REACTION;
}

// Simulate the reaction
template<typename InterpPolicy, bool processed_cross_section>
void BremsstrahlungAdjointElectroatomicReaction<InterpPolicy,processed_cross_section>::react(
                             AdjointElectronState& electron,
                             ParticleBank& bank,
                             Data::SubshellType& shell_of_interaction ) const
{
  d_bremsstrahlung_distribution->scatterAdjointElectron( electron,
                                                         bank,
                                                         shell_of_interaction);

  electron.incrementCollisionNumber();

  // The shell of interaction is currently ignored
  shell_of_interaction =Data::UNKNOWN_SUBSHELL;
}

EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( BremsstrahlungAdjointElectroatomicReaction<Utility::LinLin,false> );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( BremsstrahlungAdjointElectroatomicReaction<Utility::LinLin,true> );

EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( BremsstrahlungAdjointElectroatomicReaction<Utility::LinLog,false> );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( BremsstrahlungAdjointElectroatomicReaction<Utility::LinLog,true> );

EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( BremsstrahlungAdjointElectroatomicReaction<Utility::LogLin,false> );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( BremsstrahlungAdjointElectroatomicReaction<Utility::LogLin,true> );

EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( BremsstrahlungAdjointElectroatomicReaction<Utility::LogLog,false> );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( BremsstrahlungAdjointElectroatomicReaction<Utility::LogLog,true> );

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_BREMSSTRAHLUNG_ADJOINT_ELECTROATOMIC_REACTION_DEF_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_BremsstrahlungAdjointElectroatomicReaction_def.hpp
//---------------------------------------------------------------------------//
