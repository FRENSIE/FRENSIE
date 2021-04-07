//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_AtomicExcitationElectronScatteringDistributionNativeFactory.cpp
//! \author Luke Kersting
//! \brief  The atomic excitation scattering distribution Native factory definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_AtomicExcitationElectronScatteringDistributionNativeFactory.hpp"
#include "Utility_TabularDistribution.hpp"
#include "Utility_DesignByContract.hpp"

namespace MonteCarlo{

// Create a atomic excitation distribution
void AtomicExcitationElectronScatteringDistributionNativeFactory::createAtomicExcitationDistribution(
        const Data::ElectronPhotonRelaxationDataContainer& data_container,
        std::shared_ptr<const AtomicExcitationElectronScatteringDistribution>&
            energy_loss_distribution )
{
  // Create the energy loss function
  AtomicExcitationElectronScatteringDistribution::AtomicDistribution
                                                    energy_loss_function;

  AtomicExcitationElectronScatteringDistributionNativeFactory::createEnergyLossFunction(
            data_container,
            energy_loss_function );

  energy_loss_distribution.reset(
   new AtomicExcitationElectronScatteringDistribution( energy_loss_function ) );
}

// Create the energy loss function
void AtomicExcitationElectronScatteringDistributionNativeFactory::createEnergyLossFunction(
       const Data::ElectronPhotonRelaxationDataContainer& data_container,
           AtomicExcitationElectronScatteringDistribution::AtomicDistribution&
                                                        energy_loss_function )
{
  // Extract the energy grid for atomic excitation energy loss
  std::vector<double> excitation_energy_grid(
        data_container.getAtomicExcitationEnergyGrid() );

  // Extract the energy loss for atomic excitation
  std::vector<double> energy_loss(
        data_container.getAtomicExcitationEnergyLoss() );

  energy_loss_function.reset(
    new Utility::TabularDistribution<Utility::LogLog>( excitation_energy_grid,
                                                       energy_loss ) );
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_AtomicExcitationElectronScatteringDistributionNativeFactory.cpp
//---------------------------------------------------------------------------//

