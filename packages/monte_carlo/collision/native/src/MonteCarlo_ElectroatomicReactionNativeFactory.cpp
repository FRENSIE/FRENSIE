//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ElectroatomicReactionNativeFactory.cpp
//! \author Luke Kersting
//! \brief  The electroatomic reaction Native data factory definition
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <algorithm>

// FRENSIE Includes
#include "MonteCarlo_ElectroatomicReactionNativeFactory.hpp"
#include "MonteCarlo_AnalogElasticElectroatomicReaction.hpp"
#include "MonteCarlo_ScreenedRutherfordElasticElectroatomicReaction.hpp"
#include "MonteCarlo_ElasticElectronScatteringDistributionNativeFactory.hpp"
#include "MonteCarlo_AtomicExcitationElectroatomicReaction.hpp"
#include "MonteCarlo_AtomicExcitationElectronScatteringDistributionNativeFactory.hpp"
#include "MonteCarlo_BremsstrahlungElectroatomicReaction.hpp"
#include "MonteCarlo_BremsstrahlungElectronScatteringDistributionNativeFactory.hpp"
#include "MonteCarlo_ElectroionizationElectroatomicReaction.hpp"
#include "MonteCarlo_ElectroionizationSubshellElectroatomicReaction.hpp"
#include "MonteCarlo_ElectroionizationSubshellElectronScatteringDistributionNativeFactory.hpp"
#include "MonteCarlo_VoidAbsorptionElectroatomicReaction.hpp"
#include "MonteCarlo_SubshellType.hpp"
#include "Utility_TabularDistribution.hpp"
#include "Utility_SortAlgorithms.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Create the analog elastic scattering electroatomic reactions
void ElectroatomicReactionNativeFactory::createAnalogElasticReaction(
			const Data::EvaluatedElectronDataContainer& raw_electroatom_data,
			const Teuchos::ArrayRCP<const double>& energy_grid,
			Teuchos::RCP<ElectroatomicReaction>& elastic_reaction,
            const double lower_cutoff_angle )
{
  // Make sure the energy grid is valid
  testPrecondition( raw_electroatom_data.getElectronEnergyGrid().size() == 
                    energy_grid.size() );
  testPrecondition( Utility::Sort::isSortedAscending( energy_grid.begin(),
                                                      energy_grid.end() ) );

  // Create the analog elastic scattering distribution
  Teuchos::RCP<const AnalogElasticElectronScatteringDistribution> distribution;

  ElasticElectronScatteringDistributionNativeFactory::createAnalogElasticDistribution(
    distribution,
    raw_electroatom_data,
    lower_cutoff_angle ); 

  // Analog elastic cross section 
  Teuchos::ArrayRCP<double> elastic_cross_section;
  elastic_cross_section.assign( 
    raw_electroatom_data.getCutoffElasticCrossSection().begin(),
	raw_electroatom_data.getCutoffElasticCrossSection().end() );
  
  // Analog elastic cross section threshold energy bin index
  unsigned threshold_energy_index =
    raw_electroatom_data.getCutoffElasticCrossSectionThresholdEnergyIndex();

  elastic_reaction.reset(
	new AnalogElasticElectroatomicReaction<Utility::LinLin>(
						  energy_grid,
						  elastic_cross_section,
						  threshold_energy_index,
						  distribution,
                          lower_cutoff_angle ) );
}

// Create the screened Rutherford elastic scattering electroatomic reaction
void ElectroatomicReactionNativeFactory::createScreenedRutherfordElasticReaction(
			const Data::EvaluatedElectronDataContainer& raw_electroatom_data,
			const Teuchos::ArrayRCP<const double>& energy_grid,
			Teuchos::RCP<ElectroatomicReaction>& elastic_reaction,
            const double upper_cutoff_angle )
{
  // Make sure the energy grid is valid
  testPrecondition( raw_electroatom_data.getElectronEnergyGrid().size() == 
                    energy_grid.size() );
  testPrecondition( Utility::Sort::isSortedAscending( energy_grid.begin(),
                                                      energy_grid.end() ) );


  // Create the screened Rutherford elastic scattering distribution
  Teuchos::RCP<const ScreenedRutherfordElasticElectronScatteringDistribution> 
    distribution;

  ElasticElectronScatteringDistributionNativeFactory::createScreenedRutherfordElasticDistribution(
    distribution,
    raw_electroatom_data,
    upper_cutoff_angle ); 

  // Screened Rutherford elastic cross section 
  Teuchos::ArrayRCP<double> elastic_cross_section;
  elastic_cross_section.assign( 
    raw_electroatom_data.getScreenedRutherfordElasticCrossSection().begin(),
	raw_electroatom_data.getScreenedRutherfordElasticCrossSection().end() );

  // Screened Rutherford elastic cross section threshold energy bin index
  unsigned threshold_energy_index =
    raw_electroatom_data.getScreenedRutherfordElasticCrossSectionThresholdEnergyIndex();


  elastic_reaction.reset(
	new ScreenedRutherfordElasticElectroatomicReaction<Utility::LinLin>(
						  energy_grid,
						  elastic_cross_section,
						  threshold_energy_index,
						  distribution,
                          upper_cutoff_angle ) );
}

