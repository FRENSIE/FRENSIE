//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ElectroionizationElectroatomicReaction_def.hpp
//! \author Luke Kersting
//! \brief  The electroionization electroatomic reaction class definition
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_ELECTROIONIZATION_ELECTROATOMIC_REACTION_DEF_HPP
#define MONTE_CARLO_ELECTROIONIZATION_ELECTROATOMIC_REACTION_DEF_HPP

// FRENSIE Includes
#include "Utility_DesignByContract.hpp"
#include "Utility_ExplicitTemplateInstantiationMacros.hpp"
#include "Utility_RandomNumberGenerator.hpp"

namespace MonteCarlo{

// Basic Constructor
template<typename InterpPolicy, bool processed_cross_section>
ElectroionizationElectroatomicReaction<InterpPolicy,processed_cross_section>::ElectroionizationElectroatomicReaction(
  const std::shared_ptr<const std::vector<double> >& incoming_energy_grid,
  const std::shared_ptr<const std::vector<double> >& cross_section,
  const size_t threshold_energy_index,
  const std::vector<std::shared_ptr<const ElectroatomicReaction> >& subshell_reactions )
  : BaseType( incoming_energy_grid,
              cross_section,
              threshold_energy_index ),
    d_subshell_reactions( subshell_reactions )
{ /* ... */ }

// Constructor
template<typename InterpPolicy, bool processed_cross_section>
ElectroionizationElectroatomicReaction<InterpPolicy,processed_cross_section>::ElectroionizationElectroatomicReaction(
  const std::shared_ptr<const std::vector<double> >& incoming_energy_grid,
  const std::shared_ptr<const std::vector<double> >& cross_section,
  const size_t threshold_energy_index,
  const std::shared_ptr<const Utility::HashBasedGridSearcher<double>>& grid_searcher,
  const std::vector<std::shared_ptr<const ElectroatomicReaction> >& subshell_reactions )
  : BaseType( incoming_energy_grid,
              cross_section,
              threshold_energy_index,
              grid_searcher ),
    d_subshell_reactions( subshell_reactions )
{ /* ... */ }

// Return the number of photons emitted from the rxn at the given energy
/*! \details This does not include photons from atomic relaxation.
 */
template<typename InterpPolicy, bool processed_cross_section>
unsigned ElectroionizationElectroatomicReaction<InterpPolicy,processed_cross_section>::getNumberOfEmittedPhotons( const double energy ) const
{
  return 0u;
}

// Return the number of electrons emitted from the rxn at the given energy
/*! \details This does not include electrons from atomic relaxation.
 */
template<typename InterpPolicy, bool processed_cross_section>
unsigned ElectroionizationElectroatomicReaction<InterpPolicy,processed_cross_section>::getNumberOfEmittedElectrons( const double energy ) const
{
  if( energy >= this->getThresholdEnergy() )
    return 2u;
  else
    return 0u;
}

// Return the number of positrons emitted from the rxn at the given energy
template<typename InterpPolicy, bool processed_cross_section>
unsigned ElectroionizationElectroatomicReaction<InterpPolicy,processed_cross_section>::getNumberOfEmittedPositrons( const double energy ) const
{
  return 0u;
}

// Return the differential cross section
template<typename InterpPolicy, bool processed_cross_section>
double ElectroionizationElectroatomicReaction<InterpPolicy,processed_cross_section>::getDifferentialCrossSection(
                const double incoming_energy,
                const double outgoing_energy ) const
{
  THROW_EXCEPTION( std::logic_error,
                   "The total electroionization reaction differential "
                   "cross section function has not been implemented");
}

// Return the reaction type
template<typename InterpPolicy, bool processed_cross_section>
ElectroatomicReactionType ElectroionizationElectroatomicReaction<InterpPolicy,processed_cross_section>::getReactionType() const
{
  return TOTAL_ELECTROIONIZATION_ELECTROATOMIC_REACTION;
}

// Simulate the reaction
template<typename InterpPolicy, bool processed_cross_section>
void ElectroionizationElectroatomicReaction<InterpPolicy,processed_cross_section>::react(
                     ElectronState& electron,
                     ParticleBank& bank,
                     Data::SubshellType& shell_of_interaction ) const
{
  // Sum cross section over all subshells
  std::vector<double> cumulative_cross_section( d_subshell_reactions.size() );
  cumulative_cross_section[0] =
        d_subshell_reactions[0]->getCrossSection( electron.getEnergy() );

  for ( unsigned i = 1; i < d_subshell_reactions.size(); ++i )
  {
    cumulative_cross_section[i] = cumulative_cross_section[i-1] +
        d_subshell_reactions[i]->getCrossSection( electron.getEnergy() );
  }

  // Sample the subshell reaction
  double scaled_random_number = cumulative_cross_section.back()*
            Utility::RandomNumberGenerator::getRandomNumber<double>();

  for ( unsigned i = 0; i < d_subshell_reactions.size(); ++i )
  {
    if ( scaled_random_number <= cumulative_cross_section[i] )
    {
      d_subshell_reactions[i]->react( electron, bank, shell_of_interaction );
      break;
    }
  }
}

EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( ElectroionizationElectroatomicReaction<Utility::LinLin,false> );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( ElectroionizationElectroatomicReaction<Utility::LinLin,true> );

EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( ElectroionizationElectroatomicReaction<Utility::LinLog,false> );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( ElectroionizationElectroatomicReaction<Utility::LinLog,true> );

EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( ElectroionizationElectroatomicReaction<Utility::LogLin,false> );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( ElectroionizationElectroatomicReaction<Utility::LogLin,true> );

EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( ElectroionizationElectroatomicReaction<Utility::LogLog,false> );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( ElectroionizationElectroatomicReaction<Utility::LogLog,true> );

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_ELECTROIONIZATION_ELECTROATOMIC_REACTION_DEF_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ElectroionizationElectroatomicReaction_def.hpp
//---------------------------------------------------------------------------//
