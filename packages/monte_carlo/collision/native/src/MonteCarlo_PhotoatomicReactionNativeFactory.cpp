//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_PhotoatomicReactionNativeFactory.cpp
//! \author Alex Robinson
//! \brief  The photoatomic reaction native data factory declaration
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <algorithm>
#include <limits>

// FRENSIE Includes
#include "MonteCarlo_PhotoatomicReactionNativeFactory.hpp"
#include "MonteCarlo_IncoherentPhotonScatteringDistributionNativeFactory.hpp"
#include "MonteCarlo_CoherentScatteringDistributionNativeFactory.hpp"
#include "MonteCarlo_IncoherentPhotoatomicReaction.hpp"
#include "MonteCarlo_SubshellIncoherentPhotoatomicReaction.hpp"
#include "MonteCarlo_CoherentPhotoatomicReaction.hpp"
#include "MonteCarlo_PairProductionPhotoatomicReaction.hpp"
#include "MonteCarlo_PhotoelectricPhotoatomicReaction.hpp"
#include "MonteCarlo_SubshellPhotoelectricPhotoatomicReaction.hpp"
#include "MonteCarlo_AbsorptionPhotoatomicReaction.hpp"
#include "MonteCarlo_SubshellType.hpp"
#include "Utility_TabularDistribution.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Create the incoherent photoatomic reaction(s)
void PhotoatomicReactionNativeFactory::createIncoherentReactions(
       const Data::ElectronPhotonRelaxationDataContainer& raw_photoatom_data,
       const Teuchos::ArrayRCP<const double>& energy_grid,
       const Teuchos::RCP<const Utility::HashBasedGridSearcher>& grid_searcher,
       Teuchos::Array<Teuchos::RCP<PhotoatomicReaction> >&
       incoherent_reactions,
       const IncoherentModelType incoherent_model,
       const double kahn_sampling_cutoff_energy )
{
  // Make sure the energy grid is valid
  testPrecondition( raw_photoatom_data.getPhotonEnergyGrid().size() ==
		    energy_grid.size() );
  testPrecondition( Utility::Sort::isSortedAscending( energy_grid.begin(),
						      energy_grid.end() ) );

  std::string model_name = 
    convertIncoherentModelTypeToString( incoherent_model );

  // Use Waller-Hartree data
  if( model_name.find( "Impulse" ) >= model_name.size() )
  {
    incoherent_reactions.resize( 1 );

    // Extract the cross section
    Teuchos::ArrayRCP<double> incoherent_cross_section;
    incoherent_cross_section.assign( 
	   raw_photoatom_data.getWallerHartreeIncoherentCrossSection().begin(),
	   raw_photoatom_data.getWallerHartreeIncoherentCrossSection().end() );

    unsigned threshold_index = 
      raw_photoatom_data.getWallerHartreeIncoherentCrossSectionThresholdEnergyIndex();

    // Create the scattering distribution
    Teuchos::RCP<const IncoherentPhotonScatteringDistribution> distribution;

    IncoherentPhotonScatteringDistributionNativeFactory::createIncoherentDistribution( 
						 raw_photoatom_data,
						 distribution,
						 incoherent_model,
						 kahn_sampling_cutoff_energy );
    
    // Create the incoherent reaction
    incoherent_reactions[0].reset(
		      new IncoherentPhotoatomicReaction<Utility::LinLin,false>(
						     energy_grid,
						     incoherent_cross_section,
						     threshold_index,
						     grid_searcher,
						     distribution ) );
  }
  // Create the subshell reactions using the impulse approximation
  else
  {
    incoherent_reactions.clear();

    Teuchos::RCP<PhotoatomicReaction> subshell_incoherent_reaction;
    
    std::set<unsigned>::const_iterator subshell_it = 
      raw_photoatom_data.getSubshells().begin();

    while( subshell_it != raw_photoatom_data.getSubshells().end() )
    {
      // Extract the cross section
      Teuchos::ArrayRCP<double> subshell_incoherent_cross_section;
      subshell_incoherent_cross_section.assign(
	   raw_photoatom_data.getImpulseApproxSubshellIncoherentCrossSection(*subshell_it).begin(),
	   raw_photoatom_data.getImpulseApproxSubshellIncoherentCrossSection(*subshell_it).end() );

      unsigned subshell_threshold_index = 
	raw_photoatom_data.getImpulseApproxSubshellIncoherentCrossSectionThresholdEnergyIndex(*subshell_it);

      // Create the subshell incoherent distribution
      Teuchos::RCP<const IncoherentPhotonScatteringDistribution> 
	base_distribution;

      IncoherentPhotonScatteringDistributionNativeFactory::createIncoherentDistribution( 
						   raw_photoatom_data,
						   base_distribution,
						   incoherent_model,
						   kahn_sampling_cutoff_energy,
						   *subshell_it );
      
      Teuchos::RCP<const SubshellIncoherentPhotonScatteringDistribution> 
      distribution = Teuchos::rcp_dynamic_cast<const SubshellIncoherentPhotonScatteringDistribution>( base_distribution );

      subshell_incoherent_reaction.reset(
	   new SubshellIncoherentPhotoatomicReaction<Utility::LinLin,false>(
		   energy_grid,
		   subshell_incoherent_cross_section,
		   subshell_threshold_index,
		   grid_searcher,
		   distribution ) );

      incoherent_reactions.push_back( subshell_incoherent_reaction );
      
      ++subshell_it;
    }
  }
}

