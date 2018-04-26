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
template<typename TwoDInterpPolicy, template<typename> class TwoDGridPolicy>
void BremsstrahlungElectronScatteringDistributionNativeFactory::createBremsstrahlungDistribution(
    const Data::ElectronPhotonRelaxationDataContainer& raw_electroatom_data,
    const std::vector<double>& bremsstrahlung_energy_grid,
    std::shared_ptr<const BremsstrahlungElectronScatteringDistribution>&
        scattering_distribution,
    const double evaluation_tol )
{
  // Make sure the evaluation tol is valid
  testPrecondition( evaluation_tol > 0.0 );

  // Create the scattering function
  std::shared_ptr<const Utility::FullyTabularBasicBivariateDistribution>
    energy_loss_function;

  ThisType::createEnergyLossFunction<TwoDInterpPolicy,TwoDGridPolicy>(
        raw_electroatom_data,
        bremsstrahlung_energy_grid,
        energy_loss_function,
        evaluation_tol );

  scattering_distribution.reset(
   new BremsstrahlungElectronScatteringDistribution( energy_loss_function ) );
}

// Create a simple dipole bremsstrahlung distribution
template<typename TwoDInterpPolicy, template<typename> class TwoDGridPolicy>
void BremsstrahlungElectronScatteringDistributionNativeFactory::createBremsstrahlungDistribution(
    const Data::ElectronPhotonRelaxationDataContainer& raw_electroatom_data,
    std::shared_ptr<const BremsstrahlungElectronScatteringDistribution>&
        scattering_distribution,
    const double evaluation_tol )
{
  // Make sure the evaluation tol is valid
  testPrecondition( evaluation_tol > 0.0 );

  // Get the energy grid for bremsstrahlung energy distributions
  std::vector<double> bremsstrahlung_energy_grid =
        raw_electroatom_data.getBremsstrahlungEnergyGrid();

  ThisType::createBremsstrahlungDistribution<TwoDInterpPolicy,TwoDGridPolicy>(
    raw_electroatom_data,
    bremsstrahlung_energy_grid,
    scattering_distribution,
    evaluation_tol );
}

// Create a detailed 2BS bremsstrahlung distribution
template <typename TwoDInterpPolicy, template<typename> class TwoDGridPolicy>
void BremsstrahlungElectronScatteringDistributionNativeFactory::createBremsstrahlungDistribution(
    const Data::ElectronPhotonRelaxationDataContainer& raw_electroatom_data,
    const int atomic_number,
    const std::vector<double>& bremsstrahlung_energy_grid,
    std::shared_ptr<const BremsstrahlungElectronScatteringDistribution>&
        scattering_distribution,
    const double evaluation_tol )
{
  // Make sure the evaluation tol is valid
  testPrecondition( evaluation_tol > 0.0 );

  // Create the scattering function
  std::shared_ptr<const Utility::FullyTabularBasicBivariateDistribution> energy_loss_function;

  ThisType::createEnergyLossFunction<TwoDInterpPolicy,TwoDGridPolicy>(
        raw_electroatom_data,
        bremsstrahlung_energy_grid,
        energy_loss_function,
        evaluation_tol );

  scattering_distribution.reset(
   new BremsstrahlungElectronScatteringDistribution( atomic_number,
                                                     energy_loss_function ) );
}

// Create a detailed 2BS bremsstrahlung distribution
template <typename TwoDInterpPolicy, template<typename> class TwoDGridPolicy>
void BremsstrahlungElectronScatteringDistributionNativeFactory::createBremsstrahlungDistribution(
    const Data::ElectronPhotonRelaxationDataContainer& raw_electroatom_data,
    const int atomic_number,
    std::shared_ptr<const BremsstrahlungElectronScatteringDistribution>&
        scattering_distribution,
    const double evaluation_tol )
{
  // Make sure the evaluation tol is valid
  testPrecondition( evaluation_tol > 0.0 );


  ThisType::createBremsstrahlungDistribution<TwoDInterpPolicy,TwoDGridPolicy>(
    raw_electroatom_data,
    atomic_number,
    raw_electroatom_data.getBremsstrahlungEnergyGrid(),
    scattering_distribution,
    evaluation_tol );
}

// Create the energy loss function
template<typename TwoDInterpPolicy, template<typename> class TwoDGridPolicy>
void BremsstrahlungElectronScatteringDistributionNativeFactory::createEnergyLossFunction(
    const Data::ElectronPhotonRelaxationDataContainer& raw_electroatom_data,
    const std::vector<double> energy_grid,
    std::shared_ptr<const Utility::FullyTabularBasicBivariateDistribution>& energy_loss_function,
    const double evaluation_tol )
{
  // Make sure the evaluation tol is valid
  testPrecondition( evaluation_tol > 0.0 );

  // Get the function data
  std::vector<double> primary_grid( energy_grid.size() );
  std::vector<std::shared_ptr<const Utility::TabularUnivariateDistribution> >
    secondary_dists( energy_grid.size() );

  for( size_t n = 0; n < energy_grid.size(); ++n )
  {
    primary_grid[n] = energy_grid[n];

    // Get the energy of the bremsstrahlung photon at the incoming energy
    std::vector<double> photon_energy(
        raw_electroatom_data.getBremsstrahlungPhotonEnergy( energy_grid[n] ) );

    // Get the bremsstrahlung photon pdf at the incoming energy
    std::vector<double> pdf(
        raw_electroatom_data.getBremsstrahlungPhotonPDF( energy_grid[n] ) );

    secondary_dists[n].reset(
      new const Utility::TabularDistribution<Utility::LinLin>( photon_energy,
                                                               pdf ) );
  }

  // Create the scattering function
  energy_loss_function.reset(
    new Utility::InterpolatedFullyTabularBasicBivariateDistribution<TwoDGridPolicy<TwoDInterpPolicy> >(
            primary_grid,
            secondary_dists,
            1e-6,
            evaluation_tol ) );
}

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_BREMSSTRAHLUNG_ELECTRON_SCATTERING_DISTRIBUTION_NATIVE_FACTORY_DEF_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_BremsstrahlungElectronScatteringDistributionNativeFactory_def.hpp
//---------------------------------------------------------------------------//
