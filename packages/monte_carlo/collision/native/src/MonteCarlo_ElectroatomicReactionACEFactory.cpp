//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ElectroatomicReactionACEFactory.cpp
//! \author Luke Kersting
//! \brief  The electroatomic reaction ACE data factory definition
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <algorithm>

// FRENSIE Includes
#include "MonteCarlo_ElectroatomicReactionACEFactory.hpp"
//#include "MonteCarlo_HardElasticElectroatomicReaction.hpp"
#include "MonteCarlo_AtomicExcitationElectroatomicReaction.hpp"
#include "MonteCarlo_BremsstrahlungElectroatomicReaction.hpp"
#include "MonteCarlo_ElectroionizationElectroatomicReaction.hpp"
#include "Utility_TabularDistribution.hpp"
#include "Utility_SortAlgorithms.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{
/*
// Create a hard elastic scattering electroatomic reaction
void ElectroatomicReactionACEFactory::createHardElasticReaction(
			const Data::XSSEPRDataExtractor& raw_electroatom_data,
			const Teuchos::ArrayRCP<const double>& energy_grid,
			Teuchos::RCP<ElectroatomicReaction>& elastic_reaction,
            const double cutoff_angle_cosine )
{
  // Make sure the energy grid is valid
  testPrecondition( raw_electroatom_data.extractElectronEnergyGrid().size() == 
		    energy_grid.size() );
  testPrecondition( Utility::Sort::isSortedAscending( energy_grid.begin(),
						      energy_grid.end() ) );

  // Extract the cross section
  Teuchos::ArrayRCP<double> elastic_cross_section;
  unsigned threshold_energy_index;

  ElectroatomicReactionACEFactory::removeZerosFromProcessedCrossSection(
			    energy_grid,
			    raw_electroatom_data.extractElasticCrossSection(),
			    elastic_cross_section,
			    threshold_energy_index );

  // Extract the elastic scattering information data block (ELASI)
  Teuchos::ArrayView<const double> elasi_block(
				      xss_data_extractor->extractELASIBlock() );
  
  // Extract the number of tabulated distributions
  int size = elasi_block.size()/3;

  // Extract the energy grid for elastic scattering angular distributions
  Teuchos::Array<double> energy_grid(elasi_block(0,size));

  // Extract the table lengths for elastic scattering angular distributions
  Teuchos::Array<double> table_length(elasi_block(size,size));

  // Extract the offsets for elastic scattering angular distributions
  Teuchos::Array<double> offset(elasi_block(2*size,size));

  // Extract the elastic scattering angular distributions block (elas)
  Teuchos::ArrayView<const double> elas_block = 
    xss_data_extractor->extractELASBlock();

  // Create the elastic scattering distributions
  Teuchos::Array<Utility::Pair<double,Teuchos::RCP<Utility::OneDDistribution> > >
    scattering_function( size );
  
  for( unsigned n = 0; n < size; ++n )
  {
    scattering_function[n].first = energy_grid[n];

    scattering_function[n].second.reset( 
	  new Utility::HistogramDistribution(
		 elas_block( offset[n], table_length[n] ),
		 elas_block( offset[n] + 1 + table_length[n], table_length[n]-1 ),
         true ) );
  }

  // Get the atomic number 
  const int atomic_number = raw_photoatom_data.extractAtomicNumber();

  elastic_reaction.reset(
	new HardElasticElectroatomicReaction<Utility::LinLin>(
						  energy_grid,
						  elastic_cross_section,
						  threshold_energy_index,				
                          atomic_number,
                          cutoff_angle_cosine,
                          scattering_function ) );
}
*/
// Create an atomic excitation electroatomic reaction
void ElectroatomicReactionACEFactory::createAtomicExcitationReaction(
			const Data::XSSEPRDataExtractor& raw_electroatom_data,
			const Teuchos::ArrayRCP<const double>& energy_grid,
			Teuchos::RCP<ElectroatomicReaction>& atomic_excitation_reaction )
{
  // Make sure the energy grid is valid
  testPrecondition( raw_electroatom_data.extractElectronEnergyGrid().size() == 
		    energy_grid.size() );
  testPrecondition( Utility::Sort::isSortedAscending( energy_grid.begin(),
						      energy_grid.end() ) );

  // Extract the cross section
  Teuchos::ArrayRCP<double> atomic_excitation_cross_section;
  unsigned threshold_energy_index;

  ElectroatomicReactionACEFactory::removeZerosFromProcessedCrossSection(
			    energy_grid,
			    raw_electroatom_data.extractExcitationCrossSection(),
			    atomic_excitation_cross_section,
			    threshold_energy_index );
/*
  // Create the atomic form factor
  Teuchos::ArrayView<const double> jcohe_block = 
    raw_electroatom_data.extractJCOHEBlock();

  unsigned form_factor_size = jcohe_block.size()/3;

  Teuchos::Array<double> recoil_momentum_squared(
					  jcohe_block( 0, form_factor_size ) );

  Teuchos::Array<double> form_factor_squared(
			 jcohe_block( 2*form_factor_size, form_factor_size ) );

  // The stored recoil momemtum has units of inverse Angstroms - convert to
  // inverse cm^2
  for( unsigned i = 0; i < form_factor_size; ++i )
  {
    recoil_momentum_squared[i] *= recoil_momentum_squared[i]*1e16;
    
    form_factor_squared[i] *= form_factor_squared[i];
  }

  Teuchos::RCP<Utility::OneDDistribution> form_factor(
			     new Utility::TabularDistribution<Utility::LogLog>(
						      recoil_momentum_squared,
						      form_factor_squared ) );

  // Create the coherent reaction
  coherent_reaction.reset(
			  new CoherentElectroatomicReaction<Utility::LogLog>(
							energy_grid,
							coherent_cross_section,
							threshold_energy_index,
							form_factor ) );*/
}

