//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_AtomicExcitationElectronScatteringDistributionNativeFactory.cpp
//! \author Luke Kersting
//! \brief  The atomic excitation scattering distribution Native factory definition
//!
//---------------------------------------------------------------------------//

// Trilinos Includes
#include <Teuchos_Array.hpp>
#include <Teuchos_ArrayView.hpp>

// FRENSIE Includes
#include "MonteCarlo_AtomicExcitationElectronScatteringDistributionNativeFactory.hpp"
#include "Utility_TabularDistribution.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Create a atomic excitation distribution
void AtomicExcitationElectronScatteringDistributionNativeFactory::createAtomicExcitationDistribution(
			  const Data::ElectronPhotonRelaxationDataContainer& raw_electroatom_data,
			  Teuchos::RCP<const AtomicExcitationElectronScatteringDistribution>&
			    energy_loss_distribution )
{
  // Create the energy loss function
  AtomicExcitationElectronScatteringDistribution::AtomicDistribution
                                                    energy_loss_function;

  AtomicExcitationElectronScatteringDistributionNativeFactory::createEnergyLossFunction(
							  raw_electroatom_data,
							  energy_loss_function );

  energy_loss_distribution.reset(
   new AtomicExcitationElectronScatteringDistribution( energy_loss_function ) );
}

// Create the energy loss function
void AtomicExcitationElectronScatteringDistributionNativeFactory::createEnergyLossFunction(
	   const Data::ElectronPhotonRelaxationDataContainer& raw_electroatom_data,
           AtomicExcitationElectronScatteringDistribution::AtomicDistribution&
                                                        energy_loss_function )
{
  // Extract the energy grid for atomic excitation energy loss
  Teuchos::Array<double> excitation_energy_grid(
        raw_electroatom_data.getAtomicExcitationEnergyGrid() );

  // Extract the energy loss for atomic excitation
  Teuchos::Array<double> energy_loss (
        raw_electroatom_data.getAtomicExcitationEnergyLoss() );

  energy_loss_function.reset(
    new Utility::TabularDistribution<Utility::LinLin>( excitation_energy_grid,
                                                       energy_loss ) );
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_AtomicExcitationElectronScatteringDistributionNativeFactory.cpp
//---------------------------------------------------------------------------//

