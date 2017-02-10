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
#include "MonteCarlo_VoidAbsorptionElectroatomicReaction.hpp"

namespace MonteCarlo{

// Create the analog elastic scattering electroatomic reactions
void ElectroatomicReactionNativeFactory::createAnalogElasticReaction(
            const Data::ElectronPhotonRelaxationDataContainer& raw_electroatom_data,
            const Teuchos::ArrayRCP<const double>& energy_grid,
            const Teuchos::RCP<Utility::HashBasedGridSearcher>& grid_searcher,
            std::shared_ptr<ElectroatomicReaction>& elastic_reaction,
            const bool use_linlinlog_interpolation )
{
  // Make sure the energy grid is valid
  testPrecondition( raw_electroatom_data.getElectronEnergyGrid().size() ==
                    energy_grid.size() );
  testPrecondition( Utility::Sort::isSortedAscending( energy_grid.begin(),
                                                      energy_grid.end() ) );

  // Create the analog elastic scattering distribution
  std::shared_ptr<const AnalogElasticElectronScatteringDistribution> distribution;

  if ( use_linlinlog_interpolation )
  {
    // Create the analog elastic scattering distribution that uses LinLinLog interpolation
    ElasticElectronScatteringDistributionNativeFactory::createAnalogElasticDistribution<true>(
    distribution,
    raw_electroatom_data );
  }
  else
  {
    // Create the analog elastic scattering distribution that uses LinLinLin interpolation
    ElasticElectronScatteringDistributionNativeFactory::createAnalogElasticDistribution<false>(
    distribution,
    raw_electroatom_data );
  }

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

  // Calculate the analog cross section
  unsigned analog_threshold_energy_index =
    std::min( sr_threshold_energy_index, cutoff_threshold_energy_index );

  unsigned sr_threshold_diff =
    sr_threshold_energy_index - analog_threshold_energy_index;
  unsigned cutoff_threshold_diff =
    cutoff_threshold_energy_index - analog_threshold_energy_index;

  std::vector<double> combined_cross_section(
                           energy_grid.size() - analog_threshold_energy_index );

  for (unsigned i = 0; i < combined_cross_section.size(); ++i )
  {
    double energy = energy_grid[i + analog_threshold_energy_index];

    if ( i < sr_threshold_diff )
    {
      combined_cross_section[i] = cutoff_cross_section[i];
    }
    else if ( i < cutoff_threshold_diff )
    {
      combined_cross_section[i] = sr_cross_section[i];
    }
    else
    {
      combined_cross_section[i] =
        cutoff_cross_section[i-cutoff_threshold_diff] +
        sr_cross_section[i-sr_threshold_diff];
    }
  }

  Teuchos::ArrayRCP<double> analog_cross_section;
  analog_cross_section.assign( combined_cross_section.begin(),
                               combined_cross_section.end() );

  elastic_reaction.reset(
    new AnalogElasticElectroatomicReaction<Utility::LinLin>(
      energy_grid,
      analog_cross_section,
      analog_threshold_energy_index,
      grid_searcher,
      distribution ) );
}

// Create a hybrid elastic scattering electroatomic reaction
void ElectroatomicReactionNativeFactory::createHybridElasticReaction(
    const Data::ElectronPhotonRelaxationDataContainer& raw_electroatom_data,
    const Teuchos::ArrayRCP<const double>& energy_grid,
    const Teuchos::RCP<Utility::HashBasedGridSearcher>& grid_searcher,
    std::shared_ptr<ElectroatomicReaction>& elastic_reaction,
    const double cutoff_angle_cosine,
    const bool use_linlinlog_interpolation )
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

  // Reduced cutoff elastic cross section ratio
  std::vector<double> reduced_cutoff_ratio =
    raw_electroatom_data.getReducedCutoffCrossSectionRatios();

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

  if ( use_linlinlog_interpolation )
  {
    // Create the hybrid elastic scattering distribution that uses LinLinLog interpolation
    ElasticElectronScatteringDistributionNativeFactory::createHybridElasticDistribution<true>(
            distribution,
            grid_searcher,
            energy_grid,
            cutoff_cross_section,
            mp_cross_section,
            raw_electroatom_data,
            cutoff_angle_cosine );
  }
  else
  {
    // Create the hybrid elastic scattering distribution that uses LinLinLin interpolation
    ElasticElectronScatteringDistributionNativeFactory::createHybridElasticDistribution<false>(
            distribution,
            grid_searcher,
            energy_grid,
            cutoff_cross_section,
            mp_cross_section,
            raw_electroatom_data,
            cutoff_angle_cosine );
  }

  // Calculate the hybrid cross section
  unsigned hybrid_threshold_energy_index =
    std::min( mp_threshold_energy_index, cutoff_threshold_energy_index );

  unsigned mp_threshold_diff =
    mp_threshold_energy_index - hybrid_threshold_energy_index;
  unsigned cutoff_threshold_diff =
    cutoff_threshold_energy_index - hybrid_threshold_energy_index;

  std::vector<double> combined_cross_section(
                           energy_grid.size() - hybrid_threshold_energy_index );

  for (unsigned i = 0; i < combined_cross_section.size(); ++i )
  {
    double energy = energy_grid[i + hybrid_threshold_energy_index];

    if ( i < mp_threshold_diff )
    {
      combined_cross_section[i] = cutoff_cross_section[i]*reduced_cutoff_ratio[i];
    }
    else if ( i < cutoff_threshold_diff )
    {
      combined_cross_section[i] = mp_cross_section[i];
    }
    else
    {
      combined_cross_section[i] =
        cutoff_cross_section[i-cutoff_threshold_diff]*reduced_cutoff_ratio[i] +
        mp_cross_section[i-mp_threshold_diff];
    }
  }

  Teuchos::ArrayRCP<double> hybrid_cross_section;
  hybrid_cross_section.assign( combined_cross_section.begin(),
                               combined_cross_section.end() );


  // Create the hybrid elastic reaction
  elastic_reaction.reset(
    new HybridElasticElectroatomicReaction<Utility::LinLin>(
            energy_grid,
            hybrid_cross_section,
            hybrid_threshold_energy_index,
            grid_searcher,
            cutoff_angle_cosine,
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
