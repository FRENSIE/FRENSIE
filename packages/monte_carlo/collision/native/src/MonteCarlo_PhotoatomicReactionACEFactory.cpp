//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_PhotoatomicReactionACEFactory.cpp
//! \author Alex Robinson
//! \brief  The photoatomic reaction ACE data factory definition
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <algorithm>
#include <limits>
#include <memory>

// FRENSIE Includes
#include "MonteCarlo_PhotoatomicReactionACEFactory.hpp"
#include "MonteCarlo_IncoherentPhotonScatteringDistributionACEFactory.hpp"
#include "MonteCarlo_CoherentScatteringDistributionACEFactory.hpp"
#include "MonteCarlo_IncoherentPhotoatomicReaction.hpp"
#include "MonteCarlo_CoherentPhotoatomicReaction.hpp"
#include "MonteCarlo_PairProductionPhotoatomicReaction.hpp"
#include "MonteCarlo_PhotoelectricPhotoatomicReaction.hpp"
#include "MonteCarlo_SubshellPhotoelectricPhotoatomicReaction.hpp"
#include "MonteCarlo_AbsorptionPhotoatomicReaction.hpp"
#include "MonteCarlo_IncoherentPhotoatomicReaction.hpp"
#include "MonteCarlo_SubshellType.hpp"
#include "Utility_SortAlgorithms.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Create an incoherent scattering photoatomic reaction
void PhotoatomicReactionACEFactory::createIncoherentReaction(
       const Data::XSSEPRDataExtractor& raw_photoatom_data,
       const Teuchos::ArrayRCP<const double>& energy_grid,
       const Teuchos::RCP<const Utility::HashBasedGridSearcher>& grid_searcher,
       Teuchos::RCP<PhotoatomicReaction>& incoherent_reaction,
       const IncoherentModelType incoherent_model,
       const double kahn_sampling_cutoff_energy )
{
  // Make sure the energy grid is valid
  testPrecondition( raw_photoatom_data.extractPhotonEnergyGrid().size() == 
		    energy_grid.size() );
  testPrecondition( Utility::Sort::isSortedAscending( energy_grid.begin(),
						      energy_grid.end() ) );

  // Extract the cross section
  Teuchos::ArrayRCP<double> incoherent_cross_section;
  unsigned threshold_energy_index;
  
  PhotoatomicReactionACEFactory::removeZerosFromProcessedCrossSection(
			    energy_grid,
			    raw_photoatom_data.extractIncoherentCrossSection(),
			    incoherent_cross_section,
			    threshold_energy_index );
  
  // Create the scattering distribution
  Teuchos::RCP<const IncoherentPhotonScatteringDistribution> distribution;

  IncoherentPhotonScatteringDistributionACEFactory::createDistribution(
						 raw_photoatom_data,
						 distribution,
						 incoherent_model,
						 kahn_sampling_cutoff_energy );
    
  // Create the incoherent reaction
  incoherent_reaction.reset(new IncoherentPhotoatomicReaction<Utility::LogLog>(
						      energy_grid,
			                              incoherent_cross_section,
						      threshold_energy_index,
						      grid_searcher,
						      distribution ) );
}

// Create a coherent scattering photoatomic reaction
void PhotoatomicReactionACEFactory::createCoherentReaction(
       const Data::XSSEPRDataExtractor& raw_photoatom_data,
       const Teuchos::ArrayRCP<const double>& energy_grid,
       const Teuchos::RCP<const Utility::HashBasedGridSearcher>& grid_searcher,
       Teuchos::RCP<PhotoatomicReaction>& coherent_reaction )
{
  // Make sure the energy grid is valid
  testPrecondition( raw_photoatom_data.extractPhotonEnergyGrid().size() == 
		    energy_grid.size() );
  testPrecondition( Utility::Sort::isSortedAscending( energy_grid.begin(),
						      energy_grid.end() ) );

  // Extract the cross section
  Teuchos::ArrayRCP<double> coherent_cross_section;
  unsigned threshold_energy_index;

  PhotoatomicReactionACEFactory::removeZerosFromProcessedCrossSection(
			    energy_grid,
			    raw_photoatom_data.extractCoherentCrossSection(),
			    coherent_cross_section,
			    threshold_energy_index );

  // Create the coherent scattering distribution
  Teuchos::RCP<const CoherentScatteringDistribution> distribution;

  CoherentScatteringDistributionACEFactory::createEfficientCoherentDistribution(
					                    raw_photoatom_data,
							    distribution );  

  // Create the coherent reaction
  coherent_reaction.reset(new CoherentPhotoatomicReaction<Utility::LogLog>(
							energy_grid,
							coherent_cross_section,
							threshold_energy_index,
							grid_searcher,
							distribution ) );
}

