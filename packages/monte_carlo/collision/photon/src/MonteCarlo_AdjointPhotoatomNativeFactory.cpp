//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_AdjointPhotoatomNativeFactory.cpp
//! \author Alex Robinson
//! \brief  The adjoint photoatom native factory class definition.
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <algorithm>
#include <list>

// FRENSIE Includes
#include "MonteCarlo_AdjointPhotoatomNativeFactory.hpp"
#include "MonteCarlo_AdjointPhotoatomicReactionNativeFactory.hpp"
#include "Utility_StandardHashBasedGridSearcher.hpp"
#include "Utility_SortAlgorithms.hpp"
#include "Utility_DesignByContract.hpp"

namespace MonteCarlo{

// Create an adjoint photoatom core
void AdjointPhotoatomNativeFactory::createAdjointPhotoatomCore(
                   const Data::AdjointElectronPhotonRelaxationDataContainer&
                   raw_adjoint_photoatom_data,
                   const SimulationAdjointPhotonProperties& properties,
                   std::shared_ptr<const AdjointPhotoatomCore>& adjoint_photoatom_core )
{
  // Create the critical line energies array
  std::shared_ptr<const std::vector<double> > critical_line_energies =
    ThisType::addCriticalLineEnergies(
                           raw_adjoint_photoatom_data,
                           properties.getMaxAdjointPhotonEnergy(),
                           properties.getCriticalAdjointPhotonLineEnergies() );

  // Create the union energy grid
  std::shared_ptr<std::vector<double> > energy_grid( new std::vector<double> );

  AdjointPhotoatomicReactionNativeFactory::createUnionEnergyGrid(
                                      raw_adjoint_photoatom_data,
                                      *energy_grid,
                                      properties.getMaxAdjointPhotonEnergy() );

  // Create the hash based grid searcher
  std::shared_ptr<const Utility::HashBasedGridSearcher<double> > grid_searcher(
         new Utility::StandardHashBasedGridSearcher<std::vector<double>,false>(
                         energy_grid,
                         properties.getNumberOfAdjointPhotonHashGridBins() ) );

  // Create the total forward reaction
  std::shared_ptr<const PhotoatomicReaction> total_forward_reaction;

  AdjointPhotoatomicReactionNativeFactory::createTotalForwardReaction(
                                    raw_adjoint_photoatom_data,
                                    energy_grid,
                                    grid_searcher,
                                    properties.getIncoherentAdjointModelType(),
                                    total_forward_reaction );

  // Create the scattering reactions
  AdjointPhotoatomCore::ConstReactionMap scattering_reactions;

  // Create the incoherent reaction(s)
  {
    std::vector<std::shared_ptr<const AdjointPhotoatomicReaction> >
      incoherent_reactions;

    AdjointPhotoatomicReactionNativeFactory::createIncoherentReactions(
                               raw_adjoint_photoatom_data,
                               energy_grid,
                               grid_searcher,
                               incoherent_reactions,
                               properties.getIncoherentAdjointModelType(),
                               properties.getAdjointKleinNishinaSamplingType(),
                               critical_line_energies );

    for( size_t i = 0; i < incoherent_reactions.size(); ++i )
    {
      scattering_reactions[incoherent_reactions[i]->getReactionType()] =
        incoherent_reactions[i];
    }
  }

  // Create the coherent reaction
  {
    AdjointPhotoatomCore::ConstReactionMap::mapped_type& reaction_pointer =
      scattering_reactions[COHERENT_ADJOINT_PHOTOATOMIC_REACTION];

    AdjointPhotoatomicReactionNativeFactory::createCoherentReaction(
                                                    raw_adjoint_photoatom_data,
                                                    energy_grid,
                                                    grid_searcher,
                                                    reaction_pointer );
  }

  // Create the line energy reactions
  AdjointPhotoatomCore::ConstLineEnergyReactionMap line_energy_reactions;

  // Create the pair production reaction
  if( properties.getMaxAdjointPhotonEnergy() >
      2*Utility::PhysicalConstants::electron_rest_mass_energy )
  {
    AdjointPhotoatomCore::ConstReactionMap& me_line_energy_reactions =
      line_energy_reactions[Utility::PhysicalConstants::electron_rest_mass_energy];

    std::shared_ptr<const LineEnergyAdjointPhotoatomicReaction>
      reaction_pointer;
    
    AdjointPhotoatomicReactionNativeFactory::createPairProductionReaction(
                                                    raw_adjoint_photoatom_data,
                                                    energy_grid,
                                                    grid_searcher,
                                                    reaction_pointer,
                                                    critical_line_energies );
    
    me_line_energy_reactions[PAIR_PRODUCTION_ADJOINT_PHOTOATOMIC_REACTION] =
      reaction_pointer;
  }

  // Create the triplet production reaction
  if( properties.getMaxAdjointPhotonEnergy() >
      4*Utility::PhysicalConstants::electron_rest_mass_energy )
  {
    AdjointPhotoatomCore::ConstReactionMap& me_line_energy_reactions =
      line_energy_reactions[Utility::PhysicalConstants::electron_rest_mass_energy];

    std::shared_ptr<const LineEnergyAdjointPhotoatomicReaction>
      reaction_pointer;
    
    AdjointPhotoatomicReactionNativeFactory::createTripletProductionReaction(
                                                    raw_adjoint_photoatom_data,
                                                    energy_grid,
                                                    grid_searcher,
                                                    reaction_pointer,
                                                    critical_line_energies );

    me_line_energy_reactions[TRIPLET_PRODUCTION_ADJOINT_PHOTOATOMIC_REACTION] =
      reaction_pointer;
  }
  
  // Create the adjoint photoatom core
  adjoint_photoatom_core.reset( new AdjointPhotoatomCore(
                                      energy_grid,
                                      grid_searcher,
                                      critical_line_energies,
                                      total_forward_reaction,
                                      scattering_reactions,
                                      AdjointPhotoatomCore::ConstReactionMap(),
                                      line_energy_reactions,
                                      false,
                                      Utility::LinLin() ) );
}

// Create an adjoint photoatom
void AdjointPhotoatomNativeFactory::createAdjointPhotoatom(
                      const Data::AdjointElectronPhotonRelaxationDataContainer&
                      raw_adjoint_photoatom_data,
                      const std::string& adjoint_photoatom_name,
                      const double atomic_weight,
                      const SimulationAdjointPhotonProperties& properties,
                      std::shared_ptr<const AdjointPhotoatom>& adjoint_photoatom )
{
  // Make sure the atomic weight is valid
  testPrecondition( atomic_weight > 0.0 );

  std::shared_ptr<const AdjointPhotoatomCore> core;

  ThisType::createAdjointPhotoatomCore( raw_adjoint_photoatom_data,
                                        properties,
                                        core );

  // Create the adjoint photoatom
  adjoint_photoatom.reset( new AdjointPhotoatom(
                                  adjoint_photoatom_name,
                                  raw_adjoint_photoatom_data.getAtomicNumber(),
                                  atomic_weight,
                                  *core ) );
}

// Add critical line energyies based on available reactions
/*! \details Currently, the only line energy reactions are pair production
 * and triplet production. If the max energy is above 2*me then pair 
 * production can occur with all elements. If the max energy is above 4*me
 * then triplet production can occur with all elements. The critical line
 * energy of me will be added to the critical line energies array when the
 * max energy is above 2*me. This method will be more useful when adjoint
 * atomic relaxation is implemented. A line energy reaction (and it's 
 * corresponding critical line energy) will be defined for each radiative
 * transition. These line energy reactions will be different for each
 * element.
 */
std::shared_ptr<const std::vector<double> > AdjointPhotoatomNativeFactory::addCriticalLineEnergies(
                    const Data::AdjointElectronPhotonRelaxationDataContainer&
                    raw_adjoint_photoatom_data,
                    const double max_energy,
                    const std::vector<double>& user_critical_line_energies )
{
  std::list<double> critical_line_energies(user_critical_line_energies.begin(),
                                           user_critical_line_energies.end() );
  
  if( max_energy > 2*Utility::PhysicalConstants::electron_rest_mass_energy )
  {
    std::list<double>::const_iterator required_line_energy =
      std::find( critical_line_energies.begin(),
                 critical_line_energies.end(),
                 Utility::PhysicalConstants::electron_rest_mass_energy );

    if( required_line_energy == critical_line_energies.end() )
    {
      critical_line_energies.push_back( Utility::PhysicalConstants::electron_rest_mass_energy );
    }
  }

  critical_line_energies.sort();

  std::shared_ptr<std::vector<double> >
    critical_line_energies_copy( new std::vector<double> );
  
  critical_line_energies_copy->assign( critical_line_energies.begin(),
                                       critical_line_energies.end() );

  // if( !critical_line_energies_copy->empty() )
  // {
  //   if( max_energy > critical_line_energies_copy->back() )
  //     critical_line_energies_copy->push_back( max_energy );
  // }
  // else
  //   critical_line_energies_copy->push_back( max_energy );
  
  return critical_line_energies_copy;
}
  
} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_AdjointPhotoatomNativeFactory.cpp
//---------------------------------------------------------------------------//
