//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ElectroionizationSubshellElectronScatteringDistributionNativeFactory.cpp
//! \author Luke Kersting
//! \brief  The electroionization subshell scattering distribution Native factory definition
//!
//---------------------------------------------------------------------------//

// Trilinos Includes
#include <Teuchos_ArrayView.hpp>

// FRENSIE Includes
#include "MonteCarlo_ElectroionizationSubshellElectronScatteringDistributionNativeFactory.hpp"
#include "Utility_TabularDistribution.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Create a electroionization subshell distribution
void ElectroionizationSubshellElectronScatteringDistributionNativeFactory::createElectroionizationSubshellDistribution(
	const Data::ElectronPhotonRelaxationDataContainer& raw_electroionization_data,
    const unsigned subshell,
    const double binding_energy,
	std::shared_ptr<const ElectroionizationSubshellElectronScatteringDistribution>&
	  electroionization_subshell_distribution )
{
  // Get the energies for which knock-on sampling tables are given
  std::vector<double> energy_grid =
        raw_electroionization_data.getElectroionizationEnergyGrid( subshell );

  // Subshell distribution
  ElectroionizationSubshellElectronScatteringDistribution::ElectroionizationSubshellDistribution
        subshell_distribution( energy_grid.size() );

  // Create the subshell distribution
  createSubshellDistribution( raw_electroionization_data,
                              energy_grid,
                              subshell,
	                          subshell_distribution );

  electroionization_subshell_distribution.reset(
    new ElectroionizationSubshellElectronScatteringDistribution(
            subshell_distribution,
            binding_energy ) );
}

// Create the subshell recoil distribution
void ElectroionizationSubshellElectronScatteringDistributionNativeFactory::createSubshellDistribution(
	const Data::ElectronPhotonRelaxationDataContainer& raw_electroionization_data,
    const std::vector<double> energy_grid,
    const unsigned subshell,
    ElectroionizationSubshellElectronScatteringDistribution::ElectroionizationSubshellDistribution&
	 subshell_distribution )
{
  for( unsigned n = 0; n < energy_grid.size(); ++n )
  {
    subshell_distribution[n].first = energy_grid[n];

    // Get the recoil energy distribution at the incoming energy
    Teuchos::Array<double> recoil_energy(
        raw_electroionization_data.getElectroionizationRecoilEnergy(
            subshell,
            energy_grid[n] ) );

    // Get the recoil energy pdf at the incoming energy
    Teuchos::Array<double> pdf(
        raw_electroionization_data.getElectroionizationRecoilPDF(
            subshell,
            energy_grid[n] ) );

    subshell_distribution[n].second.reset(
	  new const Utility::TabularDistribution<Utility::LinLin>( recoil_energy,
                                                               pdf ) );
  }
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_ElectroionizationSubshellScatteringDistributionNativeFactory.cpp
//---------------------------------------------------------------------------//

