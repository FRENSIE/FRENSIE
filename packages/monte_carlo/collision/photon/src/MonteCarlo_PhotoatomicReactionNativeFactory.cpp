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
#include "MonteCarlo_TripletProductionPhotoatomicReaction.hpp"
#include "MonteCarlo_PhotoelectricPhotoatomicReaction.hpp"
#include "MonteCarlo_SubshellPhotoelectricPhotoatomicReaction.hpp"
#include "MonteCarlo_AbsorptionPhotoatomicReaction.hpp"
#include "Data_SubshellType.hpp"
#include "Utility_TabularDistribution.hpp"
#include "Utility_DesignByContract.hpp"

namespace MonteCarlo{

// Create the incoherent photoatomic reaction(s)
void PhotoatomicReactionNativeFactory::createIncoherentReactions(
       const Data::ElectronPhotonRelaxationDataContainer& raw_photoatom_data,
       const std::shared_ptr<const std::vector<double> >& energy_grid,
       const std::shared_ptr<const Utility::HashBasedGridSearcher<double> >&
       grid_searcher,
       std::vector<std::shared_ptr<const PhotoatomicReaction> >&
       incoherent_reactions,
       const IncoherentModelType incoherent_model,
       const double kahn_sampling_cutoff_energy )
{
  // Make sure the energy grid is valid
  testPrecondition( raw_photoatom_data.getPhotonEnergyGrid().size() ==
		    energy_grid->size() );
  testPrecondition( Utility::Sort::isSortedAscending( energy_grid->begin(),
						      energy_grid->end() ) );

  std::string model_name = Utility::toString( incoherent_model );

  // Use Waller-Hartree data
  if( model_name.find( "Impulse" ) >= model_name.size() )
  {
    incoherent_reactions.resize( 1 );

    // Extract the cross section
    std::shared_ptr<std::vector<double> > incoherent_cross_section(
       new std::vector<double>( raw_photoatom_data.getWallerHartreeIncoherentCrossSection().begin(),
                                raw_photoatom_data.getWallerHartreeIncoherentCrossSection().end() ) );

    size_t threshold_index =
      raw_photoatom_data.getWallerHartreeIncoherentCrossSectionThresholdEnergyIndex();

    // Create the scattering distribution
    std::shared_ptr<const IncoherentPhotonScatteringDistribution> distribution;

    IncoherentPhotonScatteringDistributionNativeFactory::createDistribution(
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

    std::shared_ptr<PhotoatomicReaction> subshell_incoherent_reaction;

    std::set<unsigned>::const_iterator subshell_it =
      raw_photoatom_data.getSubshells().begin();

    while( subshell_it != raw_photoatom_data.getSubshells().end() )
    {
      // Extract the cross section
      std::shared_ptr<std::vector<double> > subshell_incoherent_cross_section(
         new std::vector<double>( raw_photoatom_data.getImpulseApproxSubshellIncoherentCrossSection(*subshell_it).begin(),
                                  raw_photoatom_data.getImpulseApproxSubshellIncoherentCrossSection(*subshell_it).end() ) );

      size_t subshell_threshold_index =
	raw_photoatom_data.getImpulseApproxSubshellIncoherentCrossSectionThresholdEnergyIndex(*subshell_it);

      // Create the subshell incoherent distribution
      std::shared_ptr<const IncoherentPhotonScatteringDistribution>
	base_distribution;

      IncoherentPhotonScatteringDistributionNativeFactory::createDistribution(
						   raw_photoatom_data,
						   base_distribution,
						   incoherent_model,
						   kahn_sampling_cutoff_energy,
						   *subshell_it );

      std::shared_ptr<const SubshellIncoherentPhotonScatteringDistribution>
        distribution = std::dynamic_pointer_cast<const SubshellIncoherentPhotonScatteringDistribution>( base_distribution );

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
       const std::shared_ptr<const std::vector<double> >& energy_grid,
       const std::shared_ptr<const Utility::HashBasedGridSearcher<double> >&
       grid_searcher,
       std::shared_ptr<const PhotoatomicReaction>& coherent_reaction )
{
  // Make sure the energy grid is valid
  testPrecondition( raw_photoatom_data.getPhotonEnergyGrid().size() ==
		    energy_grid->size() );
  testPrecondition( Utility::Sort::isSortedAscending( energy_grid->begin(),
						      energy_grid->end() ) );

  std::shared_ptr<std::vector<double> > coherent_cross_section(
     new std::vector<double>( raw_photoatom_data.getWallerHartreeCoherentCrossSection().begin(),
                              raw_photoatom_data.getWallerHartreeCoherentCrossSection().end() ) );

  size_t threshold_index =
    raw_photoatom_data.getWallerHartreeCoherentCrossSectionThresholdEnergyIndex();

  // Create the coherent scattering distribution
  std::shared_ptr<const CoherentScatteringDistribution> distribution;

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
       const std::shared_ptr<const std::vector<double> >& energy_grid,
       const std::shared_ptr<const Utility::HashBasedGridSearcher<double> >&
       grid_searcher,
       std::shared_ptr<const PhotoatomicReaction>& pair_production_reaction,
       const bool use_detailed_pair_production_data )
{
  // Make sure the energy grid is valid
  testPrecondition( raw_photoatom_data.getPhotonEnergyGrid().size() ==
		    energy_grid->size() );
  testPrecondition( Utility::Sort::isSortedAscending( energy_grid->begin(),
						      energy_grid->end() ) );

  std::shared_ptr<std::vector<double> > pair_production_cross_section(
     new std::vector<double>( raw_photoatom_data.getPairProductionCrossSection().begin(),
                              raw_photoatom_data.getPairProductionCrossSection().end() ) );

  size_t threshold_index =
    raw_photoatom_data.getPairProductionCrossSectionThresholdEnergyIndex();

  pair_production_reaction.reset(
		  new PairProductionPhotoatomicReaction<Utility::LinLin,false>(
					 energy_grid,
					 pair_production_cross_section,
					 threshold_index,
					 grid_searcher,
					 use_detailed_pair_production_data ) );
}

// Create the triplet production photoatomic reaction
void PhotoatomicReactionNativeFactory::createTripletProductionReaction(
       const Data::ElectronPhotonRelaxationDataContainer& raw_photoatom_data,
       const std::shared_ptr<const std::vector<double> >& energy_grid,
       const std::shared_ptr<const Utility::HashBasedGridSearcher<double> >&
       grid_searcher,
       std::shared_ptr<const PhotoatomicReaction>& triplet_production_reaction,
       const bool use_detailed_triplet_production_data )
{
  // Make sure the energy grid is valid
  testPrecondition( raw_photoatom_data.getPhotonEnergyGrid().size() ==
		    energy_grid->size() );
  testPrecondition( Utility::Sort::isSortedAscending( energy_grid->begin(),
						      energy_grid->end() ) );

  std::shared_ptr<std::vector<double> > triplet_production_cross_section(
     new std::vector<double>( raw_photoatom_data.getTripletProductionCrossSection().begin(),
                              raw_photoatom_data.getTripletProductionCrossSection().end() ) );

  size_t threshold_index =
    raw_photoatom_data.getTripletProductionCrossSectionThresholdEnergyIndex();

  triplet_production_reaction.reset(
               new TripletProductionPhotoatomicReaction<Utility::LinLin,false>(
                                      energy_grid,
                                      triplet_production_cross_section,
                                      threshold_index,
                                      grid_searcher,
                                      use_detailed_triplet_production_data ) );
}

// Create the total photoelectric photoatomic reaction
void PhotoatomicReactionNativeFactory::createTotalPhotoelectricReaction(
       const Data::ElectronPhotonRelaxationDataContainer& raw_photoatom_data,
       const std::shared_ptr<const std::vector<double> >& energy_grid,
       const std::shared_ptr<const Utility::HashBasedGridSearcher<double> >&
       grid_searcher,
       std::shared_ptr<const PhotoatomicReaction>& photoelectric_reaction )
{
  // Make sure the energy grid is valid
  testPrecondition( raw_photoatom_data.getPhotonEnergyGrid().size() ==
		    energy_grid->size() );
  testPrecondition( Utility::Sort::isSortedAscending( energy_grid->begin(),
						      energy_grid->end() ) );

  std::shared_ptr<std::vector<double> > photoelectric_cross_section(
     new std::vector<double>( raw_photoatom_data.getPhotoelectricCrossSection().begin(),
                              raw_photoatom_data.getPhotoelectricCrossSection().end() ) );

  size_t threshold_index =
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
       const std::shared_ptr<const std::vector<double> >& energy_grid,
       const std::shared_ptr<const Utility::HashBasedGridSearcher<double> >&
       grid_searcher,
       std::vector<std::shared_ptr<const PhotoatomicReaction> >&
       subshell_photoelectric_reactions )
{
  // Make sure the energy grid is valid
  testPrecondition( raw_photoatom_data.getPhotonEnergyGrid().size() ==
		    energy_grid->size() );
  testPrecondition( Utility::Sort::isSortedAscending( energy_grid->begin(),
						      energy_grid->end() ) );

  subshell_photoelectric_reactions.clear();

  std::shared_ptr<PhotoatomicReaction> subshell_photoelectric_reaction;

  std::set<unsigned>::const_iterator subshell_it =
    raw_photoatom_data.getSubshells().begin();

  while( subshell_it != raw_photoatom_data.getSubshells().end() )
  {
    // Extract the cross section
    std::shared_ptr<std::vector<double> > subshell_photoelectric_cross_section(
      new std::vector<double>( raw_photoatom_data.getSubshellPhotoelectricCrossSection(*subshell_it).begin(),
                               raw_photoatom_data.getSubshellPhotoelectricCrossSection(*subshell_it).end() ) );

    size_t subshell_threshold_index =
      raw_photoatom_data.getSubshellPhotoelectricCrossSectionThresholdEnergyIndex( *subshell_it );

    subshell_photoelectric_reaction.reset(
	   new SubshellPhotoelectricPhotoatomicReaction<Utility::LinLin,false>(
	       energy_grid,
	       subshell_photoelectric_cross_section,
	       subshell_threshold_index,
	       grid_searcher,
	      Data::convertENDFDesignatorToSubshellEnum( *subshell_it ),
	       raw_photoatom_data.getSubshellBindingEnergy( *subshell_it ) ) );

    subshell_photoelectric_reactions.push_back(
					     subshell_photoelectric_reaction );

    ++subshell_it;
  }
}

// Create the heating photoatomic reaction
void PhotoatomicReactionNativeFactory::createHeatingReaction(
       const Data::ElectronPhotonRelaxationDataContainer& raw_photoatom_data,
       const std::shared_ptr<const std::vector<double> >& energy_grid,
       const std::shared_ptr<const Utility::HashBasedGridSearcher<double> >&
       grid_searcher,
       std::shared_ptr<const PhotoatomicReaction>& heating_reaction )
{
  // Make sure the energy grid is valid
  testPrecondition( raw_photoatom_data.getPhotonEnergyGrid().size() ==
		    energy_grid->size() );
  testPrecondition( Utility::Sort::isSortedAscending( energy_grid->begin(),
						      energy_grid->end() ) );

  std::shared_ptr<std::vector<double> > heating_cross_section(
     new std::vector<double>( raw_photoatom_data.getAveragePhotonHeatingNumbers().begin(),
                              raw_photoatom_data.getAveragePhotonHeatingNumbers().end() ) );

  size_t threshold_index = 0u;

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
