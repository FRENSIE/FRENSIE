//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_AdjointElectroatomicReactionNativeFactory_def.hpp
//! \author Luke Kersting
//! \brief  The adjoint electroatomic reaction Native data factory template definition
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_ADJOINT_ELECTROATOMIC_REACTION_NATIVE_FACTORY_DEF_HPP
#define MONTE_CARLO_ADJOINT_ELECTROATOMIC_REACTION_NATIVE_FACTORY_DEF_HPP

// Std Lib Includes
#include <algorithm>

// FRENSIE Includes
#include "MonteCarlo_AnalogElasticAdjointElectroatomicReaction.hpp"
#include "MonteCarlo_HybridElasticAdjointElectroatomicReaction.hpp"
#include "MonteCarlo_CutoffElasticAdjointElectroatomicReaction.hpp"
#include "MonteCarlo_ScreenedRutherfordElasticAdjointElectroatomicReaction.hpp"
#include "MonteCarlo_MomentPreservingElasticAdjointElectroatomicReaction.hpp"
#include "MonteCarlo_ElasticElectronScatteringDistributionNativeFactory.hpp"
#include "MonteCarlo_BremsstrahlungAdjointElectroatomicReaction.hpp"
#include "MonteCarlo_BremsstrahlungAdjointElectronScatteringDistributionNativeFactory.hpp"
#include "MonteCarlo_ElectroionizationSubshellAdjointElectroatomicReaction.hpp"
#include "MonteCarlo_ElectroionizationSubshellAdjointElectronScatteringDistributionNativeFactory.hpp"
#include "Data_SubshellType.hpp"
#include "Utility_TabularDistribution.hpp"
#include "Utility_SortAlgorithms.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Create the analog elastic scattering adjoint electroatomic reactions
template<typename TwoDInterpPolicy>
void AdjointElectroatomicReactionNativeFactory::createAnalogElasticReaction(
        const Data::AdjointElectronPhotonRelaxationDataContainer&
            raw_adjoint_electroatom_data,
        const Teuchos::ArrayRCP<const double>& energy_grid,
        const Teuchos::RCP<Utility::HashBasedGridSearcher>& grid_searcher,
        std::shared_ptr<AdjointElectroatomicReaction>& elastic_reaction,
        const double evaluation_tol )
{
  // Make sure the energy grid is valid
  testPrecondition( raw_adjoint_electroatom_data.getAdjointElectronEnergyGrid().size() ==
                    energy_grid.size() );
  testPrecondition( raw_adjoint_electroatom_data.getAdjointElectronEnergyGrid().back() >=
                    energy_grid[energy_grid.size()-1] );
  testPrecondition( Utility::Sort::isSortedAscending( energy_grid.begin(),
                                                      energy_grid.end() ) );

  // Create the analog elastic scattering distribution
  std::shared_ptr<const AnalogElasticElectronScatteringDistribution> distribution;

  ElasticElectronScatteringDistributionNativeFactory::createAnalogElasticDistribution<TwoDInterpPolicy>(
    distribution,
    raw_adjoint_electroatom_data,
    evaluation_tol );

  // Cutoff elastic cross section
  Teuchos::ArrayRCP<double> cutoff_cross_section;
  cutoff_cross_section.assign(
    raw_adjoint_electroatom_data.getAdjointCutoffElasticCrossSection().begin(),
    raw_adjoint_electroatom_data.getAdjointCutoffElasticCrossSection().end() );

  // Cutoff elastic cross section threshold energy bin index
  unsigned cutoff_threshold_energy_index =
    raw_adjoint_electroatom_data.getAdjointCutoffElasticCrossSectionThresholdEnergyIndex();

  // Screened Rutherford elastic cross section
  Teuchos::ArrayRCP<double> sr_cross_section;
  sr_cross_section.assign(
    raw_adjoint_electroatom_data.getAdjointScreenedRutherfordElasticCrossSection().begin(),
    raw_adjoint_electroatom_data.getAdjointScreenedRutherfordElasticCrossSection().end() );

  // Screened Rutherford elastic cross section threshold energy bin index
  unsigned sr_threshold_energy_index =
    raw_adjoint_electroatom_data.getAdjointScreenedRutherfordElasticCrossSectionThresholdEnergyIndex();

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
    new AnalogElasticAdjointElectroatomicReaction<Utility::LinLin>(
      energy_grid,
      analog_cross_section,
      analog_threshold_energy_index,
      grid_searcher,
      distribution ) );
}

