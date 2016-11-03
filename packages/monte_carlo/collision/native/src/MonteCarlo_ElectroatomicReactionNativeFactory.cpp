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
#include "MonteCarlo_HybridElasticElectroatomicReaction.hpp"
#include "MonteCarlo_CutoffElasticElectroatomicReaction.hpp"
#include "MonteCarlo_ScreenedRutherfordElasticElectroatomicReaction.hpp"
#include "MonteCarlo_MomentPreservingElasticElectroatomicReaction.hpp"
#include "MonteCarlo_ElasticElectronScatteringDistributionNativeFactory.hpp"
#include "MonteCarlo_AtomicExcitationElectroatomicReaction.hpp"
#include "MonteCarlo_AtomicExcitationElectronScatteringDistributionNativeFactory.hpp"
#include "MonteCarlo_BremsstrahlungElectroatomicReaction.hpp"
#include "MonteCarlo_BremsstrahlungElectronScatteringDistributionNativeFactory.hpp"
#include "MonteCarlo_VoidAbsorptionElectroatomicReaction.hpp"
#include "Data_SubshellType.hpp"
#include "Utility_SortAlgorithms.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Create the analog elastic scattering electroatomic reactions
void ElectroatomicReactionNativeFactory::createAnalogElasticReaction(
			const Data::ElectronPhotonRelaxationDataContainer& raw_electroatom_data,
			const Teuchos::ArrayRCP<const double>& energy_grid,
            const Teuchos::RCP<Utility::HashBasedGridSearcher>& grid_searcher,
			std::shared_ptr<ElectroatomicReaction>& elastic_reaction )
{
  // Make sure the energy grid is valid
  testPrecondition( raw_electroatom_data.getElectronEnergyGrid().size() ==
                    energy_grid.size() );
  testPrecondition( Utility::Sort::isSortedAscending( energy_grid.begin(),
                                                      energy_grid.end() ) );

  // Create the analog elastic scattering distribution
  std::shared_ptr<const AnalogElasticElectronScatteringDistribution> distribution;

  ElasticElectronScatteringDistributionNativeFactory::createAnalogElasticDistribution(
    distribution,
    raw_electroatom_data );

  // Cutoff elastic cross section
  Teuchos::ArrayRCP<double> cutoff_cross_section;
  cutoff_cross_section.assign(
    raw_electroatom_data.getCutoffElasticCrossSection().begin(),
	raw_electroatom_data.getCutoffElasticCrossSection().end() );

  // Cutoff elastic cross section threshold energy bin index
  unsigned cutoff_threshold_energy_index =
    raw_electroatom_data.getCutoffElasticCrossSectionThresholdEnergyIndex();

  // Screened Rutherford elastic cross section
  Teuchos::ArrayRCP<double> sr_cross_section;
  sr_cross_section.assign(
    raw_electroatom_data.getScreenedRutherfordElasticCrossSection().begin(),
	raw_electroatom_data.getScreenedRutherfordElasticCrossSection().end() );

  // Screened Rutherford elastic cross section threshold energy bin index
  unsigned sr_threshold_energy_index =
    raw_electroatom_data.getScreenedRutherfordElasticCrossSectionThresholdEnergyIndex();

  elastic_reaction.reset(
	new AnalogElasticElectroatomicReaction<Utility::LinLin>(
						  energy_grid,
						  cutoff_cross_section,
						  sr_cross_section,
						  cutoff_threshold_energy_index,
						  sr_threshold_energy_index,
                          grid_searcher,
						  distribution ) );
}