// Create a pair production photoatomic reaction
void PhotoatomicReactionACEFactory::createPairProductionReaction(
       const Data::XSSEPRDataExtractor& raw_photoatom_data,
       const Teuchos::ArrayRCP<const double>& energy_grid,
       const Teuchos::RCP<const Utility::HashBasedGridSearcher>& grid_searcher,
       Teuchos::RCP<PhotoatomicReaction>& pair_production_reaction,
       const bool use_detailed_pair_production_data )
{
  // Make sure the energy grid is valid
  testPrecondition( raw_photoatom_data.extractPhotonEnergyGrid().size() == 
		    energy_grid.size() );
  testPrecondition( Utility::Sort::isSortedAscending( energy_grid.begin(),
						      energy_grid.end() ) );

  // Extract the cross section
  Teuchos::ArrayRCP<double> pair_production_cross_section;
  unsigned threshold_energy_index;

  PhotoatomicReactionACEFactory::removeZerosFromProcessedCrossSection(
			energy_grid,
			raw_photoatom_data.extractPairProductionCrossSection(),
			pair_production_cross_section,
			threshold_energy_index );

  // Create the pair production reaction
  pair_production_reaction.reset(
		      new PairProductionPhotoatomicReaction<Utility::LogLog>(
					 energy_grid,
					 pair_production_cross_section,
					 threshold_energy_index,
					 grid_searcher,
					 use_detailed_pair_production_data ) );
}

// Create the total photoelectric photoatomic reaction
void PhotoatomicReactionACEFactory::createTotalPhotoelectricReaction(
       const Data::XSSEPRDataExtractor& raw_photoatom_data,
       const Teuchos::ArrayRCP<const double>& energy_grid,
       const Teuchos::RCP<const Utility::HashBasedGridSearcher>& grid_searcher,
       Teuchos::RCP<PhotoatomicReaction>& photoelectric_reaction )
{
  // Make sure the energy grid is valid
  testPrecondition( raw_photoatom_data.extractPhotonEnergyGrid().size() == 
		    energy_grid.size() );
  testPrecondition( Utility::Sort::isSortedAscending( energy_grid.begin(),
						      energy_grid.end() ) );

  // Extract the cross section
  Teuchos::ArrayRCP<double> photoelectric_cross_section;
  unsigned threshold_energy_index;

  PhotoatomicReactionACEFactory::removeZerosFromProcessedCrossSection(
			energy_grid,
			raw_photoatom_data.extractPhotoelectricCrossSection(),
			photoelectric_cross_section,
			threshold_energy_index );

  // Create the total photoelectric reaction
  photoelectric_reaction.reset(
		     new PhotoelectricPhotoatomicReaction<Utility::LogLog>(
						   energy_grid,
						   photoelectric_cross_section,
						   threshold_energy_index,
						   grid_searcher ) );
}