// Create a hybrid elastic scattering adjoint electroatomic reaction
template< typename TwoDInterpPolicy>
void AdjointElectroatomicReactionNativeFactory::createHybridElasticReaction(
    const Data::AdjointElectronPhotonRelaxationDataContainer&
                raw_adjoint_electroatom_data,
    const Teuchos::ArrayRCP<const double>& energy_grid,
    const Teuchos::RCP<Utility::HashBasedGridSearcher>& grid_searcher,
    std::shared_ptr<AdjointElectroatomicReaction>& elastic_reaction,
    const double cutoff_angle_cosine,
    const double evaluation_tol )
{
  // Make sure the energy grid is valid
  testPrecondition( raw_adjoint_electroatom_data.getAdjointElectronEnergyGrid().size() ==
                    energy_grid.size() );
  testPrecondition( raw_adjoint_electroatom_data.getAdjointElectronEnergyGrid().back() >=
                    energy_grid[energy_grid.size()-1] );
  testPrecondition( Utility::Sort::isSortedAscending( energy_grid.begin(),
                                                      energy_grid.end() ) );

  // Cutoff elastic cross section
  Teuchos::ArrayRCP<double> cutoff_cross_section;
  cutoff_cross_section.assign(
    raw_adjoint_electroatom_data.getAdjointCutoffElasticCrossSection().begin(),
    raw_adjoint_electroatom_data.getAdjointCutoffElasticCrossSection().end() );

  // Cutoff elastic cross section threshold energy bin index
  unsigned cutoff_threshold_energy_index =
    raw_adjoint_electroatom_data.getAdjointCutoffElasticCrossSectionThresholdEnergyIndex();

  // Reduced cutoff elastic cross section ratio
  std::vector<double> reduced_cutoff_ratio =
    raw_adjoint_electroatom_data.getReducedCutoffCrossSectionRatios();

  // Moment preserving elastic cross section
  Teuchos::ArrayRCP<double> mp_cross_section;
  mp_cross_section.assign(
    raw_adjoint_electroatom_data.getAdjointMomentPreservingCrossSection().begin(),
    raw_adjoint_electroatom_data.getAdjointMomentPreservingCrossSection().end() );

  // Moment preserving elastic cross section threshold energy bin index
  unsigned mp_threshold_energy_index =
    raw_adjoint_electroatom_data.getAdjointMomentPreservingCrossSectionThresholdEnergyIndex();

  // Create the hybrid elastic scattering distribution
  std::shared_ptr<const HybridElasticElectronScatteringDistribution> distribution;

  ElasticElectronScatteringDistributionNativeFactory::createHybridElasticDistribution<TwoDInterpPolicy>(
    distribution,
    grid_searcher,
    energy_grid,
    cutoff_cross_section,
    mp_cross_section,
    raw_adjoint_electroatom_data,
    cutoff_angle_cosine,
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
    new HybridElasticAdjointElectroatomicReaction<TwoDInterpPolicy,Utility::LinLin>(
            energy_grid,
            hybrid_cross_section,
            hybrid_threshold_energy_index,
            grid_searcher,
            cutoff_angle_cosine,
            distribution ) );
}

