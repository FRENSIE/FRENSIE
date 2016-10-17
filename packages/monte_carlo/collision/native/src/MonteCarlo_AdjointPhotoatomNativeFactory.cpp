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
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Create an adjoint photoatom core
void AdjointPhotoatomNativeFactory::createAdjointPhotoatomCore(
                    const Data::AdjointElectronPhotonRelaxationDataContainer&
                    raw_adjoint_photoatom_data,
                    Teuchos::RCP<AdjointPhotoatomCore>& adjoint_photoatom_core,
                    const double max_energy,
                    const unsigned hash_grid_bins,
                    const IncoherentAdjointModelType incoherent_adjoint_model,
                    const Teuchos::Array<double>& user_critical_line_energies )
{
  // Make sure the max energy is valid
  testPrecondition( max_energy > 0.0 );
  testPrecondition( max_energy >= user_critical_line_energies.back() );
  // Make sure the hash grid bins are valid
  testPrecondition( hash_grid_bins > 0u );

  // Create the critical line energies array
  Teuchos::ArrayRCP<const double> critical_line_energies =
    ThisType::addCriticalLineEnergies( raw_adjoint_photoatom_data,
                                       max_energy,
                                       user_critical_line_energies );

  // Create the union energy grid
  Teuchos::ArrayRCP<double> energy_grid;

  AdjointPhotoatomicReactionNativeFactory::createUnionEnergyGrid(
                                                    raw_adjoint_photoatom_data,
                                                    energy_grid,
                                                    max_energy );

  // Create the hash based grid searcher
  Teuchos::RCP<const Utility::HashBasedGridSearcher> grid_searcher(
   new Utility::StandardHashBasedGridSearcher<Teuchos::ArrayRCP<double>,false>(
                                                            energy_grid,
                                                            hash_grid_bins ) );

  // Create the total forward reaction
  std::shared_ptr<PhotoatomicReaction> total_forward_reaction;

  AdjointPhotoatomicReactionNativeFactory::createTotalForwardReaction(
                                                    raw_adjoint_photoatom_data,
                                                    energy_grid,
                                                    grid_searcher,
                                                    incoherent_adjoint_model,
                                                    total_forward_reaction );

  // Create the scattering reactions
  AdjointPhotoatomCore::ReactionMap scattering_reactions;

  // Create the incoherent reaction(s)
  {
    std::vector<std::shared_ptr<AdjointPhotoatomicReaction> >
      incoherent_reactions;

    AdjointPhotoatomicReactionNativeFactory::createIncoherentReactions(
                                                    raw_adjoint_photoatom_data,
                                                    energy_grid,
                                                    grid_searcher,
                                                    incoherent_reactions,
                                                    incoherent_adjoint_model,
                                                    critical_line_energies );

    for( size_t i = 0; i < incoherent_reactions.size(); ++i )
    {
      scattering_reactions[incoherent_reactions[i]->getReactionType()] =
        incoherent_reactions[i];
    }
  }

  // Create the coherent reaction
  {
    AdjointPhotoatomCore::ReactionMap::mapped_type& reaction_pointer =
      scattering_reactions[COHERENT_ADJOINT_PHOTOATOMIC_REACTION];

    AdjointPhotoatomicReactionNativeFactory::createCoherentReaction(
                                                    raw_adjoint_photoatom_data,
                                                    energy_grid,
                                                    grid_searcher,
                                                    reaction_pointer );
  }

  // Create the line energy reactions
  AdjointPhotoatomCore::LineEnergyReactionMap line_energy_reactions;

  // Create the pair production reaction
  if( max_energy > 2*Utility::PhysicalConstants::electron_rest_mass_energy )
  {
    AdjointPhotoatomCore::ReactionMap& me_line_energy_reactions =
      line_energy_reactions[Utility::PhysicalConstants::electron_rest_mass_energy];

    std::shared_ptr<LineEnergyAdjointPhotoatomicReaction> reaction_pointer;
    
    AdjointPhotoatomicReactionNativeFactory::createPairProductionReaction(
                                                    raw_adjoint_photoatom_data,
                                                    energy_grid,
                                                    grid_searcher,
                                                    reaction_pointer );
    
    me_line_energy_reactions[PAIR_PRODUCTION_ADJOINT_PHOTOATOMIC_REACTION] =
      reaction_pointer;
  }

  // Create the triplet production reaction
  if( max_energy > 4*Utility::PhysicalConstants::electron_rest_mass_energy )
  {
    AdjointPhotoatomCore::ReactionMap& me_line_energy_reactions =
      line_energy_reactions[Utility::PhysicalConstants::electron_rest_mass_energy];

    std::shared_ptr<LineEnergyAdjointPhotoatomicReaction> reaction_pointer;
    
    AdjointPhotoatomicReactionNativeFactory::createTripletProductionReaction(
                                                    raw_adjoint_photoatom_data,
                                                    energy_grid,
                                                    grid_searcher,
                                                    reaction_pointer );

    me_line_energy_reactions[TRIPLET_PRODUCTION_ADJOINT_PHOTOATOMIC_REACTION] =
      reaction_pointer;
  }

  // Create the adjoint photoatom core
  adjoint_photoatom_core.reset( new AdjointPhotoatomCore(
                                           grid_searcher,
                                           total_forward_reaction,
                                           scattering_reactions,
                                           AdjointPhotoatomCore::ReactionMap(),
                                           line_energy_reactions ) );
}

