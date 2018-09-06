//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_CoherentPhotoatomicReaction_def.hpp
//! \author Alex Robinson
//! \brief  The coherent photoatomic reaction class decl.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_COHERENT_PHOTOATOMIC_REACTION_DEF_HPP
#define MONTE_CARLO_COHERENT_PHOTOATOMIC_REACTION_DEF_HPP

// FRENSIE Includes
#include "Utility_ExplicitTemplateInstantiationMacros.hpp"
#include "Utility_DesignByContract.hpp"

namespace MonteCarlo{

// Basic Constructor
template<typename InterpPolicy, bool processed_cross_section>
CoherentPhotoatomicReaction<InterpPolicy,processed_cross_section>::CoherentPhotoatomicReaction(
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
  // Make sure the form factor is valid
  testPrecondition( scattering_distribution.get() );
}

// Constructor
template<typename InterpPolicy, bool processed_cross_section>
CoherentPhotoatomicReaction<InterpPolicy,processed_cross_section>::CoherentPhotoatomicReaction(
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
  // Make sure the form factor is valid
  testPrecondition( scattering_distribution.get() );
}

// Return the number of photons emitted from the rxn at the given energy
template<typename InterpPolicy, bool processed_cross_section>
unsigned CoherentPhotoatomicReaction<InterpPolicy,processed_cross_section>::getNumberOfEmittedPhotons( const double energy ) const
{
  if( energy >= this->getThresholdEnergy() )
    return 1u;
  else
    return 0u;
}

// Return the number of electrons emitted from the rxn at the given energy
template<typename InterpPolicy, bool processed_cross_section>
unsigned CoherentPhotoatomicReaction<InterpPolicy,processed_cross_section>::getNumberOfEmittedElectrons( const double energy ) const
{
  return 0u;
}

// Return the number of positrons emitted from the rxn at the given energy
template<typename InterpPolicy, bool processed_cross_section>
unsigned CoherentPhotoatomicReaction<InterpPolicy,processed_cross_section>::getNumberOfEmittedPositrons( const double energy ) const
{
  return 0u;
}

// Return the reaction type
template<typename InterpPolicy, bool processed_cross_section>
PhotoatomicReactionType CoherentPhotoatomicReaction<InterpPolicy,processed_cross_section>::getReactionType() const
{
  return COHERENT_PHOTOATOMIC_REACTION;
}

// Simulate the reaction
template<typename InterpPolicy, bool processed_cross_section>
void CoherentPhotoatomicReaction<InterpPolicy,processed_cross_section>::react(
				     PhotonState& photon,
				     ParticleBank& bank,
				     Data::SubshellType& shell_of_interaction ) const
{
  d_scattering_distribution->scatterPhoton( photon,
					    bank,
					    shell_of_interaction );

  photon.incrementCollisionNumber();

  // No subshell vacancies are created by this reaction
  shell_of_interaction =Data::UNKNOWN_SUBSHELL;
}

EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( CoherentPhotoatomicReaction<Utility::LinLin,false> );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( CoherentPhotoatomicReaction<Utility::LinLin,true> );

EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( CoherentPhotoatomicReaction<Utility::LinLog,false> );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( CoherentPhotoatomicReaction<Utility::LinLog,true> );

EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( CoherentPhotoatomicReaction<Utility::LogLin,false> );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( CoherentPhotoatomicReaction<Utility::LogLin,true> );

EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( CoherentPhotoatomicReaction<Utility::LogLog,false> );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( CoherentPhotoatomicReaction<Utility::LogLog,true> );

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_COHERENT_PHOTOATOMIC_REACTION_DEF_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_CoherentPhotoatomicReaction_def.hpp
//---------------------------------------------------------------------------//
