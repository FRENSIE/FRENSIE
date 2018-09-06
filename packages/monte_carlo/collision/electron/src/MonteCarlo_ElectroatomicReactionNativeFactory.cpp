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

// Create the screened Rutherford elastic scattering electroatomic reaction
void ElectroatomicReactionNativeFactory::createScreenedRutherfordElasticReaction(
            const Data::ElectronPhotonRelaxationDataContainer& raw_electroatom_data,
            const std::shared_ptr<const std::vector<double> >& energy_grid,
            const std::shared_ptr<const Utility::HashBasedGridSearcher<double>>& grid_searcher,
            std::shared_ptr<const ElectroatomicReaction>& elastic_reaction )
{
  // Make sure the energy grid is valid
  testPrecondition( raw_electroatom_data.getElectronEnergyGrid().size() ==
                    energy_grid->size() );
  testPrecondition( Utility::Sort::isSortedAscending( energy_grid->begin(),
                                                      energy_grid->end() ) );


  // Create the screened Rutherford elastic scattering distribution
  std::shared_ptr<const ScreenedRutherfordElasticElectronScatteringDistribution> distribution;
  ElasticFactory::createScreenedRutherfordElasticDistribution(
    distribution,
    raw_electroatom_data.getAtomicNumber() );

  // Screened Rutherford elastic cross section
  std::shared_ptr<std::vector<double> >
    elastic_cross_section( new std::vector<double> );
  elastic_cross_section->assign(
    raw_electroatom_data.getScreenedRutherfordElasticCrossSection().begin(),
    raw_electroatom_data.getScreenedRutherfordElasticCrossSection().end() );

  // Screened Rutherford elastic cross section threshold energy bin index
  size_t threshold_energy_index =
    raw_electroatom_data.getScreenedRutherfordElasticCrossSectionThresholdEnergyIndex();


  elastic_reaction.reset(
    new ScreenedRutherfordElasticElectroatomicReaction<Utility::LogLog>(
                          energy_grid,
                          elastic_cross_section,
                          threshold_energy_index,
                          grid_searcher,
                          distribution ) );
}

// Create an atomic excitation electroatomic reaction
void ElectroatomicReactionNativeFactory::createAtomicExcitationReaction(
            const Data::ElectronPhotonRelaxationDataContainer& raw_electroatom_data,
            const std::shared_ptr<const std::vector<double> >& energy_grid,
            const std::shared_ptr<const Utility::HashBasedGridSearcher<double>>& grid_searcher,
            std::shared_ptr<const ElectroatomicReaction>& atomic_excitation_reaction )
{
  // Make sure the energy grid is valid
  testPrecondition( raw_electroatom_data.getElectronEnergyGrid().size() ==
                    energy_grid->size() );
  testPrecondition( Utility::Sort::isSortedAscending( energy_grid->begin(),
                                                      energy_grid->end() ) );

  // Atomic Excitation cross section
  std::shared_ptr<std::vector<double> >
    atomic_excitation_cross_section( new std::vector<double> );
  atomic_excitation_cross_section->assign(
    raw_electroatom_data.getAtomicExcitationCrossSection().begin(),
    raw_electroatom_data.getAtomicExcitationCrossSection().end() );

  // Index of first non zero cross section in the energy grid
  size_t threshold_energy_index =
    raw_electroatom_data.getAtomicExcitationCrossSectionThresholdEnergyIndex();

  // Create the energy loss distribution
  std::shared_ptr<const AtomicExcitationElectronScatteringDistribution>
    energy_loss_distribution;

  ExcitationFactory::createAtomicExcitationDistribution(
                                                 raw_electroatom_data,
                                                 energy_loss_distribution );

  atomic_excitation_reaction.reset(
    new AtomicExcitationElectroatomicReaction<Utility::LogLog>(
                                                energy_grid,
                                                atomic_excitation_cross_section,
                                                threshold_energy_index,
                                                grid_searcher,
                                                energy_loss_distribution ) );
}

// Create a void absorption electroatomic reaction
void ElectroatomicReactionNativeFactory::createVoidAbsorptionReaction(
      std::shared_ptr<const ElectroatomicReaction>& void_absorption_reaction )
{
  // Create the void absorption reaction
  void_absorption_reaction.reset(
             new VoidAbsorptionElectroatomicReaction() );
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_ElectroatomicReactionNativeFactory.cpp
//---------------------------------------------------------------------------//
