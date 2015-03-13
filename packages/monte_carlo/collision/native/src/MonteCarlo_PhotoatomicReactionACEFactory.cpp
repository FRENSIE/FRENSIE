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

// FRENSIE Includes
#include "MonteCarlo_PhotoatomicReactionACEFactory.hpp"
#include "MonteCarlo_IncoherentPhotoatomicReaction.hpp"
#include "MonteCarlo_CoherentPhotoatomicReaction.hpp"
#include "MonteCarlo_PairProductionPhotoatomicReaction.hpp"
#include "MonteCarlo_PhotoelectricPhotoatomicReaction.hpp"
#include "MonteCarlo_SubshellPhotoelectricPhotoatomicReaction.hpp"
#include "MonteCarlo_AbsorptionPhotoatomicReaction.hpp"
#include "MonteCarlo_ComptonProfileSubshellConverterFactory.hpp"
#include "MonteCarlo_SubshellType.hpp"
#include "Utility_TabularDistribution.hpp"
#include "Utility_SortAlgorithms.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Create an incoherent scattering photoatomic reaction
void PhotoatomicReactionACEFactory::createIncoherentReaction(
			const Data::XSSEPRDataExtractor& raw_photoatom_data,
			const Teuchos::ArrayRCP<const double>& energy_grid,
			Teuchos::RCP<PhotoatomicReaction>& incoherent_reaction,
			const bool use_doppler_broadening_data )
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
  
  // Create the scattering function
  Teuchos::ArrayView<const double> jince_block = 
    raw_photoatom_data.extractJINCEBlock();

  unsigned scatt_func_size = jince_block.size()/2;

  Teuchos::Array<double> recoil_momentum( jince_block( 0, scatt_func_size ) );
  
  // The stored recoil momemtum has units of inverse Angstroms - convert to
  // inverse cm
  for( unsigned i = 0; i < scatt_func_size; ++i )
    recoil_momentum[i] *= 1e8;

  // Log-Log interpolation is required but first recoil momentum may be 0.0
  if( recoil_momentum.front() == 0.0 )
    recoil_momentum.front() = std::numeric_limits<double>::min();

  Teuchos::Array<double> scattering_function_values( 
			     jince_block( scatt_func_size, scatt_func_size ) );

  // Log-Log interpolation is required but first value may be 0.0
  if( scattering_function_values.front() == 0.0 )
    scattering_function_values.front() = std::numeric_limits<double>::min();

  Teuchos::RCP<Utility::OneDDistribution> scattering_function(
		     new Utility::TabularDistribution<Utility::LogLog>(
						recoil_momentum,
						scattering_function_values ) );
  
  if( use_doppler_broadening_data )
  {
    // Create the subshell order array
    Teuchos::ArrayView<const double> subshell_endf_designators = 
      raw_photoatom_data.extractSubshellENDFDesignators();
    
    Teuchos::Array<SubshellType> subshell_order(
					    subshell_endf_designators.size() );

    for( unsigned i = 0; i < subshell_order.size(); ++i )
    {
      subshell_order[i] = convertENDFDesignatorToSubshellEnum(
				      (unsigned)subshell_endf_designators[i] );
    }
    
    // Create the Compton profile subshell converter
    Teuchos::RCP<ComptonProfileSubshellConverter> converter;

    ComptonProfileSubshellConverterFactory::createConverter(
				    converter,
				    raw_photoatom_data.extractAtomicNumber() );
  
    // Create the compton profile distributions
    Teuchos::ArrayView<const double> lswd_block = 
      raw_photoatom_data.extractLSWDBlock();
    
    Teuchos::ArrayView<const double> swd_block = 
      raw_photoatom_data.extractSWDBlock();

    Teuchos::Array<Teuchos::RCP<const Utility::OneDDistribution> >
      compton_profiles( lswd_block.size() );
    
    for( unsigned subshell = 0; subshell < lswd_block.size(); ++subshell )
    {
      unsigned subshell_index = lswd_block[subshell]; 

      unsigned num_momentum_points = swd_block[subshell_index];
      
      // Ignore interp parameter (always assume log-log inerpolation)
      compton_profiles[subshell].reset(
	       new Utility::TabularDistribution<Utility::LogLin>(
			  swd_block( subshell_index + 1, num_momentum_points ),
			  swd_block( subshell_index + 1 + num_momentum_points,
				     num_momentum_points ) ) );
    }
    
    // Create the incoherent reaction
    incoherent_reaction.reset( 
		  new IncoherentPhotoatomicReaction<Utility::LogLog>(
			   energy_grid,
			   incoherent_cross_section,
			   threshold_energy_index,
			   scattering_function,
			   raw_photoatom_data.extractSubshellBindingEnergies(),
			   raw_photoatom_data.extractSubshellOccupancies(),
			   subshell_order,
			   converter,
			   compton_profiles ) );
  }
  // Ignore Doppler broadening
  else
  {
    incoherent_reaction.reset(
		 new IncoherentPhotoatomicReaction<Utility::LogLog>(
						    energy_grid,
						    incoherent_cross_section,
						    threshold_energy_index,
						    scattering_function ) );
  }
}