// Create the total electroionization electroatomic reaction
static void createTotalElectroionizationReaction(
		   const Data::XSSEPRDataExtractor& raw_electroatom_data,
		   const Teuchos::ArrayRCP<const double>& energy_grid,
		   Teuchos::RCP<ElectroatomicReaction>& electroionization_reaction)
{
  // Make sure the energy grid is valid
  testPrecondition( raw_electroatom_data.extractElectronEnergyGrid().size() == 
		    energy_grid.size() );
  testPrecondition( Utility::Sort::isSortedAscending( energy_grid.begin(),
						      energy_grid.end() ) );

  // Extract the cross section
  Teuchos::ArrayRCP<double> electroelectric_cross_section;
  unsigned threshold_energy_index;

  ElectroatomicReactionACEFactory::removeZerosFromProcessedCrossSection(
			energy_grid,
			raw_electroatom_data.extractElectroionizationCrossSection(),
			electroionization_cross_section,
			threshold_energy_index );
/*
  // Create the total electroelectric reaction
  electroelectric_reaction.reset(
		     new ElectroelectricElectroatomicReaction<Utility::LinLin>(
						   energy_grid,
						   electroelectric_cross_section,
						   threshold_energy_index ) );
*/
}

// Create the subshell electroionization electroatomic reaction
  static void createSubshellElectroionizationReaction(
		   const Data::XSSEPRDataExtractor& raw_electroatom_data,
		   const Teuchos::ArrayRCP<const double>& energy_grid,
		   Teuchos::Array<Teuchos::RCP<ElectroatomicReaction> >&
		   subshell_electroionization_reactions )
{
  // Make sure the energy grid is valid
  testPrecondition( raw_electroatom_data.extractElectronEnergyGrid().size() == 
		    energy_grid.size() );
  testPrecondition( Utility::Sort::isSortedAscending( energy_grid.begin(),
						      energy_grid.end() ) );
/*
  subshell_electroelectric_reactions.clear();

  // Extract the subshell information
  Teuchos::ArrayView<const double> subshell_endf_designators = 
    raw_electroatom_data.extractSubshellENDFDesignators();

  Teuchos::Array<SubshellType> subshell_order(
					    subshell_endf_designators.size() );

    for( unsigned i = 0; i < subshell_order.size(); ++i )
    {
      subshell_order[i] = convertENDFDesignatorToSubshellEnum(
				      (unsigned)subshell_endf_designators[i] );
    }

  Teuchos::ArrayView<const double> binding_energies = 
    raw_electroatom_data.extractSubshellBindingEnergies();

  // Extract the subshell cross sections
  Teuchos::ArrayView<const double> raw_subshell_cross_sections = 
    raw_electroatom_data.extractSPHELBlock();

  unsigned num_subshells = subshell_order.size();
  unsigned num_energy_points = energy_grid.size();

  Teuchos::RCP<ElectroatomicReaction> subshell_electroelectric_reaction;

  for( unsigned subshell = 0; subshell < num_subshells; ++subshell )
  {
    Teuchos::ArrayRCP<double> subshell_cross_section;
    unsigned threshold_energy_index;

    Teuchos::ArrayView<const double> raw_subshell_cross_section = 
      raw_subshell_cross_sections( subshell*num_energy_points,
				   num_energy_points );

    ElectroatomicReactionACEFactory::removeZerosFromProcessedCrossSection(
						    energy_grid,
		                                    raw_subshell_cross_section,
						    subshell_cross_section,
						    threshold_energy_index );

    // Create the subshell electroelectric reaction
    subshell_electroelectric_reaction.reset(
	      new SubshellElectroelectricElectroatomicReaction<Utility::LogLog>(
						energy_grid,
						subshell_cross_section,
						threshold_energy_index,
						subshell_order[subshell],
					        binding_energies[subshell] ) );

    subshell_electroelectric_reactions.push_back( 
					     subshell_electroelectric_reaction );
  }

  // Make sure the subshell electroelectric reactions have been created
  testPostcondition( subshell_electroelectric_reactions.size() > 0 );*/
}

