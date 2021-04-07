//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_BremsstrahlungAdjointElectronScatteringDistributionNativeFactory_def.hpp
//! \author Luke Kersting
//! \brief  The bremsstrahlung adjoint scattering distribution native factory definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "Utility_TabularDistribution.hpp"
#include "Utility_DesignByContract.hpp"

namespace MonteCarlo{

// Create a bremsstrahlung adjoint distribution
template<typename TwoDInterpPolicy, template<typename> class TwoDGridPolicy>
void BremsstrahlungAdjointElectronScatteringDistributionNativeFactory::createBremsstrahlungDistribution(
    const Data::AdjointElectronPhotonRelaxationDataContainer& raw_electroatom_data,
    const std::vector<double>& adjoint_energy_grid,
    std::shared_ptr<BremsstrahlungAdjointElectronScatteringDistribution>&
        scattering_distribution,
    const double evaluation_tol )
{
  // Make sure the eval tol is valid
  testPrecondition( evaluation_tol <= 1.0 );
  testPrecondition( evaluation_tol > 0.0 );

  // Create the scattering function
  std::shared_ptr<Utility::FullyTabularBasicBivariateDistribution> energy_gain_function;

  BremsstrahlungAdjointElectronScatteringDistributionNativeFactory::createEnergyGainFunction<TwoDInterpPolicy,TwoDGridPolicy>(
        raw_electroatom_data,
        adjoint_energy_grid,
        energy_gain_function,
        evaluation_tol );

  scattering_distribution.reset(
   new BremsstrahlungAdjointElectronScatteringDistribution(
                                energy_gain_function ) );
}

// Create the energy gain function
template<typename TwoDInterpPolicy, template<typename> class TwoDGridPolicy>
void BremsstrahlungAdjointElectronScatteringDistributionNativeFactory::createEnergyGainFunction(
    const Data::AdjointElectronPhotonRelaxationDataContainer& raw_electroatom_data,
    const std::vector<double> energy_grid,
    std::shared_ptr<Utility::FullyTabularBasicBivariateDistribution>& energy_gain_function,
    const double evaluation_tol )
{
  // Get the function data
  std::vector<double> primary_grid( energy_grid.size() );
  std::vector<std::shared_ptr<const Utility::TabularUnivariateDistribution> >
    secondary_dists( energy_grid.size() );

  for( size_t n = 0; n < energy_grid.size(); ++n )
  {
    primary_grid[n] = energy_grid[n];

    // Get the outgoing energy of the adjoint bremsstrahlung electron at the incoming energy
    std::vector<double> outgoing_energy(
      raw_electroatom_data.getAdjointElectronBremsstrahlungEnergy( energy_grid[n] ) );

    // Get the adjoint bremsstrahlung pdf at the incoming energy
    std::vector<double> pdf(
      raw_electroatom_data.getAdjointElectronBremsstrahlungPDF( energy_grid[n] ) );

    secondary_dists[n].reset(
      new const Utility::TabularDistribution<Utility::LinLin>( outgoing_energy,
                                                               pdf ) );
  }

  // Create the scattering function
  energy_gain_function.reset(
    new Utility::InterpolatedFullyTabularBasicBivariateDistribution<TwoDGridPolicy<TwoDInterpPolicy> >(
                                                            primary_grid,
                                                            secondary_dists,
                                                            1e-6,
                                                            evaluation_tol ) );
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_BremsstrahlungAdjointElectronScatteringDistributionNativeFactory_def.hpp
//---------------------------------------------------------------------------//

