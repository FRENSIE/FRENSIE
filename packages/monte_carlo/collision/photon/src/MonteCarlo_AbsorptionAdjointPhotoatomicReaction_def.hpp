//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_AbsorptionAdjointPhotoatomicReaction_def.hpp
//! \author Alex Robinson
//! \brief  The absorption adjoint photoatomic reaction class definition
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_ABSORPTION_ADJOINT_PHOTOATOMIC_REACTION_DEF_HPP
#define MONTE_CARLO_ABSORPTION_ADJOINT_PHOTOATOMIC_REACTION_DEF_HPP

// FRENSIE Includes
#include "Utility_ExplicitTemplateInstantiationMacros.hpp"
#include "Utility_DesignByContract.hpp"

namespace MonteCarlo{

// Basic constructor
template<typename InterpPolicy, bool processed_cross_section>
AbsorptionAdjointPhotoatomicReaction<InterpPolicy,processed_cross_section>::AbsorptionAdjointPhotoatomicReaction(
                   const std::shared_ptr<const std::vector<double> >& incoming_energy_grid,
                   const std::shared_ptr<const std::vector<double> >& cross_section,
                   const size_t threshold_energy_index,
                   const AdjointPhotoatomicReactionType reaction )
  : BaseType( incoming_energy_grid, cross_section, threshold_energy_index ),
    d_reaction( reaction )
{ /* ... */ }

// Constructor
template<typename InterpPolicy, bool processed_cross_section>
AbsorptionAdjointPhotoatomicReaction<InterpPolicy,processed_cross_section>::AbsorptionAdjointPhotoatomicReaction(
    const std::shared_ptr<const std::vector<double> >& incoming_energy_grid,
    const std::shared_ptr<const std::vector<double> >& cross_section,
    const size_t threshold_energy_index,
    const std::shared_ptr<const Utility::HashBasedGridSearcher<double> >&
    grid_searcher,
    const AdjointPhotoatomicReactionType reaction )
  : BaseType( incoming_energy_grid,
              cross_section,
              threshold_energy_index,
              grid_searcher ),
    d_reaction( reaction )
{ /* ... */ }

// Return the number of adjoint photons emitted from the rxn at the given energy
template<typename InterpPolicy, bool processed_cross_section>
unsigned AbsorptionAdjointPhotoatomicReaction<InterpPolicy,processed_cross_section>::getNumberOfEmittedAdjointPhotons( const double energy ) const
{
  return 0u;
}

// Return the number of adjoint electrons emitted from the rxn at the given energy
template<typename InterpPolicy, bool processed_cross_section>
unsigned AbsorptionAdjointPhotoatomicReaction<InterpPolicy,processed_cross_section>::getNumberOfEmittedAdjointElectrons( const double energy ) const
{
  return 0u;
}

// Return the number of adjoint positrons emitted from the rxn at the given energy
template<typename InterpPolicy, bool processed_cross_section>
unsigned AbsorptionAdjointPhotoatomicReaction<InterpPolicy,processed_cross_section>::getNumberOfEmittedAdjointPositrons( const double energy ) const
{
  return 0u;
}

// Return the reaction type
template<typename InterpPolicy, bool processed_cross_section>
AdjointPhotoatomicReactionType AbsorptionAdjointPhotoatomicReaction<InterpPolicy,processed_cross_section>::getReactionType() const
{
  return d_reaction;
}

// Simulate the reaction
template<typename InterpPolicy, bool processed_cross_section>
void AbsorptionAdjointPhotoatomicReaction<InterpPolicy,processed_cross_section>::react(
                               AdjointPhotonState& adjoint_photon,
                               ParticleBank& bank,
                               Data::SubshellType& shell_of_interaction ) const
{
  adjoint_photon.setAsGone();

  shell_of_interaction = Data::UNKNOWN_SUBSHELL;
}

EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( AbsorptionAdjointPhotoatomicReaction<Utility::LinLin,false> );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( AbsorptionAdjointPhotoatomicReaction<Utility::LinLin,true> );

EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( AbsorptionAdjointPhotoatomicReaction<Utility::LinLog,false> );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( AbsorptionAdjointPhotoatomicReaction<Utility::LinLog,true> );

EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( AbsorptionAdjointPhotoatomicReaction<Utility::LogLin,false> );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( AbsorptionAdjointPhotoatomicReaction<Utility::LogLin,true> );

EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( AbsorptionAdjointPhotoatomicReaction<Utility::LogLog,false> );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( AbsorptionAdjointPhotoatomicReaction<Utility::LogLog,true> );
  
} // end MonteCarlo namespace

#endif // end MONTE_CARLO_ABSORPTION_ADJOINT_PHOTOATOMIC_REACTION_DEF_HPP


//---------------------------------------------------------------------------//
// end MonteCarlo_AbsorptionAdjointPhotoatomicReaction_def.hpp
//---------------------------------------------------------------------------//
