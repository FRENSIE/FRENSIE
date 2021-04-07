//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_CoherentAdjointPhotoatomicReaction_def.hpp
//! \author Alex Robinson
//! \brief  The coherent adjoint photoatomic reaction class decl.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_COHERENT_ADJOINT_PHOTOATOMIC_REACTION_DEF_HPP
#define MONTE_CARLO_COHERENT_ADJOINT_PHOTOATOMIC_REACTION_DEF_HPP

// FRENSIE Includes
#include "Utility_ExplicitTemplateInstantiationMacros.hpp"
#include "Utility_DesignByContract.hpp"

namespace MonteCarlo{

// Basic Constructor
template<typename InterpPolicy, bool processed_cross_section>
CoherentAdjointPhotoatomicReaction<InterpPolicy,processed_cross_section>::CoherentAdjointPhotoatomicReaction(
       const std::shared_ptr<const std::vector<double> >& incoming_energy_grid,
       const std::shared_ptr<const std::vector<double> >& cross_section,
       const size_t threshold_energy_index,
       const std::shared_ptr<const CoherentScatteringDistribution>&
       scattering_distribution )
  : BaseType( incoming_energy_grid,
              cross_section,
              threshold_energy_index ),
    d_scattering_distribution( scattering_distribution )
{
  // Make sure the scattering distribution is valid
  testPrecondition( scattering_distribution.get() );
}

// Constructor
template<typename InterpPolicy, bool processed_cross_section>
CoherentAdjointPhotoatomicReaction<InterpPolicy,processed_cross_section>::CoherentAdjointPhotoatomicReaction(
    const std::shared_ptr<const std::vector<double> >& incoming_energy_grid,
    const std::shared_ptr<const std::vector<double> >& cross_section,
    const size_t threshold_energy_index,
    const std::shared_ptr<const Utility::HashBasedGridSearcher<double> >&
    grid_searcher,
    const std::shared_ptr<const CoherentScatteringDistribution>&
    scattering_distribution )
  : BaseType( incoming_energy_grid,
              cross_section,
              threshold_energy_index,
              grid_searcher ),
    d_scattering_distribution( scattering_distribution )
{
  // Make sure the scattering distribution is valid
  testPrecondition( scattering_distribution.get() );
}

// Return the number of adjoint photons emitted from the rxn at the given energy
template<typename InterpPolicy, bool processed_cross_section>
unsigned CoherentAdjointPhotoatomicReaction<InterpPolicy,processed_cross_section>::getNumberOfEmittedAdjointPhotons( const double energy ) const
{
  if( energy >= this->getThresholdEnergy() && energy <= this->getMaxEnergy() )
    return 1u;
  else
    return 0u;
}

// Return the number of adjoint electrons emitted from the rxn at the given energy
template<typename InterpPolicy, bool processed_cross_section>
unsigned CoherentAdjointPhotoatomicReaction<InterpPolicy,processed_cross_section>::getNumberOfEmittedAdjointElectrons( const double energy ) const
{
  return 0u;
}

// Return the number of adjoint positrons emitted from the rxn at the given energy
template<typename InterpPolicy, bool processed_cross_section>
unsigned CoherentAdjointPhotoatomicReaction<InterpPolicy,processed_cross_section>::getNumberOfEmittedAdjointPositrons( const double energy ) const
{
  return 0u;
}

// Return the reaction type
template<typename InterpPolicy, bool processed_cross_section>
AdjointPhotoatomicReactionType CoherentAdjointPhotoatomicReaction<InterpPolicy,processed_cross_section>::getReactionType() const
{
  return COHERENT_ADJOINT_PHOTOATOMIC_REACTION;
}
  
// Simulate the reaction
template<typename InterpPolicy, bool processed_cross_section>
void CoherentAdjointPhotoatomicReaction<InterpPolicy,processed_cross_section>::react(
                               AdjointPhotonState& adjoint_photon,
                               ParticleBank& bank,
                               Data::SubshellType& shell_of_interaction ) const
{
  d_scattering_distribution->scatterAdjointPhoton( adjoint_photon,
                                                   bank,
                                                   shell_of_interaction );

  adjoint_photon.incrementCollisionNumber();

  shell_of_interaction = Data::UNKNOWN_SUBSHELL;
}

EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( CoherentAdjointPhotoatomicReaction<Utility::LinLin,false> );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( CoherentAdjointPhotoatomicReaction<Utility::LinLin,true> );

EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( CoherentAdjointPhotoatomicReaction<Utility::LinLog,false> );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( CoherentAdjointPhotoatomicReaction<Utility::LinLog,true> );

EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( CoherentAdjointPhotoatomicReaction<Utility::LogLin,false> );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( CoherentAdjointPhotoatomicReaction<Utility::LogLin,true> );

EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( CoherentAdjointPhotoatomicReaction<Utility::LogLog,false> );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( CoherentAdjointPhotoatomicReaction<Utility::LogLog,true> );
  
} // end MonteCarlo namespace

#endif // end MONTE_CARLO_COHERENT_ADJOINT_PHOTOATOMIC_REACTION_DEF_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_CoherentAdjointPhotoatomicReaction_def.hpp
//---------------------------------------------------------------------------//
