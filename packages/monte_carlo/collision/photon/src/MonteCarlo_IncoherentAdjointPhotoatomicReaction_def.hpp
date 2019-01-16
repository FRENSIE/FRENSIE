//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_IncoherentAdjointPhotoatomicReaction_def.hpp
//! \author Alex Robinson
//! \brief  The incoherent adjoint photoatomic reaction class definition
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION_DEF_HPP
#define MONTE_CARLO_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION_DEF_HPP

// Std Lib Includes
#include <functional>

// FRENSIE Includes
#include "Utility_ExplicitTemplateInstantiationMacros.hpp"
#include "Utility_DesignByContract.hpp"

namespace MonteCarlo{

// Basic Contructor
template<typename InterpPolicy, bool processed_cross_section>
IncoherentAdjointPhotoatomicReaction<InterpPolicy,processed_cross_section>::IncoherentAdjointPhotoatomicReaction(
    const std::shared_ptr<const std::vector<double> >& incoming_energy_grid,
    const std::shared_ptr<const std::vector<double> >& cross_section,
    const size_t threshold_energy_index,
    const std::shared_ptr<IncoherentAdjointPhotonScatteringDistribution>&
    scattering_distribution )
  : BaseType( incoming_energy_grid, cross_section, threshold_energy_index ),
    d_scattering_distribution( scattering_distribution )
{
  // Make sure the form factor is valid
  testPrecondition( scattering_distribution.get() );
  testPrecondition( scattering_distribution->getMaxEnergy() ==
                    this->getMaxEnergy() );

  // Set the external integrated incoherent cross section evaluator
  d_scattering_distribution->setExternalIntegratedCrossSectionEvaluator(
                          std::bind<double>( &ThisType::getCrossSectionAdapter,
                                             this,
                                             std::placeholders::_1,
                                             std::placeholders::_2,
                                             std::placeholders::_3 ) );
}

// Constructor
template<typename InterpPolicy, bool processed_cross_section>
IncoherentAdjointPhotoatomicReaction<InterpPolicy,processed_cross_section>::IncoherentAdjointPhotoatomicReaction(
    const std::shared_ptr<const std::vector<double> >& incoming_energy_grid,
    const std::shared_ptr<const std::vector<double> >& cross_section,
    const size_t threshold_energy_index,
    const std::shared_ptr<const Utility::HashBasedGridSearcher<double> >&
    grid_searcher,
    const std::shared_ptr<IncoherentAdjointPhotonScatteringDistribution>&
    scattering_distribution )
  : BaseType( incoming_energy_grid,
              cross_section,
              threshold_energy_index,
              grid_searcher ),
    d_scattering_distribution( scattering_distribution )
{
  // Make sure the scattering distribution is valid
  testPrecondition( scattering_distribution.get() );
  testPrecondition( scattering_distribution->getMaxEnergy() ==
                    this->getMaxEnergy() );

  // Set the external integrated incoherent cross section evaluator
  d_scattering_distribution->setExternalIntegratedCrossSectionEvaluator(
                          std::bind<double>( &ThisType::getCrossSectionAdapter,
                                             this,
                                             std::placeholders::_1,
                                             std::placeholders::_2,
                                             std::placeholders::_3 ) );
}

// Adapter for the getCrossSection method for use with the scattering dist
template<typename InterpPolicy, bool processed_cross_section>
double IncoherentAdjointPhotoatomicReaction<InterpPolicy,processed_cross_section>::getCrossSectionAdapter(
                                                 const double energy,
                                                 const double max_energy,
                                                 const double precision ) const
{
  return this->getCrossSection( energy );
}

// Set the critical line energies
template<typename InterpPolicy, bool processed_cross_section>
void IncoherentAdjointPhotoatomicReaction<InterpPolicy,processed_cross_section>::setCriticalLineEnergies(
                const std::shared_ptr<const std::vector<double> >& critical_line_energies )
{
  d_scattering_distribution->setCriticalLineEnergies( critical_line_energies );
}

// Get the critical line energies
template<typename InterpPolicy, bool processed_cross_section>
const std::vector<double>&
IncoherentAdjointPhotoatomicReaction<InterpPolicy,processed_cross_section>::getCriticalLineEnergies() const
{
  return d_scattering_distribution->getCriticalLineEnergies();
}

// Return the number of adjoint photons emitted from the rxn at the given energy
template<typename InterpPolicy, bool processed_cross_section>
unsigned IncoherentAdjointPhotoatomicReaction<InterpPolicy,processed_cross_section>::getNumberOfEmittedAdjointPhotons( const double energy ) const
{
  if( energy >= this->getThresholdEnergy() && energy <= this->getMaxEnergy() )
    return 1u;
  else
    return 0u;
}

// Return the number of adjoint electrons emitted from the rxn at the given energy
template<typename InterpPolicy, bool processed_cross_section>
unsigned IncoherentAdjointPhotoatomicReaction<InterpPolicy,processed_cross_section>::getNumberOfEmittedAdjointElectrons( const double energy ) const
{
  return 0u;
}

// Return the number of adjoint positrons emitted from the rxn at the given energy
template<typename InterpPolicy, bool processed_cross_section>
unsigned IncoherentAdjointPhotoatomicReaction<InterpPolicy,processed_cross_section>::getNumberOfEmittedAdjointPositrons( const double energy ) const
{
  return 0u;
}

// Return the reaction type
template<typename InterpPolicy, bool processed_cross_section>
AdjointPhotoatomicReactionType IncoherentAdjointPhotoatomicReaction<InterpPolicy,processed_cross_section>::getReactionType() const
{
  return TOTAL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION;
}

// Simulate the reaction
template<typename InterpPolicy, bool processed_cross_section>
void IncoherentAdjointPhotoatomicReaction<InterpPolicy,processed_cross_section>::react( AdjointPhotonState& adjoint_photon,
	      ParticleBank& bank,
	      Data::SubshellType& shell_of_interaction ) const
{
  // Increment the collision number first so that any generated probe particles
  // have the correct collision number
  adjoint_photon.incrementCollisionNumber();
  
  d_scattering_distribution->scatterAdjointPhoton( adjoint_photon,
                                                   bank,
                                                   shell_of_interaction );
}

EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( IncoherentAdjointPhotoatomicReaction<Utility::LinLin,false> );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( IncoherentAdjointPhotoatomicReaction<Utility::LinLin,true> );

EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( IncoherentAdjointPhotoatomicReaction<Utility::LinLog,false> );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( IncoherentAdjointPhotoatomicReaction<Utility::LinLog,true> );

EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( IncoherentAdjointPhotoatomicReaction<Utility::LogLin,false> );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( IncoherentAdjointPhotoatomicReaction<Utility::LogLin,true> );

EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( IncoherentAdjointPhotoatomicReaction<Utility::LogLog,false> );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( IncoherentAdjointPhotoatomicReaction<Utility::LogLog,true> );
  
} // end MonteCarlo namespace

#endif // MONTE_CARLO_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION_DEF_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_IncoherentAdjointPhotoatomicReaction_def.hpp
//---------------------------------------------------------------------------//
