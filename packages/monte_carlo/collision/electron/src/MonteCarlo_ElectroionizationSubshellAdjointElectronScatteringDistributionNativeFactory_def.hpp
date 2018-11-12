//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ElectroionizationSubshellAdjointElectronScatteringDistributionNativeFactory_def.hpp
//! \author Luke Kersting
//! \brief  The electroionization subshell scattering distribution Native factory definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "Utility_TabularDistribution.hpp"
#include "Utility_Vector.hpp"
#include "Utility_DesignByContract.hpp"

namespace MonteCarlo{

// Create a electroionization subshell distribution
template<typename TwoDInterpPolicy, template<typename> class TwoDGridPolicy>
void ElectroionizationSubshellAdjointElectronScatteringDistributionNativeFactory::createElectroionizationSubshellDistribution(
    const Data::AdjointElectronPhotonRelaxationDataContainer& raw_electroionization_data,
    const unsigned subshell,
    const double binding_energy,
    std::shared_ptr<ElectroionizationSubshellAdjointElectronScatteringDistribution>&
      electroionization_subshell_distribution,
    const double evaluation_tol )
{
  // Subshell distribution
  std::shared_ptr<Utility::FullyTabularBasicBivariateDistribution> subshell_distribution;

  // Create the subshell distribution
  ThisType::createSubshellDistribution<TwoDInterpPolicy,TwoDGridPolicy>(
    raw_electroionization_data,
    raw_electroionization_data.getAdjointElectroionizationEnergyGrid( subshell ),
    subshell,
    subshell_distribution,
    evaluation_tol );

  electroionization_subshell_distribution.reset(
    new ElectroionizationSubshellAdjointElectronScatteringDistribution(
            subshell_distribution,
            binding_energy ) );
}

// Create the subshell recoil distribution
template<typename TwoDInterpPolicy, template<typename> class TwoDGridPolicy>
void ElectroionizationSubshellAdjointElectronScatteringDistributionNativeFactory::createSubshellDistribution(
    const Data::AdjointElectronPhotonRelaxationDataContainer& raw_electroionization_data,
    const std::vector<double> energy_grid,
    const unsigned subshell,
    std::shared_ptr<Utility::FullyTabularBasicBivariateDistribution>&
        subshell_distribution,
    const double evaluation_tol )
{
  // Create the scattering function
  std::vector<double> primary_grid( energy_grid.size() );
  std::vector<std::shared_ptr<const Utility::TabularUnivariateDistribution> >
    secondary_dists( energy_grid.size() );

  for( size_t n = 0; n < energy_grid.size(); ++n )
  {
    primary_grid[n] = energy_grid[n];

    // Get the recoil energy distribution at the incoming energy
    std::vector<double> recoil_energy(
        raw_electroionization_data.getAdjointElectroionizationRecoilEnergy(
            subshell,
            energy_grid[n] ) );

    // Get the recoil energy pdf at the incoming energy
    std::vector<double> pdf(
        raw_electroionization_data.getAdjointElectroionizationRecoilPDF(
            subshell,
            energy_grid[n] ) );

    secondary_dists[n].reset(
      new const Utility::TabularDistribution<Utility::LinLin>( recoil_energy,
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

//---------------------------------------------------------------------------//
// end MonteCarlo_ElectroionizationSubshellAdjointElectronScatteringDistributionNativeFactory_def.hpp
//---------------------------------------------------------------------------//

