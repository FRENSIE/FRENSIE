//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_PhotoelectricPhotoatomicReaction_def.hpp
//! \author Alex Robinson
//! \brief  The photoelectric photoatomic reaction class definition
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_PHOTOELECTRIC_PHOTOATOMIC_REACTION_DEF_HPP
#define MONTE_CARLO_PHOTOELECTRIC_PHOTOATOMIC_REACTION_DEF_HPP

// FRENSIE Includes
#include "Utility_ExplicitTemplateInstantiationMacros.hpp"
#include "Utility_DesignByContract.hpp"

namespace MonteCarlo{

// Basic constructor
template<typename InterpPolicy, bool processed_cross_section>
PhotoelectricPhotoatomicReaction<InterpPolicy,processed_cross_section>::PhotoelectricPhotoatomicReaction(
       const std::shared_ptr<const std::vector<double> >& incoming_energy_grid,
       const std::shared_ptr<const std::vector<double> >& cross_section,
       const size_t threshold_energy_index )
  : BaseType( incoming_energy_grid,
              cross_section,
              threshold_energy_index )
{ /* ... */ }

// Constructor
template<typename InterpPolicy, bool processed_cross_section>
PhotoelectricPhotoatomicReaction<InterpPolicy,processed_cross_section>::PhotoelectricPhotoatomicReaction(
      const std::shared_ptr<const std::vector<double> >& incoming_energy_grid,
      const std::shared_ptr<const std::vector<double> >& cross_section,
      const size_t threshold_energy_index,
      const std::shared_ptr<const Utility::HashBasedGridSearcher<double> >&
      grid_searcher )
  : BaseType( incoming_energy_grid,
              cross_section,
              threshold_energy_index,
              grid_searcher )
{ /* ... */ }

// Return the number of photons emitted from the rxn at the given energy
/*! \details This does not include photons from atomic relaxation.
 */
template<typename InterpPolicy, bool processed_cross_section>
unsigned PhotoelectricPhotoatomicReaction<InterpPolicy,processed_cross_section>::getNumberOfEmittedPhotons( const double energy ) const
{
  return 0u;
}

// Return the number of electrons emitted from the rxn at the given energy
/*! \details Without the subshell information we cannot generate secondary
 * electrons. This does not include electrons from atomic relaxation.
 */
template<typename InterpPolicy, bool processed_cross_section>
unsigned PhotoelectricPhotoatomicReaction<InterpPolicy,processed_cross_section>::getNumberOfEmittedElectrons( const double energy ) const
{
  return 0u;
}

// Return the number of positrons emitted from the rxn at the given energy
template<typename InterpPolicy, bool processed_cross_section>
unsigned PhotoelectricPhotoatomicReaction<InterpPolicy,processed_cross_section>::getNumberOfEmittedPositrons( const double energy ) const
{
  return 0u;
}

// Return the reaction type
template<typename InterpPolicy, bool processed_cross_section>
PhotoatomicReactionType PhotoelectricPhotoatomicReaction<InterpPolicy,processed_cross_section>::getReactionType() const
{
  return TOTAL_PHOTOELECTRIC_PHOTOATOMIC_REACTION;
}

// Simulate the reaction
template<typename InterpPolicy, bool processed_cross_section>
void
PhotoelectricPhotoatomicReaction<InterpPolicy,processed_cross_section>::react(
				     PhotonState& photon,
				     ParticleBank& bank,
				     Data::SubshellType& shell_of_interaction ) const
{
  // End the photon history
  photon.setAsGone();

  // The interaction subshell is not taken into account in this reaction
  shell_of_interaction =Data::UNKNOWN_SUBSHELL;
}

EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( PhotoelectricPhotoatomicReaction<Utility::LinLin,false> );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( PhotoelectricPhotoatomicReaction<Utility::LinLin,true> );

EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( PhotoelectricPhotoatomicReaction<Utility::LinLog,false> );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( PhotoelectricPhotoatomicReaction<Utility::LinLog,true> );

EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( PhotoelectricPhotoatomicReaction<Utility::LogLin,false> );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( PhotoelectricPhotoatomicReaction<Utility::LogLin,true> );

EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( PhotoelectricPhotoatomicReaction<Utility::LogLog,false> );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( PhotoelectricPhotoatomicReaction<Utility::LogLog,true> );

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_PHOTOELECTRIC_PHOTOATOMIC_REACTION_DEF_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_PhotoelectricPhotoatomicReaction_def.hpp
//---------------------------------------------------------------------------//