// Create the coherent scattering photoatomic reaction
void PhotoatomicReactionNativeFactory::createCoherentReaction(
       const Data::ElectronPhotonRelaxationDataContainer& raw_photoatom_data,
       const Teuchos::ArrayRCP<const double>& energy_grid,
       const Teuchos::RCP<const Utility::HashBasedGridSearcher>& grid_searcher,
       Teuchos::RCP<PhotoatomicReaction>& coherent_reaction )
{
  // Make sure the energy grid is valid
  testPrecondition( raw_photoatom_data.getPhotonEnergyGrid().size() ==
		    energy_grid.size() );
  testPrecondition( Utility::Sort::isSortedAscending( energy_grid.begin(),
						      energy_grid.end() ) );

  Teuchos::ArrayRCP<double> coherent_cross_section;
  coherent_cross_section.assign(
	     raw_photoatom_data.getWallerHartreeCoherentCrossSection().begin(),
	     raw_photoatom_data.getWallerHartreeCoherentCrossSection().end() );

  unsigned threshold_index = 
    raw_photoatom_data.getWallerHartreeCoherentCrossSectionThresholdEnergyIndex();

  // Create the coherent scattering distribution
  Teuchos::RCP<const CoherentScatteringDistribution> distribution;

  CoherentScatteringDistributionNativeFactory::createEfficientCoherentDistribution(
					                    raw_photoatom_data,
							    distribution ); 
  
  // Create the coherent reaction
  coherent_reaction.reset(
		        new CoherentPhotoatomicReaction<Utility::LinLin,false>(
							energy_grid,
							coherent_cross_section,
							threshold_index,
							grid_searcher,
							distribution ) );
}

// Create the pair production photoatomic reaction
void PhotoatomicReactionNativeFactory::createPairProductionReaction(
       const Data::ElectronPhotonRelaxationDataContainer& raw_photoatom_data,
       const Teuchos::ArrayRCP<const double>& energy_grid,
       const Teuchos::RCP<const Utility::HashBasedGridSearcher>& grid_searcher,
       Teuchos::RCP<PhotoatomicReaction>& pair_production_reaction,
       const bool use_detailed_pair_production_data )
{
  // Make sure the energy grid is valid
  testPrecondition( raw_photoatom_data.getPhotonEnergyGrid().size() ==
		    energy_grid.size() );
  testPrecondition( Utility::Sort::isSortedAscending( energy_grid.begin(),
						      energy_grid.end() ) );

  Teuchos::ArrayRCP<double> pair_production_cross_section;
  pair_production_cross_section.assign(
	     raw_photoatom_data.getPairProductionCrossSection().begin(),
	     raw_photoatom_data.getPairProductionCrossSection().end() );

  unsigned threshold_index = 
    raw_photoatom_data.getPairProductionCrossSectionThresholdEnergyIndex();

  pair_production_reaction.reset(
		  new PairProductionPhotoatomicReaction<Utility::LinLin,false>(
					 energy_grid,
					 pair_production_cross_section,
					 threshold_index,
					 grid_searcher,
					 use_detailed_pair_production_data ) );
}

