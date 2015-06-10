//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_AtomicExcitationAdjointElectronScatteringDistributionACEFactory.cpp
//! \author Luke Kersting
//! \brief  The atomic excitation adjoint scattering distribution ACE factory definition
//!
//---------------------------------------------------------------------------//

// Trilinos Includes
#include <Teuchos_Array.hpp>
#include <Teuchos_ArrayView.hpp>

// FRENSIE Includes
#include "MonteCarlo_AtomicExcitationAdjointElectronScatteringDistributionACEFactory.hpp"
#include "Utility_TabularDistribution.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Create a atomic excitation distribution
void AtomicExcitationAdjointElectronScatteringDistributionACEFactory::createAtomicExcitationAdjointDistribution(
			  const Data::XSSEPRDataExtractor& raw_electroatom_data,
			  Teuchos::RCP<const AtomicExcitationAdjointElectronScatteringDistribution>&
			  energy_gain_distribution )
{
  // Create the energy gain function
  AtomicExcitationAdjointElectronScatteringDistribution::AtomicDistribution 
                                                           energy_gain_function;

  AtomicExcitationAdjointElectronScatteringDistributionACEFactory::createEnergyGainFunction( 
							 raw_electroatom_data,
							 energy_gain_function );

  // Get the max energy
  double max_energy = 20.0;

  energy_gain_distribution.reset( 
    new AtomicExcitationAdjointElectronScatteringDistribution( 
                                                       max_energy,
                                                       energy_gain_function ) );
}


// Create the energy gain function
void AtomicExcitationAdjointElectronScatteringDistributionACEFactory::createEnergyGainFunction(
	   const Data::XSSEPRDataExtractor& raw_electroatom_data,
           AtomicExcitationAdjointElectronScatteringDistribution::AtomicDistribution& 
                                                        energy_gain_function )
{
   // Extract the atomic excitation scattering information data block (EXCIT)
  Teuchos::ArrayView<const double> excit_block(
				      raw_electroatom_data.extractEXCITBlock() );
  
  // Extract the number of tabulated energies
  int size = excit_block.size()/2;

  // Extract the energy grid for atomic excitation energy gain
  Teuchos::Array<double> excitation_energy_grid(excit_block(0,size));

  // Extract the energy gain for atomic excitation
  Teuchos::Array<double> energy_gain(excit_block(size,size));

  energy_gain_function.reset( 
    new Utility::TabularDistribution<Utility::LinLin>( excitation_energy_grid,
		                                       energy_gain ) );
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_AtomicExcitationAdjointElectronScatteringDistributionACEFactory.cpp
//---------------------------------------------------------------------------//

