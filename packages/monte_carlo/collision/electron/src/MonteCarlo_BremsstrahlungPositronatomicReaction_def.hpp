//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_BremsstrahlungPositronatomicReaction_def.hpp
//! \author Luke Kersting
//! \brief  The bremsstrahlung positron-atomic reaction class definition
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_BREMSSTRAHLUNG_POSITRONATOMIC_REACTION_DEF_HPP
#define MONTE_CARLO_BREMSSTRAHLUNG_POSITRONATOMIC_REACTION_DEF_HPP

// FRENSIE Includes
#include "Utility_SortAlgorithms.hpp"
#include "Utility_ExplicitTemplateInstantiationMacros.hpp"
#include "Utility_DesignByContract.hpp"

namespace MonteCarlo{

// Basic Constructor
template<typename InterpPolicy, bool processed_cross_section>
BremsstrahlungPositronatomicReaction<InterpPolicy,processed_cross_section>::BremsstrahlungPositronatomicReaction(
       const std::shared_ptr<const std::vector<double> >& incoming_energy_grid,
       const std::shared_ptr<const std::vector<double> >& cross_section,
       const size_t threshold_energy_index,
       const std::shared_ptr<const BremsstrahlungElectronScatteringDistribution>&
              bremsstrahlung_distribution )
  : BaseType( incoming_energy_grid,
              cross_section,
              threshold_energy_index ),
    d_bremsstrahlung_distribution( bremsstrahlung_distribution )
{
  // Make sure the bremsstrahlung scattering distribution data is valid
  testPrecondition( bremsstrahlung_distribution.use_count() > 0 );
}

// Constructor
template<typename InterpPolicy, bool processed_cross_section>
BremsstrahlungPositronatomicReaction<InterpPolicy,processed_cross_section>::BremsstrahlungPositronatomicReaction(
       const std::shared_ptr<const std::vector<double> >& incoming_energy_grid,
       const std::shared_ptr<const std::vector<double> >& cross_section,
       const size_t threshold_energy_index,
       const std::shared_ptr<const Utility::HashBasedGridSearcher<double>>& grid_searcher,
       const std::shared_ptr<const BremsstrahlungElectronScatteringDistribution>&
              bremsstrahlung_distribution )
  : BaseType( incoming_energy_grid,
              cross_section,
              threshold_energy_index,
              grid_searcher ),
    d_bremsstrahlung_distribution( bremsstrahlung_distribution )
{
  // Make sure the bremsstrahlung scattering distribution data is valid
  testPrecondition( bremsstrahlung_distribution.use_count() > 0 );
}

// Return the number of photons emitted from the rxn at the given energy
template<typename InterpPolicy, bool processed_cross_section>
unsigned BremsstrahlungPositronatomicReaction<InterpPolicy,processed_cross_section>::getNumberOfEmittedPhotons( const double energy ) const
{
  if( energy >= this->getThresholdEnergy() )
    return 1u;
  else
    return 0u;
}

// Return the number of electrons emitted from the rxn at the given energy
template<typename InterpPolicy, bool processed_cross_section>
unsigned BremsstrahlungPositronatomicReaction<InterpPolicy,processed_cross_section>::getNumberOfEmittedElectrons( const double energy ) const
{
  return 0u;
}

// Return the number of positrons emitted from the rxn at the given energy
template<typename InterpPolicy, bool processed_cross_section>
unsigned BremsstrahlungPositronatomicReaction<InterpPolicy,processed_cross_section>::getNumberOfEmittedPositrons( const double energy ) const
{
  if( energy >= this->getThresholdEnergy() )
    return 1u;
  else
    return 0u;
}

// Return the reaction type
template<typename InterpPolicy, bool processed_cross_section>
PositronatomicReactionType BremsstrahlungPositronatomicReaction<InterpPolicy,processed_cross_section>::getReactionType() const
{
  return BREMSSTRAHLUNG_POSITRONATOMIC_REACTION;
}

// Return the differential cross section
template<typename InterpPolicy, bool processed_cross_section>
double BremsstrahlungPositronatomicReaction<InterpPolicy,processed_cross_section>::getDifferentialCrossSection(
    const double incoming_energy,
    const double outgoing_energy ) const
{
  // Make sure the energies are valid
  testPrecondition( incoming_energy > 0.0 );
  testPrecondition( outgoing_energy >= 0.0 );
  testPrecondition( outgoing_energy <= incoming_energy );

  if ( !this->isEnergyWithinEnergyGrid( incoming_energy ) )
    return 0.0;

  double outgoing_photon_energy = incoming_energy - outgoing_energy;

  // If the photon energy is less than the tables min photon energy return 0
  if ( outgoing_photon_energy < 1e-7 )
    return 0.0;

  double cross_section = this->getCrossSection( incoming_energy );

  // Evaluate the PDF at a given incoming and outgoing energy
  double pdf =
    d_bremsstrahlung_distribution->evaluatePDF( incoming_energy,
                                                outgoing_photon_energy );

  return cross_section*pdf;
}

// Simulate the reaction
template<typename InterpPolicy, bool processed_cross_section>
void BremsstrahlungPositronatomicReaction<InterpPolicy,processed_cross_section>::react(
         PositronState& positron,
         ParticleBank& bank,
         Data::SubshellType& shell_of_interaction ) const
{
  d_bremsstrahlung_distribution->scatterPositron( positron,
                                                  bank,
                                                  shell_of_interaction);

  positron.incrementCollisionNumber();

  // The shell of interaction is currently ignored
  shell_of_interaction =Data::UNKNOWN_SUBSHELL;
}

EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( BremsstrahlungPositronatomicReaction<Utility::LinLin,false> );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( BremsstrahlungPositronatomicReaction<Utility::LinLin,true> );

EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( BremsstrahlungPositronatomicReaction<Utility::LinLog,false> );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( BremsstrahlungPositronatomicReaction<Utility::LinLog,true> );

EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( BremsstrahlungPositronatomicReaction<Utility::LogLin,false> );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( BremsstrahlungPositronatomicReaction<Utility::LogLin,true> );

EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( BremsstrahlungPositronatomicReaction<Utility::LogLog,false> );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( BremsstrahlungPositronatomicReaction<Utility::LogLog,true> );

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_BREMSSTRAHLUNG_POSITRONATOMIC_REACTION_DEF_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_BremsstrahlungPositronatomicReaction_def.hpp
//---------------------------------------------------------------------------//
