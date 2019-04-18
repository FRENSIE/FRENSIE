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
#include "Utility_DesignByContract.hpp"

namespace MonteCarlo{

// Create a simple dipole bremsstrahlung distribution
template<typename TwoDInterpPolicy, template<typename> class TwoDGridPolicy>
void BremsstrahlungElectronScatteringDistributionNativeFactory::createBremsstrahlungDistribution(
    const Data::ElectronPhotonRelaxationDataContainer& raw_electroatom_data,
    std::shared_ptr<const BremsstrahlungElectronScatteringDistribution>&
        scattering_distribution,
    const double evaluation_tol,
    const unsigned max_number_of_iterations )
{
  // Make sure the evaluation tol is valid
  testPrecondition( evaluation_tol > 0.0 );
  // Make sure the max number of iterations is valid
  testPrecondition( max_number_of_iterations > 1 );

  ThisType::createBremsstrahlungDistribution<TwoDInterpPolicy,TwoDGridPolicy>(
    raw_electroatom_data.getBremsstrahlungPhotonEnergy(),
    raw_electroatom_data.getBremsstrahlungPhotonPDF(),
    raw_electroatom_data.getBremsstrahlungEnergyGrid(),
    scattering_distribution,
    evaluation_tol,
    max_number_of_iterations );
}

// Create a simple dipole bremsstrahlung distribution
template<typename TwoDInterpPolicy, template<typename> class TwoDGridPolicy>
void BremsstrahlungElectronScatteringDistributionNativeFactory::createBremsstrahlungDistribution(
    const std::map<double,std::vector<double> >& photon_energy_data,
    const std::map<double,std::vector<double> >& photon_pdf_data,
    const std::vector<double>& energy_grid,
    std::shared_ptr<const BremsstrahlungElectronScatteringDistribution>&
        scattering_distribution,
    const double evaluation_tol,
    const unsigned max_number_of_iterations )
{
  // Make sure the evaluation tol is valid
  testPrecondition( evaluation_tol > 0.0 );
  // Make sure the max number of iterations is valid
  testPrecondition( max_number_of_iterations > 1 );

  // Create the scattering function
  std::shared_ptr<const Utility::FullyTabularBasicBivariateDistribution>
    energy_loss_function;

  ThisType::createEnergyLossFunction<TwoDInterpPolicy,TwoDGridPolicy>(
    photon_energy_data,
    photon_pdf_data,
    energy_grid,
    energy_loss_function,
    evaluation_tol,
    max_number_of_iterations );

  scattering_distribution.reset(
   new BremsstrahlungElectronScatteringDistribution( energy_loss_function ) );
}

// Create a detailed 2BS bremsstrahlung distribution
template <typename TwoDInterpPolicy, template<typename> class TwoDGridPolicy>
void BremsstrahlungElectronScatteringDistributionNativeFactory::createBremsstrahlungDistribution(
    const Data::ElectronPhotonRelaxationDataContainer& raw_electroatom_data,
    const int atomic_number,
    std::shared_ptr<const BremsstrahlungElectronScatteringDistribution>&
        scattering_distribution,
    const double evaluation_tol,
    const unsigned max_number_of_iterations )
{
  // Make sure the evaluation tol is valid
  testPrecondition( evaluation_tol > 0.0 );
  // Make sure the max number of iterations is valid
  testPrecondition( max_number_of_iterations > 1 );

  ThisType::createBremsstrahlungDistribution<TwoDInterpPolicy,TwoDGridPolicy>(
    raw_electroatom_data.getBremsstrahlungPhotonEnergy(),
    raw_electroatom_data.getBremsstrahlungPhotonPDF(),
    raw_electroatom_data.getBremsstrahlungEnergyGrid(),
    atomic_number,
    scattering_distribution,
    evaluation_tol,
    max_number_of_iterations );
}

// Create a detailed 2BS bremsstrahlung distribution
template <typename TwoDInterpPolicy, template<typename> class TwoDGridPolicy>
void BremsstrahlungElectronScatteringDistributionNativeFactory::createBremsstrahlungDistribution(
    const std::map<double,std::vector<double> >& photon_energy_data,
    const std::map<double,std::vector<double> >& photon_pdf_data,
    const std::vector<double>& energy_grid,
    const int atomic_number,
    std::shared_ptr<const BremsstrahlungElectronScatteringDistribution>&
        scattering_distribution,
    const double evaluation_tol,
    const unsigned max_number_of_iterations )
{
  // Make sure the evaluation tol is valid
  testPrecondition( evaluation_tol > 0.0 );
  // Make sure the max number of iterations is valid
  testPrecondition( max_number_of_iterations > 1 );

  // Create the scattering function
  std::shared_ptr<const Utility::FullyTabularBasicBivariateDistribution>
    energy_loss_function;

  ThisType::createEnergyLossFunction<TwoDInterpPolicy,TwoDGridPolicy>(
    photon_energy_data,
    photon_pdf_data,
    energy_grid,
    energy_loss_function,
    evaluation_tol,
    max_number_of_iterations );

  scattering_distribution.reset(
   new BremsstrahlungElectronScatteringDistribution( atomic_number,
                                                     energy_loss_function ) );
}

// Create the energy loss function
template<typename TwoDInterpPolicy, template<typename> class TwoDGridPolicy>
void BremsstrahlungElectronScatteringDistributionNativeFactory::createEnergyLossFunction(
    const std::map<double,std::vector<double> >& photon_energy_data,
    const std::map<double,std::vector<double> >& photon_pdf_data,
    const std::vector<double>& energy_grid,
    std::shared_ptr<const Utility::FullyTabularBasicBivariateDistribution>& energy_loss_function,
    const double evaluation_tol,
    const unsigned max_number_of_iterations )
{
  // Make sure the evaluation tol is valid
  testPrecondition( evaluation_tol > 0.0 );
  // Make sure the max number of iterations is valid
  testPrecondition( max_number_of_iterations > 1 );

  // Get the function data
  std::vector<std::shared_ptr<const Utility::TabularUnivariateDistribution> >
    secondary_dists( energy_grid.size() );

  for( size_t n = 0; n < energy_grid.size(); ++n )
  {
    secondary_dists[n] =
      std::make_shared<const Utility::TabularDistribution<Utility::LinLin> >(
        photon_energy_data.find( energy_grid[n] )->second,
        photon_pdf_data.find( energy_grid[n] )->second );
  }

  // Create the scattering function
  energy_loss_function.reset(
    new Utility::InterpolatedFullyTabularBasicBivariateDistribution<TwoDGridPolicy<TwoDInterpPolicy> >(
            energy_grid,
            secondary_dists,
            1e-6,
            evaluation_tol,
            1e-16,
            max_number_of_iterations ) );
}

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_BREMSSTRAHLUNG_ELECTRON_SCATTERING_DISTRIBUTION_NATIVE_FACTORY_DEF_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_BremsstrahlungElectronScatteringDistributionNativeFactory_def.hpp
//---------------------------------------------------------------------------//