// Create a coherent scattering photoatomic reaction
void PhotoatomicReactionACEFactory::createCoherentReaction(
			const Data::XSSEPRDataExtractor& raw_photoatom_data,
			const Teuchos::ArrayRCP<const double>& energy_grid,
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

  // Create the atomic form factor
  Teuchos::ArrayView<const double> jcohe_block = 
    raw_photoatom_data.extractJCOHEBlock();

  unsigned form_factor_size = jcohe_block.size()/3;

  Teuchos::Array<double> recoil_momentum_squared(
					  jcohe_block( 0, form_factor_size ) );

  Teuchos::Array<double> form_factor_squared(
			 jcohe_block( 2*form_factor_size, form_factor_size ) );

  // The stored recoil momentum has units of inverse Angstroms - convert to
  // inverse cm^2
  for( unsigned i = 0; i < form_factor_size; ++i )
  {
    recoil_momentum_squared[i] *= recoil_momentum_squared[i]*1e16;
    
    form_factor_squared[i] *= form_factor_squared[i];
  }

  // Log-Log interpolation is required but the last recoil momentum may be 0.0
  if( recoil_momentum_squared.back() == 0.0 )
    recoil_momentum_squared.back() = std::numeric_limits<double>::min();

  // Log-Log interpolation is required but the last form factor value may be 0
  if( form_factor_squared.back() == 0.0 )
    form_factor_squared.back() = std::numeric_limits<double>::min();

  Teuchos::RCP<Utility::OneDDistribution> form_factor(
			     new Utility::TabularDistribution<Utility::LogLog>(
						      recoil_momentum_squared,
						      form_factor_squared ) );

  // Create the coherent reaction
  coherent_reaction.reset(
			  new CoherentPhotoatomicReaction<Utility::LogLog>(
							energy_grid,
							coherent_cross_section,
							threshold_energy_index,
							form_factor ) );
}

// Create a pair production photoatomic reaction
void PhotoatomicReactionACEFactory::createPairProductionReaction(
		   const Data::XSSEPRDataExtractor& raw_photoatom_data,
		   const Teuchos::ArrayRCP<const double>& energy_grid,
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
					 use_detailed_pair_production_data ) );
}

// Create the total photoelectric photoatomic reaction
void PhotoatomicReactionACEFactory::createTotalPhotoelectricReaction(
		   const Data::XSSEPRDataExtractor& raw_photoatom_data,
		   const Teuchos::ArrayRCP<const double>& energy_grid,
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
						   threshold_energy_index ) );
}

// Create the subshell photoelectric photoatomic reactions
void PhotoatomicReactionACEFactory::createSubshellPhotoelectricReactions(
		const Data::XSSEPRDataExtractor& raw_photoatom_data,
		const Teuchos::ArrayRCP<const double>& energy_grid,
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
