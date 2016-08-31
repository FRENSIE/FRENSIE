//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ElectroatomicReactionENDLFactory.cpp
//! \author Luke Kersting
//! \brief  The electroatomic reaction ENDL data factory definition
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <algorithm>

// FRENSIE Includes
#include "MonteCarlo_ElectroatomicReactionENDLFactory.hpp"
#include "MonteCarlo_BremsstrahlungElectronScatteringDistributionENDLFactory.hpp"
#include "MonteCarlo_ElectroionizationSubshellElectronScatteringDistributionENDLFactory.hpp"
#include "Data_SubshellType.hpp"
#include "Utility_TabularDistribution.hpp"
#include "Utility_SortAlgorithms.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Create the subshell electroionization electroatomic reaction
void ElectroatomicReactionENDLFactory::createSubshellElectroionizationReaction(
    const Data::ENDLDataContainer& raw_electroatom_data,
    const std::vector<double>& ionization_recoil_energy_grid,
    const unsigned shell,
    std::shared_ptr<ElectroionizationReaction>& electroionization_subshell_reaction )
{
  electroionization_subshell_reaction.reset();

  Data::SubshellType subshell_type;

  // Convert subshell number to enum
  subshell_type = Data::convertENDFDesignatorToSubshellEnum( shell );

  // Electroionization cross section energy grid
  Teuchos::ArrayRCP<double> energy_grid;
  energy_grid.assign(
	   raw_electroatom_data.getElectroionizationCrossSectionEnergyGrid( shell ).begin(),
	   raw_electroatom_data.getElectroionizationCrossSectionEnergyGrid( shell ).end() );

  // Create the hash-based grid searcher
  Teuchos::RCP<Utility::HashBasedGridSearcher> grid_searcher(
    new Utility::StandardHashBasedGridSearcher<Teuchos::ArrayRCP<const double>,false>(
      energy_grid,
      energy_grid[0],
      energy_grid[energy_grid.size()-1],
      energy_grid.size()/10 + 1 ) );

  // Electroionization cross section
  Teuchos::ArrayRCP<double> subshell_cross_section;
  subshell_cross_section.assign(
    raw_electroatom_data.getElectroionizationCrossSection( shell ).begin(),
    raw_electroatom_data.getElectroionizationCrossSection( shell ).end() );

  // The electroionization subshell distribution
  std::shared_ptr<const ElectroionizationSubshellElectronScatteringDistribution>
    electroionization_subshell_distribution;

  // Create the electroionization subshell distribution
  ElectroionizationSubshellElectronScatteringDistributionENDLFactory::createElectroionizationSubshellDistribution(
    raw_electroatom_data,
    ionization_recoil_energy_grid,
    shell,
    raw_electroatom_data.getSubshellBindingEnergy( shell ),
    electroionization_subshell_distribution );


  // Create the subshell electroelectric reaction
  electroionization_subshell_reaction.reset(
    new ElectroionizationReaction(
        energy_grid,
        subshell_cross_section,
        0,
        grid_searcher,
        subshell_type,
        electroionization_subshell_distribution ) );
}

// Create the subshell electroionization electroatomic reactions
void ElectroatomicReactionENDLFactory::createSubshellElectroionizationReactions(
    const Data::ENDLDataContainer& raw_electroatom_data,
    const std::map<unsigned, std::vector<double> >& ionization_recoil_energy_grids,
    std::vector<std::shared_ptr<ElectroionizationReaction> >&
    electroionization_subshell_reactions )
{
  electroionization_subshell_reactions.clear();

  // Extract the subshell information
  std::set<unsigned> subshells = raw_electroatom_data.getSubshells();

  std::shared_ptr<ElectroionizationReaction> electroionization_subshell_reaction;

  std::set<unsigned>::iterator shell = subshells.begin();

  for( shell; shell != subshells.end(); ++shell )
  {
    ElectroatomicReactionENDLFactory::createSubshellElectroionizationReaction(
            raw_electroatom_data,
            ionization_recoil_energy_grids.find( *shell )->second,
            *shell,
            electroionization_subshell_reaction );

    electroionization_subshell_reactions.push_back(
					  electroionization_subshell_reaction );
  }

  // Make sure the subshell electroelectric reactions have been created
  testPostcondition( electroionization_subshell_reactions.size() > 0 );
}

// Create a bremsstrahlung electroatomic reactions
void ElectroatomicReactionENDLFactory::createBremsstrahlungReaction(
	const Data::ENDLDataContainer& raw_electroatom_data,
  const std::vector<double>& bremsstrahlung_photon_energy_grid,
	std::shared_ptr<BremsstrahlungReaction>& bremsstrahlung_reaction,
	BremsstrahlungAngularDistributionType photon_distribution_function )
{
  // Bremsstrahlung cross section energy grid
  Teuchos::ArrayRCP<double> energy_grid;
  energy_grid.assign(
	   raw_electroatom_data.getBremsstrahlungCrossSectionEnergyGrid().begin(),
	   raw_electroatom_data.getBremsstrahlungCrossSectionEnergyGrid().end() );

  // Create the hash-based grid searcher
  Teuchos::RCP<Utility::HashBasedGridSearcher> grid_searcher(
    new Utility::StandardHashBasedGridSearcher<Teuchos::ArrayRCP<const double>,false>(
      energy_grid,
      energy_grid[0],
      energy_grid[energy_grid.size()-1],
      energy_grid.size()/10 + 1 ) );

  // Bremsstrahlung cross section
  Teuchos::ArrayRCP<double> bremsstrahlung_cross_section;
  bremsstrahlung_cross_section.assign(
	   raw_electroatom_data.getBremsstrahlungCrossSection().begin(),
	   raw_electroatom_data.getBremsstrahlungCrossSection().end() );

  // Create bremsstrahlung scattering distribution
  std::shared_ptr<const BremsstrahlungElectronScatteringDistribution>
    bremsstrahlung_distribution;

  if( photon_distribution_function = DIPOLE_DISTRIBUTION )
  {
    BremsstrahlungElectronScatteringDistributionENDLFactory::createBremsstrahlungDistribution(
      raw_electroatom_data,
      bremsstrahlung_photon_energy_grid,
      bremsstrahlung_distribution );

  }
  else if( photon_distribution_function = TABULAR_DISTRIBUTION )
  {
  THROW_EXCEPTION( std::logic_error,
          "Error! The detailed bremsstrahlung reaction has not been implemented");
  }
  else if( photon_distribution_function = TWOBS_DISTRIBUTION )
  {
    BremsstrahlungElectronScatteringDistributionENDLFactory::createBremsstrahlungDistribution(
      raw_electroatom_data,
      bremsstrahlung_photon_energy_grid,
      bremsstrahlung_distribution,
      raw_electroatom_data.getAtomicNumber() );
  }

  // Create the bremsstrahlung reaction
  bremsstrahlung_reaction.reset(
		     new BremsstrahlungReaction(
              energy_grid,
              bremsstrahlung_cross_section,
              0,
              grid_searcher,
              bremsstrahlung_distribution ) );
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_ElectroatomicReactionENDLFactory.cpp
//---------------------------------------------------------------------------//