// Create an atomic excitation electroatomic reaction
void ElectroatomicReactionNativeFactory::createAtomicExcitationReaction(
			const Data::EvaluatedElectronDataContainer& raw_electroatom_data,
			const Teuchos::ArrayRCP<const double>& energy_grid,
			Teuchos::RCP<ElectroatomicReaction>& atomic_excitation_reaction )
{
  // Make sure the energy grid is valid
  testPrecondition( raw_electroatom_data.getElectronEnergyGrid().size() == 
                    energy_grid.size() );
  testPrecondition( Utility::Sort::isSortedAscending( energy_grid.begin(),
                                                      energy_grid.end() ) );

  // Atomic Excitation cross section 
  Teuchos::ArrayRCP<double> atomic_excitation_cross_section;
  atomic_excitation_cross_section.assign( 
    raw_electroatom_data.getAtomicExcitationCrossSection().begin(),
	raw_electroatom_data.getAtomicExcitationCrossSection().end() );
  
  // Index of first non zero cross section in the energy grid
  unsigned threshold_energy_index = 
    raw_electroatom_data.getAtomicExcitationCrossSectionThresholdEnergyIndex();


  // Create the energy loss distribution
  Teuchos::RCP<const AtomicExcitationElectronScatteringDistribution> 
    energy_loss_distribution;

  AtomicExcitationElectronScatteringDistributionNativeFactory::createAtomicExcitationDistribution(
                                                 raw_electroatom_data,
                                                 energy_loss_distribution ); 
 
  atomic_excitation_reaction.reset(
	new AtomicExcitationElectroatomicReaction<Utility::LinLin>(
                                                energy_grid,
                                                atomic_excitation_cross_section,
                                                threshold_energy_index,				
                                                energy_loss_distribution ) );
}

// Create the subshell electroionization electroatomic reactions
void ElectroatomicReactionNativeFactory::createSubshellElectroionizationReactions(
		   const Data::EvaluatedElectronDataContainer& raw_electroatom_data,
		   const Teuchos::ArrayRCP<const double>& energy_grid,
           const Teuchos::Array<double>& binding_energies, 
		   Teuchos::Array<Teuchos::RCP<ElectroatomicReaction> >&
		   electroionization_subshell_reactions )
{
  // Make sure the energy grid is valid
  testPrecondition( raw_electroatom_data.getSubshells().size() == 
                    binding_energies.size() );

  // Make sure the binding energies are valid
  testPrecondition( raw_electroatom_data.getElectronEnergyGrid().size() == 
                    energy_grid.size() );
  testPrecondition( Utility::Sort::isSortedAscending( energy_grid.begin(),
                                                      energy_grid.end() ) );

  electroionization_subshell_reactions.clear();

  // Extract the subshell information
  std::set<unsigned> subshells = raw_electroatom_data.getSubshells();

  Teuchos::RCP<ElectroatomicReaction> electroionization_subshell_reaction;

  SubshellType subshell_type;

  std::set<unsigned>::iterator shell = subshells.begin();
  int i = 0;

  for( shell; shell != subshells.end(); ++shell ) 
  {
    // Convert subshell number to enum
    subshell_type = convertEADLDesignatorToSubshellEnum( *shell );

    // Electroionization cross section 
    Teuchos::ArrayRCP<double> subshell_cross_section;
    subshell_cross_section.assign( 
	   raw_electroatom_data.getElectroionizationCrossSection( *shell ).begin(),
	   raw_electroatom_data.getElectroionizationCrossSection( *shell ).end() );

    // Electroionization cross section threshold energy bin index
    unsigned threshold_energy_index =
      raw_electroatom_data.getElectroionizationCrossSectionThresholdEnergyIndex( 
        *shell );

    // The electroionization subshell distribution
    Teuchos::RCP<const ElectroionizationSubshellElectronScatteringDistribution>
      electroionization_subshell_distribution;

    // Create the electroionization subshell distribution
    ElectroionizationSubshellElectronScatteringDistributionNativeFactory::createElectroionizationSubshellDistribution(
        raw_electroatom_data,
        *shell,
        binding_energies[i],
	    electroionization_subshell_distribution );


    // Create the subshell electroelectric reaction
    electroionization_subshell_reaction.reset(
      new ElectroionizationSubshellElectroatomicReaction<Utility::LinLin>(
              energy_grid,
              subshell_cross_section,
              threshold_energy_index,
              subshell_type,
              electroionization_subshell_distribution ) );

    electroionization_subshell_reactions.push_back( 
					  electroionization_subshell_reaction );

    ++i;
  }

  // Make sure the subshell electroelectric reactions have been created
  testPostcondition( electroionization_subshell_reactions.size() > 0 );
}