// Create the cutoff elastic scattering adjoint electroatomic reactions
template<typename TwoDInterpPolicy>
void AdjointElectroatomicReactionNativeFactory::createCutoffElasticReaction(
        const Data::AdjointElectronPhotonRelaxationDataContainer&
            raw_adjoint_electroatom_data,
        const Teuchos::ArrayRCP<const double>& energy_grid,
        const Teuchos::RCP<Utility::HashBasedGridSearcher>& grid_searcher,
        std::shared_ptr<AdjointElectroatomicReaction>& elastic_reaction,
        const double cutoff_angle_cosine,
        const double evaluation_tol )
{
  // Make sure the energy grid is valid
  testPrecondition( raw_adjoint_electroatom_data.getAdjointElectronEnergyGrid().size() ==
                    energy_grid.size() );
  testPrecondition( raw_adjoint_electroatom_data.getAdjointElectronEnergyGrid().back() >=
                    energy_grid[energy_grid.size()-1] );
  testPrecondition( Utility::Sort::isSortedAscending( energy_grid.begin(),
                                                      energy_grid.end() ) );

  // Create the cutoff elastic scattering distribution
  std::shared_ptr<const CutoffElasticElectronScatteringDistribution> distribution;

  ElasticElectronScatteringDistributionNativeFactory::createCutoffElasticDistribution<TwoDInterpPolicy>(
    distribution,
    raw_adjoint_electroatom_data,
    cutoff_angle_cosine,
    evaluation_tol );

  // Cutoff elastic cross section
  Teuchos::ArrayRCP<double> elastic_cross_section;
  elastic_cross_section.assign(
    raw_adjoint_electroatom_data.getAdjointCutoffElasticCrossSection().begin(),
    raw_adjoint_electroatom_data.getAdjointCutoffElasticCrossSection().end() );

  // Cutoff elastic cross section threshold energy bin index
  unsigned threshold_energy_index =
    raw_adjoint_electroatom_data.getAdjointCutoffElasticCrossSectionThresholdEnergyIndex();

  elastic_reaction.reset(
    new CutoffElasticAdjointElectroatomicReaction<Utility::LinLin>(
                          energy_grid,
                          elastic_cross_section,
                          threshold_energy_index,
                          grid_searcher,
                          distribution ) );
}

// Create the screened Rutherford elastic scattering adjoint electroatomic reaction
template<typename TwoDInterpPolicy>
void AdjointElectroatomicReactionNativeFactory::createScreenedRutherfordElasticReaction(
        const Data::AdjointElectronPhotonRelaxationDataContainer&
            raw_adjoint_electroatom_data,
        const Teuchos::ArrayRCP<const double>& energy_grid,
        const Teuchos::RCP<Utility::HashBasedGridSearcher>& grid_searcher,
        std::shared_ptr<AdjointElectroatomicReaction>& elastic_reaction,
        const double cutoff_angle_cosine,
        const double evaluation_tol )
{
  // Make sure the energy grid is valid
  testPrecondition( raw_adjoint_electroatom_data.getAdjointElectronEnergyGrid().size() ==
                    energy_grid.size() );
  testPrecondition( raw_adjoint_electroatom_data.getAdjointElectronEnergyGrid().back() >=
                    energy_grid[energy_grid.size()-1] );
  testPrecondition( Utility::Sort::isSortedAscending( energy_grid.begin(),
                                                      energy_grid.end() ) );

  // Create the cutoff elastic scattering distribution
  std::shared_ptr<const CutoffElasticElectronScatteringDistribution>
    cutoff_distribution;

  ElasticElectronScatteringDistributionNativeFactory::createCutoffElasticDistribution<TwoDInterpPolicy>(
    cutoff_distribution,
    raw_adjoint_electroatom_data,
    cutoff_angle_cosine,
    evaluation_tol );


  // Create the screened Rutherford elastic scattering distribution
  std::shared_ptr<const ScreenedRutherfordElasticElectronScatteringDistribution>
    distribution;

  ElasticElectronScatteringDistributionNativeFactory::createScreenedRutherfordElasticDistribution(
    distribution,
    cutoff_distribution,
    raw_adjoint_electroatom_data.getAtomicNumber() );

  // Screened Rutherford elastic cross section
  Teuchos::ArrayRCP<double> elastic_cross_section;
  elastic_cross_section.assign(
    raw_adjoint_electroatom_data.getAdjointScreenedRutherfordElasticCrossSection().begin(),
    raw_adjoint_electroatom_data.getAdjointScreenedRutherfordElasticCrossSection().end() );

  // Screened Rutherford elastic cross section threshold energy bin index
  unsigned threshold_energy_index =
    raw_adjoint_electroatom_data.getAdjointScreenedRutherfordElasticCrossSectionThresholdEnergyIndex();


  elastic_reaction.reset(
    new ScreenedRutherfordElasticAdjointElectroatomicReaction<Utility::LinLin>(
                          energy_grid,
                          elastic_cross_section,
                          threshold_energy_index,
                          grid_searcher,
                          distribution ) );
}

