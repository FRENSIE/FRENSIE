//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_BremsstrahlungElectronScatteringDistributionNativeFactory_def.hpp
//! \author Luke Kersting
//! \brief  The bremsstrahlung scattering distribution native factory template definition
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_BREMSSTRAHLUNG_ELECTRON_SCATTERING_DISTRIBUTION_NATIVE_FACTORY_DEF_HPP
#define MONTE_CARLO_BREMSSTRAHLUNG_ELECTRON_SCATTERING_DISTRIBUTION_NATIVE_FACTORY_DEF_HPP

#include "Utility_TabularDistribution.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Create a simple dipole bremsstrahlung distribution
template <typename TwoDInterpPolicy>
void BremsstrahlungElectronScatteringDistributionNativeFactory::createBremsstrahlungDistribution(
    const Data::ElectronPhotonRelaxationDataContainer& raw_electroatom_data,
    const std::vector<double>& bremsstrahlung_energy_grid,
    std::shared_ptr<const BremsstrahlungElectronScatteringDistribution>&
        scattering_distribution )
{
  // Create the scattering function
  std::shared_ptr<Utility::FullyTabularTwoDDistribution> energy_loss_function;

  BremsstrahlungElectronScatteringDistributionNativeFactory::createEnergyLossFunction<TwoDInterpPolicy>(
        raw_electroatom_data,
        bremsstrahlung_energy_grid,
        energy_loss_function );

  scattering_distribution.reset(
   new BremsstrahlungElectronScatteringDistribution( energy_loss_function,
                                                     true ) );
}

// Create a simple dipole bremsstrahlung distribution
template <typename TwoDInterpPolicy>
void BremsstrahlungElectronScatteringDistributionNativeFactory::createBremsstrahlungDistribution(
    const Data::ElectronPhotonRelaxationDataContainer& raw_electroatom_data,
    std::shared_ptr<const BremsstrahlungElectronScatteringDistribution>&
        scattering_distribution )
{
  // Get the energy grid for bremsstrahlung energy distributions
  std::vector<double> bremsstrahlung_energy_grid =
        raw_electroatom_data.getBremsstrahlungEnergyGrid();

  BremsstrahlungElectronScatteringDistributionNativeFactory::createBremsstrahlungDistribution<TwoDInterpPolicy>(
    raw_electroatom_data,
    bremsstrahlung_energy_grid,
    scattering_distribution );
}

// Create a detailed 2BS bremsstrahlung distribution
template <typename TwoDInterpPolicy>
void BremsstrahlungElectronScatteringDistributionNativeFactory::createBremsstrahlungDistribution(
    const Data::ElectronPhotonRelaxationDataContainer& raw_electroatom_data,
    const std::vector<double>& bremsstrahlung_energy_grid,
    std::shared_ptr<const BremsstrahlungElectronScatteringDistribution>&
        scattering_distribution,
    const int atomic_number )
{
  // Create the scattering function
  std::shared_ptr<Utility::FullyTabularTwoDDistribution> energy_loss_function;

  BremsstrahlungElectronScatteringDistributionNativeFactory::createEnergyLossFunction<TwoDInterpPolicy>(
        raw_electroatom_data,
        bremsstrahlung_energy_grid,
        energy_loss_function );

  scattering_distribution.reset(
   new BremsstrahlungElectronScatteringDistribution( energy_loss_function,
                                                     atomic_number,
                                                     true ) );
}

// Create a detailed 2BS bremsstrahlung distribution
template <typename TwoDInterpPolicy>
void BremsstrahlungElectronScatteringDistributionNativeFactory::createBremsstrahlungDistribution(
    const Data::ElectronPhotonRelaxationDataContainer& raw_electroatom_data,
    std::shared_ptr<const BremsstrahlungElectronScatteringDistribution>&
        scattering_distribution,
    const int atomic_number )
{
  // Get the energy grid for bremsstrahlung energy distributions
  std::vector<double> bremsstrahlung_energy_grid =
        raw_electroatom_data.getBremsstrahlungEnergyGrid();

  BremsstrahlungElectronScatteringDistributionNativeFactory::createBremsstrahlungDistribution<TwoDInterpPolicy>(
    raw_electroatom_data,
    bremsstrahlung_energy_grid,
    scattering_distribution,
    atomic_number );
}

// Create the energy loss function
template <typename TwoDInterpPolicy>
void BremsstrahlungElectronScatteringDistributionNativeFactory::createEnergyLossFunction(
    const Data::ElectronPhotonRelaxationDataContainer& raw_electroatom_data,
    const std::vector<double> energy_grid,
    std::shared_ptr<Utility::FullyTabularTwoDDistribution>& energy_loss_function )
{
  // Get the function data
  Utility::FullyTabularTwoDDistribution::DistributionType
    function_data( energy_grid.size() );

  for( unsigned n = 0; n < energy_grid.size(); ++n )
  {
    function_data[n].first = energy_grid[n];

    // Get the energy of the bremsstrahlung photon at the incoming energy
    std::vector<double> photon_energy(
        raw_electroatom_data.getBremsstrahlungPhotonEnergy( energy_grid[n] ) );

    // Get the bremsstrahlung photon pdf at the incoming energy
    std::vector<double> pdf(
        raw_electroatom_data.getBremsstrahlungPhotonPDF( energy_grid[n] ) );

    function_data[n].second.reset(
      new const Utility::TabularDistribution<Utility::LinLin>( photon_energy,
                                                               pdf ) );
  }

  // Create the scattering function
  energy_loss_function.reset(
    new Utility::InterpolatedFullyTabularTwoDDistribution<TwoDInterpPolicy>(
            function_data ) );
}

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_BREMSSTRAHLUNG_ELECTRON_SCATTERING_DISTRIBUTION_NATIVE_FACTORY_DEF_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_BremsstrahlungElectronScatteringDistributionNativeFactory_def.hpp
//---------------------------------------------------------------------------//

