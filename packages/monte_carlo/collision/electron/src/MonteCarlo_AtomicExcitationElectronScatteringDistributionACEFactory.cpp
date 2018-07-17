//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_AtomicExcitationElectronScatteringDistributionACEFactory.cpp
//! \author Luke Kersting
//! \brief  The atomic excitation scattering distribution ACE factory definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_AtomicExcitationElectronScatteringDistributionACEFactory.hpp"
#include "Utility_TabularDistribution.hpp"
#include "Utility_DesignByContract.hpp"

namespace MonteCarlo{

// Create a atomic excitation distribution
void AtomicExcitationElectronScatteringDistributionACEFactory::createAtomicExcitationDistribution(
			  const Data::XSSEPRDataExtractor& raw_electroatom_data,
			  std::shared_ptr<const AtomicExcitationElectronScatteringDistribution>&
			    energy_loss_distribution )
{
  // Create the energy loss function
  AtomicExcitationElectronScatteringDistribution::AtomicDistribution
                                                    energy_loss_function;

  AtomicExcitationElectronScatteringDistributionACEFactory::createEnergyLossFunction(
							  raw_electroatom_data,
							  energy_loss_function );

  energy_loss_distribution.reset(
   new AtomicExcitationElectronScatteringDistribution( energy_loss_function ) );
}

// Create the energy loss function
void AtomicExcitationElectronScatteringDistributionACEFactory::createEnergyLossFunction(
	   const Data::XSSEPRDataExtractor& raw_electroatom_data,
           AtomicExcitationElectronScatteringDistribution::AtomicDistribution&
                                                        energy_loss_function )
{
   // Extract the atomic excitation scattering information data block (EXCIT)
  Utility::ArrayView<const double> excit_block(
				      raw_electroatom_data.extractEXCITBlock() );

  // Extract the number of tabulated energies
  int size = excit_block.size()/2;

  // Extract the energy grid for atomic excitation energy loss
  std::vector<double> excitation_energy_grid(excit_block(0,size));

  // Extract the energy loss for atomic excitation
  std::vector<double> energy_loss(excit_block(size,size));

  // Check if the file version is eprdata14 or eprdata12
  if ( raw_electroatom_data.isEPRVersion14() )
  {
    energy_loss_function.reset(
      new Utility::TabularDistribution<Utility::LogLog>( excitation_energy_grid,
                                                         energy_loss ) );
  }
  else
  {
    energy_loss_function.reset(
      new Utility::TabularDistribution<Utility::LinLin>( excitation_energy_grid,
                                                         energy_loss ) );
  }
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_AtomicExcitationElectronScatteringDistributionACEFactory.cpp
//---------------------------------------------------------------------------//

