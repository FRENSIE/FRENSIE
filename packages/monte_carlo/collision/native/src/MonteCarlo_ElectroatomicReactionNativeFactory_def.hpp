//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ElectroatomicReactionNativeFactory_def.hpp
//! \author Luke Kersting
//! \brief  The electroatomic reaction Native data factory template definition
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_ELECTROATOMIC_REACTION_NATIVE_FACTORY_DEF_HPP
#define MONTE_CARLO_ELECTROATOMIC_REACTION_NATIVE_FACTORY_DEF_HPP

// FRENSIE Includes
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
#include "MonteCarlo_ElectroionizationSubshellElectroatomicReaction.hpp"
#include "MonteCarlo_ElectroionizationSubshellElectronScatteringDistributionNativeFactory.hpp"
#include "MonteCarlo_BremsstrahlungElectroatomicReaction.hpp"
#include "MonteCarlo_BremsstrahlungElectronScatteringDistributionNativeFactory.hpp"
#include "Data_SubshellType.hpp"
#include "Utility_SortAlgorithms.hpp"
#include "Utility_TabularDistribution.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Create the analog elastic scattering electroatomic reactions
template<typename TwoDInterpPolicy>
void ElectroatomicReactionNativeFactory::createAnalogElasticReaction(
            const Data::ElectronPhotonRelaxationDataContainer& raw_electroatom_data,
            const Teuchos::ArrayRCP<const double>& energy_grid,
            const Teuchos::RCP<Utility::HashBasedGridSearcher>& grid_searcher,
            std::shared_ptr<ElectroatomicReaction>& elastic_reaction,
            const bool correlated_sampling_mode_on,
            const double evaluation_tol )
{
  // Make sure the energy grid is valid
  testPrecondition( raw_electroatom_data.getElectronEnergyGrid().size() ==
                    energy_grid.size() );
  testPrecondition( Utility::Sort::isSortedAscending( energy_grid.begin(),
                                                      energy_grid.end() ) );

  // Create the analog elastic scattering distribution
  std::shared_ptr<const AnalogElasticElectronScatteringDistribution> distribution;

  // Create the analog elastic scattering distribution
  ElasticElectronScatteringDistributionNativeFactory::createAnalogElasticDistribution<TwoDInterpPolicy>(
    distribution,
    raw_electroatom_data,
    correlated_sampling_mode_on,
    evaluation_tol );

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
template<typename TwoDInterpPolicy>
void ElectroatomicReactionNativeFactory::createHybridElasticReaction(
    const Data::ElectronPhotonRelaxationDataContainer& raw_electroatom_data,
    const Teuchos::ArrayRCP<const double>& energy_grid,
    const Teuchos::RCP<Utility::HashBasedGridSearcher>& grid_searcher,
    std::shared_ptr<ElectroatomicReaction>& elastic_reaction,
    const double cutoff_angle_cosine,
    const bool correlated_sampling_mode_on,
    const double evaluation_tol )
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

  // Create the hybrid elastic scattering distribution that uses LinLinLog interpolation
  ElasticElectronScatteringDistributionNativeFactory::createHybridElasticDistribution<TwoDInterpPolicy>(
            distribution,
            grid_searcher,
            energy_grid,
            cutoff_cross_section,
            mp_cross_section,
            raw_electroatom_data,
            cutoff_angle_cosine,
            correlated_sampling_mode_on,
            evaluation_tol );

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
    new HybridElasticElectroatomicReaction<TwoDInterpPolicy,Utility::LinLin>(
            energy_grid,
            hybrid_cross_section,
            hybrid_threshold_energy_index,
            grid_searcher,
            cutoff_angle_cosine,
            distribution ) );
}

