//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_AbsorptionPhotoatomicReaction_def.hpp
//! \author Alex Robinson
//! \brief  The absorption photoatomic reaction class decl.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_ABSORPTION_PHOTOATOMIC_REACTION_DEF_HPP
#define MONTE_CARLO_ABSORPTION_PHOTOATOMIC_REACTION_DEF_HPP

// FRENSIE Includes
#include "Utility_SortAlgorithms.hpp"
#include "Utility_ExplicitTemplateInstantiationMacros.hpp"
#include "Utility_DesignByContract.hpp"

namespace MonteCarlo{

// Basic constructor
template<typename InterpPolicy, bool processed_cross_section>
AbsorptionPhotoatomicReaction<InterpPolicy,processed_cross_section>::AbsorptionPhotoatomicReaction(
	   const std::shared_ptr<const std::vector<double> >& incoming_energy_grid,
	   const std::shared_ptr<const std::vector<double> >& cross_section,
	   const size_t threshold_energy_index,
	   const PhotoatomicReactionType reaction )
  : BaseType( incoming_energy_grid,
              cross_section,
              threshold_energy_index ),
    d_reaction( reaction )
{
  // Make sure the incoming energy grid is valid
  testPrecondition( incoming_energy_grid->size() > 0 );
  testPrecondition( Utility::Sort::isSortedAscending(
						incoming_energy_grid->begin(),
						incoming_energy_grid->end() ) );
  // Make sure the cross section is valid
  testPrecondition( cross_section->size() > 0 );
  testPrecondition( cross_section->size() ==
		    incoming_energy_grid->size() - threshold_energy_index );
  // Make sure the threshold energy is valid
  testPrecondition( threshold_energy_index < incoming_energy_grid->size() );
}

// Constructor
template<typename InterpPolicy, bool processed_cross_section>
AbsorptionPhotoatomicReaction<InterpPolicy,processed_cross_section>::AbsorptionPhotoatomicReaction(
       const std::shared_ptr<const std::vector<double> >& incoming_energy_grid,
       const std::shared_ptr<const std::vector<double> >& cross_section,
       const size_t threshold_energy_index,
       const std::shared_ptr<const Utility::HashBasedGridSearcher<double> >&
       grid_searcher,
       const PhotoatomicReactionType reaction )
  : BaseType( incoming_energy_grid,
              cross_section,
              threshold_energy_index,
              grid_searcher ),
    d_reaction( reaction )
{ /* ... */ }

// Return the number of photons emitted from the rxn at the given energy
template<typename InterpPolicy, bool processed_cross_section>
unsigned AbsorptionPhotoatomicReaction<InterpPolicy,processed_cross_section>::getNumberOfEmittedPhotons( const double energy ) const
{
  return 0u;
}

// Return the number of electrons emitted from the rxn at the given energy
template<typename InterpPolicy, bool processed_cross_section>
unsigned AbsorptionPhotoatomicReaction<InterpPolicy,processed_cross_section>::getNumberOfEmittedElectrons( const double energy ) const
{
  return 0u;
}

// Return the number of positrons emitted from the rxn at the given energy
template<typename InterpPolicy, bool processed_cross_section>
unsigned AbsorptionPhotoatomicReaction<InterpPolicy,processed_cross_section>::getNumberOfEmittedPositrons( const double energy ) const
{
  return 0u;
}

// Return the reaction type
template<typename InterpPolicy, bool processed_cross_section>
PhotoatomicReactionType AbsorptionPhotoatomicReaction<InterpPolicy,processed_cross_section>::getReactionType() const
{
  return d_reaction;
}

// Simulate the reaction
template<typename InterpPolicy, bool processed_cross_section>
void AbsorptionPhotoatomicReaction<InterpPolicy,processed_cross_section>::react(
				     PhotonState& photon,
				     ParticleBank& bank,
				     Data::SubshellType& shell_of_interaction ) const
{
  photon.setAsGone();

  shell_of_interaction = Data::UNKNOWN_SUBSHELL;
}

EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( AbsorptionPhotoatomicReaction<Utility::LinLin,false> );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( AbsorptionPhotoatomicReaction<Utility::LinLin,true> );

EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( AbsorptionPhotoatomicReaction<Utility::LinLog,false> );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( AbsorptionPhotoatomicReaction<Utility::LinLog,true> );

EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( AbsorptionPhotoatomicReaction<Utility::LogLin,false> );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( AbsorptionPhotoatomicReaction<Utility::LogLin,true> );

EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( AbsorptionPhotoatomicReaction<Utility::LogLog,false> );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( AbsorptionPhotoatomicReaction<Utility::LogLog,true> );

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_ABSORPTION_PHOTOATOMIC_REACTION_DEF_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_AbsorptionPhotoatomicReaction_def.hpp
//---------------------------------------------------------------------------//
