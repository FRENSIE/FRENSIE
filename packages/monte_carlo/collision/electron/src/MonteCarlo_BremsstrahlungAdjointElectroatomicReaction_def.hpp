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
#include "Utility_DesignByContract.hpp"

namespace MonteCarlo{

// Basic Constructor
/*! \details If the last couple of cross section values are zero the max energy
 *  index will be set to the last non-zero cross section value. All energies
 *  above the max energy index will return a cross section of zero.
 */
template<typename InterpPolicy, bool processed_cross_section>
BremsstrahlungAdjointElectroatomicReaction<InterpPolicy,processed_cross_section>::BremsstrahlungAdjointElectroatomicReaction(
    const std::shared_ptr<const std::vector<double> >& incoming_energy_grid,
    const std::shared_ptr<const std::vector<double> >& cross_section,
    const size_t threshold_energy_index,
    const std::shared_ptr<BremsstrahlungAdjointElectronScatteringDistribution>&
            bremsstrahlung_distribution )
  : BaseType( incoming_energy_grid,
              cross_section,
              threshold_energy_index ),
    d_bremsstrahlung_distribution( bremsstrahlung_distribution )
{
  // Make sure the energy gain distribution data is valid
  testPrecondition( bremsstrahlung_distribution.use_count() > 0 );

  // Set the max energy index
  size_t max_energy_index = incoming_energy_grid->size() - threshold_energy_index - 1;

  // Check if the cross section at max_energy_index is zero
  while( cross_section->at(max_energy_index) == 0.0 )
    --max_energy_index;

  this->setMaxEnergyIndex( max_energy_index );
}

// Constructor
/*! \details If the last couple of cross section values are zero the max energy
 *  index will be set to the last non-zero cross section value. All energies
 *  above the max energy index will return a cross section of zero.
 */
template<typename InterpPolicy, bool processed_cross_section>
BremsstrahlungAdjointElectroatomicReaction<InterpPolicy,processed_cross_section>::BremsstrahlungAdjointElectroatomicReaction(
    const std::shared_ptr<const std::vector<double> >& incoming_energy_grid,
    const std::shared_ptr<const std::vector<double> >& cross_section,
    const size_t threshold_energy_index,
    const std::shared_ptr<const Utility::HashBasedGridSearcher<double>>& grid_searcher,
    const std::shared_ptr<BremsstrahlungAdjointElectronScatteringDistribution>&
            bremsstrahlung_distribution )
  : BaseType( incoming_energy_grid,
              cross_section,
              threshold_energy_index,
              grid_searcher ),
    d_bremsstrahlung_distribution( bremsstrahlung_distribution )
{
  // Make sure the energy gain distribution data is valid
  testPrecondition( bremsstrahlung_distribution.use_count() > 0 );

  // Set the max energy index
  size_t max_energy_index = incoming_energy_grid->size() - threshold_energy_index - 1;

  while( cross_section->at(max_energy_index) == 0.0 )
    --max_energy_index;

  this->setMaxEnergyIndex( max_energy_index );
}

// Set the critical line energies
template<typename InterpPolicy, bool processed_cross_section>
void BremsstrahlungAdjointElectroatomicReaction<InterpPolicy,processed_cross_section>::setCriticalLineEnergies(
                const std::shared_ptr<const std::vector<double> >& critical_line_energies )
{
  d_bremsstrahlung_distribution->setCriticalLineEnergies( critical_line_energies );
}

// Get the critical line energies
template<typename InterpPolicy, bool processed_cross_section>
const std::vector<double>&
BremsstrahlungAdjointElectroatomicReaction<InterpPolicy,processed_cross_section>::getCriticalLineEnergies() const
{
  return d_bremsstrahlung_distribution->getCriticalLineEnergies();
}

// Return the number of adjoint photons emitted from the rxn at the given energy
template<typename InterpPolicy, bool processed_cross_section>
unsigned BremsstrahlungAdjointElectroatomicReaction<InterpPolicy,processed_cross_section>::getNumberOfEmittedAdjointPhotons( const double energy ) const
{
  return 0u;
}

// Return the number of adjoint electrons emitted from the rxn at the given energy
template<typename InterpPolicy, bool processed_cross_section>
unsigned BremsstrahlungAdjointElectroatomicReaction<InterpPolicy,processed_cross_section>::getNumberOfEmittedAdjointElectrons( const double energy ) const
{
  return 1u;
}

// Return the number of adjoint positrons emitted from the rxn at the given energy
template<typename InterpPolicy, bool processed_cross_section>
unsigned BremsstrahlungAdjointElectroatomicReaction<InterpPolicy,processed_cross_section>::getNumberOfEmittedAdjointPositrons( const double energy ) const
{
  return 0u;
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
}

EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( BremsstrahlungAdjointElectroatomicReaction<Utility::LinLin,false> );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( BremsstrahlungAdjointElectroatomicReaction<Utility::LinLin,true> );

EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( BremsstrahlungAdjointElectroatomicReaction<Utility::LogLog,false> );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( BremsstrahlungAdjointElectroatomicReaction<Utility::LogLog,true> );

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_BREMSSTRAHLUNG_ADJOINT_ELECTROATOMIC_REACTION_DEF_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_BremsstrahlungAdjointElectroatomicReaction_def.hpp
//---------------------------------------------------------------------------//
