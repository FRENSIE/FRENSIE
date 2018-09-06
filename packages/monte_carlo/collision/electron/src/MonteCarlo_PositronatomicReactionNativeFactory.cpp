//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_PositronatomicReactionNativeFactory.cpp
//! \author Luke Kersting
//! \brief  The positron-atomic reaction Native data factory definition
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <algorithm>

// FRENSIE Includes
#include "MonteCarlo_PositronatomicReactionNativeFactory.hpp"
#include "MonteCarlo_VoidAbsorptionPositronatomicReaction.hpp"

namespace MonteCarlo{

// Create the screened Rutherford elastic scattering positron-atomic reaction
void PositronatomicReactionNativeFactory::createScreenedRutherfordElasticReaction(
      const Data::ElectronPhotonRelaxationDataContainer& raw_positronatom_data,
      const std::shared_ptr<const std::vector<double> >& energy_grid,
      const std::shared_ptr<const Utility::HashBasedGridSearcher<double>>& grid_searcher,
      std::shared_ptr<const PositronatomicReaction>& elastic_reaction )
{
  // Make sure the energy grid is valid
  testPrecondition( raw_positronatom_data.getElectronEnergyGrid().size() ==
                    energy_grid->size() );
  testPrecondition( Utility::Sort::isSortedAscending( energy_grid->begin(),
                                                      energy_grid->end() ) );


  // Create the screened Rutherford elastic scattering distribution
  std::shared_ptr<const ScreenedRutherfordElasticElectronScatteringDistribution> distribution;
  ElasticFactory::createScreenedRutherfordElasticDistribution(
    distribution,
    raw_positronatom_data.getAtomicNumber() );

  // Screened Rutherford elastic cross section
  std::shared_ptr<const std::vector<double> > elastic_cross_section(
     new std::vector<double>( raw_positronatom_data.getScreenedRutherfordElasticCrossSection().begin(),
                              raw_positronatom_data.getScreenedRutherfordElasticCrossSection().end() ) );

  // Screened Rutherford elastic cross section threshold energy bin index
  size_t threshold_energy_index =
    raw_positronatom_data.getScreenedRutherfordElasticCrossSectionThresholdEnergyIndex();


  elastic_reaction.reset(
    new ScreenedRutherfordElasticPositronatomicReaction<Utility::LogLog>(
                          energy_grid,
                          elastic_cross_section,
                          threshold_energy_index,
                          grid_searcher,
                          distribution ) );
}

// Create an atomic excitation positron-atomic reaction
void PositronatomicReactionNativeFactory::createAtomicExcitationReaction(
    const Data::ElectronPhotonRelaxationDataContainer& raw_positronatom_data,
    const std::shared_ptr<const std::vector<double> >& energy_grid,
    const std::shared_ptr<const Utility::HashBasedGridSearcher<double>>& grid_searcher,
    std::shared_ptr<const PositronatomicReaction>& atomic_excitation_reaction )
{
  // Make sure the energy grid is valid
  testPrecondition( raw_positronatom_data.getElectronEnergyGrid().size() ==
                    energy_grid->size() );
  testPrecondition( Utility::Sort::isSortedAscending( energy_grid->begin(),
                                                      energy_grid->end() ) );

  // Atomic Excitation cross section
  std::shared_ptr<const std::vector<double> > atomic_excitation_cross_section(
     new std::vector<double>( raw_positronatom_data.getAtomicExcitationCrossSection().begin(),
                              raw_positronatom_data.getAtomicExcitationCrossSection().end() ) );

  // Index of first non zero cross section in the energy grid
  size_t threshold_energy_index =
    raw_positronatom_data.getAtomicExcitationCrossSectionThresholdEnergyIndex();

  // Create the energy loss distribution
  std::shared_ptr<const AtomicExcitationElectronScatteringDistribution>
    energy_loss_distribution;

  ExcitationFactory::createAtomicExcitationDistribution(
                                                 raw_positronatom_data,
                                                 energy_loss_distribution );

  atomic_excitation_reaction.reset(
    new AtomicExcitationPositronatomicReaction<Utility::LogLog>(
                                                energy_grid,
                                                atomic_excitation_cross_section,
                                                threshold_energy_index,
                                                grid_searcher,
                                                energy_loss_distribution ) );
}

// Create a void absorption positron-atomic reaction
void PositronatomicReactionNativeFactory::createVoidAbsorptionReaction(
      std::shared_ptr<const PositronatomicReaction>& void_absorption_reaction )
{
  // Create the void absorption reaction
  void_absorption_reaction.reset(
             new VoidAbsorptionPositronatomicReaction() );
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_PositronatomicReactionNativeFactory.cpp
//---------------------------------------------------------------------------//
