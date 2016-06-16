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
#include "MonteCarlo_CutoffElasticElectroatomicReaction.hpp"
#include "MonteCarlo_ScreenedRutherfordElasticElectroatomicReaction.hpp"
#include "MonteCarlo_MomentPreservingElasticElectroatomicReaction.hpp"
#include "MonteCarlo_ElasticElectronScatteringDistributionNativeFactory.hpp"
#include "MonteCarlo_AtomicExcitationElectroatomicReaction.hpp"
#include "MonteCarlo_AtomicExcitationElectronScatteringDistributionNativeFactory.hpp"
#include "MonteCarlo_BremsstrahlungElectroatomicReaction.hpp"
#include "MonteCarlo_BremsstrahlungElectronScatteringDistributionNativeFactory.hpp"
#include "MonteCarlo_ElectroionizationElectroatomicReaction.hpp"
#include "MonteCarlo_ElectroionizationSubshellElectroatomicReaction.hpp"
#include "MonteCarlo_ElectroionizationSubshellElectronScatteringDistributionNativeFactory.hpp"
#include "MonteCarlo_VoidAbsorptionElectroatomicReaction.hpp"
#include "Data_SubshellType.hpp"
#include "Utility_TabularDistribution.hpp"
#include "Utility_SortAlgorithms.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Create the cutoff elastic scattering electroatomic reactions
void ElectroatomicReactionNativeFactory::createCutoffElasticReaction(
			const Data::ElectronPhotonRelaxationDataContainer& raw_electroatom_data,
			const Teuchos::ArrayRCP<const double>& energy_grid,
            const Teuchos::RCP<Utility::HashBasedGridSearcher>& grid_searcher,
			Teuchos::RCP<ElectroatomicReaction>& elastic_reaction,
            const double cutoff_angle_cosine )
{
  // Make sure the energy grid is valid
  testPrecondition( raw_electroatom_data.getElectronEnergyGrid().size() ==
                    energy_grid.size() );
  testPrecondition( Utility::Sort::isSortedAscending( energy_grid.begin(),
                                                      energy_grid.end() ) );

  // Create the cutoff elastic scattering distribution
  Teuchos::RCP<const CutoffElasticElectronScatteringDistribution> distribution;

  ElasticElectronScatteringDistributionNativeFactory::createCutoffElasticDistribution(
    distribution,
    raw_electroatom_data,
    cutoff_angle_cosine );

  // Cutoff elastic cross section
  Teuchos::ArrayRCP<double> elastic_cross_section;
  elastic_cross_section.assign(
    raw_electroatom_data.getCutoffElasticCrossSection().begin(),
	raw_electroatom_data.getCutoffElasticCrossSection().end() );

  // Cutoff elastic cross section threshold energy bin index
  unsigned threshold_energy_index =
    raw_electroatom_data.getCutoffElasticCrossSectionThresholdEnergyIndex();

  elastic_reaction.reset(
	new CutoffElasticElectroatomicReaction<Utility::LinLin>(
						  energy_grid,
						  elastic_cross_section,
						  threshold_energy_index,
                          grid_searcher,
						  distribution ) );
}

// Create the screened Rutherford elastic scattering electroatomic reaction
void ElectroatomicReactionNativeFactory::createScreenedRutherfordElasticReaction(
			const Data::ElectronPhotonRelaxationDataContainer& raw_electroatom_data,
			const Teuchos::ArrayRCP<const double>& energy_grid,
            const Teuchos::RCP<Utility::HashBasedGridSearcher>& grid_searcher,
			Teuchos::RCP<ElectroatomicReaction>& elastic_reaction,
            const double cutoff_angle_cosine )
{
  // Make sure the energy grid is valid
  testPrecondition( raw_electroatom_data.getElectronEnergyGrid().size() ==
                    energy_grid.size() );
  testPrecondition( Utility::Sort::isSortedAscending( energy_grid.begin(),
                                                      energy_grid.end() ) );

  // Create the cutoff elastic scattering distribution
  Teuchos::RCP<const CutoffElasticElectronScatteringDistribution>
    cutoff_distribution;

  ElasticElectronScatteringDistributionNativeFactory::createCutoffElasticDistribution(
    cutoff_distribution,
    raw_electroatom_data,
    cutoff_angle_cosine );


  // Create the screened Rutherford elastic scattering distribution
  Teuchos::RCP<const ScreenedRutherfordElasticElectronScatteringDistribution>
    distribution;

  ElasticElectronScatteringDistributionNativeFactory::createScreenedRutherfordElasticDistribution(
    distribution,
    cutoff_distribution,
    raw_electroatom_data );

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
                          grid_searcher,
						  distribution ) );
}

