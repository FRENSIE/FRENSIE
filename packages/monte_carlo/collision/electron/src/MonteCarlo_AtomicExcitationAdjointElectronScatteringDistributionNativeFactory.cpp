//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_AtomicExcitationAdjointElectronScatteringDistributionNativeFactory.cpp
//! \author Luke Kersting
//! \brief  The Atomic Excitation adjoint scattering distribution native factory definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_AtomicExcitationAdjointElectronScatteringDistributionNativeFactory.hpp"
#include "Utility_TabularDistribution.hpp"
#include "Utility_DesignByContract.hpp"

namespace MonteCarlo{

// Create a Atomic Excitation adjoint distribution
void AtomicExcitationAdjointElectronScatteringDistributionNativeFactory::createAtomicExcitationDistribution(
    const Data::AdjointElectronPhotonRelaxationDataContainer& raw_electroatom_data,
    std::shared_ptr<AtomicExcitationAdjointElectronScatteringDistribution>&
        scattering_distribution )
{
  // Create the scattering function
  std::shared_ptr<Utility::UnivariateDistribution> energy_gain_function;
  AtomicExcitationAdjointElectronScatteringDistributionNativeFactory::createEnergyGainFunction(
        raw_electroatom_data,
        energy_gain_function );

  scattering_distribution.reset(
   new AtomicExcitationAdjointElectronScatteringDistribution( energy_gain_function ) );
}

// Create the energy gain function
void AtomicExcitationAdjointElectronScatteringDistributionNativeFactory::createEnergyGainFunction(
    const Data::AdjointElectronPhotonRelaxationDataContainer& raw_electroatom_data,
    std::shared_ptr<Utility::UnivariateDistribution>& energy_gain_function )
{
  // Get the adjoint atomic excitation energy grid
  std::vector<double> energy_grid(
    raw_electroatom_data.getAdjointAtomicExcitationEnergyGrid() );

  // Get the adjoint atomic excitation energy gain
  std::vector<double> energy_gain(
    raw_electroatom_data.getAdjointAtomicExcitationEnergyGain() );

  // Create the energy gain distribution
  energy_gain_function.reset(
    new Utility::TabularDistribution<Utility::LogLog>( energy_grid,
                                                       energy_gain ) );
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_AtomicExcitationAdjointElectronScatteringDistributionNativeFactory.cpp
//---------------------------------------------------------------------------//