// Create a hybrid elastic scattering electroatomic reaction
void ElectroatomicReactionNativeFactory::createHybridElasticReaction(
    const Data::ElectronPhotonRelaxationDataContainer& raw_electroatom_data,
    const Teuchos::ArrayRCP<const double>& energy_grid,
    const Teuchos::RCP<Utility::HashBasedGridSearcher>& grid_searcher,
    std::shared_ptr<ElectroatomicReaction>& elastic_reaction,
    const double cutoff_angle_cosine )
{
  // Make sure the energy grid is valid
  testPrecondition( raw_electroatom_data.getElectronEnergyGrid().size() ==
                    energy_grid.size() );
  testPrecondition( Utility::Sort::isSortedAscending( energy_grid.begin(),
                                                      energy_grid.end() ) );

  // Cutoff elastic cross section
  Teuchos::ArrayRCP<double> cutoff_cross_section;
  cutoff_cross_section.assign(
    raw_electroatom_data.getCutoffElasticCrossSection().begin(),
	raw_electroatom_data.getCutoffElasticCrossSection().end() );

  // Cutoff elastic cross section threshold energy bin index
  unsigned cutoff_threshold_energy_index =
    raw_electroatom_data.getCutoffElasticCrossSectionThresholdEnergyIndex();

  // Moment preserving elastic cross section
  Teuchos::ArrayRCP<double> mp_cross_section;
  mp_cross_section.assign(
    raw_electroatom_data.getMomentPreservingCrossSection().begin(),
	raw_electroatom_data.getMomentPreservingCrossSection().end() );

  // Moment preserving elastic cross section threshold energy bin index
  unsigned mp_threshold_energy_index =
    raw_electroatom_data.getMomentPreservingCrossSectionThresholdEnergyIndex();

  // Create the hybrid elastic scattering distribution
  std::shared_ptr<const HybridElasticElectronScatteringDistribution> distribution;

  ElasticElectronScatteringDistributionNativeFactory::createHybridElasticDistribution(
    distribution,
    grid_searcher,
    energy_grid,
    cutoff_cross_section,
    mp_cross_section,
    raw_electroatom_data,
    cutoff_angle_cosine );

  // Create the hybrid elastic reaction
  elastic_reaction.reset(
	new HybridElasticElectroatomicReaction<Utility::LinLin>(
            energy_grid,
            cutoff_cross_section,
            cutoff_threshold_energy_index,
            grid_searcher,
            mp_cross_section,
            mp_threshold_energy_index,
            cutoff_angle_cosine,
            distribution ) );
}

// Create the cutoff elastic scattering electroatomic reactions
void ElectroatomicReactionNativeFactory::createCutoffElasticReaction(
			const Data::ElectronPhotonRelaxationDataContainer& raw_electroatom_data,
			const Teuchos::ArrayRCP<const double>& energy_grid,
            const Teuchos::RCP<Utility::HashBasedGridSearcher>& grid_searcher,
			std::shared_ptr<ElectroatomicReaction>& elastic_reaction,
            const double cutoff_angle_cosine )
{
  // Make sure the energy grid is valid
  testPrecondition( raw_electroatom_data.getElectronEnergyGrid().size() ==
                    energy_grid.size() );
  testPrecondition( Utility::Sort::isSortedAscending( energy_grid.begin(),
                                                      energy_grid.end() ) );

  // Create the cutoff elastic scattering distribution
  std::shared_ptr<const CutoffElasticElectronScatteringDistribution> distribution;

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
			std::shared_ptr<ElectroatomicReaction>& elastic_reaction,
            const double cutoff_angle_cosine )
{
  // Make sure the energy grid is valid
  testPrecondition( raw_electroatom_data.getElectronEnergyGrid().size() ==
                    energy_grid.size() );
  testPrecondition( Utility::Sort::isSortedAscending( energy_grid.begin(),
                                                      energy_grid.end() ) );

  // Create the cutoff elastic scattering distribution
  std::shared_ptr<const CutoffElasticElectronScatteringDistribution>
    cutoff_distribution;

  ElasticElectronScatteringDistributionNativeFactory::createCutoffElasticDistribution(
    cutoff_distribution,
    raw_electroatom_data,
    cutoff_angle_cosine );


  // Create the screened Rutherford elastic scattering distribution
  std::shared_ptr<const ScreenedRutherfordElasticElectronScatteringDistribution>
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
			std::shared_ptr<ElectroatomicReaction>& elastic_reaction,
            const double cutoff_angle_cosine )
{
  // Make sure the energy grid is valid
  testPrecondition( raw_electroatom_data.getElectronEnergyGrid().size() ==
                    energy_grid.size() );
  testPrecondition( Utility::Sort::isSortedAscending( energy_grid.begin(),
                                                      energy_grid.end() ) );

  // Create the moment preserving elastic scattering distribution
  std::shared_ptr<const MomentPreservingElasticElectronScatteringDistribution>
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
			std::shared_ptr<ElectroatomicReaction>& atomic_excitation_reaction )
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
  std::shared_ptr<const AtomicExcitationElectronScatteringDistribution>
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

// Create a void absorption electroatomic reaction
void ElectroatomicReactionNativeFactory::createVoidAbsorptionReaction(
      std::shared_ptr<ElectroatomicReaction>& void_absorption_reaction )
{
  // Create the void absorption reaction
  void_absorption_reaction.reset(
		     new VoidAbsorptionElectroatomicReaction() );
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_ElectroatomicReactionNativeFactory.cpp
//---------------------------------------------------------------------------//