// Create the moment preserving elastic scattering electroatomic reaction
void ElectroatomicReactionNativeFactory::createMomentPreservingElasticReaction(
			const Data::ElectronPhotonRelaxationDataContainer& raw_electroatom_data,
			const Teuchos::ArrayRCP<const double>& energy_grid,
            const Teuchos::RCP<Utility::HashBasedGridSearcher>& grid_searcher,
			Teuchos::RCP<ElectroatomicReaction>& elastic_reaction,
            const double cutoff_angle_cosine )
{
  // Make sure the energy grid is valid
  testPrecondition( raw_electroatom_data.getElectronEnergyGrid().size() ==
                    energy_grid.size() );
  testPrecondition( Utility::Sort::isSortedAscending( energy_grid.begin(),
                                                      energy_grid.end() ) );

  // Create the moment preserving elastic scattering distribution
  Teuchos::RCP<const MomentPreservingElasticElectronScatteringDistribution>
    distribution;

  ElasticElectronScatteringDistributionNativeFactory::createMomentPreservingElasticDistribution(
    distribution,
    raw_electroatom_data );

  // Moment preserving elastic cross section
  Teuchos::ArrayRCP<double> elastic_cross_section;
  elastic_cross_section.assign(
    raw_electroatom_data.getMomentPreservingCrossSection().begin(),
	raw_electroatom_data.getMomentPreservingCrossSection().end() );

  // Moment preserving elastic cross section threshold energy bin index
  unsigned threshold_energy_index =
    raw_electroatom_data.getMomentPreservingCrossSectionThresholdEnergyIndex();


  elastic_reaction.reset(
	new MomentPreservingElasticElectroatomicReaction<Utility::LinLin>(
						  energy_grid,
						  elastic_cross_section,
						  threshold_energy_index,
                          grid_searcher,
						  distribution ) );
}

// Create an atomic excitation electroatomic reaction
void ElectroatomicReactionNativeFactory::createAtomicExcitationReaction(
			const Data::ElectronPhotonRelaxationDataContainer& raw_electroatom_data,
			const Teuchos::ArrayRCP<const double>& energy_grid,
            const Teuchos::RCP<Utility::HashBasedGridSearcher>& grid_searcher,
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
                                                grid_searcher,
                                                energy_loss_distribution ) );
}

// Create the subshell electroionization electroatomic reactions
void ElectroatomicReactionNativeFactory::createSubshellElectroionizationReactions(
		   const Data::ElectronPhotonRelaxationDataContainer& raw_electroatom_data,
		   const Teuchos::ArrayRCP<const double>& energy_grid,
           const Teuchos::RCP<Utility::HashBasedGridSearcher>& grid_searcher,
		   Teuchos::Array<Teuchos::RCP<ElectroatomicReaction> >&
		   electroionization_subshell_reactions )
{
  electroionization_subshell_reactions.clear();

  // Extract the subshell information
  std::set<unsigned> subshells = raw_electroatom_data.getSubshells();

  Teuchos::RCP<ElectroatomicReaction> electroionization_subshell_reaction;

  Data::SubshellType subshell_type;

  std::set<unsigned>::iterator shell = subshells.begin();

  for( shell; shell != subshells.end(); ++shell )
  {
    // Convert subshell number to enum
    subshell_type = Data::convertENDFDesignatorToSubshellEnum( *shell );

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
        raw_electroatom_data.getSubshellBindingEnergy( *shell ),
	    electroionization_subshell_distribution );


    // Create the subshell electroelectric reaction
    electroionization_subshell_reaction.reset(
      new ElectroionizationSubshellElectroatomicReaction<Utility::LinLin>(
              energy_grid,
              subshell_cross_section,
              threshold_energy_index,
              grid_searcher,
              subshell_type,
              electroionization_subshell_distribution ) );

    electroionization_subshell_reactions.push_back(
					  electroionization_subshell_reaction );
  }

  // Make sure the subshell electroelectric reactions have been created
  testPostcondition( electroionization_subshell_reactions.size() > 0 );
}

// Create a bremsstrahlung electroatomic reactions
void ElectroatomicReactionNativeFactory::createBremsstrahlungReaction(
		const Data::ElectronPhotonRelaxationDataContainer& raw_electroatom_data,
		const Teuchos::ArrayRCP<const double>& energy_grid,
        const Teuchos::RCP<Utility::HashBasedGridSearcher>& grid_searcher,
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
                          grid_searcher,
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