// Create an adjoint photoatom
void AdjointPhotoatomNativeFactory::createAdjointPhotoatom(
                    const Data::AdjointElectronPhotonRelaxationDataContainer&
                    raw_adjoint_photoatom_data,
                    const std::string& adjoint_photoatom_name,
                    const double atomic_weight,
                    Teuchos::RCP<AdjointPhotoatom>& adjoint_photoatom,
                    const double max_energy,
                    const unsigned hash_grid_bins,
                    const IncoherentAdjointModelType incoherent_adjoint_model,
                    const Teuchos::Array<double>& user_critical_line_energies )
{
  // Make sure the atomic weight is valid
  testPrecondition( atomic_weight > 0.0 );
  // Make sure the max energy is valid
  testPrecondition( max_energy > 0.0 );
  testPrecondition( max_energy >= user_critical_line_energies.back() );
  // Make sure the hash grid bins are valid
  testPrecondition( hash_grid_bins > 0u );

  Teuchos::RCP<AdjointPhotoatomCore> core;

  ThisType::createAdjointPhotoatomCore( raw_adjoint_photoatom_data,
                                        core,
                                        max_energy,
                                        hash_grid_bins,
                                        incoherent_adjoint_model,
                                        user_critical_line_energies );

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
Teuchos::ArrayRCP<const double> AdjointPhotoatomNativeFactory::addCriticalLineEnergies(
                    const Data::AdjointElectronPhotonRelaxationDataContainer&
                    raw_adjoint_photoatom_data,
                    const double max_energy,
                    const Teuchos::Array<double>& user_critical_line_energies )
{
  std::list<double> critical_line_energies(user_critical_line_energies.begin(),
                                           user_critical_line_energies.end() );
  
  if( max_energy > 2*Utility::PhysicalConstants::electron_rest_mass_energy )
  {
    std::list<double>::const_iterator required_line_energy =
      std::find( critical_line_energies.begin(),
                 critical_line_energies.end(),
                 Utility::PhysicalConstants::electron_rest_mass_energy );

    if( required_line_energy != critical_line_energies.end() )
    {
      critical_line_energies.push_back( Utility::PhysicalConstants::electron_rest_mass_energy );
    }
  }

  critical_line_energies.sort();

  Teuchos::ArrayRCP<double> critical_line_energies_copy;
  critical_line_energies_copy.assign( critical_line_energies.begin(),
                                      critical_line_energies.end() );

  return critical_line_energies_copy;
}
  
} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_AdjointPhotoatomNativeFactory.cpp
//---------------------------------------------------------------------------//