// Create the moment preserving elastic scattering adjoint electroatomic reaction
template< typename TwoDInterpPolicy>
void AdjointElectroatomicReactionNativeFactory::createMomentPreservingElasticReaction(
        const Data::AdjointElectronPhotonRelaxationDataContainer&
            raw_adjoint_electroatom_data,
        const Teuchos::ArrayRCP<const double>& energy_grid,
        const Teuchos::RCP<Utility::HashBasedGridSearcher>& grid_searcher,
        std::shared_ptr<AdjointElectroatomicReaction>& elastic_reaction,
        const double cutoff_angle_cosine,
        const double evaluation_tol )
{
  // Make sure the energy grid is valid
  testPrecondition( raw_adjoint_electroatom_data.getAdjointElectronEnergyGrid().size() ==
                    energy_grid.size() );
  testPrecondition( raw_adjoint_electroatom_data.getAdjointElectronEnergyGrid().back() >=
                    energy_grid[energy_grid.size()-1] );
  testPrecondition( Utility::Sort::isSortedAscending( energy_grid.begin(),
                                                      energy_grid.end() ) );

  // Create the moment preserving elastic scattering distribution
  std::shared_ptr<const MomentPreservingElasticElectronScatteringDistribution>
    distribution;

  ElasticElectronScatteringDistributionNativeFactory::createMomentPreservingElasticDistribution<TwoDInterpPolicy>(
    distribution,
    raw_adjoint_electroatom_data,
    cutoff_angle_cosine,
    evaluation_tol );

  // Moment preserving elastic cross section
  Teuchos::ArrayRCP<double> elastic_cross_section;
  elastic_cross_section.assign(
    raw_adjoint_electroatom_data.getAdjointMomentPreservingCrossSection().begin(),
    raw_adjoint_electroatom_data.getAdjointMomentPreservingCrossSection().end() );

  // Moment preserving elastic cross section threshold energy bin index
  unsigned threshold_energy_index =
    raw_adjoint_electroatom_data.getAdjointMomentPreservingCrossSectionThresholdEnergyIndex();


  elastic_reaction.reset(
    new MomentPreservingElasticAdjointElectroatomicReaction<Utility::LinLin>(
                          energy_grid,
                          elastic_cross_section,
                          threshold_energy_index,
                          grid_searcher,
                          distribution ) );
}

// Create the subshell electroionization electroatomic reactions
template< typename TwoDInterpPolicy>
void AdjointElectroatomicReactionNativeFactory::createSubshellElectroionizationReaction(
    const Data::AdjointElectronPhotonRelaxationDataContainer& raw_adjoint_electroatom_data,
    const Teuchos::ArrayRCP<const double>& energy_grid,
    const Teuchos::RCP<Utility::HashBasedGridSearcher>& grid_searcher,
    const unsigned subshell,
    std::shared_ptr<AdjointElectroatomicReaction>& electroionization_subshell_reaction,
    const double evaluation_tol )
{
  // Convert subshell number to enum
  Data::SubshellType subshell_type =
    Data::convertENDFDesignatorToSubshellEnum( subshell );

  // Electroionization cross section
  Teuchos::ArrayRCP<double> subshell_cross_section;
  subshell_cross_section.assign(
      raw_adjoint_electroatom_data.getAdjointElectroionizationCrossSection( subshell ).begin(),
      raw_adjoint_electroatom_data.getAdjointElectroionizationCrossSection( subshell ).end() );

  // Electroionization cross section threshold energy bin index
  unsigned threshold_energy_index =
      raw_adjoint_electroatom_data.getAdjointElectroionizationCrossSectionThresholdEnergyIndex(
      subshell );

  // The electroionization subshell distribution
  std::shared_ptr<const ElectroionizationSubshellAdjointElectronScatteringDistribution>
      electroionization_subshell_distribution;

  // Create the electroionization subshell distribution
  ElectroionizationSubshellAdjointElectronScatteringDistributionNativeFactory::createAdjointElectroionizationSubshellDistribution(
      raw_adjoint_electroatom_data,
      subshell,
      raw_adjoint_electroatom_data.getSubshellBindingEnergy( subshell ),
      electroionization_subshell_distribution );


  // Create the subshell electroelectric reaction
  electroionization_subshell_reaction.reset(
      new ElectroionizationSubshellAdjointElectroatomicReaction<Utility::LinLin>(
              energy_grid,
              subshell_cross_section,
              threshold_energy_index,
              grid_searcher,
              subshell_type,
              electroionization_subshell_distribution ) );
}