// Create the total photoelectric photoatomic reaction
void PhotoatomicReactionNativeFactory::createTotalPhotoelectricReaction(
       const Data::ElectronPhotonRelaxationDataContainer& raw_photoatom_data,
       const Teuchos::ArrayRCP<const double>& energy_grid,
       const Teuchos::RCP<const Utility::HashBasedGridSearcher>& grid_searcher,
       Teuchos::RCP<PhotoatomicReaction>& photoelectric_reaction )
{
  // Make sure the energy grid is valid
  testPrecondition( raw_photoatom_data.getPhotonEnergyGrid().size() ==
		    energy_grid.size() );
  testPrecondition( Utility::Sort::isSortedAscending( energy_grid.begin(),
						      energy_grid.end() ) );

  Teuchos::ArrayRCP<double> photoelectric_cross_section;
  photoelectric_cross_section.assign(
	     raw_photoatom_data.getPhotoelectricCrossSection().begin(),
	     raw_photoatom_data.getPhotoelectricCrossSection().end() );

  unsigned threshold_index = 
    raw_photoatom_data.getPhotoelectricCrossSectionThresholdEnergyIndex();

  // Create the total photoelectric reaction
  photoelectric_reaction.reset( 
		   new PhotoelectricPhotoatomicReaction<Utility::LinLin,false>(
						   energy_grid,
						   photoelectric_cross_section,
						   threshold_index,
						   grid_searcher ) );
}
					       
// Create the subshell photoelectric photoatomic reactions
void PhotoatomicReactionNativeFactory::createSubshellPhotoelectricReactions(
       const Data::ElectronPhotonRelaxationDataContainer& raw_photoatom_data,
       const Teuchos::ArrayRCP<const double>& energy_grid,
       const Teuchos::RCP<const Utility::HashBasedGridSearcher>& grid_searcher,
       Teuchos::Array<Teuchos::RCP<PhotoatomicReaction> >&
       subshell_photoelectric_reactions )
{
  // Make sure the energy grid is valid
  testPrecondition( raw_photoatom_data.getPhotonEnergyGrid().size() ==
		    energy_grid.size() );
  testPrecondition( Utility::Sort::isSortedAscending( energy_grid.begin(),
						      energy_grid.end() ) );

  subshell_photoelectric_reactions.clear();

  Teuchos::RCP<PhotoatomicReaction> subshell_photoelectric_reaction;

  std::set<unsigned>::const_iterator subshell_it = 
    raw_photoatom_data.getSubshells().begin();

  while( subshell_it != raw_photoatom_data.getSubshells().end() )
  {
    // Extract the cross section
    Teuchos::ArrayRCP<double> subshell_photoelectric_cross_section;
    subshell_photoelectric_cross_section.assign(
      raw_photoatom_data.getSubshellPhotoelectricCrossSection(*subshell_it).begin(),
      raw_photoatom_data.getSubshellPhotoelectricCrossSection(*subshell_it).end() );

    unsigned subshell_threshold_index = 
      raw_photoatom_data.getSubshellPhotoelectricCrossSectionThresholdEnergyIndex( *subshell_it );

    subshell_photoelectric_reaction.reset(
	   new SubshellPhotoelectricPhotoatomicReaction<Utility::LinLin,false>(
	       energy_grid,
	       subshell_photoelectric_cross_section,
	       subshell_threshold_index,
	       grid_searcher,
	       convertENDFDesignatorToSubshellEnum( *subshell_it ),
	       raw_photoatom_data.getSubshellBindingEnergy( *subshell_it ) ) );

    subshell_photoelectric_reactions.push_back( 
					     subshell_photoelectric_reaction );

    ++subshell_it;
  }
}

// Create the heating photoatomic reaction
void PhotoatomicReactionNativeFactory::createHeatingReaction(
       const Data::ElectronPhotonRelaxationDataContainer& raw_photoatom_data,
       const Teuchos::ArrayRCP<const double>& energy_grid,
       const Teuchos::RCP<const Utility::HashBasedGridSearcher>& grid_searcher,
       Teuchos::RCP<PhotoatomicReaction>& heating_reaction )
{
  // Make sure the energy grid is valid
  testPrecondition( raw_photoatom_data.getPhotonEnergyGrid().size() ==
		    energy_grid.size() );
  testPrecondition( Utility::Sort::isSortedAscending( energy_grid.begin(),
						      energy_grid.end() ) );

  Teuchos::ArrayRCP<double> heating_cross_section;
  heating_cross_section.assign(
	     raw_photoatom_data.getAveragePhotonHeatingNumbers().begin(),
	     raw_photoatom_data.getAveragePhotonHeatingNumbers().end() );

  unsigned threshold_index = 0u;

  // Create the heating reaction
  heating_reaction.reset(
		      new AbsorptionPhotoatomicReaction<Utility::LinLin,false>(
					      energy_grid,
					      heating_cross_section,
					      threshold_index,
					      grid_searcher,
					      HEATING_PHOTOATOMIC_REACTION ) );
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_PhotoatomicReactionNativeFactory.cpp
//---------------------------------------------------------------------------//
