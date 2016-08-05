//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_BremsstrahlungElectronScatteringDistributionNativeFactory.cpp
//! \author Luke Kersting
//! \brief  The bremsstrahlung scattering distribution native factory definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_BremsstrahlungElectronScatteringDistributionNativeFactory.hpp"
#include "MonteCarlo_BremsstrahlungElectronScatteringDistribution.hpp"
#include "Utility_TabularDistribution.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Create a simple dipole bremsstrahlung distribution
void BremsstrahlungElectronScatteringDistributionNativeFactory::createBremsstrahlungDistribution(
	const Data::ElectronPhotonRelaxationDataContainer& raw_electroatom_data,
	std::shared_ptr<const BremsstrahlungElectronScatteringDistribution>&
		scattering_distribution )
{
  // Get the energy grid for bremsstrahlung energy distributions
  std::vector<double> energy_grid =
        raw_electroatom_data.getBremsstrahlungEnergyGrid();

  // Create the scattering function
  BremsstrahlungElectronScatteringDistribution::BremsstrahlungDistribution
         energy_loss_function( energy_grid.size() );

  BremsstrahlungElectronScatteringDistributionNativeFactory::createEnergyLossFunction(
        raw_electroatom_data,
        energy_grid,
        energy_loss_function );

  scattering_distribution.reset(
   new BremsstrahlungElectronScatteringDistribution( energy_loss_function ) );
}

// Create a detailed 2BS bremsstrahlung distribution
void BremsstrahlungElectronScatteringDistributionNativeFactory::createBremsstrahlungDistribution(
	const Data::ElectronPhotonRelaxationDataContainer& raw_electroatom_data,
	std::shared_ptr<const BremsstrahlungElectronScatteringDistribution>&
		scattering_distribution,
    const int atomic_number )
{
  // Get the energy grid for bremsstrahlung energy distributions
  std::vector<double> energy_grid =
        raw_electroatom_data.getBremsstrahlungEnergyGrid();

  // Create the scattering function
  BremsstrahlungElectronScatteringDistribution::BremsstrahlungDistribution
        energy_loss_function( energy_grid.size() );

  BremsstrahlungElectronScatteringDistributionNativeFactory::createEnergyLossFunction(
        raw_electroatom_data,
        energy_grid,
        energy_loss_function );

  scattering_distribution.reset(
   new BremsstrahlungElectronScatteringDistribution( energy_loss_function,
                                                     atomic_number ) );
}

// Create the energy loss function
void BremsstrahlungElectronScatteringDistributionNativeFactory::createEnergyLossFunction(
	const Data::ElectronPhotonRelaxationDataContainer& raw_electroatom_data,
    const std::vector<double> energy_grid,
    BremsstrahlungElectronScatteringDistribution::BremsstrahlungDistribution&
        energy_loss_function )
{
  testPrecondition( energy_loss_function.size() == energy_grid.size() );

  for( unsigned n = 0; n < energy_grid.size(); ++n )
  {
    energy_loss_function[n].first = energy_grid[n];

    // Get the energy of the bremsstrahlung photon at the incoming energy
    std::vector<double> photon_energy(
        raw_electroatom_data.getBremsstrahlungPhotonEnergy( energy_grid[n] ) );

    // Get the bremsstrahlung photon pdf at the incoming energy
    std::vector<double> pdf(
        raw_electroatom_data.getBremsstrahlungPhotonPDF( energy_grid[n] ) );

    energy_loss_function[n].second.reset(
	  new const Utility::TabularDistribution<Utility::LinLin>( photon_energy,
                                                               pdf ) );
  }
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_BremsstrahlungElectronScatteringDistributionNativeFactory.cpp
//---------------------------------------------------------------------------//

