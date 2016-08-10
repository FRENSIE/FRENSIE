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
#include "MonteCarlo_BremsstrahlungElectroatomicReaction.hpp"
#include "MonteCarlo_BremsstrahlungElectronScatteringDistributionNativeFactory.hpp"
#include "Utility_TabularDistribution.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Create a bremsstrahlung electroatomic reactions
template< typename ReactionType>
void ElectroatomicReactionNativeFactory::createBremsstrahlungReaction(
		const Data::ElectronPhotonRelaxationDataContainer& raw_electroatom_data,
		const Teuchos::ArrayRCP<const double>& energy_grid,
        const Teuchos::RCP<Utility::HashBasedGridSearcher>& grid_searcher,
		std::shared_ptr<ReactionType>& bremsstrahlung_reaction,
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
  std::shared_ptr<const BremsstrahlungElectronScatteringDistribution>
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

} // end MontCarlo namespace

#endif // end MONTE_CARLO_ELECTROATOMIC_REACTION_NATIVE_FACTORY_DEF_HPP
