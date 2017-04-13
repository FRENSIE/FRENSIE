//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_BremsstrahlungAdjointElectronScatteringDistributionNativeFactory_def.hpp
//! \author Luke Kersting
//! \brief  The bremsstrahlung adjoint scattering distribution native factory definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "Utility_TabularDistribution.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Create a bremsstrahlung adjoint distribution
template<typename TwoDInterpPolicy>
void BremsstrahlungAdjointElectronScatteringDistributionNativeFactory::createBremsstrahlungDistribution(
    const Data::AdjointElectronPhotonRelaxationDataContainer& raw_electroatom_data,
    const std::vector<double>& adjoint_energy_grid,
    std::shared_ptr<const BremsstrahlungAdjointElectronScatteringDistribution>&
        scattering_distribution,
    const bool correlated_sampling_mode_on,
    const bool unit_based_interpolation_mode_on,
    const double evaluation_tol )
{
  // Make sure bool are valid
  testPrecondition( correlated_sampling_mode_on == 0 ||
                    correlated_sampling_mode_on == 1 );
  testPrecondition( unit_based_interpolation_mode_on == 0 ||
                    unit_based_interpolation_mode_on == 1 );
  // Make sure the eval tol is valid
  testPrecondition( evaluation_tol <= 1.0 );
  testPrecondition( evaluation_tol > 0.0 );

  // Create the scattering function
  std::shared_ptr<Utility::FullyTabularTwoDDistribution> energy_gain_function;

  BremsstrahlungAdjointElectronScatteringDistributionNativeFactory::createEnergyGainFunction<TwoDInterpPolicy>(
        raw_electroatom_data,
        adjoint_energy_grid,
        energy_gain_function,
        evaluation_tol );

  scattering_distribution.reset(
   new BremsstrahlungAdjointElectronScatteringDistribution(
                                energy_gain_function,
                                correlated_sampling_mode_on,
                                unit_based_interpolation_mode_on ) );
}

// Create the energy gain function
template<typename TwoDInterpPolicy>
void BremsstrahlungAdjointElectronScatteringDistributionNativeFactory::createEnergyGainFunction(
    const Data::AdjointElectronPhotonRelaxationDataContainer& raw_electroatom_data,
    const std::vector<double> energy_grid,
    std::shared_ptr<Utility::FullyTabularTwoDDistribution>& energy_gain_function,
    const double evaluation_tol )
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
    new Utility::InterpolatedFullyTabularTwoDDistribution<TwoDInterpPolicy>(
            function_data,
            1e-6,
            evaluation_tol ) );
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_BremsstrahlungAdjointElectronScatteringDistributionNativeFactory_def.hpp
//---------------------------------------------------------------------------//