// Create the subshell photoelectric photoatomic reactions
void PhotoatomicReactionACEFactory::createSubshellPhotoelectricReactions(
       const Data::XSSEPRDataExtractor& raw_photoatom_data,
       const Teuchos::ArrayRCP<const double>& energy_grid,
       const Teuchos::RCP<const Utility::HashBasedGridSearcher>& grid_searcher,
       Teuchos::Array<Teuchos::RCP<PhotoatomicReaction> >&
       subshell_photoelectric_reactions )
{
  // Make sure the energy grid is valid
  testPrecondition( raw_photoatom_data.extractPhotonEnergyGrid().size() == 
		    energy_grid.size() );
  testPrecondition( Utility::Sort::isSortedAscending( energy_grid.begin(),
						      energy_grid.end() ) );

  subshell_photoelectric_reactions.clear();

  // Extract the subshell information
  Teuchos::ArrayView<const double> subshell_endf_designators = 
    raw_photoatom_data.extractSubshellENDFDesignators();

  Teuchos::Array<SubshellType> subshell_order(
					    subshell_endf_designators.size() );

    for( unsigned i = 0; i < subshell_order.size(); ++i )
    {
      subshell_order[i] = convertENDFDesignatorToSubshellEnum(
				      (unsigned)subshell_endf_designators[i] );
    }

  Teuchos::ArrayView<const double> binding_energies = 
    raw_photoatom_data.extractSubshellBindingEnergies();

  // Extract the subshell cross sections
  Teuchos::ArrayView<const double> raw_subshell_cross_sections = 
    raw_photoatom_data.extractSPHELBlock();

  unsigned num_subshells = subshell_order.size();
  unsigned num_energy_points = energy_grid.size();

  Teuchos::RCP<PhotoatomicReaction> subshell_photoelectric_reaction;

  for( unsigned subshell = 0; subshell < num_subshells; ++subshell )
  {
    Teuchos::ArrayRCP<double> subshell_cross_section;
    unsigned threshold_energy_index;

    Teuchos::ArrayView<const double> raw_subshell_cross_section = 
      raw_subshell_cross_sections( subshell*num_energy_points,
				   num_energy_points );

    PhotoatomicReactionACEFactory::removeZerosFromProcessedCrossSection(
						    energy_grid,
		                                    raw_subshell_cross_section,
						    subshell_cross_section,
						    threshold_energy_index );

    // Create the subshell photoelectric reaction
    subshell_photoelectric_reaction.reset(
	      new SubshellPhotoelectricPhotoatomicReaction<Utility::LogLog>(
						energy_grid,
						subshell_cross_section,
						threshold_energy_index,
						grid_searcher,
						subshell_order[subshell],
					        binding_energies[subshell] ) );

    subshell_photoelectric_reactions.push_back( 
					     subshell_photoelectric_reaction );
  }

  // Make sure the subshell photoelectric reactions have been created
  testPostcondition( subshell_photoelectric_reactions.size() > 0 );
}

// Create the heating photoatomic reaction
void PhotoatomicReactionACEFactory::createHeatingReaction(
       const Data::XSSEPRDataExtractor& raw_photoatom_data,
       const Teuchos::ArrayRCP<const double>& energy_grid,
       const Teuchos::RCP<const Utility::HashBasedGridSearcher>& grid_searcher,
       Teuchos::RCP<PhotoatomicReaction>& heating_reaction )
{
  // Make sure the energy grid is valid
  testPrecondition( raw_photoatom_data.extractPhotonEnergyGrid().size() == 
		    energy_grid.size() );
  testPrecondition( Utility::Sort::isSortedAscending( energy_grid.begin(),
						      energy_grid.end() ) );

  // Extract the cross section
  Teuchos::ArrayRCP<double> heating_cross_section;
  unsigned threshold_energy_index;

  PhotoatomicReactionACEFactory::removeZerosFromProcessedCrossSection(
			energy_grid,
			raw_photoatom_data.extractLHNMBlock(),
			heating_cross_section,
			threshold_energy_index );

  // Process the heating cross section (the logarithms are not stored)
  for( unsigned i = 0; i < heating_cross_section.size(); ++i )
    heating_cross_section[i] = log( heating_cross_section[i] );

  // Create the heating reaction
  heating_reaction.reset(
		     new AbsorptionPhotoatomicReaction<Utility::LogLog>(
					      energy_grid,
					      heating_cross_section,
					      threshold_energy_index,
					      grid_searcher,
					      HEATING_PHOTOATOMIC_REACTION ) );
}

// Remove the zeros from a processed cross section
void PhotoatomicReactionACEFactory::removeZerosFromProcessedCrossSection(
		     const Teuchos::ArrayRCP<const double>& energy_grid,
		     const Teuchos::ArrayView<const double>& raw_cross_section,
		     Teuchos::ArrayRCP<double>& cross_section,
		     unsigned& threshold_energy_index )
{
  // Make sure the energy grid is valid
  testPrecondition( energy_grid.size() > 1 );
  // Make sure the raw cross section is valid
  testPrecondition( raw_cross_section.size() == energy_grid.size() );

  cross_section.clear();

  // Find the first non-zero cross section value
  Teuchos::ArrayView<const double>::iterator start = 
    std::find_if( raw_cross_section.begin(),
		  raw_cross_section.end(),
		  PhotoatomicReactionACEFactory::notEqualZero );

  // Remove the zeros from the cross section
  cross_section.assign( start, raw_cross_section.end() );

  // Determine the threshold energy index of the reaction
  threshold_energy_index = energy_grid.size() - cross_section.size();  

  // Make sure the cross section is valid
  testPostcondition( cross_section.size() > 1 );
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_PhotoatomicReactionACEFactory.cpp
//---------------------------------------------------------------------------//
