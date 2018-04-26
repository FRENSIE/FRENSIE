//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ElectroionizationAdjointElectroatomicReaction_def.hpp
//! \author Luke Kersting
//! \brief  The electroionization adjoint electrotomic reaction class def.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION_DEF_HPP
#define MONTE_CARLO_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION_DEF_HPP

// FRENSIE Includes
#include "Utility_ExplicitTemplateInstantiationMacros.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Basic Constructor
template<typename InterpPolicy, bool processed_cross_section>
ElectroionizationAdjointElectroatomicReaction<InterpPolicy,processed_cross_section>::ElectroionizationAdjointElectroatomicReaction(
       const std::shared_ptr<const std::vector<double> >& incoming_energy_grid,
       const std::shared_ptr<const std::vector<double> >& cross_section,
       const size_t threshold_energy_index )
  : BaseType( incoming_energy_grid,
              cross_section,
              threshold_energy_index )
{ /* ... */ }

// Constructor
template<typename InterpPolicy, bool processed_cross_section>
ElectroionizationAdjointElectroatomicReaction<InterpPolicy,processed_cross_section>::ElectroionizationAdjointElectroatomicReaction(
       const std::shared_ptr<const std::vector<double> >& incoming_energy_grid,
       const std::shared_ptr<const std::vector<double> >& cross_section,
       const size_t threshold_energy_index,
       const std::shared_ptr<const Utility::HashBasedGridSearcher<double>>& grid_searcher )
  : BaseType( incoming_energy_grid,
              cross_section,
              threshold_energy_index,
              grid_searcher )
{ /* ... */ }

// Return the number of photons emitted from the rxn at the given energy
/*! \details This does not include photons from atomic relaxation.
 */
template<typename InterpPolicy, bool processed_cross_section>
unsigned ElectroionizationAdjointElectroatomicReaction<InterpPolicy,processed_cross_section>::getNumberOfEmittedPhotons( const double energy ) const
{
  return 0u;
}

// Return the number of electrons emitted from the rxn at the given energy
template<typename InterpPolicy, bool processed_cross_section>
unsigned ElectroionizationAdjointElectroatomicReaction<InterpPolicy,processed_cross_section>::getNumberOfEmittedElectrons( const double energy ) const
{
  return 0u;
}

// Return the reaction type
template<typename InterpPolicy, bool processed_cross_section>
AdjointElectroatomicReactionType ElectroionizationAdjointElectroatomicReaction<InterpPolicy,processed_cross_section>::getReactionType() const
{
  return TOTAL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION;
}

// Simulate the reaction
template<typename InterpPolicy, bool processed_cross_section>
void ElectroionizationAdjointElectroatomicReaction<InterpPolicy,processed_cross_section>::react(
         AdjointElectronState& electron,
         ParticleBank& bank,
         Data::SubshellType& shell_of_interaction ) const
{
  shell_of_interaction =Data::UNKNOWN_SUBSHELL;

  THROW_EXCEPTION( std::logic_error,
        "The total electroionization reaction scatter function has not been implemented");

}

EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( ElectroionizationAdjointElectroatomicReaction<Utility::LinLin,false> );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( ElectroionizationAdjointElectroatomicReaction<Utility::LinLin,true> );

EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( ElectroionizationAdjointElectroatomicReaction<Utility::LinLog,false> );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( ElectroionizationAdjointElectroatomicReaction<Utility::LinLog,true> );

EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( ElectroionizationAdjointElectroatomicReaction<Utility::LogLin,false> );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( ElectroionizationAdjointElectroatomicReaction<Utility::LogLin,true> );

EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( ElectroionizationAdjointElectroatomicReaction<Utility::LogLog,false> );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( ElectroionizationAdjointElectroatomicReaction<Utility::LogLog,true> );

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION_DEF_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ElectroionizationAdjointElectroatomicReaction_def.hpp
//---------------------------------------------------------------------------//
