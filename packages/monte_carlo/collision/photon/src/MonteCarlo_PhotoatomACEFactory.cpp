//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_PhotoatomACEFactory.hpp
//! \author Alex Robinson
//! \brief  The photoatom ace factory class definition.
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_PhotoatomACEFactory.hpp"
#include "MonteCarlo_PhotoatomicReactionACEFactory.hpp"
#include "Utility_StandardHashBasedGridSearcher.hpp"
#include "Utility_Vector.hpp"
#include "Utility_DesignByContract.hpp"

namespace MonteCarlo{

// Create a photoatom core (using the provided atomic relaxation model)
/*! \details The provided atomic relaxation model will be used with this
 * core. Special care must be taken to assure that the model corresponds to
 * the atom of interest. If the use of atomic relaxation data has been
 * requested, a photoelectric reaction for each subshell will be created.
 * Otherwise a single total photoelectric reaction will be created.
 */
void PhotoatomACEFactory::createPhotoatomCore(
   const Data::XSSEPRDataExtractor& raw_photoatom_data,
   const std::shared_ptr<const AtomicRelaxationModel>& atomic_relaxation_model,
   const SimulationPhotonProperties& properties,
   std::shared_ptr<const PhotoatomCore>& photoatom_core )
{
  // Make sure the atomic relaxation model is valid
  testPrecondition( atomic_relaxation_model.get() );

  Photoatom::ConstReactionMap scattering_reactions, absorption_reactions;

  // Extract the common energy grid used for this atom
  std::shared_ptr<std::vector<double> > energy_grid(
        new std::vector<double>( raw_photoatom_data.extractPhotonEnergyGrid().begin(),
                                 raw_photoatom_data.extractPhotonEnergyGrid().end() ) );

  std::shared_ptr<const Utility::HashBasedGridSearcher<double> > grid_searcher(
         new Utility::StandardHashBasedGridSearcher<std::vector<double>, true>(
                                energy_grid,
                                properties.getNumberOfPhotonHashGridBins() ) );

  // Create the incoherent scattering reaction
  {
    Photoatom::ConstReactionMap::mapped_type& reaction_pointer =
      scattering_reactions[TOTAL_INCOHERENT_PHOTOATOMIC_REACTION];

    PhotoatomicReactionACEFactory::createIncoherentReaction(
                                    raw_photoatom_data,
                                    energy_grid,
                                    grid_searcher,
                                    reaction_pointer,
                                    properties.getIncoherentModelType(),
                                    properties.getKahnSamplingCutoffEnergy() );
  }

  // Create the coherent scattering reaction
  {
    Photoatom::ConstReactionMap::mapped_type& reaction_pointer =
      scattering_reactions[COHERENT_PHOTOATOMIC_REACTION];

    PhotoatomicReactionACEFactory::createCoherentReaction( raw_photoatom_data,
							   energy_grid,
							   grid_searcher,
							   reaction_pointer );
  }

  // Create the pair production reaction
  {
    Photoatom::ConstReactionMap::mapped_type& reaction_pointer =
      scattering_reactions[PAIR_PRODUCTION_PHOTOATOMIC_REACTION];

    PhotoatomicReactionACEFactory::createPairProductionReaction(
                                 raw_photoatom_data,
                                 energy_grid,
                                 grid_searcher,
                                 reaction_pointer,
                                 properties.isDetailedPairProductionModeOn() );
  }

  // Create the photoelectric reaction(s)
  if( properties.isAtomicRelaxationModeOn() )
  {
    std::vector<std::shared_ptr<const PhotoatomicReaction> > reaction_pointers;

    PhotoatomicReactionACEFactory::createSubshellPhotoelectricReactions(
							   raw_photoatom_data,
							   energy_grid,
							   grid_searcher,
							   reaction_pointers );

    for( unsigned i = 0; i < reaction_pointers.size(); ++i )
    {
      absorption_reactions[reaction_pointers[i]->getReactionType()] =
	reaction_pointers[i];
    }
  }
  else
  {
    Photoatom::ConstReactionMap::mapped_type& reaction_pointer =
      absorption_reactions[TOTAL_PHOTOELECTRIC_PHOTOATOMIC_REACTION];

    PhotoatomicReactionACEFactory::createTotalPhotoelectricReaction(
							    raw_photoatom_data,
							    energy_grid,
							    grid_searcher,
							    reaction_pointer );
  }

  // Create the heating reaction
  Photoatom::ConstReactionMap::mapped_type& reaction_pointer =
      absorption_reactions[HEATING_PHOTOATOMIC_REACTION];

  PhotoatomicReactionACEFactory::createHeatingReaction( raw_photoatom_data,
							energy_grid,
							grid_searcher,
							reaction_pointer );

  // Create the photoatom core
  photoatom_core.reset( new PhotoatomCore( energy_grid,
					   grid_searcher,
					   scattering_reactions,
					   absorption_reactions,
					   atomic_relaxation_model,
					   true,
					   Utility::LogLog() ) );
}

// Create a photoatom (using the provided atomic relaxation model)
/*! \details The provided atomic relaxation model will be used with this
 * atom. Special care must be taken to assure that the model corresponds with
 * the atom of interest. If the use of atomic relaxation data has been
 * requested, a photoelectric reaction for each subshell will be created.
 * Otherwise a single total photoelectric reaction will be created.
 */
void PhotoatomACEFactory::createPhotoatom(
   const Data::XSSEPRDataExtractor& raw_photoatom_data,
   const std::string& photoatom_name,
   const double atomic_weight,
   const std::shared_ptr<const AtomicRelaxationModel>& atomic_relaxation_model,
   const SimulationPhotonProperties& properties,
   std::shared_ptr<const Photoatom>& photoatom )
{
  // Make sure the atomic weight is valid
  testPrecondition( atomic_weight > 0.0 );
  // Make sure the atomic relaxation model is valid
  testPrecondition( atomic_relaxation_model.get() );

  std::shared_ptr<const PhotoatomCore> core;

  PhotoatomACEFactory::createPhotoatomCore( raw_photoatom_data,
					    atomic_relaxation_model,
                                            properties,
					    core );

  // Create the photoatom
  photoatom.reset( new Photoatom( photoatom_name,
				  raw_photoatom_data.extractAtomicNumber(),
				  atomic_weight,
				  *core ) );
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_PhotoatomACEFactory.cpp
//---------------------------------------------------------------------------//
