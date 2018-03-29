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
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Basic Constructor
template<typename InterpPolicy, bool processed_cross_section>
PositronionizationPositronatomicReaction<InterpPolicy,processed_cross_section>::PositronionizationPositronatomicReaction(
       const std::shared_ptr<const std::vector<double> >& incoming_energy_grid,
       const std::shared_ptr<const std::vector<double> >& cross_section,
       const unsigned threshold_energy_index )
  : BaseType( incoming_energy_grid,
              cross_section,
              threshold_energy_index )
{ /* ... */ }

// Constructor
template<typename InterpPolicy, bool processed_cross_section>
PositronionizationPositronatomicReaction<InterpPolicy,processed_cross_section>::PositronionizationPositronatomicReaction(
       const std::shared_ptr<const std::vector<double> >& incoming_energy_grid,
       const std::shared_ptr<const std::vector<double> >& cross_section,
       const unsigned threshold_energy_index,
       const std::shared_ptr<const Utility::HashBasedGridSearcher>& grid_searcher )
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
template<typename InterpPolicy, bool processed_cross_section>
unsigned PositronionizationPositronatomicReaction<InterpPolicy,processed_cross_section>::getNumberOfEmittedElectrons( const double energy ) const
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
                   "Error! The total electroionization reaction differential "
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
                   "Error! The total electroionization reaction scatter "
                   "function has not been implemented");
}

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_POSITRONIONIZATION_POSITRONATOMIC_REACTION_DEF_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_PositronionizationPositronatomicReaction_def.hpp
//---------------------------------------------------------------------------//
