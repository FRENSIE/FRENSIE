//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_BremsstrahlungElectronScatteringDistributionACEFactory.cpp
//! \author Luke Kersting
//! \brief  The bremsstrahlung scattering distribution ACE factory definition
//!
//---------------------------------------------------------------------------//

// Trilinos Includes
#include <Teuchos_ArrayView.hpp>

// FRENSIE Includes
#include "MonteCarlo_BremsstrahlungElectronScatteringDistributionACEFactory.hpp"
#include "MonteCarlo_BremsstrahlungElectronScatteringDistribution.hpp"
#include "Utility_HistogramDistribution.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Create a simple dipole bremsstrahlung distribution
void BremsstrahlungElectronScatteringDistributionACEFactory::createBremsstrahlungDistribution(
	const Data::XSSEPRDataExtractor& raw_electroatom_data,
	std::shared_ptr<const BremsstrahlungElectronScatteringDistribution>&
			  scattering_distribution )
{
  // Get the number of tables
  double size = raw_electroatom_data.extractBREMIBlock().size()/3;

  // Create the scattering function
  BremsstrahlungElectronScatteringDistribution::BremsstrahlungDistribution
         scattering_function( size );

  BremsstrahlungElectronScatteringDistributionACEFactory::createScatteringFunction(
							  raw_electroatom_data,
							  scattering_function );

  scattering_distribution.reset(
   new BremsstrahlungElectronScatteringDistribution( scattering_function ) );
}

// Create a detailed tabular bremsstrahlung distribution
void BremsstrahlungElectronScatteringDistributionACEFactory::createBremsstrahlungDistribution(
	const Data::XSSEPRDataExtractor& raw_electroatom_data,
	std::shared_ptr<const BremsstrahlungElectronScatteringDistribution>&
			          scattering_distribution,
        std::shared_ptr<Utility::OneDDistribution>& angular_distribution,
        const double lower_cutoff_energy,
        const double upper_cutoff_energy )
{
  // Get the number of tables
  double size = raw_electroatom_data.extractBREMIBlock().size()/3;

  // Create the scattering function
  BremsstrahlungElectronScatteringDistribution::BremsstrahlungDistribution
         scattering_function( size );

  BremsstrahlungElectronScatteringDistributionACEFactory::createScatteringFunction(
							  raw_electroatom_data,
							  scattering_function );

  scattering_distribution.reset(
   new BremsstrahlungElectronScatteringDistribution( scattering_function,
                                                     angular_distribution,
                                                     lower_cutoff_energy,
                                                     upper_cutoff_energy  ) );
}

// Create a detailed 2BS bremsstrahlung distribution
void BremsstrahlungElectronScatteringDistributionACEFactory::createBremsstrahlungDistribution(
	const Data::XSSEPRDataExtractor& raw_electroatom_data,
	std::shared_ptr<const BremsstrahlungElectronScatteringDistribution>&
		                  scattering_distribution,
    const int atomic_number )
{
  // Get the number of tables
  double size = raw_electroatom_data.extractBREMIBlock().size()/3;

  // Create the scattering function
  BremsstrahlungElectronScatteringDistribution::BremsstrahlungDistribution
         scattering_function( size );

  BremsstrahlungElectronScatteringDistributionACEFactory::createScatteringFunction(
							  raw_electroatom_data,
							  scattering_function );

  scattering_distribution.reset(
   new BremsstrahlungElectronScatteringDistribution( scattering_function,
                                                     atomic_number ) );
}

// Create the energy loss function
void BremsstrahlungElectronScatteringDistributionACEFactory::createScatteringFunction(
	   const Data::XSSEPRDataExtractor& raw_electroatom_data,
           BremsstrahlungElectronScatteringDistribution::BremsstrahlungDistribution&
                                                        scattering_function )
{
  // Extract the bremsstrahlung scattering information data block (BREMI)
  Teuchos::ArrayView<const double> bremi_block(
				    raw_electroatom_data.extractBREMIBlock() );

  // Extract the number of tabulated distributions
  int N = bremi_block.size()/3;

  // Extract the electron energy grid for bremsstrahlung energy distributions
  Teuchos::Array<double> electron_energy_grid(bremi_block(0,N));

  // Extract the table lengths for bremsstrahlung energy distributions
  Teuchos::Array<double> table_length(bremi_block(N,N));

  // Extract the offsets for bremsstrahlung energy distributions
  Teuchos::Array<double> offset(bremi_block(2*N,N));

  // Extract the bremsstrahlung photon energy distributions block (BREME)
  Teuchos::ArrayView<const double> breme_block =
    raw_electroatom_data.extractBREMEBlock();

  for( unsigned n = 0; n < N; ++n )
  {
    Utility::get<0>( scattering_function[n] ) = electron_energy_grid[n];

    Utility::get<1>( scattering_function[n] ).reset(
	  new Utility::HistogramDistribution(
	      breme_block( offset[n], table_length[n] ),
	      breme_block( offset[n] + 1 + table_length[n], table_length[n]-1 ),
          true ) );
  }
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_BremsstrahlungElectronScatteringDistributionACEFactory.cpp
//---------------------------------------------------------------------------//