// Create the subshell electroionization electroatomic reactions
template< typename TwoDInterpPolicy>
void AdjointElectroatomicReactionNativeFactory::createSubshellElectroionizationReactions(
           const Data::AdjointElectronPhotonRelaxationDataContainer& raw_adjoint_electroatom_data,
           const Teuchos::ArrayRCP<const double>& energy_grid,
           const Teuchos::RCP<Utility::HashBasedGridSearcher>& grid_searcher,
           std::vector<std::shared_ptr<AdjointElectroatomicReaction> >&
           electroionization_subshell_reactions,
           const double evaluation_tol )
{
  electroionization_subshell_reactions.clear();

  // Extract the subshell information
  std::set<unsigned> subshells = raw_adjoint_electroatom_data.getSubshells();

  std::shared_ptr<AdjointElectroatomicReaction> electroionization_subshell_reaction;

  std::set<unsigned>::iterator shell = subshells.begin();

  for( shell; shell != subshells.end(); ++shell )
  {
    AdjointElectroatomicReactionNativeFactory::createSubshellElectroionizationReaction<TwoDInterpPolicy>(
      raw_adjoint_electroatom_data,
      energy_grid,
      grid_searcher,
      *shell,
      electroionization_subshell_reaction,
      evaluation_tol );

    electroionization_subshell_reactions.push_back(
                      electroionization_subshell_reaction );
  }

  // Make sure the subshell electroelectric reactions have been created
  testPostcondition( electroionization_subshell_reactions.size() > 0 );
}

// Create a bremsstrahlung electroatomic reactions
template< typename TwoDInterpPolicy>
void AdjointElectroatomicReactionNativeFactory::createBremsstrahlungReaction(
        const Data::AdjointElectronPhotonRelaxationDataContainer& raw_adjoint_electroatom_data,
        const Teuchos::ArrayRCP<const double>& energy_grid,
        const Teuchos::RCP<Utility::HashBasedGridSearcher>& grid_searcher,
        std::shared_ptr<AdjointElectroatomicReaction>& bremsstrahlung_reaction,
        const double evaluation_tol )
{
  // Make sure the energy grid is valid
  testPrecondition( raw_adjoint_electroatom_data.getAdjointElectronEnergyGrid().size() ==
                    energy_grid.size() );
  testPrecondition( Utility::Sort::isSortedAscending( energy_grid.begin(),
                                                      energy_grid.end() ) );

  // Bremsstrahlung cross section
  Teuchos::ArrayRCP<double> bremsstrahlung_cross_section;
  bremsstrahlung_cross_section.assign(
   raw_adjoint_electroatom_data.getAdjointBremsstrahlungElectronCrossSection().begin(),
   raw_adjoint_electroatom_data.getAdjointBremsstrahlungElectronCrossSection().end() );

  // Index of first non zero cross section in the energy grid
  unsigned threshold_energy_index =
    raw_adjoint_electroatom_data.getAdjointBremsstrahlungElectronCrossSectionThresholdEnergyIndex();

  // Create bremsstrahlung scattering distribution
  std::shared_ptr<const BremsstrahlungAdjointElectronScatteringDistribution>
    bremsstrahlung_distribution;

  BremsstrahlungAdjointElectronScatteringDistributionNativeFactory::createBremsstrahlungAdjointDistribution(
      raw_adjoint_electroatom_data,
      raw_adjoint_electroatom_data.getAdjointElectronEnergyGrid(),
      bremsstrahlung_distribution );

  // Create the bremsstrahlung reaction
  bremsstrahlung_reaction.reset(
         new BremsstrahlungAdjointElectroatomicReaction<Utility::LinLin>(
                          energy_grid,
                          bremsstrahlung_cross_section,
                          threshold_energy_index,
                          grid_searcher,
                          bremsstrahlung_distribution ) );
}

} // end MontCarlo namespace

#endif // end MONTE_CARLO_ADJOINT_ELECTROATOMIC_REACTION_NATIVE_FACTORY_DEF_HPP
