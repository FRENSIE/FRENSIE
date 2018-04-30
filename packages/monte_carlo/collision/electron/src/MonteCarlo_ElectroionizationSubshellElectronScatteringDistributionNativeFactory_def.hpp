//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ElectroionizationSubshellElectronScatteringDistributionNativeFactory_def.hpp
//! \author Luke Kersting
//! \brief  The electroionization subshell scattering distribution Native factory definition
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_ELECTROIONIZATION_SUBSHELL_ELECTRON_SCATTERING_DISTRIBUTION_NATIVE_FACTORY_DEF_HPP
#define MONTE_CARLO_ELECTROIONIZATION_SUBSHELL_ELECTRON_SCATTERING_DISTRIBUTION_NATIVE_FACTORY_DEF_HPP


// FRENSIE Includes
#include "Utility_TabularDistribution.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Create a electroionization subshell distribution
template <typename TwoDInterpPolicy,
          template<typename> class TwoDGridPolicy>
void ElectroionizationSubshellElectronScatteringDistributionNativeFactory::createElectroionizationSubshellDistribution(
    const Data::ElectronPhotonRelaxationDataContainer& raw_electroionization_data,
    const unsigned subshell,
    const double binding_energy,
    std::shared_ptr<const ElectroionizationSubshellElectronScatteringDistribution>&
      electroionization_subshell_distribution,
    const double evaluation_tol )
{
  // Make sure the subshell is valid
  testPrecondition( subshell >= 0 );
  // Make sure the binding energy is valid
  testPrecondition( binding_energy > 0.0 );
  // Make sure the evaluation tol is valid
  testPrecondition( evaluation_tol > 0.0 );

  // Get the energies for which knock-on sampling tables are given
  std::vector<double> energy_grid =
        raw_electroionization_data.getElectroionizationEnergyGrid( subshell );

  // Subshell distribution
  std::shared_ptr<const Utility::FullyTabularBasicBivariateDistribution>
    subshell_distribution;

  // Create the subshell distribution
  ThisType::createSubshellDistribution<TwoDInterpPolicy,TwoDGridPolicy>(
            raw_electroionization_data,
            energy_grid,
            subshell,
            subshell_distribution,
            evaluation_tol );

  electroionization_subshell_distribution.reset(
    new ElectroionizationSubshellElectronScatteringDistribution(
            subshell_distribution,
            binding_energy ) );
}

// Create the subshell recoil distribution
template<typename TwoDInterpPolicy,
         template<typename> class TwoDGridPolicy>
void ElectroionizationSubshellElectronScatteringDistributionNativeFactory::createSubshellDistribution(
    const Data::ElectronPhotonRelaxationDataContainer& raw_electroionization_data,
    const std::vector<double> energy_grid,
    const unsigned subshell,
    std::shared_ptr<const Utility::FullyTabularBasicBivariateDistribution>&
        subshell_distribution,
    const double evaluation_tol )
{
  // Make sure the subshell is valid
  testPrecondition( subshell >= 0 );
  // Make sure the evaluation tol is valid
  testPrecondition( evaluation_tol > 0.0 );

  // Create the scattering function
  std::vector<double> primary_grid( energy_grid.size() );
  std::vector<std::shared_ptr<const Utility::TabularUnivariateDistribution> >
    secondary_dists( energy_grid.size() );
  
  for( size_t n = 0; n < energy_grid.size(); ++n )
  {
    primary_grid[n] = energy_grid[n];

    // Get the recoil energy distribution at the incoming energy
    std::vector<double> recoil_energy(
        raw_electroionization_data.getElectroionizationRecoilEnergy(
            subshell,
            energy_grid[n] ) );

    // Get the recoil energy pdf at the incoming energy
    std::vector<double> pdf(
        raw_electroionization_data.getElectroionizationRecoilPDF(
            subshell,
            energy_grid[n] ) );

    secondary_dists[n].reset(
      new const Utility::TabularDistribution<Utility::LogLog>( recoil_energy,
                                                               pdf ) );
  }

  // Create the scattering function
  subshell_distribution.reset(
    new Utility::InterpolatedFullyTabularBasicBivariateDistribution<TwoDGridPolicy<TwoDInterpPolicy> >(
            primary_grid,
            secondary_dists,
            1e-6,
            evaluation_tol ) );
}

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_ELECTROIONIZATION_SUBSHELL_ELECTRON_SCATTERING_DISTRIBUTION_NATIVE_FACTORY_DEF_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ElectroionizationSubshellElectronScatteringDistributionNativeFactory.cpp
//---------------------------------------------------------------------------//