// Create a bremsstrahlung electroatomic reactions
  static void createBremsstrahlungReactions(
		const Data::XSSEPRDataExtractor& raw_electroatom_data,
		const Teuchos::ArrayRCP<const double>& energy_grid,
		Teuchos::RCP<ElectroatomicReaction>& bremsstrahlung_reactions
		const bool use_detailed_bremsstrahlung_data )
{
  // Make sure the energy grid is valid
  testPrecondition( raw_electroatom_data.extractElectronEnergyGrid().size() == 
		    energy_grid.size() );
  testPrecondition( Utility::Sort::isSortedAscending( energy_grid.begin(),
						      energy_grid.end() ) );

  // Extract the cross section
  Teuchos::ArrayRCP<double> electroelectric_cross_section;
  unsigned threshold_energy_index;

  ElectroatomicReactionACEFactory::removeZerosFromProcessedCrossSection(
			energy_grid,
			raw_electroatom_data.extractBremsstrahlungCrossSection(),
			electroionization_cross_section,
			threshold_energy_index );
/*
  // Extract the cross section
  Teuchos::ArrayRCP<double> heating_cross_section;
  unsigned threshold_energy_index;

  ElectroatomicReactionACEFactory::removeZerosFromProcessedCrossSection(
			energy_grid,
			raw_electroatom_data.extractLHNMBlock(),
			heating_cross_section,
			threshold_energy_index );

  // Process the heating cross section (the logarithms are not stored)
  for( unsigned i = 0; i < heating_cross_section.size(); ++i )
    heating_cross_section[i] = log( heating_cross_section[i] );

  // Create the heating reaction
  heating_reaction.reset(
		     new AbsorptionElectroatomicReaction<Utility::LogLog>(
					      energy_grid,
					      heating_cross_section,
					      threshold_energy_index,
					      HEATING_PHOTOATOMIC_REACTION ) );*/
}

// Remove the zeros from a processed cross section
void ElectroatomicReactionACEFactory::removeZerosFromProcessedCrossSection(
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
		  ElectroatomicReactionACEFactory::notEqualZero );

  // Remove the zeros from the cross section
  cross_section.assign( start, raw_cross_section.end() );

  // Determine the threshold energy index of the reaction
  threshold_energy_index = energy_grid.size() - cross_section.size();  

  // Make sure the cross section is valid
  testPostcondition( cross_section.size() > 1 );
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_ElectroatomicReactionACEFactory.cpp
//---------------------------------------------------------------------------//
