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
        const std::shared_ptr<const Utility::HashBasedGridSearcher<double>>& grid_searcher,
        std::shared_ptr<const AdjointElectroatomicReaction>& elastic_reaction )
{
  // Make sure the energy grid is valid
  testPrecondition( raw_adjoint_electroatom_data.getAdjointElectronEnergyGrid().size() ==
                    energy_grid->size() );
  testPrecondition( raw_adjoint_electroatom_data.getAdjointElectronEnergyGrid().back() >=
                    energy_grid->back() );
  testPrecondition( Utility::Sort::isSortedAscending( energy_grid->begin(),
                                                      energy_grid->end() ) );

  // Create the screened Rutherford elastic scattering distribution
  std::shared_ptr<const ScreenedRutherfordElasticElectronScatteringDistribution>
    distribution;

  ElasticFactory::createScreenedRutherfordElasticDistribution(
    distribution,
    raw_adjoint_electroatom_data.getAtomicNumber() );

  // Screened Rutherford elastic cross section
  auto elastic_cross_section= std::make_shared<std::vector<double> >(
    raw_adjoint_electroatom_data.getAdjointScreenedRutherfordElasticCrossSection() );

  // Screened Rutherford elastic cross section threshold energy bin index
  size_t threshold_energy_index =
    raw_adjoint_electroatom_data.getAdjointScreenedRutherfordElasticCrossSectionThresholdEnergyIndex();


  elastic_reaction.reset(
    new ScreenedRutherfordElasticAdjointElectroatomicReaction<Utility::LogLog>(
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
      const std::shared_ptr<const Utility::HashBasedGridSearcher<double>>& grid_searcher,
      std::shared_ptr<const AdjointElectroatomicReaction>& atomic_excitation_reaction,
      const std::shared_ptr<const std::vector<double> >& critical_line_energies )
{
  // Make sure the energy grid is valid
  testPrecondition( raw_adjoint_electroatom_data.getAdjointElectronEnergyGrid().size() ==
                    energy_grid->size() );
  testPrecondition( Utility::Sort::isSortedAscending( energy_grid->begin(),
                                                      energy_grid->end() ) );

  // Atomic Excitation cross section
  auto atomic_excitation_cross_section = std::make_shared<std::vector<double> >(
    raw_adjoint_electroatom_data.getAdjointAtomicExcitationCrossSection() );

  // Index of first non zero cross section in the energy grid
  size_t threshold_energy_index =
    raw_adjoint_electroatom_data.getAdjointAtomicExcitationCrossSectionThresholdEnergyIndex();

  // Create the energy gain distribution
  std::shared_ptr<AtomicExcitationAdjointElectronScatteringDistribution>
    energy_gain_distribution;

  AtomicExcitationAdjointElectronScatteringDistributionNativeFactory::createAtomicExcitationDistribution(
                                                 raw_adjoint_electroatom_data,
                                                 energy_gain_distribution );

  // Assign the critical line energies
  if( critical_line_energies->size() > 0 )
  {
    energy_gain_distribution->setCriticalLineEnergies( critical_line_energies );
  }

  atomic_excitation_reaction.reset(
    new AtomicExcitationAdjointElectroatomicReaction<Utility::LogLog>(
                                                energy_grid,
                                                atomic_excitation_cross_section,
                                                threshold_energy_index,
                                                grid_searcher,
                                                energy_gain_distribution ) );
}

// Create the forward total reaction (only used to get the cross section)
void AdjointElectroatomicReactionNativeFactory::createTotalForwardReaction(
      const std::vector<std::vector<double> >& forward_inelastic_cross_section,
      const std::shared_ptr<const std::vector<double> >& energy_grid,
      const std::shared_ptr<const Utility::HashBasedGridSearcher<double>>& grid_searcher,
      const std::function<double (const double&)> forward_elastic_xs_evaluator,
      std::shared_ptr<const ElectroatomicReaction>& total_forward_reaction )
{
  // Add the inelastic and elastic cross section together
  auto total_forward_cross_section = std::make_shared<std::vector<double> >(
    energy_grid->size() );

  for( size_t i = 0; i < energy_grid->size(); ++i )
  {
    // Add the elastic cross section
    (*total_forward_cross_section)[i] =
      forward_elastic_xs_evaluator( (*energy_grid)[i] );

    // Add the inelastic cross section
    for (size_t j = 0; j < forward_inelastic_cross_section.size(); ++j )
    {
      (*total_forward_cross_section)[i] +=
        forward_inelastic_cross_section[j].at(i);
    }

  }

  // Create the total forward reaction
  total_forward_reaction.reset(
     new AbsorptionElectroatomicReaction<Utility::LogLog,false>(
                                               energy_grid,
                                               total_forward_cross_section,
                                               0u,
                                               grid_searcher,
                                               TOTAL_ELECTROATOMIC_REACTION ) );
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_AdjointElectroatomicReactionNativeFactory.cpp
//---------------------------------------------------------------------------//
