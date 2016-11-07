//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_BremsstrahlungAdjointElectronScatteringDistributionNativeFactory.cpp
//! \author Luke Kersting
//! \brief  The bremsstrahlung adjoint scattering distribution native factory definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_BremsstrahlungAdjointElectronScatteringDistributionNativeFactory.hpp"
#include "Utility_TabularDistribution.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Create a bremsstrahlung adjoint distribution
void BremsstrahlungAdjointElectronScatteringDistributionNativeFactory::createBremsstrahlungAdjointDistribution(
	const Data::AdjointElectronPhotonRelaxationDataContainer& raw_electroatom_data,
    const std::vector<double>& adjoint_energy_grid,
	std::shared_ptr<const BremsstrahlungAdjointElectronScatteringDistribution>&
		scattering_distribution )
{
  // Create the scattering function
  std::shared_ptr<Utility::FullyTabularTwoDDistribution> energy_gain_function;

  BremsstrahlungAdjointElectronScatteringDistributionNativeFactory::createEnergyGainFunction(
        raw_electroatom_data,
        adjoint_energy_grid,
        energy_gain_function );

  scattering_distribution.reset(
   new BremsstrahlungAdjointElectronScatteringDistribution( energy_gain_function ) );
}

// Create the energy gain function
void BremsstrahlungAdjointElectronScatteringDistributionNativeFactory::createEnergyGainFunction(
	const Data::AdjointElectronPhotonRelaxationDataContainer& raw_electroatom_data,
    const std::vector<double> energy_grid,
    std::shared_ptr<Utility::FullyTabularTwoDDistribution>& energy_gain_function )
{
  // Get the function data
  Utility::FullyTabularTwoDDistribution::DistributionType
    function_data( energy_grid.size() );

  for( unsigned n = 0; n < energy_grid.size(); ++n )
  {
    function_data[n].first = energy_grid[n];

    // Get the outgoing energy of the adjoint bremsstrahlung electron at the incoming energy
    std::vector<double> outgoing_energy(
      raw_electroatom_data.getAdjointElectronBremsstrahlungEnergy( energy_grid[n] ) );

    // Get the adjoint bremsstrahlung pdf at the incoming energy
    std::vector<double> pdf(
      raw_electroatom_data.getAdjointElectronBremsstrahlungPDF( energy_grid[n] ) );

    function_data[n].second.reset(
	  new const Utility::TabularDistribution<Utility::LinLin>( outgoing_energy,
                                                               pdf ) );
  }

  // Create the scattering function
  energy_gain_function.reset(
    new Utility::InterpolatedFullyTabularTwoDDistribution<Utility::LinLinLog>(
            function_data ) );
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_BremsstrahlungAdjointElectronScatteringDistributionNativeFactory.cpp
//---------------------------------------------------------------------------//

