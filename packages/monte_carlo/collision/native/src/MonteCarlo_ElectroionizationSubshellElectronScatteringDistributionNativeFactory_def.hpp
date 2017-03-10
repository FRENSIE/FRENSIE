//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ElectroionizationSubshellElectronScatteringDistributionNativeFactory_def.hpp
//! \author Luke Kersting
//! \brief  The electroionization subshell scattering distribution Native factory definition
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_ELECTRIONIZATION_SUBSHELL_ELECTRON_SCATTERING_DISTRIBUTION_NATIVE_FACTORY_DEF_HPP
#define MONTE_CARLO_ELECTRIONIZATION_SUBSHELL_ELECTRON_SCATTERING_DISTRIBUTION_NATIVE_FACTORY_DEF_HPP


// FRENSIE Includes
#include "Utility_TabularDistribution.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Create a electroionization subshell distribution
template <typename TwoDInterpPolicy>
void
ElectroionizationSubshellElectronScatteringDistributionNativeFactory::createElectroionizationSubshellDistribution(
    const Data::ElectronPhotonRelaxationDataContainer& raw_electroionization_data,
    const unsigned subshell,
    const double binding_energy,
    std::shared_ptr<const ElectroionizationSubshellElectronScatteringDistribution>&
      electroionization_subshell_distribution,
    const bool use_weighted_interpolation,
    const double evaluation_tol )
{
  // Get the energies for which knock-on sampling tables are given
  std::vector<double> energy_grid =
        raw_electroionization_data.getElectroionizationEnergyGrid( subshell );

  // Subshell distribution
  std::shared_ptr<Utility::FullyTabularTwoDDistribution> subshell_distribution;

  // Create the subshell distribution
  createSubshellDistribution<TwoDInterpPolicy>( raw_electroionization_data,
                              energy_grid,
                              subshell,
                              subshell_distribution,
                              evaluation_tol );

  electroionization_subshell_distribution.reset(
    new ElectroionizationSubshellElectronScatteringDistribution(
            subshell_distribution,
            binding_energy,
            use_weighted_interpolation ) );
}

// Create the subshell recoil distribution
template <typename TwoDInterpPolicy>
void
ElectroionizationSubshellElectronScatteringDistributionNativeFactory::createSubshellDistribution(
    const Data::ElectronPhotonRelaxationDataContainer& raw_electroionization_data,
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
        raw_electroionization_data.getElectroionizationRecoilEnergy(
            subshell,
            energy_grid[n] ) );

    // Get the recoil energy pdf at the incoming energy
    Teuchos::Array<double> pdf(
        raw_electroionization_data.getElectroionizationRecoilPDF(
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

#endif // end MONTE_CARLO_ELECTRIONIZATION_SUBSHELL_ELECTRON_SCATTERING_DISTRIBUTION_NATIVE_FACTORY_DEF_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ElectroionizationSubshellElectronScatteringDistributionNativeFactory.cpp
//---------------------------------------------------------------------------//
