//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_AdjointElectroatomicReactionNativeFactory.cpp
//! \author Luke Kersting
//! \brief  The adjoint electroatomic reaction Native data factory definition
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <algorithm>

// FRENSIE Includes
#include "MonteCarlo_AdjointElectroatomicReactionNativeFactory.hpp"
#include "MonteCarlo_ScreenedRutherfordElasticAdjointElectroatomicReaction.hpp"
#include "MonteCarlo_AtomicExcitationAdjointElectroatomicReaction.hpp"
#include "MonteCarlo_AtomicExcitationAdjointElectronScatteringDistributionNativeFactory.hpp"
#include "MonteCarlo_AbsorptionElectroatomicReaction.hpp"

namespace MonteCarlo{

// Create the screened Rutherford elastic scattering adjoint electroatomic reaction
void AdjointElectroatomicReactionNativeFactory::createScreenedRutherfordElasticReaction(
        const Data::AdjointElectronPhotonRelaxationDataContainer&
            raw_adjoint_electroatom_data,
        const std::shared_ptr<const std::vector<double> >& energy_grid,
        const std::shared_ptr<const Utility::HashBasedGridSearcher>& grid_searcher,
        std::shared_ptr<const AdjointElectroatomicReaction>& elastic_reaction )
{
  // Make sure the energy grid is valid
  testPrecondition( raw_adjoint_electroatom_data.getAdjointElectronEnergyGrid().size() ==
                    energy_grid.size() );
  testPrecondition( raw_adjoint_electroatom_data.getAdjointElectronEnergyGrid().back() >=
                    energy_grid[energy_grid.size()-1] );
  testPrecondition( Utility::Sort::isSortedAscending( energy_grid.begin(),
                                                      energy_grid.end() ) );


  // Create the screened Rutherford elastic scattering distribution
  std::shared_ptr<const ScreenedRutherfordElasticElectronScatteringDistribution>
    distribution;

  ElasticFactory::createScreenedRutherfordElasticDistribution(
    distribution,
    raw_adjoint_electroatom_data.getAtomicNumber() );

  // Screened Rutherford elastic cross section
  std::shared_ptr<std::vector<double> >
    elastic_cross_section( new std::vector<double> );
  elastic_cross_section->assign(
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

// Create an atomic excitation adjoint electroatomic reaction
void AdjointElectroatomicReactionNativeFactory::createAtomicExcitationReaction(
            const Data::AdjointElectronPhotonRelaxationDataContainer&
                raw_adjoint_electroatom_data,
            const std::shared_ptr<const std::vector<double> >& energy_grid,
            const std::shared_ptr<const Utility::HashBasedGridSearcher>& grid_searcher,
            std::shared_ptr<const AdjointElectroatomicReaction>& atomic_excitation_reaction )
{
  // Make sure the energy grid is valid
  testPrecondition( raw_adjoint_electroatom_data.getAdjointElectronEnergyGrid().size() ==
                    energy_grid.size() );
  testPrecondition( Utility::Sort::isSortedAscending( energy_grid.begin(),
                                                      energy_grid.end() ) );

  // Atomic Excitation cross section
  std::shared_ptr<std::vector<double> >
    atomic_excitation_cross_section( new std::vector<double> );
  
  atomic_excitation_cross_section->assign(
    raw_adjoint_electroatom_data.getAdjointAtomicExcitationCrossSection().begin(),
    raw_adjoint_electroatom_data.getAdjointAtomicExcitationCrossSection().end() );

  // Index of first non zero cross section in the energy grid
  unsigned threshold_energy_index =
    raw_adjoint_electroatom_data.getAdjointAtomicExcitationCrossSectionThresholdEnergyIndex();

  // Create the energy loss distribution
  std::shared_ptr<const AtomicExcitationAdjointElectronScatteringDistribution>
    energy_loss_distribution;

  AtomicExcitationAdjointElectronScatteringDistributionNativeFactory::createAtomicExcitationDistribution(
                                                 raw_adjoint_electroatom_data,
                                                 energy_loss_distribution );

  atomic_excitation_reaction.reset(
    new AtomicExcitationAdjointElectroatomicReaction<Utility::LinLin>(
                                                energy_grid,
                                                atomic_excitation_cross_section,
                                                threshold_energy_index,
                                                grid_searcher,
                                                energy_loss_distribution ) );
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_AdjointElectroatomicReactionNativeFactory.cpp
//---------------------------------------------------------------------------//
