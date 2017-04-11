//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ElectroionizationSubshellAdjointElectronScatteringDistributionNativeFactory_def.hpp
//! \author Luke Kersting
//! \brief  The electroionization subshell scattering distribution Native factory definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "Utility_TabularDistribution.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Create a electroionization subshell distribution
template<typename TwoDInterpPolicy>
void ElectroionizationSubshellAdjointElectronScatteringDistributionNativeFactory::createAdjointElectroionizationSubshellDistribution(
    const Data::AdjointElectronPhotonRelaxationDataContainer& raw_electroionization_data,
    const unsigned subshell,
    const double binding_energy,
    std::shared_ptr<const ElectroionizationSubshellAdjointElectronScatteringDistribution>&
      electroionization_subshell_distribution,
    const bool correlated_sampling_mode_on,
    const bool unit_based_interpolation_mode_on,
    const double evaluation_tol )
{
  // Get the energies for which knock-on sampling tables are given
  std::vector<double> energy_grid =
        raw_electroionization_data.getAdjointElectronEnergyGrid();

  // Subshell distribution
  std::shared_ptr<Utility::FullyTabularTwoDDistribution> subshell_distribution;

  // Create the subshell distribution
  ElectroionizationSubshellAdjointElectronScatteringDistributionNativeFactory::createSubshellDistribution<TwoDInterpPolicy>(
                                raw_electroionization_data,
                                energy_grid,
                                subshell,
                                subshell_distribution,
                                evaluation_tol );

  electroionization_subshell_distribution.reset(
    new ElectroionizationSubshellAdjointElectronScatteringDistribution(
            subshell_distribution,
            binding_energy,
            correlated_sampling_mode_on,
            unit_based_interpolation_mode_on ) );
}

// Create the subshell recoil distribution
template<typename TwoDInterpPolicy>
void ElectroionizationSubshellAdjointElectronScatteringDistributionNativeFactory::createSubshellDistribution(
    const Data::AdjointElectronPhotonRelaxationDataContainer& raw_electroionization_data,
    const std::vector<double> energy_grid,
    const unsigned subshell,
    std::shared_ptr<Utility::FullyTabularTwoDDistribution>&
        subshell_distribution,
    const double evaluation_tol )
{
  // Create the scattering function
  Utility::FullyTabularTwoDDistribution::DistributionType
     function_data( energy_grid.size() );

  for( unsigned n = 0; n < energy_grid.size(); ++n )
  {
    function_data[n].first = energy_grid[n];

    // Get the recoil energy distribution at the incoming energy
    Teuchos::Array<double> recoil_energy(
        raw_electroionization_data.getAdjointElectroionizationRecoilEnergy(
            subshell,
            energy_grid[n] ) );

    // Get the recoil energy pdf at the incoming energy
    Teuchos::Array<double> pdf(
        raw_electroionization_data.getAdjointElectroionizationRecoilPDF(
            subshell,
            energy_grid[n] ) );

    function_data[n].second.reset(
      new const Utility::TabularDistribution<Utility::LinLin>( recoil_energy,
                                                               pdf ) );
  }

  // Create the scattering function
  subshell_distribution.reset(
    new Utility::InterpolatedFullyTabularTwoDDistribution<TwoDInterpPolicy>(
            function_data,
            1e-6,
            evaluation_tol ) );
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_ElectroionizationSubshellAdjointElectronScatteringDistributionNativeFactory_def.hpp
//---------------------------------------------------------------------------//