// Create a bremsstrahlung electroatomic reactions
void ElectroatomicReactionNativeFactory::createBremsstrahlungReaction(
		const Data::EvaluatedElectronDataContainer& raw_electroatom_data,
		const Teuchos::ArrayRCP<const double>& energy_grid,
		Teuchos::RCP<ElectroatomicReaction>& bremsstrahlung_reaction,
		BremsstrahlungAngularDistributionType photon_distribution_function )
{
  // Make sure the energy grid is valid
  testPrecondition( raw_electroatom_data.getElectronEnergyGrid().size() == 
                    energy_grid.size() );
  testPrecondition( Utility::Sort::isSortedAscending( energy_grid.begin(),
                                                      energy_grid.end() ) );

  // Bremsstrahlung cross section 
  Teuchos::ArrayRCP<double> bremsstrahlung_cross_section;
  bremsstrahlung_cross_section.assign( 
	   raw_electroatom_data.getBremsstrahlungCrossSection().begin(),
	   raw_electroatom_data.getBremsstrahlungCrossSection().end() );
  
  // Index of first non zero cross section in the energy grid
  unsigned threshold_energy_index = 
    raw_electroatom_data.getBremsstrahlungCrossSectionThresholdEnergyIndex();

  // Create bremsstrahlung scattering distribution
  Teuchos::RCP<const BremsstrahlungElectronScatteringDistribution>
    bremsstrahlung_distribution;
  
  if( photon_distribution_function = DIPOLE_DISTRIBUTION )
  {
    BremsstrahlungElectronScatteringDistributionNativeFactory::createBremsstrahlungDistribution( 
      raw_electroatom_data,
      bremsstrahlung_distribution );

  }
  else if( photon_distribution_function = TABULAR_DISTRIBUTION )
  {
  THROW_EXCEPTION( std::logic_error, 
          "Error! The detailed bremsstrahlung reaction has not been implemented");
  }
  else if( photon_distribution_function = TWOBS_DISTRIBUTION )
  {
    BremsstrahlungElectronScatteringDistributionNativeFactory::createBremsstrahlungDistribution( 
      raw_electroatom_data,
      bremsstrahlung_distribution,
      raw_electroatom_data.getAtomicNumber() );
  }

  // Create the bremsstrahlung reaction
  bremsstrahlung_reaction.reset(
		     new BremsstrahlungElectroatomicReaction<Utility::LinLin>(
					      energy_grid,
					      bremsstrahlung_cross_section,
					      threshold_energy_index,
					      bremsstrahlung_distribution ) );
}

// Create a void absorption electroatomic reaction
void ElectroatomicReactionNativeFactory::createVoidAbsorptionReaction(
      Teuchos::RCP<ElectroatomicReaction>& void_absorption_reaction )
{
  // Create the void absorption reaction
  void_absorption_reaction.reset(
		     new VoidAbsorptionElectroatomicReaction() );
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_ElectroatomicReactionNativeFactory.cpp
//---------------------------------------------------------------------------//
