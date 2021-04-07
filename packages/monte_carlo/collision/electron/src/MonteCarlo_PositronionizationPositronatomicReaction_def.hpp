//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_PositronionizationPositronatomicReaction_def.hpp
//! \author Luke Kersting
//! \brief  The electroionization electroatomic reaction class definition
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_POSITRONIONIZATION_POSITRONATOMIC_REACTION_DEF_HPP
#define MONTE_CARLO_POSITRONIONIZATION_POSITRONATOMIC_REACTION_DEF_HPP

// FRENSIE Includes
#include "Utility_ExplicitTemplateInstantiationMacros.hpp"
#include "Utility_DesignByContract.hpp"

namespace MonteCarlo{

// Basic Constructor
template<typename InterpPolicy, bool processed_cross_section>
PositronionizationPositronatomicReaction<InterpPolicy,processed_cross_section>::PositronionizationPositronatomicReaction(
       const std::shared_ptr<const std::vector<double> >& incoming_energy_grid,
       const std::shared_ptr<const std::vector<double> >& cross_section,
       const size_t threshold_energy_index )
  : BaseType( incoming_energy_grid,
              cross_section,
              threshold_energy_index )
{ /* ... */ }

// Constructor
template<typename InterpPolicy, bool processed_cross_section>
PositronionizationPositronatomicReaction<InterpPolicy,processed_cross_section>::PositronionizationPositronatomicReaction(
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
unsigned PositronionizationPositronatomicReaction<InterpPolicy,processed_cross_section>::getNumberOfEmittedPhotons( const double energy ) const
{
  return 0u;
}

// Return the number of electrons emitted from the rxn at the given energy
/*! \details The knock-on electron cannot be emitted unless we know the
 * subshell that was interacted with. The value returned does not include 
 * electrons from atomic relaxation.
 */
template<typename InterpPolicy, bool processed_cross_section>
unsigned PositronionizationPositronatomicReaction<InterpPolicy,processed_cross_section>::getNumberOfEmittedElectrons( const double energy ) const
{
  return 0u;
}

// Return the number of positrons emitted from the rxn at the given energy
template<typename InterpPolicy, bool processed_cross_section>
unsigned PositronionizationPositronatomicReaction<InterpPolicy,processed_cross_section>::getNumberOfEmittedPositrons( const double energy ) const
{
  if( energy >= this->getThresholdEnergy() )
    return 1u;
  else
    return 0u;
}

// Return the differential cross section
template<typename InterpPolicy, bool processed_cross_section>
double PositronionizationPositronatomicReaction<InterpPolicy,processed_cross_section>::getDifferentialCrossSection(
                const double incoming_energy,
                const double outgoing_energy ) const
{
  THROW_EXCEPTION( std::logic_error,
                   "The total electroionization reaction differential "
                   "cross section function has not been implemented");
}

// Return the reaction type
template<typename InterpPolicy, bool processed_cross_section>
PositronatomicReactionType PositronionizationPositronatomicReaction<InterpPolicy,processed_cross_section>::getReactionType() const
{
  return TOTAL_POSITRONIONIZATION_POSITRONATOMIC_REACTION;
}

// Simulate the reaction
template<typename InterpPolicy, bool processed_cross_section>
void PositronionizationPositronatomicReaction<InterpPolicy,processed_cross_section>::react(
                     PositronState& electron,
                     ParticleBank& bank,
                     Data::SubshellType& shell_of_interaction ) const
{
  electron.incrementCollisionNumber();

  shell_of_interaction =Data::UNKNOWN_SUBSHELL;

  THROW_EXCEPTION( std::logic_error,
                   "The total electroionization reaction scatter "
                   "function has not been implemented");
}

EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( PositronionizationPositronatomicReaction<Utility::LinLin,false> );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( PositronionizationPositronatomicReaction<Utility::LinLin,true> );

EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( PositronionizationPositronatomicReaction<Utility::LinLog,false> );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( PositronionizationPositronatomicReaction<Utility::LinLog,true> );

EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( PositronionizationPositronatomicReaction<Utility::LogLin,false> );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( PositronionizationPositronatomicReaction<Utility::LogLin,true> );

EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( PositronionizationPositronatomicReaction<Utility::LogLog,false> );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( PositronionizationPositronatomicReaction<Utility::LogLog,true> );

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_POSITRONIONIZATION_POSITRONATOMIC_REACTION_DEF_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_PositronionizationPositronatomicReaction_def.hpp
//---------------------------------------------------------------------------//
