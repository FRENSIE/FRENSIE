//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_AbsorptionPositronatomicReaction_def.hpp
//! \author Luke Kersting
//! \brief  The absorption positron-atomic reaction class decl.
//!
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_ABSORPTION_POSITRONATOMIC_REACTION_DEF_HPP
#define MONTE_CARLO_ABSORPTION_POSITRONATOMIC_REACTION_DEF_HPP

// FRENSIE Includes
#include "Utility_SortAlgorithms.hpp"
#include "Utility_ExplicitTemplateInstantiationMacros.hpp"
#include "Utility_DesignByContract.hpp"

namespace MonteCarlo{

// Constructor
template<typename InterpPolicy, bool processed_cross_section>
AbsorptionPositronatomicReaction<InterpPolicy,processed_cross_section>::AbsorptionPositronatomicReaction(
       const std::shared_ptr<const std::vector<double> >& incoming_energy_grid,
       const std::shared_ptr<const std::vector<double> >& cross_section,
       const size_t threshold_energy_index,
       const PositronatomicReactionType reaction )
  : BaseType( incoming_energy_grid,
              cross_section,
              threshold_energy_index ),
    d_reaction( reaction )
{ /* ... */ }

// Constructor
template<typename InterpPolicy, bool processed_cross_section>
AbsorptionPositronatomicReaction<InterpPolicy,processed_cross_section>::AbsorptionPositronatomicReaction(
       const std::shared_ptr<const std::vector<double> >& incoming_energy_grid,
       const std::shared_ptr<const std::vector<double> >& cross_section,
       const size_t threshold_energy_index,
       const std::shared_ptr<const Utility::HashBasedGridSearcher<double>>& grid_searcher,
       const PositronatomicReactionType reaction )
  : BaseType( incoming_energy_grid,
              cross_section,
              threshold_energy_index,
              grid_searcher ),
    d_reaction( reaction )
{ /* ... */ }

// Return the number of photons emitted from the rxn at the given energy
template<typename InterpPolicy, bool processed_cross_section>
unsigned AbsorptionPositronatomicReaction<InterpPolicy,processed_cross_section>::getNumberOfEmittedPhotons( const double energy ) const
{
  return 0u;
}

// Return the number of electrons emitted from the rxn at the given energy
template<typename InterpPolicy, bool processed_cross_section>
unsigned AbsorptionPositronatomicReaction<InterpPolicy,processed_cross_section>::getNumberOfEmittedElectrons( const double energy ) const
{
  return 0u;
}

// Return the number of positrons emitted from the rxn at the given energy
template<typename InterpPolicy, bool processed_cross_section>
unsigned AbsorptionPositronatomicReaction<InterpPolicy,processed_cross_section>::getNumberOfEmittedPositrons( const double energy ) const
{
  return 0u;
}

// Return the reaction type
template<typename InterpPolicy, bool processed_cross_section>
PositronatomicReactionType AbsorptionPositronatomicReaction<InterpPolicy,processed_cross_section>::getReactionType() const
{
  return d_reaction;
}

// Return the differential cross section
/*! \details It is assumed that the cross section and differential cross section
 *  are equivalent.
 */
template<typename InterpPolicy, bool processed_cross_section>
double AbsorptionPositronatomicReaction<InterpPolicy,processed_cross_section>::getDifferentialCrossSection(
    const double incoming_energy,
    const double outgoing_energy ) const
{
  return this->getCrossSection( incoming_energy );
}

// Simulate the reaction
template<typename InterpPolicy, bool processed_cross_section>
void AbsorptionPositronatomicReaction<InterpPolicy,processed_cross_section>::react(
         PositronState& positron,
         ParticleBank& bank,
         Data::SubshellType& shell_of_interaction ) const
{
  positron.setAsGone();

  shell_of_interaction =Data::UNKNOWN_SUBSHELL;
}

EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( AbsorptionPositronatomicReaction<Utility::LinLin,false> );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( AbsorptionPositronatomicReaction<Utility::LinLin,true> );

EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( AbsorptionPositronatomicReaction<Utility::LinLog,false> );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( AbsorptionPositronatomicReaction<Utility::LinLog,true> );

EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( AbsorptionPositronatomicReaction<Utility::LogLin,false> );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( AbsorptionPositronatomicReaction<Utility::LogLin,true> );

EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( AbsorptionPositronatomicReaction<Utility::LogLog,false> );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( AbsorptionPositronatomicReaction<Utility::LogLog,true> );

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_ABSORPTION_POSITRONATOMIC_REACTION_DEF_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_AbsorptionPositronatomicReaction_def.hpp
//---------------------------------------------------------------------------//