// Create the cutoff elastic scattering electroatomic reactions
template<typename TwoDInterpPolicy>
void ElectroatomicReactionNativeFactory::createCutoffElasticReaction(
            const Data::ElectronPhotonRelaxationDataContainer& raw_electroatom_data,
            const Teuchos::ArrayRCP<const double>& energy_grid,
            const Teuchos::RCP<Utility::HashBasedGridSearcher>& grid_searcher,
            std::shared_ptr<ElectroatomicReaction>& elastic_reaction,
            const double cutoff_angle_cosine,
            const bool correlated_sampling_mode_on,
            const double evaluation_tol )
{
  // Make sure the energy grid is valid
  testPrecondition( raw_electroatom_data.getElectronEnergyGrid().size() ==
                    energy_grid.size() );
  testPrecondition( Utility::Sort::isSortedAscending( energy_grid.begin(),
                                                      energy_grid.end() ) );

  // Create the cutoff elastic scattering distribution
  std::shared_ptr<const CutoffElasticElectronScatteringDistribution> distribution;

  ElasticElectronScatteringDistributionNativeFactory::createCutoffElasticDistribution<TwoDInterpPolicy>(
    distribution,
    raw_electroatom_data,
    cutoff_angle_cosine,
    correlated_sampling_mode_on,
    evaluation_tol );

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
template<typename TwoDInterpPolicy>
void ElectroatomicReactionNativeFactory::createScreenedRutherfordElasticReaction(
            const Data::ElectronPhotonRelaxationDataContainer& raw_electroatom_data,
            const Teuchos::ArrayRCP<const double>& energy_grid,
            const Teuchos::RCP<Utility::HashBasedGridSearcher>& grid_searcher,
            std::shared_ptr<ElectroatomicReaction>& elastic_reaction,
            const double cutoff_angle_cosine,
            const bool correlated_sampling_mode_on,
            const double evaluation_tol )
{
  // Make sure the energy grid is valid
  testPrecondition( raw_electroatom_data.getElectronEnergyGrid().size() ==
                    energy_grid.size() );
  testPrecondition( Utility::Sort::isSortedAscending( energy_grid.begin(),
                                                      energy_grid.end() ) );

  // Create the cutoff elastic scattering distribution
  std::shared_ptr<const CutoffElasticElectronScatteringDistribution>
    cutoff_distribution;

  ElasticElectronScatteringDistributionNativeFactory::createCutoffElasticDistribution<TwoDInterpPolicy>(
    cutoff_distribution,
    raw_electroatom_data,
    cutoff_angle_cosine,
    correlated_sampling_mode_on,
    evaluation_tol );


  // Create the screened Rutherford elastic scattering distribution
  std::shared_ptr<const ScreenedRutherfordElasticElectronScatteringDistribution>
    distribution;

  ElasticElectronScatteringDistributionNativeFactory::createScreenedRutherfordElasticDistribution(
    distribution,
    cutoff_distribution,
    raw_electroatom_data.getAtomicNumber() );

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
template<typename TwoDInterpPolicy>
void ElectroatomicReactionNativeFactory::createMomentPreservingElasticReaction(
            const Data::ElectronPhotonRelaxationDataContainer& raw_electroatom_data,
            const Teuchos::ArrayRCP<const double>& energy_grid,
            const Teuchos::RCP<Utility::HashBasedGridSearcher>& grid_searcher,
            std::shared_ptr<ElectroatomicReaction>& elastic_reaction,
            const double cutoff_angle_cosine,
            const bool correlated_sampling_mode_on,
            const double evaluation_tol )
{
  // Make sure the energy grid is valid
  testPrecondition( raw_electroatom_data.getElectronEnergyGrid().size() ==
                    energy_grid.size() );
  testPrecondition( Utility::Sort::isSortedAscending( energy_grid.begin(),
                                                      energy_grid.end() ) );

  // Create the moment preserving elastic scattering distribution
  std::shared_ptr<const MomentPreservingElasticElectronScatteringDistribution>
    distribution;

  ElasticElectronScatteringDistributionNativeFactory::createMomentPreservingElasticDistribution<TwoDInterpPolicy>(
    distribution,
    raw_electroatom_data,
    cutoff_angle_cosine,
    correlated_sampling_mode_on,
    evaluation_tol );

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

// Create the subshell electroionization electroatomic reactions
template<typename ReactionType, typename TwoDInterpPolicy>
void ElectroatomicReactionNativeFactory::createSubshellElectroionizationReaction(
    const Data::ElectronPhotonRelaxationDataContainer& raw_electroatom_data,
    const Teuchos::ArrayRCP<const double>& energy_grid,
    const Teuchos::RCP<Utility::HashBasedGridSearcher>& grid_searcher,
    const unsigned subshell,
    std::shared_ptr<ReactionType>& electroionization_subshell_reaction,
    const bool correlated_sampling_mode_on,
    const bool unit_based_interpolation_mode_on,
    const double evaluation_tol )
{
  // Convert subshell number to enum
  Data::SubshellType subshell_type =
    Data::convertENDFDesignatorToSubshellEnum( subshell );

  // Electroionization cross section
  Teuchos::ArrayRCP<double> subshell_cross_section;
  subshell_cross_section.assign(
      raw_electroatom_data.getElectroionizationCrossSection( subshell ).begin(),
      raw_electroatom_data.getElectroionizationCrossSection( subshell ).end() );

  // Electroionization cross section threshold energy bin index
  unsigned threshold_energy_index =
      raw_electroatom_data.getElectroionizationCrossSectionThresholdEnergyIndex(
      subshell );

  // The electroionization subshell distribution
  std::shared_ptr<const ElectroionizationSubshellElectronScatteringDistribution>
      electroionization_subshell_distribution;

  // Create the electroionization subshell distribution
  ElectroionizationSubshellElectronScatteringDistributionNativeFactory::createElectroionizationSubshellDistribution<TwoDInterpPolicy>(
      raw_electroatom_data,
      subshell,
      raw_electroatom_data.getSubshellBindingEnergy( subshell ),
      electroionization_subshell_distribution,
      correlated_sampling_mode_on,
      unit_based_interpolation_mode_on,
      evaluation_tol );


  // Create the subshell electroelectric reaction
  electroionization_subshell_reaction.reset(
      new ElectroionizationSubshellElectroatomicReaction<Utility::LinLin>(
              energy_grid,
              subshell_cross_section,
              threshold_energy_index,
              grid_searcher,
              subshell_type,
              electroionization_subshell_distribution ) );
}

// Create the subshell electroionization electroatomic reactions
template<typename ReactionType, typename TwoDInterpPolicy>
void ElectroatomicReactionNativeFactory::createSubshellElectroionizationReactions(
    const Data::ElectronPhotonRelaxationDataContainer& raw_electroatom_data,
    const Teuchos::ArrayRCP<const double>& energy_grid,
    const Teuchos::RCP<Utility::HashBasedGridSearcher>& grid_searcher,
    std::vector<std::shared_ptr<ReactionType> >&
    electroionization_subshell_reactions,
    const bool correlated_sampling_mode_on,
    const bool unit_based_interpolation_mode_on,
    const double evaluation_tol )
{
  electroionization_subshell_reactions.clear();

  // Extract the subshell information
  std::set<unsigned> subshells = raw_electroatom_data.getSubshells();

  std::shared_ptr<ElectroatomicReaction> electroionization_subshell_reaction;

  std::set<unsigned>::iterator shell = subshells.begin();

  for( shell; shell != subshells.end(); ++shell )
  {
    ElectroatomicReactionNativeFactory::createSubshellElectroionizationReaction<ElectroatomicReaction,TwoDInterpPolicy>(
      raw_electroatom_data,
      energy_grid,
      grid_searcher,
      *shell,
      electroionization_subshell_reaction,
      correlated_sampling_mode_on,
      unit_based_interpolation_mode_on,
      evaluation_tol );

    electroionization_subshell_reactions.push_back(
                      electroionization_subshell_reaction );
  }

  // Make sure the subshell electroelectric reactions have been created
  testPostcondition( electroionization_subshell_reactions.size() > 0 );
}

// Create a bremsstrahlung electroatomic reactions
template<typename ReactionType, typename TwoDInterpPolicy>
void ElectroatomicReactionNativeFactory::createBremsstrahlungReaction(
    const Data::ElectronPhotonRelaxationDataContainer& raw_electroatom_data,
    const Teuchos::ArrayRCP<const double>& energy_grid,
    const Teuchos::RCP<Utility::HashBasedGridSearcher>& grid_searcher,
    std::shared_ptr<ReactionType>& bremsstrahlung_reaction,
    BremsstrahlungAngularDistributionType photon_distribution_function,
    const bool correlated_sampling_mode_on,
    const bool unit_based_interpolation_mode_on,
    const double evaluation_tol )
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
  std::shared_ptr<const BremsstrahlungElectronScatteringDistribution>
    bremsstrahlung_distribution;

  if( photon_distribution_function = DIPOLE_DISTRIBUTION )
  {
    BremsstrahlungElectronScatteringDistributionNativeFactory::createBremsstrahlungDistribution<TwoDInterpPolicy>(
      raw_electroatom_data,
      bremsstrahlung_distribution,
      correlated_sampling_mode_on,
      unit_based_interpolation_mode_on,
      evaluation_tol );

  }
  else if( photon_distribution_function = TABULAR_DISTRIBUTION )
  {
  THROW_EXCEPTION( std::logic_error,
          "Error! The detailed bremsstrahlung reaction has not been implemented");
  }
  else if( photon_distribution_function = TWOBS_DISTRIBUTION )
  {
    BremsstrahlungElectronScatteringDistributionNativeFactory::createBremsstrahlungDistribution<TwoDInterpPolicy>(
      raw_electroatom_data,
      raw_electroatom_data.getAtomicNumber(),
      bremsstrahlung_distribution,
      correlated_sampling_mode_on,
      unit_based_interpolation_mode_on,
      evaluation_tol );
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

} // end MontCarlo namespace

#endif // end MONTE_CARLO_ELECTROATOMIC_REACTION_NATIVE_FACTORY_DEF_HPP
