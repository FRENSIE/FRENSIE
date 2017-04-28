//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_BremsstrahlungElectronScatteringDistributionENDLFactory.cpp
//! \author Luke Kersting
//! \brief  The bremsstrahlung scattering distribution ENDL factory definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_BremsstrahlungElectronScatteringDistributionENDLFactory.hpp"
#include "MonteCarlo_BremsstrahlungElectronScatteringDistribution.hpp"
#include "Utility_TabularDistribution.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Create a simple dipole bremsstrahlung distribution
void BremsstrahlungElectronScatteringDistributionENDLFactory::createBremsstrahlungDistribution(
	const Data::ENDLDataContainer& raw_electroatom_data,
    const std::vector<double>& bremsstrahlung_energy_grid,
	std::shared_ptr<const BremsstrahlungElectronScatteringDistribution>&
		scattering_distribution )
{
  // Create the scattering function
  BremsstrahlungElectronScatteringDistribution::BremsstrahlungDistribution
         energy_loss_function( bremsstrahlung_energy_grid.size() );

  BremsstrahlungElectronScatteringDistributionENDLFactory::createEnergyLossFunction(
        raw_electroatom_data,
        bremsstrahlung_energy_grid,
        energy_loss_function );

  scattering_distribution.reset(
   new BremsstrahlungElectronScatteringDistribution( energy_loss_function ) );
}

// Create a detailed 2BS bremsstrahlung distribution
void BremsstrahlungElectronScatteringDistributionENDLFactory::createBremsstrahlungDistribution(
	const Data::ENDLDataContainer& raw_electroatom_data,
    const std::vector<double>& bremsstrahlung_energy_grid,
	std::shared_ptr<const BremsstrahlungElectronScatteringDistribution>&
		scattering_distribution,
    const int atomic_number )
{
  // Create the scattering function
  BremsstrahlungElectronScatteringDistribution::BremsstrahlungDistribution
        energy_loss_function( bremsstrahlung_energy_grid.size() );

  BremsstrahlungElectronScatteringDistributionENDLFactory::createEnergyLossFunction(
        raw_electroatom_data,
        bremsstrahlung_energy_grid,
        energy_loss_function );

  scattering_distribution.reset(
   new BremsstrahlungElectronScatteringDistribution( energy_loss_function,
                                                     atomic_number ) );
}

// Create the energy loss function
void BremsstrahlungElectronScatteringDistributionENDLFactory::createEnergyLossFunction(
	const Data::ENDLDataContainer& raw_electroatom_data,
    const std::vector<double>& bremsstrahlung_energy_grid,
    BremsstrahlungElectronScatteringDistribution::BremsstrahlungDistribution&
        energy_loss_function )
{
  testPrecondition( energy_loss_function.size() == bremsstrahlung_energy_grid.size() );

  for( unsigned n = 0; n < bremsstrahlung_energy_grid.size(); ++n )
  {
    Utility::get<0>( energy_loss_function[n] ) = bremsstrahlung_energy_grid[n];

    // Get the energy of the bremsstrahlung photon at the incoming energy
    std::vector<double> photon_energy(
        raw_electroatom_data.getBremsstrahlungPhotonEnergyAtEnergy(
            bremsstrahlung_energy_grid[n] ) );

    // Get the bremsstrahlung photon pdf at the incoming energy
    std::vector<double> pdf(
        raw_electroatom_data.getBremsstrahlungPhotonPDFAtEnergy(
            bremsstrahlung_energy_grid[n] ) );

    Utility::get<1>( energy_loss_function[n] ).reset(
	  new const Utility::TabularDistribution<Utility::LinLin>( photon_energy,
                                                               pdf ) );
  }
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_BremsstrahlungElectronScatteringDistributionENDLFactory.cpp
//---------------------------------------------------------------------------//

