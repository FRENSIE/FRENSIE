//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_BremsstrahlungElectronScatteringDistributionNativeFactory.cpp
//! \author Luke Kersting
//! \brief  The bremsstrahlung scattering distribution native factory definition
//!
//---------------------------------------------------------------------------//

// Trilinos Includes
#include <Teuchos_Array.hpp>
#include <Teuchos_ArrayView.hpp>

// FRENSIE Includes
#include "MonteCarlo_BremsstrahlungElectronScatteringDistributionNativeFactory.hpp"
#include "MonteCarlo_BremsstrahlungElectronScatteringDistribution.hpp"
#include "Utility_TabularDistribution.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Create a simple dipole bremsstrahlung distribution
void BremsstrahlungElectronScatteringDistributionNativeFactory::createBremsstrahlungDistribution(
	const Data::EvaluatedElectronDataContainer& raw_electroatom_data,
	Teuchos::RCP<const BremsstrahlungElectronScatteringDistribution>&
		scattering_distribution )
{
  // Get the energy grid for bremsstrahlung energy distributions
  std::vector<double> energy_grid = 
        raw_electroatom_data.getBremsstrahlungEnergyGrid();

  // Get size of the distribution
  int size = energy_grid.size();

  // Create the scattering function
  BremsstrahlungElectronScatteringDistribution::BremsstrahlungDistribution 
         scattering_function( size );

  BremsstrahlungElectronScatteringDistributionNativeFactory::createScatteringFunction( 
        raw_electroatom_data,
        energy_grid,
        scattering_function );

  scattering_distribution.reset( 
   new BremsstrahlungElectronScatteringDistribution( scattering_function ) );
}

// Create a detailed tabular bremsstrahlung distribution
void BremsstrahlungElectronScatteringDistributionNativeFactory::createBremsstrahlungDistribution(
	const Data::EvaluatedElectronDataContainer& raw_electroatom_data,
	Teuchos::RCP<const BremsstrahlungElectronScatteringDistribution>&
		scattering_distribution,
    Teuchos::RCP<Utility::OneDDistribution>& angular_distribution,
    const double lower_cutoff_energy,
    const double upper_cutoff_energy )
{
  // Get the energy grid for bremsstrahlung energy distributions
  std::vector<double> energy_grid = 
        raw_electroatom_data.getBremsstrahlungEnergyGrid();

  // Get size of the distribution
  int size = energy_grid.size();

  // Create the scattering function
  BremsstrahlungElectronScatteringDistribution::BremsstrahlungDistribution 
         scattering_function( size );

  BremsstrahlungElectronScatteringDistributionNativeFactory::createScatteringFunction( 
        raw_electroatom_data,
        energy_grid,
        scattering_function );

  scattering_distribution.reset( 
   new BremsstrahlungElectronScatteringDistribution( scattering_function,
                                                     angular_distribution,
                                                     lower_cutoff_energy,
                                                     upper_cutoff_energy  ) );
}

// Create a detailed 2BS bremsstrahlung distribution
void BremsstrahlungElectronScatteringDistributionNativeFactory::createBremsstrahlungDistribution(
	const Data::EvaluatedElectronDataContainer& raw_electroatom_data,
	Teuchos::RCP<const BremsstrahlungElectronScatteringDistribution>&
		scattering_distribution,
    const int atomic_number )
{
  // Get the energy grid for bremsstrahlung energy distributions
  std::vector<double> energy_grid = 
        raw_electroatom_data.getBremsstrahlungEnergyGrid();

  // Get size of the distribution
  int size = energy_grid.size();

  // Create the scattering function
  BremsstrahlungElectronScatteringDistribution::BremsstrahlungDistribution 
        scattering_function( size );

  BremsstrahlungElectronScatteringDistributionNativeFactory::createScatteringFunction( 
        raw_electroatom_data,
        energy_grid,
        scattering_function );

  scattering_distribution.reset( 
   new BremsstrahlungElectronScatteringDistribution( scattering_function,
                                                     atomic_number ) );
}

// Create the energy loss function
void BremsstrahlungElectronScatteringDistributionNativeFactory::createScatteringFunction(
	const Data::EvaluatedElectronDataContainer& raw_electroatom_data,
    const std::vector<double> energy_grid, 
    BremsstrahlungElectronScatteringDistribution::BremsstrahlungDistribution& 
        scattering_function )
{
  for( unsigned n = 0; n < energy_grid.size(); ++n )
  {
    scattering_function[n].first = energy_grid[n];

    // Get the energy of the bremsstrahlung photon at the incoming energy
    Teuchos::Array<double> photon_energy( 
        raw_electroatom_data.getBremsstrahlungPhotonEnergy( energy_grid[n] ) );

    // Get the bremsstrahlung photon pdf at the incoming energy
    Teuchos::Array<double> pdf( 
        raw_electroatom_data.getBremsstrahlungPhotonPDF( energy_grid[n] ) );

    scattering_function[n].second.reset( 
	  new const Utility::TabularDistribution<Utility::LinLin>( photon_energy, 
                                                               pdf ) );
  }
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_BremsstrahlungElectronScatteringDistributionNativeFactory.cpp
//---------------------------------------------------------------------------//

